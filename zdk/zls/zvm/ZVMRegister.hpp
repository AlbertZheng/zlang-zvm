/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/ZVMRegister.hpp,v $
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


#ifndef _ZLS_zvm_ZVMRegister_hpp_
#define _ZLS_zvm_ZVMRegister_hpp_

#include <zls/zvm/Manifest.hpp>
#include <zls/zvm/CZVMFunction.hpp>
#include <zls/zvm/CInstruction.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


// forward declaration
class CConstantPool;


/**
 * ZVM PC register.
 */
class CPCRegister {
  private:
    /** 保存"CZVMFunction *"只是为了出错时能够debug line number. */
    const zvm::CZVMFunction * _pciZVMFunction;
    const zvm::CConstantPool * _pciConstantPool;
    const zvm::CInstruction * _pciInstruction;

  public:
    void Set(const CZVMFunction * pciZVMFunction)
    {
      _pciZVMFunction = pciZVMFunction;
      _pciConstantPool = pciZVMFunction->GetConstantPool();
      _pciInstruction = pciZVMFunction->GetInstructionSequence();
    }

    const zvm::CZVMFunction * GetZVMFunction() const
    {
      return _pciZVMFunction;
    }

    const zvm::CConstantPool * GetConstantPool() const
    {
      return _pciConstantPool;
    }

    const zvm::CInstruction * GetInstruction() const
    {
      return _pciInstruction;
    }

    CPCRegister & operator+=(TZVMIndex nOffset)
    {
      _pciInstruction += nOffset;
      return *this;
    }

    CPCRegister & operator=(const CPCRegister & rciOther)
    {
      _pciZVMFunction = rciOther._pciZVMFunction;
      _pciConstantPool = rciOther._pciConstantPool;
      _pciInstruction = rciOther._pciInstruction;
      return *this;
    }

    /** @attention 仅仅比较CPCRegister instance指针相同否. */
    bool operator==(const CPCRegister & rciOther) const
    {  return this == &rciOther; }

    /** @attention 仅仅比较CPCRegister instance指针相同否. */
    bool operator!=(const CPCRegister & rciOther) const
    {  return this != &rciOther; }

    CPCRegister(const CPCRegister & rciOther)
    {
      _pciZVMFunction = rciOther._pciZVMFunction;
      _pciConstantPool = rciOther._pciConstantPool;
      _pciInstruction = rciOther._pciInstruction;
    }

    CPCRegister()
      : _pciZVMFunction(0),
        _pciConstantPool(0),
        _pciInstruction(0)
    { }
};


/**
 * ZVM Object register.
 */
/* 2001/7/17: Discarded
template <class TObject>
class CZVMObjectRegister {
  private:
    TObject _pci;

  public:
    TObject * GetObjectAddress()
    {
      return &_pci;
    }

    void Replace(TObject pciNeedStoredTempObject)
    {
      delete _pci;  // delete old
      _pci = pciNeedStoredTempObject;
    }

    CZVMObjectRegister()
      : _pci(0)
    { }

    ~CZVMObjectRegister()
    { delete _pci; }
};


typedef CZVMObjectRegister<CZVMString *> CZVMStringObjectRegister;
typedef CZVMObjectRegister<CZVMIPv4Address *> CZVMIPv4AddressObjectRegister;
typedef CZVMObjectRegister<CZVMPPort *> CZVMPPortObjectRegister;
typedef CZVMObjectRegister<CZVMTable *> CZVMTableObjectRegister;
*/


ZLS_END_NAMESPACE


#endif

