/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CSynchronized.cpp,v $
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


#include <zls/zfc/CSynchronized.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


CSynchronized::CSynchronized(const CMonitor & rciMonitor)
  :_pciMonitor(&rciMonitor),
   _eLockType(tltLOCKED_MONITOR)
{
  _pciMonitor->Lock();
}


CSynchronized::CSynchronized(const CMutex & rciMutex)
  :_pciMutex(&rciMutex),
   _eLockType(tltLOCKED_MUTEX)
{
  _pciMutex->Lock();
}


CSynchronized::~CSynchronized()
{
  try {
    switch(_eLockType)
    {
      case tltLOCKED_MONITOR:
        _pciMonitor->Unlock();
        break;

      case tltLOCKED_MUTEX:
        _pciMutex->Unlock();
        break;
    }
  }
  catch(ESystemCallFailure & e)
  // 注意：Destructor是不允许throw exception的，因为当某个function抛出一个
  // exception后，compiler在调用链上unwind时要调用Destructor，此时如果可能
  // 再抛出exception则是不可意料的，通常compiler会调用terminate().
  {
  }
}


ZLS_END_NAMESPACE

