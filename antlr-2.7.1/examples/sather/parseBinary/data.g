options {
	language = "Sather";
}

class DATA_PARSER extends Parser;
{
   println ( s : STR ) is
     #OUT + s + "\n";
   end;
}
   
file:	(	sh:SHORT	{println(sh.text);}
		|	st:STRING	{println("\"" + st.text + "\"");}
		)+
	;

class DATA_LEXER extends Lexer;
options {
	charVocabulary = '\u0000'..'\u00FF';
}

SHORT
	:	'\0' high:. lo:.
		{
		v : INT := high.int.lshift(8) + lo.int;
		%setText(""+v);
		}
	;

STRING
	:	'\1'!	// begin string (discard)
		( ~'\2' )*
		'\2'!	// end string (discard)
	;
