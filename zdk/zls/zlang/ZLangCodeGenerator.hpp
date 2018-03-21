#ifndef INC_ZLangCodeGenerator_hpp_
#define INC_ZLangCodeGenerator_hpp_

#line 1 "zlangpass3.g"

#include <zls/zlang/SymbolTable.hpp>
#include <zls/zlang/ConstantPool.hpp>
#include <zls/zlang/CCodeGeneratorHelper.hpp>
#include <antlr/CommonAST.hpp>
#include <antlr/SemanticException.hpp>
#include <zls/zlang/CZLangAST.hpp>


#define __PREPARE_A_OPERATOR__(autoTreeRoot)     \
  { \
    zlang::CCodeGeneratorHelper::TExpressionAtom tOperator; \
    tOperator.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERATOR; \
    tOperator.nTokenType = autoTreeRoot->getType(); \
    tOperator.stringTokenText = autoTreeRoot->getText(); \
    antlr::RefToken & rautoToken = autoTreeRoot->getSavedToken(); \
    tOperator.nLineNumber = rautoToken->getLine(); \
    tOperator.nColumnNumber = rautoToken->getColumn(); \
    rdequeExpressionAtoms.push_back(tOperator); \
  }

#define __PREPARE_A_OPERAND__(autoTreeLeaf)      \
  { \
    zlang::CCodeGeneratorHelper::TExpressionAtom tOperand; \
    tOperand.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERAND; \
    tOperand.nTokenType = autoTreeLeaf->getType(); \
    tOperand.stringTokenText = autoTreeLeaf->getText(); \
    antlr::RefToken & rautoToken = autoTreeLeaf->getSavedToken(); \
    tOperand.nLineNumber = rautoToken->getLine(); \
    tOperand.nColumnNumber = rautoToken->getColumn(); \
    rdequeExpressionAtoms.push_back(tOperand); \
  }

#line 39 "ZLangCodeGenerator.hpp"
#include "antlr/config.hpp"
#include "ZLangCodeGeneratorTokenTypes.hpp"
/* $ANTLR 2.7.1: "zlangpass3.g" -> "ZLangCodeGenerator.hpp"$ */
#include "antlr/TreeParser.hpp"

ANTLR_BEGIN_NAMESPACE(zlang)
/**
 * <b>ZLang Compiler Pass3 Parser.</b>
 *
 * It will do semantic parsing and generating byte codes.
 *
 * <pre>
 * @version 0.4,   2001/01/09
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
 * @version 0.4.5, 2001/02/13
 *   (1) some rules changed;
 *   (2) semantic parsing and generating codes had completed.
 * @version 0.5, 2001/04/01
 *   (1) Zlang grammar was redesigned:
 *       (a) 'machine','method','environment','state' were discarded;
 *       (b) 'static' was introduced into and 'global' was discarded.
 * @version 0.5.2, 2001/05/10
 *   (1) rule 'expressionDefinition' and 'postfixExpression' modified for
 *       supporting 'nested assign'.
 * @version 0.5.3, 2001/06/5
 *   (1) ZVM instructions are redesigned, so the code generator need some modifiy.
 * @version 0.5.6, 2001/06/23
 *   (1) Supporting "SQWORD", "UQWORD".
 * @version 0.6.0, 2001/06/26
 *   (1) 'Expression statement' checking added.
 *   (2) 'Local variables initializing byte codes' generated into a temp container,
 *       then patched to the generated function.
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
 * @version 1.2.1, 2001/7/21
 *   (1) Automatic generating 'string','ipaddress','pport','table' temp variable
 *       now supported. This feature is important, so such as the following expressions
 *       will be correct(Note: In the old version, I use a single object register to
 *       save the result of 'string plus' or 'function result'. This is a big bug):
 *           string s8 = ((s1 + s2) + (s3 + s4)) + (s5 + s6);
 *           bool b = ReturnPPortFunction() != ReturnPPortFunction();
 * </pre>
 *
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/zlangpass3.g,v $
 *
 * $Date: 2001/08/10 18:34:36 $
 *
 * $Revision: 1.3 $
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
class ZLangCodeGenerator : public antlr::TreeParser, public ZLangCodeGeneratorTokenTypes
 {
#line 135 "zlangpass3.g"

private:
  enum TCodeLabelTag {
    LABEL_END_OF_THEN = 0,
    LABEL_END_OF_IF,
    LABEL_BEGIN_OF_LOOP_TEST,
    LABEL_END_OF_LOOP
  };

  struct TBackPatchPosition {
    zvm::TZVMIndex nInstructionIndex;
    TCodeLabelTag    eLabelTag;

    TBackPatchPosition()
     : nInstructionIndex(0),
       eLabelTag(LABEL_END_OF_THEN)
    { }

    TBackPatchPosition(zvm::TZVMIndex nIndex, TCodeLabelTag eTag)
     : nInstructionIndex(nIndex),
       eLabelTag(eTag)
    { }
  };

  /**
   * Generating byte codes for a valid expression statement.
   */
  void GenerateExpressionStatement(
    zlang::CInstructionContainer_auto & rautoIntoFunction,
    std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms)
  {
    zlang::CCodeGeneratorHelper::TExpressionAtom tAtom = rdequeExpressionAtoms.front();  // Not removed
    int nOperatorType = tAtom.nTokenType;
    if (nOperatorType != ZLangCodeGeneratorTokenTypes::ASSIGN &&
        nOperatorType != ZLangCodeGeneratorTokenTypes::NESTED_ASSIGN &&
        nOperatorType != ZLangCodeGeneratorTokenTypes::INC &&
        nOperatorType != ZLangCodeGeneratorTokenTypes::DEC &&
        nOperatorType != ZLangCodeGeneratorTokenTypes::POST_INC &&
        nOperatorType != ZLangCodeGeneratorTokenTypes::POST_DEC &&
        nOperatorType != ZLangCodeGeneratorTokenTypes::CALLING)
    {
      _ciCodeGeneratorHelper.ThrowSemanticError_InvalidExpressionStatement(tAtom.nLineNumber, tAtom.nColumnNumber);
    }

    std::string stringResultSignature =
        _ciCodeGeneratorHelper.GenerateExpressionInstruction(rautoIntoFunction,
                                                             _vectorFindNames,
                                                             rdequeExpressionAtoms);

    // May remove unused result-operand to balance ZVM stack
    switch (nOperatorType)
    {
      case ZLangCodeGeneratorTokenTypes::NESTED_ASSIGN:
      case ZLangCodeGeneratorTokenTypes::INC:
      case ZLangCodeGeneratorTokenTypes::DEC:
      case ZLangCodeGeneratorTokenTypes::POST_INC:
      case ZLangCodeGeneratorTokenTypes::POST_DEC:
        _ciCodeGeneratorHelper.GenerateInstruction(rautoIntoFunction,
                                                   tAtom.nLineNumber,
                                                   zvm::ZVM_popAny);
        break;

      case ZLangCodeGeneratorTokenTypes::CALLING:
        if (stringResultSignature != zvm::CstringZVM_VOID_SIGNATURE)
        {
          // We need not destruct the memory if the slot is a
          // string(table, ipv4address, pport)-object, because
          // 'convertValueToAddress' will let the ZVM object
          // register reference to the memory, then ZVM will
          // automatic free the memory when need.
          _ciCodeGeneratorHelper.GenerateInstruction(rautoIntoFunction,
                                                     tAtom.nLineNumber,
                                                     zvm::ZVM_popAny);
        }
        break;

      default:
        break;
    }
  }

  /**
   * Generating byte codes for a valid testing expression statement.
   */
  std::string GenerateTestingExpressionStatement(
    zlang::CInstructionContainer_auto & rautoIntoFunction,
    std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms)
  {
    zlang::CCodeGeneratorHelper::TExpressionAtom tAtom = rdequeExpressionAtoms.front();  // Not removed

    std::string stringResultSignature =
        _ciCodeGeneratorHelper.GenerateExpressionInstruction(rautoIntoFunction,
                                                             _vectorFindNames,
                                                             rdequeExpressionAtoms);

    if (stringResultSignature == zvm::CstringZVM_VOID_SIGNATURE)
    {
      // Testing expression statement must have a non-void result !
      _ciCodeGeneratorHelper.ThrowSemanticError_InvalidTestingExpressionStatement(tAtom.nLineNumber, tAtom.nColumnNumber);
    }

    return stringResultSignature;
  }

  /**
   * Fix local variable initializing instruction sequence.
   */
  void FixLocalVariablesInitializeInstructionSequence(
    CInstructionContainer_auto  & rautoLocalVariablesInitializeSequence,
    UWORD uwLocalVariableCount)
  {
    rautoLocalVariablesInitializeSequence->SmartFixTempLocalVariableOffset(uwLocalVariableCount);
  }

protected:
  std::string _stringSourceFileName;
  zlang::CSymbolTable * _pciSymbolTable;

  /**
   * Byte codes generator helper.
   * 'class ZLangCodeGenerator' will driving it to generate byte codes.
   */
  zlang::CCodeGeneratorHelper _ciCodeGeneratorHelper;

  /** Codes generating period working variables. */
  std::vector<std::string> _vectorFindNames;
  zlang::CInstructionContainer_auto _autoInitializerFunction;  // for internal global variables initialization.
  zlang::CInstructionContainer_auto _autoCurrentFunction;
  zlang::CInstructionContainer_auto _autoCurrentLocalVariablesInitializeSequence;  // 2001/6/26: Added
  std::string _stringCurrentFunctionReturnSignature;  // for testing 'return'.
  std::string _stringCurrentFunctionName;  // for generating 'result argument' and report error.
  int _nFunctionDefinitionBeginLineNumber;  // saving function definition begin line number.
  bool _bHaveReturnStatement;  // testing for whether 'return' is appeared.

public:
  ZLangCodeGenerator(const std::string & rstringSourceFileName,
                     zlang::CSymbolTable * pciSymbolTable)
    : _stringSourceFileName(rstringSourceFileName),
      _pciSymbolTable(pciSymbolTable),
      _ciCodeGeneratorHelper(rstringSourceFileName, pciSymbolTable),
      _nFunctionDefinitionBeginLineNumber(0),
      antlr::TreeParser()
  {
    setTokenNames(_tokenNames);
  }

  void DumpDetail() const
  {
    _ciCodeGeneratorHelper.DumpDetail();
  }

  friend zfc::CBinaryOutputFileStream & operator << (zfc::CBinaryOutputFileStream & bos,
                                                     const ZLangCodeGenerator & rciGenerator)
  {
    return (bos << rciGenerator._ciCodeGeneratorHelper);
  }
#line 120 "ZLangCodeGenerator.hpp"
public:
  ZLangCodeGenerator();
  public: void zlangScript(zlang::CZLangAST_auto _t);
  public: void externGlobalFunctionDeclaration(zlang::CZLangAST_auto _t);
  public: void externGlobalVariableDeclaration(zlang::CZLangAST_auto _t);
  public: void globalVariableDefinition(zlang::CZLangAST_auto _t);
  public: void globalFunctionDefinition(zlang::CZLangAST_auto _t);
  public: void builtInType(zlang::CZLangAST_auto _t,
    std::string & rstringType
  );
  public: void externParameterDeclarationList(zlang::CZLangAST_auto _t,
    std::string & rstringParametersSignature
  );
  public: void externParameterDeclaration(zlang::CZLangAST_auto _t,
    std::string & rstringParametersSignature
  );
  public: void parameterDeclarationList(zlang::CZLangAST_auto _t,
    std::string & rstringParametersSignature,
                          std::vector<std::pair<std::string, std::string> > & rvectorParameters
  );
  public: void codeBlock(zlang::CZLangAST_auto _t);
  public: void parameterDeclaration(zlang::CZLangAST_auto _t,
    std::string & rstringParametersSignature,
                      std::pair<std::string, std::string> & rpairParameters
  );
  public: void initializationConstant(zlang::CZLangAST_auto _t,
    std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
  );
  public: void globalTableDefinition(zlang::CZLangAST_auto _t,
    std::string & rstringTableName,
                       int & rnLineNumber,
                       int & rnColumnNumber,
                       bool bIsStatic
  );
  public: void globalTableInit(zlang::CZLangAST_auto _t,
    std::string & rstringTableName, int nLineNumber, int nColumnNumber
  );
  public: void localVariableDefinition(zlang::CZLangAST_auto _t,
    int & rnIndex
  );
  public: void compoundStatement(zlang::CZLangAST_auto _t,
    std::stack<TBackPatchPosition> & rstackOuterBackPatchPositions
  );
  public: void statement(zlang::CZLangAST_auto _t,
    std::stack<TBackPatchPosition> & rstackOuterBackPatchPositions
  );
  public: void expression(zlang::CZLangAST_auto _t,
    std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
  );
  public: void ifStatement(zlang::CZLangAST_auto _t,
    std::stack<TBackPatchPosition> & rstackOuterBackPatchPositions
  );
  public: void whileStatement(zlang::CZLangAST_auto _t,
    std::stack<TBackPatchPosition> & rstackOuterBackPatchPositions
  );
  public: void forStatement(zlang::CZLangAST_auto _t,
    std::stack<TBackPatchPosition> & rstackOuterBackPatchPositions
  );
  public: void forExpression1(zlang::CZLangAST_auto _t,
    std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
  );
  public: void forExpression2(zlang::CZLangAST_auto _t,
    std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
  );
  public: void forExpression3(zlang::CZLangAST_auto _t,
    std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
  );
  public: void expressionDefinition(zlang::CZLangAST_auto _t,
    std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
  );
  public: void localTableDefinition(zlang::CZLangAST_auto _t,
    std::string & rstringTableName,
                      std::string & rstringTableSignature,
                      int & rnLineNumber,
                      int & rnColumnNumber,
                      bool & rbIsReferenceVariable,
                      int nVariableIndex
  );
  public: void localTableInit(zlang::CZLangAST_auto _t,
    std::string & rstringTableName,
                int nLineNumber,
                int nColumnNumber
  );
  public: void argumentList(zlang::CZLangAST_auto _t,
    std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
  );
  public: void postfixExpression(zlang::CZLangAST_auto _t,
    std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
  );
  public: void primaryExpression(zlang::CZLangAST_auto _t,
    std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
  );
  public: void constant(zlang::CZLangAST_auto _t,
    std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
  );
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
#endif /*INC_ZLangCodeGenerator_hpp_*/
