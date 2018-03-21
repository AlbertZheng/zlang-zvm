options {
	language = "Sather";
}

class CALC_PARSER extends Parser;
options {
	buildAST = true;	// uses CommonAST by default
}
expr
	:	mexpr (PLUS^ mexpr)* SEMI!
	;

mexpr
	:	atom (STAR^ atom)*
	;

atom:	INT
	;

class CALC_LEXER extends Lexer;

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

STAR:	'*'
	;

PLUS:	'+'
	;

SEMI:	';'
	;

protected
DIGIT
	:	'0'..'9'
	;

INT	:	(DIGIT)+
	;

class CALC_TREE_WALKER extends TreeParser;

expr returns [ r : FLT ]
{
	a , b : FLT;
	r := 0.0;
}
	:	#(PLUS a=expr b=expr)	{r := a+b;}
	|	#(STAR a=expr b=expr)	{r := a*b;}
	|	i:INT			{r := #FLT( i.text );}
	;

