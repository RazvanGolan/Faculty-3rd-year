# AtomC - Lexical Rules

## Identifiers

**ID:** `[a-zA-Z_] [a-zA-Z0-9_]*`

## Keywords

**TYPE_CHAR:** `'char'`  
**TYPE_DOUBLE:** `'double'`  
**ELSE:** `'else'`  
**IF:** `'if'`  
**TYPE_INT:** `'int'`  
**RETURN:** `'return'`  
**STRUCT:** `'struct'`  
**VOID:** `'void'`  
**WHILE:** `'while'`

## Constants

**INT:** `[0-9]+`

**DOUBLE:** `[0-9]+ ( '.' [0-9]+ ( [eE] [+-]? [0-9]+ )? | ( '.' [0-9]+ )? [eE] [+-]? [0-9]+ )`

**CHAR:** `['] [^'] [']`

**STRING:** `["] [^"]* ["]`

## Delimiters

**COMMA:** `','`  
**SEMICOLON:** `';'`  
**LPAR:** `'('`  
**RPAR:** `')'`  
**LBRACKET:** `'['`  
**RBRACKET:** `']'`  
**LACC:** `'{'`  
**RACC:** `'}'`  
**END:** `'\0' | EOF`  *(where `'\0'` is the string terminator and `EOF` is the C code for End Of File)*

## Operators

**ADD:** `'+'`  
**SUB:** `'-'`  
**MUL:** `'*'`  
**DIV:** `'/'`  
**DOT:** `'.'`  
**AND:** `'&&'`  
**OR:** `'||'`  
**NOT:** `'!'`  
**ASSIGN:** `'='`  
**EQUAL:** `'=='`  
**NOTEQ:** `'!='`  
**LESS:** `'<'`  
**LESSEQ:** `'<='`  
**GREATER:** `'>'`  
**GREATEREQ:** `'>='`

## Whitespace - These do not form lexical atoms

**SPACE:** `[ \n\r\t]` *(includes space, newline, carriage return, and tab characters)*  
**LINECOMMENT:** `'//' [^\n\r\0]*` *(single-line comments starting with `//`)*  
