use std::collections::HashMap;
use std::fmt::Debug;
use std::ops::Deref;
use std::path::{Path, PathBuf};
use std::str::FromStr;
use std::sync::Mutex;

use crop::Rope;
use dashmap::DashMap;
use lalrpop_util::ParseError;
use log::debug;
use pascalm::lexer::{self, Token};
use pascalm::loader::{resolve_uses, ModuleLoader};
use pascalm::{parser, CompilationUnit, SemanticAnalyzer, SymbolKind};
use tower_lsp::jsonrpc::Result;
use tower_lsp::lsp_types::*;
use tower_lsp::{Client, LanguageServer, LspService, Server};

struct TextDocumentChange<'a> {
    uri: String,
    text: &'a str,
}

#[derive(Debug)]
struct AnalysisResult {
    ast: CompilationUnit,
    analyzer: SemanticAnalyzer,
}

/// A parsed workspace file, indexed for cross-file features.
#[derive(Debug, Clone)]
struct IndexedUnit {
    uri: String,
    unit: CompilationUnit,
}

/// A workspace unit *after* semantic analysis — the data cross-file features
/// query. `analyzer` holds `definitions`/`references` (with spans) and
/// `symbol_table.all_symbols`; `interface` is the unit's exported symbols.
#[derive(Debug)]
struct AnalyzedUnit {
    uri: String,
    analyzer: SemanticAnalyzer,
    interface: HashMap<String, SymbolKind>,
}

#[derive(Debug)]
struct Backend {
    client: Client,
    document_map: DashMap<String, Rope>,
    semanticast_map: DashMap<String, AnalysisResult>,
    /// Workspace index: file stem (lowercased — the key a `uses` resolves by)
    /// -> the parsed unit. Built on `initialize`; the foundation that later
    /// cross-file features (go-to-definition into a `unit`, cross-file rename)
    /// will query.
    workspace: DashMap<String, IndexedUnit>,
    /// Per-unit semantic analysis, keyed by `ModuleLoader` module id. Built by
    /// `analyze_workspace`; this is what cross-file go-to-definition / rename
    /// will query.
    analyses: DashMap<String, AnalyzedUnit>,
    /// Bridge from a file stem (what a `uses` spec resolves by, lowercased) to
    /// its module id in `analyses`. Lets cross-file go-to-definition turn a
    /// `uses Foo` into Foo's analysis.
    unit_by_stem: DashMap<String, String>,
    /// The workspace root, captured from `initialize` and indexed in
    /// `initialized`.
    root: Mutex<Option<PathBuf>>,
}

impl Backend {
    fn find_symbol_at_offset(
        &self,
        analyzer: &SemanticAnalyzer,
        offset: usize,
    ) -> Option<pascalm::symbol_table::SymbolId> {
        // Search in references first (most common case: clicking on a use)
        for (span, id) in &analyzer.references {
            if offset >= span.start && offset <= span.end {
                return Some(*id);
            }
        }
        // Search in definitions
        for (span, id) in &analyzer.definitions {
            if offset >= span.start && offset <= span.end {
                return Some(*id);
            }
        }
        None
    }

    /// Resolve the definition of `name` exported by one of `uses`, returning a
    /// `Location` in the *defining* file. This is the cross-file part of
    /// go-to-definition. Returns `None` if no used unit exports `name`.
    fn cross_file_definition(&self, uses: &[String], name: &str) -> Option<Location> {
        for spec in uses {
            // A `uses` spec can be a path (e.g. `uses math/math_lib`); the index
            // is keyed by the bare file stem, so match on the last component.
            let stem = spec.rsplit(['/', '\\']).next().unwrap_or(spec);
            let Some(module_id) = self.unit_by_stem.get(stem).map(|r| r.value().clone()) else {
                continue;
            };
            let Some(unit) = self.analyses.get(&module_id) else {
                continue;
            };

            if !unit.interface.contains_key(name) {
                continue;
            }

            let Some(symbol_info) = unit
                .analyzer
                .symbol_table
                .all_symbols
                .iter()
                .find(|s| s.name == name && s.span.start != s.span.end)
            else {
                continue;
            };

            let uri = Url::parse(&unit.uri).ok()?;
            let path = uri.to_file_path().ok()?;
            let text = std::fs::read_to_string(&path).ok()?;
            let rope = Rope::from(text);
            let start = offset_to_position(symbol_info.span.start, &rope)?;
            let end = offset_to_position(symbol_info.span.end, &rope)?;
            return Some(Location::new(uri, Range::new(start, end)));
        }

        None
    }

    /// Scan the workspace for Pascal sources, parse each, and index it by file
    /// stem (the key a `uses` spec resolves by). Returns how many were indexed.
    fn index_workspace(&self, root: &Path) -> usize {
        let mut files = Vec::new();
        collect_pascal_files(root, &mut files, 0);

        let parser = parser::CompilationUnitParser::new();
        let mut count = 0;
        for path in files {
            let Ok(text) = std::fs::read_to_string(&path) else {
                continue;
            };
            let Ok(unit) = parser.parse(lexer::Lexer::new(&text)) else {
                continue; // skip files that don't parse; they'll re-index on edit
            };
            let stem = path
                .file_stem()
                .and_then(|s| s.to_str())
                .unwrap_or("")
                .to_lowercase();
            if stem.is_empty() {
                continue;
            }
            let uri = Url::from_file_path(&path)
                .map(|u| u.to_string())
                .unwrap_or_default();
            self.workspace.insert(stem, IndexedUnit { uri, unit });
            count += 1;
        }
        count
    }

    fn analyze_workspace(&self, root: &Path) -> usize {
        let mut files = Vec::new();
        collect_pascal_files(root, &mut files, 0);

        let mut loader = ModuleLoader::new();
        loader.search_paths = vec![root.to_path_buf()];

        let mut id_to_path: HashMap<String, PathBuf> = HashMap::new();
        for path in &files {
            if loader.load_recursively(path, false).is_ok() {
                if let Ok(id) = ModuleLoader::file_module_id(path) {
                    id_to_path.insert(id, path.clone());
                }
            }
        }

        let Some(order) = loader.topological_sort() else {
            return 0;
        };

        let mut module_interfaces: HashMap<String, HashMap<String, SymbolKind>> = HashMap::new();
        for id in &order {
            let loaded = loader.modules.get(id).unwrap();
            let uses_map = loaded.uses_map.clone();
            let unit = loaded.unit.clone();

            let mut analyzer = SemanticAnalyzer::with_interfaces(module_interfaces.clone());
            let mut interface: HashMap<String, SymbolKind> = HashMap::new();

            match unit {
                CompilationUnit::Program(mut p) => {
                    p.uses = resolve_uses(&p.uses, &uses_map);

                    if analyzer.analyze_program(&p).is_err() {
                        continue;
                    }
                }
                CompilationUnit::Unit(mut u) => {
                    u.interface.uses = resolve_uses(&u.interface.uses, &uses_map);
                    u.implementation.uses = resolve_uses(&u.implementation.uses, &uses_map);

                    match analyzer.analyze_unit(&u) {
                        Ok((iface, _block)) => {
                            interface = iface;
                            module_interfaces.insert(id.clone(), interface.clone());
                        }
                        Err(_) => continue,
                    }
                }
            }

            let Some(path) = id_to_path.get(id) else {
                continue;
            };
            let Ok(url) = Url::from_file_path(path) else {
                continue;
            };
            if let Some(stem) = path.file_stem().and_then(|s| s.to_str()) {
                self.unit_by_stem.insert(stem.to_lowercase(), id.clone());
            }
            self.analyses.insert(
                id.clone(),
                AnalyzedUnit {
                    uri: url.to_string(),
                    analyzer,
                    interface,
                },
            );
        }

        self.analyses.len()
    }

    fn get_rename_edit(
        &self,
        uri: String,
        position: Position,
        new_name: String,
    ) -> Option<WorkspaceEdit> {
        // document_map before semanticast_map (consistent lock order).
        let rope = self.document_map.get(&uri)?;
        let result = self.semanticast_map.get(&uri)?;
        let analyzer = &result.analyzer;

        // Identify exactly which symbol the cursor is on; rename only that one.
        let offset = position_to_offset(position, &rope)?;
        let symbol_id = self.find_symbol_at_offset(analyzer, offset)?;

        // Refuse to rename symbols without a real definition span (builtins like
        // `writeln`, or externally-provided symbols) — we can't rewrite those.
        let has_real_def = analyzer
            .definitions
            .iter()
            .any(|(span, id)| *id == symbol_id && span.start != span.end);
        if !has_real_def {
            return None;
        }

        // Every occurrence of this symbol = its definition(s) + its references.
        let mut seen = std::collections::HashSet::new();
        let mut edits = Vec::new();
        for (span, id) in analyzer
            .definitions
            .iter()
            .chain(analyzer.references.iter())
        {
            if *id != symbol_id || span.start == span.end {
                continue;
            }
            if !seen.insert((span.start, span.end)) {
                continue; // dedup: overlapping edits are invalid in a WorkspaceEdit
            }
            let start = offset_to_position(span.start, &rope)?;
            let end = offset_to_position(span.end, &rope)?;
            edits.push(TextEdit {
                range: Range::new(start, end),
                new_text: new_name.clone(),
            });
        }
        if edits.is_empty() {
            return None;
        }

        let parsed_uri =
            Url::parse(&uri).unwrap_or_else(|_| Url::from_directory_path(&uri).unwrap());
        let mut edit_map = std::collections::HashMap::new();
        edit_map.insert(parsed_uri, edits);

        Some(WorkspaceEdit::new(edit_map))
    }

    // fn get_struct_id_from_field(
    //     &self,
    //     field_expr: &l_lang::ExprField,
    //     semantic_result: &CompileResult,
    // ) -> Option<SymbolId> {
    //     let mut access_arr = vec![];
    //     let mut cur = field_expr.object.as_ref()?;
    //     loop {
    //         match cur.as_ref() {
    //             l_lang::Expr::Field(field_expr) => {
    //                 access_arr.push(field_expr.field.as_ref()?.name.clone());
    //                 cur = field_expr.object.as_ref()?;
    //             }
    //             l_lang::Expr::Name(_name_expr) => {
    //                 break;
    //             }
    //             _ => {
    //                 return None;
    //             }
    //         }
    //     }
    //     access_arr.reverse();
    //
    //     let reference_id = semantic_result
    //         .semantic
    //         .get_reference_at(field_expr.object.as_ref()?.span().start as usize)?;
    //     let symbol_id = semantic_result.semantic.references[reference_id]?;
    //     let ty_info = semantic_result.semantic.get_symbol_type(symbol_id)?;
    //     let Type::Struct(mut struct_id) = ty_info.ty else {
    //         return None;
    //     };
    //
    //     for field_name in access_arr {
    //         let struct_def = semantic_result.semantic.structs.get(&struct_id)?;
    //         let field = struct_def.fields.iter().find(|f| f.name == field_name)?;
    //         let Type::Struct(next_struct_id) = field.ty else {
    //             return None;
    //         };
    //         struct_id = next_struct_id;
    //     }
    //     Some(struct_id)
    // }
    //
    // fn get_completion(&self, params: CompletionParams) -> Option<Vec<CompletionItem>> {
    //     let text_doc_position = params.text_document_position;
    //     let uri = text_doc_position.text_document.uri.to_string();
    //     let semantic_result = self.semanticast_map.get(&uri)?;
    //     let rope = self.document_map.get(&uri)?;
    //     let offset = position_to_offset(text_doc_position.position, &rope)?;
    //
    //     let mut items = Vec::new();
    //
    //     // Try to find the AST node at the current position
    //     if let Some(nearest_node) =
    //         find_node_at_offset(semantic_result.program.file(), offset as u32)
    //     {
    //         match nearest_node {
    //             // Field access completion: suggest available fields/members
    //             AstNode::ExprField(field_expr) => {
    //                 let struct_id = self.get_struct_id_from_field(field_expr, &semantic_result)?;
    //                 let struct_def = semantic_result.semantic.structs.get(&struct_id)?;
    //                 struct_def.fields.iter().for_each(|field| {
    //                     items.push(CompletionItem {
    //                         label: field.name.clone(),
    //                         kind: Some(CompletionItemKind::FIELD),
    //                         detail: Some(format!(
    //                             ": {}",
    //                             field.ty.format_literal_type(&semantic_result.semantic)
    //                         )),
    //                         insert_text: Some(field.name.clone()),
    //                         ..Default::default()
    //                     });
    //                 });
    //             }
    //             _ => {
    //                 // Default: suggest all available symbols
    //                 let bindings = &semantic_result.semantic.bindings;
    //                 bindings
    //                     .iter_enumerated()
    //                     .for_each(|(symbol_id, type_info)| {
    //                         let symbol_kind = semantic_result.semantic.get_symbol_kind(symbol_id);
    //                         let span = semantic_result.semantic.get_symbol_span(symbol_id);
    //
    //                         let name_slice =
    //                             rope.byte_slice(span.start as usize..span.end as usize);
    //                         if let Ok(name) = std::str::from_utf8(
    //                             name_slice.bytes().collect::<Vec<_>>().as_slice(),
    //                         ) {
    //                             let (kind, detail) = match symbol_kind {
    //                                 l_lang::SymbolKind::Variable => (
    //                                     Some(CompletionItemKind::VARIABLE),
    //                                     Some(format!(
    //                                         ": {}",
    //                                         type_info
    //                                             .ty
    //                                             .format_literal_type(&semantic_result.semantic)
    //                                     )),
    //                                 ),
    //                                 l_lang::SymbolKind::Function => {
    //                                     (Some(CompletionItemKind::FUNCTION), None)
    //                                 }
    //                                 l_lang::SymbolKind::Struct => {
    //                                     (Some(CompletionItemKind::STRUCT), None)
    //                                 }
    //                                 _ => (None, None),
    //                             };
    //
    //                             items.push(CompletionItem {
    //                                 label: name.to_string(),
    //                                 kind,
    //                                 detail,
    //                                 insert_text: Some(name.to_string()),
    //                                 ..Default::default()
    //                             });
    //                         }
    //                     });
    //             }
    //         }
    //     } else {
    //         // No node found, suggest all available symbols
    //         let bindings = &semantic_result.semantic.bindings;
    //         bindings
    //             .iter_enumerated()
    //             .for_each(|(symbol_id, type_info)| {
    //                 let symbol_kind = semantic_result.semantic.get_symbol_kind(symbol_id);
    //                 let span = semantic_result.semantic.get_symbol_span(symbol_id);
    //
    //                 let name_slice = rope.byte_slice(span.start as usize..span.end as usize);
    //                 if let Ok(name) =
    //                     std::str::from_utf8(name_slice.bytes().collect::<Vec<_>>().as_slice())
    //                 {
    //                     let (kind, detail) = match symbol_kind {
    //                         l_lang::SymbolKind::Variable => (
    //                             Some(CompletionItemKind::VARIABLE),
    //                             Some(format!(
    //                                 ": {}",
    //                                 type_info.ty.format_literal_type(&semantic_result.semantic)
    //                             )),
    //                         ),
    //                         l_lang::SymbolKind::Function => {
    //                             (Some(CompletionItemKind::FUNCTION), None)
    //                         }
    //                         l_lang::SymbolKind::Struct => (Some(CompletionItemKind::STRUCT), None),
    //                         _ => (None, None),
    //                     };
    //
    //                     items.push(CompletionItem {
    //                         label: name.to_string(),
    //                         kind,
    //                         detail,
    //                         insert_text: Some(name.to_string()),
    //                         ..Default::default()
    //                     });
    //                 }
    //             });
    //     }
    //     Some(items)
    // }

    async fn on_change(&self, item: TextDocumentChange<'_>) {
        let lexer = lexer::Lexer::new(item.text);
        let parser = parser::CompilationUnitParser::new();

        let mut diagnostics = Vec::new();

        match parser.parse(lexer) {
            Ok(unit) => {
                let (diags, analyzer) = get_diagnostics(item.text, &unit);
                diagnostics.extend(diags);

                self.semanticast_map.insert(
                    item.uri.clone(),
                    AnalysisResult {
                        ast: unit,
                        analyzer,
                    },
                );
            }
            Err(e) => {
                let lsp_diag = lalrpop_error_to_diagnostic(item.text, e);
                diagnostics.push(lsp_diag);
            }
        };

        let uri =
            Url::parse(&item.uri).unwrap_or_else(|_| Url::from_directory_path(&item.uri).unwrap());
        self.client
            .publish_diagnostics(uri, diagnostics, None)
            .await;

        let rope = Rope::from(item.text);
        self.document_map.insert(item.uri.clone(), rope);
    }

    fn build_semantic_tokens(&self, uri: &str) -> Option<Vec<SemanticToken>> {
        // Always lock document_map before semanticast_map, matching hover/goto/
        // formatting, so the two maps are never acquired in opposite orders.
        let rope = self.document_map.get(uri)?;
        let semantic_result = self.semanticast_map.get(uri)?;
        let analyzer = &semantic_result.analyzer;

        let mut sema: HashMap<usize, u32> = HashMap::new();
        for (span, id) in analyzer
            .definitions
            .iter()
            .chain(analyzer.references.iter())
        {
            if span.start == span.end {
                continue;
            } // pula builtins (span default 0..0)
            if let Some(info) = analyzer.symbol_table.all_symbols.get(*id) {
                let idx = match info.kind {
                    SymbolKind::Function { .. } | SymbolKind::Procedure { .. } => 5, // FUNCTION
                    SymbolKind::Type { .. } => 6,
                    // TYPE
                    SymbolKind::Variable { .. } | SymbolKind::Constant { .. } => 4, // VARIABLE
                };
                sema.insert(span.start, idx);
            }
        }

        let mut incomplete_tokens: Vec<(usize, usize, u32)> = Vec::new();
        for spanned in lexer::Lexer::new(&rope.to_string()) {
            let Ok((start, token, end)) = spanned else {
                continue;
            };
            let Some(mut idx) = token_type_index(&token) else {
                continue;
            };

            if matches!(token, Token::Identifier(_)) {
                if let Some(&sidx) = sema.get(&start) {
                    idx = sidx;
                }
            }
            incomplete_tokens.push((start, end - start, idx));
        }

        incomplete_tokens.sort_by(|a, b| a.0.cmp(&b.0));

        // Convert to LSP SemanticToken format with delta encoding
        let mut pre_line: u32 = 0;
        let mut pre_start: u32 = 0;

        let semantic_tokens = incomplete_tokens
            .iter()
            .map(|(start, length, token_type)| {
                // Convert byte offset to line and character
                let line = rope.line_of_byte(*start) as u32;
                let line_start_byte = rope.byte_of_line(line as usize);
                let char_offset = *start - line_start_byte;

                let delta_line = line - pre_line;
                let delta_start = if delta_line == 0 {
                    char_offset as u32 - pre_start
                } else {
                    char_offset as u32
                };

                let token = SemanticToken {
                    delta_line,
                    delta_start,
                    length: *length as u32,
                    token_type: *token_type,
                    token_modifiers_bitset: 0,
                };

                pre_line = line;
                pre_start = char_offset as u32;

                token
            })
            .collect::<Vec<_>>();

        Some(semantic_tokens)
    }
}

fn token_type_index(token: &Token) -> Option<u32> {
    use Token::*;
    Some(match token {
        // 0 = KEYWORD — palavras reservadas
        Program | Var | Const | Type | Label | Procedure | Function | Begin | End | If | Then
        | Else | While | Do | For | To | Downto | Repeat | Until | Case | Of | Goto | Array
        | Record | Set | File | Write | Writeln | Read | Readln | With | Forward | Name
        | Packed | Unit | Interface | Implementation | Uses | Initialization | External | Nil => 0,

        // operadores que são palavras — também tratados como keyword
        // (troque para 1/OPERATOR se preferir tematizar como símbolo)
        Not | And | Or | Div | Mod | In => 0,

        // booleanos: true/false como keyword/constante
        BooleanLiteral(_) => 0,

        // 6 = TYPE — tipos primitivos embutidos
        Integer | Real | Boolean | String | Char => 6,

        // 1 = OPERATOR — operadores simbólicos
        Plus | Minus | Slash | Star | Gte | Lte | Gt | Lt | Eq | Neq | Assign | Caret => 1,

        // 2 = NUMBER
        IntegerLiteral(_) | RealLiteral(_) => 2,

        // 3 = STRING — strings e chars
        StringLiteral(_) | CharLiteral(_) | CharCode(_) => 3,

        // 4 = VARIABLE — default p/ identificadores
        // (no passo 4 você refina para FUNCTION/TYPE via o analyzer)
        Identifier(_) => 4,

        // pontuação e erro → sem highlight
        LParen | RParen | LBrace | RBrace | LBracket | RBracket | Comma | Colon | Semicolon
        | Dot | DotDot | Error => return None,
    })
}

fn legend() -> SemanticTokensLegend {
    SemanticTokensLegend {
        token_types: vec![
            SemanticTokenType::KEYWORD,
            SemanticTokenType::OPERATOR,
            SemanticTokenType::NUMBER,
            SemanticTokenType::STRING,
            SemanticTokenType::VARIABLE,
            SemanticTokenType::FUNCTION,
            SemanticTokenType::TYPE,
        ],
        token_modifiers: vec![],
    }
}

fn lalrpop_error_to_diagnostic(text: &str, err: ParseError<usize, Token, String>) -> Diagnostic {
    let (start, end, message) = match err {
        ParseError::InvalidToken { location } => {
            (location, location + 1, "Invalid token".to_string())
        }
        ParseError::UnrecognizedEof { location, expected } => (
            location,
            location,
            format!("Unrecognized EOF, expected: {}", expected.join(", ")),
        ),
        ParseError::UnrecognizedToken {
            token: (start, token, end),
            expected,
        } => (
            start,
            end,
            format!(
                "Unrecognized token {:?}, expected: {}",
                token,
                expected.join(", ")
            ),
        ),
        ParseError::ExtraToken {
            token: (start, token, end),
        } => (start, end, format!("Extra token {:?}", token)),
        ParseError::User { error } => (0, 0, format!("User error: {}", error)),
    };

    let rope = Rope::from(text);
    let start_pos = offset_to_position(start, &rope).unwrap();
    let end_pos = offset_to_position(end, &rope).unwrap();

    Diagnostic {
        range: Range::new(start_pos, end_pos),
        severity: Some(DiagnosticSeverity::ERROR),
        message,
        source: Some("pascalm".to_string()),
        ..Default::default()
    }
}

pub fn get_diagnostics(
    text: &str,
    compilation_unit: &CompilationUnit,
) -> (Vec<Diagnostic>, SemanticAnalyzer) {
    let mut all_diagnostics = Vec::new();
    let mut analyzer = SemanticAnalyzer::new();

    // The analyzer reports semantic problems both through its `diagnostics` buffer
    // and (for the first fatal error) as a `Result::Err`; capture the latter too so
    // the editor still gets a diagnostic when analysis aborts early.
    let analysis_error = match &compilation_unit {
        CompilationUnit::Program(p) => analyzer.analyze_program(p).err(),
        CompilationUnit::Unit(u) => analyzer.analyze_unit(u).err(),
    };

    let rope = Rope::from(text);

    if let Some(message) = analysis_error {
        let pos = offset_to_position(0, &rope).unwrap_or_else(|| Position::new(0, 0));
        all_diagnostics.push(Diagnostic {
            range: Range::new(pos, pos),
            severity: Some(DiagnosticSeverity::ERROR),
            source: Some("pascalm".to_string()),
            message,
            ..Default::default()
        });
    }

    for diag in &analyzer.diagnostics {
        let start = offset_to_position(diag.span.start, &rope).unwrap();
        let end = offset_to_position(diag.span.end, &rope).unwrap();
        all_diagnostics.push(Diagnostic {
            range: Range::new(start, end),
            severity: Some(DiagnosticSeverity::ERROR),
            source: Some("pascalm".to_string()),
            message: diag.message.clone(),
            ..Default::default()
        });
    }

    (all_diagnostics, analyzer)
}

fn offset_to_position(offset: usize, rope: &Rope) -> Option<Position> {
    // Clamp instead of bailing: while the user types, a stale analysis can hold
    // spans that point past the (now shorter) document. Clamping keeps the
    // conversion total so callers never panic on `unwrap()` — a hung request
    // here shows up to the editor as an LSP timeout.
    let offset = offset.min(rope.byte_len());
    let line = rope.line_of_byte(offset);
    let line_start_byte = rope.byte_of_line(line);
    let column = offset - line_start_byte;
    Some(Position::new(line as u32, column as u32))
}

fn position_to_offset(position: Position, rope: &Rope) -> Option<usize> {
    if position.line as usize >= rope.line_len() {
        return None;
    }
    let line_byte_offset = rope.byte_of_line(position.line as usize);
    Some(line_byte_offset + position.character as usize)
}

/// Recursively collect `.pas`/`.pascalm` files under `dir`, skipping build and
/// VCS directories. Depth-bounded to avoid pathological trees.
fn collect_pascal_files(dir: &Path, out: &mut Vec<PathBuf>, depth: usize) {
    if depth > 16 {
        return;
    }
    let Ok(entries) = std::fs::read_dir(dir) else {
        return;
    };
    for entry in entries.flatten() {
        let path = entry.path();
        if path.is_dir() {
            let name = entry.file_name();
            let name = name.to_string_lossy();
            if name == "target" || name == ".git" || name == "node_modules" {
                continue;
            }
            collect_pascal_files(&path, out, depth + 1);
        } else if matches!(
            path.extension().and_then(|s| s.to_str()),
            Some("pas") | Some("pascalm")
        ) {
            out.push(path);
        }
    }
}

/// Extract the identifier (`[A-Za-z0-9_]+`) surrounding `offset`, if any.
fn word_at_offset(text: &str, offset: usize) -> Option<String> {
    let bytes = text.as_bytes();
    if offset > bytes.len() {
        return None;
    }
    let is_ident = |b: u8| b == b'_' || b.is_ascii_alphanumeric();
    let mut start = offset;
    while start > 0 && is_ident(bytes[start - 1]) {
        start -= 1;
    }
    let mut end = offset;
    while end < bytes.len() && is_ident(bytes[end]) {
        end += 1;
    }
    if start == end {
        return None;
    }
    Some(text[start..end].to_string())
}

/// The `uses` specs of a compilation unit (lowercased — the keys a unit
/// resolves by).
fn unit_uses(unit: &CompilationUnit) -> Vec<String> {
    let lists: Vec<&Option<Vec<String>>> = match unit {
        CompilationUnit::Program(p) => vec![&p.uses],
        CompilationUnit::Unit(u) => vec![&u.interface.uses, &u.implementation.uses],
    };
    lists
        .into_iter()
        .flatten()
        .flatten()
        .map(|s| s.to_lowercase())
        .collect()
}

#[tower_lsp::async_trait]
impl LanguageServer for Backend {
    #[allow(deprecated)]
    async fn initialize(&self, params: InitializeParams) -> Result<InitializeResult> {
        // Capture the workspace root now; index it in `initialized` so we don't
        // delay the initialize handshake.
        let root = params
            .workspace_folders
            .as_ref()
            .and_then(|folders| folders.first())
            .map(|folder| folder.uri.clone())
            .or(params.root_uri)
            .and_then(|uri| uri.to_file_path().ok());
        if let Ok(mut guard) = self.root.lock() {
            *guard = root;
        }

        Ok(InitializeResult {
            capabilities: ServerCapabilities {
                document_formatting_provider: Some(OneOf::Left(true)),
                inlay_hint_provider: Some(OneOf::Left(false)), // verificar para adicionar true
                text_document_sync: Some(TextDocumentSyncCapability::Options(
                    TextDocumentSyncOptions {
                        open_close: Some(true),
                        change: Some(TextDocumentSyncKind::FULL),
                        save: Some(TextDocumentSyncSaveOptions::SaveOptions(SaveOptions {
                            include_text: Some(true),
                        })),
                        ..Default::default()
                    },
                )),
                hover_provider: Some(HoverProviderCapability::Simple(true)),
                completion_provider: Some(CompletionOptions {
                    resolve_provider: Some(false),
                    trigger_characters: Some(vec![".".to_string()]),
                    work_done_progress_options: Default::default(),
                    all_commit_characters: None,
                    completion_item: None,
                }),
                workspace: Some(WorkspaceServerCapabilities {
                    workspace_folders: Some(WorkspaceFoldersServerCapabilities {
                        supported: Some(true),
                        change_notifications: Some(OneOf::Left(true)),
                    }),
                    file_operations: None,
                }),
                semantic_tokens_provider: Some(
                    SemanticTokensServerCapabilities::SemanticTokensOptions(
                        SemanticTokensOptions {
                            legend: legend(),
                            full: Some(SemanticTokensFullOptions::Bool(true)),
                            range: Some(false),
                            ..Default::default()
                        },
                    ),
                ),
                definition_provider: Some(OneOf::Left(true)),
                references_provider: Some(OneOf::Left(true)),
                rename_provider: Some(OneOf::Left(true)),
                ..Default::default()
            },
            server_info: Some(ServerInfo {
                name: "pascalmls".to_string(),
                version: Some("0.0.1".to_string()),
            }),
        })
    }

    async fn initialized(&self, _: InitializedParams) {
        let root = self.root.lock().ok().and_then(|guard| guard.clone());
        let message = match root {
            Some(root) => {
                let indexed = self.index_workspace(&root);
                let analyzed = self.analyze_workspace(&root);
                format!(
                    "Pascalm LSP initialized — indexed {indexed}, analyzed {analyzed} unit(s) under {}",
                    root.display()
                )
            }
            None => "Pascalm LSP initialized (no workspace root)".to_string(),
        };
        self.client.log_message(MessageType::INFO, message).await;
    }

    async fn shutdown(&self) -> Result<()> {
        Ok(())
    }

    async fn did_open(&self, params: DidOpenTextDocumentParams) {
        self.on_change(TextDocumentChange {
            uri: params.text_document.uri.to_string(),
            text: &params.text_document.text,
        })
        .await;
    }

    async fn did_change(&self, params: DidChangeTextDocumentParams) {
        // FULL sync sends the whole document as the last change; some clients may
        // send an empty list, so guard against indexing an empty vec (a panic
        // here would kill the task and stall the server).
        let Some(change) = params.content_changes.last() else {
            return;
        };
        self.on_change(TextDocumentChange {
            text: &change.text,
            uri: params.text_document.uri.to_string(),
        })
        .await;
    }

    async fn did_close(&self, params: DidCloseTextDocumentParams) {
        let uri = params.text_document.uri.to_string();
        self.document_map.remove(&uri);

        self.client
            .publish_diagnostics(params.text_document.uri, vec![], None)
            .await;
    }

    async fn did_save(&self, params: DidSaveTextDocumentParams) {
        let uri = params.text_document.uri.to_string();

        debug!("file saved");

        // Copy the text out and drop the document_map guard BEFORE awaiting.
        // Holding a DashMap guard across `.await` can deadlock the runtime
        // against a concurrent did_change write on the same shard.
        let text = match self.document_map.get(&uri) {
            Some(text_rope) => text_rope.deref().to_string(),
            None => return,
        };

        let lexer = lexer::Lexer::new(&text);
        let parser = parser::CompilationUnitParser::new();
        if let Ok(unit) = parser.parse(lexer) {
            let (diagnostics, analyzer) = get_diagnostics(&text, &unit);

            self.client
                .publish_diagnostics(params.text_document.uri, diagnostics, None)
                .await;

            self.semanticast_map.insert(
                uri,
                AnalysisResult {
                    ast: unit,
                    analyzer,
                },
            );
        }
    }

    async fn goto_definition(
        &self,
        params: GotoDefinitionParams,
    ) -> Result<Option<GotoDefinitionResponse>> {
        let uri = params
            .text_document_position_params
            .text_document
            .uri
            .to_string();
        let position = params.text_document_position_params.position;

        let (Some(rope), Some(result)) =
            (self.document_map.get(&uri), self.semanticast_map.get(&uri))
        else {
            return Ok(None);
        };
        let Some(offset) = position_to_offset(position, &rope) else {
            return Ok(None);
        };

        // 1) Local definition (same file).
        if let Some(symbol_id) = self.find_symbol_at_offset(&result.analyzer, offset) {
            for (span, id) in &result.analyzer.definitions {
                // Skip synthetic spans (0..0) — those are imported symbols,
                // handled by the cross-file step below.
                if *id == symbol_id && span.start != span.end {
                    let start = offset_to_position(span.start, &rope).unwrap();
                    let end = offset_to_position(span.end, &rope).unwrap();
                    return Ok(Some(GotoDefinitionResponse::Scalar(Location::new(
                        params.text_document_position_params.text_document.uri,
                        Range::new(start, end),
                    ))));
                }
            }
        }

        // 2) Cross-file: the symbol is likely imported from a `uses` unit.
        let text = rope.to_string();
        if let Some(name) = word_at_offset(&text, offset) {
            let uses = unit_uses(&result.ast);
            if let Some(location) = self.cross_file_definition(&uses, &name) {
                return Ok(Some(GotoDefinitionResponse::Scalar(location)));
            }
        }

        Ok(None)
    }

    async fn hover(&self, params: HoverParams) -> Result<Option<Hover>> {
        let uri = params
            .text_document_position_params
            .text_document
            .uri
            .to_string();
        let position = params.text_document_position_params.position;

        if let (Some(rope), Some(result)) =
            (self.document_map.get(&uri), self.semanticast_map.get(&uri))
        {
            if let Some(offset) = position_to_offset(position, &rope) {
                if let Some(symbol_id) = self.find_symbol_at_offset(&result.analyzer, offset) {
                    if let Some(symbol_info) =
                        result.analyzer.symbol_table.all_symbols.get(symbol_id)
                    {
                        let content = format!(
                            "```pascal\n{} : {}\n```",
                            symbol_info.name, symbol_info.kind
                        );
                        return Ok(Some(Hover {
                            contents: HoverContents::Markup(MarkupContent {
                                kind: MarkupKind::Markdown,
                                value: content,
                            }),
                            range: None,
                        }));
                    }
                }
            }
        }
        Ok(None)
    }

    async fn semantic_tokens_full(
        &self,
        params: SemanticTokensParams,
    ) -> Result<Option<SemanticTokensResult>> {
        let uri = params.text_document.uri.to_string();
        let data = self.build_semantic_tokens(&uri).unwrap_or_default();
        Ok(Some(SemanticTokensResult::Tokens(SemanticTokens {
            result_id: None,
            data,
        })))
    }

    async fn completion(&self, _params: CompletionParams) -> Result<Option<CompletionResponse>> {
        Ok(None)
    }

    async fn rename(&self, params: RenameParams) -> Result<Option<WorkspaceEdit>> {
        let uri = params.text_document_position.text_document.uri.to_string();
        let position = params.text_document_position.position;
        let edits = self.get_rename_edit(uri, position, params.new_name);
        Ok(edits)
    }

    async fn references(&self, params: ReferenceParams) -> Result<Option<Vec<Location>>> {
        let uri = params.text_document_position.text_document.uri;
        let position = params.text_document_position.position;
        let include_decl = params.context.include_declaration;

        let (Some(rope), Some(result)) = (
            self.document_map.get(&uri.to_string()),
            self.semanticast_map.get(&uri.to_string()),
        ) else {
            return Ok(None);
        };

        let Some(offset) = position_to_offset(position, &rope) else {
            return Ok(None);
        };
        let Some(symbol_id) = self.find_symbol_at_offset(&result.analyzer, offset) else {
            return Ok(None);
        };

        let mut refs = Vec::new();

        if include_decl {
            for (span, id) in &result.analyzer.definitions {
                if *id == symbol_id && span.start != span.end {
                    let start = offset_to_position(span.start, &rope).unwrap();
                    let end = offset_to_position(span.end, &rope).unwrap();
                    refs.push(Location {
                        uri: uri.clone(),
                        range: Range::new(start, end),
                    })
                }
            }
        }

        for (span, id) in &result.analyzer.references {
            if *id == symbol_id {
                let start = offset_to_position(span.start, &rope).unwrap();
                let end = offset_to_position(span.end, &rope).unwrap();
                refs.push(Location {
                    uri: uri.clone(),
                    range: Range::new(start, end),
                });
            }
        }

        Ok(Some(refs))
    }

    async fn formatting(&self, params: DocumentFormattingParams) -> Result<Option<Vec<TextEdit>>> {
        let uri = params.text_document.uri.to_string();
        let Some(rope) = self.document_map.get(&uri) else {
            return Ok(None);
        };
        let text = rope.to_string();

        // Only format syntactically valid input — never rewrite a broken file.
        let lexer = lexer::Lexer::new(&text);
        let parser = parser::CompilationUnitParser::new();
        let Ok(unit) = parser.parse(lexer) else {
            return Ok(None);
        };

        let formatted = pascalm::formatter::format_compilation_unit(&unit, &text);
        if formatted == text {
            return Ok(None);
        }

        // Replace the whole document with the formatted output.
        let end = offset_to_position(text.len(), &rope).unwrap_or(Position::new(0, 0));
        let range = Range::new(Position::new(0, 0), end);
        Ok(Some(vec![TextEdit {
            range,
            new_text: formatted,
        }]))
    }

    async fn did_change_configuration(&self, _: DidChangeConfigurationParams) {
        debug!("configuration changed!");
    }

    async fn did_change_workspace_folders(&self, _: DidChangeWorkspaceFoldersParams) {
        debug!("workspace folders changed!");
    }

    async fn did_change_watched_files(&self, _: DidChangeWatchedFilesParams) {
        debug!("watched files have changed!");
    }
}

#[tokio::main]
async fn main() {
    env_logger::init();

    let stdin = tokio::io::stdin();
    let stdout = tokio::io::stdout();

    let (service, socket) = LspService::build(|client| Backend {
        client,
        semanticast_map: DashMap::new(),
        document_map: DashMap::new(),
        workspace: DashMap::new(),
        analyses: DashMap::new(),
        unit_by_stem: DashMap::new(),
        root: Mutex::new(None),
    })
    .finish();

    Server::new(stdin, stdout, socket).serve(service).await;
}
