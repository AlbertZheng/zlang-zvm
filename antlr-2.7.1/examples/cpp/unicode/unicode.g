options {
	language="Cpp";
}

class L extends Lexer;

options
{
	// Allow any char but \uFFFF (16 bit -1)
	charVocabulary='\u0000'..'\uFFFE';
}

{
	bool done;

	public void uponEOF()
	{
		done = true;
	}

	int main(int argc, char **argv)
	{
	  	done = false;
		L lexer = new L(std::stdin);
		while ( !done )
		{
			Token t = lexer.nextToken();
			cout << "Token: " << t.getText() << endl;;
		}
	}
}

ID	:	ID_START_LETTER ( ID_LETTER )*
	;

WS	:	(' '|'\n') {$setType(Token.SKIP);
}
;

protected
	ID_START_LETTER
	:	'$'
	|	'_'
	|	'a'..'z'
	|	'\u0080'..'\ufffe'
	;

protected
	ID_LETTER
	:	ID_START_LETTER
	|	'0'..'9'
	;
