#include <iostream>
#include "antlr/AST.hpp"
#include "CalcLexer.hpp"
#include "CalcParser.hpp"
#include "CalcTreeWalker.hpp"

int main()
{
	ANTLR_USING_NAMESPACE(std)
	ANTLR_USING_NAMESPACE(antlr)
	try
	{
		CalcLexer lexer(cin);
		lexer.setFilename("<stdin>");

		CalcParser parser(lexer);
		parser.setFilename("<stdin>");

		// Parse the input expression
		parser.expr();
		RefAST t = parser.getAST();
		if( t )
		{
			// Print the resulting tree out in LISP notation
			cout << t->toStringTree() << endl;
			CalcTreeWalker walker;

			// Traverse the tree created by the parser
			float r = walker.expr(t);
			cout << "value is " << r << endl;
		}
		else
			cout << "No tree produced" << endl;

	}
	catch(exception& e)
	{
		cerr << "exception: " << e.what() << endl;
	}
}
