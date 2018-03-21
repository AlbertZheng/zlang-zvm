#include <iostream>
#include "TinyCLexer.hpp"
#include "MyCParser.hpp"

int main()
{
	ANTLR_USING_NAMESPACE(std)

	try {
		TinyCLexer lexer(cin);
		MyCParser parser(lexer);
		parser.program();
	} catch(exception& e) {
		cerr << "exception: " << e.what() << endl;
	}
}

