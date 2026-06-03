use lalrpop_util::lalrpop_mod;

pub mod lexer;
pub mod ast;
pub mod typed_ast;
pub mod symbol_table;
pub mod analyzer;
pub mod codegen;
lalrpop_mod!(pub parser);

pub use analyzer::{SemanticAnalyzer, Diagnostic};
pub use ast::{CompilationUnit, Program, Unit};
pub use symbol_table::{SymbolTable, SymbolKind, SymbolId};
