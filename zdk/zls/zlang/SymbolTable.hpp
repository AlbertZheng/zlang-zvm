/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/SymbolTable.hpp,v $
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


#ifndef _ZLS_zlang_SymbolTable_hpp_
#define _ZLS_zlang_SymbolTable_hpp_

#include <zls/zvm/Manifest.hpp>
#include <zls/zfc/SmartPointer.hpp>
#include <zls/zlang/ZLangException.hpp>



// Begin namespace 'zlang::'

ZLS_BEGIN_NAMESPACE(zlang)


// forward declaration
class CSymbol;
class CSymbolAttributes;

typedef zfc::CSmartPointerT<CSymbol>         CSymbol_auto;
typedef zfc::CSmartPointerT<CSymbolAttributes>       CSymbolAttributes_auto;


/**
 * 表示Symbol table中的Symbol.
 *
 * @attention 该class还不符合STL的基本要求，所以在STL的容器中只能包含该class的
 * 指针。同时由于该class还可内嵌symbol table，而C++不是动态语言（在class中不能
 * 内嵌自己class实例），因此下面的CSymbol::CSymbolHashMap也只能使用包含指针.
 *
 * @todo
 * <pre>
 * (1)function符号名采用将参数的类型签名添加到function名后面，以支持函数重载.
 * </pre>
 */
class CSymbol : public zfc::CReferenceCounter {
  private:
    /** Forbidden copy constructor and operator=(). */
    CSymbol(const CSymbol & rci);
    CSymbol & operator=(const CSymbol & rci);

  public:
    enum TSymbolTag {
     TAG_GLOBAL_FUNCTION = 0,  ///< denote ZLang Global Function.
     TAG_GLOBAL_VARIABLE,      ///< denote ZLang Global Variable.
     TAG_LOCAL_VARIABLE,       ///< denote ZLang Local Variable.
     TAG_PARAMETER             ///< denote ZLang Parameter.
    };

  public:
    typedef std::hash_map<std::string, CSymbol_auto> CSymbolHashMap;

  private:
    static const CSymbolHashMap::size_type _nDefaultBuckets = 16;
    static const std::string _SastringTagTexts[];

    TSymbolTag             _eSymbolTag;
    CSymbolHashMap         _hmapNextNest;
    std::string            _stringSymbolName;
    std::string            _stringNamespace;
    int                    _nNestLevel;
    CSymbolAttributes_auto _autoAttributes;

  public:
    static const std::string & SymbolTagToString(TSymbolTag eSymbolTag);

    CSymbolHashMap * GetNextNestHashMap()
    {
      return(&_hmapNextNest);
    }

    const std::string & GetSymbolName() const
    {
      return(_stringSymbolName);
    }

    const std::string & GetNamespace() const
    {
      return(_stringNamespace);
    }

    int GetNestLevel() const
    {
      return(_nNestLevel);
    }

    const CSymbolAttributes_auto & GetAttributes() const
    {
      return(_autoAttributes);
    }

    TSymbolTag GetSymbolTag() const
    {
      return(_eSymbolTag);
    }

    void DumpDetail();

    CSymbol(TSymbolTag eSymbolTag,
            const std::string & rstringName,
            const std::string & rstringNamespace,
            int nNestLevel,
            CSymbolAttributes * pciAttributes);

    ~CSymbol();
};


/**
 * Symbol table.
 *
 * @attention 由于上面的CSymbol::CSymbolHashMap也只能使用包含指针，因此这个class
 * 也只能如此.
 */
class CSymbolTable {
  public:
    typedef std::hash_map<std::string, CSymbol_auto> CSymbolHashMap;

  private:
    static const CSymbolHashMap::size_type _nDefaultBuckets = 16;
    CSymbolHashMap _hmapFirstNest;  /**< 第一层的symbol table implementation. */

    CSymbol_auto & _InsertSymbol(CSymbolHashMap * phmap,
                                 const std::string & rstringName,
                                 const std::string & rstringNamespace,
                                 int nNestLevel,
                                 CSymbolAttributes * pciAttributes);

    /**
     * 查找一个Symbol.
     *
     * @throw ESymbolNotFound 当查找失败时.
     */
    CSymbol_auto & _FindSymbol(CSymbolHashMap * phmap,
                               const std::string & rstringName,
                               const std::string & rstringUnifyName);


    void _DumpDetail(CSymbolHashMap * phmap);

  public:
    static std::string ToUnifyName(const std::vector<std::string> & rvectorFindNames);

    CSymbolHashMap * GetFirstNestHashMap()
    {
      return(&_hmapFirstNest);
    }

    /**
     * 插入一个符号到符号表.
     *
     * @throw ESymbolInsertFailure 当插入失败时.
     */
    CSymbol_auto & InsertSymbol(const std::vector<std::string> & rvectorFindNames,
                                CSymbolAttributes * pciAttributes);

    /**
     * 在符号表中查找一个符号.
     *
     * @throw ESymbolNotFound 当查找失败时.
     */
    CSymbol_auto & FindSymbol(const std::vector<std::string> & rvectorFindNames);

    void DumpDetail();

    CSymbolTable()
      : _hmapFirstNest(_nDefaultBuckets)
    { }
};


/**
 * Base class for Symbol's attributes.
 */
class CSymbolAttributes : public zfc::CReferenceCounter {
  private:
    CSymbol::TSymbolTag _eSymbolTag;

  public:
    CSymbolAttributes(CSymbol::TSymbolTag eSymbolTag)
      : _eSymbolTag(eSymbolTag)
    { }

    virtual ~CSymbolAttributes() = 0;

    CSymbol::TSymbolTag GetSymbolTag() const
    {
      return(_eSymbolTag);
    }

    virtual void DumpDetail() = 0;
};


class CFunctionSymbolAttributes : public CSymbolAttributes {
  protected:
    std::string _stringReturnSignature;
    std::string _stringFunctionSignature;

  public:
    CFunctionSymbolAttributes(CSymbol::TSymbolTag eTag)
      : CSymbolAttributes(eTag)
    { }

    virtual ~CFunctionSymbolAttributes();

    const std::string & GetReturnSignature() const
    {
      return(_stringReturnSignature);
    }
    void SetReturnSignature(const std::string & rstringReturnSignature)
    {
      _stringReturnSignature = rstringReturnSignature;
    }

    const std::string & GetFunctionSignature() const
    {
      return(_stringFunctionSignature);
    }
    void SetFunctionSignature(const std::string & rstringFunctionSignature)
    {
      _stringFunctionSignature = rstringFunctionSignature;
    }

    virtual void DumpDetail() = 0;
};


class CGlobalFunctionSymbolAttributes : public CFunctionSymbolAttributes {
  private:
    zvm::TAccessModifierTag _eAccessModifierTag;

  public:
    CGlobalFunctionSymbolAttributes(zvm::TAccessModifierTag eAccessModifierTag)
      : CFunctionSymbolAttributes(CSymbol::TAG_GLOBAL_FUNCTION),
        _eAccessModifierTag(eAccessModifierTag)
    { }

    virtual ~CGlobalFunctionSymbolAttributes();

    zvm::TAccessModifierTag GetAccessModifierTag() const
    {
      return _eAccessModifierTag;
    }

    virtual void DumpDetail();
};


class CVariableSymbolAttributes : public CSymbolAttributes {
  protected:
    std::string _stringVariableSignature;

  public:
    CVariableSymbolAttributes(CSymbol::TSymbolTag eTag)
      : CSymbolAttributes(eTag)
    { }

    virtual ~CVariableSymbolAttributes();

    const std::string & GetVariableSignature() const
    {
      return _stringVariableSignature;
    }
    void SetVariableSignature(const std::string & rstringVariableSignature)
    {
      _stringVariableSignature = rstringVariableSignature;
    }

    virtual void DumpDetail() = 0;
};


class CGlobalVariableSymbolAttributes : public CVariableSymbolAttributes {
  private:
    zvm::TAccessModifierTag _eAccessModifierTag;

  public:
    CGlobalVariableSymbolAttributes(zvm::TAccessModifierTag eAccessModifierTag)
      : CVariableSymbolAttributes(CSymbol::TAG_GLOBAL_VARIABLE),
        _eAccessModifierTag(eAccessModifierTag)
    { }

    virtual ~CGlobalVariableSymbolAttributes();

    zvm::TAccessModifierTag GetAccessModifierTag() const
    {
      return _eAccessModifierTag;
    }

    virtual void DumpDetail();
};


class CStackVariableSymbolAttributes : public CVariableSymbolAttributes {
  protected:
    zvm::TZVMIndex _nIndex;  /**< 指示这是第几个，从1开始编号. */

    /**
     * 如果是Parameter，则_nBPOffset是负的，第一个参数为1(index)-CountOfParameters-2，
     * 第二个参数为2(index)-CountOfParameters-2，第n个参数为n(index)-CountOfParameters-2；
     * 如果是Local Variable，则_nBPOffset是正的，第一个Local Variable为1，第n个
     * Local Variable为n.
     */
    SWORD _nBPOffset;

  public:
    CStackVariableSymbolAttributes(CSymbol::TSymbolTag eTag, zvm::TZVMIndex nIndex)
      : CVariableSymbolAttributes(eTag),
        _nIndex(nIndex),
        _nBPOffset(0)
    { }

    virtual ~CStackVariableSymbolAttributes();

    const SWORD GetBPOffset() const
    {
      return(_nBPOffset);
    }

    const zvm::TZVMIndex GetIndex() const
    {
      return(_nIndex);
    }

    virtual void DumpDetail() = 0;
};


class CLocalVariableSymbolAttributes : public CStackVariableSymbolAttributes {
  public:
    CLocalVariableSymbolAttributes(zvm::TZVMIndex nIndex)
      : CStackVariableSymbolAttributes(CSymbol::TAG_LOCAL_VARIABLE, nIndex)
    {
      _nBPOffset = static_cast<SWORD>(nIndex);
    }

    virtual ~CLocalVariableSymbolAttributes();

    virtual void DumpDetail();
};


class CParameterSymbolAttributes : public CStackVariableSymbolAttributes {
  public:
    CParameterSymbolAttributes(zvm::TZVMIndex nIndex)
      : CStackVariableSymbolAttributes(CSymbol::TAG_PARAMETER, nIndex)
    { }

    virtual ~CParameterSymbolAttributes();

    void AdjustBPOffset(int nParameterTotal)
    {
      _nBPOffset = static_cast<SWORD>(_nIndex - nParameterTotal - 2);
    }

    /** 'GetParameterSignature()' is the pretty name of 'GetVariableSignature()'. */
    const std::string & GetParameterSignature() const
    {
      return GetVariableSignature();
    }
    /** 'SetParameterSignature()' is the pretty name of 'SetVariableSignature()'. */
    void SetParameterSignature(const std::string & rstringParameterSignature)
    {
      SetVariableSignature(rstringParameterSignature);
    }

    virtual void DumpDetail();
};


ZLS_END_NAMESPACE


#endif

