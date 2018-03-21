options {
	language = "Sather";
}

class INSTR_PARSER extends Parser;
options {
	buildAST = true;
	k=2;
}

tokens {
	CALL; // define imaginary token CALL
}

slist
	:	( stat )+
	;

stat:	LBRACE^ (stat)+ RBRACE
	|	"if"^ expr "then" stat ("else" stat)?
	|	ID ASSIGN^ expr SEMI
	|	call
	;

expr
	:	mexpr (PLUS^ mexpr)*
	;

mexpr
	:	atom (STAR^ atom)*
	;

atom:	INT
	|	ID
	;

call:	ID LPAREN (expr)? RPAREN SEMI
		{@call := @(@[CALL,"CALL"], @call);}
	;

class INSTR_LEXER extends Lexer;
options {
	charVocabulary = '\3'..'\377';
}

WS	:	(' '
		|	'\t'
		|	('\n'|'\r'('\n')?) {newline;}
		)+
	;

// Single-line comments
SL_COMMENT
	:	"//"
		(~('\n'|'\r'))* ('\n'|'\r'('\n')?)
		{newline;}
	;

LBRACE:	'{'
	;

RBRACE:	'}'
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

ASSIGN
	:	'='
	;

protected
DIGIT
	:	'0'..'9'
	;

INT	:	(DIGIT)+
	;

ID	:	('a'..'z')+
	;

class INSTR_TREE_WALKER extends TreeParser;
{
       -- MAIN does not do well with a shared attribute, it seems, so
       -- I put it here.
       private attr filter : ANTLR_TOKEN_STREAM_HIDDEN_TOKEN_FILTER;

        create ( f : ANTLR_TOKEN_STREAM_HIDDEN_TOKEN_FILTER ) : SAME is
          res ::= SAME::create;
          res.filter := f;
          return res;
        end;

        print ( s : STR ) is
          OUT::create + s;
        end;

	-- walk list of hidden tokens in order, printing them out 
	dump_hidden( t : ANTLR_COMMON_HIDDEN_STREAM_TOKEN ) is
	  loop while!( ~void(t) );
	    print(t.text);
            t := filter.hidden_after(t);
          end;
	end;

	pr( p : ANTLR_COMMON_AST_WITH_HIDDEN_TOKENS ) is
	   print( p.text );
  	   dump_hidden( p.hidden_after );
        end;

}

slist
	:	{dump_hidden( filter.first_hidden_token );}
		(stat)+
	;

stat:	#(LBRACE {pr(@LBRACE);} (stat)+ RBRACE {pr(@RBRACE);})
	|	#(i:"if" {pr(i);} expr t:"then" {pr(t);} stat (e:"else" {pr(e);} stat)?)
	|	#(ASSIGN ID {pr(@ID); pr(@ASSIGN);} expr SEMI {pr(@SEMI);} )
	|	call
	;

expr
	:	#(PLUS expr {pr(@PLUS);} expr)
	|	#(STAR expr {pr(@STAR);} expr)
	|	INT {pr(@INT);}
	|	ID  {pr(@ID);}
	;

call:	{
		-- add instrumentation about call; manually call rule
		callDumpInstrumentation(@call);
		}
		#(CALL ID {pr(@ID);}
		  LPAREN {pr(@LPAREN);} (expr)? RPAREN {pr(@RPAREN);}
		  SEMI
		  {
		  -- print SEMI manually; need '}' between it and whitespace
		  print(@SEMI.text);
		  print("}"); -- close {...} of instrumentation
		  dump_hidden( (@SEMI).hidden_after );
		  }
		)
	;

/* Dump instrumentation for a call statement.
 *  The reference to rule expr prints out the arg
 *  and then at the end of this rule, we close the
 *  generated called to dbg.invoke().
 */
callDumpInstrumentation
	:	#(CALL id:ID
		  { print("{dbg.invoke(\"" + id.text + "\", \"" ); }
		  LPAREN (e:expr)? RPAREN SEMI
		  { print("\"); "); }
		)
	;

