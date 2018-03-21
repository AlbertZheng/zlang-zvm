#include <iostream>
#include "Rewrite.hpp"

int main()
{
	ANTLR_USING_NAMESPACE(std)
	try {
		Rewrite lexer(cin);
		lexer.mSTART(true);
		cout << "result Token=" << lexer.getTokenObject()->toString() << endl;
	} catch(exception& e) {
		cerr << "exception: " << e.what() << endl;
	}
}

