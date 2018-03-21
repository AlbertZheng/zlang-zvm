/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CVirtualMachine.cpp,v $
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


#include <zls/zvm/CVirtualMachine.hpp>
#include <zls/zvm/CZVMObjectFile.hpp>
#include <zls/zvm/CZVMVirtualThread.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


/******************************************************************************
 * CVirtualMachine
 ******************************************************************************/
CVirtualMachine::CVirtualMachine(TZVMIndex nDefaultVirtualThreadStackCapacity = 1500)
  : _eZVMState(STATE_DEFAULT),
    _nDefaultVirtualThreadStackCapacity(nDefaultVirtualThreadStackCapacity)
{
  // Creating first ZVM virtual thread
  _pciInitializerZVMVirtualThread = new __OPTION(_THROW) CZVMVirtualThread(this);
  _bInitializerZVMVirtualThreadUnilized = false;
}


CVirtualMachine::~CVirtualMachine()
{
  Reset();
  // Deleting first ZVM virtual thread
  delete _pciInitializerZVMVirtualThread;
}


CZVMVirtualThread * CVirtualMachine::CreateZVMVirtualThread()
{
  if (! _bInitializerZVMVirtualThreadUnilized)
  {
    _bInitializerZVMVirtualThreadUnilized = true;
    return _pciInitializerZVMVirtualThread;
  }
  else
  {
    CZVMVirtualThread * pci = new __OPTION(_THROW) CZVMVirtualThread(this);
    _vectorCreatedZVMVirtualThreads.push_back(pci);
    return pci;
  }
}


void CVirtualMachine::DeleteZVMVirtualThread(CZVMVirtualThread * pciWhich)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CVirtualMachine::DeleteZVMVirtualThread()");
  if (pciWhich == _pciInitializerZVMVirtualThread)
  {
    _bInitializerZVMVirtualThreadUnilized = false;
  }
  else
  {
    std::vector<CZVMVirtualThread *>::iterator it;
    for (it = _vectorCreatedZVMVirtualThreads.begin();
         it != _vectorCreatedZVMVirtualThreads.end();
         ++it)
    {
      if (*it == pciWhich)
      {
        delete pciWhich;
        _vectorCreatedZVMVirtualThreads.erase(it);
        return;
      }
    }

    std::string stringError = "Bug: Invalid 'CZVMVirtualThread *'";
    throw zfc::EInvalidArgument(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
  }
}


CGlobalVariableRegisterTable::iterator CVirtualMachine::RegisterGlobalVariable(
      const std::string & rstringVariableName,
      const std::string & rstringTypeSignature,
      IDynamicLoadableModule * pciOwnerModule)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CVirtualMachine::RegisterGlobalVariable()");
  std::string stringError;

  CGlobalVariableRegisterTable::iterator it;
  if ((it = _hmapGlobalVariableRegisterTable.find(rstringVariableName))
      != _hmapGlobalVariableRegisterTable.end())
  // If duplicate global variable
  {
    CZVMErrorReporter::ThrowError_MultipleDefinitionSymbol(__FILE__, __PRETTY_FUNC__ , __LINE__,
                                                           "global variable",
                                                           rstringVariableName,
                                                           pciOwnerModule->GetSourceFileName(),
                                                           pciOwnerModule->GetObjectFileName(),
                                                           (*it).second->GetSourceFileName(),
                                                           (*it).second->GetObjectFileName());
  }

  CGlobalVariableRegisterEntry * pciEntry = 0;
  std::pair<CGlobalVariableRegisterTable::iterator, bool> pairInserted;
  try {
    try {
      pciEntry = new __OPTION(_THROW) CGlobalVariableRegisterEntry(rstringTypeSignature,
                                                                   pciOwnerModule);
      // Insert into std::map
      pairInserted =
        _hmapGlobalVariableRegisterTable.insert(
          CGlobalVariableRegisterTable::value_type(rstringVariableName, pciEntry)
                                                );
    }
    catch(zfc::EBaseException & e1)
    {
      stringError = "Constructing storage slot for global variable '" +
                    rstringVariableName + "' of '" +
                    pciOwnerModule->GetSourceFileName() + "(" +
                    pciOwnerModule->GetObjectFileName() + ")' failure";
      e1.AppendWhat(__FILE__, __PRETTY_FUNC__ ,__LINE__, stringError);
      throw;
    }
    catch(std::exception & e2)
    {
      stringError = "Constructing storage slot for global variable '" +
                    rstringVariableName + "' of '" +
                    pciOwnerModule->GetSourceFileName() + "(" +
                    pciOwnerModule->GetObjectFileName() + ")' failure due to '" + e2.what() + "'";
      throw;
    }
    catch(...)
    {
      stringError = "Constructing storage slot for global variable '" +
                    rstringVariableName + "' of '" +
                    pciOwnerModule->GetSourceFileName() + "(" +
                    pciOwnerModule->GetObjectFileName() + ")' failure due to 'Unknown exception'";
      throw;
    }
  }
  catch(...)
  {
    delete pciEntry;
    throw;
  }

  pciOwnerModule->AppendGlobalVariablesRegisterIterator(pairInserted.first);
  return pairInserted.first;
}


CGlobalFunctionRegisterTable::iterator CVirtualMachine::RegisterGlobalFunction(
      const std::string & rstringFunctionName,
      const std::string & rstringFunctionSignature,
      const CZVMFunction * pciZVMFunction,
      IDynamicLoadableModule * pciOwnerModule)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CVirtualMachine::RegisterGlobalFunction()");
  std::string stringError;

  CGlobalFunctionRegisterTable::iterator it;
  if ((it = _hmapGlobalFunctionRegisterTable.find(rstringFunctionName))
      != _hmapGlobalFunctionRegisterTable.end())
  // If duplicate global function
  {
    CZVMErrorReporter::ThrowError_MultipleDefinitionSymbol(__FILE__, __PRETTY_FUNC__ , __LINE__,
                                                           "global function",
                                                           FunctionNameAndSignatureToPrettyString(rstringFunctionName, rstringFunctionSignature),
                                                           pciOwnerModule->GetSourceFileName(),
                                                           pciOwnerModule->GetObjectFileName(),
                                                           (*it).second->GetSourceFileName(),
                                                           (*it).second->GetObjectFileName());
  }

  CGlobalFunctionRegisterEntry * pciEntry = 0;
  std::pair<CGlobalFunctionRegisterTable::iterator, bool> pairInserted;
  try {
    try {
      pciEntry = new __OPTION(_THROW) CGlobalFunctionRegisterEntry(rstringFunctionSignature,
                                                                   pciZVMFunction,
                                                                   pciOwnerModule);

      // Insert into std::map
      pairInserted =
        _hmapGlobalFunctionRegisterTable.insert(
          CGlobalFunctionRegisterTable::value_type(rstringFunctionName, pciEntry)
                                                );
    }
    catch(zfc::EBaseException & e1)
    {
      // 这里还是不能用FunctionNameAndSignatureToPrettyString()来打印出一个pretty text，
      // 因为如果正好是signature不合法，那么将再throw出同样的exception的.

      stringError = "Registering global function '" +
                    rstringFunctionName + "' of '" +
                    pciOwnerModule->GetSourceFileName() + "(" +
                    pciOwnerModule->GetObjectFileName() + ")' failure";
      e1.AppendWhat(__FILE__, __PRETTY_FUNC__ ,__LINE__, stringError);
      throw;
    }
    catch(std::exception & e2)
    {
      stringError = "Registering global function '" +
                    rstringFunctionName + "' of '" +
                    pciOwnerModule->GetSourceFileName() + "(" +
                    pciOwnerModule->GetObjectFileName() + ")' failure due to '" + e2.what() + "'";
      throw;
    }
    catch(...)
    {
      stringError = "Registering global function '" +
                    rstringFunctionName + "' of '" +
                    pciOwnerModule->GetSourceFileName() + "(" +
                    pciOwnerModule->GetObjectFileName() + ")' failure due to 'Unknown exception'";
      throw;
    }
  }
  catch(...)
  {
    delete pciEntry;
    throw;
  }

  pciOwnerModule->AppendGlobalFunctionsRegisterIterator(pairInserted.first);
  return pairInserted.first;
}


CGlobalFunctionRegisterTable::iterator CVirtualMachine::RegisterGlobalFunction(
      const std::string & rstringFunctionName,
      const std::string & rstringFunctionSignature,
      TNativeFunction pfuncNativeFunction,
      IDynamicLoadableModule * pciOwnerModule)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CVirtualMachine::RegisterGlobalFunction()");
  std::string stringError;

  CGlobalFunctionRegisterTable::iterator it;
  if ((it = _hmapGlobalFunctionRegisterTable.find(rstringFunctionName))
      != _hmapGlobalFunctionRegisterTable.end())
  // If duplicate global function
  {
    CZVMErrorReporter::ThrowError_MultipleDefinitionSymbol(__FILE__, __PRETTY_FUNC__ , __LINE__,
                                                           "global function",
                                                           FunctionNameAndSignatureToPrettyString(rstringFunctionName, rstringFunctionSignature),
                                                           pciOwnerModule->GetSourceFileName(),
                                                           pciOwnerModule->GetObjectFileName(),
                                                           (*it).second->GetSourceFileName(),
                                                           (*it).second->GetObjectFileName());
  }

  CGlobalFunctionRegisterEntry * pciEntry = 0;
  std::pair<CGlobalFunctionRegisterTable::iterator, bool> pairInserted;
  try {
    try {
      pciEntry = new __OPTION(_THROW) CGlobalFunctionRegisterEntry(rstringFunctionSignature,
                                                                   pfuncNativeFunction,
                                                                   pciOwnerModule);

      // Insert into std::map
      pairInserted =
        _hmapGlobalFunctionRegisterTable.insert(
          CGlobalFunctionRegisterTable::value_type(rstringFunctionName, pciEntry)
                                                );
    }
    catch(zfc::EBaseException & e1)
    {
      stringError = "Registering global native function '" +
                    rstringFunctionName + "' of '" +
                    pciOwnerModule->GetSourceFileName() + "(" +
                    pciOwnerModule->GetObjectFileName() + ")' failure";
      e1.AppendWhat(__FILE__, __PRETTY_FUNC__ ,__LINE__, stringError);
      throw;
    }
    catch(std::exception & e2)
    {
      stringError = "Registering global native function '" +
                    rstringFunctionName + "' of '" +
                    pciOwnerModule->GetSourceFileName() + "(" +
                    pciOwnerModule->GetObjectFileName() + ")' failure due to '" + e2.what() + "'";
      throw;
    }
    catch(...)
    {
      stringError = "Registering global native function '" +
                    rstringFunctionName + "' of '" +
                    pciOwnerModule->GetSourceFileName() + "(" +
                    pciOwnerModule->GetObjectFileName() + ")' failure due to 'Unknown exception'";
      throw;
    }
  }
  catch(...)
  {
    delete pciEntry;
    throw;
  }

  pciOwnerModule->AppendGlobalFunctionsRegisterIterator(pairInserted.first);
  return pairInserted.first;
}


CGlobalVariableRegisterEntry *
CVirtualMachine::FindRegisteredGlobalVariable(const std::string & rstringVariableName,
                                              const std::string & rstringVariableSignature)
{
  CGlobalVariableRegisterTable::iterator it;
  if ((it = _hmapGlobalVariableRegisterTable.find(rstringVariableName))
      == _hmapGlobalVariableRegisterTable.end())
  {
    return 0;
  }

  if ((*it).second->GetTypeSignature() != rstringVariableSignature)
  {
    return 0;
  }

  return (*it).second;
}


const CGlobalVariableRegisterEntry *
CVirtualMachine::FindRegisteredGlobalVariable(const std::string & rstringVariableName,
                                              const std::string & rstringVariableSignature) const
{
  CGlobalVariableRegisterTable::const_iterator it;
  if ((it = _hmapGlobalVariableRegisterTable.find(rstringVariableName))
      == _hmapGlobalVariableRegisterTable.end())
  {
    return 0;
  }

  if ((*it).second->GetTypeSignature() != rstringVariableSignature)
  {
    return 0;
  }

  return (*it).second;
}


CGlobalFunctionRegisterEntry *
CVirtualMachine::FindRegisteredGlobalFunction(const std::string & rstringFunctionName,
                                              const std::string & rstringFunctionSignature)
{
  CGlobalFunctionRegisterTable::iterator it;
  if ((it = _hmapGlobalFunctionRegisterTable.find(rstringFunctionName))
      == _hmapGlobalFunctionRegisterTable.end())
  {
    return 0;
  }

  if ((*it).second->GetFunctionSignature() != rstringFunctionSignature)
  {
    return 0;
  }

  return (*it).second;
}


const CGlobalFunctionRegisterEntry *
CVirtualMachine::FindRegisteredGlobalFunction(const std::string & rstringFunctionName,
                                              const std::string & rstringFunctionSignature) const
{
  CGlobalFunctionRegisterTable::const_iterator it;
  if ((it = _hmapGlobalFunctionRegisterTable.find(rstringFunctionName))
      == _hmapGlobalFunctionRegisterTable.end())
  {
    return 0;
  }

  if ((*it).second->GetFunctionSignature() != rstringFunctionSignature)
  {
    return 0;
  }

  return (*it).second;
}


const CGlobalVariableRegisterEntry *
CVirtualMachine::FindRegisteredGlobalVariable(const std::string & rstringVariableName) const
{
  CGlobalVariableRegisterTable::const_iterator it;
  if ((it = _hmapGlobalVariableRegisterTable.find(rstringVariableName))
      == _hmapGlobalVariableRegisterTable.end())
  {
    return 0;
  }

  return (*it).second;
}


const CGlobalFunctionRegisterEntry *
CVirtualMachine::FindRegisteredGlobalFunction(const std::string & rstringFunctionName) const
{
  CGlobalFunctionRegisterTable::const_iterator it;
  if ((it = _hmapGlobalFunctionRegisterTable.find(rstringFunctionName))
      == _hmapGlobalFunctionRegisterTable.end())
  {
    return 0;
  }

  return (*it).second;
}


void CVirtualMachine::ClearGlobalVariableRegisterTable()
{
  CGlobalVariableRegisterTable::iterator it;
  for (it = _hmapGlobalVariableRegisterTable.begin();
       it != _hmapGlobalVariableRegisterTable.end();
       ++it)
  {
    delete (*it).second;
  }
  _hmapGlobalVariableRegisterTable.clear();
}


void CVirtualMachine::ClearGlobalFunctionRegisterTable()
{
  CGlobalFunctionRegisterTable::iterator it;
  for (it = _hmapGlobalFunctionRegisterTable.begin();
       it != _hmapGlobalFunctionRegisterTable.end();
       ++it)
  {
    delete (*it).second;
  }
  _hmapGlobalFunctionRegisterTable.clear();
}


void CVirtualMachine::ClearLinkedObjectFiles()
{
  CObjectFileRegisterTable::iterator it;
  for (it = _hmapLinkedObjectFiles.begin(); it != _hmapLinkedObjectFiles.end(); ++it)
  {
    delete (*it).second;
  }
  _hmapLinkedObjectFiles.clear();
}


void CVirtualMachine::ClearUnlinkedObjectFiles()
{
  CObjectFileRegisterTable::iterator it;
  for (it = _hmapUnlinkedObjectFiles.begin(); it != _hmapUnlinkedObjectFiles.end(); ++it)
  {
    delete (*it).second;
  }
  _hmapUnlinkedObjectFiles.clear();
}


void CVirtualMachine::ClearImportedLibrarys()
{
  CLibraryRegisterTable::iterator it;
  for (it = _hmapImportedLibrarys.begin(); it != _hmapImportedLibrarys.end(); ++it)
  {
    delete (*it).second;
  }
  _hmapImportedLibrarys.clear();
}


void CVirtualMachine::Reset()
{
  // Free 'initializer virtual thread'
  _bInitializerZVMVirtualThreadUnilized = false;

  // Free 'all others virtual threads'
  std::vector<CZVMVirtualThread *>::iterator it1;
  for (it1 = _vectorCreatedZVMVirtualThreads.begin(); it1 != _vectorCreatedZVMVirtualThreads.end(); ++it1)
  {
    delete *it1;
  }
  _vectorCreatedZVMVirtualThreads.clear();

  // Free 'global variables register table'
  ClearGlobalVariableRegisterTable();

  // Free 'global functions register table'
  ClearGlobalFunctionRegisterTable();

  // Free 'linked object files'
  ClearLinkedObjectFiles();

  // Free 'unlinked object files'
  ClearUnlinkedObjectFiles();

  // Free 'imported native librarys'
  ClearImportedLibrarys();

  _eZVMState = STATE_DEFAULT;
}


void CVirtualMachine::UnregisterGlobalVariables(std::vector<CGlobalVariableRegisterTable::iterator> & rvector)
{
  std::vector<CGlobalVariableRegisterTable::iterator>::iterator it;
  for (it = rvector.begin(); it != rvector.end(); ++it)
  {
    _hmapGlobalVariableRegisterTable.erase(*it);
  }
}


void CVirtualMachine::UnregisterGlobalFunctions(std::vector<CGlobalFunctionRegisterTable::iterator> & rvector)
{
  std::vector<CGlobalFunctionRegisterTable::iterator>::iterator it;
  for (it = rvector.begin(); it != rvector.end(); ++it)
  {
    _hmapGlobalFunctionRegisterTable.erase(*it);
  }
}


void CVirtualMachine::DynamicUnloadObjectFile(const std::string & rstringObjectFileName)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CVirtualMachine::DynamicUnloadObjectFile()");
  std::string stringError;

  CObjectFileRegisterTable::iterator it;
  if ((it = _hmapUnlinkedObjectFiles.find(rstringObjectFileName)) != _hmapUnlinkedObjectFiles.end())
  {
    // Free这个Object file
    delete (*it).second;
    _hmapUnlinkedObjectFiles.erase(it);
  }
  else
  {
    if ((it = _hmapLinkedObjectFiles.find(rstringObjectFileName)) != _hmapLinkedObjectFiles.end())
    {
      CZVMObjectFile * pciObjectFile = (*it).second;
      if (pciObjectFile->GetReferencedCount() > 0)
      // 如果被引用的计数大于0
      {
        stringError = "Could not unload object file '" + rstringObjectFileName + "' which is referenced by others";
        throw zvm::EUnloadObjectFileFailure(__FILE__, __PRETTY_FUNC__ ,__LINE__, stringError);
      }

      // Unregister这个Object file的所有global variables和functions
      UnregisterGlobalVariables(pciObjectFile->GetGlobalVariablesRegisterIterators());
      UnregisterGlobalFunctions(pciObjectFile->GetGlobalFunctionsRegisterIterators());
      // Free这个Object file
      delete pciObjectFile;

      _hmapLinkedObjectFiles.erase(it);
    }
    else
    {
      stringError = "Object file '" + rstringObjectFileName + "' is yet not loaded";
      throw zvm::EUnloadObjectFileFailure(__FILE__, __PRETTY_FUNC__ ,__LINE__, stringError);
    }
  }
}


void CVirtualMachine::DynamicLoadObjectFile(const std::string & rstringObjectFileName, bool bStripDebugInfo = false)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CVirtualMachine::DynamicLoadObjectFile()");
  std::string stringError;

  zfc::CBinaryInputFileStream bis(rstringObjectFileName.c_str());
  if (bis)
  {
    // Active stream exception mask
    bis.exceptions(std::ios_base::badbit | std::ios_base::failbit | std::ios_base::eofbit);

    CZVMObjectFile * pciObjectFile = 0;
    try {
      try {
        pciObjectFile = new __OPTION(_THROW) CZVMObjectFile(this, rstringObjectFileName);
        bis >> *pciObjectFile;
        //< May throw zvm::EInvalidObjectFile、std::ios_base::failure

        if (bStripDebugInfo)
        {
          pciObjectFile->StripDebugInfo();
        }

        // Insert into hash_map
        std::pair<CObjectFileRegisterTable::iterator, bool> pairInserted =
          _hmapUnlinkedObjectFiles.insert(
            CObjectFileRegisterTable::value_type(rstringObjectFileName, pciObjectFile)
                                         );
      }
      catch(zfc::EBaseException & e1)
      {
        stringError = "Loading object file '" + rstringObjectFileName + "' failure";
        e1.AppendWhat(__FILE__, __PRETTY_FUNC__ ,__LINE__, stringError);
        // Mapping to zvm::ELoadObjectFileFailure
        throw zvm::ELoadObjectFileFailure(e1);
      }
      catch(std::exception & e2)
      {
        stringError = "Loading object file '" + rstringObjectFileName + "' failure due to '" + e2.what() + "'";
        // Mapping to zvm::ELoadObjectFileFailure
        throw zvm::ELoadObjectFileFailure(__FILE__, __PRETTY_FUNC__ ,__LINE__, stringError);
      }
      catch(...)
      {
        stringError = "Loading object file '" + rstringObjectFileName + "' failure due to 'Unknown exception'";
        // Mapping to zvm::ELoadObjectFileFailure
        throw zvm::ELoadObjectFileFailure(__FILE__, __PRETTY_FUNC__ ,__LINE__, stringError);
      }
    }
    catch(...)
    {
      delete pciObjectFile;
      throw;
    }
  }
  else
  {
    stringError = "Could not open object file '" + rstringObjectFileName + "'";
    throw zvm::ELoadObjectFileFailure(__FILE__, __PRETTY_FUNC__ ,__LINE__, stringError);
  }
}


void CVirtualMachine::Link()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CVirtualMachine::Link()");
  std::string stringError;

  try {
    CObjectFileRegisterTable::iterator it;

    try {
      // Verify Byte Codes Integrity
      for (it = _hmapUnlinkedObjectFiles.begin(); it != _hmapUnlinkedObjectFiles.end(); ++it)
      {
        (*it).second->VerifyByteCodesIntegrity();
                       //< May throw zvm::CVerifyFailureException
      }

      // Link1
      for (it = _hmapUnlinkedObjectFiles.begin(); it != _hmapUnlinkedObjectFiles.end(); ++it)
      {
        (*it).second->Link1();
                       //< May throw zvm::ELink1Failure
      }

      // Link2
      for (it = _hmapUnlinkedObjectFiles.begin(); it != _hmapUnlinkedObjectFiles.end(); ++it)
      {
        (*it).second->Link2();
                       //< May throw zvm::ELink2Failure
      }
    }
    catch (zfc::EBaseException & e1)
    {
      stringError = "Link stopped at '" + (*it).first + "'";
      e1.AppendWhat(__FILE__, __PRETTY_FUNC__, __LINE__ , stringError);
      throw zvm::ELinkFailure(e1);
    }
    catch (std::exception & e2)
    {
      stringError = "Link stopped at '" + (*it).first + "' due to '" + e2.what() + "'";
      throw zvm::ELinkFailure(__FILE__, __PRETTY_FUNC__, __LINE__ , stringError);
    }
    catch (...)
    {
      stringError = "Link stopped at '" + (*it).first + "' due to 'Unknown exception'";
      throw zvm::ELinkFailure(__FILE__, __PRETTY_FUNC__, __LINE__ , stringError);
    }

    // 现在可以执行Initializer function来初值化global variables
    try {
      for (it = _hmapUnlinkedObjectFiles.begin(); it != _hmapUnlinkedObjectFiles.end(); ++it)
      {
        _pciInitializerZVMVirtualThread->CallZVMFunction((*it).second->GetInitializerZVMFunction());
        //< May throw zvm::EZVMRuntimeException、zvm::CFunctionInvokeInterfaceException
      }
    }
    catch (zfc::EBaseException & e1)
    {
      stringError = "Link stopped when initializing '" + (*it).first + "'";
      e1.AppendWhat(__FILE__, __PRETTY_FUNC__, __LINE__ , stringError);
      throw zvm::ELinkFailure(e1);
    }
    catch (std::exception & e2)
    {
      stringError = "Link stopped when initializing '" + (*it).first + "' due to '" + e2.what() + "'";
      throw zvm::ELinkFailure(__FILE__, __PRETTY_FUNC__, __LINE__ , stringError);
    }
    catch (...)
    {
      stringError = "Link stopped when initializing '" + (*it).first + "' due to 'Unknown exception'";
      throw zvm::ELinkFailure(__FILE__, __PRETTY_FUNC__, __LINE__ , stringError);
    }

    // 将刚被link成功的object files添加到"已被link成功的object files"表中.
    _hmapLinkedObjectFiles.insert(_hmapUnlinkedObjectFiles.begin(), _hmapUnlinkedObjectFiles.end());
    _hmapUnlinkedObjectFiles.clear();
  }
  catch (...)
  {
    _eZVMState = STATE_OBJECT_FILES_LINKED_NOTOK;
    throw;
  }

  _eZVMState = STATE_OBJECT_FILES_LINKED_OK;
}


void CVirtualMachine::ImportNativeLibrary(const INativeLibraryImport & rciImport)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CVirtualMachine::ImportNativeLibrary()");

  INativeLibraryImport * pciLibrary = 0;
  try {
    try {
      pciLibrary = new __OPTION(_THROW) INativeLibraryImport(rciImport);

      // Insert into hash_map
      std::pair<CLibraryRegisterTable::iterator, bool> pairInserted =
        _hmapImportedLibrarys.insert(
          CLibraryRegisterTable::value_type(rciImport.GetLibraryName(), pciLibrary)
                                    );
    }
    catch (zfc::EBaseException & e1)
    {
      // Mapping to zvm::EImportNativeLibraryFailure
      throw zvm::EImportNativeLibraryFailure(e1);
    }
    catch (std::exception & e2)
    {
      // Mapping to zvm::EImportNativeLibraryFailure
      throw zvm::EImportNativeLibraryFailure(__FILE__, __PRETTY_FUNC__, __LINE__, e2.what());
    }
    catch (...)
    {
      // Mapping to zvm::EImportNativeLibraryFailure
      throw zvm::EImportNativeLibraryFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "Unknown exception");
    }
  }
  catch (...)
  {
    delete pciLibrary;
    throw;
  }

  try {
    const std::string & rstringSourceFileName = pciLibrary->GetSourceFileName();
    const std::string & rstringObjectFileName = pciLibrary->GetObjectFileName();
    const std::vector<INativeLibraryImport::TNativeFunctionImportEntry> & rvectorImportTable = pciLibrary->GetNativeFunctionImportTable();
    std::vector<INativeLibraryImport::TNativeFunctionImportEntry>::const_iterator it;
    for (it = rvectorImportTable.begin(); it != rvectorImportTable.end(); ++it)
    {
      RegisterGlobalFunction((*it).GetFunctionName(),
                             (*it).GetFunctionSignature(),
                             (*it).GetNativeFunction(),
                             pciLibrary);
    }

    // 清空Import Table，以便节省内存
    pciLibrary->ClearNativeFunctionImportTable();
  }
  catch (zfc::EBaseException & e1)
  {
    // Mapping to zvm::EImportNativeLibraryFailure
    throw zvm::EImportNativeLibraryFailure(e1);
  }
  catch (std::exception & e2)
  {
    // Mapping to zvm::EImportNativeLibraryFailure
    throw zvm::EImportNativeLibraryFailure(__FILE__, __PRETTY_FUNC__, __LINE__, e2.what());
  }
  catch (...)
  {
    // Mapping to zvm::EImportNativeLibraryFailure
    throw zvm::EImportNativeLibraryFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "Unknown exception");
  }
}


void CVirtualMachine::DumpDetail()
{
  CObjectFileRegisterTable::const_iterator it;
  for (it = _hmapLinkedObjectFiles.begin(); it != _hmapLinkedObjectFiles.end(); ++it)
  {
    (*it).second->DumpDetail();
  }
}


ZLS_END_NAMESPACE

