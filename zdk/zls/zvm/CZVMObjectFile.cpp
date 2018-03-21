/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CZVMObjectFile.cpp,v $
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


#include <zls/zvm/CZVMObjectFile.hpp>
#include <zls/zvm/CVirtualMachine.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


CZVMObjectFile::CZVMObjectFile(CVirtualMachine * pciOwnerZVM, const std::string & rstringObjectFileName)
  : _pciOwnerZVM(pciOwnerZVM),
    _stringObjectFileName(rstringObjectFileName),
    _pciInitializerZVMFunction(0)
{ }


CZVMObjectFile::~CZVMObjectFile()
{
  std::vector<CZVMFunction *>::iterator it;

  for (it = _vectorGlobalFunctions.begin(); it != _vectorGlobalFunctions.end(); ++it)
  {
    delete *it;
  }
  _vectorGlobalFunctions.clear();
}


zfc::CBinaryInputFileStream & operator>>(zfc::CBinaryInputFileStream & bis, CZVMObjectFile & rciObjectFile)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("operator>>(zfc::CBinaryInputFileStream &, CZVMObjectFile &)");
  std::string stringError;
  TZVMIndex i;
  try {
    // Magic Number、Version
    bis >> rciObjectFile._udwMagicNumber
        >> rciObjectFile._uwMajorVersion
        >> rciObjectFile._uwMinorVersion;

    if (rciObjectFile._udwMagicNumber != CudwZVM_MAGIC_NUMBER)
    {
      stringError = std::string("Invalid ZVM magic number '") + rciObjectFile._udwMagicNumber + "'";
      throw zvm::EInvalidObjectFile(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
    }

    if (rciObjectFile._uwMajorVersion != CuwZVM_MAJOR_VERSION)
    {
      stringError = std::string("Incompatible ZVM major version '") + rciObjectFile._uwMajorVersion + "'";
      throw zvm::EInvalidObjectFile(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
    }

    if (rciObjectFile._uwMinorVersion != CuwZVM_MINOR_VERSION)
    {
      stringError = std::string("Incompatible ZVM minor version '") + rciObjectFile._uwMinorVersion + "'";
      throw zvm::EInvalidObjectFile(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
    }

    // constant pool
    bis >> rciObjectFile._ciConstantPool;

    // source file name index
    bis >> rciObjectFile._nSourceFileNameIndex;

    // 解析_nSourceFileNameIndex
    const CConstantPoolSlot * pciSlot =
          rciObjectFile._ciConstantPool.GetSlotAt(rciObjectFile._nSourceFileNameIndex);
          //< May throw zfc::EOutOfRange
    if (pciSlot->GetElementTag() != CONSTANT_POOL_ELEMENT_TAG_NIL_END_STRING)
    {
      stringError = std::string("Bad constant pool: Resolving 'source file name index=") +
                    rciObjectFile._nSourceFileNameIndex + "' failure";
      throw zvm::EInvalidObjectFile(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
    }
    rciObjectFile._stringSourceFileName = *(pciSlot->GetAsNilEndString());

    // global functions
    TZVMIndex nGlobalFunctionsCount;
    bis >> nGlobalFunctionsCount;
    for (i = 0; i < nGlobalFunctionsCount; ++i)
    {
      // 创建CZVMFunction instance，同时从流中读入信息
      CZVMFunction * pciFunction = new __OPTION(_THROW) CZVMFunction(&rciObjectFile, bis);
      rciObjectFile._vectorGlobalFunctions.push_back(pciFunction);
    }

    return bis;
  }
  catch (std::ios_base::failure & e)
  {
    if (bis.eof())  // 注；fail()包含failbit和badbit
    // 如果stream的eofbit被置位时
    {
      // Mapping to zlang::EInvalidObjectFile
      throw zvm::EInvalidObjectFile(__FILE__, __PRETTY_FUNC__, __LINE__, e.what());
    }
    else
    {
      throw;
    }
  }
}


void CZVMObjectFile::StripDebugInfo()
{
  std::vector<CZVMFunction *>::iterator it;

  for (it = _vectorGlobalFunctions.begin(); it != _vectorGlobalFunctions.end(); ++it)
  {
    (*it)->StripDebugInfo();
  }
}


void CZVMObjectFile::DumpDetail() const
{
  std::cout << "Magic number: " << std::hex << _udwMagicNumber << std::endl;
  std::cout << "Version: " << std::dec << _uwMajorVersion << "." << _uwMinorVersion << std::endl;

  std::cout << "Begin of constant pool: " << std::endl;
  _ciConstantPool.DumpDetail();
  std::cout << "End of constant pool." << std::endl;

  std::vector<CZVMFunction *>::const_iterator it;
  std::cout << "Begin of all global functions: " << std::endl;
  for (it = _vectorGlobalFunctions.begin(); it != _vectorGlobalFunctions.end(); ++it)
  {
    (*it)->DumpDetail();
  }
  std::cout << "End of all global functions." << std::endl << std::endl;
}


void CZVMObjectFile::VerifyByteCodesIntegrity() const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMObjectFile::VerifyByteCodesIntegrity()");
  std::string stringError;
  try {
    LogInfo(("Info: %s: Verifing ...\n", _stringObjectFileName.c_str()));

    ///> 检查各个ZVM function的完整性
    std::vector<CZVMFunction *>::const_iterator it;
    for (it = _vectorGlobalFunctions.begin(); it != _vectorGlobalFunctions.end(); ++it)
    {
      (*it)->VerifyByteCodesIntegrity();
    }

    LogInfo(("Info: %s: Verifing done.\n", _stringObjectFileName.c_str()));
  }
  catch(zvm::EVerifyFailure & e1)
  {
    throw;
  }
  catch(zfc::EBaseException & e2)
  {
    // Mapping to zlang::EVerifyFailure
    throw zvm::EVerifyFailure(e2);
  }
  catch(std::exception & e3)
  {
    // Mapping to zlang::EVerifyFailure
    throw zvm::EVerifyFailure(__FILE__, __PRETTY_FUNC__, __LINE__, e3.what());
  }
}


void CZVMObjectFile::Link1()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMObjectFile::Link1()");
  try {
    LogInfo(("Info: %s: Link1 ...\n", _stringObjectFileName.c_str()));

    TZVMIndex nSlotCapacity = _ciConstantPool.GetSlotCapacity();
    CConstantPoolSlot * pciSlot = _ciConstantPool.GetSlots();
    for (TZVMIndex i = 0; i < nSlotCapacity; ++i, ++pciSlot)
    {
      switch (pciSlot->GetElementTag())
      {
        case CONSTANT_POOL_ELEMENT_TAG_GLOBAL_VARIABLE_REFERENCE:
          {
            zvm::CGlobalVariableReference * pciVariableReference = pciSlot->GetAsGlobalVariableReference();
            TAccessModifierTag eAccessModifierTag = pciVariableReference->GetAccessModifierTag();
            switch (eAccessModifierTag)
            {
              case zvm::PUBLIC_BY_SELF_MODULE:
                // 如果是Internal的则注册，然后得到一个offset.
                {
                  // 得到name and signature串
                  const zvm::CNameAndSignatureReference * pciNameAndSignatureReference =
                                    pciVariableReference->GetNameAndSignatureReference();
                  // 注册,May throw zvm::ELink1Failure
                  CGlobalVariableRegisterTable::iterator it =
                        _pciOwnerZVM->RegisterGlobalVariable(pciNameAndSignatureReference->GetName(),
                                                             pciNameAndSignatureReference->GetSignature(),
                                                             this);
                  // 现在可以填写Relocated slot了
                  pciVariableReference->PatchRelocatedSlot((*it).second->GetVariableSlot());
                }
                break;

              case zvm::PRIVATE_FOR_SELF_MODULE:
                {
                  // 得到name and signature串
                  const zvm::CNameAndSignatureReference * pciNameAndSignatureReference =
                                    pciVariableReference->GetNameAndSignatureReference();
                  // 自己new一个CSlot
                  CSlot * pciSlot = new __OPTION(_THROW) CSlot(pciNameAndSignatureReference->GetSignature());
                  // 现在可以填写Relocated slot了
                  pciVariableReference->PatchRelocatedSlot(pciSlot);
                }
                break;

              default:
                break;
            }
          }
          break;

        case CONSTANT_POOL_ELEMENT_TAG_GLOBAL_FUNCTION_REFERENCE:
          {
            zvm::CGlobalFunctionReference * pciFunctionReference = pciSlot->GetAsGlobalFunctionReference();
            TAccessModifierTag eAccessModifierTag = pciFunctionReference->GetAccessModifierTag();
            switch (eAccessModifierTag)
            {
              case zvm::PUBLIC_BY_SELF_MODULE:
                // 如果是Internal public的则先自己进行内部定位，然后再注册
                LinkInternalPublicGlobalFunction(i, pciFunctionReference);
                //< 内部Link，May throw zvm::ELink1Failure.
                break;

              case zvm::PRIVATE_FOR_SELF_MODULE:
                // 如果是static的则先自己进行内部定位，但不注册
                LinkInternalStaticGlobalFunction(i, pciFunctionReference);
                //< 内部Link，May throw zvm::ELink1Failure.
                break;

              default:
                break;
            }
          }
          break;

        default:
          break;
      }
    }

    LogInfo(("Info: %s: Link1 done.\n", _stringObjectFileName.c_str()));
  }
  catch(zvm::ELink1Failure & e1)
  {
    throw;
  }
  catch(zfc::EBaseException & e2)
  {
    // Mapping to zvm::ELink1Failure
    throw zvm::ELink1Failure(e2);
  }
  catch(std::exception & e3)
  {
    // Mapping to zvm::ELink1Failure
    throw zvm::ELink1Failure(__FILE__, __PRETTY_FUNC__, __LINE__, e3.what());
  }
}


void CZVMObjectFile::LinkInternalPublicGlobalFunction(
  TZVMIndex iTargetFunctionReference,
  zvm::CGlobalFunctionReference * pciFunctionReference)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMObjectFile::LinkInternalPublicGlobalFunction()");
  const zvm::CNameAndSignatureReference * pciNameAndSignatureReference =
                            pciFunctionReference->GetNameAndSignatureReference();
  const std::string & rstringName = pciNameAndSignatureReference->GetName();
  const std::string & rstringSignature = pciNameAndSignatureReference->GetSignature();
  ///> 查找这个global function的CZVMFunction
  std::vector<CZVMFunction *>::iterator it;
  for (it = _vectorGlobalFunctions.begin(); it != _vectorGlobalFunctions.end(); ++it)
  {
    CZVMFunction * pciFunction = *it;
    if (pciFunction->GetFunctionReferenceIndex() == iTargetFunctionReference)
    {
      // 注册,May throw zvm::ELink1Failure
      _pciOwnerZVM->RegisterGlobalFunction(rstringName,
                                           rstringSignature,
                                           pciFunction,
                                           this);

      // 刷新Constant pool
      pciFunctionReference->PatchZVMFunction(pciFunction);
      return;
    }
  }

  ///> 现在是查找失败，throw zvm::ELink1Failure
  std::string stringError = "Unresolved global function '" +
                            FunctionNameAndSignatureToPrettyString(rstringName, rstringSignature) +
                            "'";
  throw zvm::ELink1Failure(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
}


void CZVMObjectFile::LinkInternalStaticGlobalFunction(
  TZVMIndex iTargetFunctionReference,
  zvm::CGlobalFunctionReference * pciFunctionReference)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMObjectFile::LinkInternalStaticGlobalFunction()");
  const zvm::CNameAndSignatureReference * pciNameAndSignatureReference =
                            pciFunctionReference->GetNameAndSignatureReference();
  const std::string & rstringName = pciNameAndSignatureReference->GetName();
  const std::string & rstringSignature = pciNameAndSignatureReference->GetSignature();
  ///> 查找这个static global function的CZVMFunction
  std::vector<CZVMFunction *>::iterator it;
  for (it = _vectorGlobalFunctions.begin(); it != _vectorGlobalFunctions.end(); ++it)
  {
    CZVMFunction * pciFunction = *it;
    if (pciFunction->GetFunctionReferenceIndex() == iTargetFunctionReference)
    {
      // 刷新Constant pool
      pciFunctionReference->PatchZVMFunction(pciFunction);

      // 如果这个static function是隐含的Initializer function
      if (rstringName == CstringInitializerFunctionName)
      {
        _pciInitializerZVMFunction = pciFunction;
      }

      return;
    }
  }

  ///> 现在是查找失败，throw zvm::ELink1Failure
  std::string stringError = "Unresolved static global function '" +
                            FunctionNameAndSignatureToPrettyString(rstringName, rstringSignature) +
                            "'";
  throw zvm::ELink1Failure(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
}


void CZVMObjectFile::Link2()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMObjectFile::Link2()");
  try {
    LogInfo(("Info: %s: Link2 ...\n", _stringObjectFileName.c_str()));

    TZVMIndex nSlotCapacity = _ciConstantPool.GetSlotCapacity();
    CConstantPoolSlot * pciSlot = _ciConstantPool.GetSlots();
    for (TZVMIndex i = 0; i < nSlotCapacity; ++i, ++pciSlot)
    {
      switch (pciSlot->GetElementTag())
      {
        case CONSTANT_POOL_ELEMENT_TAG_GLOBAL_VARIABLE_REFERENCE:
          {
            zvm::CGlobalVariableReference * pciVariableReference = pciSlot->GetAsGlobalVariableReference();
            if (pciVariableReference->GetAccessModifierTag() == zvm::PUBLIC_BY_EXTERN_MODULE)
            // 如果是Extern的则查Register表得到它的offset，然后刷新constant pool.
            {
              const zvm::CNameAndSignatureReference * pciNameAndSignatureReference =
                            pciVariableReference->GetNameAndSignatureReference();
              const std::string & rstringName = pciNameAndSignatureReference->GetName();
              const std::string & rstringSignature = pciNameAndSignatureReference->GetSignature();
              // Find
              CGlobalVariableRegisterEntry * pciEntry;
              if ((pciEntry = _pciOwnerZVM->FindRegisteredGlobalVariable(rstringName, rstringSignature)))
              {
                // 刷新Constant pool，现在可以填写Relocated slot了
                pciVariableReference->PatchRelocatedSlot(pciEntry->GetVariableSlot());

                // 增加对那个Object file或Library的引用计数
                IDynamicLoadableModule * pciModule = pciEntry->GetOwnerModule();
                pciModule->IncreaseReferencedCount();
              }
              else
              {
                std::string stringError = "Unresolved extern global variable '" +
                                           rstringName + "' referenced by '" +
                                          _stringSourceFileName + "(" + _stringObjectFileName + ")'";
                throw zvm::ELink2Failure(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
              }
            }
          }
          break;

        case CONSTANT_POOL_ELEMENT_TAG_GLOBAL_FUNCTION_REFERENCE:
          {
            zvm::CGlobalFunctionReference * pciFunctionReference = pciSlot->GetAsGlobalFunctionReference();
            if (pciFunctionReference->GetAccessModifierTag() == zvm::PUBLIC_BY_EXTERN_MODULE)
            // 如果是Extern的则查Register表得到它的注册信息，然后刷新constant pool.
            {
              const zvm::CNameAndSignatureReference * pciNameAndSignatureReference =
                            pciFunctionReference->GetNameAndSignatureReference();
              const std::string & rstringName = pciNameAndSignatureReference->GetName();
              const std::string & rstringSignature = pciNameAndSignatureReference->GetSignature();
              // Find
              CGlobalFunctionRegisterEntry * pciEntry;
              if (! (pciEntry = _pciOwnerZVM->FindRegisteredGlobalFunction(rstringName, rstringSignature)))
              {
                std::string stringError = "Unresolved extern global function '" +
                                          FunctionNameAndSignatureToPrettyString(rstringName, rstringSignature) +
                                          "' referenced by '" +
                                          _stringSourceFileName + "(" + _stringObjectFileName + ")'";
                throw zvm::ELink2Failure(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
              }
              else
              {
                // 刷新Constant pool
                if (pciEntry->GetLanguageTag() == LANGUAGE_TAG_IS_ZLANG)
                {
                  pciFunctionReference->PatchZVMFunction(pciEntry->GetZVMFunction());
                }
                else
                {
                  pciFunctionReference->PatchNativeFunction(pciEntry->GetNativeFunction());
                }
                // 增加对那个Object file或Library的引用计数
                IDynamicLoadableModule * pciModule = pciEntry->GetOwnerModule();
                pciModule->IncreaseReferencedCount();
              }
            }
          }
          break;

        default:
          break;
      }
    }

    LogInfo(("Info: %s: Link2 done.\n", _stringObjectFileName.c_str()));
  }
  catch(zvm::ELink2Failure & e1)
  {
    throw;
  }
  catch(zfc::EBaseException & e2)
  {
    // Mapping to zlang::ELink2Failure
    throw zvm::ELink2Failure(e2);
  }
  catch(std::exception & e3)
  {
    // Mapping to zlang::ELink2Failure
    throw zvm::ELink2Failure(__FILE__, __PRETTY_FUNC__, __LINE__, e3.what());
  }
}


ZLS_END_NAMESPACE

