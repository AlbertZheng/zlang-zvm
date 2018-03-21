/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CBinaryString.hpp,v $
 *
 * $Date: 2002/02/28 13:59:25 $
 *
 * $Revision: 1.6 $
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


#ifndef _ZLS_zfc_CBinaryString_hpp_
#define _ZLS_zfc_CBinaryString_hpp_

#include <zls/zfc/Manifest.h>
#if defined(HAVE_CXX_STL) && (defined(HAVE_GNU_LIBSTDCXX_V2) || defined(HAVE_GNU_LIBSTDCXX_V3))
  #if defined(HAVE_GNU_LIBSTDCXX_V2)
    #include <rope>
  #else
    #if defined(__GNUC__) && __GNUC__ == 3
      #if __GNUC_MINOR__ == 0 && (__GNUC_PATCHLEVEL__ == 1 || __GNUC_PATCHLEVEL__ == 2)  // If GCC-3.0.1or2
        //
        // 从"/usr/local/lib/gcc-lib/i386-portbld-freebsd4.3/3.0.1/include/g++/i386-portbld-freebsd4.3/
        // bits/c++-config.h"中可知道GCC-3.0.1在FreeBSD-4.3上被配置为"__STL_GTHREADS"
        //
        // 而按照<bits/stl_threads.h>中的下面这段话，我必须patch一个_Atomic_swap，否则<ext/rope>不能被编译过去.
        //
        // #ifdef __STL_GTHREADS
        // // We don't provide an _Atomic_swap in this configuration.  This only
        // // affects the use of ext/rope with threads.  Someone could add this
        // // later, if required.  You can start by cloning the __STL_PTHREADS
        // // path while making the obvious changes.  Later it could be optimized
        // // to use the atomicity.h abstraction layer from libstdc++-v3.
        // #else
        //
        // 下面这段patch是从<bits/stl_threads.h>中的"# elif defined(__STL_PTHREADS)"段cloning来的.
        //

        ZLS_BEGIN_NAMESPACE(std)
        // We use a template here only to get a unique initialized instance.
        template<int __dummy>
        struct _Swap_lock_struct {
            static pthread_mutex_t _S_swap_lock;
        };

        template<int __dummy>
        pthread_mutex_t
        _Swap_lock_struct<__dummy>::_S_swap_lock = PTHREAD_MUTEX_INITIALIZER;

        // This should be portable, but performance is expected
        // to be quite awful.  This really needs platform specific
        // code.
        inline unsigned long _Atomic_swap(unsigned long * __p, unsigned long __q) {
            pthread_mutex_lock(&_Swap_lock_struct<0>::_S_swap_lock);
            unsigned long __result = *__p;
            *__p = __q;
            pthread_mutex_unlock(&_Swap_lock_struct<0>::_S_swap_lock);
            return __result;
        }
        ZLS_END_NAMESPACE
      #else
        #error "Unsupported GCC version !"
      #endif
    #endif
    #include <ext/rope>
  #endif
#else
  #error "'std::rope' just is SGI STL extension !"
#endif


// Begin namespace 'zfc::'
ZLS_BEGIN_NAMESPACE(zfc)


/**
 * Binary String类.
 *
 * @note CBinaryString can handles binary data, which can contain embedded '\0'
 * characters.
 */
class CBinaryString : public std::rope<UCHAR> {
  protected:
    /*
    CBinaryString(_RopeRep* __t)
      : std::rope<UCHAR>(__t)
    { }
    */

  public:
    std::string ToString() const;

    /**
     * @name 从char的相关型construct，这是为了简化用户使用reinterpret_cast<>.
     */
    //@{
    CBinaryString(const char* __s)
      : std::rope<UCHAR>(reinterpret_cast<const UCHAR *>(__s))
    { }

    CBinaryString(const char* __s, size_t __len)
      : std::rope<UCHAR>(reinterpret_cast<const UCHAR *>(__s), __len)
    { }

    CBinaryString(char __c)
      : std::rope<UCHAR>(static_cast<UCHAR>(__c))
    { }

    CBinaryString(size_t __n, char __c)
      : std::rope<UCHAR>(__n, static_cast<UCHAR>(__c))
    { }
    //@}

    /**
     * @name 从UCHAR的相关型construct.
     */
    //@{
    CBinaryString(const UCHAR* __s)
      : std::rope<UCHAR>(__s)
    { }

    CBinaryString(const UCHAR* __s, size_t __len)
      : std::rope<UCHAR>(__s, __len)
    { }

    CBinaryString(const const_iterator& __s, const const_iterator& __e)
      : std::rope<UCHAR>(__s, __e)
    { }

    CBinaryString(UCHAR __c)
      : std::rope<UCHAR>(__c)
    { }

    CBinaryString(size_t __n, UCHAR __c)
      : std::rope<UCHAR>(__n, __c)
    { }
    //@}

    CBinaryString(const iterator& __s, const iterator& __e)
      : std::rope<UCHAR>(__s, __e)
    { }

    // Construct a std::rope from a function that can compute its members
    CBinaryString(std::char_producer<UCHAR> *__fn, size_t __len, bool __delete_fn)
      : std::rope<UCHAR>(__fn, __len, __delete_fn)
    { }

    CBinaryString(const CBinaryString& __x)
      : std::rope<UCHAR>(__x)
    { }

    CBinaryString(const std::rope<UCHAR>& __x)
      : std::rope<UCHAR>(__x)
    { }

    CBinaryString()
      : std::rope<UCHAR>()
    { }

    CBinaryString & operator=(const CBinaryString & __x)
    {
      std::rope<UCHAR>::operator=(__x);
      return *this;
    }
};


/**
 * @name zfc::CBinaryString toolkit routines.
 */
//@{
#if defined(HAVE_GNU_LIBSTDCXX_V2)
ostream & operator<<(ostream & __o, const CBinaryString& __r)
#else
template<class _CharT, class _Traits>
std::basic_ostream<_CharT, _Traits>& operator<<(std::basic_ostream<_CharT, _Traits>& __o,
                                                const CBinaryString& __r)
#endif
{
  if (__r.size() > 0)
  // 当为rope<非char或非wchar_t>时，如果size()等于0则会在ropeimpl.h中如下这行：
  //    if (!__is_simple) __o.width(__w/__rope_len);
  // 产生Floating pointer exception !
  {
    #if defined(__GNUC__) && __GNUC__ == 3
      #if __GNUC_MINOR__ == 0 && (__GNUC_PATCHLEVEL__ == 1 || __GNUC_PATCHLEVEL__ == 2)
        const std::rope<UCHAR> & __rciTempRope = __r;
        return __o << __rciTempRope;
        // GCC-3.0.1好象还是有点问题，采用下面的代码就抱怨找不到operator<<(...,std::rope<...>&)，
        // 注意：不是抱怨找不到std::operator<<(...,std::rope<...>&).
        //   return std::operator<<(__o, __r);
      #else
        #error "Unsupported GCC version !"
      #endif
    #else
      return std::operator<<(__o, __r);
    #endif
  }
  else
  {
    return __o;
  }
}


inline CBinaryString operator+(const CBinaryString& __left, const char* __right)
{
/*
  size_t __rlen = std::rope<UCHAR>::_S_char_ptr_len(reinterpret_cast<const UCHAR *>(__right));
  return CBinaryString(
   CBinaryString::_S_concat_char_iter(
       __left._M_tree_ptr,
       reinterpret_cast<const UCHAR *>(__right),
       __rlen));
  */
  return std::operator+(__left, reinterpret_cast<const UCHAR *>(__right));
}


inline CBinaryString & operator+=(CBinaryString & __left, const char * __right)
{
  __left.append(reinterpret_cast<const UCHAR *>(__right));
  return __left;
}


/**
 *  CBinaryString的hash function.
 */
struct MakeBinaryStringHash {
/*
  inline size_t operator()(const CBinaryString & __s) const
  {
    unsigned long __h = 0;
    for (int i=0; i < __s.size(); ++i)
      __h = 5*__h + __s[i];

    return size_t(__h);
  }
*/
  inline size_t operator()(const CBinaryString & __s) const
  {
    unsigned long __h = 0;
    for (CBinaryString::const_iterator i = __s.begin(); i != __s.end(); ++i)
      __h = 5*__h + *i;

    return size_t(__h);
  }
};
//@}


/**
 * @name zfc::CBinaryString的各种转换函数（大小写转换、数值转换、裁剪）.
 */
//@{
CBinaryString IPv4AddressToBinaryString(NUDWORD nudw);
inline CBinaryString IPv4AddressToBinaryString(struct in_addr siAddress)
{
 return IPv4AddressToBinaryString(siAddress.s_addr);
}

CBinaryString UQWORDToBinaryString(UQWORD uqw, int nBase);
CBinaryString SQWORDToBinaryString(SQWORD sqw, int nBase);

CBinaryString UDWORDToBinaryString(UDWORD udw, int nBase);
CBinaryString SDWORDToBinaryString(SDWORD sdw, int nBase);

#if SIZEOF_INT == SIZEOF_LONG
CBinaryString UnsignedLongToBinaryString(unsigned long ul, int nBase);
CBinaryString LongToBinaryString(long l, int nBase);
#endif

CBinaryString UWORDToBinaryString(UWORD uw, int nBase);
CBinaryString SWORDToBinaryString(SWORD sw, int nBase);

CBinaryString FloatToBinaryString(float f);
CBinaryString DoubleToBinaryString(double df);

void RightTrimBinaryString(CBinaryString & rbstring, char chWhichTrimed);


inline CBinaryString operator+(const CBinaryString & rbstringLeft, UQWORD uqwRight)
{
  return rbstringLeft + UQWORDToBinaryString(uqwRight, 10);
}

inline CBinaryString operator+(const CBinaryString & rbstringLeft, SQWORD sqwRight)
{
  return rbstringLeft + SQWORDToBinaryString(sqwRight, 10);
}

inline CBinaryString operator+(const CBinaryString & rbstringLeft, UDWORD udwRight)
{
  return rbstringLeft + UDWORDToBinaryString(udwRight, 10);
}

inline CBinaryString operator+(const CBinaryString & rbstringLeft, SDWORD sdwRight)
{
  return rbstringLeft + SDWORDToBinaryString(sdwRight, 10);
}

#if SIZEOF_INT == SIZEOF_LONG
inline CBinaryString operator+(const CBinaryString & rbstringLeft, unsigned long ulRight)
{
  return rbstringLeft + UDWORDToBinaryString(static_cast<UDWORD>(ulRight), 10);
}

inline CBinaryString operator+(const CBinaryString & rbstringLeft, long lRight)
{
  return rbstringLeft + SDWORDToBinaryString(static_cast<SDWORD>(lRight), 10);
}
#endif

inline CBinaryString operator+(const CBinaryString & rbstringLeft, UWORD uwRight)
{
  return rbstringLeft + UWORDToBinaryString(uwRight, 10);
}

inline CBinaryString operator+(const CBinaryString & rbstringLeft, SWORD swRight)
{
  return rbstringLeft + SWORDToBinaryString(swRight, 10);
}

inline CBinaryString operator+(const CBinaryString & rbstringLeft, float fRight)
{
  return rbstringLeft + FloatToBinaryString(fRight);
}

inline CBinaryString operator+(const CBinaryString & rbstringLeft, double dfRight)
{
  return rbstringLeft + DoubleToBinaryString(dfRight);
}
//@}


ZLS_END_NAMESPACE


#endif

