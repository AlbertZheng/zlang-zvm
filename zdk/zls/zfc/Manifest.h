/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/Manifest.h,v $
 *
 * $Date: 2002/02/28 13:59:25 $
 *
 * $Revision: 1.5 $
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


#ifndef _ZLS_zfc_Manifest_h_
#define _ZLS_zfc_Manifest_h_

#include <zls/zfc/config.h>


/* 我的匈牙力命名法的变量缩写前缀.
 *******************************************************************************
 *  v      -> void
 *  df     -> double
 *  f      -> float
 *  mas    -> MASIZE（Machine Address Size,根据ILP32或LP64决定）
 *  sqw    -> SQWORD
 *  udw    -> UDWORD
 *  sdw    -> SDWORD
 *  uw     -> UWORD
 *  sw     -> SWORD
 *  nudw   -> NUDWORD
 *  nsdw   -> NSDWORD
 *  nuw    -> NUWORD
 *  nsw    -> NSWORD
 *  uch    -> UCHAR
 *  ch     -> char
 *  ci     -> class instance
 *  si     -> struct instance
 *  deque  -> std::deque instance
 *  vector -> std::vector instance
 *  list   -> std::list instance
 *  string -> std::string instance
 *  hmap   -> std::hash_map instance
 *  auto   -> Reference Handle(Smart Pointer)
 *  p      -> pointer
 ******************************************************************************/

/* 我的匈牙力命名法的类型缩写前缀.
 *******************************************************************************
 *  TUl...      -> struct or new type
 *  CUl...      -> class
 *  IUl...      -> interface class
 *  CUl...T     -> template class
 *  CUl..._auto -> Smart Pointer class
 ******************************************************************************/


/* OS环境定义 */
/*******************************************************************************
 *  Dec             : __alpha__     (64 bits)
 *  SCO Unixware    : __unixware__
 *  IBM RS6000      : __aix__
 *  SGI Irix        : __irix__      (32 or 64 bits)
 *  Sun Solaris     : __solaris__
 *  BSD compatible  : __bsd__
 *  SVR4 compatible : __svr4__
 *  SYS5 compatible : __sys5__
 *  HP HP-UX        : __hpux__
 *  WIN32           : __win32__ 或 WIN32(VC++的缺省定义)
 *  Linux           : __linux__
 *  FreeBSD         : __FreeBSD__(FreeBSD GCC的缺省定义)
 ******************************************************************************/

/* C/C++ Compiler */
/*******************************************************************************
 *  Borland C++ 4.5 : __BORLANDC__ = 0x450
 *  GNU GCC 2.95.2  : __GNUC__ = 2, __GNUG__ = 2, __GNUC_MINOR__ = 95
 *  GNU GCC 3.x     : __GNUC__ = 3, __GNUG__ = 3, __GNUC_MINOR__ = x
 *  GNU GCC 3.0.p   : __GNUC__ = 3, __GNUG__ = 3, __GNUC_MINOR__ = 0, __GNUC_PATCHLEVEL__ = p
 *  Watcom C++      : __WATCOMC__
 *
 *  GNU GCC 3.0有如下新编译选项可能要注意：
 *      -fcheck-new
 *          Check that the pointer returned by "operator new" is
 *          non-null before attempting to modify the storage allo-
 *          cated.  The current Working Paper requires that "oper-
 *          ator new" never return a null pointer, so this check
 *          is normally unnecessary.
 *
 *          An alternative to using this option is to specify that
 *          your "operator new" does not throw any exceptions; if
 *          you declare it throw(), g++ will check the return
 *          value.  See also new (nothrow).
 *
 *      -Wreturn-type
 *         Warn whenever a function is defined with a return-type
 *         that defaults to "int".  Also warn about any "return"
 *         statement with no return-value in a function whose
 *         return-type is not "void".
 *
 *         For C++, a function without return type always pro-
 *         duces a diagnostic message, even when -Wno-return-type
 *         is specified. The only exceptions are main and func-
 *         tions defined in system headers.
 *
 *     -Wunused-parameter
 *         Warn whenever a function parameter is unused aside
 *         from its declaration.
 *
 *         To suppress this warning use the unused attribute.
 *
 *     -Wunused-variable
 *         Warn whenever a local variable or non-constant static
 *         variable is unused aside from its declaration
 *
 *         To suppress this warning use the unused attribute.
 *
 *     -Wunused-value
 *         Warn whenever a statement computes a result that is
 *         explicitly not used.
 *
 *         To suppress this warning cast the expression to void.
 *
 ******************************************************************************/


#if defined(__GNUC__) || defined(__GNUG__)
#  define ZLS_PRETTY_FUNCTION(X)        __PRETTY_FUNCTION__
#else
#  define ZLS_PRETTY_FUNCTION(X)        X
#endif


#ifdef ENABLE_THREADS
#  ifndef HAVE_PTHREAD_H
#    error "Only supporting POSIX thread !"
#  endif

   /* _REENTRANT is required for some OS( Linux, Solaris, HPUX) */
#  ifndef _REENTRANT
#    define _REENTRANT
#  endif

   /*
    * 好象_THREAD_SAFE也在一些OS(FreeBSD)的系统头文件中被使用，不知道定义否有什么区别.
    */
#  ifndef _THREAD_SAFE
#    define _THREAD_SAFE
#  endif

   /*
    * _PTHREADS is required for SGI STL (and GNU libstdc++).
    * It imposes "Alloc.h" is thread-safety.
    *
    * 2001/9/9: 在FreeBSD-4.3上升级到GCC-3.0.1后发现"_PTHREADS"好象已经没有被libstdc++-3.0
    *           中的任何文件使用了，只有在"/usr/local/lib/gcc-lib/i386-portbld-freebsd4.3/
    *           3.0.1/include/g++/i386-portbld-freebsd4.3/bits/gthr.h"中有看到如下的注释：
    *
    *    Currently supported threads packages are
    *      POSIX threads with -D_PTHREADS
    *      DCE threads with -D_DCE_THREADS
    *      Solaris/UI threads with -D_SOLARIS_THREADS
    *
    * 但是只是注释而已！
    */
#  ifndef _PTHREADS
#    define _PTHREADS
#  endif
#endif


/* We always follow POSIX standard */
/* Shit,定义了_POSIX_SOURCE后导致/usr/include/sys/socket.h编译不过去.
#ifndef _POSIX_SOURCE
#  define _POSIX_SOURCE
#endif
*/
#include <limits.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <syslog.h>
#include <assert.h>
#include <pwd.h>
#include <fcntl.h>
#include <signal.h>
#include <syslog.h>
#include <string.h>

#if defined(__unixware__) || defined(__sys5__) || defined(__win32__) || defined(WIN32)
#  include <string.h>
#else
#  include <strings.h>
#endif

#if defined(__hpux__)
#  include <stdarg.h>
#  include <varargs.h>
#else
#  include <stdarg.h>
#endif

#ifdef ENABLE_THREADS
#  include <pthread.h>
#  ifndef PTHREAD_STACK_MIN   /* 这是一个标准宏 */
#    define PTHREAD_STACK_MIN   32768
#  endif
#  if PTHREAD_STACK_MIN < 32768  /* FreeBSD-4.2只为1024，太小了 */
#    undef PTHREAD_STACK_MIN
#    define PTHREAD_STACK_MIN   32768
#  endif
#  if defined(HAVE_PTHREAD_MUTEX_RECURSIVE) && defined(__FreeBSD__)
   /*
    * 注意：FreeBSD-4.2上的"递归"型mutex有Bug: 当被同一Thread lock三次及以上次数后，
    * 然后同一Thread unlock到第三次时将给出EINVAL错，如果继续unlock的话将给出EPERM
    * 错.
    */
#    undef HAVE_PTHREAD_MUTEX_RECURSIVE
#  endif
#  if defined(HAVE_PTHREAD_MUTEX_RECURSIVE) && defined(__linux__)
#    undef HAVE_PTHREAD_MUTEX_RECURSIVE
#  endif
#endif

#include <sys/select.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <net/ethernet.h>
#include <net/if_arp.h>


/** POSIX标准宏，每一行最多允许多少个字符. */
#ifndef LINE_MAX
#  error "Your OS is missing 'LINE_MAX' !"
#endif

/** POSIX标准宏，PATH最多允许多少个字符. */
#ifndef PATH_MAX
#  error "Your OS is missing 'PATH_MAX' !"
#endif

/** POSIX标准宏，FILE-NAME最多允许多少个字符. */
#ifndef NAME_MAX
#  error "Your OS is missing 'NAME_MAX' !"
#endif


/*
 * 好象对于宏的命名有一些不成文的假定：
 * (1) 如果是compiler在运行时自动添加的宏，则名称格式一般为__X或__X__，例如__GNUC__;
 *
 * (2) 在头文件中表示“类型”的宏，如果其是“内部private使用”，则名称格式一般为
 *     _X_T_或_x_t，例如_BSD_SIZE_T_或__int64_t，而如果是public的“类型”宏，则
 *     名称格式一般为int64_t;
 *
 * (3) 在头文件中的其它宏，则名称格式一般为X或_X或__X，其中_X和__X通常用于不希望名称
 *     与别的头文件中的宏“冲突”时、或系统内部private使用的宏时.
 */
#if defined(__linux__) && defined(__P)
#  undef __P  /* @todo Linux Mandarake的__P()宏好象不行，待证实 */
#endif
#ifndef __P
#  if defined(__STDC__) || defined(__cplusplus)
#    define __P(args) args
#  else
#    define __P(args) ()
#  endif
#endif


/*
 * Create DLL if ENABLE_ZFC_DLL is defined (Windows only)
 */
#if defined(__win32__) || defined(WIN32)
#ifdef ENABLE_ZFC_DLL
#define ZFC_DLL_EXPORT  __declspec(dllexport)
#endif
#endif
#ifndef ZFC_DLL_EXPORT
#define ZFC_DLL_EXPORT
#endif


#ifdef __cplusplus
extern "C" {
#endif


/* 可移植的数据类型 */
/*******************************************************************************
 *            -128 < signed char    < 127
 *               0 < unsinged char  < 255
 *          -32768 < signed short   < 32767
 *               0 < unsigned short < 65535
 *     -2147483648 < signed int     < 2147483647
 *               0 < unsigned int   < 4294967295
 * 32位主机:
 *     -2147483648 < signed long    < 2147483647
 *               0 < unsigned long  < 4294967295
 *
 *     -9223372036854775808 < signed long long < 9223372036854775807
 *                        0 < unsigned long long < 18446744073709551615
 * 64位主机:
 *     -9223372036854775808 < signed long   < 9223372036854775807
 *                        0 < unsigned long < 18446744073709551615
 *
 * Some known macro declared by Some famous vendors:
 *   "__SQL"       declared by Informix cli
 *   "_UDBCTYPE_H" declared by openlink UDBC
 *
 * @note Openlink UDBC的数据类型定义与我的定义相同,因此不必再自己定义;而Informix
 * cli 2.5定义的数据类型在64位UNIX上不是很准确，因此我们要自己定义，同时我们必须
 * 修改Informix cli 2.5的相应的头文件,避免编译器因类型重定义而出错.
 ******************************************************************************/

#if SIZEOF_LONG == 4
#  define __ILP32__ 1
#else
#  if SIZEOF_LONG == 8
#    define __LP64__ 1
#  else
#    error "Undeterminated Machine Address Size."
#  endif
#endif

                                     /* 这是Informix cli 2.7以上 */
#if ! defined(_UDBCTYPE_H) && ! defined(__INFXCLI_H)
  typedef unsigned char  UCHAR;   /**< unsigned 1 byte */
  typedef short          SWORD;   /**< signed 2 bytes */
  typedef unsigned short UWORD;   /**< unsigned 2 bytes */
  typedef unsigned long  MASIZE;  /**< Machine Address Size,根据ILP32或LP64决定 */
# if SIZEOF_INT == 4
    typedef int          SDWORD;  /**< signed 4 bytes */
    typedef unsigned int UDWORD;  /**< unsigned 4 bytes */
# else
#   if SIZEOF_LONG == 4
      typedef long          SDWORD;  /**< signed 4 bytes */
      typedef unsigned long UDWORD;  /**< unsigned 4 bytes */
#   else
#     error "Undeterminated 4 bytes type."
#   endif
# endif
#endif

#ifdef __GNUC__
  typedef int64_t   SQWORD;  /**< signed 8 bytes */
  typedef u_int64_t UQWORD;  /**< unsigned 8 bytes */
#else
# if SIZEOF_LONG == 8
    typedef long          SQWORD;  /**< signed 8 bytes */
    typedef unsigned long UQWORD;  /**< unsigned 8 bytes */
# else
#   if SIZEOF_LONG_LONG == 8
      typedef long long          SQWORD;  /**< signed 8 bytes */
      typedef unsigned long long UQWORD;  /**< unsigned 8 bytes */
#   else
#     error "Undeterminated 8 bytes type."
#   endif
# endif
#endif

/** 表示这个UDWORD型的字节序是网络字节序，这是专门为IPv4地址而定义的类型. */
typedef UDWORD  NUDWORD;
/** 表示这个UWORD型的字节序是网络字节序，这是专门为IPv4 protocol port而定义的类型. */
typedef UWORD   NUWORD;

#if !defined(__win32__) && !defined(WIN32)
  /* typedef SDWORD         SOCKET; */  /**< Type for network socket */
#endif

typedef unsigned short PPORT;  /**< Type for Internet Protocol Port */

#ifndef __cplusplus
   /** C语言没有bool类型，我们模拟它. */
   typedef int bool;       /**< boolean, signed 2 byte */
#  define true    (bool)1  /**< boolean true */
#  define false   (bool)0  /**< boolean false */
#endif
/* End of 可移植的数据类型 ****************************************************/


#if !defined(OK)
#  define OK           0
#endif
#if !defined(NOTOK)
#  define NOTOK        -1
#endif


#define DWORD_ALIGN_BYTES       (sizeof(UDWORD)-1)
#define QWORD_ALIGN_BYTES       (sizeof(UQWORD)-1)
/** 用来进行DWORD对齐的宏. */
#define DWORD_ALIGN(n)  (((UDWORD)(n) + DWORD_ALIGN_BYTES) & ~DWORD_ALIGN_BYTES)
/** 用来进行QWORD对齐的宏. */
#define QWORD_ALIGN(n)  (((UQWORD)(n) + QWORD_ALIGN_BYTES) & ~QWORD_ALIGN_BYTES)

/** 在32bits主机上采用DWORD Align. */
#define ZLS_ALIGN(n)        DWORD_ALIGN(n)
#define ZLS_ALIGN_BYTES         DWORD_ALIGN_BYTES


#if !defined(__win32__) && !defined(WIN32)
/* extern int    errno; */
/*
 * @attention 上面的这行是不恰当的，在某些OS上errno是个函数的宏!而且在WIN32下并没有
 * errno而是getLastError()，因此要使用errno正确的做法是只要#include <errno.h>即可.
 */
#endif

/**
 * 得到errno对应的Text信息.
 */
#if defined(__irix__)
#  define ERRNO_TEXT(eno) sys_errlist[eno]
#else
#  if defined(__solaris__) || defined(SOLARIS) || defined(__linux__) || defined(__FreeBSD__)
#    define ERRNO_TEXT(eno) strerror(eno)
#  else
#    define ERRNO_TEXT(eno) _sys_errlist[eno]
#  endif
#endif


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
extern "C++"
{
  #ifdef HAVE_CXX_NS  /* 如果你的compiler支持namespace. */
    #define ZLS_USE_NAMESPACE(_x_)        _x_::
    #define ZLS_USING_NAMESPACE(_x_)      using namespace _x_;
    #define ZLS_USING_NAME(_x_)           using _x_;
    #define ZLS_BEGIN_NAMESPACE(_x_)      namespace _x_ {
    #define ZLS_END_NAMESPACE             }
  #else
    #define ZLS_USE_NAMESPACE(_x_)
    #define ZLS_USING_NAMESPACE(_x_)
    #define ZLS_USING_NAME(_x_)
    #define ZLS_BEGIN_NAMESPACE(_x_)
    #define ZLS_END_NAMESPACE
  #endif

  #if (defined(__GNUC__) && __GNUC__ == 3)
    // GNU GCC 3.0开始采用libstdc++-v3
    #define HAVE_GNU_LIBSTDCXX_V3       1
  #else
    #define HAVE_GNU_LIBSTDCXX_V2       1
  #endif

  #ifdef HAVE_CXX_STL
    #ifdef HAVE_GNU_LIBSTDCXX_V2
      #include <stl.h>
      #include <typeinfo>
      #include <string>
      #include <hash_map>
    #else
      #include <typeinfo>
      #include <iostream>
      #include <string>
      #include <vector>
      #include <deque>
      #include <stack>
      #include <list>
      #include <map>
      #include <ext/hash_map>
    #endif
  #else
    #error "C++ STL is required by libzfc !"
  #endif

  #include <zls/zfc/Memory.hpp>
  #include <zls/zfc/Toolkit.hpp>
}
#endif

#include <zls/zfc/Memory.h>
#include <zls/zfc/Debug.h>
#include <zls/zfc/Toolkit.h>


#endif

