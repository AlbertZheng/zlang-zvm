/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/CCodeGeneratorHelper.hpp,v $
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


#ifndef _ZLS_zlang_CCodeGeneratorHelper_hpp_
#define _ZLS_zlang_CCodeGeneratorHelper_hpp_

#include <zls/zfc/Exception.hpp>
#include <zls/zfc/CBinaryOutputFileStream.hpp>
#include <zls/zfc/SmartPointer.hpp>
#include <zls/zvm/Manifest.hpp>
#include <zls/zvm/InstructionCode.hpp>
#include <zls/zlang/SymbolTable.hpp>
#include <zls/zlang/ConstantPool.hpp>
#include <zls/zlang/ZLangFunction.hpp>
#include <antlr/config.hpp>
#include <antlr/SemanticException.hpp>
#include <zls/zlang/ZLangCodeGeneratorTokenTypes.hpp>



/**
 * ZVM object file version 2.0文件的格式（采用网络字节序）：
 *
 *   UDWORD   : Magic Number = 0x19730122
 *   UWORD    : Major Version = 0x0200
 *   UWORD    : Minor Version = 0x0001
 *   TZVMIndex: count of elements in constant pool
 *   BYTES    : content of pool element 1
 *              content of pool element 2
 *              ......
 *   (pool element的格式：
 *     UWORD: element's tag
 *            CNilEndStringLiteral: UDWORD: length of string
 *                                  BYTES : content of string（不包括末尾的'\0')
 *            CBinaryStringLiteral: UDWORD: length of binary string
 *                                  BYTES : content of binary string（不包括末尾的'\0')
 *            CRopeStringLiteral: UDWORD: length of rope string
 *                                BYTES : content of rope string（不包括末尾的'\0')
 *            CSDWORDLiteral: SDWORD: literal
 *            CUDWORDLiteral: UDWORD: literal
 *            CDoubleLiteral: double: literal
 *            CPPortLiteral : UWORD: protocol type
 *                            PPORT: port number
 *            CIPv4AddressLiteral: UDWORD: IPv4 address/host-name string length
 *                                 BYTES : content of address string（不包括末尾的'\0')
 *                                 UDWORD: network mask
 *            CNameAndSignatureReference: TZVMIndex: name index
 *                                        TZVMIndex: signature index
 *            CGlobalVariableReference:     UCHAR: Is declared by extern(true or false)
 *                                      TZVMIndex: name and signature index
 *            CGlobalFunctionReference:     UCHAR: Is declared by extern(true or false)
 *                                      TZVMIndex: name and signature index
 *   )
 *
 *   TZVMIndex: Source file name index（A CNilEndStringLiteral reference)
 *
 *   [ global functions部分 ]
 *   TZVMIndex: count of global functions
 *   BYTES    : content of global function 1
 *              content of global function 2
 *              ......
 *   (每个CZLangFunction的格式：
 *     TZVMIndex: constant pool global/static function reference
 *     UWORD    : parameter count
 *     UWORD    : local variable count
 *
 *     [ 指令部分 ]
 *     TZVMIndex: count of instructions
 *     BYTES    : content of instruction 1
 *                content of instruction 2
 *                ......
 *     (每个CInstruction的格式：
 *       TZVMICode: instruction code
 *       UCHAR    : count of operands
 *       如果=0,则: 没有操作数;
 *       如果=1,则: a byte
 *       如果=2,则: two bytes
 *       如果>2,则: sizeof(TZVMIndex)个bytes
 *     )
 *
 *     [ 行号跟踪部分 ]
 *     TZVMIndex: count of line number debug info
 *     BYTES    : content
 *                ......
 *     (每个TLineNumberDebug的格式：
 *       TZVMIndex: from which instruction start
 *       TZVMIndex: line number
 *     )
 *
 *     [ stack variable跟踪部分 ]
 *     TZVMIndex: count of stack variable debug info
 *     BYTES    : content
 *                ......
 *     (每个TStackVariableDebug的格式：
 *       TZVMIndex: name and signature index
 *       TZVMIndex: Offset from BP
 *     )
 *   )
 *
 * @attention 如果将来TZVMIndex和PPort的typedef发生了改变，则ZVM Object file的
 * 版本号必须也进行改变.
 */



// Begin namespace 'zlang::'
ZLS_BEGIN_NAMESPACE(zlang)


/**
 * Zlang script支持的操作符.
 */
enum TZVMOperator {
  ZVM_OPERATOR_ASSIGN = ZLangCodeGeneratorTokenTypes::ASSIGN,
  ZVM_OPERATOR_NESTED_ASSIGN = ZLangCodeGeneratorTokenTypes::NESTED_ASSIGN,  // 2001/5/10: 被增加
  ZVM_OPERATOR_LOR = ZLangCodeGeneratorTokenTypes::LOR,
  ZVM_OPERATOR_LAND = ZLangCodeGeneratorTokenTypes::LAND,
  ZVM_OPERATOR_BOR = ZLangCodeGeneratorTokenTypes::BOR,
  ZVM_OPERATOR_BXOR = ZLangCodeGeneratorTokenTypes::BXOR,
  ZVM_OPERATOR_BAND = ZLangCodeGeneratorTokenTypes::BAND,
  ZVM_OPERATOR_NOT_EQUAL = ZLangCodeGeneratorTokenTypes::NOT_EQUAL,
  ZVM_OPERATOR_EQUAL = ZLangCodeGeneratorTokenTypes::EQUAL,
  ZVM_OPERATOR_LT = ZLangCodeGeneratorTokenTypes::LT_,
  ZVM_OPERATOR_GT = ZLangCodeGeneratorTokenTypes::GT,
  ZVM_OPERATOR_LE = ZLangCodeGeneratorTokenTypes::LE,
  ZVM_OPERATOR_GE = ZLangCodeGeneratorTokenTypes::GE,
  ZVM_OPERATOR_SL = ZLangCodeGeneratorTokenTypes::SL,
  ZVM_OPERATOR_SR = ZLangCodeGeneratorTokenTypes::SR,
  ZVM_OPERATOR_PLUS = ZLangCodeGeneratorTokenTypes::PLUS,
  ZVM_OPERATOR_MINUS = ZLangCodeGeneratorTokenTypes::MINUS,
  ZVM_OPERATOR_STAR = ZLangCodeGeneratorTokenTypes::STAR,
  ZVM_OPERATOR_DIV = ZLangCodeGeneratorTokenTypes::DIV,
  ZVM_OPERATOR_MOD = ZLangCodeGeneratorTokenTypes::MOD,
  ZVM_OPERATOR_INC = ZLangCodeGeneratorTokenTypes::INC,
  ZVM_OPERATOR_DEC = ZLangCodeGeneratorTokenTypes::DEC,
  ZVM_OPERATOR_UNARY_PLUS = ZLangCodeGeneratorTokenTypes::UNARY_PLUS,
  ZVM_OPERATOR_UNARY_MINUS = ZLangCodeGeneratorTokenTypes::UNARY_MINUS,
  ZVM_OPERATOR_BNOT = ZLangCodeGeneratorTokenTypes::BNOT,
  ZVM_OPERATOR_LNOT = ZLangCodeGeneratorTokenTypes::LNOT,
  ZVM_OPERATOR_CAST = ZLangCodeGeneratorTokenTypes::TYPECAST,
  ZVM_OPERATOR_ADVANCE_CAST = ZLangCodeGeneratorTokenTypes::ADVANCE_CAST,  // 2001/6/1: 被增加
  ZVM_OPERATOR_CALLING = ZLangCodeGeneratorTokenTypes::CALLING,
  ZVM_OPERATOR_DOT = ZLangCodeGeneratorTokenTypes::DOT,
  ZVM_OPERATOR_SUBSCRIPT = ZLangCodeGeneratorTokenTypes::SUBSCRIPT,                  // 取table元素的值
  ZVM_OPERATOR_SUBSCRIPT_ADDRESS = ZLangCodeGeneratorTokenTypes::SUBSCRIPT_ADDRESS,  // 取table元素的地址
  ZVM_OPERATOR_POST_INC = ZLangCodeGeneratorTokenTypes::POST_INC,
  ZVM_OPERATOR_POST_DEC = ZLangCodeGeneratorTokenTypes::POST_DEC
};


/**
 * 代码产生器的伴侣.
 *
 * @note 一些特殊statement的代码产生技巧：
 * <pre>
 * (1)return
 * 当碰到return语句时，ZLang compiler自动地将return语句转换为如下的两条语句：
 *     result-argument = <function要返回的东西>;
 *     return;
 *
 * (2)变量的初始化行
 * 当碰到"变量的初始化行"时，ZLang compiler总是自动地立即将"变量的初始化行"转换
 * 为一个expression计算和一个assign语句.
 *
 * (3)目前产生load?Address地址的指令只有：
 *    (a)ASSIGN的左值
 *    (b)SUBSCRIPT的左值
 *    (c)一元++、--
 *    (d)传递reference argument时
 *    (e)Object型变量计算时
 *
 * (4)reference argument的实现：
 * 为了能够让代码产生器知道function的某个参数要求的是reference argument，在ZLang
 * compiler为function产生function signature时，如果某个参数要求的是reference
 * argument，则让这个argument的signature采用小写形式，即function signature可能为
 * 类似"(sIp)V"的形式.
 *
 * </pre>
 *
 * @log
 * <pre>
 * 2001/5/15:
 * (1)引入类似pascal的reference argument。不采用C++的"&"作为reference
 * argument的参数原型申明是：因为对于table型参数比较难于决定"&"到底应该设计在参
 * 数申明中的哪个位置比较好.
 * 2001/7/21:
 * (1)'Logic AND' and 'Logic OR' are supported.
 * (2)对于'stringPlus'和'返回Object型数据类型的Function'，ZLang compiler现在采用
 * 自动产生临时变量的方案，以前整个ZVM中只有一个公用的string、ipaddress、pport、
 * table object register的方案是严重错误的.
 * </pre>
 *
 * @todo
 * <pre>
 * (1)对传递value argument产生的指令进行优化.
 * (2)在为Local variable initializing expression产生byte codes时，由于Symbol table
 * 是在pass2已经被生成了，这样在expression中就可能出现前面的变量却要使用还没被定义
 * 的后面的变量，而由于Symbol table却已经登记了这些后面的变量，因此能够被通过。一般
 * 情况下在ZVM实际解析运行这些Byte codes时不会出现问题，因为ZLang compiler总是将
 * 所有Local variable initializing expression的Byte codes放置在所有的Local variables
 * 被construct的Byte codes后面，但是如果被使用的没被定义的后面的变量是"Reference variable"，
 * 则会出现问题，因为此时这些后面的"Reference variable"的Initializing Byte Codes
 * 还没被执行，因此会出现在NULL Pointer（或非法内存）上进行操作的问题。
 *     我设想的改进办法是今后将pass2和pass3合并在一起.
 * </pre>
 *
 * @bug
 * <pre>
 * 2001/7/12:
 * (1)发现sqword类型兼容表有不正确，被修复了.
 * (2)发现table类型居然可以进行二元加等操作，被修复了.
 * </pre>
 */
class CCodeGeneratorHelper {
  public:
    /**
     * 表示一个expression中的一个"原子".
     *
     * @note 当CCodeGeneratorHelper::GenerateExpressionInstructionBackend()在为一个ZLang
     * Expression产生指令时，它被需要传递一个描述这个Expression的"表达式原子队列"，
     * 这个队列的格式是"操作符 左操作数 右操作数"，如果"左"、"右"操作数还是一个
     * Expression，则队列可以变成不断嵌套的形式，即好似：
     * <pre>
     *       "操作符1 操作符2 左操作数 右操作数 操作符3 左操作数 右操作数"
     * </pre>
     * 任何一个操作数都可不断嵌套，但是这个队列最终必须是饱和的，即操作符和操作数
     * 最终必须是匹配的，当队列被pop到达空时，这个Expression的指令产生应该正好结束.
     */
    struct TExpressionAtom {
      /** "原子"的类型. */
      enum TAtomTag {
        tatOPERATOR = 1,  ///< 是个"操作符".
        tatOPERAND        ///< 是个"操作数".
      };

      TAtomTag eTag;                ///< 这个"原子"的类型.
      int nTokenType;               ///< 这个"原子"的Lex-Token-Type.
      std::string stringTokenText;  ///< 这个"原子"的Lex-Token-Text.

      int nLineNumber;         ///< 这个Lex-Token-Text在源代码中的行号.
      int nColumnNumber;       ///< 这个Lex-Token-Text在源代码中的列号.

      TExpressionAtom()
      { }

      TExpressionAtom(const TExpressionAtom & rtOther)
      {
        operator=(rtOther);
      }

      TExpressionAtom & operator=(const TExpressionAtom & rtOther)
      {
        eTag = rtOther.eTag;
        nTokenType = rtOther.nTokenType;
        stringTokenText = rtOther.stringTokenText;
        nLineNumber = rtOther.nLineNumber;
        nColumnNumber = rtOther.nColumnNumber;
        return(*this);
      }
    };

    /**
     * 定义"类型兼容"表中的一列.
     */
    struct TCompatibleTableColumn {
      /**
       * 如果stringRightSignature为"V"，则表示让左值成为一元操作符的操作数，
       * 不需要考虑右值.
       */
      std::string  stringRightSignature;  ///< 如果"右值"的类型signature是这种.
      int          nOperatorCount;        ///< 则有几种"操作符"被允许运用在这种"左值"和这种"右值".
      int        * anOperators;           ///< 这几种"操作符"分别是什么.
    };

    /**
     * 定义"类型兼容"表中的一行.
     */
    struct TCompatibleTableLine {
      std::string              stringLeftSignature;  ///< 如果"左值"的类型signature是这种.
      int                      nColumnCount;         ///< 则有几列"类型兼容"定义.
      TCompatibleTableColumn * atColumns;            ///< 这几列"类型兼容"定义分别是什么.
    };

  private:
    /** "类型兼容"表. */
    static TCompatibleTableLine _SasiSignatureCompatibleTable[];
    /** "类型兼容"表的行数. */
    static int _SnLineCountOfSignatureCompatibleTable;

    /** Codes generating period working variables. */
    int _nLatestLineNumberDebug;

    /**
     * 指示为带有临时local variable offset的指令Mark上需要以后进一步被Fix的标志，
     * 因为这个offset是不正确的（只出现在Local variable initializing expression时）.
     */
    bool _bSwitchOfNeedFixTempLocalVariableOffset;  //< 2001/7/21: Added

    /** 当前正在被产生代码的ZLangFunction中的temp variable allocator. */
    //CZLangFunction::TempVariableAllocator * _pciCurrentTempVariableAllocator;

    enum TVariableInstructionTag {
      /** 指示产生取值指令（取一个value，然后push到ZVM stack顶）. */
      VARIABLE_INSTRUCTION_TAG_LOAD_VALUE,

      /**

       * 指示产生取地址指令（取一个address，然后push到ZVM stack顶），返回的

       * signature为大写的形式表示这个address将作为一个value operand来被接下

       * 来的指令使用.

       */

      VARIABLE_INSTRUCTION_TAG_LOAD_ADDRESS_AS_VALUE_OPERAND,

      /** 指示产生store指令. */

      VARIABLE_INSTRUCTION_TAG_STORE,

      /** 指示产生nested store指令. */

      VARIABLE_INSTRUCTION_TAG_NESTED_STORE,

      /** 指示产生（return statement）的store指令. */

      VARIABLE_INSTRUCTION_TAG_RETURN_PSEUDO_STORE,

      /**

       * 指示产生取地址指令（取一个address，然后push到ZVM stack顶），返回的

       * signature为小写的形式表示这个address将作为一个reference address

       * operand来被接下来的指令使用.

       */

      VARIABLE_INSTRUCTION_TAG_LOAD_ADDRESS_AS_REFERENCE_ADDRESS_OPERAND,

      /** 指示产生assign reference address指令. */

      VARIABLE_INSTRUCTION_TAG_REFERENCE_ADDRESS_ASSIGN

    };


    /**
     * 为表达式产生相应的指令.
     *
     * @return 表达式结果的类型signature.
     * @throw antlr::SemanticException.
     */
    std::string _GenerateExpressionInstructionBackend(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms);

    /**
     * 为IDENTIFIER产生指令的Backend.
     *
     * @return 类型signature.
     */
    std::string _GenerateVariableInstructionBackend(
                           CInstructionContainer_auto autoCurrentInstructionContainer,
                           int nLineNumberDebug,
                           const std::string & rstringName,
                           const CSymbolAttributes_auto & rautoSymbolAttributes,
                           TVariableInstructionTag eInstructionTag);

    /**
     * 为IDENTIFIER产生取值指令的Backend.
     *
     * @return 类型signature.
     * @attention
     * <pre>
     * (1)对于reference argument，则要产生indirect load value指令.
     * </pre>
     */
    std::string _GenerateLoadValueInstructionBackend(
                          CInstructionContainer_auto autoCurrentInstructionContainer,
                          int nLineNumberDebug,
                          const std::string & rstringName,
                          const CSymbolAttributes_auto & rautoSymbolAttributes);

    /**
     * 为IDENTIFIER产生取地址指令（结果作为一个value operand）的Backend.
     *
     * @return 类型signature.
     * @attention
     * <pre>
     * (1)对于reference variable，则要产生load reference to address指令.
     * </pre>
     */
    std::string _GenerateLoadAddressAsValueOperandInstructionBackend(
                          CInstructionContainer_auto autoCurrentInstructionContainer,
                          int nLineNumberDebug,
                          const std::string & rstringName,
                          const CSymbolAttributes_auto & rautoSymbolAttributes);

    /**
     * 为IDENTIFIER产生取地址指令（结果作为一个reference address operand）的Backend.
     *
     * @return 类型signature.
     * @attention
     * <pre>
     * (1)对于reference variable，则要产生load reference to address指令.
     * </pre>
     */
    std::string _GenerateLoadAddressAsReferenceAddressOperandInstructionBackend(
                          CInstructionContainer_auto autoCurrentInstructionContainer,
                          int nLineNumberDebug,
                          const std::string & rstringName,
                          const CSymbolAttributes_auto & rautoSymbolAttributes);

    void _GenerateTypeCastInstructionBackend(CInstructionContainer_auto autoFunction,
                                             int nLineNumberDebug,
                                             const std::string & rstringFromSignature,
                                             const std::string & rstringToSignature);

    bool _SignatureIsCompatibleBackend(const std::string & rstringLeftSignature,
                                       const std::string & rstringRightSignature,
                                       int nOperatorTokenType);

    CSymbol_auto _FindFunctionSymbol(int nLineNumberDebug,
                                     int nColumnNumberDebug,
                                     const std::string & rstringFunctionName);

    CSymbol_auto _FindVariableSymbol(int nLineNumberDebug,
                                     int nColumnNumberDebug,
                                     const std::string & rstringName,
                                     const std::vector<std::string> & rvectorNameSpace);

  protected:
    CSymbolTable * _pciSymbolTable;        ///< 符号表
    std::string    _stringSourceFileName;  ///< 被编译的源文件名

    /**
     * @name 要写入Object file的东西.
     */
    //@{
    static const UDWORD _SudwMagicNumber = zvm::CudwZVM_MAGIC_NUMBER;
    static const UWORD  _SuwMajorVersion = zvm::CuwZVM_MAJOR_VERSION;
    static const UWORD  _SuwMinorVersion = zvm::CuwZVM_MINOR_VERSION;
    CConstantPool _ciConstantPool;
    zvm::TZVMIndex _nSourceFileNameIndex;
    std::deque<CInstructionContainer_auto> _dequeGlobalFunctions;
    //@}

  public:
    /**
     * Constructor which should not be called.
     *
     * @throw zfc::EPanic
     */
    CCodeGeneratorHelper();

    /**
     * Constructor.
     */
    CCodeGeneratorHelper(const std::string & rstringSourceFileName,
                         CSymbolTable * pciSymbolTable)
      : _stringSourceFileName(rstringSourceFileName),
        _pciSymbolTable(pciSymbolTable),
        _nLatestLineNumberDebug(0),
        _bSwitchOfNeedFixTempLocalVariableOffset(false)
    {
      _nSourceFileNameIndex = _ciConstantPool.InsertNilEndStringLiteral(rstringSourceFileName);
    }

    void TurnOnSwitchOfNeedFixTempLocalVariableOffset()
    { _bSwitchOfNeedFixTempLocalVariableOffset = true; }

    void TurnOffSwitchOfNeedFixTempLocalVariableOffset()
    { _bSwitchOfNeedFixTempLocalVariableOffset = false; }

    /**
     * @name 编译错误报告methods.
     */
    //@{
    /**
     * 如果某些操作符的"左值"必须是变量，但在语义分析过程中却发现不是，则报告此错误.
     * 通常用于:
     * (1) 二元操作符"="、"[]"（对table元素进行操作）
     * (2) 一元操作符"++"、"--"
     */
    void ThrowSemanticError_NonLeftValue(
      const TExpressionAtom & rsiOperator
    ) const;

    /**
     * 如果二元操作符的"左值"、"右值"的类型不兼容，则报告此错误.
     */
    void ThrowSemanticError_InvalidOperandsToBinaryOperator(
      const TExpressionAtom & rsiOperator,
      const TExpressionAtom & rsiLeftOperand,
      const TExpressionAtom & rsiRightOperand,
      const std::string & rstringLeftOperandSignature,
      const std::string & rstringRightOperandSignature
    ) const;

    /**
     * 如果一元操作符的"左值"的类型不合法，则报告此错误.
     */
    void ThrowSemanticError_InvalidOperandToUnaryOperator(
      const TExpressionAtom & rsiOperator,
      const TExpressionAtom & rsiOperand,
      const std::string & rstringOperandSignature
    ) const;

    /**
     * 如果不能进行Cast，则报告此错误.
     */
    void ThrowSemanticError_InvalidCast(
      const TExpressionAtom & rsiOperator,
      const TExpressionAtom & rsiRightOperand,
      const std::string & rstringRightOperandSignature,
      const std::string & rstringCastToSignature
    ) const;

    /**
     * 如果在产生函数调用时，发现"左值"(函数名)不是Literal，则报告此错误.
     */
    void ThrowSemanticError_InvalidFunctionName(
      const TExpressionAtom & rsiLeftOperand
    ) const;

    /**
     * 如果在产生函数调用时，通过查找Symbol table发现"左值"Symbol不是函数名，则报告此错误.
     */
    void ThrowSemanticError_SymbolIsNotFunction(
      int nErrorLineNumber,
      int nErrorColumnNumber,
      CSymbol::TSymbolTag eSymbolTag,
      const std::string & rstringSymbolName
    ) const;

    /**
     * 如果在产生函数调用、取值（地址）时，通过查找Symbol table发现"左值"Symbol没有被定义，则报告此错误.
     */
    void ThrowSemanticError_UndeclaredSymbol(
      int nErrorLineNumber,
      int nErrorColumnNumber,
      const std::string & rstringSymbolName
    ) const;

    /**
     * 如果在产生函数调用时，发现调用参数(s)的类型不兼容函数定义，则报告此错误.
     */
    void ThrowSemanticError_PassIncompatibleArguments(
      const TExpressionAtom & rsiOperator,
      const std::string & rstringFunctionName,
      const std::string & rstringFunctionSignature,
      const std::string & rstringPassedArgumentsSignature
    ) const;

    /**
     * 如果在产生取值（地址）指令时，通过查找Symbol table发现"左值"Symbol不是global
     * variable、local variable或parameter时，则报告此错误.
     */
    void ThrowSemanticError_SymbolIsNotVariable(
      int nErrorLineNumber,
      int nErrorColumnNumber,
      CSymbol::TSymbolTag eSymbolTag,
      const std::string & rstringSymbolName
    ) const;

    /**
     * 如果SUBSCRIPT操作的"左值"不是一个table变量，则报告此错误.
     */
    void ThrowSemanticError_InvalidLeftOperandToTableSubscript(
      const TExpressionAtom & rsiLeftOperand
    ) const;

    /**
     * 如果SUBSCRIPT操作的"右值"还是一个table或是一个void返回时，则报告此错误.
     */
    void ThrowSemanticError_InvalidRightOperandToTableSubscript(
      const TExpressionAtom & rsiRightOperand,
      const char * pszCanNotBeWhat
    ) const;

    /**
     * 如果function有返回值，但是代码中却没有return语句，或return返回的类型不兼容，则报告此错误.
     */
    void ThrowSemanticError_ReturnStatementIsRequired(
      int nNearLineNumber,
      const std::string & rstringFunctionName,
      const std::string & rstringFunctionReturnSignature
    ) const;

    /**
     * 如果function是void返回，但是代码中却有return(类型)语句，则报告此错误.
     */
    void ThrowSemanticError_ReturnIsNotAllowed(
      int nNearLineNumber,
      const std::string & rstringFunctionName
    ) const;

    /**
     * 如果在IPv4 Literal中CIDR的mask bits不合法（<1或>32），则报告此错误.
     */
    void ThrowSemanticError_InvalidCIDRMask(
      int nErrorLineNumber,
      int nErrorColumnNumber,
      const zfc::EOutOfRange & e
    ) const;

    /**
     * 当一个function的参数要求是个reference argument时，如果调用者却妄想将一个
     * expression作为reference argument来传递，则此错误.
     */
    void ThrowSemanticError_CanNotPassExpressionAsReferenceArgument(
      const CCodeGeneratorHelper::TExpressionAtom & rsiOperand,
      const std::string & rstringReferenceArgumentSignature
    ) const;

    /**
     * 如果一个expression statement是不被允许的，则此错误.
     * @note 仅仅允许'ASSIGN'、'++/--'、'function calling' expression as a single statement line.
     */
    void ThrowSemanticError_InvalidExpressionStatement(
      int nErrorLineNumber,
      int nErrorColumnNumber
    ) const;

    /**
     * 如果一个testing expression statement是不被允许的，则此错误.
     * @note testing expression statement必须有操作结果被push到ZVM stack上.
     */
    void ThrowSemanticError_InvalidTestingExpressionStatement(
      int nErrorLineNumber,
      int nErrorColumnNumber
    ) const;

    /**
     * 如果Reference variable没有被初始化，则报告此错误.
     */
    void ThrowSemanticError_ReferenceVariableMustBeInitialized(
      int nErrorLineNumber,
      int nErrorColumnNumber,
      const std::string & rstringVariableName,
      const std::string & rstringVariableSignature
    ) const;

    /**
     * 如果reference variable的initializer不合法，则报告此错误.
     */
    void ThrowSemanticError_InvalidReferenceVariableInitializer(
      const TExpressionAtom & rsiRightOperand
    ) const;
    //@}

    /**
     * @name Get方法.
     */
    //@{
    /** 得到Constant pool. */
    CConstantPool & GetConstantPool()
    {
      return(_ciConstantPool);
    }
    //@}

    /** 产生类似"opcode"这种没有操作数的指令. */
    zvm::TZVMIndex GenerateInstruction(CInstructionContainer_auto autoCurrentInstructionContainer,
                                       int nLineNumberDebug,
                                       zvm::TZVMICode uchInstructionCode);

    /** 产生类似"opcode byte"这种单字节操作数的指令. */
    zvm::TZVMIndex GenerateInstruction(CInstructionContainer_auto autoCurrentInstructionContainer,
                                       int nLineNumberDebug,
                                       zvm::TZVMICode uchInstructionCode,
                                       UCHAR uchOperand);

    /** 产生类似"opcode uword"这种双字节操作数的指令. */
    zvm::TZVMIndex GenerateInstruction(CInstructionContainer_auto autoCurrentInstructionContainer,
                                       int nLineNumberDebug,
                                       zvm::TZVMICode uchInstructionCode,
                                       UWORD uwOperand);

    /** 产生类似"opcode sword"这种双字节操作数的指令. */
    zvm::TZVMIndex GenerateInstruction(CInstructionContainer_auto autoCurrentInstructionContainer,
                                       int nLineNumberDebug,
                                       zvm::TZVMICode uchInstructionCode,
                                       SWORD swOperand);

    /** 产生类似"opcode index"这种四字节操作数的指令. */
    zvm::TZVMIndex GenerateInstruction(CInstructionContainer_auto autoCurrentInstructionContainer,
                                       int nLineNumberDebug,
                                       zvm::TZVMICode uchInstructionCode,
                                       zvm::TZVMIndex nIndex);

    /** 产生类似"opcode udword"这种四字节操作数的指令. */
    zvm::TZVMIndex GenerateInstruction(CInstructionContainer_auto autoCurrentInstructionContainer,
                                       int nLineNumberDebug,
                                       zvm::TZVMICode uchInstructionCode,
                                       UDWORD udwOperand);

    /** 插入类似"opcode"这种没有操作数的指令. */
    zvm::TZVMIndex InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                           CInstructionContainer_auto autoCurrentInstructionContainer,
                                           int nLineNumberDebug,
                                           zvm::TZVMICode uchInstructionCode);

    /** 插入类似"opcode byte"这种单字节操作数的指令. */
    zvm::TZVMIndex InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                           CInstructionContainer_auto autoCurrentInstructionContainer,
                                           int nLineNumberDebug,
                                           zvm::TZVMICode uchInstructionCode,
                                           UCHAR uchOperand);

    /** 插入类似"opcode uword"这种双字节操作数的指令. */
    zvm::TZVMIndex InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                           CInstructionContainer_auto autoCurrentInstructionContainer,
                                           int nLineNumberDebug,
                                           zvm::TZVMICode uchInstructionCode,
                                           UWORD uwOperand);

    /** 插入类似"opcode sword"这种双字节操作数的指令. */
    zvm::TZVMIndex InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                           CInstructionContainer_auto autoCurrentInstructionContainer,
                                           int nLineNumberDebug,
                                           zvm::TZVMICode uchInstructionCode,
                                           SWORD swOperand);

    /** 插入类似"opcode index"这种四字节操作数的指令. */
    zvm::TZVMIndex InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                           CInstructionContainer_auto autoCurrentInstructionContainer,
                                           int nLineNumberDebug,
                                           zvm::TZVMICode uchInstructionCode,
                                           zvm::TZVMIndex nIndex);

    /** 插入类似"opcode udword"这种四字节操作数的指令. */
    zvm::TZVMIndex InsertInstructionBefore(zvm::TZVMIndex nBeforePosition,
                                           CInstructionContainer_auto autoCurrentInstructionContainer,
                                           int nLineNumberDebug,
                                           zvm::TZVMICode uchInstructionCode,
                                           UDWORD udwOperand);

    /**
     * 为某个新的ZLang global function产生一些开始的byte code、参数Debug-Info和
     * 插入必需的reference到Constant pool中.
     */
    void PrepareGlobalFunctionFramework(
      CInstructionContainer_auto autoCurrentInstructionContainer,
      int nLineNumberDebug,
      const std::vector<std::string> & rvectorFindNames,
      const std::string & rstringFunctionName,
      const std::string & rstringFunctionSignature,
      const std::vector<std::pair<std::string, std::string> > & rpairParameters,
      zvm::TAccessModifierTag eAccessModifierTag
    );

    /**
     * 为表达式产生相应的指令.
     *
     * @return 表达式结果的类型signature.
     * @throw antlr::SemanticException.
     * @attention GenerateExpressionInstructionBackend()一次只能产生一条完整的ZLang expression，
     * 如果有多条expression需要产生代码，则必须调用GenerateExpressionInstructionBackend()多次.
     */
    std::string GenerateExpressionInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms);

    /**
     * 为ASSIGN表达式产生相应的指令.
     *
     * @return 表达式结果（即左操作数）的类型signature.
     * @throw antlr::SemanticException.
     * @attention
     * <pre>
     * (1)对于ASSIGN的左值，必须产生load address指令.
     * (2)由于(1)，因此ASSIGN的左值只能是IDENTIFIER或Table SUBSCRIPT操作.
     * (3)当ASSIGN的左Operand是IDENTIFIER时，要记得虽然此时左Operand的指令先
     * 于右Operand的指令而被产生，但是由于store到非table-element的指令是带一个指令
     * 操作数（variable的index）的，因此当append instruction到autoCurrentFunction
     * 时要先append右Operand的，然后才是左Operand的.
     * (4)当ASSIGN的左Operand是SUBSCRIPT时，要记得将其偷改为SUBSCRIPT_ADDRESS，以
     * 告诉说要产生的是table-element的地址.
     * (5)如果右操作数又是一个ASSIGN操作的结果，则需先偷偷将这个ASSIGN改为NESTED_ASSIGN.
     * </pre>
     */
    std::string GenerateAssignExpressionInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms);

    /**
     * 为二元表达式产生相应的指令.
     *
     * @return 表达式结果（即左操作数）的类型signature.
     * @throw antlr::SemanticException.
     */
    std::string GenerateBinaryExpressionInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms);

    /**
     * 为一元表达式产生相应的指令.
     *
     * @return 表达式结果（即左操作数）的类型signature.
     * @throw antlr::SemanticException.
     * @attention
     * <pre>
     * (1)如果是"++/--"操作符，操作数必须是变量.
     * (2)如果是"++/--"操作符，必须产生取地址指令.
     * </pre>
     */
    std::string GenerateUnaryExpressionInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms);

    /**
     * 为TYPECAST表达式产生相应的指令.
     *
     * @return 表达式结果（即左操作数）的类型signature.
     * @throw antlr::SemanticException.
     */
    std::string GenerateTypeCastExpressionInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms);

    /**
     * 为INDEX_OPERATION表达式产生相应的指令.
     *
     * @return table的元素的类型signature.
     * @throw antlr::SemanticException.
     */
    std::string GenerateSubscriptExpressionInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms);

    /**
     * 为CALLING表达式产生calling before和after sequence的相应的指令.
     *
     * @return 被调用的function的类型signature.
     * @throw antlr::SemanticException.
     */
    std::string GenerateCallingSequenceExpressionInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms);

    /**
     * 为IDENTIFIER产生取值或取地址指令.
     *
     * @return 类型signature.
     * @throw antlr::SemanticException.
     * @attention
     * <pre>
     * (1)对于string等object型variable，则要产生load address指令.
     * (2)对于简单型variable，则要产生load value指令.
     * </pre>
     */
    std::string GenerateLoadInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms);

    /**
     * 为IDENTIFIER产生取值指令.
     *
     * @return 类型signature.
     * @throw antlr::SemanticException.
     */
    std::string GenerateLoadValueInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms);

    /**
     * 产生"loadAddressGlobal/Field/BP index"指令.
     *
     * 先将查找符号表，猜测它是local variable，或是parameter，或是field，或是
     * global variable，然后插入constant pool相应的field-reference或
     * global-variable-reference，最后再产生指令.
     *
     * @return IDENTIFIER的signature.
     * @throw antlr::SemanticException.
     */
    std::string GenerateLoadAddressAsValueOperandInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms);

    /**
     * 产生"loadAddressGlobal/Field/BP index"指令.
     *
     * 先将查找符号表，猜测它是local variable，或是parameter，或是field，或是
     * global variable，然后插入constant pool相应的field-reference或
     * global-variable-reference，最后再产生指令.
     *
     * @return IDENTIFIER的signature.
     * @throw antlr::SemanticException.
     */
    std::string GenerateLoadAddressAsReferenceAddressOperandInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                const std::vector<std::string> & rvectorFindNames,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms);

    /**
     * 为literal constant产生取值指令.
     *
     * @return 类型signature.
     * @throw antlr::SemanticException.
     */
    std::string GenerateLoadConstantValueInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms);

    /**
     * 为literal constant产生取地址指令.
     *
     * @return 类型signature.
     * @throw antlr::SemanticException.
     */
    std::string GenerateLoadConstantAddressInstruction(
                                CInstructionContainer_auto autoCurrentInstructionContainer,
                                std::deque<TExpressionAtom> & rdequeExpressionAtoms);

    /**
     * 产生"call pool_index"指令.
     *
     * 先将查找符号表，猜测它static或global function，然后插入constant
     * pool相应的static或global-function-reference，最后再产生指令.
     *
     * @return 返回的signature.
     * @throw antlr::SemanticException.
     */
    std::string GenerateCallInstruction(CInstructionContainer_auto autoCurrentInstructionContainer,
                                   int nLineNumberDebug,
                                   int nColumnNumberDebug,
                                   const std::vector<std::string> & rvectorFindNames,
                                   const std::string & rstringFunctionName);

    /**
     * 为function prepare sequence产生"constructLocalVariable"指令.
     *
     * @param nTheVariableIndex >=1.
     */
    void GenerateConstructLocalVariableInstruction(CInstructionContainer_auto autoCurrentInstructionContainer,
                                                   int nLineNumberDebug,
                                                   const std::vector<std::string> & rvectorFindNames,
                                                   const std::string & rstringName,
                                                   const std::string & rstringSignature,
                                                   int nTheVariableIndex);

    /**
     * 如果发现"左"、"右"类型不兼容，则尝试自动添加cast指令，如果不能进行cast则返回false.
     *
     * @attention rstringLeftSignature和rstringRightSignature可能被修改（如果可以cast的话）.
     */
    bool BackPatchCastInstructionIfIncompatible(std::string & rstringLeftSignature,
                                                CInstructionContainer_auto & rautoLeftOperandFunction,
                                                std::string & rstringRightSignature,
                                                CInstructionContainer_auto & rautoRightOperandFunction,
                                                const TExpressionAtom & rtOperator);

    /**
     * 为function添加stack variable debug info.
     * @note 先插入一个name-and-signature-reference，然后再添加stack variable debug info.
     */
    void AppendStackVariableDebugInfo(CInstructionContainer_auto autoCurrentInstructionContainer,
                                      const std::vector<std::string> & rvectorFindNames,
                                      const std::string & rstringName,
                                      const std::string & rstringSignature);

    /**
     * 检查两种类型（的操作数）能否进行某项操作.
     * @param rstringLeftSignature 左signature.
     * @param rstringRightSignature 右signature.
     * @param nOperatorTokenType 操作符.
     * @return false or true表示兼容否.
     *
     * @note
     * (1) 如果是非SUBSCRIPT操作，且只要其中一个signature为"[X"，则两个signature都必
     *     须为相同的"[X"，且这时只允许"="、"=="、"!="操作;
     * (2) 如果是SUBSCRIPT操作，则左signature必须为"[."，右signature只要不是"[."即可，
     *     这时都返回true;
     * (3) 如果右signature为"V"，则表示测试的是对左操作数允许什么样的一元操作符;
     * (4) 如果是CALLING操作，要做特殊分析.
     *
     * @todo
     * (1)对于CALLING操作，目前只处理调用参数完全匹配的情况，以后有时间再处理
     * 可隐含cast.
     * (2)对于CALLING操作，如果发现调用参数的类型不兼容的情况下，提示信息能否更
     * 准确点，即告知是第几个参数不兼容的.
     */
    bool SignatureIsCompatible(const std::string & rstringLeftSignature,
                               const std::string & rstringRightSignature,
                               int nOperatorTokenType);

    /**
     * 将Byte codes内容按照pretty的格式dump到stdout.
     *
     * @throw zfc::EPanic 当CInstruction::_uchInstructionCode或
     * CInstruction::_uchOperandByteCount不合法时。但是如果ZLang compiler
     * 是正确无误的话，则这是一个"不可能的任务".
     */
    void DumpDetail() const;

    /**
     * 将Byte codes写入CBinaryOutputFileStream.
     *
     * @throw zfc::EPanic 当CInstruction::_uchOperandByteCount不合法时。
     * 但是如果ZLang compiler是正确无误的话，则这是一个"不可能的任务".
     */
    friend zfc::CBinaryOutputFileStream & operator << (zfc::CBinaryOutputFileStream & bos,
                                                       const CCodeGeneratorHelper & rciHelper);
};


ZLS_END_NAMESPACE


#endif

