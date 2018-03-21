/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/IPv4Address.hpp,v $
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


#ifndef _ZLS_zfc_IPv4Address_hpp_
#define _ZLS_zfc_IPv4Address_hpp_

#include <zls/zfc/Manifest.h>
#ifdef ENABLE_THREADS
#include <zls/zfc/CSynchronized.hpp>
#endif


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


/**
 * The network name and address objects are all derived from a common
 * CIPv4Address base class. Specific classes, such as CIPv4HostAddress,
 * CIPv4MaskAddress, etc, are defined from CIPv4Address entirely so that the
 * manner a network address is being used can easily be documented and
 * understood from the code and to avoid common errors and accidental misuse
 * of the wrong address object.  For example, a "connection" to something
 * that is declared as a "CIPv4HostAddress" can be kept type-safe from a
 * "connection" accidently being made to something that was declared a
 * "CIPv4BroadcastAddress".
 *
 * @short Internet Address binary data type.
 */
class CIPv4Address
{
  protected:
    /** For synchronized C functions 'gethostbyaddr()' and 'gethostbyname()'. */
    static CMutex    _SciMutex;

    struct in_addr * _asiIPv4Address;
    size_t           _nCountOfAddress;

    /**
     * Sets the IP address from a string representation of the
     * numeric address, ie "127.0.0.1"
     *
     * @param host The string representation of the IP address
     * @return true if successful
     */
    bool SetIPAddress(const char *host);

  public:
    /**
     * Create an Internet Address object with an empty (0.0.0.0)
     * address.
     */
    CIPv4Address();

    /**
     * Convert the system internet address data type (struct in_addr)
     * into a Common C++ CIPv4Address object.
     *
     * @param addr struct of system used binary internet address.
     */

    CIPv4Address(struct in_addr addr);

    /**
     * Convert a null terminated ASCII host address string (example:
     * "127.0.0.1") directly into a Common C++ CIPv4Address object.
     *
     * @param address null terminated C string.
     */
    CIPv4Address(const char *address);

    /**
     * Copy constructor
     */
    CIPv4Address(const CIPv4Address &rhs);

    /**
     * Destructor
     */
    virtual ~CIPv4Address();

    /**
     * Used to specify a host name or numeric internet address.
     *
     * @param host The string representation of the IP address or
     *	a hostname, if NULL, it will default to INADDR_NONE
     *
     * @return true if successful, false if DNS resolve failed or parameter is a
     * NULL pointer.
     */
    bool SetAddress(const char *host);

    /**
     * Provide a string representation of the value (Internet Address)
     * held in the CIPv4Address object.
     *
     * @return string representation of CIPv4Address.
     */
    const std::string GetHostName(void);

    /**
     * May be used to verify if a given CIPv4Address returned by another function
     * contains a "valid" address, or "ff.ff.ff.ff"(INADDR_NONE) which is often
     * used to mark "invalid" CIPv4Address values.
     *
     * @return true if address != ff.ff.ff.ff(INADDR_NONE)
     */
    bool IsValidIPv4Address(void) const;

    /**
     * Provide a low level system usable struct in_addr object from
     * the contents of CIPv4Address.  This is needed for services such
     * as bind() and connect().
     *
     * @return system binary coded internet address.
     */
    struct in_addr GetAddress(void) const;

    /**
     * Provide a low level system usable struct in_addr object from
     * the contents of CIPv4Address.
     *
     * @return std::string of internet address.
     */
    std::string CIPv4Address::GetAddressAsString(void) const;

    /**
     * Provide a low level system usable struct in_addr object from
     * the contents of CIPv4Address.  This is needed for services such
     * as bind() and connect().
     *
     * @param i for InetAddresses with multiple addresses, returns the
     *	address at this index.  User should call GetAddressCount()
     *	to determine the number of address the object contains.
     *
     * @return system binary coded internet address.  If parameter i is
     *	out of range, the first address is returned.
     */
    struct in_addr GetAddress(size_t i) const;

    /**
     * Provide a low level system usable struct in_addr object from
     * the contents of CIPv4Address.
     *
     * @param i for InetAddresses with multiple addresses, returns the
     *	address at this index.  User should call GetAddressCount()
     *	to determine the number of address the object contains.
     *
     * @return std::string of internet address.  If parameter i is out of range,
     * the first address is returned.
     */
    std::string CIPv4Address::GetAddressAsString(size_t i) const;

    /**
     * Returns the number of internet addresses that an CIPv4Address object
     * contains.  This usually only happens with CIPv4HostAddress objects
     * where multiple IP addresses are returned for a DNS lookup
     */
    size_t GetAddressCount() const { return _nCountOfAddress; }

    CIPv4Address & operator=(const char *str);
    CIPv4Address & operator=(struct in_addr addr);
    CIPv4Address & operator=(const CIPv4Address &rhs);

    /**
     * Allows assignment from the return of functions like inet_addr() or htonl()
     */
    CIPv4Address & operator=(NUDWORD addr);

    bool operator!() const
    { return !IsValidIPv4Address(); }

    /**
     * Compare two internet addresses to see if they are equal
     * (if they specify the physical address of the same internet host).
     *
     * If there is more than one IP address in either CIPv4Address object,
     * this will return true if all of the IP addresses in the smaller
     * are in the larger in any order.
     */
    bool operator==(const CIPv4Address &a) const;

    /**
     * Compare two internet addresses to see if they are not
     * equal (if they each refer to unique and different physical
     * ip addresses).
     *
     * This is implimented in terms of operator==
     */
    bool operator!=(const CIPv4Address &a) const;
};


// forward declaration
class CIPv4HostAddress;


/**
 * Internet addresses used specifically as masking addresses (such as "
 * 255.255.255.0") are held in the CIPv4MaskAddress derived object.  The
 * seperate class is used so that C++ type casting can automatically
 * determine when an CIPv4Address object is really a mask address object
 * rather than simply using the base class.  This also allows manipulative
 * operators for address masking to operate only when presented with a
 * Masked address as well as providing cleaner and safer source.
 *
 * @short Internet Address Mask such as subnet masks.
 */
class CIPv4MaskAddress : public CIPv4Address {
  public:
    /**
     * Create the mask from a null terminated ASCII string such as
     * "255.255.255.128".
     *
     * @param mask null terminated ASCII mask string.
     *
     * @throw zfc::EInvalidArgument 当mask串不合法时.
     */
    CIPv4MaskAddress(const char *mask);

    /**
     * Create the mask from a numeric such as 24 for "255.255.255.0".
     *
     * @param nMaskBits a numeric such as 24 for "255.255.255.0".
     *
     * @throw zfc::EOutOfRange 当nMaskBits<1或nMaskBits>32.
     */
    CIPv4MaskAddress(const int nMaskBits);

    NUDWORD GetNetworkMask() const
    {  return GetAddress().s_addr; }

    /**
     * Allows assignment from the return of functions like inet_addr() or htonl()
     *
     * @attention 理论上基类CIPv4Address已经有operator=(NUDWORD)了，派生类
     * 可以不用再显式定义operator=(NUDWORD)了，但由于gcc-2.95.3的Bugs，它
     * 始终抱怨查找不到CIPv4HostAddress::operator=(long unsigne int &)，因
     * 此只能在这里重写一个.
     */
    CIPv4Address & operator=(NUDWORD nudwMask)
    { return CIPv4Address::operator=(nudwMask); }

    /**
     * Masks are usually used to coerce host addresses into a specific
     * router or class domain.  This can be done by taking the Inet
     * Host Address object and "and"ing it with an address mask.  This
     * operation can be directly expressed in C++ through the & operator.
     *
     * @return a internet host address that has been masked.
     * @param addr host address to be masked by subnet.
     * @param mask inetnet mask address object to mask by.
     */
    friend CIPv4HostAddress operator&(const CIPv4HostAddress &addr,
                                      const CIPv4MaskAddress &mask);
};


/**
 * This object is used to hold the actual and valid internet address of a
 * specific host machine that will be accessed through a socket.
 *
 * @short Address of a specific Internet host machine.
 */
class CIPv4HostAddress : public CIPv4Address {
  public:
    /**
     * Create a new host address for a specific internet host.  The
     * internet host can be specified in a null terminated ASCII
     * string and include either the physical host address or the
     * DNS name of a host machine.  Hence, an CIPv4HostAddress
     * ("www.voxilla.org") can be directly declaired in this manner.
     *
     * Defaults to the IP address that represents the interface matching
     * "gethostname()".
     *
     * @param host dns or physical address of an Internet host.
     */
    CIPv4HostAddress(const char *host = NULL);

    /**
     * Convert a system socket binary address such as may be
     * returned through the accept() call or getsockpeer() into
     * an internet host address object.
     *
     * @param addr binary address of internet host.
     */
    CIPv4HostAddress(struct in_addr addr);

    /**
     * Allows assignment from the return of functions like inet_addr() or htonl().
     *
     * @attention 理论上基类CIPv4Address已经有operator=(NUDWORD)了，派生类
     * 可以不用再显式定义operator=(NUDWORD)了，但由于gcc-2.95.3的Bugs，它
     * 始终抱怨查找不到CIPv4HostAddress::operator=(long unsigne int &)，因
     * 此只能在这里重写一个.
     */
    CIPv4Address & operator=(NUDWORD addr)
    { return CIPv4Address::operator=(addr); }

    /**
     * Mask the internet host address object with a network mask address.
     * This is commonly used to coerce an address by subnet.
     */
    CIPv4HostAddress & operator&=(const CIPv4MaskAddress &mask);
    CIPv4HostAddress & operator&=(NUDWORD nudwMask);

    friend class CIPv4MaskAddress;
    friend CIPv4HostAddress operator&(const CIPv4HostAddress &addr,
                                      const CIPv4MaskAddress &mask);
};


/**
 * The broadcast address object is used to store the broadcast address for
 * a specific subnet.  This is commonly used for UDP broadcast operations.
 */
class CIPv4BroadcastAddress : public CIPv4Address {
  public:
    /**
     * Specify the physical broadcast address to use and create a new
     * broadcast address object based on a null terminated ASCII
     * string.
     *
     * @param net null terminated ASCII network address.
     */
    CIPv4BroadcastAddress(const char *net = "255.255.255.255");
};


ZLS_END_NAMESPACE


#endif

