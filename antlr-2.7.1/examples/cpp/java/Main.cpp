#include <iostream>
#include <fstream>
#include "JavaLexer.hpp"
#include "JavaRecognizer.hpp"
#include "JavaTreeParser.hpp"

ANTLR_USING_NAMESPACE(std)
ANTLR_USING_NAMESPACE(antlr)

static void parseFile(const string& f);
static void doTreeAction(const string& f, RefAST t);

int main(int argc,char* argv[])
{
	// Use a try/catch block for parser exceptions
	try {
		// if we have at least one command-line argument
		if (argc > 1 ) {
			cerr << "Parsing..." << endl;

			// for each file specified on the command line
			for(int i=1; i< argc;i++) {
				cerr << "   " << argv[i] << endl;
				parseFile(argv[i]);
			} }
		else
			cerr << "Usage: " << argv[0]
				  << " <file name(s)>" << endl;
	}
	catch(exception& e) {
		cerr << "exception: " << e.what() << endl;
//		e.printStackTrace(System.err);   // so we can get stack trace
	}
}

// Here's where we do the real work...
static void parseFile(const string& f)
{
	try {
		ifstream s(f.c_str());

		// Create a scanner that reads from the input stream
		JavaLexer lexer(s);
		lexer.setFilename(f);

/*
		while (true) {
			RefToken t = lexer.nextToken();
			if (t->getType() == Token::EOF_TYPE)
				break;
			cout << t->getText() << ":" << t->getType() << endl;
		}
*/

		// Create a parser that reads from the scanner
		JavaRecognizer parser(lexer);
		parser.setFilename(f);

		// start parsing at the compilationUnit rule
		parser.compilationUnit();
		
		// do something with the tree
		doTreeAction(f, parser.getAST());
	}
	catch (exception& e) {
		cerr << "parser exception: " << e.what() << endl;
//		e.printStackTrace();   // so we can get stack trace		
	}
}
	
static void doTreeAction(const string& f, RefAST t)
{
	if ( t==nullAST ) return;
	JavaTreeParser tparse;
	try {
		tparse.compilationUnit(t);
		// System.out.println("successful walk of result AST for "+f);
	}
	catch (RecognitionException& e) {
		cerr << e.getMessage() << endl;
//		e.printStackTrace();
	}
}

