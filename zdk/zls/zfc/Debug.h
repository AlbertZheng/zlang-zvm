/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/Debug.h,v $
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


#ifndef _ZLS_zfc_Debug_h_
#define _ZLS_zfc_Debug_h_

#include <zls/zfc/Manifest.h>
#include <zls/zfc/Memory.h>


/*******************************************************************************
 * This module implements debugging utility.
 *
 * The syntax of a debugging log file is represented as:
 *
 *  <debugfile> :== { <debugmsg> }
 *  <debugmsg>  :== <debughdr> "\n  " <debugtext>
 *  <debughdr>  :== '[' TIME [',' LEVEL ']'] [[FILENAME ':'] [FUNCTION '(' FILELINE ')']]
 *  <debugtext> :== { <debugline> }
 *  <debugline> :== TEXT '\n'
 *
 * TEXT     is a string of characters excluding the newline character.
 * LEVEL    is the DEBUG level of the message (an integer in the range 0..10).
 * TIME     is a timestamp of occurrence,and it should be before the timestamp of syslogd.
 * FILENAME is the name of the file from which the debug message was generated.
 * FUNCTION is the function from which the debug message was generated.
 * FILELINE is the line of the source code where the debug message was generated.
 *
 * @note
 * (1) 当log被syslogd处理时，syslogd还将在<debughdr>的前面添加
 * "TIMESTAMP HOSTNAME ident[pid]: "，并且将多的'\n'去除，只允许一个'\n'，这里
 * 的TIMESTAMP应该是比上面的上面的TIME慢点的，它指的是syslogd处理这条message时
 * 的时间.
 * (2) LogWarning()、LogError()、LogExit()、LogAbort()还会将log显示到stderr.
 * (3) log串中如有"%m"，则象syslogd那样我们会将其先转换为"strerror(errno)".
 * (4) 除了LogInfo、LogNotice外，<debughdr>中都有指出源文件的行号跟踪信息.
 *
 * @attention 所有需要使用Logger的函数体中都必须定义一个"static const char * __PRETTY_FUNC__"
 * 的static const变量，因此我建议在每个需要调用Logger的函数体的第一行都有如下一行代码：
 * <pre>
 *   static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("你的函数的原型");
 * </pre>
 ******************************************************************************/



#ifdef __cplusplus
extern "C" {
#endif

#ifndef NDEBUG  /* 这是一个标准宏，如果不想将程序中的所有assert编译进入可执行文件则定义它. */

/**
 * @name ZFC的ASSERT机制的开关变量的相关routine.
 */
//@{
/**
 * 可动态关闭ZFC的ASSERT机制的一个开关变量，缺省为true.
 * 当没有采用NDEBUG进行compile时，还是可通过这个开关变量来动态关闭ZFC的ASSERT机制.
 * @note This is a private global variable.
 */
extern bool _GbZFC_ASSERT_CHECK;

/**
 * ZFC的ASSERT机制的开关变量的相关routine.
 * @note These are public interface.
 */
bool TurnZFCAssertOn __P(());
bool TurnZFCAssertOff __P(());
bool GetZFCAssertSwitchState __P(());
//@}


/**
 * 不带变参的assert宏.
 * @attention 在Logger被open后建议使用LogAssert0()宏.
 */
#define ZLS_ASSERT0(expr, pszMessage)   \
   if (_GbZFC_ASSERT_CHECK && !(expr)) \
   { \
     fprintf(stderr, "%s: %d: assertion('" #expr "') failure due to '" pszMessage "'\n", \
             __FILE__, __LINE__); \
     abort(); \
   }

/**
 * 带一个变参的assert宏.
 * @attention 在Logger被open后建议使用LogAssert1()宏.
 */
#define ZLS_ASSERT1(expr, pszMsgFormat, vp1)    \
   if (_GbZFC_ASSERT_CHECK && !(expr)) \
   { \
     fprintf(stderr, "%s: %d: assertion('" #expr "') failure due to '" pszMsgFormat "'\n", \
             __FILE__, __LINE__, vp1); \
     abort(); \
   }

/**
 * 带两个变参的assert宏.
 * @attention 在Logger被open后建议使用LogAssert2()宏.
 */
#define ZLS_ASSERT2(expr, pszMsgFormat, vp1, vp2)       \
   if (_GbZFC_ASSERT_CHECK && !(expr)) \
   { \
     fprintf(stderr, "%s: %d: assertion('" #expr "') failure due to '" pszMsgFormat "'\n", \
             __FILE__, __LINE__, vp1, vp2); \
     abort(); \
   }

/**
 * 带三个变参的assert宏.
 * @attention 在Logger被open后建议使用LogAssert3()宏.
 */
#define ZLS_ASSERT3(expr, pszMsgFormat, vp1, vp2, vp3)       \
   if (_GbZFC_ASSERT_CHECK && !(expr)) \
   { \
     fprintf(stderr, "%s: %d: assertion('" #expr "') failure due to '" pszMsgFormat "'\n", \
             __FILE__, __LINE__, vp1, vp2, vp3); \
     abort(); \
   }

/**
 * 调用“检查不变量”function的宏.
 *
 * @note “检查不变量”function应该是只包含LogAssert?()或ZLS_ASSERT?()语句的function.
 */
#define ZLS_CHECK_INVARIANTS(calling_function_statement)  calling_function_statement;

#else  /* ! NDEBUG */

#define ZLS_ASSERT0(expr, pszMessage)
#define ZLS_ASSERT1(expr, pszMsgFormat, vp1)
#define ZLS_ASSERT2(expr, pszMsgFormat, vp1, vp2)
#define ZLS_ASSERT3(expr, pszMsgFormat, vp1, vp2, vp3)

#define ZLS_CHECK_INVARIANTS(calling_function_statement)

#endif  /* ! NDEBUG */


/**
 * Logger的Thread special storage.
 * 它将传递源文件名、函数名、行号等信息给_vLogBackend().
 */
typedef struct {
  const char * pszFileName;
  const char * pszFuncName;
  int nLine;

  /** Special for LogDebug(). */
  int nDebugLevel;

  /** Special for LogInfo()、LogNotice()、LogWarning()、LogError(). */
  int nSyslogPriority;
} TLoggerTSS;


/**
 * private global variable.
 */
extern bool _GbLoggerHadBeenOpened;
#ifdef ENABLE_THREADS
extern pthread_key_t _GtLoggerTSSKey;
#endif
extern TLoggerTSS _GtSharedLoggerTSS;


/**
 * public interface.
 */
int IncreaseLoggerDebugLevel __P(());
int DecreaseLoggerDebugLevel __P(());
int SetLoggerDebugLevel __P((int nNewDebugLevel));
int GetLoggerDebugLevel __P(());
void OpenLogger  __P((const char *pszProcessName));
void CloseLogger __P(());


#ifdef ENABLE_THREADS

#define _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(ptr) \
  /* 在第一次调用Logger的任何功能之前必须先调用"OpenLogger()"，以便allocate TSS key */ \
  ZLS_ASSERT0(_GbLoggerHadBeenOpened == true, \
              "You forget to call 'OpenLogger()' firstly before you can start to use any logging features."); \
  if ((ptr = (TLoggerTSS *)pthread_getspecific(_GtLoggerTSSKey)) == (void *)0) \
  { \
    /* 不用ZLS_malloc()是怕引起边界效应，ZLS_malloc()在out of memory或采用跟踪模式时还要调用Logger. */ \
    if (ptr = (TLoggerTSS *)malloc(sizeof(TLoggerTSS))) \
    { \
      pthread_setspecific(_GtLoggerTSSKey, ptr); \
    } \
    else \
    /* 如果thread版本malloc()失败，则只能使用shared而无法再考虑thread间的边界效应了 */ \
    { \
      ptr = &_GtSharedLoggerTSS; \
    } \
  }

/** Logging一级跟踪信息，即当GetLoggerDebugLevel()>=1时才真正进行logging. */
#define LogDebug1(X)    \
  { \
    TLoggerTSS * __ptLoggerTSS__; \
    _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__); \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    __ptLoggerTSS__->nDebugLevel = 1; \
    _LogDebug X; \
  }

/** Logging二级跟踪信息，即当GetLoggerDebugLevel()>=2时才真正进行logging. */
#define LogDebug2(X)    \
  { \
    TLoggerTSS * __ptLoggerTSS__; \
    _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__); \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    __ptLoggerTSS__->nDebugLevel = 2; \
    _LogDebug X; \
  }

/** Logging三级跟踪信息，即当GetLoggerDebugLevel()>=3时才真正进行logging. */
#define LogDebug3(X)    \
  { \
    TLoggerTSS * __ptLoggerTSS__; \
    _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__); \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    __ptLoggerTSS__->nDebugLevel = 3; \
    _LogDebug X; \
  }

/** Logging一般信息. */
#define LogInfo(X)      \
  { \
    TLoggerTSS * __ptLoggerTSS__; \
    _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__); \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    __ptLoggerTSS__->nSyslogPriority = LOG_INFO; \
    _LogMiddle X; \
  }

/** Logging警告信息，警告信息除被logging到syslogd外，还将被dump到stderr. */
#define LogWarning(X)      \
  { \
    TLoggerTSS * __ptLoggerTSS__; \
    _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__); \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    __ptLoggerTSS__->nSyslogPriority = LOG_WARNING; \
    _LogMiddle X; \
  }

/** Logging错误信息，错误信息除被logging到syslogd外，还将被dump到stderr. */
#define LogError(X)      \
  { \
    TLoggerTSS * __ptLoggerTSS__; \
    _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__); \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    __ptLoggerTSS__->nSyslogPriority = LOG_ERR; \
    _LogMiddle X; \
  }

/** Logging严重错误信息，并强制exit程序，严重错误信息除被logging到syslogd外，还将被dump到stderr. */
#define LogExit(X)      \
  { \
    TLoggerTSS * __ptLoggerTSS__; \
    _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__); \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    _LogExit X; \
  }

/** Logging严重错误信息，并强制abort程序，严重错误信息除被logging到syslogd外，还将被dump到stderr. */
#define LogAbort(X)      \
  { \
    TLoggerTSS * __ptLoggerTSS__; \
    _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__); \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    _LogAbort X; \
  }

#ifndef NDEBUG
                             /* pszMessage必须不是变量，而是一个串Literal. */
#define LogAssert0(assert_expr, pszMessage)     \
  if (_GbZFC_ASSERT_CHECK && !(assert_expr)) \
  { \
    TLoggerTSS * __ptLoggerTSS__; \
    _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__); \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    _LogAbort("assertion('" #assert_expr "') failure due to '" pszMessage "'\n"); \
  }

                             /* pszMsgFormat必须不是变量，而是一个串Literal. */
#define LogAssert1(assert_expr, pszMsgFormat, vp1)      \
  if (_GbZFC_ASSERT_CHECK && !(assert_expr)) \
  { \
    TLoggerTSS * __ptLoggerTSS__; \
    _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__); \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    _LogAbort("assertion('" #assert_expr "') failure due to '" pszMsgFormat "'\n", vp1); \
  }

                             /* pszMsgFormat必须不是变量，而是一个串Literal. */
#define LogAssert2(assert_expr, pszMsgFormat, vp1, vp2) \
  if (_GbZFC_ASSERT_CHECK && !(assert_expr)) \
  { \
    TLoggerTSS * __ptLoggerTSS__; \
    _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__); \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    _LogAbort("assertion('" #assert_expr "') failure due to '" pszMsgFormat "'\n", vp1, vp2); \
  }

                             /* pszMsgFormat必须不是变量，而是一个串Literal. */
#define LogAssert3(assert_expr, pszMsgFormat, vp1, vp2, vp3)    \
  if (_GbZFC_ASSERT_CHECK && !(assert_expr)) \
  { \
    TLoggerTSS * __ptLoggerTSS__; \
    _GET_AND_MAY_INITIALIZE_LOGGER_TSS_PTR(__ptLoggerTSS__); \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    _LogAbort("assertion('" #assert_expr "') failure due to '" pszMsgFormat "'\n", vp1, vp2, vp3); \
  }
#else  /* ! NDEBUG */
#define LogAssert0(assert_expr, pszMessage)
#define LogAssert1(assert_expr, pszMsgFormat, vp1)
#define LogAssert2(assert_expr, pszMsgFormat, vp1, vp2)
#define LogAssert3(assert_expr, pszMsgFormat, vp1, vp2, vp3)
#endif  /* ! NDEBUG */

#else  /* ENABLE_THREADS */

#define LogDebug1(X)    \
  { \
    TLoggerTSS * __ptLoggerTSS__ = &_GtLoggerTSS; \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    __ptLoggerTSS__->nDebugLevel = 1; \
    _LogDebug X; \
  }

#define LogDebug2(X)    \
  { \
    TLoggerTSS * __ptLoggerTSS__ = &_GtLoggerTSS; \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    __ptLoggerTSS__->nDebugLevel = 2; \
    _LogDebug X; \
  }

#define LogDebug3(X)    \
  { \
    TLoggerTSS * __ptLoggerTSS__ = &_GtLoggerTSS; \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    __ptLoggerTSS__->nDebugLevel = 3; \
    _LogDebug X; \
  }

#define LogInfo(X)      \
  { \
    TLoggerTSS * __ptLoggerTSS__ = &_GtLoggerTSS; \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    __ptLoggerTSS__->nSyslogPriority = LOG_INFO; \
    _LogMiddle X; \
  }

#define LogWarning(X)      \
  { \
    TLoggerTSS * __ptLoggerTSS__ = &_GtLoggerTSS; \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    __ptLoggerTSS__->nSyslogPriority = LOG_WARNING; \
    _LogMiddle X; \
  }

#define LogError(X)      \
  { \
    TLoggerTSS * __ptLoggerTSS__ = &_GtLoggerTSS; \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    __ptLoggerTSS__->nSyslogPriority = LOG_ERR; \
    _LogMiddle X; \
  }

#define LogExit(X)      \
  { \
    TLoggerTSS * __ptLoggerTSS__ = &_GtLoggerTSS; \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    _LogExit X; \
  }

#define LogAbort(X)      \
  { \
    TLoggerTSS * __ptLoggerTSS__ = &_GtLoggerTSS; \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    _LogAbort X; \
  }

#ifndef NDEBUG
#define LogAssert0(assert_expr, pszMessage)     \
  if (_GbZFC_ASSERT_CHECK && !(assert_expr)) \
  { \
    TLoggerTSS * __ptLoggerTSS__ = &_GtLoggerTSS; \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    _LogAbort("assertion('" #assert_expr "') failure due to '" pszMessage "'\n"); \
  }

#define LogAssert1(assert_expr, pszMsgFormat, vp1)      \
  if (_GbZFC_ASSERT_CHECK && !(assert_expr)) \
  { \
    TLoggerTSS * __ptLoggerTSS__ = &_GtLoggerTSS; \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    _LogAbort("assertion('" #assert_expr "') failure due to '" pszMsgFormat "'\n", vp1); \
  }

#define LogAssert2(assert_expr, pszMsgFormat, vp1, vp2) \
  if (_GbZFC_ASSERT_CHECK && !(assert_expr)) \
  { \
    TLoggerTSS * __ptLoggerTSS__ = &_GtLoggerTSS; \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    _LogAbort("assertion('" #assert_expr "') failure due to '" pszMsgFormat "'\n", vp1, vp2); \
  }

#define LogAssert3(assert_expr, pszMsgFormat, vp1, vp2, vp3)    \
  if (_GbZFC_ASSERT_CHECK && !(assert_expr)) \
  { \
    TLoggerTSS * __ptLoggerTSS__ = &_GtLoggerTSS; \
    __ptLoggerTSS__->pszFileName = __FILE__; \
    __ptLoggerTSS__->pszFuncName = __PRETTY_FUNC__; \
    __ptLoggerTSS__->nLine = __LINE__; \
    _LogAbort("assertion('" #assert_expr "') failure due to '" pszMsgFormat "'\n", vp1, vp2, vp3); \
  }
#else  /* ! NDEBUG */
#define LogAssert0(assert_expr, pszMessage)
#define LogAssert1(assert_expr, pszMsgFormat, vp1)
#define LogAssert2(assert_expr, pszMsgFormat, vp1, vp2)
#define LogAssert3(assert_expr, pszMsgFormat, vp1, vp2, vp3)
#endif  /* ! NDEBUG */

#endif  /* ENABLE_THREADS */


/** Logging一段Byte stream，并且只有跟踪级别足够(>=3)，才真正进行Logging */
#define LogHex(pBuffer, nLength)       \
  if (GetLoggerDebugLevel() >= 3) \
  /* 只有跟踪级别足够，才... */ \
  { \
    _LogHex(pBuffer, nLength); \
  }


/**
 * private interface.
 */
void _LogMiddle  __P((const char* pszFormat, ...));
void _LogDebug   __P((const char* pszFormat, ...));
void _LogExit    __P((const char* pszFormat, ...));
void _LogAbort   __P((const char* pszFormat, ...));
void _LogHex     __P((register const UCHAR * puchBuffer, register UDWORD udwLength));

#ifdef __cplusplus
}
#endif


/**
 * 一个与false同样功能的pretty faking function，通常这个宏只被用在assert中.
 */
#define ShouldNotRunToHere()    false


#endif

