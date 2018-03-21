/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/ZVMException.cpp,v $
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

 
#include <zls/zvm/ZVMException.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


void CZVMErrorReporter::ThrowRuntimeError(const char * pszFileName,
                                          const char * pszFuncName,
                                          const int nLineNumber,
                                          const std::string & rstringError)
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
  _LogMiddle("Fatal: ZVM: %s !\n", rstringError.c_str());
  throw EZVMRuntimeException(pszFileName, pszFuncName, nLineNumber, rstringError);
}


void CZVMErrorReporter::ThrowError_MultipleDefinitionSymbol(
  const char * pszFileName,
  const char * pszFuncName,
  const int nLineNumber,
  const char * pszSymbolTypeName,
  const std::string & rstringSymbolName,
  const std::string & rstringFirstSourceFileName,
  const std::string & rstringFirstObjectFileName,
  const std::string & rstringSecondSourceFileName,
  const std::string & rstringSecondObjectFileName)
{
  std::string stringError = std::string("Multiple definition of ") + pszSymbolTypeName + " '" + rstringSymbolName +
                            "' in '" + rstringFirstSourceFileName + "(" + rstringFirstObjectFileName +
                            ")' and '" + rstringSecondSourceFileName + "(" + rstringSecondObjectFileName + ")'";
  throw ELink1Failure(pszFileName, pszFuncName, nLineNumber, stringError);
}


/**
 * 当妄想将某个二元操作符应用到（这个操作符）不允许的数据类型的操作数上时，报告这个Bug.
 * 例如："*"、"/"等.
 *
 * @throw zfc::EPanic.
 */
/*
void CZVMErrorReporter::ThrowBug_InvalidUseBinaryOperator(
  const char * pszFileName,
  const char * pszFuncName,
  const int nLineNumber,
  char chOperator,
  const std::string & rstringLeftTypeSignature,
  const std::string & rstringRightTypeSignature)
{
  std:: string stringError = "Invalid use of binary '" + std::string(1, chOperator) +
                             "' on type '" + TypeSignatureToPrettyString(rstringLeftTypeSignature) +
                             "' and type '" + TypeSignatureToPrettyString(rstringRightTypeSignature) +
                             "'";
  throw zfc::EPanic(pszFileName, pszFuncName, nLineNumber, stringError);
}

*/


/**
 * 当妄想将某个二元操作符应用到（这个操作符）不允许的数据类型的操作数上时，报告这个Bug.
 * 例如："<="、">="、"<<"、">>"等.
 *
 * @throw zfc::EPanic.
 */
/*
void CZVMErrorReporter::ThrowBug_InvalidUseBinaryOperator(
  const char * pszFileName,
  const char * pszFuncName,
  const int nLineNumber,
  const std::string & rstringOperator,
  const std::string & rstringLeftTypeSignature,
  const std::string & rstringRightTypeSignature)
{
  std:: string stringError = "Invalid use of binary '" + rstringOperator +
                             "' on type '" + TypeSignatureToPrettyString(rstringLeftTypeSignature) +
                             "' and type '" + TypeSignatureToPrettyString(rstringRightTypeSignature) +
                             "'";
  throw zfc::EPanic(pszFileName, pszFuncName, nLineNumber, stringError);
}

*/


/**
 * 当妄想将某个二元操作符应用到（这个操作符）不允许的数据类型的操作数上时，报告这个Bug.
 *
 * @throw zfc::EPanic.
 */
/*
void CZVMErrorReporter::ThrowBug_InvalidUseBinaryOperator(
  const char * pszFileName,
  const char * pszFuncName,
  const int nLineNumber,
  char chOperator,
  const std::string & rstringLeftTypeSignature)
{
  std:: string stringError = "Invalid use of binary '" + std::string(1, chOperator) +
                             "' on type '" + TypeSignatureToPrettyString(rstringLeftTypeSignature) +
                             "'";
  throw zfc::EPanic(pszFileName, pszFuncName, nLineNumber, stringError);
}

*/


/**
 * 当妄想将某个二元操作符应用到（这个操作符）不允许的数据类型的操作数上时，报告这个Bug.
 * 例如："<="、">="、"<<"、">>"等.
 *
 * @throw zfc::EPanic.
 */
/*
void CZVMErrorReporter::ThrowBug_InvalidUseBinaryOperator(
  const char * pszFileName,
  const char * pszFuncName,
  const int nLineNumber,
  const std::string & rstringOperator,
  const std::string & rstringLeftTypeSignature)
{
  std:: string stringError = "Invalid use of binary '" + rstringOperator +
                             "' on type '" + TypeSignatureToPrettyString(rstringLeftTypeSignature) +
                             "'";
  throw zfc::EPanic(pszFileName, pszFuncName, nLineNumber, stringError);
}

*/


/**
 * 当妄想将某个一元操作符应用到（这个操作符）不允许的数据类型的操作数上时，报告这个Bug.
 * 例如:"~"等.
 *
 * @throw zfc::EPanic.
 */
/*
void CZVMErrorReporter::ThrowBug_InvalidUseUnaryOperator(
  const char * pszFileName,
  const char * pszFuncName,
  const int nLineNumber,
  char chOperator,
  const std::string & rstringLeftTypeSignature)
{
  std:: string stringError = "Invalid use of unary '" + std::string(1, chOperator) +
                             "' on type '" + TypeSignatureToPrettyString(rstringLeftTypeSignature) +
                             "'";
  throw zfc::EPanic(pszFileName, pszFuncName, nLineNumber, stringError);
}

*/


/**
 * 当妄想将某个一元操作符应用到（这个操作符）不允许的数据类型的操作数上时，报告这个Bug.
 * 例如："++"、"--"等.
 *
 * @throw zfc::EPanic.
 */
/*
void CZVMErrorReporter::ThrowBug_InvalidUseUnaryOperator(
  const char * pszFileName,
  const char * pszFuncName,
  const int nLineNumber,
  const std::string & rstringOperator,
  const std::string & rstringLeftTypeSignature)
{
  std:: string stringError = "Invalid use of unary '" + rstringOperator +
                             "' on type '" + TypeSignatureToPrettyString(rstringLeftTypeSignature) +
                             "'";
  throw zfc::EPanic(pszFileName, pszFuncName, nLineNumber, stringError);
}

*/


/**
 * 当妄想进行不允许的Cast操作时，报告这个Bug.
 * 例如："ZVM string" cast to "ZVM udword"等.
 *
 * @throw zfc::EPanic.
 */
/*
void CZVMErrorReporter::ThrowBug_InvalidUseCast(
  const char * pszFileName,
  const char * pszFuncName,
  const int nLineNumber,
  const std::string & rstringLeftTypeSignature,
  char chTargetSignature)
{
  std:: string stringError = "Invalid use of 'cast' from type '" +
                             TypeSignatureToPrettyString(rstringLeftTypeSignature) +
                             "' to '" + std::string(1, chTargetSignature) + "'";
  throw zfc::EPanic(pszFileName, pszFuncName, nLineNumber, stringError);
}

*/


/*
void CZVMErrorReporter::ThrowBug_BadAssumeTypeSignatureOfCZVMObject(
  const char * pszFileName,
  const char * pszFuncName,
  const int nLineNumber,
  const std::string & rstringRealTypeSignature)
{
  std::string stringError = "Bad assume type signature of CZVMObject, Real type signature is '" +
                            rstringRealTypeSignature +
                            "'";
  throw zfc::EPanic(pszFileName, pszFuncName, nLineNumber, stringError);
}
*/


ZLS_END_NAMESPACE

