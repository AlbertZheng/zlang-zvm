/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/Toolkit.hpp,v $
 *
 * $Date: 2001/11/14 17:25:10 $
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


#ifndef _ZLS_zfc_Toolkit_hpp_
#define _ZLS_zfc_Toolkit_hpp_

#include <zls/zfc/Toolkit.h>


ZLS_BEGIN_NAMESPACE(std)

/**
 * 为string计算Hash值（我扩充的STL遗漏的一些function objects）.
 */
#if defined(HAVE_CXX_STL) && defined(HAVE_GNU_LIBSTDCXX_V2)
__STL_TEMPLATE_NULL
#else
template<>
#endif
struct hash<string>
{
  inline size_t operator()(const string & __s) const
  {
    return __stl_hash_string(__s.c_str());
  }
};

ZLS_END_NAMESPACE



ZLS_BEGIN_NAMESPACE(zfc)


/**
 * @name 我扩充的STL遗漏的一些function objects.
 */
//@{
template <class _Ret, class _Tp, class _Arg1, class _Arg2>
class mem_fun2_t {
public:
  explicit mem_fun2_t(_Ret (_Tp::*__pf)(_Arg1,_Arg2)) : _M_f(__pf) {}
  _Ret operator()(_Tp* __p, _Arg1 __x1, _Arg2 __x2) const { return (__p->*_M_f)(__x1, __x2); }
private:
  _Ret (_Tp::*_M_f)(_Arg1,_Arg2);
};

template <class _Ret, class _Tp, class _Arg1, class _Arg2>
class const_mem_fun2_t {
public:
  explicit const_mem_fun2_t(_Ret (_Tp::*__pf)(_Arg1,_Arg2) const) : _M_f(__pf) {}
  _Ret operator()(const _Tp* __p, _Arg1 __x1, _Arg2 __x2) const
    { return (__p->*_M_f)(__x1, __x2); }
private:
  _Ret (_Tp::*_M_f)(_Arg1,_Arg2) const;
};

/**
 * 我自己扩展一种mem_fun()，它可以多接收额外的两个参数.
 */
template <class _Ret, class _Tp, class _Arg1, class _Arg2>
inline mem_fun2_t<_Ret,_Tp,_Arg1,_Arg2> mem_fun(_Ret (_Tp::*__f)(_Arg1,_Arg2))
  { return mem_fun2_t<_Ret,_Tp,_Arg1,_Arg2>(__f); }

/**
 * 我自己扩展一种mem_fun() const，它可以多接收额外的两个参数.
 */
template <class _Ret, class _Tp, class _Arg1, class _Arg2>
inline const_mem_fun2_t<_Ret,_Tp,_Arg1,_Arg2> mem_fun(_Ret (_Tp::*__f)(_Arg1,_Arg2) const)
  { return const_mem_fun2_t<_Ret,_Tp,_Arg1,_Arg2>(__f); }


/**
 * Apply a function to every element of a range.
 *
 * @note 这是我自己扩展一种for_each()，它可以多接收额外的一个参数.
 */
template <class _InputIter, class _Function, class _Arg1>
_Function for_each(_InputIter __first, _InputIter __last, _Function __f, _Arg1 __a1) {
  for ( ; __first != __last; ++__first)
    __f(*__first, __a1);
  return __f;
}

/**
 * Apply a function to every element of a range.
 *
 * @note 这是我自己扩展一种for_each()，它可以多接收额外的两个参数.
 */
template <class _InputIter, class _Function, class _Arg1, class _Arg2>
_Function for_each(_InputIter __first, _InputIter __last, _Function __f, _Arg1 __a1, _Arg2 __a2) {
  for ( ; __first != __last; ++__first)
    __f(*__first, __a1, __a2);
  return __f;
}
//@}


/**
 * @name std::string的各种转换函数（大小写转换、数值转换、裁剪）.
 */
//@{
/**
 * 将用NUDWORD表示的IPv4 address转换为"a1.a2.a3.a4"的串格式.
 * @attention 这个函数完成与inet_ntoa()类似的功能，但是其却是thread安全的.
 */
std::string IPv4AddressToString(NUDWORD nudwAddress);

/**
 * 将用struct in_addr表示的IPv4 address转换为"a1.a2.a3.a4"的串格式.
 * @attention 这个函数完成与inet_ntoa()类似的功能，但是其却是thread安全的.
 */
inline std::string IPv4AddressToString(struct in_addr siAddress)
{
  return IPv4AddressToString(siAddress.s_addr);
}

std::string UQWORDToString(UQWORD uqw, int nBase);
std::string SQWORDToString(SQWORD sqw, int nBase);

std::string UDWORDToString(UDWORD udw, int nBase);
std::string SDWORDToString(SDWORD sdw, int nBase);
#if SIZEOF_INT == SIZEOF_LONG
std::string UnsignedLongToString(unsigned long ul, int nBase);
std::string LongToString(long l, int nBase);
#endif

std::string UWORDToString(UWORD uw, int nBase);
std::string SWORDToString(SWORD sw, int nBase);

std::string FloatToString(float f);
std::string DoubleToString(double df);


/**
 * Change everything into upper case.
 */
template<typename _CharT, typename _Traits, typename _Alloc>
inline void UpperString(std::basic_string<_CharT, _Traits, _Alloc> & rstring)
{
  std::transform(rstring.begin(), rstring.end(), rstring.begin(), toupper);
}

/**
 * Change everything into lower case.
 */
template<typename _CharT, typename _Traits, typename _Alloc>
inline void LowerString(std::basic_string<_CharT, _Traits, _Alloc> & rstring)
{
  std::transform(rstring.begin(), rstring.end(), rstring.begin(), tolower);
}

/**
 * Change everything back into upper case, but store the result in a different string.
 *
 * @param rstringSource 源string
 * @param rstringDestination 目的string.
 */
template<typename _CharT, typename _Traits, typename _Alloc>
inline void UpperString(const std::basic_string<_CharT, _Traits, _Alloc> & rstringSource,
                        std::basic_string<_CharT, _Traits, _Alloc> & rstringDestination)
{
  rstringDestination.reserve(rstringSource.size());
  std::transform(rstringSource.begin(), rstringSource.end(), rstringDestination.begin(), toupper);
}

/**
 * Change everything back into upper case, but store the result in a different string.
 *
 * @param rstringSource 源string
 * @param rstringDestination 目的string.
 */
template<typename _CharT, typename _Traits, typename _Alloc>
inline void LowerString(const std::basic_string<_CharT, _Traits, _Alloc> & rstringSource,
                        std::basic_string<_CharT, _Traits, _Alloc> & rstringDestination)
{
  rstringDestination.reserve(rstringSource.size());
  std::transform(rstringSource.begin(), rstringSource.end(), rstringDestination.begin(), tolower);
}

//void RightTrimString(std::string & rstring, char chWhichTrimed);

/**
 * Left trim leading char.
 */
template<typename _CharT, typename _Traits, typename _Alloc>
inline void LeftTrimString(std::basic_string<_CharT, _Traits, _Alloc> & rstring,
                           _CharT chWhichTrimed)
{
  std::basic_string<_CharT, _Traits, _Alloc>::size_type nStart = rstring.find_first_not_of(chWhichTrimed);
  rstring.erase(0, nStart);
}

/**
 * Right trim trailing char.
 */
template<typename _CharT, typename _Traits, typename _Alloc>
inline void RightTrimString(std::basic_string<_CharT, _Traits, _Alloc> & rstring,
                            _CharT chWhichTrimed)
{
  std::basic_string<_CharT, _Traits, _Alloc>::size_type nStart = rstring.find_last_not_of(chWhichTrimed);
  rstring.erase(nStart + 1);
}

/**
 * 对两个std::string进行"不区分大小写"的比较.
 * @param rstring1 串1.
 * @param rstring2 串2.
 * @return 0为相等，-1为串1小于串2，1为串1大于串2.
 */
template<typename _CharT, typename _Traits, typename _Alloc>
int StringCaseInsensitiveCompare(const std::basic_string<_CharT, _Traits, _Alloc> & rstring1,
                                 const std::basic_string<_CharT, _Traits, _Alloc> & rstring2)
{
  size_t i, l1, l2;

  l1 = rstring1.size();
  l2 = rstring2.size();
  if (l1 != l2)
  {
    return (l1 > l2 ? 1 : -1);
  }

  for (i = 0; i < l1; ++i)
  {
    int c1 = tolower(rstring1[i]);
    int c2 = tolower(rstring2[i]);
    if (c1 == c2)
      continue;
    return (c1 > c2 ? 1 : -1);
  }
  return 0;
}

/**
 * 判断一个std::string中的所有字母字符是否都是小写形式的.
 * @param rstring 串.
 * @return true是.
 * @attention 如果串中有非字母字符，则skip它然后继续检查.
 */
template<typename _CharT, typename _Traits, typename _Alloc>
bool StringIsLowerCase(const std::basic_string<_CharT, _Traits, _Alloc> & rstring)
{
  std::basic_string<_CharT, _Traits, _Alloc>::const_iterator it;
  for (it = rstring.begin(); it != rstring.end(); ++it)
  {
    _CharT c1 = *it;
    if (isalpha(c1) && !islower(c1))
    {
      return false;
    }
  }
  return true;
}

/**
 * 判断一个std::string中的所有字母字符是否都是大写形式的.
 * @param rstring 串.
 * @return true是.
 * @attention 如果串中有非字母字符，则skip它然后继续检查.
 */
template<typename _CharT, typename _Traits, typename _Alloc>
bool StringIsUpperCase(const std::basic_string<_CharT, _Traits, _Alloc> & rstring)
{
  std::basic_string<_CharT, _Traits, _Alloc>::const_iterator it;
  for (it = rstring.begin(); it != rstring.end(); ++it)
  {
    _CharT c1 = *it;
    if (isalpha(c1) && !isupper(c1))
    {
      return false;
    }
  }
  return true;
}


inline std::string operator+(const std::string & rstringLeft, UQWORD uqwRight)
{
  return(rstringLeft + UQWORDToString(uqwRight, 10));
}

inline std::string operator+(const std::string & rstringLeft, SQWORD sqwRight)
{
  return(rstringLeft + SQWORDToString(sqwRight, 10));
}

inline std::string operator+(const std::string & rstringLeft, UDWORD udwRight)
{
  return(rstringLeft + UDWORDToString(udwRight, 10));
}

inline std::string operator+(const std::string & rstringLeft, SDWORD sdwRight)
{
  return(rstringLeft + SDWORDToString(sdwRight, 10));
}

#if SIZEOF_INT == SIZEOF_LONG
inline std::string operator+(const std::string & rstringLeft, unsigned long ulRight)
{
  return(rstringLeft + UDWORDToString((UDWORD)ulRight, 10));
}

inline std::string operator+(const std::string & rstringLeft, long lRight)
{
  return(rstringLeft + SDWORDToString((SDWORD)lRight, 10));
}
#endif

inline std::string operator+(const std::string & rstringLeft, UWORD uwRight)
{
  return(rstringLeft + UWORDToString(uwRight, 10));
}

inline std::string operator+(const std::string & rstringLeft, SWORD swRight)
{
  return(rstringLeft + SWORDToString(swRight, 10));
}

inline std::string operator+(const std::string & rstringLeft, float fRight)
{
  return(rstringLeft + FloatToString(fRight));
}

inline std::string operator+(const std::string & rstringLeft, double dfRight)
{
  return(rstringLeft + DoubleToString(dfRight));
}


inline std::string & operator+=(std::string & rstringLeft, UQWORD uqwRight)
{
  rstringLeft += UQWORDToString(uqwRight, 10);
  return rstringLeft;
}

inline std::string & operator+=(std::string & rstringLeft, SQWORD sqwRight)
{
  rstringLeft += SQWORDToString(sqwRight, 10);
  return rstringLeft;
}

inline std::string & operator+=(std::string & rstringLeft, UDWORD udwRight)
{
  rstringLeft += UDWORDToString(udwRight, 10);
  return rstringLeft;
}

inline std::string & operator+=(std::string & rstringLeft, SDWORD sdwRight)
{
  rstringLeft += SDWORDToString(sdwRight, 10);
  return rstringLeft;
}

#if SIZEOF_INT == SIZEOF_LONG
inline std::string & operator+=(std::string & rstringLeft, unsigned long ulRight)
{
  rstringLeft += UDWORDToString((UDWORD)ulRight, 10);
  return rstringLeft;
}

inline std::string & operator+=(std::string & rstringLeft, long lRight)
{
  rstringLeft += SDWORDToString((SDWORD)lRight, 10);
  return rstringLeft;
}
#endif

inline std::string & operator+=(std::string & rstringLeft, UWORD uwRight)
{
  rstringLeft += UWORDToString(uwRight, 10);
  return rstringLeft;
}

inline std::string & operator+=(std::string & rstringLeft, SWORD swRight)
{
  rstringLeft += SWORDToString(swRight, 10);
  return rstringLeft;
}

inline std::string & operator+=(std::string & rstringLeft, float fRight)
{
  rstringLeft += FloatToString(fRight);
  return rstringLeft;
}

inline std::string & operator+=(std::string & rstringLeft, double dfRight)
{
  rstringLeft += DoubleToString(dfRight);
  return rstringLeft;
}
//@}


/**
 * 类似与C的strtok()函数，将一个string按照指定的分割符分解为多个string，然后存放
 * 到一个用户指定的container中.
 */
template <typename StringType, typename Container>
void StringToken(Container & container, StringType const & in,
                 const char * const delimiters = " \t\n")
{
    const typename StringType::size_type len = in.length();
          typename StringType::size_type i = 0;

    while ( i < len )
    {
        // eat leading whitespace
        i = in.find_first_not_of (delimiters, i);
        if (i == StringType::npos)
            return;   // nothing left but white space

        // find the end of the token
        typename StringType::size_type j = in.find_first_of (delimiters, i);

        // push token
        if (j == StringType::npos) {
            container.push_back (in.substr(i));
            return;
        } else
            container.push_back (in.substr(i, j-i));

        // set up for next loop
        i = j + 1;
    }
}


/**
 * 一个可用来跟踪function进出的工具class.
 */
class CInOutTracer {
  private:
    /** Forbidden operator new(). */
    void * operator new(size_t size);

    std::string _stringFunctionName;

  public:
    static int SnInDepth;
    static void Ident()
    {
      for (int i = 0; i < SnInDepth; i++ )
      {
	std::cout << "  ";
      }
    }

    CInOutTracer(const char * pszFunctionName)
      : _stringFunctionName(pszFunctionName)
    {
      ++SnInDepth;
      Ident();
      std::cout << SnInDepth << " > " << _stringFunctionName << std::endl;
    }

    ~CInOutTracer()
    {
      Ident();
      std::cout << SnInDepth << " < " << _stringFunctionName << std::endl;
      --SnInDepth;
    }
};


ZLS_END_NAMESPACE

/*
 * 没有这两行则我overload的zfc::operator+(std::string, ...)和
 * zfc::operator+=(std::string, ...)不能被其它namespace中的代码所透明使用，
 * 可是std::operator+(std::string,...)等也没被输出呀，它们是怎么回事呀？
 */
ZLS_USING_NAME(zfc::operator+)
ZLS_USING_NAME(zfc::operator+=)


#endif

