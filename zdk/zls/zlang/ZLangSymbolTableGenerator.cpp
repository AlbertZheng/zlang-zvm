/* $ANTLR 2.7.1: "zlangpass2.g" -> "ZLangSymbolTableGenerator.cpp"$ */
#include "ZLangSymbolTableGenerator.hpp"
#include "antlr/Token.hpp"
#include "antlr/AST.hpp"
#include "antlr/NoViableAltException.hpp"
#include "antlr/MismatchedTokenException.hpp"
#include "antlr/SemanticException.hpp"
#include "antlr/BitSet.hpp"
ANTLR_BEGIN_NAMESPACE(zlang)
#line 1 "zlangpass2.g"

#line 12 "ZLangSymbolTableGenerator.cpp"
ZLangSymbolTableGenerator::ZLangSymbolTableGenerator()
	: antlr::TreeParser() {
  setTokenNames(_tokenNames);
}

/** ZLang script starting. */
void ZLangSymbolTableGenerator::zlangScript(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto zlangScript_AST_in = _t;
  
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
  _retTree = _t;
}

void ZLangSymbolTableGenerator::externGlobalFunctionDeclaration(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto externGlobalFunctionDeclaration_AST_in = _t;
  zlang::CZLangAST_auto autoName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto __t5 = _t;
  zlang::CZLangAST_auto tmp1_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),EXTERN_GFUNCTION_DECLARATION);
  _t = _t->getFirstChild();
  zlang::CZLangAST_auto __t6 = _t;
  autoName = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
  match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
  _t = _t->getFirstChild();
#line 129 "zlangpass2.g"
  //---------------------------------------------------------------
  _vectorFindNames.push_back(autoName->getText());
  
  zlang::CGlobalFunctionSymbolAttributes * pciAttributes =
  new __OPTION(_THROW) zlang::CGlobalFunctionSymbolAttributes(zvm::PUBLIC_BY_EXTERN_MODULE);
  __INSERT_SYMBOL__(autoName);
  
  std::string stringResultSignature;
  bool bIsTable = false;
  bool bIsReturnReference = false;
  
#line 86 "ZLangSymbolTableGenerator.cpp"
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
#line 141 "zlangpass2.g"
      bIsTable = true;
#line 115 "ZLangSymbolTableGenerator.cpp"
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
#line 141 "zlangpass2.g"
      bIsReturnReference = true;
#line 151 "ZLangSymbolTableGenerator.cpp"
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
#line 142 "zlangpass2.g"
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
    
#line 177 "ZLangSymbolTableGenerator.cpp"
    break;
  }
  case LITERAL_void:
  {
    zlang::CZLangAST_auto tmp4_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_void);
    _t = _t->getNextSibling();
#line 154 "zlangpass2.g"
    //-----------------------------------------------------------
    stringResultSignature = zvm::CstringZVM_VOID_SIGNATURE;
    
#line 189 "ZLangSymbolTableGenerator.cpp"
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
#line 158 "zlangpass2.g"
  //---------------------------------------------------------------
  pciAttributes->SetReturnSignature(stringResultSignature);
  std::string stringFunctionSignature = "(";
  
#line 203 "ZLangSymbolTableGenerator.cpp"
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
#line 164 "zlangpass2.g"
  //---------------------------------------------------------------
  stringFunctionSignature += ")";
  stringFunctionSignature += stringResultSignature;
  pciAttributes->SetFunctionSignature(stringFunctionSignature);
  
  _vectorFindNames.pop_back();
  
#line 232 "ZLangSymbolTableGenerator.cpp"
  _t = __t6;
  _t = _t->getNextSibling();
  _t = __t5;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangSymbolTableGenerator::externGlobalVariableDeclaration(zlang::CZLangAST_auto _t) {
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
#line 207 "zlangpass2.g"
    //-------------------------------------------------------------
    std::string stringVariableSignature;
    
#line 269 "ZLangSymbolTableGenerator.cpp"
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
#line 213 "zlangpass2.g"
        //------------------------------------------------------------
        _vectorFindNames.push_back(autoName->getText());
        
        zlang::CGlobalVariableSymbolAttributes * pciAttributes =
        new __OPTION(_THROW) zlang::CGlobalVariableSymbolAttributes(zvm::PUBLIC_BY_EXTERN_MODULE);
        pciAttributes->SetVariableSignature(stringVariableSignature);
        __INSERT_SYMBOL__(autoName);
        
        _vectorFindNames.pop_back();
        
#line 292 "ZLangSymbolTableGenerator.cpp"
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
#line 225 "zlangpass2.g"
    //-------------------------------------------------------------
    std::string stringElementSignature;
    
#line 310 "ZLangSymbolTableGenerator.cpp"
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
#line 231 "zlangpass2.g"
        //------------------------------------------------------------
        std::string stringTableSignature = zvm::CstringZVM_TABLE_PREFIX_SIGNATURE + stringElementSignature;
        std::string stringTableName = autoTableName->getText();
        _vectorFindNames.push_back(stringTableName);
        
        zlang::CGlobalVariableSymbolAttributes * pciAttributes =
        new __OPTION(_THROW) zlang::CGlobalVariableSymbolAttributes(zvm::PUBLIC_BY_EXTERN_MODULE);
        pciAttributes->SetVariableSignature(stringTableSignature);
        __INSERT_SYMBOL__(autoTableName);
        
        _vectorFindNames.pop_back();
        
#line 338 "ZLangSymbolTableGenerator.cpp"
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

void ZLangSymbolTableGenerator::globalVariableDefinition(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto globalVariableDefinition_AST_in = _t;
  zlang::CZLangAST_auto autoName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTableName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto __t35 = _t;
  zlang::CZLangAST_auto tmp7_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),GVARIABLE_DEFINITION);
  _t = _t->getFirstChild();
#line 351 "zlangpass2.g"
  //-----------------------------------------------------------------
  bool bIsStatic = false;
  
#line 374 "ZLangSymbolTableGenerator.cpp"
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case LITERAL_static:
  {
    zlang::CZLangAST_auto tmp8_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_static);
    _t = _t->getNextSibling();
#line 354 "zlangpass2.g"
    bIsStatic = true;
#line 386 "ZLangSymbolTableGenerator.cpp"
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
#line 356 "zlangpass2.g"
    //-------------------------------------------------------------
    std::string stringVariableSignature;
    
#line 430 "ZLangSymbolTableGenerator.cpp"
    builtInType(_t,stringVariableSignature);
    _t = _retTree;
    {
    int _cnt41=0;
    for (;;) {
      if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
        _t = ASTNULL;
      if ((_t->getType()==IDENTIFIER)) {
        zlang::CZLangAST_auto __t39 = _t;
        autoName = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
        match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
        _t = _t->getFirstChild();
#line 362 "zlangpass2.g"
        //----------------------------------------------------------
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
        
#line 461 "ZLangSymbolTableGenerator.cpp"
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
          initializationConstant(_t);
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
        _t = __t39;
        _t = _t->getNextSibling();
      }
      else {
        if ( _cnt41>=1 ) { goto _loop41; } else {throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));}
      }
      
      _cnt41++;
    }
    _loop41:;
    }
    break;
  }
  case LITERAL_table:
  {
#line 384 "zlangpass2.g"
    //-------------------------------------------------------------
    std::string stringElementSignature;
    
#line 514 "ZLangSymbolTableGenerator.cpp"
    zlang::CZLangAST_auto tmp9_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_table);
    _t = _t->getNextSibling();
    builtInType(_t,stringElementSignature);
    _t = _retTree;
    autoTableName = _t;
    match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
    _t = _t->getNextSibling();
#line 389 "zlangpass2.g"
    //-------------------------------------------------------------
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
    
#line 543 "ZLangSymbolTableGenerator.cpp"
    {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case ELEMENT_INIT:
    {
      tableInit(_t);
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
  _t = __t35;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangSymbolTableGenerator::globalFunctionDefinition(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto globalFunctionDefinition_AST_in = _t;
  zlang::CZLangAST_auto autoName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto __t27 = _t;
  zlang::CZLangAST_auto tmp10_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),GFUNCTION_DEFINITION);
  _t = _t->getFirstChild();
#line 250 "zlangpass2.g"
  //-----------------------------------------------------------------
  bool bIsStatic = false;
  
#line 589 "ZLangSymbolTableGenerator.cpp"
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case LITERAL_static:
  {
    zlang::CZLangAST_auto tmp11_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_static);
    _t = _t->getNextSibling();
#line 253 "zlangpass2.g"
    bIsStatic = true;
#line 601 "ZLangSymbolTableGenerator.cpp"
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
#line 256 "zlangpass2.g"
  //---------------------------------------------------------------
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
  
#line 639 "ZLangSymbolTableGenerator.cpp"
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
      zlang::CZLangAST_auto tmp12_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),LITERAL_table);
      _t = _t->getNextSibling();
#line 277 "zlangpass2.g"
      bIsTable = true;
#line 668 "ZLangSymbolTableGenerator.cpp"
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
      zlang::CZLangAST_auto tmp13_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),BAND);
      _t = _t->getNextSibling();
#line 277 "zlangpass2.g"
      bIsReturnReference = true;
#line 704 "ZLangSymbolTableGenerator.cpp"
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
#line 278 "zlangpass2.g"
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
    
#line 730 "ZLangSymbolTableGenerator.cpp"
    break;
  }
  case LITERAL_void:
  {
    zlang::CZLangAST_auto tmp14_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_void);
    _t = _t->getNextSibling();
#line 290 "zlangpass2.g"
    //-----------------------------------------------------------
    stringResultSignature = zvm::CstringZVM_VOID_SIGNATURE;
    
#line 742 "ZLangSymbolTableGenerator.cpp"
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  }
#line 294 "zlangpass2.g"
  //---------------------------------------------------------------
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
  
#line 785 "ZLangSymbolTableGenerator.cpp"
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case PARAMETERS_DECLARATION:
  {
    parameterDeclarationList(_t,nParameterIndex, stringFunctionSignature);
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
#line 329 "zlangpass2.g"
  //---------------------------------------------------------------
  stringFunctionSignature += ")";
  stringFunctionSignature += stringResultSignature;
  pciAttributes->SetFunctionSignature(stringFunctionSignature);
  
  /* now adjust pseudo argument's BP offset */
  if (pciReturnParameterAttributes)
  {
  pciReturnParameterAttributes->AdjustBPOffset(nParameterIndex);
  }
  
#line 818 "ZLangSymbolTableGenerator.cpp"
  codeBlock(_t);
  _t = _retTree;
#line 342 "zlangpass2.g"
  //---------------------------------------------------------------
  _vectorFindNames.pop_back();
  
#line 825 "ZLangSymbolTableGenerator.cpp"
  _t = __t29;
  _t = _t->getNextSibling();
  _t = __t27;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangSymbolTableGenerator::builtInType(zlang::CZLangAST_auto _t,
  std::string & rstringSignature
) {
  zlang::CZLangAST_auto builtInType_AST_in = _t;
  
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case LITERAL_byte:
  {
    zlang::CZLangAST_auto tmp15_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_byte);
    _t = _t->getNextSibling();
#line 591 "zlangpass2.g"
    rstringSignature = zvm::CstringZVM_BYTE_SIGNATURE;
#line 848 "ZLangSymbolTableGenerator.cpp"
    break;
  }
  case LITERAL_bool:
  {
    zlang::CZLangAST_auto tmp16_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_bool);
    _t = _t->getNextSibling();
#line 592 "zlangpass2.g"
    rstringSignature = zvm::CstringZVM_BOOL_SIGNATURE;
#line 858 "ZLangSymbolTableGenerator.cpp"
    break;
  }
  case LITERAL_sdword:
  {
    zlang::CZLangAST_auto tmp17_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_sdword);
    _t = _t->getNextSibling();
#line 593 "zlangpass2.g"
    rstringSignature = zvm::CstringZVM_SDWORD_SIGNATURE;
#line 868 "ZLangSymbolTableGenerator.cpp"
    break;
  }
  case LITERAL_udword:
  {
    zlang::CZLangAST_auto tmp18_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_udword);
    _t = _t->getNextSibling();
#line 594 "zlangpass2.g"
    rstringSignature = zvm::CstringZVM_UDWORD_SIGNATURE;
#line 878 "ZLangSymbolTableGenerator.cpp"
    break;
  }
  case LITERAL_sqword:
  {
    zlang::CZLangAST_auto tmp19_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_sqword);
    _t = _t->getNextSibling();
#line 595 "zlangpass2.g"
    rstringSignature = zvm::CstringZVM_SQWORD_SIGNATURE;
#line 888 "ZLangSymbolTableGenerator.cpp"
    break;
  }
  case LITERAL_uqword:
  {
    zlang::CZLangAST_auto tmp20_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_uqword);
    _t = _t->getNextSibling();
#line 596 "zlangpass2.g"
    rstringSignature = zvm::CstringZVM_UQWORD_SIGNATURE;
#line 898 "ZLangSymbolTableGenerator.cpp"
    break;
  }
  case LITERAL_double:
  {
    zlang::CZLangAST_auto tmp21_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_double);
    _t = _t->getNextSibling();
#line 597 "zlangpass2.g"
    rstringSignature = zvm::CstringZVM_DOUBLE_SIGNATURE;
#line 908 "ZLangSymbolTableGenerator.cpp"
    break;
  }
  case LITERAL_string:
  {
    zlang::CZLangAST_auto tmp22_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_string);
    _t = _t->getNextSibling();
#line 598 "zlangpass2.g"
    rstringSignature = zvm::CstringZVM_STRING_SIGNATURE;
#line 918 "ZLangSymbolTableGenerator.cpp"
    break;
  }
  case LITERAL_ipaddress:
  {
    zlang::CZLangAST_auto tmp23_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_ipaddress);
    _t = _t->getNextSibling();
#line 599 "zlangpass2.g"
    rstringSignature = zvm::CstringZVM_IPv4ADDR_SIGNATURE;
#line 928 "ZLangSymbolTableGenerator.cpp"
    break;
  }
  case LITERAL_pport:
  {
    zlang::CZLangAST_auto tmp24_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_pport);
    _t = _t->getNextSibling();
#line 600 "zlangpass2.g"
    rstringSignature = zvm::CstringZVM_PPORT_SIGNATURE;
#line 938 "ZLangSymbolTableGenerator.cpp"
    break;
  }
  case LITERAL_rope:
  {
    zlang::CZLangAST_auto tmp25_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_rope);
    _t = _t->getNextSibling();
#line 601 "zlangpass2.g"
    rstringSignature = zvm::CstringZVM_ROPE_SIGNATURE;
#line 948 "ZLangSymbolTableGenerator.cpp"
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  _retTree = _t;
}

void ZLangSymbolTableGenerator::externParameterDeclarationList(zlang::CZLangAST_auto _t,
  std::string & rstringParametersSignature
) {
  zlang::CZLangAST_auto externParameterDeclarationList_AST_in = _t;
  
  zlang::CZLangAST_auto __t12 = _t;
  zlang::CZLangAST_auto tmp26_AST_in = _t;
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

void ZLangSymbolTableGenerator::externParameterDeclaration(zlang::CZLangAST_auto _t,
  std::string & rstringParametersSignature
) {
  zlang::CZLangAST_auto externParameterDeclaration_AST_in = _t;
  
#line 182 "zlangpass2.g"
  //-------------------------------------------------------------------
  std::string stringTypeSignature;
  bool bIsTable = false;
  bool bIsReferenceArgument = false;
  
#line 1001 "ZLangSymbolTableGenerator.cpp"
  zlang::CZLangAST_auto __t16 = _t;
  zlang::CZLangAST_auto tmp27_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
  _t = _t->getFirstChild();
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case LITERAL_table:
  {
    zlang::CZLangAST_auto tmp28_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_table);
    _t = _t->getNextSibling();
#line 189 "zlangpass2.g"
    bIsTable = true;
#line 1017 "ZLangSymbolTableGenerator.cpp"
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
    zlang::CZLangAST_auto tmp29_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),BAND);
    _t = _t->getNextSibling();
#line 189 "zlangpass2.g"
    bIsReferenceArgument = true;
#line 1053 "ZLangSymbolTableGenerator.cpp"
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
#line 191 "zlangpass2.g"
  //-------------------------------------------------------------------
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
  
#line 1081 "ZLangSymbolTableGenerator.cpp"
  _retTree = _t;
}

void ZLangSymbolTableGenerator::parameterDeclarationList(zlang::CZLangAST_auto _t,
  int & rnParameterIndex, std::string & rstringParametersSignature
) {
  zlang::CZLangAST_auto parameterDeclarationList_AST_in = _t;
  
  zlang::CZLangAST_auto __t48 = _t;
  zlang::CZLangAST_auto tmp30_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),PARAMETERS_DECLARATION);
  _t = _t->getFirstChild();
#line 426 "zlangpass2.g"
  //-----------------------------------------------------------------
  std::vector<zlang::CParameterSymbolAttributes *> vectorOfPSymbolAttributes;
  
#line 1098 "ZLangSymbolTableGenerator.cpp"
  {
  int _cnt50=0;
  for (;;) {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    if ((_t->getType()==IDENTIFIER)) {
      parameterDeclaration(_t,rnParameterIndex, rstringParametersSignature, vectorOfPSymbolAttributes);
      _t = _retTree;
    }
    else {
      if ( _cnt50>=1 ) { goto _loop50; } else {throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));}
    }
    
    _cnt50++;
  }
  _loop50:;
  }
#line 431 "zlangpass2.g"
  //-----------------------------------------------------------------
  std::vector<zlang::CParameterSymbolAttributes *>::iterator it;
  for (it = vectorOfPSymbolAttributes.begin();
  it != vectorOfPSymbolAttributes.end();
  ++it)
  {
  (*it)->AdjustBPOffset(rnParameterIndex);
  }
  
#line 1126 "ZLangSymbolTableGenerator.cpp"
  _t = __t48;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangSymbolTableGenerator::codeBlock(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto codeBlock_AST_in = _t;
  
  zlang::CZLangAST_auto __t44 = _t;
  zlang::CZLangAST_auto tmp31_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),CODE_BLOCK);
  _t = _t->getFirstChild();
#line 416 "zlangpass2.g"
  //-----------------------------------------------------------------
  int nIndex = 0;
  
#line 1143 "ZLangSymbolTableGenerator.cpp"
  {
  for (;;) {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    if ((_t->getType()==LVARIABLE_DEFINITION)) {
      localVariableDefinition(_t,nIndex);
      _t = _retTree;
    }
    else {
      goto _loop46;
    }
    
  }
  _loop46:;
  }
  compoundStatement(_t);
  _t = _retTree;
  _t = __t44;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangSymbolTableGenerator::initializationConstant(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto initializationConstant_AST_in = _t;
  
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case PLUS:
  case MINUS:
  case NUM_INT:
  case NUM_QUAD:
  case NUM_FLOAT:
  {
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
      zlang::CZLangAST_auto tmp34_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),NUM_INT);
      _t = _t->getNextSibling();
      break;
    }
    case NUM_QUAD:
    {
      zlang::CZLangAST_auto tmp35_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),NUM_QUAD);
      _t = _t->getNextSibling();
      break;
    }
    case NUM_FLOAT:
    {
      zlang::CZLangAST_auto tmp36_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),NUM_FLOAT);
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
  case NUM_HEX_INT:
  {
    zlang::CZLangAST_auto tmp37_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),NUM_HEX_INT);
    _t = _t->getNextSibling();
    break;
  }
  case NUM_HEX_QUAD:
  {
    zlang::CZLangAST_auto tmp38_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),NUM_HEX_QUAD);
    _t = _t->getNextSibling();
    break;
  }
  case CHAR_LITERAL:
  {
    zlang::CZLangAST_auto tmp39_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),CHAR_LITERAL);
    _t = _t->getNextSibling();
    break;
  }
  case STRING_LITERAL:
  {
    zlang::CZLangAST_auto tmp40_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),STRING_LITERAL);
    _t = _t->getNextSibling();
    break;
  }
  case IPv4ADDR_LITERAL:
  {
    zlang::CZLangAST_auto tmp41_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),IPv4ADDR_LITERAL);
    _t = _t->getNextSibling();
    break;
  }
  case PPORT_LITERAL:
  {
    zlang::CZLangAST_auto tmp42_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),PPORT_LITERAL);
    _t = _t->getNextSibling();
    break;
  }
  case LITERAL_true:
  {
    zlang::CZLangAST_auto tmp43_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_true);
    _t = _t->getNextSibling();
    break;
  }
  case LITERAL_false:
  {
    zlang::CZLangAST_auto tmp44_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_false);
    _t = _t->getNextSibling();
    break;
  }
  case ROPE_LITERAL:
  {
    zlang::CZLangAST_auto tmp45_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),ROPE_LITERAL);
    _t = _t->getNextSibling();
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  _retTree = _t;
}

void ZLangSymbolTableGenerator::tableInit(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto tableInit_AST_in = _t;
  
  {
  int _cnt91=0;
  for (;;) {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    if ((_t->getType()==ELEMENT_INIT)) {
      zlang::CZLangAST_auto __t90 = _t;
      zlang::CZLangAST_auto tmp46_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),ELEMENT_INIT);
      _t = _t->getFirstChild();
      initializationConstant(_t);
      _t = _retTree;
      initializationConstant(_t);
      _t = _retTree;
      _t = __t90;
      _t = _t->getNextSibling();
    }
    else {
      if ( _cnt91>=1 ) { goto _loop91; } else {throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));}
    }
    
    _cnt91++;
  }
  _loop91:;
  }
  _retTree = _t;
}

void ZLangSymbolTableGenerator::localVariableDefinition(zlang::CZLangAST_auto _t,
  int & rnIndex
) {
  zlang::CZLangAST_auto localVariableDefinition_AST_in = _t;
  zlang::CZLangAST_auto autoName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto autoTableName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto __t79 = _t;
  zlang::CZLangAST_auto tmp47_AST_in = _t;
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
#line 525 "zlangpass2.g"
    //-------------------------------------------------------------
    std::string stringVariableSignature;
    bool bIsReferenceVariable = false;
    
#line 1375 "ZLangSymbolTableGenerator.cpp"
    builtInType(_t,stringVariableSignature);
    _t = _retTree;
    {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case BAND:
    {
      zlang::CZLangAST_auto tmp48_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),BAND);
      _t = _t->getNextSibling();
#line 529 "zlangpass2.g"
      bIsReferenceVariable = true;
#line 1389 "ZLangSymbolTableGenerator.cpp"
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
#line 530 "zlangpass2.g"
    //-------------------------------------------------------------
    if (bIsReferenceVariable)
    {
    // Turn signature to lower char
    zfc::LowerString(stringVariableSignature);
    }
    
#line 1410 "ZLangSymbolTableGenerator.cpp"
    {
    int _cnt85=0;
    for (;;) {
      if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
        _t = ASTNULL;
      if ((_t->getType()==IDENTIFIER)) {
        zlang::CZLangAST_auto __t83 = _t;
        autoName = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
        match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
        _t = _t->getFirstChild();
#line 539 "zlangpass2.g"
        //----------------------------------------------------------
        ++rnIndex;
        _vectorFindNames.push_back(autoName->getText());
        
        zlang::CLocalVariableSymbolAttributes * pciAttributes =
        new zlang::CLocalVariableSymbolAttributes(rnIndex);
        pciAttributes->SetVariableSignature(stringVariableSignature);
        __INSERT_SYMBOL__(autoName);
        
        _vectorFindNames.pop_back();
        
#line 1433 "ZLangSymbolTableGenerator.cpp"
        {
        if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
          _t = ASTNULL;
        switch ( _t->getType()) {
        case EXPRESSION:
        {
          expression(_t);
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
        _t = __t83;
        _t = _t->getNextSibling();
      }
      else {
        if ( _cnt85>=1 ) { goto _loop85; } else {throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));}
      }
      
      _cnt85++;
    }
    _loop85:;
    }
    break;
  }
  case LITERAL_table:
  {
#line 555 "zlangpass2.g"
    //-------------------------------------------------------------
    std::string stringElementSignature;
    bool bIsReferenceVariable = false;
    ++rnIndex;
    
#line 1475 "ZLangSymbolTableGenerator.cpp"
    zlang::CZLangAST_auto tmp49_AST_in = _t;
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
      zlang::CZLangAST_auto tmp50_AST_in = _t;
      match(static_cast<antlr::RefAST>(_t),BAND);
      _t = _t->getNextSibling();
#line 560 "zlangpass2.g"
      bIsReferenceVariable = true;
#line 1492 "ZLangSymbolTableGenerator.cpp"
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
    autoTableName = _t;
    match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
    _t = _t->getNextSibling();
#line 562 "zlangpass2.g"
    //-------------------------------------------------------------
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
    
#line 1527 "ZLangSymbolTableGenerator.cpp"
    {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case ELEMENT_INIT:
    {
      tableInit(_t);
      _t = _retTree;
      break;
    }
    case EXPRESSION:
    {
      expression(_t);
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
  _t = __t79;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangSymbolTableGenerator::compoundStatement(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto compoundStatement_AST_in = _t;
  
  zlang::CZLangAST_auto __t56 = _t;
  zlang::CZLangAST_auto tmp51_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),COMPOUND_STATEMENTS);
  _t = _t->getFirstChild();
  {
  for (;;) {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    if ((_tokenSet_0.member(_t->getType()))) {
      statement(_t);
      _t = _retTree;
    }
    else {
      goto _loop58;
    }
    
  }
  _loop58:;
  }
  _t = __t56;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangSymbolTableGenerator::parameterDeclaration(zlang::CZLangAST_auto _t,
  int & rnIndex,
                      std::string & rstringParametersSignature,
                      std::vector<zlang::CParameterSymbolAttributes *> & rvectorOfPSymbolAttributes
) {
  zlang::CZLangAST_auto parameterDeclaration_AST_in = _t;
  zlang::CZLangAST_auto autoName = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
#line 446 "zlangpass2.g"
  //-------------------------------------------------------------------
  std::string stringTypeSignature;
  std::string stringName;
  bool bIsTable = false;
  bool bIsReferenceArgument = false;
  
#line 1609 "ZLangSymbolTableGenerator.cpp"
  zlang::CZLangAST_auto __t52 = _t;
  autoName = (_t == ASTNULL) ? static_cast<zlang::CZLangAST_auto>(antlr::nullAST) : _t;
  match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
  _t = _t->getFirstChild();
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case LITERAL_table:
  {
    zlang::CZLangAST_auto tmp52_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_table);
    _t = _t->getNextSibling();
#line 454 "zlangpass2.g"
    bIsTable = true;
#line 1625 "ZLangSymbolTableGenerator.cpp"
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
    zlang::CZLangAST_auto tmp53_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),BAND);
    _t = _t->getNextSibling();
#line 454 "zlangpass2.g"
    bIsReferenceArgument = true;
#line 1661 "ZLangSymbolTableGenerator.cpp"
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
  _t = __t52;
  _t = _t->getNextSibling();
#line 456 "zlangpass2.g"
  //-------------------------------------------------------------------
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
  
#line 1704 "ZLangSymbolTableGenerator.cpp"
  _retTree = _t;
}

void ZLangSymbolTableGenerator::statement(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto statement_AST_in = _t;
  
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case EXPRESSION:
  {
    expression(_t);
    _t = _retTree;
    break;
  }
  case LITERAL_if:
  {
    ifStatement(_t);
    _t = _retTree;
    break;
  }
  case LITERAL_while:
  {
    whileStatement(_t);
    _t = _retTree;
    break;
  }
  case LITERAL_break:
  {
    zlang::CZLangAST_auto tmp54_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_break);
    _t = _t->getNextSibling();
    break;
  }
  case LITERAL_continue:
  {
    zlang::CZLangAST_auto tmp55_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_continue);
    _t = _t->getNextSibling();
    break;
  }
  case LITERAL_return:
  {
    zlang::CZLangAST_auto __t60 = _t;
    zlang::CZLangAST_auto tmp56_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_return);
    _t = _t->getFirstChild();
    {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case EXPRESSION:
    {
      expression(_t);
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
    _t = __t60;
    _t = _t->getNextSibling();
    break;
  }
  case LITERAL_for:
  {
    forStatement(_t);
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

void ZLangSymbolTableGenerator::expression(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto expression_AST_in = _t;
  
  zlang::CZLangAST_auto __t94 = _t;
  zlang::CZLangAST_auto tmp57_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),EXPRESSION);
  _t = _t->getFirstChild();
  expressionDefinition(_t);
  _t = _retTree;
  _t = __t94;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangSymbolTableGenerator::ifStatement(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto ifStatement_AST_in = _t;
  
  zlang::CZLangAST_auto __t63 = _t;
  zlang::CZLangAST_auto tmp58_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),LITERAL_if);
  _t = _t->getFirstChild();
  expression(_t);
  _t = _retTree;
  compoundStatement(_t);
  _t = _retTree;
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case COMPOUND_STATEMENTS:
  {
    compoundStatement(_t);
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
  _t = __t63;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangSymbolTableGenerator::whileStatement(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto whileStatement_AST_in = _t;
  
  zlang::CZLangAST_auto __t66 = _t;
  zlang::CZLangAST_auto tmp59_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),LITERAL_while);
  _t = _t->getFirstChild();
  expression(_t);
  _t = _retTree;
  compoundStatement(_t);
  _t = _retTree;
  _t = __t66;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangSymbolTableGenerator::forStatement(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto forStatement_AST_in = _t;
  
  zlang::CZLangAST_auto __t68 = _t;
  zlang::CZLangAST_auto tmp60_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),LITERAL_for);
  _t = _t->getFirstChild();
  {
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case FOR_EXPRESSION1:
  {
    forExpression1(_t);
    _t = _retTree;
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
    forExpression2(_t);
    _t = _retTree;
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
    forExpression3(_t);
    _t = _retTree;
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
  compoundStatement(_t);
  _t = _retTree;
  _t = __t68;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangSymbolTableGenerator::forExpression1(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto forExpression1_AST_in = _t;
  
  zlang::CZLangAST_auto __t73 = _t;
  zlang::CZLangAST_auto tmp61_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),FOR_EXPRESSION1);
  _t = _t->getFirstChild();
  expressionDefinition(_t);
  _t = _retTree;
  _t = __t73;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangSymbolTableGenerator::forExpression2(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto forExpression2_AST_in = _t;
  
  zlang::CZLangAST_auto __t75 = _t;
  zlang::CZLangAST_auto tmp62_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),FOR_EXPRESSION2);
  _t = _t->getFirstChild();
  expressionDefinition(_t);
  _t = _retTree;
  _t = __t75;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangSymbolTableGenerator::forExpression3(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto forExpression3_AST_in = _t;
  
  zlang::CZLangAST_auto __t77 = _t;
  zlang::CZLangAST_auto tmp63_AST_in = _t;
  match(static_cast<antlr::RefAST>(_t),FOR_EXPRESSION3);
  _t = _t->getFirstChild();
  expressionDefinition(_t);
  _t = _retTree;
  _t = __t77;
  _t = _t->getNextSibling();
  _retTree = _t;
}

void ZLangSymbolTableGenerator::expressionDefinition(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto expressionDefinition_AST_in = _t;
  
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case ASSIGN:
  {
    zlang::CZLangAST_auto __t99 = _t;
    zlang::CZLangAST_auto tmp64_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),ASSIGN);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t99;
    _t = _t->getNextSibling();
    break;
  }
  case LOR:
  {
    zlang::CZLangAST_auto __t100 = _t;
    zlang::CZLangAST_auto tmp65_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LOR);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t100;
    _t = _t->getNextSibling();
    break;
  }
  case LAND:
  {
    zlang::CZLangAST_auto __t101 = _t;
    zlang::CZLangAST_auto tmp66_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LAND);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t101;
    _t = _t->getNextSibling();
    break;
  }
  case BOR:
  {
    zlang::CZLangAST_auto __t102 = _t;
    zlang::CZLangAST_auto tmp67_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),BOR);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t102;
    _t = _t->getNextSibling();
    break;
  }
  case BXOR:
  {
    zlang::CZLangAST_auto __t103 = _t;
    zlang::CZLangAST_auto tmp68_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),BXOR);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t103;
    _t = _t->getNextSibling();
    break;
  }
  case BAND:
  {
    zlang::CZLangAST_auto __t104 = _t;
    zlang::CZLangAST_auto tmp69_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),BAND);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t104;
    _t = _t->getNextSibling();
    break;
  }
  case NOT_EQUAL:
  {
    zlang::CZLangAST_auto __t105 = _t;
    zlang::CZLangAST_auto tmp70_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),NOT_EQUAL);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t105;
    _t = _t->getNextSibling();
    break;
  }
  case EQUAL:
  {
    zlang::CZLangAST_auto __t106 = _t;
    zlang::CZLangAST_auto tmp71_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),EQUAL);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t106;
    _t = _t->getNextSibling();
    break;
  }
  case LT_:
  {
    zlang::CZLangAST_auto __t107 = _t;
    zlang::CZLangAST_auto tmp72_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LT_);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t107;
    _t = _t->getNextSibling();
    break;
  }
  case GT:
  {
    zlang::CZLangAST_auto __t108 = _t;
    zlang::CZLangAST_auto tmp73_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),GT);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t108;
    _t = _t->getNextSibling();
    break;
  }
  case LE:
  {
    zlang::CZLangAST_auto __t109 = _t;
    zlang::CZLangAST_auto tmp74_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LE);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t109;
    _t = _t->getNextSibling();
    break;
  }
  case GE:
  {
    zlang::CZLangAST_auto __t110 = _t;
    zlang::CZLangAST_auto tmp75_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),GE);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t110;
    _t = _t->getNextSibling();
    break;
  }
  case SL:
  {
    zlang::CZLangAST_auto __t111 = _t;
    zlang::CZLangAST_auto tmp76_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),SL);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t111;
    _t = _t->getNextSibling();
    break;
  }
  case SR:
  {
    zlang::CZLangAST_auto __t112 = _t;
    zlang::CZLangAST_auto tmp77_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),SR);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t112;
    _t = _t->getNextSibling();
    break;
  }
  case PLUS:
  {
    zlang::CZLangAST_auto __t113 = _t;
    zlang::CZLangAST_auto tmp78_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),PLUS);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t113;
    _t = _t->getNextSibling();
    break;
  }
  case MINUS:
  {
    zlang::CZLangAST_auto __t114 = _t;
    zlang::CZLangAST_auto tmp79_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),MINUS);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t114;
    _t = _t->getNextSibling();
    break;
  }
  case STAR:
  {
    zlang::CZLangAST_auto __t115 = _t;
    zlang::CZLangAST_auto tmp80_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),STAR);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t115;
    _t = _t->getNextSibling();
    break;
  }
  case DIV:
  {
    zlang::CZLangAST_auto __t116 = _t;
    zlang::CZLangAST_auto tmp81_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),DIV);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t116;
    _t = _t->getNextSibling();
    break;
  }
  case MOD:
  {
    zlang::CZLangAST_auto __t117 = _t;
    zlang::CZLangAST_auto tmp82_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),MOD);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t117;
    _t = _t->getNextSibling();
    break;
  }
  case INC:
  {
    zlang::CZLangAST_auto __t118 = _t;
    zlang::CZLangAST_auto tmp83_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),INC);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t118;
    _t = _t->getNextSibling();
    break;
  }
  case DEC:
  {
    zlang::CZLangAST_auto __t119 = _t;
    zlang::CZLangAST_auto tmp84_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),DEC);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t119;
    _t = _t->getNextSibling();
    break;
  }
  case UNARY_MINUS:
  {
    zlang::CZLangAST_auto __t120 = _t;
    zlang::CZLangAST_auto tmp85_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),UNARY_MINUS);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t120;
    _t = _t->getNextSibling();
    break;
  }
  case UNARY_PLUS:
  {
    zlang::CZLangAST_auto __t121 = _t;
    zlang::CZLangAST_auto tmp86_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),UNARY_PLUS);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t121;
    _t = _t->getNextSibling();
    break;
  }
  case BNOT:
  {
    zlang::CZLangAST_auto __t122 = _t;
    zlang::CZLangAST_auto tmp87_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),BNOT);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t122;
    _t = _t->getNextSibling();
    break;
  }
  case LNOT:
  {
    zlang::CZLangAST_auto __t123 = _t;
    zlang::CZLangAST_auto tmp88_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LNOT);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t123;
    _t = _t->getNextSibling();
    break;
  }
  case TYPECAST:
  {
    zlang::CZLangAST_auto __t124 = _t;
    zlang::CZLangAST_auto tmp89_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),TYPECAST);
    _t = _t->getFirstChild();
#line 652 "zlangpass2.g"
    //---------------------------------------------------------------
    std::string stringCastToSignature;
    
#line 2329 "ZLangSymbolTableGenerator.cpp"
    builtInType(_t,stringCastToSignature);
    _t = _retTree;
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t124;
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
    postfixExpression(_t);
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

void ZLangSymbolTableGenerator::argumentList(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto argumentList_AST_in = _t;
  
  {
  int _cnt97=0;
  for (;;) {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    if ((_t->getType()==EXPRESSION)) {
      expression(_t);
      _t = _retTree;
    }
    else {
      if ( _cnt97>=1 ) { goto _loop97; } else {throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));}
    }
    
    _cnt97++;
  }
  _loop97:;
  }
  _retTree = _t;
}

void ZLangSymbolTableGenerator::postfixExpression(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto postfixExpression_AST_in = _t;
  
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case CALLING:
  {
    zlang::CZLangAST_auto __t126 = _t;
    zlang::CZLangAST_auto tmp90_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),CALLING);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    {
    if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      _t = ASTNULL;
    switch ( _t->getType()) {
    case EXPRESSION:
    {
      argumentList(_t);
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
    _t = __t126;
    _t = _t->getNextSibling();
    break;
  }
  case DOT:
  {
    zlang::CZLangAST_auto __t128 = _t;
    zlang::CZLangAST_auto tmp91_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),DOT);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    zlang::CZLangAST_auto tmp92_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
    _t = _t->getNextSibling();
    _t = __t128;
    _t = _t->getNextSibling();
    break;
  }
  case SUBSCRIPT:
  {
    zlang::CZLangAST_auto __t129 = _t;
    zlang::CZLangAST_auto tmp93_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),SUBSCRIPT);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    expression(_t);
    _t = _retTree;
    _t = __t129;
    _t = _t->getNextSibling();
    break;
  }
  case POST_INC:
  {
    zlang::CZLangAST_auto __t130 = _t;
    zlang::CZLangAST_auto tmp94_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),POST_INC);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t130;
    _t = _t->getNextSibling();
    break;
  }
  case POST_DEC:
  {
    zlang::CZLangAST_auto __t131 = _t;
    zlang::CZLangAST_auto tmp95_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),POST_DEC);
    _t = _t->getFirstChild();
    expressionDefinition(_t);
    _t = _retTree;
    _t = __t131;
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
    primaryExpression(_t);
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

void ZLangSymbolTableGenerator::primaryExpression(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto primaryExpression_AST_in = _t;
  
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case IDENTIFIER:
  {
    zlang::CZLangAST_auto tmp96_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),IDENTIFIER);
    _t = _t->getNextSibling();
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
    constant(_t);
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

void ZLangSymbolTableGenerator::constant(zlang::CZLangAST_auto _t) {
  zlang::CZLangAST_auto constant_AST_in = _t;
  
  if (_t == static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
    _t = ASTNULL;
  switch ( _t->getType()) {
  case NUM_INT:
  {
    zlang::CZLangAST_auto tmp97_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),NUM_INT);
    _t = _t->getNextSibling();
    break;
  }
  case NUM_HEX_INT:
  {
    zlang::CZLangAST_auto tmp98_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),NUM_HEX_INT);
    _t = _t->getNextSibling();
    break;
  }
  case NUM_QUAD:
  {
    zlang::CZLangAST_auto tmp99_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),NUM_QUAD);
    _t = _t->getNextSibling();
    break;
  }
  case NUM_HEX_QUAD:
  {
    zlang::CZLangAST_auto tmp100_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),NUM_HEX_QUAD);
    _t = _t->getNextSibling();
    break;
  }
  case NUM_FLOAT:
  {
    zlang::CZLangAST_auto tmp101_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),NUM_FLOAT);
    _t = _t->getNextSibling();
    break;
  }
  case CHAR_LITERAL:
  {
    zlang::CZLangAST_auto tmp102_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),CHAR_LITERAL);
    _t = _t->getNextSibling();
    break;
  }
  case STRING_LITERAL:
  {
    zlang::CZLangAST_auto tmp103_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),STRING_LITERAL);
    _t = _t->getNextSibling();
    break;
  }
  case IPv4ADDR_LITERAL:
  {
    zlang::CZLangAST_auto tmp104_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),IPv4ADDR_LITERAL);
    _t = _t->getNextSibling();
    break;
  }
  case PPORT_LITERAL:
  {
    zlang::CZLangAST_auto tmp105_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),PPORT_LITERAL);
    _t = _t->getNextSibling();
    break;
  }
  case LITERAL_true:
  {
    zlang::CZLangAST_auto tmp106_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_true);
    _t = _t->getNextSibling();
    break;
  }
  case LITERAL_false:
  {
    zlang::CZLangAST_auto tmp107_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),LITERAL_false);
    _t = _t->getNextSibling();
    break;
  }
  case ROPE_LITERAL:
  {
    zlang::CZLangAST_auto tmp108_AST_in = _t;
    match(static_cast<antlr::RefAST>(_t),ROPE_LITERAL);
    _t = _t->getNextSibling();
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(static_cast<antlr::RefAST>(_t));
  }
  }
  _retTree = _t;
}

zlang::CZLangAST_auto ZLangSymbolTableGenerator::getAST()
{
	return returnAST;
}

const char* ZLangSymbolTableGenerator::_tokenNames[] = {
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
  0
};

const unsigned long ZLangSymbolTableGenerator::_tokenSet_0_data_[] = { 8192UL, 14208UL, 0UL, 0UL };
// EXPRESSION "break" "continue" "return" "if" "while" "for" 
const antlr::BitSet ZLangSymbolTableGenerator::_tokenSet_0(_tokenSet_0_data_,4);


ANTLR_END_NAMESPACE
