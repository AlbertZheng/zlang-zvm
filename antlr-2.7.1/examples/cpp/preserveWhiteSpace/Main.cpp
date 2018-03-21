#include <iostream>
#include "antlr/CommonASTWithHiddenTokens.hpp"
#include "antlr/CommonHiddenStreamToken.hpp"
#include "InstrLexer.hpp"
#include "InstrParser.hpp"
#include "InstrTreeWalker.hpp"

ANTLR_USING_NAMESPACE(std)
ANTLR_USING_NAMESPACE(antlr)

int main(int argc,char* argv[])
{
	InstrLexer lexer(cin);
	lexer.setTokenObjectFactory(&CommonHiddenStreamToken::factory);
	TokenStreamHiddenTokenFilter filter(lexer);
	filter.hide(InstrParser::WS_);
	filter.hide(InstrParser::SL_COMMENT);
	InstrParser parser(filter);
	parser.setASTNodeFactory(&CommonASTWithHiddenTokens::factory);
	try {
		// Parse the input statements
		parser.slist();
	}
	catch(RecognitionException& e) {
		cerr << "exception: " << e.what() << endl;
	}

	RefAST t = parser.getAST();

	InstrTreeWalker walker;
	walker.setFilter(filter);
	try {
		walker.slist(t);
	}
	catch(RecognitionException& e) {
		cerr << "exception: " << e.what() << endl;
	}

}

void InstrTreeWalker::setFilter(TokenStreamHiddenTokenFilter& filter_)
{
	filter = &filter_;
}

/** walk list of hidden tokens in order, printing them out */
void InstrTreeWalker::dumpHidden(RefToken t)
{
	for ( ; t ; t=filter->getHiddenAfter(t) ) {
		cout << t->getText();
	}
}

void InstrTreeWalker::pr(RefAST p)
{
	cout << p->getText();
	dumpHidden(
		(RefCommonASTWithHiddenTokens(p))->getHiddenAfter()
	);
}
