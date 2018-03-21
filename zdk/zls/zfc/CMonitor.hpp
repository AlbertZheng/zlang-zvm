/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CMonitor.hpp,v $
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


#ifndef _ZLS_zfc_CMonitor_hpp_
#define _ZLS_zfc_CMonitor_hpp_

#include <zls/zfc/Manifest.h>
#include <zls/zfc/CMutex.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


/**
 * CMonitor其实是一个内含有一个CMutex的类（而这个CMutex是专门准备给CSynchronized
 * 使用的），CMonitor通常作为其它需要使用CSynchronized来进行Thread同步的类的基类.
 */
class CMonitor {
  friend class CSynchronized;

  private:
    /**
     * 隐藏掉copy constructor和assignment operator，因为我不允许这种操作.
     */
    CMonitor(const CMonitor &);
    const CMonitor & operator=(const CMonitor &) ;

    CMutex _ciMutex;

    /**
     * Lock internal mutex.
     *
     * @throw ESystemCallFailure.
     */
    void Lock() const
    {
      _ciMutex.Lock();
    }

    /**
     * Unlock internal mutex.
     *
     * @throw ESystemCallFailure.
     */
    void Unlock() const
    {
      _ciMutex.Unlock();
    }

  public:
    /**
     * Constructor.
     *
     * @throw ESystemCallFailure.
     */
    CMonitor();

    /**
     * Destructor.
     */
    virtual ~CMonitor();
};


inline CMonitor::CMonitor()
{ }

inline CMonitor::~CMonitor()
{ }


ZLS_END_NAMESPACE


#endif

