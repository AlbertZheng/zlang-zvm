/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CFunctionInvokeInterface.hpp,v $
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


#ifndef _ZLS_zvm_CFunctionInvokeInterface_hpp_
#define _ZLS_zvm_CFunctionInvokeInterface_hpp_

#include <zls/zfc/CBinaryString.hpp>
#include <zls/zvm/Manifest.hpp>
#include <zls/zvm/CSlot.hpp>
#include <zls/zvm/ZVMException.hpp>
#include <zls/zvm/CZVMFunction.hpp>
#include <zls/zvm/CVirtualMachine.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


// forward declaration
class CZVMVirtualThread;


/**
 * 一个面向C++的调用接口，它可以灵活地让用户在C++中调用ZVM function.
 */
class CFunctionInvokeInterface {
  private:
    enum TFunctionInvokeInterfaceState {
      STATE_DEFAULT = 0,  ///< 缺省状态.
      STATE_PREPARED,  ///< prepare结束.
      STATE_TIED_TO_VIRTUAL_THREAD, ///< 已被打结到某个ZVM virtual thread了.
      STATE_INVOKE_START  ///< 开始进行invoke.
    };

    TFunctionInvokeInterfaceState _eState;

    /**
     * @name Prepare Cache variables.
     */
    //@{
    std::string _stringFunctionName;

    /** 被打结到某个ZVM virtual thread. */
    CZVMVirtualThread * _pciTiedZVMVirtualThread;

    /**
     * 一个指向这个function在ZVM的global function register table中的位置的iterator.
     * @attention map::iterator不是易变性的，因此如果在创建出一个CFunctionInvokeInterface
     * instance后，又还对ZVM的global function register table进行了insert或erase等修改
     * 操作，则CFunctionInvokeInterface中已经取得的iterator不会失效！
     */
    const CGlobalFunctionRegisterEntry * _pciFunctionRegisterEntry;

    CSlot::TSlotTag _eReturnSlotTag;
    TZVMIndex _nArgumentsCount;
    const std::vector<CSlot::TSlotTag> * _pvectorArgumentsSlotTags;

    /**
     * 开始call这个function时stack需先调整几格.
     * @note 这个值=1(返回值，如果没有返回值的话则为0)+_nArgumentsCount(参数个数).
     */
    TZVMIndex _nStackAdjustedOffset;

    TLanguageTag _eLanguageTag;
    union {
      const CZVMFunction * _pciZVMFunction;
      TNativeFunction _pfuncNativeFunction;
    };
    //@}

    /**
     * @name Working period variables.
     */
    //@{
    CSlot * _pciReturnSlot;
    CSlot * _pciArgumentsBeginSlot;
    //@}

    const std::string & GetFunctionName() const;
    const std::string & GetFunctionSignature() const;
    const std::string & GetSourceFileName() const;
    const std::string & GetObjectFileName() const;

    /**
     * 检查这个Function invoke interface现在的状态是否正确.
     * @throw zfc::EInvalidState.
     */
    void CheckFunctionInvokeInterfaceState(
      const char * pszFileName,
      const char * pszFuncName,
      const int nLineNumber
    ) const;

    /**
     * @throw zfc::EOutOfRange.
     */
    void CheckArgumentRange(
      TZVMIndex iArgumentIndex,
      const char * pszFileName,
      const char * pszFuncName,
      const int nLineNumber
    ) const;

    /**
     * @throw zvm::EFunctionInvokeInterfaceException.
     */
    void CheckArgumentType(
      TZVMIndex iArgumentIndex,
      CSlot::TSlotTag ePassedTag,
      const char * pszFileName,
      const char * pszFuncName,
      const int nLineNumber
    ) const;

    /**
     * @throw zvm::EFunctionInvokeInterfaceException.
     */
    void CheckReturnType(
      CSlot::TSlotTag ePassedBufferTag,
      const char * pszFileName,
      const char * pszFuncName,
      const int nLineNumber
    ) const;

    /**
     * @throw zvm::EFunctionInvokeInterfaceException.
     */
    void CheckWhetherAllArgumentsPassed(
      const char * pszFileName,
      const char * pszFuncName,
      const int nLineNumber
    ) const;

    void ExecuteFunction();

  public:
    /**
     * 为能够调用某个ZVM function做一些预准备工作.
     *
     * @throw zvm::EFunctionInvokeInterfaceException 当ZVM的状态不合法、或这个
     * function不能被发现.
     */
    void PrepareForFunction(CZVMVirtualThread * pciZVMVirtualThread,
                            const std::string & rstringFunctionName);

    /**
     * 将这个Invoke Interface打结到被'PrepareForFunction()'设置的ZVM virtual thread.
     *
     * @throw zvm::EFunctionInvokeInterfaceException 当这个被打结的某个ZVM
     * virtual thread的ZVM stack不够Capacity来容纳result argument和所有的
     * arguments时.
     */
    void TieToZVMVirtualThread();

    /**
     * 按值参的方式传递"调用参数".
     *
     * @param iArgumentIndex 参数的Index，从1开始.
     * @param b 参数值.
     * @throw zvm::EFunctionInvokeInterfaceException 当参数类型与这个function
     * 需要的参数的类型不相同时.
     */
    void PassValueArgumentAsBool(TZVMIndex iArgumentIndex, bool b);

    void PassValueArgumentAsByte(TZVMIndex iArgumentIndex, UCHAR uch);
    void PassValueArgumentAsSDWORD(TZVMIndex iArgumentIndex, SDWORD sdw);
    void PassValueArgumentAsUDWORD(TZVMIndex iArgumentIndex, UDWORD udw);
    void PassValueArgumentAsSQWORD(TZVMIndex iArgumentIndex, SQWORD sqw);
    void PassValueArgumentAsUQWORD(TZVMIndex iArgumentIndex, UQWORD uqw);
    void PassValueArgumentAsDouble(TZVMIndex iArgumentIndex, double df);

    /**
     * 按值参的方式传递"调用参数".
     *
     * @param iArgumentIndex 参数的Index，从1开始.
     * @param pciString 参数值.
     * @throw zvm::EFunctionInvokeInterfaceException 当参数类型与这个function
     * 需要的参数的类型不相同时.
     */
    void PassValueArgumentAsStringObject(TZVMIndex iArgumentIndex, const CZVMString & rciString);
    void PassValueArgumentAsPPortObject(TZVMIndex iArgumentIndex, const CZVMPPort & rciPPort);
    void PassValueArgumentAsIPv4AddressObject(TZVMIndex iArgumentIndex, const CZVMIPv4Address & rciIPv4Address);
    void PassValueArgumentAsTableObject(TZVMIndex iArgumentIndex, const CZVMTable & rciTable);

    /**
     * 按引用参数的方式传递"调用参数".
     *
     * @param iArgumentIndex 参数的Index，从1开始.
     * @param rb 引用参数.
     * @throw zvm::EFunctionInvokeInterfaceException 当参数类型与这个function
     * 需要的参数的类型不相同时.
     * @attention 对于reference argument参数，我们为了效率，直接将用户传递给的指针的引用
     * push到ZVM stack上让ZVM function使用，因此用户传递给的指针的引用在
     * PassReferenceArgumentAs?()后，必须保持有效直至Invoke()被调用且执行完毕为止.
     */
    void PassReferenceArgumentAsBoolAddress(TZVMIndex iArgumentIndex, bool & rb);
    void PassReferenceArgumentAsByteAddress(TZVMIndex iArgumentIndex, UCHAR & ruch);
    void PassReferenceArgumentAsSDWORDAddress(TZVMIndex iArgumentIndex, SDWORD & rsdw);
    void PassReferenceArgumentAsUDWORDAddress(TZVMIndex iArgumentIndex, UDWORD & rudw);
    void PassReferenceArgumentAsSQWORDAddress(TZVMIndex iArgumentIndex, SQWORD & rsqw);
    void PassReferenceArgumentAsUQWORDAddress(TZVMIndex iArgumentIndex, UQWORD & ruqw);
    void PassReferenceArgumentAsDoubleAddress(TZVMIndex iArgumentIndex, double & rdf);

    /**
     * 按引用参数的方式传递"调用参数".
     *
     * @param iArgumentIndex 参数的Index，从1开始.
     * @param rpciString 引用参数.
     * @throw zvm::EFunctionInvokeInterfaceException 当参数类型与这个function
     * 需要的参数的类型不相同时.
     * @attention 对于reference argument参数，我们为了效率，直接将用户传递给的指针的引用
     * push到ZVM stack上让ZVM function使用，因此用户传递给的指针的引用在
     * PassReferenceArgumentAs?()后，必须保持有效直至Invoke()被调用且执行完毕为止.
     */
    void PassReferenceArgumentAsStringObjectAddress(TZVMIndex iArgumentIndex,
                                                    CZVMString *& rpciString);
    void PassReferenceArgumentAsIPv4AddressObjectAddress(TZVMIndex iArgumentIndex,
                                                         CZVMIPv4Address *& rpciIPv4Address);
    void PassReferenceArgumentAsPPortObjectAddress(TZVMIndex iArgumentIndex,
                                                   CZVMPPort *& rpciPPort);
    void PassReferenceArgumentAsTableObjectAddress(TZVMIndex iArgumentIndex,
                                                   CZVMTable * & rpciTable);

    /**
     * 调用具有返回值的ZVM function.
     *
     * @param rbReturnBuffer 一个用来接收返回值的buffer.
     * @throw zvm::EFunctionInvokeInterfaceException (1)当这个function实际上并没有返回值时,
     * (2)当这个function的还有某些参数还没被传递时.
     * @throw zvm::EZVMRuntimeException 当解释执行这个function发生了错误时.
     */
    void Invoke(bool & rbReturnBuffer);
    void Invoke(UCHAR & ruchReturnBuffer);
    void Invoke(SDWORD & rsdwReturnBuffer);
    void Invoke(UDWORD & rudwReturnBuffer);
    void Invoke(SQWORD & rsqwReturnBuffer);
    void Invoke(UQWORD & ruqwReturnBuffer);
    void Invoke(double & rdfReturnBuffer);

    void Invoke(CZVMString & rciReturnBuffer);
    void Invoke(CZVMPPort & rciReturnBuffer);
    void Invoke(CZVMIPv4Address & rciReturnBuffer);
    void Invoke(CZVMTable & rciReturnBuffer);

    /**
     * 调用没有返回值的ZVM function.
     *
     * @throw zvm::EFunctionInvokeInterfaceException (1)当这个function实际上有返回值时,
     * (2)当这个function的还有某些参数还没被传递时.
     * @throw zvm::EZVMRuntimeException 当解释执行这个function发生了错误时.
     */
    void Invoke();

    CFunctionInvokeInterface & operator=(const CFunctionInvokeInterface & rciOther);

    /** Copy Constructor. */
    CFunctionInvokeInterface(const CFunctionInvokeInterface & rciOther);

    /** Constructor. */
    CFunctionInvokeInterface();

    /** Destructor. */
    ~CFunctionInvokeInterface();
};


ZLS_END_NAMESPACE


#endif

