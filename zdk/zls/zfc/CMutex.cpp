/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CMutex.cpp,v $
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


#include <zls/zfc/CMutex.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


CMutex::CMutex()
  #ifndef HAVE_PTHREAD_MUTEX_RECURSIVE
  :_nLockedLevel(0),
   _siOwnerThreadId(0)
  #endif
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCMutex::CMutex()");
  int nResult;
  pthread_mutexattr_t siAttribute;

  if ((nResult = pthread_mutexattr_init(&siAttribute)) != 0)
  {
    // nResult should be ENOMEM
    throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_mutexattr_init", nResult);
  }

  #ifdef HAVE_PTHREAD_MUTEX_RECURSIVE
  if ((nResult = pthread_mutexattr_settype(&siAttribute, PTHREAD_MUTEX_RECURSIVE)) != 0)
  {
    // nResult should be EINVAL
    throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_mutexattr_settype", nResult);
  }
  #endif

  if ((nResult = pthread_mutex_init(&_siMutex, &siAttribute)) != 0)
  {
    // nResult should be EINVAL or ENOMEM or EAGAIN(The temporarily lacks the resources to create another mutex)
    throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_mutex_init", nResult);
  }
}


CMutex::~CMutex()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCMutex::~CMutex()");
  int nResult;
  if ((nResult = pthread_mutex_destroy(&_siMutex)) != 0)
  {
    // nResult should be EINVAL or EBUSY(Mutex is locked by another thread)
    try {
      throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_mutex_destroy", nResult);
    }
    catch(ESystemCallFailure & e)
    // 注意：Destructor是不允许throw exception的，因为当某个function抛出一个
    // exception后，compiler在调用链上unwind时要调用Destructor，此时如果可能
    // 再抛出exception则是不可意料的，通常compiler会调用terminate().
    {
    }
  }
}


#if defined(HAVE_PTHREAD_MUTEX_RECURSIVE)
void CMutex::Lock() const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCMutex::Lock()");
  CMutex * pci = const_cast<CMutex *>(this);
  int nResult;
  if ((nResult = pthread_mutex_lock(&(pci->_siMutex))) != 0)
  {
    // nResult should be EINVAL or EDEADLK
    throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_mutex_lock", nResult);
  }
  // Q: 如果是"递归"型的，即使是自己再次lock也应该返回0吧，尚未证实?
}


bool CMutex::TryLock() const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCMutex::TryLock()");
  CMutex * pci = const_cast<CMutex *>(this);
  int nResult;
  if ((nResult = pthread_mutex_trylock(&(pci->_siMutex))) != 0)
  {
    // nResult should be EINVAL or EBUSY(Mutex is locked by another thread)
    if (nResult == EINVAL)
    // 不正确的pthread_mutex_t
    {
      throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_mutex_trylock", nResult);
    }
    else
    // 已经被locked过了，等待吧
    {
      // It must be EBUSY
      LogAssert0(nResult == EBUSY, "Oh, I must check POSIX thread's documents.");
      return false;
    }
  }
  else
  // Q: 如果是"递归"型的，即使是自己再次trylock也应该返回0吧，尚未证实?
  {
    return true;
  }
}


void CMutex::Unlock() const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCMutex::Unlock()");
  CMutex * pci = const_cast<CMutex *>(this);
  int nResult;
  if ((nResult = pthread_mutex_unlock(&(pci->_siMutex))) != 0)
  {
    // nResult should be EINVAL or EPERM(The current thread does not hold a lock on mutex)
    throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_mutex_unlock", nResult);
  }
}

#else

void CMutex::Lock() const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCMutex::Lock()");

  CMutex * pci = const_cast<CMutex *>(this);
  if (pci->_nLockedLevel)
  {
    if (pthread_equal(pci->_siOwnerThreadId, pthread_self()))
    {
      ++(pci->_nLockedLevel);
      return;
    }
  }

  int nResult;
  if ((nResult = pthread_mutex_lock(&(pci->_siMutex))) != 0)
  {
    // nResult should be EINVAL or EDEADLK
    throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_mutex_lock", nResult);
  }
  ++(pci->_nLockedLevel);
  pci->_siOwnerThreadId = pthread_self();
}


bool CMutex::TryLock() const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCMutex::TryLock()");

  CMutex * pci = const_cast<CMutex *>(this);
  if(pci->_nLockedLevel)
  {
    if(pthread_equal(pci->_siOwnerThreadId, pthread_self()))
    {
      ++(pci->_nLockedLevel);
      return true;
    }
    else
    {
      return false;
    }
  }

  int nResult;
  if ((nResult = pthread_mutex_trylock(&(pci->_siMutex))) != 0)
  {
    // nResult should be EINVAL or EBUSY(Mutex is locked by another thread)
    if (nResult == EINVAL)
    // 不正确的pthread_mutex_t
    {
      throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_mutex_trylock", nResult);
    }
    else
    // 已经被locked过了，等待吧
    {
      // It must be EBUSY
      LogAssert0(nResult == EBUSY, "Oh, I must check POSIX thread's documents.");
      return false;
    }
  }
  else
  {
    pci->_siOwnerThreadId = pthread_self();
    ++(pci->_nLockedLevel);
    return true;
  }
}


void CMutex::Unlock() const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CCMutex::Unlock()");

  CMutex * pci = const_cast<CMutex *>(this);
  if(pci->_nLockedLevel > 1)
  {
    --(pci->_nLockedLevel);
    return;
  }
  --(pci->_nLockedLevel);
  pci->_siOwnerThreadId = 0;

  int nResult;
  if ((nResult = pthread_mutex_unlock(&(pci->_siMutex))) != 0)
  {
    // nResult should be EINVAL or EPERM(The current thread does not hold a lock on mutex)
    throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_mutex_unlock", nResult);
  }
}
#endif


ZLS_END_NAMESPACE

