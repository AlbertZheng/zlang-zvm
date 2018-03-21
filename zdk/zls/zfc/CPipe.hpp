/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CPipe.hpp,v $
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


#ifndef _ZLS_zfc_CPipe_hpp_
#define _ZLS_zfc_CPipe_hpp_

#include <zls/zfc/Manifest.h>
#include <zls/zfc/Exception.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


/**
 * The CPipe uses system kernel buffering to hold data being passed either
 * between two execution contexts within the same process, or between
 * different processes.  Unlike thread's "Buffer", Pipe uses system
 * descriptors and kernel memory.  Under Posix, the size of the pipe and
 * associated kernel memory is always a fixed constant as defined by
 * _PC_PIPE_BUF.  The ZFC "CPipe" class primarily deals with "atomic"
 * transfers of fixed sized objects through pipes.
 *
 * @short kernel buffering between processes and/or threads.
 */
class CPipe
{
  private:
    int _fd[2];

    /**
     * 拷贝一个已存在的CPipe.
     *
     * @throw zfc::ESystemCallFailure 当调用dup()失败时.
     */
    void Copy(const CPipe & rci);

    /**
     * 关闭CPipe.
     */
    void Close();

    void Dup2FileDescriptor(int fdFromWhich, int fdToWhich);

  public:
    /**
     * Sender is often used for implementing a fork()'d message port
     * between processes.  By stopping the sender, the current pipe
     * can then only be used for receiving, and the sender is presumed
     * to be in the other half of a fork()'d process.
     *
     * @see CloseRead()
     */
    void CloseWrite();

    /**
     * Receiver is often used for implementing a fork()'d message port
     * between processes.  By stopping the receiver, the current pipe
     * can then only be used for sending, and the receiver is presumed
     * to be in the other half of a fork()'d process.
     *
     * @see CloseWrite()
     */
    void CloseRead();

    /**
     * 先将Read file descriptor复制到一个指定的新file descriptor上，然后再关闭
     * 这个Read file descriptor.
     *
     * @throw zfc::ESystemCallFailure 当调用dup2()失败时.
     */
    void Dup2AndThenCloseReadFileDescriptor(int fdToWhich);

    /**
     * 先将Write file descriptor复制到一个指定的新file descriptor上，然后再关闭
     * 这个Write file descriptor.
     *
     * @throw zfc::ESystemCallFailure 当调用dup2()失败时.
     */
    void Dup2AndThenCloseWriteFileDescriptor(int fdToWhich);

    /**
     * Perform an read transfer of data from a pipe.
     *
     * @param pvBuffer 读缓冲区，注意"读缓冲区"必须又足够的大小（>=nCount），
     * 否则结果你自己知道的.
     * @param nCount 指示要读出多少个字节的数据.
     * @return number of bytes actually read if successful.
     *
     * @attention 'ssize_t'在<sys/types.h>中被定义为"#define _BSD_SSIZE_T_ ssize_t"，
     * 而"_BSD_SSIZE_T_"在<machine/ansi.h>中被定义为"#define _BSD_SSIZE_T_ int"，它
     * 表示"byte count or error".
     *
     * @throw zfc::EInvalidState 当你以前已经调用过了CloseRead()，却还
     * 想read时.
     */
    ssize_t Read(void * pvBuffer, size_t nCount);

    /**
     * Perform an object atomic transfer of data to a pipe.
     *
     * @param pvBuffer 写缓冲区.
     * @param nCount 指示要写出多少个字节的数据.
     * @return number of bytes written if successful.
     *
     * @throw zfc::EInvalidState 当你以前已经调用过了CloseWrite()，却还
     * 想write时.
     */
    ssize_t Write(const void * pvBuffer, size_t nCount);

    /**
     * 拷贝一个已存在的CPipe.
     *
     * @throw zfc::ESystemCallFailure 当调用dup()失败时.
     */
    CPipe & operator=(const CPipe & rci);

    /**
     * Create a kernel pipe descriptor set using pipe().
     *
     * @throw zfc::ESystemCallFailure 当调用pipe()失败时.
     */
    CPipe();

    /**
     * Create a pipe as a duplicate of an existing pipe.
     *
     * @param a CPipe to duplicate.
     * @throw zfc::ESystemCallFailure 当调用dup()失败时.
     */
    CPipe(const CPipe & rci)
    { Copy(rci); }

    /**
     * Destroy the pipe and kernel descriptor resources.
     */
    virtual ~CPipe()
    { Close(); }
};


ZLS_END_NAMESPACE


#endif

