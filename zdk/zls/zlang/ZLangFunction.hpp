/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/ZLangFunction.hpp,v $
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


#ifndef _ZLS_zlang_ZLangFunction_hpp_
#define _ZLS_zlang_ZLangFunction_hpp_

#include <zls/zvm/Manifest.hpp>


// Begin namespace 'zlang::'
ZLS_BEGIN_NAMESPACE(zlang)


// forward declaration
class CConstantPool;
class CInstructionContainer;
typedef zfc::CSmartPointerT<CInstructionContainer>      CInstructionContainer_auto;


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

    /**
     * 指示这条指令中有temp local variable offset，而这个offset是不正确的
     * （只出现在Local variable initializing expression时）.
     */
    bool _bNeedFixTempLocalVariableOffset;  //< 2001/7/21: Added

    #ifndef NDEBUG
    /** "检查不变量"方法. */
    void AssertPostCondition() const
    {
      ZLS_ASSERT0(_nInstructionCode > 0xff, "Shit, a bug");
    }
    #endif

  public:
    /**
     * 将指令码转换为Pretty text.
     *
     * @param nInstructionCode 指令码（必须为合法的指令码）.
     * @throw zfc::EInvalidArgument 当nInstructionCode不合法时.
     */
    static const std::string InstructionCodeToString(zvm::TZVMICode nInstructionCode);

    /** Back patch code label for 'break'、'continue'、'while'、'if-then-else'. */
    void BackPatchLabel(zvm::TZVMIndex iPatchedLabelOffset)
    {
      _udwOperand = static_cast<UDWORD>(iPatchedLabelOffset);
    }

    /** Overload operator=(). */
    CInstruction & operator=(const CInstruction & rciRight);

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

    /** 认为这条指令的操作数是一个UDWORD，然后取得它. */
    UDWORD GetOperandAsUDWORD() const
    {
      return _udwOperand;
    }

    /** 认为这条指令的操作数是一个zvm::TZVMIndex，然后取得它. */
    zvm::TZVMIndex GetOperandAsTZVMIndex() const
    {
      return static_cast<zvm::TZVMIndex>(_udwOperand);
    }

    /** 打上标识这条指令以后还需要被Fix temp local variable offset. */
    void MarkNeedFixTempLocalVariableOffset()
    {
      _bNeedFixTempLocalVariableOffset = true;
    }

    /** Fix temp local variable offset. */
    void SmartFixTempLocalVariableOffset(UWORD uwLocalVariableCount)
    {
      if (_bNeedFixTempLocalVariableOffset)
      {
        _uwOperand += uwLocalVariableCount;
      }
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
    void DumpDetail() const
    {
      std::cout << ToString() << std::endl;
    }

    /** Default constructor. */
    CInstruction()
      : _nInstructionCode(0),
        _nOperandByteCount(0),
        _bNeedFixTempLocalVariableOffset(false)
    { }

    /** Copy constructor. */
    CInstruction(const CInstruction & rciRight)
    {
      operator=(rciRight);
      ZLS_CHECK_INVARIANTS(AssertPostCondition());
    }

    /** Constructor for 没操作数的指令. */
    CInstruction(zvm::TZVMICode nInstructionCode)
      : _nInstructionCode(nInstructionCode),
        _nOperandByteCount(0),
        _bNeedFixTempLocalVariableOffset(false)
    {
      ZLS_CHECK_INVARIANTS(AssertPostCondition());
    }

    /** Constructor for 一个Byte操作数的指令. */
    CInstruction(zvm::TZVMICode nInstructionCode, UCHAR uchOperand)
      : _nInstructionCode(nInstructionCode),
        _nOperandByteCount(sizeof(UCHAR)),
        _uchOperand(uchOperand),
        _bNeedFixTempLocalVariableOffset(false)
    {
      ZLS_CHECK_INVARIANTS(AssertPostCondition());
    }

    /** Constructor for 一个UWORD操作数的指令. */
    CInstruction(zvm::TZVMICode nInstructionCode, UWORD uwOperand)
      : _nInstructionCode(nInstructionCode),
        _nOperandByteCount(sizeof(UWORD)),
        _bNeedFixTempLocalVariableOffset(false)
    {
      _uwOperand = uwOperand;
      ZLS_CHECK_INVARIANTS(AssertPostCondition());
    }

    /** Constructor for 一个SWORD操作数的指令. */
    CInstruction(zvm::TZVMICode nInstructionCode, SWORD swOperand)
      : _nInstructionCode(nInstructionCode),
        _nOperandByteCount(sizeof(SWORD)),
        _bNeedFixTempLocalVariableOffset(false)
    {
      _uwOperand = static_cast<UWORD>(swOperand);
      ZLS_CHECK_INVARIANTS(AssertPostCondition());
    }

    /** Constructor for 一个zvm::TZVMIndex操作数的指令. */
    CInstruction(zvm::TZVMICode nInstructionCode, zvm::TZVMIndex iOperand)
      : _nInstructionCode(nInstructionCode),
        _nOperandByteCount(sizeof(zvm::TZVMIndex)),
        _bNeedFixTempLocalVariableOffset(false)
    {
      _udwOperand = static_cast<UDWORD>(iOperand);
      ZLS_CHECK_INVARIANTS(AssertPostCondition());
    }

    /** Constructor for 一个UDWORD操作数的指令. */
    CInstruction(zvm::TZVMICode nInstructionCode, UDWORD udwOperand)
      : _nInstructionCode(nInstructionCode),
        _nOperandByteCount(sizeof(UDWORD)),
        _udwOperand(udwOperand),
        _bNeedFixTempLocalVariableOffset(false)
    {
      _udwOperand = udwOperand;
      ZLS_CHECK_INVARIANTS(AssertPostCondition());
    }

    /** Destructor. */
    ~CInstruction()
    { }

    /**
     * 将这条指令写入CBinaryOutputFileStream.
     *
     * @throw zfc::EPanic 当CInstruction::_nOperandByteCount不合法时。
     * 但是如果ZLang compiler是正确无误的话，则这是一个"不可能的任务".
     */
    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const CInstruction & rci);
};


/**
 * 该类是个抽象基类.
 *
 * @note 该抽象基类被用来存贮ZLang compiler编译产生的Byte codes和Line number
 * debug info，以及定义了一组产生Temp variable的接口.
 *
 * @todo 将_dequeLineNumberDebugInfo修改为可自动按iFromWhichInstructionStart
 * 升序排序的container（或在写byte codes到object file时先进行一次升序排序）.
 */
class CInstructionContainer : public zfc::CReferenceCounter {
  private:
    /** Forbidden copy constructor. */
    CInstructionContainer(const CInstructionContainer & rci);

    /** Forbidden operator=(). */
    CInstructionContainer & operator=(const CInstructionContainer & rci);

  public:
    /**
     * 用于跟踪某个function的byte codes的行号信息，基本表达的意思是：从哪条指令
     * 开始的一段指令是属于源文件的第几行.
     */
    struct TLineNumberDebug {
      /**
       * 从哪条指令开始.
       * @attention 指令的下标是从0开始的，即为为下面的std::deque<CInstruction_auto>的下标.
       */
      zvm::TZVMIndex iFromWhichInstructionStart;
      zvm::TZVMIndex iLineNumber;

      TLineNumberDebug()
      { }

      TLineNumberDebug(zvm::TZVMIndex iStart, zvm::TZVMIndex _iLineNumber)
        : iFromWhichInstructionStart(iStart),
          iLineNumber(_iLineNumber)
      { }
    };

  protected:
    /**
     * @name 写入Object file的东西.
     */
    //@{
    std::deque<CInstruction>     _dequeInstructions;
    std::deque<TLineNumberDebug> _dequeLineNumberDebugInfos;
    //@}

    /** 返回在nPosition（>=0）位置的instruction的iterator. */
    std::deque<CInstruction>::iterator JumpToPosition(zvm::TZVMIndex nPosition);

  public:
    /**
     * @name Interface for generating byte codes.
     */
    //@{
    std::deque<TLineNumberDebug> & GetLineNumberDebugInfos()
    { return _dequeLineNumberDebugInfos; }

    const std::deque<TLineNumberDebug> & GetLineNumberDebugInfos() const
    { return _dequeLineNumberDebugInfos; }

    const std::deque<CInstruction> & GetInstructions() const
    { return _dequeInstructions; }

    /**
     * 按下标得到一条指令.
     *
     * @attention 指令的下标是从0开始的.
     * @throw zfc::EOutOfRange
     */
    CInstruction & GetInstructionAt(zvm::TZVMIndex iIndex);

    /**
     * 得到当前已产生的代码的最后位置（即下一条可产生的位置），返回的整数可以
     * 作为label位置.
     *
     * @attention 指令的下标是从0开始的.
     */
    zvm::TZVMIndex GetLabelBookmark() const
    { return _dequeInstructions.size(); }

    void SmartFixTempLocalVariableOffset(UWORD uwLocalVariableCount);
    void BackPatchLabel(zvm::TZVMIndex iWhichInstruction, zvm::TZVMIndex iPatchedLabel);

    void AppendLineNumberDebugInfo(zvm::TZVMIndex iStart, zvm::TZVMIndex iLineNumber);

    zvm::TZVMIndex AppendInstruction(zvm::TZVMICode nInstructionCode);
    zvm::TZVMIndex AppendInstruction(zvm::TZVMICode nInstructionCode, UCHAR uchOperand);
    zvm::TZVMIndex AppendInstruction(zvm::TZVMICode nInstructionCode, UWORD uwOperand);
    zvm::TZVMIndex AppendInstruction(zvm::TZVMICode nInstructionCode, SWORD swOperand);
    zvm::TZVMIndex AppendInstruction(zvm::TZVMICode nInstructionCode, zvm::TZVMIndex nOperand);
    zvm::TZVMIndex AppendInstruction(zvm::TZVMICode nInstructionCode, UDWORD udwOperand);
    zvm::TZVMIndex AppendInstruction(CInstructionContainer_auto autoContainer);

    /**
     * 在nBeforePosition（>=0）指示的位置前面insert新指令.
     *
     * @return 新指令的Index，也即等于nBeforePosition.
     */
    zvm::TZVMIndex InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                           zvm::TZVMICode nInstructionCode);
    zvm::TZVMIndex InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                           zvm::TZVMICode nInstructionCode,
                                           UCHAR uchOperand);
    zvm::TZVMIndex InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                           zvm::TZVMICode nInstructionCode,
                                           UWORD uwOperand);
    zvm::TZVMIndex InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                           zvm::TZVMICode nInstructionCode,
                                           SWORD swOperand);
    zvm::TZVMIndex InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                           zvm::TZVMICode nInstructionCode,
                                           zvm::TZVMIndex nOperand);
    zvm::TZVMIndex InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                           zvm::TZVMICode nInstructionCode,
                                           UDWORD udwOperand);

    virtual void FreeAllTempVariables() = 0;
    /**
     * 动态申请一个temp string variable.
     *
     * @param bReturnIndex true则表示需要返回的是被动态产生的temp variable在
     * ZVM stack上的BP Offset；false则表示需要返回的是这个temp variable的Index.
     */
    virtual SWORD AllocateTempStringVariable(bool bReturnIndex = false) = 0;
    virtual SWORD AllocateTempIPv4AddressVariable(bool bReturnIndex = false) = 0;
    virtual SWORD AllocateTempPPortVariable(bool bReturnIndex = false) = 0;
    virtual SWORD AllocateTempTableVariable(char chTableElementTypeTag, bool bReturnIndex = false) = 0;
    //@}

    CInstructionContainer()
    { }

    virtual ~CInstructionContainer()
    { }

    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const TLineNumberDebug & rt);
};


/**
 * 该类通常被用来辅助ZLang compiler为ZLang function产生Byte codes时使用.
 *
 * @note 例如为二元表达式、Local variables初始化等就需要new一个临时的CInstructionSequence.
 */
class CInstructionSequence : public CInstructionContainer {
  private:
    /**
     * 这个member variable被用来能够恰当地找到当前正在被产生byte codes的
     * CZLangFunction instance，然后正确地Insert temp variable instruction.
     *
     * @attention CInstructionSequence会形成如下的嵌套关系：
     * <pre>
     *   CInstructionSequence
     *     |
     *     -> CInstructionSequence
     *          |
     *          -> CInstructionSequence
     *               |
     *               -> CInstructionSequence
     *                    |
     *                    -> CZLangFunction
     *
     * 最内层一定是一个CZLangFunction.
     * </pre>
     */
    CInstructionContainer * _pciOwnerInstructionContainer;

  public:
    virtual void FreeAllTempVariables()
    {
      // Forward to inline member variable's virtual method
      _pciOwnerInstructionContainer->FreeAllTempVariables();
    }

    virtual SWORD AllocateTempStringVariable(bool bReturnIndex = false)
    {
      // Forward to inline member variable's virtual method
      return _pciOwnerInstructionContainer->AllocateTempStringVariable(bReturnIndex);
    }

    virtual SWORD AllocateTempIPv4AddressVariable(bool bReturnIndex = false)
    {
      // Forward to inline member variable's virtual method
      return _pciOwnerInstructionContainer->AllocateTempIPv4AddressVariable(bReturnIndex);
    }

    virtual SWORD AllocateTempPPortVariable(bool bReturnIndex = false)
    {
      // Forward to inline member variable's virtual method
      return _pciOwnerInstructionContainer->AllocateTempPPortVariable(bReturnIndex);
    }

    virtual SWORD AllocateTempTableVariable(char chTableElementTypeTag, bool bReturnIndex = false)
    {
      // Forward to inline member variable's virtual method
      return _pciOwnerInstructionContainer->AllocateTempTableVariable(chTableElementTypeTag, bReturnIndex);
    }

    CInstructionSequence(CInstructionContainer * pciOwnerInstructionContainer)
      : _pciOwnerInstructionContainer(pciOwnerInstructionContainer)
    { }
};


/**
 * 该类被用来表示ZLang中的static或global function被compile后的结果.
 */
class CZLangFunction : public CInstructionContainer {
  public:
    class TempVariableAllocator {
      private:
        CZLangFunction * _pciOwnerZLangFunction;

        /** 这个function需要的临时变量的总数. */
        UWORD _uwTempVariableCount;

        /**
         * 这个function中每个string型临时变量的各自在总的临时变量的总数中的Index（>=1）.
         *
         * @note 在产生临时变量时，各种类型的临时变量是可以混合交叉申请的.
         */
        std::vector<SWORD> _vectorStringVariableOffsets;

        /**
         * 这个function中每个rope型临时变量的各自在总的临时变量的总数中的Index（>=1）.
         *
         * @note 在产生临时变量时，各种类型的临时变量是可以混合交叉申请的.
         */
        std::vector<SWORD> _vectorRopeVariableOffsets;

        /**
         * 这个function中每个ipv4address型临时变量的各自在总的临时变量的总数中的Index（>=1）.
         *
         * @note 在产生临时变量时，各种类型的临时变量是可以混合交叉申请的.
         */
        std::vector<SWORD> _vectorIPv4AddressVariableOffsets;

        /**
         * 这个function中每个pport型临时变量的各自在总的临时变量的总数中的Index（>=1）.
         *
         * @note 在产生临时变量时，各种类型的临时变量是可以混合交叉申请的.
         */
        std::vector<SWORD> _vectorPPortVariableOffsets;

        /**
         * 这个function中每个table型临时变量的各自在总的临时变量的总数中的Index（>=1）.
         *
         * @note 在产生临时变量时，各种类型的临时变量是可以混合交叉申请的.
         */
        std::vector<SWORD> _vectorTableVariableOffsets;

        /** 这个function中目前第一个可用的string型临时变量在_vectorStringVariables中的Index. */
        UWORD _iFirstAvailableStringVariable;

        /** 这个function中目前第一个可用的rope型临时变量在_vectorStringVariables中的Index. */
        UWORD _iFirstAvailableRopeVariable;

        /** 这个function中目前第一个可用的ipv4address型临时变量在_vectorIPv4AddressVariables中的Index. */
        UWORD _iFirstAvailableIPv4AddressVariable;

        /** 这个function中目前第一个可用的pport型临时变量在_vectorPPortVariables中的Index. */
        UWORD _iFirstAvailablePPortVariable;

        /** 这个function中目前第一个可用的table型临时变量在_vectorTableVariables中的Index. */
        UWORD _iFirstAvailableTableVariable;

        /**
         * 在Local Variables指令后插入需要的Temp Variables指令.
         *
         * @attention 还好我们的falseJump、unlimitJump等指令采用的都是offset，
         * 这样只要新Insert的指令不是在Jump指令的code block中就不会影响已被
         * 产生的其它指令了.
         */
        void InsertTempVariableInstruction(zvm::TZVMICode nICode);

      public:
        void FreeAllTempVariables();
        SWORD AllocateTempStringVariable(bool bReturnIndex = false);
        SWORD AllocateTempRopeVariable(bool bReturnIndex = false);
        SWORD AllocateTempIPv4AddressVariable(bool bReturnIndex = false);
        SWORD AllocateTempPPortVariable(bool bReturnIndex = false);
        SWORD AllocateTempTableVariable(char chTableElementTypeTag, bool bReturnIndex = false);

        UWORD GetTempVariableCount()
        { return _uwTempVariableCount; }

        TempVariableAllocator(CZLangFunction * pciOwnerZLangFunction);
    };

    /**
     * 用于跟踪某个function的Local variable或Parameter信息.
     */
    struct TStackVariableDebug {
      zvm::TZVMIndex iNameAndSignatureIndex;  /**< 该variable的name and signature index */
      SWORD iBPOffset;  /**< 该variable与寄存器BP的offset（compile time决定）*/

      TStackVariableDebug()
      { }
      TStackVariableDebug(zvm::TZVMIndex iIndex, SWORD _iBPOffset)
        : iNameAndSignatureIndex(iIndex),
          iBPOffset(_iBPOffset)
      {}
    };

    friend class TempVariableAllocator;

  private:
    /** 临时Local variables产生器. */
    TempVariableAllocator _ciTempVariableAllocator;

    /**
     * @name 写入Object file的东西.
     */
    //@{
    /**
     * 指向一个在Constant pool中的ZVM function引用，重定位时将利用它.
     *
     * @note 在为static function和internal global function进行重定位时，通过遍历
     * ZVM的function注册表，如果某个CZVMFunction的_iFunctionReference与某个
     * static-function-reference、global-function-reference的在constant pool的下
     * 标相等，则定位成功.
     */
    zvm::TZVMIndex _iFunctionReference;

    UWORD                           _uwParameterCount;
    UWORD                           _uwLocalVariableCount;
    std::deque<TStackVariableDebug> _dequeStackVariableDebugInfo;
    //std::deque<TLineNumberDebug>    _dequeLineNumberDebugInfos;
    //std::deque<CInstruction>        _dequeInstructions;
    //@}

  public:
    /**
     * @name Interface for generating byte codes.
     */
    //@{
    void AppendStackVariableDebugInfo(zvm::TZVMIndex nIndex, SWORD iBPOffset);

    /** 从一个临时CInstructionContainer中将它的指令copy到我的末尾. */
    zvm::TZVMIndex AppendInstruction(CInstructionContainer_auto autoContainer);

    /** @attention 隐含参数也算在内. */
    void SetParameterCount(UWORD uwCount)
    {
      _uwParameterCount = uwCount;
    }

    void SetLocalVariableCount(UWORD uwCount)
    {
      _uwLocalVariableCount = uwCount;
    }

    void SetFunctionReference(zvm::TZVMIndex iFunctionReference)
    {
      _iFunctionReference = iFunctionReference;
    }

    virtual void FreeAllTempVariables()
    { _ciTempVariableAllocator.FreeAllTempVariables(); }

    virtual SWORD AllocateTempStringVariable(bool bReturnIndex = false)
    { return _ciTempVariableAllocator.AllocateTempStringVariable(bReturnIndex); }

    virtual SWORD AllocateTempIPv4AddressVariable(bool bReturnIndex = false)
    { return _ciTempVariableAllocator.AllocateTempIPv4AddressVariable(bReturnIndex); }

    virtual SWORD AllocateTempPPortVariable(bool bReturnIndex = false)
    { return _ciTempVariableAllocator.AllocateTempPPortVariable(bReturnIndex); }

    virtual SWORD AllocateTempTableVariable(char chTableElementTypeTag, bool bReturnIndex = false)
    { return _ciTempVariableAllocator.AllocateTempTableVariable(chTableElementTypeTag, bReturnIndex); }
    //@}

    zvm::TZVMIndex GetFunctionReference() const
    { return _iFunctionReference; }

    /**
     * 将这条指令的内容按照pretty的格式dump到stdout.
     *
     * @throw zfc::EPanic 当CInstruction::_nInstructionCode或
     * CInstruction::_nOperandByteCount不合法时。但是如果ZLang compiler
     * 是正确无误的话，则这是一个"不可能的任务".
     */
    void DumpDetail() const;

    /** Default constructor. */
    CZLangFunction();

    /**
     * 将这个ZVM function写入CBinaryOutputFileStream.
     *
     * @throw zfc::EPanic 当CInstruction::_nOperandByteCount不合法时。
     * 但是如果ZLang compiler是正确无误的话，则这是一个"不可能的任务".
     */
    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const CZLangFunction & rci);

    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const TStackVariableDebug & rt);
};



ZLS_END_NAMESPACE


#endif

