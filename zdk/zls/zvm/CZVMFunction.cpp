/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CZVMFunction.cpp,v $
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


#include <zls/zvm/CZVMFunction.hpp>
#include <zls/zvm/CZVMObjectFile.hpp>
#include <zls/zvm/CInstruction.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


void CZVMFunction::DoCache()
{
  _pciConstantPool = &(_pciOwnerObjectFile->GetConstantPool());
  const zvm::CGlobalFunctionReference * pciFunctionReference =
            _pciConstantPool->GetAsGlobalFunctionReference(_iFunctionReference);
                              //< May throw zfc::EOutOfRange
  // 先预解析name and signature reference
  _pciNameAndSignatureReference = pciFunctionReference->GetNameAndSignatureReference();
}


CZVMFunction::CZVMFunction(const CZVMObjectFile * pciObjectFile,
                           zfc::CBinaryInputFileStream & bis)
  : _pciOwnerObjectFile(pciObjectFile),
    _pciConstantPool(0),
    _pciNameAndSignatureReference(0),
    _bDebugInfoStriped(false),
    _iFunctionReference(0),
    _uwParameterCount(0),
    _uwLocalVariableCount(0)
{
  bis >> *this;
  // 预解析name and signature reference
  DoCache();
}


CZVMFunction::~CZVMFunction()
{
  delete [] _aciInstructionSequence;
}


void CZVMFunction::StripDebugInfo()
{
  _vectorLineNumberDebugInfo.clear();
  _vectorStackVariableDebugInfo.clear();
  _bDebugInfoStriped = true;
}


TZVMIndex CZVMFunction::InstructionToLineNumber(const CInstruction * pciInstruction) const
{
  // 计算这条指令的Index
  TZVMIndex iInstruction = pciInstruction - _aciInstructionSequence;
  return InstructionIndexToLineNumber(iInstruction);
}


TZVMIndex CZVMFunction::InstructionIndexToLineNumber(TZVMIndex iInstruction) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMFunction::InstructionIndexToLineNumber()");

  if (_bDebugInfoStriped)
  {
    std::string stringError = "Sorry, But debug info had been striped";
    throw zfc::EInvalidState(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
  }

  std::vector<TLineNumberDebug>::const_iterator it;
  for (it = _vectorLineNumberDebugInfo.begin();
       it != _vectorLineNumberDebugInfo.end();
       ++it)
  {
    if ((*it).iFromWhichInstructionStart > iInstruction)
    {
      if (it != _vectorLineNumberDebugInfo.begin())
      {
        return (*(--it)).iLineNumber;
      }
      else
      {
        return 0;
      }
    }
  }

  if (_vectorLineNumberDebugInfo.size() > 0)
  {
    return _vectorLineNumberDebugInfo.back().iLineNumber;
  }
  else
  {
    return 0;
  }
}


void CZVMFunction::VerifyByteCodesIntegrity() const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMFunction::VerifyByteCodesIntegrity()");

  for (TZVMIndex nIndex = 0; nIndex < _nInstructionSequenceCapacity; ++nIndex)
  {
    try {
      _aciInstructionSequence[nIndex].VerifyByteCodesIntegrity(*_pciConstantPool,
                                                               nIndex,
                                                               _nInstructionSequenceCapacity - 1);
    }
    catch (zvm::EVerifyFailure & e)
    {
      std::string stringError = std::string("Verifing function integrity stopped at the ") + nIndex + " instruction";
      stringError += " of '";
      stringError += FunctionNameAndSignatureToPrettyString(_pciNameAndSignatureReference->GetName(),
                                                            _pciNameAndSignatureReference->GetSignature());
      stringError += "'";
      e.AppendWhat(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      throw;
    }
  }
}


void CZVMFunction::DumpDetail() const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMFunction::DumpDetail()");
  std::cout << "  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
  std::cout << "    function name: " << _pciNameAndSignatureReference->GetName() << std::endl;
  std::cout << "    function reference: " << _iFunctionReference << std::endl;
  std::cout << "    parameter count: " << _uwParameterCount << std::endl;
  std::cout << "    local variable count: " << _uwLocalVariableCount << std::endl;
  std::cout << "    instruction sequence: " << std::endl;

  for (TZVMIndex nIndex = 0; nIndex < _nInstructionSequenceCapacity; ++nIndex)
  {
    std::cout << "      " << nIndex << ": ";
    #ifndef NDEBUG
    try {
    #endif
      _aciInstructionSequence[nIndex].DumpDetail();
    #ifndef NDEBUG
    }
    catch(zfc::EPanic & e)
    {
      std::string stringError = std::string("Dump stopped at the ") + nIndex + " instruction";
      e.AppendWhat(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      throw;
    }
    #endif
  }
  std::cout << "  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl << std::endl;
}


zfc::CBinaryInputFileStream & operator>>(zfc::CBinaryInputFileStream & bis, CZVMFunction::TLineNumberDebug & rsi)
{
  bis >> rsi.iFromWhichInstructionStart >> rsi.iLineNumber;
  return bis;
}


zfc::CBinaryInputFileStream & operator >> (zfc::CBinaryInputFileStream & bis, CZVMFunction::TStackVariableDebug & rsi)
{
  bis >> rsi.iNameAndSignatureReference >> rsi.iBPOffset;
  return bis;
}


zfc::CBinaryInputFileStream & operator>>(zfc::CBinaryInputFileStream & bis, CZVMFunction & rci)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("operator>>(zfc::CBinaryInputFileStream &, CZVMFunction &)");

  // 读入最前面的三个字段
  bis >> rci._iFunctionReference >> rci._uwParameterCount >> rci._uwLocalVariableCount;

  ///> 读入各条指令
  TZVMIndex nCapacity;
  bis >> nCapacity;
  rci._nInstructionSequenceCapacity = nCapacity;  // instruction sequence capacity
  rci._aciInstructionSequence = new __OPTION(_THROW) zvm::CInstruction[nCapacity];
  memset(rci._aciInstructionSequence, '\0', sizeof(zvm::CInstruction) * nCapacity);
  for (TZVMIndex nIndex = 0; nIndex < nCapacity; ++nIndex)
  {
    try {
      bis >> rci._aciInstructionSequence[nIndex];
    }
    catch(zvm::EInvalidObjectFile & e)
    {
      std::string stringError = std::string("Read function stopped at the ") + nIndex + " instruction";
      e.AppendWhat(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      throw;
    }
  }

  ///> 读入Line跟踪信息
  bis >> nCapacity;
  while (nCapacity > 0)
  {
    CZVMFunction::TLineNumberDebug siDebug;
    bis >> siDebug;
    rci._vectorLineNumberDebugInfo.push_back(siDebug);
    --nCapacity;
  }

  ///> 读入Stack variable跟踪信息
  bis >> nCapacity;
  while (nCapacity > 0)
  {
    CZVMFunction::TStackVariableDebug siDebug;
    bis >> siDebug;
    rci._vectorStackVariableDebugInfo.push_back(siDebug);
    --nCapacity;
  }

  return bis;
}


ZLS_END_NAMESPACE

