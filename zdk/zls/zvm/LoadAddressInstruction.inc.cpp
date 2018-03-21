/******************************************************************************
 * Load value指令Interpreter
 ******************************************************************************/
TZVMIndex CZVMVirtualThread::_loadBoolGlobalVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolGlobalVariableAddress()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BOOL, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushBoolAddress(pciSlot->GetBoolAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteGlobalVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteGlobalVariableAddress()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BYTE, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushByteAddress(pciSlot->GetByteAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDGlobalVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDGlobalVariableAddress()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORDAddress(pciSlot->GetSDWORDAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDGlobalVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDGlobalVariableAddress()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORDAddress(pciSlot->GetUDWORDAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDGlobalVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDGlobalVariableAddress()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORDAddress(pciSlot->GetSQWORDAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDGlobalVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDGlobalVariableAddress()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORDAddress(pciSlot->GetUQWORDAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleGlobalVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleGlobalVariableAddress()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_DOUBLE, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushDoubleAddress(pciSlot->GetDoubleAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringGlobalVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringGlobalVariableAddress()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushStringObjectAddress(pciSlot->GetStringObjectAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeGlobalVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeGlobalVariableAddress()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ROPE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortGlobalVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortGlobalVariableAddress()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressGlobalVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressGlobalVariableAddress()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadTableGlobalVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadTableGlobalVariableAddress()");
  CSlot * pciSlot = GetGlobalVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushTableObjectAddress(pciSlot->GetTableObjectAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolStackVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolStackVariableAddress()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BOOL, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushBoolAddress(pciSlot->GetBoolAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteStackVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteStackVariableAddress()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BYTE, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushByteAddress(pciSlot->GetByteAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDStackVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDStackVariableAddress()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORDAddress(pciSlot->GetSDWORDAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDStackVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDStackVariableAddress()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORDAddress(pciSlot->GetUDWORDAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDStackVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDStackVariableAddress()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORDAddress(pciSlot->GetSQWORDAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDStackVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDStackVariableAddress()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORDAddress(pciSlot->GetUQWORDAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleStackVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleStackVariableAddress()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_DOUBLE, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushDoubleAddress(pciSlot->GetDoubleAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringStackVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringStackVariableAddress()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushStringObjectAddress(pciSlot->GetStringObjectAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeStackVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeStackVariableAddress()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ROPE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressStackVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressStackVariableAddress()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortStackVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortStackVariableAddress()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadTableStackVariableAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadTableStackVariableAddress()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushTableObjectAddress(pciSlot->GetTableObjectAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadReferenceStackVariableReferenceToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadReferenceStackVariableReferenceToAddress()");
  CSlot * pciSlot = GetStackVariableSlot();
  ZVM_SLOT_MASK_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS, __FILE__, __PRETTY_FUNC__, __LINE__);
  memcpy(PrefixIncreaseSPRegister(), pciSlot, sizeof(CSlot));
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementAddressByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementAddressByBoolKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  ReplaceAsBoolAddress(pciSlot->GetBoolAddress());
  #else
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushBoolAddress(pciSlot->GetBoolAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementAddressByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementAddressByByteKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  ReplaceAsBoolAddress(pciSlot->GetBoolAddress());
  #else
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushBoolAddress(pciSlot->GetBoolAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementAddressBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementAddressBySDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  ReplaceAsBoolAddress(pciSlot->GetBoolAddress());
  #else
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushBoolAddress(pciSlot->GetBoolAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementAddressByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementAddressByUDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  ReplaceAsBoolAddress(pciSlot->GetBoolAddress());
  #else
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushBoolAddress(pciSlot->GetBoolAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementAddressBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementAddressBySQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  ReplaceAsBoolAddress(pciSlot->GetBoolAddress());
  #else
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushBoolAddress(pciSlot->GetBoolAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementAddressByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementAddressByUQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  ReplaceAsBoolAddress(pciSlot->GetBoolAddress());
  #else
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushBoolAddress(pciSlot->GetBoolAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementAddressByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementAddressByDoubleKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  ReplaceAsBoolAddress(pciSlot->GetBoolAddress());
  #else
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushBoolAddress(pciSlot->GetBoolAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementAddressByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementAddressByStringKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  ReplaceAsBoolAddress(pciSlot->GetBoolAddress());
  #else
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushBoolAddress(pciSlot->GetBoolAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementAddressByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementAddressByRopeKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  ReplaceAsBoolAddress(pciSlot->GetBoolAddress());
  #else
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushBoolAddress(pciSlot->GetBoolAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementAddressByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementAddressByPPortKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  ReplaceAsBoolAddress(pciSlot->GetBoolAddress());
  #else
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushBoolAddress(pciSlot->GetBoolAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadBoolTableElementAddressByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadBoolTableElementAddressByIPv4AddressKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  ReplaceAsBoolAddress(pciSlot->GetBoolAddress());
  #else
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BOOL_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushBoolAddress(pciSlot->GetBoolAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementAddressByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementAddressByBoolKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  ReplaceAsByteAddress(pciSlot->GetByteAddress());
  #else
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushByteAddress(pciSlot->GetByteAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementAddressByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementAddressByByteKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  ReplaceAsByteAddress(pciSlot->GetByteAddress());
  #else
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushByteAddress(pciSlot->GetByteAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementAddressBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementAddressBySDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  ReplaceAsByteAddress(pciSlot->GetByteAddress());
  #else
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushByteAddress(pciSlot->GetByteAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementAddressByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementAddressByUDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  ReplaceAsByteAddress(pciSlot->GetByteAddress());
  #else
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushByteAddress(pciSlot->GetByteAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementAddressBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementAddressBySQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  ReplaceAsByteAddress(pciSlot->GetByteAddress());
  #else
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushByteAddress(pciSlot->GetByteAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementAddressByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementAddressByUQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  ReplaceAsByteAddress(pciSlot->GetByteAddress());
  #else
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushByteAddress(pciSlot->GetByteAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementAddressByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementAddressByDoubleKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  ReplaceAsByteAddress(pciSlot->GetByteAddress());
  #else
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushByteAddress(pciSlot->GetByteAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementAddressByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementAddressByStringKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  ReplaceAsByteAddress(pciSlot->GetByteAddress());
  #else
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushByteAddress(pciSlot->GetByteAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementAddressByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementAddressByRopeKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  ReplaceAsByteAddress(pciSlot->GetByteAddress());
  #else
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushByteAddress(pciSlot->GetByteAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementAddressByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementAddressByPPortKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  ReplaceAsByteAddress(pciSlot->GetByteAddress());
  #else
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushByteAddress(pciSlot->GetByteAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadByteTableElementAddressByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadByteTableElementAddressByIPv4AddressKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  ReplaceAsByteAddress(pciSlot->GetByteAddress());
  #else
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_BYTE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushByteAddress(pciSlot->GetByteAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementAddressByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementAddressByBoolKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  ReplaceAsSDWORDAddress(pciSlot->GetSDWORDAddress());
  #else
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushSDWORDAddress(pciSlot->GetSDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementAddressByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementAddressByByteKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  ReplaceAsSDWORDAddress(pciSlot->GetSDWORDAddress());
  #else
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushSDWORDAddress(pciSlot->GetSDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementAddressBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementAddressBySDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  ReplaceAsSDWORDAddress(pciSlot->GetSDWORDAddress());
  #else
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushSDWORDAddress(pciSlot->GetSDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementAddressByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementAddressByUDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  ReplaceAsSDWORDAddress(pciSlot->GetSDWORDAddress());
  #else
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushSDWORDAddress(pciSlot->GetSDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementAddressBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementAddressBySQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  ReplaceAsSDWORDAddress(pciSlot->GetSDWORDAddress());
  #else
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushSDWORDAddress(pciSlot->GetSDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementAddressByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementAddressByUQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  ReplaceAsSDWORDAddress(pciSlot->GetSDWORDAddress());
  #else
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushSDWORDAddress(pciSlot->GetSDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementAddressByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementAddressByDoubleKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  ReplaceAsSDWORDAddress(pciSlot->GetSDWORDAddress());
  #else
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushSDWORDAddress(pciSlot->GetSDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementAddressByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementAddressByStringKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  ReplaceAsSDWORDAddress(pciSlot->GetSDWORDAddress());
  #else
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushSDWORDAddress(pciSlot->GetSDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementAddressByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementAddressByRopeKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  ReplaceAsSDWORDAddress(pciSlot->GetSDWORDAddress());
  #else
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushSDWORDAddress(pciSlot->GetSDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementAddressByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementAddressByPPortKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  ReplaceAsSDWORDAddress(pciSlot->GetSDWORDAddress());
  #else
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushSDWORDAddress(pciSlot->GetSDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSDWORDTableElementAddressByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSDWORDTableElementAddressByIPv4AddressKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  ReplaceAsSDWORDAddress(pciSlot->GetSDWORDAddress());
  #else
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushSDWORDAddress(pciSlot->GetSDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementAddressByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementAddressByBoolKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  ReplaceAsUDWORDAddress(pciSlot->GetUDWORDAddress());
  #else
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushUDWORDAddress(pciSlot->GetUDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementAddressByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementAddressByByteKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  ReplaceAsUDWORDAddress(pciSlot->GetUDWORDAddress());
  #else
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushUDWORDAddress(pciSlot->GetUDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementAddressBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementAddressBySDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  ReplaceAsUDWORDAddress(pciSlot->GetUDWORDAddress());
  #else
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushUDWORDAddress(pciSlot->GetUDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementAddressByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementAddressByUDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  ReplaceAsUDWORDAddress(pciSlot->GetUDWORDAddress());
  #else
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushUDWORDAddress(pciSlot->GetUDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementAddressBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementAddressBySQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  ReplaceAsUDWORDAddress(pciSlot->GetUDWORDAddress());
  #else
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushUDWORDAddress(pciSlot->GetUDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementAddressByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementAddressByUQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  ReplaceAsUDWORDAddress(pciSlot->GetUDWORDAddress());
  #else
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushUDWORDAddress(pciSlot->GetUDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementAddressByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementAddressByDoubleKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  ReplaceAsUDWORDAddress(pciSlot->GetUDWORDAddress());
  #else
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushUDWORDAddress(pciSlot->GetUDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementAddressByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementAddressByStringKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  ReplaceAsUDWORDAddress(pciSlot->GetUDWORDAddress());
  #else
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushUDWORDAddress(pciSlot->GetUDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementAddressByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementAddressByRopeKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  ReplaceAsUDWORDAddress(pciSlot->GetUDWORDAddress());
  #else
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushUDWORDAddress(pciSlot->GetUDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementAddressByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementAddressByPPortKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  ReplaceAsUDWORDAddress(pciSlot->GetUDWORDAddress());
  #else
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushUDWORDAddress(pciSlot->GetUDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUDWORDTableElementAddressByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUDWORDTableElementAddressByIPv4AddressKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  ReplaceAsUDWORDAddress(pciSlot->GetUDWORDAddress());
  #else
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UDWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushUDWORDAddress(pciSlot->GetUDWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementAddressByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementAddressByBoolKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  ReplaceAsSQWORDAddress(pciSlot->GetSQWORDAddress());
  #else
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushSQWORDAddress(pciSlot->GetSQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementAddressByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementAddressByByteKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  ReplaceAsSQWORDAddress(pciSlot->GetSQWORDAddress());
  #else
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushSQWORDAddress(pciSlot->GetSQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementAddressBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementAddressBySDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  ReplaceAsSQWORDAddress(pciSlot->GetSQWORDAddress());
  #else
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushSQWORDAddress(pciSlot->GetSQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementAddressByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementAddressByUDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  ReplaceAsSQWORDAddress(pciSlot->GetSQWORDAddress());
  #else
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushSQWORDAddress(pciSlot->GetSQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementAddressBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementAddressBySQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  ReplaceAsSQWORDAddress(pciSlot->GetSQWORDAddress());
  #else
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushSQWORDAddress(pciSlot->GetSQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementAddressByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementAddressByUQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  ReplaceAsSQWORDAddress(pciSlot->GetSQWORDAddress());
  #else
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushSQWORDAddress(pciSlot->GetSQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementAddressByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementAddressByDoubleKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  ReplaceAsSQWORDAddress(pciSlot->GetSQWORDAddress());
  #else
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushSQWORDAddress(pciSlot->GetSQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementAddressByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementAddressByStringKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  ReplaceAsSQWORDAddress(pciSlot->GetSQWORDAddress());
  #else
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushSQWORDAddress(pciSlot->GetSQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementAddressByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementAddressByRopeKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  ReplaceAsSQWORDAddress(pciSlot->GetSQWORDAddress());
  #else
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushSQWORDAddress(pciSlot->GetSQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementAddressByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementAddressByPPortKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  ReplaceAsSQWORDAddress(pciSlot->GetSQWORDAddress());
  #else
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushSQWORDAddress(pciSlot->GetSQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadSQWORDTableElementAddressByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadSQWORDTableElementAddressByIPv4AddressKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  ReplaceAsSQWORDAddress(pciSlot->GetSQWORDAddress());
  #else
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_SQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushSQWORDAddress(pciSlot->GetSQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementAddressByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementAddressByBoolKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  ReplaceAsUQWORDAddress(pciSlot->GetUQWORDAddress());
  #else
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushUQWORDAddress(pciSlot->GetUQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementAddressByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementAddressByByteKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  ReplaceAsUQWORDAddress(pciSlot->GetUQWORDAddress());
  #else
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushUQWORDAddress(pciSlot->GetUQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementAddressBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementAddressBySDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  ReplaceAsUQWORDAddress(pciSlot->GetUQWORDAddress());
  #else
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushUQWORDAddress(pciSlot->GetUQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementAddressByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementAddressByUDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  ReplaceAsUQWORDAddress(pciSlot->GetUQWORDAddress());
  #else
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushUQWORDAddress(pciSlot->GetUQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementAddressBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementAddressBySQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  ReplaceAsUQWORDAddress(pciSlot->GetUQWORDAddress());
  #else
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushUQWORDAddress(pciSlot->GetUQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementAddressByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementAddressByUQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  ReplaceAsUQWORDAddress(pciSlot->GetUQWORDAddress());
  #else
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushUQWORDAddress(pciSlot->GetUQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementAddressByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementAddressByDoubleKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  ReplaceAsUQWORDAddress(pciSlot->GetUQWORDAddress());
  #else
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushUQWORDAddress(pciSlot->GetUQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementAddressByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementAddressByStringKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  ReplaceAsUQWORDAddress(pciSlot->GetUQWORDAddress());
  #else
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushUQWORDAddress(pciSlot->GetUQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementAddressByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementAddressByRopeKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  ReplaceAsUQWORDAddress(pciSlot->GetUQWORDAddress());
  #else
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushUQWORDAddress(pciSlot->GetUQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementAddressByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementAddressByPPortKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  ReplaceAsUQWORDAddress(pciSlot->GetUQWORDAddress());
  #else
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushUQWORDAddress(pciSlot->GetUQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadUQWORDTableElementAddressByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadUQWORDTableElementAddressByIPv4AddressKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  ReplaceAsUQWORDAddress(pciSlot->GetUQWORDAddress());
  #else
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_UQWORD_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushUQWORDAddress(pciSlot->GetUQWORDAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementAddressByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementAddressByBoolKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  ReplaceAsDoubleAddress(pciSlot->GetDoubleAddress());
  #else
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushDoubleAddress(pciSlot->GetDoubleAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementAddressByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementAddressByByteKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  ReplaceAsDoubleAddress(pciSlot->GetDoubleAddress());
  #else
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushDoubleAddress(pciSlot->GetDoubleAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementAddressBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementAddressBySDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  ReplaceAsDoubleAddress(pciSlot->GetDoubleAddress());
  #else
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushDoubleAddress(pciSlot->GetDoubleAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementAddressByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementAddressByUDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  ReplaceAsDoubleAddress(pciSlot->GetDoubleAddress());
  #else
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushDoubleAddress(pciSlot->GetDoubleAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementAddressBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementAddressBySQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  ReplaceAsDoubleAddress(pciSlot->GetDoubleAddress());
  #else
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushDoubleAddress(pciSlot->GetDoubleAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementAddressByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementAddressByUQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  ReplaceAsDoubleAddress(pciSlot->GetDoubleAddress());
  #else
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushDoubleAddress(pciSlot->GetDoubleAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementAddressByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementAddressByDoubleKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  ReplaceAsDoubleAddress(pciSlot->GetDoubleAddress());
  #else
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushDoubleAddress(pciSlot->GetDoubleAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementAddressByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementAddressByStringKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  ReplaceAsDoubleAddress(pciSlot->GetDoubleAddress());
  #else
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushDoubleAddress(pciSlot->GetDoubleAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementAddressByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementAddressByRopeKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  ReplaceAsDoubleAddress(pciSlot->GetDoubleAddress());
  #else
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushDoubleAddress(pciSlot->GetDoubleAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementAddressByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementAddressByPPortKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  ReplaceAsDoubleAddress(pciSlot->GetDoubleAddress());
  #else
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushDoubleAddress(pciSlot->GetDoubleAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadDoubleTableElementAddressByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadDoubleTableElementAddressByIPv4AddressKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  ReplaceAsDoubleAddress(pciSlot->GetDoubleAddress());
  #else
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_DOUBLE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushDoubleAddress(pciSlot->GetDoubleAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementAddressByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementAddressByBoolKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  ReplaceAsStringObjectAddress(pciSlot->GetStringObjectAddress());
  #else
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushStringObjectAddress(pciSlot->GetStringObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementAddressByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementAddressByByteKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  ReplaceAsStringObjectAddress(pciSlot->GetStringObjectAddress());
  #else
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushStringObjectAddress(pciSlot->GetStringObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementAddressBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementAddressBySDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  ReplaceAsStringObjectAddress(pciSlot->GetStringObjectAddress());
  #else
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushStringObjectAddress(pciSlot->GetStringObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementAddressByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementAddressByUDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  ReplaceAsStringObjectAddress(pciSlot->GetStringObjectAddress());
  #else
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushStringObjectAddress(pciSlot->GetStringObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementAddressBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementAddressBySQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  ReplaceAsStringObjectAddress(pciSlot->GetStringObjectAddress());
  #else
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushStringObjectAddress(pciSlot->GetStringObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementAddressByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementAddressByUQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  ReplaceAsStringObjectAddress(pciSlot->GetStringObjectAddress());
  #else
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushStringObjectAddress(pciSlot->GetStringObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementAddressByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementAddressByDoubleKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  ReplaceAsStringObjectAddress(pciSlot->GetStringObjectAddress());
  #else
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushStringObjectAddress(pciSlot->GetStringObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementAddressByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementAddressByStringKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  ReplaceAsStringObjectAddress(pciSlot->GetStringObjectAddress());
  #else
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushStringObjectAddress(pciSlot->GetStringObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementAddressByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementAddressByRopeKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  ReplaceAsStringObjectAddress(pciSlot->GetStringObjectAddress());
  #else
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushStringObjectAddress(pciSlot->GetStringObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementAddressByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementAddressByPPortKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  ReplaceAsStringObjectAddress(pciSlot->GetStringObjectAddress());
  #else
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushStringObjectAddress(pciSlot->GetStringObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadStringTableElementAddressByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadStringTableElementAddressByIPv4AddressKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  ReplaceAsStringObjectAddress(pciSlot->GetStringObjectAddress());
  #else
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_STRING_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushStringObjectAddress(pciSlot->GetStringObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementAddressByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementAddressByBoolKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  ReplaceAsRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #else
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementAddressByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementAddressByByteKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  ReplaceAsRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #else
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementAddressBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementAddressBySDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  ReplaceAsRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #else
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementAddressByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementAddressByUDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  ReplaceAsRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #else
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementAddressBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementAddressBySQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  ReplaceAsRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #else
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementAddressByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementAddressByUQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  ReplaceAsRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #else
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementAddressByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementAddressByDoubleKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  ReplaceAsRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #else
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementAddressByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementAddressByStringKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  ReplaceAsRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #else
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementAddressByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementAddressByRopeKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  ReplaceAsRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #else
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementAddressByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementAddressByPPortKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  ReplaceAsRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #else
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeTableElementAddressByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadRopeTableElementAddressByIPv4AddressKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  ReplaceAsRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #else
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_ROPE_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushRopeObjectAddress(pciSlot->GetRopeObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementAddressByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementAddressByBoolKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  ReplaceAsIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #else
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementAddressByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementAddressByByteKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  ReplaceAsIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #else
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementAddressBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementAddressBySDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  ReplaceAsIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #else
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementAddressByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementAddressByUDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  ReplaceAsIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #else
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementAddressBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementAddressBySQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  ReplaceAsIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #else
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementAddressByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementAddressByUQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  ReplaceAsIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #else
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementAddressByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementAddressByDoubleKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  ReplaceAsIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #else
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementAddressByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementAddressByStringKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  ReplaceAsIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #else
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementAddressByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementAddressByRopeKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  ReplaceAsIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #else
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementAddressByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementAddressByPPortKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  ReplaceAsIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #else
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressTableElementAddressByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadIPv4AddressTableElementAddressByIPv4AddressKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  ReplaceAsIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #else
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_IPv4ADDR_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushIPv4AddressObjectAddress(pciSlot->GetIPv4AddressObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementAddressByBoolKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementAddressByBoolKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  ReplaceAsPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #else
  bool bKey = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](bKey);
  PushPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementAddressByByteKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementAddressByByteKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  ReplaceAsPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #else
  UCHAR uchKey = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uchKey);
  PushPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementAddressBySDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementAddressBySDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  ReplaceAsPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #else
  SDWORD sdwKey = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sdwKey);
  PushPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementAddressByUDWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementAddressByUDWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  ReplaceAsPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #else
  UDWORD udwKey = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](udwKey);
  PushPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementAddressBySQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementAddressBySQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  ReplaceAsPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #else
  SQWORD sqwKey = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](sqwKey);
  PushPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementAddressByUQWORDKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementAddressByUQWORDKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  ReplaceAsPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #else
  UQWORD uqwKey = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](uqwKey);
  PushPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementAddressByDoubleKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementAddressByDoubleKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  ReplaceAsPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #else
  double dfKey = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](dfKey);
  PushPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementAddressByStringKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementAddressByStringKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  ReplaceAsPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #else
  CZVMString ** ppciStringKey = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciStringKey);
  PushPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementAddressByRopeKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementAddressByRopeKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  ReplaceAsPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #else
  CZVMRope ** ppciRopeKey = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciRopeKey);
  PushPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementAddressByPPortKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementAddressByPPortKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  ReplaceAsPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #else
  CZVMPPort ** ppciPPortKey = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciPPortKey);
  PushPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortTableElementAddressByIPv4AddressKey()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_loadPPortTableElementAddressByIPv4AddressKey()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = TOP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  ReplaceAsPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #else
  CZVMIPv4Address ** ppciIPv4AddressKey = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciTable = POP_TABLE_OBJECT_ADDRESS(CchZVM_PPORT_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = (*ppciTable)->operator[](*ppciIPv4AddressKey);
  PushPPortObjectAddress(pciSlot->GetPPortObjectAddress());
  #endif
  return 1;
}


/* 2001/7/17: Discarded
TZVMIndex CZVMVirtualThread::_convertStringValueToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_convertStringValueToAddress()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString * pciString = QUICK_TOP_STRING_OBJECT(__FILE__, __PRETTY_FUNC__, __LINE__);
  _ciStringObjectRegister.Replace(pciString);
  ReplaceAsStringObjectAddress(_ciStringObjectRegister.GetObjectAddress());
  #else
  CZVMString * pciString = QUICK_POP_STRING_OBJECT(__FILE__, __PRETTY_FUNC__, __LINE__);
  _ciStringObjectRegister.Replace(pciString);
  PushStringObjectAddress(_ciStringObjectRegister.GetObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_convertIPv4AddressValueToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_convertIPv4AddressValueToAddress()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMIPv4Address * pciIPv4Address = QUICK_TOP_IPv4ADDRESS_OBJECT(__FILE__, __PRETTY_FUNC__, __LINE__);
  _ciIPv4AddressObjectRegister.Replace(pciIPv4Address);
  ReplaceAsIPv4AddressObjectAddress(_ciIPv4AddressObjectRegister.GetObjectAddress());
  #else
  CZVMIPv4Address * pciIPv4Address = QUICK_POP_IPv4ADDRESS_OBJECT(__FILE__, __PRETTY_FUNC__, __LINE__);
  _ciIPv4AddressObjectRegister.Replace(pciIPv4Address);
  PushIPv4AddressObjectAddress(_ciIPv4AddressObjectRegister.GetObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_convertPPortValueToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_convertPPortValueToAddress()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort * pciPPort = QUICK_TOP_PPORT_OBJECT(__FILE__, __PRETTY_FUNC__, __LINE__);
  _ciPPortObjectRegister.Replace(pciPPort);
  ReplaceAsPPortObjectAddress(_ciPPortObjectRegister.GetObjectAddress());
  #else
  CZVMPPort * pciPPort = QUICK_POP_PPORT_OBJECT(__FILE__, __PRETTY_FUNC__, __LINE__);
  _ciPPortObjectRegister.Replace(pciPPort);
  PushPPortObjectAddress(_ciPPortObjectRegister.GetObjectAddress());
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_convertTableValueToAddress()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_convertTableValueToAddress()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMTable * pciTable = QUICK_TOP_TABLE_OBJECT(__FILE__, __PRETTY_FUNC__, __LINE__);
  _ciTableObjectRegister.Replace(pciTable);
  ReplaceAsTableObjectAddress(_ciTableObjectRegister.GetObjectAddress());
  #else
  CZVMTable * pciTable = QUICK_POP_TABLE_OBJECT(__FILE__, __PRETTY_FUNC__, __LINE__);
  _ciTableObjectRegister.Replace(pciTable);
  PushTableObjectAddress(_ciTableObjectRegister.GetObjectAddress());
  #endif
  return 1;
}
*/


TZVMIndex CZVMVirtualThread::_loadStringConstantAddress()
{
  const CConstantPool * pciConstantPool = _ciPCRegister.GetConstantPool();
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  TZVMIndex iLiteral = pciInstruction->GetOperandAsTZVMIndex();
  const CZVMString * const * ppci = pciConstantPool->GetAsPointerOfBinaryStringPointer(iLiteral);
  PushStringObjectAddress(const_cast<CZVMString **>(ppci));
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadRopeConstantAddress()
{
  const CConstantPool * pciConstantPool = _ciPCRegister.GetConstantPool();
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  TZVMIndex iLiteral = pciInstruction->GetOperandAsTZVMIndex();
  const CZVMRope * const * ppci = pciConstantPool->GetAsPointerOfRopeStringPointer(iLiteral);
  PushRopeObjectAddress(const_cast<CZVMRope **>(ppci));
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadIPv4AddressConstantAddress()
{
  const CConstantPool * pciConstantPool = _ciPCRegister.GetConstantPool();
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  TZVMIndex iLiteral = pciInstruction->GetOperandAsTZVMIndex();
  const CZVMIPv4Address * const * ppci = pciConstantPool->GetAsPointerOfIPv4AddressPointer(iLiteral);
  PushIPv4AddressObjectAddress(const_cast<CZVMIPv4Address **>(ppci));
  return 1;
}


TZVMIndex CZVMVirtualThread::_loadPPortConstantAddress()
{
  const CConstantPool * pciConstantPool = _ciPCRegister.GetConstantPool();
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  TZVMIndex iLiteral = pciInstruction->GetOperandAsTZVMIndex();
  const CZVMPPort * const * ppci = pciConstantPool->GetAsPointerOfPPortPointer(iLiteral);
  PushPPortObjectAddress(const_cast<CZVMPPort **>(ppci));
  return 1;
}


