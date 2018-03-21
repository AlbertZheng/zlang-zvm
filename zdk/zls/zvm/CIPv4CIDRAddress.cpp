/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CIPv4CIDRAddress.cpp,v $
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


#include <zls/zvm/CIPv4CIDRAddress.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


CZVMString CIPv4CIDRAddress::ToBinaryString() const
{
  CZVMString bstringResult = IPv4ADDRESS_TO_ZVM_STRING(_ciAddress.GetAddress());
  bstringResult += "/";
  bstringResult += IPv4ADDRESS_TO_ZVM_STRING(_nudwCIDRMask);
  return(bstringResult);
}



std::string CIPv4CIDRAddress::ToString() const

{
  std::string stringResult = zfc::IPv4AddressToString(_ciAddress.GetAddress());
  stringResult += "/";
  stringResult += zfc::IPv4AddressToString(_nudwCIDRMask);
  return(stringResult);
}



ZLS_END_NAMESPACE


