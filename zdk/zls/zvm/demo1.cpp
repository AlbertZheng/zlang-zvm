/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/demo1.cpp,v $
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
#include <zls/zvm/CFunctionInvokeInterface.hpp>
#include <zls/zvm/CZVMVirtualThread.hpp>
#include <zls/zvm/CStandardLibrary.hpp>
#include <zls/zvm/CSlot.hpp>


class CDemoLibrary : public zvm::INativeLibraryImport {
  public:
    static zvm::CZVMString   _SciString;
    static zvm::CZVMString * _SpciString;

    static SDWORD _Ssdw;

    CDemoLibrary();

    static void GetStringReference(zvm::CSlot * pciLastArgumentSlot);
    static void GetSDWORDReference(zvm::CSlot * pciLastArgumentSlot);
};


zvm::CZVMString   CDemoLibrary::_SciString = "old value";
zvm::CZVMString * CDemoLibrary::_SpciString = &CDemoLibrary::_SciString;
SDWORD CDemoLibrary::_Ssdw = 0;


void CDemoLibrary::GetStringReference(zvm::CSlot * pciLastArgumentSlot)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CDemoLibrary::GetStringReference()");
  // ZLang script看到的函数原型是:
  //    string & GetStringReference()
  // 没有调用参数，只是返回一个string &.
  pciLastArgumentSlot->SlotAssert(zvm::CSlot::SLOT_TAG_ADDRESS_OF_STRING_OBJECT, __FILE__, __PRETTY_FUNC__, __LINE__);
  pciLastArgumentSlot->ConstructSlotAsStringObjectAddress(&CDemoLibrary::_SpciString);
}


void CDemoLibrary::GetSDWORDReference(zvm::CSlot * pciLastArgumentSlot)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CDemoLibrary::GetSDWORDReference()");
  // ZLang script看到的函数原型是:
  //    sdword & GetSDWORDReference()
  // 没有调用参数，只是返回一个sdword &.
  pciLastArgumentSlot->SlotAssert(zvm::CSlot::SLOT_TAG_ADDRESS_OF_SDWORD, __FILE__, __PRETTY_FUNC__, __LINE__);
  pciLastArgumentSlot->ConstructSlotAsSDWORDAddress(&CDemoLibrary::_Ssdw);
}


CDemoLibrary::CDemoLibrary()
  : INativeLibraryImport("demo", "demo1.cpp", "demo1.o")
{
  AppendNativeFunctionImportEntry("GetStringReference", "()s", CDemoLibrary::GetStringReference);
  AppendNativeFunctionImportEntry("GetSDWORDReference", "()i", CDemoLibrary::GetSDWORDReference);
}



int main(int argc, char * argv[])
{
  OpenLogger("zvm");
  SetLoggerDebugLevel(3);

  zvm::CVirtualMachine * pciZVM = 0;
  zvm::CZVMVirtualThread * pciZVMVirtualThread = 0;
  zvm::CStandardLibrary * pciStandardLibrary = 0;
  try {
    try {
      // 创建一个Function invoke interface
      zvm::CFunctionInvokeInterface ciFunctionInvokeInterface;

      // 创建一个ZVM
      pciZVM = new __OPTION(_THROW) zvm::CVirtualMachine();
      // 让ZVM创建一个Virtual Thread
      pciZVMVirtualThread = pciZVM->CreateZVMVirtualThread();

      // Import standard library
      pciStandardLibrary = new __OPTION(_THROW) zvm::CStandardLibrary();
      pciZVM->ImportNativeLibrary(*pciStandardLibrary);
      delete pciStandardLibrary;
      pciStandardLibrary = 0;

      // Import demo library
      pciZVM->ImportNativeLibrary(CDemoLibrary());

      // 让ZVM调入Object files
      pciZVM->DynamicLoadObjectFile("../zlang/data/demo1.zo", false);
      pciZVM->DynamicLoadObjectFile("../zlang/data/demo2.zo", false);
      // 让ZVM链结Object files
      pciZVM->Link();

      // Just for testing 'dynamic loading'
      pciZVM->DynamicLoadObjectFile("../zlang/data/t5.zo");
      pciZVM->Link();
      // Just for testing 'dynamic unloading'
      pciZVM->DynamicUnloadObjectFile("../zlang/data/t5.zo");

      // 让Function invoke interface准备调用'demo1'函数
      ciFunctionInvokeInterface.PrepareForFunction(pciZVMVirtualThread, "demo1");

      // Prepare完毕后可重复按如下步骤使用这个Function invoke interface
      //for (;;)
      //{
        // 步骤1: 将Function invoke interface打结到ZVM virtual thread
        ciFunctionInvokeInterface.TieToZVMVirtualThread();

        // 步骤2: 传递参数
        zvm::CZVMString stringUser = "root";
        zvm::CZVMString * pstringUser = &stringUser;
        // 传递第1个参数：是string型reference argument
        ciFunctionInvokeInterface.PassReferenceArgumentAsStringObjectAddress(1, pstringUser);

        zvm::CZVMString stringCommand = "ls -la";
        // 传递第2个参数：是string型value argument
        ciFunctionInvokeInterface.PassValueArgumentAsStringObject(2, stringCommand);

        // 步骤3: 准备返回值的Buffer
        //bool bReturn;
        zvm::CZVMString stringReturn;

        struct timeval tvBegin, tvEnd;
        gettimeofday(&tvBegin, 0);

        // 步骤4: 开始调用"demo1"
        //ciFunctionInvokeInterface.Invoke(bReturn);
        ciFunctionInvokeInterface.Invoke(stringReturn);
        
        gettimeofday(&tvEnd, 0);

        // 打印返回值
        //std::cout << "Return to C++: function invoke result: " << BoolToPSZ(bReturn) << std::endl;
        std::cout << "Return to C++: function invoke result: " << stringReturn << std::endl;
        // 打印reference argument的值是否被正确改变了
        std::cout << "Reference argument's new value: " << stringUser << std::endl;
        std::cout << "Demo library return-string-reference's new value: " << CDemoLibrary::_SciString << std::endl;
        std::cout << "Demo library return-sdword-reference's new value: " << CDemoLibrary::_Ssdw << std::endl;

        UQWORD uqwBegin = static_cast<UQWORD>(tvBegin.tv_sec)*1000 + static_cast<UQWORD>(tvBegin.tv_usec)/1000;
        UQWORD uqwEnd = static_cast<UQWORD>(tvEnd.tv_sec)*1000 + static_cast<UQWORD>(tvEnd.tv_usec)/1000;
        std::cout << "Begin at (milliseconds) -> " << zfc::UQWORDToString(uqwBegin, 10) << std::endl;
        std::cout << "End at (milliseconds) -> " << zfc::UQWORDToString(uqwEnd, 10) << std::endl;
        std::cout << "Total (milliseconds) -> " << zfc::UQWORDToString(uqwEnd - uqwBegin, 10) << std::endl;
      //}

      pciZVM->DeleteZVMVirtualThread(pciZVMVirtualThread);
      delete pciZVM;
    }
    catch (zfc::EBaseException & e1)
    {
      e1.DumpWhats(zfc::EBaseException::DumpToStandardOutput("Error"));
      throw;
    }
    catch (std::exception & e2)
    {
      std::cout << "Error: " << e2.what() << std::endl;
      throw;
    }
    catch (...)
    {
      std::cout << "Error: Unknown exception" << std::endl;
      throw;
    }
  }
  catch (...)
  {
    delete pciStandardLibrary;
    if (pciZVM && pciZVMVirtualThread)
    {
      pciZVM->DeleteZVMVirtualThread(pciZVMVirtualThread);
    }
    delete pciZVM;
  }

  CloseLogger();
}

