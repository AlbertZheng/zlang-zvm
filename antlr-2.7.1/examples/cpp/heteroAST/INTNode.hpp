#ifndef INC_INTNode_hpp__
#define INC_INTNode_hpp__

#include <cstdlib>
#include "antlr/Token.hpp"
#include "antlr/String.hpp"
#include "CalcAST.hpp"

/** A simple node to represent an INT */
class INTNode : public CalcAST {
protected:
	int v; //=0;

public:
	INTNode(ANTLR_USE_NAMESPACE(antlr)RefToken tok) {
		v = atoi(tok->getText().c_str());
	}

	/** Compute value of subtree; this is heterogeneous part :) */
	int value() const {
		return v;
	}

	ANTLR_USE_NAMESPACE(std)string toString() const {
		ANTLR_USING_NAMESPACE(antlr)
		return ANTLR_USE_NAMESPACE(std)string(" ")+v;
	}

	// satisfy abstract methods from ASTNode
	void initialize(int t, const ANTLR_USE_NAMESPACE(std)string& txt) {
	}
	void initialize(ANTLR_USE_NAMESPACE(antlr)RefAST t) {
	}
	void initialize(ANTLR_USE_NAMESPACE(antlr)RefToken tok) {
	}
};

typedef ANTLR_USE_NAMESPACE(antlr)ASTRefCount<INTNode> RefINTNode;

#endif //INC_INTNode_hpp__
