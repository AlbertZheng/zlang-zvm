options {
	language="Cpp";
}

{
#include <iostream>
}

class LangParser extends Parser;

options {
	codeGenMakeSwitchThreshold = 3;
	codeGenBitsetTestThreshold = 4;
	buildAST=true;
}

block
	:	LCURLY^ ( statement )* RCURLY!
	;

statement
	:	expr SEMI!
	|	"if"^ LPAREN! expr RPAREN! statement
		( "else"! statement )?
	|	"while"^ LPAREN! expr RPAREN! statement
	|!	b:block { statement_AST = b_AST; }
		// do some manual tree returning
	;

expr:	assignExpr
	;

assignExpr
	:	aexpr (ASSIGN^ assignExpr)?
	;

aexpr
	:	mexpr (PLUS^ mexpr)*
	;

mexpr
	:	atom (STAR^ atom)*
	;

atom:	ID
	|	INT
	;

{
#include <iostream>
}

class LangWalker extends TreeParser;

block
	:	#( LCURLY ( stat )+ )
	;

stat:	#("if" expr stat (stat)?)
	|	#("while" expr stat)
	|	expr
	|	block
	;

expr:	#(ASSIGN expr expr)		{std::cout << "found assign" << std::endl;}
	|	#(PLUS expr expr)		{std::cout << "found +" << std::endl;}
	|	#(STAR expr expr)		{std::cout << "found *" << std::endl;}
	|	a:ID					{std::cout << "found ID " << a->getText() << std::endl;}
	|	b:INT					{std::cout << "found INT " << b->getText() << std::endl;}
	;

class LangLexer extends Lexer;

WS_	:	(' '
	|	'\t'
	|	'\n'
	|	'\r')
		{ _ttype = ANTLR_USE_NAMESPACE(antlr)Token::SKIP; }
	;

LPAREN:	'('
	;

RPAREN:	')'
	;

LCURLY:	'{'
	;

RCURLY:	'}'
	;

STAR:	'*'
	;

PLUS:	'+'
	;

ASSIGN
	:	'='
	;

SEMI:	';'
	;

COMMA
	:	','
	;

protected
ESC	:	'\\'
		(	'n'
		|	'r'
		|	't'
		|	'b'
		|	'f'
		|	'"'
		|	'\''
		|	'\\'
		|	('0'..'3') ( DIGIT (DIGIT)? )?
		|	('4'..'7') (DIGIT)?
		)
	;

protected
DIGIT
	:	'0'..'9'
	;

INT	:	(DIGIT)+
	;

ID
options {
	testLiterals=true;
}
	:	('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'_'|'0'..'9')*
	;
