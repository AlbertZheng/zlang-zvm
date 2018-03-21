/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/CCodeGeneratorHelper.cpp,v $
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


#include <zls/zlang/CCodeGeneratorHelper.hpp>
#include <zls/zlang/ZLangCodeGeneratorTokenTypes.hpp>


// Begin namespace 'zlang::'
ZLS_BEGIN_NAMESPACE(zlang)


#ifdef ENABLE_TRACE_IN_OUT /* 如果要跟踪对"某个ZLang表达式"的"表达式Atom队列"的分析处理过程. */
  /* 返回在队头的Atom引用，但不pop它 */
  static CCodeGeneratorHelper::TExpressionAtom &
  _TraceFront(std::deque<CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms)
  {
    CCodeGeneratorHelper::TExpressionAtom & rtAtom = rdequeExpressionAtoms.front();
    CInOutTracer::Ident();
    std::cout << "Inspecting: " << rtAtom.stringTokenText << std::endl;
    return(rtAtom);
  }

  /* pop出在队头的Atom */
  static void
  _TracePopFront(std::deque<CCodeGeneratorHelper::TExpressionAtom> & rdequeExpressionAtoms)
  {
    CCodeGeneratorHelper::TExpressionAtom & rtAtom = rdequeExpressionAtoms.front();
    CInOutTracer::Ident();
    std::cout << "Poping: " << rtAtom.stringTokenText << std::endl;
    rdequeExpressionAtoms.pop_front();
  }

  #define __INSPECT_FRONT__(x)    _TraceFront(x)
  #define __POP_FRONT__(x)        _TracePopFront(x)
#else
  #define __INSPECT_FRONT__(x)    x.front()
  #define __POP_FRONT__(x)        x.pop_front()
#endif


/* ZLang支持的操作符：
 ******************************************************************************
  算术操作符：
  二元：
  ZVM_OPERATOR_ASSIGN,
  ZVM_OPERATOR_BOR, ZVM_OPERATOR_BXOR, ZVM_OPERATOR_BAND, ZVM_OPERATOR_SL, ZVM_OPERATOR_SR,
  ZVM_OPERATOR_PLUS, ZVM_OPERATOR_MINUS, ZVM_OPERATOR_STAR, ZVM_OPERATOR_DIV, ZVM_OPERATOR_MOD,

  一元：
  ZVM_OPERATOR_BNOT,
  ZVM_OPERATOR_POST_INC, ZVM_OPERATOR_POST_DEC
  ZVM_OPERATOR_INC, ZVM_OPERATOR_DEC, ZVM_OPERATOR_UNARY_PLUS, ZVM_OPERATOR_UNARY_MINUS,

  逻辑操作符：
  二元：
  ZVM_OPERATOR_LOR, ZVM_OPERATOR_LAND,
  ZVM_OPERATOR_NOT_EQUAL, ZVM_OPERATOR_EQUAL, ZVM_OPERATOR_LT, ZVM_OPERATOR_GT, ZVM_OPERATOR_LE, ZVM_OPERATOR_GE,

  一元：
  ZVM_OPERATOR_LNOT,

  特殊操作符：
  ZVM_OPERATOR_CAST, ZVM_OPERATOR_ADVANCE_CAST，ZVM_OPERATOR_CALLING, ZVM_OPERATOR_DOT, ZVM_OPERATOR_SUBSCRIPT,
 ******************************************************************************/


/******************************************************************************
 * 以下static global variables的命名规则：_SGan左值类型右值类型Operators
 ******************************************************************************/
/*
 * bool作为左值.
 */
static int _SGanBoolVoidOperators[] = {
  ZVM_OPERATOR_LNOT
};
static int _SGanBoolBoolOperators[] = {
  ZVM_OPERATOR_ASSIGN,
  ZVM_OPERATOR_LOR, ZVM_OPERATOR_LAND,
  ZVM_OPERATOR_NOT_EQUAL, ZVM_OPERATOR_EQUAL
};
static int _SGanBoolByteOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanBoolSDWORDOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST  // 非ASSIGN时才进行的cast
};
static int _SGanBoolUDWORDOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};
static int _SGanBoolSQWORDOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST  // 非ASSIGN时才进行的cast
};
static int _SGanBoolUQWORDOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};

/*
 * byte作为左值.
 */
static int _SGanByteVoidOperators[] = {
  ZVM_OPERATOR_BNOT,
  ZVM_OPERATOR_POST_INC, ZVM_OPERATOR_POST_DEC,
  ZVM_OPERATOR_INC, ZVM_OPERATOR_DEC, ZVM_OPERATOR_UNARY_PLUS, ZVM_OPERATOR_UNARY_MINUS,
};
static int _SGanByteBoolOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};
static int _SGanByteByteOperators[] = {
  ZVM_OPERATOR_ASSIGN,
  ZVM_OPERATOR_BOR, ZVM_OPERATOR_BXOR, ZVM_OPERATOR_BAND,
  ZVM_OPERATOR_PLUS, ZVM_OPERATOR_MINUS, ZVM_OPERATOR_STAR, ZVM_OPERATOR_DIV, ZVM_OPERATOR_MOD,
  ZVM_OPERATOR_LOR, ZVM_OPERATOR_LAND,
  ZVM_OPERATOR_NOT_EQUAL, ZVM_OPERATOR_EQUAL, ZVM_OPERATOR_LT, ZVM_OPERATOR_GT, ZVM_OPERATOR_LE, ZVM_OPERATOR_GE
};
static int _SGanByteSDWORDOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};
static int _SGanByteUDWORDOperators[] = {
  ZVM_OPERATOR_SL, ZVM_OPERATOR_SR,
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};
static int _SGanByteSQWORDOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};
static int _SGanByteUQWORDOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};
static int _SGanByteDoubleOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};

/*
 * sdword作为左值.
 */
static int _SGanSDWORDVoidOperators[] = {
  ZVM_OPERATOR_BNOT,
  ZVM_OPERATOR_POST_INC, ZVM_OPERATOR_POST_DEC,
  ZVM_OPERATOR_INC, ZVM_OPERATOR_DEC, ZVM_OPERATOR_UNARY_PLUS, ZVM_OPERATOR_UNARY_MINUS
};
static int _SGanSDWORDBoolOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanSDWORDByteOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanSDWORDSDWORDOperators[] = {
  ZVM_OPERATOR_ASSIGN,
  ZVM_OPERATOR_BOR, ZVM_OPERATOR_BXOR, ZVM_OPERATOR_BAND,
  ZVM_OPERATOR_PLUS, ZVM_OPERATOR_MINUS, ZVM_OPERATOR_STAR, ZVM_OPERATOR_DIV, ZVM_OPERATOR_MOD,
  ZVM_OPERATOR_LOR, ZVM_OPERATOR_LAND,
  ZVM_OPERATOR_NOT_EQUAL, ZVM_OPERATOR_EQUAL, ZVM_OPERATOR_LT, ZVM_OPERATOR_GT, ZVM_OPERATOR_LE, ZVM_OPERATOR_GE
};
static int _SGanSDWORDUDWORDOperators[] = {
  ZVM_OPERATOR_SL, ZVM_OPERATOR_SR,
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};
static int _SGanSDWORDSQWORDOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};
static int _SGanSDWORDUQWORDOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};
static int _SGanSDWORDDoubleOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};

/*
 * udword作为左值.
 */
static int _SGanUDWORDVoidOperators[] = {
  ZVM_OPERATOR_BNOT,
  ZVM_OPERATOR_POST_INC, ZVM_OPERATOR_POST_DEC,
  ZVM_OPERATOR_INC, ZVM_OPERATOR_DEC, ZVM_OPERATOR_UNARY_PLUS, ZVM_OPERATOR_UNARY_MINUS
};
static int _SGanUDWORDBoolOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanUDWORDByteOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanUDWORDSDWORDOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanUDWORDUDWORDOperators[] = {
  ZVM_OPERATOR_ASSIGN,
  ZVM_OPERATOR_BOR, ZVM_OPERATOR_BXOR, ZVM_OPERATOR_BAND, ZVM_OPERATOR_SL, ZVM_OPERATOR_SR,
  ZVM_OPERATOR_PLUS, ZVM_OPERATOR_MINUS, ZVM_OPERATOR_STAR, ZVM_OPERATOR_DIV, ZVM_OPERATOR_MOD,
  ZVM_OPERATOR_LOR, ZVM_OPERATOR_LAND,
  ZVM_OPERATOR_NOT_EQUAL, ZVM_OPERATOR_EQUAL, ZVM_OPERATOR_LT, ZVM_OPERATOR_GT, ZVM_OPERATOR_LE, ZVM_OPERATOR_GE
};
static int _SGanUDWORDSQWORDOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};
static int _SGanUDWORDUQWORDOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};
static int _SGanUDWORDDoubleOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};

/*
 * sqword作为左值.
 */
static int _SGanSQWORDVoidOperators[] = {
  ZVM_OPERATOR_BNOT,
  ZVM_OPERATOR_POST_INC, ZVM_OPERATOR_POST_DEC,
  ZVM_OPERATOR_INC, ZVM_OPERATOR_DEC, ZVM_OPERATOR_UNARY_PLUS, ZVM_OPERATOR_UNARY_MINUS
};
static int _SGanSQWORDBoolOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanSQWORDByteOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanSQWORDSDWORDOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanSQWORDUDWORDOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanSQWORDSQWORDOperators[] = {
  ZVM_OPERATOR_ASSIGN,
  ZVM_OPERATOR_BOR, ZVM_OPERATOR_BXOR, ZVM_OPERATOR_BAND,
  ZVM_OPERATOR_PLUS, ZVM_OPERATOR_MINUS, ZVM_OPERATOR_STAR, ZVM_OPERATOR_DIV, ZVM_OPERATOR_MOD,
  ZVM_OPERATOR_LOR, ZVM_OPERATOR_LAND,
  ZVM_OPERATOR_NOT_EQUAL, ZVM_OPERATOR_EQUAL, ZVM_OPERATOR_LT, ZVM_OPERATOR_GT, ZVM_OPERATOR_LE, ZVM_OPERATOR_GE
};
static int _SGanSQWORDUQWORDOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};
static int _SGanSQWORDDoubleOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};

/*
 * uqword作为左值.
 */
static int _SGanUQWORDVoidOperators[] = {
  ZVM_OPERATOR_BNOT,
  ZVM_OPERATOR_POST_INC, ZVM_OPERATOR_POST_DEC,
  ZVM_OPERATOR_INC, ZVM_OPERATOR_DEC, ZVM_OPERATOR_UNARY_PLUS, ZVM_OPERATOR_UNARY_MINUS
};
static int _SGanUQWORDBoolOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanUQWORDByteOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanUQWORDSDWORDOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanUQWORDUDWORDOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanUQWORDSQWORDOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanUQWORDUQWORDOperators[] = {
  ZVM_OPERATOR_ASSIGN,
  ZVM_OPERATOR_BOR, ZVM_OPERATOR_BXOR, ZVM_OPERATOR_BAND, ZVM_OPERATOR_SL, ZVM_OPERATOR_SR,
  ZVM_OPERATOR_PLUS, ZVM_OPERATOR_MINUS, ZVM_OPERATOR_STAR, ZVM_OPERATOR_DIV, ZVM_OPERATOR_MOD,
  ZVM_OPERATOR_LOR, ZVM_OPERATOR_LAND,
  ZVM_OPERATOR_NOT_EQUAL, ZVM_OPERATOR_EQUAL, ZVM_OPERATOR_LT, ZVM_OPERATOR_GT, ZVM_OPERATOR_LE, ZVM_OPERATOR_GE
};
static int _SGanUQWORDDoubleOperators[] = {
  ZVM_OPERATOR_CAST,
  ZVM_OPERATOR_ADVANCE_CAST
};

/*
 * double作为左值.
 */
static int _SGanDoubleVoidOperators[] = {
  ZVM_OPERATOR_POST_INC, ZVM_OPERATOR_POST_DEC,
  ZVM_OPERATOR_INC, ZVM_OPERATOR_DEC, ZVM_OPERATOR_UNARY_PLUS, ZVM_OPERATOR_UNARY_MINUS
};
static int _SGanDoubleByteOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanDoubleSDWORDOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanDoubleUDWORDOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanDoubleSQWORDOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanDoubleUQWORDOperators[] = {
  ZVM_OPERATOR_CAST
};
static int _SGanDoubleDoubleOperators[] = {
  ZVM_OPERATOR_ASSIGN,
  ZVM_OPERATOR_PLUS, ZVM_OPERATOR_MINUS, ZVM_OPERATOR_STAR, ZVM_OPERATOR_DIV,
  ZVM_OPERATOR_LOR, ZVM_OPERATOR_LAND,
  ZVM_OPERATOR_NOT_EQUAL, ZVM_OPERATOR_EQUAL, ZVM_OPERATOR_LT, ZVM_OPERATOR_GT, ZVM_OPERATOR_LE, ZVM_OPERATOR_GE
};

/*
 * string作为左值.
 */
static int _SGanStringStringOperators[] = {
  ZVM_OPERATOR_ASSIGN,
  ZVM_OPERATOR_PLUS,
  ZVM_OPERATOR_NOT_EQUAL, ZVM_OPERATOR_EQUAL, ZVM_OPERATOR_LT, ZVM_OPERATOR_GT, ZVM_OPERATOR_LE, ZVM_OPERATOR_GE
};

/*
 * rope作为左值.
 */
static int _SGanRopeRopeOperators[] = {
  ZVM_OPERATOR_ASSIGN,
  ZVM_OPERATOR_PLUS,
  ZVM_OPERATOR_NOT_EQUAL, ZVM_OPERATOR_EQUAL, ZVM_OPERATOR_LT, ZVM_OPERATOR_GT, ZVM_OPERATOR_LE, ZVM_OPERATOR_GE
};

/*
 * ipv4addr作为左值.
 */
static int _SGanIPv4AddrIPv4AddrOperators[] = {
  ZVM_OPERATOR_ASSIGN,
  ZVM_OPERATOR_NOT_EQUAL, ZVM_OPERATOR_EQUAL
};

/*
 * pport作为左值.
 */
static int _SGanPPortPPortOperators[] = {
  ZVM_OPERATOR_ASSIGN,
  ZVM_OPERATOR_NOT_EQUAL, ZVM_OPERATOR_EQUAL, ZVM_OPERATOR_LT, ZVM_OPERATOR_GT, ZVM_OPERATOR_LE, ZVM_OPERATOR_GE
};


/******************************************************************************
 * 以下static global variables的命名规则：_SGasi左值类型Columns
 ******************************************************************************/
static CCodeGeneratorHelper::TCompatibleTableColumn _SGasiBoolColumns[] = {
  {zvm::CstringZVM_VOID_SIGNATURE, sizeof(_SGanBoolVoidOperators)/sizeof(int), _SGanBoolVoidOperators},
  {zvm::CstringZVM_BYTE_SIGNATURE, sizeof(_SGanBoolByteOperators)/sizeof(int), _SGanBoolByteOperators},
  {zvm::CstringZVM_BOOL_SIGNATURE, sizeof(_SGanBoolBoolOperators)/sizeof(int), _SGanBoolBoolOperators},
  {zvm::CstringZVM_SDWORD_SIGNATURE, sizeof(_SGanBoolSDWORDOperators)/sizeof(int), _SGanBoolSDWORDOperators},
  {zvm::CstringZVM_UDWORD_SIGNATURE, sizeof(_SGanBoolUDWORDOperators)/sizeof(int), _SGanBoolUDWORDOperators},
  {zvm::CstringZVM_SQWORD_SIGNATURE, sizeof(_SGanBoolSQWORDOperators)/sizeof(int), _SGanBoolSQWORDOperators},
  {zvm::CstringZVM_UQWORD_SIGNATURE, sizeof(_SGanBoolUQWORDOperators)/sizeof(int), _SGanBoolUQWORDOperators}
};
static CCodeGeneratorHelper::TCompatibleTableColumn _SGasiByteColumns[] = {
  {zvm::CstringZVM_VOID_SIGNATURE, sizeof(_SGanByteVoidOperators)/sizeof(int), _SGanByteVoidOperators},
  {zvm::CstringZVM_BYTE_SIGNATURE, sizeof(_SGanByteByteOperators)/sizeof(int), _SGanByteByteOperators},
  {zvm::CstringZVM_BOOL_SIGNATURE, sizeof(_SGanByteBoolOperators)/sizeof(int), _SGanByteBoolOperators},
  {zvm::CstringZVM_SDWORD_SIGNATURE, sizeof(_SGanByteSDWORDOperators)/sizeof(int), _SGanByteSDWORDOperators},
  {zvm::CstringZVM_UDWORD_SIGNATURE, sizeof(_SGanByteUDWORDOperators)/sizeof(int), _SGanByteUDWORDOperators},
  {zvm::CstringZVM_SQWORD_SIGNATURE, sizeof(_SGanByteSQWORDOperators)/sizeof(int), _SGanByteSQWORDOperators},
  {zvm::CstringZVM_UQWORD_SIGNATURE, sizeof(_SGanByteUQWORDOperators)/sizeof(int), _SGanByteUQWORDOperators},
  {zvm::CstringZVM_DOUBLE_SIGNATURE, sizeof(_SGanByteDoubleOperators)/sizeof(int), _SGanByteDoubleOperators}
};
static CCodeGeneratorHelper::TCompatibleTableColumn _SGasiSDWORDColumns[] = {
  {zvm::CstringZVM_VOID_SIGNATURE, sizeof(_SGanSDWORDVoidOperators)/sizeof(int), _SGanSDWORDVoidOperators},
  {zvm::CstringZVM_BYTE_SIGNATURE, sizeof(_SGanSDWORDByteOperators)/sizeof(int), _SGanSDWORDByteOperators},
  {zvm::CstringZVM_BOOL_SIGNATURE, sizeof(_SGanSDWORDBoolOperators)/sizeof(int), _SGanSDWORDBoolOperators},
  {zvm::CstringZVM_SDWORD_SIGNATURE, sizeof(_SGanSDWORDSDWORDOperators)/sizeof(int), _SGanSDWORDSDWORDOperators},
  {zvm::CstringZVM_UDWORD_SIGNATURE, sizeof(_SGanSDWORDUDWORDOperators)/sizeof(int), _SGanSDWORDUDWORDOperators},
  {zvm::CstringZVM_SQWORD_SIGNATURE, sizeof(_SGanSDWORDSQWORDOperators)/sizeof(int), _SGanSDWORDSQWORDOperators},
  {zvm::CstringZVM_UQWORD_SIGNATURE, sizeof(_SGanSDWORDUQWORDOperators)/sizeof(int), _SGanSDWORDUQWORDOperators},
  {zvm::CstringZVM_DOUBLE_SIGNATURE, sizeof(_SGanSDWORDDoubleOperators)/sizeof(int), _SGanSDWORDDoubleOperators}
};
static CCodeGeneratorHelper::TCompatibleTableColumn _SGasiUDWORDColumns[] = {
  {zvm::CstringZVM_VOID_SIGNATURE, sizeof(_SGanUDWORDVoidOperators)/sizeof(int), _SGanUDWORDVoidOperators},
  {zvm::CstringZVM_BYTE_SIGNATURE, sizeof(_SGanUDWORDByteOperators)/sizeof(int), _SGanUDWORDByteOperators},
  {zvm::CstringZVM_BOOL_SIGNATURE, sizeof(_SGanUDWORDBoolOperators)/sizeof(int), _SGanUDWORDBoolOperators},
  {zvm::CstringZVM_SDWORD_SIGNATURE, sizeof(_SGanUDWORDSDWORDOperators)/sizeof(int), _SGanUDWORDSDWORDOperators},
  {zvm::CstringZVM_UDWORD_SIGNATURE, sizeof(_SGanUDWORDUDWORDOperators)/sizeof(int), _SGanUDWORDUDWORDOperators},
  {zvm::CstringZVM_SQWORD_SIGNATURE, sizeof(_SGanUDWORDSQWORDOperators)/sizeof(int), _SGanUDWORDSQWORDOperators},
  {zvm::CstringZVM_UQWORD_SIGNATURE, sizeof(_SGanUDWORDUQWORDOperators)/sizeof(int), _SGanUDWORDUQWORDOperators},
  {zvm::CstringZVM_DOUBLE_SIGNATURE, sizeof(_SGanUDWORDDoubleOperators)/sizeof(int), _SGanUDWORDDoubleOperators}
};
static CCodeGeneratorHelper::TCompatibleTableColumn _SGasiSQWORDColumns[] = {
  {zvm::CstringZVM_VOID_SIGNATURE, sizeof(_SGanSQWORDVoidOperators)/sizeof(int), _SGanSQWORDVoidOperators},
  {zvm::CstringZVM_BYTE_SIGNATURE, sizeof(_SGanSQWORDByteOperators)/sizeof(int), _SGanSQWORDByteOperators},
  {zvm::CstringZVM_BOOL_SIGNATURE, sizeof(_SGanSQWORDBoolOperators)/sizeof(int), _SGanSQWORDBoolOperators},
  {zvm::CstringZVM_SDWORD_SIGNATURE, sizeof(_SGanSQWORDSDWORDOperators)/sizeof(int), _SGanSQWORDSDWORDOperators},
  {zvm::CstringZVM_UDWORD_SIGNATURE, sizeof(_SGanSQWORDUDWORDOperators)/sizeof(int), _SGanSQWORDUDWORDOperators},
  {zvm::CstringZVM_SQWORD_SIGNATURE, sizeof(_SGanSQWORDSQWORDOperators)/sizeof(int), _SGanSQWORDSQWORDOperators},
  {zvm::CstringZVM_UQWORD_SIGNATURE, sizeof(_SGanSQWORDUQWORDOperators)/sizeof(int), _SGanSQWORDUQWORDOperators},
  {zvm::CstringZVM_DOUBLE_SIGNATURE, sizeof(_SGanSQWORDDoubleOperators)/sizeof(int), _SGanSQWORDDoubleOperators}
};
static CCodeGeneratorHelper::TCompatibleTableColumn _SGasiUQWORDColumns[] = {
  {zvm::CstringZVM_VOID_SIGNATURE, sizeof(_SGanUQWORDVoidOperators)/sizeof(int), _SGanUQWORDVoidOperators},
  {zvm::CstringZVM_BYTE_SIGNATURE, sizeof(_SGanUQWORDByteOperators)/sizeof(int), _SGanUQWORDByteOperators},
  {zvm::CstringZVM_BOOL_SIGNATURE, sizeof(_SGanUQWORDBoolOperators)/sizeof(int), _SGanUQWORDBoolOperators},
  {zvm::CstringZVM_SDWORD_SIGNATURE, sizeof(_SGanUQWORDSDWORDOperators)/sizeof(int), _SGanUQWORDSDWORDOperators},
  {zvm::CstringZVM_UDWORD_SIGNATURE, sizeof(_SGanUQWORDUDWORDOperators)/sizeof(int), _SGanUQWORDUDWORDOperators},
  {zvm::CstringZVM_SQWORD_SIGNATURE, sizeof(_SGanUQWORDSQWORDOperators)/sizeof(int), _SGanUQWORDSQWORDOperators},
  {zvm::CstringZVM_UQWORD_SIGNATURE, sizeof(_SGanUQWORDUQWORDOperators)/sizeof(int), _SGanUQWORDUQWORDOperators},
  {zvm::CstringZVM_DOUBLE_SIGNATURE, sizeof(_SGanUQWORDDoubleOperators)/sizeof(int), _SGanUQWORDDoubleOperators}
};
static CCodeGeneratorHelper::TCompatibleTableColumn _SGasiDoubleColumns[] = {
  {zvm::CstringZVM_VOID_SIGNATURE, sizeof(_SGanDoubleVoidOperators)/sizeof(int), _SGanDoubleVoidOperators},
  {zvm::CstringZVM_BYTE_SIGNATURE, sizeof(_SGanDoubleByteOperators)/sizeof(int), _SGanDoubleByteOperators},
  {zvm::CstringZVM_SDWORD_SIGNATURE, sizeof(_SGanDoubleSDWORDOperators)/sizeof(int), _SGanDoubleSDWORDOperators},
  {zvm::CstringZVM_UDWORD_SIGNATURE, sizeof(_SGanDoubleUDWORDOperators)/sizeof(int), _SGanDoubleUDWORDOperators},
  {zvm::CstringZVM_SQWORD_SIGNATURE, sizeof(_SGanDoubleSQWORDOperators)/sizeof(int), _SGanDoubleSQWORDOperators},
  {zvm::CstringZVM_UQWORD_SIGNATURE, sizeof(_SGanDoubleUQWORDOperators)/sizeof(int), _SGanDoubleUQWORDOperators},
  {zvm::CstringZVM_DOUBLE_SIGNATURE, sizeof(_SGanDoubleDoubleOperators)/sizeof(int), _SGanDoubleDoubleOperators}
};
static CCodeGeneratorHelper::TCompatibleTableColumn _SGasiStringColumns[] = {
  {zvm::CstringZVM_STRING_SIGNATURE, sizeof(_SGanStringStringOperators)/sizeof(int), _SGanStringStringOperators}
};
static CCodeGeneratorHelper::TCompatibleTableColumn _SGasiRopeColumns[] = {
  {zvm::CstringZVM_ROPE_SIGNATURE, sizeof(_SGanRopeRopeOperators)/sizeof(int), _SGanRopeRopeOperators}
};
static CCodeGeneratorHelper::TCompatibleTableColumn _SGasiIPv4AddrColumns[] = {
  {zvm::CstringZVM_IPv4ADDR_SIGNATURE, sizeof(_SGanIPv4AddrIPv4AddrOperators)/sizeof(int), _SGanIPv4AddrIPv4AddrOperators}
};
static CCodeGeneratorHelper::TCompatibleTableColumn _SGasiPPortColumns[] = {
  {zvm::CstringZVM_PPORT_SIGNATURE, sizeof(_SGanPPortPPortOperators)/sizeof(int), _SGanPPortPPortOperators}
};


/*******************************************************************************
 * class CCodeGeneratorHelper
 ******************************************************************************/
/* static member */
CCodeGeneratorHelper::TCompatibleTableLine CCodeGeneratorHelper::_SasiSignatureCompatibleTable[] = {
  {zvm::CstringZVM_BOOL_SIGNATURE,
   sizeof(_SGasiBoolColumns)/sizeof(CCodeGeneratorHelper::TCompatibleTableColumn),
   _SGasiBoolColumns},

  {zvm::CstringZVM_BYTE_SIGNATURE,
   sizeof(_SGasiByteColumns)/sizeof(CCodeGeneratorHelper::TCompatibleTableColumn),
   _SGasiByteColumns},

  {zvm::CstringZVM_SDWORD_SIGNATURE,
   sizeof(_SGasiSDWORDColumns)/sizeof(CCodeGeneratorHelper::TCompatibleTableColumn),
   _SGasiSDWORDColumns},

  {zvm::CstringZVM_UDWORD_SIGNATURE,
   sizeof(_SGasiUDWORDColumns)/sizeof(CCodeGeneratorHelper::TCompatibleTableColumn),
   _SGasiUDWORDColumns},

  {zvm::CstringZVM_SQWORD_SIGNATURE,
   sizeof(_SGasiSQWORDColumns)/sizeof(CCodeGeneratorHelper::TCompatibleTableColumn),
   _SGasiSQWORDColumns},

  {zvm::CstringZVM_UQWORD_SIGNATURE,
   sizeof(_SGasiUQWORDColumns)/sizeof(CCodeGeneratorHelper::TCompatibleTableColumn),
   _SGasiUQWORDColumns},

  {zvm::CstringZVM_DOUBLE_SIGNATURE,
   sizeof(_SGasiDoubleColumns)/sizeof(CCodeGeneratorHelper::TCompatibleTableColumn),
   _SGasiDoubleColumns},

  {zvm::CstringZVM_STRING_SIGNATURE,
   sizeof(_SGasiStringColumns)/sizeof(CCodeGeneratorHelper::TCompatibleTableColumn),
   _SGasiStringColumns},

  {zvm::CstringZVM_ROPE_SIGNATURE,
   sizeof(_SGasiRopeColumns)/sizeof(CCodeGeneratorHelper::TCompatibleTableColumn),
   _SGasiRopeColumns},

  {zvm::CstringZVM_IPv4ADDR_SIGNATURE,
   sizeof(_SGasiIPv4AddrColumns)/sizeof(CCodeGeneratorHelper::TCompatibleTableColumn),
   _SGasiIPv4AddrColumns},

  {zvm::CstringZVM_PPORT_SIGNATURE,
   sizeof(_SGasiPPortColumns)/sizeof(CCodeGeneratorHelper::TCompatibleTableColumn),
   _SGasiPPortColumns}
};

int CCodeGeneratorHelper::_SnLineCountOfSignatureCompatibleTable =
  sizeof(CCodeGeneratorHelper::_SasiSignatureCompatibleTable)/
  sizeof(CCodeGeneratorHelper::TCompatibleTableLine);


CCodeGeneratorHelper::CCodeGeneratorHelper()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::CCodeGeneratorHelper()");
  std::string stringError = "You should not call the constructor that is only written \
for meeting 'ZLangCodeGenerator::ZLangCodeGenerator()' generated by ANLTR !";
  throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
}


zvm::TZVMIndex CCodeGeneratorHelper::GenerateInstruction(CInstructionContainer_auto autoCurrentInstructionContainer,
                                                         int nLineNumberDebug,
                                                         zvm::TZVMICode nInstructionCode)
{
  int nInstructionIndex = autoCurrentInstructionContainer->AppendInstruction(nInstructionCode);
  if (_nLatestLineNumberDebug != nLineNumberDebug)
  // 这是新的行号,产生debug info
  {
    autoCurrentInstructionContainer->AppendLineNumberDebugInfo(nInstructionIndex, nLineNumberDebug);
    // update
    _nLatestLineNumberDebug = nLineNumberDebug;
  }
  return(nInstructionIndex);
}


zvm::TZVMIndex CCodeGeneratorHelper::GenerateInstruction(CInstructionContainer_auto autoCurrentInstructionContainer,
                                                         int nLineNumberDebug,
                                                         zvm::TZVMICode nInstructionCode,
                                                         UCHAR uchOperand)
{
  int nInstructionIndex = autoCurrentInstructionContainer->AppendInstruction(nInstructionCode, uchOperand);
  if (_nLatestLineNumberDebug != nLineNumberDebug)
  // 这是新的行号,产生debug info
  {
    autoCurrentInstructionContainer->AppendLineNumberDebugInfo(nInstructionIndex, nLineNumberDebug);
    // update
    _nLatestLineNumberDebug = nLineNumberDebug;
  }
  return(nInstructionIndex);
}


zvm::TZVMIndex CCodeGeneratorHelper::GenerateInstruction(CInstructionContainer_auto autoCurrentInstructionContainer,
                                                         int nLineNumberDebug,
                                                         zvm::TZVMICode nInstructionCode,
                                                         UWORD uwOperand)
{
  int nInstructionIndex = autoCurrentInstructionContainer->AppendInstruction(nInstructionCode, uwOperand);
  if (_nLatestLineNumberDebug != nLineNumberDebug)
  // 这是新的行号,产生debug info
  {
    autoCurrentInstructionContainer->AppendLineNumberDebugInfo(nInstructionIndex, nLineNumberDebug);
    // update
    _nLatestLineNumberDebug = nLineNumberDebug;
  }
  return(nInstructionIndex);
}


zvm::TZVMIndex CCodeGeneratorHelper::GenerateInstruction(CInstructionContainer_auto autoCurrentInstructionContainer,
                                                         int nLineNumberDebug,
                                                         zvm::TZVMICode nInstructionCode,
                                                         SWORD swOperand)
{
  int nInstructionIndex = autoCurrentInstructionContainer->AppendInstruction(nInstructionCode, swOperand);
  if (_nLatestLineNumberDebug != nLineNumberDebug)
  // 这是新的行号,产生debug info
  {
    autoCurrentInstructionContainer->AppendLineNumberDebugInfo(nInstructionIndex, nLineNumberDebug);
    // update
    _nLatestLineNumberDebug = nLineNumberDebug;
  }
  return(nInstructionIndex);
}


zvm::TZVMIndex CCodeGeneratorHelper::GenerateInstruction(CInstructionContainer_auto autoCurrentInstructionContainer,
                                                         int nLineNumberDebug,
                                                         zvm::TZVMICode nInstructionCode,
                                                         zvm::TZVMIndex nIndex)
{
  int nInstructionIndex = autoCurrentInstructionContainer->AppendInstruction(nInstructionCode, nIndex);
  if (_nLatestLineNumberDebug != nLineNumberDebug)
  // 这是新的行号,产生debug info
  {
    autoCurrentInstructionContainer->AppendLineNumberDebugInfo(nInstructionIndex, nLineNumberDebug);
    // update
    _nLatestLineNumberDebug = nLineNumberDebug;
  }
  return(nInstructionIndex);
}


zvm::TZVMIndex CCodeGeneratorHelper::GenerateInstruction(CInstructionContainer_auto autoCurrentInstructionContainer,
                                                         int nLineNumberDebug,
                                                         zvm::TZVMICode nInstructionCode,
                                                         UDWORD udwOperand)
{
  int nInstructionIndex = autoCurrentInstructionContainer->AppendInstruction(nInstructionCode, udwOperand);
  if (_nLatestLineNumberDebug != nLineNumberDebug)
  // 这是新的行号,产生debug info
  {
    autoCurrentInstructionContainer->AppendLineNumberDebugInfo(nInstructionIndex, nLineNumberDebug);
    // update
    _nLatestLineNumberDebug = nLineNumberDebug;
  }
  return(nInstructionIndex);
}


zvm::TZVMIndex CCodeGeneratorHelper::InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                                             CInstructionContainer_auto autoCurrentInstructionContainer,
                                                             int nLineNumberDebug,
                                                             zvm::TZVMICode nInstructionCode)
{
  int nInstructionIndex = autoCurrentInstructionContainer->InsertInstructionBefore(nBeforePosition, nInstructionCode);
  if (_nLatestLineNumberDebug != nLineNumberDebug)
  // 这是新的行号,产生debug info
  {
    autoCurrentInstructionContainer->AppendLineNumberDebugInfo(nInstructionIndex, nLineNumberDebug);
    // update
    _nLatestLineNumberDebug = nLineNumberDebug;
  }
  return(nInstructionIndex);
}


zvm::TZVMIndex CCodeGeneratorHelper::InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                                             CInstructionContainer_auto autoCurrentInstructionContainer,
                                                             int nLineNumberDebug,
                                                             zvm::TZVMICode nInstructionCode,
                                                             UCHAR uchOperand)
{
  int nInstructionIndex = autoCurrentInstructionContainer->InsertInstructionBefore(nBeforePosition, nInstructionCode, uchOperand);
  if (_nLatestLineNumberDebug != nLineNumberDebug)
  // 这是新的行号,产生debug info
  {
    autoCurrentInstructionContainer->AppendLineNumberDebugInfo(nInstructionIndex, nLineNumberDebug);
    // update
    _nLatestLineNumberDebug = nLineNumberDebug;
  }
  return(nInstructionIndex);
}


zvm::TZVMIndex CCodeGeneratorHelper::InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                                             CInstructionContainer_auto autoCurrentInstructionContainer,
                                                             int nLineNumberDebug,
                                                             zvm::TZVMICode nInstructionCode,
                                                             UWORD uwOperand)
{
  int nInstructionIndex = autoCurrentInstructionContainer->InsertInstructionBefore(nBeforePosition, nInstructionCode, uwOperand);
  if (_nLatestLineNumberDebug != nLineNumberDebug)
  // 这是新的行号,产生debug info
  {
    autoCurrentInstructionContainer->AppendLineNumberDebugInfo(nInstructionIndex, nLineNumberDebug);
    // update
    _nLatestLineNumberDebug = nLineNumberDebug;
  }
  return(nInstructionIndex);
}


zvm::TZVMIndex CCodeGeneratorHelper::InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                                             CInstructionContainer_auto autoCurrentInstructionContainer,
                                                             int nLineNumberDebug,
                                                             zvm::TZVMICode nInstructionCode,
                                                             SWORD swOperand)
{
  int nInstructionIndex = autoCurrentInstructionContainer->InsertInstructionBefore(nBeforePosition, nInstructionCode, swOperand);
  if (_nLatestLineNumberDebug != nLineNumberDebug)
  // 这是新的行号,产生debug info
  {
    autoCurrentInstructionContainer->AppendLineNumberDebugInfo(nInstructionIndex, nLineNumberDebug);
    // update
    _nLatestLineNumberDebug = nLineNumberDebug;
  }
  return(nInstructionIndex);
}


zvm::TZVMIndex CCodeGeneratorHelper::InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                                             CInstructionContainer_auto autoCurrentInstructionContainer,
                                                             int nLineNumberDebug,
                                                             zvm::TZVMICode nInstructionCode,
                                                             zvm::TZVMIndex nIndex)
{
  int nInstructionIndex = autoCurrentInstructionContainer->InsertInstructionBefore(nBeforePosition, nInstructionCode, nIndex);
  if (_nLatestLineNumberDebug != nLineNumberDebug)
  // 这是新的行号,产生debug info
  {
    autoCurrentInstructionContainer->AppendLineNumberDebugInfo(nInstructionIndex, nLineNumberDebug);
    // update
    _nLatestLineNumberDebug = nLineNumberDebug;
  }
  return(nInstructionIndex);
}


zvm::TZVMIndex CCodeGeneratorHelper::InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                                             CInstructionContainer_auto autoCurrentInstructionContainer,
                                                             int nLineNumberDebug,
                                                             zvm::TZVMICode nInstructionCode,
                                                             UDWORD udwOperand)
{
  int nInstructionIndex = autoCurrentInstructionContainer->InsertInstructionBefore(nBeforePosition, nInstructionCode, udwOperand);
  if (_nLatestLineNumberDebug != nLineNumberDebug)
  // 这是新的行号,产生debug info
  {
    autoCurrentInstructionContainer->AppendLineNumberDebugInfo(nInstructionIndex, nLineNumberDebug);
    // update
    _nLatestLineNumberDebug = nLineNumberDebug;
  }
  return(nInstructionIndex);
}


void CCodeGeneratorHelper::PrepareGlobalFunctionFramework(
  CInstructionContainer_auto autoCurrentInstructionContainer,
  int nLineNumberDebug,
  const std::vector<std::string> & rvectorFindNames,
  const std::string & rstringFunctionName,
  const std::string & rstringFunctionSignature,
  const std::vector<std::pair<std::string, std::string> > & rvectorParameters,
  zvm::TAccessModifierTag eAccessModifierTag)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::PrepareGlobalFunctionFramework()");

  // 插入function的name-and-signature-reference
  zvm::TZVMIndex nNameAndSignatureIndex = _ciConstantPool.InsertNameAndSignatureReference(
                                                                 rstringFunctionName,
                                                                 rstringFunctionSignature);
  // 插入function的global-function-reference
  CConstantPoolElement_auto autoElement =
              new __OPTION(_THROW) CGlobalFunctionReference(nNameAndSignatureIndex, eAccessModifierTag);
  zvm::TZVMIndex iFunctionReference = _ciConstantPool.Insert(autoElement);

  // Set the function constant pool reference of the 'CZLangFunction instance'
  //autoCurrentInstructionContainer->SetFunctionReference(iFunctionReference);
  CZLangFunction * pciZLangFunction = dynamic_cast<CZLangFunction *>(autoCurrentInstructionContainer.get());
  LogAssert0(pciZLangFunction, "Bug: Impossible 'dynamic_cast<CZLangFunction *>' failure");
  pciZLangFunction->SetFunctionReference(iFunctionReference);

  // collect the 'CZLangFunction instance'
  _dequeGlobalFunctions.push_back(autoCurrentInstructionContainer);

  // 产生"pushBP"指令
  GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_pushBP);

  // 产生parameters的stack variable debug info，注意：隐含参数也算在内
  std::vector<std::string> vectorFindNames(rvectorFindNames);
  std::vector<std::pair<std::string, std::string> >::const_iterator it;
  for (it = rvectorParameters.begin(); it != rvectorParameters.end(); ++it)
  {
    vectorFindNames.push_back((*it).first);
    AppendStackVariableDebugInfo(autoCurrentInstructionContainer,
                                 vectorFindNames,
                                 (*it).first,
                                 (*it).second);
    vectorFindNames.pop_back();
  }

  // set parameters count
  //autoCurrentInstructionContainer->SetParameterCount(rvectorParameters.size());
  pciZLangFunction->SetParameterCount(rvectorParameters.size());
}


std::string CCodeGeneratorHelper::GenerateExpressionInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::GenerateExpressionInstruction()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  /*
   * 注意：
   * (1) rdequeExpressionAtoms应该是饱和的，即当最后一个element被pop_front()
   * 后，递归应该返回到GenerateExpressionInstruction()的里面，然后由
   * GenerateExpressionInstruction()里面返回class ZlangCodeGenerator.
   * (2) GenerateExpressionInstruction()一次只能产生一条完整的ZLang expression，
   * 如果有多条expression需要产生代码，则必须调用GenerateExpressionInstruction()
   * 多次.
   */
  LogAssert0(rdequeExpressionAtoms.size() > 0, "Unexpected empty std::deque");

  // 置所有已经被申请的临时变量为没有被使用状态，临时变量只能动态被增加但是却不能被动态减少.
  autoCurrentInstructionContainer->FreeAllTempVariables();

  std::string stringResultSignature = _GenerateExpressionInstructionBackend(autoCurrentInstructionContainer,
                                                                            rvectorFindNames,
                                                                            rdequeExpressionAtoms);

  return stringResultSignature;
}


std::string CCodeGeneratorHelper::_GenerateExpressionInstructionBackend(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::_GenerateExpressionInstructionBackend()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  std::string stringResultSignature;
  TExpressionAtom tAtom = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
  int nTokenType = tAtom.nTokenType;

  switch (nTokenType)
  {
    case ZLangCodeGeneratorTokenTypes::ASSIGN:
    case ZLangCodeGeneratorTokenTypes::NESTED_ASSIGN:  // 2001/5/10
    case ZLangCodeGeneratorTokenTypes::REFERENCE_ADDRESS_ASSIGN:  // 2001/7/10
    case ZLangCodeGeneratorTokenTypes::RETURN_PSEUDO_ASSIGN:  // 2001/7/10
      stringResultSignature = GenerateAssignExpressionInstruction(autoCurrentInstructionContainer,
                                                                  rvectorFindNames,
                                                                  rdequeExpressionAtoms);
      break;

    /* 二元表达式 */
    case ZLangCodeGeneratorTokenTypes::LOR:
    case ZLangCodeGeneratorTokenTypes::LAND:
    case ZLangCodeGeneratorTokenTypes::BOR:
    case ZLangCodeGeneratorTokenTypes::BXOR:
    case ZLangCodeGeneratorTokenTypes::BAND:
    case ZLangCodeGeneratorTokenTypes::NOT_EQUAL:
    case ZLangCodeGeneratorTokenTypes::EQUAL:
    case ZLangCodeGeneratorTokenTypes::LT_:
    case ZLangCodeGeneratorTokenTypes::GT:
    case ZLangCodeGeneratorTokenTypes::LE:
    case ZLangCodeGeneratorTokenTypes::GE:
    case ZLangCodeGeneratorTokenTypes::SL:
    case ZLangCodeGeneratorTokenTypes::SR:
    case ZLangCodeGeneratorTokenTypes::PLUS:
    case ZLangCodeGeneratorTokenTypes::MINUS:
    case ZLangCodeGeneratorTokenTypes::STAR:
    case ZLangCodeGeneratorTokenTypes::DIV:
    case ZLangCodeGeneratorTokenTypes::MOD:
      stringResultSignature = GenerateBinaryExpressionInstruction(autoCurrentInstructionContainer,
                                                                  rvectorFindNames,
                                                                  rdequeExpressionAtoms);
      break;

    /* 一元表达式 */
    case ZLangCodeGeneratorTokenTypes::INC:
    case ZLangCodeGeneratorTokenTypes::DEC:
    case ZLangCodeGeneratorTokenTypes::UNARY_MINUS:
    case ZLangCodeGeneratorTokenTypes::UNARY_PLUS:
    case ZLangCodeGeneratorTokenTypes::BNOT:
    case ZLangCodeGeneratorTokenTypes::LNOT:
    case ZLangCodeGeneratorTokenTypes::POST_INC:
    case ZLangCodeGeneratorTokenTypes::POST_DEC:
      stringResultSignature = GenerateUnaryExpressionInstruction(autoCurrentInstructionContainer,
                                                                 rvectorFindNames,
                                                                 rdequeExpressionAtoms);
      break;

    case ZLangCodeGeneratorTokenTypes::TYPECAST:
      stringResultSignature = GenerateTypeCastExpressionInstruction(autoCurrentInstructionContainer,
                                                                    rvectorFindNames,
                                                                    rdequeExpressionAtoms);
      break;

    case ZLangCodeGeneratorTokenTypes::SUBSCRIPT:
      stringResultSignature = GenerateSubscriptExpressionInstruction(autoCurrentInstructionContainer,
                                                                     rvectorFindNames,
                                                                     rdequeExpressionAtoms);
      break;

    case ZLangCodeGeneratorTokenTypes::CALLING:
      stringResultSignature = GenerateCallingSequenceExpressionInstruction(autoCurrentInstructionContainer,
                                                                           rvectorFindNames,
                                                                           rdequeExpressionAtoms);
      break;

    case ZLangCodeGeneratorTokenTypes::IDENTIFIER:
      stringResultSignature = GenerateLoadInstruction(autoCurrentInstructionContainer,
                                                      rvectorFindNames,
                                                      rdequeExpressionAtoms);
      break;

    case ZLangCodeGeneratorTokenTypes::NUM_INT:
    case ZLangCodeGeneratorTokenTypes::NUM_HEX_INT:
    case ZLangCodeGeneratorTokenTypes::NUM_QUAD:
    case ZLangCodeGeneratorTokenTypes::NUM_HEX_QUAD:
    case ZLangCodeGeneratorTokenTypes::NUM_FLOAT:
    case ZLangCodeGeneratorTokenTypes::LITERAL_true:
    case ZLangCodeGeneratorTokenTypes::LITERAL_false:
    case ZLangCodeGeneratorTokenTypes::CHAR_LITERAL:
      stringResultSignature = GenerateLoadConstantValueInstruction(autoCurrentInstructionContainer,
                                                                   rdequeExpressionAtoms);
      break;

    case ZLangCodeGeneratorTokenTypes::ROPE_LITERAL:
    case ZLangCodeGeneratorTokenTypes::STRING_LITERAL:
    case ZLangCodeGeneratorTokenTypes::IPv4ADDR_LITERAL:
    case ZLangCodeGeneratorTokenTypes::PPORT_LITERAL:
      stringResultSignature = GenerateLoadConstantAddressInstruction(autoCurrentInstructionContainer,
                                                                     rdequeExpressionAtoms);
      break;

    default:
      std::string stringError = "Unexpected expression atom's token type '" +
                                tAtom.stringTokenText + "'";
      throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      break;
  }

  return(stringResultSignature);
}


std::string CCodeGeneratorHelper::GenerateAssignExpressionInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::GenerateAssignExpressionInstruction()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif
  CInstructionContainer * pciInstructionContainer = autoCurrentInstructionContainer.get();
  CInstructionContainer_auto autoLeftOperandInstructionSequence = new __OPTION(_THROW) CInstructionSequence(pciInstructionContainer);
  CInstructionContainer_auto autoRightOperandInstructionSequence = new __OPTION(_THROW) CInstructionSequence(pciInstructionContainer);

  TExpressionAtom tOperator = __INSPECT_FRONT__(rdequeExpressionAtoms);
  __POP_FRONT__(rdequeExpressionAtoms);  // remove "="
  int nOperatorTokenType = tOperator.nTokenType;

  /*
   * 产生左操作数的byte codes
   */
  std::string stringLeftSignature;
  TExpressionAtom tLeftOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
  if (tLeftOperand.nTokenType == ZLangCodeGeneratorTokenTypes::IDENTIFIER)
  {
    /*
     * 注意：当ASSIGN的左Operand是IDENTIFIER时，下面要记得虽然此时左Operand的指令先
     * 于右Operand的指令而被产生，但是由于store到非table-element的指令是带一个指令
     * 操作数（variable的index）的，因此当append instruction到autoCurrentFunction
     * 时要先append右Operand的，然后才是左Operand的.
     */

    __POP_FRONT__(rdequeExpressionAtoms);  // remove "IDENTIFIER"
    int nLineNumberDebug = tLeftOperand.nLineNumber;
    int nColumnNumberDebug = tLeftOperand.nColumnNumber;
    std::string stringName = tLeftOperand.stringTokenText;

    CSymbol_auto autoSymbol = _FindVariableSymbol(nLineNumberDebug,
                                                  nColumnNumberDebug,
                                                  stringName,
                                                  rvectorFindNames);
    const CSymbolAttributes_auto & rautoSymbolAttributes = autoSymbol->GetAttributes();

    /*
     * 按照该IDENTIFIER是parameter、local、global，产生一条"(nested) store"指令，
     * 返回其signature.
     * 注意：左操作数可能（可以）为整个table.
     */
    switch (nOperatorTokenType)
    {
      case ZLangCodeGeneratorTokenTypes::ASSIGN:
        stringLeftSignature = _GenerateVariableInstructionBackend(autoLeftOperandInstructionSequence,
                                                                  nLineNumberDebug,
                                                                  stringName,
                                                                  rautoSymbolAttributes,
                                                                  VARIABLE_INSTRUCTION_TAG_STORE);
        break;

      case ZLangCodeGeneratorTokenTypes::RETURN_PSEUDO_ASSIGN:
        stringLeftSignature = _GenerateVariableInstructionBackend(autoLeftOperandInstructionSequence,
                                                                  nLineNumberDebug,
                                                                  stringName,
                                                                  rautoSymbolAttributes,
                                                                  VARIABLE_INSTRUCTION_TAG_RETURN_PSEUDO_STORE);
        break;

      case ZLangCodeGeneratorTokenTypes::NESTED_ASSIGN:
        stringLeftSignature = _GenerateVariableInstructionBackend(autoLeftOperandInstructionSequence,
                                                                  nLineNumberDebug,
                                                                  stringName,
                                                                  rautoSymbolAttributes,
                                                                  VARIABLE_INSTRUCTION_TAG_NESTED_STORE);
        break;

      case ZLangCodeGeneratorTokenTypes::REFERENCE_ADDRESS_ASSIGN:
        stringLeftSignature = _GenerateVariableInstructionBackend(autoLeftOperandInstructionSequence,
                                                                  nLineNumberDebug,
                                                                  stringName,
                                                                  rautoSymbolAttributes,
                                                                  VARIABLE_INSTRUCTION_TAG_REFERENCE_ADDRESS_ASSIGN);
        break;

      default:
        break;
    }
  }
  else
  {
    if (tLeftOperand.nTokenType == ZVM_OPERATOR_SUBSCRIPT)
    /* 如果左操作数是table元素操作 */
    {
      ///> 2001/4/26: Hack: 将ZVM_OPERATOR_SUBSCRIPT偷改为ZVM_OPERATOR_SUBSCRIPT_ADDRESS，
      /// 因为assign的左值需要的是地址.
      TExpressionAtom & rtLeftOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
      rtLeftOperand.nTokenType = ZVM_OPERATOR_SUBSCRIPT_ADDRESS;

      stringLeftSignature = GenerateSubscriptExpressionInstruction(autoLeftOperandInstructionSequence,
                                                                   rvectorFindNames,
                                                                   rdequeExpressionAtoms);  // Left operand will removed
    }
    else
    {
      /* ASSIGN的左操作数必须是IDENTIFIER或SUBSCRIPT */
      ThrowSemanticError_NonLeftValue(tOperator);
    }
  }

  /*
   * 产生右操作数的byte codes
   */
  std::string stringRightSignature;
  TExpressionAtom tRightOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);
  if (nOperatorTokenType == ZLangCodeGeneratorTokenTypes::REFERENCE_ADDRESS_ASSIGN)
  // 如果是referenc variable initializing
  {
    if (tRightOperand.nTokenType != ZLangCodeGeneratorTokenTypes::IDENTIFIER &&
        tRightOperand.nTokenType != ZLangCodeGeneratorTokenTypes::CALLING)
    // 如果右值不是一个variable或一个function calling，则这是不合法的referenc variable initializing
    {
      ThrowSemanticError_InvalidReferenceVariableInitializer(tRightOperand);
    }

    if (tRightOperand.nTokenType == ZLangCodeGeneratorTokenTypes::IDENTIFIER)
    {
      // 注意：产生"取地址"指令
      stringRightSignature = GenerateLoadAddressAsReferenceAddressOperandInstruction(
                                                            autoRightOperandInstructionSequence,
                                                            rvectorFindNames,
                                                            rdequeExpressionAtoms);
    }
    else
    {
      stringRightSignature = _GenerateExpressionInstructionBackend(autoRightOperandInstructionSequence,
                                                                   rvectorFindNames,
                                                                   rdequeExpressionAtoms);
    }

    if (stringLeftSignature != stringRightSignature)
    // referenc variable initializing必须类型完全匹配
    {
      ThrowSemanticError_InvalidOperandsToBinaryOperator(tOperator,
                                                         tLeftOperand,
                                                         tRightOperand,
                                                         stringLeftSignature,
                                                         stringRightSignature);
    }

    autoCurrentInstructionContainer->AppendInstruction(autoRightOperandInstructionSequence);
    autoCurrentInstructionContainer->AppendInstruction(autoLeftOperandInstructionSequence);
  }
  else
  {
    // 2001/5/10: Hack: 如果操作数是一个ASSIGN操作的结果，则需先偷偷将ASSIGN改为NESTED_ASSIGN
    if (tRightOperand.nTokenType == ZLangCodeGeneratorTokenTypes::ASSIGN)
    {
      TExpressionAtom & rtOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
      rtOperand.nTokenType = ZLangCodeGeneratorTokenTypes::NESTED_ASSIGN;
    }
    stringRightSignature = _GenerateExpressionInstructionBackend(autoRightOperandInstructionSequence,
                                                                 rvectorFindNames,
                                                                 rdequeExpressionAtoms);

    if (stringLeftSignature != stringRightSignature)
    // 如果左、右Operand的signature不相同
    {
      // 注意：下面这条if是重要的，它又能防止不兼容的table被错误地进行cast导致变成了相同类型的table
      if (! SignatureIsCompatible(stringRightSignature, stringLeftSignature, ZVM_OPERATOR_CAST))
      // 同时右Operand又不能被cast到左Operand
      {
        ThrowSemanticError_InvalidOperandsToBinaryOperator(tOperator,
                                                           tLeftOperand,
                                                           tRightOperand,
                                                           stringLeftSignature,
                                                           stringRightSignature);
      }
      // 产生右cast到左的指令
      _GenerateTypeCastInstructionBackend(autoRightOperandInstructionSequence,
                                          tOperator.nLineNumber,
                                          stringRightSignature,
                                          stringLeftSignature);
      // 修改right signature
      stringRightSignature = stringLeftSignature;
    }

    /*
     * 进行类型兼容性检查，这应该只是防止不兼容的table进行assign
     */
    if (! SignatureIsCompatible(stringLeftSignature, stringRightSignature, ZVM_OPERATOR_ASSIGN))
    {
      ThrowSemanticError_InvalidOperandsToBinaryOperator(tOperator,
                                                         tLeftOperand,
                                                         tRightOperand,
                                                         stringLeftSignature,
                                                         stringRightSignature);
    }

    if (tLeftOperand.nTokenType == ZLangCodeGeneratorTokenTypes::IDENTIFIER)
    // 如果是store到variable
    {
      autoCurrentInstructionContainer->AppendInstruction(autoRightOperandInstructionSequence);
      autoCurrentInstructionContainer->AppendInstruction(autoLeftOperandInstructionSequence);
    }
    else
    // 如果是store到table element
    {
      autoCurrentInstructionContainer->AppendInstruction(autoLeftOperandInstructionSequence);
      autoCurrentInstructionContainer->AppendInstruction(autoRightOperandInstructionSequence);

      /*
       * 现在为store to table element产生"storeToAddress"指令
       */
      int nLineNumberDebug = tOperator.nLineNumber;
      if (nOperatorTokenType == ZLangCodeGeneratorTokenTypes::ASSIGN)
      {
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_storeToAddress | stringLeftSignature[0]);
      }
      else
      {
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_nestedStoreToAddress | stringLeftSignature[0]);
      }
    }
  }

  return(stringLeftSignature);
}


std::string CCodeGeneratorHelper::GenerateBinaryExpressionInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::GenerateBinaryExpressionInstruction()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif
  CInstructionContainer * pciInstructionContainer = autoCurrentInstructionContainer.get();
  CInstructionContainer_auto autoLeftOperandInstructionSequence = new __OPTION(_THROW) CInstructionSequence(pciInstructionContainer);
  CInstructionContainer_auto autoRightOperandInstructionSequence = new __OPTION(_THROW) CInstructionSequence(pciInstructionContainer);

  TExpressionAtom tOperator = __INSPECT_FRONT__(rdequeExpressionAtoms);
  __POP_FRONT__(rdequeExpressionAtoms);  // remove operator
  int nOperatorTokenType = tOperator.nTokenType;
  int nLineNumberDebug = tOperator.nLineNumber;

  /*
   * 产生左操作数的byte codes
   */
  TExpressionAtom tLeftOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
  // 2001/5/10: Hack: 如果操作数是一个ASSIGN操作的结果，则需先偷偷将ASSIGN改为NESTED_ASSIGN
  if (tLeftOperand.nTokenType == ZLangCodeGeneratorTokenTypes::ASSIGN)
  {
    TExpressionAtom & rtOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
    rtOperand.nTokenType = ZLangCodeGeneratorTokenTypes::NESTED_ASSIGN;
  }
  std::string stringLeftSignature = _GenerateExpressionInstructionBackend(autoLeftOperandInstructionSequence,
                                                                          rvectorFindNames,
                                                                          rdequeExpressionAtoms);

  /*
   * 产生右操作数的byte codes
   */
  TExpressionAtom tRightOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
  // 2001/5/10: Hack: 如果操作数是一个ASSIGN操作的结果，则需先偷偷将ASSIGN改为NESTED_ASSIGN
  if (tRightOperand.nTokenType == ZLangCodeGeneratorTokenTypes::ASSIGN)
  {
    TExpressionAtom & rtOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
    rtOperand.nTokenType = ZLangCodeGeneratorTokenTypes::NESTED_ASSIGN;
  }
  std::string stringRightSignature = _GenerateExpressionInstructionBackend(autoRightOperandInstructionSequence,
                                                                           rvectorFindNames,
                                                                           rdequeExpressionAtoms);

  /*
   * 可能back-patch类型cast指令（如果patch了则相应的left或right signature将被修改），
   * 然后再进行类型兼容性检查
   */
  if (! BackPatchCastInstructionIfIncompatible(stringLeftSignature, autoLeftOperandInstructionSequence,
                                               stringRightSignature, autoRightOperandInstructionSequence,
                                               tOperator)
      //< 如果左、右类型自动cast不允许
      || ! SignatureIsCompatible(stringLeftSignature, stringRightSignature, nOperatorTokenType))
      //< 如果左、右类型不兼容这种操作符
  {
    ThrowSemanticError_InvalidOperandsToBinaryOperator(tOperator,
                                                       tLeftOperand,
                                                       tRightOperand,
                                                       stringLeftSignature,
                                                       stringRightSignature);
  }

  autoCurrentInstructionContainer->AppendInstruction(autoLeftOperandInstructionSequence);

  // 如果是Logic AND或Logic OR，则需在左操作数指令的后面Append一条"短路"指令.
  zvm::TZVMIndex nCircuitInstructionIndex;
  switch (nOperatorTokenType)
  {
    case ZVM_OPERATOR_LOR:
      nCircuitInstructionIndex = GenerateInstruction(autoCurrentInstructionContainer,
                                                     nLineNumberDebug,
                                                     zvm::ZVM_trueCircuitJump | stringLeftSignature[0],
                                                     static_cast<zvm::TZVMIndex>(0));
      break;

    case ZVM_OPERATOR_LAND:
      nCircuitInstructionIndex = GenerateInstruction(autoCurrentInstructionContainer,
                                                     nLineNumberDebug,
                                                     zvm::ZVM_falseCircuitJump | stringLeftSignature[0],
                                                     static_cast<zvm::TZVMIndex>(0));
      break;

    default:
      break;
  }

  autoCurrentInstructionContainer->AppendInstruction(autoRightOperandInstructionSequence);

  /*
   * 现在产生"lOr"等二元指令
   */
  std::string stringResultSignature = stringLeftSignature;
  switch (nOperatorTokenType)
  {
    case ZVM_OPERATOR_LOR:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_logicOr | stringLeftSignature[0]);
      /* LOR、LAND操作的结果类型应该为bool */
      stringResultSignature = zvm::CstringZVM_BOOL_SIGNATURE;
      break;

    case ZVM_OPERATOR_LAND:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_logicAnd | stringLeftSignature[0]);
      /* LOR、LAND操作的结果类型应该为bool */
      stringResultSignature = zvm::CstringZVM_BOOL_SIGNATURE;
      break;

    case ZVM_OPERATOR_BOR:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_bitOr | stringLeftSignature[0]);
      break;

    case ZVM_OPERATOR_BXOR:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_bitXor | stringLeftSignature[0]);
      break;

    case ZVM_OPERATOR_BAND:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_bitAnd | stringLeftSignature[0]);
      break;

    case ZVM_OPERATOR_NOT_EQUAL:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_notEqual | stringLeftSignature[0]);
      /* NOT_EQUAL操作的结果类型应该为bool */
      stringResultSignature = zvm::CstringZVM_BOOL_SIGNATURE;
      break;

    case ZVM_OPERATOR_EQUAL:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_equal | stringLeftSignature[0]);
      /* EQUAL操作的结果类型应该为bool */
      stringResultSignature = zvm::CstringZVM_BOOL_SIGNATURE;
      break;

    case ZVM_OPERATOR_LT:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_less | stringLeftSignature[0]);
      /* LT_操作的结果类型应该为bool */
      stringResultSignature = zvm::CstringZVM_BOOL_SIGNATURE;
      break;

    case ZVM_OPERATOR_GT:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_great | stringLeftSignature[0]);
      /* GT操作的结果类型应该为bool */
      stringResultSignature = zvm::CstringZVM_BOOL_SIGNATURE;
      break;

    case ZVM_OPERATOR_LE:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_lessEqual | stringLeftSignature[0]);
      /* LE操作的结果类型应该为bool */
      stringResultSignature = zvm::CstringZVM_BOOL_SIGNATURE;
      break;

    case ZVM_OPERATOR_GE:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_greatEqual | stringLeftSignature[0]);
      /* GE操作的结果类型应该为bool */
      stringResultSignature = zvm::CstringZVM_BOOL_SIGNATURE;
      break;

    case ZVM_OPERATOR_SL:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_shiftLeft | stringLeftSignature[0]);
      break;

    case ZVM_OPERATOR_SR:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_shiftRight | stringLeftSignature[0]);
      break;

    case ZVM_OPERATOR_PLUS:
      if (stringLeftSignature == zvm::CstringZVM_STRING_SIGNATURE)
      // 2001/7/17: stringPlus指令被重设计为需要指定一个临时变量作为指令参数
      {
        SWORD swTempVariableOffset =
              autoCurrentInstructionContainer->AllocateTempStringVariable(_bSwitchOfNeedFixTempLocalVariableOffset);
        zvm::TZVMIndex nIndex = GenerateInstruction(autoCurrentInstructionContainer,
                                                    nLineNumberDebug,
                                                    zvm::ZVM_plus | stringLeftSignature[0],
                                                    swTempVariableOffset);
        if (_bSwitchOfNeedFixTempLocalVariableOffset)
        // 如果是正在为Local variable initializing产生指令，则以后还需要fix offset
        {
          autoCurrentInstructionContainer->GetInstructionAt(nIndex).MarkNeedFixTempLocalVariableOffset();
        }
      }
      else
      {
        GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_plus | stringLeftSignature[0]);
      }
      break;

    case ZVM_OPERATOR_MINUS:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_minus | stringLeftSignature[0]);
      break;

    case ZVM_OPERATOR_STAR:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_multi | stringLeftSignature[0]);
      break;

    case ZVM_OPERATOR_DIV:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_div | stringLeftSignature[0]);
      break;

    case ZVM_OPERATOR_MOD:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_mod | stringLeftSignature[0]);
      break;

    default:
      std::string stringError = "Unexpected operator type '" + tOperator.stringTokenText + "'";
      throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      break;
  }

  // 如果是Logic AND或Logic OR，则需Patch在左操作数指令后面的那条"短路"指令的Label.
  if (nOperatorTokenType == ZVM_OPERATOR_LOR || nOperatorTokenType == ZVM_OPERATOR_LAND)
  {
    zvm::TZVMIndex nLabel = autoCurrentInstructionContainer->GetLabelBookmark();
    autoCurrentInstructionContainer->BackPatchLabel(nCircuitInstructionIndex, nLabel);
  }

  return(stringResultSignature);
}


std::string CCodeGeneratorHelper::GenerateUnaryExpressionInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::GenerateUnaryExpressionInstruction()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  TExpressionAtom tOperator = __INSPECT_FRONT__(rdequeExpressionAtoms);
  __POP_FRONT__(rdequeExpressionAtoms);  // remove operator
  int nOperatorTokenType = tOperator.nTokenType;

  /*
   * 产生左操作数的byte codes
   */
  std::string stringResultSignature;
  TExpressionAtom tOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
  if (nOperatorTokenType == ZVM_OPERATOR_INC || nOperatorTokenType == ZVM_OPERATOR_DEC ||
      nOperatorTokenType == ZVM_OPERATOR_POST_INC || nOperatorTokenType == ZVM_OPERATOR_POST_DEC)
  /* 如果是"++/--"操作符，操作数必须是变量 */
  {
    if (tOperand.nTokenType != ZLangCodeGeneratorTokenTypes::IDENTIFIER)
    {
      ThrowSemanticError_NonLeftValue(tOperator);
    }

    /* 如果是"++/--"操作符，必须产生取地址指令 */
    stringResultSignature = GenerateLoadAddressAsValueOperandInstruction(
                                                           autoCurrentInstructionContainer,
                                                           rvectorFindNames,
                                                           rdequeExpressionAtoms);
  }
  else
  {
    // 2001/5/10: Hack: 如果操作数是一个ASSIGN操作的结果，则需先偷偷将ASSIGN改为NESTED_ASSIGN
    if (tOperand.nTokenType == ZLangCodeGeneratorTokenTypes::ASSIGN)
    {
      TExpressionAtom & rtOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
      rtOperand.nTokenType = ZLangCodeGeneratorTokenTypes::NESTED_ASSIGN;
    }

    stringResultSignature = _GenerateExpressionInstructionBackend(autoCurrentInstructionContainer,
                                                                  rvectorFindNames,
                                                                  rdequeExpressionAtoms);
  }

  /*
   * 进行类型兼容性检查
   */
  if (! SignatureIsCompatible(stringResultSignature, zvm::CstringZVM_VOID_SIGNATURE, nOperatorTokenType))
  {
    ThrowSemanticError_InvalidOperandToUnaryOperator(tOperator, tOperand, stringResultSignature);
  }

  /*
   * 现在产生"inc"等一元指令
   */
  int nLineNumberDebug = tOperator.nLineNumber;
  switch (nOperatorTokenType)
  {
    case ZVM_OPERATOR_INC:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_prefixInc | stringResultSignature[0]);
      break;

    case ZVM_OPERATOR_DEC:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_prefixDec | stringResultSignature[0]);
      break;

    case ZVM_OPERATOR_UNARY_PLUS:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_unaryPlus | stringResultSignature[0]);
      break;

    case ZVM_OPERATOR_UNARY_MINUS:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_unaryMinus | stringResultSignature[0]);
      break;

    case ZVM_OPERATOR_BNOT:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_bitNot | stringResultSignature[0]);
      break;

    case ZVM_OPERATOR_LNOT:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_logicNot | stringResultSignature[0]);
      /* LNOT操作的结果类型应该为bool */
      stringResultSignature = zvm::CchZVM_BOOL_TYPE_TAG;
      break;

    case ZVM_OPERATOR_POST_INC:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_postfixInc | stringResultSignature[0]);
      break;

    case ZVM_OPERATOR_POST_DEC:
      GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_postfixDec | stringResultSignature[0]);
      break;

    default:
      std::string stringError = "Unexpected operator type '" + tOperator.stringTokenText + "'";
      throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      break;
  }

  return(stringResultSignature);
}


std::string CCodeGeneratorHelper::GenerateTypeCastExpressionInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::GenerateTypeCastExpressionInstruction()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  TExpressionAtom tOperator = __INSPECT_FRONT__(rdequeExpressionAtoms);
  __POP_FRONT__(rdequeExpressionAtoms);  // remove operator

  /*
   * 产生左操作数的byte codes
   */
  std::string stringLeftSignature;
  TExpressionAtom tLeftOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
  if (tLeftOperand.nTokenType == ZLangCodeGeneratorTokenTypes::CAST_LITERAL)
  {
    /* 得到(cast_to_type) */
    stringLeftSignature = tLeftOperand.stringTokenText;
  }
  else
  {
    std::string stringError = "Operator 'TYPECAST': Left operand must be a type name but '" +
                              tLeftOperand.stringTokenText + "' found at line " + tLeftOperand.nLineNumber +
                              " column " + tLeftOperand.nColumnNumber;
    throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
  }
  __POP_FRONT__(rdequeExpressionAtoms);  // Left operand removed

  /*
   * 产生右操作数的byte codes
   */
  TExpressionAtom tRightOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
  // 2001/5/10: Hack: 如果操作数是一个ASSIGN操作的结果，则需先偷偷将ASSIGN改为NESTED_ASSIGN
  if (tRightOperand.nTokenType == ZLangCodeGeneratorTokenTypes::ASSIGN)
  {
    TExpressionAtom & rtOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
    rtOperand.nTokenType = ZLangCodeGeneratorTokenTypes::NESTED_ASSIGN;
  }
  std::string stringRightSignature = _GenerateExpressionInstructionBackend(autoCurrentInstructionContainer,
                                                                           rvectorFindNames,
                                                                           rdequeExpressionAtoms);

  /*
   * 进行类型兼容性检查
   */
  /* 如果想通过SignatureIsCompatible()则只有被允许的cast类型才行 */
  if (! SignatureIsCompatible(stringRightSignature, stringLeftSignature, ZVM_OPERATOR_CAST))
  {
    ThrowSemanticError_InvalidCast(tOperator, tRightOperand, stringRightSignature, stringLeftSignature);
  }

  /* 现在产生cast指令 */
  int nLineNumberDebug = tLeftOperand.nLineNumber;  // 用“左”操作数的行号作为跟踪
  _GenerateTypeCastInstructionBackend(autoCurrentInstructionContainer,
                                      nLineNumberDebug,
                                      stringRightSignature,
                                      stringLeftSignature);

  return(stringLeftSignature);
}


void CCodeGeneratorHelper::_GenerateTypeCastInstructionBackend(
                                         CInstructionContainer_auto autoFunction,
                                         int nLineNumberDebug,
                                         const std::string & rstringFromSignature,
                                         const std::string & rstringToSignature)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::_GenerateTypeCastInstructionBackend()");
  switch (rstringFromSignature[0])
  {
    case zvm::CchZVM_BOOL_TYPE_TAG:
      switch (rstringToSignature[0])
      {
        case zvm::CchZVM_BYTE_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_boolToByte);
          break;

        case zvm::CchZVM_SDWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_boolToSDWORD);
          break;

        case zvm::CchZVM_UDWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_boolToUDWORD);
          break;

        case zvm::CchZVM_SQWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_boolToSQWORD);
          break;

        case zvm::CchZVM_UQWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_boolToUQWORD);
          break;

        default:
          #ifndef NDEBUG
          goto BAD_CAST_TO_SIGNATURE;
          #endif
          break;
      }
      break;

    case zvm::CchZVM_BYTE_TYPE_TAG:
      switch (rstringToSignature[0])
      {
        case zvm::CchZVM_BOOL_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_byteToBool);
          break;

        case zvm::CchZVM_SDWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_byteToSDWORD);
          break;

        case zvm::CchZVM_UDWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_byteToUDWORD);
          break;

        case zvm::CchZVM_SQWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_byteToSQWORD);
          break;

        case zvm::CchZVM_UQWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_byteToUQWORD);
          break;

        case zvm::CchZVM_DOUBLE_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_byteToDouble);
          break;

        default:
          #ifndef NDEBUG
          goto BAD_CAST_TO_SIGNATURE;
          #endif
          break;
      }
      break;

    case zvm::CchZVM_SDWORD_TYPE_TAG:
      switch (rstringToSignature[0])
      {
        case zvm::CchZVM_BOOL_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_sdwordToBool);
          break;

        case zvm::CchZVM_BYTE_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_sdwordToByte);
          break;

        case zvm::CchZVM_UDWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_sdwordToUDWORD);
          break;

        case zvm::CchZVM_SQWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_sdwordToSQWORD);
          break;

        case zvm::CchZVM_UQWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_sdwordToUQWORD);
          break;

        case zvm::CchZVM_DOUBLE_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_sdwordToDouble);
          break;

        default:
          #ifndef NDEBUG
          goto BAD_CAST_TO_SIGNATURE;
          #endif
          break;
      }
      break;

    case zvm::CchZVM_UDWORD_TYPE_TAG:
      switch (rstringToSignature[0])
      {
        case zvm::CchZVM_BOOL_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_udwordToBool);
          break;

        case zvm::CchZVM_BYTE_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_udwordToByte);
          break;

        case zvm::CchZVM_SDWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_udwordToSDWORD);
          break;

        case zvm::CchZVM_SQWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_udwordToSQWORD);
          break;

        case zvm::CchZVM_UQWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_udwordToUQWORD);
          break;

        case zvm::CchZVM_DOUBLE_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_udwordToDouble);
          break;

        default:
          #ifndef NDEBUG
          goto BAD_CAST_TO_SIGNATURE;
          #endif
          break;
      }
      break;

    case zvm::CchZVM_SQWORD_TYPE_TAG:
      switch (rstringToSignature[0])
      {
        case zvm::CchZVM_BOOL_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_sqwordToBool);
          break;

        case zvm::CchZVM_BYTE_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_sqwordToByte);
          break;

        case zvm::CchZVM_SDWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_sqwordToSDWORD);
          break;

        case zvm::CchZVM_UDWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_sqwordToUDWORD);
          break;

        case zvm::CchZVM_UQWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_sqwordToUQWORD);
          break;

        case zvm::CchZVM_DOUBLE_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_sqwordToDouble);
          break;

        default:
          #ifndef NDEBUG
          goto BAD_CAST_TO_SIGNATURE;
          #endif
          break;
      }
      break;

    case zvm::CchZVM_UQWORD_TYPE_TAG:
      switch (rstringToSignature[0])
      {
        case zvm::CchZVM_BOOL_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_uqwordToBool);
          break;

        case zvm::CchZVM_BYTE_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_uqwordToByte);
          break;

        case zvm::CchZVM_SDWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_uqwordToSDWORD);
          break;

        case zvm::CchZVM_UDWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_uqwordToUDWORD);
          break;

        case zvm::CchZVM_SQWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_uqwordToSQWORD);
          break;

        case zvm::CchZVM_DOUBLE_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_uqwordToDouble);
          break;

        default:
          #ifndef NDEBUG
          goto BAD_CAST_TO_SIGNATURE;
          #endif
          break;
      }
      break;

    case zvm::CchZVM_DOUBLE_TYPE_TAG:
      switch (rstringToSignature[0])
      {
        case zvm::CchZVM_BYTE_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_doubleToByte);
          break;

        case zvm::CchZVM_SDWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_doubleToSDWORD);
          break;

        case zvm::CchZVM_UDWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_doubleToUDWORD);
          break;

        case zvm::CchZVM_SQWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_doubleToSQWORD);
          break;

        case zvm::CchZVM_UQWORD_TYPE_TAG:
          GenerateInstruction(autoFunction, nLineNumberDebug, zvm::ZVM_doubleToUQWORD);
          break;

        default:
          #ifndef NDEBUG
          goto BAD_CAST_TO_SIGNATURE;
          #endif
          break;
      }
      break;

    default:
      #ifndef NDEBUG
      std::string stringError = "Unexpected cast-from type signature '" + rstringFromSignature + "'";
      throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      #endif
      break;
  }

  return;

#ifndef NDEBUG
BAD_CAST_TO_SIGNATURE:
  std::string stringError = "Unexpected cast-to type signature '" + rstringToSignature + "'";
  throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
#endif
}


std::string CCodeGeneratorHelper::GenerateSubscriptExpressionInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::GenerateSubscriptExpressionInstruction()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  TExpressionAtom tOperator = __INSPECT_FRONT__(rdequeExpressionAtoms);
  __POP_FRONT__(rdequeExpressionAtoms);  // remove "SUBSCRIPT"或"SUBSCRIPT_ADDRESS"

  /*
   * 产生左操作数的byte codes
   */
  std::string stringLeftSignature;
  TExpressionAtom tLeftOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
  if (tLeftOperand.nTokenType == ZLangCodeGeneratorTokenTypes::IDENTIFIER)
  {
    /*
     * 猜测该IDENTIFIER是parameter、local、global或field，产生一条"load?Address"指令，
     * 返回其signature.
     */
    stringLeftSignature = GenerateLoadAddressAsValueOperandInstruction(
                                                         autoCurrentInstructionContainer,
                                                         rvectorFindNames,
                                                         rdequeExpressionAtoms);

    if (stringLeftSignature[0] != zvm::CchZVM_TABLE_TYPE_TAG)
    {
      /* SUBSCRIPT的左操作数必须是table型变量 */
      ThrowSemanticError_InvalidLeftOperandToTableSubscript(tLeftOperand);
    }
  }
  else
  {
    /* SUBSCRIPT的左操作数必须是IDENTIFIER */
    ThrowSemanticError_NonLeftValue(tOperator);
  }

  /*
   * 产生右操作数的byte codes
   */
  std::string stringRightSignature;
  TExpressionAtom tRightOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
  /* 2001/5/9改为：key的类型只要get-key expression的结果不再是个table即可 */
  // 2001/5/10: Hack: 如果操作数是一个ASSIGN操作的结果，则需先偷偷将ASSIGN改为NESTED_ASSIGN
  if (tRightOperand.nTokenType == ZLangCodeGeneratorTokenTypes::ASSIGN)
  {
    TExpressionAtom & rtOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
    rtOperand.nTokenType = ZLangCodeGeneratorTokenTypes::NESTED_ASSIGN;
  }
  stringRightSignature = _GenerateExpressionInstructionBackend(autoCurrentInstructionContainer,
                                                               rvectorFindNames,
                                                               rdequeExpressionAtoms);

  // 检查key是否再是个table
  if (stringRightSignature[0] == zvm::CchZVM_TABLE_TYPE_TAG)
  /* 因为我们允许table的下标类型可以是动态的，只要右signature不是"[."（又是个table） */
  {
    ThrowSemanticError_InvalidRightOperandToTableSubscript(tRightOperand, "table");
  }

  // 2001/5/17: 加入判断右signature是否为void返回的function结果
  if (stringRightSignature == zvm::CstringZVM_VOID_SIGNATURE)
  /* 因为我们允许table的下标类型可以是动态的，只要右signature不是返回void的function */
  {
    ThrowSemanticError_InvalidRightOperandToTableSubscript(tRightOperand, "void return value");
  }

  /*
   * 进行类型兼容性检查
   * 2001/5/9: 好象已经没必要了，上面已经检查过了
   */
  /* 因为我们允许table的下标类型可以是动态的，只要右signature不是"[."（又是个table），则兼容. */
  if (! SignatureIsCompatible(stringLeftSignature, stringRightSignature, ZLangCodeGeneratorTokenTypes::SUBSCRIPT))
  {
    ThrowSemanticError_InvalidOperandsToBinaryOperator(tOperator,
                                                       tLeftOperand,
                                                       tRightOperand,
                                                       stringLeftSignature,
                                                       stringRightSignature);
  }

  // 取出"[X"中'['后的字符串
  std::string stringResultSignature = stringLeftSignature.substr(1, stringLeftSignature.size()-1);

  if (zfc::StringCaseInsensitiveCompare(stringResultSignature, zvm::CstringZVM_STRING_SIGNATURE) == 0 ||
      zfc::StringCaseInsensitiveCompare(stringResultSignature, zvm::CstringZVM_IPv4ADDR_SIGNATURE) == 0 ||
      zfc::StringCaseInsensitiveCompare(stringResultSignature, zvm::CstringZVM_PPORT_SIGNATURE) == 0)
  {
    // 2001/6/2: Hack: 因为无论是作为左或右Operand，Object型都是采用地址形式作为
    // operand被push到stack上的.
    tOperator.nTokenType = ZVM_OPERATOR_SUBSCRIPT_ADDRESS;
  }

  /* 2001/4/26: 改为增加了两种"SUBSCRIPT"指令 */
  int nLineNumberDebug = tOperator.nLineNumber;
  char chKeyTypeTag = stringRightSignature[0];
  if (tOperator.nTokenType == ZVM_OPERATOR_SUBSCRIPT)
  {
    switch (stringResultSignature[0])
    {
      case zvm::CchZVM_BOOL_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadBoolTableElementValue | chKeyTypeTag);
        break;

      case zvm::CchZVM_BYTE_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadByteTableElementValue | chKeyTypeTag);
        break;

      case zvm::CchZVM_SDWORD_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadSDWORDTableElementValue | chKeyTypeTag);
        break;

      case zvm::CchZVM_UDWORD_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadUDWORDTableElementValue | chKeyTypeTag);
        break;

      case zvm::CchZVM_SQWORD_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadSQWORDTableElementValue | chKeyTypeTag);
        break;

      case zvm::CchZVM_UQWORD_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadUQWORDTableElementValue | chKeyTypeTag);
        break;

      case zvm::CchZVM_DOUBLE_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadDoubleTableElementValue | chKeyTypeTag);
        break;

      case zvm::CchZVM_STRING_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadStringTableElementValue | chKeyTypeTag);
        break;

      case zvm::CchZVM_IPv4ADDR_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadIPv4AddressTableElementValue | chKeyTypeTag);
        break;

      case zvm::CchZVM_PPORT_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadPPortTableElementValue | chKeyTypeTag);
        break;

      default:
        std::string stringError = "Unexpected table type signature '" + stringResultSignature + "'";
        throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
        break;
    }
  }
  else
  // ZVM_OPERATOR_SUBSCRIPT_ADDRESS
  {
    switch (stringResultSignature[0])
    {
      case zvm::CchZVM_BOOL_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadBoolTableElementAddress | chKeyTypeTag);
        break;

      case zvm::CchZVM_BYTE_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadByteTableElementAddress | chKeyTypeTag);
        break;

      case zvm::CchZVM_SDWORD_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadSDWORDTableElementAddress | chKeyTypeTag);
        break;

      case zvm::CchZVM_UDWORD_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadUDWORDTableElementAddress | chKeyTypeTag);
        break;

      case zvm::CchZVM_SQWORD_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadSQWORDTableElementAddress | chKeyTypeTag);
        break;

      case zvm::CchZVM_UQWORD_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadUQWORDTableElementAddress | chKeyTypeTag);
        break;

      case zvm::CchZVM_DOUBLE_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadDoubleTableElementAddress | chKeyTypeTag);
        break;

      case zvm::CchZVM_STRING_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadStringTableElementAddress | chKeyTypeTag);
        break;

      case zvm::CchZVM_IPv4ADDR_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadIPv4AddressTableElementAddress | chKeyTypeTag);
        break;

      case zvm::CchZVM_PPORT_TYPE_TAG:
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadPPortTableElementAddress | chKeyTypeTag);
        break;

      default:
        std::string stringError = "Unexpected table type signature '" + stringResultSignature + "'";
        throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
        break;
    }
  }

  return(stringResultSignature);
}


/**
 * 产生calling before和after sequence的指令.
 */
std::string CCodeGeneratorHelper::GenerateCallingSequenceExpressionInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::GenerateCallingSequenceExpressionInstruction()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  TExpressionAtom tOperator = __INSPECT_FRONT__(rdequeExpressionAtoms);
  __POP_FRONT__(rdequeExpressionAtoms);  // remove "CALLING"

  /*
   * 左操作数
   */
  TExpressionAtom tLeftOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
  __POP_FRONT__(rdequeExpressionAtoms);  // remove
  if (tLeftOperand.nTokenType != ZLangCodeGeneratorTokenTypes::IDENTIFIER)
  {
    /* CALLING的左操作数必须是IDENTIFIER，代表function/method名 */
    ThrowSemanticError_InvalidFunctionName(tLeftOperand);
  }

  int nLineNumberDebug = tLeftOperand.nLineNumber;
  int nColumnNumberDebug = tLeftOperand.nColumnNumber;
  std::string stringFunctionName = tLeftOperand.stringTokenText;

  /*
   * 可能需要产生一个隐含的argument.
   */
                         //> may throw antlr::SemanticException
  CSymbol_auto autoSymbol = _FindFunctionSymbol(nLineNumberDebug,
                                                nColumnNumberDebug,
                                                stringFunctionName);
  const CSymbolAttributes_auto & rautoSymbolAttributes = autoSymbol->GetAttributes();
  const CSymbolAttributes * pciSymbolAttributes = rautoSymbolAttributes.get();
  const CFunctionSymbolAttributes * pciFunctionSymbolAttributes =
           dynamic_cast<const CFunctionSymbolAttributes *>(pciSymbolAttributes);
  std::string stringResultArgumentSignature = pciFunctionSymbolAttributes->GetReturnSignature();
  std::vector<std::string> vectorFunctionSignature;
  zvm::FunctionSignatureToken(vectorFunctionSignature, pciFunctionSymbolAttributes->GetFunctionSignature());
  std::vector<std::string> vectorRequiredArgumentsSignature;
  zvm::ArgumentsSignatureToken(vectorRequiredArgumentsSignature, vectorFunctionSignature[0]);
  size_t nRequiredArgumentsCount = vectorRequiredArgumentsSignature.size();
  SWORD swTempObjectVariableOffset = 0;

  if (stringResultArgumentSignature != zvm::CstringZVM_VOID_SIGNATURE)
  // 如果function有返回类型
  {
    if (zfc::StringIsLowerCase(stringResultArgumentSignature))
    // 如果这个function是返回reference address的
    {
      // 产生"constructReference"指令
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_constructReference | static_cast<UCHAR>(toupper(stringResultArgumentSignature[0])));
    }
    else
    {
      if (stringResultArgumentSignature[0] != zvm::CchZVM_TABLE_TYPE_TAG)
      {
        zvm::TZVMIndex nIndex;

        /*
         * 2001/7/17: 加入为string、ipv4address、pport型产生Quick Construct指令.
         *
         * 因为它们是Object型，因此以前在Function Invoking结束后需要有一条
         * "convertValueToAddress"的指令来将这个临时Object转换为ZVM要求的
         * "Object型操作数在ZVM stack上的表现形式是pointer of pointer"，但是
         * 以前采用的方法是在CZVMVirtualThread中有一个相应类型的Object Register，
         * 然后将这个临时Object的Object pointer存贮到那个Object Register中，再
         * 对那个Object Register进行Get pointer of pointer，得到一个我们需要的
         * pointer of pointer型操作数到ZVM stack上，可是这种方法存在一个严重的
         * Bug，因为Register始终只有一个，那么假如有如下的expression:
         *     string func();
         *
         *     ......
         *     {
         *       string s = func() + func();
         *       ......
         *     }
         *
         * 则在expression中第一次调用func()后，Register被使用了，那么接着的第二
         * 次调用func()呢，怎么办呀？可是Register也不能无限制增加，即使可以无限
         * 制增加，那么如果func()还有其它expression也需要用到Register，那么又怎
         * 么办，在每次进入新的function之前先保存所有的Register固然是可以（也是
         * 必须的），但是如果Register的数目很多，那么这又是个负担了!
         *
         *     因此我设计一种新的方法，即在Local variables后产生一些需要的数目的
         * Object型临时变量，然后这样function的返回就直接返回到那些Object型临时
         * 变量中，然后再load address of temp variable即可，即新方法产生的指令
         * 系列可能类似：
         *     quickConstructStringObject 3  # 3是被用的string临时变量的bp offset
         *     ......正常地传递参数......
         *     call ?
         *     ......正常地pop出参数......
         *     popAny  # pop出quick指令在ZVM stack上的结果
         *     loadStringStackVariableAddress 3  # 取那个string临时变量的pointer of pointer
         *
         * 注：以前产生的指令系列为：
         *     constructString
         *     ......正常地传递参数......
         *     call ?
         *     ......正常地pop出参数......
         *     convertValueToAddress
         */
        switch (stringResultArgumentSignature[0])
        {
          case zvm::CchZVM_STRING_TYPE_TAG:
            swTempObjectVariableOffset =
                  autoCurrentInstructionContainer->AllocateTempStringVariable(_bSwitchOfNeedFixTempLocalVariableOffset);
            nIndex = GenerateInstruction(autoCurrentInstructionContainer,
                                         nLineNumberDebug,
                                         zvm::ZVM_quickConstructStringObject,
                                         swTempObjectVariableOffset);
            if (_bSwitchOfNeedFixTempLocalVariableOffset)
            // 如果是正在为Local variable initializing产生指令，则以后还需要fix offset
            {
              autoCurrentInstructionContainer->GetInstructionAt(nIndex).MarkNeedFixTempLocalVariableOffset();
            }
            break;

          case zvm::CchZVM_IPv4ADDR_TYPE_TAG:
            swTempObjectVariableOffset =
                  autoCurrentInstructionContainer->AllocateTempIPv4AddressVariable(_bSwitchOfNeedFixTempLocalVariableOffset);
            nIndex = GenerateInstruction(autoCurrentInstructionContainer,
                                         nLineNumberDebug,
                                         zvm::ZVM_quickConstructIPv4AddressObject,
                                         swTempObjectVariableOffset);
            if (_bSwitchOfNeedFixTempLocalVariableOffset)
            // 如果是正在为Local variable initializing产生指令，则以后还需要fix offset
            {
              autoCurrentInstructionContainer->GetInstructionAt(nIndex).MarkNeedFixTempLocalVariableOffset();
            }
            break;

          case zvm::CchZVM_PPORT_TYPE_TAG:
            swTempObjectVariableOffset =
                  autoCurrentInstructionContainer->AllocateTempPPortVariable(_bSwitchOfNeedFixTempLocalVariableOffset);
            nIndex = GenerateInstruction(autoCurrentInstructionContainer,
                                         nLineNumberDebug,
                                         zvm::ZVM_quickConstructPPortObject,
                                         swTempObjectVariableOffset);
            if (_bSwitchOfNeedFixTempLocalVariableOffset)
            // 如果是正在为Local variable initializing产生指令，则以后还需要fix offset
            {
              autoCurrentInstructionContainer->GetInstructionAt(nIndex).MarkNeedFixTempLocalVariableOffset();
            }
            break;

          default:
            // 产生"construct"指令
            GenerateInstruction(autoCurrentInstructionContainer,
                                nLineNumberDebug,
                                zvm::ZVM_construct | stringResultArgumentSignature[0]);
            break;
        }
      }
      else
      {
        /* 2001/7/17: 改为产生Quick Construct指令. */
        swTempObjectVariableOffset =
              autoCurrentInstructionContainer->AllocateTempTableVariable(stringResultArgumentSignature[1],
                                                                         _bSwitchOfNeedFixTempLocalVariableOffset);
        zvm::TZVMIndex nIndex = GenerateInstruction(autoCurrentInstructionContainer,
                                                    nLineNumberDebug,
                                                    zvm::ZVM_quickConstructTableObject,
                                                    swTempObjectVariableOffset);
        if (_bSwitchOfNeedFixTempLocalVariableOffset)
        // 如果是正在为Local variable initializing产生指令，则以后还需要fix offset
        {
          autoCurrentInstructionContainer->GetInstructionAt(nIndex).MarkNeedFixTempLocalVariableOffset();
        }

        /*
        // 产生"constructTable"指令
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_constructTable | stringResultArgumentSignature[1]);
        */
      }
    }
  }

  /*
   * 产生右操作数的byte codes，函数调用参数的压入顺序是从第一个参数开始，这与C正好相反.
   */
  bool bIncompatible = false;
  int nArgumentCount = 0;
  std::string stringArgumentSignature;
  //std::string stringRightSignature = "(";
  // 2001/5/9: 改为不要加"()"了，以免引起zvm::ArgumentsSignatureToken()出错
  std::string stringRightSignature;
  TExpressionAtom tRightOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);
  while (tRightOperand.nTokenType != ZLangCodeGeneratorTokenTypes::ARGUMENTS_END)
  {
    if (tRightOperand.nTokenType != ZLangCodeGeneratorTokenTypes::PASS_A_ARGUMENT)
    {
      if (nArgumentCount < nRequiredArgumentsCount &&
          zfc::StringIsLowerCase(vectorRequiredArgumentsSignature[nArgumentCount]))
      // 如果这个function要求的这个argument的signature是小写的，则是要传递reference argument
      {
        switch (tRightOperand.nTokenType)
        {
          case ZLangCodeGeneratorTokenTypes::IDENTIFIER:
            {
              // Hack: 将"IDENTIFIER"偷偷改为"IDENTIFIER_ADDRESS"
              //TExpressionAtom & rtOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
              //rtOperand.nTokenType = ZLangCodeGeneratorTokenTypes::IDENTIFIER_ADDRESS;
              //tRightOperand.nTokenType = ZLangCodeGeneratorTokenTypes::IDENTIFIER_ADDRESS;

              stringArgumentSignature = GenerateLoadAddressAsValueOperandInstruction(
                                                                       autoCurrentInstructionContainer,
                                                                       rvectorFindNames,
                                                                       rdequeExpressionAtoms);
              // 对返回的signature进行Hack，将其改为小写的.
              zfc::LowerString(stringArgumentSignature);
            }
            break;

          // table的元素应该也是可以被作为reference argument的
          case ZLangCodeGeneratorTokenTypes::SUBSCRIPT:
            {
              // Hack: 将"SUBSCRIPT"偷偷改为"SUBSCRIPT_ADDRESS"，以便强制对
              //       sdword等简单类型也产生取地址指令
              TExpressionAtom & rtOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
              rtOperand.nTokenType = ZLangCodeGeneratorTokenTypes::SUBSCRIPT_ADDRESS;
              tRightOperand.nTokenType = ZLangCodeGeneratorTokenTypes::SUBSCRIPT_ADDRESS;

              stringArgumentSignature = GenerateSubscriptExpressionInstruction(autoCurrentInstructionContainer,
                                                                               rvectorFindNames,
                                                                               rdequeExpressionAtoms);
              // 对产生"SUBSCRIPT_ADDRESS"操作指令返回的signature进行Hack，将其改为小写的.
              zfc::LowerString(stringArgumentSignature);
            }
            break;

          default:
            ThrowSemanticError_CanNotPassExpressionAsReferenceArgument(tRightOperand,
                                                                       vectorRequiredArgumentsSignature[nArgumentCount]);
            break;
        }

        if (stringArgumentSignature != vectorRequiredArgumentsSignature[nArgumentCount])
        // 引用参数必须完全匹配
        {
          bIncompatible = true;
        }
      }
      else
      // 如果是要传递value argument
      {
        // 注：对于object型variable（包括object型table element）或constant，以
        // 后可能可以优化为直接产生load value指令，而不需要象以前那样先产生load
        // address，然后再一条indirectLoadValueFromAddress指令!
        // 注：对于返回object型的function call，也可能可以优化为不再需要产生一条
        // convertValueToAddress和然后一条indirectLoadValueFromAddress指令!
        // 注：优化的方法可以是这样的：先知道是什么类型的token，然后直接调用它的
        // Generate?()方法去产生未优化的指令，然后再通过"回滚覆盖"的技巧，产生新
        // 优化指令来覆盖末尾的那几条需要优化的指令!

        // 2001/5/10: Hack: 如果操作数是一个ASSIGN操作的结果，则需先偷偷将ASSIGN改为NESTED_ASSIGN
        if (tRightOperand.nTokenType == ZLangCodeGeneratorTokenTypes::ASSIGN)
        {
          TExpressionAtom & rtOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);  // Not removed
          rtOperand.nTokenType = ZLangCodeGeneratorTokenTypes::NESTED_ASSIGN;
          tRightOperand.nTokenType = ZLangCodeGeneratorTokenTypes::NESTED_ASSIGN;
        }

        stringArgumentSignature = _GenerateExpressionInstructionBackend(autoCurrentInstructionContainer,
                                                                        rvectorFindNames,
                                                                        rdequeExpressionAtoms);

        // 如果是Object型，则需要将address转换(deep copy instance)为一个value
        char chArgumentTypeTag = stringArgumentSignature[0];
        if (chArgumentTypeTag == zvm::CchZVM_STRING_TYPE_TAG ||
            chArgumentTypeTag == zvm::CchZVM_IPv4ADDR_TYPE_TAG ||
            chArgumentTypeTag == zvm::CchZVM_PPORT_TYPE_TAG ||
            chArgumentTypeTag == zvm::CchZVM_TABLE_TYPE_TAG)
        {
          GenerateInstruction(autoCurrentInstructionContainer,
                              nLineNumberDebug,
                              zvm::ZVM_indirectLoadValueFromAddress | chArgumentTypeTag);

        }

        if (stringArgumentSignature != vectorRequiredArgumentsSignature[nArgumentCount])
        // 如果参数类型不完全匹配，则试着是否能自动cast
        {
          if (SignatureIsCompatible(stringArgumentSignature,
                                    vectorRequiredArgumentsSignature[nArgumentCount],
                                    ZVM_OPERATOR_CAST))
          {
            _GenerateTypeCastInstructionBackend(autoCurrentInstructionContainer,
                                                nLineNumberDebug,
                                                stringArgumentSignature,
                                                vectorRequiredArgumentsSignature[nArgumentCount]);
            stringArgumentSignature = vectorRequiredArgumentsSignature[nArgumentCount];
          }
          else
          {
            bIncompatible = true;
          }
        }
      }

      stringRightSignature += stringArgumentSignature;
    }
    else
    {
      __POP_FRONT__(rdequeExpressionAtoms);  // Remove 'PASS_A_ARGUMENT'
      ++nArgumentCount;
    }

    tRightOperand = __INSPECT_FRONT__(rdequeExpressionAtoms);
  }
  //stringRightSignature += ")";
  __POP_FRONT__(rdequeExpressionAtoms);  // remove 'ARGUMENTS_END'

  /* 产生"savePC"指令 */
  /*
   * 2001/5/7: 改为不再需要显式的savePC指令，而由call指令隐含进行，
   * 否则在ZVM解释时会发生重复执行指令的问题，这改动也是合理的!
   */
  /* GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_savePC); */

  /*
   * 猜测是哪个作用域的function或method，然后产生"call"指令.
   */
  std::string stringFunctionSignature = GenerateCallInstruction(autoCurrentInstructionContainer,
                                                                nLineNumberDebug,
                                                                nColumnNumberDebug,
                                                                rvectorFindNames,
                                                                stringFunctionName);

  /*
   * 进行类型兼容性检查
   */
  /* 2001/6/3: 取消了这句代码，因为上面已经检查过了
                          // "(...)."     与          "(...)"进行兼容性检查
                // 2001/5/9: "(...)."     与          "..."进行兼容性检查
  if (! SignatureIsCompatible(stringFunctionSignature, stringRightSignature, ZLangCodeGeneratorTokenTypes::CALLING))
  {
    ThrowSemanticError_PassIncompatibleArguments(tOperator,
                                                 stringFunctionName,
                                                 stringFunctionSignature,
                                                 stringRightSignature);
  }
  */

  if (bIncompatible)
  {
    ThrowSemanticError_PassIncompatibleArguments(tOperator,
                                                 stringFunctionName,
                                                 stringFunctionSignature,
                                                 stringRightSignature);
  }

  /* 产生"pop"指令，弹出除隐含argument外的所有arguments */
  for (int i = nArgumentCount-1; i >= 0; --i)
  {
    if (zfc::StringIsLowerCase(vectorRequiredArgumentsSignature[i]))
    // 如果是reference argument，则采用不需要析构的pop指令
    {
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_popAny);
    }
    else
    {
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_pop | toupper(vectorRequiredArgumentsSignature[i][0]));
    }
  }

  if (zfc::StringIsUpperCase(stringResultArgumentSignature))
  // 如果这个function不是返回reference address的
  {
    /* 2001/7/17: 由于采用了新的quick指令，所以改为产生load stack variable address指令. */
    if (stringResultArgumentSignature == zvm::CstringZVM_STRING_SIGNATURE ||
        stringResultArgumentSignature == zvm::CstringZVM_IPv4ADDR_SIGNATURE ||
        stringResultArgumentSignature == zvm::CstringZVM_PPORT_SIGNATURE ||
        stringResultArgumentSignature[0] == zvm::CchZVM_TABLE_TYPE_TAG)
    {
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_popAny);
      zvm::TZVMIndex nIndex = GenerateInstruction(autoCurrentInstructionContainer,
                                                  nLineNumberDebug,
                                                  zvm::ZVM_loadStackVariableAddress | stringResultArgumentSignature[0],
                                                  swTempObjectVariableOffset);
      if (_bSwitchOfNeedFixTempLocalVariableOffset)
      // 如果是正在为Local variable initializing产生指令，则以后还需要fix offset
      {
        autoCurrentInstructionContainer->GetInstructionAt(nIndex).MarkNeedFixTempLocalVariableOffset();
      }
    }

    /*
    // 将object型的result argument（object型operand是用address形式表示的）转换为temp address
    if (stringResultArgumentSignature == zvm::CstringZVM_STRING_SIGNATURE ||
        stringResultArgumentSignature == zvm::CstringZVM_IPv4ADDR_SIGNATURE ||
        stringResultArgumentSignature == zvm::CstringZVM_PPORT_SIGNATURE ||
        stringResultArgumentSignature[0] == zvm::CchZVM_TABLE_TYPE_TAG)
    {
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_convertValueToAddress | stringResultArgumentSignature[0]);
    }
    */
  }

  /* 这个result argument(value/address)将交给用户的ASSIGN语句去处理了 */

  return(stringResultArgumentSignature);
}


CSymbol_auto CCodeGeneratorHelper::_FindFunctionSymbol(int nLineNumberDebug,
                                                       int nColumnNumberDebug,
                                                       const std::string & rstringFunctionName)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::_FindFunctionSymbol()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  std::vector<std::string> vectorFindNames;

  /* 在Global Name-Space下查找 */
  vectorFindNames.clear();
  vectorFindNames.push_back(rstringFunctionName);

  try {
    CSymbol_auto & rautoSymbol = _pciSymbolTable->FindSymbol(vectorFindNames);
    const CSymbolAttributes_auto & rautoSymbolAttributes = rautoSymbol->GetAttributes();

    CSymbol::TSymbolTag eTag = rautoSymbolAttributes->GetSymbolTag();
    if (eTag != CSymbol::TAG_GLOBAL_FUNCTION)
    {
      ThrowSemanticError_SymbolIsNotFunction(nLineNumberDebug, nColumnNumberDebug, eTag, rstringFunctionName);
    }
    return(rautoSymbol);
  }
  catch (ESymbolNotFound & e)
  {
    /* 如果查找失败则只能throw exception */
    ThrowSemanticError_UndeclaredSymbol(nLineNumberDebug, nColumnNumberDebug, rstringFunctionName);
  }
}


std::string CCodeGeneratorHelper::GenerateCallInstruction(
                                      CInstructionContainer_auto autoCurrentInstructionContainer,
                                      int nLineNumberDebug,
                                      int nColumnNumberDebug,
                                      const std::vector<std::string> & rvectorFindNames,
                                      const std::string & rstringFunctionName)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::GenerateCallInstruction()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif
                          /* may throw antlr::SemanticException */
  CSymbol_auto autoSymbol = _FindFunctionSymbol(nLineNumberDebug,
                                                nColumnNumberDebug,
                                                rstringFunctionName);
  const CSymbolAttributes_auto & rautoSymbolAttributes = autoSymbol->GetAttributes();
  const CSymbolAttributes * pciSymbolAttributes = rautoSymbolAttributes.get();

  CSymbol::TSymbolTag eTag = pciSymbolAttributes->GetSymbolTag();
  // Must be global function
  LogAssert0(eTag == CSymbol::TAG_GLOBAL_FUNCTION, "Shit");

  const CGlobalFunctionSymbolAttributes * pciFunctionAttributes =
      dynamic_cast<const CGlobalFunctionSymbolAttributes *>(pciSymbolAttributes);
  std::string stringFunctionSignature = pciFunctionAttributes->GetFunctionSignature();
  zvm::TAccessModifierTag eAccessTag = pciFunctionAttributes->GetAccessModifierTag();
  /* 插入global function的name-and-signature-reference */
  zvm::TZVMIndex nFunctionIndex = _ciConstantPool.InsertGlobalFunctionReference(
                                                         rstringFunctionName,
                                                         stringFunctionSignature,
                                                         eAccessTag);

  GenerateInstruction(autoCurrentInstructionContainer, nLineNumberDebug, zvm::ZVM_call, nFunctionIndex);

  return stringFunctionSignature;
}


CSymbol_auto CCodeGeneratorHelper::_FindVariableSymbol(
                              int nLineNumberDebug,
                              int nColumnNumberDebug,
                              const std::string & rstringName,
                              const std::vector<std::string> & rvectorNameSpace)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::_FindVariableSymbol()");

  std::vector<std::string> vectorFindNames(rvectorNameSpace);

  /* 先在当前的Name-Space下查找 */
  vectorFindNames.push_back(rstringName);
  try {
    CSymbol_auto & rautoSymbol = _pciSymbolTable->FindSymbol(vectorFindNames);
    const CSymbolAttributes_auto & rautoSymbolAttributes = rautoSymbol->GetAttributes();

    CSymbol::TSymbolTag eTag = rautoSymbol->GetSymbolTag();
    if (eTag != CSymbol::TAG_GLOBAL_VARIABLE &&
        eTag != CSymbol::TAG_LOCAL_VARIABLE &&
        eTag != CSymbol::TAG_PARAMETER)
    {
      ThrowSemanticError_SymbolIsNotVariable(nLineNumberDebug, nColumnNumberDebug, eTag, rstringName);
    }

    return rautoSymbol;
  }
  catch (ESymbolNotFound & e)
  {
    /* 最后在Global Name-Space下查找 */
    vectorFindNames.clear();
    vectorFindNames.push_back(rstringName);
    try {
      CSymbol_auto & rautoSymbol = _pciSymbolTable->FindSymbol(vectorFindNames);
      const CSymbolAttributes_auto & rautoSymbolAttributes = rautoSymbol->GetAttributes();

      CSymbol::TSymbolTag eTag = rautoSymbol->GetSymbolTag();
      if (eTag != CSymbol::TAG_GLOBAL_VARIABLE &&
          eTag != CSymbol::TAG_LOCAL_VARIABLE &&
          eTag != CSymbol::TAG_PARAMETER)
      {
        ThrowSemanticError_SymbolIsNotVariable(nLineNumberDebug, nColumnNumberDebug, eTag, rstringName);
      }

      return rautoSymbol;
    }
    catch (ESymbolNotFound & e)
    {
      /* 如果还查找失败则只能throw exception */
      ThrowSemanticError_UndeclaredSymbol(nLineNumberDebug, nColumnNumberDebug, rstringName);
    }
  }
}


std::string CCodeGeneratorHelper::_GenerateVariableInstructionBackend(
                           CInstructionContainer_auto autoCurrentInstructionContainer,
                           int nLineNumberDebug,
                           const std::string & rstringName,
                           const CSymbolAttributes_auto & rautoSymbolAttributes,
                           TVariableInstructionTag eInstructionTag)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::_GenerateVariableInstructionBackend()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  std::string stringResultSignature;
  const CSymbolAttributes * pciSymbolAttributes = rautoSymbolAttributes.get();
  CSymbol::TSymbolTag eTag = pciSymbolAttributes->GetSymbolTag();
  switch (eTag)
  {
    case CSymbol::TAG_GLOBAL_VARIABLE:
      {
        const CGlobalVariableSymbolAttributes * pciGlobalVariableAttributes =
            dynamic_cast<const CGlobalVariableSymbolAttributes *>(pciSymbolAttributes);
        stringResultSignature = pciGlobalVariableAttributes->GetVariableSignature();
        zvm::TAccessModifierTag eAccessTag = pciGlobalVariableAttributes->GetAccessModifierTag();
        zvm::TZVMIndex nReferenceIndex = _ciConstantPool.InsertGlobalVariableReference(rstringName,
                                                                                       stringResultSignature,
                                                                                       eAccessTag);
        switch (eInstructionTag)
        {
          case VARIABLE_INSTRUCTION_TAG_LOAD_VALUE:
            GenerateInstruction(autoCurrentInstructionContainer,
                                nLineNumberDebug,
                                zvm::ZVM_loadGlobalVariableValue | stringResultSignature[0],
                                nReferenceIndex);
            break;

          case VARIABLE_INSTRUCTION_TAG_LOAD_ADDRESS_AS_VALUE_OPERAND:
            GenerateInstruction(autoCurrentInstructionContainer,
                                nLineNumberDebug,
                                zvm::ZVM_loadGlobalVariableAddress | stringResultSignature[0],
                                nReferenceIndex);
            break;

          case VARIABLE_INSTRUCTION_TAG_STORE:
            GenerateInstruction(autoCurrentInstructionContainer,
                                nLineNumberDebug,
                                zvm::ZVM_storeToGlobalVariable | stringResultSignature[0],
                                nReferenceIndex);
            break;

          case VARIABLE_INSTRUCTION_TAG_NESTED_STORE:
            GenerateInstruction(autoCurrentInstructionContainer,
                                nLineNumberDebug,
                                zvm::ZVM_nestedStoreToGlobalVariable | stringResultSignature[0],
                                nReferenceIndex);
            break;

          case VARIABLE_INSTRUCTION_TAG_LOAD_ADDRESS_AS_REFERENCE_ADDRESS_OPERAND:
            GenerateInstruction(autoCurrentInstructionContainer,
                                nLineNumberDebug,
                                zvm::ZVM_loadGlobalVariableAddress | stringResultSignature[0],
                                nReferenceIndex);
            // 将signature偷偷改回为小写，因为是一个reference address operand
            zfc::LowerString(stringResultSignature);
            break;

          default:
            LogAssert1(ShouldNotRunToHere(), "Unexpected instruction tag '%d'", eInstructionTag);
            break;
        }
      }
      break;

    case CSymbol::TAG_LOCAL_VARIABLE:
    case CSymbol::TAG_PARAMETER:
      {
        const CStackVariableSymbolAttributes * pciStackVariableAttributes =
            dynamic_cast<const CStackVariableSymbolAttributes *>(pciSymbolAttributes);
        stringResultSignature = pciStackVariableAttributes->GetVariableSignature();
        SWORD nBPOffset = pciStackVariableAttributes->GetBPOffset();

        if (zfc::StringIsLowerCase(stringResultSignature))
        // 如果是reference variable，则采用indirect指令
        {
          // 偷偷将signature修改为大写，以便进行兼容性检查、和让指令码低字节正确
          zfc::UpperString(stringResultSignature);
          switch (eInstructionTag)
          {
            case VARIABLE_INSTRUCTION_TAG_LOAD_VALUE:
              GenerateInstruction(autoCurrentInstructionContainer,
                                  nLineNumberDebug,
                                  zvm::ZVM_indirectLoadStackVariableValue | stringResultSignature[0],
                                  nBPOffset);
              break;

            case VARIABLE_INSTRUCTION_TAG_LOAD_ADDRESS_AS_VALUE_OPERAND:
              GenerateInstruction(autoCurrentInstructionContainer,
                                  nLineNumberDebug,
                                  zvm::ZVM_loadReferenceStackVariableReferenceToAddress,
                                  nBPOffset);
              break;

            case VARIABLE_INSTRUCTION_TAG_STORE:
              GenerateInstruction(autoCurrentInstructionContainer,
                                  nLineNumberDebug,
                                  zvm::ZVM_indirectStoreToStackVariable | stringResultSignature[0],
                                  nBPOffset);
              break;

            case VARIABLE_INSTRUCTION_TAG_NESTED_STORE:
              GenerateInstruction(autoCurrentInstructionContainer,
                                  nLineNumberDebug,
                                  zvm::ZVM_indirectNestedStoreToStackVariable | stringResultSignature[0],
                                  nBPOffset);
              break;

            case VARIABLE_INSTRUCTION_TAG_REFERENCE_ADDRESS_ASSIGN:
              GenerateInstruction(autoCurrentInstructionContainer,
                                  nLineNumberDebug,
                                  zvm::ZVM_assignReferenceAddress | stringResultSignature[0],
                                  nBPOffset);
              // 再将signature改回为小写，因为reference address assign的结果是
              // 一个address operand，否则类型兼容检查会通不过.
              zfc::LowerString(stringResultSignature);
              break;

            case VARIABLE_INSTRUCTION_TAG_LOAD_ADDRESS_AS_REFERENCE_ADDRESS_OPERAND:
              GenerateInstruction(autoCurrentInstructionContainer,
                                  nLineNumberDebug,
                                  zvm::ZVM_loadReferenceStackVariableReferenceToAddress,
                                  nBPOffset);
              // 再将signature改回为小写，因为是一个reference address operand
              zfc::LowerString(stringResultSignature);
              break;

            case VARIABLE_INSTRUCTION_TAG_RETURN_PSEUDO_STORE:
              // 其实下面产生的这个indirect指令是错误的，因为我还不支持在ZLang
              // script中能返回reference address!
              GenerateInstruction(autoCurrentInstructionContainer,
                                  nLineNumberDebug,
                                  zvm::ZVM_indirectStoreToStackVariable | stringResultSignature[0],
                                  nBPOffset);
              // 再将signature改回为小写，以免兼容检查错误地被通过，即例如如下的情况：
              //    string & func()
              //    {
              //      string s;
              //      return s;
              //    }
              // 被错误地通过.
              zfc::LowerString(stringResultSignature);
              break;

            default:
              LogAssert1(ShouldNotRunToHere(), "Unexpected instruction tag '%d'", eInstructionTag);
              break;
          }
        }
        else
        {
          switch (eInstructionTag)
          {
            case VARIABLE_INSTRUCTION_TAG_LOAD_VALUE:
              GenerateInstruction(autoCurrentInstructionContainer,
                                  nLineNumberDebug,
                                  zvm::ZVM_loadStackVariableValue | stringResultSignature[0],
                                  nBPOffset);
              break;

            case VARIABLE_INSTRUCTION_TAG_LOAD_ADDRESS_AS_VALUE_OPERAND:
              GenerateInstruction(autoCurrentInstructionContainer,
                                  nLineNumberDebug,
                                  zvm::ZVM_loadStackVariableAddress | stringResultSignature[0],
                                  nBPOffset);
              break;

            case VARIABLE_INSTRUCTION_TAG_STORE:
            case VARIABLE_INSTRUCTION_TAG_RETURN_PSEUDO_STORE:
              GenerateInstruction(autoCurrentInstructionContainer,
                                  nLineNumberDebug,
                                  zvm::ZVM_storeToStackVariable | stringResultSignature[0],
                                  nBPOffset);
              break;

            case VARIABLE_INSTRUCTION_TAG_NESTED_STORE:
              GenerateInstruction(autoCurrentInstructionContainer,
                                  nLineNumberDebug,
                                  zvm::ZVM_nestedStoreToStackVariable | stringResultSignature[0],
                                  nBPOffset);
              break;

            case VARIABLE_INSTRUCTION_TAG_LOAD_ADDRESS_AS_REFERENCE_ADDRESS_OPERAND:
              GenerateInstruction(autoCurrentInstructionContainer,
                                  nLineNumberDebug,
                                  zvm::ZVM_loadStackVariableAddress | stringResultSignature[0],
                                  nBPOffset);
              // 将signature偷偷改回为小写，因为是一个reference address operand
              zfc::LowerString(stringResultSignature);
              break;

            default:
              LogAssert1(ShouldNotRunToHere(), "Unexpected instruction tag '%d'", eInstructionTag);
              break;
          }
        }
      }
      break;

    default:
      LogAssert1(ShouldNotRunToHere(), "Unexpected symbol tag '%d'", eTag);
      break;
  }

  return(stringResultSignature);
}



std::string CCodeGeneratorHelper::GenerateLoadInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::GenerateLoadInstruction()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  TExpressionAtom tAtom = __INSPECT_FRONT__(rdequeExpressionAtoms);
  __POP_FRONT__(rdequeExpressionAtoms);  // removed 'IDENTIFIER'
  int nLineNumberDebug = tAtom.nLineNumber;
  int nColumnNumberDebug = tAtom.nColumnNumber;
  std::string stringName = tAtom.stringTokenText;
  std::string stringResultSignature;

                         // May throw antlr::SemanticException
  CSymbol_auto autoSymbol = _FindVariableSymbol(nLineNumberDebug,
                                                nColumnNumberDebug,
                                                stringName,
                                                rvectorFindNames);
  const CSymbolAttributes_auto & rautoSymbolAttributes = autoSymbol->GetAttributes();
  const CSymbolAttributes * pciSymbolAttributes = rautoSymbolAttributes.get();
  const CVariableSymbolAttributes * pciVariableSymbolAttributes =
        dynamic_cast<const CVariableSymbolAttributes *>(pciSymbolAttributes);
  std::string stringVariableSignature = pciVariableSymbolAttributes->GetVariableSignature();

  if (zfc::StringCaseInsensitiveCompare(stringVariableSignature, zvm::CstringZVM_STRING_SIGNATURE) == 0 ||
      zfc::StringCaseInsensitiveCompare(stringVariableSignature, zvm::CstringZVM_IPv4ADDR_SIGNATURE) == 0 ||
      zfc::StringCaseInsensitiveCompare(stringVariableSignature, zvm::CstringZVM_PPORT_SIGNATURE) == 0 ||
      stringVariableSignature[0] == zvm::CchZVM_TABLE_TYPE_TAG)
  // 如果是string等object型variable，则产生load address指令.
  {
    stringResultSignature = _GenerateLoadAddressAsValueOperandInstructionBackend(
                                                                   autoCurrentInstructionContainer,
                                                                   nLineNumberDebug,
                                                                   stringName,
                                                                   rautoSymbolAttributes);
  }
  else
  // 如果是简单型variable，则产生load value指令.
  {
    stringResultSignature = _GenerateLoadValueInstructionBackend(autoCurrentInstructionContainer,
                                                                 nLineNumberDebug,
                                                                 stringName,
                                                                 rautoSymbolAttributes);
  }

  return(stringResultSignature);
}


std::string CCodeGeneratorHelper::GenerateLoadValueInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::GenerateLoadValueInstruction()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  TExpressionAtom tAtom = __INSPECT_FRONT__(rdequeExpressionAtoms);
  __POP_FRONT__(rdequeExpressionAtoms);  // removed 'IDENTIFIER'
  int nLineNumberDebug = tAtom.nLineNumber;
  int nColumnNumberDebug = tAtom.nColumnNumber;
  std::string stringName = tAtom.stringTokenText;
  std::string stringResultSignature;

                         // May throw antlr::SemanticException
  CSymbol_auto autoSymbol = _FindVariableSymbol(nLineNumberDebug,
                                                nColumnNumberDebug,
                                                stringName,
                                                rvectorFindNames);
  const CSymbolAttributes_auto & rautoSymbolAttributes = autoSymbol->GetAttributes();

  stringResultSignature = _GenerateLoadValueInstructionBackend(autoCurrentInstructionContainer,
                                                               nLineNumberDebug,
                                                               stringName,
                                                               rautoSymbolAttributes);

  return(stringResultSignature);
}


std::string CCodeGeneratorHelper::_GenerateLoadValueInstructionBackend(
                           CInstructionContainer_auto autoCurrentInstructionContainer,
                           int nLineNumberDebug,
                           const std::string & rstringName,
                           const CSymbolAttributes_auto & rautoSymbolAttributes)
{
  return _GenerateVariableInstructionBackend(autoCurrentInstructionContainer,
                                             nLineNumberDebug,
                                             rstringName,
                                             rautoSymbolAttributes,
                                             VARIABLE_INSTRUCTION_TAG_LOAD_VALUE);
}



std::string CCodeGeneratorHelper::GenerateLoadAddressAsValueOperandInstruction(

                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::GenerateLoadAddressAsValueOperandInstruction()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  TExpressionAtom tAtom = __INSPECT_FRONT__(rdequeExpressionAtoms);
  __POP_FRONT__(rdequeExpressionAtoms);  // removed 'IDENTIFIER'
  int nLineNumberDebug = tAtom.nLineNumber;
  int nColumnNumberDebug = tAtom.nColumnNumber;
  std::string stringName = tAtom.stringTokenText;
  std::string stringResultSignature;

                         // May throw antlr::SemanticException
  CSymbol_auto autoSymbol = _FindVariableSymbol(nLineNumberDebug,
                                                nColumnNumberDebug,
                                                stringName,
                                                rvectorFindNames);
  const CSymbolAttributes_auto & rautoSymbolAttributes = autoSymbol->GetAttributes();

  stringResultSignature = _GenerateLoadAddressAsValueOperandInstructionBackend(
                                                                 autoCurrentInstructionContainer,
                                                                 nLineNumberDebug,
                                                                 stringName,
                                                                 rautoSymbolAttributes);

  return(stringResultSignature);
}


std::string CCodeGeneratorHelper::_GenerateLoadAddressAsValueOperandInstructionBackend(
                           CInstructionContainer_auto autoCurrentInstructionContainer,
                           int nLineNumberDebug,
                           const std::string & rstringName,
                           const CSymbolAttributes_auto & rautoSymbolAttributes)
{
  return _GenerateVariableInstructionBackend(autoCurrentInstructionContainer,
                                             nLineNumberDebug,
                                             rstringName,
                                             rautoSymbolAttributes,
                                             VARIABLE_INSTRUCTION_TAG_LOAD_ADDRESS_AS_VALUE_OPERAND);
}



std::string CCodeGeneratorHelper::GenerateLoadAddressAsReferenceAddressOperandInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::GenerateLoadAddressAsReferenceAddressOperandInstruction()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  TExpressionAtom tAtom = __INSPECT_FRONT__(rdequeExpressionAtoms);
  __POP_FRONT__(rdequeExpressionAtoms);  // removed 'IDENTIFIER'
  int nLineNumberDebug = tAtom.nLineNumber;
  int nColumnNumberDebug = tAtom.nColumnNumber;
  std::string stringName = tAtom.stringTokenText;
  std::string stringResultSignature;

                         // May throw antlr::SemanticException
  CSymbol_auto autoSymbol = _FindVariableSymbol(nLineNumberDebug,
                                                nColumnNumberDebug,
                                                stringName,
                                                rvectorFindNames);
  const CSymbolAttributes_auto & rautoSymbolAttributes = autoSymbol->GetAttributes();

  stringResultSignature = _GenerateLoadAddressAsReferenceAddressOperandInstructionBackend(
                                                                 autoCurrentInstructionContainer,
                                                                 nLineNumberDebug,
                                                                 stringName,
                                                                 rautoSymbolAttributes);

  return(stringResultSignature);
}


std::string CCodeGeneratorHelper::_GenerateLoadAddressAsReferenceAddressOperandInstructionBackend(
                           CInstructionContainer_auto autoCurrentInstructionContainer,
                           int nLineNumberDebug,
                           const std::string & rstringName,
                           const CSymbolAttributes_auto & rautoSymbolAttributes)
{
  return _GenerateVariableInstructionBackend(autoCurrentInstructionContainer,
                                             nLineNumberDebug,
                                             rstringName,
                                             rautoSymbolAttributes,
                                             VARIABLE_INSTRUCTION_TAG_LOAD_ADDRESS_AS_REFERENCE_ADDRESS_OPERAND);
}



std::string CCodeGeneratorHelper::GenerateLoadConstantValueInstruction(
                                 CInstructionContainer_auto autoCurrentInstructionContainer,
                                 std::deque<TExpressionAtom> & rdequeExpressionAtoms)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::GenerateLoadConstantValueInstruction()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  TExpressionAtom tAtom = __INSPECT_FRONT__(rdequeExpressionAtoms);
  __POP_FRONT__(rdequeExpressionAtoms);  // removed 'NUM_INT' and etc
  int nLineNumberDebug = tAtom.nLineNumber;
  int nColumnNumberDebug = tAtom.nColumnNumber;
  std::string stringConstantText = tAtom.stringTokenText;
  int nConstantType = tAtom.nTokenType;
  zvm::TZVMIndex nReferenceIndex;
  std::string stringResultSignature;

  switch (nConstantType)
  {
    case ZLangCodeGeneratorTokenTypes::NUM_INT:
      {
        SQWORD sqw = strtoll(stringConstantText.c_str(), (char **)0, 10);
        if (stringConstantText.size() > 0 && stringConstantText[0] == '-')
        // 如果是负数
        {
          SDWORD sdw = static_cast<SDWORD>(sqw);
          stringResultSignature = zvm::CstringZVM_SDWORD_SIGNATURE;
          GenerateInstruction(autoCurrentInstructionContainer,
                              nLineNumberDebug,
                              zvm::ZVM_loadSDWORDConstantValue,
                              sdw);
        }
        else
        {
          if (sqw > INT_MAX)
          {
            UDWORD udw = static_cast<UDWORD>(sqw);
            stringResultSignature = zvm::CstringZVM_UDWORD_SIGNATURE;
            GenerateInstruction(autoCurrentInstructionContainer,
                                nLineNumberDebug,
                                zvm::ZVM_loadUDWORDConstantValue,
                                udw);
          }
          else
          // 当整型Literal小于INT_MAX时，总是将它当作为一个SDWORD型，好象是在
          // 一般程序中 // SDWORD用得比较多的.
          {
            SDWORD sdw = static_cast<SDWORD>(sqw);
            stringResultSignature = zvm::CstringZVM_SDWORD_SIGNATURE;
            GenerateInstruction(autoCurrentInstructionContainer,
                                nLineNumberDebug,
                                zvm::ZVM_loadSDWORDConstantValue,
                                sdw);
          }
        }
      }
      break;

    case ZLangCodeGeneratorTokenTypes::NUM_HEX_INT:
      {
        UDWORD udw = strtoul(stringConstantText.c_str(), (char **)0, 16);
        stringResultSignature = zvm::CstringZVM_UDWORD_SIGNATURE;
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadUDWORDConstantValue,
                            udw);
      }
      break;

    case ZLangCodeGeneratorTokenTypes::NUM_HEX_QUAD:
      {
        nReferenceIndex = _ciConstantPool.InsertUQWORDLiteral(stringConstantText, 16);
        stringResultSignature = zvm::CstringZVM_UQWORD_SIGNATURE;
        GenerateInstruction(autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_loadUQWORDConstantValue,
                            nReferenceIndex);
      }
      break;

    case ZLangCodeGeneratorTokenTypes::NUM_QUAD:
      {
        if (stringConstantText.size() > 0 && stringConstantText[0] == '-')
        // 如果是负数
        {
          nReferenceIndex = _ciConstantPool.InsertSQWORDLiteral(stringConstantText, 10);
          stringResultSignature = zvm::CstringZVM_SQWORD_SIGNATURE;
          GenerateInstruction(autoCurrentInstructionContainer,
                              nLineNumberDebug,
                              zvm::ZVM_loadSQWORDConstantValue,
                              nReferenceIndex);
        }
        else
        {
          UQWORD uqw = strtoull(stringConstantText.c_str(), (char **)0, 10);
          if (uqw > QUAD_MAX)
          {
            nReferenceIndex = _ciConstantPool.InsertUQWORDLiteral(stringConstantText, 10);
            stringResultSignature = zvm::CstringZVM_UQWORD_SIGNATURE;
            GenerateInstruction(autoCurrentInstructionContainer,
                                nLineNumberDebug,
                                zvm::ZVM_loadUQWORDConstantValue,
                                nReferenceIndex);
          }
          else
          // 当整型Literal小于QUAD_MAX时，总是将它当作为一个SQWORD型，好象是在
          // 一般程序中SQWORD用得比较多的.
          {
            nReferenceIndex = _ciConstantPool.InsertSQWORDLiteral(stringConstantText, 10);
            stringResultSignature = zvm::CstringZVM_SQWORD_SIGNATURE;
            GenerateInstruction(autoCurrentInstructionContainer,
                                nLineNumberDebug,
                                zvm::ZVM_loadSQWORDConstantValue,
                                nReferenceIndex);
          }
        }
      }
      break;

    case ZLangCodeGeneratorTokenTypes::NUM_FLOAT:
      nReferenceIndex = _ciConstantPool.InsertDoubleLiteral(stringConstantText);
      stringResultSignature = zvm::CstringZVM_DOUBLE_SIGNATURE;
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_loadDoubleConstantValue,
                          nReferenceIndex);
      break;

    case ZLangCodeGeneratorTokenTypes::CHAR_LITERAL:
      stringResultSignature = zvm::CstringZVM_BYTE_SIGNATURE;
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_loadByteConstantValue,
                          static_cast<UCHAR>(stringConstantText[0]));
      break;

    /*
    case ZLangCodeGeneratorTokenTypes::STRING_LITERAL:
      nReferenceIndex = _ciConstantPool.InsertBinaryStringLiteral(stringConstantText);
      stringResultSignature = zvm::CstringZVM_STRING_SIGNATURE;
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_loadStringConstantValue,
                          nReferenceIndex);
      break;

    case ZLangCodeGeneratorTokenTypes::IPv4ADDR_LITERAL:
      try {
        nReferenceIndex = _ciConstantPool.InsertIPv4AddressLiteral(stringConstantText);
      }
      catch (zfc::EOutOfRange & e)
      {
        // Mapping to 'antlr::SemanticException'
        ThrowSemanticError_InvalidCIDRMask(nLineNumberDebug, nColumnNumberDebug, e);
      }
      stringResultSignature = zvm::CstringZVM_IPv4ADDR_SIGNATURE;
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_loadIPv4AddressConstantValue,
                          nReferenceIndex);
      break;

    case ZLangCodeGeneratorTokenTypes::PPORT_LITERAL:
      nReferenceIndex = _ciConstantPool.InsertPPortLiteral(stringConstantText);
      stringResultSignature = zvm::CstringZVM_PPORT_SIGNATURE;
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_loadPPortConstantValue,
                          nReferenceIndex);
      break;
    */

    case ZLangCodeGeneratorTokenTypes::LITERAL_true:
      stringResultSignature = zvm::CstringZVM_BOOL_SIGNATURE;
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_loadBoolConstantValue,
                          static_cast<UCHAR>(1));
      break;

    case ZLangCodeGeneratorTokenTypes::LITERAL_false:
      stringResultSignature = zvm::CstringZVM_BOOL_SIGNATURE;
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_loadBoolConstantValue,
                          static_cast<UCHAR>(0));
      break;

    default:
      std::string stringError = "Unexpected constant type '" + stringConstantText + "'";
      throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      break;
  }

  return(stringResultSignature);
}


std::string CCodeGeneratorHelper::GenerateLoadConstantAddressInstruction(
                                 CInstructionContainer_auto autoCurrentInstructionContainer,
                                 std::deque<TExpressionAtom> & rdequeExpressionAtoms)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::GenerateLoadConstantAddressInstruction()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  TExpressionAtom tAtom = __INSPECT_FRONT__(rdequeExpressionAtoms);
  __POP_FRONT__(rdequeExpressionAtoms);  // removed 'NUM_INT' and etc
  int nLineNumberDebug = tAtom.nLineNumber;
  int nColumnNumberDebug = tAtom.nColumnNumber;
  std::string stringConstantText = tAtom.stringTokenText;
  int nConstantType = tAtom.nTokenType;
  zvm::TZVMIndex nReferenceIndex;
  std::string stringResultSignature;

  switch (nConstantType)
  {
    case ZLangCodeGeneratorTokenTypes::STRING_LITERAL:
      nReferenceIndex = _ciConstantPool.InsertBinaryStringLiteral(stringConstantText);
      stringResultSignature = zvm::CstringZVM_STRING_SIGNATURE;
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_loadStringConstantAddress,
                          nReferenceIndex);
      break;

    case ZLangCodeGeneratorTokenTypes::ROPE_LITERAL:
      nReferenceIndex = _ciConstantPool.InsertRopeStringLiteral(stringConstantText);
      stringResultSignature = zvm::CstringZVM_ROPE_SIGNATURE;
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_loadRopeConstantAddress,
                          nReferenceIndex);
      break;

    case ZLangCodeGeneratorTokenTypes::IPv4ADDR_LITERAL:
      try {
        nReferenceIndex = _ciConstantPool.InsertIPv4AddressLiteral(stringConstantText);
      }
      catch (zfc::EOutOfRange & e)
      {
        // Mapping to 'antlr::SemanticException'
        ThrowSemanticError_InvalidCIDRMask(nLineNumberDebug, nColumnNumberDebug, e);
      }
      stringResultSignature = zvm::CstringZVM_IPv4ADDR_SIGNATURE;
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_loadIPv4AddressConstantAddress,
                          nReferenceIndex);
      break;

    case ZLangCodeGeneratorTokenTypes::PPORT_LITERAL:
      nReferenceIndex = _ciConstantPool.InsertPPortLiteral(stringConstantText);
      stringResultSignature = zvm::CstringZVM_PPORT_SIGNATURE;
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_loadPPortConstantAddress,
                          nReferenceIndex);
      break;

    default:
      std::string stringError = "Unexpected constant type '" + stringConstantText + "'";
      throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      break;
  }

  return(stringResultSignature);
}


void CCodeGeneratorHelper::AppendStackVariableDebugInfo(
                                      CInstructionContainer_auto autoCurrentInstructionContainer,
                                      const std::vector<std::string> & rvectorFindNames,
                                      const std::string & rstringName,
                                      const std::string & rstringSignature)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::AppendStackVariableDebugInfo()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  /* 插入name-and-signature-reference */
  zvm::TZVMIndex nNameAndSignatureIndex = _ciConstantPool.InsertNameAndSignatureReference(
                                                                     rstringName,
                                                                     rstringSignature);

  std::string stringUnifyName = CSymbolTable::ToUnifyName(rvectorFindNames);
  try {
    CSymbol_auto & rautoSymbol = _pciSymbolTable->FindSymbol(rvectorFindNames);

    /* 该Symbol一定是PARAMETER或LOCAL_VARIABLE */
    LogAssert1(rautoSymbol->GetSymbolTag() == CSymbol::TAG_PARAMETER ||
               rautoSymbol->GetSymbolTag() == CSymbol::TAG_LOCAL_VARIABLE,
               "Symbol table have unexcepted errors for symbol '%s'",
               stringUnifyName.c_str());

    const CSymbolAttributes_auto & rautoSymbolAttributes = rautoSymbol->GetAttributes();
    const CSymbolAttributes * pciSymbolAttributes = rautoSymbolAttributes.get();
    const CStackVariableSymbolAttributes * pciSVAttributes =
      dynamic_cast<const CStackVariableSymbolAttributes *>(pciSymbolAttributes);
    SWORD nBPOffset = pciSVAttributes->GetBPOffset();

    /* 添加一个stack variable debug info */
    //autoCurrentInstructionContainer->AppendStackVariableDebugInfo(nNameAndSignatureIndex, nBPOffset);
    CZLangFunction * pciZLangFunction = dynamic_cast<CZLangFunction *>(autoCurrentInstructionContainer.get());
    LogAssert0(pciZLangFunction, "Bug: Impossible 'dynamic_cast<CZLangFunction *>' failure");
    pciZLangFunction->AppendStackVariableDebugInfo(nNameAndSignatureIndex, nBPOffset);
  }
  catch (ESymbolNotFound & e) {
    /* 该Symbol是不应该查找失败的 */
    LogError(("Bug: Symbol table has unexcepted errors for lookup symbol '%s'\n",
              stringUnifyName.c_str()));
    throw;
  }
}


void CCodeGeneratorHelper::GenerateConstructLocalVariableInstruction(
                                      CInstructionContainer_auto autoCurrentInstructionContainer,
                                      int nLineNumberDebug,
                                      const std::vector<std::string> & rvectorFindNames,
                                      const std::string & rstringName,
                                      const std::string & rstringSignature,
                                      int nTheVariableIndex)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::GenerateConstructLocalVariableInstruction()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  AppendStackVariableDebugInfo(autoCurrentInstructionContainer,
                               rvectorFindNames,
                               rstringName,
                               rstringSignature);

  if (zfc::StringIsLowerCase(rstringSignature))
  // If the variable is a reference variable
  {
    // 注意：每个ZLang function byte codes的第一条指令总是"saveBP"
    InsertInstructionBefore(nTheVariableIndex,
                            autoCurrentInstructionContainer,
                            nLineNumberDebug,
                            zvm::ZVM_constructReference | static_cast<UCHAR>(toupper(rstringSignature[0])));
    /*
    GenerateInstruction(autoCurrentInstructionContainer,
                        nLineNumberDebug,
                        zvm::ZVM_constructReference | static_cast<UCHAR>(toupper(rstringSignature[0])));
    */
  }
  else
  {
    if (rstringSignature[0] != zvm::CchZVM_TABLE_TYPE_TAG)
    {
      InsertInstructionBefore(nTheVariableIndex,
                              autoCurrentInstructionContainer,
                              nLineNumberDebug,
                              zvm::ZVM_construct | rstringSignature[0]);
      /*
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_construct | rstringSignature[0]);
      */
    }
    else
    // If the variable is a table variable
    {
      InsertInstructionBefore(nTheVariableIndex,
                              autoCurrentInstructionContainer,
                              nLineNumberDebug,
                              zvm::ZVM_constructTable | rstringSignature[1]);
      /*
      GenerateInstruction(autoCurrentInstructionContainer,
                          nLineNumberDebug,
                          zvm::ZVM_constructTable | rstringSignature[1]);
      */
    }
  }
}


bool CCodeGeneratorHelper::BackPatchCastInstructionIfIncompatible(
                                  std::string & rstringLeftSignature,
                                  CInstructionContainer_auto & rautoLeftOperandFunction,
                                  std::string & rstringRightSignature,
                                  CInstructionContainer_auto & rautoRightOperandFunction,
                                  const TExpressionAtom & rtOperator)
{
  bool bResult = true;
  switch (rtOperator.nTokenType)
  {
    case ZVM_OPERATOR_SL:
    case ZVM_OPERATOR_SR:
      if (zfc::StringCaseInsensitiveCompare(rstringRightSignature, zvm::CstringZVM_UDWORD_SIGNATURE))
      // 如果">>"或"<<"的右Operand不是UDWORD型
      {
        if (SignatureIsCompatible(rstringRightSignature, zvm::CstringZVM_UDWORD_SIGNATURE, ZVM_OPERATOR_CAST))
        // 但是右Operand却可以被cast为UDWORD型
        {
          // Back patch一条cast指令
          _GenerateTypeCastInstructionBackend(rautoRightOperandFunction,
                                              rtOperator.nLineNumber,
                                              rstringRightSignature,
                                              zvm::CstringZVM_UDWORD_SIGNATURE);
          // 修改"右"signature
          rstringRightSignature = zvm::CstringZVM_UDWORD_SIGNATURE;
        }
        else
        {
          bResult = false;
        }
      }
      break;

    default:
      if (rstringLeftSignature != rstringRightSignature)
      // 如果类型不相同
      {
        if (SignatureIsCompatible(rstringLeftSignature, rstringRightSignature, ZVM_OPERATOR_ADVANCE_CAST))
        // 但是"左"可以被提升到"右"
        {
          // Back patch一条"左"cast到"右"的指令
          _GenerateTypeCastInstructionBackend(rautoLeftOperandFunction,
                                              rtOperator.nLineNumber,
                                              rstringLeftSignature,
                                              rstringRightSignature);
          // 修改"左"signature
          rstringLeftSignature = rstringRightSignature;
        }
        else
        {
          if (SignatureIsCompatible(rstringRightSignature, rstringLeftSignature, ZVM_OPERATOR_ADVANCE_CAST))
          // 但是"右"可以被提升到"左"
          {
            // Back patch一条"右"cast到"左"的指令
            _GenerateTypeCastInstructionBackend(rautoRightOperandFunction,
                                                rtOperator.nLineNumber,
                                                rstringRightSignature,
                                                rstringLeftSignature);
            // 修改"右"signature
            rstringRightSignature = rstringLeftSignature;
          }
          else
          {
            bResult = false;
          }
        }
      }
      break;
  }

  return bResult;
}


bool CCodeGeneratorHelper::SignatureIsCompatible(const std::string & rstringLeftSignature,
                                                 const std::string & rstringRightSignature,
                                                 int nOperatorTokenType)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::SignatureIsCompatible()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  bool bResult = true;
  switch (nOperatorTokenType)
  {
    case ZVM_OPERATOR_SUBSCRIPT:
    case ZVM_OPERATOR_SUBSCRIPT_ADDRESS:
      /*
       * 如果是SUBSCRIPT操作，则左signature必须为"[."，右signature只要不是"[."即可.
       */
      if (rstringLeftSignature.size() > 0 && rstringLeftSignature[0] == zvm::CchZVM_TABLE_TYPE_TAG)
      {
        if (rstringRightSignature.size() > 0 && rstringRightSignature[0] == zvm::CchZVM_TABLE_TYPE_TAG)
        {
          bResult = false;
        }
      }
      else
      {
        bResult = false;
      }
      break;

    default:
      if ((rstringLeftSignature.size() > 0 && rstringLeftSignature[0] == zvm::CchZVM_TABLE_TYPE_TAG) &&
          (rstringRightSignature.size() > 0 && rstringRightSignature[0] == zvm::CchZVM_TABLE_TYPE_TAG))
      // A table and another table "=="、"!="、"="
      {
        if (zfc::StringCaseInsensitiveCompare(rstringLeftSignature, rstringRightSignature))
        // 如果不是相同类型的table
        {
          bResult = false;
        }

        if (nOperatorTokenType == ZVM_OPERATOR_LOR ||
            nOperatorTokenType == ZVM_OPERATOR_LAND ||
            nOperatorTokenType == ZVM_OPERATOR_BOR ||
            nOperatorTokenType == ZVM_OPERATOR_BXOR ||
            nOperatorTokenType == ZVM_OPERATOR_BAND ||
            nOperatorTokenType == ZVM_OPERATOR_LT ||
            nOperatorTokenType == ZVM_OPERATOR_GT ||
            nOperatorTokenType == ZVM_OPERATOR_LE ||
            nOperatorTokenType == ZVM_OPERATOR_GE ||
            nOperatorTokenType == ZVM_OPERATOR_SL ||
            nOperatorTokenType == ZVM_OPERATOR_SR ||
            nOperatorTokenType == ZVM_OPERATOR_PLUS ||
            nOperatorTokenType == ZVM_OPERATOR_MINUS ||
            nOperatorTokenType == ZVM_OPERATOR_STAR ||
            nOperatorTokenType == ZVM_OPERATOR_DIV ||
            nOperatorTokenType == ZVM_OPERATOR_MOD)
        {
          bResult = false;
        }
      }
      else
      {
        bResult = _SignatureIsCompatibleBackend(rstringLeftSignature,
                                                rstringRightSignature,
                                                nOperatorTokenType);
      }
      break;
  }

  return(bResult);
}


bool CCodeGeneratorHelper::_SignatureIsCompatibleBackend(
                                           const std::string & rstringLeftSignature,
                                           const std::string & rstringRightSignature,
                                           int nOperatorTokenType)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::_SignatureIsCompatibleBackend()");
  #ifdef ENABLE_TRACE_IN_OUT
  CInOutTracer ciTracer(__PRETTY_FUNC__);
  #endif

  bool bResult = false;

  for (int nLine = 0; nLine < _SnLineCountOfSignatureCompatibleTable; ++nLine)
  {
    TCompatibleTableLine tLine = _SasiSignatureCompatibleTable[nLine];
    if (! zfc::StringCaseInsensitiveCompare(rstringLeftSignature, tLine.stringLeftSignature))
    /* 如果左signature匹配 */
    {
      for (int nColumn = 0; nColumn < tLine.nColumnCount; ++nColumn)
      {
        TCompatibleTableColumn tColumn = tLine.atColumns[nColumn];
        if (! zfc::StringCaseInsensitiveCompare(rstringRightSignature, tColumn.stringRightSignature))
        /* 如果右signature也匹配 */
        {
          for (int n = 0; n < tColumn.nOperatorCount; ++n)
          {
            if (nOperatorTokenType == tColumn.anOperators[n])
            /* 如果operator也匹配 */
            {
              bResult = true;
              break;
            }
          }
          break;
        }
      }
      break;
    }
  }

  return(bResult);
}


void CCodeGeneratorHelper::DumpDetail() const
{
  _ciConstantPool.DumpDetail();

  std::cout << "Begin of all global functions: " << std::endl;
  std::deque<CInstructionContainer_auto>::const_iterator it;
  for (it = _dequeGlobalFunctions.begin(); it != _dequeGlobalFunctions.end(); ++it)
  {
    //(*it)->DumpDetail();
    const CZLangFunction * pciZLangFunction = dynamic_cast<const CZLangFunction *>((*it).get());
    pciZLangFunction->DumpDetail();
  }
  std::cout << "End of all global functions." << std::endl << std::endl;
}


zfc::CBinaryOutputFileStream & operator << (zfc::CBinaryOutputFileStream & bos, const CCodeGeneratorHelper & rciHelper)
{
  // Magic Number、Version
  bos << rciHelper._SudwMagicNumber
      << rciHelper._SuwMajorVersion
      << rciHelper._SuwMinorVersion;
  // constant pool
  bos << rciHelper._ciConstantPool;
  // source file name index
  bos << rciHelper._nSourceFileNameIndex;

  // global functions
  bos << static_cast<zvm::TZVMIndex>(rciHelper._dequeGlobalFunctions.size());
  std::deque<CInstructionContainer_auto>::const_iterator it;
  for (it = rciHelper._dequeGlobalFunctions.begin();
       it != rciHelper._dequeGlobalFunctions.end();
       ++it)
  {
    //bos << *(*it);
    const CZLangFunction * pciZLangFunction = dynamic_cast<const CZLangFunction *>((*it).get());
    bos << *pciZLangFunction;
  }

  return(bos);
}


/**
 * 如果某些操作符的"左值"必须是变量，但在语义分析过程中却发现不是，则报告此错误.
 * 通常用于:
 * (1) 二元操作符"="、"[]"（对table元素进行操作）
 * (2) 一元操作符"++"、"--"
 */
void CCodeGeneratorHelper::ThrowSemanticError_NonLeftValue(
  const CCodeGeneratorHelper::TExpressionAtom & rsiOperator) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::ThrowSemanticError_NonLeftValue()");
  std::string stringError = zfc::SDWORDToString(rsiOperator.nColumnNumber, 10) +
                            ": Error: Non left value in '" + rsiOperator.stringTokenText + "'";
  throw antlr::SemanticException(stringError, _stringSourceFileName, rsiOperator.nLineNumber);
}


/**
 * 如果二元操作符的"左值"、"右值"的类型不兼容，则报告此错误.
 */
void CCodeGeneratorHelper::ThrowSemanticError_InvalidOperandsToBinaryOperator(
  const CCodeGeneratorHelper::TExpressionAtom & rsiOperator,
  const CCodeGeneratorHelper::TExpressionAtom & rsiLeftOperand,
  const CCodeGeneratorHelper::TExpressionAtom & rsiRightOperand,
  const std::string & rstringLeftOperandSignature,
  const std::string & rstringRightOperandSignature) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::ThrowSemanticError_InvalidOperandsToBinaryOperator()");
  std::string stringError = zfc::SDWORDToString(rsiOperator.nColumnNumber, 10) +
                            ": Error: Invalid left operand '" + rsiLeftOperand.stringTokenText +
                            "' of type '" + zvm::TypeSignatureToPrettyString(rstringLeftOperandSignature) +
                            "' and right operand '" + rsiRightOperand.stringTokenText +
                            "' of type '" + zvm::TypeSignatureToPrettyString(rstringRightOperandSignature) +
                            "' to binary operator '" + rsiOperator.stringTokenText + "'";
  throw antlr::SemanticException(stringError, _stringSourceFileName, rsiOperator.nLineNumber);
}


/**
 * 如果一元操作符的"左值"的类型不合法，则报告此错误.
 */
void CCodeGeneratorHelper::ThrowSemanticError_InvalidOperandToUnaryOperator(
  const CCodeGeneratorHelper::TExpressionAtom & rsiOperator,
  const CCodeGeneratorHelper::TExpressionAtom & rsiOperand,
  const std::string & rstringOperandSignature) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::ThrowSemanticError_InvalidOperandToUnaryOperator()");
  std::string stringError = zfc::SDWORDToString(rsiOperator.nColumnNumber, 10) +
                            ": Error: Invalid operand '" + rsiOperand.stringTokenText +
                            "' of type '" + zvm::TypeSignatureToPrettyString(rstringOperandSignature) +
                            "' to unary operator '" + rsiOperator.stringTokenText + "'";
  throw antlr::SemanticException(stringError, _stringSourceFileName, rsiOperator.nLineNumber);
}


/**
 * 如果不能进行Cast，则报告此错误.
 */
void CCodeGeneratorHelper::ThrowSemanticError_InvalidCast(
  const CCodeGeneratorHelper::TExpressionAtom & rsiOperator,
  const CCodeGeneratorHelper::TExpressionAtom & rsiRightOperand,
  const std::string & rstringRightOperandSignature,
  const std::string & rstringCastToSignature) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::ThrowSemanticError_InvalidCast()");
  std::string stringError = zfc::SDWORDToString(rsiOperator.nColumnNumber, 10) +
                            ": Error: Can not cast right operand '" + rsiRightOperand.stringTokenText +
                            "' of type '" + zvm::TypeSignatureToPrettyString(rstringRightOperandSignature) +
                            "' to type '" + zvm::TypeSignatureToPrettyString(rstringCastToSignature) + "'";
  throw antlr::SemanticException(stringError, _stringSourceFileName, rsiOperator.nLineNumber);
}


/**
 * 如果在产生函数调用时，发现"左值"(函数名)不是Literal，则报告此错误.
 */
void CCodeGeneratorHelper::ThrowSemanticError_InvalidFunctionName(
  const CCodeGeneratorHelper::TExpressionAtom & rsiLeftOperand) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::ThrowSemanticError_InvalidFunctionName()");
  std::string stringError = zfc::SDWORDToString(rsiLeftOperand.nColumnNumber, 10) +
                            ": Error: '" + rsiLeftOperand.stringTokenText +
                            "' can not be used as a function name";
  throw antlr::SemanticException(stringError, _stringSourceFileName, rsiLeftOperand.nLineNumber);
}


/**
 * 如果在产生函数调用时，通过查找Symbol table发现"左值"Symbol不是函数名，则报告此错误.
 */
void CCodeGeneratorHelper::ThrowSemanticError_SymbolIsNotFunction(
  int nErrorLineNumber,
  int nErrorColumnNumber,
  CSymbol::TSymbolTag eSymbolTag,
  const std::string & rstringSymbolName) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::ThrowSemanticError_SymbolIsNotFunction()");
  std::string stringError = zfc::SDWORDToString(nErrorColumnNumber, 10) +
                            ": Error: " + CSymbol::SymbolTagToString(eSymbolTag) +
                            "'" + rstringSymbolName + "' can not be used as a function name";
  throw antlr::SemanticException(stringError, _stringSourceFileName, nErrorLineNumber);
}


/**
 * 如果在产生函数调用、取值（地址）时，通过查找Symbol table发现"左值"Symbol没有被定义，则报告此错误.
 */
void CCodeGeneratorHelper::ThrowSemanticError_UndeclaredSymbol(
  int nErrorLineNumber,
  int nErrorColumnNumber,
  const std::string & rstringSymbolName) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::ThrowSemanticError_UndeclaredSymbol()");
  std::string stringError = zfc::SDWORDToString(nErrorColumnNumber, 10) +
                            ": Error: '" + rstringSymbolName + "' undeclared";
  throw antlr::SemanticException(stringError, _stringSourceFileName, nErrorLineNumber);
}


/**
 * 如果在产生函数调用时，发现调用参数(s)的类型不兼容函数定义，则报告此错误.
 */
void CCodeGeneratorHelper::ThrowSemanticError_PassIncompatibleArguments(
  const CCodeGeneratorHelper::TExpressionAtom & rsiOperator,
  const std::string & rstringFunctionName,
  const std::string & rstringFunctionSignature,
  const std::string & rstringPassedArgumentsSignature) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::ThrowSemanticError_PassIncompatibleArguments()");
  std::string stringError = zfc::SDWORDToString(rsiOperator.nColumnNumber, 10) +
                            ": Error: Passing incompatible arguments '" +
                            zvm::ArgumentsSignatureToPrettyString(rstringPassedArgumentsSignature) +
                            "' to '" +
                            zvm::FunctionNameAndSignatureToPrettyString(rstringFunctionName, rstringFunctionSignature) +
                            "'";
  throw antlr::SemanticException(stringError, _stringSourceFileName, rsiOperator.nLineNumber);
}


/**
 * 如果在产生取值（地址）指令时，通过查找Symbol table发现"左值"Symbol不是global
 * variable、local variable或parameter时，则报告此错误.
 */
void CCodeGeneratorHelper::ThrowSemanticError_SymbolIsNotVariable(
  int nErrorLineNumber,
  int nErrorColumnNumber,
  CSymbol::TSymbolTag eSymbolTag,
  const std::string & rstringSymbolName) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::ThrowSemanticError_SymbolIsNotVariable()");
  std::string stringError = zfc::SDWORDToString(nErrorColumnNumber, 10) +
                            ": Error: " + CSymbol::SymbolTagToString(eSymbolTag) +
                            " '" + rstringSymbolName + "' can not be used as a variable name";
  throw antlr::SemanticException(stringError, _stringSourceFileName, nErrorLineNumber);
}


/**
 * 如果SUBSCRIPT操作的"左值"不是一个table变量，则报告此错误.
 */
void CCodeGeneratorHelper::ThrowSemanticError_InvalidLeftOperandToTableSubscript(
  const CCodeGeneratorHelper::TExpressionAtom & rsiLeftOperand) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::ThrowSemanticError_InvalidLeftOperandToTableSubscript()");
  std::string stringError = zfc::SDWORDToString(rsiLeftOperand.nColumnNumber, 10) +
                            ": Error: Invalid left operand '" + rsiLeftOperand.stringTokenText +
                            "' to table subscript operation. It must be a 'table' type !";
  throw antlr::SemanticException(stringError, _stringSourceFileName, rsiLeftOperand.nLineNumber);
}


/**
 * 如果SUBSCRIPT操作的"右值"不是一个variable或constant literal，则报告此错误.
 */
void CCodeGeneratorHelper::ThrowSemanticError_InvalidRightOperandToTableSubscript(
  const CCodeGeneratorHelper::TExpressionAtom & rsiRightOperand,
  const char * pszCanNotBeWhat) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::ThrowSemanticError_InvalidRightOperandToTableSubscript()");
  std::string stringError = zfc::SDWORDToString(rsiRightOperand.nColumnNumber, 10) +
                            ": Error: Invalid right operand '" + rsiRightOperand.stringTokenText +
                            "' to table subscript operation. It can not be a '" + pszCanNotBeWhat + "' !";
  throw antlr::SemanticException(stringError, _stringSourceFileName, rsiRightOperand.nLineNumber);
}


/**
 * 如果function有返回值，但是代码中却没有return语句，或return返回的类型不兼容，则报告此错误.
 */
void CCodeGeneratorHelper::ThrowSemanticError_ReturnStatementIsRequired(
  int nNearLineNumber,
  const std::string & rstringFunctionName,
  const std::string & rstringFunctionReturnSignature) const
{
  std::string stringError = "Error: 'return(" +
                            zvm::TypeSignatureToPrettyString(rstringFunctionReturnSignature) +
                            ")' statement is required for '" +
                            zvm::TypeSignatureToPrettyString(rstringFunctionReturnSignature) +
                            " " + rstringFunctionName + "(...)'";
  throw antlr::SemanticException(stringError, _stringSourceFileName, nNearLineNumber);
}


/**
 * 如果function是void返回，但是代码中却有return(类型)语句，则报告此错误.
 */
void CCodeGeneratorHelper::ThrowSemanticError_ReturnIsNotAllowed(
  int nNearLineNumber,
  const std::string & rstringFunctionName) const
{
  std::string stringError = "Error: 'return(...)' is not allow for 'void " +
                            rstringFunctionName + "(...)'";
  throw antlr::SemanticException(stringError, _stringSourceFileName, nNearLineNumber);
}


/**
 * 如果在IPv4 Literal中CIDR的mask bits不合法（<1或>32），则报告此错误.
 */
void CCodeGeneratorHelper::ThrowSemanticError_InvalidCIDRMask(
  int nErrorLineNumber,
  int nErrorColumnNumber,
  const zfc::EOutOfRange & e
) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::ThrowSemanticError_InvalidCIDRMask()");
  std::string stringError = zfc::SDWORDToString(nErrorColumnNumber, 10) +
                            ": Error: " + e.what();
  throw antlr::SemanticException(stringError, _stringSourceFileName, nErrorLineNumber);
}


/**
 * 当一个function的参数要求是个reference argument时，如果调用者却妄想将一个expression
 * 作为reference argument来传递，则此错误.
 */
void CCodeGeneratorHelper::ThrowSemanticError_CanNotPassExpressionAsReferenceArgument(
  const CCodeGeneratorHelper::TExpressionAtom & rsiOperand,
  const std::string & rstringReferenceArgumentSignature) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::ThrowSemanticError_CanNotPassExpressionAsReferenceArgument()");
  std::string stringError = zfc::SDWORDToString(rsiOperand.nColumnNumber, 10) +
                            ": Error: Can not pass a expression as reference argument of type '" +
                            zvm::ArgumentsSignatureToPrettyString(rstringReferenceArgumentSignature) + "'";
  throw antlr::SemanticException(stringError, _stringSourceFileName, rsiOperand.nLineNumber);
}


/**
 * 如果一个expression statement是不被允许的，则此错误.
 * @note 仅仅允许'ASSIGN'、'++/--'、'function calling' expression as a single statement line.
 */
void CCodeGeneratorHelper::ThrowSemanticError_InvalidExpressionStatement(
  int nErrorLineNumber,
  int nErrorColumnNumber) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::ThrowSemanticError_InvalidExpressionStatement()");
  std::string stringError = zfc::SDWORDToString(nErrorColumnNumber, 10) +
                            ": Error: Expression statement is not a 'ASSIGN' or '++/--' or 'Function Calling' expression !";
  throw antlr::SemanticException(stringError, _stringSourceFileName, nErrorLineNumber);
}


/**
 * 如果一个testing expression statement是不被允许的，则此错误.
 * @note testing expression statement必须有操作结果被push到ZVM stack上.
 */
void CCodeGeneratorHelper::ThrowSemanticError_InvalidTestingExpressionStatement(
  int nErrorLineNumber,
  int nErrorColumnNumber) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::ThrowSemanticError_InvalidTestingExpressionStatement()");
  std::string stringError = zfc::SDWORDToString(nErrorColumnNumber, 10) +
                            ": Error: Testing Expression statement is a void-result expression !";
  throw antlr::SemanticException(stringError, _stringSourceFileName, nErrorLineNumber);
}


/**
 * 如果Reference variable没有被初始化，则报告此错误.
 */
void CCodeGeneratorHelper::ThrowSemanticError_ReferenceVariableMustBeInitialized(
  int nErrorLineNumber,
  int nErrorColumnNumber,
  const std::string & rstringVariableName,
  const std::string & rstringVariableSignature) const
{
  std::string stringError = "Error: Reference variable '" +
                            zvm::TypeSignatureToPrettyString(rstringVariableSignature) + " " +
                            rstringVariableName + "' must be initialized !";
  throw antlr::SemanticException(stringError, _stringSourceFileName, nErrorLineNumber);
}


/**
 * 如果reference variable的initializer不合法，则报告此错误.
 */
void CCodeGeneratorHelper::ThrowSemanticError_InvalidReferenceVariableInitializer(
  const CCodeGeneratorHelper::TExpressionAtom & rsiRightOperand) const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCodeGeneratorHelper::ThrowSemanticError_InvalidReferenceVariableInitializer()");
  std::string stringError = zfc::SDWORDToString(rsiRightOperand.nColumnNumber, 10) +
                            ": Error: Invalid reference variable initializer '" +
                            rsiRightOperand.stringTokenText + "'";
  throw antlr::SemanticException(stringError, _stringSourceFileName, rsiRightOperand.nLineNumber);
}


ZLS_END_NAMESPACE

