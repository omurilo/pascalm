#[derive(Debug, Clone, PartialEq)]
pub enum CompilationUnit {
    Program(Program),
    Unit(Unit),
}

#[derive(Debug, Clone, PartialEq)]
pub struct Program {
    pub name: String,
    pub heading: Option<Vec<String>>,
    pub uses: Option<Vec<String>>,
    pub block: Block,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Unit {
    pub name: String,
    pub interface: InterfaceSection,
    pub implementation: ImplementationSection,
    pub initialization: Option<Vec<Stmt>>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct InterfaceSection {
    pub uses: Option<Vec<String>>,
    pub constants: Option<Vec<ConstDecl>>,
    pub types: Option<Vec<TypeDecl>>,
    pub variables: Option<Vec<VarDecl>>,
    pub headers: Option<Vec<ProcFuncDecl>>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct ImplementationSection {
    pub uses: Option<Vec<String>>,
    pub constants: Option<Vec<ConstDecl>>,
    pub types: Option<Vec<TypeDecl>>,
    pub variables: Option<Vec<VarDecl>>,
    pub bodies: Option<Vec<ProcFuncDecl>>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Block {
    pub labels: Option<Vec<i64>>,
    pub constants: Option<Vec<ConstDecl>>,
    pub types: Option<Vec<TypeDecl>>,
    pub variables: Option<Vec<VarDecl>>,
    pub procedures_functions: Option<Vec<ProcFuncDecl>>,
    pub statements: Vec<Stmt>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct ConstDecl {
    pub name: String,
    pub value: Expr,
}

#[derive(Debug, Clone, PartialEq)]
pub struct TypeDecl {
    pub name: String,
    pub type_expr: TypeExpr,
}

#[derive(Debug, Clone, PartialEq)]
pub struct VarDecl {
    pub ids: Vec<String>,
    pub type_expr: TypeExpr,
}

#[derive(Debug, Clone, PartialEq)]
pub enum ProcFuncDecl {
    Procedure {
        name: String,
        params: Option<Vec<Param>>,
        block_or_forward: BlockOrForward,
    },
    Function {
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
    External(Option<String>),
}

#[derive(Debug, Clone, PartialEq)]
pub enum Param {
    Variable {
        is_var: bool,
        ids: Vec<String>,
        type_name: String,
    },
    Procedure {
        id: String,
        params: Option<Vec<Param>>,
    },
    Function {
        id: String,
        params: Option<Vec<Param>>,
        return_type: String,
    },
}

#[derive(Debug, Clone, PartialEq)]
pub enum TypeExpr {
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
    Procedure {
        params: Option<Vec<Param>>,
    },
    Function {
        params: Option<Vec<Param>>,
        return_type: String,
    },
}

#[derive(Debug, Clone, PartialEq)]
pub struct VariantPart {
    pub tag_field: Option<String>,
    pub tag_type: String,
    pub variants: Vec<Variant>,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Variant {
    pub labels: Vec<Expr>,
    pub fields: Vec<VarDecl>,
    pub nested_variant: Option<Box<VariantPart>>,
}

#[derive(Debug, Clone, PartialEq)]
pub enum Stmt {
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
    pub labels: Vec<Expr>,
    pub stmt: Stmt,
}

#[derive(Debug, Clone, PartialEq)]
pub enum Expr {
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

#[derive(Debug, Clone, PartialEq)]
pub enum Variable {
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

#[derive(Debug, Clone, PartialEq)]
pub enum Element {
    Single(Expr),
    Range(Expr, Expr),
}

#[derive(Debug, Clone, PartialEq)]
pub enum BinOp {
    Add,
    Sub,
    Mul,
    Div,
    FloatDiv,
    Mod,
    Eq,
    Neq,
    Lt,
    Lte,
    Gt,
    Gte,
    And,
    Or,
    In,
    DotDot,
}

#[derive(Debug, Clone, PartialEq)]
pub enum UnaryOp {
    Plus,
    Minus,
    Not,
}
