options {
	language = "Sather";
}

class DEMO_JAVADOC_PARSER extends Parser;
options {
	importVocab=JAVADOC;
}
{
   println ( s : STR ) is
     #OUT + s + "\n";
   end;
}

content
	:	(	p:PARAM	// includes ID as part of PARAM
			{println("found: " + p.text);}
		|	e:EXCEPTION
			{println("found: " + e.text);}
		)*
	;
