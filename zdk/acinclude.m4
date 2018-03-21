dnl
dnl Local macros by Albert Zheng.
dnl
dnl Modify History:
dnl   2001/9/9, Due to libstdc++-3.0, the following are fixed:
dnl     (1) 'AC_CHECK_CXX_EH' added 'throw()' to 'what()' method.
dnl     (2) 'AC_CHECK_CXX_STL' added 'std::' to use 'set' template class.
dnl 
dnl $Header: /backup/cvsroot/project/pnids/zdk/acinclude.m4,v 1.3 2001/11/02 19:48:00 zls Exp $
dnl
dnl $Date: 2001/11/02 19:48:00 $
dnl
dnl $Revision: 1.3 $
dnl
dnl $Name:  $
dnl
dnl $Author: zls $
dnl
dnl Copyright(C) since 1998 by Albert Zheng - 郑立松, All Rights Reserved.
dnl
dnl lisong.zheng@gmail.com
dnl
dnl $State: Exp $
dnl


AC_DEFUN(LIBZDK_CHECK,
[
  libzdk_cv_posix_atomic=no
  AC_MSG_CHECKING([for atomic operations])
  AC_EGREP_HEADER(atomic_t, asm/atomic.h,[
        libzdk_cv_posix_atomic=yes
        AC_DEFINE(HAVE_ASM_ATOMIC_H)
        ],[
        AC_EGREP_HEADER(atomic_t, sys/atomic.h,[
                libzdk_cv_posix_atomic=yes
                AC_DEFINE(HAVE_SYS_ATOMIC_H)
        ])
  ])            
  AC_MSG_RESULT($libzdk_cv_posix_atomic)
  if test "x$libzdk_cv_cxx_posix_atomic" = "xyes"
  then
        AC_DEFINE(HAVE_ATOMIC)
  fi

  libzdk_cv_pthread_mutex_recursive=no
  AC_MSG_CHECKING([for PTHREAD_MUTEX_RECURSIVE])
  AC_EGREP_HEADER(PTHREAD_MUTEX_RECURSIVE, pthread.h,[
                libzdk_cv_pthread_mutex_recursive=yes
                AC_DEFINE(HAVE_PTHREAD_MUTEX_RECURSIVE)
        ])
  AC_MSG_RESULT($libzdk_cv_pthread_mutex_recursive)
])



dnl
dnl Local macros borrowed from libodbc++
dnl


dnl Macro: AC_CHECK_CXX_STL
dnl Sets $ac_cv_cxx_stl to yes or no
dnl defines HAVE_CXX_STL if ok

AC_DEFUN(AC_CHECK_CXX_STL,
[
AC_LANG_SAVE
AC_LANG_CPLUSPLUS
AC_MSG_CHECKING([whether STL is available])
AC_CACHE_VAL(ac_cv_cxx_stl,
[
AC_TRY_COMPILE([
#include <set>
],[
std::set<int> t;
t.insert(t.begin(),1);
std::set<int>::iterator i=t.find(1);
],
ac_cv_cxx_stl=yes,
ac_cv_cxx_stl=no)
])
AC_MSG_RESULT($ac_cv_cxx_stl)
if test "x$ac_cv_cxx_stl" = "xyes"
then
	AC_DEFINE(HAVE_CXX_STL)
fi
AC_LANG_RESTORE
])



dnl Macro: AC_CHECK_CXX_EH
dnl Sets $ac_cv_cxx_eh to yes or no

AC_DEFUN(AC_CHECK_CXX_EH,
[
AC_LANG_SAVE
AC_LANG_CPLUSPLUS
AC_MSG_CHECKING([whether the C++ compiler ($CXX $CXXFLAGS) has correct exception handling])
AC_CACHE_VAL(ac_cv_cxx_eh,
[
AC_TRY_RUN(
[
#include <exception>
#include <string.h>

using namespace std;

struct test : public exception {
	virtual const char* what() const throw() { return "test"; }
};

static void func() { throw test(); }
int main(void)
{
	try {
		func();
	} catch(exception& e) {
		return (strcmp(e.what(),"test")!=0);
	} catch(...) { return 1; }
	return 1;
}
],
ac_cv_cxx_eh=yes,
ac_cv_cxx_eh=no)
])
AC_MSG_RESULT([$ac_cv_cxx_eh])
if test "x$ac_cv_cxx_eh" = "xyes"
then
	AC_DEFINE(HAVE_CXX_EH)
fi
AC_LANG_RESTORE
])


dnl Macro: AC_CHECK_CXX_NS
dnl Test if the c++ compiler supports namespaces
dnl Set $ac_cv_cxx_ns to either yes or no
dnl Define HAVE_CXX_NS if yes

AC_DEFUN(AC_CHECK_CXX_NS,
[
AC_LANG_SAVE
AC_LANG_CPLUSPLUS
AC_MSG_CHECKING([whether the C++ compiler ($CXX $CXXFLAGS) supports namespaces])
AC_CACHE_VAL(ac_cv_cxx_ns,
[
AC_TRY_COMPILE([
namespace A {
	namespace B {
		struct X {};
	};
};
],[
	A::B::X x;
],
ac_cv_cxx_ns=yes,
ac_cv_cxx_ns=no)
])

AC_MSG_RESULT([$ac_cv_cxx_ns])

if test "x$ac_cv_cxx_ns" = "xyes"
then
	AC_DEFINE(HAVE_CXX_NS)
fi
AC_LANG_RESTORE
])


dnl Macro: AC_CHECK_THREADS
dnl Test if we should compile with thread support
AC_DEFUN(AC_CHECK_THREADS,
[
AC_MSG_CHECKING([whether to enable threads])
AC_ARG_ENABLE(threads,
[  --enable-threads        Enable threads [yes] ],
	enable_threads=$enableval,enable_threads=yes
)

if test "x$enable_threads" = "xyes" 
then
	AC_MSG_RESULT(yes)

# ok, now check for pthreads
AC_CHECK_HEADER(pthread.h,[
	AC_DEFINE(HAVE_PTHREAD_H)
	],[AC_MSG_ERROR([pthread.h not found. Consider not using --enable-threads])])

# check if pthreads are in our default library environment
AC_CHECK_FUNCS(pthread_create,pthreads_ok=yes,pthreads_ok=no)
THREAD_LIBS=""

if test "x$pthreads_ok" != xyes
then

AC_CHECK_LIB(pthread,pthread_create,
	pthreads_ok=yes
	THREAD_LIBS="-lpthread",pthreads_ok=no)
fi

if test "x$pthreads_ok" != xyes
then

# try libc_r (*BSD)
	AC_CHECK_LIB(c_r,pthread_create,
	pthreads_ok=yes
	#THREAD_LIBS="-lc_r",pthreads_ok=no)
	# Albert Zheng: *BSD only need "-pthread", then gcc will automatic known what libraries required.
	THREAD_LIBS="-pthread",pthreads_ok=no)
fi

if test "x$pthreads_ok" = xyes
then
# now we know we can use pthreads. 
# "-D_REENTRANT -D_THREAD_SAFE -D_GNU_SOURCE" is required for FreeBSD and some OS
# "-D_PTHREADS" is required for STL allocator-thread-safety
	AC_DEFINE(ENABLE_THREADS)
	CXXFLAGS="-D_REENTRANT -D_THREAD_SAFE -D_PTHREADS -DBOOST_RE_THREADS $CXXFLAGS"
	CFLAGS="-D_REENTRANT -D_THREAD_SAFE $CFLAGS"
else
	AC_MSG_ERROR([Unable to find a POSIX threads environment.])
fi
else
	AC_MSG_RESULT(no)
fi
AC_SUBST(THREAD_LIBS)
])



dnl Macro: AC_CHECK_IODBC
dnl Checks for iodbc optionally in provided directories
dnl sets shell variable iodbc_ok to yes or no.
dnl Defines HAVE_LIBIODBC, HAVE_ISQL_H, HAVE_ISQLEXT_H if they are found
AC_DEFUN(AC_CHECK_IODBC,
[
AC_LANG_SAVE
AC_LANG_C
AC_ARG_WITH(iodbc,
[  --with-iodbc[=DIR]      Use iodbc, optionally installed in DIR],
[
if test "x$withval" != "xyes"
then
	iodbc_dir=$withval
else
	iodbc_dir="/usr/local"
fi
])

if test "x$iodbc_dir" = "x"
then
	iodbc_dir="/usr/local"
fi

AC_ARG_WITH(iodbc-includes,
[  --with-iodbc-includes=DIR Find iodbc headers in DIR],
[iodbc_includes_dir=$withval],
[iodbc_includes_dir="$iodbc_dir/include"]
)

AC_ARG_WITH(iodbc-libraries,
[  --with-iodbc-libraries=DIR Find iodbc libraries in DIR],
[iodbc_libraries_dir=$withval],
[iodbc_libraries_dir="$iodbc_dir/lib"]
)

save_CPPFLAGS="$CPPFLAGS"
save_LIBS="$LIBS"

CPPFLAGS="$CPPFLAGS -I$iodbc_includes_dir"
LIBS="$LIBS -L$iodbc_libraries_dir"

AC_CHECK_HEADERS([isql.h isqlext.h],
[iodbc_ok=yes; odbc_headers="$odbc_headers $ac_hdr"],
[iodbc_ok=no; break])

if test "x$iodbc_ok" = "xyes"
then
	AC_CHECK_LIB(iodbc,SQLConnect,[iodbc_ok=yes],[iodbc_ok=no])
fi

if test "x$iodbc_ok" = "xyes"
then
	LIBS="$LIBS -liodbc"
	AC_DEFINE(HAVE_LIBIODBC)
	AC_DEFINE(HAVE_ISQL_H)
	AC_DEFINE(HAVE_ISQLEXT_H)
else
	CPPFLAGS="$save_CPPFLAGS"
	LIBS="$save_LIBS"
fi
AC_LANG_RESTORE
])


AC_DEFUN(AC_CHECK_ODBC,
[
AC_LANG_SAVE
AC_LANG_C
AC_MSG_CHECKING([whether unixODBC should be used])
AC_ARG_WITH(odbc,
[  --with-odbc[=DIR]       Use unixODBC, optionally installed in DIR],
[
if test "x$withval" != "xyes"
then
	odbc_dir=$withval
else
	odbc_dir="/usr/local"
fi
])

if test "x$odbc_dir" = "x"
then
	AC_MSG_RESULT(no)
else
	AC_MSG_RESULT(yes)

AC_ARG_WITH(odbc-includes,
[  --with-odbc-includes=DIR Find unixODBC headers in DIR],
[odbc_includes_dir=$withval],
[odbc_includes_dir="$odbc_dir/include"]
)

AC_ARG_WITH(odbc-libraries,
[  --with-odbc-libraries=DIR Find unixODBC libraries in DIR],
[odbc_libraries_dir=$withval],
[odbc_libraries_dir="$odbc_dir/lib"]
)


odbc_libraries_dir="$odbc_dir/lib"

save_CPPFLAGS="$CPPFLAGS"
save_LIBS="$LIBS"

CPPFLAGS="$CPPFLAGS -I$odbc_includes_dir"
LIBS="$LIBS -L$odbc_libraries_dir"

AC_CHECK_HEADERS([sql.h sqlext.h],
[odbc_ok=yes; odbc_headers="$odbc_headers $ac_hdr"],
[odbc_ok=no; break]
)

if test "x$odbc_ok" = "xyes"
then
	AC_CHECK_LIB(odbc,SQLConnect,[odbc_ok=yes],[odbc_ok=no])
fi

if test "x$odbc_ok" = "xyes"
then
	LIBS="$LIBS -lodbc"
	AC_DEFINE(HAVE_LIBODBC)
	AC_DEFINE(HAVE_SQL_H)
	AC_DEFINE(HAVE_SQLEXT_H)
else
	CPPFLAGS="$save_CPPFLAGS"
	LIBS="$save_LIBS"
fi
fi
AC_LANG_RESTORE
])

dnl Macro: AC_CHECK_ODBC_TYPE
dnl Checks if $1 is a valid type in the ODBC environment,
dnl and #defines it to $2 if not

AC_DEFUN(AC_CHECK_ODBC_TYPE,
[

AC_MSG_CHECKING([for $1])
AC_CACHE_VAL(ac_cv_odbc_$1,
[
AC_LANG_SAVE
AC_LANG_C
echo > conftest.c

for i in $odbc_headers
do
	echo "#include <$i>" >> conftest.c
done

echo "int main(void) { $1 x; return 0; }" >> conftest.c

if $CC -c $CFLAGS $CPPFLAGS conftest.c > /dev/null 2> /dev/null
then
	eval ac_cv_odbc_$1=yes
else
	eval ac_cv_odbc_$2=no
fi
rm -f conftest*
AC_LANG_RESTORE

])

eval ac_odbc_check_res=$ac_cv_odbc_$1
if test "x$ac_odbc_check_res" = "xyes"
then
	AC_MSG_RESULT(yes)
else
	AC_MSG_RESULT([no ($2)])
	AC_DEFINE($1,$2)
fi
])
