options {
	language = "Sather";
}

class DEMO_JAVA_LEXER extends Lexer;
options {
	k=2;
	importVocab = Common;
	exportVocab = JAVA;
}

tokens {
	INT="int";
}

JAVADOC_OPEN
	:	"/**" {MAIN::selector.push("javadoc");}
	;

ID	:	('a'..'z')+ ;
SEMI:	';' ;
WS	:	(	' '
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

