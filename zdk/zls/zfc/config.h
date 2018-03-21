/* zls/zfc/config.h.  Generated automatically by configure.  */
/* zls/zfc/config.h.in.  Generated automatically from configure.in by autoheader 2.13.  */
/*
 * Put any default '#undef' or '#define' here, they will be copied to top of 'config.h.in'.
 */

/* Define to empty if the keyword does not work.  */
/* #undef const */

/* Define if you don't have vprintf but do have _doprnt.  */
/* #undef HAVE_DOPRNT */

/* Define if you have the strftime function.  */
#define HAVE_STRFTIME 1

/* Define if you have the vprintf function.  */
#define HAVE_VPRINTF 1

/* Define as __inline if that's what the C compiler calls it.  */
/* #undef inline */

/* Define to `unsigned' if <sys/types.h> doesn't define.  */
/* #undef size_t */

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* Define if you can safely include both <sys/time.h> and <time.h>.  */
#define TIME_WITH_SYS_TIME 1

/* Define if your <sys/time.h> declares struct tm.  */
/* #undef TM_IN_SYS_TIME */

/*
 * Here are requied macros by 'AC_DEFINE()' in 'configure.in'.
 */
#define __linux__ 1
/* #undef __solaris__ */

/* #undef ENABLE_DEBUG_ZLS_malloc */
#define ENABLE_THREADS 1
#define HAVE_PTHREAD_H 1
#define HAVE_CXX_EH 1
#define HAVE_CXX_NS 1
#define HAVE_CXX_STL 1
#define ENABLE_OVERLOAD_OPERATOR_NEW 1
/* #undef NDEBUG */

#define HAVE_ASM_ATOMIC_H 1
/* #undef HAVE_SYS_ATOMIC_H */
/* #undef HAVE_ATOMIC */
#define HAVE_PTHREAD_MUTEX_RECURSIVE 1
#define HAVE_STRUCT_ICMPHDR 1
#define HAVE_TCP_STATES 1
/* #undef HAVE_STRUCT_UDPHDR */

#define ENABLE_ZVM_DEBUG 1
#define ENABLE_ZVM_OPTIMIZATION 2

/* The number of bytes in a int.  */
#define SIZEOF_INT 4

/* The number of bytes in a long.  */
#define SIZEOF_LONG 4

/* The number of bytes in a long long.  */
#define SIZEOF_LONG_LONG 8

/* Define if you have the localtime_r function.  */
#define HAVE_LOCALTIME_R 1

/* Define if you have the nanosleep function.  */
#define HAVE_NANOSLEEP 1

/* Define if you have the pthread_attr_setstacksize function.  */
/* #undef HAVE_PTHREAD_ATTR_SETSTACKSIZE */

/* Define if you have the pthread_create function.  */
/* #undef HAVE_PTHREAD_CREATE */

/* Define if you have the pthread_delay_np function.  */
/* #undef HAVE_PTHREAD_DELAY_NP */

/* Define if you have the pthread_yield function.  */
/* #undef HAVE_PTHREAD_YIELD */

/* Define if you have the sched_yield function.  */
#define HAVE_SCHED_YIELD 1

/* Define if you have the <dlfcn.h> header file.  */
#define HAVE_DLFCN_H 1

/* Define if you have the <limits.h> header file.  */
#define HAVE_LIMITS_H 1

/* Define if you have the <pthread_np.h> header file.  */
/* #undef HAVE_PTHREAD_NP_H */

/* Define if you have the <sched.h> header file.  */
#define HAVE_SCHED_H 1

/* Define if you have the <strings.h> header file.  */
#define HAVE_STRINGS_H 1

/* Define if you have the <sys/sched.h> header file.  */
/* #undef HAVE_SYS_SCHED_H */

/* Define if you have the <syslog.h> header file.  */
#define HAVE_SYSLOG_H 1

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Name of package */
#define PACKAGE "libzdk"

/* Version number of package */
#define VERSION "1.0.0"

/*
 * Put any default '#undef' or '#define' here, they will be copied to bottom of 'config.h.in'.
 */
