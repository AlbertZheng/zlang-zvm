/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/Exception.cpp,v $
 *
 * $Date: 2001/11/14 17:25:11 $
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


#include <zls/zfc/Exception.hpp>


ZLS_BEGIN_NAMESPACE(zfc)


EBaseException & EBaseException::operator=(const EBaseException & rci)
{
  try {
    _vectorWhats = rci._vectorWhats;
  }
  catch (...)
  {
  }
  return *this;
}


void EBaseException::AppendWhat(const char * pszFileName,
                                const char * pszFuncName,
                                const int nLineNumber,
                                const std::string & rstringMessage)
{
  try {
    TWhat siWhat(pszFileName, pszFuncName, nLineNumber, rstringMessage);
    _vectorWhats.push_back(siWhat);
  }
  catch (...)
  {
  }
}


void EBaseException::AppendWhat(const char * pszFileName,
                                const char * pszFuncName,
                                const int nLineNumber,
                                const char * pszMessage)
{
  if (pszMessage)
  {
    try {
      TWhat siWhat(pszFileName, pszFuncName, nLineNumber, pszMessage);
      _vectorWhats.push_back(siWhat);
    }
    catch (...)
    {
    }
  }
}


const char * EBaseException::what() const
  #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
  throw ()
  #endif
{
  try {
    return _vectorWhats[0].what();
  }
  catch (...)
  {
    return "miserable";
  }
}


ESystemCallFailure::ESystemCallFailure(const char * pszFileName,
                                       const char * pszFuncName,
                                       const int nLineNumber,
                                       const char * pszSystemCallName,
                                       const int nErrorNumber)
  : std::runtime_error(CstringLITERAL_OF_RUNTIME_ERROR),
    EBaseException(pszFileName, pszFuncName, nLineNumber, 0),
    _nErrorNumber(nErrorNumber)
{
  if (pszSystemCallName)
  {
    try {
      std::string stringError = std::string("'") + pszSystemCallName +
                                "()' failed due to '" + ERRNO_TEXT(nErrorNumber) + "'";
      AppendWhat(pszFileName, pszFuncName, nLineNumber, stringError);
    }
    catch (...)
    {
    }
  }
}


EPanic::EPanic(const char * pszFileName,
               const char * pszFuncName,
               const int nLineNumber,
               const std::string & rstringMessage)
  : std::exception(),
    EBaseException(pszFileName, pszFuncName, nLineNumber, rstringMessage)
{
  TLoggerTSS * __ptLoggerTSS__;
  #ifdef ENABLE_THREADS
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
  #else
  __ptLoggerTSS__ = &_GtLoggerTSS;
  #endif
  __ptLoggerTSS__->pszFileName = pszFileName;
  __ptLoggerTSS__->pszFuncName = pszFuncName;
  __ptLoggerTSS__->nLine = nLineNumber;
  __ptLoggerTSS__->nSyslogPriority = LOG_ERR;
  _LogMiddle("Bug: %s !\n", rstringMessage.c_str());
}


EPanic::EPanic(const char * pszFileName,
               const char * pszFuncName,
               const int nLineNumber,
               const char * pszMessage)
  : std::exception(),
    EBaseException(pszFileName, pszFuncName, nLineNumber, pszMessage)
{
  TLoggerTSS * __ptLoggerTSS__;
  #ifdef ENABLE_THREADS
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
  #else
  __ptLoggerTSS__ = &_GtLoggerTSS;
  #endif
  __ptLoggerTSS__->pszFileName = pszFileName;
  __ptLoggerTSS__->pszFuncName = pszFuncName;
  __ptLoggerTSS__->nLine = nLineNumber;
  __ptLoggerTSS__->nSyslogPriority = LOG_ERR;
  _LogMiddle("Bug: %s !\n", pszMessage);
}


EBadDynamicCast::EBadDynamicCast(const char * pszFileName,
                                 const char * pszFuncName,
                                 const int nLineNumber,
                                 const std::string & rstringMessage)
  : std::bad_cast(),
    EBaseException(pszFileName, pszFuncName, nLineNumber, rstringMessage)
{
  TLoggerTSS * __ptLoggerTSS__;
  #ifdef ENABLE_THREADS
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
  #else
  __ptLoggerTSS__ = &_GtLoggerTSS;
  #endif
  __ptLoggerTSS__->pszFileName = pszFileName;
  __ptLoggerTSS__->pszFuncName = pszFuncName;
  __ptLoggerTSS__->nLine = nLineNumber;
  __ptLoggerTSS__->nSyslogPriority = LOG_ERR;
  _LogMiddle("Bug: %s !\n", rstringMessage.c_str());
}


EBadDynamicCast::EBadDynamicCast(const char * pszFileName,
                                 const char * pszFuncName,
                                 const int nLineNumber,
                                 const char * pszMessage)
  : std::bad_cast(),
    EBaseException(pszFileName, pszFuncName, nLineNumber, pszMessage)
{
  TLoggerTSS * __ptLoggerTSS__;
  #ifdef ENABLE_THREADS
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
  #else
  __ptLoggerTSS__ = &_GtLoggerTSS;
  #endif
  __ptLoggerTSS__->pszFileName = pszFileName;
  __ptLoggerTSS__->pszFuncName = pszFuncName;
  __ptLoggerTSS__->nLine = nLineNumber;
  __ptLoggerTSS__->nSyslogPriority = LOG_ERR;
  _LogMiddle("Bug: %s !\n", pszMessage);
}


EUnimplementedVirtualMethod::EUnimplementedVirtualMethod(
  const char * pszFileName,
  const char * pszFuncName,
  const int nLineNumber,
  const std::string & rstringMessage)
  : std::logic_error(CstringLITERAL_OF_LOGIC_ERROR),
    EBaseException(pszFileName, pszFuncName, nLineNumber, rstringMessage)
{
  TLoggerTSS * __ptLoggerTSS__;
  #ifdef ENABLE_THREADS
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
  #else
  __ptLoggerTSS__ = &_GtLoggerTSS;
  #endif
  __ptLoggerTSS__->pszFileName = pszFileName;
  __ptLoggerTSS__->pszFuncName = pszFuncName;
  __ptLoggerTSS__->nLine = nLineNumber;
  __ptLoggerTSS__->nSyslogPriority = LOG_ERR;
  _LogMiddle("Bug: %s !\n", rstringMessage.c_str());
}


EUnimplementedVirtualMethod::EUnimplementedVirtualMethod(
  const char * pszFileName,
  const char * pszFuncName,
  const int nLineNumber,
  const char * pszMessage)
  : std::logic_error(CstringLITERAL_OF_LOGIC_ERROR),
    EBaseException(pszFileName, pszFuncName, nLineNumber, pszMessage)
{
  TLoggerTSS * __ptLoggerTSS__;
  #ifdef ENABLE_THREADS
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
  #else
  __ptLoggerTSS__ = &_GtLoggerTSS;
  #endif
  __ptLoggerTSS__->pszFileName = pszFileName;
  __ptLoggerTSS__->pszFuncName = pszFuncName;
  __ptLoggerTSS__->nLine = nLineNumber;
  __ptLoggerTSS__->nSyslogPriority = LOG_ERR;
  _LogMiddle("Bug: %s !\n", pszMessage);
}


EInvalidArgument::EInvalidArgument(const char * pszFileName,
                                   const char * pszFuncName,
                                   const int nLineNumber,
                                   const std::string & rstringMessage)
  : std::invalid_argument(CstringLITERAL_OF_INVALID_ARGUMENT),
    EBaseException(pszFileName, pszFuncName, nLineNumber, rstringMessage)
{
  TLoggerTSS * __ptLoggerTSS__;
  #ifdef ENABLE_THREADS
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
  #else
  __ptLoggerTSS__ = &_GtLoggerTSS;
  #endif
  __ptLoggerTSS__->pszFileName = pszFileName;
  __ptLoggerTSS__->pszFuncName = pszFuncName;
  __ptLoggerTSS__->nLine = nLineNumber;
  __ptLoggerTSS__->nSyslogPriority = LOG_ERR;
  _LogMiddle("Bug: %s !\n", rstringMessage.c_str());
}


EInvalidArgument::EInvalidArgument(const char * pszFileName,
                                   const char * pszFuncName,
                                   const int nLineNumber,
                                   const char * pszMessage)
  : std::invalid_argument(CstringLITERAL_OF_INVALID_ARGUMENT),
    EBaseException(pszFileName, pszFuncName, nLineNumber, pszMessage)
{
  TLoggerTSS * __ptLoggerTSS__;
  #ifdef ENABLE_THREADS
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
  #else
  __ptLoggerTSS__ = &_GtLoggerTSS;
  #endif
  __ptLoggerTSS__->pszFileName = pszFileName;
  __ptLoggerTSS__->pszFuncName = pszFuncName;
  __ptLoggerTSS__->nLine = nLineNumber;
  __ptLoggerTSS__->nSyslogPriority = LOG_ERR;
  _LogMiddle("Bug: %s !\n", pszMessage);
}


EInvalidState::EInvalidState(const char * pszFileName,
                             const char * pszFuncName,
                             const int nLineNumber,
                             const std::string & rstringMessage)
  : std::logic_error(CstringLITERAL_OF_LOGIC_ERROR),
    EBaseException(pszFileName, pszFuncName, nLineNumber, rstringMessage)
{
  TLoggerTSS * __ptLoggerTSS__;
  #ifdef ENABLE_THREADS
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
  #else
  __ptLoggerTSS__ = &_GtLoggerTSS;
  #endif
  __ptLoggerTSS__->pszFileName = pszFileName;
  __ptLoggerTSS__->pszFuncName = pszFuncName;
  __ptLoggerTSS__->nLine = nLineNumber;
  __ptLoggerTSS__->nSyslogPriority = LOG_ERR;
  _LogMiddle("Bug: %s !\n", rstringMessage.c_str());
}


EInvalidState::EInvalidState(const char * pszFileName,
                             const char * pszFuncName,
                             const int nLineNumber,
                             const char * pszMessage)
  : std::logic_error(CstringLITERAL_OF_LOGIC_ERROR),
    EBaseException(pszFileName, pszFuncName, nLineNumber, pszMessage)
{
  TLoggerTSS * __ptLoggerTSS__;
  #ifdef ENABLE_THREADS
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
  #else
  __ptLoggerTSS__ = &_GtLoggerTSS;
  #endif
  __ptLoggerTSS__->pszFileName = pszFileName;
  __ptLoggerTSS__->pszFuncName = pszFuncName;
  __ptLoggerTSS__->nLine = nLineNumber;
  __ptLoggerTSS__->nSyslogPriority = LOG_ERR;
  _LogMiddle("Bug: %s !\n", pszMessage);
}


EOutOfRange::EOutOfRange(const char * pszFileName,
                         const char * pszFuncName,
                         const int nLineNumber,
                         const std::string & rstringMessage)
  : std::out_of_range(CstringLITERAL_OF_OUT_OF_RANGE),
    EBaseException(pszFileName, pszFuncName, nLineNumber, rstringMessage)
{
  TLoggerTSS * __ptLoggerTSS__;
  #ifdef ENABLE_THREADS
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
  #else
  __ptLoggerTSS__ = &_GtLoggerTSS;
  #endif
  __ptLoggerTSS__->pszFileName = pszFileName;
  __ptLoggerTSS__->pszFuncName = pszFuncName;
  __ptLoggerTSS__->nLine = nLineNumber;
  __ptLoggerTSS__->nSyslogPriority = LOG_ERR;
  _LogMiddle("Bug: %s !\n", rstringMessage.c_str());
}


EOutOfRange::EOutOfRange(const char * pszFileName,
                         const char * pszFuncName,
                         const int nLineNumber,
                         const char * pszMessage)
  : std::out_of_range(CstringLITERAL_OF_OUT_OF_RANGE),
    EBaseException(pszFileName, pszFuncName, nLineNumber, pszMessage)
{
  TLoggerTSS * __ptLoggerTSS__;
  #ifdef ENABLE_THREADS
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
  #else
  __ptLoggerTSS__ = &_GtLoggerTSS;
  #endif
  __ptLoggerTSS__->pszFileName = pszFileName;
  __ptLoggerTSS__->pszFuncName = pszFuncName;
  __ptLoggerTSS__->nLine = nLineNumber;
  __ptLoggerTSS__->nSyslogPriority = LOG_ERR;
  _LogMiddle("Bug: %s !\n", pszMessage);
}


EOutOfRange::EOutOfRange(const char * pszFileName,
                         const char * pszFuncName,
                         const int nLineNumber,
                         const char * pszIndexName,
                         size_t iIndex,
                         size_t iMin,
                         size_t iMax)
  : std::out_of_range(CstringLITERAL_OF_OUT_OF_RANGE),
    EBaseException(pszFileName, pszFuncName, nLineNumber, 0)
{
  try {
    const std::string stringError = std::string(pszIndexName) + " " + iIndex +
                                    " out of range [" + iMin + "," + iMax + "]";
    TLoggerTSS * __ptLoggerTSS__;
    #ifdef ENABLE_THREADS
    _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
    #else
    __ptLoggerTSS__ = &_GtLoggerTSS;
    #endif
    __ptLoggerTSS__->pszFileName = pszFileName;
    __ptLoggerTSS__->pszFuncName = pszFuncName;
    __ptLoggerTSS__->nLine = nLineNumber;
    __ptLoggerTSS__->nSyslogPriority = LOG_ERR;
    _LogMiddle("Bug: %s !\n", stringError.c_str());

    AppendWhat(pszFileName, pszFuncName, nLineNumber, stringError);
  }
  catch (...)
  {
  }
}


ZLS_END_NAMESPACE

