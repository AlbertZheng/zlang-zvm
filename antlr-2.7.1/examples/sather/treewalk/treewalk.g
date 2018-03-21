options {
	language = "Sather";
}

class LANG_PARSER extends Parser;

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
	|!	b:block { statement_ast := b_ast; }
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

class LANG_WALKER extends TreeParser;
{
   println( s : STR ) is 
     OUT::create + s + "\n";
   end;
}

block
	:	#( LCURLY ( stat )+ )
	;

stat:	#("if" expr stat (stat)?)
	|	#("while" expr stat)
	|	expr
	|	block
	;

expr:	#(ASSIGN expr expr)		{ println("found assign");}
	|	#(PLUS expr expr)		{println("found +");}
	|	#(STAR expr expr)		{println("found *");}
	|	a:ID					{println("found ID " + a.text );}
	|	b:INT					{println("found INT " + b.text);}
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

ID	:	('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'_'|'0'..'9')*
		{
                        if ( literals.has_ind( text ) ) then
				sa_ttype := literals[ text ];
			end;
		}
	;
