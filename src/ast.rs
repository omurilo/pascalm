use std::fmt;

#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Default)]
pub struct Span {
    pub start: usize,
    pub end: usize,
}

impl Span {
    pub fn new(start: usize, end: usize) -> Self {
        Self { start, end }
    }
}

#[derive(Debug, Clone, PartialEq)]
pub enum CompilationUnit {
    Program(Program),
    Unit(Unit),
}

#[derive(Debug, Clone, PartialEq)]
pub struct Program {
    pub span: Span,
    pub name: String,
    pub heading: Option<Vec<String>>,
    pub uses: Option<Vec<String>>,
    pub block: Block,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Unit {
    pub span: Span,
    pub name: String,
    pub interface: InterfaceSection,
    pub implementation: ImplementationSection,
    pub initialization: Option<Vec<Stmt>>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct InterfaceSection {
    pub span: Span,
    pub uses: Option<Vec<String>>,
    pub constants: Option<Vec<ConstDecl>>,
    pub types: Option<Vec<TypeDecl>>,
    pub variables: Option<Vec<VarDecl>>,
    pub headers: Option<Vec<ProcFuncDecl>>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct ImplementationSection {
    pub span: Span,
    pub uses: Option<Vec<String>>,
    pub constants: Option<Vec<ConstDecl>>,
    pub types: Option<Vec<TypeDecl>>,
    pub variables: Option<Vec<VarDecl>>,
    pub bodies: Option<Vec<ProcFuncDecl>>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Block {
    pub span: Span,
    pub labels: Option<Vec<i64>>,
    pub constants: Option<Vec<ConstDecl>>,
    pub types: Option<Vec<TypeDecl>>,
    pub variables: Option<Vec<VarDecl>>,
    pub procedures_functions: Option<Vec<ProcFuncDecl>>,
    pub statements: Vec<Stmt>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct ConstDecl {
    pub span: Span,
    pub name: String,
    pub value: Expr,
}

#[derive(Debug, Clone, PartialEq)]
pub struct TypeDecl {
    pub span: Span,
    pub name: String,
    pub type_expr: TypeExpr,
}

#[derive(Debug, Clone, PartialEq)]
pub struct VarDecl {
    pub span: Span,
    pub ids: Vec<String>,
    pub type_expr: TypeExpr,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Spanned<T> {
    pub span: Span,
    pub node: T,
}

#[derive(Debug, Clone, PartialEq)]
pub enum ProcFuncDecl {
    Procedure {
        span: Span,
        name: String,
        params: Option<Vec<Param>>,
        block_or_forward: BlockOrForward,
    },
    Function {
        span: Span,
        name: String,
        params: Option<Vec<Param>>,
        return_type: String,
        block_or_forward: BlockOrForward,
    },
}

#[derive(Debug, Clone, PartialEq)]
pub enum BlockOrForward {
    Block(Box<Block>),
    Forward,
}

pub type Param = Spanned<ParamKind>;

#[derive(Debug, Clone, PartialEq)]
pub enum ParamKind {
    Variable { is_var: bool, ids: Vec<String>, type_expr: TypeExpr },
    Procedure { id: String, params: Option<Vec<Param>> },
    Function { id: String, params: Option<Vec<Param>>, return_type: String },
}

impl fmt::Display for ParamKind {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            ParamKind::Variable { is_var, ids, type_expr } => {
                if *is_var { write!(f, "var ")?; }
                write!(f, "{}: {}", ids.join(", "), type_expr.node)
            }
            ParamKind::Procedure { id, .. } => write!(f, "procedure {}", id),
            ParamKind::Function { id, .. } => write!(f, "function {}", id),
        }
    }
}

pub type TypeExpr = Spanned<TypeExprKind>;

#[derive(Debug, Clone, PartialEq)]
pub enum TypeExprKind {
    Simple(String),
    Array {
        indices: Vec<TypeExpr>,
        element_type: Box<TypeExpr>,
    },
    Record {
        fields: Vec<VarDecl>,
        variant_part: Option<VariantPart>,
    },
    Pointer(Box<TypeExpr>),
    Set(Box<TypeExpr>),
    File(Box<TypeExpr>),
    Subrange {
        start: Expr,
        end: Expr,
    },
    Enum(Vec<String>),
    Procedure { params: Option<Vec<Param>> },
    Function { params: Option<Vec<Param>>, return_type: String },
}

impl fmt::Display for TypeExprKind {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            TypeExprKind::Simple(s) => write!(f, "{}", s),
            TypeExprKind::Array { indices, element_type } => {
                write!(f, "array[")?;
                for (i, idx) in indices.iter().enumerate() {
                    if i > 0 { write!(f, ", ")?; }
                    write!(f, "{}", idx.node)?;
                }
                write!(f, "] of {}", element_type.node)
            }
            TypeExprKind::Record { .. } => write!(f, "record"),
            TypeExprKind::Pointer(inner) => write!(f, "^{}", inner.node),
            TypeExprKind::Set(inner) => write!(f, "set of {}", inner.node),
            TypeExprKind::File(inner) => write!(f, "file of {}", inner.node),
            TypeExprKind::Subrange { start, end } => write!(f, "{}..{}", start.node, end.node),
            TypeExprKind::Enum(ids) => write!(f, "({})", ids.join(", ")),
            TypeExprKind::Procedure { params } => {
                write!(f, "procedure")?;
                if let Some(p) = params {
                    write!(f, "(")?;
                    for (i, param) in p.iter().enumerate() {
                        if i > 0 { write!(f, "; ")?; }
                        write!(f, "{}", param.node)?;
                    }
                    write!(f, ")")?;
                }
                Ok(())
            }
            TypeExprKind::Function { params, return_type } => {
                write!(f, "function")?;
                if let Some(p) = params {
                    write!(f, "(")?;
                    for (i, param) in p.iter().enumerate() {
                        if i > 0 { write!(f, "; ")?; }
                        write!(f, "{}", param.node)?;
                    }
                    write!(f, ")")?;
                }
                write!(f, ": {}", return_type)
            }
        }
    }
}

#[derive(Debug, Clone, PartialEq)]
pub struct VariantPart {
    pub span: Span,
    pub tag_field: Option<String>,
    pub tag_type: String,
    pub variants: Vec<Variant>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Variant {
    pub span: Span,
    pub labels: Vec<Expr>,
    pub fields: Vec<VarDecl>,
    pub nested_variant: Option<Box<VariantPart>>,
}

pub type Stmt = Spanned<StmtKind>;

#[derive(Debug, Clone, PartialEq)]
pub enum StmtKind {
    Labeled(i64, Box<Stmt>),
    Compound(Vec<Stmt>),
    Assignment {
        target: Expr,
        value: Expr,
    },
    If {
        condition: Expr,
        then_stmt: Box<Stmt>,
        else_stmt: Option<Box<Stmt>>,
    },
    While {
        condition: Expr,
        body: Box<Stmt>,
    },
    Repeat {
        body: Vec<Stmt>,
        until: Expr,
    },
    For {
        id: String,
        start: Expr,
        up: bool, // true for 'to', false for 'downto'
        end: Expr,
        body: Box<Stmt>,
    },
    Case {
        expr: Expr,
        items: Vec<CaseItem>,
        else_stmt: Option<Box<Stmt>>,
    },
    Goto(i64),
    ProcedureCall {
        name: String,
        args: Option<Vec<Expr>>,
    },
    With {
        ids: Vec<Expr>,
        body: Box<Stmt>,
    },
    Empty,
}

#[derive(Debug, Clone, PartialEq)]
pub struct CaseItem {
    pub span: Span,
    pub labels: Vec<Expr>,
    pub stmt: Stmt,
}

pub type Expr = Spanned<ExprKind>;

#[derive(Debug, Clone, PartialEq)]
pub enum ExprKind {
    Range(Box<Expr>, Box<Expr>),
    Binary {
        op: BinOp,
        left: Box<Expr>,
        right: Box<Expr>,
    },
    Unary {
        op: UnaryOp,
        expr: Box<Expr>,
    },
    Integer(i64),
    Real(f64),
    Char(char),
    String(String),
    Boolean(bool),
    Nil,
    Variable(Box<Variable>),
    FunctionCall {
        name: String,
        args: Option<Vec<Expr>>,
    },
    Set(Vec<Element>),
}

impl fmt::Display for ExprKind {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            ExprKind::Integer(n) => write!(f, "{}", n),
            ExprKind::Real(n) => write!(f, "{}", n),
            ExprKind::Char(c) => write!(f, "'{}'", c),
            ExprKind::String(s) => write!(f, "'{}'", s),
            ExprKind::Boolean(b) => write!(f, "{}", if *b { "true" } else { "false" }),
            ExprKind::Nil => write!(f, "nil"),
            ExprKind::Variable(v) => write!(f, "{}", v.node),
            ExprKind::Binary { op, left, right } => write!(f, "{} {} {}", left.node, op, right.node),
            ExprKind::Unary { op, expr } => write!(f, "{} {}", op, expr.node),
            ExprKind::FunctionCall { name, .. } => write!(f, "{}()", name),
            ExprKind::Range(start, end) => write!(f, "{}..{}", start.node, end.node),
            ExprKind::Set(_) => write!(f, "[...]"),
        }
    }
}

pub type Variable = Spanned<VariableKind>;

#[derive(Debug, Clone, PartialEq)]
pub enum VariableKind {
    Id(String),
    MemberAccess {
        record: Box<Expr>,
        field: String,
    },
    ArrayAccess {
        array: Box<Expr>,
        indices: Vec<Expr>,
    },
    PointerDeref(Box<Expr>),
}

impl fmt::Display for VariableKind {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            VariableKind::Id(s) => write!(f, "{}", s),
            VariableKind::MemberAccess { record, field } => write!(f, "{}.{}", record.node, field),
            VariableKind::ArrayAccess { array, .. } => write!(f, "{}[]", array.node),
            VariableKind::PointerDeref(p) => write!(f, "{}^", p.node),
        }
    }
}

pub type Element = Spanned<ElementKind>;

#[derive(Debug, Clone, PartialEq)]
pub enum ElementKind {
    Single(Expr),
    Range(Expr, Expr),
}

#[derive(Debug, Clone, PartialEq)]
pub enum BinOp {
    Add, Sub, Mul, Div, FloatDiv, Mod,
    Eq, Neq, Lt, Lte, Gt, Gte,
    And, Or, In, DotDot,
}

impl fmt::Display for BinOp {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let s = match self {
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
        };
        write!(f, "{}", s)
    }
}

#[derive(Debug, Clone, PartialEq)]
pub enum UnaryOp {
    Plus, Minus, Not,
}

impl fmt::Display for UnaryOp {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let s = match self {
            UnaryOp::Plus => "+",
            UnaryOp::Minus => "-",
            UnaryOp::Not => "not",
        };
        write!(f, "{}", s)
    }
}
