use crate::ast::{BinOp, UnaryOp};

#[derive(Debug, Clone, PartialEq)]
pub enum Type {
    Integer,
    Real,
    Boolean,
    Char,
    String,
    Array { element_type: Box<Type>, size: u64 },
    Record { fields: Vec<(String, Type)> },
    Pointer(Box<Type>),
    Set(Box<Type>),
    #[allow(dead_code)]
    Subrange { start: i64, end: i64 },
    Enum(Vec<String>),
    Procedure,
    Function(Box<Type>),
    Void,
}

#[derive(Debug, Clone)]
pub struct TypedProgram {
    #[allow(dead_code)]
    pub name: String,
    pub uses: Vec<String>,
    pub block: TypedBlock,
}

#[derive(Debug, Clone)]
pub struct TypedBlock {
    #[allow(dead_code)]
    pub labels: Vec<i64>,
    pub constants: Vec<(String, TypedExpr)>,
    pub variables: Vec<(String, Type)>,
    pub procedures: Vec<TypedProcFunc>,
    pub statements: Vec<TypedStmt>,
}

#[derive(Debug, Clone)]
pub struct TypedProcFunc {
    pub name: String,
    pub params: Vec<(String, Type, bool)>, // name, type, is_var
    pub return_type: Type,
    pub body: Option<TypedBlock>,
    pub external_name: Option<String>,
}

#[derive(Debug, Clone)]
pub enum TypedStmt {
    Assignment {
        target: TypedExpr,
        value: TypedExpr,
    },
    If {
        condition: TypedExpr,
        then_stmt: Box<TypedStmt>,
        else_stmt: Option<Box<TypedStmt>>,
    },
    While {
        condition: TypedExpr,
        body: Box<TypedStmt>,
    },
    Repeat {
        body: Vec<TypedStmt>,
        until: TypedExpr,
    },
    For {
        id: String,
        start: TypedExpr,
        up: bool,
        end: TypedExpr,
        body: Box<TypedStmt>,
    },
    ProcedureCall {
        name: String,
        args: Vec<TypedExpr>,
    },
    Compound(Vec<TypedStmt>),
    With {
        objects: Vec<TypedExpr>,
        body: Box<TypedStmt>,
    },
    Goto(i64),
    Labeled(i64, Box<TypedStmt>),
    Case {
        expr: TypedExpr,
        items: Vec<TypedCaseItem>,
        else_stmt: Option<Box<TypedStmt>>,
    },
    Empty,
}

#[derive(Debug, Clone)]
pub struct TypedCaseItem {
    pub labels: Vec<TypedExpr>,
    pub stmt: TypedStmt,
}

#[derive(Debug, Clone)]
pub struct TypedExpr {
    pub ty: Type,
    pub kind: TypedExprKind,
}

#[derive(Debug, Clone)]
pub enum TypedExprKind {
    Integer(i64),
    Real(f64),
    Boolean(bool),
    Char(char),
    String(String),
    Variable(TypedVariable),
    Binary {
        op: BinOp,
        left: Box<TypedExpr>,
        right: Box<TypedExpr>,
    },
    Unary {
        op: UnaryOp,
        expr: Box<TypedExpr>,
    },
    FunctionCall {
        name: String,
        args: Vec<TypedExpr>,
    },
    Set(Vec<TypedElement>),
    Nil,
}

#[derive(Debug, Clone)]
pub enum TypedVariable {
    Id(String),
    MemberAccess {
        record: Box<TypedExpr>,
        field: String,
    },
    ArrayAccess {
        array: Box<TypedExpr>,
        index: Box<TypedExpr>,
    },
    PointerDeref(Box<TypedExpr>),
}

#[derive(Debug, Clone)]
pub enum TypedElement {
    Single(TypedExpr),
    Range(TypedExpr, TypedExpr),
}
