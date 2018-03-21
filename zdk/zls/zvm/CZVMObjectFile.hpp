/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CZVMObjectFile.hpp,v $
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


#ifndef _ZLS_zvm_CZVMObjectFile_hpp_
#define _ZLS_zvm_CZVMObjectFile_hpp_

#include <zls/zfc/CBinaryInputFileStream.hpp>
#include <zls/zvm/Manifest.hpp>
#include <zls/zvm/ZVMException.hpp>
#include <zls/zvm/ConstantPool.hpp>
#include <zls/zvm/CZVMFunction.hpp>
#include <zls/zvm/IDynamicLoadableModule.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


// forward declaration
class CVirtualMachine;


class CZVMObjectFile : public IDynamicLoadableModule {
  private:
    /** Forbidden copy constructor. */
    CZVMObjectFile(const CZVMObjectFile &);
    /** Forbidden operator=(). */
    CZVMObjectFile & operator=(const CZVMObjectFile &);

  private:
    /**
     * @name Set by constructor.
     */
    //@{
    /**
     * 创建这个CZVMObjectFile的CVirtualMachine.
     * 注册、查找Global variables和functions时需要使用这个member variable.
     */
    CVirtualMachine * _pciOwnerZVM;

    /**
     * 这个Object file自己的文件名.
     */
    std::string _stringObjectFileName;
    //@}

    /**
     * @name 只有读入Object file后下列才有效.
     */
    //@{
    UDWORD _udwMagicNumber;
    UWORD  _uwMajorVersion;
    UWORD  _uwMinorVersion;

    zvm::CConstantPool          _ciConstantPool;
    TZVMIndex                   _nSourceFileNameIndex;
    std::vector<CZVMFunction *> _vectorGlobalFunctions;

    /**
     * 这个Object file自己的源代码文件名（读入Object file时立即解析）.
     */
    std::string _stringSourceFileName;
    //@}

    /**
     * @name Set by Linker.
     */
    //@{
    /**
     * 每个Object file中都有一个Compiler内部自动产生的static function，但
     * 又不暴露给用户，其功能是将Internal global variables的初始化行转换为
     * 相应的ZVM指令，从而完成对Internal gloabal variables的初始化.
     */
    CZVMFunction * _pciInitializerZVMFunction;
    //@}

    /**
     * Linking internal public global functions.
     *
     * @throw zvm::ELink1Failure.
     */
    void LinkInternalPublicGlobalFunction(TZVMIndex iTargetFunctionReference,
                                          zvm::CGlobalFunctionReference * pciFunctionReference);

    /**
     * Linking internal static global functions.
     *
     * @throw zvm::ELink1Failure.
     */
    void LinkInternalStaticGlobalFunction(TZVMIndex iTargetFunctionReference,
                                          zvm::CGlobalFunctionReference * pciFunctionReference);

  public:
    virtual const std::string & GetModuleName() const
    { return _stringSourceFileName; }

    virtual const std::string & GetSourceFileName() const
    { return _stringSourceFileName; }

    virtual const std::string & GetObjectFileName() const
    { return _stringObjectFileName; }

    const zvm::CConstantPool & GetConstantPool() const
    { return _ciConstantPool; }

    /**
     * 将这个CZVMObjectFile的内容按照pretty的格式dump到stdout.
     *
     * @throw zfc::EPanic 当CInstruction::_uchInstructionCode或
     * CInstruction::_uchOperandByteCount不合法时。但是如果ZLang compiler
     * 是正确无误的话，则这是一个"不可能的任务".
     */
    void DumpDetail() const;

    /**
     * 将所有function的Debug info去除掉，以节省ZVM占用的内存.
     */
    void StripDebugInfo();

    /**
     * 在Link之前进行的Object files完整性预检查，具体检查如下：
     * <pre>
     * (1) 每条指令的指令码正确否、其所需操作数的字节数符合否.
     * (2) 如果指令中涉及到Constant pool的Index，则检验Index合法否，类型兼容否.
     * (3) 如果指令涉及到code label，则检查其是否会越界.
     * </pre>
     *
     * @throw zvm::EVerifyFailure 当Object files的Byte codes完整性失效时.
     */
    void VerifyByteCodesIntegrity() const;

    /**
     * 进行第一遍link.
     *
     * @note Link1对Internal global function、Internal static function进行链接到
     * 对应的CZVMFunction instance，同时注册Internal global function到ZVM的注册
     * 表中；对Internal global variable则确定其在全局数据段中的Offset，同时注册
     * 它们到ZVM的注册表中.
     *
     * @throw zvm::ELink1Failure 通指第一遍link失败.
     */
    void Link1();

    /**
     * 进行第二遍link.
     *
     * @throw zlang::ELink2Failure 通指第二遍link失败.
     */
    void Link2();

    /**
     * Link完成后，同时Global data segment被成功construct后，就可以执行这个
     * Obejct file中的Initializer function来初值化global variables.
     */
    const CZVMFunction * GetInitializerZVMFunction()
    { return _pciInitializerZVMFunction; }

    /**
     * Constructor.
     *
     * @param pciOwnerZVM 创建这个CZVMObjectFile instance的CVirtualMachine instance.
     * @param rstringObjectFileName 告诉这个CZVMObjectFile它自己的文件名.
     */
    CZVMObjectFile(CVirtualMachine * pciOwnerZVM, const std::string & rstringObjectFileName);

    /**
     * Destructor.
     */
    ~CZVMObjectFile();

    /**
     * 读入Object file到指定的CZVMObjectFile instance中.
     *
     * @note 除读入Object file外，还同时做如下检查和解析
     * <pre>
     * (1) 检验Magic number、ZVM Version
     * (2) 解析_nSourceFileNameIndex.
     * </pre>
     * @throw zfc::EOutOfMemory.
     * @throw zvm::EInvalidObjectFile 当Object file不合法时，例如：读入
     * 时发生EOF或CInstruction::_uchOperandByteCount不合法时.
     * @throw std::ios_base::failure 当stream有问题.
     */
    friend zfc::CBinaryInputFileStream & operator>>(zfc::CBinaryInputFileStream & bis,
                                                    CZVMObjectFile & rciObjectFile);
};


ZLS_END_NAMESPACE


#endif

