/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CZVMVirtualThread.hpp,v $
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


#ifndef _ZLS_zvm_CZVMVirtualThread_hpp_
#define _ZLS_zvm_CZVMVirtualThread_hpp_

#include <zls/zvm/Manifest.hpp>
#include <zls/zvm/ConstantPool.hpp>
#include <zls/zvm/InstructionCode.hpp>
#include <zls/zvm/CInstruction.hpp>
#include <zls/zvm/CSlot.hpp>
#include <zls/zvm/ZVMException.hpp>
#include <zls/zvm/CZVMFunction.hpp>
#include <zls/zvm/ZVMRegister.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


#ifdef ENABLE_ZVM_DEBUG
  #define ZVM_STACK_ASSERT(pciVirtualThread, eTag, pszFile, pszFunc, nLine)       \
    pciVirtualThread->StackAssert(eTag, pszFile, pszFunc, nLine)
#else
  #define ZVM_STACK_ASSERT(pciVirtualThread, eTag, pszFile, pszFunc, nLine)
#endif


// forward declaration
class CVirtualMachine;
class CFunctionInvokeInterface;


/**
 * 该类抽象了一个ZVM中的虚拟Thread.
 *
 * @attention 对CZVMVirtualThread的优化方法：
 * <pre>
 * (1)当ENABLE_ZVM_OPTIMIZATION == 1时：
 *    (a)对Instruction dictionary采用"用空间换取速度"，直接采用一级查表定位的方法，
 *       而不再象以前那样采用二级查表的方法.
 *       注：采用这个优化后速度提高了(1 - (1678毫秒/2087毫秒)%) = 20%.
 *    (b)对PC register进行预cache，即每次PC register改变了后就立即取出其内部的
 *       "CInstruction *"和"CConstantPool *"的值到CZVMVirtualThread的内部member
 *       variables中，然后这样Instruction interpreter的速度应该还能再快些了.
 * (2)当ENABLE_ZVM_OPTIMIZATION == 2时：
 *   (a)对CZVMVirtualThread中的Pop?()、Top?()等methods采用inline.
 *   (b)对二元操作进行优化，只pop出右operand，然后直接在左operand上进行二元操作，
 *      这样可节省一次pop.
 *   (c)对一元操作也进行类似的优化.
 * </pre>
 */
class CZVMVirtualThread {
  friend class CVirtualMachine;
  friend class CFunctionInvokeInterface;

  private:
    /**
     * Constructor.
     * @note Only can be invoked by 'CVirtualMachine'.
     */
    CZVMVirtualThread(CVirtualMachine * pciOwnerZVM);

    /**
     * Destructor.
     * @note Only can be invoked by 'CVirtualMachine'.
     */
    ~CZVMVirtualThread();

  private:
    /**
     * @name Set by constructor.
     */
    //@{
    /** 创建这个Virtual thread的Virtual Machine instance. */
    CVirtualMachine * _pciOwnerZVM;

    /** Stack的Capacity. */
    TZVMIndex _nStackCapacity;

    /**
     * ZVM stack for this virtual thread.
     * @note Stack Low-water和High-water都空着不被使用，只是用来判断警戒位而已.
     */
    CSlot * _aciStack;

    /** The highest address possible for this stack. */
    CSlot * _pciStackHighWater;
    //@}

    /**
     * @name ZVM的寄存器.
     */
    //@{
    /**
     * SP register.
     * @note SP register总是指向位于当前Stack top的那个元素.
     */
    CSlot * _pciSPRegister;

    /** BP register. */
    CSlot * _pciBPRegister;

    /** PC register. */
    CPCRegister _ciPCRegister;
    //@}

    CSlot * GetGlobalVariableSlot();
    CSlot * GetStackVariableSlot();

    /**
     * @name SP register操作.
     */
    //@{
    CSlot * PrefixIncreaseSPRegister()
    {
      static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSPRegister::PrefixIncreaseSPRegister()");
      if (++_pciSPRegister >= _pciStackHighWater)
      {
        throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "ZVM stack overflow");
      }
      return _pciSPRegister;
    }

    CSlot * PostfixIncreaseSPRegister()
    {
      static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSPRegister::PostfixIncreaseSPRegister()");
      CSlot * pciTmp = _pciSPRegister++;
      if (_pciSPRegister >= _pciStackHighWater)
      {
        throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "ZVM stack overflow");
      }
      return pciTmp;
    }

    #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
      #define PrefixDecreaseSPRegister()      --_pciSPRegister
      #define PostfixDecreaseSPRegister()     _pciSPRegister--
    #else
      CSlot * PrefixDecreaseSPRegister()
      {
        return --_pciSPRegister;
        /* 应该不用再判断underflow吧，因为只有以前有push，才会有pop.
        static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSPRegister::PrefixDecreaseSPRegister()");
        if (--_pciSPRegister < _aciStack)
        {
          throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "ZVM stack underflow");
        }
        return _pciSPRegister;
        */
      }

      CSlot * PostfixDecreaseSPRegister()
      {
        return _pciSPRegister--;
        /* 应该不用再判断underflow吧，因为只有以前有push，才会有pop.
        static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSPRegister::PostfixDecreaseSPRegister()");
        CSlot * pciTmp = _pciSPRegister--;
        if (_pciSPRegister < _aciStack)
        {
          throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "ZVM stack underflow");
        }
        return pciTmp;
        */
      }
    #endif
    //@}

    /**
     * @name pop操作.
     */
    //@{
    #ifdef ENABLE_ZVM_DEBUG
    bool PopBool(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    bool PopBool();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    UCHAR PopByte(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    UCHAR PopByte();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    SDWORD PopSDWORD(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    SDWORD PopSDWORD();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    UDWORD PopUDWORD(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    UDWORD PopUDWORD();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    SQWORD PopSQWORD(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    SQWORD PopSQWORD();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    UQWORD PopUQWORD(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    UQWORD PopUQWORD();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    double PopDouble(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    double PopDouble();
    #endif

    /**
     * 不进行内存析构的Pop string object.
     * @attention 用于"convertStringValueToAddress"指令.
     */
    /*
     * 注：2001/7/17由于"convertStringValueToAddress"等指令被Discarded了!
     *
    #ifdef ENABLE_ZVM_DEBUG
    CZVMString * QuickPopStringObject(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMString * QuickPopStringObject();
    #endif
     */

    /**
     * 不进行内存析构的Pop ipv4address object.
     * @attention 用于"convertIPv4AddressValueToAddress"指令.
     */
    /*
     * 注：2001/7/17由于"convertStringValueToAddress"等指令被Discarded了!
     *
    #ifdef ENABLE_ZVM_DEBUG
    CZVMIPv4Address * QuickPopIPv4AddressObject(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMIPv4Address * QuickPopIPv4AddressObject();
    #endif
     */

    /**
     * 不进行内存析构的Pop pport object.
     * @attention 用于"convertPPortValueToAddress"指令.
     */
    /*
     * 注：2001/7/17由于"convertStringValueToAddress"等指令被Discarded了!
     *
    #ifdef ENABLE_ZVM_DEBUG
    CZVMPPort * QuickPopPPortObject(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMPPort * QuickPopPPortObject();
    #endif
     */

    /**
     * 不进行内存析构的Pop table object.
     * @attention 用于"convertTableValueToAddress"指令.
     */
    /*
     * 注：2001/7/17由于"convertStringValueToAddress"等指令被Discarded了!
     *
    #ifdef ENABLE_ZVM_DEBUG
    CZVMTable * QuickPopTableObject(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMTable * QuickPopTableObject();
    #endif
     */

    #ifdef ENABLE_ZVM_DEBUG
    bool * PopBoolAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    bool * PopBoolAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    UCHAR * PopByteAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    UCHAR * PopByteAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    SDWORD * PopSDWORDAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    SDWORD * PopSDWORDAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    UDWORD * PopUDWORDAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    UDWORD * PopUDWORDAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    SQWORD * PopSQWORDAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    SQWORD * PopSQWORDAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    UQWORD * PopUQWORDAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    UQWORD * PopUQWORDAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    double * PopDoubleAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    double * PopDoubleAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    CZVMString ** PopStringObjectAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMString ** PopStringObjectAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    CZVMRope ** PopRopeObjectAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMRope ** PopRopeObjectAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    CZVMIPv4Address ** PopIPv4AddressObjectAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMIPv4Address ** PopIPv4AddressObjectAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    CZVMPPort ** PopPPortObjectAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMPPort ** PopPPortObjectAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    CZVMTable ** PopTableObjectAddress(char chTableElementTypeTag, const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMTable ** PopTableObjectAddress();
    #endif
    //@}

    /**
     * @name top操作.
     */
    //@{
    #ifdef ENABLE_ZVM_DEBUG
    bool TopBool(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    bool TopBool();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    UCHAR TopByte(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    UCHAR TopByte();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    SDWORD TopSDWORD(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    SDWORD TopSDWORD();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    UDWORD TopUDWORD(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    UDWORD TopUDWORD();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    SQWORD TopSQWORD(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    SQWORD TopSQWORD();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    UQWORD TopUQWORD(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    UQWORD TopUQWORD();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    double TopDouble(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    double TopDouble();
    #endif

    /**
     * 不进行内存析构的Top string object.
     * @attention 用于"convertStringValueToAddress"指令.
     */
    /*
     * 注：2001/7/17由于"convertStringValueToAddress"等指令被Discarded了!
     *
    #ifdef ENABLE_ZVM_DEBUG
    CZVMString * QuickTopStringObject(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMString * QuickTopStringObject();
    #endif
     */

    /**
     * 不进行内存析构的Top ipv4address object.
     * @attention 用于"convertIPv4AddressValueToAddress"指令.
     */
    /*
     * 注：2001/7/17由于"convertStringValueToAddress"等指令被Discarded了!
     *
    #ifdef ENABLE_ZVM_DEBUG
    CZVMIPv4Address * QuickTopIPv4AddressObject(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMIPv4Address * QuickTopIPv4AddressObject();
    #endif
     */

    /**
     * 不进行内存析构的Top pport object.
     * @attention 用于"convertPPortValueToAddress"指令.
     */
    /*
     * 注：2001/7/17由于"convertStringValueToAddress"等指令被Discarded了!
     *
    #ifdef ENABLE_ZVM_DEBUG
    CZVMPPort * QuickTopPPortObject(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMPPort * QuickTopPPortObject();
    #endif
     */

    /**
     * 不进行内存析构的Top table object.
     * @attention 用于"convertTableValueToAddress"指令.
     */
    /*
     * 注：2001/7/17由于"convertStringValueToAddress"等指令被Discarded了!
     *
    #ifdef ENABLE_ZVM_DEBUG
    CZVMTable * QuickTopTableObject(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMTable * QuickTopTableObject();
    #endif
     */

    #ifdef ENABLE_ZVM_DEBUG
    bool * TopBoolAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    bool * TopBoolAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    UCHAR * TopByteAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    UCHAR * TopByteAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    SDWORD * TopSDWORDAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    SDWORD * TopSDWORDAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    UDWORD * TopUDWORDAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    UDWORD * TopUDWORDAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    SQWORD * TopSQWORDAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    SQWORD * TopSQWORDAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    UQWORD * TopUQWORDAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    UQWORD * TopUQWORDAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    double * TopDoubleAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    double * TopDoubleAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    CZVMString ** TopStringObjectAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMString ** TopStringObjectAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    CZVMRope ** TopRopeObjectAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMRope ** TopRopeObjectAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    CZVMIPv4Address ** TopIPv4AddressObjectAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMIPv4Address ** TopIPv4AddressObjectAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    CZVMPPort ** TopPPortObjectAddress(const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMPPort ** TopPPortObjectAddress();
    #endif

    #ifdef ENABLE_ZVM_DEBUG
    CZVMTable ** TopTableObjectAddress(char chTableElementTypeTag, const char * pszFileName, const char *pszFuncName, int nLineNumber);
    #else
    CZVMTable ** TopTableObjectAddress();
    #endif
    //@}

    /**
     * @name Quick Pop
     * @attention Just for 'CFunctionInvokeInterface'.
     */
    //@{
    void QuickPopAny()
    {
      CSlot * pciSlot = PostfixDecreaseSPRegister();
      pciSlot->ClearSlot();
    }
    //@}

    /**
     * @name Push Register
     */
    //@{
    void PushPCRegister()
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsSavedPCRegister(_ciPCRegister);
    }
    //@}

    /**
     * @name Push Defaule Value
     */
    //@{
    void PushDefaultBool()
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsDefaultBool();
    }

    void PushDefaultByte()
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsDefaultByte();
    }

    void PushDefaultSDWORD()
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsDefaultSDWORD();
    }

    void PushDefaultUDWORD()
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsDefaultUDWORD();
    }

    void PushDefaultSQWORD()
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsDefaultSQWORD();
    }

    void PushDefaultUQWORD()
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsDefaultUQWORD();
    }

    void PushDefaultDouble()
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsDefaultDouble();
    }

    void PushDefaultStringObject()
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsDefaultStringObject();
    }

    void PushDefaultRopeObject()
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsDefaultRopeObject();
    }

    void PushDefaultPPortObject()
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsDefaultPPortObject();
    }

    void PushDefaultIPv4AddressObject()
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsDefaultIPv4AddressObject();
    }

    void PushDefaultTableObject(char chTableElementTypeTag)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsDefaultTableObject(chTableElementTypeTag);
    }
    //@}

    /**
     * @name Push Value
     */
    //@{
    void PushBool(bool b)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsBool(b);
    }

    void PushByte(UCHAR uch)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsByte(uch);
    }

    void PushSDWORD(SDWORD sdw)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsSDWORD(sdw);
    }

    void PushUDWORD(UDWORD udw)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsUDWORD(udw);
    }

    void PushSQWORD(SQWORD sqw)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsSQWORD(sqw);
    }

    void PushUQWORD(UQWORD uqw)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsUQWORD(uqw);
    }

    void PushDouble(double df)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsDouble(df);
    }

    void PushStringObject(const CZVMString * pciString)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsStringObject(pciString);
    }

    void PushRopeObject(const CZVMRope * pciRope)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsRopeObject(pciRope);
    }

    void PushIPv4AddressObject(const CZVMIPv4Address * pciIPv4Address)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsIPv4AddressObject(pciIPv4Address);
    }

    void PushPPortObject(const CZVMPPort * pciPPort)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsPPortObject(pciPPort);
    }

    void PushTableObject(const CZVMTable * pciTable)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsTableObject(pciTable);
    }
    //@}

    /**
     * @name Push Address
     */
    //@{
    void PushBoolAddress(bool * pb)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsBoolAddress(pb);
    }

    void PushByteAddress(UCHAR * puch)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsByteAddress(puch);
    }

    void PushSDWORDAddress(SDWORD * psdw)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsSDWORDAddress(psdw);
    }

    void PushUDWORDAddress(UDWORD * pudw)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsUDWORDAddress(pudw);
    }

    void PushSQWORDAddress(SQWORD * psqw)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsSQWORDAddress(psqw);
    }

    void PushUQWORDAddress(UQWORD * puqw)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsUQWORDAddress(puqw);
    }

    void PushDoubleAddress(double * pdf)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsDoubleAddress(pdf);
    }

    void PushStringObjectAddress(CZVMString ** ppciString)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsStringObjectAddress(ppciString);
    }

    void PushRopeObjectAddress(CZVMRope ** ppciRope)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsRopeObjectAddress(ppciRope);
    }

    void PushPPortObjectAddress(CZVMPPort ** ppciPPort)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsPPortObjectAddress(ppciPPort);
    }

    void PushIPv4AddressObjectAddress(CZVMIPv4Address ** ppciIPv4Address)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsIPv4AddressObjectAddress(ppciIPv4Address);
    }

    void PushTableObjectAddress(CZVMTable ** ppciTable)
    {
      CSlot * pciSlot = PrefixIncreaseSPRegister();
      pciSlot->ConstructSlotAsTableObjectAddress(ppciTable);
    }
    //@}

    /**
     * @name Replace As Value
     * @attention 用于直接将一种类型的Slot替换为另一种类型的Slot.
     */
    //@{
    void ReplaceAsBool(bool b)
    {
      _pciSPRegister->ConstructSlotAsBool(b);
    }

    void ReplaceAsByte(UCHAR uch)
    {
      _pciSPRegister->ConstructSlotAsByte(uch);
    }

    void ReplaceAsSDWORD(SDWORD sdw)
    {
      _pciSPRegister->ConstructSlotAsSDWORD(sdw);
    }

    void ReplaceAsUDWORD(UDWORD udw)
    {
      _pciSPRegister->ConstructSlotAsUDWORD(udw);
    }

    void ReplaceAsSQWORD(SQWORD sqw)
    {
      _pciSPRegister->ConstructSlotAsSQWORD(sqw);
    }

    void ReplaceAsUQWORD(UQWORD uqw)
    {
      _pciSPRegister->ConstructSlotAsUQWORD(uqw);
    }

    void ReplaceAsDouble(double df)
    {
      _pciSPRegister->ConstructSlotAsDouble(df);
    }

    void ReplaceAsStringObject(const CZVMString * pciString)
    {
      _pciSPRegister->ConstructSlotAsStringObject(pciString);
    }

    void ReplaceAsRopeObject(const CZVMRope * pciRope)
    {
      _pciSPRegister->ConstructSlotAsRopeObject(pciRope);
    }

    void ReplaceAsIPv4AddressObject(const CZVMIPv4Address * pciIPv4Address)
    {
      _pciSPRegister->ConstructSlotAsIPv4AddressObject(pciIPv4Address);
    }

    void ReplaceAsPPortObject(const CZVMPPort * pciPPort)
    {
      _pciSPRegister->ConstructSlotAsPPortObject(pciPPort);
    }

    void ReplaceAsTableObject(const CZVMTable * pciTable)
    {
      _pciSPRegister->ConstructSlotAsTableObject(pciTable);
    }
    //@}

    /**
     * @name Replace As Address
     * @attention 用于直接将一种类型的Slot替换为另一种类型的Slot.
     */
    //@{
    void ReplaceAsBoolAddress(bool * pb)
    {
      _pciSPRegister->ConstructSlotAsBoolAddress(pb);
    }

    void ReplaceAsByteAddress(UCHAR * puch)
    {
      _pciSPRegister->ConstructSlotAsByteAddress(puch);
    }

    void ReplaceAsSDWORDAddress(SDWORD * psdw)
    {
      _pciSPRegister->ConstructSlotAsSDWORDAddress(psdw);
    }

    void ReplaceAsUDWORDAddress(UDWORD * pudw)
    {
      _pciSPRegister->ConstructSlotAsUDWORDAddress(pudw);
    }

    void ReplaceAsSQWORDAddress(SQWORD * psqw)
    {
      _pciSPRegister->ConstructSlotAsSQWORDAddress(psqw);
    }

    void ReplaceAsUQWORDAddress(UQWORD * puqw)
    {
      _pciSPRegister->ConstructSlotAsUQWORDAddress(puqw);
    }

    void ReplaceAsDoubleAddress(double * pdf)
    {
      _pciSPRegister->ConstructSlotAsDoubleAddress(pdf);
    }

    void ReplaceAsStringObjectAddress(CZVMString ** ppciString)
    {
      _pciSPRegister->ConstructSlotAsStringObjectAddress(ppciString);
    }

    void ReplaceAsRopeObjectAddress(CZVMRope ** ppciRope)
    {
      _pciSPRegister->ConstructSlotAsRopeObjectAddress(ppciRope);
    }

    void ReplaceAsPPortObjectAddress(CZVMPPort ** ppciPPort)
    {
      _pciSPRegister->ConstructSlotAsPPortObjectAddress(ppciPPort);
    }

    void ReplaceAsIPv4AddressObjectAddress(CZVMIPv4Address ** ppciIPv4Address)
    {
      _pciSPRegister->ConstructSlotAsIPv4AddressObjectAddress(ppciIPv4Address);
    }

    void ReplaceAsTableObjectAddress(CZVMTable ** ppciTable)
    {
      _pciSPRegister->ConstructSlotAsTableObjectAddress(ppciTable);
    }
    //@}

    /**
     * @name Store Value
     * @attention 用于直接替换"同类型"的Slot的内容.
     */
    //@{
    void StoreBool(bool b)
    {
      _pciSPRegister->StoreBool(b);
    }

    void StoreByte(UCHAR uch)
    {
      _pciSPRegister->StoreByte(uch);
    }

    void StoreSDWORD(SDWORD sdw)
    {
      _pciSPRegister->StoreSDWORD(sdw);
    }

    void StoreUDWORD(UDWORD udw)
    {
      _pciSPRegister->StoreUDWORD(udw);
    }

    void StoreSQWORD(SQWORD sqw)
    {
      _pciSPRegister->StoreSQWORD(sqw);
    }

    void StoreUQWORD(UQWORD uqw)
    {
      _pciSPRegister->StoreUQWORD(uqw);
    }

    void StoreDouble(double df)
    {
      _pciSPRegister->StoreDouble(df);
    }

    void StoreStringObject(const CZVMString * pciString)
    {
      _pciSPRegister->StoreStringObject(pciString);
    }

    void StoreRopeObject(const CZVMRope * pciRope)
    {
      _pciSPRegister->StoreRopeObject(pciRope);
    }

    void StoreIPv4AddressObject(const CZVMIPv4Address * pciIPv4Address)
    {
      _pciSPRegister->StoreIPv4AddressObject(pciIPv4Address);
    }

    void StorePPortObject(const CZVMPPort * pciPPort)
    {
      _pciSPRegister->StorePPortObject(pciPPort);
    }

    void StoreTableObject(const CZVMTable * pciTable)
    {
      _pciSPRegister->StoreTableObject(pciTable);
    }
    //@}

    /**
     * @name Store Address
     * @attention 用于直接替换"同类型"的Slot的内容.
     */
    //@{
    void StoreBoolAddress(bool * pb)
    {
      _pciSPRegister->StoreBoolAddress(pb);
    }

    void StoreByteAddress(UCHAR * puch)
    {
      _pciSPRegister->StoreByteAddress(puch);
    }

    void StoreSDWORDAddress(SDWORD * psdw)
    {
      _pciSPRegister->StoreSDWORDAddress(psdw);
    }

    void StoreUDWORDAddress(UDWORD * pudw)
    {
      _pciSPRegister->StoreUDWORDAddress(pudw);
    }

    void StoreSQWORDAddress(SQWORD * psqw)
    {
      _pciSPRegister->StoreSQWORDAddress(psqw);
    }

    void StoreUQWORDAddress(UQWORD * puqw)
    {
      _pciSPRegister->StoreUQWORDAddress(puqw);
    }

    void StoreDoubleAddress(double * pdf)
    {
      _pciSPRegister->StoreDoubleAddress(pdf);
    }

    void StoreStringObjectAddress(CZVMString ** ppciString)
    {
      _pciSPRegister->StoreStringObjectAddress(ppciString);
    }

    void StoreRopeObjectAddress(CZVMRope ** ppciRope)
    {
      _pciSPRegister->StoreRopeObjectAddress(ppciRope);
    }

    void StorePPortObjectAddress(CZVMPPort ** ppciPPort)
    {
      _pciSPRegister->StorePPortObjectAddress(ppciPPort);
    }

    void StoreIPv4AddressObjectAddress(CZVMIPv4Address ** ppciIPv4Address)
    {
      _pciSPRegister->StoreIPv4AddressObjectAddress(ppciIPv4Address);
    }

    void StoreTableObjectAddress(CZVMTable ** ppciTable)
    {
      _pciSPRegister->StoreTableObjectAddress(ppciTable);
    }
    //@}

  public:
    #ifdef ENABLE_ZVM_DEBUG
    /**
     * 确保SP指向的那个Slot的Tag为我们希望的Tag.
     *
     * @throw zfc::EPanic 当不是我们希望的Tag时.
     */
    void StackAssert(CSlot::TSlotTag eAssertedTag,
                     const char * pszFileName,
                     const char * pszFuncName,
                     const int nLineNumber)
    { _pciSPRegister->SlotAssert(eAssertedTag, pszFileName, pszFuncName, nLineNumber); }
    #endif

    #include <zls/zvm/LoadValueInstruction.inc.hpp>
    #include <zls/zvm/LoadAddressInstruction.inc.hpp>
    #include <zls/zvm/StoreInstruction.inc.hpp>
    #include <zls/zvm/BinaryInstruction.inc.hpp>
    #include <zls/zvm/UnaryInstruction.inc.hpp>
    #include <zls/zvm/MiscInstruction.inc.hpp>

    const CVirtualMachine * GetOwnerZVM() const
    { return _pciOwnerZVM; }

    const CSlot * GetStackLowWater() const
    { return _aciStack; }

    const CSlot * GetStackHighWater() const
    { return _pciStackHighWater; }

    CSlot * GetSPRegister()
    { return _pciSPRegister; }

    CSlot * GetBPRegister()
    { return _pciBPRegister; }

    void AdjustSPRegister(TZVMIndex nAdjustedOffset)
    {
      static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSPRegister::AdjustSPRegister()");
      if ((_pciSPRegister += nAdjustedOffset) >= _pciStackHighWater)
      {
        throw zvm::EZVMRuntimeException(__FILE__, __PRETTY_FUNC__, __LINE__, "ZVM stack overflow");
      }
    }

    void CallZVMFunction(const CZVMFunction * pciZVMFunction);

    void CallNativeFunction(TNativeFunction pfuncNativeFunction)
    {
      // Native function不需要执行隐含"PushPC"的指令，编写者应该清楚这点的
      pfuncNativeFunction(GetSPRegister());
    }
};


#if defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION > 1  // 如果采用二级优化
#include <zls/zvm/CZVMVirtualThread.inc.cpp>
#endif


ZLS_END_NAMESPACE


#endif

