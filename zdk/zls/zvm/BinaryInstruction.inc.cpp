/******************************************************************************
 * Binary指令Interpreter
 ******************************************************************************/
TZVMIndex CZVMVirtualThread::_boolLogicOr()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_boolLogicOr()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool bRight = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  bool bLeft = TOP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreBool(bLeft || bRight);
  #else
  bool bRight = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  bool bLeft = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(bLeft || bRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteLogicOr()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteLogicOr()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(uchLeft || uchRight);
  #else
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(uchLeft || uchRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordLogicOr()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordLogicOr()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(sdwLeft || sdwRight);
  #else
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(sdwLeft || sdwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordLogicOr()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordLogicOr()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(udwLeft || udwRight);
  #else
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(udwLeft || udwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordLogicOr()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordLogicOr()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(sqwLeft || sqwRight);
  #else
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(sqwLeft || sqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordLogicOr()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordLogicOr()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(uqwLeft || uqwRight);
  #else
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(uqwLeft || uqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleLogicOr()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleLogicOr()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(dfLeft || dfRight);
  #else
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(dfLeft || dfRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_boolLogicAnd()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_boolLogicAnd()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool bRight = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  bool bLeft = TOP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreBool(bLeft && bRight);
  #else
  bool bRight = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  bool bLeft = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(bLeft && bRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteLogicAnd()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteLogicAnd()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(uchLeft && uchRight);
  #else
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(uchLeft && uchRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordLogicAnd()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordLogicAnd()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(sdwLeft && sdwRight);
  #else
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(sdwLeft && sdwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordLogicAnd()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordLogicAnd()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(udwLeft && udwRight);
  #else
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(udwLeft && udwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordLogicAnd()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordLogicAnd()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(sqwLeft && sqwRight);
  #else
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(sqwLeft && sqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordLogicAnd()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordLogicAnd()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(uqwLeft && uqwRight);
  #else
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(uqwLeft && uqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleLogicAnd()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleLogicAnd()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(dfLeft && dfRight);
  #else
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(dfLeft && dfRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteBitOr()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteBitOr()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreByte(uchLeft | uchRight);
  #else
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(uchLeft | uchRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordBitOr()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordBitOr()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSDWORD(sdwLeft | sdwRight);
  #else
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(sdwLeft | sdwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordBitOr()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordBitOr()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUDWORD(udwLeft | udwRight);
  #else
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(udwLeft | udwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordBitOr()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordBitOr()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSQWORD(sqwLeft | sqwRight);
  #else
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(sqwLeft | sqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordBitOr()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordBitOr()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUQWORD(uqwLeft | uqwRight);
  #else
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(uqwLeft | uqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteBitXor()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteBitXor()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreByte(uchLeft ^ uchRight);
  #else
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(uchLeft ^ uchRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordBitXor()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordBitXor()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSDWORD(sdwLeft ^ sdwRight);
  #else
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(sdwLeft ^ sdwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordBitXor()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordBitXor()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUDWORD(udwLeft ^ udwRight);
  #else
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(udwLeft ^ udwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordBitXor()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordBitXor()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSQWORD(sqwLeft ^ sqwRight);
  #else
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(sqwLeft ^ sqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordBitXor()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordBitXor()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUQWORD(uqwLeft ^ uqwRight);
  #else
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(uqwLeft ^ uqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteBitAnd()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteBitAnd()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreByte(uchLeft & uchRight);
  #else
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(uchLeft & uchRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordBitAnd()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordBitAnd()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSDWORD(sdwLeft & sdwRight);
  #else
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(sdwLeft & sdwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordBitAnd()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordBitAnd()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUDWORD(udwLeft & udwRight);
  #else
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(udwLeft & udwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordBitAnd()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordBitAnd()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSQWORD(sqwLeft & sqwRight);
  #else
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(sqwLeft & sqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordBitAnd()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordBitAnd()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUQWORD(uqwLeft & uqwRight);
  #else
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(uqwLeft & uqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_boolNotEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_boolNotEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool bRight = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  bool bLeft = TOP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreBool(bLeft != bRight);
  #else
  bool bRight = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  bool bLeft = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(bLeft != bRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteNotEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteNotEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(uchLeft != uchRight);
  #else
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(uchLeft != uchRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordNotEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordNotEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(sdwLeft != sdwRight);
  #else
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(sdwLeft != sdwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordNotEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordNotEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(udwLeft != udwRight);
  #else
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(udwLeft != udwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordNotEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordNotEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(sqwLeft != sqwRight);
  #else
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(sqwLeft != sqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordNotEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordNotEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(uqwLeft != uqwRight);
  #else
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(uqwLeft != uqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleNotEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleNotEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(dfLeft != dfRight);
  #else
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(dfLeft != dfRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_stringNotEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_stringNotEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciRight = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppciLeft = TOP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft != **ppciRight);
  #else
  CZVMString ** ppciRight = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppciLeft = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft != **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_ropeNotEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_ropeNotEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRight = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppciLeft = TOP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft != **ppciRight);
  #else
  CZVMRope ** ppciRight = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppciLeft = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft != **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_ipv4addressNotEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_ipv4addressNotEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMIPv4Address ** ppciRight = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMIPv4Address ** ppciLeft = TOP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft != **ppciRight);
  #else
  CZVMIPv4Address ** ppciRight = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMIPv4Address ** ppciLeft = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft != **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_pportNotEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_pportNotEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciRight = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppciLeft = TOP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft != **ppciRight);
  #else
  CZVMPPort ** ppciRight = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppciLeft = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft != **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_tableNotEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_tableNotEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMTable ** ppciRight = POP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciLeft = TOP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft != **ppciRight);
  #else
  CZVMTable ** ppciRight = POP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciLeft = POP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft != **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_boolEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_boolEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool bRight = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  bool bLeft = TOP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreBool(bLeft == bRight);
  #else
  bool bRight = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  bool bLeft = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(bLeft == bRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(uchLeft == uchRight);
  #else
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(uchLeft == uchRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(sdwLeft == sdwRight);
  #else
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(sdwLeft == sdwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(udwLeft == udwRight);
  #else
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(udwLeft == udwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(sqwLeft == sqwRight);
  #else
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(sqwLeft == sqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(uqwLeft == uqwRight);
  #else
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(uqwLeft == uqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(dfLeft == dfRight);
  #else
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(dfLeft == dfRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_stringEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_stringEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciRight = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppciLeft = TOP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft == **ppciRight);
  #else
  CZVMString ** ppciRight = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppciLeft = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft == **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_ropeEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_ropeEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRight = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppciLeft = TOP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft == **ppciRight);
  #else
  CZVMRope ** ppciRight = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppciLeft = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft == **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_ipv4addressEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_ipv4addressEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMIPv4Address ** ppciRight = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMIPv4Address ** ppciLeft = TOP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft == **ppciRight);
  #else
  CZVMIPv4Address ** ppciRight = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMIPv4Address ** ppciLeft = POP_IPv4ADDRESS_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft == **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_pportEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_pportEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciRight = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppciLeft = TOP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft == **ppciRight);
  #else
  CZVMPPort ** ppciRight = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppciLeft = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft == **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_tableEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_tableEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMTable ** ppciRight = POP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciLeft = TOP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft == **ppciRight);
  #else
  CZVMTable ** ppciRight = POP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMTable ** ppciLeft = POP_TABLE_OBJECT_ADDRESS(CchZVM_VOID_TYPE_TAG, __FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft == **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteLess()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteLess()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(uchLeft < uchRight);
  #else
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(uchLeft < uchRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordLess()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordLess()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(sdwLeft < sdwRight);
  #else
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(sdwLeft < sdwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordLess()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordLess()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(udwLeft < udwRight);
  #else
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(udwLeft < udwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordLess()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordLess()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(sqwLeft < sqwRight);
  #else
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(sqwLeft < sqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordLess()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordLess()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(uqwLeft < uqwRight);
  #else
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(uqwLeft < uqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleLess()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleLess()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(dfLeft < dfRight);
  #else
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(dfLeft < dfRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_stringLess()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_stringLess()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciRight = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppciLeft = TOP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft < **ppciRight);
  #else
  CZVMString ** ppciRight = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppciLeft = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft < **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_ropeLess()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_ropeLess()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRight = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppciLeft = TOP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft < **ppciRight);
  #else
  CZVMRope ** ppciRight = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppciLeft = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft < **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_pportLess()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_pportLess()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciRight = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppciLeft = TOP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft < **ppciRight);
  #else
  CZVMPPort ** ppciRight = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppciLeft = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft < **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteGreat()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteGreat()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(uchLeft > uchRight);
  #else
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(uchLeft > uchRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordGreat()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordGreat()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(sdwLeft > sdwRight);
  #else
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(sdwLeft > sdwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordGreat()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordGreat()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(udwLeft > udwRight);
  #else
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(udwLeft > udwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordGreat()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordGreat()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(sqwLeft > sqwRight);
  #else
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(sqwLeft > sqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordGreat()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordGreat()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(uqwLeft > uqwRight);
  #else
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(uqwLeft > uqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleGreat()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleGreat()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(dfLeft > dfRight);
  #else
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(dfLeft > dfRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_stringGreat()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_stringGreat()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciRight = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppciLeft = TOP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft > **ppciRight);
  #else
  CZVMString ** ppciRight = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppciLeft = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft > **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_ropeGreat()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_ropeGreat()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRight = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppciLeft = TOP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft > **ppciRight);
  #else
  CZVMRope ** ppciRight = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppciLeft = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft > **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_pportGreat()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_pportGreat()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciRight = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppciLeft = TOP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft > **ppciRight);
  #else
  CZVMPPort ** ppciRight = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppciLeft = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft > **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteLessEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteLessEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(uchLeft <= uchRight);
  #else
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(uchLeft <= uchRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordLessEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordLessEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(sdwLeft <= sdwRight);
  #else
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(sdwLeft <= sdwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordLessEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordLessEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(udwLeft <= udwRight);
  #else
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(udwLeft <= udwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordLessEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordLessEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(sqwLeft <= sqwRight);
  #else
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(sqwLeft <= sqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordLessEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordLessEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(uqwLeft <= uqwRight);
  #else
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(uqwLeft <= uqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleLessEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleLessEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(dfLeft <= dfRight);
  #else
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(dfLeft <= dfRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_stringLessEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_stringLessEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciRight = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppciLeft = TOP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft <= **ppciRight);
  #else
  CZVMString ** ppciRight = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppciLeft = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft <= **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_ropeLessEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_ropeLessEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRight = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppciLeft = TOP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft <= **ppciRight);
  #else
  CZVMRope ** ppciRight = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppciLeft = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft <= **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_pportLessEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_pportLessEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciRight = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppciLeft = TOP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft <= **ppciRight);
  #else
  CZVMPPort ** ppciRight = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppciLeft = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft <= **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteGreatEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteGreatEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(uchLeft >= uchRight);
  #else
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(uchLeft >= uchRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordGreatEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordGreatEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(sdwLeft >= sdwRight);
  #else
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(sdwLeft >= sdwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordGreatEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordGreatEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(udwLeft >= udwRight);
  #else
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(udwLeft >= udwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordGreatEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordGreatEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(sqwLeft >= sqwRight);
  #else
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(sqwLeft >= sqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordGreatEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordGreatEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(uqwLeft >= uqwRight);
  #else
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(uqwLeft >= uqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleGreatEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleGreatEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(dfLeft >= dfRight);
  #else
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(dfLeft >= dfRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_stringGreatEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_stringGreatEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciRight = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppciLeft = TOP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft >= **ppciRight);
  #else
  CZVMString ** ppciRight = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppciLeft = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft >= **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_ropeGreatEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_ropeGreatEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMRope ** ppciRight = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppciLeft = TOP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft >= **ppciRight);
  #else
  CZVMRope ** ppciRight = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppciLeft = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft >= **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_pportGreatEqual()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_pportGreatEqual()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMPPort ** ppciRight = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppciLeft = TOP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(**ppciLeft >= **ppciRight);
  #else
  CZVMPPort ** ppciRight = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMPPort ** ppciLeft = POP_PPORT_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(**ppciLeft >= **ppciRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteShiftLeft()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteShiftLeft()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreByte(uchLeft << udw);
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(uchLeft << udw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordShiftLeft()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordShiftLeft()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSDWORD(sdwLeft << udw);
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(sdwLeft << udw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordShiftLeft()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordShiftLeft()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUDWORD(udwLeft << udw);
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(udwLeft << udw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordShiftLeft()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordShiftLeft()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSQWORD(sqwLeft << udw);
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(sqwLeft << udw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordShiftLeft()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordShiftLeft()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUQWORD(uqwLeft << udw);
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(uqwLeft << udw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteShiftRight()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteShiftRight()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreByte(uchLeft >> udw);
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(uchLeft >> udw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordShiftRight()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordShiftRight()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSDWORD(sdwLeft >> udw);
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(sdwLeft >> udw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordShiftRight()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordShiftRight()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUDWORD(udwLeft >> udw);
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(udwLeft >> udw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordShiftRight()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordShiftRight()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSQWORD(sqwLeft >> udw);
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(sqwLeft >> udw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordShiftRight()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordShiftRight()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUQWORD(uqwLeft >> udw);
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(uqwLeft >> udw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_bytePlus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_bytePlus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreByte(uchLeft + uchRight);
  #else
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(uchLeft + uchRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordPlus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordPlus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSDWORD(sdwLeft + sdwRight);
  #else
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(sdwLeft + sdwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordPlus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordPlus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUDWORD(udwLeft + udwRight);
  #else
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(udwLeft + udwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordPlus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordPlus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSQWORD(sqwLeft + sqwRight);
  #else
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(sqwLeft + sqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordPlus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordPlus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUQWORD(uqwLeft + uqwRight);
  #else
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(uqwLeft + uqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doublePlus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doublePlus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreDouble(dfLeft + dfRight);
  #else
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(dfLeft + dfRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_stringPlus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_stringPlus()");

  /* 2001/7/17: */
  CZVMString ** ppciRight = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppciLeft = TOP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  // 加到临时string varible中
  CSlot * pciVariableSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciVariableSlot, CSlot::SLOT_TAG_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString * pci = pciVariableSlot->GetStringObject();
  *pci = **ppciLeft;
  *pci += **ppciRight;
  // 取这个临时string varible的string object address到ZVM stack顶
  StoreStringObjectAddress(pciVariableSlot->GetStringObjectAddress());

  /* 2001/7/17: Discarded
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  CZVMString ** ppciRight = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppciLeft = TOP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  // 加到一个立即new的临时string中
  CZVMString * pci = new __OPTION(_THROW) CZVMString(**ppciLeft);
  *pci += **ppciRight;
  // 将这个临时string的地址存放到register中
  _ciStringObjectRegister.Replace(pci);
  StoreStringObjectAddress(_ciStringObjectRegister.GetObjectAddress());
  #else
  CZVMString ** ppciRight = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMString ** ppciLeft = POP_STRING_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  // 加到一个立即new的临时string中
  CZVMString * pci = new __OPTION(_THROW) CZVMString(**ppciLeft);
  *pci += **ppciRight;
  // 将这个临时string的地址存放到register中
  _ciStringObjectRegister.Replace(pci);
  PushStringObjectAddress(_ciStringObjectRegister.GetObjectAddress());
  #endif
  */

  return 1;
}


TZVMIndex CZVMVirtualThread::_ropePlus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_ropePlus()");
  CZVMRope ** ppciRight = POP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope ** ppciLeft = TOP_ROPE_OBJECT_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  // 加到临时rope varible中
  CSlot * pciVariableSlot = GetStackVariableSlot();
  ZVM_SLOT_ASSERT(pciVariableSlot, CSlot::SLOT_TAG_ROPE_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  CZVMRope * pci = pciVariableSlot->GetRopeObject();
  *pci = **ppciLeft;
  *pci += **ppciRight;
  // 取这个临时rope varible的rope object address到ZVM stack顶
  StoreRopeObjectAddress(pciVariableSlot->GetRopeObjectAddress());
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteMinus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteMinus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreByte(uchLeft - uchRight);
  #else
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(uchLeft - uchRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordMinus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordMinus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSDWORD(sdwLeft - sdwRight);
  #else
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(sdwLeft - sdwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordMinus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordMinus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUDWORD(udwLeft - udwRight);
  #else
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(udwLeft - udwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordMinus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordMinus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSQWORD(sqwLeft - sqwRight);
  #else
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(sqwLeft - sqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordMinus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordMinus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUQWORD(uqwLeft - uqwRight);
  #else
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(uqwLeft - uqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleMinus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleMinus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreDouble(dfLeft - dfRight);
  #else
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(dfLeft - dfRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteMulti()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteMulti()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreByte(uchLeft * uchRight);
  #else
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(uchLeft * uchRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordMulti()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordMulti()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSDWORD(sdwLeft * sdwRight);
  #else
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(sdwLeft * sdwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordMulti()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordMulti()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUDWORD(udwLeft * udwRight);
  #else
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(udwLeft * udwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordMulti()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordMulti()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSQWORD(sqwLeft * sqwRight);
  #else
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(sqwLeft * sqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordMulti()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordMulti()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUQWORD(uqwLeft * uqwRight);
  #else
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(uqwLeft * uqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleMulti()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleMulti()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreDouble(dfLeft * dfRight);
  #else
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(dfLeft * dfRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteDiv()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteDiv()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (uchRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreByte(uchLeft / uchRight);
  #else
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (uchRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(uchLeft / uchRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordDiv()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordDiv()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (sdwRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSDWORD(sdwLeft / sdwRight);
  #else
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (sdwRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(sdwLeft / sdwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordDiv()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordDiv()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (udwRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUDWORD(udwLeft / udwRight);
  #else
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (udwRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(udwLeft / udwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordDiv()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordDiv()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (sqwRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSQWORD(sqwLeft / sqwRight);
  #else
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (sqwRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(sqwLeft / sqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordDiv()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordDiv()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (uqwRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUQWORD(uqwLeft / uqwRight);
  #else
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (uqwRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(uqwLeft / uqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleDiv()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleDiv()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (dfRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  double dfLeft = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreDouble(dfLeft / dfRight);
  #else
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (dfRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  double dfLeft = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(dfLeft / dfRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteMod()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteMod()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (uchRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  UCHAR uchLeft = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreByte(uchLeft % uchRight);
  #else
  UCHAR uchRight = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (uchRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  UCHAR uchLeft = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(uchLeft % uchRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordMod()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordMod()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (sdwRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  SDWORD sdwLeft = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSDWORD(sdwLeft % sdwRight);
  #else
  SDWORD sdwRight = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (sdwRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  SDWORD sdwLeft = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(sdwLeft % sdwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordMod()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordMod()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (udwRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  UDWORD udwLeft = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUDWORD(udwLeft % udwRight);
  #else
  UDWORD udwRight = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (udwRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  UDWORD udwLeft = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(udwLeft % udwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordMod()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordMod()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (sqwRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  SQWORD sqwLeft = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSQWORD(sqwLeft % sqwRight);
  #else
  SQWORD sqwRight = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (sqwRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  SQWORD sqwLeft = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(sqwLeft % sqwRight);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordMod()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordMod()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (uqwRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  UQWORD uqwLeft = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUQWORD(uqwLeft % uqwRight);
  #else
  UQWORD uqwRight = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  if (uqwRight == 0)
  {
    throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "Div zero exception");
  }
  UQWORD uqwLeft = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(uqwLeft % uqwRight);
  #endif
  return 1;
}


/* C/C++不允许"double % double"
TZVMIndex CZVMVirtualThread::_doubleMod()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleMod()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreDouble(dfLeft % dfRight);
  #else
  double dfRight = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  double dfLeft = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(dfLeft % dfRight);
  #endif
  return 1;
}
*/

