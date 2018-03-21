/******************************************************************************
 * Stack指令Interpreter
 ******************************************************************************/
TZVMIndex CZVMVirtualThread::_popAny()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_popAny()");
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  //ZVM_SLOT_MASK_ASSERT(pciSlot, CSlot::SLOT_TAG_ADDRESS, __FILE__, __PRETTY_FUNC__, __LINE__);
  return 1;
}


TZVMIndex CZVMVirtualThread::_popBool()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_popBool()");
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BOOL, __FILE__, __PRETTY_FUNC__, __LINE__);
  return 1;
}


TZVMIndex CZVMVirtualThread::_popByte()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_popByte()");
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_BYTE, __FILE__, __PRETTY_FUNC__, __LINE__);
  return 1;
}


TZVMIndex CZVMVirtualThread::_popSDWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_popSDWORD()");
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  return 1;
}


TZVMIndex CZVMVirtualThread::_popUDWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_popUDWORD()");
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  return 1;
}


TZVMIndex CZVMVirtualThread::_popSQWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_popSQWORD()");
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_SQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  return 1;
}


TZVMIndex CZVMVirtualThread::_popUQWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_popUQWORD()");
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_UQWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  return 1;
}


TZVMIndex CZVMVirtualThread::_popDouble()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_popDouble()");
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_DOUBLE, __FILE__, __PRETTY_FUNC__, __LINE__);
  return 1;
}


TZVMIndex CZVMVirtualThread::_popString()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_popString()");
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->~CSlot();
  return 1;
}


TZVMIndex CZVMVirtualThread::_popRope()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_popRope()");
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_ROPE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->~CSlot();
  return 1;
}


TZVMIndex CZVMVirtualThread::_popIPv4Address()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_popIPv4Address()");
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->~CSlot();
  return 1;
}


TZVMIndex CZVMVirtualThread::_popPPort()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_popPPort()");
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->~CSlot();
  return 1;
}


TZVMIndex CZVMVirtualThread::_popTable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_popTable()");
  CSlot * pciSlot = PostfixDecreaseSPRegister();
  ZVM_SLOT_ASSERT(pciSlot, CSlot::SLOT_TAG_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  pciSlot->~CSlot();
  return 1;
}


TZVMIndex CZVMVirtualThread::_ret()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_ret()");

  /* 好象用goto比用do...while速度还慢一点点
  __LOOP_RET_:
    CSlot * pciSlot = PostfixDecreaseSPRegister();
    CSlot::TSlotTag eTag = pciSlot->GetSlotTag();
    switch (eTag)
    {
      case CSlot::SLOT_TAG_BP_REGISTER:
        _pciBPRegister = pciSlot->GetSavedBPRegister();
        goto __LOOP_RET_;
        break;

      case CSlot::SLOT_TAG_PC_REGISTER:
        _ciPCRegister = pciSlot->GetSavedPCRegister();
        pciSlot->~CSlot();
        throw CZVMTriggerFunctionReturn();
        break;

      default:
        pciSlot->~CSlot();
        goto __LOOP_RET_;
        break;
    }
  */

  do {
    CSlot * pciSlot = PostfixDecreaseSPRegister();
    CSlot::TSlotTag eTag = pciSlot->GetSlotTag();
    switch (eTag)
    {
      case CSlot::SLOT_TAG_BP_REGISTER:
        _pciBPRegister = pciSlot->GetSavedBPRegister();
        break;

      case CSlot::SLOT_TAG_PC_REGISTER:
        _ciPCRegister = pciSlot->GetSavedPCRegister();
        pciSlot->~CSlot();
        throw EZVMTriggerFunctionReturn();
        break;

      default:
        pciSlot->~CSlot();
        break;
    }
  } while (true);

  return 1;
}


TZVMIndex CZVMVirtualThread::_pushBP()
{
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsSavedBPRegister(_pciBPRegister);
  _pciBPRegister = pciSlot;
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructBool()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructBool()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultBool();
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructByte()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructByte()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultByte();
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructSDWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructSDWORD()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultSDWORD();
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructUDWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructUDWORD()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultUDWORD();
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructSQWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructSQWORD()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultSQWORD();
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructUQWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructUQWORD()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultUQWORD();
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructDouble()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructDouble()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultDouble();
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructString()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructString()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultStringObject();
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructRope()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructRope()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultRopeObject();
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructIPv4Address()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructIPv4Address()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultIPv4AddressObject();
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructPPort()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructPPort()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultPPortObject();
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructBoolTable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructBoolTable()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultTableObject(CchZVM_BOOL_TYPE_TAG);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructByteTable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructByteTable()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultTableObject(CchZVM_BYTE_TYPE_TAG);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructSDWORDTable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructSDWORDTable()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultTableObject(CchZVM_SDWORD_TYPE_TAG);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructUDWORDTable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructUDWORDTable()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultTableObject(CchZVM_UDWORD_TYPE_TAG);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructSQWORDTable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructSQWORDTable()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultTableObject(CchZVM_SQWORD_TYPE_TAG);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructUQWORDTable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructUQWORDTable()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultTableObject(CchZVM_UQWORD_TYPE_TAG);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructDoubleTable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructDoubleTable()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultTableObject(CchZVM_DOUBLE_TYPE_TAG);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructStringTable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructStringTable()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultTableObject(CchZVM_STRING_TYPE_TAG);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructRopeTable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructRopeTable()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultTableObject(CchZVM_ROPE_TYPE_TAG);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructIPv4AddressTable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructIPv4AddressTable()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultTableObject(CchZVM_IPv4ADDR_TYPE_TAG);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructPPortTable()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructPPortTable()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDefaultTableObject(CchZVM_PPORT_TYPE_TAG);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructBoolReference()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructBoolReference()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsBoolAddress(0);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructByteReference()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructByteReference()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsByteAddress(0);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructSDWORDReference()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructSDWORDReference()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsSDWORDAddress(0);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructUDWORDReference()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructUDWORDReference()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsUDWORDAddress(0);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructSQWORDReference()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructSQWORDReference()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsSQWORDAddress(0);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructUQWORDReference()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructUQWORDReference()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsUQWORDAddress(0);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructDoubleReference()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructDoubleReference()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsDoubleAddress(0);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructStringReference()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructStringReference()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsStringObjectAddress(0);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructRopeReference()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructRopeReference()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsRopeObjectAddress(0);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructIPv4AddressReference()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructIPv4AddressReference()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsIPv4AddressObjectAddress(0);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructPPortReference()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructPPortReference()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsPPortObjectAddress(0);
  return 1;
}


TZVMIndex CZVMVirtualThread::_constructTableReference()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_constructTableReference()");
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->ConstructSlotAsTableObjectAddress(0);
  return 1;
}


TZVMIndex CZVMVirtualThread::_quickConstructStringObject()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_quickConstructStringObject()");
  // 得到需要shadow的temp stack variable
  CSlot * pciVariableSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciVariableSlot, CSlot::SLOT_TAG_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->QuickConstructSlotAsStringObject(pciVariableSlot->GetStringObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_quickConstructRopeObject()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_quickConstructRopeObject()");
  // 得到需要shadow的temp stack variable
  CSlot * pciVariableSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciVariableSlot, CSlot::SLOT_TAG_ROPE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->QuickConstructSlotAsRopeObject(pciVariableSlot->GetRopeObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_quickConstructIPv4AddressObject()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_quickConstructIPv4AddressObject()");
  // 得到需要shadow的temp stack variable
  CSlot * pciVariableSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciVariableSlot, CSlot::SLOT_TAG_IPv4ADDRESS_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->QuickConstructSlotAsIPv4AddressObject(pciVariableSlot->GetIPv4AddressObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_quickConstructPPortObject()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_quickConstructPPortObject()");
  // 得到需要shadow的temp stack variable
  CSlot * pciVariableSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciVariableSlot, CSlot::SLOT_TAG_PPORT_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->QuickConstructSlotAsPPortObject(pciVariableSlot->GetPPortObject());
  return 1;
}


TZVMIndex CZVMVirtualThread::_quickConstructTableObject()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_quickConstructTableObject()");
  // 得到需要shadow的temp stack variable
  CSlot * pciVariableSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciVariableSlot, CSlot::SLOT_TAG_TABLE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CSlot * pciSlot = PrefixIncreaseSPRegister();
  pciSlot->QuickConstructSlotAsTableObject(pciVariableSlot->GetTableObject());
  return 1;
}


/******************************************************************************
 * Jump指令Interpreter
 ******************************************************************************/
TZVMIndex CZVMVirtualThread::_boolFalseJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_boolFalseJump()");
  bool b = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (b)
  {
    return 1;
  }
  else
  {
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_byteFalseJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteFalseJump()");
  UCHAR uch = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (uch)
  {
    return 1;
  }
  else
  {
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_sdwordFalseJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordFalseJump()");
  SDWORD sdw = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (sdw)
  {
    return 1;
  }
  else
  {
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_udwordFalseJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordFalseJump()");
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (udw)
  {
    return 1;
  }
  else
  {
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_sqwordFalseJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordFalseJump()");
  SQWORD sqw = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (sqw)
  {
    return 1;
  }
  else
  {
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_uqwordFalseJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordFalseJump()");
  UQWORD uqw = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (uqw)
  {
    return 1;
  }
  else
  {
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_doubleFalseJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleFalseJump()");
  double df = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (df)
  {
    return 1;
  }
  else
  {
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_stringFalseJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_stringFalseJump()");
  CZVMString ** ppci = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  // 只要这个string有内容，即认为是true
  if ((*ppci)->size())
  {
    return 1;
  }
  else
  {
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_ropeFalseJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_ropeFalseJump()");
  CZVMRope ** ppci = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  // 只要这个rope有内容，即认为是true
  if ((*ppci)->size())
  {
    return 1;
  }
  else
  {
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_ipv4addressFalseJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_ipv4addressFalseJump()");
  CZVMIPv4Address ** ppci = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  if ((*ppci)->ToBool())
  {
    return 1;
  }
  else
  {
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_pportFalseJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_pportFalseJump()");
  CZVMPPort ** ppci = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  if ((*ppci)->ToBool())
  {
    return 1;
  }
  else
  {
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_tableFalseJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_tableFalseJump()");
  CZVMTable ** ppci = POP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  if ((*ppci)->ToBool())
  {
    return 1;
  }
  else
  {
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_boolFalseCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_boolFalseCircuitJump()");
  // 检测
  bool b = TOP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (b)
  {
    return 1;
  }
  else
  {
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_byteFalseCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteFalseCircuitJump()");
  // 检测
  UCHAR uch = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (uch)
  {
    return 1;
  }
  else
  {
    // 偷偷修改为bool型false
    ReplaceAsBool(false);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_sdwordFalseCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordFalseCircuitJump()");
  // 检测
  SDWORD sdw = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (sdw)
  {
    return 1;
  }
  else
  {
    // 偷偷修改为bool型false
    ReplaceAsBool(false);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_udwordFalseCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordFalseCircuitJump()");
  // 检测
  UDWORD udw = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (udw)
  {
    return 1;
  }
  else
  {
    // 偷偷修改为bool型false
    ReplaceAsBool(false);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_sqwordFalseCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordFalseCircuitJump()");
  // 检测
  SQWORD sqw = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (sqw)
  {
    return 1;
  }
  else
  {
    // 偷偷修改为bool型false
    ReplaceAsBool(false);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_uqwordFalseCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordFalseCircuitJump()");
  // 检测
  UQWORD uqw = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (uqw)
  {
    return 1;
  }
  else
  {
    // 偷偷修改为bool型false
    ReplaceAsBool(false);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_doubleFalseCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleFalseCircuitJump()");
  // 检测
  double df = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (df)
  {
    return 1;
  }
  else
  {
    // 偷偷修改为bool型false
    ReplaceAsBool(false);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_stringFalseCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_stringFalseCircuitJump()");
  // 检测
  CZVMString ** ppci = TOP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  // 只要这个string有内容，即认为是true
  if ((*ppci)->size())
  {
    return 1;
  }
  else
  {
    // 偷偷修改为bool型false
    ReplaceAsBool(false);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_ropeFalseCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_ropeFalseCircuitJump()");
  // 检测
  CZVMRope ** ppci = TOP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  // 只要这个rope有内容，即认为是true
  if ((*ppci)->size())
  {
    return 1;
  }
  else
  {
    // 偷偷修改为bool型false
    ReplaceAsBool(false);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_ipv4addressFalseCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_ipv4addressFalseCircuitJump()");
  // 检测
  CZVMIPv4Address ** ppci = TOP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  if ((*ppci)->ToBool())
  {
    return 1;
  }
  else
  {
    // 偷偷修改为bool型false
    ReplaceAsBool(false);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_pportFalseCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_pportFalseCircuitJump()");
  // 检测
  CZVMPPort ** ppci = TOP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  if ((*ppci)->ToBool())
  {
    return 1;
  }
  else
  {
    // 偷偷修改为bool型false
    ReplaceAsBool(false);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
}


TZVMIndex CZVMVirtualThread::_boolTrueCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_boolTrueCircuitJump()");
  // 检测
  bool b = TOP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (b)
  {
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
  else
  {
    return 1;
  }
}


TZVMIndex CZVMVirtualThread::_byteTrueCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteTrueCircuitJump()");
  // 检测
  UCHAR uch = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (uch)
  {
    // 偷偷修改为bool型true
    ReplaceAsBool(true);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
  else
  {
    return 1;
  }
}


TZVMIndex CZVMVirtualThread::_sdwordTrueCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordTrueCircuitJump()");
  // 检测
  SDWORD sdw = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (sdw)
  {
    // 偷偷修改为bool型true
    ReplaceAsBool(true);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
  else
  {
    return 1;
  }
}


TZVMIndex CZVMVirtualThread::_udwordTrueCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordTrueCircuitJump()");
  // 检测
  UDWORD udw = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (udw)
  {
    // 偷偷修改为bool型true
    ReplaceAsBool(true);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
  else
  {
    return 1;
  }
}


TZVMIndex CZVMVirtualThread::_sqwordTrueCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordTrueCircuitJump()");
  // 检测
  SQWORD sqw = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (sqw)
  {
    // 偷偷修改为bool型true
    ReplaceAsBool(true);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
  else
  {
    return 1;
  }
}


TZVMIndex CZVMVirtualThread::_uqwordTrueCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordTrueCircuitJump()");
  // 检测
  UQWORD uqw = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (uqw)
  {
    // 偷偷修改为bool型true
    ReplaceAsBool(true);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
  else
  {
    return 1;
  }
}


TZVMIndex CZVMVirtualThread::_doubleTrueCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleTrueCircuitJump()");
  // 检测
  double df = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (df)
  {
    // 偷偷修改为bool型true
    ReplaceAsBool(true);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
  else
  {
    return 1;
  }
}


TZVMIndex CZVMVirtualThread::_stringTrueCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_stringTrueCircuitJump()");
  // 检测
  CZVMString ** ppci = TOP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  // 只要这个string有内容，即认为是true
  if ((*ppci)->size())
  {
    // 偷偷修改为bool型true
    ReplaceAsBool(true);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
  else
  {
    return 1;
  }
}


TZVMIndex CZVMVirtualThread::_ropeTrueCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_ropeTrueCircuitJump()");
  // 检测
  CZVMRope ** ppci = TOP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  // 只要这个rope有内容，即认为是true
  if ((*ppci)->size())
  {
    // 偷偷修改为bool型true
    ReplaceAsBool(true);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
  else
  {
    return 1;
  }
}


TZVMIndex CZVMVirtualThread::_ipv4addressTrueCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_ipv4addressTrueCircuitJump()");
  // 检测
  CZVMIPv4Address ** ppci = TOP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  if ((*ppci)->ToBool())
  {
    // 偷偷修改为bool型true
    ReplaceAsBool(true);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
  else
  {
    return 1;
  }
}


TZVMIndex CZVMVirtualThread::_pportTrueCircuitJump()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_pportTrueCircuitJump()");
  // 检测
  CZVMPPort ** ppci = TOP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  if ((*ppci)->ToBool())
  {
    // 偷偷修改为bool型true
    ReplaceAsBool(true);
    const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
    TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
    return nOffset;
  }
  else
  {
    return 1;
  }
}


TZVMIndex CZVMVirtualThread::_unlimitJump()
{
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  TZVMIndex nOffset = pciInstruction->GetOperandAsTZVMIndex();
  return nOffset;
}


TZVMIndex CZVMVirtualThread::_call()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_call()");
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  TZVMIndex iFunctionReference = pciInstruction->GetOperandAsTZVMIndex();
  // 得到Constant pool
  const zvm::CConstantPool * pciConstantPool = _ciPCRegister.GetConstantPool();
  const zvm::CGlobalFunctionReference * pciFunctionReference =
              pciConstantPool->GetAsGlobalFunctionReference(iFunctionReference);
  if (pciFunctionReference->GetLanguageTag() == LANGUAGE_TAG_IS_ZLANG)
  {
    const CZVMFunction * pciZVMFunction = pciFunctionReference->GetZVMFunction();
    CallZVMFunction(pciZVMFunction);
  }
  else
  {
    TNativeFunction pfuncNativeFunction = pciFunctionReference->GetNativeFunction();
    CallNativeFunction(pfuncNativeFunction);
  }

  return 1;
}


