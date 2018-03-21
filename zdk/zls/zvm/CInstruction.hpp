/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CInstruction.hpp,v $
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


#ifndef _ZLS_zvm_CInstruction_hpp_
#define _ZLS_zvm_CInstruction_hpp_

#include <zls/zfc/CBinaryInputFileStream.hpp>
#include <zls/zvm/Manifest.hpp>
#include <zls/zvm/ConstantPool.hpp>
#include <zls/zvm/CInstructionDictionary.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


/**
 * 该类被用来表示一行指令.
 */
class CInstruction {
  private:
    /** 该指令的指令码. */
    zvm::TZVMICode _nInstructionCode;

    /**
     * 该指令的操作数的字节数.
     * 如果_nOperandByteCount == 0，则不使用下面的union；
     * 如果_nOperandByteCount == 1，则下面的union取_uchOperand；
     * 如果_nOperandByteCount == 2，则下面的union取_uwOperand；
     * 如果_nOperandByteCount == 4，则下面的union取_udwOperand.
     */
    UCHAR _nOperandByteCount;
    union {
      UCHAR  _uchOperand;
      UWORD  _uwOperand;
      UDWORD _udwOperand;
    };

    #if defined(ENABLE_ZVM_OPTIMIZATION)
    /**
     * Verify Byte Codes Integrity后将立即解析这个字段.
     */
    TInstructionInterpreter _pfuncInterpreter;
    #endif

    #ifndef NDEBUG
    /** "检查不变量"方法. */
    void AssertPostCondition() const
    {
      ZLS_ASSERT0(_nInstructionCode > 0xff, "Shit, a bug");
    }
    #endif

  public:
    /**
     * @name Interfaces for link.
     */
    //@{
    /**
     * 在Link之后进行的完整性检查，具体检查如下：
     * <pre>
     * (1) 每条指令的指令码正确否、其所需操作数的字节数符合否.
     * (2) 如果指令中涉及到Constant pool的Index，则检验Index合法否，类型兼容否.
     * (3) 如果指令涉及到code label，则检查其是否会越界.
     * </pre>
     *
     * @param rciConstantPool 查找这个Constant pool.
     * @param iMyselfInstructionIndex 我自己的指令Index.
     * @param iLastInstructionIndex 最后一条指令的Index.
     * @throw zvm::EVerifyFailure 当Byte codes完整性失效时.
     */
    void VerifyByteCodesIntegrity(const zvm::CConstantPool & rciConstantPool,
                                  TZVMIndex iMyselfInstructionIndex,
                                  TZVMIndex iLastInstructionIndex) const;

    //@}
    /**
     * 将指令码转换为Pretty text.
     *
     * @param nInstructionCode 指令码（必须为合法的指令码）.
     * @throw zfc::EInvalidArgument 当nInstructionCode不合法时.
     */
    static const std::string InstructionCodeToString(zvm::TZVMICode nInstructionCode);

    /** Overload operator=(). */
    CInstruction & operator=(const CInstruction & rciRight);

    #if defined(ENABLE_ZVM_OPTIMIZATION)
    /** 得到这条指令的指令Interpreter. */
    TInstructionInterpreter GetInstructionInterpreter() const
    {
      return _pfuncInterpreter;
    }
    #endif

    /** 得到这条指令的指令码. */
    zvm::TZVMICode GetInstructionCode() const
    {
      return _nInstructionCode;
    }

    /** 得到这条指令的操作数的字节数. */
    UCHAR GetOperandByteCount() const
    {
      return _nOperandByteCount;
    }

    /** 认为这条指令的操作数是一个UCHAR，然后取得它. */
    UCHAR GetOperandAsUCHAR() const
    {
      return _uchOperand;
    }

    /** 认为这条指令的操作数是个UWORD，然后取得它. */
    UWORD GetOperandAsUWORD() const
    {
      return _uwOperand;
    }

    /** 认为这条指令的操作数是个SWORD，然后取得它. */
    SWORD GetOperandAsSWORD() const
    {
      return static_cast<SWORD>(_uwOperand);
    }

    /** 认为这条指令的操作数是一个zvm::TZVMIndex，然后取得它. */
    zvm::TZVMIndex GetOperandAsTZVMIndex() const
    {
      return static_cast<zvm::TZVMIndex>(_udwOperand);
    }

    /** 认为这条指令的操作数是一个SDWORD，然后取得它. */
    SDWORD GetOperandAsSDWORD() const
    {
      return static_cast<SDWORD>(_udwOperand);
    }

    /** 认为这条指令的操作数是一个UDWORD，然后取得它. */
    UDWORD GetOperandAsUDWORD() const
    {
      return _udwOperand;
    }

    /**
     * 将这条指令的内容按照pretty的格式dump到一个string中.
     *
     * @throw zfc::EPanic 当CInstruction::_nInstructionCode或
     * CInstruction::_nOperandByteCount不合法时。但是如果ZLang compiler
     * 是正确无误的话，则这是一个"不可能的任务".
     */
    std::string ToString() const;

    /**
     * 将这条指令的内容按照pretty的格式dump到stdout.
     *
     * @throw zfc::EPanic 当CInstruction::_nInstructionCode或
     * CInstruction::_nOperandByteCount不合法时。但是如果ZLang compiler
     * 是正确无误的话，则这是一个"不可能的任务".
     */
    void DumpDetail() const;

    /** Default constructor. */
    CInstruction()
      : _nInstructionCode(0),
        _nOperandByteCount(0)
    { }

    /** Copy constructor. */
    CInstruction(const CInstruction & rciRight)
    {
      operator=(rciRight);
      ZLS_CHECK_INVARIANTS(AssertPostCondition());
    }

    /** Constructor for 没操作数的指令. */
    /*
    CInstruction(zvm::TZVMICode nInstructionCode)
      : _nInstructionCode(nInstructionCode),
        _nOperandByteCount(0)
    {
      ZLS_CHECK_INVARIANTS(AssertPostCondition());
    }
    */

    /** Constructor for 一个Byte操作数的指令. */
    /*
    CInstruction(zvm::TZVMICode nInstructionCode, UCHAR uchOperand)
      : _nInstructionCode(nInstructionCode),
        _nOperandByteCount(sizeof(UCHAR)),
        _uchOperand(uchOperand)
    {
      ZLS_CHECK_INVARIANTS(AssertPostCondition());
    }
    */

    /** Constructor for 一个UWORD操作数的指令. */
    /*
    CInstruction(zvm::TZVMICode nInstructionCode, UWORD uwOperand)
      : _nInstructionCode(nInstructionCode),
        _nOperandByteCount(sizeof(UWORD))
    {
      _uwOperand = uwOperand;
      ZLS_CHECK_INVARIANTS(AssertPostCondition());
    }
    */

    /** Constructor for 一个SWORD操作数的指令. */
    /*
    CInstruction(zvm::TZVMICode nInstructionCode, SWORD swOperand)
      : _nInstructionCode(nInstructionCode),
        _nOperandByteCount(sizeof(SWORD))
    {
      _uwOperand = static_cast<UWORD>(swOperand);
      ZLS_CHECK_INVARIANTS(AssertPostCondition());
    }
    */

    /** Constructor for 一个zvm::TZVMIndex操作数的指令. */
    /*
    CInstruction(zvm::TZVMICode nInstructionCode, zvm::TZVMIndex iOperand)
      : _nInstructionCode(nInstructionCode),
        _nOperandByteCount(sizeof(zvm::TZVMIndex))
    {
      _udwOperand = static_cast<UDWORD>(iOperand);
      ZLS_CHECK_INVARIANTS(AssertPostCondition());
    }
    */

    /** Constructor for 一个UDWORD操作数的指令. */
    /*
    CInstruction(zvm::TZVMICode nInstructionCode, UDWORD udwOperand)
      : _nInstructionCode(nInstructionCode),
        _nOperandByteCount(sizeof(UDWORD)),
        _udwOperand(udwOperand)
    {
      _udwOperand = udwOperand;
      ZLS_CHECK_INVARIANTS(AssertPostCondition());
    }
    */

    /** Destructor. */
    ~CInstruction()
    { }

    /**
     * 从CBinaryInputFileStream读入一条指令.
     *
     * @throw zvm::EInvalidObjectFile 当读入的CInstruction::_nOperandByteCount不合法时.
     */
    friend zfc::CBinaryInputFileStream & operator>>(zfc::CBinaryInputFileStream & bis,
                                                    zvm::CInstruction & rci);
};


ZLS_END_NAMESPACE


#endif

