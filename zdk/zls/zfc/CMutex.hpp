/**
 * $Header: /backup/cvsroot/project/pnids/zdk/zls/zfc/CMutex.hpp,v 1.3 2001/11/14 17:25:11 zls Exp $
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


#ifndef _ZLS_zfc_CMutex_hpp_
#define _ZLS_zfc_CMutex_hpp_

#include <zls/zfc/Manifest.h>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


/**
 * CMutex实现了可"递归"的"互斥"锁功能.
 */
class CMutex
{
  private:
    /**
     * 隐藏掉copy constructor和assignment operator，因为我不允许这种操作.
     */
    CMutex(const CMutex &);
    const CMutex & operator = (const CMutex &);

    // 如果OS没有支持"可递归"的Mutex，即在<pthread.h>中没有定义PTHREAD_MUTEX_RECURSIVE
    // 不过FreeBSD却是使用enum的，怎么办呀，是否应该写m4宏来自动检测?
    #if ! defined(HAVE_PTHREAD_MUTEX_RECURSIVE)
    volatile int       _nLockedLevel;
    volatile pthread_t _siOwnerThreadId;
    #endif

  protected:
    pthread_mutex_t _siMutex;

  public:
    /**
     * Constructor.
     *
     * @throw ESystemCallFailure - 当pthread系统调用返回为EINVAL(The value
     * specified by attribute is invalid)或ENOMEM或EAGAIN(The temporarily lacks
     * the resources to create another mutex)时.
     *
     * @note 如果OS支持"递归"型mutex的话，总是初始化为"递归"型mutex.
     */
    CMutex();

    /**
     * Destroying the mutex removes any system resources associated with it.
     *
     * @attention If the mutex is locked currently by self thread, it is
     * presumed to unlock when the mutex is destroyed, but if it is locked
     * by another thread, a warning will be logged to logger.
     */
    ~CMutex();

    /**
     * Locking the mutex for the current thread.
     *
     * @throw ESystemCallFailure - 当pthread系统调用返回为EINVAL或EDEADLK时.
     *
     * @see CMutex::Unlock()
     */
    void Lock() const;

    /**
     * Tries to lock the mutex for the current thread. Behaves like
     * CMutex::Lock() , except that it doesn't block the calling thread
     * if the mutex is already locked by another thread.
     *
     * @return true If locking the mutex was succesful；false如果pthread系统
     * 调用返回为EBUSY(Mutex is locked by another thread).
     *
     * @throw ESystemCallFailure - 当pthread系统调用返回为EINVAL时.
     *
     * @see CMutex::Lock()
     * @see CMutex::Unlock()
     */
    bool TryLock() const;

    /**
     * Leaving a mutex frees that mutex for use by another thread.  If
     * the mutex has been entered (invoked) multiple times (recursivily)
     * by the same thread, then it will need to be exited the same number
     * of instances before it is free for re-use.
     *
     * @throw ESystemCallFailure - 当pthread系统调用返回为EINVAL或EPERM(
     * The current thread does not hold a lock on mutex)时.
     *
     * @see CMutex::Lock()
     */
    void Unlock() const;
};


ZLS_END_NAMESPACE


#endif

