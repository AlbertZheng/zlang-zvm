options {
	language = "Sather";
}

/* This example demonstrates the heterogeneous tree construction
 *  mechanism.  Compare this example to examples/calc/calc.g
 *  to see that I use tree node methods not a tree walker to compute
 *  the result.
 */
class CALC_PARSER extends Parser;
options {
	buildAST = true;	// uses CommonAST by default
}

// define a bunch of specific AST nodes to build.
// can override at actual reference of tokens in grammar
// below.
tokens {
	PLUS<AST=PLUS_NODE>;
	STAR<AST=MULT_NODE>;
}

expr
	:	mexpr (PLUS^ mexpr)* SEMI!
	;

mexpr
	:	atom (STAR^ atom)*
	;

atom:	INT<AST=INT_NODE>	// could have done in tokens{} section
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
