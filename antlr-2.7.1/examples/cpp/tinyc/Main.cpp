#include <iostream>
#include "TinyCLexer.hpp"
#include "TinyCParser.hpp"

int main()
{
	try {
		TinyCLexer lexer(std::cin);
		TinyCParser parser(lexer);
		parser.program();
	} catch(std::exception& e) {
		std::cerr << "exception: " << e.what() << std::endl;
	}
	return 0;
}
