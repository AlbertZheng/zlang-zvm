/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/ConstantPool.cpp,v $
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


#include <zls/zlang/ConstantPool.hpp>


// Begin namespace 'zlang::'
ZLS_BEGIN_NAMESPACE(zlang)


/*******************************************************************************
 * class CConstantPoolElement
 ******************************************************************************/
void CConstantPoolElement::DumpDetail() const
{
  std::cout << "  " << _nSelfIndex << ": " << zvm::ConstantPoolElementTagToString(_eElementTag) << std::endl;
}


/*******************************************************************************
 * class CNilEndStringLiteral
 ******************************************************************************/
bool CNilEndStringLiteral::operator==(const CConstantPoolElement & rci) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CNilEndStringLiteral::operator==()");

  try {
    const CNilEndStringLiteral & rciRight = dynamic_cast<const CNilEndStringLiteral &>(rci);
    return(this->_stringLiteral == rciRight.GetLiteral());
  }
  catch (std::bad_cast & e)
  {
    throw zfc::EBadDynamicCast(__FILE__, __PRETTY_FUNC__ , __LINE__, e.what());
  }
}


void CNilEndStringLiteral::DumpDetail() const
{
  CConstantPoolElement::DumpDetail();
  std::cout << "    literal: " << _stringLiteral << std::endl;
}


zfc::CBinaryOutputFileStream & operator << (zfc::CBinaryOutputFileStream & bos, const CNilEndStringLiteral & rci)
{
  /* write length */
  // 在ZVM中规定CNilEndString的最大长度为UDWORD
  UDWORD udwLength = rci._stringLiteral.size();
  bos << udwLength;

  /* write content */
  bos.write(rci._stringLiteral.c_str(), udwLength);

  return(bos);
}


/*******************************************************************************
 * class CBinaryStringLiteral
 ******************************************************************************/
bool CBinaryStringLiteral::operator==(const CConstantPoolElement & rci) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CBinaryStringLiteral::operator==()");

  try {
    const CBinaryStringLiteral & rciRight = dynamic_cast<const CBinaryStringLiteral &>(rci);
    return(this->_bstringLiteral == rciRight.GetLiteral());
  }
  catch (std::bad_cast & e)
  {
    throw zfc::EBadDynamicCast(__FILE__, __PRETTY_FUNC__ , __LINE__, e.what());
  }
}


void CBinaryStringLiteral::DumpDetail() const
{
  CConstantPoolElement::DumpDetail();
//  std::cout << "    literal: " << _bstringLiteral << std::endl;
  std::cout << "    literal: size:" << _bstringLiteral.size() << " , value: " << _bstringLiteral << std::endl;
}


zfc::CBinaryOutputFileStream & operator << (zfc::CBinaryOutputFileStream & bos, const CBinaryStringLiteral & rci)
{
  /* write length */
  // 在ZVM中规定CBinaryString的最大长度为UDWORD
  UDWORD udwLength = rci._bstringLiteral.size();
  bos << udwLength;

  /* write content */
  bos.write(reinterpret_cast<const char *>(rci._bstringLiteral.c_str()), udwLength);

  return(bos);
}


/*******************************************************************************
 * class CRopeStringLiteral
 ******************************************************************************/
bool CRopeStringLiteral::operator==(const CConstantPoolElement & rci) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CRopeStringLiteral::operator==()");

  try {
    const CRopeStringLiteral & rciRight = dynamic_cast<const CRopeStringLiteral &>(rci);
    return(this->_ropeLiteral == rciRight.GetLiteral());
  }
  catch (std::bad_cast & e)
  {
    throw zfc::EBadDynamicCast(__FILE__, __PRETTY_FUNC__ , __LINE__, e.what());
  }
}


void CRopeStringLiteral::DumpDetail() const
{
  CConstantPoolElement::DumpDetail();
//  std::cout << "    literal: " << _ropeLiteral << std::endl;
  std::cout << "    literal: size:" << _ropeLiteral.size() << " , value: " << _ropeLiteral << std::endl;
}


zfc::CBinaryOutputFileStream & operator << (zfc::CBinaryOutputFileStream & bos, const CRopeStringLiteral & rci)
{
  /* write length */
  // 在ZVM中规定CRopeString的最大长度为UDWORD
  UDWORD udwLength = rci._ropeLiteral.size();
  bos << udwLength;

  /* write content */
  bos.write(reinterpret_cast<const char *>(rci._ropeLiteral.c_str()), udwLength);

  return(bos);
}


/*******************************************************************************
 * class CSDWORDLiteral
 ******************************************************************************/
/*
bool CSDWORDLiteral::operator==(const CConstantPoolElement & rci) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSDWORDLiteral::operator==()");

  try {
    const CSDWORDLiteral & rciRight = dynamic_cast<const CSDWORDLiteral &>(rci);
    return(this->_sdwLiteral == rciRight.GetLiteral());
  }
  catch (std::bad_cast & e)
  {
    throw zfc::EBadDynamicCast(__FILE__, __PRETTY_FUNC__ , __LINE__, e.what());
  }
}


void CSDWORDLiteral::DumpDetail() const
{
  CConstantPoolElement::DumpDetail();
  std::cout << "    literal: " << _sdwLiteral << std::endl;
}


zfc::CBinaryOutputFileStream & operator << (zfc::CBinaryOutputFileStream & bos, const CSDWORDLiteral & rci)
{
  bos << rci._sdwLiteral;

  return(bos);
}
*/


/*******************************************************************************
 * class CUDWORDLiteral
 ******************************************************************************/
/*
bool CUDWORDLiteral::operator==(const CConstantPoolElement & rci) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CUDWORDLiteral::operator==()");

  try {
    const CUDWORDLiteral & rciRight = dynamic_cast<const CUDWORDLiteral &>(rci);
    return(this->_udwLiteral == rciRight.GetLiteral());
  }
  catch (std::bad_cast & e)
  {
    throw zfc::EBadDynamicCast(__FILE__, __PRETTY_FUNC__ , __LINE__, e.what());
  }
}


void CUDWORDLiteral::DumpDetail() const
{
  CConstantPoolElement::DumpDetail();
  std::cout << "    literal: " << _udwLiteral << std::endl;
}


zfc::CBinaryOutputFileStream & operator << (zfc::CBinaryOutputFileStream & bos, const CUDWORDLiteral & rci)
{
  bos << rci._udwLiteral;

  return(bos);
}
*/


/*******************************************************************************
 * class CSQWORDLiteral
 ******************************************************************************/
bool CSQWORDLiteral::operator==(const CConstantPoolElement & rci) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSQWORDLiteral::operator==()");

  try {
    const CSQWORDLiteral & rciRight = dynamic_cast<const CSQWORDLiteral &>(rci);
    return(this->_sqwLiteral == rciRight.GetLiteral());
  }
  catch (std::bad_cast & e)
  {
    throw zfc::EBadDynamicCast(__FILE__, __PRETTY_FUNC__ , __LINE__, e.what());
  }
}


void CSQWORDLiteral::DumpDetail() const
{
  CConstantPoolElement::DumpDetail();
  std::cout << "    literal: " << zfc::SQWORDToString(_sqwLiteral, 10) << std::endl;
}


zfc::CBinaryOutputFileStream & operator << (zfc::CBinaryOutputFileStream & bos, const CSQWORDLiteral & rci)
{
  bos << rci._sqwLiteral;

  return(bos);
}


/*******************************************************************************
 * class CUQWORDLiteral
 ******************************************************************************/
bool CUQWORDLiteral::operator==(const CConstantPoolElement & rci) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CUQWORDLiteral::operator==()");

  try {
    const CUQWORDLiteral & rciRight = dynamic_cast<const CUQWORDLiteral &>(rci);
    return(this->_uqwLiteral == rciRight.GetLiteral());
  }
  catch (std::bad_cast & e)
  {
    throw zfc::EBadDynamicCast(__FILE__, __PRETTY_FUNC__ , __LINE__, e.what());
  }
}


void CUQWORDLiteral::DumpDetail() const
{
  CConstantPoolElement::DumpDetail();
  std::cout << "    literal: " << zfc::UQWORDToString(_uqwLiteral, 10) << std::endl;
}


zfc::CBinaryOutputFileStream & operator << (zfc::CBinaryOutputFileStream & bos, const CUQWORDLiteral & rci)
{
  bos << rci._uqwLiteral;

  return(bos);
}


/*******************************************************************************
 * class CDoubleLiteral
 ******************************************************************************/
bool CDoubleLiteral::operator==(const CConstantPoolElement & rci) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CDoubleLiteral::operator==()");

  try {
    const CDoubleLiteral & rciRight = dynamic_cast<const CDoubleLiteral &>(rci);
    return(this->_dfLiteral == rciRight.GetLiteral());
  }
  catch (std::bad_cast & e)
  {
    throw zfc::EBadDynamicCast(__FILE__, __PRETTY_FUNC__ , __LINE__, e.what());
  }
}


void CDoubleLiteral::DumpDetail() const
{
  CConstantPoolElement::DumpDetail();
  std::cout << "    literal: " << _dfLiteral << std::endl;
}


zfc::CBinaryOutputFileStream & operator << (zfc::CBinaryOutputFileStream & bos, const CDoubleLiteral & rci)
{
  bos << rci._dfLiteral;

  return(bos);
}


/*******************************************************************************
 * class CPPortLiteral
 ******************************************************************************/
bool CPPortLiteral::operator==(const CConstantPoolElement & rci) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CPPortLiteral::operator==()");

  try {
    const CPPortLiteral & rciRight = dynamic_cast<const CPPortLiteral &>(rci);
    return(this->_ciLiteral == rciRight.GetLiteral());
  }
  catch (std::bad_cast & e)
  {
    throw zfc::EBadDynamicCast(__FILE__, __PRETTY_FUNC__ , __LINE__, e.what());
  }
}


void CPPortLiteral::DumpDetail() const
{
  CConstantPoolElement::DumpDetail();
  std::cout << "    literal: " << _ciLiteral << std::endl;
}


zfc::CBinaryOutputFileStream & operator << (zfc::CBinaryOutputFileStream & bos, const CPPortLiteral & rci)
{
  bos << rci._ciLiteral.GetProtocolType() << rci._ciLiteral.GetPortNumber();
  return(bos);
}


/*******************************************************************************
 * class CUnresolvedIPv4AddressLiteral
 ******************************************************************************/
bool CUnresolvedIPv4AddressLiteral::operator==(const CConstantPoolElement & rci) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CUnresolvedIPv4AddressLiteral::operator==()");

  try {
    const CUnresolvedIPv4AddressLiteral & rciRight = dynamic_cast<const CUnresolvedIPv4AddressLiteral &>(rci);
    return(this->_stringIPv4Address == rciRight._stringIPv4Address &&
           this->_nudwCIDRMask == rciRight._nudwCIDRMask);
  }
  catch (std::bad_cast & e)
  {
    throw zfc::EBadDynamicCast(__FILE__, __PRETTY_FUNC__ , __LINE__, e.what());
  }
}


void CUnresolvedIPv4AddressLiteral::DumpDetail() const
{
  CConstantPoolElement::DumpDetail();
  std::cout << "    literal: " << _stringIPv4Address << "/" << zfc::IPv4AddressToString(_nudwCIDRMask) << std::endl;
}


zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos, const CUnresolvedIPv4AddressLiteral & rci)
{
  UDWORD udwLength = rci._stringIPv4Address.size();
  // write length of ipv4 address string
  bos << udwLength;
  // write content of ipv4 address string
  bos.write(rci._stringIPv4Address.c_str(), udwLength);
  // write CIDR mask
  bos << rci._nudwCIDRMask;

  return(bos);
}


/*******************************************************************************
 * class CNameAndSignatureReference
 ******************************************************************************/
bool CNameAndSignatureReference::operator==(const CConstantPoolElement & rci) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CNameAndSignatureReference::operator==()");

  try {
    const CNameAndSignatureReference & rciRight = dynamic_cast<const CNameAndSignatureReference &>(rci);
    return (this->_nNameIndex == rciRight.GetNameIndex() &&
            this->_nSignatureIndex == rciRight.GetSignatureIndex());
  }
  catch (std::bad_cast & e)
  {
    throw zfc::EBadDynamicCast(__FILE__, __PRETTY_FUNC__ , __LINE__, e.what());
  }
}


void CNameAndSignatureReference::DumpDetail() const
{
  CConstantPoolElement::DumpDetail();
  std::cout << "    name reference: " << _nNameIndex
            << " , signature reference: " << _nSignatureIndex << std::endl;
}


zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos, const CNameAndSignatureReference & rci)
{
  bos << rci._nNameIndex << rci._nSignatureIndex;

  return(bos);
}


/*******************************************************************************
 * class CGlobalVariableReference
 ******************************************************************************/
bool CGlobalVariableReference::operator==(const CConstantPoolElement & rci) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CGlobalVariableReference::operator==()");

  try {
    const CGlobalVariableReference & rciRight = dynamic_cast<const CGlobalVariableReference &>(rci);
    return (this->_eAccessModifierTag == rciRight._eAccessModifierTag &&
            this->_nNameAndSignatureIndex == rciRight._nNameAndSignatureIndex);
  }
  catch (std::bad_cast & e)
  {
    throw zfc::EBadDynamicCast(__FILE__, __PRETTY_FUNC__ , __LINE__, e.what());
  }
}


void CGlobalVariableReference::DumpDetail() const
{
  CConstantPoolElement::DumpDetail();
  std::cout << "    global variable name and signature reference: " << _nNameAndSignatureIndex
            << " , global access modifier: " << _eAccessModifierTag << std::endl;
}


zfc::CBinaryOutputFileStream & operator << (zfc::CBinaryOutputFileStream & bos, const CGlobalVariableReference & rci)
{
  bos << static_cast<UCHAR>(rci._eAccessModifierTag)
      << rci._nNameAndSignatureIndex;

  return(bos);
}


/*******************************************************************************
 * class CGlobalFunctionReference
 ******************************************************************************/
bool CGlobalFunctionReference::operator==(const CConstantPoolElement & rci) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CGlobalFunctionReference::operator==()");

  try {
    const CGlobalFunctionReference & rciRight = dynamic_cast<const CGlobalFunctionReference &>(rci);
    return (this->_eAccessModifierTag == rciRight._eAccessModifierTag &&
            this->_nNameAndSignatureIndex == rciRight._nNameAndSignatureIndex);
  }
  catch (std::bad_cast & e)
  {
    throw zfc::EBadDynamicCast(__FILE__, __PRETTY_FUNC__ , __LINE__, e.what());
  }
}


void CGlobalFunctionReference::DumpDetail() const
{
  CConstantPoolElement::DumpDetail();
  std::cout << "    global function name and signature reference: " << _nNameAndSignatureIndex
            << " , global access modifier: " << _eAccessModifierTag << std::endl;
}


zfc::CBinaryOutputFileStream & operator << (zfc::CBinaryOutputFileStream & bos, const CGlobalFunctionReference & rci)
{
  bos << static_cast<UCHAR>(rci._eAccessModifierTag)
      << rci._nNameAndSignatureIndex;

  return(bos);
}


/*******************************************************************************
 * class CConstantPool
 ******************************************************************************/
zvm::TZVMIndex CConstantPool::InsertNilEndStringLiteral(const std::string & rstring)
{
  CConstantPoolElement_auto autoElement = new __OPTION(_THROW) CNilEndStringLiteral(rstring);
  return(Insert(autoElement));
}


zvm::TZVMIndex CConstantPool::InsertBinaryStringLiteral(const std::string & rstring)
{
  //zvm::CZVMString bstringLiteral = rstring.c_str();
  // 2001/5/11: 采用提供size的constructor，因为binary string literal中允许包含\0'
  zvm::CZVMString bstringLiteral(rstring.c_str(), rstring.size());
  CConstantPoolElement_auto autoElement = new __OPTION(_THROW) CBinaryStringLiteral(bstringLiteral);
  return(Insert(autoElement));
}


zvm::TZVMIndex CConstantPool::InsertRopeStringLiteral(const std::string & rstring)
{
  // 采用提供size的constructor，因为rope string literal中允许包含\0'
  zvm::CZVMRope ropeLiteral(rstring.c_str(), rstring.size());
  CConstantPoolElement_auto autoElement = new __OPTION(_THROW) CRopeStringLiteral(ropeLiteral);
  return(Insert(autoElement));
}


/*
zvm::TZVMIndex CConstantPool::InsertUDWORDLiteral(const std::string & rstringText, int nBase)
{
  #if SIZEOF_LONG == 4
  UDWORD udw = strtoul(rstringText.c_str(), (char **)0, nBase);
  #else
  unsigned long ul = strtoul(rstringText.c_str(), (char **)0, nBase);
  UDWORD udw = (UDWORD)ul;
  #endif

  CConstantPoolElement_auto autoElement = new __OPTION(_THROW) CUDWORDLiteral(udw);
  return(Insert(autoElement));
}


zvm::TZVMIndex CConstantPool::InsertSDWORDLiteral(const std::string & rstringText, int nBase)
{
  #if SIZEOF_LONG == 4
  SDWORD sdw = strtol(rstringText.c_str(), (char **)0, nBase);
  #else
  long l = strtol(rstringText.c_str(), (char **)0, nBase);
  SDWORD sdw = (SDWORD)l;
  #endif

  CConstantPoolElement_auto autoElement = new __OPTION(_THROW) CSDWORDLiteral(sdw);
  return(Insert(autoElement));
}
*/


zvm::TZVMIndex CConstantPool::InsertSQWORDLiteral(const std::string & rstringText, int nBase)
{
//std::cerr << rstringText << std::endl;
  SQWORD sqw = strtoll(rstringText.c_str(), (char **)0, nBase);
//std::cerr << zfc::SQWORDToString(sqw, 10) << std::endl;

  CConstantPoolElement_auto autoElement = new __OPTION(_THROW) CSQWORDLiteral(sqw);
  return(Insert(autoElement));
}


zvm::TZVMIndex CConstantPool::InsertUQWORDLiteral(const std::string & rstringText, int nBase)
{
//std::cerr << rstringText << std::endl;
  UQWORD uqw = strtoull(rstringText.c_str(), (char **)0, nBase);
//std::cerr << zfc::UQWORDToString(uqw, 10) << std::endl;

  CConstantPoolElement_auto autoElement = new __OPTION(_THROW) CUQWORDLiteral(uqw);
  return(Insert(autoElement));
}


zvm::TZVMIndex CConstantPool::InsertDoubleLiteral(const std::string & rstringText)
{
  double df = strtod(rstringText.c_str(), (char **)0);
//std::cerr << "double literal: " << zfc::DoubleToString(df) << std::endl;
  CConstantPoolElement_auto autoElement = new __OPTION(_THROW) CDoubleLiteral(df);
  return(Insert(autoElement));
}


zvm::TZVMIndex CConstantPool::InsertPPortLiteral(const std::string & rstringText)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CConstantPool::InsertPPortLiteral");

  std::string::size_type nPosition = rstringText.find('/', 0);

  LogAssert0(nPosition != std::string::npos, "Impossible mistake: Please checking ZLang compiler");

  std::string stringPort = rstringText.substr(0, nPosition);
  std::string stringProtocol = rstringText.substr(nPosition+1);
  PPORT uwPort = (PPORT)strtol(stringPort.c_str(), (char **)0, 10);
  UWORD uwProtocol;
  if (stringProtocol == "TCP" || stringProtocol == "tcp")
  {
    uwProtocol = IPPROTO_TCP;
  }
  else
  {
    uwProtocol = IPPROTO_UDP;
  }

  CConstantPoolElement_auto autoElement = new __OPTION(_THROW) CPPortLiteral(uwProtocol, uwPort);
  return(Insert(autoElement));
}


zvm::TZVMIndex CConstantPool::InsertIPv4AddressLiteral(const std::string & rstringText)
{
  static const char * __PRETTY_FUNC__ = "CConstantPool::InsertIPv4AddressLiteral()";
  std::string::size_type nPosition = rstringText.find('/', 0);
  CConstantPoolElement_auto autoElement;

  if (nPosition == std::string::npos)
  // 如果Literal没有Network mask
  {
    autoElement = new __OPTION(_THROW) CUnresolvedIPv4AddressLiteral(rstringText);
  }
  else
  {
    std::string stringNetworkAddress = rstringText.substr(0, nPosition);
    std::string stringNetworkMask = rstringText.substr(nPosition+1);

    // 'char *' to 'long'
    long lMaskBits = strtol(stringNetworkMask.c_str(), (char **)0, 10);
    // 'long' to CIDR mask
    NUDWORD nudwCIDRMask = 0xffffffff;
    int lShift = 32 - lMaskBits;
    if(lShift < 0 || lShift > 31)
    {
      throw zfc::EOutOfRange(__FILE__, __PRETTY_FUNC__, __LINE__,
                             "Invalid CDIR mask-bits", lMaskBits, 1, 32);
    }
    nudwCIDRMask = htonl(nudwCIDRMask << lShift);

    autoElement = new __OPTION(_THROW) CUnresolvedIPv4AddressLiteral(stringNetworkAddress,
                                                                     nudwCIDRMask);
  }

  return(Insert(autoElement));
}


zvm::TZVMIndex CConstantPool::InsertNameAndSignatureReference(const std::string & rstringName,
                                                         const std::string & rstringSignature)
{
  zvm::TZVMIndex nNameIndex = InsertNilEndStringLiteral(rstringName);
  zvm::TZVMIndex nSignatureIndex = InsertNilEndStringLiteral(rstringSignature);
  CConstantPoolElement_auto autoElement = new __OPTION(_THROW)
                        CNameAndSignatureReference(nNameIndex, nSignatureIndex);
  return(Insert(autoElement));
}


zvm::TZVMIndex CConstantPool::InsertGlobalVariableReference(
                                        const std::string & rstringName,
                                        const std::string & rstringSignature,
                                        zvm::TAccessModifierTag eAccessTag)
{
  zvm::TZVMIndex nNameAndSignatureIndex = InsertNameAndSignatureReference(rstringName, rstringSignature);
  CConstantPoolElement_auto autoElement = new __OPTION(_THROW)
                                          CGlobalVariableReference(nNameAndSignatureIndex,
                                                                   eAccessTag);
  return(Insert(autoElement));
}


zvm::TZVMIndex CConstantPool::InsertGlobalFunctionReference(
                                        const std::string & rstringFunctionName,
                                        const std::string & rstringFunctionSignature,
                                        zvm::TAccessModifierTag eAccessTag)
{
  /* 插入function的name-and-signature-reference */
  zvm::TZVMIndex nNameAndSignatureIndex = InsertNameAndSignatureReference(
                                                      rstringFunctionName,
                                                      rstringFunctionSignature);
  CConstantPoolElement_auto autoElement = new __OPTION(_THROW)
                                          CGlobalFunctionReference(nNameAndSignatureIndex,
                                                                   eAccessTag);
  return(Insert(autoElement));
}


zvm::TZVMIndex CConstantPool::Insert(CConstantPoolElement_auto & rautoElement)
{
  if ((rautoElement->_nSelfIndex = Find(rautoElement)) == -1)
  // 如果constant pool中还没有这样的constant.
  {
    _dequePool.push_back(rautoElement);
    rautoElement->_nSelfIndex = _dequePool.size() - 1;
  }
  return(rautoElement->_nSelfIndex);
}


zvm::TZVMIndex CConstantPool::Find(const CConstantPoolElement_auto & rautoElement)
{
  zvm::TZVMIndex nIndex = 0;
  std::deque<CConstantPoolElement_auto>::iterator it;
  for (it = _dequePool.begin(); it != _dequePool.end(); ++it, ++nIndex)
  {
      // 相同类型才能比较，否则会在operator==()的dynamic_cast处core dump
    if ((*it)->GetElementTag() == rautoElement->GetElementTag() && *(*it) == *rautoElement)
    {
      return(nIndex);
    }
  }
  return(-1);
}


void CConstantPool::DumpDetail() const
{
  std::cout << "Begin of constant pool: " << std::endl;
  std::deque<CConstantPoolElement_auto>::const_iterator it;
  for (it = _dequePool.begin(); it != _dequePool.end(); ++it)
  {
    (*it)->DumpDetail();
  }
  std::cout << "End of constant pool." << std::endl << std::endl;
}


zfc::CBinaryOutputFileStream & operator << (zfc::CBinaryOutputFileStream & bos, const CConstantPool & rciPool)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("operator << (zfc::CBinaryOutputFileStream &, const CConstantPool &)");

  // write count of elements in constant pool
  bos << (zvm::TZVMIndex)(rciPool._dequePool.size());  // 强制为zvm::TZVMIndex，因为size_t可能为不可移植的.

  /* write elements */
  std::deque<CConstantPoolElement_auto>::const_iterator it;
  for (it = rciPool._dequePool.begin(); it != rciPool._dequePool.end(); ++it)
  {
    const CConstantPoolElement * pciElement = (*it).get();

    zvm::TConstantPoolElementTag eTag = pciElement->GetElementTag();
    // write tag，按UWORD写
    bos << static_cast<UWORD>(eTag);

    switch (eTag)
    {
      case zvm::CONSTANT_POOL_ELEMENT_TAG_SQWORD:
        {
          const CSQWORDLiteral * pci = dynamic_cast<const CSQWORDLiteral *>(pciElement);
          bos << *pci;
        }
        break;

      case zvm::CONSTANT_POOL_ELEMENT_TAG_UQWORD:
        {
          const CUQWORDLiteral * pci = dynamic_cast<const CUQWORDLiteral *>(pciElement);
          bos << *pci;
        }
        break;

      case zvm::CONSTANT_POOL_ELEMENT_TAG_DOUBLE:
        {
          const CDoubleLiteral * pci = dynamic_cast<const CDoubleLiteral *>(pciElement);
          bos << *pci;
        }
        break;

      case zvm::CONSTANT_POOL_ELEMENT_TAG_IPv4ADDRESS:
        {
          const CUnresolvedIPv4AddressLiteral * pci = dynamic_cast<const CUnresolvedIPv4AddressLiteral *>(pciElement);
          bos << *pci;
        }
        break;

      case zvm::CONSTANT_POOL_ELEMENT_TAG_PROTOCOL_PORT:
        {
          const CPPortLiteral * pci = dynamic_cast<const CPPortLiteral *>(pciElement);
          bos << *pci;
        }
        break;

      case zvm::CONSTANT_POOL_ELEMENT_TAG_NIL_END_STRING:
        {
          const CNilEndStringLiteral * pci = dynamic_cast<const CNilEndStringLiteral *>(pciElement);
          bos << *pci;
        }
        break;

      case zvm::CONSTANT_POOL_ELEMENT_TAG_BINARY_STRING:
        {
          const CBinaryStringLiteral * pci = dynamic_cast<const CBinaryStringLiteral *>(pciElement);
          bos << *pci;
        }
        break;

      case zvm::CONSTANT_POOL_ELEMENT_TAG_ROPE_STRING:
        {
          const CRopeStringLiteral * pci = dynamic_cast<const CRopeStringLiteral *>(pciElement);
          bos << *pci;
        }
        break;

      case zvm::CONSTANT_POOL_ELEMENT_TAG_NAME_AND_SIGNATURE_REFERENCE:
        {
          const CNameAndSignatureReference * pci = dynamic_cast<const CNameAndSignatureReference *>(pciElement);
          bos << *pci;
        }
        break;

      case zvm::CONSTANT_POOL_ELEMENT_TAG_GLOBAL_VARIABLE_REFERENCE:
        {
          const CGlobalVariableReference * pci = dynamic_cast<const CGlobalVariableReference *>(pciElement);
          bos << *pci;
        }
        break;

      case zvm::CONSTANT_POOL_ELEMENT_TAG_GLOBAL_FUNCTION_REFERENCE:
        {
          const CGlobalFunctionReference * pci = dynamic_cast<const CGlobalFunctionReference *>(pciElement);
          bos << *pci;
        }
        break;

      default:
        std::string stringError = std::string("Unexpected tag '") + eTag + "' of constant pool element";
        throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
        break;
    }
  }

  return(bos);
}


ZLS_END_NAMESPACE

