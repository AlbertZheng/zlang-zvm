/******************************************************************************
 * Unary指令Interpreter
 ******************************************************************************/
TZVMIndex CZVMVirtualThread::_bytePrefixInc()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_bytePrefixInc()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR * puch = TOP_BYTE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *puch = *puch + 1;
  ReplaceAsByte(*puch);
  #else
  UCHAR * puch = POP_BYTE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *puch = *puch + 1;
  PushByte(*puch);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordPrefixInc()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordPrefixInc()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD * psdw = TOP_SDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *psdw = *psdw + 1;
  ReplaceAsSDWORD(*psdw);
  #else
  SDWORD * psdw = POP_SDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *psdw = *psdw + 1;
  PushSDWORD(*psdw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordPrefixInc()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordPrefixInc()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD * pudw = TOP_UDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pudw = *pudw + 1;
  ReplaceAsUDWORD(*pudw);
  #else
  UDWORD * pudw = POP_UDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pudw = *pudw + 1;
  PushUDWORD(*pudw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordPrefixInc()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordPrefixInc()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD * psqw = TOP_SQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *psqw = *psqw + 1;
  ReplaceAsSQWORD(*psqw);
  #else
  SQWORD * psqw = POP_SQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *psqw = *psqw + 1;
  PushSQWORD(*psqw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordPrefixInc()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordPrefixInc()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD * puqw = TOP_UQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *puqw = *puqw + 1;
  ReplaceAsUQWORD(*puqw);
  #else
  UQWORD * puqw = POP_UQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *puqw = *puqw + 1;
  PushUQWORD(*puqw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doublePrefixInc()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doublePrefixInc()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double * pdf = TOP_DOUBLE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pdf = *pdf + 1;
  ReplaceAsDouble(*pdf);
  #else
  double * pdf = POP_DOUBLE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pdf = *pdf + 1;
  PushDouble(*pdf);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_bytePrefixDec()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_bytePrefixDec()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR * puch = TOP_BYTE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *puch = *puch - 1;
  ReplaceAsByte(*puch);
  #else
  UCHAR * puch = POP_BYTE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *puch = *puch - 1;
  PushByte(*puch);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordPrefixDec()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordPrefixDec()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD * psdw = TOP_SDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *psdw = *psdw - 1;
  ReplaceAsSDWORD(*psdw);
  #else
  SDWORD * psdw = POP_SDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *psdw = *psdw - 1;
  PushSDWORD(*psdw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordPrefixDec()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordPrefixDec()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD * pudw = TOP_UDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pudw = *pudw - 1;
  ReplaceAsUDWORD(*pudw);
  #else
  UDWORD * pudw = POP_UDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pudw = *pudw - 1;
  PushUDWORD(*pudw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordPrefixDec()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordPrefixDec()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD * psqw = TOP_SQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *psqw = *psqw - 1;
  ReplaceAsSQWORD(*psqw);
  #else
  SQWORD * psqw = POP_SQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *psqw = *psqw - 1;
  PushSQWORD(*psqw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordPrefixDec()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordPrefixDec()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD * puqw = TOP_UQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *puqw = *puqw - 1;
  ReplaceAsUQWORD(*puqw);
  #else
  UQWORD * puqw = POP_UQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *puqw = *puqw - 1;
  PushUQWORD(*puqw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doublePrefixDec()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doublePrefixDec()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double * pdf = TOP_DOUBLE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pdf = *pdf - 1;
  ReplaceAsDouble(*pdf);
  #else
  double * pdf = POP_DOUBLE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  *pdf = *pdf - 1;
  PushDouble(*pdf);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_bytePostfixInc()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_bytePostfixInc()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR * puch = TOP_BYTE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsByte(*puch);
  *puch = *puch + 1;
  #else
  UCHAR * puch = POP_BYTE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(*puch);
  *puch = *puch + 1;
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordPostfixInc()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordPostfixInc()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD * psdw = TOP_SDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsSDWORD(*psdw);
  *psdw = *psdw + 1;
  #else
  SDWORD * psdw = POP_SDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(*psdw);
  *psdw = *psdw + 1;
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordPostfixInc()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordPostfixInc()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD * pudw = TOP_UDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsUDWORD(*pudw);
  *pudw = *pudw + 1;
  #else
  UDWORD * pudw = POP_UDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(*pudw);
  *pudw = *pudw + 1;
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordPostfixInc()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordPostfixInc()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD * psqw = TOP_SQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsSQWORD(*psqw);
  *psqw = *psqw + 1;
  #else
  SQWORD * psqw = POP_SQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(*psqw);
  *psqw = *psqw + 1;
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordPostfixInc()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordPostfixInc()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD * puqw = TOP_UQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsUQWORD(*puqw);
  *puqw = *puqw + 1;
  #else
  UQWORD * puqw = POP_UQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(*puqw);
  *puqw = *puqw + 1;
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doublePostfixInc()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doublePostfixInc()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double * pdf = TOP_DOUBLE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsDouble(*pdf);
  *pdf = *pdf + 1;
  #else
  double * pdf = POP_DOUBLE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(*pdf);
  *pdf = *pdf + 1;
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_bytePostfixDec()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_bytePostfixDec()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR * puch = TOP_BYTE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsByte(*puch);
  *puch = *puch - 1;
  #else
  UCHAR * puch = POP_BYTE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(*puch);
  *puch = *puch - 1;
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordPostfixDec()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordPostfixDec()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD * psdw = TOP_SDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsSDWORD(*psdw);
  *psdw = *psdw - 1;
  #else
  SDWORD * psdw = POP_SDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(*psdw);
  *psdw = *psdw - 1;
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordPostfixDec()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordPostfixDec()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD * pudw = TOP_UDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsUDWORD(*pudw);
  *pudw = *pudw - 1;
  #else
  UDWORD * pudw = POP_UDWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(*pudw);
  *pudw = *pudw - 1;
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordPostfixDec()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordPostfixDec()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD * psqw = TOP_SQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsSQWORD(*psqw);
  *psqw = *psqw - 1;
  #else
  SQWORD * psqw = POP_SQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(*psqw);
  *psqw = *psqw - 1;
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordPostfixDec()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordPostfixDec()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD * puqw = TOP_UQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsUQWORD(*puqw);
  *puqw = *puqw - 1;
  #else
  UQWORD * puqw = POP_UQWORD_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(*puqw);
  *puqw = *puqw - 1;
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doublePostfixDec()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doublePostfixDec()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double * pdf = TOP_DOUBLE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsDouble(*pdf);
  *pdf = *pdf - 1;
  #else
  double * pdf = POP_DOUBLE_ADDRESS(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(*pdf);
  *pdf = *pdf - 1;
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteUnaryPlus()
{
  /*
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteUnaryPlus()");
  UCHAR uch = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(uch);
  */
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordUnaryPlus()
{
  /*
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordUnaryPlus()");
  SDWORD sdw = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(sdw);
  */
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordUnaryPlus()
{
  /*
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordUnaryPlus()");
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(udw);
  */
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordUnaryPlus()
{
  /*
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordUnaryPlus()");
  SQWORD sqw = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(sqw);
  */
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordUnaryPlus()
{
  /*
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordUnaryPlus()");
  UQWORD uqw = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(uqw);
  */
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleUnaryPlus()
{
  /*
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleUnaryPlus()");
  double df = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(df);
  */
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteUnaryMinus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteUnaryMinus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uch = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreByte(-uch);
  #else
  UCHAR uch = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(-uch);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordUnaryMinus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordUnaryMinus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdw = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSDWORD(-sdw);
  #else
  SDWORD sdw = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(-sdw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordUnaryMinus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordUnaryMinus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUDWORD(-udw);
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(-udw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordUnaryMinus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordUnaryMinus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqw = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSQWORD(-sqw);
  #else
  SQWORD sqw = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(-sqw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordUnaryMinus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordUnaryMinus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqw = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUQWORD(-uqw);
  #else
  UQWORD uqw = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(-uqw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleUnaryMinus()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleUnaryMinus()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double df = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreDouble(-df);
  #else
  double df = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(-df);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteBitNot()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteBitNot()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uch = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreByte(~uch);
  #else
  UCHAR uch = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(~uch);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordBitNot()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordBitNot()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdw = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSDWORD(~sdw);
  #else
  SDWORD sdw = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(~sdw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordBitNot()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordBitNot()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUDWORD(~udw);
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(~udw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordBitNot()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordBitNot()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqw = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreSQWORD(~sqw);
  #else
  SQWORD sqw = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(~sqw);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordBitNot()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordBitNot()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqw = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreUQWORD(~uqw);
  #else
  UQWORD uqw = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(~uqw);
  #endif
  return 1;
}


/* C/C++不允许"~double"
TZVMIndex CZVMVirtualThread::_doubleBitNot()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleBitNot()");
  double df = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(~df);
  return 1;
}
*/


TZVMIndex CZVMVirtualThread::_boolLogicNot()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_boolLogicNot()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool b = TOP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  StoreBool(!b);
  #else
  bool b = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(!b);
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_boolToByte()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_boolToByte()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool b = TOP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsByte(static_cast<UCHAR>(b));
  #else
  bool b = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(static_cast<UCHAR>(b));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_boolToSDWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_boolToSDWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool b = TOP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsSDWORD(static_cast<SDWORD>(b));
  #else
  bool b = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(static_cast<SDWORD>(b));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_boolToUDWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_boolToUDWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool b = TOP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsUDWORD(static_cast<UDWORD>(b));
  #else
  bool b = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(static_cast<UDWORD>(b));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_boolToSQWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_boolToSQWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool b = TOP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsSQWORD(static_cast<SQWORD>(b));
  #else
  bool b = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(static_cast<SQWORD>(b));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_boolToUQWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_boolToUQWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  bool b = TOP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsUQWORD(static_cast<UQWORD>(b));
  #else
  bool b = POP_BOOL(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(static_cast<UQWORD>(b));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteToBool()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteToBool()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uch = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(static_cast<bool>(uch));
  #else
  UCHAR uch = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(static_cast<bool>(uch));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteToSDWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteToSDWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uch = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsSDWORD(static_cast<SDWORD>(uch));
  #else
  UCHAR uch = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(static_cast<SDWORD>(uch));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteToUDWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteToUDWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uch = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsUDWORD(static_cast<UDWORD>(uch));
  #else
  UCHAR uch = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(static_cast<UDWORD>(uch));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteToSQWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteToSQWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uch = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsSQWORD(static_cast<SQWORD>(uch));
  #else
  UCHAR uch = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(static_cast<SQWORD>(uch));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteToUQWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteToUQWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uch = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsUQWORD(static_cast<UQWORD>(uch));
  #else
  UCHAR uch = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(static_cast<UQWORD>(uch));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_byteToDouble()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_byteToDouble()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UCHAR uch = TOP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsDouble(static_cast<double>(uch));
  #else
  UCHAR uch = POP_BYTE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(static_cast<double>(uch));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordToBool()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordToBool()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdw = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(static_cast<bool>(sdw));
  #else
  SDWORD sdw = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(static_cast<bool>(sdw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordToByte()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordToByte()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdw = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsByte(static_cast<UCHAR>(sdw));
  #else
  SDWORD sdw = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(static_cast<UCHAR>(sdw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordToUDWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordToUDWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdw = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsUDWORD(static_cast<UDWORD>(sdw));
  #else
  SDWORD sdw = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(static_cast<UDWORD>(sdw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordToSQWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordToSQWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdw = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsSQWORD(static_cast<SQWORD>(sdw));
  #else
  SDWORD sdw = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(static_cast<SQWORD>(sdw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordToUQWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordToUQWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdw = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsUQWORD(static_cast<UQWORD>(sdw));
  #else
  SDWORD sdw = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(static_cast<UQWORD>(sdw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sdwordToDouble()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sdwordToDouble()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SDWORD sdw = TOP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsDouble(static_cast<double>(sdw));
  #else
  SDWORD sdw = POP_SDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(static_cast<double>(sdw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordToBool()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordToBool()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(static_cast<bool>(udw));
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(static_cast<bool>(udw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordToByte()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordToByte()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsByte(static_cast<UCHAR>(udw));
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(static_cast<UCHAR>(udw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordToSDWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordToSDWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsSDWORD(static_cast<SDWORD>(udw));
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(static_cast<SDWORD>(udw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordToSQWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordToSQWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsSQWORD(static_cast<SQWORD>(udw));
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(static_cast<SQWORD>(udw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordToUQWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordToUQWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsUQWORD(static_cast<UQWORD>(udw));
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(static_cast<UQWORD>(udw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_udwordToDouble()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_udwordToDouble()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UDWORD udw = TOP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsDouble(static_cast<double>(udw));
  #else
  UDWORD udw = POP_UDWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(static_cast<double>(udw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordToBool()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordToBool()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqw = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(static_cast<bool>(sqw));
  #else
  SQWORD sqw = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(static_cast<bool>(sqw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordToByte()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordToByte()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqw = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsByte(static_cast<UCHAR>(sqw));
  #else
  SQWORD sqw = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(static_cast<UCHAR>(sqw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordToSDWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordToSDWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqw = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsSDWORD(static_cast<SDWORD>(sqw));
  #else
  SQWORD sqw = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(static_cast<SDWORD>(sqw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordToUDWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordToUDWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqw = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsUDWORD(static_cast<UDWORD>(sqw));
  #else
  SQWORD sqw = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(static_cast<UDWORD>(sqw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordToUQWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordToUQWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqw = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsUQWORD(static_cast<UQWORD>(sqw));
  #else
  SQWORD sqw = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(static_cast<UQWORD>(sqw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_sqwordToDouble()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_sqwordToDouble()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  SQWORD sqw = TOP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsDouble(static_cast<double>(sqw));
  #else
  SQWORD sqw = POP_SQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(static_cast<double>(sqw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordToBool()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordToBool()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqw = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsBool(static_cast<bool>(uqw));
  #else
  UQWORD uqw = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushBool(static_cast<bool>(uqw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordToByte()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordToByte()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqw = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsByte(static_cast<UCHAR>(uqw));
  #else
  UQWORD uqw = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(static_cast<UCHAR>(uqw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordToSDWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordToSDWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqw = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsSDWORD(static_cast<SDWORD>(uqw));
  #else
  UQWORD uqw = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(static_cast<SDWORD>(uqw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordToUDWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordToUDWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqw = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsUDWORD(static_cast<UDWORD>(uqw));
  #else
  UQWORD uqw = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(static_cast<UDWORD>(uqw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordToSQWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordToSQWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqw = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsSQWORD(static_cast<SQWORD>(uqw));
  #else
  UQWORD uqw = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(static_cast<SQWORD>(uqw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_uqwordToDouble()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_uqwordToDouble()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  UQWORD uqw = TOP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsDouble(static_cast<double>(uqw));
  #else
  UQWORD uqw = POP_UQWORD(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushDouble(static_cast<double>(uqw));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleToByte()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleToByte()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double df = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsByte(static_cast<UCHAR>(df));
  #else
  double df = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushByte(static_cast<UCHAR>(df));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleToSDWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleToSDWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double df = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsSDWORD(static_cast<SDWORD>(df));
  #else
  double df = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSDWORD(static_cast<SDWORD>(df));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleToUDWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleToUDWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double df = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsUDWORD(static_cast<UDWORD>(df));
  #else
  double df = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUDWORD(static_cast<UDWORD>(df));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleToSQWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleToSQWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double df = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsSQWORD(static_cast<SQWORD>(df));
  #else
  double df = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushSQWORD(static_cast<SQWORD>(df));
  #endif
  return 1;
}


TZVMIndex CZVMVirtualThread::_doubleToUQWORD()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::_doubleToUQWORD()");
  #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
  double df = TOP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  ReplaceAsUQWORD(static_cast<UQWORD>(df));
  #else
  double df = POP_DOUBLE(__FILE__, __PRETTY_FUNC__, __LINE__);
  PushUQWORD(static_cast<UQWORD>(df));
  #endif
  return 1;
}


