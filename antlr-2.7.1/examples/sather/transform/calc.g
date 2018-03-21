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
options {
	buildAST = true;
	// ASTLabelType = "antlr.CommonAST";
}

expr:!	#(PLUS left:expr right:expr)
		{
			if ( @right.ttype = INT and 
				 #INT(@right.text) = 0 ) then
                                -- x+0
				@expr := @left;
			elsif ( @left.ttype = INT and
				  #INT(@left.text) = 0 ) then
                                -- 0+x
				@expr := @right;
			else -- x+y
				@expr := @(PLUS, left, right);
			end;
		}
	|	#(STAR expr expr)
	|	i:INT
	;
