/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/CZLangAST.cpp,v $
 *
 * $Date: 2001/11/14 19:03:08 $
 *
 * $Revision: 1.3 $
 *
 * $Name:  $
 *
 * $Author: zls $
 *
 * Copyright(C) since 1998 by Albert Zheng - 郑立松, All Rights Reserved.
 *
 * lisong.zheng@gmail.com
 *
 * $State: Exp $
 */


#include <zls/zlang/CZLangAST.hpp>


ZLS_BEGIN_NAMESPACE(zlang)


void CZLangAST::initialize(int nType, const std::string& rstring)
{
  antlr::CommonAST::initialize(nType, rstring);

  /*
   * 如果在Parser中采用#[type,"text"]（假想的Token）来构造Node，
   * 则没有Line、Column信息.
   */
  _autoSavedTokenForLineColumn->setText(rstring);
  _autoSavedTokenForLineColumn->setType(nType);
}


void CZLangAST::initialize(antlr::RefAST autoAST)
{
  antlr::CommonAST::initialize(autoAST);

  /* 如果在Parser中采用## = #label来构造Node，则没有Line、Column信息. */
  _autoSavedTokenForLineColumn->setText(autoAST->getText());
  _autoSavedTokenForLineColumn->setType(autoAST->getType());
}


void CZLangAST::initialize(antlr::RefToken autoToken)
{
  antlr::CommonAST::initialize(autoToken);

  _autoSavedTokenForLineColumn = autoToken;
}


antlr::RefAST CZLangAST::factory()
{
  return antlr::RefAST(new CZLangAST);
}


ZLS_END_NAMESPACE

