/**
 * $Header: /backup/cvsroot/project/pnids/zdk/zls/zfc/CThreadSpecialStorage.cpp,v 1.3 2001/11/14 17:25:11 zls Exp $
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


#include <zls/zfc/CThreadSpecialStorage.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


CThreadSpecialStorage::CThreadSpecialStorage(void (*pfuncDestructor)(void *) = 0)
  : _pfuncDestructor(pfuncDestructor)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CThreadSpecialStorage::CThreadSpecialStorage()");
  int nResult;
  if ((nResult = pthread_key_create(&_siKey, pfuncDestructor)) != 0)
  {
    // nResult should be EAGAIN or ENOMEM
    throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_key_create", nResult);
  }
}


CThreadSpecialStorage::~CThreadSpecialStorage()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CThreadSpecialStorage::~CThreadSpecialStorage()");
  int nResult;
  if ((nResult = pthread_key_delete(_siKey)) != 0)
  {
    try {
      // nResult should be EINVAL
      throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_key_delete", nResult);
    }
    catch(ESystemCallFailure & e)
    // 注意：Destructor是不允许throw exception的，因为当某个function抛出一个
    // exception后，compiler在调用链上unwind时要调用Destructor，此时如果可能
    // 再抛出exception则是不可意料的，通常compiler会调用terminate().
    {
    }
  }
}


// gcc-2.95.2好象有bug：如果inline CThreadSpecialStorage::GetStorage()则link时会抱怨
//                      CThreadSpecialStorage::GetStorage()找不到.
void * CThreadSpecialStorage::GetStorage()
{
  return pthread_getspecific(_siKey);
}


void CThreadSpecialStorage::SetStorage(void * pvPointer)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CThreadSpecialStorage::SetStorage()");

  // 先释放以前SetStorage()时给的指针
  void * pv = GetStorage();
  if (pv && _pfuncDestructor)
  {
    _pfuncDestructor(pv);
  }

  int nResult;
  if ((nResult = pthread_setspecific(_siKey, pvPointer)) != 0)
  {
    // nResult should be EINVAL or ENOMEM
    throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_setspecific", nResult);
  }
}


ZLS_END_NAMESPACE

