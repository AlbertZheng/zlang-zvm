/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/ZVMException.hpp,v $
 *
 * $Date: 2001/11/14 18:29:37 $
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


#ifndef _ZLS_zvm_ZVMException_hpp_
#define _ZLS_zvm_ZVMException_hpp_

#include <zls/zfc/Exception.hpp>
#include <zls/zvm/Manifest.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


class ELinkFailure : public std::runtime_error, public zfc::EBaseException {
  public:
    ELinkFailure & operator=(const ELinkFailure & rci)
    {
      std::runtime_error::operator=(rci);
      zfc::EBaseException::operator=(rci);
      return *this;
    }

    /** Mapping constructor. */
    ELinkFailure(const zfc::EBaseException & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    ELinkFailure(const ELinkFailure & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    ELinkFailure(const char * pszFileName,
                 const char * pszFuncName,
                 const int nLineNumber,
                 const std::string & rstringError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, rstringError)
    { }

    ELinkFailure(const char * pszFileName,
                 const char * pszFuncName,
                 const int nLineNumber,
                 const char * pszError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, pszError)
    { }

    virtual const char * GetExceptionName() const throw()
    {
      return "zvm::ELinkFailure";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return zfc::EBaseException::what();
    }
};


class ELink1Failure : public ELinkFailure {
  public:
    ELink1Failure & operator=(const ELink1Failure & rci)
    {
      ELinkFailure::operator=(rci);
      return *this;
    }

    /** Mapping constructor. */
    ELink1Failure(const zfc::EBaseException & rci)
      : ELinkFailure(rci)
    { }

    ELink1Failure(const ELink1Failure & rci)
      : ELinkFailure(rci)
    { }

    ELink1Failure(const char * pszFileName,
                  const char * pszFuncName,
                  const int nLineNumber,
                  const std::string & rstringError)
      : ELinkFailure(pszFileName, pszFuncName, nLineNumber, rstringError)
    { }

    ELink1Failure(const char * pszFileName,
                  const char * pszFuncName,
                  const int nLineNumber,
                  const char * pszError)
      : ELinkFailure(pszFileName, pszFuncName, nLineNumber, pszError)
    { }

    virtual const char * GetExceptionName() const throw()
    {
      return "zvm::ELink1Failure";
    }
};


class ELink2Failure : public ELinkFailure {

  public:
    ELink2Failure & operator=(const ELink2Failure & rci)
    {
      ELinkFailure::operator=(rci);
      return *this;
    }

    /** Mapping constructor. */
    ELink2Failure(const zfc::EBaseException & rci)
      : ELinkFailure(rci)
    { }

    ELink2Failure(const ELink2Failure & rci)
      : ELinkFailure(rci)
    { }

    ELink2Failure(const char * pszFileName,
                  const char * pszFuncName,
                  const int nLineNumber,
                  const std::string & rstringError)
      : ELinkFailure(pszFileName, pszFuncName, nLineNumber, rstringError)
    { }

    ELink2Failure(const char * pszFileName,
                  const char * pszFuncName,
                  const int nLineNumber,
                  const char * pszError)
      : ELinkFailure(pszFileName, pszFuncName, nLineNumber, pszError)
    { }

    virtual const char * GetExceptionName() const throw()
    {
      return "zvm::ELink2Failure";
    }
};


class EVerifyFailure : public std::runtime_error, public zfc::EBaseException {

  public:
    EVerifyFailure & operator=(const EVerifyFailure & rci)
    {
      std::runtime_error::operator=(rci);
      zfc::EBaseException::operator=(rci);
      return *this;
    }

    /** Mapping constructor. */
    EVerifyFailure(const zfc::EBaseException & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    EVerifyFailure(const EVerifyFailure & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    EVerifyFailure(const char * pszFileName,
                   const char * pszFuncName,
                   const int nLineNumber,
                   const std::string & rstringError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, rstringError)
    { }

    EVerifyFailure(const char * pszFileName,
                   const char * pszFuncName,
                   const int nLineNumber,
                   const char * pszError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, pszError)
    { }

    virtual const char * GetExceptionName() const throw()
    {
      return "zvm::EVerifyFailure";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return zfc::EBaseException::what();
    }
};


class EInvalidObjectFile : public std::runtime_error, public zfc::EBaseException {

  public:
    EInvalidObjectFile & operator=(const EInvalidObjectFile & rci)
    {
      std::runtime_error::operator=(rci);
      zfc::EBaseException::operator=(rci);
      return *this;
    }

    EInvalidObjectFile(const EInvalidObjectFile & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    EInvalidObjectFile(const char * pszFileName,
                       const char * pszFuncName,
                       const int nLineNumber,
                       const std::string & rstringError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, rstringError)
    { }

    EInvalidObjectFile(const char * pszFileName,
                       const char * pszFuncName,
                       const int nLineNumber,
                       const char * pszError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, pszError)
    { }

    virtual const char * GetExceptionName() const throw()
    {
      return "zvm::EInvalidObjectFile";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return zfc::EBaseException::what();
    }
};


class ELoadObjectFileFailure : public std::runtime_error, public zfc::EBaseException {
  public:
    ELoadObjectFileFailure & operator=(const ELoadObjectFileFailure & rci)
    {
      std::runtime_error::operator=(rci);
      zfc::EBaseException::operator=(rci);
      return *this;
    }

    /** Mapping constructor. */
    ELoadObjectFileFailure(const zfc::EBaseException & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    ELoadObjectFileFailure(const ELoadObjectFileFailure & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    ELoadObjectFileFailure(const char * pszFileName,
                           const char * pszFuncName,
                           const int nLineNumber,
                           const std::string & rstringError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, rstringError)
    { }

    ELoadObjectFileFailure(const char * pszFileName,
                           const char * pszFuncName,
                           const int nLineNumber,
                           const char * pszError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, pszError)
    { }

    virtual const char * GetExceptionName() const throw()
    {
      return "zvm::ELoadObjectFileFailure";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return zfc::EBaseException::what();
    }
};


class EUnloadObjectFileFailure : public std::runtime_error, public zfc::EBaseException {
  public:
    EUnloadObjectFileFailure & operator=(const EUnloadObjectFileFailure & rci)
    {
      std::runtime_error::operator=(rci);
      zfc::EBaseException::operator=(rci);
      return *this;
    }

    /** Mapping constructor. */
    EUnloadObjectFileFailure(const zfc::EBaseException & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    EUnloadObjectFileFailure(const EUnloadObjectFileFailure & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    EUnloadObjectFileFailure(const char * pszFileName,
                             const char * pszFuncName,
                             const int nLineNumber,
                             const std::string & rstringError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, rstringError)
    { }

    EUnloadObjectFileFailure(const char * pszFileName,
                             const char * pszFuncName,
                             const int nLineNumber,
                             const char * pszError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, pszError)
    { }

    virtual const char * GetExceptionName() const throw()
    {
      return "zvm::EUnloadObjectFileFailure";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return zfc::EBaseException::what();
    }
};


class EImportNativeLibraryFailure : public std::runtime_error, public zfc::EBaseException {
  public:
    EImportNativeLibraryFailure & operator=(const EImportNativeLibraryFailure & rci)
    {
      std::runtime_error::operator=(rci);
      zfc::EBaseException::operator=(rci);
      return *this;
    }

    /** Mapping constructor. */
    EImportNativeLibraryFailure(const zfc::EBaseException & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    EImportNativeLibraryFailure(const EImportNativeLibraryFailure & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    EImportNativeLibraryFailure(const char * pszFileName,
                                const char * pszFuncName,
                                const int nLineNumber,
                                const std::string & rstringError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, rstringError)
    { }

    EImportNativeLibraryFailure(const char * pszFileName,
                                const char * pszFuncName,
                                const int nLineNumber,
                                const char * pszError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, pszError)
    { }

    virtual const char * GetExceptionName() const throw()
    {
      return "zvm::EImportNativeLibraryFailure";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return zfc::EBaseException::what();
    }
};


class EFunctionInvokeInterfaceException : public std::runtime_error, public zfc::EBaseException {
  public:
    EFunctionInvokeInterfaceException & operator=(const EFunctionInvokeInterfaceException & rci)
    {
      std::runtime_error::operator=(rci);
      zfc::EBaseException::operator=(rci);
      return *this;
    }

    /** Mapping constructor. */
    EFunctionInvokeInterfaceException(const zfc::EBaseException & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    EFunctionInvokeInterfaceException(const EFunctionInvokeInterfaceException & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    EFunctionInvokeInterfaceException(const char * pszFileName,
                                      const char * pszFuncName,
                                      const int nLineNumber,
                                      const std::string & rstringError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, rstringError)
    { }

    EFunctionInvokeInterfaceException(const char * pszFileName,
                                      const char * pszFuncName,
                                      const int nLineNumber,
                                      const char * pszError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, pszError)
    { }

    virtual const char * GetExceptionName() const throw()
    {
      return "zvm::EFunctionInvokeInterfaceException";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return zfc::EBaseException::what();
    }
};


class EZVMRuntimeException : public std::runtime_error, public zfc::EBaseException {
  public:
    EZVMRuntimeException & operator=(const EZVMRuntimeException & rci)
    {
      std::runtime_error::operator=(rci);
      zfc::EBaseException::operator=(rci);
      return *this;
    }

    /** Mapping constructor. */
    EZVMRuntimeException(const zfc::EBaseException & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    EZVMRuntimeException(const EZVMRuntimeException & rci)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(rci)
    { }

    EZVMRuntimeException(const char * pszFileName,
                         const char * pszFuncName,
                         const int nLineNumber,
                         const std::string & rstringError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, rstringError)
    { }

    EZVMRuntimeException(const char * pszFileName,
                         const char * pszFuncName,
                         const int nLineNumber,
                         const char * pszError)
      : std::runtime_error(zfc::CstringLITERAL_OF_RUNTIME_ERROR),
        zfc::EBaseException(pszFileName, pszFuncName, nLineNumber, pszError)
    { }

    virtual const char * GetExceptionName() const throw()
    {
      return "zvm::EZVMRuntimeException";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return zfc::EBaseException::what();
    }
};


class CZVMErrorReporter {
  public:
    /**
     * @name 报告Bug.
     */
    //@{
    /**
     * 当妄想将某个二元操作符应用到（这个操作符）不允许的数据类型的操作数上时，报告这个Bug.
     * 例如："*"、"/"等.
     *
     * @throw zfc::EPanic.
     */
    /*
    static void ThrowBug_InvalidUseBinaryOperator(
      const char * pszFileName,
      const char * pszFuncName,
      const int nLineNumber,
      char chOperator,
      const std::string & rstringLeftTypeSignature,
      const std::string & rstringRightTypeSignature
    );
    */

    /**
     * 当妄想将某个二元操作符应用到（这个操作符）不允许的数据类型的操作数上时，报告这个Bug.
     * 例如："<="、">="、"<<"、">>"等.
     *
     * @throw zfc::EPanic.
     */
    /*
    static void ThrowBug_InvalidUseBinaryOperator(
      const char * pszFileName,
      const char * pszFuncName,
      const int nLineNumber,
      const std::string & rstringOperator,
      const std::string & rstringLeftTypeSignature,
      const std::string & rstringRightTypeSignature
    );
    */

    /**
     * 当妄想将某个二元操作符应用到（这个操作符）不允许的数据类型的操作数上时，报告这个Bug.
     *
     * @throw zfc::EPanic.
     */
    /*
    static void ThrowBug_InvalidUseBinaryOperator(
      const char * pszFileName,
      const char * pszFuncName,
      const int nLineNumber,
      char chOperator,
      const std::string & rstringLeftTypeSignature
    );
    */

    /**
     * 当妄想将某个二元操作符应用到（这个操作符）不允许的数据类型的操作数上时，报告这个Bug.
     * 例如："<="、">="、"<<"、">>"等.
     *
     * @throw zfc::EPanic.
     */
    /*
    static void ThrowBug_InvalidUseBinaryOperator(
      const char * pszFileName,
      const char * pszFuncName,
      const int nLineNumber,
      const std::string & rstringOperator,
      const std::string & rstringLeftTypeSignature
    );
    */

    /**
     * 当妄想将某个一元操作符应用到（这个操作符）不允许的数据类型的操作数上时，报告这个Bug.
     * 例如:"~"等.
     *
     * @throw zfc::EPanic.
     */
    /*
    static void ThrowBug_InvalidUseUnaryOperator(
      const char * pszFileName,
      const char * pszFuncName,
      const int nLineNumber,
      char chOperator,
      const std::string & rstringLeftTypeSignature
    );
    */

    /**
     * 当妄想将某个一元操作符应用到（这个操作符）不允许的数据类型的操作数上时，报告这个Bug.
     * 例如："++"、"--"等.
     *
     * @throw zfc::EPanic.
     */
    /*
    static void ThrowBug_InvalidUseUnaryOperator(
      const char * pszFileName,
      const char * pszFuncName,
      const int nLineNumber,
      const std::string & rstringOperator,
      const std::string & rstringLeftTypeSignature
    );
    */

    /**
     * 当妄想进行不允许的Cast操作时，报告这个Bug.
     * 例如："ZVM string" cast to "ZVM udword"等.
     *
     * @throw zfc::EPanic.
     */
    /*
    static void ThrowBug_InvalidUseCast(
      const char * pszFileName,
      const char * pszFuncName,
      const int nLineNumber,
      const std::string & rstringLeftTypeSignature,
      char chTargetSignature
    );
    */

    /**
     * 调用CZVMObject::GetAssumeAsCZVMSimpleType_wrapper()等时却不是所期望的.
     *
     * @throw zfc::EPanic.
     */
    /*
    static void ThrowBug_BadAssumeTypeSignatureOfCZVMObject(
      const char * pszFileName,
      const char * pszFuncName,
      const int nLineNumber,
      const std::string & rstringRealTypeSignature
    );
    */

    /**
     * 报告ZVM在进行中发现了被重复定义的variable或function.
     *
     * @throw zvm::ELink1Failure.
     */
    static void ThrowError_MultipleDefinitionSymbol(
      const char * pszFileName,
      const char * pszFuncName,
      const int nLineNumber,
      const char * pszSymbolTypeName,
      const std::string & rstringSymbolName,
      const std::string & rstringFirstSourceFileName,
      const std::string & rstringFirstObjectFileName,
      const std::string & rstringSecondSourceFileName,
      const std::string & rstringSecondObjectFileName
    );

    /**
     * 报告ZVM在解释Byte codes时出现错误，致使不能继续.
     *
     * @throw zvm::EZVMRuntimeException.
     */
    static void ThrowRuntimeError(
      const char * pszFileName,
      const char * pszFuncName,
      const int nLineNumber,
      const std::string & rstringError
    );
    //@}
};


ZLS_END_NAMESPACE


#endif

