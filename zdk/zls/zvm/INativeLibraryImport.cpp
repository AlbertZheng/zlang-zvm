/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/INativeLibraryImport.cpp,v $
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

 
#include <zls/zvm/INativeLibraryImport.hpp>


// Begin namespace 'zvm::'
ZLS_BEGIN_NAMESPACE(zvm)


INativeLibraryImport::TNativeFunctionImportEntry &
INativeLibraryImport::TNativeFunctionImportEntry::operator=(const INativeLibraryImport::TNativeFunctionImportEntry & rci)
{
  _stringFunctionName = rci._stringFunctionName;
  _stringFunctionSignature = rci._stringFunctionSignature;
  _pfuncNativeFunction = rci._pfuncNativeFunction;
  return *this;
}


INativeLibraryImport::TNativeFunctionImportEntry::TNativeFunctionImportEntry(
      const std::string & rstringFunctionName,
      const std::string & rstringFunctionSignature,
      TNativeFunction pfuncNativeFunction)
  : _stringFunctionName(rstringFunctionName),
    _stringFunctionSignature(rstringFunctionSignature),
    _pfuncNativeFunction(pfuncNativeFunction)
{ }


INativeLibraryImport &
INativeLibraryImport::operator=(const INativeLibraryImport & rci)
{
  _stringSourceFileName = rci._stringSourceFileName;
  _stringObjectFileName = rci._stringObjectFileName;
  _vectorNativeFunctionImportTable = rci._vectorNativeFunctionImportTable;
  return *this;
}


INativeLibraryImport::INativeLibraryImport(const std::string & rstringLibraryName,
                                           const std::string & rstringSourceFileName,
                                           const std::string & rstringObjectFileName)
  : _stringLibraryName(rstringLibraryName),
    _stringSourceFileName(rstringSourceFileName),
    _stringObjectFileName(rstringObjectFileName)
{ }


void INativeLibraryImport::AppendNativeFunctionImportEntry(const std::string & rstringFunctionName,
                                                           const std::string & rstringFunctionSignature,
                                                           TNativeFunction pfuncNativeFunction)
{
  _vectorNativeFunctionImportTable.push_back(TNativeFunctionImportEntry(rstringFunctionName,
                                                                        rstringFunctionSignature,
                                                                        pfuncNativeFunction));
}


ZLS_END_NAMESPACE
