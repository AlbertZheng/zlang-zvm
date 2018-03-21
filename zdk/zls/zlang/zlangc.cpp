/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/zlangc.cpp,v $
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


#include <zls/zfc/Manifest.h>
#include <zls/zlang/ZLangCompilerOption.h>
#include <zls/zlang/ZLangLexer.hpp>
#include <zls/zlang/ZLangParser.hpp>
#include <zls/zlang/ZLangSymbolTableGenerator.hpp>
#include <zls/zlang/ZLangCodeGenerator.hpp>
#include <antlr/TokenStreamRecognitionException.hpp>
#include <antlr/CommonAST.hpp>
#include <antlr/ASTRefCount.hpp>
#include <zls/zlang/CASTPrinter.hpp>
#include <zls/zlang/CZLangAST.hpp>
#include <zls/zlang/CZLangCompiler.hpp>


/*
 * 命令行格式为：
 *     [-D macro]
 *     [-I include-path]
 *     [-o ObjectFileName]
 *     [--trace-lexer]
 *     [--trace-ast]
 *     [--trace-symbol-table]
 *     [--trace-byte-code]
 *     SourceFileName
 */

int main(int argc,char* argv[])
{
  gengetopt_args_info siCommandLineArguments;
  if (cmdline_parser(argc, argv, &siCommandLineArguments) != 0)
  {
    exit(1);
  }

  if (siCommandLineArguments.inputs_num == 0)
  {
    cmdline_parser_print_help();
    exit(0);
  }

  OpenLogger("zlangc");
  SetLoggerDebugLevel(3);

  zlang::CZLangCompiler * pciCompiler = new __OPTION(_THROW)
          zlang::CZLangCompiler(siCommandLineArguments.trace_lexer_given,
                                siCommandLineArguments.trace_ast_given,
                                siCommandLineArguments.trace_symbol_table_given,
                                siCommandLineArguments.trace_code_given);

  // for each sourcefile specified on the command line
  //for(unsigned i = 0; i < siCommandLineArguments.inputs_num; ++i)
  //{
  //  std::cout << "source file: " << siCommandLineArguments.inputs[i] << std::endl;
  //}

  std::string stringSourceFileName = siCommandLineArguments.inputs[0];
  std::string stringObjectFileName;
  if (siCommandLineArguments.object_file_given)
  {
    stringObjectFileName = siCommandLineArguments.object_file_arg;
  }
  else
  {
    stringObjectFileName = stringSourceFileName.substr(0, stringSourceFileName.rfind('.')) + ".zo";
  }

  std::cout << "Compiling '" << stringSourceFileName << "' ..." << std::endl;
  pciCompiler->Compile(stringSourceFileName, stringObjectFileName);

  delete pciCompiler;
  exit(0);
}

