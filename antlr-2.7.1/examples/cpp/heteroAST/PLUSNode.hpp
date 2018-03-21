#ifndef INC_PLUSNode_hpp__
#define INC_PLUSNode_hpp__

#include "BinaryOperatorAST.hpp"

/** A simple node to represent PLUS operation */
class PLUSNode : public BinaryOperatorAST {
public:
	PLUSNode(ANTLR_USE_NAMESPACE(antlr)RefToken tok) {
	}

	/** Compute value of subtree; this is heterogeneous part :) */
	int value() const {
		return left()->value() + right()->value();
	}

	ANTLR_USE_NAMESPACE(std)string toString() const {
		return " +";
	}

	// satisfy abstract methods from BaseAST
	void initialize(int t, const ANTLR_USE_NAMESPACE(std)string& txt) {
	}
	void initialize(ANTLR_USE_NAMESPACE(antlr)RefAST t) {
	}
	void initialize(ANTLR_USE_NAMESPACE(antlr)RefToken tok) {
	}
};

typedef ANTLR_USE_NAMESPACE(antlr)ASTRefCount<PLUSNode> RefPLUSNode;

#endif //INC_PLUSNode_hpp__
