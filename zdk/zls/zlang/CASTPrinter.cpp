/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/CASTPrinter.cpp,v $
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


#include <cassert>
#include <cstdio>
#include <zls/zlang/CASTPrinter.hpp>


// Begin namespace 'zlang::'
ZLS_BEGIN_NAMESPACE(zlang)


#define For_each_kid(t,top)     \
  for(t=((top && is_nonleaf(top)) ? top->getFirstChild() : (antlr::RefAST)NULL ); \
      t; \
      t = t->getNextSibling())


/*
 * pr_name
 *

   Print the character string associated with an ANTLR tree node.

 */
void CASTPrinter::pr_name( antlr::RefAST node )
{
    std::string str;

    str = node->getText();
    printf("%s ", str.c_str());
} // pr_name


/*
 * pr_indent
 *

   Print indentation for a node.

 */
void CASTPrinter::pr_indent(void)
{
  const size_t BUFSIZE = 127;
  char buf[ BUFSIZE+1 ];
  int i;

  for (i = 0; i < indent_level && i < BUFSIZE; i++) {
    buf[i] = ' ';
  }
  buf[i] = '\0';
  printf("%s", buf );
} // pr_indent



void CASTPrinter::pr_open_angle(void)
{
  if ( indent_level )
    printf("\n");

  pr_indent();

  printf("<");
  indent_level += INDENT;
}  // pr_open_angle



/*
 * pr_close_angle
 *

   Print the ">" bracket to show the close of a tree production.

 */
void CASTPrinter::pr_close_angle(bool first)
{
  assert( indent_level > 0 );

  indent_level -= INDENT;

  if (!first) {
    printf("\n");
    pr_indent();
  }
  printf("> ");
} // pr_close_angle


/*
 * pr_leaves
 *

   Print the leaves of an AST node

 */
void CASTPrinter::pr_leaves( antlr::RefAST top )
{
  antlr::RefAST t;

  For_each_kid(t, top) {
    if (is_nonleaf( t ))
      pr_top( t );
    else
      pr_name( t );
  }
} // pr_leaves



/*
 * pr_top
 *

   Recursively print a tree (or a sub-tree) from the top down.

 */
void CASTPrinter::pr_top( antlr::RefAST top )
{
  antlr::RefAST tmp;
  bool first = true;

  pr_open_angle();

  pr_name( top );

  if (is_nonleaf( top )) {
    For_each_kid( tmp, top ) {
      if (is_nonleaf( tmp ))
	first = false;
    }
    pr_leaves( top );
  }

  pr_close_angle( first );
} // pr_top



/*
 * pr_tree
 *

   Main entry point for tree print.

 */
void CASTPrinter::pr_tree( antlr::RefAST top )
{
  antlr::RefAST t;

  for (t = top; t != 0; t = t->getNextSibling()) {
    indent_level = 0;
    pr_top( t );
    printf("\n");
  }
} // pr_tree


ZLS_END_NAMESPACE

