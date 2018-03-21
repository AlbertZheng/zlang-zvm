#include <iostream>
#include "T.hpp"

int main()
{
	ANTLR_USING_NAMESPACE(std)
	ANTLR_USING_NAMESPACE(antlr)

	try {
		T lexer(cin);
		bool done = false;
		while ( !done ) {
			RefToken t = lexer.nextToken();
			cout << "Token: " << t->toString() << endl;
			if ( t->getType()==Token::EOF_TYPE ) {
				done = true;
			}
		}
		cout << "done lexing..." << endl;
	} catch(exception& e) {
		cerr << "exception: " << e.what() << endl;
	}
}

