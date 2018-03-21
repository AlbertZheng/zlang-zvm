header "pre_include_hpp" {
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

}

options {
  language = "Cpp";
  namespace = "zlang";
  namespaceStd = "std::";
  namespaceAntlr = "antlr::";
}

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
class ZLangSymbolTableGenerator extends TreeParser;
options {
  importVocab = ZLang;
  ASTLabelType = "zlang::CZLangAST_auto";
  defaultErrorHandler = false;
}

{
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

}

/** ZLang script starting. */
zlangScript
        : (   externGlobalFunctionDeclaration
            | externGlobalVariableDeclaration
            | globalVariableDefinition
            | globalFunctionDefinition
          )*
        ;

externGlobalFunctionDeclaration
        : #(EXTERN_GFUNCTION_DECLARATION
            #(autoName:IDENTIFIER
              {//---------------------------------------------------------------
                _vectorFindNames.push_back(autoName->getText());

                zlang::CGlobalFunctionSymbolAttributes * pciAttributes =
                      new __OPTION(_THROW) zlang::CGlobalFunctionSymbolAttributes(zvm::PUBLIC_BY_EXTERN_MODULE);
                __INSERT_SYMBOL__(autoName);

                std::string stringResultSignature;
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
                pciAttributes->SetReturnSignature(stringResultSignature);
                std::string stringFunctionSignature = "(";
              }//---------------------------------------------------------------

              (externParameterDeclarationList[stringFunctionSignature])?
              {//---------------------------------------------------------------
                stringFunctionSignature += ")";
                stringFunctionSignature += stringResultSignature;
                pciAttributes->SetFunctionSignature(stringFunctionSignature);

                _vectorFindNames.pop_back();
              }//---------------------------------------------------------------
            )
          )
        ;

externParameterDeclarationList [std::string & rstringParametersSignature]
        : #(PARAMETERS_DECLARATION
            (externParameterDeclaration[rstringParametersSignature])+
          )
        ;

externParameterDeclaration [std::string & rstringParametersSignature]
        : {//-------------------------------------------------------------------
            std::string stringTypeSignature;
            bool bIsTable = false;
            bool bIsReferenceArgument = false;
          }//-------------------------------------------------------------------

          #(IDENTIFIER
            ("table" {bIsTable = true;})? builtInType[stringTypeSignature] (BAND {bIsReferenceArgument = true;})?
          )
          {//-------------------------------------------------------------------
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
                   _vectorFindNames.push_back(autoName->getText());

                   zlang::CGlobalVariableSymbolAttributes * pciAttributes =
                         new __OPTION(_THROW) zlang::CGlobalVariableSymbolAttributes(zvm::PUBLIC_BY_EXTERN_MODULE);
                   pciAttributes->SetVariableSignature(stringVariableSignature);
                   __INSERT_SYMBOL__(autoName);

                   _vectorFindNames.pop_back();
                 }//------------------------------------------------------------
                )+

              | {//-------------------------------------------------------------
                  std::string stringElementSignature;
                }//-------------------------------------------------------------
                "table" builtInType[stringElementSignature]

                (autoTableName:IDENTIFIER
                 {//------------------------------------------------------------
                   std::string stringTableSignature = zvm::CstringZVM_TABLE_PREFIX_SIGNATURE + stringElementSignature;
                   std::string stringTableName = autoTableName->getText();
                   _vectorFindNames.push_back(stringTableName);

                   zlang::CGlobalVariableSymbolAttributes * pciAttributes =
                         new __OPTION(_THROW) zlang::CGlobalVariableSymbolAttributes(zvm::PUBLIC_BY_EXTERN_MODULE);
                   pciAttributes->SetVariableSignature(stringTableSignature);
                   __INSERT_SYMBOL__(autoTableName);

                   _vectorFindNames.pop_back();
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
                std::string stringResultSignature;
                bool bIsTable = false;
                bool bIsReturnReference = false;

                // entering function nest level
                _vectorFindNames.push_back(stringFunctionName);

                zlang::CGlobalFunctionSymbolAttributes * pciAttributes;
                if (bIsStatic)
                {
                  pciAttributes = new zlang::CGlobalFunctionSymbolAttributes(zvm::PRIVATE_FOR_SELF_MODULE);
                }
                else
                {
                  pciAttributes = new zlang::CGlobalFunctionSymbolAttributes(zvm::PUBLIC_BY_SELF_MODULE);
                }
                __INSERT_SYMBOL__(autoName);
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
                pciAttributes->SetReturnSignature(stringResultSignature);

                int nParameterIndex = 0;
                zlang::CParameterSymbolAttributes * pciReturnParameterAttributes = 0;
                if (stringResultSignature != zvm::CstringZVM_VOID_SIGNATURE)
                /* Need a pseudo parameter for function result */
                {
                  _vectorFindNames.push_back(stringFunctionName);  // name same as this function name

                  zlang::CParameterSymbolAttributes * pciAttributes =
                        new zlang::CParameterSymbolAttributes(++nParameterIndex);
                  pciAttributes->SetParameterSignature(stringResultSignature);
                  pciReturnParameterAttributes = pciAttributes;
                  /* borrowed from __INSERT_SYMBOL__() */
                  antlr::RefToken & autoToken = autoName->getSavedToken();
                  int nLineNumber = autoToken->getLine();
                  int nColumnNumber = autoToken->getColumn();
                  try {
                    const zlang::CSymbol_auto & rautoSymbol = _ciSymbolTable.InsertSymbol(_vectorFindNames, pciAttributes);
                  }
                  catch (zlang::ESymbolInsertFailure & e)
                  {
                    std::string stringError = e.what();
                    throw antlr::SemanticException(stringError, _stringFileName, nLineNumber);
                  }
                  /* End of borrowed from __INSERT_SYMBOL__() */

                  _vectorFindNames.pop_back();
                }

                std::string stringFunctionSignature = "(";
              }//---------------------------------------------------------------

              (parameterDeclarationList[nParameterIndex, stringFunctionSignature])?
              {//---------------------------------------------------------------
                stringFunctionSignature += ")";
                stringFunctionSignature += stringResultSignature;
                pciAttributes->SetFunctionSignature(stringFunctionSignature);

                /* now adjust pseudo argument's BP offset */
                if (pciReturnParameterAttributes)
                {
                  pciReturnParameterAttributes->AdjustBPOffset(nParameterIndex);
                }
              }//---------------------------------------------------------------

              codeBlock
              {//---------------------------------------------------------------
                _vectorFindNames.pop_back();
              }//---------------------------------------------------------------
            )
          )
        ;

globalVariableDefinition
        : #(GVARIABLE_DEFINITION
            {//-----------------------------------------------------------------
              bool bIsStatic = false;
            }//-----------------------------------------------------------------
            ("static" {bIsStatic = true;})?

            (   {//-------------------------------------------------------------
                  std::string stringVariableSignature;
                }//-------------------------------------------------------------
                builtInType[stringVariableSignature]

                (#(autoName:IDENTIFIER
                   {//----------------------------------------------------------
                     _vectorFindNames.push_back(autoName->getText());

                     zlang::CGlobalVariableSymbolAttributes * pciAttributes;
                     if (bIsStatic)
                     {
                       pciAttributes = new zlang::CGlobalVariableSymbolAttributes(zvm::PRIVATE_FOR_SELF_MODULE);
                     }
                     else
                     {
                       pciAttributes = new zlang::CGlobalVariableSymbolAttributes(zvm::PUBLIC_BY_SELF_MODULE);
                     }
                     pciAttributes->SetVariableSignature(stringVariableSignature);
                     __INSERT_SYMBOL__(autoName);

                     _vectorFindNames.pop_back();
                   }//----------------------------------------------------------

                   (initializationConstant)?
                 )
                )+

              | {//-------------------------------------------------------------
                  std::string stringElementSignature;
                }//-------------------------------------------------------------
                "table" builtInType[stringElementSignature] autoTableName:IDENTIFIER

                {//-------------------------------------------------------------
                  std::string stringTableSignature = zvm::CstringZVM_TABLE_PREFIX_SIGNATURE + stringElementSignature;
                  std::string stringTableName = autoTableName->getText();
                  _vectorFindNames.push_back(stringTableName);

                  zlang::CGlobalVariableSymbolAttributes * pciAttributes;
                  if (bIsStatic)
                  {
                    pciAttributes = new __OPTION(_THROW) zlang::CGlobalVariableSymbolAttributes(zvm::PRIVATE_FOR_SELF_MODULE);
                  }
                  else
                  {
                    pciAttributes = new __OPTION(_THROW) zlang::CGlobalVariableSymbolAttributes(zvm::PUBLIC_BY_SELF_MODULE);
                  }
                  pciAttributes->SetVariableSignature(stringTableSignature);
                  __INSERT_SYMBOL__(autoTableName);

                  _vectorFindNames.pop_back();
                }//-------------------------------------------------------------

                (tableInit)?
            )
          )
        ;

codeBlock
        : #(CODE_BLOCK
            {//-----------------------------------------------------------------
              int nIndex = 0;
            }//-----------------------------------------------------------------
            (localVariableDefinition[nIndex])*
            compoundStatement
          )
        ;

parameterDeclarationList [int & rnParameterIndex, std::string & rstringParametersSignature]
        : #(PARAMETERS_DECLARATION
            {//-----------------------------------------------------------------
              std::vector<zlang::CParameterSymbolAttributes *> vectorOfPSymbolAttributes;
            }//-----------------------------------------------------------------

            (parameterDeclaration[rnParameterIndex, rstringParametersSignature, vectorOfPSymbolAttributes])+
            {//-----------------------------------------------------------------
              std::vector<zlang::CParameterSymbolAttributes *>::iterator it;
              for (it = vectorOfPSymbolAttributes.begin();
                   it != vectorOfPSymbolAttributes.end();
                   ++it)
              {
                (*it)->AdjustBPOffset(rnParameterIndex);
              }
            }//-----------------------------------------------------------------
          )
        ;

parameterDeclaration [int & rnIndex,
                      std::string & rstringParametersSignature,
                      std::vector<zlang::CParameterSymbolAttributes *> & rvectorOfPSymbolAttributes]
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
            if (bIsTable)
            {
              stringTypeSignature = zvm::CstringZVM_TABLE_PREFIX_SIGNATURE + stringTypeSignature;
            }
            if (bIsReferenceArgument)
            {
              // Turn signature to lower char just for 'function prototype signature'
              zfc::LowerString(stringTypeSignature);
            }
            rstringParametersSignature += stringTypeSignature;

            stringName = autoName->getText();

            _vectorFindNames.push_back(stringName);

            ++rnIndex;
            zlang::CParameterSymbolAttributes * pciAttributes = new zlang::CParameterSymbolAttributes(rnIndex);
            // Turn signature back to upper char
            //zfc::UpperString(stringTypeSignature);
            pciAttributes->SetParameterSignature(stringTypeSignature);
            __INSERT_SYMBOL__(autoName);

            rvectorOfPSymbolAttributes.push_back(pciAttributes);

            _vectorFindNames.pop_back();
          }//-------------------------------------------------------------------
        ;

compoundStatement
        : #(COMPOUND_STATEMENTS (statement)*)
        ;

statement
        :   expression
          | ifStatement
          | whileStatement
          | "break"                    /* Note: single 'TOKEN' can not act as AST root */
          | "continue"
          | #("return" (expression)?)  /* But this is not single 'TOKEN', so it can. */
          | forStatement
        ;

ifStatement
        : #("if" expression compoundStatement (compoundStatement)?)
        ;

whileStatement
        : #("while" expression compoundStatement)
        ;

forStatement
        : #("for" (forExpression1)? (forExpression2)? (forExpression3)? compoundStatement)
        ;

forExpression1
        : #(FOR_EXPRESSION1 expressionDefinition)
        ;

forExpression2
        : #(FOR_EXPRESSION2 expressionDefinition)
        ;

forExpression3
        : #(FOR_EXPRESSION3 expressionDefinition)
        ;

localVariableDefinition [int & rnIndex]
        : #(LVARIABLE_DEFINITION
            (   {//-------------------------------------------------------------
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
                     _vectorFindNames.push_back(autoName->getText());

                     zlang::CLocalVariableSymbolAttributes * pciAttributes =
                           new zlang::CLocalVariableSymbolAttributes(rnIndex);
                     pciAttributes->SetVariableSignature(stringVariableSignature);
                     __INSERT_SYMBOL__(autoName);

                     _vectorFindNames.pop_back();
                   }//----------------------------------------------------------

                   (expression)?
                 )
                )+

              | {//-------------------------------------------------------------
                  std::string stringElementSignature;
                  bool bIsReferenceVariable = false;
                  ++rnIndex;
                }//-------------------------------------------------------------
                "table" builtInType[stringElementSignature] (BAND {bIsReferenceVariable = true;})? autoTableName:IDENTIFIER

                {//-------------------------------------------------------------
                  std::string stringTableSignature = zvm::CstringZVM_TABLE_PREFIX_SIGNATURE + stringElementSignature;
                  if (bIsReferenceVariable)
                  {
                    // Turn signature to lower char
                    zfc::LowerString(stringTableSignature);
                  }

                  std::string stringTableName = autoTableName->getText();
                  _vectorFindNames.push_back(stringTableName);

                  zlang::CLocalVariableSymbolAttributes * pciAttributes =
                        new __OPTION(_THROW) zlang::CLocalVariableSymbolAttributes(rnIndex);
                  pciAttributes->SetVariableSignature(stringTableSignature);
                  __INSERT_SYMBOL__(autoTableName);

                  _vectorFindNames.pop_back();
                }//-------------------------------------------------------------

                (tableInit | expression)?
            )
          )
        ;

tableInit
        : (#(ELEMENT_INIT initializationConstant initializationConstant))+
        ;

builtInType [std::string & rstringSignature]
        :   "byte"      { rstringSignature = zvm::CstringZVM_BYTE_SIGNATURE; }
          | "bool"      { rstringSignature = zvm::CstringZVM_BOOL_SIGNATURE; }
          | "sdword"    { rstringSignature = zvm::CstringZVM_SDWORD_SIGNATURE; }
          | "udword"    { rstringSignature = zvm::CstringZVM_UDWORD_SIGNATURE; }
          | "sqword"    { rstringSignature = zvm::CstringZVM_SQWORD_SIGNATURE; }
          | "uqword"    { rstringSignature = zvm::CstringZVM_UQWORD_SIGNATURE; }
          | "double"    { rstringSignature = zvm::CstringZVM_DOUBLE_SIGNATURE; }
          | "string"    { rstringSignature = zvm::CstringZVM_STRING_SIGNATURE; }
          | "ipaddress" { rstringSignature = zvm::CstringZVM_IPv4ADDR_SIGNATURE; }
          | "pport"     { rstringSignature = zvm::CstringZVM_PPORT_SIGNATURE; }
          | "rope"      { rstringSignature = zvm::CstringZVM_ROPE_SIGNATURE; }
        ;

expression
        : #(EXPRESSION expressionDefinition)
        ;

argumentList
        : (expression)+
        ;

expressionDefinition
        :   #(ASSIGN expressionDefinition expressionDefinition)
          | #(LOR expressionDefinition expressionDefinition)
          | #(LAND expressionDefinition expressionDefinition)
          | #(BOR expressionDefinition expressionDefinition)
          | #(BXOR expressionDefinition expressionDefinition)
          | #(BAND expressionDefinition expressionDefinition)
          | #(NOT_EQUAL expressionDefinition expressionDefinition)
          | #(EQUAL expressionDefinition expressionDefinition)
          | #(LT_ expressionDefinition expressionDefinition)
          | #(GT expressionDefinition expressionDefinition)
          | #(LE expressionDefinition expressionDefinition)
          | #(GE expressionDefinition expressionDefinition)
          | #(SL expressionDefinition expressionDefinition)
          | #(SR expressionDefinition expressionDefinition)
          | #(PLUS expressionDefinition expressionDefinition)
          | #(MINUS expressionDefinition expressionDefinition)
          | #(STAR expressionDefinition expressionDefinition)
          | #(DIV expressionDefinition expressionDefinition)
          | #(MOD expressionDefinition expressionDefinition)
          /*
          | #(INC postfixExpression)
          | #(DEC postfixExpression)
          | #(UNARY_MINUS postfixExpression)
          | #(UNARY_PLUS postfixExpression)
          | #(BNOT postfixExpression)
          | #(LNOT postfixExpression)
          | #(TYPECAST
              {//---------------------------------------------------------------
                std::string stringCastToSignature;
              }//---------------------------------------------------------------
              builtInType[stringCastToSignature] postfixExpression)
          */
          | #(INC expressionDefinition)
          | #(DEC expressionDefinition)
          | #(UNARY_MINUS expressionDefinition)
          | #(UNARY_PLUS expressionDefinition)
          | #(BNOT expressionDefinition)
          | #(LNOT expressionDefinition)
          | #(TYPECAST
              {//---------------------------------------------------------------
                std::string stringCastToSignature;
              }//---------------------------------------------------------------
              builtInType[stringCastToSignature] expressionDefinition)
          | postfixExpression
        ;

postfixExpression
          /*
        :   #(CALLING primaryExpression (argumentList)?)
          | #(DOT primaryExpression IDENTIFIER)
          | #(SUBSCRIPT primaryExpression expression)
          | #(POST_INC primaryExpression)
          | #(POST_DEC primaryExpression)
          */
        :   #(CALLING expressionDefinition (argumentList)?)
          | #(DOT expressionDefinition IDENTIFIER)
          | #(SUBSCRIPT expressionDefinition expression)
          | #(POST_INC expressionDefinition)
          | #(POST_DEC expressionDefinition)
          | primaryExpression
          ;

primaryExpression
	:   IDENTIFIER
          | constant
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

