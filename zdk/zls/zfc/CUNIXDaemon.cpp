/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CUNIXDaemon.cpp,v $
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


#include <zls/zfc/CUNIXDaemon.hpp>
#include <zls/zfc/Exception.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


/******************************************************************************
 * static members.
 ******************************************************************************/
CUNIXDaemon * CUNIXDaemon::_SpciSingleton = 0;


/******************************************************************************
 * static methods.
 ******************************************************************************/
void CUNIXDaemon::SignalHandler(int nSignal)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CUNIXDaemon::SignalHandler()");
  int nSavedErrno = errno;

  // 注：这个method中的BLOCK和UNBLOCK老信号好象是没有必要的，因为我们总是采用
  // sigaction()来设置信号处理函数，而sigaction()是可靠的，它保证在kernel进入
  // 某个信号处理函数的同时也自动屏蔽正在被触发的这个信号，至于由于我们也想在
  // 进入某个信号处理函数的同时也屏蔽掉“我们安装的其它信号”，但是这已经在下
  // 面的“安装信号”method中进行了设置，即“安装信号”method也同时将“先前已
  // 经被安装的信号”加入到struct sigaction中的sa_mask字段中（注意：下面的代码
  // 也做了一个多余的事情，即将这个正在被安装的信号也加入到sa_mask字段中，这是不
  // 必要的，因为sigaction()是可靠的，它保证在kernel进入某个信号处理函数的同时
  // 也自动屏蔽正在被触发的这个信号），这表示告诉sigaction()如果以后kernel在触
  // 发这个被新安装的信号的时候（即进入它的信号处理函数）的同时，也屏蔽掉那些
  // “已经被安装的信号”！

  sigset_t siOldMask;
  // 得到Old mask，SIG_BLOCK并不起作用：因为第二个参数是0，而第三个参数是非0，
  // 则说明我们只是想得到老的信号集.
  sigprocmask(SIG_BLOCK, 0, &siOldMask);
  // Blocking Old Mask
  sigprocmask(SIG_BLOCK, &siOldMask, 0);

  CUNIXDaemon * pciSingleton = CUNIXDaemon::Instance();
  switch (nSignal)
  {
    case SIGUSR1:
      pciSingleton->OnUSR1Signal();
      break;

    case SIGUSR2:
      pciSingleton->OnUSR2Signal();
      break;

    case SIGHUP:
      pciSingleton->OnHUPSignal();
      break;

    case SIGTERM:
      pciSingleton->OnTERMSignal();
      break;

    case SIGCHLD:
      pciSingleton->OnCHLDSignal();
      break;

    default:
      /* Dispatching other installed signals */
      pciSingleton->OnSignal(nSignal);
      break;
  }

  // Unblocking Old Mask
  sigprocmask(SIG_UNBLOCK, &siOldMask, 0);

  errno = nSavedErrno;
}


/******************************************************************************
 * standard methods.
 ******************************************************************************/
void CUNIXDaemon::OnUSR1Signal()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CUNIXDaemon::OnUSR1Signal()");

  LogInfo(("Info: Received USR1 signal, Debug level increased !\n"));
  IncreaseLoggerDebugLevel();
}


void CUNIXDaemon::OnUSR2Signal()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CUNIXDaemon::OnUSR2Signal()");

  LogInfo(("Info: Received USR2 signal, Debug level decreased !\n"));
  DecreaseLoggerDebugLevel();
}


void CUNIXDaemon::OnHUPSignal()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CUNIXDaemon::OnHUPSignal()");

  LogInfo(("Info: Received HUP signal !\n"));
}


void CUNIXDaemon::OnTERMSignal()
{
  static const char * __PRETTY_FUNC__= ZLS_PRETTY_FUNCTION("CUNIXDaemon::OnTERMSignal()");

  LogInfo(("Info: Received TERM signal, process will exit !\n"));

  /* Using the same signal to kill all child processes */
  // 下面这行有点问题，好象导致不断地发送TERM也给父process（自己）哦.
  //kill(0, SIGTERM);

  _bDaemonCanShutdown = true;

  //exit(0);
}


void CUNIXDaemon::OnCHLDSignal()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CUNIXDaemon::OnCHLDSignal()");
  int           nStatus;
  pid_t         nPID;

  while ((nPID = (pid_t)waitpid((pid_t)-1, &nStatus, WNOHANG)) > 0)
  {
    if (WIFEXITED(nStatus))
    {
      LogInfo(("Info: Child-Process(%d) normally termination at exit code = %d\n",
               nPID, WEXITSTATUS(nStatus)));
    }
    else
    {
      if (WIFSIGNALED(nStatus))
      {
        #ifdef WCOREDUMP
        LogInfo(("Info: Child-Process(%d) abnormal termination at signal = %d%s\n",
                 nPID, WTERMSIG(nStatus),
                 WCOREDUMP(nStatus)? " (core file generated)" : ""));
        #else
        LogInfo(("Info: Child-Process(%d) abnormal termination at signal = %d%s\n",
                 nPID, WTERMSIG(nStatus), ""));
        #endif
      }
      else
      {
        if (WIFSTOPPED(nStatus))
        {
          LogInfo(("Info: Child-Process(%d) stopped at signal = %d\n",
                   nPID, WSTOPSIG(nStatus)));
        }
      }
    }
  }
}


void CUNIXDaemon::OnSignal(int nSignal)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CUNIXDaemon::OnSignal()");

  LogInfo(("Info: Received %d signal !\n", nSignal));
}


void CUNIXDaemon::InstallSignal(int nSignal)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CUNIXDaemon::InstallSignal");
  struct sigaction tSignalAction;

  // 将这个被安装的信号保存到我内部的mask中.
  if (sigaddset(&_siInstalledSignalsMask, nSignal) < 0)
  {
    LogError(("Error: Couldn't add mask for signal '%d' due to '%m' !\n", nSignal));
    return;
  }
  // 拷贝这个内部的mask给struct sigaction中的sa_mask字段，以让sigaction告诉kernel
  // ：如果进入这个信号的处理函数时，同时也要自动屏蔽掉sa_mask指定的那些信号.
  memcpy((char *)&tSignalAction.sa_mask, (char *)&_siInstalledSignalsMask, sizeof(sigset_t));
  tSignalAction.sa_handler = CUNIXDaemon::SignalHandler;
  tSignalAction.sa_flags = 0;

  // 注：我们对除SIGALARM外的所有信号都试图设置SA_RESTART（中断的系统调用能够自动再起动），
  // 而不希望再起动由SIGALARM信号中断的原因是：我们希望对I/O操作可以设置时间限制.
  if (nSignal == SIGALRM)
  {
    // 如果你的OS的默认方式是自动再起动被中断的系统调用，则我们希望对SIGALARM能例外.
    #ifdef SA_INTERRUPT
    tSignalAction.sa_flags |= SA_INTERRUPT;  /* SunOS */
    #endif
  }
  else
  {
    // 如果你的OS支持自动再起动被中断的系统调用，则我们希望除SIGALARM外都能自动再起动被中断的系统调用.
    #ifdef SA_RESTART
    tSignalAction.sa_flags |= SA_RESTART;  /* SVR4, 4.3+BSD */
    #endif
  }
  if (sigaction(nSignal, &tSignalAction, NULL) < 0)
  {
    LogError(("Error: Couldn't install signal '%d' due to '%m' !\n", nSignal));
  }
}


void CUNIXDaemon::BlockingInstalledSignals()
{
  sigprocmask(SIG_BLOCK, &_siInstalledSignalsMask, NULL);
}


void CUNIXDaemon::UnblockingInstalledSignals()
{
  sigprocmask(SIG_UNBLOCK, &_siInstalledSignalsMask, NULL);
}


CUNIXDaemon::CUNIXDaemon(const char *pszProductName, const char *pszDaemonName,
                         int nMajorVersion, int nMinorVersion, int nDebugLevel)
  : _stringProductName(pszProductName),
    _stringDaemonName(pszDaemonName),
    _nMajorVersion(nMajorVersion),
    _nMinorVersion(nMinorVersion),
    _bDaemonCanShutdown(false)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CUNIXDaemon::CUNIXDaemon()");
  char aszMyHostName[LINE_MAX];

  /*
   * 我的libzfc必须做的一些初始化工作。
   */
  if (pszDaemonName)
  {
    OpenLogger(pszDaemonName);
  }
  else
  {
    OpenLogger("?");
  }
  ZLS_memory_management_startup();
  Install_STL_out_of_memory_handler();
  SetLoggerDebugLevel(nDebugLevel);

  // 设置singleton指针
  CUNIXDaemon::_SpciSingleton = this;

  GenerateVersionInfo();
  GenerateCopyrightInfo();

  /* Determine the name of this machine */
  #ifdef __svr4__
  if (sysinfo(SI_HOSTNAME, aszMyHostName, sizeof(aszMyHostName)) < 0)
  {
    throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "sysinfo", errno);
    //LogExit(("Error: Determining the host name failed when calling 'sysinfo()' due to '%m' !\n"));
  }
  #else /* Assume __bsd__ */
  if (gethostname(aszMyHostName, sizeof(aszMyHostName)) < 0)
  {
    throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "gethostname", errno);
    //LogExit(("Error: Determining the host name failed when calling 'gethostname()' due to '%m' !\n"));
  }
  #endif /* __svr4__ */
  _stringMyHostName = aszMyHostName;

  /* Determine the IPv4 address(es) of this machine */
  _ciMyIPv4Address = aszMyHostName;

  sigemptyset(&_siInstalledSignalsMask);
  /*
   * 安装缺省的signal处理。
   */
  InstallSignal(SIGCHLD);
  InstallSignal(SIGHUP);
  InstallSignal(SIGTERM);
  InstallSignal(SIGUSR1);
  InstallSignal(SIGUSR2);

  /*
   * Note: Most newer C++ implementations do not allow one to call virtual
   *       constructors or virtual methods from constructors.
   */
}


void CUNIXDaemon::Start()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CUNIXDaemon::Start()");
  char    aszPath[PATH_MAX];
  pid_t   pidMyself;
  int     hConsole;
  int     nMaxFileHandles;
  FILE  * filePID;

  /* 打印Copyright到tty和syslog */
  const std::string & rstringCopyright = GetCopyrightInfo();
  std::cerr << rstringCopyright << std::endl;
  LogInfo(("%s\n", rstringCopyright.c_str()));

  /* dtablesize */
  nMaxFileHandles = getdtablesize();
  LogAssert0(nMaxFileHandles != -1, "Invalid size by 'getdtablesize()'");

  // 下面的代码将导致libpcap不能工作（open_pcap_live()虽然成功了）
  //for (int i = nMaxFileHandles; i >= 3; i--)
  //{
  //  close(i);
  //}

  /*
   * Disconnect from session
   */
  pidMyself = fork();
  if (pidMyself < 0)
  {
    throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "fork", errno);
    //LogExit(("Error: Could not 'fork()' due to '%m' !\n"));
  }
  if (pidMyself > 0)
  {
    /* Original father process exit */
    exit(0);
  }

  /*
   * Now the new process begin here.
   */
  /* ------------------------------------------------------------------------- */
  /* Disconnect from tty, and The process becomes a grouper */
  setsid();
  pidMyself = getpid();

  /* Disable signal processing until we're ready to go. */
  BlockingInstalledSignals();

  /* Open system console as stderr */
  hConsole = open("/dev/console", O_WRONLY | O_NOCTTY);
  if (hConsole != 2)
  {
    dup2(hConsole, 2);
    close(hConsole);
  }

  /* Write "<my>.pid" */
  snprintf(aszPath, sizeof(aszPath), "./%s.pid", _stringDaemonName.c_str());
  filePID = fopen(aszPath, "w");
  fprintf(filePID, "%d", pidMyself);
  fclose(filePID);

  /* Enable signal processing now */
  UnblockingInstalledSignals();

  // Calling virtual Run()
  Run();
  // Calling virtual Finalize()
  Finalize();

  ZLS_memory_management_cleanup();
}


void CUNIXDaemon::GenerateVersionInfo()
{
  _stringVersion = _stringProductName +
                   "\nVersion is " + _nMajorVersion + "." + _nMinorVersion +
                   "\nCompiled with ";

  /* Here are all the system definitions compilation uses */
  #if defined(__solaris__) || defined(SOLARIS)
    _stringVersion += "__solaris__ ";
  #endif

  #if defined(__linux__)
    _stringVersion += "__linux__ ";
  #endif

  #if defined(__FreeBSD__)
    _stringVersion += "__FreeBSD__ ";
  #endif

  #if defined(__hpux__)
    _stringVersion += "__hpux__ ";
  #endif

  #if defined(__aix__)
    _stringVersion += "__aix__ ";
  #endif

  #if defined(__irix__)
    _stringVersion += "__irix__(";
    #if (_MIPS_SZLONG == 64)
      _stringVersion += "64 bits) ";
    #else
      _stringVersion += "32 bits) ";
    #endif
  #endif

  #if defined(__alpha__)
    _stringVersion += "__alpha__ ";
  #endif

  #if defined(__unixware__)
    _stringVersion += "__unixware__ ";
  #endif

  #if defined(__bsd__)
    _stringVersion += "__bsd__ ";
  #endif

  #if defined(__svr4__)
    _stringVersion += "__svr4__ ";
  #endif

  #if defined(__sys5__)
    _stringVersion += "__sys5__ ";
  #endif

  #if defined(ENABLE_THREADS)
    _stringVersion += "ENABLE_THREADS ";
  #endif

  _stringVersion += "\n\n";
}


const std::string & CUNIXDaemon::GetVersionInfo() const
{
  return _stringVersion;
}


void CUNIXDaemon::GenerateCopyrightInfo()
{
  _stringCopyright = _stringProductName +
                     "\nCopyright (C) since 1998 by Albert Zheng - 郑立松, All Rights Reserved." +
                     "\nlisong.zheng@gmail.com\n\n" +
                     _stringVersion;
}


const std::string & CUNIXDaemon::GetCopyrightInfo() const
{
  return _stringCopyright;
}


ZLS_END_NAMESPACE

