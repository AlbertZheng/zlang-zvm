/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CSlot.hpp,v $
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


#ifndef _ZLS_zvm_CSlot_hpp_
#define _ZLS_zvm_CSlot_hpp_

#include <zls/zvm/Manifest.hpp>
#include <zls/zvm/ZVMRegister.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


#ifdef ENABLE_ZVM_DEBUG
  #define ZVM_SLOT_ASSERT(pciSlot, eTag, pszFile, pszFunc, nLine)       \
    pciSlot->SlotAssert(eTag, pszFile, pszFunc, nLine)
  #define ZVM_SLOT_MASK_ASSERT(pciSlot, eTag, pszFile, pszFunc, nLine)  \
    pciSlot->SlotMaskAssert(eTag, pszFile, pszFunc, nLine)
#else
  #define ZVM_SLOT_ASSERT(pciSlot, eTag, pszFile, pszFunc, nLine)
  #define ZVM_SLOT_MASK_ASSERT(pciSlot, eTag, pszFile, pszFunc, nLine)
#endif


/**
 * CSolt是各种存储结构（stack variable、global variable、table element）的基本原子.
 *
 * @note
 * <pre>
 * (1)当ZVM从stack上掸出一个CSlot时，如果发现其SLOT_TAG_NEED_GC被置位，则表示需要
 *    进行内存析构工作，然后再继续接着判断：
 *   (a)如果SLOT_TAG_ADDRESS也被置位了，则表示这是一个Object型的中间计算结果，
 *      取出其间接指向的那个CSlot，然后仿照下面的(b)进行析构;
 *   (b)如果SLOT_TAG_ADDRESS没有被置位，则判断SLOT_TAG_STRING_OBJECT等对象型的
 *      TAG被置位否，如是则做相应的析构;
 * (2)SLOT_TAG_ADDRESS和其它TAG进行OR在一起时，表示的是address of ?，例如：
 *    (SLOT_TAG_ADDRESS | SLOT_TAG_BOOL)表示为address of bool，以此类推.
 * (3)Obejct型variable的CSlot的TAG一定为(SLOT_TAG_NEED_GC | SLOT_TAG_对象类型).
 * (4)非Obejct型variable的CSlot的TAG中SLOT_TAG_NEED_GC没有被置位.
 * (5)load value后产生的CSlot的TAG与variable的使用方式一样.
 * (6)load address后产生的CSlot的TAG一定为(SLOT_TAG_ADDRESS | SLOT_TAG_类型)，
 *    且SLOT_TAG_NEED_GC一定没有被置位.
 * </pre>
 */
class CSlot {
  private:
    /**
     * Forbidden operator=().
     * @attention Deep copy content.
     * @attention 2001/6/20 - Forbidden.
     */
    CSlot & operator=(const CSlot & rciOther);

  public:
    enum TSlotTag {
      SLOT_TAG_BP_REGISTER_BIT = 1,  /**< 标识位，标识是否为BP register. */
      SLOT_TAG_PC_REGISTER_BIT = 2,  /**< 标识位，标识是否为PC register. */

      SLOT_TAG_BOOL_BIT = 4,  /**< 标识位，标识是否为bool. */
      SLOT_TAG_BYTE_BIT = 8,  /**< 标识位，标识是否为byte. */
      SLOT_TAG_SDWORD_BIT = 16,  /**< 标识位，标识是否为sdword. */
      SLOT_TAG_UDWORD_BIT = 32,  /**< 标识位，标识是否为udword. */
      SLOT_TAG_SQWORD_BIT = 64,  /**< 标识位，标识是否为sqword. */
      SLOT_TAG_UQWORD_BIT = 128,  /**< 标识位，标识是否为uqword. */
      SLOT_TAG_DOUBLE_BIT = 256,  /**< 标识位，标识是否为double. */
      SLOT_TAG_ROPE_OBJECT_BIT = 1024,  /**< 标识位，标识是否为rope. */
      SLOT_TAG_STRING_OBJECT_BIT = 2048,  /**< 标识位，标识是否为string. */
      SLOT_TAG_PPORT_OBJECT_BIT = 4096,  /**< 标识位，标识是否为pport. */
      SLOT_TAG_IPv4ADDRESS_OBJECT_BIT = 8192,  /**< 标识位，标识是否为ipv4address. */
      SLOT_TAG_TABLE_OBJECT_BIT = 16384,  /**< 标识位，标识是否为table. */

      SLOT_TAG_ADDRESS = 0x40000000,  /**< 标识位，标识是否为address. */
      SLOT_TAG_NEED_GC = 0x80000000,  /**< 标识位，标识当pop时是否要对这个slot进行memory垃圾回收. */

      /**
       * @name 在程序中真正使用的enum值.
       */
      //@{
      SLOT_TAG_BP_REGISTER = SLOT_TAG_BP_REGISTER_BIT,
      SLOT_TAG_PC_REGISTER = (SLOT_TAG_NEED_GC | SLOT_TAG_PC_REGISTER_BIT),
      ///< @attention PC register是需要析构的.

      SLOT_TAG_VOID = 0,
      SLOT_TAG_BOOL = SLOT_TAG_BOOL_BIT,
      SLOT_TAG_BYTE = SLOT_TAG_BYTE_BIT,
      SLOT_TAG_SDWORD = SLOT_TAG_SDWORD_BIT,
      SLOT_TAG_UDWORD = SLOT_TAG_UDWORD_BIT,
      SLOT_TAG_SQWORD = SLOT_TAG_SQWORD_BIT,
      SLOT_TAG_UQWORD = SLOT_TAG_UQWORD_BIT,
      SLOT_TAG_DOUBLE = SLOT_TAG_DOUBLE_BIT,
      SLOT_TAG_ROPE_OBJECT = (SLOT_TAG_NEED_GC |SLOT_TAG_ROPE_OBJECT_BIT),
      SLOT_TAG_STRING_OBJECT = (SLOT_TAG_NEED_GC |SLOT_TAG_STRING_OBJECT_BIT),
      SLOT_TAG_PPORT_OBJECT = (SLOT_TAG_NEED_GC | SLOT_TAG_PPORT_OBJECT_BIT),
      SLOT_TAG_IPv4ADDRESS_OBJECT = (SLOT_TAG_NEED_GC | SLOT_TAG_IPv4ADDRESS_OBJECT_BIT),
      SLOT_TAG_TABLE_OBJECT = (SLOT_TAG_NEED_GC | SLOT_TAG_TABLE_OBJECT_BIT),

      SLOT_TAG_ADDRESS_OF_BOOL = (SLOT_TAG_ADDRESS | SLOT_TAG_BOOL_BIT),
      SLOT_TAG_ADDRESS_OF_BYTE = (SLOT_TAG_ADDRESS | SLOT_TAG_BYTE_BIT),
      SLOT_TAG_ADDRESS_OF_SDWORD = (SLOT_TAG_ADDRESS | SLOT_TAG_SDWORD_BIT),
      SLOT_TAG_ADDRESS_OF_UDWORD = (SLOT_TAG_ADDRESS | SLOT_TAG_UDWORD_BIT),
      SLOT_TAG_ADDRESS_OF_SQWORD = (SLOT_TAG_ADDRESS | SLOT_TAG_SQWORD_BIT),
      SLOT_TAG_ADDRESS_OF_UQWORD = (SLOT_TAG_ADDRESS | SLOT_TAG_UQWORD_BIT),
      SLOT_TAG_ADDRESS_OF_DOUBLE = (SLOT_TAG_ADDRESS | SLOT_TAG_DOUBLE_BIT),
      SLOT_TAG_ADDRESS_OF_ROPE_OBJECT = (SLOT_TAG_ADDRESS | SLOT_TAG_ROPE_OBJECT_BIT),
      SLOT_TAG_ADDRESS_OF_STRING_OBJECT = (SLOT_TAG_ADDRESS | SLOT_TAG_STRING_OBJECT_BIT),
      SLOT_TAG_ADDRESS_OF_PPORT_OBJECT = (SLOT_TAG_ADDRESS | SLOT_TAG_PPORT_OBJECT_BIT),
      SLOT_TAG_ADDRESS_OF_IPv4ADDRESS_OBJECT = (SLOT_TAG_ADDRESS | SLOT_TAG_IPv4ADDRESS_OBJECT_BIT),
      SLOT_TAG_ADDRESS_OF_TABLE_OBJECT = (SLOT_TAG_ADDRESS | SLOT_TAG_TABLE_OBJECT_BIT)
      //@}
    };

  private:
    TSlotTag _eSlotTag;
    union {
      bool _b;
      UCHAR _uch;
      SDWORD _sdw;
      UDWORD _udw;
      SQWORD _sqw;
      UQWORD _uqw;
      double _df;
      CZVMRope * _pciRope;
      CZVMString * _pciString;
      CZVMPPort * _pciPPort;
      CZVMIPv4Address * _pciIPv4Address;
      CZVMTable * _pciTable;

      /**
       * 对于非Object型的member，pvAddress是pointer of instance member，例如&_b
       * 或&_uch或...；对于Object型的member，pvAddress是pointer of pointer member，
       * 例如&_pciString或&_pciPPort或...
       */
      void * _pvAddress;

      CSlot * _pciBP;
      CPCRegister * _pciPC;
    };

  public:
    #ifdef ENABLE_ZVM_DEBUG
    /**
     * Slot的Tag为我们希望的Tag.
     *
     * @throw zfc::EPanic 当不是我们希望的Tag时.
     */
    void SlotAssert(TSlotTag eAssertedTag,
                    const char * pszFileName,
                    const char * pszFuncName,
                    const int nLineNumber) const;

    /**
     * Slot的Tag中有我们希望的Tag-Mask.
     *
     * @throw zfc::EPanic 当没有我们希望的Tag-Mask时.
     */
    void SlotMaskAssert(TSlotTag eAssertedTagMask,
                        const char * pszFileName,
                        const char * pszFuncName,
                        const int nLineNumber) const;
    #endif

    TSlotTag GetSlotTag() const
    {
      return _eSlotTag;
    }

    /**
     * @name Store Value.
     */
    //@{
    void StoreBool(bool b)
    {
      _b = b;
    }

    void StoreByte(UCHAR uch)
    {
      _uch = uch;
    }

    void StoreSDWORD(SDWORD sdw)
    {
      _sdw = sdw;
    }

    void StoreUDWORD(UDWORD udw)
    {
      _udw = udw;
    }

    void StoreSQWORD(SQWORD sqw)
    {
      _sqw = sqw;
    }

    void StoreUQWORD(UQWORD uqw)
    {
      _uqw = uqw;
    }

    void StoreDouble(double df)
    {
      _df = df;
    }

    /** @attention Deep copy object content. */
    void StoreStringObject(const CZVMString * pciString)
    {
      *_pciString = *pciString;
    }

    /** @attention Deep copy object content. */
    void StoreRopeObject(const CZVMRope * pciRope)
    {
      *_pciRope = *pciRope;
    }

    /** @attention Deep copy object content. */
    void StorePPortObject(const CZVMPPort * pciPPort)
    {
      *_pciPPort = *pciPPort;
    }

    /** @attention Deep copy object content. */
    void StoreIPv4AddressObject(const CZVMIPv4Address * pciIPv4Address)
    {
      *_pciIPv4Address = *pciIPv4Address;
    }

    /** @attention Deep copy object content. */
    void StoreTableObject(const CZVMTable * pciTable)
    {
      *_pciTable = *pciTable;
    }
    //@}

    /**
     * @name Store Address.
     */
    //@{
    void StoreBoolAddress(bool * pb)
    {
      _pvAddress = pb;
    }

    void StoreByteAddress(UCHAR * puch)
    {
      _pvAddress = puch;
    }

    void StoreSDWORDAddress(SDWORD * psdw)
    {
      _pvAddress = psdw;
    }

    void StoreUDWORDAddress(UDWORD * pudw)
    {
      _pvAddress = pudw;
    }

    void StoreSQWORDAddress(SQWORD * psqw)
    {
      _pvAddress = psqw;
    }

    void StoreUQWORDAddress(UQWORD * puqw)
    {
      _pvAddress = puqw;
    }

    void StoreDoubleAddress(double * pdf)
    {
      _pvAddress = pdf;
    }

    void StoreStringObjectAddress(CZVMString ** ppciString)
    {
      _pvAddress = ppciString;
    }

    void StoreRopeObjectAddress(CZVMRope ** ppciRope)
    {
      _pvAddress = ppciRope;
    }

    void StorePPortObjectAddress(CZVMPPort ** ppciPPort)
    {
      _pvAddress = ppciPPort;
    }

    void StoreIPv4AddressObjectAddress(CZVMIPv4Address ** ppciIPv4Address)
    {
      _pvAddress = ppciIPv4Address;
    }

    void StoreTableObjectAddress(CZVMTable ** ppciTable)
    {
      _pvAddress = ppciTable;
    }
    //@}

    /**
     * @name IndirectStore Value.
     */
    //@{
    void IndirectStoreBool(bool b)
    {
      *(static_cast<bool *>(_pvAddress)) = b;
    }

    void IndirectStoreByte(UCHAR uch)
    {
      *(static_cast<UCHAR *>(_pvAddress)) = uch;
    }

    void IndirectStoreSDWORD(SDWORD sdw)
    {
      *(static_cast<SDWORD *>(_pvAddress)) = sdw;
    }

    void IndirectStoreUDWORD(UDWORD udw)
    {
      *(static_cast<UDWORD *>(_pvAddress)) = udw;
    }

    void IndirectStoreSQWORD(SQWORD sqw)
    {
      *(static_cast<SQWORD *>(_pvAddress)) = sqw;
    }

    void IndirectStoreUQWORD(UQWORD uqw)
    {
      *(static_cast<UQWORD *>(_pvAddress)) = uqw;
    }

    void IndirectStoreDouble(double df)
    {
      *(static_cast<double *>(_pvAddress)) = df;
    }

    /** @attention Deep copy object content. */
    void IndirectStoreStringObject(const CZVMString * pciString)
    {
      **(static_cast<CZVMString **>(_pvAddress)) = *pciString;
    }

    /** @attention Deep copy object content. */
    void IndirectStoreRopeObject(const CZVMRope * pciRope)
    {
      **(static_cast<CZVMRope **>(_pvAddress)) = *pciRope;
    }

    /** @attention Deep copy object content. */
    void IndirectStorePPortObject(const CZVMPPort * pciPPort)
    {
      **(static_cast<CZVMPPort **>(_pvAddress)) = *pciPPort;
    }

    /** @attention Deep copy object content. */
    void IndirectStoreIPv4AddressObject(const CZVMIPv4Address * pciIPv4Address)
    {
      **(static_cast<CZVMIPv4Address **>(_pvAddress)) = *pciIPv4Address;
    }

    /** @attention Deep copy object content. */
    void IndirectStoreTableObject(const CZVMTable * pciTable)
    {
      **(static_cast<CZVMTable **>(_pvAddress)) = *pciTable;
    }
    //@}

    /**
     * @name Get Value.
     */
    //@{
    CSlot * GetSavedBPRegister()
    {
      return _pciBP;
    }

    CPCRegister & GetSavedPCRegister()
    {
      return *_pciPC;
    }

    bool GetBool()
    {
      return _b;
    }

    UCHAR GetByte()
    {
      return _uch;
    }

    SDWORD GetSDWORD()
    {
      return _sdw;
    }

    UDWORD GetUDWORD()
    {
      return _udw;
    }

    SQWORD GetSQWORD()
    {
      return _sqw;
    }

    UQWORD GetUQWORD()
    {
      return _uqw;
    }

    double GetDouble()
    {
      return _df;
    }

    CZVMString * GetStringObject()
    {
      return _pciString;
    }

    CZVMRope * GetRopeObject()
    {
      return _pciRope;
    }

    CZVMPPort * GetPPortObject()
    {
      return _pciPPort;
    }

    CZVMIPv4Address * GetIPv4AddressObject()
    {
      return _pciIPv4Address;
    }

    CZVMTable * GetTableObject()
    {
      return _pciTable;
    }

    void * GetIndirectAddress()
    {
      return _pvAddress;
    }
    //@}

    /**
     * @name Get Address.
     */
    //@{
    bool * GetBoolAddress()
    {
      return &_b;
    }

    UCHAR * GetByteAddress()
    {
      return &_uch;
    }

    SDWORD * GetSDWORDAddress()
    {
      return &_sdw;
    }

    UDWORD * GetUDWORDAddress()
    {
      return &_udw;
    }

    SQWORD * GetSQWORDAddress()
    {
      return &_sqw;
    }

    UQWORD * GetUQWORDAddress()
    {
      return &_uqw;
    }

    double * GetDoubleAddress()
    {
      return &_df;
    }

    CZVMString ** GetStringObjectAddress()
    {
      return &_pciString;
    }

    CZVMRope ** GetRopeObjectAddress()
    {
      return &_pciRope;
    }

    CZVMIPv4Address ** GetIPv4AddressObjectAddress()
    {
      return &_pciIPv4Address;
    }

    CZVMPPort ** GetPPortObjectAddress()
    {
      return &_pciPPort;
    }

    CZVMTable ** GetTableObjectAddress()
    {
      return &_pciTable;
    }
    //@}

    /**
     * @name 将Slot的内容构造为所希望的缺省值.
     */
    //@{
    void ClearSlot()
    {
      _eSlotTag = SLOT_TAG_VOID;
    }

    void ConstructSlotByTypeSignature(const std::string & rstringTypeSignature);

    void ConstructSlotAsDefaultBool()
    {
      _eSlotTag = SLOT_TAG_BOOL;
      _b = true;
    }

    void ConstructSlotAsDefaultByte()
    {
      _eSlotTag = SLOT_TAG_BYTE;
      _uch = 0;
    }

    void ConstructSlotAsDefaultSDWORD()
    {
      _eSlotTag = SLOT_TAG_SDWORD;
      _sdw = 0;
    }

    void ConstructSlotAsDefaultUDWORD()
    {
      _eSlotTag = SLOT_TAG_UDWORD;
      _udw = 0;
    }

    void ConstructSlotAsDefaultSQWORD()
    {
      _eSlotTag = SLOT_TAG_SQWORD;
      _sqw = 0;
    }

    void ConstructSlotAsDefaultUQWORD()
    {
      _eSlotTag = SLOT_TAG_UQWORD;
      _uqw = 0;
    }

    void ConstructSlotAsDefaultDouble()
    {
      _eSlotTag = SLOT_TAG_DOUBLE;
      _df = 0;
    }

    void ConstructSlotAsDefaultStringObject()
    {
      _eSlotTag = SLOT_TAG_STRING_OBJECT;
      // 注意：由于在ZVM stack上，Slot都是可重复使用的Slot，因此之前其_pciString
      // 指向的memory应该必须在之前pop时就立即被free了.
      _pciString = new __OPTION(_THROW) CZVMString;
    }

    void ConstructSlotAsDefaultRopeObject()
    {
      _eSlotTag = SLOT_TAG_ROPE_OBJECT;
      // 注意：由于在ZVM stack上，Slot都是可重复使用的Slot，因此之前其_pciRope
      // 指向的memory应该必须在之前pop时就立即被free了.
      _pciRope = new __OPTION(_THROW) CZVMRope;
    }

    void ConstructSlotAsDefaultIPv4AddressObject()
    {
      _eSlotTag = SLOT_TAG_IPv4ADDRESS_OBJECT;
      _pciIPv4Address = new __OPTION(_THROW) CZVMIPv4Address;
    }

    void ConstructSlotAsDefaultPPortObject()
    {
      _eSlotTag = SLOT_TAG_PPORT_OBJECT;
      _pciPPort = new __OPTION(_THROW) CZVMPPort;
    }

    void ConstructSlotAsDefaultTableObject(char chTableElementTypeTag)
    {
      _eSlotTag = SLOT_TAG_TABLE_OBJECT;
      _pciTable = new __OPTION(_THROW) CZVMTable(chTableElementTypeTag);
    }
    //@}

    /**
     * @name 将Slot的内容构造为所希望的值.
     */
    //@{
    void ConstructSlotAsBool(bool b)
    {
      _eSlotTag = SLOT_TAG_BOOL;
      _b = b;
    }

    void ConstructSlotAsByte(UCHAR uch)
    {
      _eSlotTag = SLOT_TAG_BYTE;
      _uch = uch;
    }

    void ConstructSlotAsSDWORD(SDWORD sdw)
    {
      _eSlotTag = SLOT_TAG_SDWORD;
      _sdw = sdw;
    }

    void ConstructSlotAsUDWORD(UDWORD udw)
    {
      _eSlotTag = SLOT_TAG_UDWORD;
      _udw = udw;
    }

    void ConstructSlotAsSQWORD(SQWORD sqw)
    {
      _eSlotTag = SLOT_TAG_SQWORD;
      _sqw = sqw;
    }

    void ConstructSlotAsUQWORD(UQWORD uqw)
    {
      _eSlotTag = SLOT_TAG_UQWORD;
      _uqw = uqw;
    }

    void ConstructSlotAsDouble(double df)
    {
      _eSlotTag = SLOT_TAG_DOUBLE;
      _df = df;
    }

    /** @attention Deep copy content. */
    void ConstructSlotAsStringObject(const CZVMString * pciString)
    {
      _eSlotTag = SLOT_TAG_STRING_OBJECT;
      _pciString = new __OPTION(_THROW) CZVMString(*pciString);
    }

    /** @attention Deep copy content. */
    void ConstructSlotAsRopeObject(const CZVMRope * pciRope)
    {
      _eSlotTag = SLOT_TAG_ROPE_OBJECT;
      _pciRope = new __OPTION(_THROW) CZVMRope(*pciRope);
    }

    /** @attention Deep copy content. */
    void ConstructSlotAsIPv4AddressObject(const CZVMIPv4Address * pciIPv4Address)
    {
      _eSlotTag = SLOT_TAG_IPv4ADDRESS_OBJECT;
      _pciIPv4Address = new __OPTION(_THROW) CZVMIPv4Address(*pciIPv4Address);
    }

    /** @attention Deep copy content. */
    void ConstructSlotAsPPortObject(const CZVMPPort * pciPPort)
    {
      _eSlotTag = SLOT_TAG_PPORT_OBJECT;
      _pciPPort = new __OPTION(_THROW) CZVMPPort(*pciPPort);
    }

    /** @attention Deep copy content. */
    void ConstructSlotAsTableObject(const CZVMTable * pciTable)
    {
      _eSlotTag = SLOT_TAG_TABLE_OBJECT;
      _pciTable = new __OPTION(_THROW) CZVMTable(*pciTable);
    }

    void ConstructSlotAsSavedBPRegister(CSlot * pciCurrentBP)
    {
      _eSlotTag = SLOT_TAG_BP_REGISTER;
      _pciBP = pciCurrentBP;
    }

    /** @attention Deep copy content. */
    void ConstructSlotAsSavedPCRegister(const CPCRegister & rciCurrentPC)
    {
      _eSlotTag = SLOT_TAG_PC_REGISTER;
      _pciPC = new __OPTION(_THROW) CPCRegister(rciCurrentPC);
    }
    //@}

    /**
     * @name 将Slot的内容构造为所希望的地址类型.
     */
    //@{
    void ConstructSlotAsBoolAddress(bool * pb)
    {
      _eSlotTag = SLOT_TAG_ADDRESS_OF_BOOL;
      _pvAddress = pb;
    }

    void ConstructSlotAsByteAddress(UCHAR * puch)
    {
      _eSlotTag = SLOT_TAG_ADDRESS_OF_BYTE;
      _pvAddress = puch;
    }

    void ConstructSlotAsSDWORDAddress(SDWORD * psdw)
    {
      _eSlotTag = SLOT_TAG_ADDRESS_OF_SDWORD;
      _pvAddress = psdw;
    }

    void ConstructSlotAsUDWORDAddress(UDWORD * pudw)
    {
      _eSlotTag = SLOT_TAG_ADDRESS_OF_UDWORD;
      _pvAddress = pudw;
    }

    void ConstructSlotAsSQWORDAddress(SQWORD * psqw)
    {
      _eSlotTag = SLOT_TAG_ADDRESS_OF_SQWORD;
      _pvAddress = psqw;
    }

    void ConstructSlotAsUQWORDAddress(UQWORD * puqw)
    {
      _eSlotTag = SLOT_TAG_ADDRESS_OF_UQWORD;
      _pvAddress = puqw;
    }

    void ConstructSlotAsDoubleAddress(double * pdf)
    {
      _eSlotTag = SLOT_TAG_ADDRESS_OF_DOUBLE;
      _pvAddress = pdf;
    }

    void ConstructSlotAsStringObjectAddress(CZVMString ** ppciString)
    {
      _eSlotTag = SLOT_TAG_ADDRESS_OF_STRING_OBJECT;
      _pvAddress = ppciString;
    }

    void ConstructSlotAsRopeObjectAddress(CZVMRope ** ppciRope)
    {
      _eSlotTag = SLOT_TAG_ADDRESS_OF_ROPE_OBJECT;
      _pvAddress = ppciRope;
    }

    void ConstructSlotAsIPv4AddressObjectAddress(CZVMIPv4Address ** ppIPv4Address)
    {
      _eSlotTag = SLOT_TAG_ADDRESS_OF_IPv4ADDRESS_OBJECT;
      _pvAddress = ppIPv4Address;
    }

    void ConstructSlotAsPPortObjectAddress(CZVMPPort ** ppPPort)
    {
      _eSlotTag = SLOT_TAG_ADDRESS_OF_PPORT_OBJECT;
      _pvAddress = ppPPort;
    }

    void ConstructSlotAsTableObjectAddress(CZVMTable ** ppTable)
    {
      _eSlotTag = SLOT_TAG_ADDRESS_OF_TABLE_OBJECT;
      _pvAddress = ppTable;
    }
    //@}

    /**
     * @name Quick地将Slot的内容构造为所希望的值.
     * @attention 这些methods只能用于CFunctionInvokeInterface向ZVM传递reference
     * argument时，以及2001/7/17新增加的quickConstructStringObject等指令.
     */
    //@{
    void QuickConstructSlotAsStringObject(CZVMString * pciString)
    {
      _eSlotTag = SLOT_TAG_STRING_OBJECT;
      _pciString = pciString;
    }

    void QuickConstructSlotAsRopeObject(CZVMRope * pciRope)
    {
      _eSlotTag = SLOT_TAG_ROPE_OBJECT;
      _pciRope = pciRope;
    }

    void QuickConstructSlotAsIPv4AddressObject(CZVMIPv4Address * pciIPv4Address)
    {
      _eSlotTag = SLOT_TAG_IPv4ADDRESS_OBJECT;
      _pciIPv4Address = pciIPv4Address;
    }

    void QuickConstructSlotAsPPortObject(CZVMPPort * pciPPort)
    {
      _eSlotTag = SLOT_TAG_PPORT_OBJECT;
      _pciPPort = pciPPort;
    }

    void QuickConstructSlotAsTableObject(CZVMTable * pciTable)
    {
      _eSlotTag = SLOT_TAG_TABLE_OBJECT;
      _pciTable = pciTable;
    }
    //@}

    static void TypeSignatureToSlotTag(const std::vector<std::string> & rvectorSourceSignatures,
                                       std::vector<TSlotTag> & rvectorToSlotTags);
    static TSlotTag TypeSignatureToSlotTag(const std::string & rstringSourceSignature);

    /**
     * operator==().
     * @attention Deep testing content.
     */
    bool operator==(const CSlot & rciOther) const;

    /**
     * operator!=().
     * @attention Deep testing content.
     */
    bool operator!=(const CSlot & rciOther) const
    { return ! operator==(rciOther); }

    /** Default constructor. */
    CSlot()
      : _eSlotTag(SLOT_TAG_VOID),
        _uqw(0)
    { }

    explicit CSlot(const std::string & rstringTypeSignature)
    {
      ConstructSlotByTypeSignature(rstringTypeSignature);
    }

    explicit CSlot(char chTypeTag)
    {
      ConstructSlotByTypeSignature(std::string(1, chTypeTag));
    }

    /**
     * Copy constructor.
     */
    CSlot(const CSlot & rciOther);

    /**
     * Destructor.
     * @attention 从ZVM stack上pop出一个CSlot时，如果这个CSlot是需要进行内存析构
     * 工作的，则进行内存析构，然后记得将内部union的指针field的值再改为地址0.
     */
    ~CSlot();
};


ZLS_END_NAMESPACE


#endif

