/*
 *  Sather 1.2 Grammar
 *
 *  Version 0.1  Mika Illouz   mika@sdna2.ucsd.edu  
 *    Beware: full of mistakes, but its a start.  I'm particularly unsure
 *    about expression precendence, external class definition, and 
 *    closure create expression.  I started tagging various rules with
 *    imaginary tokens, but that job is far from over if the output of the
 *    parser is ever to be handed off to a tree walker.
 *
 *  This grammar is in the PUBLIC DOMAIN.
 */

options {
	language = "Sather";
}

class SATHER_PARSER extends Parser;
options {
	exportVocab=SATHER;                // Call its vocabulary "SATHER"
	codeGenMakeSwitchThreshold = 2;    // Some optimizations
	codeGenBitsetTestThreshold = 3;
	buildAST = true;
}

tokens {
        ABSTRACT_SIGNATURE_LIST;
        TYPE_SPECIFIER_LIST;

	PARAMETER_DECLARATION;
	SUBTYPING_CLAUSE;
	SUPERTYPING_CLAUSE;

	ROUTINE_CLOSURE_TYPE_SPECIFIER;
	ITER_CLOSURE_TYPE_SPECIFIER;
	RETURN_TYPE_SPECIFIER;

	AGET;
	CLOSURE_AGET;

	CALL_ARGUMENT;
	CLOSURE_ARGUMENT;

	CLOSURE_CALL;
	ARRAY_LITERAL;

	DECLARATION_STATEMENT;

	ABSTRACT_ROUTINE_SIGNATURE;
	ROUTINE_ARGUMENT;
	ROUTINE_DEFINITION;
	ITER_DEFINITION;
}

parse
	: class_definition_list
        ;


class_definition_list
	: ( class_definition ( SEMICOLON! ( class_definition )? )* )?
	;

class_definition
	: abstract_class_definition 
	| concrete_class_definition
	| external_class_definition
	;

abstract_class_definition
	: "abstract"^ 
          "class"! 
          ABSTRACT_CLASS_NAME
	  ( LCURLY! parameter_declaration_list RCURLY! )?
	  ( subtyping_clause )?
          ( supertyping_clause )?
          "is"!
	  ( abstract_signature_list )?
          "end"!
	;

concrete_class_definition
	: ( "immutable" | "partial" )?
	  "class"^
	  IDENTIFIER
	  ( LCURLY! parameter_declaration_list RCURLY! )?
	  ( subtyping_clause )?
          "is"!
	  ( class_element_list )?
	  "end"!
	;
 	  
external_class_definition
	: "external"^ ( IDENTIFIER )? 
          "class"! 
          IDENTIFIER
	  ( LCURLY! parameter_declaration_list RCURLY! )?
	  ( subtyping_clause )?
          "is"!
	  ( external_class_element_list )?
	  "end"!
	;

class_element_list
	: class_element ( SEMICOLON! ( class_element )? )*
	;


class_element
	: p:"private"! 
	  ( unmodified_definition
          | "stub" abstract_signature // typo on page 34 of spec?
          )
          {  @class_element.add_child( @[@p.ttype,@p.text] );
          }
	| "stub" abstract_signature // typo on page 34 of spec?
	| r:"readonly"! 
          ( shared_definition | attr_definition )
          {  @class_element.add_child( @[@r.ttype,@r.text] );
          }
	| unmodified_definition
	;

unmodified_definition
	: const_definition 
	| shared_definition
	| attr_definition
	| routine_definition
	| iter_definition
	| include_clause
	;

const_definition
	: "const"^ 
	  IDENTIFIER
	  ( ( COLON! type_specifier ASSIGN! expression )
          | ( ( ASSIGN! expression )? ( COMMA! identifier_list )? )
          )
	;

shared_definition
	: "shared"^
	  ( IDENTIFIER 
            ( COLON! type_specifier ( ASSIGN! expression )?
            | ( COMMA! IDENTIFIER )+ COLON! type_specifier 
            )
          )
	;

attr_definition
	: "attr"^ identifier_list COLON! t:type_specifier 
	;

routine_definition
	: abstract_routine_signature
	  ( "pre"^ expression )?
	  ( "post"^ expression )?
	  "is"! ( statement_list | builtin_statement ) "end"!  // not optional: typo on page 31 of spec?
          { @routine_definition :=
              @([ROUTINE_DEFINITION,"ROUTINE_DEFINITION"], @routine_definition );
          }
	;

iter_definition
	: abstract_iter_signature
	  ( "pre"^ expression )?
	  ( "post"^ expression )?
	  "is"! ( statement_list | builtin_statement ) "end"!
          { @iter_definition :=
              @([ITER_DEFINITION,"ITER_DEFINITION"], @iter_definition );
          }
	;

include_clause
	: "include"^ type_specifier ( feature_modifier_list )?
	;

feature_modifier_list
	: feature_modifier ( COMMA! feature_modifier )*
	;

feature_modifier
	: IDENTIFIER^ RIGHT_ARROW! ( ( "private" | "readonly" )? IDENTIFIER )?
	| ITER_NAME^  RIGHT_ARROW! ( ( "private" | "readonly" )? ITER_NAME  )?
	;

statement_list
	: ( statement )? ( SEMICOLON! ( statement )? )* 
	;

external_class_element
	: p:"private"! unmodified_definition
          {  @external_class_element.add_child( @[@p.ttype,@p.text] );
          }
	| r:"readonly"! ( shared_definition | attr_definition )
          {  @external_class_element.add_child( @[@r.ttype,@r.text] );
          }

	| const_definition 
	| shared_definition
	| attr_definition
	| include_clause

	| abstract_routine_signature
	| abstract_iter_signature
	
        ;

external_class_element_list
	: external_class_element ( SEMICOLON! ( external_class_element )? )*
        ;

builtin_statement
	: "builtin" IDENTIFIER ( SEMICOLON! )?
	;

statement
	: declaration_or_expression_statement
	| if_statement
	| return_statement
	| case_statement
	| typecase_statement
	| loop_statement
	| yield_statement
	| quit_statement
	| protect_statement
	| raise_statement
	| assert_statement
	;

declaration_or_expression_statement
	: ( IDENTIFIER ( COLON | COMMA | DBL_COLON_ASSIGN ) )=> declaration_statement
	| expression
	;

declaration_statement
        : IDENTIFIER 
          ( COLON! type_specifier ( ASSIGN! expression )? 
          | DBL_COLON_ASSIGN! expression
          | ( COMMA! IDENTIFIER )+ COLON! type_specifier 
          )
          { @declaration_statement :=
              @([DECLARATION_STATEMENT, "DECLARATION_STATEMENT"], @declaration_statement );
          }
	;

assert_statement
	: "assert" expression
	;

if_statement
	: "if" expression "then" statement_list 
	  ( "elsif" expression "then" statement_list )*  
	  ( "else" statement_list )?
          "end"
	;

return_statement
	: "return" ( expression )?
	;

case_statement
	: "case" expression 
	  ( "when" expression ( COMMA! expression )* "then" statement_list )+
	  ( "else" statement_list )?
	  "end"
	;

typecase_statement
	: "typecase" IDENTIFIER
	  ( "when" type_specifier "then" statement_list )+
	  ( "else" statement_list )?
	  "end"
	;

loop_statement
	: "loop" statement_list "end"
	;

yield_statement
	: "yield" ( expression )?
	;

quit_statement
	: "quit" 
	;

protect_statement
	: "protect" statement_list
	  ( "when" type_specifier "then" statement_list )*
	  ( "else" statement_list )?
	  "end"
	;

raise_statement
	: "raise" expression
	;

// going out on a limb, here.
closure_create_expression
	: "bind"^
	  LPAREN!
	  closure_class_call_expression
 	  RPAREN!
	;

expression_list
	: expression ( COMMA! expression )*
	;

// expressions
// Note that most of these expressions follow the pattern
//   this_level_expression :
//       next_higher_precedence_expression
//           (OPERATOR next_higher_precedence_expression)*
// which is a standard recursive definition for a parsing an expression.

expression
	: assignment_expression
	;

assignment_expression
	: logical_expression ( ASSIGN logical_expression )?
	;

logical_expression
	: relational_expression ( ( "and"^ | "or"^ ) relational_expression )*
	;

relational_expression
	: add_sub_expression
	  ( 
	    ( LESS_THAN^ 
            | LESS_THAN_EQUAL^ 
	    | EQUAL^ 
	    | NOT_EQUAL^ 
	    | GREATER_THAN_EQUAL^ 
	    | GREATER_THAN^
            )
	    add_sub_expression
	  )*
	;

add_sub_expression
	: mult_div_mod_expression ( ( PLUS^ | MINUS^ ) mult_div_mod_expression )*
	;

mult_div_mod_expression
	: unary_expression ( ( STAR^ | SLASH^ | PERCENT^ ) unary_expression )*
	;

unary_expression
	: ( NOT^ | MINUS^ )? raise_expression
	;

raise_expression
	: class_call_expression ( CARET^ class_call_expression )*
	;

class_call_expression
	: ( type_specifier DBL_COLON )=>
            type_specifier DBL_COLON^ deref_expression 
	| deref_expression
	;

deref_expression
	: call_expression ( DOT^ call_expression )*
	;

call_expression
	: primary_expression 
	  ( LPAREN! call_argument_list RPAREN! ( aget_expression )*
	  | ( aget_expression )+
	  )?
	| "new"^ ( LPAREN! expression RPAREN! )?
	| "void"^ ( LPAREN! expression RPAREN! )?
	| HASH^ ( type_specifier )? ( LPAREN! call_argument_list RPAREN! )?
	| aget_expression
	;

aget_expression
	: LSQUARE! expression_list RSQUARE! // aget() does not accept modes, right?
          { @aget_expression := @([AGET, "AGET"], @aget_expression ); }
	;

call_argument_list
	: call_argument ( COMMA! call_argument )*
	;

call_argument
	: ( ( iter_mode )? expression )
          { @call_argument := @([CALL_ARGUMENT, "CALL_ARGUMENT"], @call_argument ); }
	;

primary_expression
	: LPAREN! expression RPAREN!
	| IDENTIFIER
	| ITER_NAME
	| bool_literal_expression
	| CHAR_LITERAL
	| ( STRING_LITERAL )+
	| INT_LITERAL
	| FLT_LITERAL
	| array_expression
	| self_expression
	| result_expression
	| while_expression
	| until_expression
	| break_expression
	| except_expression
	| initial_expression
	| closure_create_expression
	;

// variants for use in closure definitions, where we augment the 
// notion of expression to include an UNDERSCORE.  Used only in
// closure_create_expression
closure_class_call_expression
	: ( type_specifier DBL_COLON )=>
            type_specifier DBL_COLON! closure_deref_expression 
	| closure_deref_expression
	;

closure_deref_expression
	: closure_call_expression ( DOT! closure_call_expression )?
	;

closure_call_expression
	: ( primary_expression | UNDERSCORE )
	  ( LPAREN! closure_argument_list RPAREN! ( closure_aget_expression )*
	  | ( closure_aget_expression )+
	  )?
          { @closure_call_expression := 
              @([CLOSURE_CALL, "CLOSURE_CALL"], @closure_call_expression ); 
          }
	| closure_aget_expression
          { @closure_call_expression := 
              @([CLOSURE_CALL, "CLOSURE_CALL"], @closure_call_expression ); 
          }
	;

closure_aget_expression
	: LSQUARE! closure_expression_list RSQUARE!
          { @closure_aget_expression := 
              @([CLOSURE_AGET, "CLOSURE_AGET"], @closure_aget_expression ); 
          }
	; 

closure_argument
	: ( ( iter_mode )? closure_expression )
          { @closure_argument := 
              @( [CLOSURE_ARGUMENT,"CLOSURE_ARGUMENT"] , @closure_argument ); 
          }
        ;

closure_argument_list
	: closure_argument ( COMMA! closure_argument )*
	;

closure_expression_list
	: closure_expression ( COMMA! closure_expression )*
	;

closure_expression
	: expression
	| UNDERSCORE
	;

except_expression
	: "exception"
	;

initial_expression
	: "initial"^ LPAREN! expression RPAREN!
	;

result_expression
	: "result"
	;

self_expression
	: "self"
	;

while_expression
	: "while!"^ LPAREN! expression RPAREN!
	;

until_expression
	: "until!"^ LPAREN! expression RPAREN!
	;

break_expression
	: "break!"
	;

array_expression 
	: BAR! expression_list BAR!
          { @array_expression :=
              @([ARRAY_LITERAL, "ARRAY_LITERAL"], @array_expression );
          }
	;

bool_literal_expression
	: "true" 
	| "false"
	;

parameter_declaration_list
	: parameter_declaration ( COMMA! parameter_declaration )*
	;

parameter_declaration
	: IDENTIFIER ( LESS_THAN! type_specifier )?
          { @parameter_declaration := 
              @([PARAMETER_DECLARATION, "PARAMETER_DECLARATION"], 
                @parameter_declaration ); 
          }
        ;

supertyping_clause
	: GREATER_THAN^ type_specifier_list
        ;

subtyping_clause
	: LESS_THAN^ type_specifier_list
        ;

abstract_signature_list
	: abstract_signature ( SEMICOLON! ( abstract_signature )? )*
          { @abstract_signature_list :=
              @([ABSTRACT_SIGNATURE_LIST, "ABSTRACT_SIGNATURE_LIST"],
                @abstract_signature_list);
          }
        ;

abstract_signature
	: abstract_routine_signature
	| abstract_iter_signature
	;

abstract_routine_signature
	: IDENTIFIER
	  ( LPAREN! routine_argument_list RPAREN! )?
	  ( COLON! type_specifier )?
          { @abstract_routine_signature :=
              @([ABSTRACT_ROUTINE_SIGNATURE, "ABSTRACT_ROUTINE_SIGNATURE"],
                @abstract_routine_signature);
          }
        ;

abstract_iter_signature
	: ITER_NAME^
	  ( LPAREN! iter_argument_list RPAREN! )?
	  ( COLON type_specifier )?
	;

routine_argument_list
	: routine_argument ( COMMA! routine_argument )*
	;

routine_argument
	: ( routine_mode )? IDENTIFIER^  // #(IDENTIFIER (routine_mode)? )
          ( COMMA! ( routine_mode )? IDENTIFIER^ )*
          COLON type_specifier
          { @routine_argument :=
              @([ROUTINE_ARGUMENT, "ROUTINE_ARGUMENT"], @routine_argument);
          }
	;

iter_argument_list
	: iter_argument ( COMMA! iter_argument )*
	;

iter_argument
	: ( iter_mode )? IDENTIFIER^ 
          ( COMMA! ( iter_mode )? IDENTIFIER^ )*
          COLON type_specifier
	;

/*
non_identifier_type_specifier
        : ABSTRACT_CLASS_NAME ( LCURLY! type_specifier_list RCURLY! )? 
	| method_closure_type_specifier
        | "SAME"
	;
*/

type_specifier
	: IDENTIFIER ( LCURLY! type_specifier_list RCURLY! )? 
        | ABSTRACT_CLASS_NAME ( LCURLY! type_specifier_list RCURLY! )? 
	| method_closure_type_specifier
        | "SAME"
	;

type_specifier_list
	: type_specifier ( COMMA! type_specifier )*
          { @type_specifier_list :=
              @([TYPE_SPECIFIER_LIST,"TYPE_SPECIFIER_LIST"], 
                @type_specifier_list);
          }
        ;

method_closure_type_specifier
	: routine_closure_type_specifier
	| iter_closure_type_specifier
	;

routine_closure_type_specifier
	: "ROUT" 
          ( LCURLY! routine_type_specifier_list RCURLY! )?
          ( COLON type_specifier )?
        ;


iter_closure_type_specifier
	: "ITER" 
          ( LCURLY! iter_type_specifier_list RCURLY! )?
          ( COLON type_specifier )?
        ;

iter_type_specifier_list
	: iter_type_specifier ( COMMA! iter_type_specifier )*
	;

routine_type_specifier_list
	: routine_type_specifier ( COMMA! routine_type_specifier )*
	;

routine_type_specifier
	: ( routine_mode )? type_specifier
	;

iter_type_specifier
	: ( iter_mode )? type_specifier
	;

routine_mode
	: "in" | "out" | "inout"
	;

iter_mode
	: routine_mode 
        | "once"
	;

identifier_list
	: IDENTIFIER ( COMMA! IDENTIFIER )*
	;

class SATHER_LEXER extends Lexer;

options {
	exportVocab = SATHER;
        testLiterals = true;
	k=2;
}

// operators, etc.
LCURLY             : '{'  ;
RCURLY             : '}'  ;
LPAREN             : '('  ;
RPAREN             : ')'  ;
LSQUARE            : '['  ;
RSQUARE            : ']'  ;
COMMA              : ','  ;
COLON              : ':'  ;
SEMICOLON          : ';'  ;
LESS_THAN          : '<'  ;
GREATER_THAN       : '>'  ;
EXCLAMATION        : '!'  ;
MINUS              : '-'  ;
PLUS               : '+'  ;
STAR               : '*'  ;
SLASH              : '/'  ;
EQUAL              : '='  ;
NOT                : '~'  ;
DOT                : '.'  ;
HASH               : '#'  ;
BAR                : '|'  ;
PERCENT            : '%'  ;
CARET              : '^'  ;
ASSIGN             : ":=" ; 
RIGHT_ARROW        : "->" ;
NOT_EQUAL          : "/=" ;
LESS_THAN_EQUAL    : "<=" ;
GREATER_THAN_EQUAL : ">=" ;

protected DBL_COLON        : "::"  ;
protected DBL_COLON_ASSIGN : "::=" ;

protected UNDERSCORE : '_' ;
protected DOLLAR     : '$' ;

protected
IDENTIFIER
	: ( 'a'..'z' | 'A'..'Z' | '_' ) ( 'a'..'z' | 'A'..'Z' | '0'..'9' | '_' )*
        ; // TODO: reject IDENTIFIERS without at least one letter

protected
ITER_NAME
	: IDENTIFIER EXCLAMATION
        ; 

protected
BINARY_INT
	: "0b" ( '0' | '1' | '_' )*
	;

protected
OCTAL_INT
	: "0o" ( '0'..'9' | '_' )*
	;

protected
HEX_INT
	: "0x" ( '0'..'9' | 'a'..'f' | '_' )*
	;

protected
DECIMAL_INT
	: ( '0'..'9' ) ( '0'..'9' | '_' )* 
	;

protected
INT_LITERAL
	: ( DECIMAL_INT | BINARY_INT | OCTAL_INT | HEX_INT ) ( 'i' )?
	;

protected
FLT_LITERAL
	: DECIMAL_INT DOT DECIMAL_INT ( 'e' ( MINUS )? DECIMAL_INT )? ( 'd' )?
	;
 
COLON_OR_ASSIGN
	: "::" { %setType(DBL_COLON); } 
          ( '=' { %setType(DBL_COLON_ASSIGN); } )?
	;

NUM_LITERAL
	: ( DECIMAL_INT DOT DECIMAL_INT )=>
          FLT_LITERAL  { %setType(FLT_LITERAL); }
          | DECIMAL_INT ( 'i' )? { %setType(INT_LITERAL); }
        | ( ( BINARY_INT | OCTAL_INT | HEX_INT ) ( 'i' )? { %setType(INT_LITERAL); } )
	;

ABSTRACT_CLASS_NAME
	: DOLLAR IDENTIFIER
        ;

ITER_NAME_OR_IDENTIFIER_OR_UNDERSCORE
	: '_' { %setType(UNDERSCORE); } 
          ( ( 'a'..'z' | 'A'..'Z' | '_' | '0'..'9' )+  { %setType(IDENTIFIER); } 
            ( EXCLAMATION { %setType(ITER_NAME); } )? 
          )?
        | ( ( 'a'..'z' | 'A'..'Z' )
            ( 'a'..'z' | 'A'..'Z' | '0'..'9' | '_' )* { %setType(IDENTIFIER); } 
            ( EXCLAMATION { %setType(ITER_NAME); } )? 
          )
        ;

// what follows is shamelessly taken from java.g:  thanks guys!

// character literals
CHAR_LITERAL
	: '\'' ( ESC | ~'\'' ) '\''
	;

// string literals
STRING_LITERAL
	: '"' (ESC|~('"'|'\\'))* '"'
	;

// escape sequence -- note that this is protected; it can only be called
//   from another lexer rule -- it will not ever directly return a token to
//   the parser
// There are various ambiguities hushed in this rule.  The optional
// '0'...'9' digit matches should be matched here rather than letting
// them go back to STRING_LITERAL to be matched.  ANTLR does the
// right thing by matching immediately; hence, it's ok to shut off
// the FOLLOW ambig warnings.
protected
ESC
	: '\\'
	 (	'n'
	 |	'r'
	 |	't'
	 |	'b'
	 |	'f'
	 |	'v' // Sather/Library/char.sa uses \v -- still needed?
         |      'a'
	 |	'"'
	 |	'\''
	 |	'\\'
	 |	('u')+ HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT 
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


// hexadecimal digit (again, note it's protected!)
protected
HEX_DIGIT
	: ('0'..'9'|'A'..'F'|'a'..'f')
	;


// a dummy rule to force vocabulary to be all characters (except special
//   ones that ANTLR uses internally (0 to 2)
protected
VOCAB
	: '\3'..'\377'
	;


// Single-line comments
SL_COMMENT
	: "--"
	  (~('\n'|'\r'))* ('\n'|'\r'('\n')?)
	  { %setType(ANTLR_COMMON_TOKEN::SKIP); newline; }
	;

// multiple-line comments
ML_COMMENT
	: "(*"
	    ( options { greedy=false; }
	    : '\r' '\n'	{ newline; }
	    | '\r' 	{ newline; }
	    | '\n'	{ newline; }
	    | .
	    )*
	  "*)"
          { %setType(ANTLR_COMMON_TOKEN::SKIP); }
	;

// Whitespace -- ignored
WS
	: (	' '
	  |	'\t'
	  |	'\f'
	  // handle newlines
	  |	(	"\r\n"  // Evil DOS
	  	|	'\r'    // Macintosh
		|	'\n'    // Unix (the right way)
		)
		{ newline; }
	  )
	  { %setType(ANTLR_COMMON_TOKEN::SKIP); }
	;

