options {
	language = "Sather";
}

class DEMO_JAVA_PARSER extends Parser;
options {
	importVocab=JAVA;
}

input
	:	( (javadoc)? INT ID SEMI )+
	;

javadoc
	:	JAVADOC_OPEN
		{
		javadoc_parser ::=  #DEMO_JAVADOC_PARSER{TOKEN,AST}( input_state );
		javadoc_parser.content;
		}
		JAVADOC_CLOSE
	;
