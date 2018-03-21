#
# $Header: /backup/cvsroot/project/pnids/zdk/zls/zvm/Makefile.am,v 1.3 2001/11/11 17:15:58 zls Exp $
#
# $Date: 2001/11/11 17:15:58 $
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

pkglib_LTLIBRARIES = libzvm.la
libzvm_la_SOURCES = Manifest.hpp Manifest.cpp \
		CInstructionDictionary.hpp CInstructionDictionary.cpp \
		ZVMException.hpp ZVMException.cpp \
		CProtocolPort.hpp CProtocolPort.cpp \
		CIPv4CIDRAddress.hpp CIPv4CIDRAddress.cpp \
		CTableWrapper.hpp CTableWrapper.cpp \
		CSlot.hpp CSlot.cpp \
		ConstantPool.hpp ConstantPool.cpp \
		CInstruction.hpp CInstruction.cpp \
		CZVMFunction.hpp CZVMFunction.cpp \
		CGlobalVariableRegisterEntry.hpp CGlobalVariableRegisterEntry.cpp \
		CGlobalFunctionRegisterEntry.hpp CGlobalFunctionRegisterEntry.cpp \
		CFunctionInvokeInterface.hpp CFunctionInvokeInterface.cpp \
		CZVMObjectFile.hpp CZVMObjectFile.cpp \
		CZVMVirtualThread.hpp CZVMVirtualThread.cpp \
		CVirtualMachine.hpp CVirtualMachine.cpp \
		INativeLibraryImport.hpp INativeLibraryImport.cpp \
		CStandardLibrary.hpp CStandardLibrary.cpp
libzvm_la_LIBADD =
libzvm_la_LDFLAGS = -version-info @lib_version@
libzvm_la_DEPENDENCIES = ${top_srcdir}/zls/zfc/libzfc.la


pkglibdir = ${libdir}/zls
 
pkginclude_HEADERS = 

pkgincludedir = ${includedir}/zls/zvm



bin_PROGRAMS = demo1

demo1_SOURCES = demo1.cpp
demo1_LDADD = libzvm.la \
	${top_srcdir}/zls/zfc/libzfc.la \
	@THREAD_LIBS@
demo1_LDFLAGS = -static
demo1_DEPENDENCIES = libzvm.la \
	${top_srcdir}/zls/zfc/libzfc.la 

