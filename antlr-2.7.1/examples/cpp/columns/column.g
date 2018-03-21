// adapted from snippet sent to the antlr-interest list by Remi Koutcherawy
options {
        language="Cpp";
}

{
#include "L.hpp"

	int main( void )
	{
		L lexer(cin);
		P parser(lexer);

		parser.start();
	}
}
class P extends Parser;
start
  : ((t:NB
         { cout << "\"" <<  t->getText() << "\""
					<< " line " << t->getLine() << " col " << t->getColumn()
						<< endl;
			}
    )* NL)*
  ;

class L extends Lexer;
NL  : '\n' {newline();}
    ;
NB  : ('0'..'9')
    ;

