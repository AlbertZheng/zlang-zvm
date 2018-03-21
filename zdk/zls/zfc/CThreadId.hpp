/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CThreadId.hpp,v $
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


#ifndef _ZLS_zfc_CThreadId_h_
#define _ZLS_zfc_CThreadId_h_

#include <zls/zfc/Manifest.h>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


/**
 * This class represents a thread id under POSIX threads, and DCE threads.
 *
 * @attention "pthread_t"其实是"struct pthread *"，它的具体形式没有被规定，在
 * 各种不同的OS上可能有不同的形式，因此将pthread_t认为是unsigned int或unsigned
 * long等的typedef是可怕的，最好不要有类似如下的危险代码：
 *
 *       sprintf(buffer, "%lu", pthread_self())
 *
 * @note FreeBSD上是个"struct *"；Linux上是个unsigned long.
 */
class CThreadId
{
  private:
     /** The thread id. */
    pthread_t _siId;

  public:
    bool operator == (const CThreadId & rhs) const
    {
      return pthread_equal(_siId, rhs._siId);
    }


    bool operator != (const CThreadId & rhs) const
    {
      return !(pthread_equal(_siId, rhs._siId));
    }


    const CThreadId & operator = (const CThreadId & rhs)
    {
      _siId = rhs._siId;  // copy pointer
      return *this;
    }


    /**
     * Conversion operator.
     */
    operator pthread_t() const
    {
      return _siId;
    }

    std::string ToString() const;

    /**
     * Constuctor. By default it is the id of current thread which calling the constructor.
     */
    CThreadId()
      :_siId(pthread_self())
    { }

    CThreadId(pthread_t id)
      :_siId(id)
    { }

    CThreadId(const CThreadId & rhs)
    {
      _siId = rhs._siId;  // copy pointer
    }
};


ZLS_END_NAMESPACE


#endif

