options {
	language = "Sather";
}

class T extends Lexer;
options {
	k=2;
	filter=IGNORE;
	charVocabulary = '\3'..'\177';
}

{
  -- used here temporarily to circumvent translation of
  -- the "#OUT" in the IGNORE action.
  println( msg: STR ) is 
    #OUT + msg + "\n";
  end;
}

P : "<p>" ;
BR: "<br>" ;

protected
IGNORE
	:	'<' (~'>')* '>' { println( "invalid tag: " + %getText ); }
	|	( "\r\n" | '\r' | '\n' ) {newline;}
	|	.
	;
