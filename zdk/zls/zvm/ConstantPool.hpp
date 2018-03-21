/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/ConstantPool.hpp,v $
 *
 * $Date: 2001/11/14 18:29:37 $
 *
 * $Revision: 1.5 $
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


#ifndef _ZLS_zvm_ConstantPool_hpp_
#define _ZLS_zvm_ConstantPool_hpp_

#include <zls/zfc/CBinaryString.hpp>
#include <zls/zfc/CBinaryInputFileStream.hpp>
#include <zls/zvm/Manifest.hpp>
#include <zls/zvm/CZVMFunction.hpp>
#include <zls/zvm/ZVMException.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


/**
 * 表示一个名称和类型引用.
 *
 * @note 由于我的ZLang compiler保证所有的name and signature reference在constant
 * pool中的位置一定是位于它的name string literan和signature string literal在
 * constant pool中的位置的后面，因此我在读入Object file时即可立即对name string
 * literal和signature string literal进行解释.
 */
class CNameAndSignatureReference {
  private:
    /** Forbidden operator=(). */
    CNameAndSignatureReference & operator=(const CNameAndSignatureReference &);
    /** Forbidden copy constructor. */
    CNameAndSignatureReference(const CNameAndSignatureReference &);

    /** 在读入Object file时，已经被立即解释的name string. */
    const std::string * _pstringName;
    /** 在读入Object file时，已经被立即解释的signature string. */
    const std::string * _pstringSignature;

  public:
    void DumpDetail() const;

    const std::string & GetName() const
    {
      return *_pstringName;
    }

    const std::string & GetSignature() const
    {
      return *_pstringSignature;
    }

    CNameAndSignatureReference(const std::string * pstringName, const std::string * pstringSignature)
      : _pstringName(pstringName),
        _pstringSignature(pstringSignature)
    { }
};


/**
 * 表示一个ZLang global variable reference.
 *
 * @note 由于我的ZLang compiler保证所有的global variable reference在constant
 * pool中的位置一定是位于它的name and signature reference在constant pool中的
 * 位置的后面，因此我在读入Object file时即可立即对name and signature reference
 * 进行解释.
 */
class CGlobalVariableReference {
  private:
    /** Forbidden operator=(). */
    CGlobalVariableReference & operator=(const CGlobalVariableReference &);
    /** Forbidden copy constructor. */
    CGlobalVariableReference(const CGlobalVariableReference &);

    /** 指向一个名称和类型引用. */
    const zvm::CNameAndSignatureReference * _pciNameAndSignatureReference;

    /** 指示这个global variable的存取修饰符Tag. */
    TAccessModifierTag _eAccessModifierTag;

    /** @name Link时决定. */
    //@{
    /** 在全局数据段中的slot. */
    CSlot * _pciVariableSlot;
    //@}

  public:
    /**
     * @name Interface for link.
     */
    //@{
    void PatchRelocatedSlot(CSlot * pciVariableSlot)
    {
      _pciVariableSlot = pciVariableSlot;
    }
    //@}

    void DumpDetail() const;

    const zvm::CNameAndSignatureReference * GetNameAndSignatureReference() const
    {
      return _pciNameAndSignatureReference;
    }

    TAccessModifierTag GetAccessModifierTag() const
    {
      return _eAccessModifierTag;
    }

    CSlot * GetRelocatedSlot() const
    {
      return _pciVariableSlot;
    }

    CGlobalVariableReference(const zvm::CNameAndSignatureReference * pciNameAndSignatureReference,
                             TAccessModifierTag eAccessModifierTag)
      : _pciNameAndSignatureReference(pciNameAndSignatureReference),
        _eAccessModifierTag(eAccessModifierTag)
    { }

    ~CGlobalVariableReference();
};


/**
 * 表示一个ZLang global function reference.
 *
 * @note 由于我的ZLang compiler保证所有的global function reference在constant
 * pool中的位置一定是位于它的name and signature reference在constant pool中的
 * 位置的后面，因此我在读入Object file时即可立即对name and signature reference
 * 进行解释.
 */
class CGlobalFunctionReference {
  private:
    /** Forbidden operator=(). */
    CGlobalFunctionReference & operator=(const CGlobalFunctionReference &);
    /** Forbidden copy constructor. */
    CGlobalFunctionReference(const CGlobalFunctionReference &);

    /** 指向一个名称和类型引用. */
    const zvm::CNameAndSignatureReference * _pciNameAndSignatureReference;

    /** 指示这个global function的存取修饰符Tag. */
    TAccessModifierTag _eAccessModifierTag;

    /** @name Link时决定. */
    //@{
    /** 该global function是用什么语言编写的. */
    TLanguageTag _eLanguageTag;
    union {
      /** 如果是用C++编写的，则选择这个字段. */
      TNativeFunction _pfuncNativeFunction;
      /** 如果是用ZLang script编写的，则选择这个字段. */
      const CZVMFunction * _pciZVMFunction;
    };
    //@}

  public:
    /**
     * @name Interface for link.
     */
    //@{
    void PatchZVMFunction(const CZVMFunction * pciZVMFunction)
    {
      _eLanguageTag = LANGUAGE_TAG_IS_ZLANG;
      _pciZVMFunction = pciZVMFunction;
    }

    void PatchNativeFunction(TNativeFunction pfuncNativeFunction)
    {
      _eLanguageTag = LANGUAGE_TAG_IS_CPP;
      _pfuncNativeFunction = pfuncNativeFunction;
    }
    //@}

    const zvm::CNameAndSignatureReference * GetNameAndSignatureReference() const
    {
      return _pciNameAndSignatureReference;
    }

    TAccessModifierTag GetAccessModifierTag() const
    {
      return _eAccessModifierTag;
    }

    TLanguageTag GetLanguageTag() const
    {
      return _eLanguageTag;
    }

    const CZVMFunction * GetZVMFunction() const
    {
      return _pciZVMFunction;
    }

    TNativeFunction GetNativeFunction() const
    {
      return _pfuncNativeFunction;
    }

    void DumpDetail() const;

    CGlobalFunctionReference(const zvm::CNameAndSignatureReference * pciNameAndSignatureReference,
                             TAccessModifierTag eAccessModifierTag)
      : _pciNameAndSignatureReference(pciNameAndSignatureReference),
        _eAccessModifierTag(eAccessModifierTag)
    { }
};


#ifdef ENABLE_ZVM_DEBUG
  #define ZVM_CONSTANT_ASSERT(pciSlot, eTag, pszFile, pszFunc, nLine)   \
    pciSlot->ConstantAssert(eTag, pszFile, pszFunc, nLine)
#else
  #define ZVM_CONSTANT_ASSERT(pciSlot, eTag, pszFile, pszFunc, nLine)
#endif


class CConstantPoolSlot {
  private:
    /** Forbidden operator=(). */
    CConstantPoolSlot & operator=(const CConstantPoolSlot &);
    /** Forbidden copy constructor. */
    CConstantPoolSlot(const CConstantPoolSlot &);

    TConstantPoolElementTag _eElementTag;
    union {
      const std::string               * _pciNilEndStringLiteral;
      const CZVMString                * _pciBinaryStringLiteral;
      const CZVMRope                  * _pciRopeStringLiteral;
      //SDWORD                            _sdwLiteral;
      //UDWORD                            _udwLiteral;
      SQWORD                            _sqwLiteral;
      UQWORD                            _uqwLiteral;
      double                            _dfLiteral;
      const CZVMPPort                 * _pciPPortLiteral;
      const CZVMIPv4Address           * _pciIPv4AddressLiteral;
      zvm::CNameAndSignatureReference * _pciNameAndSignatureReference;
      zvm::CGlobalVariableReference   * _pciGlobalVariableReference;
      zvm::CGlobalFunctionReference   * _pciGlobalFunctionReference;
    };

  public:
    #ifdef ENABLE_ZVM_DEBUG
    /**
     * 确保某个Slot的Tag为我们希望的Tag.
     *
     * @throw zfc::EPanic 当不是我们希望的Tag时.
     */
    void ConstantAssert(TConstantPoolElementTag eAssertedTag,
                        const char * pszFileName,
                        const char * pszFuncName,
                        const int nLineNumber) const;
    #endif

    void DumpDetail() const;

    TConstantPoolElementTag GetElementTag() const
    {
      return _eElementTag;
    }

    const zvm::CNameAndSignatureReference * GetAsNameAndSignatureReference() const
    {
      return _pciNameAndSignatureReference;
    }

    zvm::CGlobalVariableReference * GetAsGlobalVariableReference()
    {
      return _pciGlobalVariableReference;
    }

    const zvm::CGlobalVariableReference * GetAsGlobalVariableReference() const
    {
      return _pciGlobalVariableReference;
    }

    zvm::CGlobalFunctionReference * GetAsGlobalFunctionReference()
    {
      return _pciGlobalFunctionReference;
    }

    const zvm::CGlobalFunctionReference * GetAsGlobalFunctionReference() const
    {
      return _pciGlobalFunctionReference;
    }

    SQWORD GetAsSQWORD() const
    {
      return _sqwLiteral;
    }

    UQWORD GetAsUQWORD() const
    {
      return _uqwLiteral;
    }

    double GetAsDouble() const
    {
      return _dfLiteral;
    }

    const std::string * GetAsNilEndString() const
    {
      return _pciNilEndStringLiteral;
    }

    const CZVMString * GetAsBinaryString() const
    {
      return _pciBinaryStringLiteral;
    }

    const CZVMRope * GetAsRopeString() const
    {
      return _pciRopeStringLiteral;
    }

    const CZVMPPort * GetAsPPort() const
    {
      return _pciPPortLiteral;
    }

    const CZVMIPv4Address * GetAsIPv4Address() const
    {
      return _pciIPv4AddressLiteral;
    }

    const std::string * const * GetAsPointerOfNilEndStringPointer() const
    {
      return &_pciNilEndStringLiteral;
    }

    const CZVMString * const * GetAsPointerOfBinaryStringPointer() const
    {
      return &_pciBinaryStringLiteral;
    }

    const CZVMRope * const * GetAsPointerOfRopeStringPointer() const
    {
      return &_pciRopeStringLiteral;
    }

    const CZVMPPort * const * GetAsPointerOfPPortPointer() const
    {
      return &_pciPPortLiteral;
    }

    const CZVMIPv4Address * const * GetAsPointerOfIPv4AddressPointer() const
    {
      return &_pciIPv4AddressLiteral;
    }

    CConstantPoolSlot()
      : _eElementTag(CONSTANT_POOL_ELEMENT_TAG_NONE)
    { }

    CConstantPoolSlot(std::string * pstringNilEndStringLiteral)
      : _eElementTag(CONSTANT_POOL_ELEMENT_TAG_NIL_END_STRING),
        _pciNilEndStringLiteral(pstringNilEndStringLiteral)
    { }

    #ifdef USE_std_string_AS_ZVM_STRING
    CConstantPoolSlot(CZVMString * pciBinaryStringLiteral, int)
      : _eElementTag(CONSTANT_POOL_ELEMENT_TAG_BINARY_STRING),
        _pciBinaryStringLiteral(pciBinaryStringLiteral)
    { }
    #else
    CConstantPoolSlot(CZVMString * pciBinaryStringLiteral)
      : _eElementTag(CONSTANT_POOL_ELEMENT_TAG_BINARY_STRING),
        _pciBinaryStringLiteral(pciBinaryStringLiteral)
    { }
    #endif

    CConstantPoolSlot(CZVMRope * pciRopeStringLiteral)
      : _eElementTag(CONSTANT_POOL_ELEMENT_TAG_ROPE_STRING),
        _pciRopeStringLiteral(pciRopeStringLiteral)
    { }

    CConstantPoolSlot(SQWORD sqwLiteral)
      : _eElementTag(CONSTANT_POOL_ELEMENT_TAG_SQWORD),
        _sqwLiteral(sqwLiteral)
    { }

    CConstantPoolSlot(UQWORD uqwLiteral)
      : _eElementTag(CONSTANT_POOL_ELEMENT_TAG_UQWORD),
        _uqwLiteral(uqwLiteral)
    { }

    CConstantPoolSlot(double dfLiteral)
      : _eElementTag(CONSTANT_POOL_ELEMENT_TAG_DOUBLE),
        _dfLiteral(dfLiteral)
    { }

    CConstantPoolSlot(CZVMPPort * pciPPortLiteral)
      : _eElementTag(CONSTANT_POOL_ELEMENT_TAG_PROTOCOL_PORT),
        _pciPPortLiteral(pciPPortLiteral)
    { }

    CConstantPoolSlot(CZVMIPv4Address * pciIPv4AddressLiteral)
      : _eElementTag(CONSTANT_POOL_ELEMENT_TAG_IPv4ADDRESS),
        _pciIPv4AddressLiteral(pciIPv4AddressLiteral)
    { }

    CConstantPoolSlot(zvm::CNameAndSignatureReference * pciNameAndSignatureReference)
      : _eElementTag(CONSTANT_POOL_ELEMENT_TAG_NAME_AND_SIGNATURE_REFERENCE),
        _pciNameAndSignatureReference(pciNameAndSignatureReference)
    { }

    CConstantPoolSlot(zvm::CGlobalVariableReference * pciGlobalVariableReference)
      : _eElementTag(CONSTANT_POOL_ELEMENT_TAG_GLOBAL_VARIABLE_REFERENCE),
        _pciGlobalVariableReference(pciGlobalVariableReference)
    { }

    CConstantPoolSlot(zvm::CGlobalFunctionReference * pciGlobalFunctionReference)
      : _eElementTag(CONSTANT_POOL_ELEMENT_TAG_GLOBAL_FUNCTION_REFERENCE),
        _pciGlobalFunctionReference(pciGlobalFunctionReference)
    { }

    ~CConstantPoolSlot();
};


class CConstantPool {
  private:
    /** Forbidden operator=(). */
    CConstantPool & operator=(const CConstantPool &);
    /** Forbidden copy constructor. */
    CConstantPool(const CConstantPool &);

    TZVMIndex           _nSlotCapacity;
    CConstantPoolSlot * _aciSlots;

  public:
    void DumpDetail() const;

    TZVMIndex GetSlotCapacity() const
    {
      return _nSlotCapacity;
    }

    CConstantPoolSlot * GetSlots()
    {
      return _aciSlots;
    }

    const CConstantPoolSlot * GetSlots() const
    {
      return _aciSlots;
    }

    /**
     * @throw zfc::EOutOfRange 当nIndex越界时.
     */
    const CConstantPoolSlot * GetSlotAt(TZVMIndex nIndex) const;

    const CConstantPoolSlot * operator[](TZVMIndex nIndex) const
    {
      return &(_aciSlots[nIndex]);
    }

    const zvm::CNameAndSignatureReference * GetAsNameAndSignatureReference(TZVMIndex nIndex) const;
    const zvm::CGlobalVariableReference * GetAsGlobalVariableReference(TZVMIndex nIndex) const;
    const zvm::CGlobalFunctionReference * GetAsGlobalFunctionReference(TZVMIndex nIndex) const;

    SQWORD GetAsSQWORD(TZVMIndex nIndex) const;
    UQWORD GetAsUQWORD(TZVMIndex nIndex) const;
    double GetAsDouble(TZVMIndex nIndex) const;
    const std::string * GetAsNilEndString(TZVMIndex nIndex) const;
    const CZVMString * GetAsBinaryString(TZVMIndex nIndex) const;
    const CZVMRope * GetAsRopeString(TZVMIndex nIndex) const;
    const CZVMPPort * GetAsPPort(TZVMIndex nIndex) const;
    const CZVMIPv4Address * GetAsIPv4Address(TZVMIndex nIndex) const;

    const std::string * const * GetAsPointerOfNilEndStringPointer(TZVMIndex nIndex) const;
    const CZVMString * const * GetAsPointerOfBinaryStringPointer(TZVMIndex nIndex) const;
    const CZVMRope * const * GetAsPointerOfRopeStringPointer(TZVMIndex nIndex) const;
    const CZVMPPort * const * GetAsPointerOfPPortPointer(TZVMIndex nIndex) const;
    const CZVMIPv4Address * const * GetAsPointerOfIPv4AddressPointer(TZVMIndex nIndex) const;

    CConstantPool()
      : _nSlotCapacity(0),
        _aciSlots(0)
    { }

    ~CConstantPool()
    {
      delete [] _aciSlots;
    }

    friend zfc::CBinaryInputFileStream & operator >>(zfc::CBinaryInputFileStream & bis,
                                                     zvm::CConstantPool & rciPool);
};


ZLS_END_NAMESPACE


#endif

