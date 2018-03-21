/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/Memory.cpp,v $
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


#include <zls/zfc/Memory.hpp>


#ifdef __cplusplus
extern "C"
{
#endif

/** 指针变量：指向保留内存块. */
TMallocPointer _GpZLSReservedMemory = (TMallocPointer)0;

static bool SGbYetNotCalled = true;

#ifdef ENABLE_THREADS
/** 保留内存块Thread互斥. */
static pthread_mutex_t _SGtReservedMemoryMutex = PTHREAD_MUTEX_INITIALIZER;
#endif

#ifdef __cplusplus
}
#endif


#ifdef ENABLE_OVERLOAD_OPERATOR_NEW
  void * operator new(size_t size, const char *pszFile, const int nLine,
                      _TOperatorNewPlacement ePlacementWhenOOM = _TYPICAL)
  {
    static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("operator new(size_t, const char *, const int,...)");
    void * p = 0;
    if ((p = _ZLS_malloc_backend(size, pszFile, nLine, ePlacementWhenOOM)) == 0)
    {
      if (ePlacementWhenOOM == _THROW)
      {
        TLoggerTSS * __ptLoggerTSS__;
        #ifdef ENABLE_THREADS
        _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
        #else
        __ptLoggerTSS__ = &_GtLoggerTSS;
        #endif
        __ptLoggerTSS__->pszFileName = pszFile;
        __ptLoggerTSS__->pszFuncName = 0;
        __ptLoggerTSS__->nLine = nLine;
        __ptLoggerTSS__->nSyslogPriority = LOG_ERR;
        _LogMiddle("Fatal: Out of memory, reported by '%s' !\n", __PRETTY_FUNC__);
        throw zfc::EOutOfMemory(pszFile, 0, nLine);
      }
    }
    return(p);
  }

  void * operator new(size_t size)
  {
    static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("operator new(size_t)");
    void * p = 0;
    if ((p = _ZLS_malloc_backend(size, __FILE__, __LINE__, false)) == 0)
    {
      TLoggerTSS * __ptLoggerTSS__;
      #ifdef ENABLE_THREADS
      _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
      #else
      __ptLoggerTSS__ = &_GtLoggerTSS;
      #endif
      __ptLoggerTSS__->pszFileName = __FILE__;
      __ptLoggerTSS__->pszFuncName = 0;
      __ptLoggerTSS__->nLine = __LINE__;
      __ptLoggerTSS__->nSyslogPriority = LOG_ERR;
      _LogMiddle("Fatal: Out of memory, reported by '%s' !\n", __PRETTY_FUNC__);
      throw zfc::EOutOfMemory(__FILE__, __PRETTY_FUNC__, __LINE__);
    }
    return(p);
  }

  void operator delete(void *p)
  {
    ZLS_free(p);
  }

  #if defined(OPERATOR_NEW_ARRAY)
    void * operator new[](size_t size)
    {
      static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("operator new[](size_t)");
      void * p = 0;
      if ((p = _ZLS_malloc_backend(size, __FILE__, __LINE__, false)) == 0)
      {
        TLoggerTSS * __ptLoggerTSS__;
        #ifdef ENABLE_THREADS
        _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
        #else
        __ptLoggerTSS__ = &_GtLoggerTSS;
        #endif
        __ptLoggerTSS__->pszFileName = __FILE__;
        __ptLoggerTSS__->pszFuncName = 0;
        __ptLoggerTSS__->nLine = __LINE__;
        __ptLoggerTSS__->nSyslogPriority = LOG_ERR;
        _LogMiddle("Fatal: Out of memory, reported by '%s' !\n", __PRETTY_FUNC__);
        throw zfc::EOutOfMemory(__FILE__, __PRETTY_FUNC__, __LINE__);
      }
      return(p);
    }

    void operator delete[](void *p)
    {
      ZLS_free(p);
    }
  #endif  // OPERATOR_NEW_ARRAY
#endif  // ENABLE_OVERLOAD_OPERATOR_NEW



ZLS_BEGIN_NAMESPACE(zfc)

void _ZLS_STL_out_of_memory_handler()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("_ZLS_STL_out_of_memory_handler()");
  int nResult = NOTOK;

# ifdef ENABLE_THREADS
  pthread_mutex_lock(&_SGtReservedMemoryMutex);
# endif

  if (! LowMemory())
  /* 如果保留内存还没有被用掉 */
  {
    /* 则用掉保留内存 */
    ZLS_free(_GpZLSReservedMemory);
    _GpZLSReservedMemory = (TMallocPointer)0;
    nResult = OK;

    LogWarning(("Warning: Low memory, Reserved memory contributed !\n"));
  }

# ifdef ENABLE_THREADS
  pthread_mutex_unlock(&_SGtReservedMemoryMutex);
# endif

  /*
   * STL在out of memory时将调用我的ZLS_STL_out_of_memory_handler()，然后当
   * ZLS_STL_out_of_memory_handler()返回后，STL将再尝试申请内存，如果还失败，
   * 则继续调用我的ZLS_STL_out_of_memory_handler()，直至STL能申请内存成功为
   * 止，因此我们在释放了保留内存后如果STL还是不能成功申请内存，则我只能
   * abort()或throw bad_alloc，否则会陷入死循环！
   */

  /* 2001/5/5: 我的Logger在out of memory时应该是能够正常工作的 ! */
  LogError(("Fatal: Out of memory, reported by '%s' !\n", __PRETTY_FUNC__));

  if (nResult == OK)
  /*
   * 2001/5/5: 改为在释放掉保留内存后，还是立即throw EOutOfMemory，因为
   * 被释放的保留内存应该是被用来进行一些善后工作以及在类EOutOfMemory中
   * 也需要动态申请一些内存来保存what的，所以保留内存必须足够才行，要不然连
   * EOutOfMemory都不能被throw出了!
   */
  {
    throw EOutOfMemory(__FILE__, __PRETTY_FUNC__, __LINE__);
  }
  else
  /*
   * 现在应该是在释放掉保留内存、throw EOutOfMemory后还出现out of memory，
   * 则可能是程序在进行一些善后工作或throw EOutOfMemory时内存还不够，则
   * 现在只能throw出不再需要动态申请内存的std::bad_alloc.
   */
  {
    throw std::bad_alloc();
  }
}

ZLS_END_NAMESPACE



#ifdef __cplusplus
extern "C"
{
#endif

static void Allocate_ZLS_reserved_memory()
{
# ifdef ENABLE_THREADS
  pthread_mutex_lock(&_SGtReservedMemoryMutex);
# endif

  if (SGbYetNotCalled)
  {
    /* 先申请一块保留内存 */
    _GpZLSReservedMemory = ZLS_malloc(ZLS_DEFAULT_RESERVED_MEMORY_SIZE);
    memset(_GpZLSReservedMemory, '\0', ZLS_DEFAULT_RESERVED_MEMORY_SIZE);
    SGbYetNotCalled = false;
  }

# ifdef ENABLE_THREADS
  pthread_mutex_unlock(&_SGtReservedMemoryMutex);
# endif
}

static void Deallocate_ZLS_reserved_memory()
{
# ifdef ENABLE_THREADS
  pthread_mutex_lock(&_SGtReservedMemoryMutex);
# endif

  /*释放保留内存 */
  ZLS_free(_GpZLSReservedMemory);
  _GpZLSReservedMemory = (TMallocPointer)0;

# ifdef ENABLE_THREADS
  pthread_mutex_unlock(&_SGtReservedMemoryMutex);
# endif
}

void ZLS_memory_management_startup()
{
  Allocate_ZLS_reserved_memory();
}

void ZLS_memory_management_cleanup()
{
  Deallocate_ZLS_reserved_memory();
  pthread_mutex_destroy(&_SGtReservedMemoryMutex);
  /*
   * 注意：在这之后程序就应该立即退出，否则如果有意想不到的ZLS_malloc()或new
   *       发生，则将导致未知的情况发生（应该会core dump）。
   */
}

static void _ZLS_malloc_out_of_memory_handler(const char *pszFile, int nLine)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("_ZLS_malloc_out_of_memory_handler()");
  TLoggerTSS * __ptLoggerTSS__;

# ifdef ENABLE_THREADS
  pthread_mutex_lock(&_SGtReservedMemoryMutex);
# endif

  if (! LowMemory())
  /* 如果保留内存还没有被用掉 */
  {
    /* 则用掉保留内存 */
    ZLS_free(_GpZLSReservedMemory);
    _GpZLSReservedMemory = (TMallocPointer)0;

#   ifdef ENABLE_THREADS
    _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
#   else
    __ptLoggerTSS__ = &_GtLoggerTSS;
#   endif
    __ptLoggerTSS__->pszFileName = pszFile;
    __ptLoggerTSS__->pszFuncName = 0;
    __ptLoggerTSS__->nLine = nLine;
    __ptLoggerTSS__->nSyslogPriority = LOG_WARNING;
    _LogMiddle("Warning: Low memory, Reserved memory contributed !\n");
  }

# ifdef ENABLE_THREADS
  pthread_mutex_unlock(&_SGtReservedMemoryMutex);
# endif
}

#if !defined(__GNUC__)
void ZLS_free(TMallocPointer p)
{
  if (p)
  {
    free(p);
  }
}
#endif

TMallocPointer _ZLS_malloc_backend(size_t nBytes,
                                   const char *pszFile,
                                   int nLine,
                                   bool bAbortWhenOOM)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("_ZLS_malloc_backend()");
  TMallocPointer _pTmp;
  TLoggerTSS * __ptLoggerTSS__;

# ifdef ENABLE_DEBUG_ZLS_malloc
# ifdef ENABLE_THREADS
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
# else
  __ptLoggerTSS__ = &_GtLoggerTSS;
# endif
  __ptLoggerTSS__->pszFileName = pszFile;
  __ptLoggerTSS__->pszFuncName = 0;
  __ptLoggerTSS__->nLine = nLine;
  __ptLoggerTSS__->nDebugLevel = 3;
  _LogDebug("Debug: Need malloc %d bytes.\n", nBytes);
# endif

  /* libstdc++的"new_op.cc"告诉我“malloc (0) is unpredictable; avoid it”.  */
  if (nBytes == 0)
    nBytes = 1;

  _pTmp = malloc(nBytes);

  if (_pTmp == (TMallocPointer)0)
  /* 如果malloc()失败 */
  {
    /* 释放保留内存 */
    _ZLS_malloc_out_of_memory_handler(pszFile, nLine);

    /*
     * 2001/5/5: 改为不再尝试malloc()，而是返回0指针或按照用户要求abort()，这是：
     * (1) 避免用户有一种假象：内存还足够.
     * (2) 保留内存应该是给进行善后工作和throw zfc::EOutOfMemory的.
     */
    /* 再调用一次malloc(),这次应该成功 */
    /* _pTmp = malloc(nBytes); */

    /* if (_pTmp == (TMallocPointer)0) */
    /* 如果这次还失败，则用户如果要求abort则只能abort() */
    /* { */
      if (bAbortWhenOOM == true)
      {
#       ifdef ENABLE_THREADS
        _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
#       else
        __ptLoggerTSS__ = &_GtLoggerTSS;
#       endif
        __ptLoggerTSS__->pszFileName = pszFile;
        __ptLoggerTSS__->pszFuncName = 0;
        __ptLoggerTSS__->nLine = nLine;
        _LogAbort("Abort: Out of memory, reported by '%s' !\n", __PRETTY_FUNC__);
      }
      else
      {
        return((TMallocPointer)0);
      }
    /* } */
  }

  /* memset(_pTmp, '\0', nBytes); */
  return(_pTmp);
}

TMallocPointer _ZLS_realloc_backend(TMallocPointer p,
                                    size_t nBytes,
                                    const char *pszFile,
                                    int nLine,
                                    bool bAbortWhenOOM)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("_ZLS_realloc_backend()");
  TMallocPointer _pTmp;
  TLoggerTSS * __ptLoggerTSS__;

# ifdef ENABLE_DEBUG_ZLS_malloc
# ifdef ENABLE_THREADS
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
# else
  __ptLoggerTSS__ = &_GtLoggerTSS;
# endif
  __ptLoggerTSS__->pszFileName = pszFile;
  __ptLoggerTSS__->pszFuncName = 0;
  __ptLoggerTSS__->nLine = nLine;
  __ptLoggerTSS__->nDebugLevel = 3;
  _LogDebug("Debug: Need realloc %d bytes.\n", nBytes);
# endif

  _pTmp = realloc(p, nBytes);

  if (_pTmp == (TMallocPointer)0)
  /* 如果realloc()失败 */
  {
    /* 释放保留内存 */
    _ZLS_malloc_out_of_memory_handler(pszFile, nLine);

    /*
     * 2001/5/5: 改为不再尝试realloc()，而是返回0指针或按照用户要求abort()，这是：
     * (1) 避免用户有一种假象：内存还足够.
     * (2) 保留内存应该是给进行善后工作和throw zfc::EOutOfMemory的.
     */
    /* 再调用一次realloc(),这次应该成功 */
    /* _pTmp = realloc(p, nBytes); */

    /* if (_pTmp == (TMallocPointer)0) */
    /* 如果这次还失败，则用户如果要求abort则只能abort() */
    /* { */
      if (bAbortWhenOOM == true)
      {
#       ifdef ENABLE_THREADS
        _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__);
#       else
        __ptLoggerTSS__ = &_GtLoggerTSS;
#       endif
        __ptLoggerTSS__->pszFileName = pszFile;
        __ptLoggerTSS__->pszFuncName = 0;
        __ptLoggerTSS__->nLine = nLine;
        _LogAbort("Abort: Out of memory, reported by '%s' !\n", __PRETTY_FUNC__);
      }
      else
      {
        return((TMallocPointer)0);
      }
    /* } */
  }

  return(_pTmp);
}

#ifdef __cplusplus
}
#endif

