/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CGlobalVariableRegisterEntry.hpp,v $
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


#ifndef _ZLS_zvm_CGlobalVariableRegisterEntry_hpp_
#define _ZLS_zvm_CGlobalVariableRegisterEntry_hpp_

#include <zls/zvm/CSlot.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


// forward declaration
class IDynamicLoadableModule;


/**
 * ZVM global variables register entry.
 */
class CGlobalVariableRegisterEntry {
  private:
    CGlobalVariableRegisterEntry & operator=(const CGlobalVariableRegisterEntry &);
    CGlobalVariableRegisterEntry(const CGlobalVariableRegisterEntry &);

    CSlot _ciVariableSlot;
    std::string _stringTypeSignature;  ///< Variable type signature.
    IDynamicLoadableModule * _pciOwnerModule;  ///< Belong to which loadable module.

  public:
    CSlot * GetVariableSlot()
    { return &_ciVariableSlot; }

    const std::string & GetTypeSignature() const
    { return _stringTypeSignature; }

    IDynamicLoadableModule * GetOwnerModule()
    { return _pciOwnerModule; }

    const IDynamicLoadableModule * GetOwnerModule() const
    { return _pciOwnerModule; }

    const std::string & GetSourceFileName() const;

    const std::string & GetObjectFileName() const;

    CGlobalVariableRegisterEntry(const std::string & rstringTypeSignature,
                                 IDynamicLoadableModule * pciOwnerModule);
};


typedef std::hash_map<std::string, CGlobalVariableRegisterEntry *> CGlobalVariableRegisterTable;


ZLS_END_NAMESPACE


#endif

