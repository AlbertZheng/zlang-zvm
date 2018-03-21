/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/Hash.hpp,v $
 *
 * $Date: 2001/12/10 20:15:21 $
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


#ifndef _ZLS_zfc_Hash_hpp_
#define _ZLS_zfc_Hash_hpp_

#include <zls/zfc/Manifest.h>
#include <zls/zfc/Exception.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


/**
 * 一些常量.
 */
const int CnMaxTCPSessionBucketCount = 100000;
const int CnMaxIPv4AddressPairBucketCount = 1000;
const int CnMaxIPv4AddressBucketCount = 1000;


int ComputingBinaryLogarithm(int nBucketCount) ;


/**
 * 用来表示源、目的IPv4 Address pair和port pair的四元组.
 */
struct TIPv4Tuple4 {
  NUDWORD nudwSourceAddress;   ///< 源IPv4 address（网络字节序）
  NUDWORD nudwDestAddress;    ///< 目的IPv4 address（网络字节序）
  UWORD   uwSourcePort;       ///< 源port（主机字节序）
  UWORD   uwDestPort;         ///< 目的port（主机字节序）

  /** Default constructor. */
  TIPv4Tuple4()
  { }

  /** Copy constructor. */
  /* 让compiler帮助我们进行按bit拷贝可能效率更高
  inline TIPv4Tuple4(const TIPv4Tuple4 & rt)
  {
    nudwSourceAddress = rt.nudwSourceAddress;
    nudwDestAddress = rt.nudwDestAddress;
    uwSourcePort = rt.uwSourcePort;
    uwDestPort = rt.uwDestPort;
  }
  */

  /** Constructor. */
  TIPv4Tuple4(NUDWORD nudwSIP, NUDWORD nudwDIP, UWORD uwSPort, UWORD uwDPort)
  {
    nudwSourceAddress = nudwSIP;
    nudwDestAddress = nudwDIP;
    uwSourcePort = uwSPort;
    uwDestPort = uwDPort;
  }

  /* 让compiler帮助我们进行按bit拷贝可能效率更高
  const TIPv4Tuple4 & operator=(const TIPv4Tuple4 & rt)
  {
    nudwSourceAddress = rt.nudwSourceAddress;
    nudwDestAddress = rt.nudwDestAddress;
    uwSourcePort = rt.uwSourcePort;
    uwDestPort = rt.uwDestPort;

    return(*this);
  }
  */

  bool operator==(const TIPv4Tuple4 & rt) const
  {
    if (nudwSourceAddress == rt.nudwSourceAddress && nudwDestAddress == rt.nudwDestAddress &&
        uwSourcePort == rt.uwSourcePort && uwDestPort == rt.uwDestPort)
    {
      return(true);
    }
    else
    {
      return(false);
    }
  }
};


/**
 * 计算TCP stream的hash值的function object.
 *
 * @attention function object必须是可copy的.
 */
struct MakeTCPSessionHash {
  int nBucketCount;
  int nBucketCountLog2;

  /** Constructor. */
  MakeTCPSessionHash(size_t _nBucketCount)
    : nBucketCount(_nBucketCount)
  {
    // 计算Hash size的Log2
    nBucketCountLog2 = ComputingBinaryLogarithm(nBucketCount);
  }

  size_t operator()(const TIPv4Tuple4 & rsiTCPHaltStreamAddress) const;
};


/**
 * 判断两个TCP stream是否是同一个stream的function object.
 */
struct TCPSessionHashEqual {
  bool operator()(const TIPv4Tuple4 & rt1 , const TIPv4Tuple4 & rt2) const
  {
    return(rt1 == rt2);
  }
};


/**
 * 用来表示源、目的IPv4 Address pair的二元组.
 */
struct TIPv4Tuple2 {
  NUDWORD nudwSourceAddress;  ///< 源IPv4 address（网络字节序）
  NUDWORD nudwDestAddress;   ///< 目的IPv4 address（网络字节序）

  /** Default constructor. */
  TIPv4Tuple2()
  { }

  /** Copy constructor. */
  /* 让compiler帮助我们进行按bit拷贝可能效率更高
  TIPv4Tuple2(const TIPv4Tuple2 & rt)
  {
    nudwSourceAddress = rt.nudwSourceAddress;
    nudwDestAddress = rt.nudwDestAddress;
  }
  */

  /** Constructor. */
  TIPv4Tuple2(NUDWORD nudwSIP, NUDWORD nudwDIP)
  {
    nudwSourceAddress = nudwSIP;
    nudwDestAddress = nudwDIP;
  }

  /* 让compiler帮助我们进行按bit拷贝可能效率更高
  const TIPv4Tuple2 & operator=(const TIPv4Tuple2 & rt)
  {
    nudwSourceAddress = rt.nudwSourceAddress;
    nudwDestAddress = rt.nudwDestAddress;

    return(*this);
  }
  */

  bool operator==(const TIPv4Tuple2 & rt) const
  {
    if (nudwSourceAddress == rt.nudwSourceAddress && nudwDestAddress == rt.nudwDestAddress)
    {
      return(true);
    }
    else
    {
      return(false);
    }
  }
};


/**
 * 计算IPv4 address pair的hash值的function object.
 *
 * @attention function object必须是可copy的.
 */
struct MakeIPv4AddressPairHash {
  int nBucketCount;
  int nBucketCountLog2;

  /** Constructor. */
  MakeIPv4AddressPairHash(size_t _nBucketCount)
    : nBucketCount(_nBucketCount)
  {
    nBucketCountLog2 = ComputingBinaryLogarithm(nBucketCount);
  }

  size_t operator()(const TIPv4Tuple2 & rtAddress) const;
};


/**
 * 判断两个IPv4 address pair是否相等的function object.
 */
struct IPv4AddressPairHashEqual {
  bool operator()(const TIPv4Tuple2 & rt1 , const TIPv4Tuple2 & rt2) const
  {
    return(rt1 == rt2);
  }
};


/**
 * 计算IPv4 address的hash值的function object.
 */
struct MakeIPv4AddressHash {
  int nBucketCount;

  /** Constructor. */
  MakeIPv4AddressHash(size_t _nBucketCount)
    : nBucketCount(_nBucketCount)
  { }

  /**
   * The parenthesis operator.
   *
   * @param nudw IPv4 address（网络字节序）.
   */
  size_t operator()(const NUDWORD nudw) const
  {
    return ((nudw % 65536) ^ (nudw >> 16)) % (nBucketCount);
  }
};


/**
 * 判断两个IPv4 address是否相等的function object.
 */
struct IPv4AddressHashEqual {
  /**
   * The parenthesis operator.
   *
   * @param nudw1 First IPv4 address（网络字节序）.
   * @param nudw2 Second IPv4 address（网络字节序）.
   */
  bool operator()(const NUDWORD nudw1 , const NUDWORD nudw2) const
  {
    return(nudw1 == nudw2);
  }
};


/**
 * CTCPSessionHashTableT是以TCP half stream作为Key的存储TCP session的Hash Table模板类.
 *
 * @note 我规定：在一个TCP session中主动发起connection的一方为client方，被动的
 * 一方为server方。而每当往Hash table中插入新的TCP session时，作为Key值的TCP half
 * stream address总是默认为是client方的half stream address.
 *
 * @attention 模板的参数CData必须具备有Default constructor以及符合STL的基本要求.
 */
template <typename CData>
class CTCPSessionHashTableT {
  public:
    typedef std::hash_map<TIPv4Tuple4, CData, MakeTCPSessionHash, TCPSessionHashEqual> CHashMap;
    typedef CHashMap::iterator   iterator;
    typedef CHashMap::value_type value_type;

  private:
    CHashMap _hmapTCPSessions;

  public:
    CHashMap & GetHashMap() { return _hmapTCPSessions; }

  public:
    /**
     * Constructor.
     *
     * @param nBucketCount Hash table的桶的数目.
     */
    CTCPSessionHashTableT(size_t nBucketCount)
      : _hmapTCPSessions(nBucketCount, MakeTCPSessionHash(nBucketCount))
                                    //< 将在std::hashtable的constructor初始化行被自己的copy
                                    // constructor进行copy到std::hashtable的内部member field中.
    { }

    /**
     * Destructor.
     */
    ~CTCPSessionHashTableT()
    { }

    /**
     * 根据一个TCP half stream address在Hash table中查找相应的TCP session.
     *
     * @param rsiTCPHalfStreamAddress 一个TCP half stream address，可以是client
     * 方的half stream address，也可以是server方的.
     *
     * @return 一个pair<CData *, bool>，其中"CData *"是被找到的那个TCP session
     * 存储在的Hash table中的用户数据结构的指针，而如果"bool"为true则暗示：根据
     * 这个被查找到的TCP session可以推断参数rsiTCPHalfStreamAddress是从server方
     * 发出的TCP halt stream的address（即通过将参数中的源、目的IPv4 address和port
     * 对调后才查找到这个TCP session），否则则是从server方发出的TCP halt stream
     * 的address.
     *
     * @throw zfc::ENotFound - 当查找失败时.
     */
    std::pair<CData *, bool> Find(const TIPv4Tuple4 & rsiTCPHalfStreamAddress);

    /**
     * 插入一个新的TCP session到Hash table中，并为这个TCP session构造一个用户数
     * 据结构的新Instance（即：调用用户数据结构的Default constructor）.
     *
     * @param rsiTCPHalfStreamAddress 总是默认为是client方的TCP half stream address.
     *
     * @return 一个pair<CData *, bool>，其中"CData *"是为新插入的这个TCP session
     * 而构造的存储在Hash table中的用户数据结构的新Instance的指针，如果"bool"为
     * false则暗示：插入失败（这个TCP session其实以前已经被插入过了），因此没有
     * 为这个TCP session再构造用户数据结构的新Instance，前面那个"CData *"直接指
     * 向它.
     *
     * @attention 理论上进行Insert之前应该先调用Find判断是否该TCP session已存在
     * Hash table中，但是也可以简化为直接Insert，然后通过返回的pair.second来判断
     * 是否已存在.
     */
    std::pair<CData *, bool> Insert(const TIPv4Tuple4 & rsiTCPHalfStreamAddress);

    /**
     * 根据一个TCP half stream address从Hash table中删除相应的TCP session，并删
     * 除这个TCP session存储在Hash table中的用户数据结构Instance（即：调用用户数
     * 据结构的Destructor）.
     *
     * @param rsiTCPHalfStreamAddress 一个TCP half stream address，可以是client
     * 方的half stream address，也可以是server方的.
     *
     * @return true If success, otherwise false.
     */
    bool Erase(const TIPv4Tuple4 & rsiTCPHalfStreamAddress);
};

template <typename CData>
std::pair<CData *, bool> CTCPSessionHashTableT<CData>::Find(const TIPv4Tuple4 & rsiTCPHalfStreamAddress)
{
  static char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CTCPSessionHashTableT::Find()");
  CTCPSessionHashTableT<CData>::iterator it;

  if ((it = _hmapTCPSessions.find(rsiTCPHalfStreamAddress)) != _hmapTCPSessions.end())
  {
    std::pair<CData *, bool> pairFoundTCPStream(&(*it).second, false);
    return(pairFoundTCPStream);
  }
  else
  /* 尝试着对调 */
  {
    TIPv4Tuple4 siReserve(rsiTCPHalfStreamAddress.nudwDestAddress,
                          rsiTCPHalfStreamAddress.nudwSourceAddress,
                          rsiTCPHalfStreamAddress.uwDestPort,
                          rsiTCPHalfStreamAddress.uwSourcePort);
    if ((it = _hmapTCPSessions.find(siReserve)) != _hmapTCPSessions.end())
    {
      std::pair<CData *, bool> pairFoundTCPStream(&(*it).second, true);
      return(pairFoundTCPStream);
    }
    else
    {
      std::string stringError = std::string("Finding TCP session<") +
                           rsiTCPHalfStreamAddress.nudwSourceAddress + ":" + rsiTCPHalfStreamAddress.uwSourcePort + "," +
                           rsiTCPHalfStreamAddress.nudwDestAddress + ":" + rsiTCPHalfStreamAddress.uwDestPort + "> failed";
      throw zfc::ENotFound(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
    }
  }
}


template <typename CData>
bool CTCPSessionHashTableT<CData>::Erase(const TIPv4Tuple4 & rsiTCPHalfStreamAddress)
{
  CTCPSessionHashTableT<CData>::iterator it;

  if ((it = _hmapTCPSessions.find(rsiTCPHalfStreamAddress)) != _hmapTCPSessions.end())
  {
    _hmapTCPSessions.erase(it);
    return true;
  }
  else
  /* 尝试着对调 */
  {
    TIPv4Tuple4 siReserve(rsiTCPHalfStreamAddress.nudwDestAddress,
                          rsiTCPHalfStreamAddress.nudwSourceAddress,
                          rsiTCPHalfStreamAddress.uwDestPort,
                          rsiTCPHalfStreamAddress.uwSourcePort);
    if ((it = _hmapTCPSessions.find(siReserve)) != _hmapTCPSessions.end())
    {
      _hmapTCPSessions.erase(it);
      return true;
    }
    else
    {
      return false;
    }
  }
}


template <typename CData>
std::pair<CData *, bool> CTCPSessionHashTableT<CData>::Insert(const TIPv4Tuple4 & rsiTCPHalfStreamAddress)
{
  std::pair<CTCPSessionHashTableT<CData>::iterator, bool> pairInserted(
                      _hmapTCPSessions.insert( // a 'pair<key_type, data_type>'
       CTCPSessionHashTableT<CData>::value_type(rsiTCPHalfStreamAddress, CData())
                                             ) // return a 'pair<iterator, bool>'
                                                                      );
  std::pair<CData *, bool> pairResult(
                                 &(
                                   *(
                                     pairInserted.first // get the iterator of the returned 'pair<iterator, bool>'
                                    ) // get 'pair<key_type, data_type>' pointered by the iterator
                                  ).second, // get member 'data_type' of struct 'pair<key_type, data_type>'
                                 pairInserted.second // get the bool of the returned 'pair<iterator, bool>'
                                     );
  return pairResult;
}



/**
 * CIPv4AddressPairHashTableT是以IPv4 address pair作为Key的Hash Table模板类.
 *
 * @attention 模板的参数CData必须具备有Default constructor以及符合STL的基本要求.
 */
template <typename CData>
class CIPv4AddressPairHashTableT {
  public:
    typedef std::hash_map<TIPv4Tuple2, CData, MakeIPv4AddressPairHash, IPv4AddressPairHashEqual> CHashMap;
    typedef CHashMap::iterator   iterator;
    typedef CHashMap::value_type value_type;

  private:
    CHashMap _hmapIPv4AddressPairs;

  public:
    /**
     * Constructor.
     *
     * @param nBucketCount Hash table的桶的数目.
     */
    CIPv4AddressPairHashTableT(size_t nBucketCount)
      : _hmapIPv4AddressPairs(nBucketCount, MakeIPv4AddressPairHash(nBucketCount))
    { }

    /**
     * Destructor.
     */
    ~CIPv4AddressPairHashTableT()
    { }

    /**
     * 根据一个IPv4 address pair在Hash table中查找.
     *
     * @param rsiIPv4AddressPair 一个IPv4 address pair，注意：这个IPv4 address
     * pair中的两个address的方向并不重要，即，如果用<SourceIP, DestIP>可以查找
     * 成功，则那么用<DestIP, SourceIP>也能查找到同一个用户数据结构的引用.
     *
     * @return 一个pair<CData *, bool>，其中"CData *"是被找到的那个address pair
     * 存储在的Hash table中的用户数据结构的指针，而如果"bool"为true则暗示：这个
     * 被查找到的address pair是通过将参数rsiIPv4AddressPair中的两个address进行
     * 对调后才查找成功的.
     *
     * @throw zfc::ENotFound - 当查找失败时.
     */
    std::pair<CData *, bool> Find(const TIPv4Tuple2 & rsiIPv4AddressPair);

    /**
     * 插入一个新的IPv4 address pair到Hash table中，并为这构造一个用户数
     * 据结构的新Instance（即：调用用户数据结构的Default constructor）.
     *
     * @param rsiIPv4Address 一个IPv4 address pair，，注意：这个IPv4 address
     * pair中的两个address的方向并不重要，即，如果用<SourceIP, DestIP>可以查找
     * 成功，则那么用<DestIP, SourceIP>也能查找到同一个用户数据结构的引用.
     *
     * @return 一个pair<CData *, bool>，其中"CData *"是为新插入的这个address pair
     * 而构造的存储在Hash table中的用户数据结构的新Instance的指针，如果"bool"为
     * false则暗示：插入失败（这个address pair其实以前已经被插入过了），因此没有
     * 为这个address pair再构造用户数据结构的新Instance，前面那个"CData *"直接指
     * 向它.
     */
    std::pair<CData *, bool> Insert(const TIPv4Tuple2 & rsiIPv4AddressPair);

    /**
     * 将一个IPv4 address pair从Hash table中删除，并删除对应的存储在Hash table
     * 中的用户数据结构Instance（即：调用用户数据结构的Destructor）.
     *
     * @param rsiIPv4AddressPair 一个IPv4 address pair，，注意：这个IPv4 address
     * pair中的两个address的方向并不重要，即，如果用<SourceIP, DestIP>可以查找
     * 成功，则那么用<DestIP, SourceIP>也能查找到同一个用户数据结构的引用.
     *
     * @return true If success, otherwise false.
     */
    bool Erase(const TIPv4Tuple2 & rsiIPv4AddressPair);
};

template <typename CData>
std::pair<CData *, bool> CIPv4AddressPairHashTableT<CData>::Find(const TIPv4Tuple2 & rsiIPv4AddressPair)

{
  static char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CIPv4AddressPairHashTableT::Find()");
  CIPv4AddressPairHashTableT<CData>::iterator it;

  if ((it = _hmapIPv4AddressPairs.find(rsiIPv4AddressPair)) != _hmapIPv4AddressPairs.end())
  {
    std::pair<CData *, bool> pairFoundTCPStream(&(*it).second, false);
    return(pairFoundTCPStream);
  }
  else
  /* 尝试着对调 */
  {
    TIPv4Tuple2 siReserve(rsiIPv4AddressPair.nudwDestAddress,
                          rsiIPv4AddressPair.nudwSourceAddress);
    if ((it = _hmapIPv4AddressPairs.find(siReserve)) != _hmapIPv4AddressPairs.end())
    {
      std::pair<CData *, bool> pairFoundTCPStream(&(*it).second, true);
      return(pairFoundTCPStream);
    }
    else
    {
      std::string stringError = std::string("Finding IPv4 address pair<") +
                                rsiIPv4AddressPair.nudwSourceAddress + "," +
                                rsiIPv4AddressPair.nudwDestAddress + "> failed";
      throw zfc::ENotFound(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
    }
  }
}


template <typename CData>
bool CIPv4AddressPairHashTableT<CData>::Erase(const TIPv4Tuple2 & rsiIPv4AddressPair)
{
  CIPv4AddressPairHashTableT<CData>::iterator it;

  if ((it = _hmapIPv4AddressPairs.find(rsiIPv4AddressPair)) != _hmapIPv4AddressPairs.end())
  {
    _hmapIPv4AddressPairs.erase(it);
    return true;
  }
  else
  /* 尝试着对调 */
  {
    TIPv4Tuple2 siReserve(rsiIPv4AddressPair.nudwDestAddress,
                          rsiIPv4AddressPair.nudwSourceAddress);
    if ((it = _hmapIPv4AddressPairs.find(siReserve)) != _hmapIPv4AddressPairs.end())
    {
      _hmapIPv4AddressPairs.erase(it);
      return true;
    }
    else
    {
      return false;
    }
  }
}


template <typename CData>
std::pair<CData *, bool> CIPv4AddressPairHashTableT<CData>::Insert(const TIPv4Tuple2 & rsiIPv4AddressPair)
{
  std::pair<CIPv4AddressPairHashTableT<CData>::iterator, bool> pairInserted(
                      _hmapIPv4AddressPairs.insert( // a 'pair<key_type, data_type>'
       CIPv4AddressPairHashTableT<CData>::value_type(rsiIPv4AddressPair, CData())
                                                  ) // return a 'pair<iterator, bool>'
                                                                           );
  std::pair<CData *, bool> pairResult(
                                 &(
                                   *(
                                     pairInserted.first // get the iterator of the returned 'pair<iterator, bool>'
                                    ) // get 'pair<key_type, data_type>' pointered by the iterator
                                  ).second, // get member 'data_type' of struct 'pair<key_type, data_type>'
                                 pairInserted.second // get the bool of the returned 'pair<iterator, bool>'
                                     );
  return pairResult;
}


ZLS_END_NAMESPACE


#endif

