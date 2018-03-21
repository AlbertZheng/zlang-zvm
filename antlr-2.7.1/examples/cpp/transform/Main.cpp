#include <iostream>
#include "CalcLexer.hpp"
#include "CalcParser.hpp"
#include "CalcTreeWalker.hpp"

int main()
{
	ANTLR_USING_NAMESPACE(std)
	ANTLR_USING_NAMESPACE(antlr)
	try {
		CalcLexer lexer(cin);
		CalcParser parser(lexer);
		// Parse the input expression
		parser.expr();
		RefAST t = parser.getAST();
		// Print the resulting tree out in LISP notation
		cout << t->toStringList() << endl;
		CalcTreeWalker walker;
		// Traverse the tree created by the parser
		walker.expr(t);
		t = walker.getAST();
		cout << t->toStringList() << endl;
	} catch(exception& e) {
		cerr << "exception: " << e.what() << endl;
	}
}

