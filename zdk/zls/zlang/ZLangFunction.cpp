/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/ZLangFunction.cpp,v $
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


#include <zls/zvm/ZVMException.hpp>
#include <zls/zvm/CInstructionDictionary.hpp>
#include <zls/zlang/ZLangFunction.hpp>
#include <zls/zlang/ConstantPool.hpp>
#include <zls/zvm/InstructionCode.hpp>


// Begin namespace 'zlang::'
ZLS_BEGIN_NAMESPACE(zlang)


/******************************************************************************
 * class CInstruction
 ******************************************************************************/
const std::string CInstruction::InstructionCodeToString(zvm::TZVMICode nInstructionCode)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CInstruction::InstructionCodeToString()");
  const zvm::CInstructionDictionary::TInstructionDictionaryEntry * psiEntry =
        zvm::GciInstructionDictionaryFactory.GetSingleton()->SeekInstructionDictionary(nInstructionCode);
  if (psiEntry)
  {
    return psiEntry->pszInstructionText;
  }
  std::string stringError = std::string("Invalid ZVM instruction code -> 0x") + zfc::UWORDToString(nInstructionCode, 16);
  throw zfc::EInvalidArgument(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
}


CInstruction & CInstruction::operator=(const CInstruction & rciRight)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CInstruction::operator=()");
  if (this != &rciRight)
  {
    _nInstructionCode = rciRight._nInstructionCode;
    _nOperandByteCount = rciRight._nOperandByteCount;
    _bNeedFixTempLocalVariableOffset = rciRight._bNeedFixTempLocalVariableOffset;
    switch (_nOperandByteCount)
    {
      case 0:
        break;

      case sizeof(UCHAR):
        _uchOperand = rciRight._uchOperand;
        break;

      case sizeof(UWORD):
        _uwOperand = rciRight._uwOperand;
        break;

      case sizeof(UDWORD):
        _udwOperand = rciRight._udwOperand;
        break;

      default:
        LogAssert1(ShouldNotRunToHere(), "Operand count '%d' is invalid", static_cast<SDWORD>(_nOperandByteCount));
        break;
    }
  }
  return *this;
}


std::string CInstruction::ToString() const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CInstruction::ToString()");
  std::string stringError;
  std::string stringResult;
  const zvm::CInstructionDictionary::TInstructionDictionaryEntry * psiEntry =
        zvm::GciInstructionDictionaryFactory.GetSingleton()->SeekInstructionDictionary(_nInstructionCode);
  #ifndef NDEBUG
  /*
  std::cout << "Instruction-Code = 0x"
            << zfc::UWORDToString(_nInstructionCode, 16)
            << " , Operand-Count = "
            << static_cast<SWORD>(_nOperandByteCount)
            << std::endl;
  */
  if (! psiEntry)
  {
    stringError = std::string("Instruction or Dictionary have some bugs -> Instruction-Code = 0x") +
                  zfc::UWORDToString(_nInstructionCode, 16) + " , Operand-Count = " + _nOperandByteCount;
    throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
  }
  #endif

  stringResult = psiEntry->pszInstructionText;

  switch (_nOperandByteCount)
  {
    case 0:
      break;

    case 1:
      stringResult += " ";
      if (psiEntry->eOperandType & zvm::CInstructionDictionary::OPERAND_IS_SIGNED_NUMBER_BIT)
      {
        stringResult += zfc::SWORDToString(static_cast<SWORD>(_uchOperand), 10);
      }
      else
      {
        stringResult += zfc::UWORDToString(_uchOperand, 10);
      }
      break;

    case 2:
      stringResult += " ";
      if (psiEntry->eOperandType & zvm::CInstructionDictionary::OPERAND_IS_SIGNED_NUMBER_BIT)
      {
        stringResult += zfc::SWORDToString(static_cast<SWORD>(_uwOperand), 10);
      }
      else
      {
        stringResult += zfc::UWORDToString(_uwOperand, 10);
      }
      break;

    case sizeof(UDWORD):
      stringResult += " ";
      if (psiEntry->eOperandType & zvm::CInstructionDictionary::OPERAND_IS_SIGNED_NUMBER_BIT)
      {
        stringResult += zfc::SDWORDToString(static_cast<SDWORD>(_udwOperand), 10);
      }
      else
      {
        stringResult += zfc::UDWORDToString(_udwOperand, 10);
      }
      break;

    default:
      #ifndef NDEBUG
      stringError = std::string("Invalid operand byte count -> ") + _nOperandByteCount;
      throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      #endif
      break;
  }

  return stringResult;
}


zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos, const CInstruction & rci)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("operator<<(zfc::CBinaryOutputFileStream &,const CInstruction &)");

  bos << rci._nInstructionCode << rci._nOperandByteCount;

  switch (rci._nOperandByteCount)
  {
    case 0:
      break;

    case sizeof(UCHAR):
      bos << rci._uchOperand;
      break;

    case sizeof(UWORD):
      bos << rci._uwOperand;
      break;

    case sizeof(UDWORD):
      bos << rci._udwOperand;
      break;

    default:
      #ifndef NDEBUG
      std::string stringError = std::string("Invalid operand byte count -> ") + rci._nOperandByteCount;
      throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      #endif
      break;
  }

  return bos;
}


/******************************************************************************
 * class CInstructionContainer
 ******************************************************************************/
void CInstructionContainer::AppendLineNumberDebugInfo(zvm::TZVMIndex iStart, zvm::TZVMIndex iLineNumber)
{
  TLineNumberDebug siDebug(iStart, iLineNumber);
  _dequeLineNumberDebugInfos.push_back(siDebug);
}


zvm::TZVMIndex CInstructionContainer::AppendInstruction(zvm::TZVMICode nInstructionCode)
{
  CInstruction ciInstruction(nInstructionCode);
  _dequeInstructions.push_back(ciInstruction);
  return _dequeInstructions.size()-1;
}


zvm::TZVMIndex CInstructionContainer::AppendInstruction(zvm::TZVMICode nInstructionCode, UCHAR uchOperand)
{
  CInstruction ciInstruction(nInstructionCode, uchOperand);
  _dequeInstructions.push_back(ciInstruction);
  return _dequeInstructions.size()-1;
}


zvm::TZVMIndex CInstructionContainer::AppendInstruction(zvm::TZVMICode nInstructionCode, UWORD uwOperand)
{
  CInstruction ciInstruction(nInstructionCode, uwOperand);
  _dequeInstructions.push_back(ciInstruction);
  return _dequeInstructions.size()-1;
}


zvm::TZVMIndex CInstructionContainer::AppendInstruction(zvm::TZVMICode nInstructionCode, SWORD swOperand)
{
  CInstruction ciInstruction(nInstructionCode, swOperand);
  _dequeInstructions.push_back(ciInstruction);
  return _dequeInstructions.size()-1;
}


zvm::TZVMIndex CInstructionContainer::AppendInstruction(zvm::TZVMICode nInstructionCode, zvm::TZVMIndex nOperand)
{
  CInstruction ciInstruction(nInstructionCode, nOperand);
  _dequeInstructions.push_back(ciInstruction);
  return _dequeInstructions.size()-1;
}


zvm::TZVMIndex CInstructionContainer::AppendInstruction(zvm::TZVMICode nInstructionCode, UDWORD udwOperand)
{
  CInstruction ciInstruction(nInstructionCode, udwOperand);
  _dequeInstructions.push_back(ciInstruction);
  return _dequeInstructions.size()-1;
}


zvm::TZVMIndex CInstructionContainer::AppendInstruction(CInstructionContainer_auto autoContainer)
{
  // 记下当前还没Append之前的最后一条指令的位置
  zvm::TZVMIndex nCurrentLastInstruction = _dequeInstructions.size() - 1;
  // Append instructions
  _dequeInstructions.insert(_dequeInstructions.end(),
                            autoContainer->GetInstructions().begin(),
                            autoContainer->GetInstructions().end());
  // Append and fix line number info
  std::deque<TLineNumberDebug>::iterator it;
  for (it = autoContainer->GetLineNumberDebugInfos().begin();
       it != autoContainer->GetLineNumberDebugInfos().end();
       ++it)
  {
    TLineNumberDebug si = *it;
    // 修正指令Number
    si.iFromWhichInstructionStart += nCurrentLastInstruction;
    // Append
    _dequeLineNumberDebugInfos.push_back(si);
  }

  return _dequeInstructions.size()-1;
}


std::deque<CInstruction>::iterator CInstructionContainer::JumpToPosition(zvm::TZVMIndex nPosition)
{
  std::deque<CInstruction>::iterator it;
  for (it = _dequeInstructions.begin();
       it != _dequeInstructions.end() && nPosition > 0;
       ++it, --nPosition)
  { }
  return it;
}


zvm::TZVMIndex CInstructionContainer::InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                                              zvm::TZVMICode nInstructionCode)
{
  CInstruction ciInstruction(nInstructionCode);
  std::deque<CInstruction>::iterator it = JumpToPosition(nBeforePosition);
  _dequeInstructions.insert(it, ciInstruction);
  return nBeforePosition;
}


zvm::TZVMIndex CInstructionContainer::InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                                              zvm::TZVMICode nInstructionCode,
                                                              UCHAR uchOperand)
{
  CInstruction ciInstruction(nInstructionCode, uchOperand);
  std::deque<CInstruction>::iterator it = JumpToPosition(nBeforePosition);
  _dequeInstructions.insert(it, ciInstruction);
  return nBeforePosition;
}


zvm::TZVMIndex CInstructionContainer::InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                                              zvm::TZVMICode nInstructionCode,
                                                              UWORD uwOperand)
{
  CInstruction ciInstruction(nInstructionCode, uwOperand);
  std::deque<CInstruction>::iterator it = JumpToPosition(nBeforePosition);
  _dequeInstructions.insert(it, ciInstruction);
  return nBeforePosition;
}


zvm::TZVMIndex CInstructionContainer::InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                                              zvm::TZVMICode nInstructionCode,
                                                              SWORD swOperand)
{
  CInstruction ciInstruction(nInstructionCode, swOperand);
  std::deque<CInstruction>::iterator it = JumpToPosition(nBeforePosition);
  _dequeInstructions.insert(it, ciInstruction);
  return nBeforePosition;
}


zvm::TZVMIndex CInstructionContainer::InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                                              zvm::TZVMICode nInstructionCode,
                                                              zvm::TZVMIndex nOperand)
{
  CInstruction ciInstruction(nInstructionCode, nOperand);
  std::deque<CInstruction>::iterator it = JumpToPosition(nBeforePosition);
  _dequeInstructions.insert(it, ciInstruction);
  return nBeforePosition;
}


zvm::TZVMIndex CInstructionContainer::InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                                              zvm::TZVMICode nInstructionCode,
                                                              UDWORD udwOperand)
{
  CInstruction ciInstruction(nInstructionCode, udwOperand);
  std::deque<CInstruction>::iterator it = JumpToPosition(nBeforePosition);
  _dequeInstructions.insert(it, ciInstruction);
  return nBeforePosition;
}


void CInstructionContainer::SmartFixTempLocalVariableOffset(UWORD uwLocalVariableCount)
{
  std::deque<CInstruction>::iterator it;
  for (it = _dequeInstructions.begin(); it != _dequeInstructions.end(); ++it)
  {
    (*it).SmartFixTempLocalVariableOffset(uwLocalVariableCount);
  }
}


void CInstructionContainer::BackPatchLabel(zvm::TZVMIndex iWhichInstruction, zvm::TZVMIndex iPatchedLabel)
{
  CInstruction & rciInstruction = _dequeInstructions[iWhichInstruction];
  // 注意：采用offset
  rciInstruction.BackPatchLabel(iPatchedLabel - iWhichInstruction);
}


CInstruction & CInstructionContainer::GetInstructionAt(zvm::TZVMIndex iIndex)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZLangFunction::GetInstructionAt()");
  zvm::TZVMIndex nSize = _dequeInstructions.size() - 1;
  if (iIndex < 0 || iIndex > nSize )
  {
    throw zfc::EOutOfRange(__FILE__, __PRETTY_FUNC__ , __LINE__,
                           "Instruction index", iIndex, 0, nSize);
  }
  return _dequeInstructions[iIndex];
}


zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos, const CInstructionContainer::TLineNumberDebug & rt)
{
  bos << rt.iFromWhichInstructionStart << rt.iLineNumber;
  return(bos);
}


/******************************************************************************
 * class CInstructionSequence
 ******************************************************************************/


/******************************************************************************
 * class CZLangFunction::TempVariableAllocator
 ******************************************************************************/
CZLangFunction::TempVariableAllocator::TempVariableAllocator(CZLangFunction * pciOwnerZLangFunction)
  : _pciOwnerZLangFunction(pciOwnerZLangFunction),
    _uwTempVariableCount(0),
    _iFirstAvailableStringVariable(0),
    _iFirstAvailableIPv4AddressVariable(0),
    _iFirstAvailablePPortVariable(0),
    _iFirstAvailableTableVariable(0)
{ }


void CZLangFunction::TempVariableAllocator::FreeAllTempVariables()
{
  _iFirstAvailableStringVariable = 0;
  _iFirstAvailableRopeVariable = 0;
  _iFirstAvailableIPv4AddressVariable = 0;
  _iFirstAvailablePPortVariable = 0;
  _iFirstAvailableTableVariable = 0;
}


void CZLangFunction::TempVariableAllocator::InsertTempVariableInstruction(zvm::TZVMICode nICode)
{
  // 动态新增加temp variable
  CInstruction ciInstruction(nICode);

  // 跳过最前面的那些正式变量和已被新增加的temp variable的"construct?"指令
  // 注意：还要加1，因为最前面有一条pushBP指令
  int nJump = _pciOwnerZLangFunction->_uwLocalVariableCount + _uwTempVariableCount + 1;
  std::deque<CInstruction>::iterator it = _pciOwnerZLangFunction->JumpToPosition(nJump);

  // 在当前it前面插入新指令
  _pciOwnerZLangFunction->_dequeInstructions.insert(it, ciInstruction);
}


SWORD CZLangFunction::TempVariableAllocator::AllocateTempStringVariable(bool bReturnIndex = false)
{
  SWORD swOffset;
  if (_iFirstAvailableStringVariable == _vectorStringVariableOffsets.size())
  // 如果需要动态新增加temp variable
  {
    // 动态新增加temp string variable指令
    InsertTempVariableInstruction(zvm::ZVM_construct | zvm::CchZVM_STRING_TYPE_TAG);

    ++_uwTempVariableCount;
    // 2001/7/21: 改为只存贮temp variable index，然后要返回offset时再立即加上local variable count即可
    _vectorStringVariableOffsets.push_back(_uwTempVariableCount);
    if (bReturnIndex)
    {
      swOffset = _uwTempVariableCount;
    }
    else
    {
      swOffset = _pciOwnerZLangFunction->_uwLocalVariableCount + _uwTempVariableCount;
    }
  }
  else
  // 直接利用已经被动态增加的temp variable
  {
    // 2001/7/21: 改为只存贮temp variable index，然后要返回offset时再立即加上local variable count即可
    if (bReturnIndex)
    {
      swOffset = _vectorStringVariableOffsets[_iFirstAvailableStringVariable];
    }
    else
    {
      swOffset = _pciOwnerZLangFunction->_uwLocalVariableCount +
                 _vectorStringVariableOffsets[_iFirstAvailableStringVariable];
    }
  }

  ++_iFirstAvailableStringVariable;
  return swOffset;
}


SWORD CZLangFunction::TempVariableAllocator::AllocateTempRopeVariable(bool bReturnIndex = false)
{
  SWORD swOffset;
  if (_iFirstAvailableRopeVariable == _vectorRopeVariableOffsets.size())
  // 如果需要动态新增加temp variable
  {
    // 动态新增加temp rope variable指令
    InsertTempVariableInstruction(zvm::ZVM_construct | zvm::CchZVM_ROPE_TYPE_TAG);

    ++_uwTempVariableCount;
    // 2001/7/21: 改为只存贮temp variable index，然后要返回offset时再立即加上local variable count即可
    _vectorRopeVariableOffsets.push_back(_uwTempVariableCount);
    if (bReturnIndex)
    {
      swOffset = _uwTempVariableCount;
    }
    else
    {
      swOffset = _pciOwnerZLangFunction->_uwLocalVariableCount + _uwTempVariableCount;
    }
  }
  else
  // 直接利用已经被动态增加的temp variable
  {
    // 2001/7/21: 改为只存贮temp variable index，然后要返回offset时再立即加上local variable count即可
    if (bReturnIndex)
    {
      swOffset = _vectorRopeVariableOffsets[_iFirstAvailableRopeVariable];
    }
    else
    {
      swOffset = _pciOwnerZLangFunction->_uwLocalVariableCount +
                 _vectorRopeVariableOffsets[_iFirstAvailableRopeVariable];
    }
  }

  ++_iFirstAvailableRopeVariable;
  return swOffset;
}


SWORD CZLangFunction::TempVariableAllocator::AllocateTempIPv4AddressVariable(bool bReturnIndex = false)
{
  SWORD swOffset;
  if (_iFirstAvailableIPv4AddressVariable == _vectorIPv4AddressVariableOffsets.size())
  // 如果需要动态新增加temp variable
  {
    // 动态新增加temp ipv4address variable指令
    InsertTempVariableInstruction(zvm::ZVM_construct | zvm::CchZVM_IPv4ADDR_TYPE_TAG);

    ++_uwTempVariableCount;
    // 2001/7/21: 改为只存贮temp variable index，然后要返回offset时再立即加上local variable count即可
    _vectorIPv4AddressVariableOffsets.push_back(_uwTempVariableCount);
    if (bReturnIndex)
    {
      swOffset = _uwTempVariableCount;
    }
    else
    {
      swOffset = _pciOwnerZLangFunction->_uwLocalVariableCount + _uwTempVariableCount;
    }
  }
  else
  // 直接利用已经被动态增加的temp variable
  {
    // 2001/7/21: 改为只存贮temp variable index，然后要返回offset时再立即加上local variable count即可
    if (bReturnIndex)
    {
      swOffset = _vectorIPv4AddressVariableOffsets[_iFirstAvailableIPv4AddressVariable];
    }
    else
    {
      swOffset = _pciOwnerZLangFunction->_uwLocalVariableCount +
                 _vectorIPv4AddressVariableOffsets[_iFirstAvailableIPv4AddressVariable];
    }
  }

  ++_iFirstAvailableIPv4AddressVariable;
  return swOffset;
}


SWORD CZLangFunction::TempVariableAllocator::AllocateTempPPortVariable(bool bReturnIndex = false)
{
  SWORD swOffset;
  if (_iFirstAvailablePPortVariable == _vectorPPortVariableOffsets.size())
  // 如果需要动态新增加temp variable
  {
    // 动态新增加temp pport variable指令
    InsertTempVariableInstruction(zvm::ZVM_construct | zvm::CchZVM_PPORT_TYPE_TAG);

    ++_uwTempVariableCount;
    // 2001/7/21: 改为只存贮temp variable index，然后要返回offset时再立即加上local variable count即可
    _vectorPPortVariableOffsets.push_back(_uwTempVariableCount);
    if (bReturnIndex)
    {
      swOffset = _uwTempVariableCount;
    }
    else
    {
      swOffset = _pciOwnerZLangFunction->_uwLocalVariableCount + _uwTempVariableCount;
    }
  }
  else
  // 直接利用已经被动态增加的temp variable
  {
    // 2001/7/21: 改为只存贮temp variable index，然后要返回offset时再立即加上local variable count即可
    if (bReturnIndex)
    {
      swOffset = _vectorPPortVariableOffsets[_iFirstAvailablePPortVariable];
    }
    else
    {
      swOffset = _pciOwnerZLangFunction->_uwLocalVariableCount +
                 _vectorPPortVariableOffsets[_iFirstAvailablePPortVariable];
    }
  }

  ++_iFirstAvailablePPortVariable;
  return swOffset;
}


SWORD CZLangFunction::TempVariableAllocator::AllocateTempTableVariable(char chTableElementTypeTag, bool bReturnIndex = false)
{
  SWORD swOffset;
  if (_iFirstAvailableTableVariable == _vectorTableVariableOffsets.size())
  // 如果需要动态新增加temp variable
  {
    // 动态新增加temp pport variable指令
    InsertTempVariableInstruction(zvm::ZVM_constructTable | chTableElementTypeTag);

    ++_uwTempVariableCount;
    // 2001/7/21: 改为只存贮temp variable index，然后要返回offset时再立即加上local variable count即可
    _vectorTableVariableOffsets.push_back(_uwTempVariableCount);
    if (bReturnIndex)
    {
      swOffset = _uwTempVariableCount;
    }
    else
    {
      swOffset = _pciOwnerZLangFunction->_uwLocalVariableCount + _uwTempVariableCount;
    }
  }
  else
  // 直接利用已经被动态增加的temp variable
  {
    // 2001/7/21: 改为只存贮temp variable index，然后要返回offset时再立即加上local variable count即可
    if (bReturnIndex)
    {
      swOffset = _vectorTableVariableOffsets[_iFirstAvailableTableVariable];
    }
    else
    {
      swOffset = _pciOwnerZLangFunction->_uwLocalVariableCount +
                 _vectorTableVariableOffsets[_iFirstAvailableTableVariable];
    }
  }

  ++_iFirstAvailableTableVariable;
  return swOffset;
}


/******************************************************************************
 * class CZLangFunction
 ******************************************************************************/
CZLangFunction::CZLangFunction()
  : _iFunctionReference(0),
    _uwParameterCount(0),
    _uwLocalVariableCount(0),
    _ciTempVariableAllocator(this)
{ }


void CZLangFunction::AppendStackVariableDebugInfo(zvm::TZVMIndex nIndex, SWORD iBPOffset)
{
  TStackVariableDebug tDebug(nIndex, iBPOffset);
  _dequeStackVariableDebugInfo.push_back(tDebug);
}


void CZLangFunction::DumpDetail() const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZLangFunction::DumpDetail()");
  std::cout << "  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
  std::cout << "    function reference: " << _iFunctionReference << std::endl;
  std::cout << "    parameter count: " << _uwParameterCount << std::endl;
  std::cout << "    local variable count: " << _uwLocalVariableCount << std::endl;
  std::cout << "    instructions: " << std::endl;

  for (zvm::TZVMIndex nIndex = 0; nIndex < _dequeInstructions.size(); ++nIndex)
  {
    std::cout << "      " << nIndex << ": " << std::flush;
    #ifndef NDEBUG
    try {
    #endif
      _dequeInstructions[nIndex].DumpDetail();
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


zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos, const CZLangFunction & rci)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("operator<<(zfc::CBinaryOutputFileStream &, const CZLangFunction &)");
  bos << rci._iFunctionReference << rci._uwParameterCount << rci._uwLocalVariableCount;

  bos << static_cast<zvm::TZVMIndex>(rci._dequeInstructions.size());
  for (zvm::TZVMIndex nIndex = 0; nIndex < rci._dequeInstructions.size(); ++nIndex)
  {
    #ifndef NDEBUG
    try {
    #endif
      bos << rci._dequeInstructions[nIndex];
    #ifndef NDEBUG
    }
    catch(zfc::EPanic & e)
    {
      std::string stringError = std::string("Write stopped at the ") + nIndex + " instruction";
      e.AppendWhat(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      throw;
    }
    #endif
  }

  bos << static_cast<zvm::TZVMIndex>(rci._dequeLineNumberDebugInfos.size());
  std::deque<CZLangFunction::TLineNumberDebug>::const_iterator it2;
  for (it2 = rci._dequeLineNumberDebugInfos.begin(); it2 != rci._dequeLineNumberDebugInfos.end(); ++it2)
  {
    bos << *it2;
  }

  bos << static_cast<zvm::TZVMIndex>(rci._dequeStackVariableDebugInfo.size());
  std::deque<CZLangFunction::TStackVariableDebug>::const_iterator it3;
  for (it3 = rci._dequeStackVariableDebugInfo.begin(); it3 != rci._dequeStackVariableDebugInfo.end(); ++it3)
  {
    bos << *it3;
  }

  return(bos);
}


zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos, const CZLangFunction::TStackVariableDebug & rt)
{
  bos << rt.iNameAndSignatureIndex << rt.iBPOffset;
  return(bos);
}


ZLS_END_NAMESPACE

