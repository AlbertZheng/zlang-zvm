options {
	language = "Sather";
}

class LANG_PARSER extends Parser;

options {
	buildAST=true;
}

tokens {
	BLOCK; // imaginary token
}

block
	:	LCURLY! ( statement )* RCURLY!
		// add imaginary BLOCK node on top of statement list
		{@block := @([BLOCK, "BLOCK"], @block);}
	;

statement
	:	ID ASSIGN^ expr SEMI!
	|	"if"^ LPAREN! expr RPAREN! statement
		( "else"! statement )?
	|	"while"^ LPAREN! expr RPAREN! statement
	|!	b:block { statement_ast := @b; }
		// do some manual tree returning
	;

// add an EXPR node on top of an expression
// note that the two alternatives behave exactly
// the same way.
expr:!	id:ID		{@expr := @([EXPR,"EXPR"],@id);}
	|	INT			{@expr := @([EXPR,"EXPR"],@expr);}
	;

class LANG_WALKER extends TreeParser;

block	:	#( BLOCK ( stat )+ )
	;

stat:	#("if" expr stat (stat)?)
	|	#("while" expr stat)
	|	expr
	|	block
	|	#( ASSIGN ID expr )
	;

expr:	#(	EXPR
			(	a:ID	{ OUT::create + "found ID " + a.text + "\n";}
			|	b:INT	{ OUT::create + "found INT " + b.text + "\n";}
			)
		 )
	;

class LANG_LEXER extends Lexer;

WS	:	(' '
	|	'\t'
	|	'\n'
	|	'\r')
		{ sa_ttype := ANTLR_COMMON_TOKEN::SKIP; }
	;

LPAREN:	'('
	;

RPAREN:	')'
	;

LCURLY:	'{'
	;

RCURLY:	'}'
	;

ASSIGN
	:	'='
	;

SEMI:	';'
	;

protected
DIGIT
	:	'0'..'9'
	;

INT	:	(DIGIT)+
	;

ID
options {
	testLiterals = true;
}
	:	('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'_'|DIGIT)*
	;
