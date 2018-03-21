/* $ANTLR 2.7.1: "zlangpass1.g" -> "ZLangParser.cpp"$ */
#include "ZLangParser.hpp"
#include "antlr/NoViableAltException.hpp"
#include "antlr/SemanticException.hpp"
ANTLR_BEGIN_NAMESPACE(zlang)
#line 1 "zlangpass1.g"

#line 8 "ZLangParser.cpp"
ZLangParser::ZLangParser(antlr::TokenBuffer& tokenBuf, int k)
: antlr::LLkParser(tokenBuf,k)
{
  setTokenNames(_tokenNames);
}

ZLangParser::ZLangParser(antlr::TokenBuffer& tokenBuf)
: antlr::LLkParser(tokenBuf,4)
{
  setTokenNames(_tokenNames);
}

ZLangParser::ZLangParser(antlr::TokenStream& lexer, int k)
: antlr::LLkParser(lexer,k)
{
  setTokenNames(_tokenNames);
}

ZLangParser::ZLangParser(antlr::TokenStream& lexer)
: antlr::LLkParser(lexer,4)
{
  setTokenNames(_tokenNames);
}

ZLangParser::ZLangParser(const antlr::ParserSharedInputState& state)
: antlr::LLkParser(state,4)
{
  setTokenNames(_tokenNames);
}

/**
 * ZLang script start rule.
 */
void ZLangParser::zlangScript() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto zlangScript_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  {
  for (;;) {
    switch ( LA(1)) {
    case LITERAL_extern:
    {
      externGlobalDeclaration();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
      break;
    }
    case LITERAL_table:
    case LITERAL_void:
    case LITERAL_static:
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
      globalDefinition();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
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
  zlang::CZLangAST_auto tmp1_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp1_AST = astFactory.create(LT(1));
  match(antlr::Token::EOF_TYPE);
  zlangScript_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = zlangScript_AST;
}

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
void ZLangParser::externGlobalDeclaration() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto externGlobalDeclaration_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto tmp2_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp2_AST = astFactory.create(LT(1));
  match(LITERAL_extern);
  {
  switch ( LA(1)) {
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
    switch ( LA(1)) {
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
      builtInType();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
      break;
    }
    case LITERAL_table:
    {
      zlang::CZLangAST_auto tmp3_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp3_AST = astFactory.create(LT(1));
      astFactory.addASTChild(currentAST, antlr::RefAST(tmp3_AST));
      match(LITERAL_table);
      zlang::CZLangAST_auto tmp4_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp4_AST = astFactory.create(LT(1));
      match(LT_);
      builtInType();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
      zlang::CZLangAST_auto tmp5_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp5_AST = astFactory.create(LT(1));
      match(GT);
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(LT(1), getFilename());
    }
    }
    }
    {
    if ((LA(1)==BAND||LA(1)==IDENTIFIER) && (LA(2)==IDENTIFIER||LA(2)==LPAREN)) {
      {
      switch ( LA(1)) {
      case BAND:
      {
        zlang::CZLangAST_auto tmp6_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp6_AST = astFactory.create(LT(1));
        astFactory.addASTChild(currentAST, antlr::RefAST(tmp6_AST));
        match(BAND);
        break;
      }
      case IDENTIFIER:
      {
        break;
      }
      default:
      {
        throw antlr::NoViableAltException(LT(1), getFilename());
      }
      }
      }
      zlang::CZLangAST_auto tmp7_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp7_AST = astFactory.create(LT(1));
      astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp7_AST));
      match(IDENTIFIER);
      zlang::CZLangAST_auto tmp8_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp8_AST = astFactory.create(LT(1));
      match(LPAREN);
      {
      switch ( LA(1)) {
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
        parameterDeclarationList();
        astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
        break;
      }
      case RPAREN:
      {
        break;
      }
      default:
      {
        throw antlr::NoViableAltException(LT(1), getFilename());
      }
      }
      }
      zlang::CZLangAST_auto tmp9_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp9_AST = astFactory.create(LT(1));
      match(RPAREN);
      zlang::CZLangAST_auto tmp10_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp10_AST = astFactory.create(LT(1));
      match(SEMI);
      externGlobalDeclaration_AST = zlang::CZLangAST_auto(currentAST.root);
#line 127 "zlangpass1.g"
      externGlobalDeclaration_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(EXTERN_GFUNCTION_DECLARATION,"EXTERN_GFUNCTION_DECLARATION")))->add(static_cast<antlr::RefAST>(externGlobalDeclaration_AST))));
#line 238 "ZLangParser.cpp"
      currentAST.root = externGlobalDeclaration_AST;
      if ( externGlobalDeclaration_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
        externGlobalDeclaration_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
          currentAST.child = externGlobalDeclaration_AST->getFirstChild();
      else
        currentAST.child = externGlobalDeclaration_AST;
      currentAST.advanceChildToEnd();
    }
    else if ((LA(1)==IDENTIFIER) && (LA(2)==SEMI||LA(2)==COMMA)) {
      zlang::CZLangAST_auto tmp11_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp11_AST = astFactory.create(LT(1));
      astFactory.addASTChild(currentAST, antlr::RefAST(tmp11_AST));
      match(IDENTIFIER);
      {
      for (;;) {
        if ((LA(1)==COMMA)) {
          zlang::CZLangAST_auto tmp12_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
          tmp12_AST = astFactory.create(LT(1));
          match(COMMA);
          zlang::CZLangAST_auto tmp13_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
          tmp13_AST = astFactory.create(LT(1));
          astFactory.addASTChild(currentAST, antlr::RefAST(tmp13_AST));
          match(IDENTIFIER);
        }
        else {
          goto _loop11;
        }
        
      }
      _loop11:;
      }
      zlang::CZLangAST_auto tmp14_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp14_AST = astFactory.create(LT(1));
      match(SEMI);
      externGlobalDeclaration_AST = zlang::CZLangAST_auto(currentAST.root);
#line 130 "zlangpass1.g"
      externGlobalDeclaration_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(EXTERN_GVARIABLE_DECLARATION,"EXTERN_GVARIABLE_DECLARATION")))->add(static_cast<antlr::RefAST>(externGlobalDeclaration_AST))));
#line 276 "ZLangParser.cpp"
      currentAST.root = externGlobalDeclaration_AST;
      if ( externGlobalDeclaration_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
        externGlobalDeclaration_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
          currentAST.child = externGlobalDeclaration_AST->getFirstChild();
      else
        currentAST.child = externGlobalDeclaration_AST;
      currentAST.advanceChildToEnd();
    }
    else {
      throw antlr::NoViableAltException(LT(1), getFilename());
    }
    
    }
    break;
  }
  case LITERAL_void:
  {
    zlang::CZLangAST_auto tmp15_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp15_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp15_AST));
    match(LITERAL_void);
    zlang::CZLangAST_auto tmp16_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp16_AST = astFactory.create(LT(1));
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp16_AST));
    match(IDENTIFIER);
    zlang::CZLangAST_auto tmp17_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp17_AST = astFactory.create(LT(1));
    match(LPAREN);
    {
    switch ( LA(1)) {
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
      parameterDeclarationList();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
      break;
    }
    case RPAREN:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(LT(1), getFilename());
    }
    }
    }
    zlang::CZLangAST_auto tmp18_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp18_AST = astFactory.create(LT(1));
    match(RPAREN);
    zlang::CZLangAST_auto tmp19_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp19_AST = astFactory.create(LT(1));
    match(SEMI);
    externGlobalDeclaration_AST = zlang::CZLangAST_auto(currentAST.root);
#line 134 "zlangpass1.g"
    externGlobalDeclaration_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(EXTERN_GFUNCTION_DECLARATION,"EXTERN_GFUNCTION_DECLARATION")))->add(static_cast<antlr::RefAST>(externGlobalDeclaration_AST))));
#line 343 "ZLangParser.cpp"
    currentAST.root = externGlobalDeclaration_AST;
    if ( externGlobalDeclaration_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
      externGlobalDeclaration_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
        currentAST.child = externGlobalDeclaration_AST->getFirstChild();
    else
      currentAST.child = externGlobalDeclaration_AST;
    currentAST.advanceChildToEnd();
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  }
  externGlobalDeclaration_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = externGlobalDeclaration_AST;
}

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
void ZLangParser::globalDefinition() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto globalDefinition_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::RefToken  tSTATIC = antlr::nullToken;
  zlang::CZLangAST_auto tSTATIC_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::RefToken  tNAME1 = antlr::nullToken;
  zlang::CZLangAST_auto tNAME1_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto rINIT1_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::RefToken  tNAME2 = antlr::nullToken;
  zlang::CZLangAST_auto tNAME2_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto rINIT2_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
#line 163 "zlangpass1.g"
  bool bStatic = false;
#line 402 "ZLangParser.cpp"
  {
  switch ( LA(1)) {
  case LITERAL_static:
  {
    tSTATIC = LT(1);
    tSTATIC_AST = astFactory.create(tSTATIC);
    match(LITERAL_static);
#line 164 "zlangpass1.g"
    bStatic = true;
#line 412 "ZLangParser.cpp"
    break;
  }
  case LITERAL_table:
  case LITERAL_void:
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
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  }
  {
  switch ( LA(1)) {
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
    switch ( LA(1)) {
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
      builtInType();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
      {
      if ((LA(1)==BAND||LA(1)==IDENTIFIER) && (LA(2)==IDENTIFIER||LA(2)==LPAREN)) {
        {
        switch ( LA(1)) {
        case BAND:
        {
          zlang::CZLangAST_auto tmp20_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
          tmp20_AST = astFactory.create(LT(1));
          astFactory.addASTChild(currentAST, antlr::RefAST(tmp20_AST));
          match(BAND);
          break;
        }
        case IDENTIFIER:
        {
          break;
        }
        default:
        {
          throw antlr::NoViableAltException(LT(1), getFilename());
        }
        }
        }
        zlang::CZLangAST_auto tmp21_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp21_AST = astFactory.create(LT(1));
        astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp21_AST));
        match(IDENTIFIER);
        zlang::CZLangAST_auto tmp22_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp22_AST = astFactory.create(LT(1));
        match(LPAREN);
        {
        switch ( LA(1)) {
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
          parameterDeclarationList();
          astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
          break;
        }
        case RPAREN:
        {
          break;
        }
        default:
        {
          throw antlr::NoViableAltException(LT(1), getFilename());
        }
        }
        }
        zlang::CZLangAST_auto tmp23_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp23_AST = astFactory.create(LT(1));
        match(RPAREN);
        codeBlock();
        astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
        globalDefinition_AST = zlang::CZLangAST_auto(currentAST.root);
#line 168 "zlangpass1.g"
        
        if (bStatic)
        {
        globalDefinition_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(3))->add(static_cast<antlr::RefAST>(astFactory.create(GFUNCTION_DEFINITION,"GFUNCTION_DEFINITION")))->add(static_cast<antlr::RefAST>(tSTATIC_AST))->add(static_cast<antlr::RefAST>(globalDefinition_AST))));
        }
        else
        {
        globalDefinition_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(GFUNCTION_DEFINITION,"GFUNCTION_DEFINITION")))->add(static_cast<antlr::RefAST>(globalDefinition_AST))));
        }
        
#line 543 "ZLangParser.cpp"
        currentAST.root = globalDefinition_AST;
        if ( globalDefinition_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
          globalDefinition_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
            currentAST.child = globalDefinition_AST->getFirstChild();
        else
          currentAST.child = globalDefinition_AST;
        currentAST.advanceChildToEnd();
      }
      else if ((LA(1)==IDENTIFIER) && (_tokenSet_0.member(LA(2)))) {
        {
        tNAME1 = LT(1);
        tNAME1_AST = astFactory.create(tNAME1);
        match(IDENTIFIER);
        {
        switch ( LA(1)) {
        case ASSIGN:
        {
          zlang::CZLangAST_auto tmp24_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
          tmp24_AST = astFactory.create(LT(1));
          match(ASSIGN);
          initializationConstant();
          rINIT1_AST = zlang::CZLangAST_auto(returnAST);
#line 183 "zlangpass1.g"
          tNAME1_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(tNAME1_AST))->add(static_cast<antlr::RefAST>(rINIT1_AST))));
#line 568 "ZLangParser.cpp"
          break;
        }
        case SEMI:
        case COMMA:
        {
          break;
        }
        default:
        {
          throw antlr::NoViableAltException(LT(1), getFilename());
        }
        }
        }
#line 185 "zlangpass1.g"
        astFactory.addASTChild(currentAST, ANTLR_USE_NAMESPACE(antlr)RefAST(tNAME1_AST));
#line 584 "ZLangParser.cpp"
        {
        for (;;) {
          if ((LA(1)==COMMA)) {
            zlang::CZLangAST_auto tmp25_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
            tmp25_AST = astFactory.create(LT(1));
            match(COMMA);
            tNAME2 = LT(1);
            tNAME2_AST = astFactory.create(tNAME2);
            match(IDENTIFIER);
            {
            switch ( LA(1)) {
            case ASSIGN:
            {
              zlang::CZLangAST_auto tmp26_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
              tmp26_AST = astFactory.create(LT(1));
              match(ASSIGN);
              initializationConstant();
              rINIT2_AST = zlang::CZLangAST_auto(returnAST);
#line 188 "zlangpass1.g"
              tNAME2_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(tNAME2_AST))->add(static_cast<antlr::RefAST>(rINIT2_AST))));
#line 605 "ZLangParser.cpp"
              break;
            }
            case SEMI:
            case COMMA:
            {
              break;
            }
            default:
            {
              throw antlr::NoViableAltException(LT(1), getFilename());
            }
            }
            }
#line 190 "zlangpass1.g"
            astFactory.addASTChild(currentAST, ANTLR_USE_NAMESPACE(antlr)RefAST(tNAME2_AST));
#line 621 "ZLangParser.cpp"
          }
          else {
            goto _loop24;
          }
          
        }
        _loop24:;
        }
        zlang::CZLangAST_auto tmp27_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp27_AST = astFactory.create(LT(1));
        match(SEMI);
        }
        globalDefinition_AST = zlang::CZLangAST_auto(currentAST.root);
#line 194 "zlangpass1.g"
        
        if (bStatic)
        {
        globalDefinition_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(3))->add(static_cast<antlr::RefAST>(astFactory.create(GVARIABLE_DEFINITION,"GVARIABLE_DEFINITION")))->add(static_cast<antlr::RefAST>(tSTATIC_AST))->add(static_cast<antlr::RefAST>(globalDefinition_AST))));
        }
        else
        {
        globalDefinition_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(GVARIABLE_DEFINITION,"GVARIABLE_DEFINITION")))->add(static_cast<antlr::RefAST>(globalDefinition_AST))));
        }
        
#line 646 "ZLangParser.cpp"
        currentAST.root = globalDefinition_AST;
        if ( globalDefinition_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
          globalDefinition_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
            currentAST.child = globalDefinition_AST->getFirstChild();
        else
          currentAST.child = globalDefinition_AST;
        currentAST.advanceChildToEnd();
      }
      else {
        throw antlr::NoViableAltException(LT(1), getFilename());
      }
      
      }
      break;
    }
    case LITERAL_table:
    {
      zlang::CZLangAST_auto tmp28_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp28_AST = astFactory.create(LT(1));
      astFactory.addASTChild(currentAST, antlr::RefAST(tmp28_AST));
      match(LITERAL_table);
      zlang::CZLangAST_auto tmp29_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp29_AST = astFactory.create(LT(1));
      match(LT_);
      builtInType();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
      zlang::CZLangAST_auto tmp30_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp30_AST = astFactory.create(LT(1));
      match(GT);
      {
      if ((LA(1)==BAND||LA(1)==IDENTIFIER) && (LA(2)==IDENTIFIER||LA(2)==LPAREN)) {
        {
        switch ( LA(1)) {
        case BAND:
        {
          zlang::CZLangAST_auto tmp31_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
          tmp31_AST = astFactory.create(LT(1));
          astFactory.addASTChild(currentAST, antlr::RefAST(tmp31_AST));
          match(BAND);
          break;
        }
        case IDENTIFIER:
        {
          break;
        }
        default:
        {
          throw antlr::NoViableAltException(LT(1), getFilename());
        }
        }
        }
        zlang::CZLangAST_auto tmp32_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp32_AST = astFactory.create(LT(1));
        astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp32_AST));
        match(IDENTIFIER);
        zlang::CZLangAST_auto tmp33_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp33_AST = astFactory.create(LT(1));
        match(LPAREN);
        {
        switch ( LA(1)) {
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
          parameterDeclarationList();
          astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
          break;
        }
        case RPAREN:
        {
          break;
        }
        default:
        {
          throw antlr::NoViableAltException(LT(1), getFilename());
        }
        }
        }
        zlang::CZLangAST_auto tmp34_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp34_AST = astFactory.create(LT(1));
        match(RPAREN);
        codeBlock();
        astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
        globalDefinition_AST = zlang::CZLangAST_auto(currentAST.root);
#line 208 "zlangpass1.g"
        
        if (bStatic)
        {
        globalDefinition_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(3))->add(static_cast<antlr::RefAST>(astFactory.create(GFUNCTION_DEFINITION,"GFUNCTION_DEFINITION")))->add(static_cast<antlr::RefAST>(tSTATIC_AST))->add(static_cast<antlr::RefAST>(globalDefinition_AST))));
        }
        else
        {
        globalDefinition_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(GFUNCTION_DEFINITION,"GFUNCTION_DEFINITION")))->add(static_cast<antlr::RefAST>(globalDefinition_AST))));
        }
        
#line 751 "ZLangParser.cpp"
        currentAST.root = globalDefinition_AST;
        if ( globalDefinition_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
          globalDefinition_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
            currentAST.child = globalDefinition_AST->getFirstChild();
        else
          currentAST.child = globalDefinition_AST;
        currentAST.advanceChildToEnd();
      }
      else if ((LA(1)==IDENTIFIER) && (LA(2)==SEMI||LA(2)==ASSIGN)) {
        zlang::CZLangAST_auto tmp35_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp35_AST = astFactory.create(LT(1));
        astFactory.addASTChild(currentAST, antlr::RefAST(tmp35_AST));
        match(IDENTIFIER);
        {
        switch ( LA(1)) {
        case ASSIGN:
        {
          tableInit();
          astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
          break;
        }
        case SEMI:
        {
          break;
        }
        default:
        {
          throw antlr::NoViableAltException(LT(1), getFilename());
        }
        }
        }
        zlang::CZLangAST_auto tmp36_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp36_AST = astFactory.create(LT(1));
        match(SEMI);
        globalDefinition_AST = zlang::CZLangAST_auto(currentAST.root);
#line 220 "zlangpass1.g"
        
        if (bStatic)
        {
        globalDefinition_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(3))->add(static_cast<antlr::RefAST>(astFactory.create(GVARIABLE_DEFINITION,"GVARIABLE_DEFINITION")))->add(static_cast<antlr::RefAST>(tSTATIC_AST))->add(static_cast<antlr::RefAST>(globalDefinition_AST))));
        }
        else
        {
        globalDefinition_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(GVARIABLE_DEFINITION,"GVARIABLE_DEFINITION")))->add(static_cast<antlr::RefAST>(globalDefinition_AST))));
        }
        
#line 798 "ZLangParser.cpp"
        currentAST.root = globalDefinition_AST;
        if ( globalDefinition_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
          globalDefinition_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
            currentAST.child = globalDefinition_AST->getFirstChild();
        else
          currentAST.child = globalDefinition_AST;
        currentAST.advanceChildToEnd();
      }
      else {
        throw antlr::NoViableAltException(LT(1), getFilename());
      }
      
      }
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(LT(1), getFilename());
    }
    }
    }
    break;
  }
  case LITERAL_void:
  {
    zlang::CZLangAST_auto tmp37_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp37_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp37_AST));
    match(LITERAL_void);
    zlang::CZLangAST_auto tmp38_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp38_AST = astFactory.create(LT(1));
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp38_AST));
    match(IDENTIFIER);
    zlang::CZLangAST_auto tmp39_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp39_AST = astFactory.create(LT(1));
    match(LPAREN);
    {
    switch ( LA(1)) {
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
      parameterDeclarationList();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
      break;
    }
    case RPAREN:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(LT(1), getFilename());
    }
    }
    }
    zlang::CZLangAST_auto tmp40_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp40_AST = astFactory.create(LT(1));
    match(RPAREN);
    codeBlock();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    globalDefinition_AST = zlang::CZLangAST_auto(currentAST.root);
#line 233 "zlangpass1.g"
    
    if (bStatic)
    {
    globalDefinition_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(3))->add(static_cast<antlr::RefAST>(astFactory.create(GFUNCTION_DEFINITION,"GFUNCTION_DEFINITION")))->add(static_cast<antlr::RefAST>(tSTATIC_AST))->add(static_cast<antlr::RefAST>(globalDefinition_AST))));
    }
    else
    {
    globalDefinition_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(GFUNCTION_DEFINITION,"GFUNCTION_DEFINITION")))->add(static_cast<antlr::RefAST>(globalDefinition_AST))));
    }
    
#line 881 "ZLangParser.cpp"
    currentAST.root = globalDefinition_AST;
    if ( globalDefinition_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
      globalDefinition_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
        currentAST.child = globalDefinition_AST->getFirstChild();
    else
      currentAST.child = globalDefinition_AST;
    currentAST.advanceChildToEnd();
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  }
  globalDefinition_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = globalDefinition_AST;
}

void ZLangParser::builtInType() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto builtInType_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  switch ( LA(1)) {
  case LITERAL_byte:
  {
    zlang::CZLangAST_auto tmp41_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp41_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp41_AST));
    match(LITERAL_byte);
    builtInType_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_bool:
  {
    zlang::CZLangAST_auto tmp42_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp42_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp42_AST));
    match(LITERAL_bool);
    builtInType_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_sdword:
  {
    zlang::CZLangAST_auto tmp43_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp43_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp43_AST));
    match(LITERAL_sdword);
    builtInType_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_udword:
  {
    zlang::CZLangAST_auto tmp44_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp44_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp44_AST));
    match(LITERAL_udword);
    builtInType_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_sqword:
  {
    zlang::CZLangAST_auto tmp45_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp45_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp45_AST));
    match(LITERAL_sqword);
    builtInType_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_uqword:
  {
    zlang::CZLangAST_auto tmp46_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp46_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp46_AST));
    match(LITERAL_uqword);
    builtInType_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_double:
  {
    zlang::CZLangAST_auto tmp47_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp47_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp47_AST));
    match(LITERAL_double);
    builtInType_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_string:
  {
    zlang::CZLangAST_auto tmp48_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp48_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp48_AST));
    match(LITERAL_string);
    builtInType_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_ipaddress:
  {
    zlang::CZLangAST_auto tmp49_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp49_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp49_AST));
    match(LITERAL_ipaddress);
    builtInType_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_pport:
  {
    zlang::CZLangAST_auto tmp50_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp50_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp50_AST));
    match(LITERAL_pport);
    builtInType_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_rope:
  {
    zlang::CZLangAST_auto tmp51_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp51_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp51_AST));
    match(LITERAL_rope);
    builtInType_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  returnAST = builtInType_AST;
}

/**
 * PARAMETERS_DECLARATION
 *  |
 * <parameter1Name> - <parameter2Name> - <tableParameterName>
 *  |                  |                  |
 */
void ZLangParser::parameterDeclarationList() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto parameterDeclarationList_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  parameterDeclaration();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  {
  for (;;) {
    if ((LA(1)==COMMA)) {
      zlang::CZLangAST_auto tmp52_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp52_AST = astFactory.create(LT(1));
      match(COMMA);
      parameterDeclaration();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    }
    else {
      goto _loop35;
    }
    
  }
  _loop35:;
  }
  parameterDeclarationList_AST = zlang::CZLangAST_auto(currentAST.root);
#line 267 "zlangpass1.g"
  parameterDeclarationList_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(PARAMETERS_DECLARATION,"PARAMETERS_DECLARATION")))->add(static_cast<antlr::RefAST>(parameterDeclarationList_AST))));
#line 1046 "ZLangParser.cpp"
  currentAST.root = parameterDeclarationList_AST;
  if ( parameterDeclarationList_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
    parameterDeclarationList_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      currentAST.child = parameterDeclarationList_AST->getFirstChild();
  else
    currentAST.child = parameterDeclarationList_AST;
  currentAST.advanceChildToEnd();
  parameterDeclarationList_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = parameterDeclarationList_AST;
}

/**
 * CODE_BLOCK
 *  |
 * ...
 */
void ZLangParser::codeBlock() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto codeBlock_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto tmp53_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp53_AST = astFactory.create(LT(1));
  match(LCURLY);
  {
  for (;;) {
    if ((_tokenSet_1.member(LA(1)))) {
      localVariableDefinition();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    }
    else {
      goto _loop32;
    }
    
  }
  _loop32:;
  }
  compoundStatement();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  zlang::CZLangAST_auto tmp54_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp54_AST = astFactory.create(LT(1));
  match(RCURLY);
  codeBlock_AST = zlang::CZLangAST_auto(currentAST.root);
#line 256 "zlangpass1.g"
  codeBlock_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(CODE_BLOCK,"CODE_BLOCK")))->add(static_cast<antlr::RefAST>(codeBlock_AST))));
#line 1092 "ZLangParser.cpp"
  currentAST.root = codeBlock_AST;
  if ( codeBlock_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
    codeBlock_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      currentAST.child = codeBlock_AST->getFirstChild();
  else
    currentAST.child = codeBlock_AST;
  currentAST.advanceChildToEnd();
  codeBlock_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = codeBlock_AST;
}

void ZLangParser::initializationConstant() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto initializationConstant_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  switch ( LA(1)) {
  case PLUS:
  case MINUS:
  case NUM_INT:
  case NUM_QUAD:
  case NUM_FLOAT:
  {
    {
    switch ( LA(1)) {
    case PLUS:
    {
      zlang::CZLangAST_auto tmp55_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp55_AST = astFactory.create(LT(1));
      astFactory.addASTChild(currentAST, antlr::RefAST(tmp55_AST));
      match(PLUS);
      break;
    }
    case MINUS:
    {
      zlang::CZLangAST_auto tmp56_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp56_AST = astFactory.create(LT(1));
      astFactory.addASTChild(currentAST, antlr::RefAST(tmp56_AST));
      match(MINUS);
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
      throw antlr::NoViableAltException(LT(1), getFilename());
    }
    }
    }
    {
    switch ( LA(1)) {
    case NUM_INT:
    {
      zlang::CZLangAST_auto tmp57_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp57_AST = astFactory.create(LT(1));
      astFactory.addASTChild(currentAST, antlr::RefAST(tmp57_AST));
      match(NUM_INT);
      break;
    }
    case NUM_QUAD:
    {
      zlang::CZLangAST_auto tmp58_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp58_AST = astFactory.create(LT(1));
      astFactory.addASTChild(currentAST, antlr::RefAST(tmp58_AST));
      match(NUM_QUAD);
      break;
    }
    case NUM_FLOAT:
    {
      zlang::CZLangAST_auto tmp59_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp59_AST = astFactory.create(LT(1));
      astFactory.addASTChild(currentAST, antlr::RefAST(tmp59_AST));
      match(NUM_FLOAT);
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(LT(1), getFilename());
    }
    }
    }
    initializationConstant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case NUM_HEX_INT:
  {
    zlang::CZLangAST_auto tmp60_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp60_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp60_AST));
    match(NUM_HEX_INT);
    initializationConstant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case NUM_HEX_QUAD:
  {
    zlang::CZLangAST_auto tmp61_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp61_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp61_AST));
    match(NUM_HEX_QUAD);
    initializationConstant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case CHAR_LITERAL:
  {
    zlang::CZLangAST_auto tmp62_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp62_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp62_AST));
    match(CHAR_LITERAL);
    initializationConstant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case STRING_LITERAL:
  {
    zlang::CZLangAST_auto tmp63_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp63_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp63_AST));
    match(STRING_LITERAL);
    initializationConstant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case IPv4ADDR_LITERAL:
  {
    zlang::CZLangAST_auto tmp64_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp64_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp64_AST));
    match(IPv4ADDR_LITERAL);
    initializationConstant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case PPORT_LITERAL:
  {
    zlang::CZLangAST_auto tmp65_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp65_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp65_AST));
    match(PPORT_LITERAL);
    initializationConstant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_true:
  {
    zlang::CZLangAST_auto tmp66_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp66_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp66_AST));
    match(LITERAL_true);
    initializationConstant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_false:
  {
    zlang::CZLangAST_auto tmp67_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp67_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp67_AST));
    match(LITERAL_false);
    initializationConstant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case ROPE_LITERAL:
  {
    zlang::CZLangAST_auto tmp68_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp68_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp68_AST));
    match(ROPE_LITERAL);
    initializationConstant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  returnAST = initializationConstant_AST;
}

void ZLangParser::tableInit() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto tableInit_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto tmp69_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp69_AST = astFactory.create(LT(1));
  match(ASSIGN);
  {
  switch ( LA(1)) {
  case LCURLY:
  {
    zlang::CZLangAST_auto tmp70_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp70_AST = astFactory.create(LT(1));
    match(LCURLY);
    tableElementInit();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    {
    for (;;) {
      if ((LA(1)==COMMA)) {
        zlang::CZLangAST_auto tmp71_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp71_AST = astFactory.create(LT(1));
        match(COMMA);
        tableElementInit();
        astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
      }
      else {
        goto _loop67;
      }
      
    }
    _loop67:;
    }
    zlang::CZLangAST_auto tmp72_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp72_AST = astFactory.create(LT(1));
    match(RCURLY);
    break;
  }
  case IDENTIFIER:
  case LPAREN:
  case PLUS:
  case MINUS:
  case INC:
  case DEC:
  case BNOT:
  case LNOT:
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
    expression();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  }
  tableInit_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = tableInit_AST;
}

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
void ZLangParser::localVariableDefinition() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto localVariableDefinition_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::RefToken  tNAME1 = antlr::nullToken;
  zlang::CZLangAST_auto tNAME1_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto rINIT1_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::RefToken  tNAME2 = antlr::nullToken;
  zlang::CZLangAST_auto tNAME2_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  zlang::CZLangAST_auto rINIT2_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  {
  switch ( LA(1)) {
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
    builtInType();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    {
    switch ( LA(1)) {
    case BAND:
    {
      zlang::CZLangAST_auto tmp73_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp73_AST = astFactory.create(LT(1));
      astFactory.addASTChild(currentAST, antlr::RefAST(tmp73_AST));
      match(BAND);
      break;
    }
    case IDENTIFIER:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(LT(1), getFilename());
    }
    }
    }
    tNAME1 = LT(1);
    tNAME1_AST = astFactory.create(tNAME1);
    match(IDENTIFIER);
    {
    switch ( LA(1)) {
    case ASSIGN:
    {
      zlang::CZLangAST_auto tmp74_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp74_AST = astFactory.create(LT(1));
      match(ASSIGN);
      expression();
      rINIT1_AST = zlang::CZLangAST_auto(returnAST);
#line 383 "zlangpass1.g"
      tNAME1_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(tNAME1_AST))->add(static_cast<antlr::RefAST>(rINIT1_AST))));
#line 1429 "ZLangParser.cpp"
      break;
    }
    case SEMI:
    case COMMA:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(LT(1), getFilename());
    }
    }
    }
#line 385 "zlangpass1.g"
    astFactory.addASTChild(currentAST, ANTLR_USE_NAMESPACE(antlr)RefAST(tNAME1_AST));
#line 1445 "ZLangParser.cpp"
    {
    for (;;) {
      if ((LA(1)==COMMA)) {
        zlang::CZLangAST_auto tmp75_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp75_AST = astFactory.create(LT(1));
        match(COMMA);
        tNAME2 = LT(1);
        tNAME2_AST = astFactory.create(tNAME2);
        match(IDENTIFIER);
        {
        switch ( LA(1)) {
        case ASSIGN:
        {
          zlang::CZLangAST_auto tmp76_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
          tmp76_AST = astFactory.create(LT(1));
          match(ASSIGN);
          expression();
          rINIT2_AST = zlang::CZLangAST_auto(returnAST);
#line 388 "zlangpass1.g"
          tNAME2_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(tNAME2_AST))->add(static_cast<antlr::RefAST>(rINIT2_AST))));
#line 1466 "ZLangParser.cpp"
          break;
        }
        case SEMI:
        case COMMA:
        {
          break;
        }
        default:
        {
          throw antlr::NoViableAltException(LT(1), getFilename());
        }
        }
        }
#line 390 "zlangpass1.g"
        astFactory.addASTChild(currentAST, ANTLR_USE_NAMESPACE(antlr)RefAST(tNAME2_AST));
#line 1482 "ZLangParser.cpp"
      }
      else {
        goto _loop61;
      }
      
    }
    _loop61:;
    }
    zlang::CZLangAST_auto tmp77_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp77_AST = astFactory.create(LT(1));
    match(SEMI);
    break;
  }
  case LITERAL_table:
  {
    zlang::CZLangAST_auto tmp78_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp78_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp78_AST));
    match(LITERAL_table);
    zlang::CZLangAST_auto tmp79_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp79_AST = astFactory.create(LT(1));
    match(LT_);
    builtInType();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    zlang::CZLangAST_auto tmp80_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp80_AST = astFactory.create(LT(1));
    match(GT);
    {
    switch ( LA(1)) {
    case BAND:
    {
      zlang::CZLangAST_auto tmp81_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp81_AST = astFactory.create(LT(1));
      astFactory.addASTChild(currentAST, antlr::RefAST(tmp81_AST));
      match(BAND);
      break;
    }
    case IDENTIFIER:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(LT(1), getFilename());
    }
    }
    }
    zlang::CZLangAST_auto tmp82_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp82_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp82_AST));
    match(IDENTIFIER);
    {
    switch ( LA(1)) {
    case ASSIGN:
    {
      tableInit();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
      break;
    }
    case SEMI:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(LT(1), getFilename());
    }
    }
    }
    zlang::CZLangAST_auto tmp83_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp83_AST = astFactory.create(LT(1));
    match(SEMI);
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  }
  localVariableDefinition_AST = zlang::CZLangAST_auto(currentAST.root);
#line 396 "zlangpass1.g"
  localVariableDefinition_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(LVARIABLE_DEFINITION,"LVARIABLE_DEFINITION")))->add(static_cast<antlr::RefAST>(localVariableDefinition_AST))));
#line 1566 "ZLangParser.cpp"
  currentAST.root = localVariableDefinition_AST;
  if ( localVariableDefinition_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
    localVariableDefinition_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      currentAST.child = localVariableDefinition_AST->getFirstChild();
  else
    currentAST.child = localVariableDefinition_AST;
  currentAST.advanceChildToEnd();
  localVariableDefinition_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = localVariableDefinition_AST;
}

/**
 * COMPOUND_STATEMENTS
 *  |
 * LITERAL_if - LITERAL_while - EXPRESSION - ...
 */
void ZLangParser::compoundStatement() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto compoundStatement_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  {
  for (;;) {
    if ((_tokenSet_2.member(LA(1)))) {
      statement();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    }
    else {
      goto _loop42;
    }
    
  }
  _loop42:;
  }
  compoundStatement_AST = zlang::CZLangAST_auto(currentAST.root);
#line 288 "zlangpass1.g"
  compoundStatement_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(COMPOUND_STATEMENTS,"COMPOUND_STATEMENTS")))->add(static_cast<antlr::RefAST>(compoundStatement_AST))));
#line 1604 "ZLangParser.cpp"
  currentAST.root = compoundStatement_AST;
  if ( compoundStatement_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
    compoundStatement_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      currentAST.child = compoundStatement_AST->getFirstChild();
  else
    currentAST.child = compoundStatement_AST;
  currentAST.advanceChildToEnd();
  compoundStatement_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = compoundStatement_AST;
}

/**
 * <parameterName>             <tableParameterName>
 *  |                           |
 * <builtInType> - '&'?        "table" - <builtInType> - '&'?
 */
void ZLangParser::parameterDeclaration() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto parameterDeclaration_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  {
  switch ( LA(1)) {
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
    builtInType();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    {
    switch ( LA(1)) {
    case BAND:
    {
      zlang::CZLangAST_auto tmp84_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp84_AST = astFactory.create(LT(1));
      astFactory.addASTChild(currentAST, antlr::RefAST(tmp84_AST));
      match(BAND);
      break;
    }
    case IDENTIFIER:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(LT(1), getFilename());
    }
    }
    }
    zlang::CZLangAST_auto tmp85_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp85_AST = astFactory.create(LT(1));
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp85_AST));
    match(IDENTIFIER);
    break;
  }
  case LITERAL_table:
  {
    zlang::CZLangAST_auto tmp86_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp86_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp86_AST));
    match(LITERAL_table);
    zlang::CZLangAST_auto tmp87_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp87_AST = astFactory.create(LT(1));
    match(LT_);
    builtInType();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    zlang::CZLangAST_auto tmp88_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp88_AST = astFactory.create(LT(1));
    match(GT);
    {
    switch ( LA(1)) {
    case BAND:
    {
      zlang::CZLangAST_auto tmp89_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp89_AST = astFactory.create(LT(1));
      astFactory.addASTChild(currentAST, antlr::RefAST(tmp89_AST));
      match(BAND);
      break;
    }
    case IDENTIFIER:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(LT(1), getFilename());
    }
    }
    }
    zlang::CZLangAST_auto tmp90_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp90_AST = astFactory.create(LT(1));
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp90_AST));
    match(IDENTIFIER);
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  }
  parameterDeclaration_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = parameterDeclaration_AST;
}

void ZLangParser::statement() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto statement_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  switch ( LA(1)) {
  case SEMI:
  {
    zlang::CZLangAST_auto tmp91_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp91_AST = astFactory.create(LT(1));
    match(SEMI);
    statement_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case IDENTIFIER:
  case LPAREN:
  case PLUS:
  case MINUS:
  case INC:
  case DEC:
  case BNOT:
  case LNOT:
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
    expression();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    zlang::CZLangAST_auto tmp92_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp92_AST = astFactory.create(LT(1));
    match(SEMI);
    statement_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_if:
  {
    ifStatement();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    statement_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_while:
  {
    whileStatement();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    statement_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_break:
  {
    zlang::CZLangAST_auto tmp93_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp93_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp93_AST));
    match(LITERAL_break);
    zlang::CZLangAST_auto tmp94_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp94_AST = astFactory.create(LT(1));
    match(SEMI);
    statement_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_continue:
  {
    zlang::CZLangAST_auto tmp95_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp95_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp95_AST));
    match(LITERAL_continue);
    zlang::CZLangAST_auto tmp96_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp96_AST = astFactory.create(LT(1));
    match(SEMI);
    statement_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_return:
  {
    zlang::CZLangAST_auto tmp97_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp97_AST = astFactory.create(LT(1));
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp97_AST));
    match(LITERAL_return);
    {
    switch ( LA(1)) {
    case IDENTIFIER:
    case LPAREN:
    case PLUS:
    case MINUS:
    case INC:
    case DEC:
    case BNOT:
    case LNOT:
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
      expression();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
      break;
    }
    case SEMI:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(LT(1), getFilename());
    }
    }
    }
    zlang::CZLangAST_auto tmp98_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp98_AST = astFactory.create(LT(1));
    match(SEMI);
    statement_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_for:
  {
    forStatement();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    statement_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  returnAST = statement_AST;
}

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
void ZLangParser::expression() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto expression_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  assignExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  expression_AST = zlang::CZLangAST_auto(currentAST.root);
#line 468 "zlangpass1.g"
  expression_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(EXPRESSION,"EXPRESSION")))->add(static_cast<antlr::RefAST>(expression_AST))));
#line 1914 "ZLangParser.cpp"
  currentAST.root = expression_AST;
  if ( expression_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
    expression_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      currentAST.child = expression_AST->getFirstChild();
  else
    currentAST.child = expression_AST;
  currentAST.advanceChildToEnd();
  expression_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = expression_AST;
}

/**
 * LITERAL_if
 *  |
 * EXPRESSION - COMPOUND_STATEMENTS - COMPOUND_STATEMENTS
 */
void ZLangParser::ifStatement() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto ifStatement_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto tmp99_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp99_AST = astFactory.create(LT(1));
  astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp99_AST));
  match(LITERAL_if);
  zlang::CZLangAST_auto tmp100_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp100_AST = astFactory.create(LT(1));
  match(LPAREN);
  expression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  zlang::CZLangAST_auto tmp101_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp101_AST = astFactory.create(LT(1));
  match(RPAREN);
  zlang::CZLangAST_auto tmp102_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp102_AST = astFactory.create(LT(1));
  match(LCURLY);
  compoundStatement();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  zlang::CZLangAST_auto tmp103_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp103_AST = astFactory.create(LT(1));
  match(RCURLY);
  {
  switch ( LA(1)) {
  case LITERAL_else:
  {
    zlang::CZLangAST_auto tmp104_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp104_AST = astFactory.create(LT(1));
    match(LITERAL_else);
    zlang::CZLangAST_auto tmp105_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp105_AST = astFactory.create(LT(1));
    match(LCURLY);
    compoundStatement();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    zlang::CZLangAST_auto tmp106_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp106_AST = astFactory.create(LT(1));
    match(RCURLY);
    break;
  }
  case IDENTIFIER:
  case LPAREN:
  case SEMI:
  case RCURLY:
  case LITERAL_break:
  case LITERAL_continue:
  case LITERAL_return:
  case LITERAL_if:
  case LITERAL_while:
  case LITERAL_for:
  case PLUS:
  case MINUS:
  case INC:
  case DEC:
  case BNOT:
  case LNOT:
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
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  }
  ifStatement_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = ifStatement_AST;
}

/**
 * LITERAL_while
 *  |
 * EXPRESSION - COMPOUND_STATEMENTS
 */
void ZLangParser::whileStatement() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto whileStatement_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto tmp107_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp107_AST = astFactory.create(LT(1));
  astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp107_AST));
  match(LITERAL_while);
  zlang::CZLangAST_auto tmp108_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp108_AST = astFactory.create(LT(1));
  match(LPAREN);
  expression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  zlang::CZLangAST_auto tmp109_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp109_AST = astFactory.create(LT(1));
  match(RPAREN);
  zlang::CZLangAST_auto tmp110_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp110_AST = astFactory.create(LT(1));
  match(LCURLY);
  compoundStatement();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  zlang::CZLangAST_auto tmp111_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp111_AST = astFactory.create(LT(1));
  match(RCURLY);
  whileStatement_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = whileStatement_AST;
}

/**
 * LITERAL_for
 *  |
 * EXPRESSION1? - EXPRESSION2? - EXPRESSION3? - COMPOUND_STATEMENTS
 */
void ZLangParser::forStatement() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto forStatement_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  zlang::CZLangAST_auto tmp112_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp112_AST = astFactory.create(LT(1));
  astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp112_AST));
  match(LITERAL_for);
  zlang::CZLangAST_auto tmp113_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp113_AST = astFactory.create(LT(1));
  match(LPAREN);
  {
  switch ( LA(1)) {
  case IDENTIFIER:
  case LPAREN:
  case PLUS:
  case MINUS:
  case INC:
  case DEC:
  case BNOT:
  case LNOT:
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
    forExpression1();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    break;
  }
  case SEMI:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  }
  zlang::CZLangAST_auto tmp114_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp114_AST = astFactory.create(LT(1));
  match(SEMI);
  {
  switch ( LA(1)) {
  case IDENTIFIER:
  case LPAREN:
  case PLUS:
  case MINUS:
  case INC:
  case DEC:
  case BNOT:
  case LNOT:
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
    forExpression2();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    break;
  }
  case SEMI:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  }
  zlang::CZLangAST_auto tmp115_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp115_AST = astFactory.create(LT(1));
  match(SEMI);
  {
  switch ( LA(1)) {
  case IDENTIFIER:
  case LPAREN:
  case PLUS:
  case MINUS:
  case INC:
  case DEC:
  case BNOT:
  case LNOT:
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
    forExpression3();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    break;
  }
  case RPAREN:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  }
  zlang::CZLangAST_auto tmp116_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp116_AST = astFactory.create(LT(1));
  match(RPAREN);
  zlang::CZLangAST_auto tmp117_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp117_AST = astFactory.create(LT(1));
  match(LCURLY);
  compoundStatement();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  zlang::CZLangAST_auto tmp118_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp118_AST = astFactory.create(LT(1));
  match(RCURLY);
  forStatement_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = forStatement_AST;
}

void ZLangParser::forExpression1() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto forExpression1_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  assignExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  forExpression1_AST = zlang::CZLangAST_auto(currentAST.root);
#line 341 "zlangpass1.g"
  forExpression1_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(FOR_EXPRESSION1,"FOR_EXPRESSION1")))->add(static_cast<antlr::RefAST>(forExpression1_AST))));
#line 2207 "ZLangParser.cpp"
  currentAST.root = forExpression1_AST;
  if ( forExpression1_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
    forExpression1_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      currentAST.child = forExpression1_AST->getFirstChild();
  else
    currentAST.child = forExpression1_AST;
  currentAST.advanceChildToEnd();
  forExpression1_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = forExpression1_AST;
}

void ZLangParser::forExpression2() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto forExpression2_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  assignExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  forExpression2_AST = zlang::CZLangAST_auto(currentAST.root);
#line 346 "zlangpass1.g"
  forExpression2_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(FOR_EXPRESSION2,"FOR_EXPRESSION2")))->add(static_cast<antlr::RefAST>(forExpression2_AST))));
#line 2229 "ZLangParser.cpp"
  currentAST.root = forExpression2_AST;
  if ( forExpression2_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
    forExpression2_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      currentAST.child = forExpression2_AST->getFirstChild();
  else
    currentAST.child = forExpression2_AST;
  currentAST.advanceChildToEnd();
  forExpression2_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = forExpression2_AST;
}

void ZLangParser::forExpression3() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto forExpression3_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  assignExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  forExpression3_AST = zlang::CZLangAST_auto(currentAST.root);
#line 351 "zlangpass1.g"
  forExpression3_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(FOR_EXPRESSION3,"FOR_EXPRESSION3")))->add(static_cast<antlr::RefAST>(forExpression3_AST))));
#line 2251 "ZLangParser.cpp"
  currentAST.root = forExpression3_AST;
  if ( forExpression3_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
    forExpression3_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      currentAST.child = forExpression3_AST->getFirstChild();
  else
    currentAST.child = forExpression3_AST;
  currentAST.advanceChildToEnd();
  forExpression3_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = forExpression3_AST;
}

/**
 * assign (=)  (level 13)
 *
 * ASSIGN
 *   |
 * leftSubTree - rightSubTree
 */
void ZLangParser::assignExpression() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto assignExpression_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  logicalOrExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  {
  switch ( LA(1)) {
  case ASSIGN:
  {
    zlang::CZLangAST_auto tmp119_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp119_AST = astFactory.create(LT(1));
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp119_AST));
    match(ASSIGN);
    assignExpression();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    break;
  }
  case RPAREN:
  case SEMI:
  case COMMA:
  case RBRACK:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  }
  assignExpression_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = assignExpression_AST;
}

void ZLangParser::tableElementInit() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto tableElementInit_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  initializationConstant();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  zlang::CZLangAST_auto tmp120_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  tmp120_AST = astFactory.create(LT(1));
  match(ASSIGN);
  initializationConstant();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  tableElementInit_AST = zlang::CZLangAST_auto(currentAST.root);
#line 408 "zlangpass1.g"
  tableElementInit_AST = zlang::CZLangAST_auto(astFactory.make((new antlr::ASTArray(2))->add(static_cast<antlr::RefAST>(astFactory.create(ELEMENT_INIT,"ELEMENT_INIT")))->add(static_cast<antlr::RefAST>(tableElementInit_AST))));
#line 2321 "ZLangParser.cpp"
  currentAST.root = tableElementInit_AST;
  if ( tableElementInit_AST!=static_cast<zlang::CZLangAST_auto>(antlr::nullAST) &&
    tableElementInit_AST->getFirstChild() != static_cast<zlang::CZLangAST_auto>(antlr::nullAST) )
      currentAST.child = tableElementInit_AST->getFirstChild();
  else
    currentAST.child = tableElementInit_AST;
  currentAST.advanceChildToEnd();
  tableElementInit_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = tableElementInit_AST;
}

/** this is a list of expressions for function calling. */
void ZLangParser::argumentList() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto argumentList_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  expression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  {
  for (;;) {
    if ((LA(1)==COMMA)) {
      zlang::CZLangAST_auto tmp121_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp121_AST = astFactory.create(LT(1));
      match(COMMA);
      expression();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    }
    else {
      goto _loop73;
    }
    
  }
  _loop73:;
  }
  argumentList_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = argumentList_AST;
}

/**
 * logical or (||)  (level 11)
 *
 * LOR
 *  |
 * leftSubTree - rightSubTree
 */
void ZLangParser::logicalOrExpression() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto logicalOrExpression_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  logicalAndExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  {
  for (;;) {
    if ((LA(1)==LOR)) {
      zlang::CZLangAST_auto tmp122_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp122_AST = astFactory.create(LT(1));
      astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp122_AST));
      match(LOR);
      logicalAndExpression();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    }
    else {
      goto _loop78;
    }
    
  }
  _loop78:;
  }
  logicalOrExpression_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = logicalOrExpression_AST;
}

/**
 * logical and (&&)  (level 10)
 *
 * LAND
 *  |
 * leftSubTree - rightSubTree
 */
void ZLangParser::logicalAndExpression() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto logicalAndExpression_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  bitwiseOrExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  {
  for (;;) {
    if ((LA(1)==LAND)) {
      zlang::CZLangAST_auto tmp123_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp123_AST = astFactory.create(LT(1));
      astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp123_AST));
      match(LAND);
      bitwiseOrExpression();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    }
    else {
      goto _loop81;
    }
    
  }
  _loop81:;
  }
  logicalAndExpression_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = logicalAndExpression_AST;
}

/**
 * bitwise or non-short-circuiting or (|)  (level 9)
 *
 * BOR
 *  |
 * leftSubTree - rightSubTree
 */
void ZLangParser::bitwiseOrExpression() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto bitwiseOrExpression_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  bitwiseXorExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  {
  for (;;) {
    if ((LA(1)==BOR)) {
      zlang::CZLangAST_auto tmp124_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp124_AST = astFactory.create(LT(1));
      astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp124_AST));
      match(BOR);
      bitwiseXorExpression();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    }
    else {
      goto _loop84;
    }
    
  }
  _loop84:;
  }
  bitwiseOrExpression_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = bitwiseOrExpression_AST;
}

/**
 * exclusive or (^)  (level 8)
 *
 * BXOR
 *  |
 * leftSubTree - rightSubTree
 */
void ZLangParser::bitwiseXorExpression() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto bitwiseXorExpression_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  bitwiseAndExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  {
  for (;;) {
    if ((LA(1)==BXOR)) {
      zlang::CZLangAST_auto tmp125_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp125_AST = astFactory.create(LT(1));
      astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp125_AST));
      match(BXOR);
      bitwiseAndExpression();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    }
    else {
      goto _loop87;
    }
    
  }
  _loop87:;
  }
  bitwiseXorExpression_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = bitwiseXorExpression_AST;
}

/**
 * bitwise or non-short-circuiting and (&)  (level 7)
 *
 * BAND
 *  |
 * leftSubTree - rightSubTree
 */
void ZLangParser::bitwiseAndExpression() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto bitwiseAndExpression_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  equalityExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  {
  for (;;) {
    if ((LA(1)==BAND)) {
      zlang::CZLangAST_auto tmp126_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp126_AST = astFactory.create(LT(1));
      astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp126_AST));
      match(BAND);
      equalityExpression();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    }
    else {
      goto _loop90;
    }
    
  }
  _loop90:;
  }
  bitwiseAndExpression_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = bitwiseAndExpression_AST;
}

/**
 * equality/inequality (== !=) (level 6)
 *
 * NOT_EQUAL/EQUAL
 *  |
 * leftSubTree - rightSubTree
 */
void ZLangParser::equalityExpression() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto equalityExpression_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  relationalExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  {
  for (;;) {
    if ((LA(1)==NOT_EQUAL||LA(1)==EQUAL)) {
      {
      switch ( LA(1)) {
      case NOT_EQUAL:
      {
        zlang::CZLangAST_auto tmp127_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp127_AST = astFactory.create(LT(1));
        astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp127_AST));
        match(NOT_EQUAL);
        break;
      }
      case EQUAL:
      {
        zlang::CZLangAST_auto tmp128_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp128_AST = astFactory.create(LT(1));
        astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp128_AST));
        match(EQUAL);
        break;
      }
      default:
      {
        throw antlr::NoViableAltException(LT(1), getFilename());
      }
      }
      }
      relationalExpression();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    }
    else {
      goto _loop94;
    }
    
  }
  _loop94:;
  }
  equalityExpression_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = equalityExpression_AST;
}

/**
 * boolean relational expressions (level 5)
 *
 * LT_/GT/LE/GE
 *  |
 * leftSubTree - rightSubTree
 */
void ZLangParser::relationalExpression() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto relationalExpression_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  shiftExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  {
  for (;;) {
    if ((_tokenSet_3.member(LA(1)))) {
      {
      switch ( LA(1)) {
      case LT_:
      {
        zlang::CZLangAST_auto tmp129_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp129_AST = astFactory.create(LT(1));
        astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp129_AST));
        match(LT_);
        break;
      }
      case GT:
      {
        zlang::CZLangAST_auto tmp130_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp130_AST = astFactory.create(LT(1));
        astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp130_AST));
        match(GT);
        break;
      }
      case LE:
      {
        zlang::CZLangAST_auto tmp131_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp131_AST = astFactory.create(LT(1));
        astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp131_AST));
        match(LE);
        break;
      }
      case GE:
      {
        zlang::CZLangAST_auto tmp132_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp132_AST = astFactory.create(LT(1));
        astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp132_AST));
        match(GE);
        break;
      }
      default:
      {
        throw antlr::NoViableAltException(LT(1), getFilename());
      }
      }
      }
      shiftExpression();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    }
    else {
      goto _loop98;
    }
    
  }
  _loop98:;
  }
  relationalExpression_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = relationalExpression_AST;
}

/**
 * bit shift expressions (<< >>) (level 4)
 *
 * SL/SR
 *  |
 * leftSubTree - rightSubTree
 */
void ZLangParser::shiftExpression() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto shiftExpression_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  additiveExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  {
  for (;;) {
    if ((LA(1)==SL||LA(1)==SR)) {
      {
      switch ( LA(1)) {
      case SL:
      {
        zlang::CZLangAST_auto tmp133_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp133_AST = astFactory.create(LT(1));
        astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp133_AST));
        match(SL);
        break;
      }
      case SR:
      {
        zlang::CZLangAST_auto tmp134_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp134_AST = astFactory.create(LT(1));
        astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp134_AST));
        match(SR);
        break;
      }
      default:
      {
        throw antlr::NoViableAltException(LT(1), getFilename());
      }
      }
      }
      additiveExpression();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    }
    else {
      goto _loop102;
    }
    
  }
  _loop102:;
  }
  shiftExpression_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = shiftExpression_AST;
}

/**
 * binary addition/subtraction (+ -) (level 3)
 *
 * PLUS/MINUS
 *  |
 * leftSubTree - rightSubTree
 */
void ZLangParser::additiveExpression() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto additiveExpression_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  multiplicativeExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  {
  for (;;) {
    if ((LA(1)==PLUS||LA(1)==MINUS)) {
      {
      switch ( LA(1)) {
      case PLUS:
      {
        zlang::CZLangAST_auto tmp135_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp135_AST = astFactory.create(LT(1));
        astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp135_AST));
        match(PLUS);
        break;
      }
      case MINUS:
      {
        zlang::CZLangAST_auto tmp136_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp136_AST = astFactory.create(LT(1));
        astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp136_AST));
        match(MINUS);
        break;
      }
      default:
      {
        throw antlr::NoViableAltException(LT(1), getFilename());
      }
      }
      }
      multiplicativeExpression();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    }
    else {
      goto _loop106;
    }
    
  }
  _loop106:;
  }
  additiveExpression_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = additiveExpression_AST;
}

/**
 * multiplication/division/modulo (* / %) (level 2)
 *
 * STAR/DIV/MOD
 *  |
 * leftSubTree - rightSubTree
 */
void ZLangParser::multiplicativeExpression() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto multiplicativeExpression_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  unaryExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  {
  for (;;) {
    if (((LA(1) >= STAR && LA(1) <= MOD))) {
      {
      switch ( LA(1)) {
      case STAR:
      {
        zlang::CZLangAST_auto tmp137_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp137_AST = astFactory.create(LT(1));
        astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp137_AST));
        match(STAR);
        break;
      }
      case DIV:
      {
        zlang::CZLangAST_auto tmp138_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp138_AST = astFactory.create(LT(1));
        astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp138_AST));
        match(DIV);
        break;
      }
      case MOD:
      {
        zlang::CZLangAST_auto tmp139_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
        tmp139_AST = astFactory.create(LT(1));
        astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp139_AST));
        match(MOD);
        break;
      }
      default:
      {
        throw antlr::NoViableAltException(LT(1), getFilename());
      }
      }
      }
      unaryExpression();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    }
    else {
      goto _loop110;
    }
    
  }
  _loop110:;
  }
  multiplicativeExpression_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = multiplicativeExpression_AST;
}

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
void ZLangParser::unaryExpression() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto unaryExpression_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::RefToken  tCAST = antlr::nullToken;
  zlang::CZLangAST_auto tCAST_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  {
  switch ( LA(1)) {
  case INC:
  {
    zlang::CZLangAST_auto tmp140_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp140_AST = astFactory.create(LT(1));
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp140_AST));
    match(INC);
    break;
  }
  case DEC:
  {
    zlang::CZLangAST_auto tmp141_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp141_AST = astFactory.create(LT(1));
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp141_AST));
    match(DEC);
    break;
  }
  case MINUS:
  {
    zlang::CZLangAST_auto tmp142_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp142_AST = astFactory.create(LT(1));
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp142_AST));
    match(MINUS);
#line 623 "zlangpass1.g"
    tmp142_AST->setType(UNARY_MINUS); tmp142_AST->setText("UNARY_MINUS");
#line 2879 "ZLangParser.cpp"
    break;
  }
  case PLUS:
  {
    zlang::CZLangAST_auto tmp143_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp143_AST = astFactory.create(LT(1));
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp143_AST));
    match(PLUS);
#line 625 "zlangpass1.g"
    tmp143_AST->setType(UNARY_PLUS); tmp143_AST->setText("UNARY_PLUS");
#line 2890 "ZLangParser.cpp"
    break;
  }
  case BNOT:
  {
    zlang::CZLangAST_auto tmp144_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp144_AST = astFactory.create(LT(1));
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp144_AST));
    match(BNOT);
    break;
  }
  case LNOT:
  {
    zlang::CZLangAST_auto tmp145_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp145_AST = astFactory.create(LT(1));
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp145_AST));
    match(LNOT);
    break;
  }
  default:
    if ((LA(1)==LPAREN) && ((LA(2) >= LITERAL_byte && LA(2) <= LITERAL_rope))) {
      tCAST = LT(1);
      tCAST_AST = astFactory.create(tCAST);
      astFactory.makeASTRoot(currentAST, antlr::RefAST(tCAST_AST));
      match(LPAREN);
#line 630 "zlangpass1.g"
      tCAST_AST->setType(TYPECAST); tCAST_AST->setText("TYPE_CAST");
#line 2917 "ZLangParser.cpp"
      builtInType();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
      zlang::CZLangAST_auto tmp146_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
      tmp146_AST = astFactory.create(LT(1));
      match(RPAREN);
    }
    else if ((_tokenSet_4.member(LA(1))) && (_tokenSet_5.member(LA(2)))) {
    }
  else {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  }
  postfixExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  unaryExpression_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = unaryExpression_AST;
}

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
void ZLangParser::postfixExpression() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto postfixExpression_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::RefToken  tCALLING = antlr::nullToken;
  zlang::CZLangAST_auto tCALLING_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::RefToken  tINDEX = antlr::nullToken;
  zlang::CZLangAST_auto tINDEX_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::RefToken  tINC = antlr::nullToken;
  zlang::CZLangAST_auto tINC_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::RefToken  tDEC = antlr::nullToken;
  zlang::CZLangAST_auto tDEC_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  primaryExpression();
  astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
  {
  switch ( LA(1)) {
  case LPAREN:
  {
    tCALLING = LT(1);
    tCALLING_AST = astFactory.create(tCALLING);
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tCALLING_AST));
    match(LPAREN);
#line 662 "zlangpass1.g"
    tCALLING_AST->setType(CALLING); tCALLING_AST->setText("CALLING");
#line 2984 "ZLangParser.cpp"
    {
    switch ( LA(1)) {
    case IDENTIFIER:
    case LPAREN:
    case PLUS:
    case MINUS:
    case INC:
    case DEC:
    case BNOT:
    case LNOT:
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
      argumentList();
      astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
      break;
    }
    case RPAREN:
    {
      break;
    }
    default:
    {
      throw antlr::NoViableAltException(LT(1), getFilename());
    }
    }
    }
    zlang::CZLangAST_auto tmp147_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp147_AST = astFactory.create(LT(1));
    match(RPAREN);
    break;
  }
  case DOT:
  {
    zlang::CZLangAST_auto tmp148_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp148_AST = astFactory.create(LT(1));
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tmp148_AST));
    match(DOT);
    zlang::CZLangAST_auto tmp149_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp149_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp149_AST));
    match(IDENTIFIER);
    break;
  }
  case LBRACK:
  {
    tINDEX = LT(1);
    tINDEX_AST = astFactory.create(tINDEX);
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tINDEX_AST));
    match(LBRACK);
#line 670 "zlangpass1.g"
    tINDEX_AST->setType(SUBSCRIPT); tINDEX_AST->setText("SUBSCRIPT");
#line 3047 "ZLangParser.cpp"
    expression();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    zlang::CZLangAST_auto tmp150_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp150_AST = astFactory.create(LT(1));
    match(RBRACK);
    break;
  }
  case INC:
  {
    tINC = LT(1);
    tINC_AST = astFactory.create(tINC);
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tINC_AST));
    match(INC);
#line 675 "zlangpass1.g"
    tINC_AST->setType(POST_INC); tINC_AST->setText("POST++");
#line 3063 "ZLangParser.cpp"
    break;
  }
  case DEC:
  {
    tDEC = LT(1);
    tDEC_AST = astFactory.create(tDEC);
    astFactory.makeASTRoot(currentAST, antlr::RefAST(tDEC_AST));
    match(DEC);
#line 677 "zlangpass1.g"
    tDEC_AST->setType(POST_DEC); tDEC_AST->setText("POST--");
#line 3074 "ZLangParser.cpp"
    break;
  }
  case LT_:
  case GT:
  case BAND:
  case RPAREN:
  case SEMI:
  case COMMA:
  case ASSIGN:
  case LOR:
  case LAND:
  case BOR:
  case BXOR:
  case NOT_EQUAL:
  case EQUAL:
  case LE:
  case GE:
  case SL:
  case SR:
  case PLUS:
  case MINUS:
  case STAR:
  case DIV:
  case MOD:
  case RBRACK:
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  }
  postfixExpression_AST = zlang::CZLangAST_auto(currentAST.root);
  returnAST = postfixExpression_AST;
}

/** the basic element of an expression. */
void ZLangParser::primaryExpression() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto primaryExpression_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  switch ( LA(1)) {
  case IDENTIFIER:
  {
    zlang::CZLangAST_auto tmp151_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp151_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp151_AST));
    match(IDENTIFIER);
    primaryExpression_AST = zlang::CZLangAST_auto(currentAST.root);
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
    constant();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    primaryExpression_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LPAREN:
  {
    zlang::CZLangAST_auto tmp152_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp152_AST = astFactory.create(LT(1));
    match(LPAREN);
    assignExpression();
    astFactory.addASTChild(currentAST, antlr::RefAST(returnAST));
    zlang::CZLangAST_auto tmp153_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp153_AST = astFactory.create(LT(1));
    match(RPAREN);
    primaryExpression_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  returnAST = primaryExpression_AST;
}

void ZLangParser::constant() {
  returnAST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  antlr::ASTPair currentAST;
  zlang::CZLangAST_auto constant_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
  
  switch ( LA(1)) {
  case NUM_INT:
  {
    zlang::CZLangAST_auto tmp154_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp154_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp154_AST));
    match(NUM_INT);
    constant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case NUM_HEX_INT:
  {
    zlang::CZLangAST_auto tmp155_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp155_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp155_AST));
    match(NUM_HEX_INT);
    constant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case NUM_QUAD:
  {
    zlang::CZLangAST_auto tmp156_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp156_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp156_AST));
    match(NUM_QUAD);
    constant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case NUM_HEX_QUAD:
  {
    zlang::CZLangAST_auto tmp157_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp157_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp157_AST));
    match(NUM_HEX_QUAD);
    constant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case NUM_FLOAT:
  {
    zlang::CZLangAST_auto tmp158_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp158_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp158_AST));
    match(NUM_FLOAT);
    constant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case CHAR_LITERAL:
  {
    zlang::CZLangAST_auto tmp159_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp159_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp159_AST));
    match(CHAR_LITERAL);
    constant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case STRING_LITERAL:
  {
    zlang::CZLangAST_auto tmp160_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp160_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp160_AST));
    match(STRING_LITERAL);
    constant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case IPv4ADDR_LITERAL:
  {
    zlang::CZLangAST_auto tmp161_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp161_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp161_AST));
    match(IPv4ADDR_LITERAL);
    constant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case PPORT_LITERAL:
  {
    zlang::CZLangAST_auto tmp162_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp162_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp162_AST));
    match(PPORT_LITERAL);
    constant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_true:
  {
    zlang::CZLangAST_auto tmp163_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp163_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp163_AST));
    match(LITERAL_true);
    constant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case LITERAL_false:
  {
    zlang::CZLangAST_auto tmp164_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp164_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp164_AST));
    match(LITERAL_false);
    constant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  case ROPE_LITERAL:
  {
    zlang::CZLangAST_auto tmp165_AST = static_cast<zlang::CZLangAST_auto>(antlr::nullAST);
    tmp165_AST = astFactory.create(LT(1));
    astFactory.addASTChild(currentAST, antlr::RefAST(tmp165_AST));
    match(ROPE_LITERAL);
    constant_AST = zlang::CZLangAST_auto(currentAST.root);
    break;
  }
  default:
  {
    throw antlr::NoViableAltException(LT(1), getFilename());
  }
  }
  returnAST = constant_AST;
}

zlang::CZLangAST_auto ZLangParser::getAST()
{
	return returnAST;
}

const char* ZLangParser::_tokenNames[] = {
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

const unsigned long ZLangParser::_tokenSet_0_data_[] = { 0UL, 19UL, 0UL, 0UL };
// SEMI COMMA ASSIGN 
const antlr::BitSet ZLangParser::_tokenSet_0(_tokenSet_0_data_,4);
const unsigned long ZLangParser::_tokenSet_1_data_[] = { 33554432UL, 33538048UL, 0UL, 0UL };
// "table" "byte" "bool" "sdword" "udword" "sqword" "uqword" "double" "string" 
// "ipaddress" "pport" "rope" 
const antlr::BitSet ZLangParser::_tokenSet_1(_tokenSet_1_data_,4);
const unsigned long ZLangParser::_tokenSet_2_data_[] = { 1610612736UL, 14209UL, 134188824UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// IDENTIFIER LPAREN SEMI "break" "continue" "return" "if" "while" "for" 
// PLUS MINUS INC DEC BNOT LNOT NUM_INT NUM_HEX_INT NUM_QUAD NUM_HEX_QUAD 
// NUM_FLOAT CHAR_LITERAL STRING_LITERAL IPv4ADDR_LITERAL PPORT_LITERAL 
// "true" "false" ROPE_LITERAL 
const antlr::BitSet ZLangParser::_tokenSet_2(_tokenSet_2_data_,8);
const unsigned long ZLangParser::_tokenSet_3_data_[] = { 201326592UL, 2147483648UL, 1UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// LT_ GT LE GE 
const antlr::BitSet ZLangParser::_tokenSet_3(_tokenSet_3_data_,8);
const unsigned long ZLangParser::_tokenSet_4_data_[] = { 1610612736UL, 0UL, 134184960UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// IDENTIFIER LPAREN NUM_INT NUM_HEX_INT NUM_QUAD NUM_HEX_QUAD NUM_FLOAT 
// CHAR_LITERAL STRING_LITERAL IPv4ADDR_LITERAL PPORT_LITERAL "true" "false" 
// ROPE_LITERAL 
const antlr::BitSet ZLangParser::_tokenSet_4(_tokenSet_4_data_,8);
const unsigned long ZLangParser::_tokenSet_5_data_[] = { 4227858432UL, 4261412883UL, 134217727UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// LT_ GT BAND IDENTIFIER LPAREN RPAREN SEMI COMMA ASSIGN LOR LAND BOR 
// BXOR NOT_EQUAL EQUAL LE GE SL SR PLUS MINUS STAR DIV MOD INC DEC BNOT 
// LNOT DOT LBRACK RBRACK NUM_INT NUM_HEX_INT NUM_QUAD NUM_HEX_QUAD NUM_FLOAT 
// CHAR_LITERAL STRING_LITERAL IPv4ADDR_LITERAL PPORT_LITERAL "true" "false" 
// ROPE_LITERAL 
const antlr::BitSet ZLangParser::_tokenSet_5(_tokenSet_5_data_,8);


ANTLR_END_NAMESPACE
