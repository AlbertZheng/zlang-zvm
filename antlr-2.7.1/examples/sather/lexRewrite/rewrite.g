options {
	language = "Sather";
}

class REWRITE extends Lexer;
{
   println ( str : STR ) is 
     #OUT + str + "\n";
   end;
}

protected
START
options {
	ignore=WS;
}
	:	id:ID ":="! '('! expr:EXPR ')'!
		{
			-- can access text matched for any rule
			println( "found " + id.text + "," + expr.text );
			-- text will be ID+EXPR minus whitespace
		}
	;

protected
ID	:	( let:LETTER { println( "letter "+let.text ); } )+
	;

protected
LETTER
	:	'a'..'z'
                // note do !NOT! put spaces inside parens! (ActionLexer does not seem to handle it).		
                {
		s : STR := %getText;	-- get access text of this rule
		%setText(s.upper);	-- can reset it too 
		}
	;
protected
EXPR:	i:INT!	// don't include, but i.text has access
		{%setText(i.text);} // effect is if no "!" and no "i:"
	|	ID
	;

protected
INT	:	('0'..'9')+
	;

// what if ! on rule itself and invoker had !...should
// rule return anything in the token to the invoker?  NO!
// make sure 'if' is in the right spot
// What about no ! on caller but ! on called rule?
protected
WS!	:	(	' '			// whitespace not saved
		|	'\t'
		|	'\n' {newline;}
		)+
		{%setType(ANTLR_COMMON_TOKEN::SKIP);}		// way to set token type
	;


