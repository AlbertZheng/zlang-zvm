#include <iostream>
#include "SimpleLexer.hpp"
#include "SimpleParser.hpp"
#include "SimpleParser2.hpp"
#include "antlr/TokenBuffer.hpp"

int main()
{
	using namespace std;
	try {
		SimpleLexer lexer(cin);
		TokenBuffer buffer(lexer);

		/* Invoke first parser */
		cout << "first parser" << endl;
		SimpleParser parser(buffer);
		parser.simple();

		/* When first parser runs out, invoke secnond parser */
		cout << "second parser" << endl;
		SimpleParser2 parser2(buffer);
		parser2.simple();

	} catch(exception& e) {
		cerr << "exception: " << e.what() << endl;
	}
}

