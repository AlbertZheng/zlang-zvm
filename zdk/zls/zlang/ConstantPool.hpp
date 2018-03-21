/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/ConstantPool.hpp,v $
 *
 * $Date: 2001/08/10 18:34:37 $
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


#ifndef _ZLS_zlang_ConstantPool_hpp_
#define _ZLS_zlang_ConstantPool_hpp_

#include <zls/zvm/Manifest.hpp>
#include <zls/zvm/CProtocolPort.hpp>
#include <zls/zvm/CIPv4CIDRAddress.hpp>
#include <zls/zlang/SymbolTable.hpp>


// Begin namespace 'zlang::'
ZLS_BEGIN_NAMESPACE(zlang)


/**
 * Constant pool element.
 *
 * @attention 该class还不符合STL的基本要求，所以在STL的容器中只能包含该class的
 * 指针.
 */
class CConstantPoolElement : public zfc::CReferenceCounter {
  friend class CConstantPool;

  private:
    /** Forbidden copy constructor. */
    CConstantPoolElement(const CConstantPoolElement & rci);
    /** Forbidden operator=(). */
    CConstantPoolElement & operator=(const CConstantPoolElement & rci);

  protected:
    zvm::TConstantPoolElementTag _eElementTag;
    zvm::TZVMIndex               _nSelfIndex;  // 运行时恢复

  public:
    zvm::TConstantPoolElementTag GetElementTag() const
    {
      return _eElementTag;
    }

    zvm::TZVMIndex GetSelfIndex() const
    {
      return _nSelfIndex;
    }
    void SetSelfIndex(zvm::TZVMIndex nIndex)
    {
      _nSelfIndex = nIndex;
    }

    /**
     * Overload operator==().
     */
    virtual bool operator==(const CConstantPoolElement & rciRight) const = 0;
    /**
     * Overload operator!=().
     * 将调用virtual operator==().
     */
    bool operator!=(const CConstantPoolElement & rciRight) const
    { return ! operator==(rciRight); }

    virtual void DumpDetail() const = 0;

    CConstantPoolElement(zvm::TConstantPoolElementTag eTag)
      : _eElementTag(eTag)
    { }

    virtual ~CConstantPoolElement()
    { }
};

typedef zfc::CSmartPointerT<CConstantPoolElement>    CConstantPoolElement_auto;


/**
 * class CConstantPoolElement的具体形态，它表示一个需NIL结尾的字符串字面值.
 */
class CNilEndStringLiteral : public CConstantPoolElement {
  private:
    std::string _stringLiteral;

  public:
    const std::string & GetLiteral() const
    {
      return _stringLiteral;
    }

    virtual bool operator==(const CConstantPoolElement & rciRight) const;

    virtual void DumpDetail() const;

    CNilEndStringLiteral()
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_NIL_END_STRING)
    { }

    CNilEndStringLiteral(const std::string & rstringLiteral)
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_NIL_END_STRING),
        _stringLiteral(rstringLiteral)
    { }

    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                    const CNilEndStringLiteral & rci);
};


/**
 * class CConstantPoolElement的具体形态，它表示一个可非NIL结尾的8bit清楚的字符串字面值.
 */
class CBinaryStringLiteral : public CConstantPoolElement {
  private:
    zvm::CZVMString _bstringLiteral;

  public:
    const zvm::CZVMString & GetLiteral() const
    {
      return _bstringLiteral;
    }

    virtual bool operator==(const CConstantPoolElement & rciRight) const;

    virtual void DumpDetail() const;

    CBinaryStringLiteral()
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_BINARY_STRING)
    { }

    CBinaryStringLiteral(const zvm::CZVMString & rbstringLiteral)
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_BINARY_STRING),
        _bstringLiteral(rbstringLiteral)
    { }

    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const CBinaryStringLiteral & rci);
};


/**
 * class CConstantPoolElement的具体形态，它表示一个可非NIL结尾的8bit清楚的Rope字符串字面值.
 */
class CRopeStringLiteral : public CConstantPoolElement {
  private:
    zvm::CZVMRope _ropeLiteral;

  public:
    const zvm::CZVMRope & GetLiteral() const
    {
      return _ropeLiteral;
    }

    virtual bool operator==(const CConstantPoolElement & rciRight) const;

    virtual void DumpDetail() const;

    CRopeStringLiteral()
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_ROPE_STRING)
    { }

    CRopeStringLiteral(const zvm::CZVMRope & rropeLiteral)
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_ROPE_STRING),
        _ropeLiteral(rropeLiteral)
    { }

    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const CRopeStringLiteral & rci);
};


/**
 * class CConstantPoolElement的具体形态，它表示一个SDWORD字面值.
 */
/*
class CSDWORDLiteral : public CConstantPoolElement {
  private:
    SDWORD _sdwLiteral;

  public:
    SDWORD GetLiteral() const
    {
      return(_sdwLiteral);
    }

    virtual bool operator==(const CConstantPoolElement & rciRight) const;

    virtual void DumpDetail() const;

    CSDWORDLiteral()
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_SDWORD)
    { }

    CSDWORDLiteral(const SDWORD sdwLiteral)
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_SDWORD),
        _sdwLiteral(sdwLiteral)
    { }

    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const CSDWORDLiteral & rci);
};
*/


/**
 * class CConstantPoolElement的具体形态，它表示一个UDWORD字面值.
 */
/*
class CUDWORDLiteral : public CConstantPoolElement {
  private:
    UDWORD _udwLiteral;

  public:
    UDWORD GetLiteral() const
    {
      return(_udwLiteral);
    }

    virtual bool operator==(const CConstantPoolElement & rciRight) const;

    virtual void DumpDetail() const;

    CUDWORDLiteral()
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_UDWORD)
    { }

    CUDWORDLiteral(const UDWORD udwLiteral)
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_UDWORD),
        _udwLiteral(udwLiteral)
    { }

    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const CUDWORDLiteral & rci);
};
*/


class CSQWORDLiteral : public CConstantPoolElement {
  private:
    SQWORD _sqwLiteral;

  public:
    SQWORD GetLiteral() const
    {
      return(_sqwLiteral);
    }

    virtual bool operator==(const CConstantPoolElement & rciRight) const;

    virtual void DumpDetail() const;

    CSQWORDLiteral()
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_SQWORD)
    { }

    CSQWORDLiteral(const SQWORD sqwLiteral)
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_SQWORD),
        _sqwLiteral(sqwLiteral)
    { }

    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const CSQWORDLiteral & rci);
};


class CUQWORDLiteral : public CConstantPoolElement {
  private:
    UQWORD _uqwLiteral;

  public:
    UQWORD GetLiteral() const
    {
      return(_uqwLiteral);
    }

    virtual bool operator==(const CConstantPoolElement & rciRight) const;

    virtual void DumpDetail() const;

    CUQWORDLiteral()
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_UQWORD)
    { }

    CUQWORDLiteral(const UQWORD uqwLiteral)
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_UQWORD),
        _uqwLiteral(uqwLiteral)
    { }

    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const CUQWORDLiteral & rci);
};


/**
 * class CConstantPoolElement的具体形态，它表示一个double字面值.
 */
class CDoubleLiteral : public CConstantPoolElement {
  private:
    double _dfLiteral;

  public:
    double GetLiteral() const
    {
      return(_dfLiteral);
    }

    virtual bool operator==(const CConstantPoolElement & rciRight) const;

    virtual void DumpDetail() const;

    CDoubleLiteral()
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_DOUBLE)
    { }

    CDoubleLiteral(const double dfLiteral)
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_DOUBLE),
        _dfLiteral(dfLiteral)
    { }

    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const CDoubleLiteral & rci);
};


/**
 * class CConstantPoolElement的具体形态，它表示一个pport字面值.
 */
class CPPortLiteral : public CConstantPoolElement {
  private:
    zvm::CProtocolPort _ciLiteral;

  public:
    const zvm::CProtocolPort & GetLiteral() const
    {
      return(_ciLiteral);
    }

    virtual bool operator==(const CConstantPoolElement & rciRight) const;

    virtual void DumpDetail() const;

    CPPortLiteral()
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_PROTOCOL_PORT)
    { }

    CPPortLiteral(const UWORD uwProtocolType,
                  const PPORT nPortNumber)
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_PROTOCOL_PORT),
        _ciLiteral(uwProtocolType, nPortNumber)
    { }

    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const CPPortLiteral & rci);
};


/**
 * class CConstantPoolElement的具体形态，它表示一个不进行DNS解析的IPv4Address字面值.
 */
class CUnresolvedIPv4AddressLiteral : public CConstantPoolElement {
  private:
    std::string _stringIPv4Address;
    NUDWORD     _nudwCIDRMask;

  public:
    virtual bool operator==(const CConstantPoolElement & rciRight) const;

    virtual void DumpDetail() const;

    CUnresolvedIPv4AddressLiteral(const char * pszHostAddress)
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_IPv4ADDRESS),
        _stringIPv4Address(pszHostAddress),
        _nudwCIDRMask(INADDR_BROADCAST)
    { }
    CUnresolvedIPv4AddressLiteral(const std::string & rstringHostAddress)
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_IPv4ADDRESS),
        _stringIPv4Address(rstringHostAddress),
        _nudwCIDRMask(INADDR_BROADCAST)
    { }

    CUnresolvedIPv4AddressLiteral(const std::string & rstringNetworkAddress,
                                  NUDWORD nudwCIDRMask)
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_IPv4ADDRESS),
        _stringIPv4Address(rstringNetworkAddress),
        _nudwCIDRMask(nudwCIDRMask)
    { }

    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const CUnresolvedIPv4AddressLiteral & rci);
};


/**
 * class CConstantPoolElement的具体形态，它表示一个名称和类型引用.
 */
class CNameAndSignatureReference : public CConstantPoolElement {
  private:
    zvm::TZVMIndex _nNameIndex;   /**< 指向一个CNilEndStringLiteral */
    zvm::TZVMIndex _nSignatureIndex;   /**< 指向一个CNilEndStringLiteral */

  public:
    virtual bool operator==(const CConstantPoolElement & rciRight) const;

    virtual void DumpDetail() const;

    zvm::TZVMIndex GetNameIndex() const
    {
      return(_nNameIndex);
    }

    zvm::TZVMIndex GetSignatureIndex() const
    {
      return(_nSignatureIndex);
    }

    CNameAndSignatureReference()
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_NAME_AND_SIGNATURE_REFERENCE)
    { }

    CNameAndSignatureReference(const zvm::TZVMIndex nNameIndex,
                               const zvm::TZVMIndex nSignatureIndex)
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_NAME_AND_SIGNATURE_REFERENCE),
        _nNameIndex(nNameIndex),
        _nSignatureIndex(nSignatureIndex)
    { }

    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const CNameAndSignatureReference & rci);
};


/**
 * class CConstantPoolElement的具体形态，它表示一个ZLang global variable reference.
 */
class CGlobalVariableReference : public CConstantPoolElement {
  private:
    /** 指示这个global variable的access modifier. */
    zvm::TAccessModifierTag _eAccessModifierTag;
    /** 指向一个名称和类型引用. */
    zvm::TZVMIndex _nNameAndSignatureIndex;

  public:
    virtual bool operator==(const CConstantPoolElement & rciRight) const;

    virtual void DumpDetail() const;

    zvm::TAccessModifierTag GetAccessModifierTag() const
    {
      return _eAccessModifierTag;
    }

    zvm::TZVMIndex GetNameAndSignatureIndex() const
    {
      return _nNameAndSignatureIndex;
    }

    CGlobalVariableReference()
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_GLOBAL_VARIABLE_REFERENCE)
    { }

    CGlobalVariableReference(zvm::TZVMIndex nNameAndSignatureIndex,
                             zvm::TAccessModifierTag eAccessModifierTag)
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_GLOBAL_VARIABLE_REFERENCE),
        _nNameAndSignatureIndex(nNameAndSignatureIndex),
        _eAccessModifierTag(eAccessModifierTag)
    { }

    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const CGlobalVariableReference & rci);
};


/**
 * class CConstantPoolElement的具体形态，它表示一个ZLang global function reference.
 */
class CGlobalFunctionReference : public CConstantPoolElement {
  private:
    /** 指示这个global function的access modifier. */
    zvm::TAccessModifierTag _eAccessModifierTag;
    /** 指向一个名称和类型引用 */
    zvm::TZVMIndex _nNameAndSignatureIndex;

  public:
    virtual bool operator==(const CConstantPoolElement & rciRight) const;

    virtual void DumpDetail() const;

    zvm::TAccessModifierTag GetAccessModifierTag() const
    {
      return _eAccessModifierTag;
    }

    zvm::TZVMIndex GetNameAndSignatureIndex() const
    {
      return _nNameAndSignatureIndex;
    }

    CGlobalFunctionReference()
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_GLOBAL_FUNCTION_REFERENCE)
    { }

    CGlobalFunctionReference(zvm::TZVMIndex nNameAndSignatureIndex,
                             zvm::TAccessModifierTag eAccessModifierTag)
      : CConstantPoolElement(zvm::CONSTANT_POOL_ELEMENT_TAG_GLOBAL_FUNCTION_REFERENCE),
        _nNameAndSignatureIndex(nNameAndSignatureIndex),
        _eAccessModifierTag(eAccessModifierTag)
    { }

    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const CGlobalFunctionReference & rci);
};


/**
 * Constant pool for a ZLang object file.
 *
 * @todo InsertDoubleLiteral()由于strtod()的精度只有小数点后5位，所以精度受到限制.
 */
class CConstantPool {
  private:
    std::deque<CConstantPoolElement_auto> _dequePool;

  public:
    typedef std::deque<CConstantPoolElement_auto>::iterator        iterator;
    typedef std::deque<CConstantPoolElement_auto>::const_iterator  const_iterator;
    typedef std::deque<CConstantPoolElement_auto>::value_type      value_type;
    typedef std::deque<CConstantPoolElement_auto>::reference       reference;
    typedef std::deque<CConstantPoolElement_auto>::const_reference const_reference;
    typedef std::deque<CConstantPoolElement_auto>::size_type       size_type;

  public:
    const_iterator begin() const
    { return _dequePool.begin(); }

    const_iterator end() const
    { return _dequePool.end(); }

    const_reference operator[](size_type __n) const
    { return _dequePool.operator[](__n); }

    const_reference front() const
    { return _dequePool.front(); }

    const_reference back() const
    { return _dequePool.back(); }

    size_type size() const { return _dequePool.size(); }
    size_type max_size() const { return _dequePool.max_size(); }
    bool empty() const { return _dequePool.empty(); }

  public:
    /**
     * @name 插入操作.
     */
    //@{
    /**
     * 在constant pool中插入一个Nil-End string literal，如果该literal已经存在，则不再
     * 插入而返回其在constant pool中的index.
     *
     * @param rstring A NIL-End 'string' literal.
     * @return Index at pool.
     *
     * @attention 我的ZLang Lexer在扫描string literal时，即使已经碰到了'\0'，也
     * 还是继续扫描后面的字符，因此参数rstring实际上是一个可能(可以)内嵌'\0'的
     * std::string instance（std::string实际上是可以内嵌'\0'的）。而GNU C/C++
     * compiler's lexer在扫描string literal时则是碰到'\0'就停止继续扫描了.
     */
    zvm::TZVMIndex InsertNilEndStringLiteral(const std::string & rstring);

    /**
     * 在constant pool中插入一个Binary string literal，如果该literal已经存在，则不再
     * 插入而返回其在constant pool中的index.
     *
     * @param rstring A Nil-End 'string' literal.
     * @return Index at pool.
     *
     * @attention 我的ZLang Lexer在扫描string literal时，即使已经碰到了'\0'，也
     * 还是继续扫描后面的字符，因此参数rstring实际上是一个可能(可以)内嵌'\0'的
     * std::string instance（std::string实际上是可以内嵌'\0'的）。而GNU C/C++
     * compiler's lexer在扫描string literal时则是碰到'\0'就停止继续扫描了.
     */
    zvm::TZVMIndex InsertBinaryStringLiteral(const std::string & rstring);

    /**
     * 在constant pool中插入一个Rope string literal，如果该literal已经存在，则不再
     * 插入而返回其在constant pool中的index.
     *
     * @param rstring A Nil-End 'string' literal.
     * @return Index at pool.
     *
     * @attention 我的ZLang Lexer在扫描string literal时，即使已经碰到了'\0'，也
     * 还是继续扫描后面的字符，因此参数rstring实际上是一个可能(可以)内嵌'\0'的
     * std::string instance（std::string实际上是可以内嵌'\0'的）。而GNU C/C++
     * compiler's lexer在扫描string literal时则是碰到'\0'就停止继续扫描了.
     */
    zvm::TZVMIndex InsertRopeStringLiteral(const std::string & rstring);

    /**
     * 在constant pool中插入一个sdword literal，如果该literal已经存在，则不再
     * 插入而返回其在constant pool中的index.
     */
    /*
    zvm::TZVMIndex InsertSDWORDLiteral(const std::string & rstringText, int nBase);
    zvm::TZVMIndex InsertUDWORDLiteral(const std::string & rstringText, int nBase);
    */

    zvm::TZVMIndex InsertSQWORDLiteral(const std::string & rstringText, int nBase);
    zvm::TZVMIndex InsertUQWORDLiteral(const std::string & rstringText, int nBase);

    zvm::TZVMIndex InsertDoubleLiteral(const std::string & rstringText);
    zvm::TZVMIndex InsertPPortLiteral(const std::string & rstringText);
    zvm::TZVMIndex InsertIPv4AddressLiteral(const std::string & rstringText);

    /**
     * 为一个ZLang class field or local/global variable在constant pool中插入
     * name-and-signature-reference，如果该reference已经存在，则不再插入而返回其在
     * constant pool中的index.
     *
     * @param rstringName Name.
     * @param rstringSignature Signature.
     * @return Index at pool.
     */
    zvm::TZVMIndex InsertNameAndSignatureReference(const std::string & rstringName,
                                                   const std::string & rstringSignature);

    /**
     * 为一个ZLang global variable在constant pool中插入global-variable-reference，
     * 如果该reference已经存在，则不再插入而返回其在constant pool中的index.
     *
     * @param rstringName Name.
     * @param rstringSignature Signature.
     * @param eDeclarationTag 标识该global function是否的定义位置.
     * @return Index at pool.
     */
    zvm::TZVMIndex InsertGlobalVariableReference(const std::string & rstringName,
                                                 const std::string & rstringSignature,
                                                 zvm::TAccessModifierTag eAccessTag);

    /**
     * 为一个外部/内部的ZLang global function在constant pool中插入global-function-reference，
     * 如果该reference已经存在，则不再插入而返回其在constant pool中的index.
     *
     * @param nNameAndSignatureIndex 该global function的name-and-type-reference.
     * @param eDeclarationTag 标识该global function是否的定义位置.
     * @return Index at pool.
     */
    zvm::TZVMIndex InsertGlobalFunctionReference(const std::string & rstringFunctionName,
                                                 const std::string & rstringFunctionSignature,
                                                 zvm::TAccessModifierTag eAccessTag);

    /**
     * 在constant pool中插入一个CConstantPoolElement_auto，如果该constant已经存在，
     * 则不再插入而返回其在constant pool中的index.
     *
     * @param rautoElement A CConstantPoolElement smart-pointer reference.
     * @return Index at pool.
     */
    zvm::TZVMIndex Insert(CConstantPoolElement_auto & rautoElement);
    //@}


    /**
     * @name 查找操作.
     */
    //@{
    /**
     * 在constant pool中查找是否有这样的Element，查找的方法是利用各种CConstantPoolElement
     * 的派生类各自overload的operator==().
     *
     * @param rautoElement 一个被查找元素的CConstantPoolElement的Smart pointer.
     * @return -1表示查找失败，>=0表示被找到的这个元素在constant pool中的index.
     */
    zvm::TZVMIndex Find(const CConstantPoolElement_auto & rautoElement);
    //@}

    /**
     * Dump content to stdout.
     */
    void DumpDetail() const;

    /**
     * Default Constructor.
     */
    CConstantPool()
    { }

    /**
     * @name Binary file stream操作.
     */
    //@{
    friend zfc::CBinaryOutputFileStream & operator<<(zfc::CBinaryOutputFileStream & bos,
                                                     const CConstantPool & rciPool);
    //@}
};


ZLS_END_NAMESPACE


#endif

