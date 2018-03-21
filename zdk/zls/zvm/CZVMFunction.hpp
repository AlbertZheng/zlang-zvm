/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CZVMFunction.hpp,v $
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


#ifndef _ZLS_zvm_CZVMFunction_hpp_
#define _ZLS_zvm_CZVMFunction_hpp_

#include <zls/zfc/CBinaryInputFileStream.hpp>
#include <zls/zvm/Manifest.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


// forward declaration
class CSlot;
class CInstruction;
class CZVMObjectFile;
class CConstantPool;
class CNameAndSignatureReference;


/**
 * 该类型被用来表示用C++编写的本地function，它们符合ZVM function的调用规范，
 * 被用来扩展ZLang的能力.
 *
 * @param pciLastArgumentSlot 在ZVM stack上，这个function需要的最后一个参数
 * 的Slot指针.
 *
 * @attention (1)隐含参数（返回值Slot）也被认为是一个参数. (2)对于Native function，
 * ZVM并不Push PC到ZVM stack上保存.
 */
typedef void (* TNativeFunction)(CSlot * pciLastArgumentSlot);


class CZVMFunction {
  private:
    /** Forbidden operator=(). */
    CZVMFunction & operator=(const CZVMFunction &);
    /** Forbidden Copy constructor. */
    CZVMFunction(const CZVMFunction &);

  public:
    /**
     * 用于跟踪某个function的byte codes的行号信息，基本表达的意思是：从哪条指令
     * 开始的一段指令是属于源文件的第几行.
     */
    struct TLineNumberDebug {
      /**
       * 从哪条指令开始.
       * @attention 指令的下标是从0开始的.
       */
      zvm::TZVMIndex iFromWhichInstructionStart;
      zvm::TZVMIndex iLineNumber;

      TLineNumberDebug()
      { }
    };

    /**
     * 用于跟踪某个function的Local variable或Parameter信息.
     */
    struct TStackVariableDebug {
      zvm::TZVMIndex iNameAndSignatureReference;  /**< 该variable的name and signature reference */
      SWORD iBPOffset;  /**< 该variable与寄存器BP的offset（compile time决定）*/

      TStackVariableDebug()
      { }
    };

  private:
    /**
     * @name Construct时填写的字段.
     */
    //@{
    /**
     * 指向该ZVM function所在Object file.
     */
    const CZVMObjectFile * _pciOwnerObjectFile;

    /**
     * 指向该ZVM function所在Object file中的Constant pool.
     */
    const zvm::CConstantPool * _pciConstantPool;

    /**
     * 指向该ZVM function在Constant pool中的name and signature reference.
     */
    const zvm::CNameAndSignatureReference * _pciNameAndSignatureReference;
    //@}

    /**
     * 指示Debug info是否已经被去除了.
     * @note 当用户让ZVM调入一个Object file后，用户还可以让ZVM将已经读入内存的
     * ZVM function's debug info去除掉以节省内存.
     */
    bool _bDebugInfoStriped;

    /**
     * @name 从Object file读入的东西.
     */
    //@{
    /**
     * 指向一个ZVM function引用，重定位时将利用它.
     *
     * @note 在为static function和internal global function进行重定位时，通过遍历
     * ZVM的function注册表，如果某个CZVMFunction的_iFunctionReference与某个
     * static-function-reference、global-function-reference的在constant pool的下
     * 标相等，则定位成功.
     */
    zvm::TZVMIndex _iFunctionReference;
    /** @attention 隐含参数也算在内. */
    UWORD _uwParameterCount;
    UWORD _uwLocalVariableCount;

    zvm::TZVMIndex                     _nInstructionSequenceCapacity;
    zvm::CInstruction                * _aciInstructionSequence;
    std::vector<TLineNumberDebug>      _vectorLineNumberDebugInfo;
    std::vector<TStackVariableDebug>   _vectorStackVariableDebugInfo;
    //@}

    void DoCache();

  public:
    /**
     * @name Interface for link.
     */
    //@{
    TZVMIndex GetFunctionReferenceIndex() const
    { return _iFunctionReference; }

    /**
     * 在Link之后进行的完整性检查，具体检查如下：
     * (1) 每条指令的指令码正确否、其所需操作数的字节数符合否.
     * (2) 指令中如涉及到Constant pool的index，则检验合法否，类型兼容否.
     * (3) 如果指令涉及到type signature，则检查合法否.
     *
     * @throw zvm::EVerifyFailure 当Byte codes完整性失效时.
     * @throw zfc::EInvalidState 如果在调用这个method之前还没被link，
     * 则throw出此exception.
     */
    void VerifyByteCodesIntegrity() const;
    //@}

    /** 去除这个ZVM function的Debug info. */
    void StripDebugInfo();

    const CZVMObjectFile * GetOwnerObjectFile() const
    { return _pciOwnerObjectFile; }

    const zvm::CConstantPool * GetConstantPool() const
    { return _pciConstantPool; }

    const zvm::CNameAndSignatureReference * GetNameAndSignatureReference() const
    { return _pciNameAndSignatureReference; }

    bool DebugInfoStriped() const
    { return _bDebugInfoStriped; }

    UWORD GetParameterCount() const
    { return _uwParameterCount; }

    UWORD GetLocalVariableCount() const
    { return _uwLocalVariableCount; }

    const zvm::CInstruction * GetInstructionSequence() const
    { return _aciInstructionSequence; }

    /**
     * 根据所给指令的Index，得到该指令所属的源代码中的行号.
     *
     * @param iInstruction 指令Index.
     * @return 源代码行号.
     * @throw zfc::EInvalidState 如果Debug info已经被去除了，则throw出
     * 此exception.
     */
    TZVMIndex InstructionIndexToLineNumber(TZVMIndex iInstruction) const;
    TZVMIndex InstructionToLineNumber(const CInstruction * pciInstruction) const;

    /**
     * 将这条指令的内容按照pretty的格式dump到stdout.
     *
     * @throw zfc::EPanic 当CInstruction::_nInstructionCode或
     * CInstruction::_nOperandByteCount不合法时。但是如果ZLang compiler
     * 是正确无误的话，则这是一个"不可能的任务".
     */
    void DumpDetail() const;

    CZVMFunction(const CZVMObjectFile * pciOwnerObjectFile, zfc::CBinaryInputFileStream & bis);

    ~CZVMFunction();

    /**
     * 从CBinaryInputFileStream读入一个ZVM function.
     *
     * @throw zvm::EInvalidObjectFile 当读入的CInstruction::_nOperandByteCount不合法时.
     */
    friend zfc::CBinaryInputFileStream & operator>>(zfc::CBinaryInputFileStream & bis,
                                                    CZVMFunction & rci);

    friend zfc::CBinaryInputFileStream & operator>>(zfc::CBinaryInputFileStream & bis,
                                                    TLineNumberDebug & rsi);

    friend zfc::CBinaryInputFileStream & operator>>(zfc::CBinaryInputFileStream & bis,
                                                    TStackVariableDebug & rsi);
};


ZLS_END_NAMESPACE


#endif

