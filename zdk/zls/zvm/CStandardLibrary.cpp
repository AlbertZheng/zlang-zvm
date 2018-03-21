/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CStandardLibrary.cpp,v $
 *
 * $Date: 2001/08/11 18:54:42 $
 *
 * $Revision: 1.2 $
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

 
#include <zls/zvm/CStandardLibrary.hpp>
#include <zls/zvm/CSlot.hpp>


// Begin namespace 'zvm::'
ZLS_BEGIN_NAMESPACE(zvm)


void CStandardLibrary::PrintBool(CSlot * pciLastArgumentSlot)
{
  bool b = pciLastArgumentSlot->GetBool();
  std::cout << BoolToPSZ(b);
}


void CStandardLibrary::PrintlnBool(CSlot * pciLastArgumentSlot)
{
  bool b = pciLastArgumentSlot->GetBool();
  std::cout << BoolToPSZ(b) << std::endl;
}


void CStandardLibrary::PrintByte(CSlot * pciLastArgumentSlot)
{
  UCHAR uch = pciLastArgumentSlot->GetByte();
  std::cout << static_cast<SWORD>(uch);
}


void CStandardLibrary::PrintlnByte(CSlot * pciLastArgumentSlot)
{
  UCHAR uch = pciLastArgumentSlot->GetByte();
  std::cout << static_cast<SWORD>(uch) << std::endl;
}


void CStandardLibrary::PrintSDWORD(CSlot * pciLastArgumentSlot)
{
  SDWORD sdw = pciLastArgumentSlot->GetSDWORD();
  std::cout << sdw;
}


void CStandardLibrary::PrintlnSDWORD(CSlot * pciLastArgumentSlot)
{
  SDWORD sdw = pciLastArgumentSlot->GetSDWORD();
  std::cout << sdw << std::endl;
}


void CStandardLibrary::PrintUDWORD(CSlot * pciLastArgumentSlot)
{
  UDWORD udw = pciLastArgumentSlot->GetUDWORD();
  std::cout << udw;
}


void CStandardLibrary::PrintlnUDWORD(CSlot * pciLastArgumentSlot)
{
  UDWORD udw = pciLastArgumentSlot->GetUDWORD();
  std::cout << udw << std::endl;
}


void CStandardLibrary::PrintSQWORD(CSlot * pciLastArgumentSlot)
{
  SQWORD sqw = pciLastArgumentSlot->GetSQWORD();
  std::cout << zfc::SQWORDToString(sqw, 10);
}


void CStandardLibrary::PrintlnSQWORD(CSlot * pciLastArgumentSlot)
{
  SQWORD sqw = pciLastArgumentSlot->GetSQWORD();
  std::cout << zfc::SQWORDToString(sqw, 10) << std::endl;
}


void CStandardLibrary::PrintUQWORD(CSlot * pciLastArgumentSlot)
{
  UQWORD uqw = pciLastArgumentSlot->GetUQWORD();
  std::cout << zfc::UQWORDToString(uqw, 10);
}


void CStandardLibrary::PrintlnUQWORD(CSlot * pciLastArgumentSlot)
{
  UQWORD uqw = pciLastArgumentSlot->GetUQWORD();
  std::cout << zfc::UQWORDToString(uqw, 10) << std::endl;
}


void CStandardLibrary::PrintDouble(CSlot * pciLastArgumentSlot)
{
  double df = pciLastArgumentSlot->GetDouble();
  std::cout << df;
}


void CStandardLibrary::PrintlnDouble(CSlot * pciLastArgumentSlot)
{
  double df = pciLastArgumentSlot->GetDouble();
  std::cout << df << std::endl;
}


/** @attention 采用value argument. */
void CStandardLibrary::PrintString(CSlot * pciLastArgumentSlot)
{
  CZVMString * pci = pciLastArgumentSlot->GetStringObject();
  std::cout << *pci;
}


/** @attention 采用value argument. */
void CStandardLibrary::PrintlnString(CSlot * pciLastArgumentSlot)
{
  CZVMString * pci = pciLastArgumentSlot->GetStringObject();
  std::cout << *pci << std::endl;
}


/** @attention 采用value argument. */
void CStandardLibrary::PrintRope(CSlot * pciLastArgumentSlot)
{
  CZVMRope * pci = pciLastArgumentSlot->GetRopeObject();
  std::cout << *pci;
}


/** @attention 采用value argument. */
void CStandardLibrary::PrintlnRope(CSlot * pciLastArgumentSlot)
{
  CZVMRope * pci = pciLastArgumentSlot->GetRopeObject();
  std::cout << *pci << std::endl;
}


/** @attention 采用value argument. */
void CStandardLibrary::PrintPPort(CSlot * pciLastArgumentSlot)
{
  CZVMPPort * pci = pciLastArgumentSlot->GetPPortObject();
  std::cout << *pci;
}


/** @attention 采用value argument. */
void CStandardLibrary::PrintlnPPort(CSlot * pciLastArgumentSlot)
{
  CZVMPPort * pci = pciLastArgumentSlot->GetPPortObject();
  std::cout << *pci << std::endl;
}


/** @attention 采用value argument. */
void CStandardLibrary::PrintIPv4Address(CSlot * pciLastArgumentSlot)
{
  CZVMIPv4Address * pci = pciLastArgumentSlot->GetIPv4AddressObject();
  std::cout << *pci;
}


/** @attention 采用value argument. */
void CStandardLibrary::PrintlnIPv4Address(CSlot * pciLastArgumentSlot)
{
  CZVMIPv4Address * pci = pciLastArgumentSlot->GetIPv4AddressObject();
  std::cout << *pci << std::endl;
}


void CStandardLibrary::Time(CSlot * pciLastArgumentSlot)
{
  /*
  UDWORD udw = time(0);
  pciLastArgumentSlot->StoreUDWORD(udw);
  */
  struct timeval tv;
  gettimeofday(&tv, 0);
  // 转换为毫秒精度
  UQWORD uqw = static_cast<UQWORD>(tv.tv_sec)*1000 + static_cast<UQWORD>(tv.tv_usec)/1000;
  pciLastArgumentSlot->StoreUQWORD(uqw);
}


CStandardLibrary::CStandardLibrary()
  : INativeLibraryImport("standard", "CStandardLibrary.cpp", "CStandardLibrary.o")
{
  AppendNativeFunctionImportEntry("PrintBool", "(Z)V", CStandardLibrary::PrintBool);
  AppendNativeFunctionImportEntry("PrintByte", "(B)V", CStandardLibrary::PrintByte);
  AppendNativeFunctionImportEntry("PrintSDWORD", "(I)V", CStandardLibrary::PrintSDWORD);
  AppendNativeFunctionImportEntry("PrintUDWORD", "(J)V", CStandardLibrary::PrintUDWORD);
  AppendNativeFunctionImportEntry("PrintSQWORD", "(L)V", CStandardLibrary::PrintSQWORD);
  AppendNativeFunctionImportEntry("PrintUQWORD", "(M)V", CStandardLibrary::PrintUQWORD);
  AppendNativeFunctionImportEntry("PrintDouble", "(D)V", CStandardLibrary::PrintDouble);
  AppendNativeFunctionImportEntry("PrintString", "(S)V", CStandardLibrary::PrintString);
  AppendNativeFunctionImportEntry("PrintRope", "(R)V", CStandardLibrary::PrintRope);
  AppendNativeFunctionImportEntry("PrintPPort", "(P)V", CStandardLibrary::PrintPPort);
  AppendNativeFunctionImportEntry("PrintIPAddress", "(N)V", CStandardLibrary::PrintIPv4Address);

  AppendNativeFunctionImportEntry("PrintlnBool", "(Z)V", CStandardLibrary::PrintlnBool);
  AppendNativeFunctionImportEntry("PrintlnByte", "(B)V", CStandardLibrary::PrintlnByte);
  AppendNativeFunctionImportEntry("PrintlnSDWORD", "(I)V", CStandardLibrary::PrintlnSDWORD);
  AppendNativeFunctionImportEntry("PrintlnUDWORD", "(J)V", CStandardLibrary::PrintlnUDWORD);
  AppendNativeFunctionImportEntry("PrintlnSQWORD", "(L)V", CStandardLibrary::PrintlnSQWORD);
  AppendNativeFunctionImportEntry("PrintlnUQWORD", "(M)V", CStandardLibrary::PrintlnUQWORD);
  AppendNativeFunctionImportEntry("PrintlnDouble", "(D)V", CStandardLibrary::PrintlnDouble);
  AppendNativeFunctionImportEntry("PrintlnString", "(S)V", CStandardLibrary::PrintlnString);
  AppendNativeFunctionImportEntry("PrintlnRope", "(R)V", CStandardLibrary::PrintlnRope);
  AppendNativeFunctionImportEntry("PrintlnPPort", "(P)V", CStandardLibrary::PrintlnPPort);
  AppendNativeFunctionImportEntry("PrintlnIPAddress", "(N)V", CStandardLibrary::PrintlnIPv4Address);

  AppendNativeFunctionImportEntry("Time", "()M", CStandardLibrary::Time);
}


ZLS_END_NAMESPACE

