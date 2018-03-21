/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/INativeLibraryImport.hpp,v $
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

 
#ifndef _ZLS_zvm_INativeLibraryImport_hpp_
#define _ZLS_zvm_INativeLibraryImport_hpp_


#include <zls/zfc/Manifest.h>
#include <zls/zvm/CZVMFunction.hpp>
#include <zls/zvm/IDynamicLoadableModule.hpp>


// Begin namespace 'zvm::'
ZLS_BEGIN_NAMESPACE(zvm)


class INativeLibraryImport : public IDynamicLoadableModule {
  public:
    struct TNativeFunctionImportEntry {
      private:
        /**
         * Native library function name.
         */
        std::string _stringFunctionName;

        /**
         * Native library function的signature.
         * 这个signature将被用在CFunctionInvokeInterface::PassReferenceArgument()
         * 的代码中.
         */
        std::string _stringFunctionSignature;

        /**
         * Native library function pointer.
         */
        TNativeFunction _pfuncNativeFunction;

      public:
        const std::string & GetFunctionName() const
        { return _stringFunctionName; }

        const std::string & GetFunctionSignature() const
        { return _stringFunctionSignature; }

        TNativeFunction GetNativeFunction() const
        { return _pfuncNativeFunction; }

        TNativeFunctionImportEntry & operator=(const TNativeFunctionImportEntry & rci);

        TNativeFunctionImportEntry(const TNativeFunctionImportEntry & rci)
        { operator=(rci); }

        TNativeFunctionImportEntry(const std::string & rstringFunctionName,
                                   const std::string & rstringFunctionSignature,
                                   TNativeFunction pfuncNativeFunction);
    };

  protected:
    std::string _stringLibraryName;
    std::string _stringSourceFileName;
    std::string _stringObjectFileName;
    std::vector<TNativeFunctionImportEntry> _vectorNativeFunctionImportTable;

    void AppendNativeFunctionImportEntry(const std::string & rstringFunctionName,
                                         const std::string & rstringFunctionSignature,
                                         TNativeFunction pfuncNativeFunction);

  public:
    virtual const std::string & GetModuleName() const
    { return _stringLibraryName; }

    virtual const std::string & GetSourceFileName() const
    { return _stringSourceFileName; }

    virtual const std::string & GetObjectFileName() const
    { return _stringObjectFileName; }

    const std::string & GetLibraryName() const
    { return _stringLibraryName; }

    const std::vector<TNativeFunctionImportEntry> & GetNativeFunctionImportTable() const
    { return _vectorNativeFunctionImportTable; }

    void ClearNativeFunctionImportTable()
    { _vectorNativeFunctionImportTable.clear(); }

    INativeLibraryImport & operator=(const INativeLibraryImport & rci);

    INativeLibraryImport(const INativeLibraryImport & rci)
    { operator=(rci); }

    INativeLibraryImport(const std::string & rstringLibraryName,
                         const std::string & rstringSourceFileName,
                         const std::string & rstringObjectFileName);

    virtual ~INativeLibraryImport()
    { }
};


ZLS_END_NAMESPACE


#endif

