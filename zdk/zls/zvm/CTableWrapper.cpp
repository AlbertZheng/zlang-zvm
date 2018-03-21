/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/CTableWrapper.cpp,v $
 *
 * $Date: 2001/11/02 19:49:44 $
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


#include <zls/zvm/CTableWrapper.hpp>
#include <zls/zvm/CSlot.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


CTableWrapper::CTableWrapper(char chTableElementTypeTag)
  : _hmapTable(_SCnDefaultBuckets),
    _chTableElementTypeTag(chTableElementTypeTag)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CTableWrapper::CTableWrapper()");
  // 现在还不允许表中表
  LogAssert1(chTableElementTypeTag != CchZVM_TABLE_TYPE_TAG,
             "Invalid table element type tag '%c'",
             chTableElementTypeTag);
}


CTableWrapper::~CTableWrapper()
{
  CHashMap::iterator it;
  for (it = _hmapTable.begin(); it != _hmapTable.end(); ++it)
  {
    delete (*it).second;
  }
}


CTableWrapper & CTableWrapper::operator=(const CTableWrapper & rciRight)
{
  if (this == &rciRight)
  {
    return *this;
  }

  // 先清空以前的内容
  CHashMap::iterator it1;
  for (it1 = _hmapTable.begin(); it1 != _hmapTable.end(); ++it1)
  {
    delete (*it1).second;
  }
  _hmapTable.clear();

  // copy tag
  _chTableElementTypeTag = rciRight._chTableElementTypeTag;
  // deep copy content
  CHashMap::const_iterator it2;
  for (it2 = rciRight._hmapTable.begin(); it2 != rciRight._hmapTable.end(); ++it2)
  {
    CSlot * pciSourceSlot = (*it2).second;
    // Deep copy content
    CSlot * pciSlot = new __OPTION(_THROW) CSlot(*pciSourceSlot);
    _hmapTable.insert(       // a 'pair<key_type, data_type>'
                      CHashMap::value_type((*it2).first, pciSlot)
                     );  // return a 'pair<iterator, bool>'
  }
  return *this;
}


bool CTableWrapper::operator==(const CTableWrapper & rciRight) const
{
  if (this == &rciRight)
  {
    return true;
  }

  if (_chTableElementTypeTag != rciRight._chTableElementTypeTag ||
      _hmapTable.size() != rciRight._hmapTable.size())
  {
    return false;
  }

  // 注：我想如果"桶"数一样的话，那么如果同时两个Hash table的内容也是完全一样
  // （key和value）的话，则应该是可以采用一格一格比较的.
  CHashMap::const_iterator it1, it2;
  for (it1 = _hmapTable.begin(), it2 = rciRight._hmapTable.begin();
       it1 != _hmapTable.end();
       ++it1, ++it2)
  {
                                     // 注：Deep compare content
    if ((*it1).first != (*it2).first || *((*it1).second) != *((*it2).second))
    {
      return false;
    }
  }
  return true;
}


CSlot * CTableWrapper::operator[](bool bKey)
{
  CZVMString ciString = ZVM_BOOL_TO_ZVM_STRING(bKey);

  CHashMap::iterator it;
  if ((it = _hmapTable.find(ciString)) != _hmapTable.end())
  // 如果这个元素已经被插入过了，则直接返回它
  {
    return (*it).second;
  }

  // 否则立即创建一个新元素
  CSlot * pciSlot = new __OPTION(_THROW) CSlot(_chTableElementTypeTag);
  return (
          *(
            (
             _hmapTable.insert(       // a 'pair<key_type, data_type>'
                               CHashMap::value_type(ciString, pciSlot)
                              )  // return a 'pair<iterator, bool>'
            ).first
           )  // get 'pair<key_type, data_type> &' by the iterator
         ).second;  // get 'data_type' of 'pair<key_type, data_type>'
}


CSlot * CTableWrapper::operator[](UCHAR uchKey)
{
  CZVMString ciString = ZVM_BYTE_TO_ZVM_STRING(uchKey);

  CHashMap::iterator it;
  if ((it = _hmapTable.find(ciString)) != _hmapTable.end())
  // 如果这个元素已经被插入过了，则直接返回它
  {
    return (*it).second;
  }

  // 否则立即创建一个新元素
  CSlot * pciSlot = new __OPTION(_THROW) CSlot(_chTableElementTypeTag);
  return (
          *(
            (
             _hmapTable.insert(       // a 'pair<key_type, data_type>'
                               CHashMap::value_type(ciString, pciSlot)
                              )  // return a 'pair<iterator, bool>'
            ).first
           )  // get 'pair<key_type, data_type> &' by the iterator
         ).second;  // get 'data_type' of 'pair<key_type, data_type>'
}


CSlot * CTableWrapper::operator[](SDWORD sdwKey)
{
  CZVMString ciString = ZVM_SDWORD_TO_ZVM_STRING(sdwKey);

  CHashMap::iterator it;
  if ((it = _hmapTable.find(ciString)) != _hmapTable.end())
  // 如果这个元素已经被插入过了，则直接返回它
  {
    return (*it).second;
  }

  // 否则立即创建一个新元素
  CSlot * pciSlot = new __OPTION(_THROW) CSlot(_chTableElementTypeTag);
  return (
          *(
            (
             _hmapTable.insert(       // a 'pair<key_type, data_type>'
                               CHashMap::value_type(ciString, pciSlot)
                              )  // return a 'pair<iterator, bool>'
            ).first
           )  // get 'pair<key_type, data_type> &' by the iterator
         ).second;  // get 'data_type' of 'pair<key_type, data_type>'
}


CSlot * CTableWrapper::operator[](UDWORD udwKey)
{
  CZVMString ciString = ZVM_UDWORD_TO_ZVM_STRING(udwKey);

  CHashMap::iterator it;
  if ((it = _hmapTable.find(ciString)) != _hmapTable.end())
  // 如果这个元素已经被插入过了，则直接返回它
  {
    return (*it).second;
  }

  // 否则立即创建一个新元素
  CSlot * pciSlot = new __OPTION(_THROW) CSlot(_chTableElementTypeTag);
  return (
          *(
            (
             _hmapTable.insert(       // a 'pair<key_type, data_type>'
                               CHashMap::value_type(ciString, pciSlot)
                              )  // return a 'pair<iterator, bool>'
            ).first
           )  // get 'pair<key_type, data_type> &' by the iterator
         ).second;  // get 'data_type' of 'pair<key_type, data_type>'
}


CSlot * CTableWrapper::operator[](SQWORD sqwKey)
{
  CZVMString ciString = ZVM_SQWORD_TO_ZVM_STRING(sqwKey);

  CHashMap::iterator it;
  if ((it = _hmapTable.find(ciString)) != _hmapTable.end())
  // 如果这个元素已经被插入过了，则直接返回它
  {
    return (*it).second;
  }

  // 否则立即创建一个新元素
  CSlot * pciSlot = new __OPTION(_THROW) CSlot(_chTableElementTypeTag);
  return (
          *(
            (
             _hmapTable.insert(       // a 'pair<key_type, data_type>'
                               CHashMap::value_type(ciString, pciSlot)
                              )  // return a 'pair<iterator, bool>'
            ).first
           )  // get 'pair<key_type, data_type> &' by the iterator
         ).second;  // get 'data_type' of 'pair<key_type, data_type>'
}


CSlot * CTableWrapper::operator[](UQWORD uqwKey)
{
  CZVMString ciString = ZVM_UQWORD_TO_ZVM_STRING(uqwKey);

  CHashMap::iterator it;
  if ((it = _hmapTable.find(ciString)) != _hmapTable.end())
  // 如果这个元素已经被插入过了，则直接返回它
  {
    return (*it).second;
  }

  // 否则立即创建一个新元素
  CSlot * pciSlot = new __OPTION(_THROW) CSlot(_chTableElementTypeTag);
  return (
          *(
            (
             _hmapTable.insert(       // a 'pair<key_type, data_type>'
                               CHashMap::value_type(ciString, pciSlot)
                              )  // return a 'pair<iterator, bool>'
            ).first
           )  // get 'pair<key_type, data_type> &' by the iterator
         ).second;  // get 'data_type' of 'pair<key_type, data_type>'
}


CSlot * CTableWrapper::operator[](double dfKey)
{
  CZVMString ciString = ZVM_DOUBLE_TO_ZVM_STRING(dfKey);

  CHashMap::iterator it;
  if ((it = _hmapTable.find(ciString)) != _hmapTable.end())
  // 如果这个元素已经被插入过了，则直接返回它
  {
    return (*it).second;
  }

  // 否则立即创建一个新元素
  CSlot * pciSlot = new __OPTION(_THROW) CSlot(_chTableElementTypeTag);
  return (
          *(
            (
             _hmapTable.insert(       // a 'pair<key_type, data_type>'
                               CHashMap::value_type(ciString, pciSlot)
                              )  // return a 'pair<iterator, bool>'
            ).first
           )  // get 'pair<key_type, data_type> &' by the iterator
         ).second;  // get 'data_type' of 'pair<key_type, data_type>'
}


CSlot * CTableWrapper::operator[](const CZVMString * pciStringKey)
{
  CHashMap::iterator it;
  if ((it = _hmapTable.find(*pciStringKey)) != _hmapTable.end())
  // 如果这个元素已经被插入过了，则直接返回它
  {
    return (*it).second;
  }

  // 否则立即创建一个新元素
  CSlot * pciSlot = new __OPTION(_THROW) CSlot(_chTableElementTypeTag);
  return (
          *(
            (
             _hmapTable.insert(       // a 'pair<key_type, data_type>'
                               CHashMap::value_type(*pciStringKey, pciSlot)
                              )  // return a 'pair<iterator, bool>'
            ).first
           )  // get 'pair<key_type, data_type> &' by the iterator
         ).second;  // get 'data_type' of 'pair<key_type, data_type>'
}


CSlot * CTableWrapper::operator[](const CZVMRope * pciRopeKey)
{
  CZVMString ciString = ZVM_ROPE_TO_ZVM_STRING(pciRopeKey);

  CHashMap::iterator it;
  if ((it = _hmapTable.find(ciString)) != _hmapTable.end())
  // 如果这个元素已经被插入过了，则直接返回它
  {
    return (*it).second;
  }

  // 否则立即创建一个新元素
  CSlot * pciSlot = new __OPTION(_THROW) CSlot(_chTableElementTypeTag);
  return (
          *(
            (
             _hmapTable.insert(       // a 'pair<key_type, data_type>'
                               CHashMap::value_type(ciString, pciSlot)
                              )  // return a 'pair<iterator, bool>'
            ).first
           )  // get 'pair<key_type, data_type> &' by the iterator
         ).second;  // get 'data_type' of 'pair<key_type, data_type>'
}


CSlot * CTableWrapper::operator[](const CZVMPPort * pciPPortKey)
{
  CZVMString ciString = ZVM_PPORT_TO_ZVM_STRING(pciPPortKey);

  CHashMap::iterator it;
  if ((it = _hmapTable.find(ciString)) != _hmapTable.end())
  // 如果这个元素已经被插入过了，则直接返回它
  {
    return (*it).second;
  }

  // 否则立即创建一个新元素
  CSlot * pciSlot = new __OPTION(_THROW) CSlot(_chTableElementTypeTag);
  return (
          *(
            (
             _hmapTable.insert(       // a 'pair<key_type, data_type>'
                               CHashMap::value_type(ciString, pciSlot)
                              )  // return a 'pair<iterator, bool>'
            ).first
           )  // get 'pair<key_type, data_type> &' by the iterator
         ).second;  // get 'data_type' of 'pair<key_type, data_type>'
}


CSlot * CTableWrapper::operator[](const CZVMIPv4Address * pciIPv4AddressKey)
{
  CZVMString ciString = ZVM_IPv4ADDRESS_TO_ZVM_STRING(pciIPv4AddressKey);

  CHashMap::iterator it;
  if ((it = _hmapTable.find(ciString)) != _hmapTable.end())
  // 如果这个元素已经被插入过了，则直接返回它
  {
    return (*it).second;
  }

  // 否则立即创建一个新元素
  CSlot * pciSlot = new __OPTION(_THROW) CSlot(_chTableElementTypeTag);
  return (
          *(
            (
             _hmapTable.insert(       // a 'pair<key_type, data_type>'
                               CHashMap::value_type(ciString, pciSlot)
                              )  // return a 'pair<iterator, bool>'
            ).first
           )  // get 'pair<key_type, data_type> &' by the iterator
         ).second;  // get 'data_type' of 'pair<key_type, data_type>'
}


ZLS_END_NAMESPACE

