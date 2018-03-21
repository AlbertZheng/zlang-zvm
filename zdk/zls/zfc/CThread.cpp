/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CThread.cpp,v $
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


#include <zls/zfc/CThread.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


// 由于CThread::ThreadAdapter只能是static method，这样需要一个TSS以便以后我能找到我自己.
static CThreadSpecialStorage SGciPointerToSelf;


CThread * CThread::GetMyThread()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CThread::GetMyThread()");
  void * pv = SGciPointerToSelf.GetStorage();
  CThread * pciThread = reinterpret_cast<CThread *>(pv);
  if (pciThread == 0)
  {
    LogAbort(("Fatal: You are making mistakes !"));
  }
  return pciThread;
}


void * CThread::ThreadAdapter(void * pvArg)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CThread::ThreadAdapter");
  struct sched_param siScheduleParameter;
  int    nPolicy;

  LogAssert0(pvArg != 0, "Impossible mistake");

  // 由于CThread::ThreadAdapter只能是static method，这样需要一个TSS以便以后我能找到我自己.
  SGciPointerToSelf.SetStorage(pvArg);

  // ThreadAdapter()是static method，必须将参数转换为一个CThread *
  CThread * pciThread = reinterpret_cast<CThread *>(pvArg);

  pciThread->_bThreadRunning = true;
  if (pciThread->_stringThreadName.size() == 0)
  // 如果用户没有设置Thread名
  {
    pciThread->GenerateDefaultName();
  }
  pthread_getschedparam(pciThread->_siThreadId, &nPolicy, &siScheduleParameter);
  LogDebug1(("Debug: Thread '%s': Running at policy '%d' and priority '%d'\n",
             pciThread->GetThreadName().c_str(), nPolicy, siScheduleParameter.sched_priority));

  // Calling virtual method CThread::Run()
  pciThread->Run();
  // Calling virtual method CThread::Finalize()
  pciThread->Finalize();

  // A thread quit
  pciThread->_bThreadRunning = false;
  pthread_exit(0);
}


void CThread::Start()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CThread::Start()");
  int nResult;
  if ((nResult = pthread_create(&_siThreadId, &_siThreadAttribute, CThread::ThreadAdapter, this)) != 0)
  {
    throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_create", nResult);
  }
}


void CThread::Yield()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CThread::Yield()");
  if (ThreadRunning())
  {
    if (sched_yield() < 0)
    {
      throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "sched_yield", errno);
    }
  }
}


int CThread::Sleep(long nMilliseconds, int nNanoseconds)
{
  if (ThreadRunning())
  {
    if(nMilliseconds < 0)
    {
      nMilliseconds = 0;
    }
    if(nNanoseconds > 999999)
    {
      nNanoseconds = 999999;
    }

    struct timespec tv;
    tv.tv_sec = nMilliseconds/1000;
    tv.tv_nsec = (nMilliseconds % 1000)*1000000 + nNanoseconds;
    #if defined(HAVE_PTHREAD_DELAY_NP)
      if (pthread_delay_np(&tv) == EINTR)
      {
        return -1;
      }
      else
      {
        return 0;
      }
    #else
      #if defined(HAVE_NANOSLEEP)
        if(nanosleep(&tv, 0) < 0 && errno == EINTR)
        {
          return -1;
        }
        else
        {
          return 0;
        }
      #else
        #error "Your OS is missing some routines ..."
      #endif
    #endif
  }
  else
  {
    return 0;
  }
}


void CThread::SetThreadPriority(int nPriority)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CThread::SetThreadPriority()");

  if (nPriority)
  {
    int nResult;
    struct sched_param siThreadScheduleParameter;

    //如果不是对老的".sched_priority"进行改变，好象不需要调用pthread_attr_getschedparam()
    //pthread_attr_getschedparam(&_siThreadAttribute, &siThreadScheduleParameter);

    // 调度优先级
    siThreadScheduleParameter.sched_priority = nPriority;   // 有待实验 ?
    // 调度策略：轮转法.
    //pthread_attr_setschedpolicy(&_siThreadAttribute, SCHED_RR);
    if ((nResult = pthread_attr_setschedparam(&_siThreadAttribute, &siThreadScheduleParameter)) != 0)
    {
      throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_attr_setschedparam", nResult);
    }
  }
}


void CThread::SetThreadStackSize(size_t nStackSize)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CThread::SetThreadStackSize()");

  if (nStackSize)
  {
    int nResult;
    if((nResult = pthread_attr_setstacksize(&_siThreadAttribute, nStackSize <= PTHREAD_STACK_MIN ? PTHREAD_STACK_MIN : nStackSize)) != 0)
    {
      throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_attr_setstacksize", nResult);
    }
  }
}


void CThread::GenerateDefaultName()
{
  CThreadId ciId;  //default constructor
  _stringThreadName = ciId.ToString();
}


void CThread::SafetyJoinMe() const
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CThread::SafetyJoinMe()");
  if (! _bThreadDetached)
  {
    int nResult;
    if ((nResult = pthread_join(_siThreadId, 0)) != 0)
    {
      // nResult should be EINVAL(The implementation has detected that the value
      // speci-fied by thread does not refer to a joinable thread) or EDEADLK
      // or ESRCH(No thread could be found corresponding to that speci-fied by
      // the given thread ID.)
      throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_join", nResult);
    }
  }
}

CThread::CThread(const char * pszThreadName = "", bool bThreadDetached = false,
                 int nThreadPriority = 0, size_t nThreadStackSize = 0)
  :_bThreadRunning(false),
   _bThreadCanShutdown(false),
   _bThreadDetached(bThreadDetached)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CThread::CThread()");
  int nResult;
  if ((nResult = pthread_attr_init(&_siThreadAttribute)) != 0)
  {
    // nResult should be ENOMEM
    throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_attr_init", nResult);
  }

  /* 注意：如果用户要自己设置stack，则这个thread一定不能是detached的. */
  if (nThreadStackSize > 0 && _bThreadDetached)
  {
    std::string stringError = "'bThreadDetached' should not be 'true' if 'nThreadStackSize' > 0";
    throw zfc::EInvalidArgument(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
  }

  if (_bThreadDetached)
  {
    if ((nResult = pthread_attr_setdetachstate(&_siThreadAttribute, PTHREAD_CREATE_DETACHED)) != 0)
    {
      // nResult should be EINVAL
      throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_attr_setdetachstate", nResult);
    }
  }
  SetThreadPriority(nThreadPriority);
  SetThreadStackSize(nThreadStackSize);
  if (pszThreadName && *pszThreadName != '\0')
  {
    _stringThreadName = pszThreadName;
  }
  // Thread并不立即开始，只有当Start()被调用时才开始一个新的Thread.
}


// gcc-2.95.2好象有bug：如果inline CThread::~CThread()则link时会抱怨
//                      CThread::GetThreadId()找不到，甚至影响到memory.cpp
//                      中的ZLS_memory_management_startup()也找不到.
CThread::~CThread()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CThread::~CThread()");
  int nResult;
  if ((nResult = pthread_attr_destroy(&_siThreadAttribute)) != 0)
  {
    try {
      // nResult should be EINVAL
      throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pthread_attr_destroy", nResult);
    }
    catch(ESystemCallFailure & e)
    // 注意：Destructor是不允许throw exception的，因为当某个function抛出一个
    // exception后，compiler在调用链上unwind时要调用Destructor，此时如果可能
    // 再抛出exception则是不可意料的，通常compiler会调用terminate().
    {
    }
  }
}


ZLS_END_NAMESPACE

