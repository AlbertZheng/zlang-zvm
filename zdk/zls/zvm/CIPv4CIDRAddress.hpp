/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CIPv4CIDRAddress.hpp,v $
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


#ifndef _ZLS_zvm_CIPv4CIDRAddress_hpp_
#define _ZLS_zvm_CIPv4CIDRAddress_hpp_

#include <zls/zfc/IPv4Address.hpp>
#include <zls/zfc/CBinaryString.hpp>
#include <zls/zfc/CBinaryInputFileStream.hpp>
#include <zls/zfc/CBinaryOutputFileStream.hpp>
#include <zls/zvm/Manifest.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


/**
 * 抽象Internet CIDR address（即将Host-IP-Address和Network-Mask整合在一起考虑）.
 *
 * @attention 如果采用了提供CIDR mask的constructor，则在构造实例时将立即对address
 * 进行mask操作，然后再将结果存作为address.
 */
class CIPv4CIDRAddress {
  private:
    /**
     * 一个IPv4 address，可能是表示host地址，也可能是表示network地址，这由
     * _nudwCIDRMask来决定，当_nudwCIDRMask为255.255.255.255时，表示_ciAddress
     * 为host地址，否则为CIDR network地址.
     */
    zfc::CIPv4HostAddress _ciAddress;

    /**
     * 当为255.255.255.255时，表示_ciAddress为host地址，否则为CIDR network地址.
     */
    NUDWORD _nudwCIDRMask;

  public:
    const zfc::CIPv4HostAddress & GetAddress() const
    {
      return(_ciAddress);
    }

    NUDWORD GetCIDRMask() const
    {
      return(_nudwCIDRMask);
    }

    void Set(const zfc::CIPv4HostAddress & rciHostAddress)
    {
      _ciAddress = rciHostAddress;
      _nudwCIDRMask = INADDR_BROADCAST;
    }

    void Set(const char * pszHostAddress)
    {
      _ciAddress = pszHostAddress;
      _nudwCIDRMask = INADDR_BROADCAST;
    }

    void Set(const zfc::CIPv4HostAddress & rciNetworkAddress, NUDWORD nudwCIDRMask)
    {
      _ciAddress = rciNetworkAddress;
      _nudwCIDRMask = nudwCIDRMask;
      // Now mask address
      _ciAddress &= _nudwCIDRMask;
    }

    void Set(const char * pszNetworkAddress, NUDWORD nudwCIDRMask)
    {
      _ciAddress = pszNetworkAddress;
      _nudwCIDRMask = nudwCIDRMask;
      // Now mask address
      _ciAddress &= _nudwCIDRMask;
    }

    CIPv4CIDRAddress & operator=(const CIPv4CIDRAddress & rciRight)
    {
      _ciAddress = rciRight._ciAddress;
      _nudwCIDRMask = rciRight._nudwCIDRMask;
      return *this;
    }

    bool operator==(const CIPv4CIDRAddress & rciRight) const
    {
      return(_ciAddress == rciRight._ciAddress &&
             _nudwCIDRMask == rciRight._nudwCIDRMask);
    }

    bool operator!=(const CIPv4CIDRAddress & rciRight) const
    {
      return(_ciAddress != rciRight._ciAddress ||
             _nudwCIDRMask != rciRight._nudwCIDRMask);
    }

    CZVMString ToBinaryString() const;
    std::string ToString() const;

    /** 只要IPv4Address不是ff.ff.ff.ff，就为true. */
    bool ToBool() const
    {
      return _ciAddress.IsValidIPv4Address();
    }

    CIPv4CIDRAddress()
      : _ciAddress("127.0.0.1"),
        _nudwCIDRMask(INADDR_BROADCAST)
    { }

    CIPv4CIDRAddress(const zfc::CIPv4HostAddress & rciHostAddress)
      : _ciAddress(rciHostAddress),
        _nudwCIDRMask(INADDR_BROADCAST)
    { }

    CIPv4CIDRAddress(const zfc::CIPv4HostAddress & rciNetworkAddress, NUDWORD nudwCIDRMask)
      : _ciAddress(rciNetworkAddress),
        _nudwCIDRMask(nudwCIDRMask)
    {
      // Now mask address
      _ciAddress &= _nudwCIDRMask;
    }

    CIPv4CIDRAddress(const char * pszHostAddress)
      : _ciAddress(pszHostAddress),
        _nudwCIDRMask(INADDR_BROADCAST)
    { }

    CIPv4CIDRAddress(const char * pszNetworkAddress, NUDWORD nudwCIDRMask)
      : _ciAddress(pszNetworkAddress),
        _nudwCIDRMask(nudwCIDRMask)
    {
      // Now mask address
      _ciAddress &= _nudwCIDRMask;
    }

    CIPv4CIDRAddress(const CIPv4CIDRAddress & rciRight)
      : _ciAddress(rciRight._ciAddress),
        _nudwCIDRMask(rciRight._nudwCIDRMask)
    {
      /* 注：CIPv4HostAddress和CIPv4MaskAddress没有缺省的constructor */
    }

    ~CIPv4CIDRAddress()
    { }
};

inline std::ostream & operator<<(std::ostream & ros, const CIPv4CIDRAddress & rciIPv4Address)
{
  ros << rciIPv4Address.ToString();
  return(ros);
}


ZLS_END_NAMESPACE


#endif

