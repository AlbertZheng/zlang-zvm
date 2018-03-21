#
# $Header: /backup/cvsroot/project/pnids/zdk/zls/zlang/Makefile.am,v 1.4 2002/02/28 14:00:05 zls Exp $
#
# $Date: 2002/02/28 14:00:05 $
#
# $Revision: 1.4 $
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


ANTLR = antlr-2.7.1
INCLUDES = -I${prefix}/${ANTLR}/include -I${top_srcdir}
#INCLUDES = -I/backup/pnids/gnu/packages/${ANTLR}/include -I${top_srcdir}

pkglib_LTLIBRARIES = libzlang.la
libzlang_la_SOURCES = \
		ZLangLexer.hpp ZLangLexer.cpp ZLangLexerTokenTypes.hpp \
		ZLangParser.hpp ZLangParser.cpp ZLangTokenTypes.hpp \
		ZLangSymbolTableGenerator.cpp ZLangSymbolTableGenerator.hpp \
		ZLangCodeGenerator.hpp ZLangCodeGenerator.cpp \
		CASTPrinter.cpp CASTPrinter.hpp \
		CZLangAST.hpp CZLangAST.cpp \
		ZLangException.hpp ZLangException.cpp \
		SymbolTable.hpp SymbolTable.cpp \
		CCodeGeneratorHelper.hpp CCodeGeneratorHelper.cpp \
		ConstantPool.hpp ConstantPool.cpp \
		ZLangFunction.hpp ZLangFunction.cpp \
		CZLangCompiler.hpp CZLangCompiler.cpp
libzlang_la_LIBADD =
libzlang_la_LDFLAGS = -version-info @lib_version@
libzlang_la_DEPENDENCIES = ${top_srcdir}/zls/zfc/libzfc.la


pkglibdir = ${libdir}/zls
 
pkginclude_HEADERS =
 
pkgincludedir = ${includedir}/zls/zlang



bin_PROGRAMS = zlangc

zlangc_SOURCES = zlangc.cpp ZLangCompilerOption.h ZLangCompilerOption.c
zlangc_LDADD =	libzlang.la \
		../zvm/libzvm.la \
		${top_srcdir}/zls/zfc/libzfc.la \
		${prefix}/${ANTLR}/lib/libantlr.la \
		@THREAD_LIBS@
zlangc_LDFLAGS = -static
zlangc_DEPENDENCIES =	libzlang.la \
		../zvm/libzvm.la \
		${top_srcdir}/zls/zfc/libzfc.la \
		${prefix}/${ANTLR}/lib/libantlr.la


#ZLangLexer.hpp ZLangLexer.cpp ZLangParser.hpp ZLangParser.cpp : zlangpass1.g
#	java antlr.Tool $^

#ZLangSymbolTableGenerator.hpp ZLangSymbolTableGenerator.cpp : zlangpass2.g
#	java antlr.Tool $^

#ZLangCodeGenerator.hpp ZLangCodeGenerator.cpp : zlangpass3.g
#	java antlr.Tool $^

ZLangCompilerOption.h ZLangCompilerOption.c : zlangc.ggo
	gengetopt --unamed-opts --file-name=ZLangCompilerOption < $^

