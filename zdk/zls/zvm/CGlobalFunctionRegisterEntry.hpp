/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CGlobalFunctionRegisterEntry.hpp,v $
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


#ifndef _ZLS_zvm_CGlobalFunctionRegisterEntry_hpp_
#define _ZLS_zvm_CGlobalFunctionRegisterEntry_hpp_

#include <zls/zvm/CSlot.hpp>
#include <zls/zvm/CZVMFunction.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


// forward declaration
class IDynamicLoadableModule;


/**
 * ZVM global functions register entry.
 */
class CGlobalFunctionRegisterEntry {
  private:
    CGlobalFunctionRegisterEntry & operator=(const CGlobalFunctionRegisterEntry &);
    CGlobalFunctionRegisterEntry(const CGlobalFunctionRegisterEntry &);

    /**
     * @name Function register item.
     */
    //@{
    std::string _stringFunctionSignature;  ///< Global function type signature

    /** 该global function是用什么语言编写的. */
    TLanguageTag _eLanguageTag;
    union {
      /** 如果是用C++编写的，则选择这个字段. */
      TNativeFunction _pfuncNativeFunction;
      /** 如果是用ZLang script编写的，则选择这个字段. */
      const CZVMFunction * _pciZVMFunction;
    };

    IDynamicLoadableModule * _pciOwnerModule;  ///< Belong to which loadable module.
    //@}

    /**
     * @name Member variables will be set by DoCache().
     */
    //@{
    /** ZVM function返回值type signature对应的slot tag. */
    CSlot::TSlotTag _eReturnSlotTag;

    /** 打包每个参数的type signature对应的slot tag的container. */
    std::vector<CSlot::TSlotTag> _vectorArgumentsSlotTags;
    //@}

    void DoCache();

  public:
    const std::string & GetFunctionSignature() const
    { return _stringFunctionSignature; }

    IDynamicLoadableModule * GetOwnerModule()
    { return _pciOwnerModule; }

    const IDynamicLoadableModule * GetOwnerModule() const
    { return _pciOwnerModule; }

    TLanguageTag GetLanguageTag() const
    { return _eLanguageTag; }

    const std::string & GetSourceFileName() const;

    const std::string & GetObjectFileName() const;

    const CZVMFunction * GetZVMFunction() const
    { return _pciZVMFunction; }

    TNativeFunction GetNativeFunction() const
    { return _pfuncNativeFunction; }

    CSlot::TSlotTag GetReturnSlotTag() const
    { return _eReturnSlotTag; }

    const std::vector<CSlot::TSlotTag> & GetArgumentsSlotTags() const
    { return _vectorArgumentsSlotTags; }

    CGlobalFunctionRegisterEntry(const std::string & rstringFunctionSignature,
                                 const CZVMFunction * pciZVMFunction,
                                 IDynamicLoadableModule * pciOwnerModule);

    CGlobalFunctionRegisterEntry(const std::string & rstringFunctionSignature,
                                 TNativeFunction pfuncNativeFunction,
                                 IDynamicLoadableModule * pciOwnerModule);
};


typedef std::hash_map<std::string, CGlobalFunctionRegisterEntry *> CGlobalFunctionRegisterTable;


ZLS_END_NAMESPACE


#endif

