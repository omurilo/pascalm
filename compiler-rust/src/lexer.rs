use logos::Logos;

#[derive(Logos, Debug, PartialEq, Clone)]
#[logos(skip r"[ \t\r\n\f]+")] // Skip whitespace
#[logos(skip r"\{[^}]*\}")]    // Skip { comments }
#[logos(skip r"\(\*(?:[^*]|\*[^)])*\*\)")] // Simple (* *) comment skip (non-nested for now)
pub enum Token {
    // Keywords (case-insensitive)
    #[token("program", ignore(case))]
    Program,
    #[token("var", ignore(case))]
    Var,
    #[token("const", ignore(case))]
    Const,
    #[token("type", ignore(case))]
    Type,
    #[token("label", ignore(case))]
    Label,
    #[token("procedure", ignore(case))]
    Procedure,
    #[token("function", ignore(case))]
    Function,
    #[token("begin", ignore(case))]
    Begin,
    #[token("end", ignore(case))]
    End,
    #[token("if", ignore(case))]
    If,
    #[token("then", ignore(case))]
    Then,
    #[token("else", ignore(case))]
    Else,
    #[token("while", ignore(case))]
    While,
    #[token("do", ignore(case))]
    Do,
    #[token("for", ignore(case))]
    For,
    #[token("to", ignore(case))]
    To,
    #[token("downto", ignore(case))]
    Downto,
    #[token("repeat", ignore(case))]
    Repeat,
    #[token("until", ignore(case))]
    Until,
    #[token("case", ignore(case))]
    Case,
    #[token("of", ignore(case))]
    Of,
    #[token("goto", ignore(case))]
    Goto,
    #[token("array", ignore(case))]
    Array,
    #[token("record", ignore(case))]
    Record,
    #[token("set", ignore(case))]
    Set,
    #[token("in", ignore(case))]
    In,
    #[token("file", ignore(case))]
    File,
    #[token("integer", ignore(case))]
    Integer,
    #[token("real", ignore(case))]
    Real,
    #[token("boolean", ignore(case))]
    Boolean,
    #[token("string", ignore(case))]
    String,
    #[token("char", ignore(case))]
    Char,
    #[token("not", ignore(case))]
    Not,
    #[token("and", ignore(case))]
    And,
    #[token("or", ignore(case))]
    Or,
    #[token("div", ignore(case))]
    Div,
    #[token("mod", ignore(case))]
    Mod,
    #[token("write", ignore(case))]
    Write,
    #[token("writeln", ignore(case))]
    Writeln,
    #[token("read", ignore(case))]
    Read,
    #[token("readln", ignore(case))]
    Readln,
    #[token("Chr", ignore(case))]
    Chr,
    #[token("nil", ignore(case))]
    Nil,
    #[token("with", ignore(case))]
    With,
    #[token("forward", ignore(case))]
    Forward,
    #[token("packed", ignore(case))]
    Packed,
    #[token("unit", ignore(case))]
    Unit,
    #[token("interface", ignore(case))]
    Interface,
    #[token("implementation", ignore(case))]
    Implementation,
    #[token("uses", ignore(case))]
    Uses,
    #[token("initialization", ignore(case))]
    Initialization,

    // Symbols
    #[token("+")]
    Plus,
    #[token("-")]
    Minus,
    #[token("/")]
    Slash,
    #[token("*")]
    Star,
    #[token("(")]
    LParen,
    #[token(")")]
    RParen,
    #[token("{")]
    LBrace,
    #[token("}")]
    RBrace,
    #[token("[")]
    LBracket,
    #[token("]")]
    RBracket,
    #[token(">=")]
    Gte,
    #[token("<=")]
    Lte,
    #[token(">")]
    Gt,
    #[token("<")]
    Lt,
    #[token("=")]
    Eq,
    #[token("<>")]
    Neq,
    #[token(":=")]
    Assign,
    #[token(",")]
    Comma,
    #[token(":")]
    Colon,
    #[token(";")]
    Semicolon,
    #[token("..")]
    DotDot,
    #[token(".")]
    Dot,
    #[token("^")]
    Caret,

    // Literals
    #[regex(r"(?i)false|true", |lex| lex.slice().to_lowercase() == "true")]
    BooleanLiteral(bool),

    #[regex(r"'.'", |lex| lex.slice().chars().nth(1).unwrap(), priority = 10)]
    CharLiteral(char),

    #[regex(r"\$[0-9a-fA-F]+", |lex| i64::from_str_radix(&lex.slice()[1..], 16).unwrap())]
    #[regex(r"[0-9]+", |lex| lex.slice().parse::<i64>().unwrap())]
    IntegerLiteral(i64),

    #[regex(r"#[0-9]+", |lex| lex.slice()[1..].parse::<i64>().unwrap() as u8 as char)]
    CharCode(char),

    #[regex(r"[0-9]+(\.[0-9]+([eE][+-]?[0-9]+)?|[eE][+-]?[0-9]+)", |lex| lex.slice().parse::<f64>().unwrap())]
    RealLiteral(f64),

    #[regex(r"[a-zA-Z_][a-zA-Z0-9_]*", |lex| lex.slice().to_string(), priority = 1)]
    Identifier(String),

    #[regex(r"'([^']|'')*'", |lex| {
        let s = lex.slice();
        // Remove surrounding quotes and replace '' with '
        s[1..s.len()-1].replace("''", "'")
    })]
    StringLiteral(String),

    // Error
    Error,
}

pub type Spanned<Tok, Loc, Error> = Result<(Loc, Tok, Loc), Error>;

pub struct Lexer<'input> {
    lexer: logos::Lexer<'input, Token>,
}

impl<'input> Lexer<'input> {
    pub fn new(input: &'input str) -> Self {
        Self {
            lexer: Token::lexer(input),
        }
    }
}

impl<'input> Iterator for Lexer<'input> {
    type Item = Spanned<Token, usize, String>;

    fn next(&mut self) -> Option<Self::Item> {
        let token = self.lexer.next()?;
        let span = self.lexer.span();
        match token {
            Ok(Token::Error) => Some(Err(format!("Lexer error at {:?}", span))),
            Ok(t) => Some(Ok((span.start, t, span.end))),
            Err(_) => Some(Err(format!("Lexer error at {:?}", span))),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_keywords() {
        let mut lex = Token::lexer("program var uses BEGIN end");
        assert_eq!(lex.next(), Some(Ok(Token::Program)));
        assert_eq!(lex.next(), Some(Ok(Token::Var)));
        assert_eq!(lex.next(), Some(Ok(Token::Uses)));
        assert_eq!(lex.next(), Some(Ok(Token::Begin)));
        assert_eq!(lex.next(), Some(Ok(Token::End)));
    }

    #[test]
    fn test_literals() {
        let mut lex = Token::lexer("123 $FF 45.67 'a' '#' #65 'string with ''quote''' true");
        assert_eq!(lex.next(), Some(Ok(Token::IntegerLiteral(123))));
        assert_eq!(lex.next(), Some(Ok(Token::IntegerLiteral(255))));
        assert_eq!(lex.next(), Some(Ok(Token::RealLiteral(45.67))));
        assert_eq!(lex.next(), Some(Ok(Token::CharLiteral('a'))));
        assert_eq!(lex.next(), Some(Ok(Token::CharLiteral('#'))));
        assert_eq!(lex.next(), Some(Ok(Token::CharCode('A'))));
        assert_eq!(lex.next(), Some(Ok(Token::StringLiteral("string with 'quote'".to_string()))));
        assert_eq!(lex.next(), Some(Ok(Token::BooleanLiteral(true))));
    }
}
