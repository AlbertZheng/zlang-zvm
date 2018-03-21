/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CSingletonFactoryT.hpp,v $
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


#ifndef _ZLS_zfc_CSingletonFactoryT_hpp_
#define _ZLS_zfc_CSingletonFactoryT_hpp_

#include <zls/zfc/Manifest.h>
#include <zls/zfc/SmartPointer.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


/**
 * 这是一个"单件"工厂template，它只适用于constructor是default constructor的class.
 *
 * @note 如果一个class想限制在一个程序中只能有一个自己的"单件"实例，则必须：
 * <pre>
 * (1)这个class必须从zfc::CReferenceCounter继承.
 * (2)将这个class的constructor放置在private或protected区中，这样可以防止用户误用
 * new或"自动变量"来创建这个class的实例.
 * (3)如果想利用CSingletonFactoryT这个template来帮助用户创建实例，则这个class的
 * constructor必须是default constructor.
 * (4)让template CSingletonFactoryT成为这个class的friend.
 *
 * 以下是个应用举例：
 *   CSingletonFactoryT<YOUR_CLASS> factory;
 *   CSmartPointerT<YOUR_CLASS> autoSingleton = factory.GetSingleton();
 *   autoSingleton->any_method();
 * </pre>
 */
template <class CType>
class CSingletonFactoryT {
  public:
    typedef CSmartPointerT<CType> CSingleton_auto;

  private:
    /** 指向唯一的static singleton instance. */
    static CType * _SpciSingleton;

    /** 这个Smart Pointer将引用到那个唯一的static singleton instance. */
    CSingleton_auto _autoSingleton;

  public:
    /**
     * Constructor.
     *
     * @throw zfc::EOutOfMemory.
     */
    CSingletonFactoryT()
    {
      if (! _SpciSingleton)
      {
        _SpciSingleton = new __OPTION(_THROW) CType();
      }

      // Let us reference to the singleton
      _autoSingleton = _SpciSingleton;
    }

    CSingleton_auto & GetSingleton()
    {
      return _autoSingleton;
    }
};

template <class CType>
CType * CSingletonFactoryT<CType>::_SpciSingleton = 0;


ZLS_END_NAMESPACE


#endif

