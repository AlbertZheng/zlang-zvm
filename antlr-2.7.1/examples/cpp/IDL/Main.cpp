#include "IDLLexer.hpp"
#include "IDLParser.hpp"
#include <iostream>

int main()
{
	ANTLR_USING_NAMESPACE(std)

	try {
		IDLLexer lexer(cin);
		IDLParser parser(lexer);
		parser.specification();
	} catch(exception& e) {
		cerr << "exception: " << e.what() << endl;
	}
}

