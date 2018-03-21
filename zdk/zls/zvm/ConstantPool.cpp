/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/ConstantPool.cpp,v $
 *
 * $Date: 2001/11/14 18:29:37 $
 *
 * $Revision: 1.6 $
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


#include <zls/zvm/ConstantPool.hpp>
#include <zls/zvm/CSlot.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


/******************************************************************************
 * CNameAndSignatureReference
 ******************************************************************************/
void CNameAndSignatureReference::DumpDetail() const
{
  std::cout << "    name: '" << *_pstringName << "'" << std::endl;
  std::cout << "    signature: '" << *_pstringSignature << "'" << std::endl;
}


/******************************************************************************
 * CGlobalVariableReference
 ******************************************************************************/
CGlobalVariableReference::~CGlobalVariableReference()
{
  if (_eAccessModifierTag == zvm::PRIVATE_FOR_SELF_MODULE)
  {
    delete _pciVariableSlot;
  }
}


void CGlobalVariableReference::DumpDetail() const
{
  _pciNameAndSignatureReference->DumpDetail();
  std::cout << "    access modifier: " << _eAccessModifierTag << std::endl;
  //std::cout << "    relocated offset: " << _masRelocatedOffset << std::endl;
}


/******************************************************************************
 * CGlobalFunctionReference
 ******************************************************************************/
void CGlobalFunctionReference::DumpDetail() const
{
  _pciNameAndSignatureReference->DumpDetail();
  std::cout << "    access modifier: " << _eAccessModifierTag << std::endl;
}


/******************************************************************************
 * CConstantPoolSlot
 ******************************************************************************/
#ifdef ENABLE_ZVM_DEBUG
void CConstantPoolSlot::ConstantAssert(TConstantPoolElementTag eAssertedTag,
                                       const char * pszFileName,
                                       const char * pszFuncName,
                                       const int nLineNumber) const
{
  if (_eElementTag != eAssertedTag)
  {
    std::string stringError = "Assertion failed ! Constant expected tag is '" +
                              ConstantPoolElementTagToString(eAssertedTag) + "', but found tag '" +
                              ConstantPoolElementTagToString(_eElementTag) + "'";
    throw zfc::EPanic(pszFileName, pszFuncName, nLineNumber, stringError);
  }
}
#endif


CConstantPoolSlot::~CConstantPoolSlot()
{
  switch (_eElementTag)
  {
    case CONSTANT_POOL_ELEMENT_TAG_NIL_END_STRING:
      delete _pciNilEndStringLiteral;
      break;

    case CONSTANT_POOL_ELEMENT_TAG_BINARY_STRING:
      delete _pciBinaryStringLiteral;
      break;

    case CONSTANT_POOL_ELEMENT_TAG_ROPE_STRING:
      delete _pciRopeStringLiteral;
      break;

    case CONSTANT_POOL_ELEMENT_TAG_PROTOCOL_PORT:
      delete _pciPPortLiteral;
      break;

    case CONSTANT_POOL_ELEMENT_TAG_IPv4ADDRESS:
      delete _pciIPv4AddressLiteral;
      break;

    case CONSTANT_POOL_ELEMENT_TAG_NAME_AND_SIGNATURE_REFERENCE:
      delete _pciNameAndSignatureReference;
      break;

    case CONSTANT_POOL_ELEMENT_TAG_GLOBAL_VARIABLE_REFERENCE:
      delete _pciGlobalVariableReference;
      break;

    case CONSTANT_POOL_ELEMENT_TAG_GLOBAL_FUNCTION_REFERENCE:
      delete _pciGlobalFunctionReference;
      break;

    default:
      break;
  }
}


void CConstantPoolSlot::DumpDetail() const
{
  switch (_eElementTag)
  {
    case CONSTANT_POOL_ELEMENT_TAG_SQWORD:
      std::cout << "    literal: " << zfc::SQWORDToString(_sqwLiteral, 10) << std::endl;
      break;

    case CONSTANT_POOL_ELEMENT_TAG_UQWORD:
      std::cout << "    literal: " << zfc::UQWORDToString(_uqwLiteral, 10) << std::endl;
      break;

    case CONSTANT_POOL_ELEMENT_TAG_IPv4ADDRESS:
      std::cout << "    literal: " << *_pciIPv4AddressLiteral << std::endl;
      break;

    case CONSTANT_POOL_ELEMENT_TAG_PROTOCOL_PORT:
      std::cout << "    literal: " << *_pciPPortLiteral << std::endl;
      break;

    case CONSTANT_POOL_ELEMENT_TAG_DOUBLE:
      std::cout << "    literal: " << _dfLiteral << std::endl;
      break;

    case CONSTANT_POOL_ELEMENT_TAG_NIL_END_STRING:
      std::cout << "    literal: " << *_pciNilEndStringLiteral << std::endl;
      break;

    case CONSTANT_POOL_ELEMENT_TAG_BINARY_STRING:
      std::cout << "    literal: " << *_pciBinaryStringLiteral << std::endl;
      break;

    case CONSTANT_POOL_ELEMENT_TAG_ROPE_STRING:
      std::cout << "    literal: " << *_pciRopeStringLiteral << std::endl;
      break;

    case CONSTANT_POOL_ELEMENT_TAG_NAME_AND_SIGNATURE_REFERENCE:
      _pciNameAndSignatureReference->DumpDetail();
      break;

    case CONSTANT_POOL_ELEMENT_TAG_GLOBAL_VARIABLE_REFERENCE:
      _pciGlobalVariableReference->DumpDetail();
      break;

    case CONSTANT_POOL_ELEMENT_TAG_GLOBAL_FUNCTION_REFERENCE:
      _pciGlobalFunctionReference->DumpDetail();
      break;

    default:
      break;
  }
}


/******************************************************************************
 * CConstantPool
 ******************************************************************************/
void CConstantPool::DumpDetail() const
{
  std::cout << "Begin of constant pool: " << std::endl;
  for (TZVMIndex nIndex = 0; nIndex < _nSlotCapacity; ++nIndex)
  {
    TConstantPoolElementTag eElementTag = _aciSlots[nIndex].GetElementTag();
    std::cout << "  " << nIndex << ": " << ConstantPoolElementTagToString(eElementTag) << std::endl;
    _aciSlots[nIndex].DumpDetail();
  }
  std::cout << "End of constant pool." << std::endl << std::endl;
}


const CConstantPoolSlot * CConstantPool::GetSlotAt(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetSlotAt()");

  if (nIndex < 0 || nIndex >= _nSlotCapacity)
  {
    throw zfc::EOutOfRange(__FILE__, __PRETTY_FUNC__ , __LINE__,
                                    "Slot index", nIndex, 0, _nSlotCapacity - 1);
  }
  return &(_aciSlots[nIndex]);
}


const zvm::CNameAndSignatureReference * CConstantPool::GetAsNameAndSignatureReference(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetAsNameAndSignatureReference()");

  #ifdef ENABLE_ZVM_DEBUG
  const CConstantPoolSlot * pciSlot = GetSlotAt(nIndex);
  ZVM_CONSTANT_ASSERT(pciSlot, CONSTANT_POOL_ELEMENT_TAG_NAME_AND_SIGNATURE_REFERENCE,
                      __FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  const CConstantPoolSlot * pciSlot = operator[](nIndex);
  #endif
  const zvm::CNameAndSignatureReference * pciReference = pciSlot->GetAsNameAndSignatureReference();
  return pciReference;
}


const zvm::CGlobalVariableReference * CConstantPool::GetAsGlobalVariableReference(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetAsGlobalVariableReference()");

  #ifdef ENABLE_ZVM_DEBUG
  const CConstantPoolSlot * pciSlot = GetSlotAt(nIndex);
  ZVM_CONSTANT_ASSERT(pciSlot, CONSTANT_POOL_ELEMENT_TAG_GLOBAL_VARIABLE_REFERENCE,
                      __FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  const CConstantPoolSlot * pciSlot = operator[](nIndex);
  #endif
  const zvm::CGlobalVariableReference * pciReference = pciSlot->GetAsGlobalVariableReference();
  return pciReference;
}


const zvm::CGlobalFunctionReference * CConstantPool::GetAsGlobalFunctionReference(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetAsGlobalFunctionReference()");

  #ifdef ENABLE_ZVM_DEBUG
  const CConstantPoolSlot * pciSlot = GetSlotAt(nIndex);
  ZVM_CONSTANT_ASSERT(pciSlot, CONSTANT_POOL_ELEMENT_TAG_GLOBAL_FUNCTION_REFERENCE,
                      __FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  const CConstantPoolSlot * pciSlot = operator[](nIndex);
  #endif
  const zvm::CGlobalFunctionReference * pciReference = pciSlot->GetAsGlobalFunctionReference();
  return pciReference;
}


SQWORD CConstantPool::GetAsSQWORD(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetAsSQWORD()");

  #ifdef ENABLE_ZVM_DEBUG
  const CConstantPoolSlot * pciSlot = GetSlotAt(nIndex);
  ZVM_CONSTANT_ASSERT(pciSlot, CONSTANT_POOL_ELEMENT_TAG_SQWORD,
                      __FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  const CConstantPoolSlot * pciSlot = operator[](nIndex);
  #endif
  SQWORD sqw = pciSlot->GetAsSQWORD();
  return sqw;
}


UQWORD CConstantPool::GetAsUQWORD(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetAsUQWORD()");

  #ifdef ENABLE_ZVM_DEBUG
  const CConstantPoolSlot * pciSlot = GetSlotAt(nIndex);
  ZVM_CONSTANT_ASSERT(pciSlot, CONSTANT_POOL_ELEMENT_TAG_UQWORD,
                      __FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  const CConstantPoolSlot * pciSlot = operator[](nIndex);
  #endif
  UQWORD uqw = pciSlot->GetAsUQWORD();
  return uqw;
}


double CConstantPool::GetAsDouble(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetAsDouble()");

  #ifdef ENABLE_ZVM_DEBUG
  const CConstantPoolSlot * pciSlot = GetSlotAt(nIndex);
  ZVM_CONSTANT_ASSERT(pciSlot, CONSTANT_POOL_ELEMENT_TAG_DOUBLE,
                      __FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  const CConstantPoolSlot * pciSlot = operator[](nIndex);
  #endif
  double df = pciSlot->GetAsDouble();
  return df;
}


const std::string * CConstantPool::GetAsNilEndString(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetAsNilEndString()");

  #ifdef ENABLE_ZVM_DEBUG
  const CConstantPoolSlot * pciSlot = GetSlotAt(nIndex);
  ZVM_CONSTANT_ASSERT(pciSlot, CONSTANT_POOL_ELEMENT_TAG_NIL_END_STRING,
                      __FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  const CConstantPoolSlot * pciSlot = operator[](nIndex);
  #endif
  return pciSlot->GetAsNilEndString();
}


const CZVMString * CConstantPool::GetAsBinaryString(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetAsBinaryString()");

  #ifdef ENABLE_ZVM_DEBUG
  const CConstantPoolSlot * pciSlot = GetSlotAt(nIndex);
  ZVM_CONSTANT_ASSERT(pciSlot, CONSTANT_POOL_ELEMENT_TAG_BINARY_STRING,
                      __FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  const CConstantPoolSlot * pciSlot = operator[](nIndex);
  #endif
  return pciSlot->GetAsBinaryString();
}


const CZVMRope * CConstantPool::GetAsRopeString(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetAsRopeString()");

  #ifdef ENABLE_ZVM_DEBUG
  const CConstantPoolSlot * pciSlot = GetSlotAt(nIndex);
  ZVM_CONSTANT_ASSERT(pciSlot, CONSTANT_POOL_ELEMENT_TAG_ROPE_STRING,
                      __FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  const CConstantPoolSlot * pciSlot = operator[](nIndex);
  #endif
  return pciSlot->GetAsRopeString();
}


const CZVMPPort * CConstantPool::GetAsPPort(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetAsPPort()");

  #ifdef ENABLE_ZVM_DEBUG
  const CConstantPoolSlot * pciSlot = GetSlotAt(nIndex);
  ZVM_CONSTANT_ASSERT(pciSlot, CONSTANT_POOL_ELEMENT_TAG_PROTOCOL_PORT,
                      __FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  const CConstantPoolSlot * pciSlot = operator[](nIndex);
  #endif
  return pciSlot->GetAsPPort();
}


const CZVMIPv4Address * CConstantPool::GetAsIPv4Address(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetAsIPv4Address()");

  #ifdef ENABLE_ZVM_DEBUG
  const CConstantPoolSlot * pciSlot = GetSlotAt(nIndex);
  ZVM_CONSTANT_ASSERT(pciSlot, CONSTANT_POOL_ELEMENT_TAG_IPv4ADDRESS,
                      __FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  const CConstantPoolSlot * pciSlot = operator[](nIndex);
  #endif
  return pciSlot->GetAsIPv4Address();
}


const std::string * const * CConstantPool::GetAsPointerOfNilEndStringPointer(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetAsPointerOfNilEndStringPointer()");

  #ifdef ENABLE_ZVM_DEBUG
  const CConstantPoolSlot * pciSlot = GetSlotAt(nIndex);
  ZVM_CONSTANT_ASSERT(pciSlot, CONSTANT_POOL_ELEMENT_TAG_NIL_END_STRING,
                      __FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  const CConstantPoolSlot * pciSlot = operator[](nIndex);
  #endif
  return pciSlot->GetAsPointerOfNilEndStringPointer();
}


const CZVMString * const * CConstantPool::GetAsPointerOfBinaryStringPointer(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetAsPointerOfBinaryStringPointer()");

  #ifdef ENABLE_ZVM_DEBUG
  const CConstantPoolSlot * pciSlot = GetSlotAt(nIndex);
  ZVM_CONSTANT_ASSERT(pciSlot, CONSTANT_POOL_ELEMENT_TAG_BINARY_STRING,
                      __FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  const CConstantPoolSlot * pciSlot = operator[](nIndex);
  #endif
  return pciSlot->GetAsPointerOfBinaryStringPointer();
}


const CZVMRope * const * CConstantPool::GetAsPointerOfRopeStringPointer(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetAsPointerOfRopeStringPointer()");

  #ifdef ENABLE_ZVM_DEBUG
  const CConstantPoolSlot * pciSlot = GetSlotAt(nIndex);
  ZVM_CONSTANT_ASSERT(pciSlot, CONSTANT_POOL_ELEMENT_TAG_ROPE_STRING,
                      __FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  const CConstantPoolSlot * pciSlot = operator[](nIndex);
  #endif
  return pciSlot->GetAsPointerOfRopeStringPointer();
}


const CZVMPPort * const * CConstantPool::GetAsPointerOfPPortPointer(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetAsPointerOfPPortPointer()");

  #ifdef ENABLE_ZVM_DEBUG
  const CConstantPoolSlot * pciSlot = GetSlotAt(nIndex);
  ZVM_CONSTANT_ASSERT(pciSlot, CONSTANT_POOL_ELEMENT_TAG_PROTOCOL_PORT,
                      __FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  const CConstantPoolSlot * pciSlot = operator[](nIndex);
  #endif
  return pciSlot->GetAsPointerOfPPortPointer();
}


const CZVMIPv4Address * const * CConstantPool::GetAsPointerOfIPv4AddressPointer(TZVMIndex nIndex) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::GetAsPointerOfIPv4AddressPointer()");

  #ifdef ENABLE_ZVM_DEBUG
  const CConstantPoolSlot * pciSlot = GetSlotAt(nIndex);
  ZVM_CONSTANT_ASSERT(pciSlot, CONSTANT_POOL_ELEMENT_TAG_IPv4ADDRESS,
                      __FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  const CConstantPoolSlot * pciSlot = operator[](nIndex);
  #endif
  return pciSlot->GetAsPointerOfIPv4AddressPointer();
}


zfc::CBinaryInputFileStream & operator >> (zfc::CBinaryInputFileStream & bis, zvm::CConstantPool & rciPool)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("operator >> (zfc::CBinaryInputFileStream &, const zvm::CConstantPool &)");
  std::string stringError;

  // read 'count of elements in constant pool'
  TZVMIndex nCapacity;
  bis >> nCapacity;

  rciPool._nSlotCapacity = nCapacity;
  rciPool._aciSlots = new __OPTION(_THROW) CConstantPoolSlot[nCapacity];
  // zero constant pool
  memset(rciPool._aciSlots, '\0', sizeof(CConstantPoolSlot) * nCapacity);

  // read 'elements'
  CConstantPoolSlot * pciPosition = rciPool._aciSlots;
  for (TZVMIndex nIndex = 0; nIndex < nCapacity; ++nIndex, ++pciPosition)
  {
    UWORD eElementTag;
    // read 'element tag'
    bis >> eElementTag;

    // read 'element content'
    switch (eElementTag)
    {
      case CONSTANT_POOL_ELEMENT_TAG_SQWORD:
        {
          // read
          SQWORD sqw;
          bis >> sqw;
          // 在正确的address上调用正确的Constructor
          CConstantPoolSlot * pciElement = new (pciPosition) CConstantPoolSlot(sqw);
        }
        break;

      case CONSTANT_POOL_ELEMENT_TAG_UQWORD:
        {
          // read
          UQWORD uqw;
          bis >> uqw;
          // 在正确的address上调用正确的Constructor
          CConstantPoolSlot * pciElement = new (pciPosition) CConstantPoolSlot(uqw);
        }
        break;

      case CONSTANT_POOL_ELEMENT_TAG_IPv4ADDRESS:
        {
          // read 'length of ipv4 address string'
          UDWORD udwLength;  // 在ZVM中规定'ipv4 address string'的最大长度为UDWORD
          bis >> udwLength;

          // read 'content of ipv4 address string'
          std::string stringIPv4Address;
          char * pBuffer = new __OPTION(_THROW) char[udwLength];
          try {
            bis.read(pBuffer, udwLength);
            stringIPv4Address.append(pBuffer, udwLength);
            delete [] pBuffer;
          }
          catch(...)
          {
            delete [] pBuffer;
            throw;
          }

          // read 'CIDR mask'
          NUDWORD nudwCIDRMask;
          bis >> nudwCIDRMask;

          // Now may resolve DNS
          CZVMIPv4Address * pci =
                new __OPTION(_THROW) CZVMIPv4Address(stringIPv4Address.c_str(), nudwCIDRMask);
          if (! pci->GetAddress().IsValidIPv4Address())  // 如果DNS解析失败
          {
            delete pci;
            stringError = std::string("Constant pool: The ") + nIndex +
                          " slot: Unresolved IPv4 address literal '" + stringIPv4Address + "'";
            throw zvm::EInvalidObjectFile(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
          }

          // 在正确的address上调用正确的Constructor
          CConstantPoolSlot * pciElement = new (pciPosition) CConstantPoolSlot(pci);
        }
        break;

      case CONSTANT_POOL_ELEMENT_TAG_PROTOCOL_PORT:
        {
          // read 'protocol type' and 'port number'
          UWORD uwProtocolType;
          PPORT nPortNumber;
          bis >> uwProtocolType >> nPortNumber;

          CZVMPPort * pci = new __OPTION(_THROW) CZVMPPort(uwProtocolType, nPortNumber);

          // 在正确的address上调用正确的Constructor
          CConstantPoolSlot * pciElement = new (pciPosition) CConstantPoolSlot(pci);
        }
        break;

      case CONSTANT_POOL_ELEMENT_TAG_DOUBLE:
        {
          // read
          double df;
          bis >> df;
          // 在正确的address上调用正确的Constructor
          CConstantPoolSlot * pciElement = new (pciPosition) CConstantPoolSlot(df);
        }
        break;

      case CONSTANT_POOL_ELEMENT_TAG_NIL_END_STRING:
        {
          // read 'string length'
          UDWORD udwLength;  // 在ZVM中规定nil end string的最大长度为UDWORD
          bis >> udwLength;

          // read 'string content'
          std::string * pstring = new __OPTION(_THROW) std::string;
          char * pBuffer = new __OPTION(_THROW) char[udwLength];
          try {
            bis.read(pBuffer, udwLength);
            pstring->assign(pBuffer, udwLength);
            delete [] pBuffer;
          }
          catch(...)
          {
            delete [] pBuffer;
            delete pstring;
            throw;
          }

          // 在正确的address上调用正确的Constructor
          CConstantPoolSlot * pciElement = new (pciPosition) CConstantPoolSlot(pstring);
        }
        break;

      case CONSTANT_POOL_ELEMENT_TAG_BINARY_STRING:
        {
          // read 'string length'
          UDWORD udwLength;  // 在ZVM中规定binary string的最大长度为UDWORD
          bis >> udwLength;

          // read 'string content'
          CZVMString * pci = new __OPTION(_THROW) CZVMString;
          char * pBuffer = new __OPTION(_THROW) char[udwLength];
          try {
            bis.read(pBuffer, udwLength);
            #ifdef USE_std_string_AS_ZVM_STRING
            pci->append(pBuffer, udwLength);
            #else
            pci->append(reinterpret_cast<const UCHAR *>(pBuffer), udwLength);
            #endif
            delete [] pBuffer;
          }
          catch(...)
          {
            delete [] pBuffer;
            delete pci;
            throw;
          }

          // 在正确的address上调用正确的Constructor
          #ifdef USE_std_string_AS_ZVM_STRING
          CConstantPoolSlot * pciElement = new (pciPosition) CConstantPoolSlot(pci, 1);
          #else
          CConstantPoolSlot * pciElement = new (pciPosition) CConstantPoolSlot(pci);
          #endif
        }
        break;

      case CONSTANT_POOL_ELEMENT_TAG_ROPE_STRING:
        {
          // read 'string length'
          UDWORD udwLength;  // 在ZVM中规定rope string的最大长度为UDWORD
          bis >> udwLength;

          // read 'string content'
          CZVMRope * pci = new __OPTION(_THROW) CZVMRope;
          char * pBuffer = new __OPTION(_THROW) char[udwLength];
          try {
            bis.read(pBuffer, udwLength);
            //pci->append(pBuffer, udwLength);
            pci->append(reinterpret_cast<const UCHAR *>(pBuffer), udwLength);
            delete [] pBuffer;
          }
          catch(...)
          {
            delete [] pBuffer;
            delete pci;
            throw;
          }

          // 在正确的address上调用正确的Constructor
          CConstantPoolSlot * pciElement = new (pciPosition) CConstantPoolSlot(pci);
        }
        break;

      case CONSTANT_POOL_ELEMENT_TAG_NAME_AND_SIGNATURE_REFERENCE:
        {
          // read
          TZVMIndex nNameIndex;
          TZVMIndex nSignatureIndex;
          bis >> nNameIndex >> nSignatureIndex;

          ///> 立即解析name and signature string
          if (nNameIndex >= nIndex || nSignatureIndex >= nIndex)
          {
            stringError = std::string("Constant pool: The ") + nIndex +
                          " slot: Bad 'name and signature reference': Invalid 'name'=" +
                          nNameIndex + " or 'signature'=" + nSignatureIndex;
            throw zvm::EInvalidObjectFile(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
          }

          CConstantPoolSlot * pciNameSlot = rciPool._aciSlots + nNameIndex;
          if (pciNameSlot->GetElementTag() != CONSTANT_POOL_ELEMENT_TAG_NIL_END_STRING)
          {
            stringError = std::string("Constant pool: The ") + nIndex +
                          " slot: Bad 'name and signature reference': 'name'=" +
                          nNameIndex + " is not a 'nil-end string'";
            throw zvm::EInvalidObjectFile(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
          }

          CConstantPoolSlot * pciSignatureSlot = rciPool._aciSlots + nSignatureIndex;
          if (pciSignatureSlot->GetElementTag() != CONSTANT_POOL_ELEMENT_TAG_NIL_END_STRING)
          {
            stringError = std::string("Constant pool: The ") + nIndex +
                          " slot: Bad 'name and signature reference': 'signature'=" +
                          nSignatureIndex + " is not a 'nil-end string'";
            throw zvm::EInvalidObjectFile(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
          }

          // new一个zvm::CNameAndSignatureReference
          zvm::CNameAndSignatureReference * pci = new __OPTION(_THROW)
                zvm::CNameAndSignatureReference(pciNameSlot->GetAsNilEndString(),
                                                pciSignatureSlot->GetAsNilEndString());

          // 在正确的address上调用正确的Constructor
          CConstantPoolSlot * pciElement = new (pciPosition) CConstantPoolSlot(pci);
        }
        break;

      case CONSTANT_POOL_ELEMENT_TAG_GLOBAL_VARIABLE_REFERENCE:
        {
          // read
          UCHAR uchAccessModifierTag;  // 为了portable，enum是采用UCHAR存贮的.
          TZVMIndex nNameAndSignatureIndex;
          bis >> uchAccessModifierTag >> nNameAndSignatureIndex;

          ///> 立即解析name and signature reference
          if (nNameAndSignatureIndex >= nIndex)
          {
            stringError = std::string("Constant pool: The ") + nIndex +
                          " slot: Bad 'global variable reference': Invalid 'name and signature'=" +
                          nNameAndSignatureIndex;
            throw zvm::EInvalidObjectFile(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
          }

          CConstantPoolSlot * pciNameAndSignatureSlot = rciPool._aciSlots + nNameAndSignatureIndex;
          if (pciNameAndSignatureSlot->GetElementTag() != CONSTANT_POOL_ELEMENT_TAG_NAME_AND_SIGNATURE_REFERENCE)
          {
            stringError = std::string("Constant pool: The ") + nIndex +
                          " slot: Bad 'global variable reference': 'name and signature reference'=" +
                          nNameAndSignatureIndex + " is not a 'name and signature reference'";
            throw zvm::EInvalidObjectFile(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
          }

          // new一个zvm::CGlobalVariableReference
          zvm::CGlobalVariableReference * pci = new __OPTION(_THROW)
                zvm::CGlobalVariableReference(pciNameAndSignatureSlot->GetAsNameAndSignatureReference(),
                                              static_cast<TAccessModifierTag>(uchAccessModifierTag));

          // 在正确的address上调用正确的Constructor
          CConstantPoolSlot * pciElement = new (pciPosition) CConstantPoolSlot(pci);
        }
        break;

      case CONSTANT_POOL_ELEMENT_TAG_GLOBAL_FUNCTION_REFERENCE:
        {
          // read
          UCHAR uchAccessModifierTag;  // 为了portable，enum是采用UCHAR存贮的.
          TZVMIndex nNameAndSignatureIndex;
          bis >> uchAccessModifierTag >> nNameAndSignatureIndex;

          ///> 立即解析name and signature reference
          if (nNameAndSignatureIndex >= nIndex)
          {
            stringError = std::string("Constant pool: The ") + nIndex +
                          " slot: Bad 'global function reference': Invalid 'name and signature reference'=" +
                          nNameAndSignatureIndex;
            throw zvm::EInvalidObjectFile(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
          }

          CConstantPoolSlot * pciNameAndSignatureSlot = rciPool._aciSlots + nNameAndSignatureIndex;
          if (pciNameAndSignatureSlot->GetElementTag() != CONSTANT_POOL_ELEMENT_TAG_NAME_AND_SIGNATURE_REFERENCE)
          {
            stringError = std::string("Constant pool: The ") + nIndex +
                          " slot: Bad 'global function reference': 'name and signature reference'=" +
                          nNameAndSignatureIndex + " is not a 'name and signature reference'";
            throw zvm::EInvalidObjectFile(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
          }

          // new一个zvm::CGlobalFunctionReference
          zvm::CGlobalFunctionReference * pci = new __OPTION(_THROW)
                zvm::CGlobalFunctionReference(pciNameAndSignatureSlot->GetAsNameAndSignatureReference(),
                                              static_cast<TAccessModifierTag>(uchAccessModifierTag));

          // 在正确的address上调用正确的Constructor
          CConstantPoolSlot * pciElement = new (pciPosition) CConstantPoolSlot(pci);
        }
        break;

      default:
        stringError = std::string("Constant pool: The ") + nIndex + " slot: Invalid element tag '" + eElementTag + "'";
        throw zvm::EInvalidObjectFile(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
        break;
    }
  }

  return(bis);
}


ZLS_END_NAMESPACE

