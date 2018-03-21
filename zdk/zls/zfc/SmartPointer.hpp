/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/SmartPointer.hpp,v $
 *
 * $Date: 2001/11/14 17:25:10 $
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


#ifndef _ZLS_zfc_SmartPointer_hpp_
#define _ZLS_zfc_SmartPointer_hpp_

#include <zls/zfc/Manifest.h>
#include <zls/zfc/CMutex.hpp>


// Begin namespace 'zfc::'
ZLS_BEGIN_NAMESPACE(zfc)


/**
 * This is a base class to be used in conjunction with the CSmartPointerT class.
 *
 * @todo 为什么不直接在CReferenceCounter中加入增加、减少"计数器"的method或operator呢?
 * 这是因为CReferenceCounter将作为所有需要"引用计数"的class的一个基类，如果将这些增加、
 * 减少"计数器"的method或operator放置在public区，则有可能在派生类中会无意地override了
 * 它们。为了效率的原因，这些代码我使用inline的方式。
 */
class CReferenceCounter {
  private:
    /**
     * 隐藏掉copy constructor和assignment operator，因为我不允许这种操作.
     *
     * @note 如果派生类需要copy constructor和assignment operator，在用户自己没有
     * 编写的情况下compiler会替用户编写一个，但是它甚至连基类CReferenceCounter
     * 以及CReferenceCounter::_ciReferMutex都想copy，这时编译时肯定报错，这正是
     * 我所希望的，因为采用"引用计数"技术后的copy语义是不应该能copy"引用计数"的，
     * 而应该只copy派生类的"内容"，因此用户必须自己定义一个copy constructor和
     * assignment operator.
     */
    CReferenceCounter(const CReferenceCounter &);
    CReferenceCounter & operator=(const CReferenceCounter &);

    long _lReferenceCount;
    #if defined(ENABLE_THREADS) && !defined(WIN32)
    CMutex _ciReferMutex;
    #endif

  public:
    /**
     * 自杀method.
     *
     * @note 2001/5/9:在做ZLang时发现，如果类采用"public virtual"继承时，则
     * CSmartPointerT<虚基类>的delete将使free()函数抱怨：
     * <pre>
     *   zlang in free(): warning: modified (chunk-) pointer.
     * </pre>
     * 因此我引进这个自杀method，让采用虚继承的派生类可以通过重实现它来正确
     * 地调用delete。如果不是采用虚继承的派生类则不用再重实现它.
     */
    virtual void SelfDestruct()
    { delete this; }

    CReferenceCounter()
     : _lReferenceCount(0)
    { }

    virtual ~CReferenceCounter()
    { }

  template <class T, bool bNeedThreadMutex> friend class CSmartPointerT;
};


#ifdef ENABLE_THREADS
  #define __LOCK_REFERENCE_COUNTER    \
    if (bNeedThreadMutex) \
    { _pciTarget->_ciReferMutex.Lock(); }

  #define __UNLOCK_REFERENCE_COUNTER        \
    if (bNeedThreadMutex) \
    { _pciTarget->_ciReferMutex.Unlock(); }

  #define __WIN32_INCREMENT_REFERENCE_COUNTER   \
    InterlockedIncrement(&_pciTarget->_lReferenceCount)

  #define __WIN32_DECREMENT_REFERENCE_COUNTER   \
    InterlockedDecrement(&_pciTarget->_lReferenceCount)
#else
  #define __LOCK_REFERENCE_COUNTER
  #define __UNLOCK_REFERENCE_COUNTER
  #define __WIN32_INCREMENT_REFERENCE_COUNTER   \
    ++_pciTarget->_lReferenceCount
  #define __WIN32_DECREMENT_REFERENCE_COUNTER   \
    --_pciTarget->_lReferenceCount
#endif


/**
 *  This class is a handle to a reference counted object. This ensures
 *  that the object is deleted when it is no longer referenced.
 */
template <class T, bool bNeedThreadMutex = true>
class CSmartPointerT {
  private:
    T * _pciTarget; // Referenced object

  public:
    CSmartPointerT(T * pciTarget = 0);
    CSmartPointerT(const CSmartPointerT<T, bNeedThreadMutex> & rautoOther);

    /**
     *  Destructor.
     *  Deletes object when reference count drops to zero.
     */
    ~CSmartPointerT();

    /**
     *  Assignment operator.
     */
    CSmartPointerT<T, bNeedThreadMutex> & operator=(T * pciOther);
    CSmartPointerT<T, bNeedThreadMutex> & operator=(const CSmartPointerT<T, bNeedThreadMutex> & rautoOther);

    /**
     *  Equality and inequality.
     */
    bool operator==(const CSmartPointerT<T, bNeedThreadMutex> & rautoOther) const
    {
      return (_pciTarget == rautoOther._pciTarget);
    }
    bool operator!=(const CSmartPointerT<T, bNeedThreadMutex> & rautoOther) const
    {
      return (_pciTarget != rautoOther._pciTarget);
    }

    /**
     *  Logical not operator and bool operator.
     *  For testing whether are we referring to a valid pointer ?
     */
    bool operator!() const
    {
      return (_pciTarget == 0);
    }
    operator bool() const
    {
      return (_pciTarget != 0);
    }

    /**
     *  Make access to the pointer intuitive.
     */
    T * operator->()
    {
      return (_pciTarget);
    }
    const T * operator->() const
    {
      return (_pciTarget);
    }

    T * get()
    {
      return (_pciTarget);
    }
    const T * get() const
    {
      return (_pciTarget);
    }

    T & operator*()
    {
      return (*_pciTarget);
    }
    const T & operator*() const
    {
      return (*_pciTarget);
    }

    /**
     *  De-reference.
     */
    void DeReference();
};

template <class T, bool bNeedThreadMutex>
CSmartPointerT<T, bNeedThreadMutex>::CSmartPointerT(T * pciTarget)
  : _pciTarget(pciTarget)
{
  if (_pciTarget != 0)
  {
    //
    // Boost reference count.
    //
    #ifdef WIN32
    __WIN32_INCREMENT_REFERENCE_COUNTER;
    #else
    __LOCK_REFERENCE_COUNTER;
    ++_pciTarget->_lReferenceCount;
    __UNLOCK_REFERENCE_COUNTER;
    #endif
  }
}


template <class T, bool bNeedThreadMutex>
CSmartPointerT<T, bNeedThreadMutex>::~CSmartPointerT()
{
  #ifdef WIN32
  if (_pciTarget != 0 && __WIN32_DECREMENT_REFERENCE_COUNTER == 0)
  {
    //::delete _pciTarget;
    // 2001/5/9: 改为调用virtual SelfDestruct()
    _pciTarget->SelfDestruct();
  }
  #else
  if (_pciTarget != 0)
  {
    bool bDeleteIt = false;

    __LOCK_REFERENCE_COUNTER;
    if (--_pciTarget->_lReferenceCount == 0)
      bDeleteIt = true;
    /*
     * 为什么要引进bDeleteIt呢，这是怕如果Leave Mutex后再判断_pciTarget->_lReferenceCount
     * 为0否可能会存在着边界效应。其实如果CReferenceCounter有自己的DecreaseCounter()方法的
     * 话，则DecreaseCounter()方法可能要如下：
     *
     *   int CReferenceCounter::DecreaseCounter()
     *   {
     *     _ciReferMutex.Lock();
     *     int n = --_pciTarget->_lReferenceCount;  // 一定要有临时变量，否则还是会有边界效应
     *     _ciReferMutex.Unlock();
     *     return n;
     *   }
     */
    __UNLOCK_REFERENCE_COUNTER;

    if (bDeleteIt)
    {
      //::delete _pciTarget;
      // 2001/5/9: 改为调用virtual SelfDestruct()
      _pciTarget->SelfDestruct();
    }
  }
  #endif
}


template <class T, bool bNeedThreadMutex>
CSmartPointerT<T, bNeedThreadMutex>::CSmartPointerT(const CSmartPointerT<T, bNeedThreadMutex> & rautoOther)
  : _pciTarget(rautoOther._pciTarget)
{
  if (_pciTarget != 0)
  {
    //
    // Boost reference count.
    //
    #ifdef WIN32
    __WIN32_INCREMENT_REFERENCE_COUNTER;
    #else
    __LOCK_REFERENCE_COUNTER;
    ++_pciTarget->_lReferenceCount;
    __UNLOCK_REFERENCE_COUNTER;
    #endif
  }
}


template <class T, bool bNeedThreadMutex>
CSmartPointerT<T, bNeedThreadMutex> &
CSmartPointerT<T, bNeedThreadMutex>::operator=(T * pciOther)
{
  if (_pciTarget == pciOther)
    return (*this);

  #ifdef WIN32
  if (_pciTarget != 0 && __WIN32_DECREMENT_REFERENCE_COUNTER == 0)
  {
    //::delete _pciTarget;
    // 2001/5/9: 改为调用virtual SelfDestruct()
    _pciTarget->SelfDestruct();
  }

  // Copy pciOther.
  _pciTarget = pciOther;  /* 这里在thread环境中还是有问题，怎么改进呢? */

  // Boost reference count.
  if (_pciTarget != 0)  /* 这里在thread环境中还是有问题，怎么改进呢? */
    __WIN32_INCREMENT_REFERENCE_COUNTER;
  #else
  if (_pciTarget != 0)
  {
    //
    // Time to clean out object?
    //
    bool bDeleteIt = false;

    __LOCK_REFERENCE_COUNTER;
    if (--_pciTarget->_lReferenceCount == 0)
      bDeleteIt = true;
    __UNLOCK_REFERENCE_COUNTER;

    if (bDeleteIt)
    {
      //::delete _pciTarget;
      // 2001/5/9: 改为调用virtual SelfDestruct()
      _pciTarget->SelfDestruct();
    }
  }

  // Copy pciOther.
  _pciTarget = pciOther;

  // Boost reference count.
  if (_pciTarget != 0)
  {
    __LOCK_REFERENCE_COUNTER;
    ++_pciTarget->_lReferenceCount;
    __UNLOCK_REFERENCE_COUNTER;
  }
  #endif

  return (*this);
}


template <class T, bool bNeedThreadMutex>
CSmartPointerT<T, bNeedThreadMutex> &
CSmartPointerT<T, bNeedThreadMutex>::operator=(const CSmartPointerT<T, bNeedThreadMutex> & rautoOther)
{
  if (_pciTarget == rautoOther._pciTarget)
    return (*this);

  #ifdef WIN32
  if (_pciTarget != 0 && __WIN32_DECREMENT_REFERENCE_COUNTER == 0)
  {
    //::delete _pciTarget;
    // 2001/5/9: 改为调用virtual SelfDestruct()
    _pciTarget->SelfDestruct();
  }

  // Copy rautoOther's referenced-pointer.
  _pciTarget = rautoOther._pciTarget;

  // Boost reference count.
  if (_pciTarget != 0)
    __WIN32_INCREMENT_REFERENCE_COUNTER;
  #else
  if (_pciTarget != 0)
  {
    //
    // Time to clean out object?
    //
    bool bDeleteIt = false;

    __LOCK_REFERENCE_COUNTER;
    if (--_pciTarget->_lReferenceCount == 0)
      bDeleteIt = true;
    __UNLOCK_REFERENCE_COUNTER;

    if (bDeleteIt)
    {
      //::delete _pciTarget;
      // 2001/5/9: 改为调用virtual SelfDestruct()
      _pciTarget->SelfDestruct();
    }
  }

  // Copy rautoOther's referenced-pointer.
  _pciTarget = rautoOther._pciTarget;
  // Boost reference count.
  if (_pciTarget != 0)
  {
    __LOCK_REFERENCE_COUNTER;
    ++_pciTarget->_lReferenceCount;
    __UNLOCK_REFERENCE_COUNTER;
  }
  #endif

  return (*this);
}


template <class T, bool bNeedThreadMutex>
void CSmartPointerT<T, bNeedThreadMutex>::DeReference()
{
  #ifdef WIN32
  if (_pciTarget != 0 && __WIN32_DECREMENT_REFERENCE_COUNTER == 0)
  {
    //::delete _pciTarget;
    // 2001/5/9: 改为调用virtual SelfDestruct()
    _pciTarget->SelfDestruct();
  }
  #else
  if (_pciTarget != 0)
  {
    bool bDeleteIt = false;

    __LOCK_REFERENCE_COUNTER;
    if (--_pciTarget->_lReferenceCount == 0)
      bDeleteIt = true;
    __UNLOCK_REFERENCE_COUNTER;

    if (bDeleteIt)
    {
      //::delete _pciTarget;
      // 2001/5/9: 改为调用virtual SelfDestruct()
      _pciTarget->SelfDestruct();
    }
  }
  #endif

  _pciTarget = 0;
}


ZLS_END_NAMESPACE


#endif

