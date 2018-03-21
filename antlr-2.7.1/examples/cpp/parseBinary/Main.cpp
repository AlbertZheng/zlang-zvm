#include <iostream>
#include "DataLexer.hpp"
#include "DataParser.hpp"

int main(int argc,char* argv[])
{
	ANTLR_USING_NAMESPACE(std)
	try {
		DataLexer lexer(cin);
		DataParser parser(lexer);
		parser.file();
	} catch(std::exception& e) {
		std::cerr << "exception: " << e.what() << std::endl;
	}
}

