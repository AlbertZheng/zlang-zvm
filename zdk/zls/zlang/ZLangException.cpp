/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/ZLangException.cpp,v $
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


#include <zls/zlang/ZLangException.hpp>


ZLS_BEGIN_NAMESPACE(zlang)


ESymbolNotFound::ESymbolNotFound(const char * pszFileName,
                                 const char * pszFuncName,
                                 const int nLineNumber,
                                 const std::string & rstringSymbol)
  : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
    zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, 0)
{
  try {
    std::string stringError = "Undeclared symbol '" + rstringSymbol + "'";
    AppendWhat(pszFileName, pszFuncName, nLineNumber, stringError);
  }
  catch (...)
  {
  }
}


ESymbolInsertFailure::ESymbolInsertFailure(const char * pszFileName,
                                           const char * pszFuncName,
                                           const int nLineNumber,
                                           const std::string & rstringSymbol)
  : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
    zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, 0)
{
  try {
    std::string stringError = "Multiple definition of symbol '" + rstringSymbol + "'";
    AppendWhat(pszFileName, pszFuncName, nLineNumber, stringError);
  }
  catch (...)
  {
  }
}


ZLS_END_NAMESPACE

