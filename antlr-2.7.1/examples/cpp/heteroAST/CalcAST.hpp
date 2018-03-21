#ifndef INC_CalcAST_hpp__
#define INC_CalcAST_hpp__

#include "antlr/BaseAST.hpp"

class CalcAST : public ANTLR_USE_NAMESPACE(antlr)BaseAST {
public:
	virtual int value() const=0;
};

typedef ANTLR_USE_NAMESPACE(antlr)ASTRefCount<CalcAST> RefCalcAST;

#endif //INC_CalcAST_hpp__
