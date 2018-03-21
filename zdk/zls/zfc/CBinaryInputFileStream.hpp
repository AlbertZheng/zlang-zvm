/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CBinaryInputFileStream.hpp,v $
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


#ifndef _ZLS_zfc_CBinaryInputFileStream_hpp_
#define _ZLS_zfc_CBinaryInputFileStream_hpp_

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
 * 可移植的二进制输入文件流.
 * 可移植意味着这个class在读文件时总是坚持认为输入文件是采用网络字节序的.
 */
class CBinaryInputFileStream : public std::ifstream {
  public:
    CBinaryInputFileStream(const char * pszFileName)
      : std::ifstream(pszFileName, std::ios::in | std::ios::binary)
    { }

    void open(const char * pszFileName)
    {
      std::ifstream::open(pszFileName, std::ios::in | std::ios::binary);
    }

    friend CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, double & df);
    #if SIZEOF_LONG == 4
    friend CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, long & l);
    friend CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, unsigned long & ul);
    #endif
    friend CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, SDWORD & sdw);
    friend CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, UDWORD & udw);
    friend CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, SQWORD & sqw);
    friend CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, UQWORD & uqw);
    friend CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, SWORD & sw);
    friend CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, UWORD & uw);
    friend CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, UCHAR & uch);
    friend CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, char & ch);
};


ZLS_END_NAMESPACE


#endif

