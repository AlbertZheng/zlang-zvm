/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CSynchronized.hpp,v $
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


#ifndef _ZLS_zfc_CSynchronized_hpp_
#define _ZLS_zfc_CSynchronized_hpp_

#include <zls/zfc/CMonitor.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


/**
 * This class is used to lock and unlock a monitor.
 */
class CSynchronized
{
  private:
    /**
     * 隐藏掉copy constructor、assignment operator和new operator，因为我不允许这种操作.
     */
    CSynchronized(const CSynchronized &);
    CSynchronized & operator=(const CSynchronized &);
    void * operator new(size_t size);
    void * operator new[](size_t size);

    /** The lock type. */
    enum TLockedType {
      tltLOCKED_MONITOR,
      tltLOCKED_MUTEX,
    } _eLockType;

    union {
      /** Associated monitor. */
      const CMonitor * _pciMonitor;

      /** Associated mutex. */
      const CMutex * _pciMutex;
    };

  public:
    /**
     * Constructor.
     *
     * @throw zfc::ESystemCallFailure.
     */
    CSynchronized(const CMonitor & rciMonitor);

    /**
     * Constructor.
     *
     * @throw zfc::ESystemCallFailure.
     */
    CSynchronized(const CMutex & rciMutex);

    ~CSynchronized();
};


ZLS_END_NAMESPACE


#endif

