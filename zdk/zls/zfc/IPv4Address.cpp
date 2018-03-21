/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/IPv4Address.cpp,v $
 *
 * $Date: 2001/11/14 17:25:10 $
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


#include <zls/zfc/IPv4Address.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


/******************************************************************************
 * class CIPv4Address.
 ******************************************************************************/
CMutex CIPv4Address::_SciMutex;


CIPv4Address::CIPv4Address()
  : _asiIPv4Address(0)
{
  *this = INADDR_ANY;
}

CIPv4Address::CIPv4Address(const char *address)
  : _asiIPv4Address(0)
{
  if (address == 0 || !strcmp(address, "*"))
    *this = INADDR_NONE;
  else
    SetAddress(address);
}

CIPv4Address::CIPv4Address(struct in_addr addr)
  : _asiIPv4Address(0)
{
  _nCountOfAddress = 1;
  _asiIPv4Address = new __OPTION(_THROW) struct in_addr[1];
  _asiIPv4Address[0] = addr;
}

CIPv4Address::CIPv4Address(const CIPv4Address &rhs)
  : _nCountOfAddress(rhs._nCountOfAddress)
{
  _asiIPv4Address = new __OPTION(_THROW) struct in_addr[_nCountOfAddress];
  memcpy(_asiIPv4Address, rhs._asiIPv4Address, sizeof(struct in_addr) * _nCountOfAddress);
}

CIPv4Address::~CIPv4Address()
{
  delete [] _asiIPv4Address;
}

struct in_addr CIPv4Address::GetAddress() const
{
  return _asiIPv4Address[0];
}

struct in_addr CIPv4Address::GetAddress(size_t i) const
{
  return (i < _nCountOfAddress ? _asiIPv4Address[i] : _asiIPv4Address[0]);
}

std::string CIPv4Address::GetAddressAsString() const
{
  return IPv4AddressToString(_asiIPv4Address[0]);
}

std::string CIPv4Address::GetAddressAsString(size_t i) const
{
  return (i < _nCountOfAddress ? IPv4AddressToString(_asiIPv4Address[i]) : IPv4AddressToString(_asiIPv4Address[0]));
}

bool CIPv4Address::IsValidIPv4Address() const
{
  if (_asiIPv4Address[0].s_addr != INADDR_NONE)
  {
    return true;
  }
  else
  {
    return false;
  }
}

CIPv4Address & CIPv4Address::operator=(const char *str)
{
  if (str == 0 || !strcmp(str, "*"))
  {
    return *this = INADDR_NONE;
  }
  else
  {
    SetAddress(str);
    return *this;
  }
}

CIPv4Address & CIPv4Address::operator=(struct in_addr addr)
{
  delete [] _asiIPv4Address;
  _nCountOfAddress = 1;
  _asiIPv4Address = new __OPTION(_THROW) struct in_addr[1];
  _asiIPv4Address[0] = addr;
  return *this;
}

CIPv4Address & CIPv4Address::operator=(NUDWORD addr)
{
  delete [] _asiIPv4Address;
  _nCountOfAddress = 1;
  _asiIPv4Address = new __OPTION(_THROW) struct in_addr[1];
  _asiIPv4Address[0].s_addr = addr;
  return *this;
}

CIPv4Address & CIPv4Address::operator=(const CIPv4Address &rhs)
{
  if(this == &rhs) return *this;

  _nCountOfAddress = rhs._nCountOfAddress;
  delete [] _asiIPv4Address;
  _asiIPv4Address = new __OPTION(_THROW) struct in_addr[_nCountOfAddress];
  memcpy(_asiIPv4Address, rhs._asiIPv4Address, sizeof(struct in_addr) * _nCountOfAddress);
  return *this;
}

bool CIPv4Address::operator==(const CIPv4Address &a) const
{
  const CIPv4Address *smaller, *larger;
  size_t s, l;

  if(_nCountOfAddress > a._nCountOfAddress)
  {
    smaller = &a;
    larger  = this;
  }
  else
  {
    smaller = this;
    larger  = &a;
  }

  // Loop through all addr's in the smaller and make sure
  // that they are all in the larger
  for(s = 0; s < smaller->_nCountOfAddress; s++)
  {
    for(l = 0;
        l < larger->_nCountOfAddress &&
        memcmp((char *)&_asiIPv4Address[s], (char *)&a._asiIPv4Address[l], sizeof(struct in_addr));
        l++)
      ;
    if (l == larger->_nCountOfAddress) return false;
  }
  return true;
}

bool CIPv4Address::operator!=(const CIPv4Address &a) const
{
  // Impliment in terms of operator==
  return (*this == a ? false : true);
}

bool CIPv4Address::SetIPAddress(const char *host)
{
  if (! host)
    return false;

  #if defined(WIN32) || defined(__win32__)
    NUDWORD n_addr;

    n_addr = inet_addr(host);
    if (n_addr == INADDR_NONE)  // 0xFFFFFFFF
    {
      return false;
    }
    *this = n_addr;
  #else
    struct in_addr l_addr;

    if (! inet_aton(host, &l_addr))
    {
      return false;
    }
    *this = l_addr;
  #endif
  return true;
}

bool CIPv4Address::SetAddress(const char *host)
{
  if (! host)  // The way this is currently used, this can never happen
  {
    *this = INADDR_NONE;
    return false;
  }

  // 如果假设是数字串型"x.x.x.x"失败
  if (! SetIPAddress(host))
  {
    struct hostent *hp;
    struct in_addr **bptr;

    #if defined(__GLIBC__)
      char   hbuf[8192];
      struct hostent hb;
      int    rtn;

      if (gethostbyname_r(host, &hb, hbuf, sizeof(hbuf), &hp, &rtn))
        hp = NULL;
    #elif defined(__solaris__)
      char   hbuf[8192];
      struct hostent hb;
      int    rtn;

      hp = gethostbyname_r(host, &hb, hbuf, sizeof(hbuf), &rtn);
    #else
      CSynchronized ciSynchronized(_SciMutex);
      hp = gethostbyname(host);
    #endif
      if (! hp)
      {
        delete [] _asiIPv4Address;
        _asiIPv4Address = new __OPTION(_THROW) struct in_addr[1];
        _asiIPv4Address[0].s_addr = INADDR_NONE;
        return false;
      }

      // Count the number of IP addresses returned
      _nCountOfAddress = 0;
      for(bptr = (struct in_addr **)hp->h_addr_list; *bptr != NULL; bptr++)
      {
        _nCountOfAddress++;
      }

      // Allocate enough memory
      delete [] _asiIPv4Address;	// Cause this was allocated in base
      _asiIPv4Address = new __OPTION(_THROW) struct in_addr[_nCountOfAddress];

      // Now go through the list again assigning to the member _asiIPv4Address
      bptr = (struct in_addr **)hp->h_addr_list;
      for(unsigned int i = 0; i < _nCountOfAddress; i++)
      {
        _asiIPv4Address[i] = *bptr[i];
      }
  }

  return true;
}

const std::string CIPv4Address::GetHostName()
{
  struct hostent *hp = 0;
  struct in_addr addr0;
  std::string stringHostName = "0.0.0.0";

  memset(&addr0, 0, sizeof(addr0));
  // if is "0.0.0.0"
  if (!memcmp(&addr0, &_asiIPv4Address[0], sizeof(addr0)))
    return stringHostName;

  #if defined(__GLIBC__)
    char   hbuf[8192];
    struct hostent hb;
    int    rtn;
    if (gethostbyaddr_r((char *)&_asiIPv4Address[0], sizeof(addr0), AF_INET, &hb, hbuf, sizeof(hbuf), &hp, &rtn))
      hp = 0;
  #elif defined(__solaris__)
    char   hbuf[8192];
    struct hostent hb;
    int    rtn;
    hp = gethostbyaddr_r((char *)&_asiIPv4Address[0], (int)sizeof(addr0), (int)AF_INET, &hb, hbuf, (int)sizeof(hbuf), &rtn);
  #else
    CSynchronized ciSynchronized(_SciMutex);
    hp = gethostbyaddr((char *)&_asiIPv4Address[0], sizeof(addr0), AF_INET);
  #endif
    if (hp)
    {
      stringHostName = hp->h_name;
      return stringHostName;
    }
    else
    {
      stringHostName = IPv4AddressToString(_asiIPv4Address[0]);
      return stringHostName;
    }
}


CIPv4MaskAddress::CIPv4MaskAddress(const char *mask)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CIPv4MaskAddress::CIPv4MaskAddress()");
  if (SetIPAddress(mask))
  {
    return;
  }
  else
  {
    std::string stringError = std::string("Invalid CIDR mask '") + mask + "'";
    throw zfc::EInvalidArgument(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
  }
}

CIPv4MaskAddress::CIPv4MaskAddress(const int nMaskBits)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CIPv4MaskAddress::CIPv4MaskAddress()");
  NUDWORD x = 0xffffffff;
  int l = 32 - nMaskBits;

  if(l < 0 || l > 31)
  {
    throw zfc::EOutOfRange(__FILE__, __PRETTY_FUNC__, __LINE__,
                           "Invalid CIDR mask-bits", nMaskBits, 1, 32);
  }

  *this = htonl(x << l);
}


CIPv4HostAddress::CIPv4HostAddress(struct in_addr addr)
  : CIPv4Address(addr)
{ }

CIPv4HostAddress::CIPv4HostAddress(const char *host)
  : CIPv4Address(host)
{ }

CIPv4HostAddress & CIPv4HostAddress::operator&=(const CIPv4MaskAddress &ma)
{
  NUDWORD nudwMask = ma.GetAddress().s_addr;
  for(size_t i = 0; i < _nCountOfAddress; i++)
  {
    _asiIPv4Address[i].s_addr &= nudwMask;
  }

  return *this;
}

CIPv4HostAddress & CIPv4HostAddress::operator&=(NUDWORD nudwMask)
{
  for(size_t i = 0; i < _nCountOfAddress; i++)
  {
    _asiIPv4Address[i].s_addr &= nudwMask;
  }

  return *this;
}

CIPv4HostAddress operator&(const CIPv4HostAddress &addr,
                           const CIPv4MaskAddress &mask)
{
  CIPv4HostAddress temp = addr;
  temp &= mask;
  return temp;
}


CIPv4BroadcastAddress::CIPv4BroadcastAddress(const char *net = "255.255.255.255")
  : CIPv4Address(net)
{ }


ZLS_END_NAMESPACE

