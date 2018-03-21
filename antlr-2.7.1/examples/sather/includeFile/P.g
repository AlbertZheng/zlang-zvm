options {
	language = "Sather";
}

class P_PARSER extends Parser;
{
	println( s : STR ) is
		OUT::create + s + '\n';
	end;
}

startRule
	:	( decl )+
	;

decl:	INT a:ID { println("decl " + a.text ); }
		( COMMA b:ID { println("decl " + b.text ); } )*
		SEMI
	;

class P_LEXER extends Lexer;
options {
	charVocabulary = '\3'..'\377';
	k=2;
}

tokens {
	INT="int";
}

{
	upon_eof is
		if ( ~SYS::is_eq( M::selector.current_stream, M::main_lexer ) ) then
			-- // don't allow EOF until main lexer.  Force the
			-- // selector to retry for another token.
			M::selector.pop; -- // return to old lexer/stream
			M::selector.retry;
		else 
			OUT::create + "Hit EOF of main file\n";
		end;
	end;
}

SEMI:	';'
	;

COMMA
	:	','
	;

ID
	:	('a'..'z')+
	;

INCLUDE
	:	"#include" (WS)? f:STRING
		{
		-- // create lexer to handle include
		name : STR := f.text;
                input ::= IFSTREAM::open_for_read( name );

                if ( void(input) ) then
	            raise "cannot find file " + name;
                end;

		sublexer ::= P_LEXER{TOKEN}::create(input);

		-- // make sure errors are reported in right file
		sublexer.file_name(name);
		M::parser.file_name(name);

		-- // you can't just call nextToken of sublexer
		-- // because you need a stream of tokens to
		-- // head to the parser.  The only way is
		-- // to blast out of this lexer and reenter
		-- // the nextToken of the sublexer instance
		-- // of this class.

                M::selector.push(sublexer);

		-- // ignore this as whitespace; ask selector to try
		-- // to get another token.  It will call nextToken()
		-- // of the new instance of this lexer.
		M::selector.retry; -- // throws TokenStreamRetryException
		}
	;

STRING
	:	'"'! ( ~'"' )* '"'!
	;

WS	:	(	' '
		|	'\t'
		|	'\f'
			// handle newlines
		|	(	options {generateAmbigWarnings=false;}
			:	"\r\n"  // Evil DOS
			|	'\r'    // Macintosh
			|	'\n'    // Unix (the right way)
			)
			{ newline; }
		)+
		{ %setType(ANTLR_COMMON_TOKEN::SKIP); }
	;
