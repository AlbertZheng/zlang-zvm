#ifndef INC_MULTNode_hpp__
#define INC_MULTNode_hpp__

#include "BinaryOperatorAST.hpp"

/** A simple node to represent MULT operation */
class MULTNode : public BinaryOperatorAST {
public:
	MULTNode(ANTLR_USE_NAMESPACE(antlr)RefToken tok) {
	}

	/** Compute value of subtree; this is heterogeneous part :) */
	int value() const {
		return left()->value() * right()->value();
	}

	ANTLR_USE_NAMESPACE(std)string toString() const {
		return " *";
	}

	// satisfy abstract methods from BaseAST
	void initialize(int t, const ANTLR_USE_NAMESPACE(std)string& txt) {
	}
	void initialize(ANTLR_USE_NAMESPACE(antlr)RefAST t) {
	}
	void initialize(ANTLR_USE_NAMESPACE(antlr)RefToken tok) {
	}
};

typedef ANTLR_USE_NAMESPACE(antlr)ASTRefCount<MULTNode> RefMULTNode;

#endif //INC_MULTNode_hpp__
