/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CProtocolPort.hpp,v $
 *
 * $Date: 2001/11/14 18:29:37 $
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


#ifndef _ZLS_zvm_CProtocolPort_hpp_
#define _ZLS_zvm_CProtocolPort_hpp_

#include <zls/zfc/CBinaryString.hpp>
#include <zls/zfc/CBinaryInputFileStream.hpp>
#include <zls/zfc/CBinaryOutputFileStream.hpp>
#include <zls/zvm/Manifest.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


/**
 * 抽象Internet protocol port.
 */
class CProtocolPort {
  private:
    UWORD _uwProtocolType;  /**< IPPROTO_TCP or IPPROTO_UDP */
    PPORT _nPortNumber;

  public:
    UWORD GetProtocolType() const
    {
      return(_uwProtocolType);
    }

    PPORT GetPortNumber() const
    {
      return(_nPortNumber);
    }

    void Set(UWORD uwProtocolType, PPORT nPortNumber)
    {
      _uwProtocolType = uwProtocolType;
      _nPortNumber = nPortNumber;
    }

    CProtocolPort & operator=(const CProtocolPort & rciRight)
    {
      _uwProtocolType = rciRight._uwProtocolType;
      _nPortNumber = rciRight._nPortNumber;
      return(*this);
    }

    bool operator==(const CProtocolPort & rciRight) const
    {
      return(_uwProtocolType == rciRight._uwProtocolType &&
             _nPortNumber == rciRight._nPortNumber);
    }

    bool operator!=(const CProtocolPort & rciRight) const
    {
      return(_uwProtocolType != rciRight._uwProtocolType ||
             _nPortNumber != rciRight._nPortNumber);
    }

    /**
     * operator<().
     *
     * @attention "协议"必须相同，否则比较结果始终为false.
     */
    bool operator<(const CProtocolPort & rciRight) const
    {
      return (_uwProtocolType == rciRight._uwProtocolType &&
              _nPortNumber < rciRight._nPortNumber);
    }

    /**
     * operator<=().
     *
     * @attention "协议"必须相同，否则比较结果始终为false.
     */
    bool operator<=(const CProtocolPort & rciRight) const
    {
      return (_uwProtocolType == rciRight._uwProtocolType &&
              _nPortNumber <= rciRight._nPortNumber);
    }

    /**
     * operator>().
     *
     * @attention "协议"必须相同，否则比较结果始终为false.
     */
    bool operator>(const CProtocolPort & rciRight) const
    {
      return (_uwProtocolType == rciRight._uwProtocolType &&
              _nPortNumber > rciRight._nPortNumber);
    }

    /**
     * operator>=().
     *
     * @attention "协议"必须相同，否则比较结果始终为false.
     */
    bool operator>=(const CProtocolPort & rciRight) const
    {
      return (_uwProtocolType == rciRight._uwProtocolType &&
              _nPortNumber >= rciRight._nPortNumber);
    }

    CZVMString ToBinaryString() const;
    std::string ToString() const;

    /** 永远为true. */
    bool ToBool() const
    { return true; }

    CProtocolPort()
      :_uwProtocolType(IPPROTO_TCP),
       _nPortNumber(80)
    { }

    CProtocolPort(UWORD uwProtocolType, PPORT nPortNumber)
      :_uwProtocolType(uwProtocolType),
       _nPortNumber(nPortNumber)
    { }

    CProtocolPort(const CProtocolPort & rciRight)
      :_uwProtocolType(rciRight._uwProtocolType),
       _nPortNumber(rciRight._nPortNumber)
    { }

    virtual ~CProtocolPort()
    { }
};

inline std::ostream & operator<<(std::ostream & ros, const CProtocolPort & rciPort)
{
  ros << rciPort.ToString();
  return(ros);
}


ZLS_END_NAMESPACE


#endif

