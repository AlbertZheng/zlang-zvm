/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CTableWrapper.hpp,v $
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


#ifndef _ZLS_zvm_CTableWrapper_hpp_
#define _ZLS_zvm_CTableWrapper_hpp_

#include <zls/zvm/Manifest.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


// forward declaration
class CSlot;


/**
 * ZVM的table类型的wrapper类.
 */
class CTableWrapper {
  public:
    typedef std::hash_map<CZVMString, CSlot *,
                          MAKE_ZVM_STRING_HASH, std::equal_to<CZVMString> > CHashMap;

  private:
    static const CHashMap::size_type _SCnDefaultBuckets = 16;
    CHashMap _hmapTable;

    /**
     * Table Element的signature tag.
     */
    char _chTableElementTypeTag;

  public:
    char GetTableElementTypeTag() const
    {
      return _chTableElementTypeTag;
    }

    /**
     * Reimplement overload operator '='.
     *
     * @attention Deep copy.
     */
    CTableWrapper & operator=(const CTableWrapper & rciRight);

    /**
     * Reimplement overload operator '=='.
     *
     * @attention Deep testing content.
     */
    bool operator==(const CTableWrapper & rciRight) const;

    /**
     * Reimplement overload operator '!='.
     *
     * @attention Deep testing content.
     */
    bool operator!=(const CTableWrapper & rciRight) const
    { return ! operator==(rciRight); }

    /**
     * @name Overload operator '[]'.
     *
     * @attention 如果原来table中没有这个key对应的value，则会立即自动插入一个
     * default的value，然后再返回它.
     *
     * @throw zfc::EOutOfMemory.
     */
    //@{
    CSlot * operator[](bool bKey);
    CSlot * operator[](UCHAR uchKey);
    CSlot * operator[](SDWORD sdwKey);
    CSlot * operator[](UDWORD udwKey);
    CSlot * operator[](SQWORD sqwKey);
    CSlot * operator[](UQWORD uqwKey);
    CSlot * operator[](double dfKey);
    CSlot * operator[](const CZVMString * pciStringKey);
    CSlot * operator[](const CZVMRope * pciRopeKey);
    CSlot * operator[](const CZVMPPort * pciPPortKey);
    CSlot * operator[](const CZVMIPv4Address * pciIPv4AddressKey);
    //@}

    /**
     * 将作为"fJump"的判断method.
     *
     * @attention 当内部Hash table的size大于0时返回true.
     */
    bool ToBool() const
    {
      return(_hmapTable.size() > 0);
    }

    /**
     * Default constructor.
     */
    explicit CTableWrapper(char chTableElementTypeTag);

    /**
     * Copy constructor.
     *
     * @attention Deep copy.
     */
    CTableWrapper(const CTableWrapper & rciRight)
    {
      operator=(rciRight);
    }

    ~CTableWrapper();
};


ZLS_END_NAMESPACE


#endif

