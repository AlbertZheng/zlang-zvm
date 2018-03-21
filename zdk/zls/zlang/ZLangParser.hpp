#ifndef INC_ZLangParser_hpp_
#define INC_ZLangParser_hpp_

#include "antlr/config.hpp"
/* $ANTLR 2.7.1: "zlangpass1.g" -> "ZLangParser.hpp"$ */
#include "antlr/TokenStream.hpp"
#include "antlr/TokenBuffer.hpp"
#include "ZLangTokenTypes.hpp"
#include "antlr/LLkParser.hpp"

#line 1 "zlangpass1.g"

#include <antlr/CharScanner.hpp>
#include <zls/zlang/CZLangAST.hpp>

#line 17 "ZLangParser.hpp"
ANTLR_BEGIN_NAMESPACE(zlang)
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
class ZLangParser : public antlr::LLkParser, public ZLangTokenTypes
 {
#line 1 "zlangpass1.g"
#line 80 "ZLangParser.hpp"
protected:
  ZLangParser(antlr::TokenBuffer& tokenBuf, int k);
public:
  ZLangParser(antlr::TokenBuffer& tokenBuf);
protected:
  ZLangParser(antlr::TokenStream& lexer, int k);
public:
  ZLangParser(antlr::TokenStream& lexer);
  ZLangParser(const antlr::ParserSharedInputState& state);
  public: void zlangScript();
  public: void externGlobalDeclaration();
  public: void globalDefinition();
  public: void builtInType();
  public: void parameterDeclarationList();
  public: void codeBlock();
  public: void initializationConstant();
  public: void tableInit();
  public: void localVariableDefinition();
  public: void compoundStatement();
  public: void parameterDeclaration();
  public: void statement();
  public: void expression();
  public: void ifStatement();
  public: void whileStatement();
  public: void forStatement();
  public: void forExpression1();
  public: void forExpression2();
  public: void forExpression3();
  public: void assignExpression();
  public: void tableElementInit();
  public: void argumentList();
  public: void logicalOrExpression();
  public: void logicalAndExpression();
  public: void bitwiseOrExpression();
  public: void bitwiseXorExpression();
  public: void bitwiseAndExpression();
  public: void equalityExpression();
  public: void relationalExpression();
  public: void shiftExpression();
  public: void additiveExpression();
  public: void multiplicativeExpression();
  public: void unaryExpression();
  public: void postfixExpression();
  public: void primaryExpression();
  public: void constant();
public:
  zlang::CZLangAST_auto getAST();
  
protected:
  zlang::CZLangAST_auto returnAST;
private:
  static const char* _tokenNames[];
  
  static const unsigned long _tokenSet_0_data_[];
  static const antlr::BitSet _tokenSet_0;
  static const unsigned long _tokenSet_1_data_[];
  static const antlr::BitSet _tokenSet_1;
  static const unsigned long _tokenSet_2_data_[];
  static const antlr::BitSet _tokenSet_2;
  static const unsigned long _tokenSet_3_data_[];
  static const antlr::BitSet _tokenSet_3;
  static const unsigned long _tokenSet_4_data_[];
  static const antlr::BitSet _tokenSet_4;
  static const unsigned long _tokenSet_5_data_[];
  static const antlr::BitSet _tokenSet_5;
};

ANTLR_END_NAMESPACE
#endif /*INC_ZLangParser_hpp_*/
