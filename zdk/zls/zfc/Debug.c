/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/Debug.c,v $
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


#include <zls/zfc/Debug.h>


/*
 * 注意：在Logger中只允许使用realloc()来动态扩加_GpszLogBuffer，而不允许使用
 *       ZLS_realloc().因为ZLS_realloc()中将可能使用Logger来log内存申请失败信
 *       息!同理，也不允许使用ZLS_malloc()!
 *       如果使用了Garbage Collector，则还可允许使用GC_realloc().
 */
#define _LOGGER_realloc   realloc
#define _LOGGER_free      ZLS_free

bool _GbZFC_ASSERT_CHECK = true;

bool TurnZFCAssertOn()
{
  bool bOld = _GbZFC_ASSERT_CHECK;
  _GbZFC_ASSERT_CHECK = true;
  return bOld;
}

bool TurnZFCAssertOff()
{
  bool bOld = _GbZFC_ASSERT_CHECK;
  _GbZFC_ASSERT_CHECK = false;
  return bOld;
}

bool GetZFCAssertSwitchState()
{
  return _GbZFC_ASSERT_CHECK;
}


static int _SGnDebugLevel = 3;

int IncreaseLoggerDebugLevel()
{
  ++_SGnDebugLevel;
  return(_SGnDebugLevel);
}

int DecreaseLoggerDebugLevel()
{
  --_SGnDebugLevel;
  if (_SGnDebugLevel < 0)
    _SGnDebugLevel = 0;
  return(_SGnDebugLevel);
}

int SetLoggerDebugLevel(int nDebugLevel)
{
  int nOldLevel = _SGnDebugLevel;
  _SGnDebugLevel = nDebugLevel;
  return(nOldLevel);
}

int GetLoggerDebugLevel()
{
  return(_SGnDebugLevel);
}


static int    _SGnBufferBucketCount = 1;
static char * _SGpszLoggerBuffer = (char *)NULL;
bool          _GbLoggerHadBeenOpened = false;
#ifdef ENABLE_THREADS
pthread_key_t           _GtLoggerTSSKey;  /* @todo 在什么时候释放这个 */
static pthread_once_t   _SGtLoggerTSSOnce = PTHREAD_ONCE_INIT;
static pthread_mutex_t  _SGtLoggerMutex = PTHREAD_MUTEX_INITIALIZER;  /* @todo 在什么时候释放这个 */
#endif
TLoggerTSS      _GtSharedLoggerTSS;


#ifdef ENABLE_THREADS
static void _LoggerTSSOnce()
{
  int nResult;
  if ((nResult = pthread_key_create(&_GtLoggerTSSKey, free)) != 0)
  {
    ZLS_ASSERT1(nResult == 0, "pthread_key_create(): %s", ERRNO_TEXT(nResult));
  }
}
#endif

void OpenLogger(const char * pszProcessName)
{
#ifdef ENABLE_THREADS
  /* 无论在一个process中调用OpenLogger()多少次，都必须保证_GtLoggerTSSKey只被申请一次. */
  pthread_once(&_SGtLoggerTSSOnce, _LoggerTSSOnce);
  pthread_mutex_lock(&_SGtLoggerMutex);
#endif

  if (! _GbLoggerHadBeenOpened)
  /* 不也在pthread_once()中申请_SGpszLoggerBuffer的原因是我也必须支持非thread版本 */
  {
    /*
     * 在main()中就应该调用OpenLogger()，当第一次调用OpenLogger()时，下面那行
     * 代码其实变成：
     *     _SGpszLoggerBuffer = realloc((char *)NULL, _SGnBufferBucketCount * LINE_MAX);
     * 此时realloc()应该必须要成功的！
     */
    _SGpszLoggerBuffer = _LOGGER_realloc(_SGpszLoggerBuffer, _SGnBufferBucketCount * LINE_MAX);  /* LINE_MAX: a POSIX constant */
    ZLS_ASSERT0(_SGpszLoggerBuffer != (char *)NULL, "Unexpected failure at 'realloc()'");

    /* Q: openlog()应该会copy第一个参数的值吧? */
    openlog(pszProcessName, LOG_CONS | LOG_NDELAY | LOG_PID, LOG_USER);

    _GbLoggerHadBeenOpened = true;
  }

#ifdef ENABLE_THREADS
  pthread_mutex_unlock(&_SGtLoggerMutex);
#endif
}

void CloseLogger()
{
#ifdef ENABLE_THREADS
  pthread_mutex_lock(&_SGtLoggerMutex);
#endif

  _LOGGER_free(_SGpszLoggerBuffer);
  _SGpszLoggerBuffer = (char *)NULL;

  closelog();

  _GbLoggerHadBeenOpened = false;

#ifdef ENABLE_THREADS
  pthread_mutex_unlock(&_SGtLoggerMutex);
#endif
}


#define _INCREASE_LOG_BUFFER    \
   /* save current distance */ \
   nDistance = psz - _SGpszLoggerBuffer; \
   /* we must dynamicly increace "_GaszLoggerBuffer" ! */ \
   if ((pTmp = _LOGGER_realloc(_SGpszLoggerBuffer, (++_SGnBufferBucketCount)*LINE_MAX))) \
   { \
     _SGpszLoggerBuffer = pTmp; \
     psz = _SGpszLoggerBuffer + nDistance; \
     nAvailable += LINE_MAX; \
     nAvailableForReallocFailed += LINE_MAX; \
   } \
   else \
   { \
     nLen = snprintf(_SGpszLoggerBuffer + nDistanceForReallocFailed, nAvailableForReallocFailed, \
                     "The log-message too long, and MUST realloc '_SGpszLoggerBuffer' BUT failed !\n"); \
     psz = _SGpszLoggerBuffer + nDistanceForReallocFailed + nLen; \
     break; \
   }

static void _vLogBackend(int nSyslogPriority, int nDebugLevel,
                         const char * pszFormat, va_list arguments)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("_vLogBackend()");
  int nOldErrno = errno;   /* save "errno" */
  time_t timeval = time(0);
  int nLen;
  int nAvailable = _SGnBufferBucketCount * LINE_MAX;
  char * psz;
  int nDistance;
  char * pTmp;
  int nDistanceForReallocFailed;
  int nAvailableForReallocFailed;
  TLoggerTSS * ptLoggerTSS;
  const char *pszFile;
  const char *pszFunc;
  int nLine;

  /* 在第一次调用Logger的任何功能之前必须先调用"OpenLogger()"，以便allocate TSS key */
  ZLS_ASSERT0(_GbLoggerHadBeenOpened == true,
              "You forget to call 'OpenLogger()' firstly before you can start to use any logging features.");

#ifdef ENABLE_THREADS
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(ptLoggerTSS);
  /* lock以免多个线程争用syslog机制 */
  pthread_mutex_lock(&_SGtLoggerMutex);
#else
  ptLoggerTSS = &_GtSharedLoggerTSS;
#endif
  pszFile = ptLoggerTSS->pszFileName;
  pszFunc = ptLoggerTSS->pszFuncName;
  nLine = ptLoggerTSS->nLine;

  psz = _SGpszLoggerBuffer;

  /* 产生timestamp */
  if (nSyslogPriority != LOG_NOTICE)
  /* LOG_NOTICE是专门给LogHex使用的，不想要timestamp. */
  {
    /*
     * 在_GaszLogBuffer中产生Log Header.
     */
    *psz++ = '[';
    --nAvailable;
    nLen = PrintTime(psz, nAvailable, timeval);
    psz += nLen;
    nAvailable -= nLen;

    if (nSyslogPriority == LOG_DEBUG)
    {
      nLen = snprintf(psz, nAvailable, ",%d] ", nDebugLevel);
    }
    else
    {
      nLen = snprintf(psz, nAvailable, "] ");
    }
    psz += nLen;
    nAvailable -= nLen;
  }

  /* 产生"File:Line(Function)" */
  if (nSyslogPriority != LOG_NOTICE && nSyslogPriority != LOG_INFO)
  /* LOG_DEBUG、LOG_ERR、LOG_WARNING还需要Log源码跟踪信息. */
  {
    if (pszFile && pszFunc)
    {
      nLen = snprintf(psz, nAvailable, "%s:%d(%s)\n  ", pszFile, nLine, pszFunc);
    }
    else
    {
      if (pszFile)
      {
        nLen = snprintf(psz, nAvailable, "%s:%d(???)\n  ", pszFile, nLine);
      }
      else
      {
        nLen = snprintf(psz, nAvailable, "???:%d(%s)\n  ", nLine, pszFunc);
      }
    }

    psz += nLen;
    nAvailable -= nLen;
  }

  /* save current position */
  nDistanceForReallocFailed = psz - _SGpszLoggerBuffer;
  nAvailableForReallocFailed = nAvailable;

  /*
   * 将pszFormat添加到_GaszLogBuffer中.
   */

  if (nSyslogPriority < LOG_NOTICE)
  /*
   * 当为LOG_WARNING、LOG_ERR、LOG_CRIT、LOG_ALERT、LOG_EMERG时，message还必须
   * dump到stderr，现在先dump到stderr.
   */
  {
    /*
     * scan "pszFormat", and replace "%m" with "strerror(errno)".
     *
     * syslog()也将做一次同样的转换，但是由于我们必须先将message输出到stderr，
     * 所以我们必须自己做这个转换，否则vfprintf()将会因为"%m"没有相应的参数来
     * 匹配而出现不可意料的问题。
     */
    while (*pszFormat)
    {
                     /* one byte reserved for tail '\0' */
      if (nAvailable <= 1)
      {
        _INCREASE_LOG_BUFFER
      }

      if (*pszFormat == '%' && *(pszFormat+1) && *(pszFormat+1) == 'm')
      {
        nLen = strlen(ERRNO_TEXT(nOldErrno));
        if (nLen >= nAvailable)
        {
          /* strlen(strerror(errno)) should be less than LINE_MAX. */
          ZLS_ASSERT3(nLen < LINE_MAX,
                      "%d=strlen(strerror(%d)) should be less than %d=LINE_MAX.",
                      strlen(ERRNO_TEXT(nOldErrno)), nOldErrno, LINE_MAX);

          _INCREASE_LOG_BUFFER
        }

        strcat(psz, ERRNO_TEXT(nOldErrno));
        psz += nLen;
        nAvailable -= nLen;
        pszFormat += 2;   // jump "%m"
      }
      else
      {
        *psz++ = *pszFormat++;
        --nAvailable;
      }
    }
    *psz = '\0';

    /* first dump to stderr */
    vfprintf(stderr, _SGpszLoggerBuffer, arguments);
  }
  else
  {
    while (*pszFormat)
    {
                     /* one byte reserved for tail '\0' */
      if (nAvailable <= 1)
      {
        _INCREASE_LOG_BUFFER
      }

      *psz++ = *pszFormat++;
      --nAvailable;
    }
    *psz = '\0';
  }

  /*
   * 修改nSyslogPriority，因为：
   * (1) 如果在短期内（好象是1秒）log到syslogd的多条LOG_DEBUG型信息完全相同，则
   *     syslogd只log在这期间内的最后的一条.
   * (2) LOG_NOTICE、LOG_WARNING型信息将再被syslogd重复log两次，即共log三次.
   * (3) 好象在FreeBSD上的etc/syslog.conf配置，LOG_WARNING、LOG_ERR还将被送到
   * /dev/console上好多次，到其它root用户的终端上也好多次，至于次数是在哪里配
   * 置的我还不清楚.
   */
  /*
  if (nSyslogPriority == LOG_DEBUG)
  {
    nSyslogPriority = LOG_INFO;
  }
  else
  {
    if (nSyslogPriority == LOG_WARNING)
    {
      nSyslogPriority = LOG_ERR;
    }
  }
  */
  if (nSyslogPriority == LOG_DEBUG ||
      nSyslogPriority == LOG_WARNING ||
      nSyslogPriority == LOG_ERR ||
      nSyslogPriority == LOG_NOTICE)
  {
    nSyslogPriority = LOG_INFO;
  }
  /* now dump to "syslogd" */
  vsyslog(nSyslogPriority, _SGpszLoggerBuffer, arguments);

#ifdef ENABLE_THREADS
  pthread_mutex_unlock(&_SGtLoggerMutex);
#endif
}

static void _LogBackend(int nSyslogPriority, int nDebugLevel,
                        const char * pszFormat, ...)
{
  va_list arguments;
  va_start(arguments, pszFormat);
  _vLogBackend(nSyslogPriority, nDebugLevel, pszFormat, arguments);
  va_end(arguments);
}

void _LogDebug(const char * pszFormat, ...)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("_LogDebug");
  va_list arguments;
  int nDebugLevel;
#ifdef ENABLE_THREADS
  TLoggerTSS * ptLoggerTSS;
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(ptLoggerTSS);
#else
  TLoggerTSS * ptLoggerTSS = &_GtSharedLoggerTSS;
#endif
  nDebugLevel = ptLoggerTSS->nDebugLevel;

  va_start(arguments, pszFormat);
  if (nDebugLevel <= _SGnDebugLevel)
  /* 只有跟踪级别足够，才log */
  {
    _vLogBackend(LOG_DEBUG, nDebugLevel, pszFormat, arguments);
  }
  va_end(arguments);
}

void _LogMiddle(const char * pszFormat, ...)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("_LogMiddle");
  va_list arguments;
  int nSyslogPriority;
#ifdef ENABLE_THREADS
  TLoggerTSS * ptLoggerTSS;
  _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(ptLoggerTSS);
#else
  TLoggerTSS * ptLoggerTSS = &_GtSharedLoggerTSS;
#endif
  nSyslogPriority = ptLoggerTSS->nSyslogPriority;
  va_start(arguments, pszFormat);
  _vLogBackend(nSyslogPriority, 0, pszFormat, arguments);
  va_end(arguments);
}

void _LogExit(const char * pszFormat, ...)
{
  va_list arguments;
  va_start(arguments, pszFormat);
  _vLogBackend(LOG_ERR, 0, pszFormat, arguments);
  va_end(arguments);

  exit(1);
}

void _LogAbort(const char * pszFormat, ...)
{
  va_list arguments;
  va_start(arguments, pszFormat);
  _vLogBackend(LOG_ERR, 0, pszFormat, arguments);
  va_end(arguments);

  abort();
}


/* LOG_NOTICE将作为LogHex的专用区别. */
#ifdef ENABLE_THREADS
#define LogNotice(X)      \
  { \
    TLoggerTSS * __ptLoggerTSS__; \
    _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__); \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    __ptLoggerTSS__->nSyslogPriority = LOG_NOTICE; \
    _LogMiddle X; \
  }
#else
#define LogNotice(X)      \
  { \
    TLoggerTSS * __ptLoggerTSS__ = &_GtLoggerTSS; \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    __ptLoggerTSS__->nSyslogPriority = LOG_NOTICE; \
    _LogMiddle X; \
  }
#endif

void _LogHex(register const UCHAR *cp, register UDWORD length)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("LogHex()");
  register int ad, i, j, k;
  u_char c;
  u_char line[60];
  static u_char binhex[16] = {
          '0', '1', '2', '3', '4', '5', '6', '7',
          '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

  memset (line, ' ', sizeof line);
  line[sizeof (line)-1] = 0;
  for (ad=i=j=k=0; i<length; i++) {
          c = *cp++;
          line[j++] = binhex[c>>4];
          line[j++] = binhex[c&0xf];
          if (i&1) j++;
          line[42+k++] = c >= ' ' && c < 0x7f ? c : '.';
          if ((i & 15) == 15) {
                  LogNotice(("\n%4x  %s", ad, line));
                  memset (line, ' ', sizeof line);
                  line[sizeof (line)-1] = j = k = 0;
                  ad += 16;
          }
  }

  if (line[0] != ' ') { LogNotice(("\n%4x  %s", ad, line)); }
  LogNotice(("\n"));
  return;
}

