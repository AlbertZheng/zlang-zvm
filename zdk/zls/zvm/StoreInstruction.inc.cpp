/******************************************************************************
 * Store指令Interpreter
 ******************************************************************************/
TZVMIndex CZVMVirtualThread::_storeToBoolGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToBoolGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BOOL, __FILE__, __PRETTY_FUNC__, __LINE__);
  bool b = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreBool(b);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToByteGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToByteGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BYTE, __FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uch = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreByte(uch);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToSDWORDGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToSDWORDGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdw = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreSDWORD(sdw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToUDWORDGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToUDWORDGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreUDWORD(udw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToSQWORDGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToSQWORDGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqw = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreSQWORD(sqw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToUQWORDGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToUQWORDGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqw = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreUQWORD(uqw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToDoubleGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToDoubleGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_DOUBLE, __FILE__, __PRETTY_FUNC__, __LINE__);
  double df = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreDouble(df);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToStringGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToStringGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppci = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreStringObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToRopeGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToRopeGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ROPE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppci = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreRopeObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToIPv4AddressGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToIPv4AddressGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMIPv4Address ** ppci = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreIPv4AddressObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToPPortGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToPPortGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppci = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StorePPortObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToTableGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToTableGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppci = POP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreTableObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToBoolStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToBoolStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BOOL, __FILE__, __PRETTY_FUNC__, __LINE__);
  bool b = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreBool(b);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToByteStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToByteStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BYTE, __FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uch = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreByte(uch);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToSDWORDStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToSDWORDStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdw = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreSDWORD(sdw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToUDWORDStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToUDWORDStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreUDWORD(udw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToSQWORDStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToSQWORDStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqw = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreSQWORD(sqw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToUQWORDStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToUQWORDStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqw = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreUQWORD(uqw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToDoubleStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToDoubleStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_DOUBLE, __FILE__, __PRETTY_FUNC__, __LINE__);
  double df = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreDouble(df);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToStringStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToStringStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppci = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreStringObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToRopeStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToRopeStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ROPE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppci = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreRopeObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToIPv4AddressStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToIPv4AddressStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMIPv4Address ** ppci = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreIPv4AddressObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToPPortStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToPPortStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppci = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StorePPortObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeToTableStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeToTableStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppci = POP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreTableObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectStoreToBoolStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectStoreToBoolStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_BOOL, __FILE__, __PRETTY_FUNC__, __LINE__);
  bool b = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreBool(b);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectStoreToByteStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectStoreToByteStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_BYTE, __FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uch = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreByte(uch);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectStoreToSDWORDStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectStoreToSDWORDStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdw = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreSDWORD(sdw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectStoreToUDWORDStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectStoreToUDWORDStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_UDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreUDWORD(udw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectStoreToSQWORDStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectStoreToSQWORDStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_SQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqw = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreSQWORD(sqw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectStoreToUQWORDStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectStoreToUQWORDStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_UQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqw = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreUQWORD(uqw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectStoreToDoubleStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectStoreToDoubleStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_DOUBLE, __FILE__, __PRETTY_FUNC__, __LINE__);
  double df = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreDouble(df);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectStoreToStringStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectStoreToStringStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppci = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreStringObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectStoreToRopeStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectStoreToRopeStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_ROPE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppci = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreRopeObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectStoreToIPv4AddressStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectStoreToIPv4AddressStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMIPv4Address ** ppci = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreIPv4AddressObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectStoreToPPortStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectStoreToPPortStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppci = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStorePPortObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectStoreToTableStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectStoreToTableStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppci = POP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreTableObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeBoolToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeBoolToAddress()");
  bool b = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  bool * pb = POP_BOOL_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pb = b;
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeByteToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeByteToAddress()");
  UCHAR uch = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR * puch = POP_BYTE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *puch = uch;
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeSDWORDToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeSDWORDToAddress()");
  SDWORD sdw = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD * psdw = POP_SDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *psdw = sdw;
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeUDWORDToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeUDWORDToAddress()");
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD * pudw = POP_UDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pudw = udw;
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeSQWORDToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeSQWORDToAddress()");
  SQWORD sqw = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD * psqw = POP_SQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *psqw = sqw;
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeUQWORDToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeUQWORDToAddress()");
  UQWORD uqw = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD * puqw = POP_UQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *puqw = uqw;
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeDoubleToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeDoubleToAddress()");
  double df = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double * pdf = POP_DOUBLE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pdf = df;
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeStringToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeStringToAddress()");
  CZVMString ** ppciFrom = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppciTo = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  **ppciTo = **ppciFrom;
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeRopeToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeRopeToAddress()");
  CZVMRope ** ppciFrom = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppciTo = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  **ppciTo = **ppciFrom;
  return 1;
}


TZVMIndex CZVMVirtualThread::_storeIPv4AddressToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storeIPv4AddressToAddress()");
  CZVMIPv4Address ** ppciFrom = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMIPv4Address ** ppciTo = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  **ppciTo = **ppciFrom;
  return 1;
}


TZVMIndex CZVMVirtualThread::_storePPortToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_storePPortToAddress()");
  CZVMPPort ** ppciFrom = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppciTo = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  **ppciTo = **ppciFrom;
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToBoolGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToBoolGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BOOL, __FILE__, __PRETTY_FUNC__, __LINE__);
  bool b = TOP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreBool(b);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToByteGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToByteGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BYTE, __FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uch = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreByte(uch);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToSDWORDGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToSDWORDGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdw = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreSDWORD(sdw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToUDWORDGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToUDWORDGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udw = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreUDWORD(udw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToSQWORDGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToSQWORDGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqw = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreSQWORD(sqw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToUQWORDGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToUQWORDGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqw = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreUQWORD(uqw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToDoubleGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToDoubleGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_DOUBLE, __FILE__, __PRETTY_FUNC__, __LINE__);
  double df = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreDouble(df);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToStringGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToStringGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppci = TOP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreStringObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToRopeGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToRopeGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ROPE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppci = TOP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreRopeObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToIPv4AddressGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToIPv4AddressGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMIPv4Address ** ppci = TOP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreIPv4AddressObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToPPortGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToPPortGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppci = TOP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StorePPortObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToTableGlobalVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToTableGlobalVariable()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppci = TOP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreTableObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToBoolStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToBoolStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BOOL, __FILE__, __PRETTY_FUNC__, __LINE__);
  bool b = TOP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreBool(b);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToByteStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToByteStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BYTE, __FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uch = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreByte(uch);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToSDWORDStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToSDWORDStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdw = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreSDWORD(sdw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToUDWORDStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToUDWORDStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udw = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreUDWORD(udw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToSQWORDStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToSQWORDStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqw = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreSQWORD(sqw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToUQWORDStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToUQWORDStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqw = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreUQWORD(uqw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToDoubleStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToDoubleStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_DOUBLE, __FILE__, __PRETTY_FUNC__, __LINE__);
  double df = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreDouble(df);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToStringStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToStringStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppci = TOP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreStringObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToRopeStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToRopeStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ROPE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppci = TOP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreRopeObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToIPv4AddressStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToIPv4AddressStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMIPv4Address ** ppci = TOP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreIPv4AddressObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToPPortStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToPPortStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppci = TOP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StorePPortObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreToTableStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreToTableStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppci = TOP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreTableObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectNestedStoreToBoolStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectNestedStoreToBoolStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_BOOL, __FILE__, __PRETTY_FUNC__, __LINE__);
  bool b = TOP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreBool(b);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectNestedStoreToByteStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectNestedStoreToByteStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_BYTE, __FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uch = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreByte(uch);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectNestedStoreToSDWORDStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectNestedStoreToSDWORDStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdw = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreSDWORD(sdw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectNestedStoreToUDWORDStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectNestedStoreToUDWORDStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_UDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udw = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreUDWORD(udw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectNestedStoreToSQWORDStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectNestedStoreToSQWORDStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_SQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqw = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreSQWORD(sqw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectNestedStoreToUQWORDStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectNestedStoreToUQWORDStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_UQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqw = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreUQWORD(uqw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectNestedStoreToDoubleStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectNestedStoreToDoubleStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_DOUBLE, __FILE__, __PRETTY_FUNC__, __LINE__);
  double df = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreDouble(df);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectNestedStoreToStringStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectNestedStoreToStringStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppci = TOP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreStringObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectNestedStoreToRopeStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectNestedStoreToRopeStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_ROPE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppci = TOP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreRopeObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectNestedStoreToIPv4AddressStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectNestedStoreToIPv4AddressStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMIPv4Address ** ppci = TOP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreIPv4AddressObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectNestedStoreToPPortStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectNestedStoreToPPortStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppci = TOP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStorePPortObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectNestedStoreToTableStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectNestedStoreToTableStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppci = TOP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->IndirectStoreTableObject(*ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreBoolToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreBoolToAddress()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool bFrom = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  bool * pbTo = TOP_BOOL_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pbTo = bFrom;
  ReplaceAsBool(bFrom);
  #else
  bool bFrom = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  bool * pbTo = POP_BOOL_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pbTo = bFrom;
  PushBool(bFrom);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreByteToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreByteToAddress()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchFrom = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR * puchTo = TOP_BYTE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *puchTo = uchFrom;
  ReplaceAsByte(uchFrom);
  #else
  UCHAR uchFrom = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR * puchTo = POP_BYTE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *puchTo = uchFrom;
  PushByte(uchFrom);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreSDWORDToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreSDWORDToAddress()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwFrom = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD * psdwTo = TOP_SDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *psdwTo = sdwFrom;
  ReplaceAsSDWORD(sdwFrom);
  #else
  SDWORD sdwFrom = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD * psdwTo = POP_SDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *psdwTo = sdwFrom;
  PushSDWORD(sdwFrom);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreUDWORDToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreUDWORDToAddress()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwFrom = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD * pudwTo = TOP_UDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pudwTo = udwFrom;
  ReplaceAsUDWORD(udwFrom);
  #else
  UDWORD udwFrom = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD * pudwTo = POP_UDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pudwTo = udwFrom;
  PushUDWORD(udwFrom);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreSQWORDToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreSQWORDToAddress()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwFrom = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD * psqwTo = TOP_SQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *psqwTo = sqwFrom;
  ReplaceAsSQWORD(sqwFrom);
  #else
  SQWORD sqwFrom = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD * psqwTo = POP_SQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *psqwTo = sqwFrom;
  PushSQWORD(sqwFrom);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreUQWORDToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreUQWORDToAddress()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwFrom = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD * puqwTo = TOP_UQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *puqwTo = uqwFrom;
  ReplaceAsUQWORD(uqwFrom);
  #else
  UQWORD uqwFrom = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD * puqwTo = POP_UQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *puqwTo = uqwFrom;
  PushUQWORD(uqwFrom);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreDoubleToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreDoubleToAddress()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfFrom = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double * pdfTo = TOP_DOUBLE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pdfTo = dfFrom;
  ReplaceAsDouble(dfFrom);
  #else
  double dfFrom = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double * pdfTo = POP_DOUBLE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pdfTo = dfFrom;
  PushDouble(dfFrom);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreStringToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreStringToAddress()");
  CZVMString ** ppciFrom = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  // 注意：采用top操作，可以节省一次push操作
  CZVMString ** ppciTo = TOP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  **ppciTo = **ppciFrom;
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreRopeToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreRopeToAddress()");
  CZVMRope ** ppciFrom = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  // 注意：采用top操作，可以节省一次push操作
  CZVMRope ** ppciTo = TOP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  **ppciTo = **ppciFrom;
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStoreIPv4AddressToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStoreIPv4AddressToAddress()");
  CZVMIPv4Address ** ppciFrom = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  // 注意：采用top操作，可以节省一次push操作
  CZVMIPv4Address ** ppciTo = TOP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  **ppciTo = **ppciFrom;
  return 1;
}


TZVMIndex CZVMVirtualThread::_nestedStorePPortToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_nestedStorePPortToAddress()");
  CZVMPPort ** ppciFrom = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  // 注意：采用top操作，可以节省一次push操作
  CZVMPPort ** ppciTo = TOP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  **ppciTo = **ppciFrom;
  return 1;
}


TZVMIndex CZVMVirtualThread::_assignReferenceAddressToBoolReferenceStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_assignReferenceAddressToBoolReferenceStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_BOOL, __FILE__, __PRETTY_FUNC__, __LINE__);
  bool * pb = POP_BOOL_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreBoolAddress(pb);
  return 1;
}


TZVMIndex CZVMVirtualThread::_assignReferenceAddressToByteReferenceStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_assignReferenceAddressToByteReferenceStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_BYTE, __FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR * puch = POP_BYTE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreByteAddress(puch);
  return 1;
}


TZVMIndex CZVMVirtualThread::_assignReferenceAddressToSDWORDReferenceStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_assignReferenceAddressToSDWORDReferenceStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD * psdw = POP_SDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreSDWORDAddress(psdw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_assignReferenceAddressToUDWORDReferenceStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_assignReferenceAddressToUDWORDReferenceStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_UDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD * pudw = POP_UDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreUDWORDAddress(pudw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_assignReferenceAddressToSQWORDReferenceStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_assignReferenceAddressToSQWORDReferenceStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_SQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD * psqw = POP_SQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreSQWORDAddress(psqw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_assignReferenceAddressToUQWORDReferenceStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_assignReferenceAddressToUQWORDReferenceStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_UQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD * puqw = POP_UQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreUQWORDAddress(puqw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_assignReferenceAddressToDoubleReferenceStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_assignReferenceAddressToDoubleReferenceStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_DOUBLE, __FILE__, __PRETTY_FUNC__, __LINE__);
  double * pdf = POP_DOUBLE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreDoubleAddress(pdf);
  return 1;
}


TZVMIndex CZVMVirtualThread::_assignReferenceAddressToStringReferenceStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_assignReferenceAddressToStringReferenceStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppci = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreStringObjectAddress(ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_assignReferenceAddressToRopeReferenceStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_assignReferenceAddressToRopeReferenceStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_ROPE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppci = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreRopeObjectAddress(ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_assignReferenceAddressToIPv4AddressReferenceStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_assignReferenceAddressToIPv4AddressReferenceStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMIPv4Address ** ppci = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreIPv4AddressObjectAddress(ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_assignReferenceAddressToPPortReferenceStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_assignReferenceAddressToPPortReferenceStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppci = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StorePPortObjectAddress(ppci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_assignReferenceAddressToTableReferenceStackVariable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_assignReferenceAddressToTableReferenceStackVariable()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppci = POP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->StoreTableObjectAddress(ppci);
  return 1;
}



