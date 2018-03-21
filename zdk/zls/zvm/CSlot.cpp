/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CSlot.cpp,v $
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


#include <zls/zvm/CSlot.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


#ifdef ENABLE_ZVM_DEBUG
void CSlot::SlotAssert(TSlotTag eAssertedTag,
                       const char * pszFileName,
                       const char * pszFuncName,
                       const int nLineNumber) const
{
  if (_eSlotTag != eAssertedTag)
  {
    std::string stringError = std::string("Assertion failed ! Slot expected tag is '") +
                              static_cast<UDWORD>(eAssertedTag) + "', but found tag '" +
                              static_cast<UDWORD>(_eSlotTag) + "'";
    throw zfc::EPanic(pszFileName, pszFuncName, nLineNumber, stringError);
  }
}


void CSlot::SlotMaskAssert(TSlotTag eAssertedTagMask,
                           const char * pszFileName,
                           const char * pszFuncName,
                           const int nLineNumber) const
{
  if (! (_eSlotTag & eAssertedTagMask))
  {
    std::string stringError = std::string("Assertion failed ! Slot expected tag mask is '") +
                              static_cast<UDWORD>(eAssertedTagMask) + "', but found tag '" +
                              static_cast<UDWORD>(_eSlotTag) + "'";
    throw zfc::EPanic(pszFileName, pszFuncName, nLineNumber, stringError);
  }
}
#endif


CSlot::~CSlot()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSlot::~CSlot()");

  switch (_eSlotTag)
  {
    case SLOT_TAG_VOID:
    case SLOT_TAG_BOOL:
    case SLOT_TAG_BYTE:
    case SLOT_TAG_SDWORD:
    case SLOT_TAG_UDWORD:
    case SLOT_TAG_SQWORD:
    case SLOT_TAG_UQWORD:
    case SLOT_TAG_DOUBLE:
      break;

    case SLOT_TAG_ADDRESS_OF_BOOL:
    case SLOT_TAG_ADDRESS_OF_BYTE:
    case SLOT_TAG_ADDRESS_OF_SDWORD:
    case SLOT_TAG_ADDRESS_OF_UDWORD:
    case SLOT_TAG_ADDRESS_OF_SQWORD:
    case SLOT_TAG_ADDRESS_OF_UQWORD:
    case SLOT_TAG_ADDRESS_OF_DOUBLE:
    case SLOT_TAG_ADDRESS_OF_STRING_OBJECT:
    case SLOT_TAG_ADDRESS_OF_ROPE_OBJECT:
    case SLOT_TAG_ADDRESS_OF_PPORT_OBJECT:
    case SLOT_TAG_ADDRESS_OF_IPv4ADDRESS_OBJECT:
    case SLOT_TAG_ADDRESS_OF_TABLE_OBJECT:
      _pvAddress = 0;
      break;

    case SLOT_TAG_BP_REGISTER:
      _pciBP = 0;
      break;

    case SLOT_TAG_PC_REGISTER:
      delete _pciPC;
      _pciPC = 0;
      break;

    case SLOT_TAG_STRING_OBJECT:
      delete _pciString;
      _pciString = 0;
      break;

    case SLOT_TAG_ROPE_OBJECT:
      delete _pciRope;
      _pciRope = 0;
      break;

    case SLOT_TAG_PPORT_OBJECT:
      delete _pciPPort;
      _pciPPort = 0;
      break;

    case SLOT_TAG_IPv4ADDRESS_OBJECT:
      delete _pciIPv4Address;
      _pciIPv4Address = 0;
      break;

    case SLOT_TAG_TABLE_OBJECT:
      delete _pciTable;
      _pciTable = 0;
      break;

    default:
      std::string stringError = std::string("Invalid slot tag '") + _eSlotTag + "'";
      throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      break;
  }
}


CSlot::CSlot(const CSlot & rciOther)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSlot::CSlot(const CSlot &)");
  _eSlotTag = rciOther._eSlotTag;
  switch (_eSlotTag)
  {
    case SLOT_TAG_BP_REGISTER:
      _pciBP = rciOther._pciBP;
      break;

    case SLOT_TAG_PC_REGISTER:
      _pciPC = new __OPTION(_THROW) CPCRegister(*(rciOther._pciPC));
      break;

    case SLOT_TAG_VOID:
      break;

    case SLOT_TAG_BOOL:
      _b = rciOther._b;
      break;

    case SLOT_TAG_BYTE:
      _uch = rciOther._uch;
      break;

    case SLOT_TAG_SDWORD:
      _sdw = rciOther._sdw;
      break;

    case SLOT_TAG_UDWORD:
      _udw = rciOther._udw;
      break;

    case SLOT_TAG_SQWORD:
      _sqw = rciOther._sqw;
      break;

    case SLOT_TAG_UQWORD:
      _uqw = rciOther._uqw;
      break;

    case SLOT_TAG_DOUBLE:
      _df = rciOther._df;
      break;

    case SLOT_TAG_STRING_OBJECT:
      _pciString = new __OPTION(_THROW) CZVMString(*(rciOther._pciString));
      break;

    case SLOT_TAG_ROPE_OBJECT:
      _pciRope = new __OPTION(_THROW) CZVMRope(*(rciOther._pciRope));
      break;

    case SLOT_TAG_PPORT_OBJECT:
      _pciPPort = new __OPTION(_THROW) CZVMPPort(*(rciOther._pciPPort));
      break;

    case SLOT_TAG_IPv4ADDRESS_OBJECT:
      _pciIPv4Address = new __OPTION(_THROW) CZVMIPv4Address(*(rciOther._pciIPv4Address));
      break;

    case SLOT_TAG_TABLE_OBJECT:
      _pciTable = new __OPTION(_THROW) CZVMTable(*_pciTable);
      break;

    case SLOT_TAG_ADDRESS_OF_BOOL:
    case SLOT_TAG_ADDRESS_OF_BYTE:
    case SLOT_TAG_ADDRESS_OF_SDWORD:
    case SLOT_TAG_ADDRESS_OF_UDWORD:
    case SLOT_TAG_ADDRESS_OF_SQWORD:
    case SLOT_TAG_ADDRESS_OF_UQWORD:
    case SLOT_TAG_ADDRESS_OF_DOUBLE:
    case SLOT_TAG_ADDRESS_OF_STRING_OBJECT:
    case SLOT_TAG_ADDRESS_OF_ROPE_OBJECT:
    case SLOT_TAG_ADDRESS_OF_PPORT_OBJECT:
    case SLOT_TAG_ADDRESS_OF_IPv4ADDRESS_OBJECT:
    case SLOT_TAG_ADDRESS_OF_TABLE_OBJECT:
      _pvAddress = _pvAddress;
      break;

    default:
      std::string stringError = std::string("Invalid slot tag '") + _eSlotTag + "'";
      throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      break;
  }
}


/*
CSlot & CSlot::operator=(const CSlot & rciOther)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSlot::operator=()");

  // 先调用Destructor进行析够构以前得内容
  this->~CSlot();

  _eSlotTag = rciOther._eSlotTag;
  switch (_eSlotTag)
  {
    case SLOT_TAG_BP_REGISTER:
      _pciBP = rciOther._pciBP;
      break;

    case SLOT_TAG_PC_REGISTER:
      _pciPC = new __OPTION(_THROW) CPCRegister(*(rciOther._pciPC));
      break;

    case SLOT_TAG_VOID:
      break;

    case SLOT_TAG_BOOL:
      _b = rciOther._b;
      break;

    case SLOT_TAG_BYTE:
      _uch = rciOther._uch;
      break;

    case SLOT_TAG_SDWORD:
      _sdw = rciOther._sdw;
      break;

    case SLOT_TAG_UDWORD:
      _udw = rciOther._udw;
      break;

    case SLOT_TAG_SQWORD:
      _sqw = rciOther._sqw;
      break;

    case SLOT_TAG_UQWORD:
      _uqw = rciOther._uqw;
      break;

    case SLOT_TAG_DOUBLE:
      _df = rciOther._df;
      break;

    case SLOT_TAG_STRING_OBJECT:
      _pciString = new __OPTION(_THROW) CZVMString(*(rciOther._pciString));
      break;

    case SLOT_TAG_ROPE_OBJECT:
      _pciRope = new __OPTION(_THROW) CZVMRope(*(rciOther._pciRope));
      break;

    case SLOT_TAG_PPORT_OBJECT:
      _pciPPort = new __OPTION(_THROW) CZVMPPort(*(rciOther._pciPPort));
      break;

    case SLOT_TAG_IPv4ADDRESS_OBJECT:
      _pciIPv4Address = new __OPTION(_THROW) CZVMIPv4Address(*(rciOther._pciIPv4Address));
      break;

    case SLOT_TAG_TABLE_OBJECT:
      _pciTable = new __OPTION(_THROW) CZVMTable(*_pciTable);
      break;

    case SLOT_TAG_ADDRESS_OF_BOOL:
    case SLOT_TAG_ADDRESS_OF_BYTE:
    case SLOT_TAG_ADDRESS_OF_SDWORD:
    case SLOT_TAG_ADDRESS_OF_UDWORD:
    case SLOT_TAG_ADDRESS_OF_SQWORD:
    case SLOT_TAG_ADDRESS_OF_UQWORD:
    case SLOT_TAG_ADDRESS_OF_DOUBLE:
    case SLOT_TAG_ADDRESS_OF_STRING_OBJECT:
    case SLOT_TAG_ADDRESS_OF_ROPE_OBJECT:
    case SLOT_TAG_ADDRESS_OF_PPORT_OBJECT:
    case SLOT_TAG_ADDRESS_OF_IPv4ADDRESS_OBJECT:
    case SLOT_TAG_ADDRESS_OF_TABLE_OBJECT:
      _pvAddress = _pvAddress;
      break;

    default:
      std::string stringError = std::string("Invalid slot tag '") + _eSlotTag + "'";
      throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      break;
  }
  return *this;
}
*/


bool CSlot::operator==(const CSlot & rciOther) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSlot::operator==()");

  if (this == &rciOther)
  {
    return true;
  }

  if (_eSlotTag != rciOther._eSlotTag)
  {
    return false;
  }

  bool bResult = false;
  switch (_eSlotTag)
  {
    case SLOT_TAG_BP_REGISTER:
      bResult = (_pciBP == rciOther._pciBP);
      break;

    case SLOT_TAG_PC_REGISTER:
      bResult = (*_pciPC == *(rciOther._pciPC));
      break;

    case SLOT_TAG_VOID:
      bResult = true;
      break;

    case SLOT_TAG_BOOL:
      bResult = (_b == rciOther._b);
      break;

    case SLOT_TAG_BYTE:
      bResult = (_uch == rciOther._uch);
      break;

    case SLOT_TAG_SDWORD:
      bResult = (_sdw == rciOther._sdw);
      break;

    case SLOT_TAG_UDWORD:
      bResult = (_udw == rciOther._udw);
      break;

    case SLOT_TAG_SQWORD:
      bResult = (_sqw == rciOther._sqw);
      break;

    case SLOT_TAG_UQWORD:
      bResult = (_uqw == rciOther._uqw);
      break;

    case SLOT_TAG_DOUBLE:
      bResult = (_df == rciOther._df);
      break;

    case SLOT_TAG_STRING_OBJECT:
      bResult = (*_pciString == *(rciOther._pciString));
      break;

    case SLOT_TAG_ROPE_OBJECT:
      bResult = (*_pciRope == *(rciOther._pciRope));
      break;

    case SLOT_TAG_PPORT_OBJECT:
      bResult = (*_pciPPort == *(rciOther._pciPPort));
      break;

    case SLOT_TAG_IPv4ADDRESS_OBJECT:
      bResult = (*_pciIPv4Address == *(rciOther._pciIPv4Address));
      break;

    case SLOT_TAG_TABLE_OBJECT:
      bResult = (*_pciTable == *(rciOther._pciTable));
      break;

    case SLOT_TAG_ADDRESS_OF_BOOL:
    case SLOT_TAG_ADDRESS_OF_BYTE:
    case SLOT_TAG_ADDRESS_OF_SDWORD:
    case SLOT_TAG_ADDRESS_OF_UDWORD:
    case SLOT_TAG_ADDRESS_OF_SQWORD:
    case SLOT_TAG_ADDRESS_OF_UQWORD:
    case SLOT_TAG_ADDRESS_OF_DOUBLE:
    case SLOT_TAG_ADDRESS_OF_STRING_OBJECT:
    case SLOT_TAG_ADDRESS_OF_ROPE_OBJECT:
    case SLOT_TAG_ADDRESS_OF_PPORT_OBJECT:
    case SLOT_TAG_ADDRESS_OF_IPv4ADDRESS_OBJECT:
    case SLOT_TAG_ADDRESS_OF_TABLE_OBJECT:
      bResult = (_pvAddress == _pvAddress);
      break;

    default:
      std::string stringError = std::string("Invalid slot tag '") + _eSlotTag + "'";
      throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      break;
  }
  return bResult;
}


void CSlot::ConstructSlotByTypeSignature(const std::string & rstringSignature)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSlot::ConstructSlotByTypeSignature()");

  switch (rstringSignature[0])
  {
    case CchZVM_BOOL_TYPE_TAG:
      ConstructSlotAsDefaultBool();
      break;

    case CchZVM_BYTE_TYPE_TAG:
      ConstructSlotAsDefaultByte();
      break;

    case CchZVM_SDWORD_TYPE_TAG:
      ConstructSlotAsDefaultSDWORD();
      break;

    case CchZVM_UDWORD_TYPE_TAG:
      ConstructSlotAsDefaultUDWORD();
      break;

    case CchZVM_SQWORD_TYPE_TAG:
      ConstructSlotAsDefaultSQWORD();
      break;

    case CchZVM_UQWORD_TYPE_TAG:
      ConstructSlotAsDefaultUQWORD();
      break;

    case CchZVM_DOUBLE_TYPE_TAG:
      ConstructSlotAsDefaultDouble();
      break;

    case CchZVM_STRING_TYPE_TAG:
      ConstructSlotAsDefaultStringObject();
      break;

    case CchZVM_ROPE_TYPE_TAG:
      ConstructSlotAsDefaultRopeObject();
      break;

    case CchZVM_PPORT_TYPE_TAG:
      ConstructSlotAsDefaultPPortObject();
      break;

    case CchZVM_IPv4ADDR_TYPE_TAG:
      ConstructSlotAsDefaultIPv4AddressObject();
      break;

    case CchZVM_TABLE_TYPE_TAG:
      ConstructSlotAsDefaultTableObject(rstringSignature[1]);
      break;

    default:
      std::string stringError = "Invalid type signature '" + rstringSignature + "'";
      throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      break;
  }
}


CSlot::TSlotTag CSlot::TypeSignatureToSlotTag(const std::string & rstringSignature)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSlot::TypeSignatureToSlotTag()");

  CSlot::TSlotTag eTag;
  switch (rstringSignature[0])
  {
    case CchZVM_VOID_TYPE_TAG:
      eTag = SLOT_TAG_VOID;
      break;

    case CchZVM_BOOL_TYPE_TAG:
      eTag = SLOT_TAG_BOOL;
      break;

    case CchZVM_BYTE_TYPE_TAG:
      eTag = SLOT_TAG_BYTE;
      break;

    case CchZVM_SDWORD_TYPE_TAG:
      eTag = SLOT_TAG_SDWORD;
      break;

    case CchZVM_UDWORD_TYPE_TAG:
      eTag = SLOT_TAG_UDWORD;
      break;

    case CchZVM_SQWORD_TYPE_TAG:
      eTag = SLOT_TAG_SQWORD;
      break;

    case CchZVM_UQWORD_TYPE_TAG:
      eTag = SLOT_TAG_UQWORD;
      break;

    case CchZVM_DOUBLE_TYPE_TAG:
      eTag = SLOT_TAG_DOUBLE;
      break;

    case CchZVM_STRING_TYPE_TAG:
      eTag = SLOT_TAG_STRING_OBJECT;
      break;

    case CchZVM_ROPE_TYPE_TAG:
      eTag = SLOT_TAG_ROPE_OBJECT;
      break;

    case CchZVM_PPORT_TYPE_TAG:
      eTag = SLOT_TAG_PPORT_OBJECT;
      break;

    case CchZVM_IPv4ADDR_TYPE_TAG:
      eTag = SLOT_TAG_IPv4ADDRESS_OBJECT;
      break;

    case CchZVM_TABLE_TYPE_TAG:
      if (islower(rstringSignature[1]))
      {
        eTag = SLOT_TAG_ADDRESS_OF_TABLE_OBJECT;
      }
      else
      {
        eTag = SLOT_TAG_TABLE_OBJECT;
      }
      break;

    default:
      if (islower(rstringSignature[0]))
      {
        switch (toupper(rstringSignature[0]))
        {
          case CchZVM_BOOL_TYPE_TAG:
            eTag = SLOT_TAG_ADDRESS_OF_BOOL;
            break;

          case CchZVM_BYTE_TYPE_TAG:
            eTag = SLOT_TAG_ADDRESS_OF_BYTE;
            break;

          case CchZVM_SDWORD_TYPE_TAG:
            eTag = SLOT_TAG_ADDRESS_OF_SDWORD;
            break;

          case CchZVM_UDWORD_TYPE_TAG:
            eTag = SLOT_TAG_ADDRESS_OF_UDWORD;
            break;

          case CchZVM_SQWORD_TYPE_TAG:
            eTag = SLOT_TAG_ADDRESS_OF_SQWORD;
            break;

          case CchZVM_UQWORD_TYPE_TAG:
            eTag = SLOT_TAG_ADDRESS_OF_UQWORD;
            break;

          case CchZVM_DOUBLE_TYPE_TAG:
            eTag = SLOT_TAG_ADDRESS_OF_DOUBLE;
            break;

          case CchZVM_STRING_TYPE_TAG:
            eTag = SLOT_TAG_ADDRESS_OF_STRING_OBJECT;
            break;

          case CchZVM_ROPE_TYPE_TAG:
            eTag = SLOT_TAG_ADDRESS_OF_ROPE_OBJECT;
            break;

          case CchZVM_PPORT_TYPE_TAG:
            eTag = SLOT_TAG_ADDRESS_OF_PPORT_OBJECT;
            break;

          case CchZVM_IPv4ADDR_TYPE_TAG:
            eTag = SLOT_TAG_ADDRESS_OF_IPv4ADDRESS_OBJECT;
            break;

          default:
            goto __LABEL_INVALID_SIGNATURE__;
            break;
        }
      }
      else
      {
        goto __LABEL_INVALID_SIGNATURE__;
      }
      break;
  }

  return eTag;

__LABEL_INVALID_SIGNATURE__:
  std::string stringError = "Invalid type signature '" + rstringSignature + "'";
  throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
  return eTag;  // Just for avoid warning
}


void CSlot::TypeSignatureToSlotTag(const std::vector<std::string> & rvectorSourceSignatures,
                                   std::vector<CSlot::TSlotTag> & rvectorToSlotTags)
{
  std::vector<std::string>::const_iterator it;
  for (it = rvectorSourceSignatures.begin(); it != rvectorSourceSignatures.end(); ++it)
  {
    CSlot::TSlotTag eTag = CSlot::TypeSignatureToSlotTag(*it);
    rvectorToSlotTags.push_back(eTag);
  }
}


ZLS_END_NAMESPACE

