/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CZVMVirtualThread.cpp,v $
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


#include <zls/zvm/CInstructionDictionary.hpp>
#include <zls/zvm/CZVMVirtualThread.hpp>
#include <zls/zvm/CVirtualMachine.hpp>
#include <zls/zvm/CZVMObjectFile.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


CZVMVirtualThread::CZVMVirtualThread(CVirtualMachine * pciOwnerZVM)
  : _pciOwnerZVM(pciOwnerZVM)
{
  // 创建Stack
  _nStackCapacity = _pciOwnerZVM->GetDefaultVirtualThreadStackCapacity();
  _aciStack = new __OPTION(_THROW) CSlot[_nStackCapacity];
  memset(_aciStack, '\0', sizeof(CSlot) * _nStackCapacity);
  _pciStackHighWater = _aciStack + (_nStackCapacity - 1);

  _pciSPRegister = _aciStack;
  _pciBPRegister = _aciStack;
}


CZVMVirtualThread::~CZVMVirtualThread()
{
  delete [] _aciStack;
}


/******************************************************************************
 * 指令Interpreter's Helper methods
 ******************************************************************************/
/**
 * 当ZVM解释到ret指令时，throw这个exception，以便让主循环知道该return了.
 */
class EZVMTriggerFunctionReturn {
  public:
    EZVMTriggerFunctionReturn()
    { }
};


void CZVMVirtualThread::CallZVMFunction(const CZVMFunction * pciZVMFunction)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZVMVirtualThread::CallZVMFunction()");

  // 执行隐含"PushPC"的指令
  PushPCRegister();
  // 置PC新值
  _ciPCRegister.Set(pciZVMFunction);

  #if !defined(ENABLE_ZVM_OPTIMIZATION)  // 如果没有采用优化
  CInstructionDictionary_auto & rautoInstructionDictionary = GciInstructionDictionaryFactory.GetSingleton();
  CInstructionDictionary * pciInstructionDictionary = rautoInstructionDictionary.get();
  #endif

  const CInstruction * pciInstruction;
  try {
    __LOOP_INTERPRET__:
      pciInstruction = _ciPCRegister.GetInstruction();

      // 得到解析这条指令的Interperter
      #if defined(ENABLE_ZVM_OPTIMIZATION)  // 如果采用优化
        TInstructionInterpreter pfuncInterpreter = pciInstruction->GetInstructionInterpreter();
      #else
        TInstructionInterpreter pfuncInterpreter =
          pciInstructionDictionary->GetInstructionInterpreter(pciInstruction->GetInstructionCode());
      #endif

      // 调用这个Interpreter
      TZVMIndex nNextInstructionOffset = (this->*pfuncInterpreter)();

      // PC到下一条指令
      _ciPCRegister += nNextInstructionOffset;
      goto __LOOP_INTERPRET__;
  }
  catch (zvm::EZVMTriggerFunctionReturn & e)
  // 如果碰到了ret指令
  {
    return;
  }
  catch (zfc::EBaseException & e1)
  {
    const CZVMFunction * pciZVMFunction = _ciPCRegister.GetZVMFunction();
    const std::string & rstringSourceFileName = pciZVMFunction->GetOwnerObjectFile()->GetSourceFileName();
    const zvm::CNameAndSignatureReference * pciNSReference = pciZVMFunction->GetNameAndSignatureReference();
    const zvm::CInstruction * pciBegin = pciZVMFunction->GetInstructionSequence();
    TZVMIndex iInstruction = pciInstruction - pciBegin;
    std::string stringError = std::string("When interpreting the ") + iInstruction +
                              " instruction '" + pciInstruction->ToString() +
                              "' of function '" +
                              FunctionNameAndSignatureToPrettyString(pciNSReference->GetName(), pciNSReference->GetSignature()) +
                              "' at ";
    std::string stringTmp;
    if (pciZVMFunction->DebugInfoStriped())
    {
      stringTmp = "? line of '" + rstringSourceFileName + "'";
    }
    else
    {
      stringTmp = zfc::SDWORDToString(pciZVMFunction->InstructionIndexToLineNumber(iInstruction), 10) +
                  " line of '" + rstringSourceFileName + "'";
    }
    stringError += stringTmp;
    e1.AppendWhat(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);

    try {
      // Important: ZVM stack unwind
      _ret();
    }
    catch (zvm::EZVMTriggerFunctionReturn & ciReturn)
    {
    }

    // Important: C++ stack unwind
    throw;
  }
  catch (...)
  {
    const CZVMFunction * pciZVMFunction = _ciPCRegister.GetZVMFunction();
    const std::string & rstringSourceFileName = pciZVMFunction->GetOwnerObjectFile()->GetSourceFileName();
    const zvm::CNameAndSignatureReference * pciNSReference = pciZVMFunction->GetNameAndSignatureReference();
    const zvm::CInstruction * pciBegin = pciZVMFunction->GetInstructionSequence();
    TZVMIndex iInstruction = pciInstruction - pciBegin;
    if (pciZVMFunction->DebugInfoStriped())
    {
      LogError(("Fatal: When interpreting the %d instruction '%s' of function '%s' at ? line of '%s'\n",
                iInstruction,
                pciInstruction->ToString().c_str(),
                FunctionNameAndSignatureToPrettyString(pciNSReference->GetName(), pciNSReference->GetSignature()).c_str(),
                rstringSourceFileName.c_str()));
    }
    else
    {
      LogError(("Fatal: When interpreting the %d instruction '%s' of function '%s' at %d line of '%s'\n",
                iInstruction,
                pciInstruction->ToString().c_str(),
                FunctionNameAndSignatureToPrettyString(pciNSReference->GetName(), pciNSReference->GetSignature()).c_str(),
                pciZVMFunction->InstructionIndexToLineNumber(iInstruction),
                rstringSourceFileName.c_str()));
    }

    try {
      // Important: ZVM stack unwind
      _ret();
    }
    catch (zvm::EZVMTriggerFunctionReturn & ciReturn)
    {
    }

    // Important: C++ stack unwind
    throw;
  }
}


/*
const zvm::CGlobalVariableReference & CZVMVirtualThread::GetGlobalVariableReference()
{
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  TZVMIndex nVariableReference = pciInstruction->GetOperandAsTZVMIndex();
  const zvm::CConstantPool * pciConstantPool = _ciPCRegister.GetConstantPool();
  const zvm::CGlobalVariableReference & rciReference =
             pciConstantPool->GetAsGlobalVariableReference(nVariableReference);
  return rciReference;
}


CSlot * CZVMVirtualThread::GetGlobalVariableSlot(const zvm::CGlobalVariableReference & rciReference)
{
  TZVMIndex iOffset = rciReference.GetRelocatedOffset();
  CSlot * pciSlot = _pciGlobalDataSegment + iOffset;
  return pciSlot;
}
*/


CSlot * CZVMVirtualThread::GetGlobalVariableSlot()
{
  // 得到当前被执行得指令
  const CInstruction * pciInstruction = _ciPCRegister.GetInstruction();
  // 得到指令操作数
  TZVMIndex nVariableReference = pciInstruction->GetOperandAsTZVMIndex();
  // 得到Constant pool
  const zvm::CConstantPool * pciConstantPool = _ciPCRegister.GetConstantPool();
  // 得到Global variable reference
  const zvm::CGlobalVariableReference * pciReference =
             pciConstantPool->GetAsGlobalVariableReference(nVariableReference);
  // 得到global variable的slot
  CSlot * pciSlot = pciReference->GetRelocatedSlot();
  return pciSlot;
}


#if !defined(ENABLE_ZVM_OPTIMIZATION) || \
    (defined(ENABLE_ZVM_OPTIMIZATION) && ENABLE_ZVM_OPTIMIZATION < 2)
#include <zls/zvm/CZVMVirtualThread.inc.cpp>
#endif


/******************************************************************************
 * 指令Interpreter
 ******************************************************************************/
#include <zls/zvm/LoadValueInstruction.inc.cpp>
#include <zls/zvm/LoadAddressInstruction.inc.cpp>
#include <zls/zvm/StoreInstruction.inc.cpp>
#include <zls/zvm/BinaryInstruction.inc.cpp>
#include <zls/zvm/UnaryInstruction.inc.cpp>
#include <zls/zvm/MiscInstruction.inc.cpp>


ZLS_END_NAMESPACE

