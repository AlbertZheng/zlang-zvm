/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/IDynamicLoadableModule.hpp,v $
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


#ifndef _ZLS_zvm_IDynamicLoadableModule_hpp_
#define _ZLS_zvm_IDynamicLoadableModule_hpp_

#include <zls/zvm/CGlobalVariableRegisterEntry.hpp>
#include <zls/zvm/CGlobalFunctionRegisterEntry.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


class IDynamicLoadableModule {
  private:
    /** Forbidden operator=(). */
    IDynamicLoadableModule & operator=(const IDynamicLoadableModule &);
    /** Forbidden copy constructor. */
    IDynamicLoadableModule(const IDynamicLoadableModule &);

    /** 该Module中的global variable和global function被其它Modules引用的总计次数. */
    UDWORD _udwReferencedCount;
    std::vector<CGlobalVariableRegisterTable::iterator> _vectorMyGlobalVariables;
    std::vector<CGlobalFunctionRegisterTable::iterator> _vectorMyGlobalFunctions;

  public:
    UDWORD IncreaseReferencedCount()
    { return ++_udwReferencedCount; }

    UDWORD GetReferencedCount() const
    { return _udwReferencedCount; }

    void AppendGlobalVariablesRegisterIterator(const CGlobalVariableRegisterTable::iterator & rit)
    { _vectorMyGlobalVariables.push_back(rit); }

    void AppendGlobalFunctionsRegisterIterator(const CGlobalFunctionRegisterTable::iterator & rit)
    { _vectorMyGlobalFunctions.push_back(rit); }

    std::vector<CGlobalVariableRegisterTable::iterator> & GetGlobalVariablesRegisterIterators()
    { return _vectorMyGlobalVariables; }

    std::vector<CGlobalFunctionRegisterTable::iterator> & GetGlobalFunctionsRegisterIterators()
    { return _vectorMyGlobalFunctions; }

    virtual const std::string & GetModuleName() const = 0;
    virtual const std::string & GetSourceFileName() const = 0;
    virtual const std::string & GetObjectFileName() const = 0;

    IDynamicLoadableModule()
      : _udwReferencedCount(0)
    { }

    virtual ~IDynamicLoadableModule()
    { }
};


ZLS_END_NAMESPACE


#endif

