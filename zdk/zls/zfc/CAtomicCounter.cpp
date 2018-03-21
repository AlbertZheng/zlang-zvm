/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CAtomicCounter.cpp,v $
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


#include <zls/zfc/CAtomicCounter.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


#ifdef HAVE_ATOMIC

#error "To doing"

#else

CAtomicCounter::CAtomicCounter()
{
  _udwCounter = 0;
}

CAtomicCounter::CAtomicCounter(UDWORD udwValue)
{
  _udwCounter = udwValue;
}

UDWORD CAtomicCounter::operator++()
{
  UDWORD udwValue;

  _ciMutex.Lock();
  udwValue = ++_udwCounter;
  _ciMutex.Unlock();
  return udwValue;
}

UDWORD CAtomicCounter::operator--()
{
  UDWORD udwValue;
  _ciMutex.Lock();
  udwValue = --_udwCounter;
  _ciMutex.Unlock();
  return udwValue;
}

UDWORD CAtomicCounter::operator++(int)
{
  UDWORD udwOld;

  _ciMutex.Lock();
  udwOld = _udwCounter;
  ++_udwCounter;
  _ciMutex.Unlock();
  return udwOld;
}

UDWORD CAtomicCounter::operator--(int)
{
  UDWORD udwOld;
  _ciMutex.Lock();
  udwOld = _udwCounter;
  --_udwCounter;
  _ciMutex.Unlock();
  return udwOld;
}

UDWORD CAtomicCounter::operator+=(UDWORD udwChange)
{
  UDWORD udwValue;
  _ciMutex.Lock();
  _udwCounter += udwChange;
  udwValue = _udwCounter;
  _ciMutex.Unlock();
  return udwValue;
}

UDWORD CAtomicCounter::operator-=(UDWORD udwChange)
{
  UDWORD udwValue;
  _ciMutex.Lock();
  _udwCounter -= udwChange;
  udwValue = _udwCounter;
  _ciMutex.Unlock();
  return udwValue;
}

UDWORD CAtomicCounter::operator+(UDWORD udwChange)
{
  UDWORD udwValue;
  _ciMutex.Lock();
  udwValue = _udwCounter + udwChange;
  _ciMutex.Unlock();
  return udwValue;
}

UDWORD CAtomicCounter::operator-(UDWORD udwChange)
{
  UDWORD udwValue;
  _ciMutex.Lock();
  udwValue = _udwCounter - udwChange;
  _ciMutex.Unlock();
  return udwValue;
}

UDWORD CAtomicCounter::operator=(UDWORD udwValue)
{
  UDWORD udwOld;
  _ciMutex.Lock();
  udwOld = _udwCounter;
  _udwCounter = udwValue;
  _ciMutex.Unlock();
  return udwOld;
}

bool CAtomicCounter::operator!() const
{
  UDWORD udwValue;
  _ciMutex.Lock();
  udwValue = _udwCounter;
  _ciMutex.Unlock();
  if (udwValue)
  {
    return false;
  }
  else
  {
    return true;
  }
}

CAtomicCounter::operator UDWORD() const

{
  UDWORD udwValue;
  _ciMutex.Lock();
  udwValue = _udwCounter;
  _ciMutex.Unlock();
  return udwValue;
}

#endif


ZLS_END_NAMESPACE
