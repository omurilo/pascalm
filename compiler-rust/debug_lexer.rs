use logos::Logos;

#[derive(Logos, Debug, PartialEq, Clone)]
#[logos(skip r"[ \t\r\n\f]+")]
pub enum Token {
    #[token("program", ignore(case))]
    Program,
    #[token("uses", ignore(case))]
    Uses,
    #[regex(r"[a-zA-Z_][a-zA-Z0-9_]*", |lex| lex.slice().to_string())]
    Identifier(String),
    #[token(";")]
    Semicolon,
}

fn main() {
    let input = "program test; uses math;";
    let mut lex = Token::lexer(input);
    while let Some(token) = lex.next() {
        println!("{:?} at {:?}", token, lex.span());
    }
}
