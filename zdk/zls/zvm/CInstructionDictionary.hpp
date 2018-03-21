/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CInstructionDictionary.hpp,v $
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


#ifndef _ZLS_zvm_CInstructionDictionary_hpp_
#define _ZLS_zvm_CInstructionDictionary_hpp_

#include <zls/zfc/CSingletonFactoryT.hpp>
#include <zls/zvm/Manifest.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


// forward declaration
class CZVMVirtualThread;


/**
 * 指令Interpreter - 实现该指令的功能的C++ Native Codes.
 * @return PC寄存器加上这个返回值到达下一个将被执行的指令.
 */
typedef TZVMIndex (zvm::CZVMVirtualThread::*TInstructionInterpreter)();


class CInstructionDictionary : public zfc::CReferenceCounter {
  friend class zfc::CSingletonFactoryT<CInstructionDictionary>;

  public:
    /** 指令的操作数类型. */
    enum TInstructionOperandType {
      OPERAND_IS_UNSIGNED_NUMBER_BIT = 1,
      OPERAND_IS_SIGNED_NUMBER_BIT = 2,
      OPERAND_IS_CONSTANT_POOL_INDEX_BIT = 4,
      OPERAND_IS_ZVM_CODE_LABEL_BIT = 8,

      /** 没有操作数. */
      NONE_OPERAND = 0,
      /** 操作数是无符号数. */
      OPERAND_IS_UNSIGNED_NUMBER = OPERAND_IS_UNSIGNED_NUMBER_BIT,
      /** 操作数是有符号数. */
      OPERAND_IS_SIGNED_NUMBER = OPERAND_IS_SIGNED_NUMBER_BIT,
      /** 操作数是一个Constant pool index. */
      OPERAND_IS_CONSTANT_POOL_INDEX = (OPERAND_IS_SIGNED_NUMBER_BIT | OPERAND_IS_CONSTANT_POOL_INDEX_BIT),
      /** 操作数是一个Code label. */
      OPERAND_IS_ZVM_CODE_LABEL = (OPERAND_IS_SIGNED_NUMBER_BIT | OPERAND_IS_ZVM_CODE_LABEL_BIT)
    };

    /** 指令字典的Entry. */
    struct TInstructionDictionaryEntry {
      /** 指令码（0 < 指令码 < max(UWORD)）. */
      TZVMICode nInstructionCode;

      /** 指令码对应的可读Text. */
      const char * pszInstructionText;

      /** 该指令的操作数的字节数. */
      UCHAR nOperandByteCount;

      /** 该指令的操作数的类型. */
      TInstructionOperandType eOperandType;

      /** 指令Interpreter - 实现该指令的功能的C++ Native Codes. */
      TInstructionInterpreter pfuncInterpreter;

      /**
       * 如果eOperandType为OPERAND_IS_CONSTANT_POOL_INDEX，则采用这个BitMask来
       * 指示可以为哪些类型的Constant pool element tag.
       */
      UWORD uwMaskOfConstantPoolElementTag;

      TInstructionDictionaryEntry(TZVMICode _nICode,
                                  const char * _pszText,
                                  UCHAR _nOperandByteCount,
                                  TInstructionOperandType _eOperandType,
                                  UWORD _uwMaskOfConstantPoolElementTag,
                                  TInstructionInterpreter _pfuncInterpreter);
    };

  private:
    /**
     * 指令码的低字节的允许的最小取值.
     * @attention 这个值必须是ZVM type signature tag char中的最小值.
     */
    #define MIN_LOW_BYTE_OF_INSTRUCTION_CODE        CchZVM_BYTE_TYPE_TAG
    /**
     * 指令码的低字节的允许的最大取值.
     * @attention 这个值必须是ZVM type signature tag char中的最大值，在设计
     * ZVM type signature tag char时不要使最小和最大值之间的范围过大，否则
     * _aapsiInstructionDictionary会有较大的内存浪费.
     */
    #define MAX_LOW_BYTE_OF_INSTRUCTION_CODE        CchZVM_TABLE_TYPE_TAG

    #if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 2  // 如果采用三级优化
      TInstructionDictionaryEntry * _apsiInstructionDictionary[65536];
    #else
      #define CAPACITY_OF_LOW_BYTE_OF_INSTRUCTION_CODE (MAX_LOW_BYTE_OF_INSTRUCTION_CODE - MIN_LOW_BYTE_OF_INSTRUCTION_CODE + 1)

      TInstructionDictionaryEntry *
      _aapsiInstructionDictionary[256][CAPACITY_OF_LOW_BYTE_OF_INSTRUCTION_CODE];
    #endif

    void AppendInstructionEntry(TZVMICode nICode,
                                const char * pszText,
                                UCHAR nOperandByteCount,
                                TInstructionOperandType eOperandType,
                                UWORD uwMaskOfConstantPoolElementTag,
                                TInstructionInterpreter pfuncInterpreter);

    /**
     * Default Constructor.
     * @note 初始化指令字典，程序开始时必须先进行初始化指令字典.
     */
    CInstructionDictionary();

    /** Destructor. */
    ~CInstructionDictionary();

  public:
    /**
     * 按"指令码"来Seek指令字典中是否有这样的指令信息被登记，如果"指令码"相同，则匹配.
     * @param nInstructionCode 指令码.
     * @return 0指针则表示查找失败.
     */
    const TInstructionDictionaryEntry * SeekInstructionDictionary(TZVMICode nInstructionCode) const;

    TInstructionInterpreter GetInstructionInterpreter(TZVMICode nInstructionCode) const;
};


typedef zfc::CSmartPointerT<CInstructionDictionary>  CInstructionDictionary_auto;


/** 全局的CInstructionDictionary factory. */
extern zfc::CSingletonFactoryT<CInstructionDictionary> GciInstructionDictionaryFactory;


ZLS_END_NAMESPACE


#endif

