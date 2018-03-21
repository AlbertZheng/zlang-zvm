package antlr;

/* ANTLR Translator Generator
 * Project led by Terence Parr at http://www.jGuru.com
 * Software rights: http://www.antlr.org/RIGHTS.html
 *
 * $Id: //depot/code/org.antlr/release/antlr-2.7.1/antlr/ASTVisitor.java#1 $
 */

import antlr.collections.AST;

public interface ASTVisitor{
    public void visit(AST node);
}
