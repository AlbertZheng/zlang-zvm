/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CThread.hpp,v $
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


#ifndef _ZLS_zfc_CThread_hpp_
#define _ZLS_zfc_CThread_hpp_

#include <zls/zfc/Manifest.h>
#include <zls/zfc/Exception.hpp>
#include <zls/zfc/CThreadSpecialStorage.hpp>
#include <zls/zfc/CThreadId.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


/**
 * 一个封装了PThread基本功能的类.
 *
 * @attention 当main（主Thread）要退出时，如何通知其它Threads让它们先退出呢？
 * (1) 采用pthread_kill()向其它Threads发送特定的signal好象可行（只要各个Threads
 *     调用pthread_sigmask()打开这个signal），但是有个问题：即各个Threads被中断
 *     后，进入了信号Handler（将调用pthread_exit()退出），但是如何释放自己的资源
 *     （内存等）呢？
 * (2) 采用判断自己实例中的一个特定的bool变量是比较合适的办法：即各个Threads在
 *     重载的Run()中加入判断自己实例中的一个特定的bool变量的代码以决定是否立即退
 *     出，该bool变量的改变将由主Thread来操作。
 */
class CThread {
  private:
    pthread_attr_t _siThreadAttribute;
    pthread_t      _siThreadId;
    std::string    _stringThreadName;
    bool           _bThreadCanShutdown;
    bool           _bThreadRunning;
    bool           _bThreadDetached;

    void GenerateDefaultName();
    /**
     * 设置Thread的stack size.
     *
     * @throw ESystemCallFailure.
     */
    void SetThreadStackSize(size_t nStackSize);

    static void * ThreadAdapter(void * pvArg);

  protected:
    /**
     * 新Thread的入口点，用户应重实现它，当CThread::Run()退出时新Thread将结束，
     * 然后CThread::Finalize()将被调用以进行用户的一些"垃圾"处理.
     *
     * @note CThread中并不设置exception handler，因此如果在CThread::Run()中有
     * exception发生，且CThread::Run()中也没有exception handler时，则将按照C++
     * 的缺省处理而abort(core dump).
     *
     * @todo Q: 是这样的吗? Thread可是另有自己的stack的呀，待测试?
     */
    virtual void Run() = 0;

    /**
     * 当Thread从CThread::Run()中正常退出后，CThread::Finalize()将被调用以进行
     * 用户的一些"垃圾"处理工作，用户可选择重实现它.
     */
    virtual void Finalize();

  public:
    /**
     * 某个Thread正在执行的代码可以通过这个static method得到自己所属的CThread instance.
     *
     * @attention 这个static method比较危险，如果是在"开始"Thread中调用了它则
     * 返回的肯定是0，因此我特地在CThread::GetMyThread()中加入了if(0)则强制abort
     * 的代码以警戒用户!
     */
    static CThread * GetMyThread();

    const std::string & GetThreadName() const
    {
      return _stringThreadName;
    }

    /**
     * 得到Thread ID.
     *
     * @attention 如果某个thread是detached的，则在这个thread退出后其它threads
     * （通常是main thread想pthread_join()或sprintf("pthread_t")等操作）继续使
     * 用它的pthread_t资源的话是一种危险的行为，因为其pthread_t资源将被pthread
     * 库自动回收了，所以保险的方法是其它threads必须知道其是not-detached的.
     */
    pthread_t GetThreadId() const
    {
      return _siThreadId;
    }

    /**
     * 得到Thread ID，这是一个conversion operator.
     *
     * @attention 如果某个thread是detached的，则在这个thread退出后其它threads
     * （通常是main thread想pthread_join()或sprintf("pthread_t")等操作）继续使
     * 用它的pthread_t资源的话是一种危险的行为，因为其pthread_t资源将被pthread
     * 库自动回收了，所以保险的方法是其它threads必须知道其是not-detached的.
     */
    operator pthread_t() const
    {
      return _siThreadId;
    }

    bool ThreadRunning() const
    {
      return _bThreadRunning;
    }

    bool ThreadDetached() const
    {
      return _bThreadDetached;
    }

    void NotifyMeShutdown()
    {
      _bThreadCanShutdown = true;
    }

    bool ThreadCanShutdown() const
    {
      return _bThreadCanShutdown;
    }

    /**
     * 开始运行Thread.
     *
     * @throw ESystemCallFailure.
     */
    void Start();
    /**
     * Thread让出CPU.
     *
     * @throw ESystemCallFailure.
     */
    void Yield();

    /**
     * 使Thread进入睡眠直至milliseconds（毫秒）+ nanoseconds（纳秒，十亿分之一秒）过完.
     *
     * @param nMilliseconds 毫秒，如果<0则被自动调整为0.
     * @param nNanoseconds 纳秒，如果>999999则被自动调整为999999.
     * @return 0 - 已经过了预定的时间，睡眠没有被"未堵塞"的信号所中断.
     *         -1 - "未堵塞"的信号到达，睡眠被中断.
     */
    int Sleep(long nMilliseconds, int nNanoseconds);

    /**
     * 设置Thread的优先级.
     *
     * @throw ESystemCallFailure.
     */
    void SetThreadPriority(int nPriority);

    /**
     * 安全地等待Thread结束.
     *
     * @throw ESystemCallFailure.
     */
    void SafetyJoinMe() const;

    bool operator == (const CThread & rhs) const
    {
      return pthread_equal(_siThreadId, rhs._siThreadId);
    }

    bool operator != (const CThread & rhs) const
    {
      return !(pthread_equal(_siThreadId, rhs._siThreadId));
    }

    /**
     * Constructor.
     *
     * @throw ESystemCallFailure、EInvalidArgument（当bThreadDetached
     * 为true时，如果同时nThreadStackSize又大于0，则throw这个exception。这是因为当Thread
     * 为Detached时是不允许改变stack大小的。）.
     */
    CThread(const char * pszThreadName = "", bool bThreadDetached = false,
            int nThreadPriority = 0, size_t nThreadStackSize = 0);

    /**
     * Destructor.
     */
    virtual ~CThread();
};


inline void CThread::Run()
{ }


inline void CThread::Finalize()
{ }


ZLS_END_NAMESPACE


#endif

