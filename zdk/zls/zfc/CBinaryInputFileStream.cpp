/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CBinaryInputFileStream.cpp,v $
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


#include <zls/zfc/CBinaryInputFileStream.hpp>


ZLS_BEGIN_NAMESPACE(zfc)


CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, double & rdf)
{
  is.read(reinterpret_cast<char *>(&rdf), sizeof(double));
  return(is);
}

#if SIZEOF_INT == SIZEOF_LONG
CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, long & rl)
{
  is.read(reinterpret_cast<char *>(&rl), sizeof(long));
  rl = ntohl(rl);
  return(is);
}

CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, unsigned long & rul)
{
  is.read(reinterpret_cast<char *>(&rul), sizeof(unsigned long));
  rul = ntohl(rul);
  return(is);
}
#endif

CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, SDWORD & rsdw)
{
  is.read(reinterpret_cast<char *>(&rsdw), sizeof(SDWORD));
  rsdw = ntohl(rsdw);
  return(is);
}

CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, UDWORD & rudw)
{
  is.read(reinterpret_cast<char *>(&rudw), sizeof(UDWORD));
  rudw = ntohl(rudw);
  return(is);
}

CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, SQWORD & rsqw)
{
  UDWORD udwHigh, udwLow;
  is.read(reinterpret_cast<char *>(&udwHigh), sizeof(UDWORD));
  is.read(reinterpret_cast<char *>(&udwLow), sizeof(UDWORD));
  udwHigh = ntohl(udwHigh);
  udwLow = ntohl(udwLow);
  rsqw = (static_cast<UQWORD>(udwHigh) << 32) | udwLow;
  return(is);
}

CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, UQWORD & ruqw)
{
  UDWORD udwHigh, udwLow;
  is.read(reinterpret_cast<char *>(&udwHigh), sizeof(UDWORD));
  is.read(reinterpret_cast<char *>(&udwLow), sizeof(UDWORD));
  udwHigh = ntohl(udwHigh);
  udwLow = ntohl(udwLow);
  ruqw = (static_cast<UQWORD>(udwHigh) << 32) | udwLow;
  return(is);
}

CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, SWORD & rsw)
{
  is.read(reinterpret_cast<char *>(&rsw), sizeof(SWORD));
  rsw = ntohs(rsw);
  return(is);
}

CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, UWORD & ruw)
{
  is.read(reinterpret_cast<char *>(&ruw), sizeof(UWORD));
  ruw = ntohs(ruw);
  return(is);
}

CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, UCHAR & ruch)
{
  is.read(reinterpret_cast<char *>(&ruch), sizeof(UCHAR));
  return(is);
}

CBinaryInputFileStream & operator >> (CBinaryInputFileStream & is, char & rch)
{
  is.read(&rch, sizeof(char));
  return(is);
}


ZLS_END_NAMESPACE

