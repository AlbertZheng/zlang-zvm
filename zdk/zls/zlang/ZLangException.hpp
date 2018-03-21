/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/ZLangException.hpp,v $
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


#ifndef _ZLS_zlang_ZLangException_hpp_
#define _ZLS_zlang_ZLangException_hpp_


#include <zls/zfc/Exception.hpp>


ZLS_BEGIN_NAMESPACE(zlang)


class ESymbolNotFound : public std::runtime_error, public zfc::EBaseException {
  public:
    ESymbolNotFound & operator=(const ESymbolNotFound & rci)
    {
      std::runtime_error::operator=(rci);
      zfc::EBaseException::operator=(rci);
      return *this;
    }

    ESymbolNotFound(const ESymbolNotFound & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    ESymbolNotFound(const char * pszFileName,
                    const char * pszFuncName,
                    const int nLineNumber,
                    const std::string & rstringSymbol);

    virtual const char * GetExceptionName() const throw()
    {
      return "zlang::ESymbolNotFound";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return zfc::EBaseException::what();
    }
};


class ESymbolInsertFailure : public std::runtime_error, public zfc::EBaseException {
  public:
    ESymbolInsertFailure & operator=(const ESymbolInsertFailure & rci)

    {
      std::runtime_error::operator=(rci);
      zfc::EBaseException::operator=(rci);
      return *this;
    }

    ESymbolInsertFailure(const ESymbolInsertFailure & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    ESymbolInsertFailure(const char * pszFileName,

                         const char * pszFuncName,

                         const int nLineNumber,

                         const std::string & rstringSymbol);

    virtual const char * GetExceptionName() const throw()
    {
      return "zlang::ESymbolInsertFailure";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return zfc::EBaseException::what();
    }
};


class EZLangCompilerException : public std::runtime_error, public zfc::EBaseException {
  public:
    EZLangCompilerException & operator=(const EZLangCompilerException & rci)
    {
      std::runtime_error::operator=(rci);
      zfc::EBaseException::operator=(rci);
      return *this;
    }

    /** Mapping constructor. */
    EZLangCompilerException(const zfc::EBaseException & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    EZLangCompilerException(const EZLangCompilerException & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    EZLangCompilerException(const char * pszFileName,
                            const char * pszFuncName,
                            const int nLineNumber,
                            const std::string & rstringError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, rstringError)
    { }

    EZLangCompilerException(const char * pszFileName,
                            const char * pszFuncName,
                            const int nLineNumber,
                            const char * pszError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, pszError)
    { }

    virtual const char * GetExceptionName() const throw()
    {
      return "zlang::EZLangCompilerException";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return zfc::EBaseException::what();
    }
};


ZLS_END_NAMESPACE


#endif

