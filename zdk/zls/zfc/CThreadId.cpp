/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CThreadId.cpp,v $
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


#include <zls/zfc/CThreadId.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


std::string CThreadId::ToString() const
{
  std::string stringId;

  #if defined(HAVE_PTHREAD_H) && (defined(__FreeBSD__) || defined(__linux))
    unsigned long l = reinterpret_cast<unsigned long>(_siId);
    stringId = UDWORDToString(l, 10);
  #else
    #if defined(HAVE_DCE_THREADS)
      unsigned long l1 = reinterpret_cast<unsigned long>(_siId.field1);
      unsigned long l2 = reinterpret_cast<unsigned long>(_siId.field2);
        #if ! defined(__alpha__)
          stringId = "(" + l1 + "," + l2 + ")";
        #eles
          unsigned long l3 = reinterpret_cast<unsigned long>(_siId.field3);
          stringId = "(" + l1 + "," + l2 + "," + l3 + ")";
        #endif
    #else
      #error "Oh, I must check your OS for 'struct pthread' !"
    #endif
  #endif

  return stringId;
}


ZLS_END_NAMESPACE

