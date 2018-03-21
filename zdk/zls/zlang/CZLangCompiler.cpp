/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/CZLangCompiler.cpp,v $
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


#include <zls/zlang/CZLangCompiler.hpp>


// Begin namespace 'zlang::'
ZLS_BEGIN_NAMESPACE(zlang)


void CZLangCompiler::Compile(const std::string & rstringSourceFileName,
                             const std::string & rstringObjectFileName)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CZLangCompiler::Compile()");

  std::ifstream ifs(rstringSourceFileName.c_str());
  if (ifs)
  {
    zfc::CPipe ciPipeWrite, ciPipeError;

    pid_t pidPreprocessor = fork();
    if (pidPreprocessor < 0)
    {
      throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "fork", errno);
    }

    if (pidPreprocessor == 0)
    /************************************************************************
     * Now the new child process begin here.
     ************************************************************************/
    {
      // 关闭write pipe的read端，我只进行write
      ciPipeWrite.CloseRead();
      // 将write pipe的write端绑定到我的stdout，然后再关闭write pipe的write端
      ciPipeWrite.Dup2AndThenCloseWriteFileDescriptor(STDOUT_FILENO);

      // 关闭error pipe的read端，我只进行write
      ciPipeError.CloseRead();
      // 将error pipe的write端绑定到我的stderr，然后再关闭error pipe的write端
      ciPipeError.Dup2AndThenCloseWriteFileDescriptor(STDERR_FILENO);

      // 现在"gcc -E"的stdout即是write pipe的write端，
      // 而stderr即是error pipe的write端.
      execlp("gcc", "gcc", "-E", "-I./data", "-I.", "-x", "c", rstringSourceFileName.c_str(), 0);
      //< 如果execlp()返回了，则意味着失败

      throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "execlp", errno);
    }

    /************************************************************************
     * Now the original father process begin here.
     ************************************************************************/
    // 关闭write pipe的write端，我只进行read
    ciPipeWrite.CloseWrite();
    // 关闭error pipe的write端，我只进行read
    ciPipeError.CloseWrite();
    // 将write pipe的read端绑定到我的stdin，然后再关闭write pipe的read端
    ciPipeWrite.Dup2AndThenCloseReadFileDescriptor(STDIN_FILENO);

    // 2001/7/22: 发现采用pipe来通信有存在问题，即本来我的做法是Father process
    // 等待Child process结束后才开始读自己的stdin，因为我需要根据Child process
    // 的结束status来判断是否Child process在进行“预处理”时报告了源代码有错误
    // （例如：#include的文件不存在等）。但是如果一定要等待Child process结束后
    // 才开始读自己的stdin，则如果源代码很长的话，当Child process将kernel的pipe
    // buffer写满后，它必须也等待Father process将pipe buffer读完后才能继续写pipe，
    // 这时就出现了僵死状态，Father process要等待Child process结束，而Child process
    // 却也要等待Father process读pipe。
    //     一种解决方案是Father process不等待Child process结束了，而是直接立即读
    // pipe，但是为了判断Child process是否报告错误，则在CStandardInputBuffer::getChar()
    // 中，每当要读一个char之前就必须先判断Child process是否报告错误，如果错误了
    // 则立即停止读char，然后输出错误到stderr，如果没有错误则继续读char。这种解
    // 决方案不是很理想和优美，因为CStandardInputBuffer::CStandardInputBuffer()
    // 必须被修改传入CPipe、Child process id等信息。
    //     另一种解决方案是不采用pipe，而采用临时文件，Child process将预处理的
    // 结果写入一个临时文件，Father process等待Child process“正确”结束后再读
    // 这个临时文件。
/*
    ///> 等待preprocessor进程结束
    int nStatus;
    if (waitpid(pidPreprocessor, &nStatus, 0) < 0)
    {
      throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "waitpid", errno);
    }
    else
    {
      if (WIFEXITED(nStatus))
      // 如果preprocessor进程是用exit()退出的
      {
        if (WEXITSTATUS(nStatus) == 1)
        // 如果preprocessor进程的退出状态码是1，表示"gcc -E"报告source codes有错误
        {
          char aszBuffer[_POSIX_PIPE_BUF];
          do {
            ssize_t nBytes = ciPipeError.Read(aszBuffer, _POSIX_PIPE_BUF);
            if (nBytes > 0)
            {
              std::cerr.write(aszBuffer, nBytes);
            }
            else
            {
              break;
            }
          } while (true);

          exit(1);
        }
      }
      else
      {
        std::string stringError = "Preprocessor have some problems !";
        throw zfc::EPanic(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
      }
    }
*/
    // 现在preprocessor应该传回处理后的source codes了
    try {
      // 让antlr::CharScanner能够从stdin读
      CStandardInputBuffer ciLexerInputBuffer;

      // Create a scanner that reads from 'std::cin'
      zlang::ZLangLexer ciLexer(ciLexerInputBuffer);
      ciLexer.setFilename(rstringSourceFileName);

      // 跟踪Lexer给出的每个Token
      if (_bTraceLexer)
      {
        while (true) {
          antlr::RefToken autoToken = ciLexer.nextToken();
          if (autoToken->getType() == antlr::Token::EOF_TYPE)
            break;
          std::cout << autoToken->getText() << " : " << autoToken->getType() << std::endl;
        }
        return;
      }

      try {
        // Create a parser that reads from the scanner.
        zlang::ZLangParser ciParser(ciLexer);
        ciParser.setASTNodeFactory(zlang::CZLangAST::factory);
        ciParser.setFilename(rstringSourceFileName);

        // Pass1 parsing
        std::cout << "Pass1: Syntax parsing ..." << std::endl;
        ciParser.zlangScript();
        std::cout << "Pass1 done." << std::endl;

        zlang::CZLangAST_auto autoAST = ciParser.getAST();

        // 跟踪Parser产生的AST
        if (_bTraceAST)
        {
          zlang::CASTPrinter *pciPrinter = new __OPTION(_THROW) zlang::CASTPrinter();
          pciPrinter->pr_tree(static_cast<antlr::RefAST>(autoAST));
          delete pciPrinter;
        }

        // Pass2 parsing
        try {
          zlang::ZLangSymbolTableGenerator ciSymbolTableGenerator(rstringSourceFileName);
          std::cout << "Pass2: Generating symbol table ..." << std::endl;
          ciSymbolTableGenerator.zlangScript(autoAST);
          std::cout << "Pass2 done." << std::endl;

          zlang::CSymbolTable & rciSymbolTable = ciSymbolTableGenerator.GetSymbolTable();

          // 跟踪产生的Symbol table
          if (_bTraceSymbolTable)
          {
            rciSymbolTable.DumpDetail();
          }

          // Pass3 parsing
          try {
            zlang::ZLangCodeGenerator ciCodeGenerator(rstringSourceFileName, &rciSymbolTable);
            std::cout << "Pass3: Semantic parsing ..." << std::endl;
            ciCodeGenerator.zlangScript(autoAST);
            std::cout << "Pass3 done." << std::endl;

            // 跟踪产生的Byte code
            if (_bTraceByteCode)
            {
              ciCodeGenerator.DumpDetail();
            }

            std::cout << "Generating object file ..." << std::endl;
            zfc::CBinaryOutputFileStream bos(rstringObjectFileName.c_str());
            if (bos)
            {
              bos << ciCodeGenerator;
              std::cout << "Object file generated." << std::endl;
            }
            else
            {
              std::cerr << "Error: Couldn't open object file '" << rstringObjectFileName << "' !" << std::endl;
            }
          }
          catch (antlr::SemanticException & e)
          {
            std::cerr << "Pass3: " << e.toString() << std::endl;
          }
          catch (antlr::RecognitionException & e)
          {
            std::cerr << "Pass3: " << e.toString() << std::endl;
          }
        }
        catch (antlr::RecognitionException & e)
        {
          std::cerr << "Pass2: " << e.toString() << std::endl;
        }
      }
      catch (antlr::RecognitionException & e)
      {
        //std::cerr << "Pass1: " << e.toString() << std::endl;

        // 2001/5/18: 雇佣"gnu cpp"来进行预处理后，antlr::Parser却不能够从Lexer中得到
        // 正确的file name信息，因为antlr::Parser是从一个antlr::ParserSharedInputState
        // 被construct的，基本construct流程如下：
        //   antlr::Parser <-- antlr::ParserSharedInputState <-- antlr::TokenBuffer <-- antlr::TokenStream
        //                 需要                              需要                   需要       |
        //                                                                                     | 继承
        //                                                                                     |
        //                                                                              antlr::CharScanner
        //                                                                                     |
        //                                                                                     | 继承
        //                                                                                     |
        //                                                                              zlang::ZlangLexer
        // 由上面和antlr的代码可看到antlr::Parser中仅仅保存一个antlr::ParserSharedInputState
        // 指针，并没有保存Lexer，而antlr::Parser::getFilename()只是直接返回
        // antlr::ParserSharedInputState::filename而已，而这个
        // antlr::ParserSharedInputState::filename是通过antlr::Parser::setFilename()
        // 来被设置的，因此如果一定要让antlr::Parser::getFilename()返回的是正确的
        // file name信息，则只能采用Hack的办法：将antlr::Parser::getFilename()改
        // 为virtual method，然后在zlang::ZlangParser中重载它，同时还要自己增加一个
        // zlang::ZlangParser::ZLangParser(const antlr::CharScanner &)的constructor，
        // 它将在zlang::ZlangParser内部保存一个antlr::CharScanner指针来接收zlang::ZlangLexer，
        // 这样zlang::ZlangParser::getFilename()就能够通过这个指针来得到正确的
        // file name信息了！
        //
        // 太累了，这种办法既要Hack antlr，又要增加constructor，因此后来我采用下面的
        // 这种简单的方法来报告正确的file name信息：

        std::cerr << "Pass1: " << ciLexer.getFilename() << ": " << ciLexer.getLine()
                  << ": " << e.getErrorMessage() << std::endl;
                     //< getErrorMessage()没有打印file name:line信息
      }
    }
    catch (antlr::TokenStreamRecognitionException & e1)
    {
           // 采用下面这条代码可以报告出错的行号信息
      std::cerr << "Lexer: " << e1.recog.toString() << std::endl;
      std::cerr << "Lexer: " << e1.what() << std::endl;
    }
    catch (zfc::EBaseException & e2)
    {
      e2.DumpWhats(zfc::EBaseException::DumpToStandardError("zlangc"));
    }
    catch (std::exception & e3)
    {
      std::cerr << "zlangc: Unexpected exception: " << e3.what() << std::endl;
    }
  }
  else
  {
    std::cerr << "Error: Could not open source file '" << rstringSourceFileName << "' !" << std::endl;
  }
}


// 发现将pipe的read端绑定到我的stdin后，如果采用C++的std::cin来读取，则却读不
// 到任何字符；而如果采用C的系统调用read(STDIN_FILENO, ...)在，则完全正确。
// 我也搞不懂为什么，没有办法，为了让antlr::CharScanner能够从stdin读，因此我只
// 能特地编写了个CStandardInputBuffer类。

/* C方式读完全正确
char aszBuffer[_POSIX_PIPE_BUF];
do {
  ssize_t nBytes = read(STDIN_FILENO, aszBuffer, _POSIX_PIPE_BUF);
  if (nBytes > 0)
  {
    std::cout.write(aszBuffer, nBytes);
  }
  else
  {
    break;
  }
} while (true);
*/

/* C++方式读却完全失败，一个字符都没读到
//std::ios_base::sync_with_stdio(false);
do {
  std::cin.read(aszBuffer, _POSIX_PIPE_BUF);
  ssize_t nBytes = std::cin.gcount();
  if (nBytes > 0)
  {
    std::cout.write(aszBuffer, nBytes);
  }
  else
  {
    break;
  }
} while(true);
*/


ZLS_END_NAMESPACE

