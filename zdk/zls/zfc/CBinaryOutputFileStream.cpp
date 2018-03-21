/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CBinaryOutputFileStream.cpp,v $
 *
 * $Date: 2002/02/28 13:59:25 $
 *
 * $Revision: 1.4 $
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


#include <zls/zfc/CBinaryOutputFileStream.hpp>


ZLS_BEGIN_NAMESPACE(zfc)


CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, double df)
{
  os.write(reinterpret_cast<char *>(&df), sizeof(double));
  return(os);
}

#if SIZEOF_INT == SIZEOF_LONG
CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, long l)
{
  l = htonl(l);
  os.write(reinterpret_cast<char *>(&l), sizeof(long));
  return(os);
}

CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, unsigned long ul)
{
  ul = htonl(ul);
  os.write(reinterpret_cast<char *>(&ul), sizeof(unsigned long));
  return(os);
}
#endif

CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, SDWORD sdw)
{
  sdw = htonl(sdw);
  os.write(reinterpret_cast<char *>(&sdw), sizeof(SDWORD));
  return(os);
}

CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, UDWORD udw)
{
  udw = htonl(udw);
  os.write(reinterpret_cast<char *>(&udw), sizeof(UDWORD));
  return(os);
}

CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, SQWORD sqw)
{
  UDWORD udwHigh, udwLow;
  #if defined(HAVE_GNU_LIBSTDCXX_V2)
  udwHigh = (sqw & 0xffffffff00000000LL) >> 32;  // 采用LL后缀，因为gcc-2.95.4抱怨integer constant太大.
  #else
  udwHigh = (sqw & 0xffffffff00000000L) >> 32;
  #endif
  udwLow = sqw & 0x00000000ffffffffL;
  udwHigh = htonl(udwHigh);
  udwLow = htonl(udwLow);
  os.write(reinterpret_cast<char *>(&udwHigh), sizeof(UDWORD));
  os.write(reinterpret_cast<char *>(&udwLow), sizeof(UDWORD));
  return(os);
}

CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, UQWORD uqw)
{
  UDWORD udwHigh, udwLow;
  #if defined(HAVE_GNU_LIBSTDCXX_V2)
  udwHigh = (uqw & 0xffffffff00000000LL) >> 32;  // 采用LL后缀，因为gcc-2.95.4抱怨integer constant太大.
  #else
  udwHigh = (uqw & 0xffffffff00000000L) >> 32;
  #endif
  udwLow = uqw & 0x00000000ffffffffL;
  udwHigh = htonl(udwHigh);
  udwLow = htonl(udwLow);
  os.write(reinterpret_cast<char *>(&udwHigh), sizeof(UDWORD));
  os.write(reinterpret_cast<char *>(&udwLow), sizeof(UDWORD));
  return(os);
}

CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, SWORD sw)
{
  sw = htons(sw);
  os.write(reinterpret_cast<char *>(&sw), sizeof(SWORD));
  return(os);
}

CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, UWORD uw)
{
  uw = htons(uw);
  os.write(reinterpret_cast<char *>(&uw), sizeof(UWORD));
  return(os);
}

CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, UCHAR uch)
{
  os.write(reinterpret_cast<char *>(&uch), sizeof(UCHAR));
  return(os);
}

CBinaryOutputFileStream & operator << (CBinaryOutputFileStream & os, char ch)
{
  os.write(&ch, sizeof(char));
  return(os);
}


ZLS_END_NAMESPACE

