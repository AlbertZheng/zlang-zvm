/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/CASTPrinter.hpp,v $
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


#ifndef _ZLS_zlang_CASTPrinter_hpp_
#define _ZLS_zlang_CASTPrinter_hpp_

#include <zls/zfc/Manifest.h>
#include <antlr/CommonAST.hpp>
#include <antlr/ASTRefCount.hpp>


// Begin namespace 'zlang::'
ZLS_BEGIN_NAMESPACE(zlang)


/**
 *  Print an ANTLR abstract syntax tree in operator prefix form.
 */
class CASTPrinter {
  private:
    typedef enum { INDENT = 2 } bogus;
    int indent_level;

  private:
    void pr_name( antlr::RefAST node );
    void pr_indent();
    void pr_top( antlr::RefAST top );
    void pr_open_angle(void);
    void pr_close_angle(bool first);
    void pr_leaves( antlr::RefAST top );

    bool is_nonleaf( antlr::RefAST node )
    {
      bool rslt;
      rslt = (bool)(node->getFirstChild() != 0);
      return rslt;
    }
  public:
    void pr_tree( const antlr::RefAST top );
};


ZLS_END_NAMESPACE


#endif

