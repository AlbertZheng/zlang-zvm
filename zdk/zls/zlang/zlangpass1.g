header "post_include_hpp" {
#include <antlr/CharScanner.hpp>
#include <zls/zlang/CZLangAST.hpp>
}


options {
  language = "Cpp";
  namespace = "zlang";
  namespaceStd = "std::";
  namespaceAntlr = "antlr::";
}

/**
 * <b>ZLang Compiler Pass1 Parser.</b>
 *
 * It will do syntax parsing.
 *
 * <pre>
 * @version 0.4,   2000/12/19
 * @version 0.5,   2000/12/20
 * @version 0.6,   2000/12/27
 * @version 0.7,   2001/01/09
 * @version 0.8,   2001/01/18
 *   Now supporting: (1) return 'table';
 *                   (2) 'table" can act as parameter;
 *                   (3) 'table's index type is unlimited;
 * @version 0.8.1, 2001/01/21
 *   Now supporting: (1) extern
 * @version 0.8.2, 2001/01/30
 *   (1) 'IPv4_LITERAL' renamed to 'IPv4ADDR_LITERAL', and rule definition changed too;
 *   (2) 'PORT_LITERAL' renamed to 'PPORT_LITERAL', and rule definition changed too;
 *   (3) 'builtInType' rule definition changed;
 * @version 0.8.3, 2001/01/31
 *   (1) "void" only can appear at function/method return declaration;
 * @version 0.9, 2001/04/01
 *   (1) Zlang grammar was redesigned:
 *       (a) 'machine','method','environment','state' were discarded;
 *       (b) 'static' was introduced into and 'global' was discarded.
 * @version 0.9.1, 2001/05/10
 *   (1) rule 'assignExpression' modified for supporting 'nested assign'.
 * @version 0.9.2, 2001/06/23
 *   (1) Supporting "SQWORD", "UQWORD".
 * @version 1.1, 2001/06/26
 *   (1) Supporting "for statement".
 *   (2) Bug of 'testing expression statement' of "if statement" and "while statement' fixed.
 * @version 1.2, 2001/7/8
 *   (1) The grammar of 'reference argument' modified to be as same as C++'s '&'.
 *   (2) The grammar of 'table' modified to be as same as C++'s template.
 *   (3) Some rules were modified or deleted.
 *   (4) 'static' was redesigned, and now supporting 'static global variable' too.
 * @version 1.2, 2001/7/10
 *   (1) Supporting 'local reference variable'.
 *   (2) Supporting 'return reference address' but only native can return 'reference address' .
 * </pre>
 *
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/zlangpass1.g,v $
 *
 * $Date: 2001/08/10 18:34:37 $
 *
 * $Revision: 1.5 $
 *
 * $Name:  $
 *
 * $Author: zls $
 *
 * Copyright(C) since 1998 by Albert Zheng, All Rights Reserved.
 *
 * lisong.zheng@gmail.com
 *
 * $State: Exp $
 */
class ZLangParser extends Parser;
options {
  k = 4;
  exportVocab = ZLang;
  codeGenMakeSwitchThreshold = 2;  // Some optimizations
  codeGenBitsetTestThreshold = 3;
  buildAST = true;
  ASTLabelType = "zlang::CZLangAST_auto";
  defaultErrorHandler = false;
}

tokens {
  EXTERN_GFUNCTION_DECLARATION; EXTERN_GVARIABLE_DECLARATION;
  GFUNCTION_DEFINITION; GVARIABLE_DEFINITION;
  PARAMETERS_DECLARATION; LVARIABLE_DEFINITION; ELEMENT_INIT;
  CODE_BLOCK; COMPOUND_STATEMENTS;
  EXPRESSION; UNARY_PLUS; UNARY_MINUS; TYPECAST;
  SUBSCRIPT; CALLING; POST_INC; POST_DEC;
  FOR_EXPRESSION1; FOR_EXPRESSION2; FOR_EXPRESSION3;
}


/**
 * ZLang script start rule.
 */
zlangScript
        : (   externGlobalDeclaration
            | globalDefinition
          )*
          EOF!
        ;

/**
 * EXTERN_GFUNCTION_DECLARATION
 *  |
 * <functionName>
 *  |
 * "table"? - <builtInType> - '&'? - PARAMETERS_DECLARATION?
 *                                    |
 *                                   ...
 *
 *
 * EXTERN_GVARIABLE_DECLARATION
 *  |
 * <builtInType> - <variable1Name> - <variable2Name>
 *
 * EXTERN_GVARIABLE_DECLARATION
 *  |
 * "table" - <builtInType> - <table1Name> - <table2Name>
 */
externGlobalDeclaration
        : "extern"!
          (   (builtInType | "table" LT_! builtInType GT!)
              (   (BAND)? IDENTIFIER^ LPAREN! (parameterDeclarationList)? RPAREN! SEMI!
                  { ## = #(#[EXTERN_GFUNCTION_DECLARATION,"EXTERN_GFUNCTION_DECLARATION"], ##); }

                | IDENTIFIER (COMMA! IDENTIFIER)* SEMI!
                  { ## = #(#[EXTERN_GVARIABLE_DECLARATION,"EXTERN_GVARIABLE_DECLARATION"], ##); }
              )

            | "void" IDENTIFIER^ LPAREN! (parameterDeclarationList)? RPAREN! SEMI!
              { ## = #(#[EXTERN_GFUNCTION_DECLARATION,"EXTERN_GFUNCTION_DECLARATION"], ##); }
          )
        ;

/**
 * GFUNCTION_DEFINITION
 *  |
 * "static"? - <functionName>
 *               |
 *             "table"? - <builtInType> - '&'? - PARAMETERS_DECLARATION - CODE_BLOCK
 *                                                |                        |
 *                                               ...                      ...
 *
 *
 * GVARIABLE_DEFINITION
 *  |
 * "static"? - <builtInType> - <variable1Name> - <variable2Name>
 *              |                 |
 *             <constant>?       ...?
 *
 * GVARIABLE_DEFINITION
 *  |
 * "static"? - "table" - <builtInType> - <tableName> ... ELEMENT_INIT? ------ ELEMENT_INIT?
 *                                                        |                    |
 *                                                       <element1Constant>   <element?Constant>
 *                                                        |                    |
 *                                                       <value1Constant>     <value?Constant>
 */
globalDefinition
        : { bool bStatic = false; }
          (tSTATIC:"static"! {bStatic = true;})?
          (
              (   builtInType
                  (   (BAND)? IDENTIFIER^ LPAREN! (parameterDeclarationList)? RPAREN! codeBlock
                      {
                        if (bStatic)
                        {
                          ## = #(#[GFUNCTION_DEFINITION,"GFUNCTION_DEFINITION"], #tSTATIC, ##);
                        }
                        else
                        {
                          ## = #(#[GFUNCTION_DEFINITION,"GFUNCTION_DEFINITION"], ##);
                        }
                      }

                    | ( tNAME1:IDENTIFIER!
                             // global variable initializer is different with local vaiable
                             // initializer. Just as possible as simple !
                        (ASSIGN! rINIT1:initializationConstant!
                         { #tNAME1 = #(#tNAME1, #rINIT1); }
                        )?
                        { astFactory.addASTChild(currentAST, ANTLR_USE_NAMESPACE(antlr)RefAST(tNAME1_AST)); }
                        (COMMA! tNAME2:IDENTIFIER!
                                (ASSIGN! rINIT2:initializationConstant!
                                 { #tNAME2 = #(#tNAME2, #rINIT2); }
                                )?
                                { astFactory.addASTChild(currentAST, ANTLR_USE_NAMESPACE(antlr)RefAST(tNAME2_AST)); }
                        )*
                        SEMI!
                      )
                      {
                        if (bStatic)
                        {
                          ## = #(#[GVARIABLE_DEFINITION,"GVARIABLE_DEFINITION"], #tSTATIC, ##);
                        }
                        else
                        {
                          ## = #(#[GVARIABLE_DEFINITION,"GVARIABLE_DEFINITION"], ##);
                        }
                      }
                  )

                | "table" LT_! builtInType GT!
                  (   (BAND)? IDENTIFIER^ LPAREN! (parameterDeclarationList)? RPAREN! codeBlock
                      {
                        if (bStatic)
                        {
                          ## = #(#[GFUNCTION_DEFINITION,"GFUNCTION_DEFINITION"], #tSTATIC, ##);
                        }
                        else
                        {
                          ## = #(#[GFUNCTION_DEFINITION,"GFUNCTION_DEFINITION"], ##);
                        }
                      }

                    | IDENTIFIER (tableInit)? SEMI!
                      {
                        if (bStatic)
                        {
                          ## = #(#[GVARIABLE_DEFINITION,"GVARIABLE_DEFINITION"], #tSTATIC, ##);
                        }
                        else
                        {
                          ## = #(#[GVARIABLE_DEFINITION,"GVARIABLE_DEFINITION"], ##);
                        }
                      }
                  )
              )
            | "void" IDENTIFIER^ LPAREN! (parameterDeclarationList)? RPAREN! codeBlock
              {
                if (bStatic)
                {
                  ## = #(#[GFUNCTION_DEFINITION,"GFUNCTION_DEFINITION"], #tSTATIC, ##);
                }
                else
                {
                  ## = #(#[GFUNCTION_DEFINITION,"GFUNCTION_DEFINITION"], ##);
                }
              }
          )
        ;

/**
 * CODE_BLOCK
 *  |
 * ...
 */
codeBlock
        : LCURLY!
          (localVariableDefinition)*
          compoundStatement
          RCURLY!
          { ## = #(#[CODE_BLOCK,"CODE_BLOCK"], ##); }
        ;

/**
 * PARAMETERS_DECLARATION
 *  |
 * <parameter1Name> - <parameter2Name> - <tableParameterName>
 *  |                  |                  |
 */
parameterDeclarationList
        : parameterDeclaration (COMMA! parameterDeclaration)*
          { ## = #(#[PARAMETERS_DECLARATION,"PARAMETERS_DECLARATION"], ##); }
        ;

/**
 * <parameterName>             <tableParameterName>
 *  |                           |
 * <builtInType> - '&'?        "table" - <builtInType> - '&'?
 */
parameterDeclaration
        : (   builtInType (BAND)? IDENTIFIER^
            | "table" LT_! builtInType GT! (BAND)? IDENTIFIER^
          )
        ;

/**
 * COMPOUND_STATEMENTS
 *  |
 * LITERAL_if - LITERAL_while - EXPRESSION - ...
 */
compoundStatement
        : (statement)*
          { ## = #(#[COMPOUND_STATEMENTS,"COMPOUND_STATEMENTS"], ##); }
        ;

statement
        :   SEMI!   // NULL statement
            // An expression statement.  This could be a function call,
            // assignment statement, or any other expression evaluated for
            // side-effects.
          | expression SEMI!
          | ifStatement
          | whileStatement
            // get out of a loop (or switch)
          | "break" SEMI!
            // do next iteration of a loop
          | "continue" SEMI!
            // return an expression
          | "return"^ (expression)? SEMI!
          | forStatement
        ;

/**
 * LITERAL_if
 *  |
 * EXPRESSION - COMPOUND_STATEMENTS - COMPOUND_STATEMENTS
 */
ifStatement
        : "if"^ LPAREN! expression RPAREN!
          LCURLY! compoundStatement RCURLY!
          ("else"! LCURLY! compoundStatement RCURLY!)?
        ;

/**
 * LITERAL_while
 *  |
 * EXPRESSION - COMPOUND_STATEMENTS
 */
whileStatement
        : "while"^ LPAREN! expression RPAREN!
          LCURLY! compoundStatement RCURLY!
        ;

/**
 * LITERAL_for
 *  |
 * EXPRESSION1? - EXPRESSION2? - EXPRESSION3? - COMPOUND_STATEMENTS
 */
forStatement
        : "for"^ LPAREN! (forExpression1)? SEMI! (forExpression2)? SEMI! (forExpression3)? RPAREN!
          LCURLY! compoundStatement RCURLY!
        ;

forExpression1
        : assignExpression
          { ## = #(#[FOR_EXPRESSION1,"FOR_EXPRESSION1"], ##); }
        ;

forExpression2
        : assignExpression
          { ## = #(#[FOR_EXPRESSION2,"FOR_EXPRESSION2"], ##); }
        ;

forExpression3
        : assignExpression
          { ## = #(#[FOR_EXPRESSION3,"FOR_EXPRESSION3"], ##); }
        ;

/**
 * LVARIABLE_DEFINITION
 *  |
 * <builtInType> - '&'? - <variable1Name> - <variable2Name>
 *                         |                 |
 *                        EXPRESSION?       ...?
 *
 *
 * LVARIABLE_DEFINITION
 *  |
 * "table" - <builtInType> - <tableName> ... ELEMENT_INIT? ------ ELEMENT_INIT?
 *                                            |                    |
 *                                           <element1Constant>   <element?Constant>
 *                                            |                    |
 *                                           <value1Constant>     <value?Constant>
 *
 *
 * Note: The following is just for reference table variable, or a function
 * calling which will return the same type table, or another same type table
 * variable, or another same type reference table variable!
 *
 * LVARIABLE_DEFINITION
 *  |
 * "table" - <builtInType> - '&'? - <tableName> - EXPRESSION?
 */
localVariableDefinition
        : (   builtInType (BAND)?
              tNAME1:IDENTIFIER!
              (ASSIGN! rINIT1:expression!
               { #tNAME1 = #(#tNAME1, #rINIT1); }
              )?
              { astFactory.addASTChild(currentAST, ANTLR_USE_NAMESPACE(antlr)RefAST(tNAME1_AST)); }
              (COMMA! tNAME2:IDENTIFIER!
                      (ASSIGN! rINIT2:expression!
                       { #tNAME2 = #(#tNAME2, #rINIT2); }
                      )?
                      { astFactory.addASTChild(currentAST, ANTLR_USE_NAMESPACE(antlr)RefAST(tNAME2_AST)); }
              )*
              SEMI!

            | "table" LT_! builtInType GT! (BAND)? IDENTIFIER (tableInit)? SEMI!
          )
          { ## = #(#[LVARIABLE_DEFINITION,"LVARIABLE_DEFINITION"], ##); }
        ;

tableInit
        : ASSIGN!
          (   LCURLY! tableElementInit (COMMA! tableElementInit)* RCURLY!
            | expression
          )
        ;

tableElementInit
        : initializationConstant ASSIGN! initializationConstant
          { ## = #(#[ELEMENT_INIT,"ELEMENT_INIT"], ##); }
        ;

builtInType
        :   "byte"
          | "bool"
          | "sdword"
          | "udword"
          | "sqword"
          | "uqword"
          | "double"
          | "string"
          | "ipaddress"
          | "pport"
          | "rope"
        ;

/**
 * expressions
 * Note that most of these expressions follow the pattern
 *   thisLevelExpression :
 *       nextHigherPrecedenceExpression (OPERATOR nextHigherPrecedenceExpression)*
 * which is a standard recursive definition for a parsing an expression.
 * Our operators have the following precedences:
 *    lowest
 *            (13)  = *= /= %= += -= <<= >>= >>>= &= ^= |=
 *                    ------------------------------------
 *                                     x
 *          x (12)  ?:
 *            (11)  ||
 *            (10)  &&
 *            ( 9)  |
 *            ( 8)  ^
 *            ( 7)  &
 *            ( 6)  == !=
 *            ( 5)  < <= > >=
 *            ( 4)  << >>
 *            ( 3)  +(binary) -(binary)
 *            ( 2)  * / %
 *            ( 1)  ++ --
 *                  +(unary) -(unary)
 *                  ~ !
 *                  (typecast)
 *                  []
 *                  ()(function call)
 *                  .(dot - identifier qualification)
 *
 * Note that the above precedence levels map to the rules below...
 * Once you have a precedence chart, writing the appropriate rules as below
 * is usually very straightfoward.
 *
 *
 * The mother of all expressions
 *
 * EXPRESSION
 *  |
 * ...
 */
expression
        : assignExpression
          { ## = #(#[EXPRESSION,"EXPRESSION"], ##); }
        ;

/** this is a list of expressions for function calling. */
argumentList
	: expression (COMMA! expression)*
	;

/**
 * assign (=)  (level 13)
 *
 * ASSIGN
 *   |
 * leftSubTree - rightSubTree
 */
assignExpression
        :                                               // Let "=" just once
          //logicalOrExpression (ASSIGN^ logicalOrExpression)?
          // 2001/5/10: Now supporting 'assign' left pass(nested 'assign')
          logicalOrExpression (ASSIGN^ assignExpression)?
	;

/**
 * logical or (||)  (level 11)
 *
 * LOR
 *  |
 * leftSubTree - rightSubTree
 */
logicalOrExpression
	: logicalAndExpression (LOR^ logicalAndExpression)*
	;

/**
 * logical and (&&)  (level 10)
 *
 * LAND
 *  |
 * leftSubTree - rightSubTree
 */
logicalAndExpression
	: bitwiseOrExpression (LAND^ bitwiseOrExpression)*
	;

/**
 * bitwise or non-short-circuiting or (|)  (level 9)
 *
 * BOR
 *  |
 * leftSubTree - rightSubTree
 */
bitwiseOrExpression
	: bitwiseXorExpression (BOR^ bitwiseXorExpression)*
	;

/**
 * exclusive or (^)  (level 8)
 *
 * BXOR
 *  |
 * leftSubTree - rightSubTree
 */
bitwiseXorExpression
	: bitwiseAndExpression (BXOR^ bitwiseAndExpression)*
	;

/**
 * bitwise or non-short-circuiting and (&)  (level 7)
 *
 * BAND
 *  |
 * leftSubTree - rightSubTree
 */
bitwiseAndExpression
	: equalityExpression (BAND^ equalityExpression)*
	;

/**
 * equality/inequality (== !=) (level 6)
 *
 * NOT_EQUAL/EQUAL
 *  |
 * leftSubTree - rightSubTree
 */
equalityExpression
	: relationalExpression ((NOT_EQUAL^ | EQUAL^) relationalExpression)*
	;

/**
 * boolean relational expressions (level 5)
 *
 * LT_/GT/LE/GE
 *  |
 * leftSubTree - rightSubTree
 */
relationalExpression
	: shiftExpression
          (
            (   LT_^
              | GT^
              | LE^
              | GE^
            )
            shiftExpression
          )*
	;

/**
 * bit shift expressions (<< >>) (level 4)
 *
 * SL/SR
 *  |
 * leftSubTree - rightSubTree
 */
shiftExpression
	: additiveExpression ((SL^ | SR^) additiveExpression)*
	;

/**
 * binary addition/subtraction (+ -) (level 3)
 *
 * PLUS/MINUS
 *  |
 * leftSubTree - rightSubTree
 */
additiveExpression
	: multiplicativeExpression ((PLUS^ | MINUS^) multiplicativeExpression)*
	;

/**
 * multiplication/division/modulo (* / %) (level 2)
 *
 * STAR/DIV/MOD
 *  |
 * leftSubTree - rightSubTree
 */
multiplicativeExpression
	: unaryExpression ((STAR^ | DIV^ | MOD^) unaryExpression)*
	;

/**
 * unary (++ -- - + ~ ! typecast) (level 1)
 *
 * INC/DEC/UNARY_MINUS/UNARY_PLUS/BNOT/LNOT
 *  |
 * leftSubTree
 *
 * TYPECAST
 *  |
 * <builtInType> - ...
 */
unaryExpression
	: (   INC^   // ++v
            | DEC^   // --v
            | MINUS^   // -v
              { #MINUS->setType(UNARY_MINUS); #MINUS->setText("UNARY_MINUS"); }
            | PLUS^   // +v
              { #PLUS->setType(UNARY_PLUS); #PLUS->setText("UNARY_PLUS"); }
            | BNOT^   // ~
            | LNOT^   // !
              // only typecast of built-in-type is support
            | tCAST:LPAREN^
              { #tCAST->setType(TYPECAST); #tCAST->setText("TYPE_CAST"); }
              builtInType RPAREN!
          )?
          postfixExpression
	;

/**
 * qualified names, array expressions, function invocation, post inc/dec
 *
 * CALLING
 *  |
 * <methodName> - <argument1> - <argument2>
 *
 *
 * DOT
 *  |
 * <left> - <right>
 *
 *
 * SUBSCRIPT
 *  |
 * <left> - <right>
 *
 *
 * POST_INC/POST_DEC
 *  |
 * <name>
 */
postfixExpression
	: primaryExpression
          (   // function call
              tCALLING:LPAREN^
              { #tCALLING->setType(CALLING); #tCALLING->setText("CALLING"); }
              (argumentList)? RPAREN!

              // qualified id (id.id)
            | DOT^ IDENTIFIER

              // an access operation using array/table's subscript
            | tINDEX:LBRACK^
              { #tINDEX->setType(SUBSCRIPT); #tINDEX->setText("SUBSCRIPT"); }
              expression RBRACK!

              // post-increment or post-decrement.
            | tINC:INC^   // v++
              { #tINC->setType(POST_INC); #tINC->setText("POST++"); }
            | tDEC:DEC^   // v--
              { #tDEC->setType(POST_DEC); #tDEC->setText("POST--"); }
          )?
	;

/** the basic element of an expression. */
primaryExpression
	:   IDENTIFIER
          | constant
          | LPAREN! assignExpression RPAREN!
	;

constant
	:   NUM_INT
          | NUM_HEX_INT
          | NUM_QUAD
          | NUM_HEX_QUAD
          | NUM_FLOAT
          | CHAR_LITERAL
          | STRING_LITERAL
          | IPv4ADDR_LITERAL
          | PPORT_LITERAL
          | "true"
          | "false"
          | ROPE_LITERAL
	;

initializationConstant
	:   (PLUS | MINUS)? (NUM_INT | NUM_QUAD | NUM_FLOAT)
          | NUM_HEX_INT
          | NUM_HEX_QUAD
          | CHAR_LITERAL
          | STRING_LITERAL
          | IPv4ADDR_LITERAL
          | PPORT_LITERAL
          | "true"
          | "false"
          | ROPE_LITERAL
	;



/**
 * <b>ZLang Lexer</b>
 *
 * <pre>
 * @version 0.2, 2000/12/16
 * @version 0.3, 2000/12/20
 * @version 1.0, 2001/5/11
 *   (1) rule 'IPv4ADDR_LITERAL' modified;
 *   (2) rule 'ESCAPE' patched;
 * @version 1.1, 2001/5/18
 *   (1) Added rule 'CPP_LINE_CONTROL';
 * @version 1.2, 2001/6/23
 *   (1) Supporting "NUM_QUAD", "NUM_HEX_QUAD";
 * @version 1.2, 2001/7/8
 *   (1) The grammar of 'ipaddress literal' and 'pport literal' was redesigned.
 * </pre>
 *
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/zlangpass1.g,v $
 *
 * $Date: 2001/08/10 18:34:37 $
 *
 * $Revision: 1.5 $
 *
 * $Name:  $
 *
 * $Author: zls $
 *
 * Copyright(C) since 1998 by Albert Zheng, All Rights Reserved.
 *
 * lisong.zheng@gmail.com
 *
 * $State: Exp $
 */
class ZLangLexer extends Lexer;
options {
  testLiterals = false;
  k = 2;
  importVocab = ZLang;
  charVocabulary = '\3'..'\377';
}

{
private:
  /**
   * The member variable saves compiled-source-file-name.
   */
  std::string _stringCompiledSourceFileName;

public:
  virtual void setFilename(const std::string & f)
  {
    antlr::CharScanner::setFilename(f);
    _stringCompiledSourceFileName = f;
  }

}

/** whitespace -- ignored. */
WS_
options {
  paraphrase = "white space";
}
        : (   ' '
	    | '\t'
	    | '\f'
	      // handle newlines
	    | (   "\r\n"  // Evil DOS
	        | '\r'    // Macintosh
	        | '\n'    // Unix (the right way)
	      )
	      { newline(); }
	  )
	  { $setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP); }
	;


/** single-line comments. */
SL_COMMENT
options {
  paraphrase = "single-line comments";
}
	: "//"
          (~('\n' | '\r'))* ('\n' | '\r'('\n')?)
	  { $setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP); newline(); }
	;

/** multiple-line comments. */
ML_COMMENT
options {
  paraphrase = "multiple-line comments";
}
	: "/*"
	  ( /*
             * '\r' '\n' can be matched in one alternative or by matching
	     * '\r' in one iteration and '\n' in another.  I am trying to
	     * handle any flavor of newline that comes in, but the language
	     * that allows both "\r\n" and "\r" and "\n" to all be valid
	     * newline is ambiguous.  Consequently, the resulting grammar
	     * must be ambiguous.  I'm shutting this warning off.
	     */
	    options {
	      generateAmbigWarnings=false;
	    }
	    :  { LA(2) != '/' }? '*'
	      |	'\r' '\n' {newline();}
	      |	'\r'	  {newline();}
	      |	'\n'	  {newline();}
	      |	~('*'|'\n'|'\r')
	  )*
	  "*/"
	  { $setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP); }
	;

/** operators. */
QUESTION     options { paraphrase = "?"; }  : '?'  ;
LPAREN       options { paraphrase = "("; }  : '('  ;
RPAREN       options { paraphrase = ")"; }  : ')'  ;
LBRACK       options { paraphrase = "["; }  : '['  ;
RBRACK       options { paraphrase = "]"; }  : ']'  ;
//LCURLY       options { paraphrase = "{"; }  : '{'  ;
RCURLY       options { paraphrase = "}"; }  : '}'  ;
COLON        options { paraphrase = ":"; }  : ':'  ;
SCOPE        options { paraphrase = "::"; } : "::" ;
COMMA        options { paraphrase = ","; }  : ','  ;
DOT          options { paraphrase = "."; }  : '.'  ;
ASSIGN       options { paraphrase = "="; }  : '='  ;
EQUAL        options { paraphrase = "=="; } : "==" ;
LNOT         options { paraphrase = "!"; }  : '!'  ;
BNOT         options { paraphrase = "~"; }  : '~'  ;
NOT_EQUAL    options { paraphrase = "!="; } : "!=" ;
DIV          options { paraphrase = "/"; }  : '/'  ;
DIV_ASSIGN   options { paraphrase = "/="; } : "/=" ;
PLUS         options { paraphrase = "+"; }  : '+'  ;
PLUS_ASSIGN  options { paraphrase = "+="; } : "+=" ;
INC          options { paraphrase = "++"; } : "++" ;
MINUS        options { paraphrase = "-"; }  : '-'  ;
MINUS_ASSIGN options { paraphrase = "-="; } : "-=" ;
DEC          options { paraphrase = "--"; } : "--" ;
STAR         options { paraphrase = "*"; }  : '*'  ;
STAR_ASSIGN  options { paraphrase = "*="; } : "*=" ;
MOD          options { paraphrase = "%"; }  : '%'  ;
MOD_ASSIGN   options { paraphrase = "%="; } : "%=" ;
SR           options { paraphrase = ">>"; } : ">>" ;
//SR_ASSIGN options { paraphrase = ">>="; } : ">>=" ;
//BSR       options { paraphrase = ">>>"; } : ">>>" ;
//BSR_ASSIGN options { paraphrase = ">>>="; } : ">>>=" ;
GE           options { paraphrase = ">="; } : ">=" ;
GT           options { paraphrase = ">"; }  : ">"  ;
SL	     options { paraphrase = "<<"; } : "<<" ;
//SL_ASSIGN options { paraphrase = "<<="; } : "<<=" ;
LE	     options { paraphrase = "<="; } : "<=" ;
LT_	     options { paraphrase = "<"; }  : '<'  ;
BXOR	     options { paraphrase = "^"; }  : '^'  ;
BXOR_ASSIGN  options { paraphrase = "^="; } : "^=" ;
BOR	     options { paraphrase = "|"; }  : '|'  ;
BOR_ASSIGN   options { paraphrase = "|="; } : "|=" ;
LOR	     options { paraphrase = "||"; } : "||" ;
BAND	     options { paraphrase = "&"; }  : '&'  ;
BAND_ASSIGN  options { paraphrase = "&="; } : "&=" ;
LAND	     options { paraphrase = "&&"; } : "&&" ;
SEMI	     options { paraphrase = ";"; }  : ';'  ;

CHAR_LITERAL
options {
  paraphrase = "a character literal";
}
        : '\''! (ESCAPE | ~'\'') '\''!
        ;

/** string literals. */
STRING_LITERAL
options {
  paraphrase = "a string literal";
}
	: '"'! (ESCAPE | ~('"' | '\\'))* '"'!
	;

/** rope-string literals. */
ROPE_LITERAL
options {
  paraphrase = "a rope-string literal";
}
	: "[["! (ESCAPE | ~('[' | ']' | '\\'))* "]]"!
	;

IPv4ADDR_LITERAL
options {
  paraphrase = "IPv4 address or port literal";
}
/*
        : LT_!
          (
              PURE_INT
              (   '.' PURE_INT '.' PURE_INT '.' PURE_INT
                  (DIV PURE_INT '.' PURE_INT '.' PURE_INT '.' PURE_INT)?
                | DIV IP_PROTOCOL
                  { $setType(PPORT_LITERAL); }
              )
            | IDENTIFIER ('.' IDENTIFIER)*
          )
          GT!
 */
        :   ('{' (   (PURE_INT ('.' PURE_INT '.' | DIV IP_PROTOCOL))
                   | IDENTIFIER ('.' IDENTIFIER)?
                 )
            )=>
            ( '{'!
              (
                  PURE_INT
                  (   '.' PURE_INT '.' PURE_INT '.' PURE_INT (DIV PURE_INT)?
                    | DIV IP_PROTOCOL
                      { $setType(PPORT_LITERAL); }
                  )
                | IDENTIFIER ('.' IDENTIFIER)* (DIV PURE_INT)?
              )
              RCURLY!
            )
          | '{' { $setType(LCURLY); }
        ;

protected
IP_PROTOCOL
options {
  paraphrase = "IPv4 protocol type";
}
        : (('T' | 't') ('C' | 'c') ('P' | 'p')) | (('U' | 'u') ('D' | 'd') ('P' | 'p'))
        ;

protected
ESCAPE
options {
  paraphrase = "an escape sequence";
}
        : '\\'
	  (   'n'  { $setText('\n'); }
	    | 'r'  { $setText('\r'); }
	    | 't'  { $setText('\t'); }
	    | 'b'  { $setText('\b'); }
	    | 'f'  { $setText('\f'); }
	    | '"'  { $setText('"'); }
	    | '\'' { $setText('\''); }
	    | '\\' { $setText('\\'); }
            | '0'  { $setText('\0'); }
	    | '['  { $setText('['); }
	    | ']'  { $setText(']'); }
            | 'x' HEX_DIGIT
              /*
               *   Since a digit can occur in a string literal, and the following
               * HEX_DIGIT is optional, so the "mESCAPE()" method can be end or
               * can continue to "match" a HEX_DIGIT. But ANTLR does not know if
               * you want to match the digit here (greedy) or in string literal.
               *   If we want greedy, this can be solved by using
               * "warnWhenFollowAmbig = false" or "greedy = true" option.
               */
              ( options {
                  //warnWhenFollowAmbig = false;
                  greedy = true;
                }
                : HEX_DIGIT
                  {
                    //std::string stringText = $getText();
                    // ANTLR have a bug when translating '$getText()'
                    // -> std::string stringText = text.substr(_begin,text.length()-_begin)();
                    std::string stringText = text.substr(_begin,text.length()-_begin);
                    // skipping '\x'
                    stringText = stringText.substr(2);
                    u_char uch = (u_char)strtol(stringText.c_str(), (char **)0, 16);
                    $setText(std::string(1, uch));
                  }
              )?
          )
        ;

IDENTIFIER
options {
  testLiterals = true;
  paraphrase = "an identifier";
}
        : ('a'..'z' | 'A'..'Z' | '_')
          ('a'..'z' | 'A'..'Z' | '_' | DIGIT)*
        ;

protected
DIGIT
options {
  paraphrase = "a digit";
}
        : '0'..'9'
        ;

protected
PURE_INT
options {
  paraphrase = "a pure integer";
}
        : (DIGIT)+
        ;

protected
HEX_DIGIT
options {
  paraphrase = "a hexadecimal digit";
}
	: (DIGIT | 'A'..'F' | 'a'..'f')
	;

/** a hexadecimal numeric literal. */
NUM_HEX_INT
options {
  paraphrase = "a hexadecimal numeric value";
}
	: ("0x" | "0X") (HEX_DIGIT)+ (('L' | 'l') { $setType(NUM_HEX_QUAD); })?
	;

/** a numeric literal. */
NUM_INT
options {
  paraphrase = "an integer value";
}
        : (DIGIT)+   // base-10
          (   '.' (DIGIT)* { $setType(NUM_FLOAT); } (EXPONENT)?
            | EXPONENT { $setType(NUM_FLOAT); }
            | ('L' | 'l') { $setType(NUM_QUAD); }
          )?
	;

/** a float literal. */
NUM_FLOAT
options {
  paraphrase = "an floating point value";
}
	: '.' (DIGIT)+ (EXPONENT)?
     	;

/** a couple protected methods to assist in matching floating point numbers. */
protected
EXPONENT
	: ('e' | 'E') ('+' | '-')? (DIGIT)+
	;

/**
 * Deal with 'gnu cpp' line control.
 * @note 'gnu cpp' line control have the format :
 * <pre>
 *   # number "/usr/include/stdio.h" number [number]
 * </pre>
 */
CPP_LINE_CONTROL
options {
  paraphrase = "a cpp preprocessor line control";
}
        : '#'
          {
            int nColumnNumber = getColumn();  // Must be '2', then it means '#' is at line-head.
            //std::cout << "start column: " << nColumnNumber << std::endl;
          }
          (' ' | '\t')
          tLineNumber:PURE_INT
          {
            int nLineNumber = strtol(tLineNumber->getText().c_str(), (char **)0, 10);
            //std::cout << "cpp line: " << nLineNumber << std::endl;
            setLine(nLineNumber);
          }
          (' ' | '\t') '"'
          tIncludeFile:CPP_LINE_CONTROL_INCLUDE_FILE
          {
            //std::cout << "'cpp' include file: " << tIncludeFile->getText() << std::endl;
            std::string stringSwitchToFile = tIncludeFile->getText();
            if (stringSwitchToFile.size() == 0 || stringSwitchToFile == "<stdin>")
            // now return to 'compiled source file'
            {
              setFilename(_stringCompiledSourceFileName);
            }
            else
            // now switch to '#include file'
            {
              setFilename(stringSwitchToFile);
            }
          }
          '"' (~('\n' | '\r'))* ('\n' | '\r'('\n')?)
	  { $setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP); }
        ;

protected
CPP_LINE_CONTROL_INCLUDE_FILE
        : (~('\n' | '\r' | '"'))*
        ;

