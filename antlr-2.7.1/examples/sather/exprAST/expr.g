options {
	language = "Sather";
}

class EXPR_PARSER extends Parser;

options {
	codeGenMakeSwitchThreshold = 3;
	codeGenBitsetTestThreshold = 4;
	buildAST=true;
}

expr
     : assignExpr EOF! ;

assignExpr
	:	addExpr
		(
			ASSIGN^
			assignExpr 
		)?
	;

addExpr
	:	multExpr 
		(
			pm:PLUS_MINUS^
			me:multExpr
			exception 
				catch [ $ANTLR_RECOGNITION_EXCEPTION dummy_not_needed_in_sather ] 
				{ 
					report_error("Caught error in addExpr");
					report_error(exception.str); 
				}
		)*
	;

multExpr
	:	postfixExpr
		(
			MULT_DIV^
			postfixExpr
		)*
	;

postfixExpr
	:	(id:ID LPAREN)=>
		// Matches function call syntax like "id(arg,arg)" 
		id2:ID^
		(
         parenArgs
		)?
	|	atom
	;

parenArgs
	:	
      LPAREN!
      (
         assignExpr
         (
            COMMA!
	        assignExpr
         )*
      )?
      RPAREN!
	;

atom
	:	ID
	|	INT
	|	CHAR_LITERAL 
	|	STRING_LITERAL
	|	LPAREN! assignExpr RPAREN!
	;

class EXPR_LEXER extends Lexer;

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

PLUS_MINUS:	'+' | '-'
	;

MULT_DIV : '*' | '/'
   ;

ASSIGN :	'='
	;

COMMA : ','
   ;
   
CHAR_LITERAL
	:	'\'' (ESC|~'\'') '\''
	;

STRING_LITERAL
	:	'"' (ESC|~'"')* '"'
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
		|	('0'..'3')
			(
				options {
					warnWhenFollowAmbig = false;
				}
			:	('0'..'9')
				(	
					options {
						warnWhenFollowAmbig = false;
					}
				:	'0'..'9'
				)?
			)?
		|	('4'..'7')
			(
				options {
					warnWhenFollowAmbig = false;
				}
			:	('0'..'9')
			)?
		)
	;

protected
DIGIT
	:	'0'..'9'
	;

INT 
	: (DIGIT)+
	;

ID
options {
	testLiterals = true;
}
	:	('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'_'|'0'..'9')*
	;

