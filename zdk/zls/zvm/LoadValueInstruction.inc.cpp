/******************************************************************************
 * Load value指令Interpreter
 ******************************************************************************/
TZVMIndex CZVMVirtualThread::_loadBoolGlobalVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolGlobalVariableValue()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BOOL, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(pciSlot->GetBool());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteGlobalVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteGlobalVariableValue()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BYTE, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(pciSlot->GetByte());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDGlobalVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDGlobalVariableValue()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(pciSlot->GetSDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDGlobalVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDGlobalVariableValue()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(pciSlot->GetUDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDGlobalVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDGlobalVariableValue()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(pciSlot->GetSQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDGlobalVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDGlobalVariableValue()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(pciSlot->GetUQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleGlobalVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleGlobalVariableValue()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_DOUBLE, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(pciSlot->GetDouble());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringGlobalVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringGlobalVariableValue()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushStringObject(pciSlot->GetStringObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeGlobalVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeGlobalVariableValue()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ROPE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushRopeObject(pciSlot->GetRopeObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortGlobalVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortGlobalVariableValue()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushPPortObject(pciSlot->GetPPortObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressGlobalVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressGlobalVariableValue()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushIPv4AddressObject(pciSlot->GetIPv4AddressObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadTableGlobalVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadTableGlobalVariableValue()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushTableObject(pciSlot->GetTableObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BOOL, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(pciSlot->GetBool());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BYTE, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(pciSlot->GetByte());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(pciSlot->GetSDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(pciSlot->GetUDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(pciSlot->GetSQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(pciSlot->GetUQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_DOUBLE, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(pciSlot->GetDouble());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushStringObject(pciSlot->GetStringObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ROPE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushRopeObject(pciSlot->GetRopeObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushIPv4AddressObject(pciSlot->GetIPv4AddressObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushPPortObject(pciSlot->GetPPortObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadTableStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadTableStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushTableObject(pciSlot->GetTableObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadBoolStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadBoolStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_BOOL, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(*(static_cast<bool *>(pciSlot->GetIndirectAddress())));
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadByteStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadByteStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_BYTE, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(*(static_cast<UCHAR *>(pciSlot->GetIndirectAddress())));
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadSDWORDStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadSDWORDStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(*(static_cast<SDWORD *>(pciSlot->GetIndirectAddress())));
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadUDWORDStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadUDWORDStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_UDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(*(static_cast<UDWORD *>(pciSlot->GetIndirectAddress())));
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadSQWORDStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadSQWORDStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_SQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(*(static_cast<SQWORD *>(pciSlot->GetIndirectAddress())));
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadUQWORDStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadUQWORDStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_UQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(*(static_cast<UQWORD *>(pciSlot->GetIndirectAddress())));
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadDoubleStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadDoubleStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_DOUBLE, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(*(static_cast<double *>(pciSlot->GetIndirectAddress())));
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadStringStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadStringStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushStringObject(*(static_cast<CZVMString **>(pciSlot->GetIndirectAddress())));
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadRopeStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadRopeStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_ROPE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushRopeObject(*(static_cast<CZVMRope **>(pciSlot->GetIndirectAddress())));
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadIPv4AddressStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadIPv4AddressStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushIPv4AddressObject(*(static_cast<CZVMIPv4Address **>(pciSlot->GetIndirectAddress())));
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadPPortStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadPPortStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushPPortObject(*(static_cast<CZVMPPort **>(pciSlot->GetIndirectAddress())));
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadTableStackVariableValue()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadTableStackVariableValue()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS_OF_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushTableObject(*(static_cast<CZVMTable **>(pciSlot->GetIndirectAddress())));
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementValueByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementValueByBoolKey()");
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushBool(pciSlot->GetBool());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementValueByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementValueByByteKey()");
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushBool(pciSlot->GetBool());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementValueBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementValueBySDWORDKey()");
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushBool(pciSlot->GetBool());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementValueByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementValueByUDWORDKey()");
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushBool(pciSlot->GetBool());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementValueBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementValueBySQWORDKey()");
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushBool(pciSlot->GetBool());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementValueByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementValueByUQWORDKey()");
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushBool(pciSlot->GetBool());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementValueByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementValueByDoubleKey()");
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushBool(pciSlot->GetBool());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementValueByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementValueByStringKey()");
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushBool(pciSlot->GetBool());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementValueByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementValueByRopeKey()");
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushBool(pciSlot->GetBool());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementValueByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementValueByPPortKey()");
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushBool(pciSlot->GetBool());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementValueByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementValueByIPv4AddressKey()");
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushBool(pciSlot->GetBool());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementValueByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementValueByBoolKey()");
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushByte(pciSlot->GetByte());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementValueByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementValueByByteKey()");
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushByte(pciSlot->GetByte());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementValueBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementValueBySDWORDKey()");
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushByte(pciSlot->GetByte());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementValueByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementValueByUDWORDKey()");
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushByte(pciSlot->GetByte());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementValueBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementValueBySQWORDKey()");
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushByte(pciSlot->GetByte());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementValueByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementValueByUQWORDKey()");
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushByte(pciSlot->GetByte());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementValueByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementValueByDoubleKey()");
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushByte(pciSlot->GetByte());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementValueByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementValueByStringKey()");
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushByte(pciSlot->GetByte());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementValueByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementValueByRopeKey()");
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushByte(pciSlot->GetByte());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementValueByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementValueByPPortKey()");
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushByte(pciSlot->GetByte());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementValueByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementValueByIPv4AddressKey()");
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushByte(pciSlot->GetByte());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementValueByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementValueByBoolKey()");
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushSDWORD(pciSlot->GetSDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementValueByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementValueByByteKey()");
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushSDWORD(pciSlot->GetSDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementValueBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementValueBySDWORDKey()");
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushSDWORD(pciSlot->GetSDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementValueByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementValueByUDWORDKey()");
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushSDWORD(pciSlot->GetSDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementValueBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementValueBySQWORDKey()");
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushSDWORD(pciSlot->GetSDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementValueByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementValueByUQWORDKey()");
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushSDWORD(pciSlot->GetSDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementValueByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementValueByDoubleKey()");
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushSDWORD(pciSlot->GetSDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementValueByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementValueByStringKey()");
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushSDWORD(pciSlot->GetSDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementValueByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementValueByRopeKey()");
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushSDWORD(pciSlot->GetSDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementValueByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementValueByPPortKey()");
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushSDWORD(pciSlot->GetSDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementValueByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementValueByIPv4AddressKey()");
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushSDWORD(pciSlot->GetSDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementValueByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementValueByBoolKey()");
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushUDWORD(pciSlot->GetUDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementValueByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementValueByByteKey()");
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushUDWORD(pciSlot->GetUDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementValueBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementValueBySDWORDKey()");
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushUDWORD(pciSlot->GetUDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementValueByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementValueByUDWORDKey()");
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushUDWORD(pciSlot->GetUDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementValueBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementValueBySQWORDKey()");
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushUDWORD(pciSlot->GetUDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementValueByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementValueByUQWORDKey()");
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushUDWORD(pciSlot->GetUDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementValueByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementValueByDoubleKey()");
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushUDWORD(pciSlot->GetUDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementValueByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementValueByStringKey()");
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushUDWORD(pciSlot->GetUDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementValueByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementValueByRopeKey()");
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushUDWORD(pciSlot->GetUDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementValueByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementValueByPPortKey()");
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushUDWORD(pciSlot->GetUDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementValueByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementValueByIPv4AddressKey()");
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushUDWORD(pciSlot->GetUDWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementValueByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementValueByBoolKey()");
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushSQWORD(pciSlot->GetSQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementValueByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementValueByByteKey()");
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushSQWORD(pciSlot->GetSQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementValueBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementValueBySDWORDKey()");
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushSQWORD(pciSlot->GetSQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementValueByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementValueByUDWORDKey()");
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushSQWORD(pciSlot->GetSQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementValueBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementValueBySQWORDKey()");
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushSQWORD(pciSlot->GetSQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementValueByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementValueByUQWORDKey()");
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushSQWORD(pciSlot->GetSQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementValueByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementValueByDoubleKey()");
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushSQWORD(pciSlot->GetSQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementValueByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementValueByStringKey()");
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushSQWORD(pciSlot->GetSQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementValueByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementValueByRopeKey()");
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushSQWORD(pciSlot->GetSQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementValueByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementValueByPPortKey()");
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushSQWORD(pciSlot->GetSQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementValueByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementValueByIPv4AddressKey()");
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushSQWORD(pciSlot->GetSQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementValueByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementValueByBoolKey()");
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushUQWORD(pciSlot->GetUQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementValueByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementValueByByteKey()");
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushUQWORD(pciSlot->GetUQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementValueBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementValueBySDWORDKey()");
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushUQWORD(pciSlot->GetUQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementValueByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementValueByUDWORDKey()");
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushUQWORD(pciSlot->GetUQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementValueBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementValueBySQWORDKey()");
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushUQWORD(pciSlot->GetUQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementValueByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementValueByUQWORDKey()");
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushUQWORD(pciSlot->GetUQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementValueByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementValueByDoubleKey()");
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushUQWORD(pciSlot->GetUQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementValueByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementValueByStringKey()");
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushUQWORD(pciSlot->GetUQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementValueByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementValueByRopeKey()");
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushUQWORD(pciSlot->GetUQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementValueByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementValueByPPortKey()");
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushUQWORD(pciSlot->GetUQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementValueByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementValueByIPv4AddressKey()");
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushUQWORD(pciSlot->GetUQWORD());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementValueByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementValueByBoolKey()");
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushDouble(pciSlot->GetDouble());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementValueByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementValueByByteKey()");
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushDouble(pciSlot->GetDouble());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementValueBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementValueBySDWORDKey()");
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushDouble(pciSlot->GetDouble());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementValueByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementValueByUDWORDKey()");
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushDouble(pciSlot->GetDouble());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementValueBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementValueBySQWORDKey()");
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushDouble(pciSlot->GetDouble());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementValueByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementValueByUQWORDKey()");
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushDouble(pciSlot->GetDouble());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementValueByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementValueByDoubleKey()");
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushDouble(pciSlot->GetDouble());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementValueByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementValueByStringKey()");
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushDouble(pciSlot->GetDouble());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementValueByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementValueByRopeKey()");
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushDouble(pciSlot->GetDouble());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementValueByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementValueByPPortKey()");
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushDouble(pciSlot->GetDouble());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementValueByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementValueByIPv4AddressKey()");
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushDouble(pciSlot->GetDouble());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementValueByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementValueByBoolKey()");
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushStringObject(pciSlot->GetStringObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementValueByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementValueByByteKey()");
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushStringObject(pciSlot->GetStringObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementValueBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementValueBySDWORDKey()");
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushStringObject(pciSlot->GetStringObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementValueByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementValueByUDWORDKey()");
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushStringObject(pciSlot->GetStringObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementValueBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementValueBySQWORDKey()");
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushStringObject(pciSlot->GetStringObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementValueByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementValueByUQWORDKey()");
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushStringObject(pciSlot->GetStringObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementValueByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementValueByDoubleKey()");
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushStringObject(pciSlot->GetStringObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementValueByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementValueByStringKey()");
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushStringObject(pciSlot->GetStringObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementValueByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementValueByRopeKey()");
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushStringObject(pciSlot->GetStringObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementValueByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementValueByPPortKey()");
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushStringObject(pciSlot->GetStringObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementValueByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementValueByIPv4AddressKey()");
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushStringObject(pciSlot->GetStringObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementValueByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementValueByBoolKey()");
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushRopeObject(pciSlot->GetRopeObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementValueByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementValueByByteKey()");
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushRopeObject(pciSlot->GetRopeObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementValueBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementValueBySDWORDKey()");
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushRopeObject(pciSlot->GetRopeObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementValueByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementValueByUDWORDKey()");
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushRopeObject(pciSlot->GetRopeObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementValueBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementValueBySQWORDKey()");
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushRopeObject(pciSlot->GetRopeObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementValueByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementValueByUQWORDKey()");
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushRopeObject(pciSlot->GetRopeObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementValueByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementValueByDoubleKey()");
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushRopeObject(pciSlot->GetRopeObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementValueByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementValueByStringKey()");
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushRopeObject(pciSlot->GetRopeObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementValueByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementValueByRopeKey()");
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushRopeObject(pciSlot->GetRopeObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementValueByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementValueByPPortKey()");
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushRopeObject(pciSlot->GetRopeObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementValueByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementValueByIPv4AddressKey()");
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushRopeObject(pciSlot->GetRopeObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementValueByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementValueByBoolKey()");
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushIPv4AddressObject(pciSlot->GetIPv4AddressObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementValueByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementValueByByteKey()");
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushIPv4AddressObject(pciSlot->GetIPv4AddressObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementValueBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementValueBySDWORDKey()");
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushIPv4AddressObject(pciSlot->GetIPv4AddressObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementValueByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementValueByUDWORDKey()");
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushIPv4AddressObject(pciSlot->GetIPv4AddressObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementValueBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementValueBySQWORDKey()");
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushIPv4AddressObject(pciSlot->GetIPv4AddressObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementValueByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementValueByUQWORDKey()");
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushIPv4AddressObject(pciSlot->GetIPv4AddressObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementValueByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementValueByDoubleKey()");
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushIPv4AddressObject(pciSlot->GetIPv4AddressObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementValueByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementValueByStringKey()");
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushIPv4AddressObject(pciSlot->GetIPv4AddressObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementValueByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementValueByRopeKey()");
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushIPv4AddressObject(pciSlot->GetIPv4AddressObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementValueByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementValueByPPortKey()");
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushIPv4AddressObject(pciSlot->GetIPv4AddressObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementValueByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementValueByIPv4AddressKey()");
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushIPv4AddressObject(pciSlot->GetIPv4AddressObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementValueByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementValueByBoolKey()");
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushPPortObject(pciSlot->GetPPortObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementValueByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementValueByByteKey()");
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushPPortObject(pciSlot->GetPPortObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementValueBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementValueBySDWORDKey()");
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushPPortObject(pciSlot->GetPPortObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementValueByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementValueByUDWORDKey()");
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushPPortObject(pciSlot->GetPPortObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementValueBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementValueBySQWORDKey()");
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushPPortObject(pciSlot->GetPPortObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementValueByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementValueByUQWORDKey()");
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushPPortObject(pciSlot->GetPPortObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementValueByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementValueByDoubleKey()");
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushPPortObject(pciSlot->GetPPortObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementValueByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementValueByStringKey()");
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushPPortObject(pciSlot->GetPPortObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementValueByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementValueByRopeKey()");
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushPPortObject(pciSlot->GetPPortObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementValueByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementValueByPPortKey()");
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushPPortObject(pciSlot->GetPPortObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementValueByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementValueByIPv4AddressKey()");
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushPPortObject(pciSlot->GetPPortObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadStringValueFromAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadStringValueFromAddress()");
  CZVMString ** ppciString = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushStringObject(*ppciString);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadRopeValueFromAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadRopeValueFromAddress()");
  CZVMRope ** ppciRope = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushRopeObject(*ppciRope);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadIPv4AddressValueFromAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadIPv4AddressValueFromAddress()");
  CZVMIPv4Address ** ppciIPv4Address = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushIPv4AddressObject(*ppciIPv4Address);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadPPortValueFromAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadPPortValueFromAddress()");
  CZVMPPort ** ppciPPort = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushPPortObject(*ppciPPort);
  return 1;
}


TZVMIndex CZVMVirtualThread::_indirectLoadTableValueFromAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_indirectLoadTableValueFromAddresse()");
                                                 // 采用CchZVM_VOID_TYPE_TAG表示不再检测table的具体类型了
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushTableObject(*ppciTable);
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolConstantValue()
{
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  UCHAR uch = pciInstruction->GetOperandAsUCHAR();
  PushBool(static_cast<bool>(uch));
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteConstantValue()
{
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  UCHAR uch = pciInstruction->GetOperandAsUCHAR();
  PushByte(uch);
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDConstantValue()
{
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  SDWORD sdw = pciInstruction->GetOperandAsSDWORD();
  PushSDWORD(sdw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDConstantValue()
{
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  UDWORD udw = pciInstruction->GetOperandAsUDWORD();
  PushUDWORD(udw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDConstantValue()
{
  const CConstantPool * pciConstantPool = _ciPCRegister.GetConstantPool();
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  TZVMIndex iLiteral = pciInstruction->GetOperandAsTZVMIndex();
  SQWORD sqw = pciConstantPool->GetAsSQWORD(iLiteral);
  PushSQWORD(sqw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDConstantValue()
{
  const CConstantPool * pciConstantPool = _ciPCRegister.GetConstantPool();
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  TZVMIndex iLiteral = pciInstruction->GetOperandAsTZVMIndex();
  UQWORD uqw = pciConstantPool->GetAsUQWORD(iLiteral);
  PushUQWORD(uqw);
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleConstantValue()
{
  const CConstantPool * pciConstantPool = _ciPCRegister.GetConstantPool();
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  TZVMIndex iLiteral = pciInstruction->GetOperandAsTZVMIndex();
  double df = pciConstantPool->GetAsDouble(iLiteral);
  PushDouble(df);
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringConstantValue()
{
  const CConstantPool * pciConstantPool = _ciPCRegister.GetConstantPool();
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  TZVMIndex iLiteral = pciInstruction->GetOperandAsTZVMIndex();
  const CZVMString * pci = pciConstantPool->GetAsBinaryString(iLiteral);
  PushStringObject(pci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeConstantValue()
{
  const CConstantPool * pciConstantPool = _ciPCRegister.GetConstantPool();
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  TZVMIndex iLiteral = pciInstruction->GetOperandAsTZVMIndex();
  const CZVMRope * pci = pciConstantPool->GetAsRopeString(iLiteral);
  PushRopeObject(pci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressConstantValue()
{
  const CConstantPool * pciConstantPool = _ciPCRegister.GetConstantPool();
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  TZVMIndex iLiteral = pciInstruction->GetOperandAsTZVMIndex();
  const CZVMIPv4Address * pci = pciConstantPool->GetAsIPv4Address(iLiteral);
  PushIPv4AddressObject(pci);
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortConstantValue()
{
  const CConstantPool * pciConstantPool = _ciPCRegister.GetConstantPool();
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  TZVMIndex iLiteral = pciInstruction->GetOperandAsTZVMIndex();
  const CZVMPPort * pci = pciConstantPool->GetAsPPort(iLiteral);
  PushPPortObject(pci);
  return 1;
}


