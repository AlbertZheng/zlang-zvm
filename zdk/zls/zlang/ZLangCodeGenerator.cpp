/* $ANTLR 2.7.1: "zlangpass3.g" -> "ZLangCodeGenerator.cpp"$ */
#include "ZLangCodeGenerator.hpp"
#include "antlr/Token.hpp"
#include "antlr/AST.hpp"
#include "antlr/NoViableAltException.hpp"
#include "antlr/MismatchedTokenException.hpp"
#include "antlr/SemanticException.hpp"
#include "antlr/BitSet.hpp"
ANTLR_BEGIN_NAMESPACE(zlang)
#line 1 "zlangpass3.g"

#line 12 "ZLangCodeGenerator.cpp"
ZLangCodeGenerator::ZLangCodeGenerator()
	: antlr::TreeParser() {
  setTokenNames(_tokenNames);
}

/** ZLang script starting. */
void ZLangCodeGenerator::zlangScript(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto zlangScript_AST_in = _t;
  
#line 296 "zlangpass3.g"
  //-------------------------------------------------------------------
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
  
#line 40 "ZLangCodeGenerator.cpp"
  {
  for (;;) {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case EXTERN_GFUNCTION_DECLARATION:
    {
      externGlobalFunctionDeclaration(_t);
      _t = _retTree;
      break;
    }
    case EXTERN_GVARIABLE_DECLARATION:
    {
      externGlobalVariableDeclaration(_t);
      _t = _retTree;
      break;
    }
    case GVARIABLE_DEFINITION:
    {
      globalVariableDefinition(_t);
      _t = _retTree;
      break;
    }
    case GFUNCTION_DEFINITION:
    {
      globalFunctionDefinition(_t);
      _t = _retTree;
      break;
    }
    default:
    {
      goto _loop3;
    }
    }
  }
  _loop3:;
  }
#line 320 "zlangpass3.g"
  //-------------------------------------------------------------------
  // Generate 'ret' for this pseudo static global function.
  _ciCodeGeneratorHelper.GenerateInstruction(_autoInitializerFunction,
  0,
  zvm::ZVM_ret);
  
#line 85 "ZLangCodeGenerator.cpp"
  _retTree = _t;
}

void ZLangCodeGenerator::externGlobalFunctionDeclaration(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto externGlobalFunctionDeclaration_AST_in = _t;
  zlang::CZLangAST_auto autoName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto __t5 = _t;
  zlang::CZLangAST_auto tmp1_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),EXTERN_GFUNCTION_DECLARATION);
  _t = _t->getFirstChild();
#line 330 "zlangpass3.g"
  //---------------------------------------------------------------
  std::string stringFunctionSignature = "(";
  std::string stringResultSignature;
  bool bIsTable = false;
  bool bIsReturnReference = false;
  
#line 104 "ZLangCodeGenerator.cpp"
  zlang::CZLangAST_auto __t6 = _t;
  autoName = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
  match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
  _t = _t->getFirstChild();
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case LITERAL_table:
  case LITERAL_byte:
  case LITERAL_bool:
  case LITERAL_sdword:
  case LITERAL_udword:
  case LITERAL_sqword:
  case LITERAL_uqword:
  case LITERAL_double:
  case LITERAL_string:
  case LITERAL_ipaddress:
  case LITERAL_pport:
  case LITERAL_rope:
  {
    {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case LITERAL_table:
    {
      zlang::CZLangAST_auto tmp2_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),LITERAL_table);
      _t = _t->getNextSibling();
#line 337 "zlangpass3.g"
      bIsTable = true;
#line 137 "ZLangCodeGenerator.cpp"
      break;
    }
    case LITERAL_byte:
    case LITERAL_bool:
    case LITERAL_sdword:
    case LITERAL_udword:
    case LITERAL_sqword:
    case LITERAL_uqword:
    case LITERAL_double:
    case LITERAL_string:
    case LITERAL_ipaddress:
    case LITERAL_pport:
    case LITERAL_rope:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
    }
    }
    }
    builtInType(_t,stringResultSignature);
    _t = _retTree;
    {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case BAND:
    {
      zlang::CZLangAST_auto tmp3_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),BAND);
      _t = _t->getNextSibling();
#line 337 "zlangpass3.g"
      bIsReturnReference = true;
#line 173 "ZLangCodeGenerator.cpp"
      break;
    }
    case 3:
    case PARAMETERS_DECLARATION:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
    }
    }
    }
#line 338 "zlangpass3.g"
    //-----------------------------------------------------------
    if (bIsTable)
    {
    stringResultSignature = zvm::CstringZVM_TABLE_PREFIX_SIGNATURE + stringResultSignature;
    }
    if (bIsReturnReference)
    {
    // Turn signature to lower char
    zfc::LowerString(stringResultSignature);
    }
    
#line 199 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_void:
  {
    zlang::CZLangAST_auto tmp4_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_void);
    _t = _t->getNextSibling();
#line 350 "zlangpass3.g"
    //-----------------------------------------------------------
    stringResultSignature = zvm::CstringZVM_VOID_SIGNATURE;
    
#line 211 "ZLangCodeGenerator.cpp"
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case PARAMETERS_DECLARATION:
  {
    externParameterDeclarationList(_t,stringFunctionSignature);
    _t = _retTree;
    break;
  }
  case 3:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
#line 355 "zlangpass3.g"
  //---------------------------------------------------------------
  stringFunctionSignature += ")";
  stringFunctionSignature += stringResultSignature;
  
#line 245 "ZLangCodeGenerator.cpp"
  _t = __t6;
  _t = _t->getNextSibling();
  _t = __t5;
  _t = _t->getNextSibling();
#line 361 "zlangpass3.g"
  //-------------------------------------------------------------------
  zlang::CConstantPool & rciConstantPool = _ciCodeGeneratorHelper.GetConstantPool();
  /* insert extern global-function-reference */
  rciConstantPool.InsertGlobalFunctionReference(autoName->getText(),
  stringFunctionSignature,
  zvm::PUBLIC_BY_EXTERN_MODULE);
  
#line 258 "ZLangCodeGenerator.cpp"
  _retTree = _t;
}

void ZLangCodeGenerator::externGlobalVariableDeclaration(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto externGlobalVariableDeclaration_AST_in = _t;
  zlang::CZLangAST_auto autoName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTableName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto __t20 = _t;
  zlang::CZLangAST_auto tmp5_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),EXTERN_GVARIABLE_DECLARATION);
  _t = _t->getFirstChild();
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case LITERAL_byte:
  case LITERAL_bool:
  case LITERAL_sdword:
  case LITERAL_udword:
  case LITERAL_sqword:
  case LITERAL_uqword:
  case LITERAL_double:
  case LITERAL_string:
  case LITERAL_ipaddress:
  case LITERAL_pport:
  case LITERAL_rope:
  {
#line 404 "zlangpass3.g"
    //-------------------------------------------------------------
    std::string stringVariableSignature;
    
#line 291 "ZLangCodeGenerator.cpp"
    builtInType(_t,stringVariableSignature);
    _t = _retTree;
    {
    int _cnt23=0;
    for (;;) {
      if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
        _t = ASTNULL;
      if ((_t->getType()==IDENTIFIER)) {
        autoName = _t;
        match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
        _t = _t->getNextSibling();
#line 409 "zlangpass3.g"
        //------------------------------------------------------------
        zlang::CConstantPool & rciConstantPool = _ciCodeGeneratorHelper.GetConstantPool();
        /* insert extern global-variable-reference */
        rciConstantPool.InsertGlobalVariableReference(autoName->getText(),
        stringVariableSignature,
        zvm::PUBLIC_BY_EXTERN_MODULE);
        
#line 311 "ZLangCodeGenerator.cpp"
      }
      else {
        if ( _cnt23>=1 ) { goto _loop23; } else {throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));}
      }
      
      _cnt23++;
    }
    _loop23:;
    }
    break;
  }
  case LITERAL_table:
  {
#line 418 "zlangpass3.g"
    //-------------------------------------------------------------
    std::string stringElementSignature;
    
#line 329 "ZLangCodeGenerator.cpp"
    zlang::CZLangAST_auto tmp6_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_table);
    _t = _t->getNextSibling();
    builtInType(_t,stringElementSignature);
    _t = _retTree;
    {
    int _cnt25=0;
    for (;;) {
      if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
        _t = ASTNULL;
      if ((_t->getType()==IDENTIFIER)) {
        autoTableName = _t;
        match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
        _t = _t->getNextSibling();
#line 423 "zlangpass3.g"
        //------------------------------------------------------------
        std::string stringTableSignature = zvm::CstringZVM_TABLE_PREFIX_SIGNATURE + stringElementSignature;
        zlang::CConstantPool & rciConstantPool = _ciCodeGeneratorHelper.GetConstantPool();
        /* insert extern global-variable-reference */
        rciConstantPool.InsertGlobalVariableReference(autoTableName->getText(),
        stringTableSignature,
        zvm::PUBLIC_BY_EXTERN_MODULE);
        
#line 353 "ZLangCodeGenerator.cpp"
      }
      else {
        if ( _cnt25>=1 ) { goto _loop25; } else {throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));}
      }
      
      _cnt25++;
    }
    _loop25:;
    }
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
  _t = __t20;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangCodeGenerator::globalVariableDefinition(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto globalVariableDefinition_AST_in = _t;
  zlang::CZLangAST_auto autoName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto __t43 = _t;
  zlang::CZLangAST_auto tmp7_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),GVARIABLE_DEFINITION);
  _t = _t->getFirstChild();
#line 585 "zlangpass3.g"
  //-----------------------------------------------------------------
  bool bIsStatic = false;
  
#line 388 "ZLangCodeGenerator.cpp"
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case LITERAL_static:
  {
    zlang::CZLangAST_auto tmp8_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_static);
    _t = _t->getNextSibling();
#line 588 "zlangpass3.g"
    bIsStatic = true;
#line 400 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_table:
  case LITERAL_byte:
  case LITERAL_bool:
  case LITERAL_sdword:
  case LITERAL_udword:
  case LITERAL_sqword:
  case LITERAL_uqword:
  case LITERAL_double:
  case LITERAL_string:
  case LITERAL_ipaddress:
  case LITERAL_pport:
  case LITERAL_rope:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case LITERAL_byte:
  case LITERAL_bool:
  case LITERAL_sdword:
  case LITERAL_udword:
  case LITERAL_sqword:
  case LITERAL_uqword:
  case LITERAL_double:
  case LITERAL_string:
  case LITERAL_ipaddress:
  case LITERAL_pport:
  case LITERAL_rope:
  {
#line 589 "zlangpass3.g"
    //-------------------------------------------------------------
    std::string stringVariableName;
    std::string stringVariableSignature;
    
#line 445 "ZLangCodeGenerator.cpp"
    builtInType(_t,stringVariableSignature);
    _t = _retTree;
    {
    int _cnt49=0;
    for (;;) {
      if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
        _t = ASTNULL;
      if ((_t->getType()==IDENTIFIER)) {
        zlang::CZLangAST_auto __t47 = _t;
        autoName = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
        match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
        _t = _t->getFirstChild();
#line 595 "zlangpass3.g"
        //----------------------------------------------------------
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
        
#line 483 "ZLangCodeGenerator.cpp"
        {
        if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
          _t = ASTNULL;
        switch ( _t->getType()) {
        case PLUS:
        case MINUS:
        case NUM_INT:
        case NUM_HEX_INT:
        case NUM_QUAD:
        case NUM_HEX_QUAD:
        case NUM_FLOAT:
        case CHAR_LITERAL:
        case STRING_LITERAL:
        case IPv4ADDR_LITERAL:
        case PPORT_LITERAL:
        case LITERAL_true:
        case LITERAL_false:
        case ROPE_LITERAL:
        {
#line 621 "zlangpass3.g"
          //---------------------------------------------------------
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
          
#line 531 "ZLangCodeGenerator.cpp"
          initializationConstant(_t,dequeExpressionAtoms);
          _t = _retTree;
#line 650 "zlangpass3.g"
          //---------------------------------------------------------
          /* generating global variables's initializing codes into "__initializer__()" */
          _ciCodeGeneratorHelper.GenerateExpressionInstruction(_autoInitializerFunction,
          _vectorFindNames,
          dequeExpressionAtoms);
          
#line 541 "ZLangCodeGenerator.cpp"
          break;
        }
        case 3:
        {
          break;
        }
        default:
        {
          throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
        }
        }
        }
        _t = __t47;
        _t = _t->getNextSibling();
      }
      else {
        if ( _cnt49>=1 ) { goto _loop49; } else {throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));}
      }
      
      _cnt49++;
    }
    _loop49:;
    }
    break;
  }
  case LITERAL_table:
  {
#line 660 "zlangpass3.g"
    //-------------------------------------------------------------
    std::string stringTableName;
    int nLineNumber;
    int nColumnNumber;
    
#line 575 "ZLangCodeGenerator.cpp"
    globalTableDefinition(_t,stringTableName, nLineNumber, nColumnNumber, bIsStatic);
    _t = _retTree;
    {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case ELEMENT_INIT:
    {
      globalTableInit(_t,stringTableName, nLineNumber, nColumnNumber);
      _t = _retTree;
      break;
    }
    case 3:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
    }
    }
    }
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
  _t = __t43;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangCodeGenerator::globalFunctionDefinition(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto globalFunctionDefinition_AST_in = _t;
  zlang::CZLangAST_auto autoName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto __t27 = _t;
  zlang::CZLangAST_auto tmp9_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),GFUNCTION_DEFINITION);
  _t = _t->getFirstChild();
#line 438 "zlangpass3.g"
  //-----------------------------------------------------------------
  bool bIsStatic = false;
  
#line 623 "ZLangCodeGenerator.cpp"
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case LITERAL_static:
  {
    zlang::CZLangAST_auto tmp10_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_static);
    _t = _t->getNextSibling();
#line 441 "zlangpass3.g"
    bIsStatic = true;
#line 635 "ZLangCodeGenerator.cpp"
    break;
  }
  case IDENTIFIER:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
  zlang::CZLangAST_auto __t29 = _t;
  autoName = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
  match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
  _t = _t->getFirstChild();
#line 443 "zlangpass3.g"
  //---------------------------------------------------------------
  std::string stringFunctionName = autoName->getText();
  _vectorFindNames.push_back(stringFunctionName);
  
  std::string stringResultSignature;
  std::string stringFunctionSignature = "(";
  std::vector<std::pair<std::string, std::string> > vectorParameters;
  bool bIsTable = false;
  bool bIsReturnReference = false;
  
#line 663 "ZLangCodeGenerator.cpp"
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case LITERAL_table:
  case LITERAL_byte:
  case LITERAL_bool:
  case LITERAL_sdword:
  case LITERAL_udword:
  case LITERAL_sqword:
  case LITERAL_uqword:
  case LITERAL_double:
  case LITERAL_string:
  case LITERAL_ipaddress:
  case LITERAL_pport:
  case LITERAL_rope:
  {
    {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case LITERAL_table:
    {
      zlang::CZLangAST_auto tmp11_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),LITERAL_table);
      _t = _t->getNextSibling();
#line 454 "zlangpass3.g"
      bIsTable = true;
#line 692 "ZLangCodeGenerator.cpp"
      break;
    }
    case LITERAL_byte:
    case LITERAL_bool:
    case LITERAL_sdword:
    case LITERAL_udword:
    case LITERAL_sqword:
    case LITERAL_uqword:
    case LITERAL_double:
    case LITERAL_string:
    case LITERAL_ipaddress:
    case LITERAL_pport:
    case LITERAL_rope:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
    }
    }
    }
    builtInType(_t,stringResultSignature);
    _t = _retTree;
    {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case BAND:
    {
      zlang::CZLangAST_auto tmp12_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),BAND);
      _t = _t->getNextSibling();
#line 454 "zlangpass3.g"
      bIsReturnReference = true;
#line 728 "ZLangCodeGenerator.cpp"
      break;
    }
    case PARAMETERS_DECLARATION:
    case CODE_BLOCK:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
    }
    }
    }
#line 455 "zlangpass3.g"
    //-----------------------------------------------------------
    if (bIsTable)
    {
    stringResultSignature = zvm::CstringZVM_TABLE_PREFIX_SIGNATURE + stringResultSignature;
    }
    if (bIsReturnReference)
    {
    // Turn signature to lower char
    zfc::LowerString(stringResultSignature);
    }
    
#line 754 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_void:
  {
    zlang::CZLangAST_auto tmp13_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_void);
    _t = _t->getNextSibling();
#line 467 "zlangpass3.g"
    //-----------------------------------------------------------
    stringResultSignature = zvm::CstringZVM_VOID_SIGNATURE;
    
#line 766 "ZLangCodeGenerator.cpp"
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
#line 471 "zlangpass3.g"
  //---------------------------------------------------------------
  if (stringResultSignature != zvm::CstringZVM_VOID_SIGNATURE)
  /* Need a pseudo parameter for function return */
  {
  std::pair<std::string, std::string> pairReturnParameter;
  pairReturnParameter.first = stringFunctionName;
  pairReturnParameter.second = stringResultSignature;
  vectorParameters.push_back(pairReturnParameter);
  }
  
#line 786 "ZLangCodeGenerator.cpp"
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case PARAMETERS_DECLARATION:
  {
    parameterDeclarationList(_t,stringFunctionSignature, vectorParameters);
    _t = _retTree;
    break;
  }
  case CODE_BLOCK:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
#line 483 "zlangpass3.g"
  //---------------------------------------------------------------
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
  
#line 847 "ZLangCodeGenerator.cpp"
  codeBlock(_t);
  _t = _retTree;
#line 524 "zlangpass3.g"
  //---------------------------------------------------------------
  // Hack: Automatically generating a tail's 'return' for imposing
  // 'uJump' and 'fJump' can be more safety when 'if-then-else' or
  // 'while' is the lastest statement of a function.
  _ciCodeGeneratorHelper.GenerateInstruction(_autoCurrentFunction,
  0,
  zvm::ZVM_ret);
  
  _vectorFindNames.pop_back();
  
#line 861 "ZLangCodeGenerator.cpp"
  _t = __t29;
  _t = _t->getNextSibling();
  _t = __t27;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangCodeGenerator::builtInType(zlang::CZLangAST_auto _t,
  std::string & rstringType
) {
  zlang::CZLangAST_auto builtInType_AST_in = _t;
  
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case LITERAL_byte:
  {
    zlang::CZLangAST_auto tmp14_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_byte);
    _t = _t->getNextSibling();
#line 1529 "zlangpass3.g"
    rstringType = zvm::CstringZVM_BYTE_SIGNATURE;
#line 884 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_bool:
  {
    zlang::CZLangAST_auto tmp15_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_bool);
    _t = _t->getNextSibling();
#line 1530 "zlangpass3.g"
    rstringType = zvm::CstringZVM_BOOL_SIGNATURE;
#line 894 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_sdword:
  {
    zlang::CZLangAST_auto tmp16_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_sdword);
    _t = _t->getNextSibling();
#line 1531 "zlangpass3.g"
    rstringType = zvm::CstringZVM_SDWORD_SIGNATURE;
#line 904 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_udword:
  {
    zlang::CZLangAST_auto tmp17_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_udword);
    _t = _t->getNextSibling();
#line 1532 "zlangpass3.g"
    rstringType = zvm::CstringZVM_UDWORD_SIGNATURE;
#line 914 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_sqword:
  {
    zlang::CZLangAST_auto tmp18_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_sqword);
    _t = _t->getNextSibling();
#line 1533 "zlangpass3.g"
    rstringType = zvm::CstringZVM_SQWORD_SIGNATURE;
#line 924 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_uqword:
  {
    zlang::CZLangAST_auto tmp19_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_uqword);
    _t = _t->getNextSibling();
#line 1534 "zlangpass3.g"
    rstringType = zvm::CstringZVM_UQWORD_SIGNATURE;
#line 934 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_double:
  {
    zlang::CZLangAST_auto tmp20_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_double);
    _t = _t->getNextSibling();
#line 1535 "zlangpass3.g"
    rstringType = zvm::CstringZVM_DOUBLE_SIGNATURE;
#line 944 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_string:
  {
    zlang::CZLangAST_auto tmp21_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_string);
    _t = _t->getNextSibling();
#line 1536 "zlangpass3.g"
    rstringType = zvm::CstringZVM_STRING_SIGNATURE;
#line 954 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_ipaddress:
  {
    zlang::CZLangAST_auto tmp22_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_ipaddress);
    _t = _t->getNextSibling();
#line 1537 "zlangpass3.g"
    rstringType = zvm::CstringZVM_IPv4ADDR_SIGNATURE;
#line 964 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_pport:
  {
    zlang::CZLangAST_auto tmp23_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_pport);
    _t = _t->getNextSibling();
#line 1538 "zlangpass3.g"
    rstringType = zvm::CstringZVM_PPORT_SIGNATURE;
#line 974 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_rope:
  {
    zlang::CZLangAST_auto tmp24_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_rope);
    _t = _t->getNextSibling();
#line 1539 "zlangpass3.g"
    rstringType = zvm::CstringZVM_ROPE_SIGNATURE;
#line 984 "ZLangCodeGenerator.cpp"
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  _retTree = _t;
}

void ZLangCodeGenerator::externParameterDeclarationList(zlang::CZLangAST_auto _t,
  std::string & rstringParametersSignature
) {
  zlang::CZLangAST_auto externParameterDeclarationList_AST_in = _t;
  
  zlang::CZLangAST_auto __t12 = _t;
  zlang::CZLangAST_auto tmp25_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),PARAMETERS_DECLARATION);
  _t = _t->getFirstChild();
  {
  int _cnt14=0;
  for (;;) {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    if ((_t->getType()==IDENTIFIER)) {
      externParameterDeclaration(_t,rstringParametersSignature);
      _t = _retTree;
    }
    else {
      if ( _cnt14>=1 ) { goto _loop14; } else {throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));}
    }
    
    _cnt14++;
  }
  _loop14:;
  }
  _t = __t12;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangCodeGenerator::externParameterDeclaration(zlang::CZLangAST_auto _t,
  std::string & rstringParametersSignature
) {
  zlang::CZLangAST_auto externParameterDeclaration_AST_in = _t;
  zlang::CZLangAST_auto autoName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
#line 377 "zlangpass3.g"
  //-------------------------------------------------------------------
  std::string stringTypeSignature;
  std::string stringName;
  bool bIsTable = false;
  bool bIsReferenceArgument = false;
  
#line 1039 "ZLangCodeGenerator.cpp"
  zlang::CZLangAST_auto __t16 = _t;
  autoName = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
  match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
  _t = _t->getFirstChild();
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case LITERAL_table:
  {
    zlang::CZLangAST_auto tmp26_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_table);
    _t = _t->getNextSibling();
#line 385 "zlangpass3.g"
    bIsTable = true;
#line 1055 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_byte:
  case LITERAL_bool:
  case LITERAL_sdword:
  case LITERAL_udword:
  case LITERAL_sqword:
  case LITERAL_uqword:
  case LITERAL_double:
  case LITERAL_string:
  case LITERAL_ipaddress:
  case LITERAL_pport:
  case LITERAL_rope:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
  builtInType(_t,stringTypeSignature);
  _t = _retTree;
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case BAND:
  {
    zlang::CZLangAST_auto tmp27_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),BAND);
    _t = _t->getNextSibling();
#line 385 "zlangpass3.g"
    bIsReferenceArgument = true;
#line 1091 "ZLangCodeGenerator.cpp"
    break;
  }
  case 3:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
  _t = __t16;
  _t = _t->getNextSibling();
#line 387 "zlangpass3.g"
  //-------------------------------------------------------------------
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
  
#line 1120 "ZLangCodeGenerator.cpp"
  _retTree = _t;
}

void ZLangCodeGenerator::parameterDeclarationList(zlang::CZLangAST_auto _t,
  std::string & rstringParametersSignature,
                          std::vector<std::pair<std::string, std::string> > & rvectorParameters
) {
  zlang::CZLangAST_auto parameterDeclarationList_AST_in = _t;
  
  zlang::CZLangAST_auto __t35 = _t;
  zlang::CZLangAST_auto tmp28_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),PARAMETERS_DECLARATION);
  _t = _t->getFirstChild();
#line 541 "zlangpass3.g"
  //-----------------------------------------------------------------
  std::pair<std::string, std::string> pairParameter;
  
#line 1138 "ZLangCodeGenerator.cpp"
  {
  int _cnt37=0;
  for (;;) {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    if ((_t->getType()==IDENTIFIER)) {
      parameterDeclaration(_t,rstringParametersSignature, pairParameter);
      _t = _retTree;
#line 546 "zlangpass3.g"
      //-----------------------------------------------------------------
      rvectorParameters.push_back(pairParameter);
      
#line 1151 "ZLangCodeGenerator.cpp"
    }
    else {
      if ( _cnt37>=1 ) { goto _loop37; } else {throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));}
    }
    
    _cnt37++;
  }
  _loop37:;
  }
  _t = __t35;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangCodeGenerator::codeBlock(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto codeBlock_AST_in = _t;
  
  zlang::CZLangAST_auto __t57 = _t;
  zlang::CZLangAST_auto tmp29_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),CODE_BLOCK);
  _t = _t->getFirstChild();
#line 759 "zlangpass3.g"
  //-----------------------------------------------------------------
  int nIndex = 0;
  
#line 1177 "ZLangCodeGenerator.cpp"
  {
  for (;;) {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    if ((_t->getType()==LVARIABLE_DEFINITION)) {
      localVariableDefinition(_t,nIndex);
      _t = _retTree;
    }
    else {
      goto _loop59;
    }
    
  }
  _loop59:;
  }
#line 815 "zlangpass3.g"
  //-----------------------------------------------------------------
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
  
#line 1211 "ZLangCodeGenerator.cpp"
  compoundStatement(_t,stackOuterBackPatchPositions);
  _t = _retTree;
#line 834 "zlangpass3.g"
  //-----------------------------------------------------------------
  if (! _bHaveReturnStatement &&
  _stringCurrentFunctionReturnSignature != zvm::CstringZVM_VOID_SIGNATURE)
  {
  _ciCodeGeneratorHelper.ThrowSemanticError_ReturnStatementIsRequired(_nFunctionDefinitionBeginLineNumber,
  _stringCurrentFunctionName,
  _stringCurrentFunctionReturnSignature);
  }
  
#line 1224 "ZLangCodeGenerator.cpp"
  _t = __t57;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangCodeGenerator::parameterDeclaration(zlang::CZLangAST_auto _t,
  std::string & rstringParametersSignature,
                      std::pair<std::string, std::string> & rpairParameters
) {
  zlang::CZLangAST_auto parameterDeclaration_AST_in = _t;
  zlang::CZLangAST_auto autoName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
#line 555 "zlangpass3.g"
  //-------------------------------------------------------------------
  std::string stringTypeSignature;
  std::string stringName;
  bool bIsTable = false;
  bool bIsReferenceArgument = false;
  
#line 1244 "ZLangCodeGenerator.cpp"
  zlang::CZLangAST_auto __t39 = _t;
  autoName = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
  match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
  _t = _t->getFirstChild();
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case LITERAL_table:
  {
    zlang::CZLangAST_auto tmp30_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_table);
    _t = _t->getNextSibling();
#line 563 "zlangpass3.g"
    bIsTable = true;
#line 1260 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_byte:
  case LITERAL_bool:
  case LITERAL_sdword:
  case LITERAL_udword:
  case LITERAL_sqword:
  case LITERAL_uqword:
  case LITERAL_double:
  case LITERAL_string:
  case LITERAL_ipaddress:
  case LITERAL_pport:
  case LITERAL_rope:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
  builtInType(_t,stringTypeSignature);
  _t = _retTree;
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case BAND:
  {
    zlang::CZLangAST_auto tmp31_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),BAND);
    _t = _t->getNextSibling();
#line 563 "zlangpass3.g"
    bIsReferenceArgument = true;
#line 1296 "ZLangCodeGenerator.cpp"
    break;
  }
  case 3:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
  _t = __t39;
  _t = _t->getNextSibling();
#line 565 "zlangpass3.g"
  //-------------------------------------------------------------------
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
  
#line 1328 "ZLangCodeGenerator.cpp"
  _retTree = _t;
}

void ZLangCodeGenerator::initializationConstant(zlang::CZLangAST_auto _t,
  std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
) {
  zlang::CZLangAST_auto initializationConstant_AST_in = _t;
  zlang::CZLangAST_auto autoTreeLeaf1 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf2 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf3 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf4 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf5 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf6 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf7 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf8 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf9 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf10 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf11 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf12 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case PLUS:
  case MINUS:
  case NUM_INT:
  case NUM_QUAD:
  case NUM_FLOAT:
  {
#line 1969 "zlangpass3.g"
    //-----------------------------------------------------------------
    bool bMinus = false;
    bool bInt = false;
    bool bQuad = false;
    bool bDouble = false;
    
#line 1365 "ZLangCodeGenerator.cpp"
    {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case PLUS:
    {
      zlang::CZLangAST_auto tmp32_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),PLUS);
      _t = _t->getNextSibling();
      break;
    }
    case MINUS:
    {
      zlang::CZLangAST_auto tmp33_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),MINUS);
      _t = _t->getNextSibling();
#line 1975 "zlangpass3.g"
      bMinus = true;
#line 1384 "ZLangCodeGenerator.cpp"
      break;
    }
    case NUM_INT:
    case NUM_QUAD:
    case NUM_FLOAT:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
    }
    }
    }
    {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case NUM_INT:
    {
      autoTreeLeaf1 = _t;
      match(static_cast<antlr::RefAST>(_t),NUM_INT);
      _t = _t->getNextSibling();
#line 1976 "zlangpass3.g"
      bInt = true;
#line 1410 "ZLangCodeGenerator.cpp"
      break;
    }
    case NUM_QUAD:
    {
      autoTreeLeaf2 = _t;
      match(static_cast<antlr::RefAST>(_t),NUM_QUAD);
      _t = _t->getNextSibling();
#line 1977 "zlangpass3.g"
      bQuad = true;
#line 1420 "ZLangCodeGenerator.cpp"
      break;
    }
    case NUM_FLOAT:
    {
      autoTreeLeaf3 = _t;
      match(static_cast<antlr::RefAST>(_t),NUM_FLOAT);
      _t = _t->getNextSibling();
#line 1978 "zlangpass3.g"
      bDouble = true;
#line 1430 "ZLangCodeGenerator.cpp"
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
    }
    }
    }
#line 1980 "zlangpass3.g"
    //-----------------------------------------------------------------
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
    
#line 1477 "ZLangCodeGenerator.cpp"
    break;
  }
  case NUM_HEX_INT:
  {
    autoTreeLeaf4 = _t;
    match(static_cast<antlr::RefAST>(_t),NUM_HEX_INT);
    _t = _t->getNextSibling();
#line 2018 "zlangpass3.g"
    //-----------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf4);
    
#line 1489 "ZLangCodeGenerator.cpp"
    break;
  }
  case NUM_HEX_QUAD:
  {
    autoTreeLeaf5 = _t;
    match(static_cast<antlr::RefAST>(_t),NUM_HEX_QUAD);
    _t = _t->getNextSibling();
#line 2022 "zlangpass3.g"
    //-----------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf5);
    
#line 1501 "ZLangCodeGenerator.cpp"
    break;
  }
  case CHAR_LITERAL:
  {
    autoTreeLeaf6 = _t;
    match(static_cast<antlr::RefAST>(_t),CHAR_LITERAL);
    _t = _t->getNextSibling();
#line 2026 "zlangpass3.g"
    //-----------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf6);
    
#line 1513 "ZLangCodeGenerator.cpp"
    break;
  }
  case STRING_LITERAL:
  {
    autoTreeLeaf7 = _t;
    match(static_cast<antlr::RefAST>(_t),STRING_LITERAL);
    _t = _t->getNextSibling();
#line 2030 "zlangpass3.g"
    //-----------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf7);
    
#line 1525 "ZLangCodeGenerator.cpp"
    break;
  }
  case IPv4ADDR_LITERAL:
  {
    autoTreeLeaf8 = _t;
    match(static_cast<antlr::RefAST>(_t),IPv4ADDR_LITERAL);
    _t = _t->getNextSibling();
#line 2034 "zlangpass3.g"
    //-----------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf8);
    
#line 1537 "ZLangCodeGenerator.cpp"
    break;
  }
  case PPORT_LITERAL:
  {
    autoTreeLeaf9 = _t;
    match(static_cast<antlr::RefAST>(_t),PPORT_LITERAL);
    _t = _t->getNextSibling();
#line 2038 "zlangpass3.g"
    //-----------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf9);
    
#line 1549 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_true:
  {
    autoTreeLeaf10 = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_true);
    _t = _t->getNextSibling();
#line 2042 "zlangpass3.g"
    //-----------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf10);
    
#line 1561 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_false:
  {
    autoTreeLeaf11 = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_false);
    _t = _t->getNextSibling();
#line 2046 "zlangpass3.g"
    //-----------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf11);
    
#line 1573 "ZLangCodeGenerator.cpp"
    break;
  }
  case ROPE_LITERAL:
  {
    autoTreeLeaf12 = _t;
    match(static_cast<antlr::RefAST>(_t),ROPE_LITERAL);
    _t = _t->getNextSibling();
#line 2050 "zlangpass3.g"
    //-----------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf12);
    
#line 1585 "ZLangCodeGenerator.cpp"
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  _retTree = _t;
}

void ZLangCodeGenerator::globalTableDefinition(zlang::CZLangAST_auto _t,
  std::string & rstringTableName,
                       int & rnLineNumber,
                       int & rnColumnNumber,
                       bool bIsStatic
) {
  zlang::CZLangAST_auto globalTableDefinition_AST_in = _t;
  zlang::CZLangAST_auto autoName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
#line 676 "zlangpass3.g"
  //-------------------------------------------------------------------
  std::string stringTableSignature;
  std::string stringElementSignature;
  
#line 1610 "ZLangCodeGenerator.cpp"
  zlang::CZLangAST_auto tmp34_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),LITERAL_table);
  _t = _t->getNextSibling();
  builtInType(_t,stringElementSignature);
  _t = _retTree;
  autoName = _t;
  match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
  _t = _t->getNextSibling();
#line 682 "zlangpass3.g"
  //-------------------------------------------------------------------
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
  
#line 1645 "ZLangCodeGenerator.cpp"
  _retTree = _t;
}

void ZLangCodeGenerator::globalTableInit(zlang::CZLangAST_auto _t,
  std::string & rstringTableName, int nLineNumber, int nColumnNumber
) {
  zlang::CZLangAST_auto globalTableInit_AST_in = _t;
  
  {
  int _cnt55=0;
  for (;;) {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    if ((_t->getType()==ELEMENT_INIT)) {
      zlang::CZLangAST_auto __t54 = _t;
      zlang::CZLangAST_auto tmp35_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),ELEMENT_INIT);
      _t = _t->getFirstChild();
#line 711 "zlangpass3.g"
      //----------------------------------------------------------------
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
      
#line 1699 "ZLangCodeGenerator.cpp"
      initializationConstant(_t,dequeExpressionAtoms);
      _t = _retTree;
      initializationConstant(_t,dequeExpressionAtoms);
      _t = _retTree;
#line 748 "zlangpass3.g"
      //----------------------------------------------------------------
      _ciCodeGeneratorHelper.GenerateExpressionInstruction(_autoInitializerFunction,
      _vectorFindNames,
      dequeExpressionAtoms);
      
#line 1710 "ZLangCodeGenerator.cpp"
      _t = __t54;
      _t = _t->getNextSibling();
    }
    else {
      if ( _cnt55>=1 ) { goto _loop55; } else {throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));}
    }
    
    _cnt55++;
  }
  _loop55:;
  }
  _retTree = _t;
}

void ZLangCodeGenerator::localVariableDefinition(zlang::CZLangAST_auto _t,
  int & rnIndex
) {
  zlang::CZLangAST_auto localVariableDefinition_AST_in = _t;
  zlang::CZLangAST_auto autoName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto __t85 = _t;
  zlang::CZLangAST_auto tmp36_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),LVARIABLE_DEFINITION);
  _t = _t->getFirstChild();
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case LITERAL_byte:
  case LITERAL_bool:
  case LITERAL_sdword:
  case LITERAL_udword:
  case LITERAL_sqword:
  case LITERAL_uqword:
  case LITERAL_double:
  case LITERAL_string:
  case LITERAL_ipaddress:
  case LITERAL_pport:
  case LITERAL_rope:
  {
#line 1258 "zlangpass3.g"
    //-------------------------------------------------------------
    std::string stringVariableName;
    std::string stringVariableSignature;
    bool bIsReferenceVariable = false;
    
#line 1757 "ZLangCodeGenerator.cpp"
    builtInType(_t,stringVariableSignature);
    _t = _retTree;
    {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case BAND:
    {
      zlang::CZLangAST_auto tmp37_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),BAND);
      _t = _t->getNextSibling();
#line 1263 "zlangpass3.g"
      bIsReferenceVariable = true;
#line 1771 "ZLangCodeGenerator.cpp"
      break;
    }
    case IDENTIFIER:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
    }
    }
    }
#line 1264 "zlangpass3.g"
    //-------------------------------------------------------------
    if (bIsReferenceVariable)
    {
    // Turn signature to lower char
    zfc::LowerString(stringVariableSignature);
    }
    
#line 1792 "ZLangCodeGenerator.cpp"
    {
    int _cnt91=0;
    for (;;) {
      if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
        _t = ASTNULL;
      if ((_t->getType()==IDENTIFIER)) {
        zlang::CZLangAST_auto __t89 = _t;
        autoName = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
        match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
        _t = _t->getFirstChild();
#line 1273 "zlangpass3.g"
        //----------------------------------------------------------
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
        
#line 1828 "ZLangCodeGenerator.cpp"
        {
        if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
          _t = ASTNULL;
        switch ( _t->getType()) {
        case EXPRESSION:
        {
#line 1299 "zlangpass3.g"
          //---------------------------------------------------------
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
          
#line 1871 "ZLangCodeGenerator.cpp"
          expression(_t,dequeExpressionAtoms);
          _t = _retTree;
#line 1336 "zlangpass3.g"
          //---------------------------------------------------------
          //> 2001/6/26: Modified
          //_ciCodeGeneratorHelper.GenerateExpressionInstruction(_autoCurrentFunction,
          _ciCodeGeneratorHelper.TurnOnSwitchOfNeedFixTempLocalVariableOffset();
          _ciCodeGeneratorHelper.GenerateExpressionInstruction(_autoCurrentLocalVariablesInitializeSequence,
          _vectorFindNames,
          dequeExpressionAtoms);
          _ciCodeGeneratorHelper.TurnOffSwitchOfNeedFixTempLocalVariableOffset();
          
#line 1884 "ZLangCodeGenerator.cpp"
          break;
        }
        case 3:
        {
          break;
        }
        default:
        {
          throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
        }
        }
        }
#line 1347 "zlangpass3.g"
        //----------------------------------------------------------
        if (bIsReferenceVariable && ! bReferenceHaveInitializer)
        // If it is reference variable and but is not initialized
        {
        _ciCodeGeneratorHelper.ThrowSemanticError_ReferenceVariableMustBeInitialized(nLineNumber,
        nColumnNumber,
        stringVariableName,
        stringVariableSignature);
        }
        
#line 1908 "ZLangCodeGenerator.cpp"
        _t = __t89;
        _t = _t->getNextSibling();
      }
      else {
        if ( _cnt91>=1 ) { goto _loop91; } else {throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));}
      }
      
      _cnt91++;
    }
    _loop91:;
    }
    break;
  }
  case LITERAL_table:
  {
#line 1360 "zlangpass3.g"
    //-------------------------------------------------------------
    std::string stringTableName;
    std::string stringTableSignature;
    int nLineNumber;
    int nColumnNumber;
    bool bIsReferenceVariable = false;
    bool bReferenceHaveInitializer = false;
    ++rnIndex;
    
#line 1934 "ZLangCodeGenerator.cpp"
    localTableDefinition(_t,stringTableName, stringTableSignature, nLineNumber, nColumnNumber, bIsReferenceVariable, rnIndex);
    _t = _retTree;
#line 1370 "zlangpass3.g"
    //-------------------------------------------------------------
    // Refersh the count of now local variables for validing initializing expression
    zlang::CZLangFunction * pciCurrentFunction = dynamic_cast<CZLangFunction *>(_autoCurrentFunction.get());
    pciCurrentFunction->SetLocalVariableCount(rnIndex);
    
#line 1943 "ZLangCodeGenerator.cpp"
    {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case ELEMENT_INIT:
    {
      localTableInit(_t,stringTableName, nLineNumber, nColumnNumber);
      _t = _retTree;
      break;
    }
    case EXPRESSION:
    {
#line 1378 "zlangpass3.g"
      //---------------------------------------------------------
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
      
#line 1992 "ZLangCodeGenerator.cpp"
      expression(_t,dequeExpressionAtoms);
      _t = _retTree;
#line 1414 "zlangpass3.g"
      //---------------------------------------------------------
      _ciCodeGeneratorHelper.TurnOnSwitchOfNeedFixTempLocalVariableOffset();
      _ciCodeGeneratorHelper.GenerateExpressionInstruction(_autoCurrentLocalVariablesInitializeSequence,
      _vectorFindNames,
      dequeExpressionAtoms);
      _ciCodeGeneratorHelper.TurnOffSwitchOfNeedFixTempLocalVariableOffset();
      
#line 2003 "ZLangCodeGenerator.cpp"
      break;
    }
    case 3:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
    }
    }
    }
#line 1422 "zlangpass3.g"
    //-------------------------------------------------------------
    if (bIsReferenceVariable && ! bReferenceHaveInitializer)
    // If it is reference variable and but is not initialized
    {
    _ciCodeGeneratorHelper.ThrowSemanticError_ReferenceVariableMustBeInitialized(nLineNumber,
    nColumnNumber,
    stringTableName,
    stringTableSignature);
    }
    
#line 2027 "ZLangCodeGenerator.cpp"
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
  _t = __t85;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangCodeGenerator::compoundStatement(zlang::CZLangAST_auto _t,
  std::stack<TBackPatchPosition> & rstackOuterBackPatchPositions
) {
  zlang::CZLangAST_auto compoundStatement_AST_in = _t;
  
  zlang::CZLangAST_auto __t61 = _t;
  zlang::CZLangAST_auto tmp38_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),COMPOUND_STATEMENTS);
  _t = _t->getFirstChild();
  {
  for (;;) {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    if ((_tokenSet_0.member(_t->getType()))) {
      statement(_t,rstackOuterBackPatchPositions);
      _t = _retTree;
    }
    else {
      goto _loop63;
    }
    
  }
  _loop63:;
  }
  _t = __t61;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangCodeGenerator::statement(zlang::CZLangAST_auto _t,
  std::stack<TBackPatchPosition> & rstackOuterBackPatchPositions
) {
  zlang::CZLangAST_auto statement_AST_in = _t;
  zlang::CZLangAST_auto autoTreeLeaf1 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf2 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf3 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case EXPRESSION:
  case LITERAL_break:
  case LITERAL_continue:
  case LITERAL_return:
  case LITERAL_if:
  case LITERAL_while:
  {
    {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case EXPRESSION:
    {
#line 851 "zlangpass3.g"
      //----------------------------------------------------------------
      std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> dequeExpressionAtoms;
      
#line 2098 "ZLangCodeGenerator.cpp"
      expression(_t,dequeExpressionAtoms);
      _t = _retTree;
#line 855 "zlangpass3.g"
      //----------------------------------------------------------------
      GenerateExpressionStatement(_autoCurrentFunction, dequeExpressionAtoms);
      
#line 2105 "ZLangCodeGenerator.cpp"
      break;
    }
    case LITERAL_if:
    {
      ifStatement(_t,rstackOuterBackPatchPositions);
      _t = _retTree;
      break;
    }
    case LITERAL_while:
    {
      whileStatement(_t,rstackOuterBackPatchPositions);
      _t = _retTree;
      break;
    }
    case LITERAL_break:
    {
      autoTreeLeaf1 = _t;
      match(static_cast<antlr::RefAST>(_t),LITERAL_break);
      _t = _t->getNextSibling();
#line 863 "zlangpass3.g"
      //----------------------------------------------------------------
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
      
#line 2139 "ZLangCodeGenerator.cpp"
      break;
    }
    case LITERAL_continue:
    {
      autoTreeLeaf2 = _t;
      match(static_cast<antlr::RefAST>(_t),LITERAL_continue);
      _t = _t->getNextSibling();
#line 878 "zlangpass3.g"
      //----------------------------------------------------------------
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
      
#line 2162 "ZLangCodeGenerator.cpp"
      break;
    }
    case LITERAL_return:
    {
      zlang::CZLangAST_auto __t66 = _t;
      autoTreeLeaf3 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
      match(static_cast<antlr::RefAST>(_t),LITERAL_return);
      _t = _t->getFirstChild();
#line 894 "zlangpass3.g"
      //--------------------------------------------------------------
      _bHaveReturnStatement = true;  // denote this function at least have a 'return' statement
      antlr::RefToken & rautoToken = autoTreeLeaf3->getSavedToken();
      int nLineNumber = rautoToken->getLine();
      int nColumnNumber = rautoToken->getColumn();
      bool bHaveReturnValue = false;
      
#line 2179 "ZLangCodeGenerator.cpp"
      {
      if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
        _t = ASTNULL;
      switch ( _t->getType()) {
      case EXPRESSION:
      {
#line 903 "zlangpass3.g"
        //-------------------------------------------------------------
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
        
#line 2220 "ZLangCodeGenerator.cpp"
        expression(_t,dequeExpressionAtoms);
        _t = _retTree;
#line 938 "zlangpass3.g"
        //----------------------------------------------------------------
        _ciCodeGeneratorHelper.GenerateExpressionInstruction(_autoCurrentFunction,
        _vectorFindNames,
        dequeExpressionAtoms);
        
#line 2229 "ZLangCodeGenerator.cpp"
        break;
      }
      case 3:
      {
        break;
      }
      default:
      {
        throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
      }
      }
      }
#line 945 "zlangpass3.g"
      //--------------------------------------------------------------
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
      
#line 2255 "ZLangCodeGenerator.cpp"
      _t = __t66;
      _t = _t->getNextSibling();
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
    }
    }
    }
    break;
  }
  case LITERAL_for:
  {
    forStatement(_t,rstackOuterBackPatchPositions);
    _t = _retTree;
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  _retTree = _t;
}

void ZLangCodeGenerator::expression(zlang::CZLangAST_auto _t,
  std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
) {
  zlang::CZLangAST_auto expression_AST_in = _t;
  
  zlang::CZLangAST_auto __t101 = _t;
  zlang::CZLangAST_auto tmp39_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),EXPRESSION);
  _t = _t->getFirstChild();
  expressionDefinition(_t,rdequeExpressionAtoms);
  _t = _retTree;
  _t = __t101;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangCodeGenerator::ifStatement(zlang::CZLangAST_auto _t,
  std::stack<TBackPatchPosition> & rstackOuterBackPatchPositions
) {
  zlang::CZLangAST_auto ifStatement_AST_in = _t;
  zlang::CZLangAST_auto autoTreeRoot = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto __t69 = _t;
  autoTreeRoot = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
  match(static_cast<antlr::RefAST>(_t),LITERAL_if);
  _t = _t->getFirstChild();
#line 965 "zlangpass3.g"
  //-----------------------------------------------------------------
  std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> dequeExpressionAtoms;
  std::stack<TBackPatchPosition> stackBackPatchPositions;
  
  antlr::RefToken & rautoToken = autoTreeRoot->getSavedToken();
  int nLineNumber = rautoToken->getLine();
  
  zvm::TZVMIndex nLabel_EndOfThen;
  zvm::TZVMIndex nLabel_EndOfIf;
  
#line 2319 "ZLangCodeGenerator.cpp"
  expression(_t,dequeExpressionAtoms);
  _t = _retTree;
#line 977 "zlangpass3.g"
  //-----------------------------------------------------------------
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
  
#line 2345 "ZLangCodeGenerator.cpp"
  compoundStatement(_t,stackBackPatchPositions);
  _t = _retTree;
#line 1001 "zlangpass3.g"
  //-----------------------------------------------------------------
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
  
#line 2363 "ZLangCodeGenerator.cpp"
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case COMPOUND_STATEMENTS:
  {
    compoundStatement(_t,stackBackPatchPositions);
    _t = _retTree;
#line 1017 "zlangpass3.g"
    //----------------------------------------------------------------
    nLabel_EndOfIf = _autoCurrentFunction->GetLabelBookmark();  /* Modify label of EndOfIf */
    
#line 2376 "ZLangCodeGenerator.cpp"
    break;
  }
  case 3:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
#line 1022 "zlangpass3.g"
  //-----------------------------------------------------------------
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
  
#line 2428 "ZLangCodeGenerator.cpp"
  _t = __t69;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangCodeGenerator::whileStatement(zlang::CZLangAST_auto _t,
  std::stack<TBackPatchPosition> & rstackOuterBackPatchPositions
) {
  zlang::CZLangAST_auto whileStatement_AST_in = _t;
  zlang::CZLangAST_auto autoTreeRoot = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto __t72 = _t;
  autoTreeRoot = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
  match(static_cast<antlr::RefAST>(_t),LITERAL_while);
  _t = _t->getFirstChild();
#line 1065 "zlangpass3.g"
  //-----------------------------------------------------------------
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("ZLangCodeGenerator::whileStatement()");
  std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> dequeExpressionAtoms;
  std::stack<TBackPatchPosition> stackBackPatchPositions;
  
  antlr::RefToken & rautoToken = autoTreeRoot->getSavedToken();
  int nLineNumber = rautoToken->getLine();
  
  zvm::TZVMIndex nLabel_BeginOfWhileTest;
  zvm::TZVMIndex nLabel_EndOfWhile;
  
  nLabel_BeginOfWhileTest = _autoCurrentFunction->GetLabelBookmark();
  
#line 2458 "ZLangCodeGenerator.cpp"
  expression(_t,dequeExpressionAtoms);
  _t = _retTree;
#line 1080 "zlangpass3.g"
  //-----------------------------------------------------------------
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
  
#line 2484 "ZLangCodeGenerator.cpp"
  compoundStatement(_t,stackBackPatchPositions);
  _t = _retTree;
#line 1104 "zlangpass3.g"
  //-----------------------------------------------------------------
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
  
#line 2527 "ZLangCodeGenerator.cpp"
  _t = __t72;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangCodeGenerator::forStatement(zlang::CZLangAST_auto _t,
  std::stack<TBackPatchPosition> & rstackOuterBackPatchPositions
) {
  zlang::CZLangAST_auto forStatement_AST_in = _t;
  zlang::CZLangAST_auto autoTreeRoot = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto __t74 = _t;
  autoTreeRoot = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
  match(static_cast<antlr::RefAST>(_t),LITERAL_for);
  _t = _t->getFirstChild();
#line 1148 "zlangpass3.g"
  //-----------------------------------------------------------------
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
  
#line 2560 "ZLangCodeGenerator.cpp"
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case FOR_EXPRESSION1:
  {
    forExpression1(_t,dequeExpressionAtoms);
    _t = _retTree;
#line 1166 "zlangpass3.g"
    //-----------------------------------------------------------------
    // Generating 'initializing expression'
    GenerateExpressionStatement(_autoCurrentFunction, dequeExpressionAtoms);
    
    // Adjust 'begin testing label'
    nLabel_BeginOfForTest = _autoCurrentFunction->GetLabelBookmark();
    
#line 2577 "ZLangCodeGenerator.cpp"
    break;
  }
  case COMPOUND_STATEMENTS:
  case FOR_EXPRESSION2:
  case FOR_EXPRESSION3:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case FOR_EXPRESSION2:
  {
    forExpression2(_t,dequeExpressionAtoms);
    _t = _retTree;
#line 1176 "zlangpass3.g"
    //----------------------------------------------------------------
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
    
#line 2616 "ZLangCodeGenerator.cpp"
    break;
  }
  case COMPOUND_STATEMENTS:
  case FOR_EXPRESSION3:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case FOR_EXPRESSION3:
  {
    forExpression3(_t,dequeExpressionAtoms);
    _t = _retTree;
#line 1194 "zlangpass3.g"
    //----------------------------------------------------------------
    // Generating 'expression3' into a temp container
    GenerateExpressionStatement(autoExpression3InstructionSequence, dequeExpressionAtoms);
    
#line 2643 "ZLangCodeGenerator.cpp"
    break;
  }
  case COMPOUND_STATEMENTS:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
  compoundStatement(_t,stackBackPatchPositions);
  _t = _retTree;
#line 1201 "zlangpass3.g"
  //-----------------------------------------------------------------
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
  
#line 2699 "ZLangCodeGenerator.cpp"
  _t = __t74;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangCodeGenerator::forExpression1(zlang::CZLangAST_auto _t,
  std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
) {
  zlang::CZLangAST_auto forExpression1_AST_in = _t;
  
  zlang::CZLangAST_auto __t79 = _t;
  zlang::CZLangAST_auto tmp40_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),FOR_EXPRESSION1);
  _t = _t->getFirstChild();
  expressionDefinition(_t,rdequeExpressionAtoms);
  _t = _retTree;
  _t = __t79;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangCodeGenerator::forExpression2(zlang::CZLangAST_auto _t,
  std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
) {
  zlang::CZLangAST_auto forExpression2_AST_in = _t;
  
  zlang::CZLangAST_auto __t81 = _t;
  zlang::CZLangAST_auto tmp41_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),FOR_EXPRESSION2);
  _t = _t->getFirstChild();
  expressionDefinition(_t,rdequeExpressionAtoms);
  _t = _retTree;
  _t = __t81;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangCodeGenerator::forExpression3(zlang::CZLangAST_auto _t,
  std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
) {
  zlang::CZLangAST_auto forExpression3_AST_in = _t;
  
  zlang::CZLangAST_auto __t83 = _t;
  zlang::CZLangAST_auto tmp42_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),FOR_EXPRESSION3);
  _t = _t->getFirstChild();
  expressionDefinition(_t,rdequeExpressionAtoms);
  _t = _retTree;
  _t = __t83;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangCodeGenerator::expressionDefinition(zlang::CZLangAST_auto _t,
  std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
) {
  zlang::CZLangAST_auto expressionDefinition_AST_in = _t;
  zlang::CZLangAST_auto autoTreeRoot1 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot2 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot3 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot4 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot5 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot6 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot7 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot8 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot9 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot10 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot11 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot12 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot13 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot14 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot15 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot16 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot17 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot18 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot19 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot20 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot21 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot22 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot23 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot24 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot25 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot26 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case ASSIGN:
  {
    zlang::CZLangAST_auto __t106 = _t;
    autoTreeRoot1 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),ASSIGN);
    _t = _t->getFirstChild();
#line 1563 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot1);
    
#line 2797 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t106;
    _t = _t->getNextSibling();
    break;
  }
  case LOR:
  {
    zlang::CZLangAST_auto __t107 = _t;
    autoTreeRoot2 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),LOR);
    _t = _t->getFirstChild();
#line 1570 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot2);
    
#line 2816 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t107;
    _t = _t->getNextSibling();
    break;
  }
  case LAND:
  {
    zlang::CZLangAST_auto __t108 = _t;
    autoTreeRoot3 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),LAND);
    _t = _t->getFirstChild();
#line 1577 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot3);
    
#line 2835 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t108;
    _t = _t->getNextSibling();
    break;
  }
  case BOR:
  {
    zlang::CZLangAST_auto __t109 = _t;
    autoTreeRoot4 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),BOR);
    _t = _t->getFirstChild();
#line 1584 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot4);
    
#line 2854 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t109;
    _t = _t->getNextSibling();
    break;
  }
  case BXOR:
  {
    zlang::CZLangAST_auto __t110 = _t;
    autoTreeRoot5 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),BXOR);
    _t = _t->getFirstChild();
#line 1591 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot5);
    
#line 2873 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t110;
    _t = _t->getNextSibling();
    break;
  }
  case BAND:
  {
    zlang::CZLangAST_auto __t111 = _t;
    autoTreeRoot6 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),BAND);
    _t = _t->getFirstChild();
#line 1598 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot6);
    
#line 2892 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t111;
    _t = _t->getNextSibling();
    break;
  }
  case NOT_EQUAL:
  {
    zlang::CZLangAST_auto __t112 = _t;
    autoTreeRoot7 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),NOT_EQUAL);
    _t = _t->getFirstChild();
#line 1605 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot7);
    
#line 2911 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t112;
    _t = _t->getNextSibling();
    break;
  }
  case EQUAL:
  {
    zlang::CZLangAST_auto __t113 = _t;
    autoTreeRoot8 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),EQUAL);
    _t = _t->getFirstChild();
#line 1612 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot8);
    
#line 2930 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t113;
    _t = _t->getNextSibling();
    break;
  }
  case LT_:
  {
    zlang::CZLangAST_auto __t114 = _t;
    autoTreeRoot9 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),LT_);
    _t = _t->getFirstChild();
#line 1619 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot9);
    
#line 2949 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t114;
    _t = _t->getNextSibling();
    break;
  }
  case GT:
  {
    zlang::CZLangAST_auto __t115 = _t;
    autoTreeRoot10 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),GT);
    _t = _t->getFirstChild();
#line 1626 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot10);
    
#line 2968 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t115;
    _t = _t->getNextSibling();
    break;
  }
  case LE:
  {
    zlang::CZLangAST_auto __t116 = _t;
    autoTreeRoot11 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),LE);
    _t = _t->getFirstChild();
#line 1633 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot11);
    
#line 2987 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t116;
    _t = _t->getNextSibling();
    break;
  }
  case GE:
  {
    zlang::CZLangAST_auto __t117 = _t;
    autoTreeRoot12 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),GE);
    _t = _t->getFirstChild();
#line 1640 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot12);
    
#line 3006 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t117;
    _t = _t->getNextSibling();
    break;
  }
  case SL:
  {
    zlang::CZLangAST_auto __t118 = _t;
    autoTreeRoot13 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),SL);
    _t = _t->getFirstChild();
#line 1647 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot13);
    
#line 3025 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t118;
    _t = _t->getNextSibling();
    break;
  }
  case SR:
  {
    zlang::CZLangAST_auto __t119 = _t;
    autoTreeRoot14 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),SR);
    _t = _t->getFirstChild();
#line 1654 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot14);
    
#line 3044 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t119;
    _t = _t->getNextSibling();
    break;
  }
  case PLUS:
  {
    zlang::CZLangAST_auto __t120 = _t;
    autoTreeRoot15 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),PLUS);
    _t = _t->getFirstChild();
#line 1661 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot15);
    
#line 3063 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t120;
    _t = _t->getNextSibling();
    break;
  }
  case MINUS:
  {
    zlang::CZLangAST_auto __t121 = _t;
    autoTreeRoot16 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),MINUS);
    _t = _t->getFirstChild();
#line 1668 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot16);
    
#line 3082 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t121;
    _t = _t->getNextSibling();
    break;
  }
  case STAR:
  {
    zlang::CZLangAST_auto __t122 = _t;
    autoTreeRoot17 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),STAR);
    _t = _t->getFirstChild();
#line 1675 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot17);
    
#line 3101 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t122;
    _t = _t->getNextSibling();
    break;
  }
  case DIV:
  {
    zlang::CZLangAST_auto __t123 = _t;
    autoTreeRoot18 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),DIV);
    _t = _t->getFirstChild();
#line 1682 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot18);
    
#line 3120 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t123;
    _t = _t->getNextSibling();
    break;
  }
  case MOD:
  {
    zlang::CZLangAST_auto __t124 = _t;
    autoTreeRoot19 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),MOD);
    _t = _t->getFirstChild();
#line 1689 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot19);
    
#line 3139 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t124;
    _t = _t->getNextSibling();
    break;
  }
  case INC:
  {
    zlang::CZLangAST_auto __t125 = _t;
    autoTreeRoot20 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),INC);
    _t = _t->getFirstChild();
#line 1753 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot20);
    
#line 3158 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t125;
    _t = _t->getNextSibling();
    break;
  }
  case DEC:
  {
    zlang::CZLangAST_auto __t126 = _t;
    autoTreeRoot21 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),DEC);
    _t = _t->getFirstChild();
#line 1759 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot21);
    
#line 3175 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t126;
    _t = _t->getNextSibling();
    break;
  }
  case UNARY_MINUS:
  {
    zlang::CZLangAST_auto __t127 = _t;
    autoTreeRoot22 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),UNARY_MINUS);
    _t = _t->getFirstChild();
#line 1765 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot22);
    
#line 3192 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t127;
    _t = _t->getNextSibling();
    break;
  }
  case UNARY_PLUS:
  {
    zlang::CZLangAST_auto __t128 = _t;
    autoTreeRoot23 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),UNARY_PLUS);
    _t = _t->getFirstChild();
#line 1771 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot23);
    
#line 3209 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t128;
    _t = _t->getNextSibling();
    break;
  }
  case BNOT:
  {
    zlang::CZLangAST_auto __t129 = _t;
    autoTreeRoot24 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),BNOT);
    _t = _t->getFirstChild();
#line 1777 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot24);
    
#line 3226 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t129;
    _t = _t->getNextSibling();
    break;
  }
  case LNOT:
  {
    zlang::CZLangAST_auto __t130 = _t;
    autoTreeRoot25 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),LNOT);
    _t = _t->getFirstChild();
#line 1783 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot25);
    
#line 3243 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t130;
    _t = _t->getNextSibling();
    break;
  }
  case TYPECAST:
  {
    zlang::CZLangAST_auto __t131 = _t;
    autoTreeRoot26 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),TYPECAST);
    _t = _t->getFirstChild();
#line 1789 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot26);
    std::string stringCastToSignature;
    
#line 3261 "ZLangCodeGenerator.cpp"
    builtInType(_t,stringCastToSignature);
    _t = _retTree;
#line 1794 "zlangpass3.g"
    //---------------------------------------------------------------
    zlang::CCodeGeneratorHelper::TExpressionAtom tOperand;
    tOperand.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERAND;
    tOperand.nTokenType = ZLangCodeGeneratorTokenTypes::CAST_LITERAL;
    tOperand.stringTokenText = stringCastToSignature;
    antlr::RefToken & autoToken = autoTreeRoot26->getSavedToken();
    tOperand.nLineNumber = autoToken->getLine();
    tOperand.nColumnNumber = autoToken->getColumn();
    rdequeExpressionAtoms.push_back(tOperand);
    
#line 3275 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t131;
    _t = _t->getNextSibling();
    break;
  }
  case SUBSCRIPT:
  case CALLING:
  case POST_INC:
  case POST_DEC:
  case IDENTIFIER:
  case DOT:
  case NUM_INT:
  case NUM_HEX_INT:
  case NUM_QUAD:
  case NUM_HEX_QUAD:
  case NUM_FLOAT:
  case CHAR_LITERAL:
  case STRING_LITERAL:
  case IPv4ADDR_LITERAL:
  case PPORT_LITERAL:
  case LITERAL_true:
  case LITERAL_false:
  case ROPE_LITERAL:
  {
    postfixExpression(_t,rdequeExpressionAtoms);
    _t = _retTree;
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  _retTree = _t;
}

void ZLangCodeGenerator::localTableDefinition(zlang::CZLangAST_auto _t,
  std::string & rstringTableName,
                      std::string & rstringTableSignature,
                      int & rnLineNumber,
                      int & rnColumnNumber,
                      bool & rbIsReferenceVariable,
                      int nVariableIndex
) {
  zlang::CZLangAST_auto localTableDefinition_AST_in = _t;
  zlang::CZLangAST_auto autoName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
#line 1442 "zlangpass3.g"
  //-------------------------------------------------------------------
  std::string stringElementSignature;
  
#line 3328 "ZLangCodeGenerator.cpp"
  zlang::CZLangAST_auto tmp43_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),LITERAL_table);
  _t = _t->getNextSibling();
  builtInType(_t,stringElementSignature);
  _t = _retTree;
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case BAND:
  {
    zlang::CZLangAST_auto tmp44_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),BAND);
    _t = _t->getNextSibling();
#line 1446 "zlangpass3.g"
    rbIsReferenceVariable = true;
#line 3345 "ZLangCodeGenerator.cpp"
    break;
  }
  case IDENTIFIER:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
  autoName = _t;
  match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
  _t = _t->getNextSibling();
#line 1447 "zlangpass3.g"
  //-------------------------------------------------------------------
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
  
#line 3387 "ZLangCodeGenerator.cpp"
  _retTree = _t;
}

void ZLangCodeGenerator::localTableInit(zlang::CZLangAST_auto _t,
  std::string & rstringTableName,
                int nLineNumber,
                int nColumnNumber
) {
  zlang::CZLangAST_auto localTableInit_AST_in = _t;
  
  {
  int _cnt98=0;
  for (;;) {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    if ((_t->getType()==ELEMENT_INIT)) {
      zlang::CZLangAST_auto __t97 = _t;
      zlang::CZLangAST_auto tmp45_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),ELEMENT_INIT);
      _t = _t->getFirstChild();
#line 1478 "zlangpass3.g"
      //----------------------------------------------------------------
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
      
#line 3443 "ZLangCodeGenerator.cpp"
      initializationConstant(_t,dequeExpressionAtoms);
      _t = _retTree;
      initializationConstant(_t,dequeExpressionAtoms);
      _t = _retTree;
#line 1515 "zlangpass3.g"
      //----------------------------------------------------------------
      //> 2001/6/26: Modified
      //_ciCodeGeneratorHelper.GenerateExpressionInstruction(_autoCurrentFunction,
      _ciCodeGeneratorHelper.TurnOnSwitchOfNeedFixTempLocalVariableOffset();
      _ciCodeGeneratorHelper.GenerateExpressionInstruction(_autoCurrentLocalVariablesInitializeSequence,
      _vectorFindNames,
      dequeExpressionAtoms);
      _ciCodeGeneratorHelper.TurnOffSwitchOfNeedFixTempLocalVariableOffset();
      
#line 3458 "ZLangCodeGenerator.cpp"
      _t = __t97;
      _t = _t->getNextSibling();
    }
    else {
      if ( _cnt98>=1 ) { goto _loop98; } else {throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));}
    }
    
    _cnt98++;
  }
  _loop98:;
  }
  _retTree = _t;
}

void ZLangCodeGenerator::argumentList(zlang::CZLangAST_auto _t,
  std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
) {
  zlang::CZLangAST_auto argumentList_AST_in = _t;
  
  {
  int _cnt104=0;
  for (;;) {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    if ((_t->getType()==EXPRESSION)) {
      expression(_t,rdequeExpressionAtoms);
      _t = _retTree;
#line 1548 "zlangpass3.g"
      //------------------------------------------------------------------
      /* borrow from __PREPARE_A_OPERATOR__ */
      zlang::CCodeGeneratorHelper::TExpressionAtom tOperator;
      tOperator.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERATOR;
      tOperator.nTokenType = ZLangCodeGeneratorTokenTypes::PASS_A_ARGUMENT;
      tOperator.stringTokenText = "PASS_A_ARGUMENT";
      tOperator.nLineNumber = 0;
      tOperator.nColumnNumber = 0;
      rdequeExpressionAtoms.push_back(tOperator);
      
#line 3497 "ZLangCodeGenerator.cpp"
    }
    else {
      if ( _cnt104>=1 ) { goto _loop104; } else {throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));}
    }
    
    _cnt104++;
  }
  _loop104:;
  }
  _retTree = _t;
}

void ZLangCodeGenerator::postfixExpression(zlang::CZLangAST_auto _t,
  std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
) {
  zlang::CZLangAST_auto postfixExpression_AST_in = _t;
  zlang::CZLangAST_auto autoTreeRoot1 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot2 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot3 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot4 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeRoot5 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case CALLING:
  {
    zlang::CZLangAST_auto __t133 = _t;
    autoTreeRoot1 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),CALLING);
    _t = _t->getFirstChild();
#line 1859 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot1);
    
#line 3534 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case EXPRESSION:
    {
      argumentList(_t,rdequeExpressionAtoms);
      _t = _retTree;
      break;
    }
    case 3:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
    }
    }
    }
#line 1864 "zlangpass3.g"
    //-------------------------------------------------------------------
    ///> borrow from __PREPARE_A_OPERATOR__
    zlang::CCodeGeneratorHelper::TExpressionAtom tOperator;
    tOperator.eTag = zlang::CCodeGeneratorHelper::TExpressionAtom::tatOPERATOR;
    tOperator.nTokenType = ZLangCodeGeneratorTokenTypes::ARGUMENTS_END;
    tOperator.stringTokenText = "ARGUMENTS_END";
    tOperator.nLineNumber = 0;
    tOperator.nColumnNumber = 0;
    rdequeExpressionAtoms.push_back(tOperator);
    
#line 3568 "ZLangCodeGenerator.cpp"
    _t = __t133;
    _t = _t->getNextSibling();
    break;
  }
  case DOT:
  {
    zlang::CZLangAST_auto __t135 = _t;
    autoTreeRoot2 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),DOT);
    _t = _t->getFirstChild();
#line 1876 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot2);
    
#line 3583 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    autoTreeLeaf = _t;
    match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
    _t = _t->getNextSibling();
#line 1881 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf);
    
#line 3593 "ZLangCodeGenerator.cpp"
    _t = __t135;
    _t = _t->getNextSibling();
    break;
  }
  case SUBSCRIPT:
  {
    zlang::CZLangAST_auto __t136 = _t;
    autoTreeRoot3 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),SUBSCRIPT);
    _t = _t->getFirstChild();
#line 1886 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot3);
    
#line 3608 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    expression(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t136;
    _t = _t->getNextSibling();
    break;
  }
  case POST_INC:
  {
    zlang::CZLangAST_auto __t137 = _t;
    autoTreeRoot4 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),POST_INC);
    _t = _t->getFirstChild();
#line 1893 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot4);
    
#line 3627 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t137;
    _t = _t->getNextSibling();
    break;
  }
  case POST_DEC:
  {
    zlang::CZLangAST_auto __t138 = _t;
    autoTreeRoot5 = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
    match(static_cast<antlr::RefAST>(_t),POST_DEC);
    _t = _t->getFirstChild();
#line 1899 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERATOR__(autoTreeRoot5);
    
#line 3644 "ZLangCodeGenerator.cpp"
    expressionDefinition(_t,rdequeExpressionAtoms);
    _t = _retTree;
    _t = __t138;
    _t = _t->getNextSibling();
    break;
  }
  case IDENTIFIER:
  case NUM_INT:
  case NUM_HEX_INT:
  case NUM_QUAD:
  case NUM_HEX_QUAD:
  case NUM_FLOAT:
  case CHAR_LITERAL:
  case STRING_LITERAL:
  case IPv4ADDR_LITERAL:
  case PPORT_LITERAL:
  case LITERAL_true:
  case LITERAL_false:
  case ROPE_LITERAL:
  {
    primaryExpression(_t,rdequeExpressionAtoms);
    _t = _retTree;
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  _retTree = _t;
}

void ZLangCodeGenerator::primaryExpression(zlang::CZLangAST_auto _t,
  std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
) {
  zlang::CZLangAST_auto primaryExpression_AST_in = _t;
  zlang::CZLangAST_auto autoTreeLeaf = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case IDENTIFIER:
  {
    autoTreeLeaf = _t;
    match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
    _t = _t->getNextSibling();
#line 1909 "zlangpass3.g"
    //-----------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf);
    
#line 3695 "ZLangCodeGenerator.cpp"
    break;
  }
  case NUM_INT:
  case NUM_HEX_INT:
  case NUM_QUAD:
  case NUM_HEX_QUAD:
  case NUM_FLOAT:
  case CHAR_LITERAL:
  case STRING_LITERAL:
  case IPv4ADDR_LITERAL:
  case PPORT_LITERAL:
  case LITERAL_true:
  case LITERAL_false:
  case ROPE_LITERAL:
  {
    constant(_t,rdequeExpressionAtoms);
    _t = _retTree;
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  _retTree = _t;
}

void ZLangCodeGenerator::constant(zlang::CZLangAST_auto _t,
  std::deque<zlang::CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms
) {
  zlang::CZLangAST_auto constant_AST_in = _t;
  zlang::CZLangAST_auto autoTreeLeaf1 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf2 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf3 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf4 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf5 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf6 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf7 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf8 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf9 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf10 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf11 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTreeLeaf12 = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case NUM_INT:
  {
    autoTreeLeaf1 = _t;
    match(static_cast<antlr::RefAST>(_t),NUM_INT);
    _t = _t->getNextSibling();
#line 1918 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf1);
    
#line 3753 "ZLangCodeGenerator.cpp"
    break;
  }
  case NUM_HEX_INT:
  {
    autoTreeLeaf2 = _t;
    match(static_cast<antlr::RefAST>(_t),NUM_HEX_INT);
    _t = _t->getNextSibling();
#line 1922 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf2);
    
#line 3765 "ZLangCodeGenerator.cpp"
    break;
  }
  case NUM_QUAD:
  {
    autoTreeLeaf3 = _t;
    match(static_cast<antlr::RefAST>(_t),NUM_QUAD);
    _t = _t->getNextSibling();
#line 1926 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf3);
    
#line 3777 "ZLangCodeGenerator.cpp"
    break;
  }
  case NUM_HEX_QUAD:
  {
    autoTreeLeaf4 = _t;
    match(static_cast<antlr::RefAST>(_t),NUM_HEX_QUAD);
    _t = _t->getNextSibling();
#line 1930 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf4);
    
#line 3789 "ZLangCodeGenerator.cpp"
    break;
  }
  case NUM_FLOAT:
  {
    autoTreeLeaf5 = _t;
    match(static_cast<antlr::RefAST>(_t),NUM_FLOAT);
    _t = _t->getNextSibling();
#line 1934 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf5);
    
#line 3801 "ZLangCodeGenerator.cpp"
    break;
  }
  case CHAR_LITERAL:
  {
    autoTreeLeaf6 = _t;
    match(static_cast<antlr::RefAST>(_t),CHAR_LITERAL);
    _t = _t->getNextSibling();
#line 1938 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf6);
    
#line 3813 "ZLangCodeGenerator.cpp"
    break;
  }
  case STRING_LITERAL:
  {
    autoTreeLeaf7 = _t;
    match(static_cast<antlr::RefAST>(_t),STRING_LITERAL);
    _t = _t->getNextSibling();
#line 1942 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf7);
    
#line 3825 "ZLangCodeGenerator.cpp"
    break;
  }
  case IPv4ADDR_LITERAL:
  {
    autoTreeLeaf8 = _t;
    match(static_cast<antlr::RefAST>(_t),IPv4ADDR_LITERAL);
    _t = _t->getNextSibling();
#line 1946 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf8);
    
#line 3837 "ZLangCodeGenerator.cpp"
    break;
  }
  case PPORT_LITERAL:
  {
    autoTreeLeaf9 = _t;
    match(static_cast<antlr::RefAST>(_t),PPORT_LITERAL);
    _t = _t->getNextSibling();
#line 1950 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf9);
    
#line 3849 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_true:
  {
    autoTreeLeaf10 = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_true);
    _t = _t->getNextSibling();
#line 1954 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf10);
    
#line 3861 "ZLangCodeGenerator.cpp"
    break;
  }
  case LITERAL_false:
  {
    autoTreeLeaf11 = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_false);
    _t = _t->getNextSibling();
#line 1958 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf11);
    
#line 3873 "ZLangCodeGenerator.cpp"
    break;
  }
  case ROPE_LITERAL:
  {
    autoTreeLeaf12 = _t;
    match(static_cast<antlr::RefAST>(_t),ROPE_LITERAL);
    _t = _t->getNextSibling();
#line 1962 "zlangpass3.g"
    //---------------------------------------------------------------
    __PREPARE_A_OPERAND__(autoTreeLeaf12);
    
#line 3885 "ZLangCodeGenerator.cpp"
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
  _retTree = _t;
}

zlang::CZLangAST_auto ZLangCodeGenerator::getAST()
{
	return returnAST;
}

const char* ZLangCodeGenerator::_tokenNames[] = {
  "<0>",
  "EOF",
  "<2>",
  "NULL_TREE_LOOKAHEAD",
  "EXTERN_GFUNCTION_DECLARATION",
  "EXTERN_GVARIABLE_DECLARATION",
  "GFUNCTION_DEFINITION",
  "GVARIABLE_DEFINITION",
  "PARAMETERS_DECLARATION",
  "LVARIABLE_DEFINITION",
  "ELEMENT_INIT",
  "CODE_BLOCK",
  "COMPOUND_STATEMENTS",
  "EXPRESSION",
  "UNARY_PLUS",
  "UNARY_MINUS",
  "TYPECAST",
  "SUBSCRIPT",
  "CALLING",
  "POST_INC",
  "POST_DEC",
  "FOR_EXPRESSION1",
  "FOR_EXPRESSION2",
  "FOR_EXPRESSION3",
  "\"extern\"",
  "\"table\"",
  "<",
  ">",
  "&",
  "an identifier",
  "(",
  ")",
  ";",
  ",",
  "\"void\"",
  "\"static\"",
  "=",
  "LCURLY",
  "}",
  "\"break\"",
  "\"continue\"",
  "\"return\"",
  "\"if\"",
  "\"else\"",
  "\"while\"",
  "\"for\"",
  "\"byte\"",
  "\"bool\"",
  "\"sdword\"",
  "\"udword\"",
  "\"sqword\"",
  "\"uqword\"",
  "\"double\"",
  "\"string\"",
  "\"ipaddress\"",
  "\"pport\"",
  "\"rope\"",
  "||",
  "&&",
  "|",
  "^",
  "!=",
  "==",
  "<=",
  ">=",
  "<<",
  ">>",
  "+",
  "-",
  "*",
  "/",
  "%",
  "++",
  "--",
  "~",
  "!",
  ".",
  "[",
  "]",
  "an integer value",
  "a hexadecimal numeric value",
  "NUM_QUAD",
  "NUM_HEX_QUAD",
  "an floating point value",
  "a character literal",
  "a string literal",
  "IPv4 address or port literal",
  "PPORT_LITERAL",
  "\"true\"",
  "\"false\"",
  "a rope-string literal",
  "CAST_LITERAL",
  "PASS_A_ARGUMENT",
  "ARGUMENTS_END",
  "SUBSCRIPT_ADDRESS",
  "NESTED_ASSIGN",
  "ADVANCE_CAST",
  "REFERENCE_ADDRESS_ASSIGN",
  "RETURN_PSEUDO_ASSIGN",
  0
};

const unsigned long ZLangCodeGenerator::_tokenSet_0_data_[] = { 8192UL, 14208UL, 0UL, 0UL };
// EXPRESSION "break" "continue" "return" "if" "while" "for" 
const antlr::BitSet ZLangCodeGenerator::_tokenSet_0(_tokenSet_0_data_,4);


ANTLR_END_NAMESPACE
