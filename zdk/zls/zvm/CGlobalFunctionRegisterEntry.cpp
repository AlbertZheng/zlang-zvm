/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CGlobalFunctionRegisterEntry.cpp,v $
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


#include <zls/zvm/CGlobalFunctionRegisterEntry.hpp>
#include <zls/zvm/IDynamicLoadableModule.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


CGlobalFunctionRegisterEntry::CGlobalFunctionRegisterEntry(
      const std::string & rstringFunctionSignature,
      const CZVMFunction * pciZVMFunction,
      IDynamicLoadableModule * pciOwnerModule)
  : _stringFunctionSignature(rstringFunctionSignature),
    _eLanguageTag(LANGUAGE_TAG_IS_ZLANG),
    _pciZVMFunction(pciZVMFunction),
    _pciOwnerModule(pciOwnerModule)
{
  DoCache();
}


CGlobalFunctionRegisterEntry::CGlobalFunctionRegisterEntry(
      const std::string & rstringFunctionSignature,
      TNativeFunction pfuncNativeFunction,
      IDynamicLoadableModule * pciOwnerModule)
  : _stringFunctionSignature(rstringFunctionSignature),
    _eLanguageTag(LANGUAGE_TAG_IS_CPP),
    _pfuncNativeFunction(pfuncNativeFunction),
    _pciOwnerModule(pciOwnerModule)
{
  DoCache();
}


void CGlobalFunctionRegisterEntry::DoCache()
{
  std::vector<std::string> vectorTokens;
  // 分解这个ZVM function的type signature
  FunctionSignatureToken(vectorTokens, _stringFunctionSignature);

  // 将"所有参数"的type signature分解到vectorArgumentsSignatures
  std::vector<std::string> vectorArgumentsSignatures;
  ArgumentsSignatureToken(vectorArgumentsSignatures, vectorTokens[0]);

  // 将type signature转换为CSlot::TSlotTag
  CSlot::TypeSignatureToSlotTag(vectorArgumentsSignatures, _vectorArgumentsSlotTags);

  // 置_eReturnSlotTag
  std::string & rstringReturnSignature = vectorTokens[1];
  _eReturnSlotTag = CSlot::TypeSignatureToSlotTag(rstringReturnSignature);
}


const std::string & CGlobalFunctionRegisterEntry::GetSourceFileName() const
{ return _pciOwnerModule->GetSourceFileName(); }


const std::string & CGlobalFunctionRegisterEntry::GetObjectFileName() const
{ return _pciOwnerModule->GetObjectFileName(); }


ZLS_END_NAMESPACE

