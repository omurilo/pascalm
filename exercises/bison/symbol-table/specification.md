Do a INTERPRETER to previous if-calculator language, but using VARIABLES and a symbol table, make a "Semantic Analysis".

<program> -> <declarations> <commands>

<declarations> -> <declaration>; | <declarations> <declaration>;

<declaration> -> int <ID> | float <ID> | boolean <ID> | char <ID>

<commands> -> <command> | <commands> <command>

<command> -> <if_command> | <attribs> | <read_command>; | <write_command>;

<read_command> -> read(<ID>)

<write_command> -> write(<ID>) | write(<NUM>) | write(<STRING>) | write(<CHAR>)

<attribs> -> <attrib>; | <attribs> <attrib>;

<if_command> -> if (<logical_expr>) then { <attrib> }
              | if (<logical_expr>) then { <attrib> } else { <attrib> }

<logical_expr> -> op1 <cmp_op> op2 
                | (<logical_expr> OR <logical_expr>) 
                | (<logical_expr> AND <logical_expr>) 
                | (NOT <logical_expr>) 
                | <ID>

<attrib> -> <variable> <attrib_op> <arithmetic_expr>

<cmp_op> -> < | > | <= | >= | !=

<arithmetic_expr> -> any infix expression with numbers or variables, using operators *, /, +, and -

<ID> -> any sequence of characters beginning with a letter (uppercase or lowercase).

Limit the length of an ID to 10 characters/digits, and allow only up to 100 variables to be declared.

Accept underscore "_" as a valid character.
Do not accept accents, "ç", or any other special characters except letters and digits.

Accept negative numbers with a unary `-` sign.

Evaluate semantic operations: boolean variables only accept values resulting from
<logical_expr> operations. Integer or float variables can receive expressions with numbers
(performing conversions when necessary).

USING REFERENCES AT: [Flex Examples](https://github.com/westes/flex/blob/master/examples/manual/pascal.lex)
