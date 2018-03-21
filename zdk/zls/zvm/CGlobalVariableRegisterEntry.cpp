/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CGlobalVariableRegisterEntry.cpp,v $
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


#include <zls/zvm/CGlobalVariableRegisterEntry.hpp>
#include <zls/zvm/IDynamicLoadableModule.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


const std::string & CGlobalVariableRegisterEntry::GetSourceFileName() const
{ return _pciOwnerModule->GetSourceFileName(); }


const std::string & CGlobalVariableRegisterEntry::GetObjectFileName() const
{ return _pciOwnerModule->GetObjectFileName(); }


CGlobalVariableRegisterEntry::CGlobalVariableRegisterEntry(
      const std::string & rstringTypeSignature,
      IDynamicLoadableModule * pciOwnerModule)
  : _stringTypeSignature(rstringTypeSignature),
    _pciOwnerModule(pciOwnerModule),
    _ciVariableSlot(rstringTypeSignature)
    //< May throw zfc::EOutOfMemory
{ }


ZLS_END_NAMESPACE

