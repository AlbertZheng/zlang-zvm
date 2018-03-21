/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CInstruction.cpp,v $
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


#include <zls/zvm/CInstruction.hpp>
#include <zls/zvm/CInstructionDictionary.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


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

    case sizeof(UCHAR):
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

    case sizeof(UWORD):
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


void CInstruction::DumpDetail() const
{
  std::cout << ToString() << std::endl;
}


void CInstruction::VerifyByteCodesIntegrity(const CConstantPool & rciConstantPool,
                                            TZVMIndex iMyselfInstructionIndex,
                                            TZVMIndex iLastInstructionIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CInstruction::VerifyByteCodesIntegrity()");
  std::string stringError;

  // 判断指令码的低字节合法否
  UCHAR uchLowByteOfICode = _nInstructionCode & 0x00ff;
  if (islower(uchLowByteOfICode) ||
      uchLowByteOfICode < MIN_LOW_BYTE_OF_INSTRUCTION_CODE ||
      uchLowByteOfICode > MAX_LOW_BYTE_OF_INSTRUCTION_CODE)
  {
    stringError = "Found a invalid instruction code '0x" + zfc::UWORDToString(_nInstructionCode, 16) +
                  "' with incorrect low-byte '" + std::string(1, uchLowByteOfICode) + "'";
    throw zvm::EVerifyFailure(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
  }

  // Seek字典
  const zvm::CInstructionDictionary::TInstructionDictionaryEntry * pciEntry =
        zvm::GciInstructionDictionaryFactory.GetSingleton()->SeekInstructionDictionary(_nInstructionCode);
  if (pciEntry)
  {
    // 检查操作数的字节数目是否正确
    if (_nOperandByteCount != pciEntry->nOperandByteCount)
    {
      // 既然pciEntry能够查找成功，那么ToString()一定不会抛出exception的
      stringError = "Found a mismatched 'operand byte count' instruction '" + ToString() + "'";
      throw zvm::EVerifyFailure(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
    }

    switch(pciEntry->eOperandType)
    {
      // 检查Constant pool index匹配否
      case zvm::CInstructionDictionary::OPERAND_IS_CONSTANT_POOL_INDEX:
        {
          const CConstantPoolSlot * pciSlot = rciConstantPool.GetSlotAt(_udwOperand);
          TConstantPoolElementTag eConstantTag = pciSlot->GetElementTag();

          if (! (eConstantTag & pciEntry->uwMaskOfConstantPoolElementTag))
          // 如果实际的Tag不符合Dictionary中要求的
          {
            // 既然pciEntry能够查找成功，那么ToString()一定不会抛出exception的
            stringError = "Found a mismatched 'constant pool index' of instruction '" + ToString() + "'";
            throw zvm::EVerifyFailure(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
          }
        }
        break;

      // 检查Code label合法否
      case zvm::CInstructionDictionary::OPERAND_IS_ZVM_CODE_LABEL:
        {
          TZVMIndex iGotoLabel = iMyselfInstructionIndex + static_cast<TZVMIndex>(_udwOperand);
          if (iGotoLabel < 0 || iGotoLabel > iLastInstructionIndex)
          {
            stringError = "Found a instruction '" + ToString() + "' which will run out of code range";
            throw zvm::EVerifyFailure(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
          }
        }
        break;

      default:
        break;
    }

    #if defined(ENABLE_ZVM_OPTIMIZATION)
    // 现在立即Patch指令Interpreter
    const_cast<CInstruction *>(this)->_pfuncInterpreter = pciEntry->pfuncInterpreter;
    #endif
  }
  else
  {
    try {
      stringError = "Found a incorrect instruction '" + InstructionCodeToString(_nInstructionCode) + "'";
    }
    catch (zfc::EInvalidArgument & e)
    {
      stringError = "Found a invalid instruction code '0x" + zfc::UWORDToString(_nInstructionCode, 16) + "'";
    }
    throw zvm::EVerifyFailure(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
  }
}


zfc::CBinaryInputFileStream & operator>>(zfc::CBinaryInputFileStream & bis, CInstruction & rci)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("operator>>(zfc::CBinaryInputFileStream &,CInstruction &)");

  bis >> rci._nInstructionCode >> rci._nOperandByteCount;

  switch (rci._nOperandByteCount)
  {
    case 0:
      break;

    case sizeof(UCHAR):
      bis >> rci._uchOperand;
      break;

    case sizeof(UWORD):
      bis >> rci._uwOperand;
      break;

    case sizeof(UDWORD):
      bis >> rci._udwOperand;
      break;

    default:
      std::string stringError = std::string("Invalid operand byte count -> ") + rci._nOperandByteCount;
      throw zvm::EInvalidObjectFile(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      break;
  }

  return bis;
}


ZLS_END_NAMESPACE

