header "pre_include_hpp" {
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
}


options {
  language = "Cpp";
  namespace = "zlang";
  namespaceStd = "std::";
  namespaceAntlr = "antlr::";
}

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
class ZLangCodeGenerator extends TreeParser;
options {
  importVocab = ZLang;
  ASTLabelType = "zlang::CZLangAST_auto";
  defaultErrorHandler = false;
}

tokens {
  CAST_LITERAL; PASS_A_ARGUMENT; ARGUMENTS_END; SUBSCRIPT_ADDRESS;
  // 2001/5/10: Adding "NESTED_ASSIGN"
  NESTED_ASSIGN;
  // 2001/5/15: Adding "IDENTIFIER_ADDRESS"
  //IDENTIFIER_ADDRESS;
  //< 2001/6/3: Discarded
  // 2001/6/1: Adding "ADVANCE_CAST"
  ADVANCE_CAST;
  REFERENCE_ADDRESS_ASSIGN;
  RETURN_PSEUDO_ASSIGN;
}

{
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
}


/** ZLang script starting. */
zlangScript
        : {//-------------------------------------------------------------------
            std::vector<std::pair<std::string, std::string> > vectorParameters;

            // Creating a pseudo static global function for my global variables's initializtion.
            _autoInitializerFunction = _autoCurrentFunction =
                                       new __OPTION(_THROW) zlang::CZLangFunction();
            std::string stringFunctionSignature = "()" + zvm::CstringZVM_VOID_SIGNATURE;
            std::string stringFunctionName = zvm::CstringInitializerFunctionName;
            _ciCodeGeneratorHelper.PrepareGlobalFunctionFramework(
                                                          _autoInitializerFunction,
                                                          0,
                                                          _vectorFindNames,
                                                          stringFunctionName,
                                                          stringFunctionSignature,
                                                          vectorParameters,
                                                          zvm::PRIVATE_FOR_SELF_MODULE);
          }//-------------------------------------------------------------------

          (   externGlobalFunctionDeclaration
            | externGlobalVariableDeclaration
            | globalVariableDefinition
            | globalFunctionDefinition
          )*

          {//-------------------------------------------------------------------
            // Generate 'ret' for this pseudo static global function.
            _ciCodeGeneratorHelper.GenerateInstruction(_autoInitializerFunction,
                                                       0,
                                                       zvm::ZVM_ret);
          }//-------------------------------------------------------------------
        ;

externGlobalFunctionDeclaration
        : #(EXTERN_GFUNCTION_DECLARATION
            {//---------------------------------------------------------------
              std::string stringFunctionSignature = "(";
              std::string stringResultSignature;
              bool bIsTable = false;
              bool bIsReturnReference = false;
            }//---------------------------------------------------------------
            #(autoName:IDENTIFIER
              (   ("table" {bIsTable = true;})? builtInType[stringResultSignature] (BAND {bIsReturnReference = true;})?
                  {//-----------------------------------------------------------
                    if (bIsTable)
                    {
                      stringResultSignature = zvm::CstringZVM_TABLE_PREFIX_SIGNATURE + stringResultSignature;
                    }
                    if (bIsReturnReference)
                    {
                      // Turn signature to lower char
                      zfc::LowerString(stringResultSignature);
                    }
                  }//-----------------------------------------------------------
                | "void"
                  {//-----------------------------------------------------------
                    stringResultSignature = zvm::CstringZVM_VOID_SIGNATURE;
                  }//-----------------------------------------------------------
              )
              (externParameterDeclarationList[stringFunctionSignature])?
              {//---------------------------------------------------------------
                stringFunctionSignature += ")";
                stringFunctionSignature += stringResultSignature;
              }//---------------------------------------------------------------
            )
          )
          {//-------------------------------------------------------------------
            zlang::CConstantPool & rciConstantPool = _ciCodeGeneratorHelper.GetConstantPool();
            /* insert extern global-function-reference */
            rciConstantPool.InsertGlobalFunctionReference(autoName->getText(),
                                                          stringFunctionSignature,
                                                          zvm::PUBLIC_BY_EXTERN_MODULE);
          }//-------------------------------------------------------------------
        ;

externParameterDeclarationList [std::string & rstringParametersSignature]
        : #(PARAMETERS_DECLARATION
            (externParameterDeclaration[rstringParametersSignature])+
          )
        ;

externParameterDeclaration [std::string & rstringParametersSignature]
        : {//-------------------------------------------------------------------
            std::string stringTypeSignature;
            std::string stringName;
            bool bIsTable = false;
            bool bIsReferenceArgument = false;
          }//-------------------------------------------------------------------

          #(autoName:IDENTIFIER
            ("table" {bIsTable = true;})? builtInType[stringTypeSignature] (BAND {bIsReferenceArgument = true;})?
          )
          {//-------------------------------------------------------------------
            stringName = autoName->getText();
            if (bIsTable)
            {
              stringTypeSignature = zvm::CstringZVM_TABLE_PREFIX_SIGNATURE + stringTypeSignature;
            }
            if (bIsReferenceArgument)
            {
              // Turn signature to lower char
              zfc::LowerString(stringTypeSignature);
            }
            rstringParametersSignature += stringTypeSignature;
          }//-------------------------------------------------------------------
        ;

externGlobalVariableDeclaration
        : #(EXTERN_GVARIABLE_DECLARATION
            (   {//-------------------------------------------------------------
                  std::string stringVariableSignature;
                }//-------------------------------------------------------------
                builtInType[stringVariableSignature]
                (autoName:IDENTIFIER
                 {//------------------------------------------------------------
                  zlang::CConstantPool & rciConstantPool = _ciCodeGeneratorHelper.GetConstantPool();
                  /* insert extern global-variable-reference */
                  rciConstantPool.InsertGlobalVariableReference(autoName->getText(),
                                                                stringVariableSignature,
                                                                zvm::PUBLIC_BY_EXTERN_MODULE);
                 }//------------------------------------------------------------
                )+

              | {//-------------------------------------------------------------
                  std::string stringElementSignature;
                }//-------------------------------------------------------------
                "table" builtInType[stringElementSignature]
                (autoTableName:IDENTIFIER
                 {//------------------------------------------------------------
                   std::string stringTableSignature = zvm::CstringZVM_TABLE_PREFIX_SIGNATURE + stringElementSignature;
                   zlang::CConstantPool & rciConstantPool = _ciCodeGeneratorHelper.GetConstantPool();
                   /* insert extern global-variable-reference */
                   rciConstantPool.InsertGlobalVariableReference(autoTableName->getText(),
                                                                 stringTableSignature,
                                                                 zvm::PUBLIC_BY_EXTERN_MODULE);
                 }//------------------------------------------------------------
                )+
            )
          )
        ;

globalFunctionDefinition
        : #(GFUNCTION_DEFINITION
            {//-----------------------------------------------------------------
              bool bIsStatic = false;
            }//-----------------------------------------------------------------
            ("static" {bIsStatic = true;})?
            #(autoName:IDENTIFIER
              {//---------------------------------------------------------------
                std::string stringFunctionName = autoName->getText();
                _vectorFindNames.push_back(stringFunctionName);

                std::string stringResultSignature;
                std::string stringFunctionSignature = "(";
                std::vector<std::pair<std::string, std::string> > vectorParameters;
                bool bIsTable = false;
                bool bIsReturnReference = false;
              }//---------------------------------------------------------------

              (   ("table" {bIsTable = true;})? builtInType[stringResultSignature] (BAND {bIsReturnReference = true;})?
                  {//-----------------------------------------------------------
                    if (bIsTable)
                    {
                      stringResultSignature = zvm::CstringZVM_TABLE_PREFIX_SIGNATURE + stringResultSignature;
                    }
                    if (bIsReturnReference)
                    {
                      // Turn signature to lower char
                      zfc::LowerString(stringResultSignature);
                    }
                  }//-----------------------------------------------------------
                | "void"
                  {//-----------------------------------------------------------
                    stringResultSignature = zvm::CstringZVM_VOID_SIGNATURE;
                  }//-----------------------------------------------------------
              )
              {//---------------------------------------------------------------
                if (stringResultSignature != zvm::CstringZVM_VOID_SIGNATURE)
                /* Need a pseudo parameter for function return */
                {
                  std::pair<std::string, std::string> pairReturnParameter;
                  pairReturnParameter.first = stringFunctionName;
                  pairReturnParameter.second = stringResultSignature;
                  vectorParameters.push_back(pairReturnParameter);
                }
              }//---------------------------------------------------------------

              (parameterDeclarationList[stringFunctionSignature, vectorParameters])?
              {//---------------------------------------------------------------
                stringFunctionSignature += ")";
                stringFunctionSignature += stringResultSignature;

                antlr::RefToken & rautoToken = autoName->getSavedToken();
                int nLineNumberDebug = _nFunctionDefinitionBeginLineNumber = rautoToken->getLine();

                _autoCurrentFunction = new __OPTION(_THROW) zlang::CZLangFunction();
                //> 2001/6/26: Added
                _autoCurrentLocalVariablesInitializeSequence =
                      new __OPTION(_THROW) zlang::CInstructionSequence(_autoCurrentFunction.get());
                _stringCurrentFunctionReturnSignature = stringResultSignature;
                _stringCurrentFunctionName = stringFunctionName;

                if (bIsStatic)
                {
                  _ciCodeGeneratorHelper.PrepareGlobalFunctionFramework(
                                                                _autoCurrentFunction,
                                                                nLineNumberDebug,
                                                                _vectorFindNames,
                                                                stringFunctionName,
                                                                stringFunctionSignature,
                                                                vectorParameters,
                                                                zvm::PRIVATE_FOR_SELF_MODULE);
                }
                else
                {
                  _ciCodeGeneratorHelper.PrepareGlobalFunctionFramework(
                                                                _autoCurrentFunction,
                                                                nLineNumberDebug,
                                                                _vectorFindNames,
                                                                stringFunctionName,
                                                                stringFunctionSignature,
                                                                vectorParameters,
                                                                zvm::PUBLIC_BY_SELF_MODULE);
                }

                _bHaveReturnStatement = false;
              }//---------------------------------------------------------------

              codeBlock
              {//---------------------------------------------------------------
                // Hack: Automatically generating a tail's 'return' for imposing
                // 'uJump' and 'fJump' can be more safety when 'if-then-else' or
                // 'while' is the lastest statement of a function.
                _ciCodeGeneratorHelper.GenerateInstruction(_autoCurrentFunction,
                                                           0,
                                                           zvm::ZVM_ret);

                _vectorFindNames.pop_back();
              }//---------------------------------------------------------------
            )
          )
        ;

parameterDeclarationList [std::string & rstringParametersSignature,
                          std::vector<std::pair<std::string, std::string> > & rvectorParameters]
        : #(PARAMETERS_DECLARATION
            {//-----------------------------------------------------------------
              std::pair<std::string, std::string> pairParameter;
            }//-----------------------------------------------------------------

            (parameterDeclaration[rstringParametersSignature, pairParameter]
             {//-----------------------------------------------------------------
               rvectorParameters.push_back(pairParameter);
             }//-----------------------------------------------------------------
            )+
          )
        ;

parameterDeclaration [std::string & rstringParametersSignature,
                      std::pair<std::string, std::string> & rpairParameters]
        : {//-------------------------------------------------------------------
            std::string stringTypeSignature;
            std::string stringName;
            bool bIsTable = false;
            bool bIsReferenceArgument = false;
          }//-------------------------------------------------------------------

          #(autoName:IDENTIFIER
            ("table" {bIsTable = true;})? builtInType[stringTypeSignature] (BAND {bIsReferenceArgument = true;})?
          )
          {//-------------------------------------------------------------------
            stringName = autoName->getText();
            if (bIsTable)
            {
              stringTypeSignature = zvm::CstringZVM_TABLE_PREFIX_SIGNATURE + stringTypeSignature;
            }
            if (bIsReferenceArgument)
            {
              // Turn signature to lower char
              zfc::LowerString(stringTypeSignature);
            }
            rstringParametersSignature += stringTypeSignature;

            rpairParameters.first = stringName;
            rpairParameters.second = stringTypeSignature;
          }//-------------------------------------------------------------------
        ;

globalVariableDefinition
        : #(GVARIABLE_DEFINITION
            {//-----------------------------------------------------------------
              bool bIsStatic = false;
            }//-----------------------------------------------------------------
            ("static" {bIsStatic = true;})?
            (   {//-------------------------------------------------------------
                  std::string stringVariableName;
                  std::string stringVariableSignature;
                }//-------------------------------------------------------------
                builtInType[stringVariableSignature]
                (#(autoName:IDENTIFIER
                   {//----------------------------------------------------------
                     antlr::RefToken & rautoToken = autoName->getSavedToken();
                     int nLineNumber = rautoToken->getLine();
                     int nColumnNumber = rautoToken->getColumn();
                     stringVariableName = autoName->getText();
                     _vectorFindNames.push_back(stringVariableName);

                     zlang::CConstantPool & rciConstantPool = _ciCodeGeneratorHelper.GetConstantPool();
                     if (bIsStatic)
                     {
                       rciConstantPool.InsertGlobalVariableReference(stringVariableName,
                                                                     stringVariableSignature,
                                                                     zvm::PRIVATE_FOR_SELF_MODULE);
                     }
                     else
                     {
                       rciConstantPool.InsertGlobalVariableReference(stringVariableName,
                                                                     stringVariableSignature,
                                                                     zvm::PUBLIC_BY_SELF_MODULE);
                     }

                     _vectorFindNames.pop_back();
                     // Now name space is in "::"
                   }//----------------------------------------------------------

                   (
                    {//---------------------------------------------------------
                     std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> dequeExpressionAtoms;

                     /*
                      * Faking a ASSIGN operation.
                      */
                     /* borrow from macro __PREPARE_A_OPERATOR__ */
                     zlang::CCodeGeneratorHelper::TExpressionAtom tOperator;
                     tOperator.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERATOR;
                     tOperator.nTokenType = ZLangCodeGeneratorTokenTypes::ASSIGN;
                     tOperator.stringTokenText = "=";
                     tOperator.nLineNumber = nLineNumber;
                     tOperator.nColumnNumber = nColumnNumber;
                     dequeExpressionAtoms.push_back(tOperator);

                     /*
                      * Faking a left operand of that ASSIGN operation.
                      */
                     /* borrow from macro __PREPARE_A_OPERAND__ */
                     zlang::CCodeGeneratorHelper::TExpressionAtom tOperand;
                     tOperand.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERAND;
                     tOperand.nTokenType = ZLangCodeGeneratorTokenTypes::IDENTIFIER;
                     tOperand.stringTokenText = stringVariableName;
                     tOperand.nLineNumber = nLineNumber;
                     tOperand.nColumnNumber = nColumnNumber;
                     dequeExpressionAtoms.push_back(tOperand);
                    }//---------------------------------------------------------

                    initializationConstant[dequeExpressionAtoms]
                    {//---------------------------------------------------------
                      /* generating global variables's initializing codes into "__initializer__()" */
                      _ciCodeGeneratorHelper.GenerateExpressionInstruction(_autoInitializerFunction,
                                                                           _vectorFindNames,
                                                                           dequeExpressionAtoms);
                    }//---------------------------------------------------------
                   )?
                 )
                )+

              | {//-------------------------------------------------------------
                  std::string stringTableName;
                  int nLineNumber;
                  int nColumnNumber;
                }//-------------------------------------------------------------
                globalTableDefinition[stringTableName, nLineNumber, nColumnNumber, bIsStatic]
                // Now name space is in "::"
                (globalTableInit[stringTableName, nLineNumber, nColumnNumber])?
            )
          )
        ;

globalTableDefinition [std::string & rstringTableName,
                       int & rnLineNumber,
                       int & rnColumnNumber,
                       bool bIsStatic]
        : {//-------------------------------------------------------------------
            std::string stringTableSignature;
            std::string stringElementSignature;
          }//-------------------------------------------------------------------

          "table" builtInType[stringElementSignature] autoName:IDENTIFIER
          {//-------------------------------------------------------------------
            rstringTableName = autoName->getText();
            _vectorFindNames.push_back(rstringTableName);

            antlr::RefToken & autoToken = autoName->getSavedToken();
            int nLineNumber = rnLineNumber = autoToken->getLine();
            int nColumnNumber = rnColumnNumber = autoToken->getColumn();
            stringTableSignature = zvm::CstringZVM_TABLE_PREFIX_SIGNATURE + stringElementSignature;

            zlang::CConstantPool & rciConstantPool = _ciCodeGeneratorHelper.GetConstantPool();
            if (bIsStatic)
            {
              rciConstantPool.InsertGlobalVariableReference(rstringTableName,
                                                            stringTableSignature,
                                                            zvm::PRIVATE_FOR_SELF_MODULE);
            }
            else
            {
              rciConstantPool.InsertGlobalVariableReference(rstringTableName,
                                                            stringTableSignature,
                                                            zvm::PUBLIC_BY_SELF_MODULE);
            }

            _vectorFindNames.pop_back();
          }//-------------------------------------------------------------------
        ;

globalTableInit [std::string & rstringTableName, int nLineNumber, int nColumnNumber]
        : (#(ELEMENT_INIT
             {//----------------------------------------------------------------
               std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> dequeExpressionAtoms;

               /*
                * Faking a ASSIGN operation.
                */
               /* borrow from macro __PREPARE_A_OPERATOR__ */
               zlang::CCodeGeneratorHelper::TExpressionAtom tOperator;
               tOperator.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERATOR;
               tOperator.nTokenType = ZLangCodeGeneratorTokenTypes::ASSIGN;
               tOperator.stringTokenText = "=";
               tOperator.nLineNumber = nLineNumber;
               tOperator.nColumnNumber = nColumnNumber;
               dequeExpressionAtoms.push_back(tOperator);

               /*
                * Faking a table SUBSCRIPT operation as the left operand of that ASSIGN operation.
                */
               /* borrow from macro __PREPARE_A_OPERATOR__ */
               tOperator.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERATOR;
               tOperator.nTokenType = ZLangCodeGeneratorTokenTypes::SUBSCRIPT;
               tOperator.stringTokenText = "SUBSCRIPT";
               tOperator.nLineNumber = nLineNumber;
               tOperator.nColumnNumber = nColumnNumber;
               dequeExpressionAtoms.push_back(tOperator);
               /* borrow from macro __PREPARE_A_OPERAND__ */
               zlang::CCodeGeneratorHelper::TExpressionAtom tOperand;
               tOperand.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERAND;
               tOperand.nTokenType = ZLangCodeGeneratorTokenTypes::IDENTIFIER;
               tOperand.stringTokenText = rstringTableName;
               tOperand.nLineNumber = nLineNumber;
               tOperand.nColumnNumber = nColumnNumber;
               dequeExpressionAtoms.push_back(tOperand);
             }//----------------------------------------------------------------

             initializationConstant[dequeExpressionAtoms]
             initializationConstant[dequeExpressionAtoms]
             {//----------------------------------------------------------------
               _ciCodeGeneratorHelper.GenerateExpressionInstruction(_autoInitializerFunction,
                                                                    _vectorFindNames,
                                                                    dequeExpressionAtoms);
             }//----------------------------------------------------------------
           )
          )+
        ;

codeBlock
        : #(CODE_BLOCK
            {//-----------------------------------------------------------------
              int nIndex = 0;
            }//-----------------------------------------------------------------

            // Attention: The step of generating byte codes for local variables:
            //
            // The 1# local variable)
            //    saveBP
            //      construct1#LocalVariable  <-- Insert by the 1# index of the 1# local variable
            //        constructTempVariable-|
            //        constructTempVariable |
            //        ......                |<-- Temp variables for the #1 local variable initializing expression
            //        ......                |
            //        constructTempVariable-|
            //
            //
            // The 2# local variable)
            //    saveBP
            //    construct1#LocalVariable
            //      construct2#LocalVariable  <-- Insert by the 2# index of the 2# local variable
            //    constructTempVariable-|
            //    constructTempVariable |
            //    ......                |<-- Temp variables for the #1 local variable initializing expression
            //    ......                |
            //    constructTempVariable-|
            //
            //        constructTempVariable-|
            //        constructTempVariable |
            //        ......                |<-- Temp variables for the #2 local variable initializing expression
            //        ......                |
            //        constructTempVariable-|
            //
            // The ......# local variable)
            //    ......
            //
            // The end)
            //    saveBP
            //    construct1#LocalVariable
            //    construct2#LocalVariable
            //    ......
            //    constructTempVariable-|
            //    constructTempVariable |
            //    ......                |<-- Temp variables for the #1 local variable initializing expression
            //    ......                |
            //    constructTempVariable-|
            //
            //    constructTempVariable-|
            //    constructTempVariable |
            //    ......                |<-- Temp variables instruction for the #2 local variable initializing expression
            //    ......                |
            //    constructTempVariable-|
            //
            //    ......
            //
            //      allInitializingInstruction  <-- Now append all initializing instructions here
            (localVariableDefinition[nIndex])*
            {//-----------------------------------------------------------------
              // Set the count of local variables
              zlang::CZLangFunction * pciCurrentFunction = dynamic_cast<CZLangFunction *>(_autoCurrentFunction.get());
              pciCurrentFunction->SetLocalVariableCount(nIndex);

              // Since now we known the count of local variables, so we must fix
              // 'local variables initializing instruction sequence' for those
              // instructions which marked 'need fix local variable offset', such
              // as 'stringPlus' and 'quickConstruct?Object' and 'load?Address'(May)
              // instruction.
              FixLocalVariablesInitializeInstructionSequence(_autoCurrentLocalVariablesInitializeSequence, nIndex);

              //> Now append local variables initializing byte codes
              _autoCurrentFunction->AppendInstruction(_autoCurrentLocalVariablesInitializeSequence);

              std::stack<TBackPatchPosition> stackOuterBackPatchPositions;
            }//-----------------------------------------------------------------

            compoundStatement[stackOuterBackPatchPositions]
            {//-----------------------------------------------------------------
              if (! _bHaveReturnStatement &&
                  _stringCurrentFunctionReturnSignature != zvm::CstringZVM_VOID_SIGNATURE)
              {
                _ciCodeGeneratorHelper.ThrowSemanticError_ReturnStatementIsRequired(_nFunctionDefinitionBeginLineNumber,
                                                                                    _stringCurrentFunctionName,
                                                                                    _stringCurrentFunctionReturnSignature);
              }
            }//-----------------------------------------------------------------
          )
        ;

compoundStatement [std::stack<TBackPatchPosition> & rstackOuterBackPatchPositions]
        : #(COMPOUND_STATEMENTS (statement[rstackOuterBackPatchPositions])*)
        ;

statement [std::stack<TBackPatchPosition> & rstackOuterBackPatchPositions]
        : (  {//----------------------------------------------------------------
               std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> dequeExpressionAtoms;
             }//----------------------------------------------------------------
             expression[dequeExpressionAtoms]
             {//----------------------------------------------------------------
               GenerateExpressionStatement(_autoCurrentFunction, dequeExpressionAtoms);
             }//----------------------------------------------------------------

           | ifStatement[rstackOuterBackPatchPositions]
           | whileStatement[rstackOuterBackPatchPositions]

           | autoTreeLeaf1:"break"
             {//----------------------------------------------------------------
               antlr::RefToken & rautoToken = autoTreeLeaf1->getSavedToken();
               int nLineNumber = rautoToken->getLine();
               /* Generating "unlimitJump" */
               zvm::TZVMIndex nInstructionOfBreak = _ciCodeGeneratorHelper.GenerateInstruction(
                                                                      _autoCurrentFunction,
                                                                      nLineNumber,
                                                                      zvm::ZVM_unlimitJump,
                                                                      static_cast<SDWORD>(0));
               TBackPatchPosition tPosition(nInstructionOfBreak,
                                            LABEL_END_OF_LOOP);
               rstackOuterBackPatchPositions.push(tPosition);
             }//----------------------------------------------------------------

           | autoTreeLeaf2:"continue"
             {//----------------------------------------------------------------
               antlr::RefToken & rautoToken = autoTreeLeaf2->getSavedToken();
               int nLineNumber = rautoToken->getLine();
               int nColumnNumber = rautoToken->getColumn();
               /* Generating "unlimitJump" */
               zvm::TZVMIndex nInstructionOfContinue = _ciCodeGeneratorHelper.GenerateInstruction(
                                                                         _autoCurrentFunction,
                                                                         nLineNumber,
                                                                         zvm::ZVM_unlimitJump,
                                                                         static_cast<SDWORD>(0));
               TBackPatchPosition tPosition(nInstructionOfContinue,
                                            LABEL_BEGIN_OF_LOOP_TEST);
               rstackOuterBackPatchPositions.push(tPosition);
             }//----------------------------------------------------------------

           | #(autoTreeLeaf3:"return"
               {//--------------------------------------------------------------
                 _bHaveReturnStatement = true;  // denote this function at least have a 'return' statement
                 antlr::RefToken & rautoToken = autoTreeLeaf3->getSavedToken();
                 int nLineNumber = rautoToken->getLine();
                 int nColumnNumber = rautoToken->getColumn();
                 bool bHaveReturnValue = false;
               }//--------------------------------------------------------------

               (
                 {//-------------------------------------------------------------
                   bHaveReturnValue = true;
                   if (_stringCurrentFunctionReturnSignature == zvm::CstringZVM_VOID_SIGNATURE)
                   {
                     _ciCodeGeneratorHelper.ThrowSemanticError_ReturnIsNotAllowed(nLineNumber,
                                                                                  _stringCurrentFunctionName);
                   }
                   std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> dequeExpressionAtoms;

                   /*
                    * Faking a ASSIGN operation.
                    */
                   /* borrow from macro __PREPARE_A_OPERATOR__ */
                   zlang::CCodeGeneratorHelper::TExpressionAtom tOperator;
                   tOperator.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERATOR;
                   tOperator.nTokenType = ZLangCodeGeneratorTokenTypes::RETURN_PSEUDO_ASSIGN;
                   tOperator.stringTokenText = "return";
                   tOperator.nLineNumber = nLineNumber;
                   tOperator.nColumnNumber = nColumnNumber;
                   dequeExpressionAtoms.push_back(tOperator);

                   /*
                    * Faking a left operand of that ASSIGN operation.
                    */
                   /* borrow from macro __PREPARE_A_OPERAND__ */
                   zlang::CCodeGeneratorHelper::TExpressionAtom tOperand;
                   tOperand.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERAND;
                   tOperand.nTokenType = ZLangCodeGeneratorTokenTypes::IDENTIFIER;
                   tOperand.stringTokenText = _stringCurrentFunctionName;  // variable name is same as this function name
                   tOperand.nLineNumber = nLineNumber;
                   tOperand.nColumnNumber = nColumnNumber;
                   dequeExpressionAtoms.push_back(tOperand);
                 }//-------------------------------------------------------------

                 expression[dequeExpressionAtoms]
                 {//----------------------------------------------------------------
                   _ciCodeGeneratorHelper.GenerateExpressionInstruction(_autoCurrentFunction,
                                                                        _vectorFindNames,
                                                                        dequeExpressionAtoms);
                 }//----------------------------------------------------------------
               )?

               {//--------------------------------------------------------------
                 if (! bHaveReturnValue &&
                     _stringCurrentFunctionReturnSignature != zvm::CstringZVM_VOID_SIGNATURE)
                 {
                   _ciCodeGeneratorHelper.ThrowSemanticError_ReturnStatementIsRequired(nLineNumber,
                                                                                       _stringCurrentFunctionName,
                                                                                       _stringCurrentFunctionReturnSignature);
                 }
                 _ciCodeGeneratorHelper.GenerateInstruction(_autoCurrentFunction,
                                                            nLineNumber,
                                                            zvm::ZVM_ret);
               }//--------------------------------------------------------------
             )
          )

         | forStatement[rstackOuterBackPatchPositions]
        ;

ifStatement [std::stack<TBackPatchPosition> & rstackOuterBackPatchPositions]
        : #(autoTreeRoot:"if"
            {//-----------------------------------------------------------------
              std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> dequeExpressionAtoms;
              std::stack<TBackPatchPosition> stackBackPatchPositions;

              antlr::RefToken & rautoToken = autoTreeRoot->getSavedToken();
              int nLineNumber = rautoToken->getLine();

              zvm::TZVMIndex nLabel_EndOfThen;
              zvm::TZVMIndex nLabel_EndOfIf;
            }//-----------------------------------------------------------------

            expression[dequeExpressionAtoms]
            {//-----------------------------------------------------------------
              /* Generating codes of "testing expression" */
              /* 2001/6/26: Modified for checking result signature
              std::string stringSignature = _ciCodeGeneratorHelper.GenerateExpressionInstruction(
                                                                   _autoCurrentFunction,
                                                                   _vectorFindNames,
                                                                   dequeExpressionAtoms);
              */
              std::string stringSignature =
                  GenerateTestingExpressionStatement(_autoCurrentFunction, dequeExpressionAtoms);

              /* Generating "falseJump" */
              zvm::TZVMIndex nInstructionOfFalseJump = _ciCodeGeneratorHelper.GenerateInstruction(
                                                                         _autoCurrentFunction,
                                                                         nLineNumber,
                                                                         zvm::ZVM_falseJump | stringSignature[0],
                                                                         static_cast<SDWORD>(0));

              TBackPatchPosition tPositionFalseJump(nInstructionOfFalseJump,
                                                    LABEL_END_OF_THEN);
              stackBackPatchPositions.push(tPositionFalseJump);
            }//-----------------------------------------------------------------

            compoundStatement[stackBackPatchPositions]
            {//-----------------------------------------------------------------
              /* Generating "unlimitJump" */
              zvm::TZVMIndex nInstructionOfUnlimitJump = _ciCodeGeneratorHelper.GenerateInstruction(
                                                                           _autoCurrentFunction,
                                                                           nLineNumber,
                                                                           zvm::ZVM_unlimitJump,
                                                                           static_cast<SDWORD>(0));

              TBackPatchPosition tPositionUJump(nInstructionOfUnlimitJump,
                                                LABEL_END_OF_IF);
              stackBackPatchPositions.push(tPositionUJump);

              nLabel_EndOfIf = nLabel_EndOfThen = _autoCurrentFunction->GetLabelBookmark();
            }//-----------------------------------------------------------------

            (compoundStatement[stackBackPatchPositions]
             {//----------------------------------------------------------------
               nLabel_EndOfIf = _autoCurrentFunction->GetLabelBookmark();  /* Modify label of EndOfIf */
             }//----------------------------------------------------------------
            )?

            {//-----------------------------------------------------------------
              /* Now back patch 'if' nest's labels */
              while (! stackBackPatchPositions.empty())
              {
                TBackPatchPosition tPosition = stackBackPatchPositions.top();
                stackBackPatchPositions.pop();

                switch (tPosition.eLabelTag)
                {
                  case LABEL_END_OF_THEN:
                    _autoCurrentFunction->BackPatchLabel(tPosition.nInstructionIndex,
                                                         nLabel_EndOfThen);
                    break;

                  case LABEL_END_OF_IF:
                    _autoCurrentFunction->BackPatchLabel(tPosition.nInstructionIndex,
                                                         nLabel_EndOfIf);
                    break;

                  default:
                    /* Such as:
                       while (...)
                       {
                         if (...)
                         {
                           break;  // 'LABEL_END_OF_LOOP' is unknown to 'IF-Statement'
                         }
                         else
                         {
                           continue;  // 'LABEL_BEGIN_OF_LOOP_TEST' is unknown to 'IF-Statement'
                         }
                       }
                     */
                    /* a label that I don't known, Let outer nest(may 'while' of another 'if' statement) patches it */
                    rstackOuterBackPatchPositions.push(tPosition);
                }
              }
            }//-----------------------------------------------------------------
          )
        ;

whileStatement [std::stack<TBackPatchPosition> & rstackOuterBackPatchPositions]
        : #(autoTreeRoot:"while"
            {//-----------------------------------------------------------------
              static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("ZLangCodeGenerator::whileStatement()");
              std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> dequeExpressionAtoms;
              std::stack<TBackPatchPosition> stackBackPatchPositions;

              antlr::RefToken & rautoToken = autoTreeRoot->getSavedToken();
              int nLineNumber = rautoToken->getLine();

              zvm::TZVMIndex nLabel_BeginOfWhileTest;
              zvm::TZVMIndex nLabel_EndOfWhile;

              nLabel_BeginOfWhileTest = _autoCurrentFunction->GetLabelBookmark();
            }//-----------------------------------------------------------------

            expression[dequeExpressionAtoms]
            {//-----------------------------------------------------------------
              /* Generating codes of "testing expression" */
              /* 2001/6/26: Modified for checking result signature
              std::string stringSignature = _ciCodeGeneratorHelper.GenerateExpressionInstruction(
                                                                   _autoCurrentFunction,
                                                                   _vectorFindNames,
                                                                   dequeExpressionAtoms);
              */
              std::string stringSignature =
                  GenerateTestingExpressionStatement(_autoCurrentFunction, dequeExpressionAtoms);

              /* Generating "falseJump" */
              zvm::TZVMIndex nInstructionOfFalseJump = _ciCodeGeneratorHelper.GenerateInstruction(
                                                                         _autoCurrentFunction,
                                                                         nLineNumber,
                                                                         zvm::ZVM_falseJump | stringSignature[0],
                                                                         static_cast<SDWORD>(0));

              TBackPatchPosition tPosition(nInstructionOfFalseJump,
                                           LABEL_END_OF_LOOP);
              stackBackPatchPositions.push(tPosition);
            }//-----------------------------------------------------------------

            compoundStatement[stackBackPatchPositions]  // May 'break' or 'continue' push label
            {//-----------------------------------------------------------------
              zvm::TZVMIndex nLabel_NowPosition = _autoCurrentFunction->GetLabelBookmark();
              /* Generating "unlimitJump" */
              zvm::TZVMIndex nInstructionOfUnlimitJump =
                  _ciCodeGeneratorHelper.GenerateInstruction(
                                  _autoCurrentFunction,
                                  nLineNumber,
                                  zvm::ZVM_unlimitJump,
                                  //nLabel_BeginOfWhileTest);
                                  nLabel_BeginOfWhileTest - nLabel_NowPosition);

              nLabel_EndOfWhile = _autoCurrentFunction->GetLabelBookmark();

              /* Now back patch label */
              while (! stackBackPatchPositions.empty())
              {
                TBackPatchPosition tPosition = stackBackPatchPositions.top();
                stackBackPatchPositions.pop();

                switch (tPosition.eLabelTag)
                {
                  case LABEL_END_OF_LOOP:
                    _autoCurrentFunction->BackPatchLabel(tPosition.nInstructionIndex,
                                                         nLabel_EndOfWhile);
                    break;

                  case LABEL_BEGIN_OF_LOOP_TEST:
                    _autoCurrentFunction->BackPatchLabel(tPosition.nInstructionIndex,
                                                         nLabel_BeginOfWhileTest);
                    break;

                  default:
                    LogAssert1(tPosition.eLabelTag == LABEL_END_OF_LOOP ||
                               tPosition.eLabelTag == LABEL_BEGIN_OF_LOOP_TEST,
                               "Unexpected code label tag '%d'", tPosition.eLabelTag);
                    break;
                }
              }
            }//-----------------------------------------------------------------
          )
        ;

forStatement [std::stack<TBackPatchPosition> & rstackOuterBackPatchPositions]
        : #(autoTreeRoot:"for"
            {//-----------------------------------------------------------------
              static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("ZLangCodeGenerator::forStatement()");
              std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> dequeExpressionAtoms;

              antlr::RefToken & rautoToken = autoTreeRoot->getSavedToken();
              int nLineNumber = rautoToken->getLine();

              zlang::CInstructionContainer_auto autoExpression3InstructionSequence =
                    new __OPTION(_THROW) zlang::CInstructionSequence(_autoCurrentFunction.get());

              std::stack<TBackPatchPosition> stackBackPatchPositions;
              zvm::TZVMIndex nLabel_BeginOfForTest;
              zvm::TZVMIndex nLabel_EndOfFor;

              nLabel_BeginOfForTest = _autoCurrentFunction->GetLabelBookmark();
            }//-----------------------------------------------------------------

            (forExpression1[dequeExpressionAtoms]
             {//-----------------------------------------------------------------
               // Generating 'initializing expression'
               GenerateExpressionStatement(_autoCurrentFunction, dequeExpressionAtoms);

               // Adjust 'begin testing label'
               nLabel_BeginOfForTest = _autoCurrentFunction->GetLabelBookmark();
             }//----------------------------------------------------------------
            )?

            (forExpression2[dequeExpressionAtoms]
             {//----------------------------------------------------------------
               // Generating 'testing expression'
               std::string stringResultSignature =
                   GenerateTestingExpressionStatement(_autoCurrentFunction, dequeExpressionAtoms);

               // Generating "falseJump"
               zvm::TZVMIndex nInstructionOfFalseJump = _ciCodeGeneratorHelper.GenerateInstruction(
                                                                          _autoCurrentFunction,
                                                                          nLineNumber,
                                                                          zvm::ZVM_falseJump | stringResultSignature[0],
                                                                          static_cast<SDWORD>(0));

               TBackPatchPosition tPosition(nInstructionOfFalseJump, LABEL_END_OF_LOOP);
               stackBackPatchPositions.push(tPosition);
             }//----------------------------------------------------------------
            )?

            (forExpression3[dequeExpressionAtoms]
             {//----------------------------------------------------------------
               // Generating 'expression3' into a temp container
               GenerateExpressionStatement(autoExpression3InstructionSequence, dequeExpressionAtoms);
             }//----------------------------------------------------------------
            )?

            compoundStatement[stackBackPatchPositions]  // May 'break' or 'continue' push label
            {//-----------------------------------------------------------------
              _autoCurrentFunction->AppendInstruction(autoExpression3InstructionSequence);

              /* Generating "unlimitJump" */
              zvm::TZVMIndex nLabel_NowPosition = _autoCurrentFunction->GetLabelBookmark();
              zvm::TZVMIndex nInstructionOfUnlimitJump =
                  _ciCodeGeneratorHelper.GenerateInstruction(
                                  _autoCurrentFunction,
                                  nLineNumber,
                                  zvm::ZVM_unlimitJump,
                                  //nLabel_BeginOfForTest);
                                  nLabel_BeginOfForTest - nLabel_NowPosition);

              /* Now back patch label */
              nLabel_EndOfFor = _autoCurrentFunction->GetLabelBookmark();
              while (! stackBackPatchPositions.empty())
              {
                TBackPatchPosition tPosition = stackBackPatchPositions.top();
                stackBackPatchPositions.pop();

                switch (tPosition.eLabelTag)
                {
                  case LABEL_END_OF_LOOP:
                    _autoCurrentFunction->BackPatchLabel(tPosition.nInstructionIndex,
                                                         nLabel_EndOfFor);
                    break;

                  case LABEL_BEGIN_OF_LOOP_TEST:
                    _autoCurrentFunction->BackPatchLabel(tPosition.nInstructionIndex,
                                                         nLabel_BeginOfForTest);
                    break;

                  default:
                    LogAssert1(tPosition.eLabelTag == LABEL_END_OF_LOOP ||
                               tPosition.eLabelTag == LABEL_BEGIN_OF_LOOP_TEST,
                               "Unexpected code label tag '%d'", tPosition.eLabelTag);
                    break;
                }
              }
            }//-----------------------------------------------------------------
          )
        ;

forExpression1 [std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms]
        : #(FOR_EXPRESSION1 expressionDefinition[rdequeExpressionAtoms])
        ;

forExpression2 [std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms]
        : #(FOR_EXPRESSION2 expressionDefinition[rdequeExpressionAtoms])
        ;

forExpression3 [std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms]
        : #(FOR_EXPRESSION3 expressionDefinition[rdequeExpressionAtoms])
        ;

localVariableDefinition [int & rnIndex]
        : #(LVARIABLE_DEFINITION
            (   {//-------------------------------------------------------------
                  std::string stringVariableName;
                  std::string stringVariableSignature;
                  bool bIsReferenceVariable = false;
                }//-------------------------------------------------------------
                builtInType[stringVariableSignature] (BAND {bIsReferenceVariable = true;})?
                {//-------------------------------------------------------------
                  if (bIsReferenceVariable)
                  {
                    // Turn signature to lower char
                    zfc::LowerString(stringVariableSignature);
                  }
                }//-------------------------------------------------------------

                (#(autoName:IDENTIFIER
                   {//----------------------------------------------------------
                     ++rnIndex;
                     antlr::RefToken & rautoToken = autoName->getSavedToken();
                     int nLineNumber = rautoToken->getLine();
                     int nColumnNumber = rautoToken->getColumn();
                     stringVariableName = autoName->getText();
                     _vectorFindNames.push_back(stringVariableName);

                     _ciCodeGeneratorHelper.GenerateConstructLocalVariableInstruction(
                                                            _autoCurrentFunction,
                                                            nLineNumber,
                                                            _vectorFindNames,
                                                            stringVariableName,
                                                            stringVariableSignature,
                                                            rnIndex);

                     _vectorFindNames.pop_back();

                     bool bReferenceHaveInitializer = false;

                     // Refersh the count of now local variables for validing initializing expression
                     zlang::CZLangFunction * pciCurrentFunction = dynamic_cast<CZLangFunction *>(_autoCurrentFunction.get());
                     pciCurrentFunction->SetLocalVariableCount(rnIndex);
                   }//----------------------------------------------------------

                   (
                    {//---------------------------------------------------------
                      std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> dequeExpressionAtoms;

                      /*
                       * Faking a ASSIGN operation.
                       */
                      /* borrow from macro __PREPARE_A_OPERATOR__ */
                      zlang::CCodeGeneratorHelper::TExpressionAtom tOperator;
                      tOperator.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERATOR;
                      if (bIsReferenceVariable)
                      {
                        bReferenceHaveInitializer = true;
                        tOperator.nTokenType = ZLangCodeGeneratorTokenTypes::REFERENCE_ADDRESS_ASSIGN;
                      }
                      else
                      {
                        tOperator.nTokenType = ZLangCodeGeneratorTokenTypes::ASSIGN;
                      }
                      tOperator.stringTokenText = "=";
                      tOperator.nLineNumber = nLineNumber;
                      tOperator.nColumnNumber = nColumnNumber;
                      dequeExpressionAtoms.push_back(tOperator);

                      /*
                       * Faking a left operand of that ASSIGN operation.
                       */
                      /* borrow from macro __PREPARE_A_OPERAND__ */
                      zlang::CCodeGeneratorHelper::TExpressionAtom tOperand;
                      tOperand.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERAND;
                      tOperand.nTokenType = ZLangCodeGeneratorTokenTypes::IDENTIFIER;
                      tOperand.stringTokenText = stringVariableName;
                      tOperand.nLineNumber = nLineNumber;
                      tOperand.nColumnNumber = nColumnNumber;
                      dequeExpressionAtoms.push_back(tOperand);
                    }//---------------------------------------------------------

                    expression[dequeExpressionAtoms]
                    {//---------------------------------------------------------
                      //> 2001/6/26: Modified
                      //_ciCodeGeneratorHelper.GenerateExpressionInstruction(_autoCurrentFunction,
                      _ciCodeGeneratorHelper.TurnOnSwitchOfNeedFixTempLocalVariableOffset();
                      _ciCodeGeneratorHelper.GenerateExpressionInstruction(_autoCurrentLocalVariablesInitializeSequence,
                                                                           _vectorFindNames,
                                                                           dequeExpressionAtoms);
                      _ciCodeGeneratorHelper.TurnOffSwitchOfNeedFixTempLocalVariableOffset();
                    }//---------------------------------------------------------
                   )?

                   {//----------------------------------------------------------
                     if (bIsReferenceVariable && ! bReferenceHaveInitializer)
                     // If it is reference variable and but is not initialized
                     {
                       _ciCodeGeneratorHelper.ThrowSemanticError_ReferenceVariableMustBeInitialized(nLineNumber,
                                                                                                    nColumnNumber,
                                                                                                    stringVariableName,
                                                                                                    stringVariableSignature);
                     }
                   }//----------------------------------------------------------
                 )
                )+

              | {//-------------------------------------------------------------
                  std::string stringTableName;
                  std::string stringTableSignature;
                  int nLineNumber;
                  int nColumnNumber;
                  bool bIsReferenceVariable = false;
                  bool bReferenceHaveInitializer = false;
                  ++rnIndex;
                }//-------------------------------------------------------------
                localTableDefinition[stringTableName, stringTableSignature, nLineNumber, nColumnNumber, bIsReferenceVariable, rnIndex]
                {//-------------------------------------------------------------
                  // Refersh the count of now local variables for validing initializing expression
                  zlang::CZLangFunction * pciCurrentFunction = dynamic_cast<CZLangFunction *>(_autoCurrentFunction.get());
                  pciCurrentFunction->SetLocalVariableCount(rnIndex);
                }//-------------------------------------------------------------

                (   localTableInit[stringTableName, nLineNumber, nColumnNumber]

                  | {//---------------------------------------------------------
                      std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> dequeExpressionAtoms;

                      /*
                       * Faking a ASSIGN operation.
                       */
                      /* borrow from macro __PREPARE_A_OPERATOR__ */
                      zlang::CCodeGeneratorHelper::TExpressionAtom tOperator;
                      tOperator.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERATOR;
                      if (bIsReferenceVariable)
                      {
                        bReferenceHaveInitializer = true;
                        tOperator.nTokenType = ZLangCodeGeneratorTokenTypes::REFERENCE_ADDRESS_ASSIGN;
                      }
                      else
                      {
                        tOperator.nTokenType = ZLangCodeGeneratorTokenTypes::ASSIGN;
                      }
                      tOperator.stringTokenText = "=";
                      tOperator.nLineNumber = nLineNumber;
                      tOperator.nColumnNumber = nColumnNumber;
                      dequeExpressionAtoms.push_back(tOperator);

                      /*
                       * Faking a left operand of that ASSIGN operation.
                       */
                      /* borrow from macro __PREPARE_A_OPERAND__ */
                      zlang::CCodeGeneratorHelper::TExpressionAtom tOperand;
                      tOperand.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERAND;
                      tOperand.nTokenType = ZLangCodeGeneratorTokenTypes::IDENTIFIER;
                      tOperand.stringTokenText = stringTableName;
                      tOperand.nLineNumber = nLineNumber;
                      tOperand.nColumnNumber = nColumnNumber;
                      dequeExpressionAtoms.push_back(tOperand);
                    }//---------------------------------------------------------
                    expression[dequeExpressionAtoms]
                    {//---------------------------------------------------------
                      _ciCodeGeneratorHelper.TurnOnSwitchOfNeedFixTempLocalVariableOffset();
                      _ciCodeGeneratorHelper.GenerateExpressionInstruction(_autoCurrentLocalVariablesInitializeSequence,
                                                                           _vectorFindNames,
                                                                           dequeExpressionAtoms);
                      _ciCodeGeneratorHelper.TurnOffSwitchOfNeedFixTempLocalVariableOffset();
                    }//---------------------------------------------------------
                )?
                {//-------------------------------------------------------------
                  if (bIsReferenceVariable && ! bReferenceHaveInitializer)
                  // If it is reference variable and but is not initialized
                  {
                    _ciCodeGeneratorHelper.ThrowSemanticError_ReferenceVariableMustBeInitialized(nLineNumber,
                                                                                                 nColumnNumber,
                                                                                                 stringTableName,
                                                                                                 stringTableSignature);
                  }
                }//-------------------------------------------------------------
            )
          )
        ;

localTableDefinition [std::string & rstringTableName,
                      std::string & rstringTableSignature,
                      int & rnLineNumber,
                      int & rnColumnNumber,
                      bool & rbIsReferenceVariable,
                      int nVariableIndex]
        : {//-------------------------------------------------------------------
            std::string stringElementSignature;
          }//-------------------------------------------------------------------

          "table" builtInType[stringElementSignature] (BAND {rbIsReferenceVariable = true;})? autoName:IDENTIFIER
          {//-------------------------------------------------------------------
            rstringTableSignature = zvm::CstringZVM_TABLE_PREFIX_SIGNATURE + stringElementSignature;
            if (rbIsReferenceVariable)
            {
              // Turn signature to lower char
              zfc::LowerString(rstringTableSignature);
            }

            rstringTableName = autoName->getText();
            _vectorFindNames.push_back(rstringTableName);

            antlr::RefToken & autoToken = autoName->getSavedToken();
            int nLineNumber = rnLineNumber = autoToken->getLine();
            int nColumnNumber = rnColumnNumber = autoToken->getColumn();

            _ciCodeGeneratorHelper.GenerateConstructLocalVariableInstruction(
                                                           _autoCurrentFunction,
                                                           rnLineNumber,
                                                           _vectorFindNames,
                                                           rstringTableName,
                                                           rstringTableSignature,
                                                           nVariableIndex);

            _vectorFindNames.pop_back();
          }//-------------------------------------------------------------------
        ;

localTableInit [std::string & rstringTableName,
                int nLineNumber,
                int nColumnNumber]
        : (#(ELEMENT_INIT
             {//----------------------------------------------------------------
               std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> dequeExpressionAtoms;

               /*
                * Faking a ASSIGN operation.
                */
               /* borrow from macro __PREPARE_A_OPERATOR__ */
               zlang::CCodeGeneratorHelper::TExpressionAtom tOperator;
               tOperator.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERATOR;
               tOperator.nTokenType = ZLangCodeGeneratorTokenTypes::ASSIGN;
               tOperator.stringTokenText = "=";
               tOperator.nLineNumber = nLineNumber;
               tOperator.nColumnNumber = nColumnNumber;
               dequeExpressionAtoms.push_back(tOperator);

               /*
                * Faking a table SUBSCRIPT operation as the left operand of that ASSIGN operation.
                */
               /* borrow from macro __PREPARE_A_OPERATOR__ */
               tOperator.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERATOR;
               tOperator.nTokenType = ZLangCodeGeneratorTokenTypes::SUBSCRIPT;
               tOperator.stringTokenText = "SUBSCRIPT";
               tOperator.nLineNumber = nLineNumber;
               tOperator.nColumnNumber = nColumnNumber;
               dequeExpressionAtoms.push_back(tOperator);
               /* borrow from macro __PREPARE_A_OPERAND__ */
               zlang::CCodeGeneratorHelper::TExpressionAtom tOperand;
               tOperand.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERAND;
               tOperand.nTokenType = ZLangCodeGeneratorTokenTypes::IDENTIFIER;
               tOperand.stringTokenText = rstringTableName;
               tOperand.nLineNumber = nLineNumber;
               tOperand.nColumnNumber = nColumnNumber;
               dequeExpressionAtoms.push_back(tOperand);
             }//----------------------------------------------------------------

             initializationConstant[dequeExpressionAtoms]
             initializationConstant[dequeExpressionAtoms]
             {//----------------------------------------------------------------
               //> 2001/6/26: Modified
               //_ciCodeGeneratorHelper.GenerateExpressionInstruction(_autoCurrentFunction,
               _ciCodeGeneratorHelper.TurnOnSwitchOfNeedFixTempLocalVariableOffset();
               _ciCodeGeneratorHelper.GenerateExpressionInstruction(_autoCurrentLocalVariablesInitializeSequence,
                                                                    _vectorFindNames,
                                                                    dequeExpressionAtoms);
               _ciCodeGeneratorHelper.TurnOffSwitchOfNeedFixTempLocalVariableOffset();
             }//----------------------------------------------------------------
           )
          )+
        ;

builtInType [std::string & rstringType]
        :   "byte"      { rstringType = zvm::CstringZVM_BYTE_SIGNATURE; }
          | "bool"      { rstringType = zvm::CstringZVM_BOOL_SIGNATURE; }
          | "sdword"    { rstringType = zvm::CstringZVM_SDWORD_SIGNATURE; }
          | "udword"    { rstringType = zvm::CstringZVM_UDWORD_SIGNATURE; }
          | "sqword"    { rstringType = zvm::CstringZVM_SQWORD_SIGNATURE; }
          | "uqword"    { rstringType = zvm::CstringZVM_UQWORD_SIGNATURE; }
          | "double"    { rstringType = zvm::CstringZVM_DOUBLE_SIGNATURE; }
          | "string"    { rstringType = zvm::CstringZVM_STRING_SIGNATURE; }
          | "ipaddress" { rstringType = zvm::CstringZVM_IPv4ADDR_SIGNATURE; }
          | "pport"     { rstringType = zvm::CstringZVM_PPORT_SIGNATURE; }
          | "rope"      { rstringType = zvm::CstringZVM_ROPE_SIGNATURE; }
        ;

expression [std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms]
        : #(EXPRESSION expressionDefinition[rdequeExpressionAtoms])
        ;

argumentList [std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms]
        : (expression[rdequeExpressionAtoms]
           {//------------------------------------------------------------------
             /* borrow from __PREPARE_A_OPERATOR__ */
             zlang::CCodeGeneratorHelper::TExpressionAtom tOperator;
             tOperator.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERATOR;
             tOperator.nTokenType = ZLangCodeGeneratorTokenTypes::PASS_A_ARGUMENT;
             tOperator.stringTokenText = "PASS_A_ARGUMENT";
             tOperator.nLineNumber = 0;
             tOperator.nColumnNumber = 0;
             rdequeExpressionAtoms.push_back(tOperator);
           }//------------------------------------------------------------------
          )+
        ;

expressionDefinition [std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms]
        :   #(autoTreeRoot1:ASSIGN
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot1);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot2:LOR
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot2);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot3:LAND
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot3);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot4:BOR
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot4);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot5:BXOR
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot5);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot6:BAND
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot6);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot7:NOT_EQUAL
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot7);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot8:EQUAL
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot8);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot9:LT_
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot9);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot10:GT
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot10);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot11:LE
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot11);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot12:GE
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot12);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot13:SL
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot13);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot14:SR
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot14);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot15:PLUS
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot15);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot16:MINUS
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot16);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot17:STAR
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot17);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot18:DIV
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot18);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot19:MOD
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot19);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expressionDefinition[rdequeExpressionAtoms]
            )

          /*
          | #(autoTreeRoot20:INC
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot20);
              }//---------------------------------------------------------------
              postfixExpression[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot21:DEC
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot21);
              }//---------------------------------------------------------------
              postfixExpression[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot22:UNARY_MINUS
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot22);
              }//---------------------------------------------------------------
              postfixExpression[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot23:UNARY_PLUS
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot23);
              }//---------------------------------------------------------------
              postfixExpression[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot24:BNOT
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot24);
              }//---------------------------------------------------------------
              postfixExpression[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot25:LNOT
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot25);
              }//---------------------------------------------------------------
              postfixExpression[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot26:TYPECAST
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot26);
                std::string stringCastToSignature;
              }//---------------------------------------------------------------
              builtInType[stringCastToSignature]
              {//---------------------------------------------------------------
                zlang::CCodeGeneratorHelper::TExpressionAtom tOperand;
                tOperand.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERAND;
                tOperand.nTokenType = ZLangCodeGeneratorTokenTypes::CAST_LITERAL;
                tOperand.stringTokenText = stringCastToSignature;
                antlr::RefToken & autoToken = autoTreeRoot26->getSavedToken();
                tOperand.nLineNumber = autoToken->getLine();
                tOperand.nColumnNumber = autoToken->getColumn();
                rdequeExpressionAtoms.push_back(tOperand);
              }//---------------------------------------------------------------
              postfixExpression[rdequeExpressionAtoms]
            )
          */
          | #(autoTreeRoot20:INC
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot20);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot21:DEC
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot21);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot22:UNARY_MINUS
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot22);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot23:UNARY_PLUS
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot23);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot24:BNOT
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot24);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot25:LNOT
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot25);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot26:TYPECAST
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot26);
                std::string stringCastToSignature;
              }//---------------------------------------------------------------
              builtInType[stringCastToSignature]
              {//---------------------------------------------------------------
                zlang::CCodeGeneratorHelper::TExpressionAtom tOperand;
                tOperand.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERAND;
                tOperand.nTokenType = ZLangCodeGeneratorTokenTypes::CAST_LITERAL;
                tOperand.stringTokenText = stringCastToSignature;
                antlr::RefToken & autoToken = autoTreeRoot26->getSavedToken();
                tOperand.nLineNumber = autoToken->getLine();
                tOperand.nColumnNumber = autoToken->getColumn();
                rdequeExpressionAtoms.push_back(tOperand);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
            )
          | postfixExpression[rdequeExpressionAtoms]
        ;

postfixExpression [std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms]
          /*
        :   #(autoTreeRoot1:CALLING
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot1);
              }//---------------------------------------------------------------
              primaryExpression[rdequeExpressionAtoms]
              (argumentList[rdequeExpressionAtoms])?
              {//-------------------------------------------------------------------
                ///> borrow from __PREPARE_A_OPERATOR__
                zlang::CCodeGeneratorHelper::TExpressionAtom tOperator;
                tOperator.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERATOR;
                tOperator.nTokenType = ZLangCodeGeneratorTokenTypes::ARGUMENTS_END;
                tOperator.stringTokenText = "ARGUMENTS_END";
                tOperator.nLineNumber = 0;
                tOperator.nColumnNumber = 0;
                rdequeExpressionAtoms.push_back(tOperator);
              }//-------------------------------------------------------------------
            )
          | #(autoTreeRoot2:DOT
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot2);
              }//---------------------------------------------------------------
              primaryExpression[rdequeExpressionAtoms]
              autoTreeLeaf:IDENTIFIER
              {//---------------------------------------------------------------
                __PREPARE_A_OPERAND__(autoTreeLeaf);
              }//---------------------------------------------------------------
            )
          | #(autoTreeRoot3:SUBSCRIPT
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot3);
              }//---------------------------------------------------------------
              primaryExpression[rdequeExpressionAtoms]
              expression[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot4:POST_INC
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot4);
              }//---------------------------------------------------------------
              primaryExpression[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot5:POST_DEC
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot5);
              }//---------------------------------------------------------------
              primaryExpression[rdequeExpressionAtoms]
            )
          */
        :   #(autoTreeRoot1:CALLING
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot1);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              (argumentList[rdequeExpressionAtoms])?
              {//-------------------------------------------------------------------
                ///> borrow from __PREPARE_A_OPERATOR__
                zlang::CCodeGeneratorHelper::TExpressionAtom tOperator;
                tOperator.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERATOR;
                tOperator.nTokenType = ZLangCodeGeneratorTokenTypes::ARGUMENTS_END;
                tOperator.stringTokenText = "ARGUMENTS_END";
                tOperator.nLineNumber = 0;
                tOperator.nColumnNumber = 0;
                rdequeExpressionAtoms.push_back(tOperator);
              }//-------------------------------------------------------------------
            )
          | #(autoTreeRoot2:DOT
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot2);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              autoTreeLeaf:IDENTIFIER
              {//---------------------------------------------------------------
                __PREPARE_A_OPERAND__(autoTreeLeaf);
              }//---------------------------------------------------------------
            )
          | #(autoTreeRoot3:SUBSCRIPT
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot3);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
              expression[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot4:POST_INC
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot4);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
            )
          | #(autoTreeRoot5:POST_DEC
              {//---------------------------------------------------------------
                __PREPARE_A_OPERATOR__(autoTreeRoot5);
              }//---------------------------------------------------------------
              expressionDefinition[rdequeExpressionAtoms]
            )
          | primaryExpression[rdequeExpressionAtoms]
        ;

primaryExpression [std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms]
	:   autoTreeLeaf:IDENTIFIER
            {//-----------------------------------------------------------------
              __PREPARE_A_OPERAND__(autoTreeLeaf);
            }//-----------------------------------------------------------------
          | constant[rdequeExpressionAtoms]
        ;

constant [std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms]
	: (
              autoTreeLeaf1:NUM_INT
              {//---------------------------------------------------------------
                __PREPARE_A_OPERAND__(autoTreeLeaf1);
              }//---------------------------------------------------------------
            | autoTreeLeaf2:NUM_HEX_INT
              {//---------------------------------------------------------------
                __PREPARE_A_OPERAND__(autoTreeLeaf2);
              }//---------------------------------------------------------------
            | autoTreeLeaf3:NUM_QUAD
              {//---------------------------------------------------------------
                __PREPARE_A_OPERAND__(autoTreeLeaf3);
              }//---------------------------------------------------------------
            | autoTreeLeaf4:NUM_HEX_QUAD
              {//---------------------------------------------------------------
                __PREPARE_A_OPERAND__(autoTreeLeaf4);
              }//---------------------------------------------------------------
            | autoTreeLeaf5:NUM_FLOAT
              {//---------------------------------------------------------------
                __PREPARE_A_OPERAND__(autoTreeLeaf5);
              }//---------------------------------------------------------------
            | autoTreeLeaf6:CHAR_LITERAL
              {//---------------------------------------------------------------
                __PREPARE_A_OPERAND__(autoTreeLeaf6);
              }//---------------------------------------------------------------
            | autoTreeLeaf7:STRING_LITERAL
              {//---------------------------------------------------------------
                __PREPARE_A_OPERAND__(autoTreeLeaf7);
              }//---------------------------------------------------------------
            | autoTreeLeaf8:IPv4ADDR_LITERAL
              {//---------------------------------------------------------------
                __PREPARE_A_OPERAND__(autoTreeLeaf8);
              }//---------------------------------------------------------------
            | autoTreeLeaf9:PPORT_LITERAL
              {//---------------------------------------------------------------
                __PREPARE_A_OPERAND__(autoTreeLeaf9);
              }//---------------------------------------------------------------
            | autoTreeLeaf10:"true"
              {//---------------------------------------------------------------
                __PREPARE_A_OPERAND__(autoTreeLeaf10);
              }//---------------------------------------------------------------
            | autoTreeLeaf11:"false"
              {//---------------------------------------------------------------
                __PREPARE_A_OPERAND__(autoTreeLeaf11);
              }//---------------------------------------------------------------
            | autoTreeLeaf12:ROPE_LITERAL
              {//---------------------------------------------------------------
                __PREPARE_A_OPERAND__(autoTreeLeaf12);
              }//---------------------------------------------------------------
          )
	;

initializationConstant [std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms]
	:   {//-----------------------------------------------------------------
              bool bMinus = false;
              bool bInt = false;
              bool bQuad = false;
              bool bDouble = false;
            }//-----------------------------------------------------------------
            (PLUS | MINUS { bMinus = true; } )?
            (   autoTreeLeaf1:NUM_INT { bInt = true; }
              | autoTreeLeaf2:NUM_QUAD { bQuad = true; }
              | autoTreeLeaf3:NUM_FLOAT { bDouble = true; }
            )
            {//-----------------------------------------------------------------
              std::string stringSign;
              if (bMinus)
              {
                stringSign = "-";
              }
              zlang::CCodeGeneratorHelper::TExpressionAtom tOperand;
              tOperand.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERAND;
              if (bInt)
              {
                tOperand.nTokenType = autoTreeLeaf1->getType();
                tOperand.stringTokenText = stringSign + autoTreeLeaf1->getText();
                antlr::RefToken & rautoToken = autoTreeLeaf1->getSavedToken();
                tOperand.nLineNumber = rautoToken->getLine();
                tOperand.nColumnNumber = rautoToken->getColumn();
              }
              else
              {
                if (bDouble)
                {
                  tOperand.nTokenType = autoTreeLeaf3->getType();
                  tOperand.stringTokenText = stringSign + autoTreeLeaf3->getText();
                  antlr::RefToken & rautoToken = autoTreeLeaf3->getSavedToken();
                  tOperand.nLineNumber = rautoToken->getLine();
                  tOperand.nColumnNumber = rautoToken->getColumn();
                }
                else
                {
                  tOperand.nTokenType = autoTreeLeaf2->getType();
                  tOperand.stringTokenText = stringSign + autoTreeLeaf2->getText();
                  antlr::RefToken & rautoToken = autoTreeLeaf2->getSavedToken();
                  tOperand.nLineNumber = rautoToken->getLine();
                  tOperand.nColumnNumber = rautoToken->getColumn();
                }
              }
              rdequeExpressionAtoms.push_back(tOperand);
            }//-----------------------------------------------------------------
          | autoTreeLeaf4:NUM_HEX_INT
            {//-----------------------------------------------------------------
              __PREPARE_A_OPERAND__(autoTreeLeaf4);
            }//-----------------------------------------------------------------
          | autoTreeLeaf5:NUM_HEX_QUAD
            {//-----------------------------------------------------------------
              __PREPARE_A_OPERAND__(autoTreeLeaf5);
            }//-----------------------------------------------------------------
          | autoTreeLeaf6:CHAR_LITERAL
            {//-----------------------------------------------------------------
              __PREPARE_A_OPERAND__(autoTreeLeaf6);
            }//-----------------------------------------------------------------
          | autoTreeLeaf7:STRING_LITERAL
            {//-----------------------------------------------------------------
              __PREPARE_A_OPERAND__(autoTreeLeaf7);
            }//-----------------------------------------------------------------
          | autoTreeLeaf8:IPv4ADDR_LITERAL
            {//-----------------------------------------------------------------
              __PREPARE_A_OPERAND__(autoTreeLeaf8);
            }//-----------------------------------------------------------------
          | autoTreeLeaf9:PPORT_LITERAL
            {//-----------------------------------------------------------------
              __PREPARE_A_OPERAND__(autoTreeLeaf9);
            }//-----------------------------------------------------------------
          | autoTreeLeaf10:"true"
            {//-----------------------------------------------------------------
              __PREPARE_A_OPERAND__(autoTreeLeaf10);
            }//-----------------------------------------------------------------
          | autoTreeLeaf11:"false"
            {//-----------------------------------------------------------------
              __PREPARE_A_OPERAND__(autoTreeLeaf11);
            }//-----------------------------------------------------------------
          | autoTreeLeaf12:ROPE_LITERAL
            {//-----------------------------------------------------------------
              __PREPARE_A_OPERAND__(autoTreeLeaf12);
            }//-----------------------------------------------------------------
	;

