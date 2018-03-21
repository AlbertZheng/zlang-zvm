/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/Memory.hpp,v $
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


#ifndef _ZLS_zfc_Memory_hpp_
#define _ZLS_zfc_Memory_hpp_

#include <zls/zfc/Manifest.h>
#include <zls/zfc/Memory.h>
#include <zls/zfc/Exception.hpp>


/**
 * 这个宏帮你catch std::bad_alloc即其派生类zfc::EOutOfMemory.
 */
#define RECOVER_FROM_new(codesAction)      \
                         /* 捕捉std::bad_alloc或其派生类zfc::EOutOfMemory */ \
   catch (std::bad_alloc & e) { \
     LogWarning(("Warning: %s", e.what())); \
     /* 简单的代码，不要有逗号 */ \
     codesAction; \
   }


#ifdef ENABLE_OVERLOAD_OPERATOR_NEW
  // 好象不需要#include <new.h>也行！
  #include <new.h>   /* Important,这样我们就能够重载掉全局的new、delete */

  /**
   * 我扩展的operator new()的placement.
   */
  enum _TOperatorNewPlacement {
    /**
     * 和常规的malloc()相似，即当Out of memory时返回0指针，这是默认方式.
     *
     * @attention 从新的C++ standard(1998)开始，operator new(size_t)在out of memory
     * 时已经缺省默认为：如果有用户New-Handler则循环调用它直至内存申请成功，否则
     * throw std::bad_alloc，而不是象传统的那样返回0指针.
     */
    _TYPICAL = 2,
    _THROW = false,  ///< 当Out of memory时throw zfc::EOutOfMemory.
    _ABORT = true    ///< 当Out of memory时强制abort程序.
  };

  /**
   * 具有多个额外参数的重载operator new()，以便可以跟踪调用new时的源码行号信息.
   *
   * @note 这个operator new(...)可以让用户决定当::operator new(...)触发out of
   * memory时是否按默认方式返回0指针、或者是强制终止程序、或者是throw
   * zfc::EOutOfMemory，这些都由用户来自行掌握.
   *
   * @throw zfc::EOutOfMemory 当用户愿意时.
   */
  void * operator new(size_t size,
                      const char * pszFile,
                      const int nLine,
                      _TOperatorNewPlacement ePlacementWhenOOM = _TYPICAL);

  /**
   * 这个宏用来帮助调用new(size_t, const char *, const int, _TOperatorNewPlacement)，
   * 使用"new __OPTION(_TYPICAL/_ABORT/_THROW) ..."则跟踪的行号才是正确的，否则行号
   * 始终是在Memory.cpp调用_ZLS_malloc_backend(size, __FILE__, __LINE__,...)这行.
   */
  #define __OPTION(OperatorNewPlacement)        (__FILE__, __LINE__, OperatorNewPlacement)


  /*
   * "#define new new(__FILE__, __LINE__)"
   *
   * 定义上面的宏是可以使我们在new时能够跟踪(只要该程序#include "Manifest.h")，
   * 但是我希望的是一些已经被编译的lib或".o"(它们在被编译的时候并没有#include
   * "Manifest.h")也能够在被我们link它们时自动改为使用我的跟踪版本的new，而宏
   * 是没有办法实现这个目的的！
   *
   * 但是如果下面这个的operator new采用inline，则这个目的还是失败，因此如果希望
   * 一些已经被编译的lib或".o"也能够跟踪（不过这种跟踪是无效的，因为行号始终是
   * Memory.cpp中调用::operator new(size, __FILE__, __LINE__)这行，不过还是有些
   * 好处，毕竟已强制将new转为隐含调用ZLS_malloc()，这样我的
   * _ZLS_malloc_out_of_memory_handler()就有了用武之地了）。
   */


  /**
   * 重载C++常规的operator new(size_t).
   *
   * @note 这个重载的operator new(size_t)的prototype和功能与C++常规的operator new(size_t)
   * 相同，而在内部实现上有不同的两点：
   * (1) 其内部是调用了我的ZLS_malloc();
   * (2) 当触发Out of memory时，由ZLS_malloc()释放保留内存，然后返回0指针，最后
   * 再由这个operator new(size_t)来throw zfc::EOutOfMemory（注：C++常规的
   * 是throw std::bad_alloc，但是由于zfc::EOutOfMemory是std::bad_alloc的
   * 派生类，因此这对已有的代码不会产生任何的影响）.
   *
   * @attention 即使已经被compile的lib或".o"在compile时没有#include <zls/zfc/Memory.hpp>，
   * 但是只要与libzfc.a链结了，则它们内部的对operator new(size_t)的调用也将统统被link到我
   * 的这个operator new(size_t).
   *
   * @throw EOutOfMemory 当Out of memory时.
   */
  void * operator new(size_t size);

  /**
   * 重载C++常规的operator delete().
   *
   * @note 这个重载的operator delete()的prototype和功能上与C++常规的operator delete()相同，
   * 而在内部实现上有不同的一点：(1) 其内部是调用了我的ZLS_free().
   */
  void operator delete(void * p);

  #if ! defined( OPERATOR_NEW_ARRAY ) \
      && (__BORLANDC__ >= 0x450 || \
          (__GNUC__ >= 2 && __GNUC_MINOR__ >= 6) || __GNUC__ == 3 \
          || __WATCOMC__ >= 1050 || _MSC_VER >= 1100)
    #define OPERATOR_NEW_ARRAY
  #endif
  #if defined(OPERATOR_NEW_ARRAY)
    /**
     * 具有多个额外参数的重载operator new[]()，以便可以跟踪调用new时的源码行号信息.
     *
     * @note 这个operator new[](...)可以让用户决定当::operator new[](...)触发
     * out of memory时是否按默认方式返回0指针,或者是强制终止程序，或者是throw
     * EOutOfMemory，这些都由用户来自行掌握.
     *
     * @throw EOutOfMemory 当用户愿意时.
     */
    inline void * operator new[](size_t size,
                                 const char * pszFile,
                                 const int nLine,
                                 _TOperatorNewPlacement ePlacementWhenOOM = _TYPICAL)
    {
      return ::operator new(size, pszFile, nLine, ePlacementWhenOOM);
    }

    /**
     * 重载C++常规的operator new[](size_t).
     *
     * @note 这个重载的operator new[](size_t)的prototype和功能与C++常规的operator new[](size_t)
     * 相同，而在内部实现上有不同的两点：
     * (1) 其内部是调用了我的ZLS_malloc();
     * (2) 当触发Out of memory时，由ZLS_malloc()释放保留内存，然后返回0指针，最后
     * 再由这个operator new[](size_t)来throw zfc::EOutOfMemory（注：C++常规的
     * 是throw std::bad_alloc，但是由于zfc::EOutOfMemory是std::bad_alloc的
     * 派生类，因此这对已有的代码不会产生任何的影响）.
     *
     * @attention 即使已经被compile的lib或".o"在compile时没有#include <zls/zfc/Memory.hpp>，
     * 但是只要与libzfc.a链结了，则它们内部的对operator new[](size_t)的调用也将统统被link到我
     * 的这个operator new[](size_t).
     *
     * @throw EOutOfMemory 当Out of memory时.
     */
    void * operator new[](size_t size);

    /**
     * 重载C++常规的operator delete[]().
     *
     * @note 这个重载的operator delete[]()的prototype和功能上与C++常规的operator delete[]()相同，
     * 而在内部实现上有不同的一点：(1) 其内部是调用了我的ZLS_free().
     */
    void operator delete[](void * p);
  #endif  // OPERATOR_NEW_ARRAY
#endif  // ENABLE_OVERLOAD_OPERATOR_NEW


#include <alloc.h>  // STL

ZLS_BEGIN_NAMESPACE(zfc)

/**
 * STL out of memory handler.
 *
 * @note: This is private internal interface.
 */
void _ZLS_STL_out_of_memory_handler();

/**
 * Install "operator new(size_t)" and "STL" out of memory handler.
 *
 * @note
 * (1) SGI STL的缺省Out-Of-Memory-Handler的处理方式是：先打印错误信息，然后exit()。
 * 当然我是不希望exit()的，至少abort()比exit()能起点跟踪作用.
 * (2) C++的"operator new(size_t)"的缺省Out-Of-Memory-Handler的处理方式是：如果
 * 用户安装了new handler，则循环“先call-back它，然后再malloc()”，如此循环直至
 * malloc()成功为止；如果用户没有安装new handler，则立即throw std::bad_alloc.
 * (3) 而我的这个Handler中的处理方式是：先释放保留内存，然后立即throw
 * zfc::EOutOfMemory.
 *
 * @attention 通常在main()的开始处、还没开始第一次使用任何的STL template之前就应
 * 该先调用Install_STL_out_of_memory_handler().
 */
inline void Install_STL_out_of_memory_handler()
{
  // 也顺便安装new handler
  std::set_new_handler(_ZLS_STL_out_of_memory_handler);
  std::malloc_alloc::__set_malloc_handler(_ZLS_STL_out_of_memory_handler);
}

ZLS_END_NAMESPACE


#endif

