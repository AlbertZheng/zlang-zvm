/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/Exception.hpp,v $
 *
 * $Date: 2002/02/28 13:59:25 $
 *
 * $Revision: 1.4 $
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


#ifndef _ZLS_zfc_Exception_hpp_
#define _ZLS_zfc_Exception_hpp_

#include <zls/zfc/Manifest.h>
#include <stdexcept>


ZLS_BEGIN_NAMESPACE(zfc)


/**
 * @name 一些std::string constant.
 */
//@{
const std::string CstringLITERAL_OF_RUNTIME_ERROR("std::runtime_error");
const std::string CstringLITERAL_OF_LOGIC_ERROR("std::logic_error");
const std::string CstringLITERAL_OF_OVERFLOW_ERROR("std::overflow_error");
const std::string CstringLITERAL_OF_UNDERFLOW_ERROR("std::underflow_error");
const std::string CstringLITERAL_OF_OUT_OF_RANGE("std::out_of_range");
const std::string CstringLITERAL_OF_INVALID_ARGUMENT("std::invalid_argument");
//@}


/**
 * ZFC exception base class.
 *
 * @attention 编写Exception类时须注意：Exception类中的任何method不允许再抛出Exception
 * 到外界，否则会乱套了，因此Exception类的member要避免为std::string等，免得它们万一
 * throw std::bad_alloc，同时Exception类也要尽量简单，并且Exception类必须是可Copy的.
 */
class EBaseException {
  public:
    struct TWhat {
      private:
        const char * _pszFileName;
        const char * _pszFuncName;
        int          _nLineNumber;
        std::string  _stringWhat;

      public:
        const char * GetFileName() const
        { return _pszFileName; }

        const char * GetFunctionName() const
        { return _pszFuncName; }

        int GetLineNumber() const
        { return _nLineNumber; }

        const char * what() const
        { return _stringWhat.c_str(); }

        const std::string & GetWhat() const
        { return _stringWhat; }

        TWhat & operator=(const TWhat & rsi)
        {
          _pszFileName = rsi._pszFileName;
          _pszFuncName = rsi._pszFuncName;
          _nLineNumber = rsi._nLineNumber;
          _stringWhat = rsi._stringWhat;
          return *this;
        }

        TWhat(const TWhat & rsi)
        { operator=(rsi); }

        TWhat(const char * pszFileName,
              const char * pszFuncName,
              const int nLineNumber,
              const std::string & rstringWhat)
          : _pszFileName(pszFileName),
            _pszFuncName(pszFuncName),
            _nLineNumber(nLineNumber),
            _stringWhat(rstringWhat)
        { }

        TWhat(const char * pszFileName,
              const char * pszFuncName,
              const int nLineNumber,
              const char * pszWhat)
          : _pszFileName(pszFileName),
            _pszFuncName(pszFuncName),
            _nLineNumber(nLineNumber),
            _stringWhat(pszWhat)
        { }
    };

  protected:
    std::vector<TWhat> _vectorWhats;

  public:
    struct DumpToStandardOutput {
      private:
        const char * _pszIdent;

      public:
        DumpToStandardOutput(const char * pszIdent)
          : _pszIdent(pszIdent)
        { }

        void operator()(const TWhat & rsiWhat) const
        {
          std::cout << _pszIdent << ": " << rsiWhat.what() << std::endl;
        }
    };

    struct DumpToStandardError {
      private:
        const char * _pszIdent;

      public:
        DumpToStandardError(const char * pszIdent)
          : _pszIdent(pszIdent)
        { }

        void operator()(const TWhat & rsiWhat) const
        {
          std::cerr << _pszIdent << ": " << rsiWhat.what() << std::endl;
        }
    };

    /**
     * 得到内部的whats vector.
     *
     * @throw none.
     */
    const std::vector<TWhat> & GetWhats() const
    { return _vectorWhats; }

    template <class Dumper>
    void DumpWhats(const Dumper & rciDumper) const
    {
      for_each(_vectorWhats.begin(), _vectorWhats.end(), rciDumper);
    }


    /**
     * 向已有的EBaseException instance添加what信息，通常这用于rethrow或mapping
     * exception to another exception时.
     *
     * @throw none.
     */
    void AppendWhat(const char * pszFileName,
                    const char * pszFuncName,
                    const int nLineNumber,
                    const std::string & rstringMessage);

    /**
     * 向已有的EBaseException instance添加what信息，通常这用于rethrow或mapping
     * exception to another exception时.
     *
     * @throw none.
     */
    void AppendWhat(const char * pszFileName,
                    const char * pszFuncName,
                    const int nLineNumber,
                    const char * pszMessage);

    virtual const char * GetExceptionName() const throw() = 0;

    /**
     * 重实现std::exception的what().
     *
     * @brief 如果内部的whats vector有多个element，则只返回最内层的那个exception的what.
     */
    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    ;

    /**
     * Overload operator=().
     * 进行copy instance或mapping a exception to another exception.
     *
     * @throw none.
     */
    EBaseException & operator=(const EBaseException & rci);

    /**
     * Copy constructor.
     *
     * @throw none.
     */
    EBaseException(const EBaseException & rci)
    {
      operator=(rci);
    }

    /**
     * Constructor.
     *
     * @throw none.
     */
    EBaseException(const char * pszFileName,
                   const char * pszFuncName,
                   const int nLineNumber,
                   const std::string & rstringMessage)
    {
      AppendWhat(pszFileName, pszFuncName, nLineNumber, rstringMessage);
    }

    /**
     * Constructor.
     *
     * @throw none.
     */
    EBaseException(const char * pszFileName,
                   const char * pszFuncName,
                   const int nLineNumber,
                   const char * pszMessage)
    {
      AppendWhat(pszFileName, pszFuncName, nLineNumber, pszMessage);
    }

    /**
     * Destructor.
     *
     * @throw none.
     */
    virtual ~EBaseException()
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    { }
};

inline const char * EBaseException::GetExceptionName() const throw()
{
  return "zfc::EBaseException";
}


/******************************************************************************
 * 以下是EBaseException的派生类.
 ******************************************************************************/
/**
 * 该类用来特指“未意料到的、或不可能的错误引起我们的恐慌”.
 *
 * @note 通常用户自己认为是根本不可能（或不应该但由于Make mistakes而）发生的错误，
 * 理论上这个错误应该可以用assert()来断言的，但有时我们并不希望在低层直接abort()，
 * 而是希望由高层来进一步报告更详尽的错误发生缘由、位置，例如在我的ZLang的解释器
 * 中当低层代码发现一个非法的Type-Tag时，我希望高层代码能够告诉我现在是解释到ZLang
 * script中的哪一行才发生这个不可能的错误的.
 */
class EPanic : public std::exception, public EBaseException {
  public:
    /** Copy operator. */
    EPanic & operator=(const EPanic & rci)
    {
      std::exception::operator=(rci);
      EBaseException::operator=(rci);
      return *this;
    }

    /**
     * Mapping constructor.
     *
     * 用来将任何一种其它的Exception类instance映射成EPanic类instance，通常只用在
     * rethrow时.
     */
    EPanic(const EBaseException & rci)
      : std::exception(),
        EBaseException(rci)
    { }

    /** Copy constructor. */
    EPanic(const EPanic & rci)
      : std::exception(),
        EBaseException(rci)
    { }

    EPanic(const char * pszFileName,
           const char * pszFuncName,
           const int nLineNumber,
           const std::string & rstringMessage);

    EPanic(const char * pszFileName,
           const char * pszFuncName,
           const int nLineNumber,
           const char * pszMessage);

    virtual const char * GetExceptionName() const throw()
    {
      return "zfc::EPanic";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return EBaseException::what();
    }
};


/**
 * 该类用来指示“妄想进行非法的dynamic_cast<>()”.
 */
class EBadDynamicCast : public std::bad_cast, public EBaseException {
  public:
    /** Copy operator. */
    EBadDynamicCast & operator=(const EBadDynamicCast & rci)
    {
      std::bad_cast::operator=(rci);
      EBaseException::operator=(rci);
      return *this;
    }

    /** Copy constructor. */
    EBadDynamicCast(const EBadDynamicCast & rci)
      : std::bad_cast(),
        EBaseException(rci)
    { }

    /**
     * Constructor.
     *
     * @param rstringMessage 提示信息，这个信息通常应该是从std::bad_cast.what()得到的.
     */
    EBadDynamicCast(const char * pszFileName,
                    const char * pszFuncName,
                    const int nLineNumber,
                    const std::string & rstringMessage);

    /**
     * Constructor.
     *
     * @param pszMessage 提示信息，这个信息通常应该是从std::bad_cast.what()得到的.
     */
    EBadDynamicCast(const char * pszFileName,
                    const char * pszFuncName,
                    const int nLineNumber,
                    const char * pszMessage);

    virtual const char * GetExceptionName() const throw()
    {
      return "zfc::EBadDynamicCast";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return EBaseException::what();
    }
};


/**
 * 当我重载的::operator new()触发out of memory时可能throw这个类.
 *
 * @attention 保留内存的大小必须足够让EOutOfMemory来进行两次"Out of memory"串的copy
 * 和一次std::vector的push_back操作，否则被throw出的将是一个没有任何信息的EOutOfMemory
 * instance，这是因为在EBaseException::AppendWhat()中采用了"try{ } catch(...)"来保证
 * 在准备EOutOfMemory instance时不会再引起exception.
 */
class EOutOfMemory : public EBaseException, public std::bad_alloc {
  public:
    EOutOfMemory & operator=(const EOutOfMemory & rci)
    {
      std::bad_alloc::operator=(rci);
      EBaseException::operator=(rci);
      return *this;
    }

    EOutOfMemory(const EOutOfMemory & rci)
      : std::bad_alloc(),
        EBaseException(rci)
    { }

    EOutOfMemory(const char * pszFileName,
                 const char * pszFuncName,
                 const int nLineNumber)
      : std::bad_alloc(),
        EBaseException(pszFileName, pszFuncName, nLineNumber, "Out of memory")
    { }

    virtual const char * GetExceptionName() const throw()
    {
      return "zfc::EOutOfMemory";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return EBaseException::what();
    }
};


/******************************************************************************
 * 以下是std::runtime_error和zfc::EBaseException的派生类.
 ******************************************************************************/
/**
 * 调用某个OS routine时，该routine返回错误信息，于是调用者就throw这个exception.
 */
class ESystemCallFailure : public std::runtime_error, public EBaseException {
  private:
    /**
     * 发生Exception时，如果UNIX's errno值有效，则这个字段保存它.
     */
    int _nErrorNumber;

  public:
    int GetErrorNumber() const
    { return _nErrorNumber; }

    ESystemCallFailure & operator=(const ESystemCallFailure & rci)
    {
      std::runtime_error::operator=(rci);
      EBaseException::operator=(rci);
      return *this;
    }

    ESystemCallFailure(const ESystemCallFailure & rci)
      : std::runtime_error(CstringLITERAL_OF_RUNTIME_ERROR),
        EBaseException(rci)
    { }

    ESystemCallFailure(const char * pszFileName,
                       const char * pszFuncName,
                       const int nLineNumber,
                       const char * pszSystemCallName,
                       const int nErrorNumber);

    virtual const char * GetExceptionName() const throw()
    {
      return "zfc::ESystemCallFailure";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return EBaseException::what();
    }
};


/**
 * 该类用来指示“在Hash table中或其它类似的结构中查找元素失败，即查找不到”.
 */
class ENotFound : public std::runtime_error, public EBaseException {
  public:
    ENotFound & operator=(const ENotFound & rci)
    {
      std::runtime_error::operator=(rci);
      EBaseException::operator=(rci);
      return *this;
    }

    ENotFound(const ENotFound & rci)
      : std::runtime_error(CstringLITERAL_OF_RUNTIME_ERROR),
        EBaseException(rci)
    { }

    ENotFound(const char * pszFileName,
              const char * pszFuncName,
              const int nLineNumber,
              const std::string & rstringMessage)
      : std::runtime_error(CstringLITERAL_OF_RUNTIME_ERROR),
        EBaseException(pszFileName, pszFuncName, nLineNumber, rstringMessage)
    { }

    ENotFound(const char * pszFileName,
              const char * pszFuncName,
              const int nLineNumber,
              const char * pszMessage)
      : std::runtime_error(CstringLITERAL_OF_RUNTIME_ERROR),
        EBaseException(pszFileName, pszFuncName, nLineNumber, pszMessage)
    { }

    virtual const char * GetExceptionName() const throw()
    {
      return "zfc::ENotFound";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return EBaseException::what();
    }
};


/**
 * 该类用来通指“类的Constructor发生某些错误，而使构造Instance失败”.
 */
class EConstructorFailure : public std::runtime_error, public EBaseException {
  public:
    EConstructorFailure & operator=(const EConstructorFailure & rci)
    {
      std::runtime_error::operator=(rci);
      EBaseException::operator=(rci);
      return *this;
    }

    /** Mapping constructor. */
    EConstructorFailure(const EBaseException & rci)
      : std::runtime_error(CstringLITERAL_OF_RUNTIME_ERROR),
        EBaseException(rci)
    { }

    EConstructorFailure(const EConstructorFailure & rci)
      : std::runtime_error(CstringLITERAL_OF_RUNTIME_ERROR),
        EBaseException(rci)
    { }

    EConstructorFailure(const char * pszFileName,
                        const char * pszFuncName,
                        const int nLineNumber,
                        const std::string & rstringMessage)
      : std::runtime_error(CstringLITERAL_OF_RUNTIME_ERROR),
        EBaseException(pszFileName, pszFuncName, nLineNumber, rstringMessage)
    { }

    EConstructorFailure(const char * pszFileName,
                        const char * pszFuncName,
                        const int nLineNumber,
                        const char * pszMessage)
      : std::runtime_error(CstringLITERAL_OF_RUNTIME_ERROR),
        EBaseException(pszFileName, pszFuncName, nLineNumber, pszMessage)
    { }

    virtual const char * GetExceptionName() const throw()
    {
      return "zfc::EConstructorFailure";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return EBaseException::what();
    }
};


/**
 * Buffer上溢Exception.
 *
 * @note 通常用于输出操作往buffer里填写时（想象一下，往某个容器里灌入"水"，当容
 * 器满时就发生了"上溢Exception"）.
 */
class EOverflow : public std::overflow_error, public EBaseException {
  public:
    EOverflow & operator=(const EOverflow & rci)
    {
      std::overflow_error::operator=(rci);
      EBaseException::operator=(rci);
      return *this;
    }

    EOverflow(const EOverflow & rci)
      : std::overflow_error(CstringLITERAL_OF_OVERFLOW_ERROR),
        EBaseException(rci)
    { }

    EOverflow(const char * pszFileName,
              const char * pszFuncName,
              const int nLineNumber,
              const std::string & rstringMessage)
      : std::overflow_error(CstringLITERAL_OF_OVERFLOW_ERROR),
        EBaseException(pszFileName, pszFuncName, nLineNumber, rstringMessage)
    { }

    EOverflow(const char * pszFileName,
              const char * pszFuncName,
              const int nLineNumber,
              const char * pszMessage)
      : std::overflow_error(CstringLITERAL_OF_OVERFLOW_ERROR),
        EBaseException(pszFileName, pszFuncName, nLineNumber, pszMessage)
    { }

    virtual const char * GetExceptionName() const throw()
    {
      return "zfc::EOverflow";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return EBaseException::what();
    }
};


/**
 * Buffer下溢Exception.
 *
 * @note 通常用于输入操作时当buffer内容被读空时（想象一下，从某个容器里抽取"水"，
 * 当容器空时就发生了"下溢Exception"）.
 */
class EUnderflow : public std::underflow_error, public EBaseException {
  public:
    EUnderflow & operator=(const EUnderflow & rci)
    {
      std::underflow_error::operator=(rci);
      EBaseException::operator=(rci);
      return *this;
    }

    EUnderflow(const EUnderflow & rci)
      : std::underflow_error(CstringLITERAL_OF_UNDERFLOW_ERROR),
        EBaseException(rci)
    { }

    EUnderflow(const char * pszFileName,
               const char * pszFuncName,
               const int nLineNumber,
               const std::string & rstringMessage)
      : std::underflow_error(CstringLITERAL_OF_UNDERFLOW_ERROR),
        EBaseException(pszFileName, pszFuncName, nLineNumber, rstringMessage)
    { }

    EUnderflow(const char * pszFileName,
               const char * pszFuncName,
               const int nLineNumber,
               const char * pszMessage)
      : std::underflow_error(CstringLITERAL_OF_UNDERFLOW_ERROR),
        EBaseException(pszFileName, pszFuncName, nLineNumber, pszMessage)
    { }

    virtual const char * GetExceptionName() const throw()
    {
      return "zfc::EUnderflow";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return EBaseException::what();
    }
};


/******************************************************************************
 * 以下是std::logic_error和zfc::EBaseException的派生类.
 ******************************************************************************/
/**
 * 该类指示“派生类并没有"真正地"实现某个overload的virtual method（或根本就没有
 * 办法支持它，只是为了interface的完整性才overload了它），但用户以为是然后调用
 * 它，于是就发生了这个exception”.
 */
class EUnimplementedVirtualMethod : public std::logic_error, public EBaseException {
  public:
    EUnimplementedVirtualMethod & operator=(const EUnimplementedVirtualMethod & rci)
    {
      std::logic_error::operator=(rci);
      EBaseException::operator=(rci);
      return *this;
    }

    EUnimplementedVirtualMethod(const EUnimplementedVirtualMethod & rci)
      : std::logic_error(CstringLITERAL_OF_LOGIC_ERROR),
        EBaseException(rci)
    { }

    EUnimplementedVirtualMethod(const char * pszFileName,
                                const char * pszFuncName,
                                const int nLineNumber,
                                const std::string & rstringMessage);

    EUnimplementedVirtualMethod(const char * pszFileName,
                                const char * pszFuncName,
                                const int nLineNumber,
                                const char * pszMessage);

    virtual const char * GetExceptionName() const throw()
    {
      return "zfc::EUnimplementedVirtualMethod";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return EBaseException::what();
    }
};


/**
 * 调用某个method或function的参数不符合它的函数原形要求.
 */
class EInvalidArgument : public std::invalid_argument, public EBaseException {
  public:
    EInvalidArgument & operator=(const EInvalidArgument & rci)
    {
      std::invalid_argument::operator=(rci);
      EBaseException::operator=(rci);
      return *this;
    }

    EInvalidArgument(const EInvalidArgument & rci)
      : std::invalid_argument(CstringLITERAL_OF_INVALID_ARGUMENT),
        EBaseException(rci)
    { }

    EInvalidArgument(const char * pszFileName,
                     const char * pszFuncName,
                     const int nLineNumber,
                     const std::string & rstringMessage);

    EInvalidArgument(const char * pszFileName,
                     const char * pszFuncName,
                     const int nLineNumber,
                     const char * pszMessage);

    virtual const char * GetExceptionName() const throw()
    {
      return "zfc::EInvalidArgument";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return EBaseException::what();
    }
};


/**
 * 非法的state.
 *
 * @note 在不合适的时间，或用不正确的顺序调用某个method或function，可能throw这个exception.
 */
class EInvalidState : public std::logic_error, public EBaseException {
  public:
    EInvalidState & operator=(const EInvalidState & rci)
    {
      std::logic_error::operator=(rci);
      EBaseException::operator=(rci);
      return *this;
    }

    EInvalidState(const EInvalidState & rci)
      : std::logic_error(CstringLITERAL_OF_LOGIC_ERROR),
        EBaseException(rci)
    { }

    EInvalidState(const char * pszFileName,
                  const char * pszFuncName,
                  const int nLineNumber,
                  const std::string & rstringMessage);

    EInvalidState(const char * pszFileName,
                  const char * pszFuncName,
                  const int nLineNumber,
                  const char * pszMessage);

    virtual const char * GetExceptionName() const throw()
    {
      return "zfc::EInvalidState";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return EBaseException::what();
    }
};


/**
 * 下标越界错，可能上越或下越.
 *
 * @note 通常是在对容器类操作时可能throw这个exception.
 */
class EOutOfRange : public std::out_of_range, public EBaseException {
  public:
    EOutOfRange & operator=(const EOutOfRange & rci)
    {
      std::out_of_range::operator=(rci);
      EBaseException::operator=(rci);
      return *this;
    }

    EOutOfRange(const EOutOfRange & rci)
      : std::out_of_range(CstringLITERAL_OF_OUT_OF_RANGE),
        EBaseException(rci)
    { }

    EOutOfRange(const char * pszFileName,
                const char * pszFuncName,
                const int nLineNumber,
                const std::string & rstringMessage);

    EOutOfRange(const char * pszFileName,
                const char * pszFuncName,
                const int nLineNumber,
                const char * pszMessage);

    /**
     * Constructor.
     *
     * @param pszIndexName Index的名称.
     * @param iIndex 越界的Index值.
     * @param iMin 允许的最小Index值.
     * @param iMax 允许的最大Index值.
     */
    EOutOfRange(const char * pszFileName,
                const char * pszFuncName,
                const int nLineNumber,
                const char * pszIndexName,
                size_t iIndex,
                size_t iMin,
                size_t iMax);

    virtual const char * GetExceptionName() const throw()
    {
      return "zfc::EOutOfRange";
    }

    virtual const char * what() const
      #if defined(HAVE_CXX_STL) && !defined(HAVE_GNU_LIBSTDCXX_V2)
      throw ()
      #endif
    {
      return EBaseException::what();
    }
};


ZLS_END_NAMESPACE


#endif

