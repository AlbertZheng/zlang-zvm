#
# $Header: /backup/cvsroot/project/pnids/zdk/zls/zfc/Makefile.am,v 1.3 2001/11/11 17:15:33 zls Exp $
#
# $Date: 2001/11/11 17:15:33 $
#
# $Revision: 1.3 $
#
# $Name:  $
#
# $Author: zls $
#
# Copyright(C) since 1998 by Albert Zheng - 郑立松, All Rights Reserved.
#
# lisong.zheng@gmail.com
#
# $State: Exp $
#


#INCLUDES = -I${includedir} -I${top_srcdir}
INCLUDES = -I${top_srcdir}

pkglib_LTLIBRARIES = libzfc.la
libzfc_la_SOURCES = \
		config.h Manifest.h \
		Debug.h Debug.c \
		Toolkit.h Toolkit.hpp Toolkit.cpp \
		Memory.h Memory.hpp Memory.cpp \
		CBinaryString.hpp CBinaryString.cpp \
		CBinaryInputFileStream.hpp CBinaryInputFileStream.cpp \
		CBinaryOutputFileStream.hpp CBinaryOutputFileStream.cpp \
		Exception.cpp \
		CUNIXDaemon.hpp CUNIXDaemon.cpp \
		CThreadSpecialStorage.hpp CThreadSpecialStorage.cpp \
		CMutex.hpp CMutex.cpp \
		CSynchronized.hpp CSynchronized.cpp \
		CThreadId.hpp CThreadId.cpp \
		CThread.hpp CThread.cpp \
		CAtomicCounter.hpp CAtomicCounter.cpp \
		IPv4Address.hpp IPv4Address.cpp \
		Hash.hpp Hash.cpp \
		CPipe.hpp CPipe.cpp \
		getopt.h getopt.c getopt1.c
libzfc_la_LIBADD = 
libzfc_la_LDFLAGS = -version-info @lib_version@
libzfc_la_DEPENDENCIES =

# 指示lib被安装位置
pkglibdir = ${libdir}/zls

# 指示这个目录下要被安装的include文件及被安装位置
pkginclude_HEADERS = \
		config.h Manifest.h Debug.h Toolkit.h Toolkit.hpp \
		Memory.h Memory.hpp SmartPointer.hpp CBinaryString.hpp \
		CBinaryInputFileStream.hpp CBinaryOutputFileStream.hpp \
		Exception.hpp CSingletonFactoryT.hpp \
		CUNIXDaemon.hpp CThreadSpecialStorage.hpp CThreadId.hpp CMutex.hpp \
		CMonitor.hpp CSynchronized.hpp CThread.hpp CAtomicCounter.hpp \
		IPv4Address.hpp Hash.hpp CPipe.hpp
pkgincludedir = ${includedir}/zls/zfc

