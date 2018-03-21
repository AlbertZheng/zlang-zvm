/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CBinaryOutputFileStream.hpp,v $
 *
 * $Date: 2001/11/14 17:25:11 $
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


#ifndef _ZLS_zfc_CBinaryOutputFileStream_hpp_
#define _ZLS_zfc_CBinaryOutputFileStream_hpp_

#include <iostream>
#include <fstream>
#if defined(WIN32) || defined(__win32__)
  #include <strstrea.h>
#else
  #include <strstream>
#endif
#include <zls/zfc/Manifest.h>


ZLS_BEGIN_NAMESPACE(zfc)


/**
 * 可移植的二进制输出文件流.
 * 可移植意味着这个class在写文件时总是坚持采用网络字节序.
 */
class CBinaryOutputFileStream : public std::ofstream {
  public:
    CBinaryOutputFileStream(const char * pszFileName)
      : std::ofstream(pszFileName, std::ios::out | std::ios::binary)
    { }

    void open(const char * pszFileName)
    {
      std::ofstream::open(pszFileName, std::ios::out | std::ios::binary);
    }

    friend CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, double df);
    #if SIZEOF_LONG == 4
    friend CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, long l);
    friend CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, unsigned long ul);
    #endif
    friend CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, SDWORD sdw);
    friend CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, UDWORD udw);
    friend CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, SQWORD sqw);
    friend CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, UQWORD uqw);
    friend CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, SWORD sw);
    friend CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, UWORD uw);
    friend CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, UCHAR uch);
    friend CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, char ch);
};


ZLS_END_NAMESPACE


#endif

