/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/Memory.h,v $
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


#ifndef _ZLS_zfc_Memory_h_
#define _ZLS_zfc_Memory_h_

#include <zls/zfc/Manifest.h>
#include <zls/zfc/Debug.h>


#ifdef __cplusplus
extern "C" {
#endif

#if defined(__STDC__) || defined(__cplusplus)
  typedef void * TMallocPointer;
#else
  typedef char * TMallocPointer;
#endif


/**
 * 保留内存块的大小.
 *
 * @note private internal interface.
 */
#define ZLS_DEFAULT_RESERVED_MEMORY_SIZE        8*1024

/**
 * 指向保留内存块的指针.
 *
 * @note private internal interface.
 */
extern TMallocPointer  _GpZLSReservedMemory;

/**
 * 判断内存是否已经用到极限了，即保留内存是否已经被释放了.
 */
#define LowMemory()  (_GpZLSReservedMemory == (TMallocPointer)0)

/**
 * 申请保留内存块，并为ZLS_malloc()等做一些准备工作.
 *
 * @note 在程序的开始处调用它.
 */
void ZLS_memory_management_startup __P(());

/**
 * 释放保留内存块，并释放ZLS_malloc()内部的pthread_mutex_t.
 *
 * @note 在程序的结束处调用它.
 *
 * @attention 在这之后程序就应该立即退出，否则如果之后程序中还有意想不到的
 * ZLS_malloc()或new调用发生，则将导致未知的情况发生（应该会core dump）.
 */
void ZLS_memory_management_cleanup __P(());

/**
 * malloc()的替代品.
 */
#define ZLS_malloc(nBytes) _ZLS_malloc_backend(nBytes, __FILE__, __LINE__, false)

/**
 * realloc()的替代品.
 */
#define ZLS_realloc(p, nBytes) _ZLS_realloc_backend(p, nBytes, __FILE__, __LINE__, false)

/**
 * free()的替代品.
 */
#if defined(__GNUC__)
inline void ZLS_free(TMallocPointer p)
{
  if (p)
  {
    free(p);
  }
}
#else
void ZLS_free __P((TMallocPointer p));
#endif


/**
 * @name Private internal interface.
 */
//@{
/**
 * ZLS_malloc()的后端.
 *
 * @note private internal interface.
 */
TMallocPointer _ZLS_malloc_backend __P((size_t nBytes,
                                        const char *pszFile, int nLine,
                                        bool bAbortWhenOOM));

/**
 * ZLS_realloc()的后端.
 *
 * @note private internal interface.
 */
TMallocPointer _ZLS_realloc_backend __P((TMallocPointer p, size_t nBytes,
                                         const char *pszFile, int nLine,
                                         bool bAbortWhenOOM));
//@}

#ifdef __cplusplus
}
#endif


#endif

