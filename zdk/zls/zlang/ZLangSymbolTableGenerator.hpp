#ifndef INC_ZLangSymbolTableGenerator_hpp_
#define INC_ZLangSymbolTableGenerator_hpp_

#line 1 "zlangpass2.g"

#include <zls/zlang/SymbolTable.hpp>
#include <zls/zlang/CZLangAST.hpp>
#include <antlr/CommonAST.hpp>
#include <antlr/SemanticException.hpp>


#define __INSERT_SYMBOL__(autoName)        \
  antlr::RefToken & autoToken = autoName->getSavedToken(); \
  int nLineNumber = autoToken->getLine(); \
  int nColumnNumber = autoToken->getColumn(); \
  try { \
    const zlang::CSymbol_auto & rautoSymbol = _ciSymbolTable.InsertSymbol(_vectorFindNames, pciAttributes); \
  } \
  catch (zlang::ESymbolInsertFailure & e) \
  { \
    std::string stringError = e.what(); \
    throw antlr::SemanticException(stringError, _stringFileName, nLineNumber); \
  }


#line 27 "ZLangSymbolTableGenerator.hpp"
#include "antlr/config.hpp"
#include "ZLangSymbolTableGeneratorTokenTypes.hpp"
/* $ANTLR 2.7.1: "zlangpass2.g" -> "ZLangSymbolTableGenerator.hpp"$ */
#include "antlr/TreeParser.hpp"

ANTLR_BEGIN_NAMESPACE(zlang)
/**
 * <b>ZLang Compiler Pass2 Parser.</b>
 *
 * It will do simple semantic parsing and generating symbol table.
 *
 * <pre>
 * @version 0.1,   2000/12/19
 * @version 0.2,   2000/12/20
 * @version 0.3,   2000/12/23
 * @version 0.4,   2001/01/09
 * @version 0.4.1, 2001/01/21
 * @version 0.4.2, 2001/01/30
 *   (1) 'IPv4_LITERAL' renamed to 'IPv4ADDR_LITERAL';
 *   (2) 'PORT_LITERAL' renamed to 'PPORT_LITERAL';
 *   (3) 'builtInType' rule definition changed;
 * @version 0.4.3, 2001/01/31
 *   (1) "void" only can appear at function/method return declaration;
 * @version 0.4.4, 2001/02/05
 *   (1) The missing option of '?VariableInit' in rule 'globalVariableDefinition'
 *       and 'localVariableDefinition' are patched;
 *   (2) 'parameterDeclarationList' and 'parameterDeclaration' rule definition changed;
 *   (3) rule 'tableDefinition' renamed to 'tableDefinitionAndMayInit';
 * @version 0.5, 2001/04/01
 *   (1) Zlang grammar was redesigned:
 *       (a) 'machine','method','environment','state' were discarded;
 *       (b) 'static' was introduced into and 'global' was discarded.
 * @version 0.5.2, 2001/05/10
 *   (1) rule 'expressionDefinition' and 'postfixExpression' modified for
 *       supporting 'nested assign'.
 * @version 0.5.3, 2001/06/23
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
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/zlangpass2.g,v $
 *
 * $Date: 2001/11/14 19:03:09 $
 *
 * $Revision: 1.4 $
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
class ZLangSymbolTableGenerator : public antlr::TreeParser, public ZLangSymbolTableGeneratorTokenTypes
 {
#line 97 "zlangpass2.g"

private:
  std::string _stringFileName;
  zlang::CSymbolTable _ciSymbolTable;
  std::vector<std::string> _vectorFindNames;

public:
  ZLangSymbolTableGenerator(const std::string & stringFileName)
    : _stringFileName(stringFileName)
  {
    ZLangSymbolTableGenerator();
  }

  zlang::CSymbolTable & GetSymbolTable()
  {
    return(_ciSymbolTable);
  }

#line 96 "ZLangSymbolTableGenerator.hpp"
public:
  ZLangSymbolTableGenerator();
  public: void zlangScript(zlang::CZLangAST_auto _t);
  public: void externGlobalFunctionDeclaration(zlang::CZLangAST_auto _t);
  public: void externGlobalVariableDeclaration(zlang::CZLangAST_auto _t);
  public: void globalVariableDefinition(zlang::CZLangAST_auto _t);
  public: void globalFunctionDefinition(zlang::CZLangAST_auto _t);
  public: void builtInType(zlang::CZLangAST_auto _t,
    std::string & rstringSignature
  );
  public: void externParameterDeclarationList(zlang::CZLangAST_auto _t,
    std::string & rstringParametersSignature
  );
  public: void externParameterDeclaration(zlang::CZLangAST_auto _t,
    std::string & rstringParametersSignature
  );
  public: void parameterDeclarationList(zlang::CZLangAST_auto _t,
    int & rnParameterIndex, std::string & rstringParametersSignature
  );
  public: void codeBlock(zlang::CZLangAST_auto _t);
  public: void initializationConstant(zlang::CZLangAST_auto _t);
  public: void tableInit(zlang::CZLangAST_auto _t);
  public: void localVariableDefinition(zlang::CZLangAST_auto _t,
    int & rnIndex
  );
  public: void compoundStatement(zlang::CZLangAST_auto _t);
  public: void parameterDeclaration(zlang::CZLangAST_auto _t,
    int & rnIndex,
                      std::string & rstringParametersSignature,
                      std::vector<zlang::CParameterSymbolAttributes *> & rvectorOfPSymbolAttributes
  );
  public: void statement(zlang::CZLangAST_auto _t);
  public: void expression(zlang::CZLangAST_auto _t);
  public: void ifStatement(zlang::CZLangAST_auto _t);
  public: void whileStatement(zlang::CZLangAST_auto _t);
  public: void forStatement(zlang::CZLangAST_auto _t);
  public: void forExpression1(zlang::CZLangAST_auto _t);
  public: void forExpression2(zlang::CZLangAST_auto _t);
  public: void forExpression3(zlang::CZLangAST_auto _t);
  public: void expressionDefinition(zlang::CZLangAST_auto _t);
  public: void argumentList(zlang::CZLangAST_auto _t);
  public: void postfixExpression(zlang::CZLangAST_auto _t);
  public: void primaryExpression(zlang::CZLangAST_auto _t);
  public: void constant(zlang::CZLangAST_auto _t);
public:
  zlang::CZLangAST_auto getAST();
  
protected:
  zlang::CZLangAST_auto returnAST;
  zlang::CZLangAST_auto _retTree;
private:
  static const char* _tokenNames[];
  
  static const unsigned long _tokenSet_0_data_[];
  static const antlr::BitSet _tokenSet_0;
};

ANTLR_END_NAMESPACE
#endif /*INC_ZLangSymbolTableGenerator_hpp_*/
