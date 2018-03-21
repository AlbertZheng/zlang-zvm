/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CVirtualMachine.hpp,v $
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


#ifndef _ZLS_zvm_CVirtualMachine_hpp_
#define _ZLS_zvm_CVirtualMachine_hpp_

#include <zls/zvm/Manifest.hpp>
#include <zls/zvm/ZVMException.hpp>
#include <zls/zvm/CSlot.hpp>
#include <zls/zvm/CZVMFunction.hpp>
#include <zls/zvm/INativeLibraryImport.hpp>
#include <zls/zvm/CGlobalVariableRegisterEntry.hpp>
#include <zls/zvm/CGlobalFunctionRegisterEntry.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


// forward declaration
class CZVMVirtualThread;
class CZVMObjectFile;


/**
 *  ZLS Virtual Machine.
 *
 * <pre>
 *  ZVM的ld checker的检查流程：
 *  (1) 一个global variable表，它将登记已被重定位成功的global variable的name和
 *      其在data segment的offset;
 *  (2) 一个global function表，它将登记已被重定位成功的global function的name和
 *      其code segment的指针（或C function指针）;
 *  (3) 先将ZLang的系统Native library调入内存，库中包含有用C++编写的native global
 *      functions，将它们登记到上述的两个表中;
 *  (4) 将在命令行指定的所有".zo"文件（ZLang object file）逐个调入内存，这时要进
 *      行两遍的global variables和global functions重定位：
 *      pass1: 在每调入一个".zo"文件后，扫描其自己的constant pool，对于标识为非
 *             extern的global variables和global functions，就将它们登记到上述两
 *             个表中，如果发现冲突，则checking失败，给出error后退出，如果没有
 *             冲突，则对于global variables，用其被重定位在data segment的offset
 *             刷新自己的constant pool中，对于global functions，则还需扫描自己
 *             CZVMObjectFile中的CGlobalFunctionTable，得到那些functions的指针，
 *             然后刷新自己的constant pool;
 *      pass2: 在调入所有的".zo"文件，进行完pass1后，逐个扫描各个CZVMObjectFile
 *             的constant pool，对于标识为extern的global variables、global functions，
 *             查找上述的两个表，如果查找成功则刷新对这个constant pool，如果不成功，
 *             则checking失败，给出error后退出.
 * </pre>
 *
 * 使用这个class的基本步骤是：
 * <pre>
 * </pre>
 */
class CVirtualMachine {
  friend class CZVMVirtualThread;
  friend class CZVMObjectFile;

  public:
    enum TZVMState {
      STATE_DEFAULT = 0,  ///< 初始状态.
      STATE_OBJECT_FILES_LINKED_OK,  ///< 新调用的Obejct files被成功Link了.
      STATE_OBJECT_FILES_LINKED_NOTOK  ///< 新调用的Obejct files不能被成功Link.
    };

  private:
    typedef std::hash_map<std::string, CZVMObjectFile *> CObjectFileRegisterTable;
    typedef std::hash_map<std::string, INativeLibraryImport *> CLibraryRegisterTable;

  private:
    /**
     * @name 被调入的Byte codes在ZVM中的表现.
     */
    //@{
    /** 缺省的Virtual Thread Stack Capacity. */
    TZVMIndex _nDefaultVirtualThreadStackCapacity;

    /**
     * 调入内存的所有的全局变量的注册表.
     */
    CGlobalVariableRegisterTable _hmapGlobalVariableRegisterTable;

    /** 调入内存的所有的全局function的注册表. */
    CGlobalFunctionRegisterTable _hmapGlobalFunctionRegisterTable;

    /**
     * 已被Link成功的各个目标文件.
     */
    CObjectFileRegisterTable _hmapLinkedObjectFiles;

    /**
     * 还没被Link的各个目标文件.
     */
    CObjectFileRegisterTable _hmapUnlinkedObjectFiles;

    /**
     * 被输入的Native librarys.
     */
    CLibraryRegisterTable _hmapImportedLibrarys;
    //@}

    bool _bInitializerZVMVirtualThreadUnilized;
    CZVMVirtualThread * _pciInitializerZVMVirtualThread;
    std::vector<CZVMVirtualThread *> _vectorCreatedZVMVirtualThreads;

    /** ZVM的当前状态. */
    TZVMState _eZVMState;

    void UnregisterGlobalVariables(std::vector<CGlobalVariableRegisterTable::iterator> & rvector);
    void UnregisterGlobalFunctions(std::vector<CGlobalFunctionRegisterTable::iterator> & rvector);

    /**
     * 注册一个Global variable.
     *
     * @return 这个global variable在全局数据段中被重定位的offset.
     * @throw zvm::ELink1Failure.
     */
    CGlobalVariableRegisterTable::iterator
    RegisterGlobalVariable(const std::string & rstringVariableName,
                           const std::string & rstringTypeSignature,
                           IDynamicLoadableModule * pciOwnerModule);

    /**
     * 注册一个Global ZVM function.
     *
     * @throw zvm::ELink1Failure.
     */
    CGlobalFunctionRegisterTable::iterator
    RegisterGlobalFunction(const std::string & rstringFunctionName,
                           const std::string & rstringFunctionSignature,
                           const CZVMFunction * pciZVMFunction,
                           IDynamicLoadableModule * pciOwnerModule);

    /**
     * 注册一个Global native library function.
     *
     * @throw zvm::ELink1Failure.
     */
    CGlobalFunctionRegisterTable::iterator
    RegisterGlobalFunction(const std::string & rstringFunctionName,
                           const std::string & rstringFunctionSignature,
                           TNativeFunction pfuncNativeFunction,
                           IDynamicLoadableModule * pciOwnerModule);

    /** 取得被配置的确省ZVM Stack的大小. */
    TZVMIndex GetDefaultVirtualThreadStackCapacity() const
    { return _nDefaultVirtualThreadStackCapacity; }

    void ClearGlobalVariableRegisterTable();
    void ClearGlobalFunctionRegisterTable();
    void ClearLinkedObjectFiles();
    void ClearUnlinkedObjectFiles();
    void ClearImportedLibrarys();

    /**
     * 查找已注册的某个Global variable的信息.
     *
     * @return 如果为0指针则表示查找失败.
     */
    CGlobalVariableRegisterEntry *
    FindRegisteredGlobalVariable(const std::string & rstringVariableName,
                                 const std::string & rstringVariableSignature);

    /**
     * 查找已注册的某个Global function的信息.
     *
     * @return 如果为0指针则表示查找失败.
     */
    CGlobalFunctionRegisterEntry *
    FindRegisteredGlobalFunction(const std::string & rstringFunctionName,
                                 const std::string & rstringFunctionSignature);

  public:
    void DumpDetail();

    TZVMState GetState() const
    { return _eZVMState; }

    /**
     * 将ZVM恢复到Constructor刚完成时的状态，以便能够重新进行load object files等
     * 工作.
     */
    void Reset();

    /**
     * 输入Native library.
     *
     * @param rciImport Native library的Import描述信息.
     * @throw zvm::EImportNativeLibraryFailure.
     */
    void ImportNativeLibrary(const INativeLibraryImport & rciImportLibrary);

    /**
     * 调入所要求的Object file，并置状态为_eZVMState为STATE_NEW_OBJECT_FILES_LOADED.
     *
     * @param rstringObjectFileName 所要求调入的Object file的Name.
     * @param bStripDebugInfo 指示是否去除Debug info，以节省ZVM占用的内存.
     * @throw zvm::ELoadObjectFileFailure.
     */
    void DynamicLoadObjectFile(const std::string & rstringObjectFileName,
                               bool bStripDebugInfo = false);

    /**
     * 卸载已经被调入的某个Object file.
     *
     * @param rstringObjectFileName 所要求卸载的Object file的Name.
     */
    void DynamicUnloadObjectFile(const std::string & rstringObjectFileName);

    /**
     * 对所有调入的Object files进行Link，并置状态为_eZVMState为STATE_OBJECT_FILES_LINKED.
     *
     * @note Link的工作包括Link1、Link2、Check Byte Codes Integrity、Construct
     * global data segment.
     * @throw zfc::EInvalidState 当Object files还没被调入或调入失败时还想
     * 进行link.
     * @throw zvm::ELinkFailure.
     */
    void Link();

    /**
     * 创建一个ZVM virtual thread.
     */
    CZVMVirtualThread * CreateZVMVirtualThread();

    /**
     * 删除被创建的一个ZVM virtual thread.
     *
     * @throw zfc::EInvalidArgument 如果这个pciWhich是一个无效的
     * 'CZVMVirtualThread *'的话.
     */
    void DeleteZVMVirtualThread(CZVMVirtualThread * pciWhich);

    /**
     * 比较严格地查找已注册的某个Global variable的信息，以防止variable name是对的，
     * 而在#include中的variable declaration却是有误的.
     *
     * @return 如果为0指针则表示查找失败.
     */
    const CGlobalVariableRegisterEntry *
    FindRegisteredGlobalVariable(const std::string & rstringVariableName,
                                 const std::string & rstringVariableSignature) const;

    /**
     * 比较严格地查找已注册的某个Global function的信息，以防止function name是对的，
     * 而在#include中的function declaration却是有误的.
     *
     * @return 如果为0指针则表示查找失败.
     */
    const CGlobalFunctionRegisterEntry *
    FindRegisteredGlobalFunction(const std::string & rstringFunctionName,
                                 const std::string & rstringFunctionSignature) const;

    /**
     * 查找已注册的某个Global variable的信息.
     *
     * @return 如果为0指针则表示查找失败.
     */
    const CGlobalVariableRegisterEntry *
    FindRegisteredGlobalVariable(const std::string & rstringVariableName) const;

    /**
     * 查找已注册的某个Global function的信息.
     *
     * @return 如果为0指针则表示查找失败.
     */
    const CGlobalFunctionRegisterEntry *
    FindRegisteredGlobalFunction(const std::string & rstringFunctionName) const;

    /** Default constructor. */
    CVirtualMachine(TZVMIndex nDefaultVirtualThreadStackCapacity = 1500);

    /** Destructor. */
    ~CVirtualMachine();
};


ZLS_END_NAMESPACE


#endif

