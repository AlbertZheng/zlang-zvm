/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CAtomicCounter.hpp,v $
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


#ifndef _ZLS_zfc_CAtomicCounter_hpp_
#define _ZLS_zfc_CAtomicCounter_hpp_

#include <zls/zfc/Manifest.h>

#include <zls/zfc/CMutex.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


/**
 * The CAtomicCounter class offers thread-safe manipulation of an integer
 * counter.  These are commonly used for building thread-safe "reference"
 * counters for C++ classes.  The CAtomicCounter depends on the platforms
 * support for "atomic" integer operations, and can alternately substitute
 * a "mutex" if no atomic support exists.
 *
 * @attention 使用CAtomicCounter时不要采用继承的方式，以免CAtomicCounter重载的
 * 各种operator混淆（影响）了你的派生类.
 * 
 * @author 郑立松 <lisong.zheng@gmail.com>
 * @short atomic counter operation.
 */
class CAtomicCounter
{
  private:
    #ifdef HAVE_ATOMIC
      atomic_t _atomic;
    #else
      UDWORD _udwCounter;
      CMutex _ciMutex;
    #endif

  public:
    /**
     * Initialize an atomic to 0.
     */
    CAtomicCounter();

    /**
     * Initialize an atomic to a known value.
     *
     * @param initial value.
     */
    CAtomicCounter(UDWORD udwValue);

    /** Prefix ++. */
    UDWORD operator++();
    /** Prefix --. */
    UDWORD operator--();
    /** Postfix ++. */
    UDWORD operator++(int);
    /** Postfix --. */
    UDWORD operator--(int);

    UDWORD operator+=(UDWORD udwChange);
    UDWORD operator-=(UDWORD udwChange);
    UDWORD operator+(UDWORD udwChange);
    UDWORD operator-(UDWORD udwChange);
    UDWORD operator=(UDWORD udwValue);
    bool operator!() const;
    operator UDWORD() const;
};


ZLS_END_NAMESPACE


#endif

