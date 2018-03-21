/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CThreadSpecialStorage.hpp,v $
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


#ifndef _ZLS_zfc_CThreadSpecialStorage_hpp_
#define _ZLS_zfc_CThreadSpecialStorage_hpp_

#include <zls/zfc/Manifest.h>
#include <zls/zfc/SmartPointer.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


/**
 * This class allows the creation of a thread context unique "pointer"
 * that can be set and retrieved and can be used to create thread specific
 * data areas for implementing "thread safe" library routines.
 */
class CThreadSpecialStorage {
  private:
    /**
     * 隐藏掉copy constructor，因为我不允许这种操作.
     */
    CThreadSpecialStorage(const CThreadSpecialStorage &);
    /**
     * 隐藏掉assignment operator，因为我不允许这种操作.
     */
    CThreadSpecialStorage & operator=(const CThreadSpecialStorage &);

    pthread_key_t _siKey;  ///< thread special storage key
    void (*_pfuncDestructor)(void *);  ///< thread special storage destructor function

  public:
    /**
     * Create a unique thread specific container.
     *
     * @throw ESystemCallFailure.
     */
    CThreadSpecialStorage(void (*pfuncDestructor)(void *) = 0);

    /**
     * Destroy a thread specific container and any contents reserved.
     */
    ~CThreadSpecialStorage();

    /**
     * Get the value of the pointer for the thread specific data
     * container.  A unique pointer can be set for each execution
     * context.
     *
     * @return a unique void * for each execution context.
     */
    void * GetStorage(void);

    /**
     * Set the value of the pointer for the current thread specific
     * execution context.  This can be used to store thread context
     * specific data.
     *
     * @param ptr to thread context specific data.
     * @throw ESystemCallFailure.
     * @attention 如果多次调用SetStorage()，则会先free以前已经Set给的指针，然后
     * 再Set为新指针.
     */
    void SetStorage(void *);
};


ZLS_END_NAMESPACE


#endif

