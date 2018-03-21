#include <iostream>
#include "CalcLexer.hpp"
#include "CalcParser.hpp"
#include "CalcAST.hpp"

int main()
{
	ANTLR_USING_NAMESPACE(std)
	ANTLR_USING_NAMESPACE(antlr)

	try {
		CalcLexer lexer(cin);
		CalcParser parser(lexer);
		// Parse the input expression
		parser.expr();
		RefCalcAST t = RefCalcAST(parser.getAST());

		// Print the resulting tree out in LISP notation
		cout << t->toStringTree() << endl;

		// Compute value and return
		int r = t->value();
		cout << "value is " << r << endl;
	} catch(exception& e) {
		cerr << "exception: " << e.what() << endl;
//		e.printStackTrace();
	}
}
