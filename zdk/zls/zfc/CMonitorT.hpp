/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CMonitorT.hpp,v $
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


#ifndef _ZLS_zfc_CMonitorT_hpp_
#define _ZLS_zfc_CMonitorT_hpp_

#include <zls/zfc/CMonitor.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


template <class T>
class CMonitorT : public CMonitor
{
  private:
    T & _rciTarget;

  public:
    /**
     * Constructor.
     *
     * @throw zfc::ESystemCallFailure.
     */
    CMonitorT(T & rciTarget)
      :_rciTarget(rciTarget)
    { }

    T & operator*()
    {
      return _rciTarget;
    }

    const T & operator*() const
    {
      return _rciTarget;
    }

    T * operator->()
    {
      return &_rciTarget;
    }

    const T * operator->() const
    {
      return &_rciTarget;
    }

    T & Get()
    {
      return _rciTarget;
    }
};


ZLS_END_NAMESPACE


#endif

