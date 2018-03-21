/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CProtocolPort.cpp,v $
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


#include <zls/zvm/CProtocolPort.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


CZVMString CProtocolPort::ToBinaryString() const
{
  CZVMString bstringResult = ZVM_UDWORD_TO_ZVM_STRING(_nPortNumber);
  bstringResult += "/";

  if (_uwProtocolType == IPPROTO_TCP)
  {
    bstringResult += "TCP";
  }
  else
  {
    bstringResult += "UDP";
  }
  return(bstringResult);
}


std::string CProtocolPort::ToString() const
{
  std::string stringResult = zfc::UWORDToString(_nPortNumber, 10);
  stringResult += "/";

  if (_uwProtocolType == IPPROTO_TCP)
  {
    stringResult += "TCP";
  }
  else
  {
    stringResult += "UDP";
  }
  return(stringResult);
}


ZLS_END_NAMESPACE

