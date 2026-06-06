//! Pretty-printer for the PascalM AST.
//!
//! Walks a parsed [`CompilationUnit`] and renders canonical, consistently
//! indented Pascal source. Used by the language server's `textDocument/formatting`.
//!
//! ## Comments
//!
//! The lexer discards comments (`{ }`, `(* *)`) before they reach the AST, so
//! they cannot be recovered from the tree. Instead, [`format_compilation_unit`]
//! re-scans the original source for comments (with byte offsets) and re-inserts
//! them during formatting, anchoring each to the AST node it precedes via the
//! spans the AST already carries on identifiers, calls and declarations.
//!
//! Placement is faithful for the common cases (header comments, comments above
//! declarations/procedures and section keywords, between statements, and
//! trailing `;`-line comments). A comment above a `label`/`const`/`type`/`var`
//! keyword stays above the keyword (anchored via [`SectionSpans`]), while one
//! between the keyword and the first declaration stays inside the section.
//! Known cosmetic edge cases: a comment sitting immediately before a *nested*
//! `end` may move just past it, and comments between reordered declaration
//! sections (e.g. a `var` interleaved with `const`) may shift, because the
//! formatter groups sections by kind.

use crate::ast::*;

const INDENT: &str = "  ";

/// A comment recovered from the source, with its starting byte offset and
/// whether only whitespace precedes it on its line (a standalone comment) as
/// opposed to trailing code (`x := 1; { trailing }`).
struct Comment {
    start: usize,
    text: String,
    own_line: bool,
}

/// Format a whole compilation unit into canonical Pascal source. `source` is the
/// original text the `unit` was parsed from; it is used only to recover comments.
pub fn format_compilation_unit(unit: &CompilationUnit, source: &str) -> String {
    let mut f = Formatter::new(collect_comments(source), line_starts(source));
    f.compilation_unit(unit);
    f.flush_rest();
    f.out
}

/// Byte offset of the start of each line, so an offset can be mapped to a line.
fn line_starts(source: &str) -> Vec<usize> {
    let mut starts = vec![0];
    for (i, b) in source.bytes().enumerate() {
        if b == b'\n' {
            starts.push(i + 1);
        }
    }
    starts
}

struct Formatter {
    out: String,
    indent: usize,
    comments: Vec<Comment>,
    cidx: usize,
    line_starts: Vec<usize>,
    /// A blank line requested but not yet written. Deferring it lets a trailing
    /// comment attach to the real line that precedes the blank, instead of to
    /// the blank itself.
    pending_blank: bool,
}

impl Formatter {
    fn new(comments: Vec<Comment>, line_starts: Vec<usize>) -> Self {
        Self {
            out: String::new(),
            indent: 0,
            comments,
            cidx: 0,
            line_starts,
            pending_blank: false,
        }
    }

    /// 0-based source line containing `offset`.
    fn line_of(&self, offset: usize) -> usize {
        self.line_starts.partition_point(|&s| s <= offset).saturating_sub(1)
    }

    /// Flush pending comments that sit on or before source `line`. Used right
    /// after emitting a statement to attach its trailing comment to that
    /// statement's line — before any following `end`/`until`/blank — instead of
    /// letting it drift to a later flush point.
    fn flush_through_line(&mut self, line: usize) {
        while self.cidx < self.comments.len()
            && self.line_of(self.comments[self.cidx].start) <= line
        {
            let text = self.comments[self.cidx].text.clone();
            let own_line = self.comments[self.cidx].own_line;
            self.cidx += 1;
            self.emit_comment(&text, own_line);
        }
    }

    // ---- comment re-insertion ------------------------------------------

    /// Emit every pending comment whose source position precedes `offset`.
    /// Standalone comments go on their own line at the current indentation;
    /// trailing comments are appended to the previously emitted line.
    fn flush_before(&mut self, offset: usize) {
        while self.cidx < self.comments.len() && self.comments[self.cidx].start < offset {
            let text = self.comments[self.cidx].text.clone();
            let own_line = self.comments[self.cidx].own_line;
            self.cidx += 1;
            self.emit_comment(&text, own_line);
        }
    }

    /// Emit one comment: standalone comments go on their own line at the current
    /// indentation; trailing comments re-attach to the real line just written
    /// (before any deferred blank line).
    fn emit_comment(&mut self, text: &str, own_line: bool) {
        if own_line || !self.out.ends_with('\n') {
            self.materialize_blank();
            self.out.push_str(&INDENT.repeat(self.indent));
            self.out.push_str(text);
            self.out.push('\n');
        } else {
            self.out.pop(); // drop the '\n'
            self.out.push_str("  ");
            self.out.push_str(text);
            self.out.push('\n');
        }
    }

    /// Emit all comments not yet placed. Call at the end of the outermost block.
    fn flush_rest(&mut self) {
        self.flush_before(usize::MAX);
    }

    /// Flush any comments that start before `node`, if a position is known.
    fn flush_for(&mut self, node: Option<usize>) {
        if let Some(off) = node {
            self.flush_before(off);
        }
    }

    /// Emit `s` prefixed with the current indentation, followed by a newline.
    /// `s` may itself contain newlines (e.g. an inline record type); those inner
    /// lines are expected to already carry their own absolute indentation.
    fn writeln(&mut self, s: &str) {
        self.materialize_blank();
        self.out.push_str(&INDENT.repeat(self.indent));
        self.out.push_str(s);
        self.out.push('\n');
    }

    fn blank(&mut self) {
        self.pending_blank = true;
    }

    fn materialize_blank(&mut self) {
        if self.pending_blank {
            self.pending_blank = false;
            if !self.out.is_empty() {
                self.out.push('\n');
            }
        }
    }

    // ---- top level ------------------------------------------------------

    fn compilation_unit(&mut self, unit: &CompilationUnit) {
        match unit {
            CompilationUnit::Program(p) => self.program(p),
            CompilationUnit::Unit(u) => self.unit(u),
        }
    }

    fn program(&mut self, p: &Program) {
        // Flush any file-header comment so it stays above the `program` line.
        self.flush_before(p.kw_offset);
        let heading = match &p.heading {
            Some(h) if !h.is_empty() => format!("({})", h.join(", ")),
            _ => String::new(),
        };
        self.writeln(&format!("program {}{};", p.name, heading));
        self.uses_clause(&p.uses);
        self.blank();
        self.block(&p.block, ".", true);
    }

    fn unit(&mut self, u: &Unit) {
        // Flush any file-header comment so it stays above the `unit` line.
        self.flush_before(u.kw_offset);
        self.writeln(&format!("unit {};", u.name));
        self.blank();
        self.writeln("interface");
        self.blank();
        self.interface_section(&u.interface);
        self.blank();
        self.writeln("implementation");
        self.blank();
        self.implementation_section(&u.implementation);
        match &u.initialization {
            Some(stmts) if !stmts.is_empty() => {
                self.blank();
                self.writeln("initialization");
                self.indent += 1;
                self.statement_list(stmts);
                self.indent -= 1;
                self.flush_rest();
                self.writeln("end.");
            }
            _ => {
                self.flush_rest();
                self.writeln("end.");
            }
        }
    }

    fn interface_section(&mut self, s: &InterfaceSection) {
        self.uses_clause(&s.uses);
        self.opt_const_section(&s.constants, None);
        self.opt_type_section(&s.types, None);
        self.opt_var_section(&s.variables, None);
        if let Some(headers) = &s.headers {
            for pf in headers {
                // Flush comments above each header so they don't drift down into
                // the implementation section.
                let name_span = match pf {
                    ProcFuncDecl::Procedure { name_span, .. }
                    | ProcFuncDecl::Function { name_span, .. } => *name_span,
                };
                self.flush_before(name_span.start);
                let sig = self.proc_func_signature(pf);
                self.writeln(&format!("{};", sig));
            }
        }
    }

    fn implementation_section(&mut self, s: &ImplementationSection) {
        self.uses_clause(&s.uses);
        self.opt_const_section(&s.constants, None);
        self.opt_type_section(&s.types, None);
        self.opt_var_section(&s.variables, None);
        if let Some(bodies) = &s.bodies {
            for pf in bodies {
                self.proc_func(pf);
                self.blank();
            }
        }
    }

    fn uses_clause(&mut self, uses: &Option<Vec<String>>) {
        if let Some(u) = uses {
            if !u.is_empty() {
                self.writeln(&format!("uses {};", u.join(", ")));
            }
        }
    }

    // ---- blocks & declarations -----------------------------------------

    fn block(&mut self, b: &Block, terminator: &str, flush_tail: bool) {
        let had_decls = self.declarations(b);
        if had_decls {
            self.blank();
        }
        self.writeln("begin");
        self.indent += 1;
        self.statement_list(&b.statements);
        self.indent -= 1;
        // Only the outermost block may safely flush every remaining comment;
        // a nested block would otherwise steal comments belonging to its parent.
        if flush_tail {
            self.flush_rest();
        }
        self.writeln(&format!("end{}", terminator));
    }

    /// Emit the declaration sections of a block. Returns whether anything was emitted.
    fn declarations(&mut self, b: &Block) -> bool {
        let mut emitted = false;
        if let Some(labels) = &b.labels {
            if !labels.is_empty() {
                // Flush a section-header comment (`{ labels }`) above the keyword.
                self.flush_for(b.section_spans.labels);
                let joined = labels
                    .iter()
                    .map(|l| l.to_string())
                    .collect::<Vec<_>>()
                    .join(", ");
                self.writeln(&format!("label {};", joined));
                emitted = true;
            }
        }
        emitted |= self.opt_const_section(&b.constants, b.section_spans.constants);
        emitted |= self.opt_type_section(&b.types, b.section_spans.types);
        emitted |= self.opt_var_section(&b.variables, b.section_spans.variables);
        if let Some(pfs) = &b.procedures_functions {
            for pf in pfs {
                self.blank();
                self.proc_func(pf);
                emitted = true;
            }
        }
        emitted
    }

    /// `kw_offset` is the byte offset of the `const` keyword when known (program
    /// blocks). Comments before it are flushed at the *outer* indent so a
    /// section-header comment sits above `const`, while comments between the
    /// keyword and the first declaration stay inside the section.
    fn opt_const_section(&mut self, decls: &Option<Vec<ConstDecl>>, kw_offset: Option<usize>) -> bool {
        match decls {
            Some(d) if !d.is_empty() => {
                self.flush_for(kw_offset);
                self.writeln("const");
                self.indent += 1;
                for c in d {
                    self.flush_before(c.name_span.start);
                    let v = self.expr(&c.value);
                    self.writeln(&format!("{} = {};", c.name, v));
                }
                self.indent -= 1;
                true
            }
            _ => false,
        }
    }

    fn opt_type_section(&mut self, decls: &Option<Vec<TypeDecl>>, kw_offset: Option<usize>) -> bool {
        match decls {
            Some(d) if !d.is_empty() => {
                self.flush_for(kw_offset);
                self.writeln("type");
                self.indent += 1;
                for t in d {
                    self.flush_before(t.name_span.start);
                    let ty = self.type_expr(&t.type_expr, self.indent);
                    self.writeln(&format!("{} = {};", t.name, ty));
                }
                self.indent -= 1;
                true
            }
            _ => false,
        }
    }

    fn opt_var_section(&mut self, decls: &Option<Vec<VarDecl>>, kw_offset: Option<usize>) -> bool {
        match decls {
            Some(d) if !d.is_empty() => {
                self.flush_for(kw_offset);
                self.writeln("var");
                self.indent += 1;
                for v in d {
                    if let Some(s) = v.id_spans.first() {
                        self.flush_before(s.start);
                    }
                    let ty = self.type_expr(&v.type_expr, self.indent);
                    self.writeln(&format!("{}: {};", v.ids.join(", "), ty));
                }
                self.indent -= 1;
                true
            }
            _ => false,
        }
    }

    fn proc_func(&mut self, pf: &ProcFuncDecl) {
        let name_span = match pf {
            ProcFuncDecl::Procedure { name_span, .. }
            | ProcFuncDecl::Function { name_span, .. } => *name_span,
        };
        self.flush_before(name_span.start);
        let (sig, bof) = match pf {
            ProcFuncDecl::Procedure {
                block_or_forward, ..
            }
            | ProcFuncDecl::Function {
                block_or_forward, ..
            } => (self.proc_func_signature(pf), block_or_forward),
        };
        match bof {
            BlockOrForward::Block(b) => {
                self.writeln(&format!("{};", sig));
                self.block(b, ";", false);
            }
            BlockOrForward::Forward => self.writeln(&format!("{}; forward;", sig)),
            BlockOrForward::External(None) => self.writeln(&format!("{}; external;", sig)),
            BlockOrForward::External(Some(s)) => self.writeln(&format!(
                "{}; external name '{}';",
                sig,
                s.replace('\'', "''")
            )),
        }
    }

    fn proc_func_signature(&self, pf: &ProcFuncDecl) -> String {
        match pf {
            ProcFuncDecl::Procedure { name, params, .. } => {
                format!("procedure {}{}", name, self.params_str(params))
            }
            ProcFuncDecl::Function {
                name,
                params,
                return_type,
                ..
            } => format!(
                "function {}{}: {}",
                name,
                self.params_str(params),
                return_type
            ),
        }
    }

    fn params_str(&self, params: &Option<Vec<Param>>) -> String {
        match params {
            Some(ps) => {
                let inner = ps
                    .iter()
                    .map(|p| self.param(p))
                    .collect::<Vec<_>>()
                    .join("; ");
                format!("({})", inner)
            }
            None => String::new(),
        }
    }

    fn param(&self, p: &Param) -> String {
        match p {
            Param::Variable {
                is_var,
                ids,
                type_name,
                ..
            } => format!(
                "{}{}: {}",
                if *is_var { "var " } else { "" },
                ids.join(", "),
                type_name
            ),
            Param::Procedure { id, params, .. } => {
                format!("procedure {}{}", id, self.params_str(params))
            }
            Param::Function {
                id,
                params,
                return_type,
                ..
            } => format!(
                "function {}{}: {}",
                id,
                self.params_str(params),
                return_type
            ),
        }
    }

    // ---- types ----------------------------------------------------------

    /// Render a type expression. `indent` is the absolute indentation level of
    /// the construct the type belongs to, used so multi-line types (records)
    /// nest correctly.
    fn type_expr(&self, t: &TypeExpr, indent: usize) -> String {
        match t {
            TypeExpr::Simple(s) => s.clone(),
            TypeExpr::Array {
                indices,
                element_type,
            } => {
                let idx = indices
                    .iter()
                    .map(|i| self.type_expr(i, indent))
                    .collect::<Vec<_>>()
                    .join(", ");
                format!("array[{}] of {}", idx, self.type_expr(element_type, indent))
            }
            TypeExpr::Record {
                fields,
                variant_part,
            } => {
                let field_pad = INDENT.repeat(indent + 1);
                let end_pad = INDENT.repeat(indent);
                let mut s = String::from("record\n");
                for f in fields {
                    s.push_str(&format!(
                        "{}{}: {};\n",
                        field_pad,
                        f.ids.join(", "),
                        self.type_expr(&f.type_expr, indent + 1)
                    ));
                }
                if let Some(vp) = variant_part {
                    s.push_str(&self.variant_part(vp, indent + 1));
                }
                s.push_str(&format!("{}end", end_pad));
                s
            }
            TypeExpr::Pointer(t) => format!("^{}", self.type_expr(t, indent)),
            TypeExpr::Set(t) => format!("set of {}", self.type_expr(t, indent)),
            TypeExpr::File(t) => format!("file of {}", self.type_expr(t, indent)),
            TypeExpr::Subrange { start, end } => {
                format!("{}..{}", self.expr(start), self.expr(end))
            }
            TypeExpr::Enum(vs) => format!("({})", vs.join(", ")),
            TypeExpr::Procedure { params } => format!("procedure{}", self.params_str(params)),
            TypeExpr::Function {
                params,
                return_type,
            } => format!("function{}: {}", self.params_str(params), return_type),
        }
    }

    fn variant_part(&self, vp: &VariantPart, indent: usize) -> String {
        let pad = INDENT.repeat(indent);
        let inner_pad = INDENT.repeat(indent + 1);
        let tag = match &vp.tag_field {
            Some(f) => format!("{}: {}", f, vp.tag_type),
            None => vp.tag_type.clone(),
        };
        let mut s = format!("{}case {} of\n", pad, tag);
        for v in &vp.variants {
            let labels = v
                .labels
                .iter()
                .map(|l| self.expr(l))
                .collect::<Vec<_>>()
                .join(", ");
            let flds = v
                .fields
                .iter()
                .map(|f| {
                    format!(
                        "{}: {}",
                        f.ids.join(", "),
                        self.type_expr(&f.type_expr, indent + 1)
                    )
                })
                .collect::<Vec<_>>()
                .join("; ");
            s.push_str(&format!("{}{}: ({});\n", inner_pad, labels, flds));
        }
        s
    }

    // ---- statements -----------------------------------------------------

    fn statement_list(&mut self, stmts: &[Stmt]) {
        for s in stmts {
            if matches!(s, Stmt::Empty) {
                continue;
            }
            // Leading comments before the statement.
            self.flush_for(stmt_min_start(s));
            self.statement(s, ";");
            // Trailing comments on the statement's own line(s) — flush now so
            // they attach to this line instead of drifting to a later `end`.
            if let Some(end) = stmt_max_end(s) {
                let line = self.line_of(end);
                self.flush_through_line(line);
            }
        }
    }

    /// Emit a statement, appending `suffix` (usually `;`) to its final line.
    fn statement(&mut self, s: &Stmt, suffix: &str) {
        match s {
            Stmt::Empty => {
                if !suffix.is_empty() {
                    self.writeln(suffix);
                }
            }
            Stmt::Assignment { target, value } => {
                let t = self.expr(target);
                let v = self.expr(value);
                self.writeln(&format!("{} := {}{}", t, v, suffix));
            }
            Stmt::ProcedureCall { name, args, .. } => {
                let a = self.args(args);
                self.writeln(&format!("{}{}{}", name, a, suffix));
            }
            Stmt::Goto(n) => self.writeln(&format!("goto {}{}", n, suffix)),
            Stmt::Labeled(n, inner) => {
                self.writeln(&format!("{}:", n));
                self.statement(inner, suffix);
            }
            Stmt::Compound(stmts) => {
                self.writeln("begin");
                self.indent += 1;
                self.statement_list(stmts);
                self.indent -= 1;
                self.writeln(&format!("end{}", suffix));
            }
            Stmt::If {
                condition,
                then_stmt,
                else_stmt,
            } => {
                let c = self.expr(condition);
                self.writeln(&format!("if {} then", c));
                match else_stmt {
                    Some(e) => {
                        self.branch(then_stmt, "");
                        self.writeln("else");
                        self.branch(e, suffix);
                    }
                    None => self.branch(then_stmt, suffix),
                }
            }
            Stmt::While { condition, body } => {
                let c = self.expr(condition);
                self.writeln(&format!("while {} do", c));
                self.branch(body, suffix);
            }
            Stmt::For {
                id,
                start,
                up,
                end,
                body,
                ..
            } => {
                let s0 = self.expr(start);
                let e0 = self.expr(end);
                self.writeln(&format!(
                    "for {} := {} {} {} do",
                    id,
                    s0,
                    if *up { "to" } else { "downto" },
                    e0
                ));
                self.branch(body, suffix);
            }
            Stmt::Repeat { body, until } => {
                self.writeln("repeat");
                self.indent += 1;
                self.statement_list(body);
                self.indent -= 1;
                let u = self.expr(until);
                self.writeln(&format!("until {}{}", u, suffix));
            }
            Stmt::With { ids, body } => {
                let i = ids
                    .iter()
                    .map(|e| self.expr(e))
                    .collect::<Vec<_>>()
                    .join(", ");
                self.writeln(&format!("with {} do", i));
                self.branch(body, suffix);
            }
            Stmt::Case {
                expr,
                items,
                else_stmt,
            } => {
                let e = self.expr(expr);
                self.writeln(&format!("case {} of", e));
                self.indent += 1;
                for item in items {
                    let labels = item
                        .labels
                        .iter()
                        .map(|l| self.expr(l))
                        .collect::<Vec<_>>()
                        .join(", ");
                    self.writeln(&format!("{}:", labels));
                    self.branch(&item.stmt, ";");
                }
                if let Some(els) = else_stmt {
                    self.writeln("else");
                    self.branch(els, ";");
                }
                self.indent -= 1;
                self.writeln(&format!("end{}", suffix));
            }
        }
    }

    /// Emit a sub-statement. Compound statements keep their own `begin`/`end` at
    /// the current level; anything else is indented one level deeper.
    fn branch(&mut self, s: &Stmt, suffix: &str) {
        if matches!(s, Stmt::Compound(_)) {
            self.statement(s, suffix);
        } else {
            self.indent += 1;
            self.statement(s, suffix);
            self.indent -= 1;
        }
    }

    // ---- expressions ----------------------------------------------------

    fn expr(&self, e: &Expr) -> String {
        match e {
            Expr::Integer(i) => i.to_string(),
            Expr::Real(r) => format!("{:?}", r),
            Expr::Char(c) => char_lit(*c),
            Expr::String(s) => format!("'{}'", s.replace('\'', "''")),
            Expr::Boolean(b) => if *b { "true" } else { "false" }.to_string(),
            Expr::Nil => "nil".to_string(),
            Expr::Variable(v) => self.variable(v),
            Expr::FunctionCall { name, args, .. } => format!("{}{}", name, self.args(args)),
            Expr::Set(elems) => {
                let inner = elems
                    .iter()
                    .map(|el| match el {
                        Element::Single(e) => self.expr(e),
                        Element::Range(a, b) => format!("{}..{}", self.expr(a), self.expr(b)),
                    })
                    .collect::<Vec<_>>()
                    .join(", ");
                format!("[{}]", inner)
            }
            Expr::Range(a, b) => format!("{}..{}", self.expr(a), self.expr(b)),
            Expr::Unary { op, expr } => {
                let inner = self.expr(expr);
                let inner = if matches!(**expr, Expr::Binary { .. } | Expr::Range(..)) {
                    format!("({})", inner)
                } else {
                    inner
                };
                match op {
                    UnaryOp::Not => format!("not {}", inner),
                    UnaryOp::Minus => format!("-{}", inner),
                    UnaryOp::Plus => format!("+{}", inner),
                }
            }
            Expr::Binary { op, left, right } => {
                if matches!(op, BinOp::DotDot) {
                    return format!(
                        "{}..{}",
                        self.expr_paren(left, 0, false),
                        self.expr_paren(right, 0, true)
                    );
                }
                let p = bin_prec(op);
                let l = self.expr_paren(left, p, false);
                let r = self.expr_paren(right, p, true);
                format!("{} {} {}", l, bin_op_str(op), r)
            }
        }
    }

    /// Render `e` as a binary operand of an operator with precedence `parent`,
    /// adding parentheses only when needed to preserve the parse. `right` marks
    /// the right operand, which needs parens on equal precedence (operators are
    /// left-associative).
    fn expr_paren(&self, e: &Expr, parent: u8, right: bool) -> String {
        let s = self.expr(e);
        if let Expr::Binary { op, .. } = e {
            let cp = bin_prec(op);
            let need = if right { cp <= parent } else { cp < parent };
            if need {
                return format!("({})", s);
            }
        }
        s
    }

    fn variable(&self, v: &Variable) -> String {
        match v {
            Variable::Id(name, _) => name.clone(),
            Variable::MemberAccess { record, field } => {
                format!("{}.{}", self.expr(record), field)
            }
            Variable::ArrayAccess { array, indices } => {
                let idx = indices
                    .iter()
                    .map(|e| self.expr(e))
                    .collect::<Vec<_>>()
                    .join(", ");
                format!("{}[{}]", self.expr(array), idx)
            }
            Variable::PointerDeref(e) => format!("{}^", self.expr(e)),
        }
    }

    fn args(&self, a: &Option<Vec<Expr>>) -> String {
        match a {
            Some(args) => {
                let inner = args
                    .iter()
                    .map(|e| self.expr(e))
                    .collect::<Vec<_>>()
                    .join(", ");
                format!("({})", inner)
            }
            None => String::new(),
        }
    }
}

fn char_lit(c: char) -> String {
    if c == '\'' {
        "''''".to_string()
    } else {
        format!("'{}'", c)
    }
}

/// Binary operator precedence (higher binds tighter), per Pascal's grouping:
/// multiplicative > additive > relational.
fn bin_prec(op: &BinOp) -> u8 {
    match op {
        BinOp::Mul | BinOp::Div | BinOp::FloatDiv | BinOp::Mod | BinOp::And => 3,
        BinOp::Add | BinOp::Sub | BinOp::Or => 2,
        BinOp::Eq | BinOp::Neq | BinOp::Lt | BinOp::Lte | BinOp::Gt | BinOp::Gte | BinOp::In => 1,
        BinOp::DotDot => 0,
    }
}

fn bin_op_str(op: &BinOp) -> &'static str {
    match op {
        BinOp::Add => "+",
        BinOp::Sub => "-",
        BinOp::Mul => "*",
        BinOp::Div => "div",
        BinOp::FloatDiv => "/",
        BinOp::Mod => "mod",
        BinOp::Eq => "=",
        BinOp::Neq => "<>",
        BinOp::Lt => "<",
        BinOp::Lte => "<=",
        BinOp::Gt => ">",
        BinOp::Gte => ">=",
        BinOp::And => "and",
        BinOp::Or => "or",
        BinOp::In => "in",
        BinOp::DotDot => "..",
    }
}

/// Scan `src` for `{ ... }` and `(* ... *)` comments, skipping string literals
/// so quoted braces/parens are not mistaken for comments. Returns them in source
/// order with their starting byte offset.
fn collect_comments(src: &str) -> Vec<Comment> {
    let bytes = src.as_bytes();
    let n = bytes.len();
    let mut comments = Vec::new();
    let mut i = 0;
    while i < n {
        match bytes[i] {
            b'\'' => {
                // String literal: skip to the closing quote, honoring '' escapes.
                i += 1;
                while i < n {
                    if bytes[i] == b'\'' {
                        if i + 1 < n && bytes[i + 1] == b'\'' {
                            i += 2;
                            continue;
                        }
                        i += 1;
                        break;
                    }
                    i += 1;
                }
            }
            b'{' => {
                let start = i;
                i += 1;
                while i < n && bytes[i] != b'}' {
                    i += 1;
                }
                if i < n {
                    i += 1; // consume '}'
                }
                comments.push(Comment {
                    start,
                    text: src[start..i].to_string(),
                    own_line: is_own_line(bytes, start),
                });
            }
            b'(' if i + 1 < n && bytes[i + 1] == b'*' => {
                let start = i;
                i += 2;
                while i + 1 < n && !(bytes[i] == b'*' && bytes[i + 1] == b')') {
                    i += 1;
                }
                i = if i + 1 < n { i + 2 } else { n };
                comments.push(Comment {
                    start,
                    text: src[start..i].to_string(),
                    own_line: is_own_line(bytes, start),
                });
            }
            _ => i += 1,
        }
    }
    comments
}

/// Whether only whitespace separates `offset` from the start of its line.
fn is_own_line(bytes: &[u8], offset: usize) -> bool {
    for &b in bytes[..offset].iter().rev() {
        match b {
            b'\n' => return true,
            b' ' | b'\t' | b'\r' => continue,
            _ => return false,
        }
    }
    true
}

fn min_opt(a: Option<usize>, b: Option<usize>) -> Option<usize> {
    match (a, b) {
        (Some(x), Some(y)) => Some(x.min(y)),
        (x, None) => x,
        (None, y) => y,
    }
}

/// Earliest source offset of any spanned node within an expression, used to know
/// where a construct begins so leading comments flush before it. Literals carry
/// no span and contribute `None`.
fn expr_min_start(e: &Expr) -> Option<usize> {
    match e {
        Expr::Variable(v) => var_min_start(v),
        Expr::FunctionCall {
            name_span, args, ..
        } => {
            let mut m = Some(name_span.start);
            if let Some(a) = args {
                for x in a {
                    m = min_opt(m, expr_min_start(x));
                }
            }
            m
        }
        Expr::Binary { left, right, .. } => {
            min_opt(expr_min_start(left), expr_min_start(right))
        }
        Expr::Unary { expr, .. } => expr_min_start(expr),
        Expr::Range(a, b) => min_opt(expr_min_start(a), expr_min_start(b)),
        Expr::Set(elems) => elems
            .iter()
            .filter_map(|el| match el {
                Element::Single(e) => expr_min_start(e),
                Element::Range(a, b) => min_opt(expr_min_start(a), expr_min_start(b)),
            })
            .min(),
        _ => None,
    }
}

fn var_min_start(v: &Variable) -> Option<usize> {
    match v {
        Variable::Id(_, span) => Some(span.start),
        Variable::MemberAccess { record, .. } => expr_min_start(record),
        Variable::ArrayAccess { array, indices } => min_opt(
            expr_min_start(array),
            indices.iter().filter_map(expr_min_start).min(),
        ),
        Variable::PointerDeref(e) => expr_min_start(e),
    }
}

fn stmt_min_start(s: &Stmt) -> Option<usize> {
    match s {
        Stmt::Assignment { target, value } => {
            min_opt(expr_min_start(target), expr_min_start(value))
        }
        Stmt::ProcedureCall {
            name_span, args, ..
        } => {
            let mut m = Some(name_span.start);
            if let Some(a) = args {
                for x in a {
                    m = min_opt(m, expr_min_start(x));
                }
            }
            m
        }
        Stmt::If {
            condition,
            then_stmt,
            else_stmt,
        } => {
            let mut m = expr_min_start(condition);
            m = min_opt(m, stmt_min_start(then_stmt));
            if let Some(e) = else_stmt {
                m = min_opt(m, stmt_min_start(e));
            }
            m
        }
        Stmt::While { condition, body } => {
            min_opt(expr_min_start(condition), stmt_min_start(body))
        }
        Stmt::For {
            id_span,
            start,
            end,
            body,
            ..
        } => {
            let mut m = Some(id_span.start);
            m = min_opt(m, expr_min_start(start));
            m = min_opt(m, expr_min_start(end));
            min_opt(m, stmt_min_start(body))
        }
        Stmt::Repeat { body, until } => {
            let m = body.iter().filter_map(stmt_min_start).min();
            min_opt(m, expr_min_start(until))
        }
        Stmt::Case {
            expr,
            items,
            else_stmt,
        } => {
            let mut m = expr_min_start(expr);
            for it in items {
                m = min_opt(m, stmt_min_start(&it.stmt));
                for l in &it.labels {
                    m = min_opt(m, expr_min_start(l));
                }
            }
            if let Some(e) = else_stmt {
                m = min_opt(m, stmt_min_start(e));
            }
            m
        }
        Stmt::With { ids, body } => {
            let m = ids.iter().filter_map(expr_min_start).min();
            min_opt(m, stmt_min_start(body))
        }
        Stmt::Compound(ss) => ss.iter().filter_map(stmt_min_start).min(),
        Stmt::Labeled(_, inner) => stmt_min_start(inner),
        Stmt::Goto(_) | Stmt::Empty => None,
    }
}

fn max_opt(a: Option<usize>, b: Option<usize>) -> Option<usize> {
    match (a, b) {
        (Some(x), Some(y)) => Some(x.max(y)),
        (x, None) => x,
        (None, y) => y,
    }
}

/// Latest source offset of any spanned node within an expression. Used to find
/// the line a statement ends on, so its trailing comment can be attached there.
fn expr_max_end(e: &Expr) -> Option<usize> {
    match e {
        Expr::Variable(v) => var_max_end(v),
        Expr::FunctionCall {
            name_span, args, ..
        } => {
            let mut m = Some(name_span.end);
            if let Some(a) = args {
                for x in a {
                    m = max_opt(m, expr_max_end(x));
                }
            }
            m
        }
        Expr::Binary { left, right, .. } => max_opt(expr_max_end(left), expr_max_end(right)),
        Expr::Unary { expr, .. } => expr_max_end(expr),
        Expr::Range(a, b) => max_opt(expr_max_end(a), expr_max_end(b)),
        Expr::Set(elems) => elems
            .iter()
            .filter_map(|el| match el {
                Element::Single(e) => expr_max_end(e),
                Element::Range(a, b) => max_opt(expr_max_end(a), expr_max_end(b)),
            })
            .max(),
        _ => None,
    }
}

fn var_max_end(v: &Variable) -> Option<usize> {
    match v {
        Variable::Id(_, span) => Some(span.end),
        Variable::MemberAccess { record, .. } => expr_max_end(record),
        Variable::ArrayAccess { array, indices } => max_opt(
            expr_max_end(array),
            indices.iter().filter_map(expr_max_end).max(),
        ),
        Variable::PointerDeref(e) => expr_max_end(e),
    }
}

fn stmt_max_end(s: &Stmt) -> Option<usize> {
    match s {
        Stmt::Assignment { target, value } => {
            max_opt(expr_max_end(target), expr_max_end(value))
        }
        Stmt::ProcedureCall {
            name_span, args, ..
        } => {
            let mut m = Some(name_span.end);
            if let Some(a) = args {
                for x in a {
                    m = max_opt(m, expr_max_end(x));
                }
            }
            m
        }
        Stmt::If {
            condition,
            then_stmt,
            else_stmt,
        } => {
            let mut m = expr_max_end(condition);
            m = max_opt(m, stmt_max_end(then_stmt));
            if let Some(e) = else_stmt {
                m = max_opt(m, stmt_max_end(e));
            }
            m
        }
        Stmt::While { condition, body } => max_opt(expr_max_end(condition), stmt_max_end(body)),
        Stmt::For {
            id_span,
            start,
            end,
            body,
            ..
        } => {
            let mut m = Some(id_span.end);
            m = max_opt(m, expr_max_end(start));
            m = max_opt(m, expr_max_end(end));
            max_opt(m, stmt_max_end(body))
        }
        Stmt::Repeat { body, until } => {
            let m = body.iter().filter_map(stmt_max_end).max();
            max_opt(m, expr_max_end(until))
        }
        Stmt::Case {
            expr,
            items,
            else_stmt,
        } => {
            let mut m = expr_max_end(expr);
            for it in items {
                m = max_opt(m, stmt_max_end(&it.stmt));
                for l in &it.labels {
                    m = max_opt(m, expr_max_end(l));
                }
            }
            if let Some(e) = else_stmt {
                m = max_opt(m, stmt_max_end(e));
            }
            m
        }
        Stmt::With { ids, body } => {
            let m = ids.iter().filter_map(expr_max_end).max();
            max_opt(m, stmt_max_end(body))
        }
        Stmt::Compound(ss) => ss.iter().filter_map(stmt_max_end).max(),
        Stmt::Labeled(_, inner) => stmt_max_end(inner),
        Stmt::Goto(_) | Stmt::Empty => None,
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::lexer::Lexer;
    use crate::parser::CompilationUnitParser;
    use std::path::{Path, PathBuf};

    fn parse(src: &str) -> Option<CompilationUnit> {
        CompilationUnitParser::new().parse(Lexer::new(src)).ok()
    }

    fn collect_pas(dir: &Path, out: &mut Vec<PathBuf>) {
        let Ok(entries) = std::fs::read_dir(dir) else {
            return;
        };
        for entry in entries.flatten() {
            let path = entry.path();
            if path.is_dir() {
                collect_pas(&path, out);
            } else if matches!(
                path.extension().and_then(|s| s.to_str()),
                Some("pas") | Some("pascalm")
            ) {
                out.push(path);
            }
        }
    }

    /// For every sample program: format it, ensure the output still parses, and
    /// ensure formatting is idempotent (formatting the output again yields the
    /// exact same text). This catches invalid syntax and dropped-parenthesis /
    /// precedence bugs, which would re-parse to a different tree and break
    /// idempotence.
    #[test]
    fn format_reparses_and_is_idempotent() {
        let mut files = Vec::new();
        collect_pas(Path::new("src/tests/success"), &mut files);
        collect_pas(Path::new("src/stdlib"), &mut files);
        collect_pas(Path::new("src/examples"), &mut files);
        files.retain(|p| !p.to_string_lossy().contains("/target/"));
        assert!(!files.is_empty(), "no sample .pas files were found");

        let mut checked = 0;
        for path in &files {
            let src = std::fs::read_to_string(path).unwrap();
            // Skip files our own parser can't handle to begin with.
            let Some(ast) = parse(&src) else {
                continue;
            };
            let formatted = format_compilation_unit(&ast, &src);

            let reparsed = parse(&formatted).unwrap_or_else(|| {
                panic!(
                    "formatted output no longer parses: {}\n--- formatted ---\n{}",
                    path.display(),
                    formatted
                )
            });

            let formatted2 = format_compilation_unit(&reparsed, &formatted);
            assert_eq!(
                formatted,
                formatted2,
                "formatting is not idempotent for {}",
                path.display()
            );
            checked += 1;
        }
        assert!(checked > 0, "no sample programs were successfully parsed");
        eprintln!("formatter checked {checked} sample program(s)");
    }

    #[test]
    fn does_not_panic_on_tricky_inputs() {
        let cases = [
            "program P; begin end.",
            "program P; begin end. { trailing }",
            "{ only a header }\nprogram P;\nbegin\nend.",
            "program P;\nbegin\n  { lonely comment }\nend.",
            "program P;\nvar x: integer;\nbegin\n  x := 1; { a }\n  { b }\nend.",
            "program P;\nbegin\n  if true then\n  begin\n    { inner }\n  end;\nend.",
            "program P;\nbegin\n  while true do\n  begin\n  end;\nend.",
            "program P;\nbegin\n  repeat\n    { note }\n  until false;\nend.",
            "program P;\nbegin\n  case 1 of\n    1: writeln('a');\n  else\n    writeln('b');\n  end;\nend.",
            "program P;\ntype r = record a: integer; b: real; end;\nbegin\nend.",
            "program P;\nvar s: set of char;\nbegin\n  s := ['a'..'z'];\nend.",
            "program P;\nbegin\n  writeln('it''s a test');\nend.",
            "program P;\nvar p: ^integer;\nbegin\nend.",
            "program P;\nlabel 1;\nbegin\n  goto 1;\n  1: writeln('x');\nend.",
        ];
        for (i, src) in cases.iter().enumerate() {
            let Some(ast) = parse(src) else {
                continue;
            };
            // Must not panic, and must produce parseable, stable output.
            let out = format_compilation_unit(&ast, src);
            let reparsed = parse(&out)
                .unwrap_or_else(|| panic!("case {i} produced unparseable output:\n{out}"));
            let out2 = format_compilation_unit(&reparsed, &out);
            assert_eq!(out, out2, "case {i} not idempotent:\n{out}");
        }
    }

    #[test]
    fn trailing_comment_stays_on_its_statement_line() {
        // A trailing comment on the LAST statement of a block must stay on that
        // statement's line, not drift onto the following `end`.
        let src = "\
program P;
procedure Q;
begin
  x := 20; { local copy }
end;
begin
  writeln(x); { prints }
end.
";
        let ast = parse(src).expect("must parse");
        let out = format_compilation_unit(&ast, src);
        assert!(
            out.contains("x := 20;  { local copy }"),
            "trailing comment left its statement line:\n{out}"
        );
        assert!(
            !out.contains("end;  { local copy }"),
            "trailing comment drifted onto `end`:\n{out}"
        );
        assert!(
            out.contains("writeln(x);  { prints }"),
            "trailing comment on last main statement misplaced:\n{out}"
        );
    }

    #[test]
    fn comments_are_preserved() {
        let src = "\
{ file header }
program Demo;
const
  { max items }
  N = 10;
var
  x: integer; { the counter }

{ doubles its input }
function Double(v: integer): integer;
begin
  Double := v * 2;
end;

begin
  { initialise }
  x := 0;
  x := Double(x); (* call it *)
  writeln(x);
end.
";
        let ast = parse(src).expect("sample must parse");
        let out = format_compilation_unit(&ast, src);

        for comment in [
            "{ file header }",
            "{ max items }",
            "{ the counter }",
            "{ doubles its input }",
            "{ initialise }",
            "(* call it *)",
        ] {
            assert!(
                out.contains(comment),
                "comment {comment:?} was dropped.\n--- output ---\n{out}"
            );
        }

        // The file-header comment must stay above the `program` line, not drift
        // into the first declaration section.
        assert!(
            out.contains("{ file header }\nprogram Demo;"),
            "file-header comment drifted off the top:\n{out}"
        );

        // Re-formatting the output must keep every comment and be stable.
        let reparsed = parse(&out).expect("formatted output must parse");
        let out2 = format_compilation_unit(&reparsed, &out);
        assert_eq!(out, out2, "comment placement is not idempotent");
    }

    #[test]
    fn section_header_comment_stays_above_keyword() {
        // A standalone comment above a section keyword must stay above the
        // keyword, not drift indented into the section body. A comment between
        // the keyword and the first declaration must stay inside the section.
        let src = "\
program P;
{ labels here }
label 100;
{ constants here }
const
  { the max }
  MAX = 5;
{ types here }
type
  T = integer;
{ vars here }
var
  i: integer;
begin
  i := MAX;
end.
";
        let ast = parse(src).expect("must parse");
        let out = format_compilation_unit(&ast, src);

        for (comment, keyword) in [
            ("{ labels here }", "label"),
            ("{ constants here }", "const"),
            ("{ types here }", "type"),
            ("{ vars here }", "var"),
        ] {
            // The header comment must appear on its own line immediately before
            // the keyword, at the outer indentation (no leading spaces).
            let needle = format!("{comment}\n{keyword}");
            assert!(
                out.contains(&needle),
                "section header {comment:?} did not stay above {keyword:?}:\n{out}"
            );
        }
        // The inner comment stays inside the const section, indented above MAX.
        assert!(
            out.contains("  { the max }\n  MAX = 5;"),
            "inner const comment drifted out of its section:\n{out}"
        );

        let reparsed = parse(&out).expect("formatted output must parse");
        let out2 = format_compilation_unit(&reparsed, &out);
        assert_eq!(out, out2, "section-header comment placement is not idempotent");
    }

    #[test]
    fn interface_header_comment_stays_in_interface() {
        // Comments above unit interface procedure/function headers must stay in
        // the interface, not drift down into the implementation section.
        let src = "\
unit U;
interface
{ math }
function Sqr(n: integer): integer;
{ control }
procedure Stop;
implementation
function Sqr(n: integer): integer;
begin
  Sqr := n * n;
end;
procedure Stop;
begin
  writeln('stop');
end;
end.
";
        let ast = parse(src).expect("must parse");
        let out = format_compilation_unit(&ast, src);

        let iface = out.split("implementation").next().unwrap();
        assert!(
            iface.contains("{ math }") && iface.contains("{ control }"),
            "interface header comments drifted out of the interface:\n{out}"
        );

        let reparsed = parse(&out).expect("formatted output must parse");
        let out2 = format_compilation_unit(&reparsed, &out);
        assert_eq!(out, out2, "interface comment placement is not idempotent");
    }
}
