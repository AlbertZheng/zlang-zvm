/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/CZLangCompiler.hpp,v $
 *
 * $Date: 2001/11/14 19:03:08 $
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


#ifndef _ZLS_zlang_CZLangCompiler_hpp_
#define _ZLS_zlang_CZLangCompiler_hpp_

#include <zls/zfc/Manifest.h>
#include <zls/zfc/CPipe.hpp>
#include <zls/zlang/ZLangLexer.hpp>
#include <zls/zlang/ZLangParser.hpp>
#include <zls/zlang/ZLangSymbolTableGenerator.hpp>
#include <zls/zlang/ZLangCodeGenerator.hpp>
#include <antlr/TokenStreamRecognitionException.hpp>
#include <antlr/CommonAST.hpp>
#include <antlr/ASTRefCount.hpp>
#include <zls/zlang/CASTPrinter.hpp>
#include <zls/zlang/CZLangAST.hpp>


// Begin namespace 'zlang::'
ZLS_BEGIN_NAMESPACE(zlang)


/**
 * ZLang compiler.
 *
 * @todo 如果在被include的文件中有语义错误，则怎么来报告正确的文件名呢?
 */
class CZLangCompiler {
  private:
    /**
     * 一个模仿antlr::CharBuffer编写的类，它的功能是提供一个让antlr::CharScanner
     * 能够从stdin读入字符的接口.
     */
    class CStandardInputBuffer : public antlr::InputBuffer {
      private:
        CStandardInputBuffer(const CStandardInputBuffer & rci);
        CStandardInputBuffer & operator=(const CStandardInputBuffer & rci);

      public:
        /** Default constructor. */
        CStandardInputBuffer()
        { }

        /** Overload for get the next character from the pipe. */
        virtual int getChar()
        {
          return fgetc(stdin);
        }
    };

    bool _bTraceLexer;
    bool _bTraceAST;
    bool _bTraceSymbolTable;
    bool _bTraceByteCode;

  public:
    CZLangCompiler(bool bTraceLexer,
                   bool bTraceAST,
                   bool bTraceSymbolTable,
                   bool bTraceByteCode)
      : _bTraceLexer(bTraceLexer),
        _bTraceAST(bTraceAST),
        _bTraceSymbolTable(bTraceSymbolTable),
        _bTraceByteCode(bTraceByteCode)
    { }

    ~CZLangCompiler()
    { }

    /**
     * 进行编译.
     *
     * @throw zfc::ESystemCallFailure 当fork()、execlp()、或waitpid()失败时.
     * @throw zfc::EPanic 当发现"gcc -E"被执行后却不是用exit()退出时，
     * 如"gcc" core dump.
     */
    void Compile(const std::string & rstringSourceFileName,
                 const std::string & rstringObjectFileName);
};


ZLS_END_NAMESPACE


#endif

