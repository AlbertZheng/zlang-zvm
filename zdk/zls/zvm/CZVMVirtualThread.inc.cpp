/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CZVMVirtualThread.inc.cpp,v $
 *
 * $Date: 2001/08/11 18:54:42 $
 *
 * $Revision: 1.2 $
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


#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CSlot * CZVMVirtualThread::GetStackVariableSlot()
{
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  SWORD nOffset = pciInstruction->GetOperandAsSWORD();
  CSlot * pciSlot = _pciBPRegister + nOffset;
  return pciSlot;
}


/******************************************************************************
 * POP Value
 ******************************************************************************/
#ifdef ENABLE_ZVM_DEBUG
#define POP_BOOL(pszFile, pszFunc, nLine)       PopBool(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
bool CZVMVirtualThread::PopBool(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_BOOL(pszFile, pszFunc, nLine)       PopBool()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
bool CZVMVirtualThread::PopBool()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BOOL, pszFileName, pszFuncName, nLineNumber);
  return pciSlot->GetBool();
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_BYTE(pszFile, pszFunc, nLine)       PopByte(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UCHAR CZVMVirtualThread::PopByte(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_BYTE(pszFile, pszFunc, nLine)       PopByte()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UCHAR CZVMVirtualThread::PopByte()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BYTE, pszFileName, pszFuncName, nLineNumber);
  return pciSlot->GetByte();
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_SDWORD(pszFile, pszFunc, nLine)       PopSDWORD(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
SDWORD CZVMVirtualThread::PopSDWORD(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_SDWORD(pszFile, pszFunc, nLine)       PopSDWORD()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
SDWORD CZVMVirtualThread::PopSDWORD()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SDWORD, pszFileName, pszFuncName, nLineNumber);
  return pciSlot->GetSDWORD();
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_UDWORD(pszFile, pszFunc, nLine)       PopUDWORD(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UDWORD CZVMVirtualThread::PopUDWORD(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_UDWORD(pszFile, pszFunc, nLine)       PopUDWORD()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UDWORD CZVMVirtualThread::PopUDWORD()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UDWORD, pszFileName, pszFuncName, nLineNumber);
  return pciSlot->GetUDWORD();
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_SQWORD(pszFile, pszFunc, nLine)       PopSQWORD(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
SQWORD CZVMVirtualThread::PopSQWORD(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_SQWORD(pszFile, pszFunc, nLine)       PopSQWORD()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
SQWORD CZVMVirtualThread::PopSQWORD()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SQWORD, pszFileName, pszFuncName, nLineNumber);
  return pciSlot->GetSQWORD();
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_UQWORD(pszFile, pszFunc, nLine)       PopUQWORD(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UQWORD CZVMVirtualThread::PopUQWORD(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_UQWORD(pszFile, pszFunc, nLine)       PopUQWORD()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UQWORD CZVMVirtualThread::PopUQWORD()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UQWORD, pszFileName, pszFuncName, nLineNumber);
  return pciSlot->GetUQWORD();
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_DOUBLE(pszFile, pszFunc, nLine)       PopDouble(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
double CZVMVirtualThread::PopDouble(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_DOUBLE(pszFile, pszFunc, nLine)       PopDouble()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
double CZVMVirtualThread::PopDouble()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_DOUBLE, pszFileName, pszFuncName, nLineNumber);
  return pciSlot->GetDouble();
}


/**
 * 不进行内存析构的Pop string object.
 * @attention 用于"convertStringValueToAddress"指令.
 */
/*
 * 注：2001/7/17由于"convertStringValueToAddress"等指令被Discarded了!
 *
#ifdef ENABLE_ZVM_DEBUG
#define QUICK_POP_STRING_OBJECT(pszFile, pszFunc, nLine)        QuickPopStringObject(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMString * CZVMVirtualThread::QuickPopStringObject(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define QUICK_POP_STRING_OBJECT(pszFile, pszFunc, nLine)        QuickPopStringObject()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMString * CZVMVirtualThread::QuickPopStringObject()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_STRING_OBJECT, pszFileName, pszFuncName, nLineNumber);
  return pciSlot->GetStringObject();
}
 */


/**
 * 不进行内存析构的Pop ipv4address object.
 * @attention 用于"convertIPv4AddressValueToAddress"指令.
 */
/*
 * 注：2001/7/17由于"convertStringValueToAddress"等指令被Discarded了!
 *
#ifdef ENABLE_ZVM_DEBUG
#define QUICK_POP_IPv4ADDRESS_OBJECT(pszFile, pszFunc, nLine)   QuickPopIPv4AddressObject(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMIPv4Address * CZVMVirtualThread::QuickPopIPv4AddressObject(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define QUICK_POP_IPv4ADDRESS_OBJECT(pszFile, pszFunc, nLine)   QuickPopIPv4AddressObject()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMIPv4Address * CZVMVirtualThread::QuickPopIPv4AddressObject()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_IPv4ADDRESS_OBJECT, pszFileName, pszFuncName, nLineNumber);
  return pciSlot->GetIPv4AddressObject();
}
 */


/**
 * 不进行内存析构的Pop pport object.
 * @attention 用于"convertPPortValueToAddress"指令.
 */
/*
 * 注：2001/7/17由于"convertStringValueToAddress"等指令被Discarded了!
 *
#ifdef ENABLE_ZVM_DEBUG
#define QUICK_POP_PPORT_OBJECT(pszFile, pszFunc, nLine) QuickPopPPortObject(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMPPort * CZVMVirtualThread::QuickPopPPortObject(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define QUICK_POP_PPORT_OBJECT(pszFile, pszFunc, nLine) QuickPopPPortObject()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMPPort * CZVMVirtualThread::QuickPopPPortObject()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_PPORT_OBJECT, pszFileName, pszFuncName, nLineNumber);
  return pciSlot->GetPPortObject();
}
 */


/**
 * 不进行内存析构的Pop table object.
 * @attention 用于"convertTableValueToAddress"指令.
 */
/*
 * 注：2001/7/17由于"convertStringValueToAddress"等指令被Discarded了!
 *
#ifdef ENABLE_ZVM_DEBUG
#define QUICK_POP_TABLE_OBJECT(pszFile, pszFunc, nLine) QuickPopTableObject(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMTable * CZVMVirtualThread::QuickPopTableObject(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define QUICK_POP_TABLE_OBJECT(pszFile, pszFunc, nLine) QuickPopTableObject()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMTable * CZVMVirtualThread::QuickPopTableObject()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_TABLE_OBJECT, pszFileName, pszFuncName, nLineNumber);
  return pciSlot->GetTableObject();
}
 */


/******************************************************************************
 * POP Address
 ******************************************************************************/
#ifdef ENABLE_ZVM_DEBUG
#define POP_BOOL_ADDRESS(pszFile, pszFunc, nLine)      PopBoolAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
bool * CZVMVirtualThread::PopBoolAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_BOOL_ADDRESS(pszFile, pszFunc, nLine)      PopBoolAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
bool * CZVMVirtualThread::PopBoolAddress()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_BOOL, pszFileName, pszFuncName, nLineNumber);
  return static_cast<bool *>(pciSlot->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_BYTE_ADDRESS(pszFile, pszFunc, nLine)      PopByteAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UCHAR * CZVMVirtualThread::PopByteAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_BYTE_ADDRESS(pszFile, pszFunc, nLine)      PopByteAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UCHAR * CZVMVirtualThread::PopByteAddress()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_BYTE, pszFileName, pszFuncName, nLineNumber);
  return static_cast<UCHAR *>(pciSlot->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_SDWORD_ADDRESS(pszFile, pszFunc, nLine)      PopSDWORDAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
SDWORD * CZVMVirtualThread::PopSDWORDAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_SDWORD_ADDRESS(pszFile, pszFunc, nLine)      PopSDWORDAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
SDWORD * CZVMVirtualThread::PopSDWORDAddress()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_SDWORD, pszFileName, pszFuncName, nLineNumber);
  return static_cast<SDWORD *>(pciSlot->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_UDWORD_ADDRESS(pszFile, pszFunc, nLine)      PopUDWORDAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UDWORD * CZVMVirtualThread::PopUDWORDAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_UDWORD_ADDRESS(pszFile, pszFunc, nLine)      PopUDWORDAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UDWORD * CZVMVirtualThread::PopUDWORDAddress()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_UDWORD, pszFileName, pszFuncName, nLineNumber);
  return static_cast<UDWORD *>(pciSlot->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_SQWORD_ADDRESS(pszFile, pszFunc, nLine)      PopSQWORDAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
SQWORD * CZVMVirtualThread::PopSQWORDAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_SQWORD_ADDRESS(pszFile, pszFunc, nLine)      PopSQWORDAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
SQWORD * CZVMVirtualThread::PopSQWORDAddress()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_SQWORD, pszFileName, pszFuncName, nLineNumber);
  return static_cast<SQWORD *>(pciSlot->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_UQWORD_ADDRESS(pszFile, pszFunc, nLine)      PopUQWORDAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UQWORD * CZVMVirtualThread::PopUQWORDAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_UQWORD_ADDRESS(pszFile, pszFunc, nLine)      PopUQWORDAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UQWORD * CZVMVirtualThread::PopUQWORDAddress()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_UQWORD, pszFileName, pszFuncName, nLineNumber);
  return static_cast<UQWORD *>(pciSlot->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_DOUBLE_ADDRESS(pszFile, pszFunc, nLine)      PopDoubleAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
double * CZVMVirtualThread::PopDoubleAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_DOUBLE_ADDRESS(pszFile, pszFunc, nLine)      PopDoubleAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
double * CZVMVirtualThread::PopDoubleAddress()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_DOUBLE, pszFileName, pszFuncName, nLineNumber);
  return static_cast<double *>(pciSlot->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_STRING_OBJECT_ADDRESS(pszFile, pszFunc, nLine)      PopStringObjectAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMString ** CZVMVirtualThread::PopStringObjectAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_STRING_OBJECT_ADDRESS(pszFile, pszFunc, nLine)      PopStringObjectAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMString ** CZVMVirtualThread::PopStringObjectAddress()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_STRING_OBJECT, pszFileName, pszFuncName, nLineNumber);
  return static_cast<CZVMString **>(pciSlot->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_ROPE_OBJECT_ADDRESS(pszFile, pszFunc, nLine)      PopRopeObjectAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMRope ** CZVMVirtualThread::PopRopeObjectAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_ROPE_OBJECT_ADDRESS(pszFile, pszFunc, nLine)      PopRopeObjectAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMRope ** CZVMVirtualThread::PopRopeObjectAddress()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_ROPE_OBJECT, pszFileName, pszFuncName, nLineNumber);
  return static_cast<CZVMRope **>(pciSlot->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_IPv4ADDRESS_OBJECT_ADDRESS(pszFile, pszFunc, nLine)      PopIPv4AddressObjectAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMIPv4Address ** CZVMVirtualThread::PopIPv4AddressObjectAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_IPv4ADDRESS_OBJECT_ADDRESS(pszFile, pszFunc, nLine)      PopIPv4AddressObjectAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMIPv4Address ** CZVMVirtualThread::PopIPv4AddressObjectAddress()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_IPv4ADDRESS_OBJECT, pszFileName, pszFuncName, nLineNumber);
  return static_cast<CZVMIPv4Address **>(pciSlot->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_PPORT_OBJECT_ADDRESS(pszFile, pszFunc, nLine)      PopPPortObjectAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMPPort ** CZVMVirtualThread::PopPPortObjectAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define POP_PPORT_OBJECT_ADDRESS(pszFile, pszFunc, nLine)      PopPPortObjectAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMPPort ** CZVMVirtualThread::PopPPortObjectAddress()
#endif
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_PPORT_OBJECT, pszFileName, pszFuncName, nLineNumber);
  return static_cast<CZVMPPort **>(pciSlot->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define POP_TABLE_OBJECT_ADDRESS(chTableElementTypeTag, pszFile, pszFunc, nLine)      PopTableObjectAddress(chTableElementTypeTag, pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMTable ** CZVMVirtualThread::PopTableObjectAddress(char chTableElementTypeTag, const char * pszFileName, const char *pszFuncName, int nLineNumber)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::PopTableObjectAddress()");
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_TABLE_OBJECT, pszFileName, pszFuncName, nLineNumber);
  CZVMTable ** ppciTable = static_cast<CZVMTable **>(pciSlot->GetIndirectAddress());
  #ifndef NDEBUG
  if (chTableElementTypeTag != CchZVM_VOID_TYPE_TAG)
  {
    LogAssert1((*ppciTable)->GetTableElementTypeTag() == chTableElementTypeTag,
               "Bug: Unexpected table element type tag '%c'",
               (*ppciTable)->GetTableElementTypeTag());
  }
  #endif
  return ppciTable;
}
#else
#define POP_TABLE_OBJECT_ADDRESS(chTableElementTypeTag, pszFile, pszFunc, nLine)      PopTableObjectAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMTable ** CZVMVirtualThread::PopTableObjectAddress()
{
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  return static_cast<CZVMTable **>(pciSlot->GetIndirectAddress());
}
#endif


/******************************************************************************
 * TOP Value
 ******************************************************************************/
#ifdef ENABLE_ZVM_DEBUG
#define TOP_BOOL(pszFile, pszFunc, nLine)       TopBool(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
bool CZVMVirtualThread::TopBool(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_BOOL(pszFile, pszFunc, nLine)       TopBool()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
bool CZVMVirtualThread::TopBool()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_BOOL, pszFileName, pszFuncName, nLineNumber);
  return _pciSPRegister->GetBool();
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_BYTE(pszFile, pszFunc, nLine)       TopByte(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UCHAR CZVMVirtualThread::TopByte(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_BYTE(pszFile, pszFunc, nLine)       TopByte()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UCHAR CZVMVirtualThread::TopByte()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_BYTE, pszFileName, pszFuncName, nLineNumber);
  return _pciSPRegister->GetByte();
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_SDWORD(pszFile, pszFunc, nLine)       TopSDWORD(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
SDWORD CZVMVirtualThread::TopSDWORD(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_SDWORD(pszFile, pszFunc, nLine)       TopSDWORD()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
SDWORD CZVMVirtualThread::TopSDWORD()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_SDWORD, pszFileName, pszFuncName, nLineNumber);
  return _pciSPRegister->GetSDWORD();
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_UDWORD(pszFile, pszFunc, nLine)       TopUDWORD(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UDWORD CZVMVirtualThread::TopUDWORD(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_UDWORD(pszFile, pszFunc, nLine)       TopUDWORD()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UDWORD CZVMVirtualThread::TopUDWORD()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_UDWORD, pszFileName, pszFuncName, nLineNumber);
  return _pciSPRegister->GetUDWORD();
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_SQWORD(pszFile, pszFunc, nLine)       TopSQWORD(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
SQWORD CZVMVirtualThread::TopSQWORD(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_SQWORD(pszFile, pszFunc, nLine)       TopSQWORD()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
SQWORD CZVMVirtualThread::TopSQWORD()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_SQWORD, pszFileName, pszFuncName, nLineNumber);
  return _pciSPRegister->GetSQWORD();
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_UQWORD(pszFile, pszFunc, nLine)       TopUQWORD(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UQWORD CZVMVirtualThread::TopUQWORD(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_UQWORD(pszFile, pszFunc, nLine)       TopUQWORD()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UQWORD CZVMVirtualThread::TopUQWORD()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_UQWORD, pszFileName, pszFuncName, nLineNumber);
  return _pciSPRegister->GetUQWORD();
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_DOUBLE(pszFile, pszFunc, nLine)       TopDouble(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
double CZVMVirtualThread::TopDouble(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_DOUBLE(pszFile, pszFunc, nLine)       TopDouble()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
double CZVMVirtualThread::TopDouble()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_DOUBLE, pszFileName, pszFuncName, nLineNumber);
  return _pciSPRegister->GetDouble();
}


/**
 * 不进行内存析构的Top string object.
 * @attention 用于"convertStringValueToAddress"指令.
 */
/*
 * 注：2001/7/17由于"convertStringValueToAddress"等指令被Discarded了!
 *
#ifdef ENABLE_ZVM_DEBUG
#define QUICK_TOP_STRING_OBJECT(pszFile, pszFunc, nLine)        QuickTopStringObject(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMString * CZVMVirtualThread::QuickTopStringObject(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define QUICK_TOP_STRING_OBJECT(pszFile, pszFunc, nLine)        QuickTopStringObject()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMString * CZVMVirtualThread::QuickTopStringObject()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_STRING_OBJECT, pszFileName, pszFuncName, nLineNumber);
  return _pciSPRegister->GetStringObject();
}
*/


/**
 * 不进行内存析构的Top ipv4address object.
 * @attention 用于"convertIPv4AddressValueToAddress"指令.
 */
/*
 * 注：2001/7/17由于"convertStringValueToAddress"等指令被Discarded了!
 *
#ifdef ENABLE_ZVM_DEBUG
#define QUICK_TOP_IPv4ADDRESS_OBJECT(pszFile, pszFunc, nLine)   QuickTopIPv4AddressObject(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMIPv4Address * CZVMVirtualThread::QuickTopIPv4AddressObject(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define QUICK_TOP_IPv4ADDRESS_OBJECT(pszFile, pszFunc, nLine)   QuickTopIPv4AddressObject()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMIPv4Address * CZVMVirtualThread::QuickTopIPv4AddressObject()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_IPv4ADDRESS_OBJECT, pszFileName, pszFuncName, nLineNumber);
  return _pciSPRegister->GetIPv4AddressObject();
}
*/


/**
 * 不进行内存析构的Top pport object.
 * @attention 用于"convertPPortValueToAddress"指令.
 */
/*
 * 注：2001/7/17由于"convertStringValueToAddress"等指令被Discarded了!
 *
#ifdef ENABLE_ZVM_DEBUG
#define QUICK_TOP_PPORT_OBJECT(pszFile, pszFunc, nLine) QuickTopPPortObject(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMPPort * CZVMVirtualThread::QuickTopPPortObject(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define QUICK_TOP_PPORT_OBJECT(pszFile, pszFunc, nLine) QuickTopPPortObject()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMPPort * CZVMVirtualThread::QuickTopPPortObject()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_PPORT_OBJECT, pszFileName, pszFuncName, nLineNumber);
  return _pciSPRegister->GetPPortObject();
}
*/


/**
 * 不进行内存析构的Top table object.
 * @attention 用于"convertTableValueToAddress"指令.
 */
/*
 * 注：2001/7/17由于"convertStringValueToAddress"等指令被Discarded了!
 *
#ifdef ENABLE_ZVM_DEBUG
#define QUICK_TOP_TABLE_OBJECT(pszFile, pszFunc, nLine) QuickTopTableObject(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMTable * CZVMVirtualThread::QuickTopTableObject(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define QUICK_TOP_TABLE_OBJECT(pszFile, pszFunc, nLine) QuickTopTableObject()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMTable * CZVMVirtualThread::QuickTopTableObject()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_TABLE_OBJECT, pszFileName, pszFuncName, nLineNumber);
  return _pciSPRegister->GetTableObject();
}
*/


/******************************************************************************
 * TOP Address
 ******************************************************************************/
#ifdef ENABLE_ZVM_DEBUG
#define TOP_BOOL_ADDRESS(pszFile, pszFunc, nLine)      TopBoolAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
bool * CZVMVirtualThread::TopBoolAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_BOOL_ADDRESS(pszFile, pszFunc, nLine)      TopBoolAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
bool * CZVMVirtualThread::TopBoolAddress()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_ADDRESS_OF_BOOL, pszFileName, pszFuncName, nLineNumber);
  return static_cast<bool *>(_pciSPRegister->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_BYTE_ADDRESS(pszFile, pszFunc, nLine)      TopByteAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UCHAR * CZVMVirtualThread::TopByteAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_BYTE_ADDRESS(pszFile, pszFunc, nLine)      TopByteAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UCHAR * CZVMVirtualThread::TopByteAddress()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_ADDRESS_OF_BYTE, pszFileName, pszFuncName, nLineNumber);
  return static_cast<UCHAR *>(_pciSPRegister->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_SDWORD_ADDRESS(pszFile, pszFunc, nLine)      TopSDWORDAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
SDWORD * CZVMVirtualThread::TopSDWORDAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_SDWORD_ADDRESS(pszFile, pszFunc, nLine)      TopSDWORDAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
SDWORD * CZVMVirtualThread::TopSDWORDAddress()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_ADDRESS_OF_SDWORD, pszFileName, pszFuncName, nLineNumber);
  return static_cast<SDWORD *>(_pciSPRegister->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_UDWORD_ADDRESS(pszFile, pszFunc, nLine)      TopUDWORDAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UDWORD * CZVMVirtualThread::TopUDWORDAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_UDWORD_ADDRESS(pszFile, pszFunc, nLine)      TopUDWORDAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UDWORD * CZVMVirtualThread::TopUDWORDAddress()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_ADDRESS_OF_UDWORD, pszFileName, pszFuncName, nLineNumber);
  return static_cast<UDWORD *>(_pciSPRegister->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_SQWORD_ADDRESS(pszFile, pszFunc, nLine)      TopSQWORDAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
SQWORD * CZVMVirtualThread::TopSQWORDAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_SQWORD_ADDRESS(pszFile, pszFunc, nLine)      TopSQWORDAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
SQWORD * CZVMVirtualThread::TopSQWORDAddress()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_ADDRESS_OF_SQWORD, pszFileName, pszFuncName, nLineNumber);
  return static_cast<SQWORD *>(_pciSPRegister->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_UQWORD_ADDRESS(pszFile, pszFunc, nLine)      TopUQWORDAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UQWORD * CZVMVirtualThread::TopUQWORDAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_UQWORD_ADDRESS(pszFile, pszFunc, nLine)      TopUQWORDAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
UQWORD * CZVMVirtualThread::TopUQWORDAddress()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_ADDRESS_OF_UQWORD, pszFileName, pszFuncName, nLineNumber);
  return static_cast<UQWORD *>(_pciSPRegister->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_DOUBLE_ADDRESS(pszFile, pszFunc, nLine)      TopDoubleAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
double * CZVMVirtualThread::TopDoubleAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_DOUBLE_ADDRESS(pszFile, pszFunc, nLine)      TopDoubleAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
double * CZVMVirtualThread::TopDoubleAddress()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_ADDRESS_OF_DOUBLE, pszFileName, pszFuncName, nLineNumber);
  return static_cast<double *>(_pciSPRegister->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_STRING_OBJECT_ADDRESS(pszFile, pszFunc, nLine)      TopStringObjectAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMString ** CZVMVirtualThread::TopStringObjectAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_STRING_OBJECT_ADDRESS(pszFile, pszFunc, nLine)      TopStringObjectAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMString ** CZVMVirtualThread::TopStringObjectAddress()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_ADDRESS_OF_STRING_OBJECT, pszFileName, pszFuncName, nLineNumber);
  return static_cast<CZVMString **>(_pciSPRegister->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_ROPE_OBJECT_ADDRESS(pszFile, pszFunc, nLine)      TopRopeObjectAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMRope ** CZVMVirtualThread::TopRopeObjectAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_ROPE_OBJECT_ADDRESS(pszFile, pszFunc, nLine)      TopRopeObjectAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMRope ** CZVMVirtualThread::TopRopeObjectAddress()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_ADDRESS_OF_ROPE_OBJECT, pszFileName, pszFuncName, nLineNumber);
  return static_cast<CZVMRope **>(_pciSPRegister->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_IPv4ADDRESS_OBJECT_ADDRESS(pszFile, pszFunc, nLine)      TopIPv4AddressObjectAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMIPv4Address ** CZVMVirtualThread::TopIPv4AddressObjectAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_IPv4ADDRESS_OBJECT_ADDRESS(pszFile, pszFunc, nLine)      TopIPv4AddressObjectAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMIPv4Address ** CZVMVirtualThread::TopIPv4AddressObjectAddress()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_ADDRESS_OF_IPv4ADDRESS_OBJECT, pszFileName, pszFuncName, nLineNumber);
  return static_cast<CZVMIPv4Address **>(_pciSPRegister->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_PPORT_OBJECT_ADDRESS(pszFile, pszFunc, nLine)      TopPPortObjectAddress(pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMPPort ** CZVMVirtualThread::TopPPortObjectAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber)
#else
#define TOP_PPORT_OBJECT_ADDRESS(pszFile, pszFunc, nLine)      TopPPortObjectAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMPPort ** CZVMVirtualThread::TopPPortObjectAddress()
#endif
{
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_ADDRESS_OF_PPORT_OBJECT, pszFileName, pszFuncName, nLineNumber);
  return static_cast<CZVMPPort **>(_pciSPRegister->GetIndirectAddress());
}


#ifdef ENABLE_ZVM_DEBUG
#define TOP_TABLE_OBJECT_ADDRESS(chTableElementTypeTag, pszFile, pszFunc, nLine)      TopTableObjectAddress(chTableElementTypeTag, pszFile, pszFunc, nLine)
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMTable ** CZVMVirtualThread::TopTableObjectAddress(char chTableElementTypeTag, const char * pszFileName, const char *pszFuncName, int nLineNumber)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::TopTableObjectAddress()");
  ZVM_SLOT_ASSERT(_pciSPRegister, CSlot::SLOT_TAG_ADDRESS_OF_TABLE_OBJECT, pszFileName, pszFuncName, nLineNumber);
  CZVMTable ** ppciTable = static_cast<CZVMTable **>(_pciSPRegister->GetIndirectAddress());
  #ifndef NDEBUG
  if (chTableElementTypeTag != CchZVM_VOID_TYPE_TAG)
  {
    LogAssert1((*ppciTable)->GetTableElementTypeTag() == chTableElementTypeTag,
               "Bug: Unexpected table element type tag '%c'",
               (*ppciTable)->GetTableElementTypeTag());
  }
  #endif
  return ppciTable;
}
#else
#define TOP_TABLE_OBJECT_ADDRESS(chTableElementTypeTag, pszFile, pszFunc, nLine)      TopTableObjectAddress()
#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
inline
#endif
CZVMTable ** CZVMVirtualThread::TopTableObjectAddress()
{
  return static_cast<CZVMTable **>(_pciSPRegister->GetIndirectAddress());
}
#endif

