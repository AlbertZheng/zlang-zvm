#include <iostream>
#include "LangLexer.hpp"
#include "LangParser.hpp"
#include "LangWalker.hpp"

int main()
{
	ANTLR_USING_NAMESPACE(std)
	try {
		LangLexer lexer(cin);
		LangParser parser(lexer);
		parser.block();
		cout << parser.getAST()->toStringList() << endl;
		LangWalker walker;
		walker.block(parser.getAST());	// walk tree
		cout << "done walking" << endl;
	} catch(exception& e) {
		cerr << "exception: " << e.what() << endl;
	}
}

