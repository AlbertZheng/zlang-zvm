/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/CZLangAST.hpp,v $
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


#ifndef _ZLS_CZLangAST_hpp_
#define _ZLS_CZLangAST_hpp_

#include <zls/zfc/Manifest.h>
#include <antlr/config.hpp>
#include <antlr/CommonAST.hpp>
#include <antlr/CommonToken.hpp>


// Begin namespace 'zlang::'
ZLS_BEGIN_NAMESPACE(zlang)


/**
 * 一个对antlr::CommonAST进行增强的AST类.
 * 它的最主要特点其还将在initialize(antlr::RefToken autoToken)传递给它的
 * antlr::RefToken保存在内部，以便在进行语义分析时能够报告行号、列号信息。
 * 而antlr::CommonAST则将antlr::RefToken抛弃了，仅保存其Token-Type和
 * Token-Text信息而已.
 */
class CZLangAST : public antlr::CommonAST {
  protected:
    /**
     * Refer to the input token which I can report line and column number.
     */
    antlr::RefToken _autoSavedTokenForLineColumn;

  public:
    CZLangAST()
      : antlr::CommonAST(),
        _autoSavedTokenForLineColumn(new antlr::CommonToken)
    { }

    virtual ~CZLangAST()
    { }

  public:
    virtual antlr::RefToken & getSavedToken()
    {
      return _autoSavedTokenForLineColumn;
    }

    // Borland C++ builder seems to need the decl's of the first two...
    virtual void initialize(int nType,const std::string& rstringText);
    virtual void initialize(antlr::RefAST autoAST);
    virtual void initialize(antlr::RefToken autoToken);

    static antlr::RefAST factory();
};

typedef antlr::ASTRefCount<CZLangAST>  CZLangAST_auto;


ZLS_END_NAMESPACE


#endif

