#include <iostream>
#include "ExprLexer.hpp"
#include "ExprParser.hpp"
#include "antlr/AST.hpp"
#include "antlr/CommonAST.hpp"

int main()
{
	ANTLR_USING_NAMESPACE(std)
	ANTLR_USING_NAMESPACE(antlr)
	try {
		ExprLexer lexer(cin);
		ExprParser parser(lexer);

		// set the type of tree node to create; this is default action
		// so it is unnecessary to do it here, but demos capability.
		parser.setASTNodeFactory(&CommonAST::factory);

		parser.expr();
		RefCommonAST ast = RefCommonAST(parser.getAST());
//		RefAST ast = parser.getAST();
		if (ast) {
			cout << ast->toStringList() << endl;
		} else {
			cout << "null AST" << endl;
		}
	} catch(exception& e) {
		cerr << "exception: " << e.what() << endl;
	}
}

