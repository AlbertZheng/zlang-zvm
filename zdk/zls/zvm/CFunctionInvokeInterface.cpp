/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CFunctionInvokeInterface.cpp,v $
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


#include <zls/zvm/CFunctionInvokeInterface.hpp>
#include <zls/zvm/CZVMVirtualThread.hpp>


// Begin namespace 'zvm::'
ZLS_BEGIN_NAMESPACE(zvm)


CFunctionInvokeInterface & CFunctionInvokeInterface::operator=(const CFunctionInvokeInterface & rciOther)
{
  _eState = CFunctionInvokeInterface::STATE_DEFAULT;
  return *this;
}


CFunctionInvokeInterface::CFunctionInvokeInterface(const CFunctionInvokeInterface & rciOther)
{
  operator=(rciOther);
}


CFunctionInvokeInterface::CFunctionInvokeInterface()
  : _eState(CFunctionInvokeInterface::STATE_DEFAULT)
{ }


CFunctionInvokeInterface::~CFunctionInvokeInterface()
{ }


const std::string & CFunctionInvokeInterface::GetFunctionName() const
{
  return _stringFunctionName;
}


const std::string & CFunctionInvokeInterface::GetFunctionSignature() const
{
  return _pciFunctionRegisterEntry->GetFunctionSignature();
}


const std::string & CFunctionInvokeInterface::GetSourceFileName() const
{
  return _pciFunctionRegisterEntry->GetSourceFileName();
}


const std::string & CFunctionInvokeInterface::GetObjectFileName() const
{
  return _pciFunctionRegisterEntry->GetObjectFileName();
}


void CFunctionInvokeInterface::PrepareForFunction(CZVMVirtualThread * pciZVMVirtualThread,
                                                  const std::string & rstringFunctionName)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PrepareForFunction()");
  std::string stringError;

  _eState = STATE_DEFAULT;

  // 检测ZVM的状态合法否
  const CVirtualMachine * pciZVM = pciZVMVirtualThread->GetOwnerZVM();
  if (pciZVM->GetState() != CVirtualMachine::STATE_OBJECT_FILES_LINKED_OK)
  {
    stringError = "Preparing failure due to 'ZVM is in linkage failed state'";
    throw zvm::EFunctionInvokeInterfaceException(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
  }

  // Find function register entry
  _pciFunctionRegisterEntry = pciZVM->FindRegisteredGlobalFunction(rstringFunctionName);
  if (! _pciFunctionRegisterEntry)
  {
    stringError = "Preparing failure due to \"function '" + rstringFunctionName + "' not found\"";
    throw zvm::EFunctionInvokeInterfaceException(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
  }

  // save 'function name'
  _stringFunctionName = rstringFunctionName;

  // 设置将要被打结的Virtual thread
  _pciTiedZVMVirtualThread = pciZVMVirtualThread;

  //
  // Cache需要用到的function register info
  //
  _eReturnSlotTag = _pciFunctionRegisterEntry->GetReturnSlotTag();
  _pvectorArgumentsSlotTags = &(_pciFunctionRegisterEntry->GetArgumentsSlotTags());
  _nArgumentsCount = _pvectorArgumentsSlotTags->size();
  if (_eReturnSlotTag != CSlot::CSlot::SLOT_TAG_VOID)  // 如果这个function是有返回值的
  {
    _nStackAdjustedOffset = _nArgumentsCount + 1;
  }
  else
  {
    _nStackAdjustedOffset = _nArgumentsCount;
  }
  _eLanguageTag = _pciFunctionRegisterEntry->GetLanguageTag();
  if (_eLanguageTag == LANGUAGE_TAG_IS_ZLANG)
  {
    _pciZVMFunction = _pciFunctionRegisterEntry->GetZVMFunction();
  }
  else
  {
    _pfuncNativeFunction = _pciFunctionRegisterEntry->GetNativeFunction();
  }

  _eState = STATE_PREPARED;
}


void CFunctionInvokeInterface::TieToZVMVirtualThread()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::TieToZVMVirtualThread()");
  std::string stringError;

  if (_eState != STATE_PREPARED)
  {
    stringError = "Invalid state, Please do 'prepare for function' firstly";
    throw zfc::EInvalidState(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
  }

  // 设置Arguments开始slot位置
  CSlot * pciBeginSlot = _pciArgumentsBeginSlot = _pciTiedZVMVirtualThread->GetSPRegister() + 1;
  if (_eReturnSlotTag != CSlot::SLOT_TAG_VOID)
  {
    // 设置Return slot位置
    _pciReturnSlot = _pciArgumentsBeginSlot;
    // 调整Arguments开始slot位置
    ++_pciArgumentsBeginSlot;
  }

  const CSlot * pciStackHighWater = _pciTiedZVMVirtualThread->GetStackHighWater();
  if (pciBeginSlot + _nStackAdjustedOffset >= pciStackHighWater)
  // Stack会溢出
  {
    stringError = "Preparing function invoke interface for function '" + GetFunctionName() + "' in '" +
                  GetObjectFileName() + "' failure due to 'ZVM virtual thread stack will overflow'";
    throw zvm::EFunctionInvokeInterfaceException(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
  }

  // zero我们要用到的所有CSlot，这样我们以后可以判断"用户"是否"pass"了全部的Arguments
  memset(pciBeginSlot, '\0', sizeof(CSlot) * _nStackAdjustedOffset);

  _eState = STATE_TIED_TO_VIRTUAL_THREAD;
}


void CFunctionInvokeInterface::CheckFunctionInvokeInterfaceState(
  const char * pszFileName,
  const char * pszFuncName,
  const int nLineNumber) const
{
  if (_eState != STATE_TIED_TO_VIRTUAL_THREAD)
  {
    std::string stringError = "Invalid state, Please do 'tie to ZVM virtual thread' firstly";
    throw zfc::EInvalidState(pszFileName, pszFuncName, nLineNumber, stringError);
  }
}


void CFunctionInvokeInterface::CheckArgumentRange(
  TZVMIndex iArgumentIndex,
  const char * pszFileName,
  const char * pszFuncName,
  const int nLineNumber) const
{
  if (iArgumentIndex < 1 || iArgumentIndex > _nArgumentsCount)
  {
    throw zfc::EOutOfRange(pszFileName, pszFuncName, nLineNumber,
                           "Invalid argument index", iArgumentIndex, 1, _nArgumentsCount);
  }
}


void CFunctionInvokeInterface::CheckArgumentType(
  TZVMIndex iArgumentIndex,
  CSlot::TSlotTag ePassedTag,
  const char * pszFileName,
  const char * pszFuncName,
  const int nLineNumber) const
{
  if (ePassedTag != _pvectorArgumentsSlotTags->operator[](iArgumentIndex-1))
  // 即使是value argument，通过C++来调用ZVM function就必须参数类型完全相同
  {
    std::string stringError = std::string("Mismatched type signature when setting the ") + iArgumentIndex +
                              " argument for function '" + GetFunctionName() + "' in '" + GetObjectFileName() + "'";
    throw zvm::EFunctionInvokeInterfaceException(pszFileName, pszFuncName, nLineNumber, stringError);
  }
}


void CFunctionInvokeInterface::PassValueArgumentAsBool(TZVMIndex iArgumentIndex, bool b)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassValueArgumentAsBool()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_BOOL, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsBool(b);
}


void CFunctionInvokeInterface::PassValueArgumentAsByte(TZVMIndex iArgumentIndex, UCHAR uch)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassValueArgumentAsByte()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_BYTE, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsByte(uch);
}


void CFunctionInvokeInterface::PassValueArgumentAsSDWORD(TZVMIndex iArgumentIndex, SDWORD sdw)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassValueArgumentAsSDWORD()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsSDWORD(sdw);
}


void CFunctionInvokeInterface::PassValueArgumentAsUDWORD(TZVMIndex iArgumentIndex, UDWORD udw)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassValueArgumentAsUDWORD()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_UDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsUDWORD(udw);
}


void CFunctionInvokeInterface::PassValueArgumentAsSQWORD(TZVMIndex iArgumentIndex, SQWORD sqw)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassValueArgumentAsSQWORD()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_SQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsSQWORD(sqw);
}


void CFunctionInvokeInterface::PassValueArgumentAsUQWORD(TZVMIndex iArgumentIndex, UQWORD uqw)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassValueArgumentAsUQWORD()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_UQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsUQWORD(uqw);
}


void CFunctionInvokeInterface::PassValueArgumentAsDouble(TZVMIndex iArgumentIndex, double df)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassValueArgumentAsDouble()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_DOUBLE, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsDouble(df);
}


void CFunctionInvokeInterface::PassValueArgumentAsStringObject(
  TZVMIndex iArgumentIndex,
  const CZVMString & rciString)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassValueArgumentAsStringObject()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsStringObject(&rciString);
}


void CFunctionInvokeInterface::PassValueArgumentAsPPortObject(
  TZVMIndex iArgumentIndex,
  const CProtocolPort & rciPPort)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassValueArgumentAsPPortObject()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsPPortObject(&rciPPort);
}


void CFunctionInvokeInterface::PassValueArgumentAsIPv4AddressObject(
  TZVMIndex iArgumentIndex,
  const CZVMIPv4Address & rciIPv4Address)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassValueArgumentAsIPv4AddressObject()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsIPv4AddressObject(&rciIPv4Address);
}


void CFunctionInvokeInterface::PassValueArgumentAsTableObject(
  TZVMIndex iArgumentIndex,
  const CZVMTable & rciTable)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassValueArgumentAsTableObject()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsTableObject(&rciTable);
}


void CFunctionInvokeInterface::PassReferenceArgumentAsBoolAddress(
  TZVMIndex iArgumentIndex,
  bool & rb)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassReferenceArgumentAsBoolAddress()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_ADDRESS_OF_BOOL, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsBoolAddress(&rb);
}


void CFunctionInvokeInterface::PassReferenceArgumentAsByteAddress(
  TZVMIndex iArgumentIndex,
  UCHAR & ruch)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassReferenceArgumentAsByteAddress()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_ADDRESS_OF_BYTE, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsByteAddress(&ruch);
}


void CFunctionInvokeInterface::PassReferenceArgumentAsSDWORDAddress(
  TZVMIndex iArgumentIndex,
  SDWORD & rsdw)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassReferenceArgumentAsSDWORDAddress()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_ADDRESS_OF_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsSDWORDAddress(&rsdw);
}


void CFunctionInvokeInterface::PassReferenceArgumentAsUDWORDAddress(
  TZVMIndex iArgumentIndex,
  UDWORD & rudw)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassReferenceArgumentAsUDWORDAddress()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_ADDRESS_OF_UDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsUDWORDAddress(&rudw);
}


void CFunctionInvokeInterface::PassReferenceArgumentAsSQWORDAddress(
  TZVMIndex iArgumentIndex,
  SQWORD & rsqw)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassReferenceArgumentAsSQWORDAddress()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_ADDRESS_OF_SQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsSQWORDAddress(&rsqw);
}


void CFunctionInvokeInterface::PassReferenceArgumentAsUQWORDAddress(
  TZVMIndex iArgumentIndex,
  UQWORD & ruqw)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassReferenceArgumentAsUQWORDAddress()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_ADDRESS_OF_UQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsUQWORDAddress(&ruqw);
}


void CFunctionInvokeInterface::PassReferenceArgumentAsDoubleAddress(
  TZVMIndex iArgumentIndex,
  double & rdf)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassReferenceArgumentAsDoubleAddress()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_ADDRESS_OF_DOUBLE, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsDoubleAddress(&rdf);
}


void CFunctionInvokeInterface::PassReferenceArgumentAsStringObjectAddress(
  TZVMIndex iArgumentIndex,
  CZVMString *& rpciString)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassReferenceArgumentAsStringObjectAddress()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_ADDRESS_OF_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsStringObjectAddress(&rpciString);
}


void CFunctionInvokeInterface::PassReferenceArgumentAsIPv4AddressObjectAddress(
  TZVMIndex iArgumentIndex,
  CZVMIPv4Address *& rpciIPv4Address)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassReferenceArgumentAsIPv4AddressObjectAddress()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_ADDRESS_OF_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsIPv4AddressObjectAddress(&rpciIPv4Address);
}


void CFunctionInvokeInterface::PassReferenceArgumentAsPPortObjectAddress(
  TZVMIndex iArgumentIndex,
  CZVMPPort *& rpciPPort)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassReferenceArgumentAsPPortObjectAddress()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_ADDRESS_OF_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsPPortObjectAddress(&rpciPPort);
}


void CFunctionInvokeInterface::PassReferenceArgumentAsTableObjectAddress(
  TZVMIndex iArgumentIndex,
  CZVMTable *& rpciTable)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::PassReferenceArgumentAsTableObjectAddress()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentRange(iArgumentIndex, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckArgumentType(iArgumentIndex, CSlot::SLOT_TAG_ADDRESS_OF_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);

  // iArgumentIndex往前移一格，因为ZLang中参数的下标是从0开始的
  iArgumentIndex -= 1;

  // Push 'value argument' into ZVM virtual thread's stack
  CSlot * pciSlot = _pciArgumentsBeginSlot + iArgumentIndex;
  pciSlot->ConstructSlotAsTableObjectAddress(&rpciTable);
}


void CFunctionInvokeInterface::CheckReturnType(
  CSlot::TSlotTag ePassedBufferTag,
  const char * pszFileName,
  const char * pszFuncName,
  const int nLineNumber) const
{

  if (_eReturnSlotTag != ePassedBufferTag)
  // 如果这个function的返回类型和用户给的buffer的类型不相同
  {
    std::string stringError = "Passed mismatched function return buffer for function '" +
                              GetFunctionName() + "' in '" + GetObjectFileName() + "'";
    throw zvm::EFunctionInvokeInterfaceException(pszFileName, pszFuncName, nLineNumber, stringError);
  }
}


void CFunctionInvokeInterface::CheckWhetherAllArgumentsPassed(
  const char * pszFileName,
  const char * pszFuncName,
  const int nLineNumber) const
{
  /// 为了安全，遍历且检验是否每个参数都被传递value了
  for (TZVMIndex i = 0; i < _nArgumentsCount; ++i)
  {
    CSlot * pciSlot = _pciArgumentsBeginSlot + i;
    if (pciSlot->GetSlotTag() == CSlot::SLOT_TAG_VOID)
    {
      std::string stringError = std::string("The ") + (i+1) + " argument for function '" +
                                GetFunctionName() + "' in '" + GetObjectFileName() + "' was yet not passed";
      throw zvm::EFunctionInvokeInterfaceException(pszFileName, pszFuncName, nLineNumber, stringError);
    }
  }
}


void CFunctionInvokeInterface::ExecuteFunction()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::ExecuteFunction()");

  try {
    // 调整ZVM stack（quick push）
    _pciTiedZVMVirtualThread->AdjustSPRegister(_nStackAdjustedOffset);

    if (_eLanguageTag == LANGUAGE_TAG_IS_ZLANG)
    {
      _pciTiedZVMVirtualThread->CallZVMFunction(_pciZVMFunction);
      //< May throw zvm::EZVMRuntimeException
    }
    else
    {
      try {
        _pciTiedZVMVirtualThread->CallNativeFunction(_pfuncNativeFunction);
      }
      catch (zfc::EBaseException & e1)
      {
        std::string stringError = "When calling native system function '" + GetFunctionName() + "'";
        e1.AppendWhat(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
        throw;
      }
      catch (...)
      {
        LogError(("Fatal: When calling native system function '%s'\n", GetFunctionName().c_str()));
        throw;
      }
    }

    // 平衡ZVM stack（quick pop），但还是将result argument保留在ZVM stack上
    _pciTiedZVMVirtualThread->AdjustSPRegister(-_nArgumentsCount);
  }
  catch (zvm::EZVMRuntimeException & e1)
  {
    throw;
  }
  catch (zfc::EBaseException & e2)
  {
    // Mapping to zvm::EZVMRuntimeException
    throw zvm::EZVMRuntimeException(e2);
  }
  catch (std::exception & e3)
  {
    // Mapping to zvm::EZVMRuntimeException
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, e3.what());
  }
  catch (...)
  {
    // Mapping to zvm::EZVMRuntimeException
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Unknown exception");
  }
}


void CFunctionInvokeInterface::Invoke(bool & rbReturnBuffer)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::Invoke()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckReturnType(CSlot::SLOT_TAG_BOOL, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckWhetherAllArgumentsPassed(__FILE__, __PRETTY_FUNC__, __LINE__);

  _eState = STATE_INVOKE_START;

  // push 'result argument'
  _pciReturnSlot->ConstructSlotAsDefaultBool();
  // 解释执行
  ExecuteFunction();
  // 现在SP一定已经指向这个'result argument'了，得到返回值
  #ifdef ENABLE_ZVM_DEBUG
  rbReturnBuffer = _pciTiedZVMVirtualThread->PopBool(__FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  rbReturnBuffer = _pciTiedZVMVirtualThread->PopBool();
  #endif

  // 恢复state到prepare态，这样下次调用时还必须先进行tie to ZVM virtual thread
  _eState = STATE_PREPARED;
}


void CFunctionInvokeInterface::Invoke(UCHAR & ruchReturnBuffer)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::Invoke()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckReturnType(CSlot::SLOT_TAG_BYTE, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckWhetherAllArgumentsPassed(__FILE__, __PRETTY_FUNC__, __LINE__);

  _eState = STATE_INVOKE_START;

  // push 'result argument'
  _pciReturnSlot->ConstructSlotAsDefaultByte();
  // 解释执行
  ExecuteFunction();
  // 现在SP一定已经指向这个'result argument'了，得到返回值
  #ifdef ENABLE_ZVM_DEBUG
  ruchReturnBuffer = _pciTiedZVMVirtualThread->PopByte(__FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  ruchReturnBuffer = _pciTiedZVMVirtualThread->PopByte();
  #endif

  // 恢复state到prepare态，这样下次调用时还必须先进行tie to ZVM virtual thread
  _eState = STATE_PREPARED;
}


void CFunctionInvokeInterface::Invoke(SDWORD & rsdwReturnBuffer)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::Invoke()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckReturnType(CSlot::SLOT_TAG_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckWhetherAllArgumentsPassed(__FILE__, __PRETTY_FUNC__, __LINE__);

  _eState = STATE_INVOKE_START;

  // push 'result argument'
  _pciReturnSlot->ConstructSlotAsDefaultSDWORD();
  // 解释执行
  ExecuteFunction();
  // 现在SP一定已经指向这个'result argument'了，得到返回值
  #ifdef ENABLE_ZVM_DEBUG
  rsdwReturnBuffer = _pciTiedZVMVirtualThread->PopSDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  rsdwReturnBuffer = _pciTiedZVMVirtualThread->PopSDWORD();
  #endif

  // 恢复state到prepare态，这样下次调用时还必须先进行tie to ZVM virtual thread
  _eState = STATE_PREPARED;
}


void CFunctionInvokeInterface::Invoke(UDWORD & rudwReturnBuffer)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::Invoke()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckReturnType(CSlot::SLOT_TAG_UDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckWhetherAllArgumentsPassed(__FILE__, __PRETTY_FUNC__, __LINE__);

  _eState = STATE_INVOKE_START;

  // push 'result argument'
  _pciReturnSlot->ConstructSlotAsDefaultUDWORD();
  // 解释执行
  ExecuteFunction();
  // 现在SP一定已经指向这个'result argument'了，得到返回值
  #ifdef ENABLE_ZVM_DEBUG
  rudwReturnBuffer = _pciTiedZVMVirtualThread->PopUDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  rudwReturnBuffer = _pciTiedZVMVirtualThread->PopUDWORD();
  #endif

  // 恢复state到prepare态，这样下次调用时还必须先进行tie to ZVM virtual thread
  _eState = STATE_PREPARED;
}


void CFunctionInvokeInterface::Invoke(SQWORD & rsqwReturnBuffer)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::Invoke()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckReturnType(CSlot::SLOT_TAG_SQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckWhetherAllArgumentsPassed(__FILE__, __PRETTY_FUNC__, __LINE__);

  _eState = STATE_INVOKE_START;

  // push 'result argument'
  _pciReturnSlot->ConstructSlotAsDefaultSQWORD();
  // 解释执行
  ExecuteFunction();
  // 现在SP一定已经指向这个'result argument'了，得到返回值
  #ifdef ENABLE_ZVM_DEBUG
  rsqwReturnBuffer = _pciTiedZVMVirtualThread->PopSQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  rsqwReturnBuffer = _pciTiedZVMVirtualThread->PopSQWORD();
  #endif

  // 恢复state到prepare态，这样下次调用时还必须先进行tie to ZVM virtual thread
  _eState = STATE_PREPARED;
}


void CFunctionInvokeInterface::Invoke(UQWORD & ruqwReturnBuffer)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::Invoke()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckReturnType(CSlot::SLOT_TAG_UQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckWhetherAllArgumentsPassed(__FILE__, __PRETTY_FUNC__, __LINE__);

  _eState = STATE_INVOKE_START;

  // push 'result argument'
  _pciReturnSlot->ConstructSlotAsDefaultUQWORD();
  // 解释执行
  ExecuteFunction();
  // 现在SP一定已经指向这个'result argument'了，得到返回值
  #ifdef ENABLE_ZVM_DEBUG
  ruqwReturnBuffer = _pciTiedZVMVirtualThread->PopUQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  ruqwReturnBuffer = _pciTiedZVMVirtualThread->PopUQWORD();
  #endif

  // 恢复state到prepare态，这样下次调用时还必须先进行tie to ZVM virtual thread
  _eState = STATE_PREPARED;
}


void CFunctionInvokeInterface::Invoke(double & rdfReturnBuffer)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::Invoke()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckReturnType(CSlot::SLOT_TAG_DOUBLE, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckWhetherAllArgumentsPassed(__FILE__, __PRETTY_FUNC__, __LINE__);

  _eState = STATE_INVOKE_START;

  // push 'result argument'
  _pciReturnSlot->ConstructSlotAsDefaultDouble();
  // 解释执行
  ExecuteFunction();
  // 现在SP一定已经指向这个'result argument'了，得到返回值
  #ifdef ENABLE_ZVM_DEBUG
  rdfReturnBuffer = _pciTiedZVMVirtualThread->PopDouble(__FILE__, __PRETTY_FUNC__, __LINE__);
  #else
  rdfReturnBuffer = _pciTiedZVMVirtualThread->PopDouble();
  #endif

  // 恢复state到prepare态，这样下次调用时还必须先进行tie to ZVM virtual thread
  _eState = STATE_PREPARED;
}


void CFunctionInvokeInterface::Invoke(CZVMString & rciReturnBuffer)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::Invoke()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckReturnType(CSlot::SLOT_TAG_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckWhetherAllArgumentsPassed(__FILE__, __PRETTY_FUNC__, __LINE__);

  _eState = STATE_INVOKE_START;

  // push 'result argument'（为了效率直接将"buffer的实际pointer" push到stack上）
  _pciReturnSlot->QuickConstructSlotAsStringObject(&rciReturnBuffer);
  // 解释执行
  ExecuteFunction();
  // 现在SP一定已经指向这个'result argument'了，得到返回值
  ZVM_STACK_ASSERT(_pciTiedZVMVirtualThread, CSlot::SLOT_TAG_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  // 其实不用得到返回值了，因为返回已经在用户给的pointer的内存中了
  // 采用不析构的pop，pop出result argument
  _pciTiedZVMVirtualThread->QuickPopAny();

  // 恢复state到prepare态，这样下次调用时还必须先进行tie to ZVM virtual thread
  _eState = STATE_PREPARED;
}


void CFunctionInvokeInterface::Invoke(CZVMIPv4Address & rciReturnBuffer)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::Invoke()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckReturnType(CSlot::SLOT_TAG_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckWhetherAllArgumentsPassed(__FILE__, __PRETTY_FUNC__, __LINE__);

  _eState = STATE_INVOKE_START;

  // push 'result argument'（为了效率直接将"buffer的实际pointer" push到stack上）
  _pciReturnSlot->QuickConstructSlotAsIPv4AddressObject(&rciReturnBuffer);
  // 解释执行
  ExecuteFunction();
  // 现在SP一定已经指向这个'result argument'了，得到返回值
  ZVM_STACK_ASSERT(_pciTiedZVMVirtualThread, CSlot::SLOT_TAG_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  // 其实不用得到返回值了，因为返回已经在用户给的pointer的内存中了
  // 采用不析构的pop，pop出result argument
  _pciTiedZVMVirtualThread->QuickPopAny();

  // 恢复state到prepare态，这样下次调用时还必须先进行tie to ZVM virtual thread
  _eState = STATE_PREPARED;
}


void CFunctionInvokeInterface::Invoke(CZVMPPort & rciReturnBuffer)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::Invoke()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckReturnType(CSlot::SLOT_TAG_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckWhetherAllArgumentsPassed(__FILE__, __PRETTY_FUNC__, __LINE__);

  _eState = STATE_INVOKE_START;

  // push 'result argument'（为了效率直接将"buffer的实际pointer" push到stack上）
  _pciReturnSlot->QuickConstructSlotAsPPortObject(&rciReturnBuffer);
  // 解释执行
  ExecuteFunction();
  // 现在SP一定已经指向这个'result argument'了，得到返回值
  ZVM_STACK_ASSERT(_pciTiedZVMVirtualThread, CSlot::SLOT_TAG_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  // 其实不用得到返回值了，因为返回已经在用户给的pointer的内存中了
  // 采用不析构的pop，pop出result argument
  _pciTiedZVMVirtualThread->QuickPopAny();

  // 恢复state到prepare态，这样下次调用时还必须先进行tie to ZVM virtual thread
  _eState = STATE_PREPARED;
}


void CFunctionInvokeInterface::Invoke(CZVMTable & rciReturnBuffer)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::Invoke()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckReturnType(CSlot::SLOT_TAG_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckWhetherAllArgumentsPassed(__FILE__, __PRETTY_FUNC__, __LINE__);

  _eState = STATE_INVOKE_START;

  // push 'result argument'（为了效率直接将"buffer的实际pointer" push到stack上）
  _pciReturnSlot->QuickConstructSlotAsTableObject(&rciReturnBuffer);
  // 解释执行
  ExecuteFunction();
  // 现在SP一定已经指向这个'result argument'了，得到返回值
  ZVM_STACK_ASSERT(_pciTiedZVMVirtualThread, CSlot::SLOT_TAG_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  // 其实不用得到返回值了，因为返回已经在用户给的pointer的内存中了
  // 采用不析构的pop，pop出result argument
  _pciTiedZVMVirtualThread->QuickPopAny();

  // 恢复state到prepare态，这样下次调用时还必须先进行tie to ZVM virtual thread
  _eState = STATE_PREPARED;
}


void CFunctionInvokeInterface::Invoke()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CFunctionInvokeInterface::Invoke()");

  CheckFunctionInvokeInterfaceState(__FILE__, __PRETTY_FUNC__, __LINE__);
  CheckReturnType(CSlot::SLOT_TAG_VOID, __FILE__, __PRETTY_FUNC__, __LINE__);
  CheckWhetherAllArgumentsPassed(__FILE__, __PRETTY_FUNC__, __LINE__);

  _eState = STATE_INVOKE_START;

  // 解释执行
  ExecuteFunction();

  // 恢复state到prepare态，这样下次调用时还必须先进行tie to ZVM virtual thread
  _eState = STATE_PREPARED;
}


ZLS_END_NAMESPACE

