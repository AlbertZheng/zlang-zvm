/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CStandardLibrary.hpp,v $
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


#ifndef _ZLS_zvm_CStandardLibrary_hpp_
#define _ZLS_zvm_CStandardLibrary_hpp_

#include <zls/zvm/INativeLibraryImport.hpp>


// Begin namespace 'zvm::'
ZLS_BEGIN_NAMESPACE(zvm)


class CStandardLibrary : public INativeLibraryImport {
  public:
    CStandardLibrary();

    static void PrintBool(CSlot * pciLastArgumentSlot);
    static void PrintByte(CSlot * pciLastArgumentSlot);
    static void PrintSDWORD(CSlot * pciLastArgumentSlot);
    static void PrintUDWORD(CSlot * pciLastArgumentSlot);
    static void PrintSQWORD(CSlot * pciLastArgumentSlot);
    static void PrintUQWORD(CSlot * pciLastArgumentSlot);
    static void PrintDouble(CSlot * pciLastArgumentSlot);
    /** @attention 采用value argument. */
    static void PrintString(CSlot * pciLastArgumentSlot);
    /** @attention 采用value argument. */
    static void PrintRope(CSlot * pciLastArgumentSlot);
    /** @attention 采用value argument. */
    static void PrintPPort(CSlot * pciLastArgumentSlot);
    /** @attention 采用value argument. */
    static void PrintIPv4Address(CSlot * pciLastArgumentSlot);

    static void PrintlnBool(CSlot * pciLastArgumentSlot);
    static void PrintlnByte(CSlot * pciLastArgumentSlot);
    static void PrintlnSDWORD(CSlot * pciLastArgumentSlot);
    static void PrintlnUDWORD(CSlot * pciLastArgumentSlot);
    static void PrintlnSQWORD(CSlot * pciLastArgumentSlot);
    static void PrintlnUQWORD(CSlot * pciLastArgumentSlot);
    static void PrintlnDouble(CSlot * pciLastArgumentSlot);
    /** @attention 采用value argument. */
    static void PrintlnString(CSlot * pciLastArgumentSlot);
    /** @attention 采用value argument. */
    static void PrintlnRope(CSlot * pciLastArgumentSlot);
    /** @attention 采用value argument. */
    static void PrintlnPPort(CSlot * pciLastArgumentSlot);
    /** @attention 采用value argument. */
    static void PrintlnIPv4Address(CSlot * pciLastArgumentSlot);

    /**
     * 得到自从1970年7月1日零时开始到现在的间隔的毫秒数.
     */
    static void Time(CSlot * pciLastArgumentSlot);
};


ZLS_END_NAMESPACE


#endif

