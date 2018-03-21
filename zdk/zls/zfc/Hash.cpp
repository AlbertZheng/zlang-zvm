/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/Hash.cpp,v $
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


#include <zls/zfc/Hash.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


int ComputingBinaryLogarithm(int nBucketCount)
{
  int nBucketCountLog2 = 32;
  // Computing ceiling of binary logarithm
  while (!(0x80000000 & nBucketCount))
  {
    nBucketCountLog2--;
    nBucketCount <<= 1;
  }

  return nBucketCountLog2;
}


/******************************************************************************
 * class MakeTCPSessionHash

 ******************************************************************************/

size_t MakeTCPSessionHash::operator()(const TIPv4Tuple4 & rsiTCPHaltStreamAddress) const
{
  UDWORD udw = (rsiTCPHaltStreamAddress.nudwSourceAddress ^ rsiTCPHaltStreamAddress.nudwDestAddress) +
               (rsiTCPHaltStreamAddress.uwSourcePort << 16 + rsiTCPHaltStreamAddress.uwDestPort);
  UDWORD udwHashIndex = 0;

  do {
    udwHashIndex ^= udw;
  } while ((udw >>= nBucketCountLog2));
  udwHashIndex %= nBucketCount;

  return(udwHashIndex);
}


/******************************************************************************
 * class MakeIPv4AddressPairHash

 ******************************************************************************/

size_t MakeIPv4AddressPairHash::operator()(const TIPv4Tuple2 & rsiIPv4PairAddress) const
{
  UDWORD udw = (rsiIPv4PairAddress.nudwSourceAddress ^ rsiIPv4PairAddress.nudwDestAddress);
  UDWORD udwHashIndex = 0;

  do {
    udwHashIndex ^= udw;
  } while ((udw >>= nBucketCountLog2));
  udwHashIndex %= nBucketCount;

  return(udwHashIndex);
}


ZLS_END_NAMESPACE


