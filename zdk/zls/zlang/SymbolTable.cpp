/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/SymbolTable.cpp,v $
 *
 * $Date: 2001/11/14 19:03:08 $
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


#include <zls/zlang/SymbolTable.hpp>


ZLS_BEGIN_NAMESPACE(zlang)


/*******************************************************************************
 * class CSymbol
 ******************************************************************************/
/* static member */
const std::string CSymbol::_SastringTagTexts[] = {
  "global function",
  "global variable",
  "local variable",
  "parameter"
};


const std::string & CSymbol::SymbolTagToString(TSymbolTag eTag)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSymbol::SymbolTagToString()");
  LogAssert1(eTag <= 3, "Too big tag value '%d'", eTag);
  return(_SastringTagTexts[eTag]);
}


CSymbol::CSymbol(TSymbolTag eSymbolTag, const std::string & rstringName,
                 const std::string & rstringNamespace, int nNestLevel,
                 CSymbolAttributes * pciAttributes)
  :_hmapNextNest(_nDefaultBuckets),
   _eSymbolTag(eSymbolTag),
   _stringSymbolName(rstringName),
   _stringNamespace(rstringNamespace),
   _nNestLevel(nNestLevel),
   _autoAttributes(pciAttributes)
{ }


CSymbol::~CSymbol()
{ }


void CSymbol::DumpDetail()
{
  std::cout << "Symbol Tag: " << SymbolTagToString(_eSymbolTag) << std::endl;
  std::cout << "Symbol Name: " << _stringNamespace << "::" << _stringSymbolName << std::endl ;
  std::cout << "Nest Level: " << _nNestLevel << std::endl ;
  std::cout << "Attributes:" << std::endl ;
  _autoAttributes->DumpDetail();
}


/*******************************************************************************
 * class CSymbolTable
 ******************************************************************************/
CSymbol_auto & CSymbolTable::InsertSymbol(const std::vector<std::string> & rvectorFindNames,
                                          CSymbolAttributes * pciAttributes)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSymbolTable::InsertSymbol");
  int nNestLevel = 0;
  std::string stringUnifyName;
  int nSize = rvectorFindNames.size();
  // 为什么GetFirstNestHashMap不返回&呢，那是因为我们必须随着lookup逐渐深入而不
  // 断地得到下一层的hash_map，而引用型变量在第一次被初始化后值就固定了，即使你
  // 对它进行了改变也没有效果。如果采用既非引用变量也非指针型变量，得到的是hash_map
  // 的deep copy，但是我们还要插入呀！
  CSymbolTable::CSymbolHashMap * phmap = GetFirstNestHashMap();

  std::vector<std::string>::const_iterator it;
  for (it = rvectorFindNames.begin(); it != rvectorFindNames.end(); ++it)
  {
    std::string stringName = *it;
    std::string stringNamespace = stringUnifyName;

    ++nNestLevel;
    if (nNestLevel == 1)
    {
      stringUnifyName = stringName;
    }
    else
    {
      stringUnifyName += "::";
      stringUnifyName += stringName;
    }

    try {
      CSymbol_auto & rautoSymbol = _FindSymbol(phmap, stringName, stringUnifyName);

      /*
       * 前面几层的name查找成功，甚至最后一层的name也查找成功.
       */
      LogDebug3(("Symbol '%s' is found !\n", stringUnifyName.c_str()));
      if (nNestLevel < nSize)
      {
        // class CSymbol采用的是hash_map对象实例member，所以hmap永远不为0.
        phmap = rautoSymbol->GetNextNestHashMap();
      }
      else
      /* 最后一层的name已经存在表中 */
      {
        throw ESymbolInsertFailure(__FILE__, __PRETTY_FUNCTION__, __LINE__, stringUnifyName);
      }
    }
    catch (ESymbolNotFound & e) {
    /* 应该是已到达最后一层的name才可能的. */
      LogDebug3(("Inserting a new Symbol '%s' !\n", stringUnifyName.c_str()));

      LogAssert1(nNestLevel == nSize, "Symbol: %s", stringUnifyName.c_str());

      CSymbol_auto & rautoSymbol = _InsertSymbol(phmap, stringName, stringNamespace,
                                                 nNestLevel, pciAttributes);
      return(rautoSymbol);
    }
  }
}


CSymbol_auto & CSymbolTable::_InsertSymbol(CSymbolTable::CSymbolHashMap * phmap,
                                           const std::string & rstringName,
                                           const std::string & rstringNamespace,
                                           int nNestLevel,
                                           CSymbolAttributes * pciAttributes)
{
  CSymbol_auto autoSymbol = new CSymbol(pciAttributes->GetSymbolTag(),
                                        rstringName, rstringNamespace,
                                        nNestLevel, pciAttributes);
  return(
         *(
           (
            phmap->insert(                           // a 'pair<key_type, data_type>'
                          CSymbolTable::CSymbolHashMap::value_type(rstringName, autoSymbol)
                         )  // return a 'pair<iterator, bool>'
           ).first  // get the iterator of the returned 'pair<iterator, bool>'
          )  // get 'pair<key_type, data_type>' pointered by the iterator
        ).second;  // get member 'data_type' of struct 'pair<key_type, data_type>'

  // 注意: 'pair<>' is a struct template, 'first' and 'second' is
  //       member variable of struct.
}


CSymbol_auto & CSymbolTable::_FindSymbol(CSymbolTable::CSymbolHashMap * phmap,
                                         const std::string & rstringName,
                                         const std::string & rstringUnifyName)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSymbolTable::FindSymbol");

  CSymbolTable::CSymbolHashMap::iterator it;
  if (phmap && (it = phmap->find(rstringName)) != phmap->end())
  {
    return((*it).second);
  }
  else
  {
    throw ESymbolNotFound(__FILE__, __PRETTY_FUNCTION__, __LINE__, rstringUnifyName);
  }
}


CSymbol_auto & CSymbolTable::FindSymbol(const std::vector<std::string> & rvectorFindNames)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CSymbolTable::FindSymbol");

  CSymbolTable::CSymbolHashMap * phmap = GetFirstNestHashMap();
  int nNestLevel = 0;
  std::string stringUnifyName;
  CSymbol_auto * pautoSymbol = (CSymbol_auto *)0;

  std::vector<std::string>::const_iterator it;
  for (it = rvectorFindNames.begin(); it != rvectorFindNames.end(); ++it)
  {
    std::string stringName = *it;

    ++nNestLevel;
    if (nNestLevel == 1)
    {
      stringUnifyName = stringName;
    }
    else
    {
      stringUnifyName += "::";
      stringUnifyName += stringName;
    }

    try {
      CSymbol_auto & rautoSymbol = _FindSymbol(phmap, stringName, stringUnifyName);
      // class CSymbol采用的是hash_map对象实例member，所以phmap永远不为0.
      phmap = rautoSymbol->GetNextNestHashMap();

      pautoSymbol = &rautoSymbol;
    }
    catch (ESymbolNotFound & e) {
      /* 某一层name查找失败 */
      throw;
    }
  }

  LogAssert0(pautoSymbol != 0, "Impossible mistake");

  return(*pautoSymbol);
}


void CSymbolTable::DumpDetail()
{
  CSymbolTable::CSymbolHashMap::iterator it;
                               // hash_map的iterator只能使用"!=?.end()"而不能是"<?.end()"
  for (it = _hmapFirstNest.begin(); it != _hmapFirstNest.end(); ++it)
  {
    CSymbol_auto & rautoSymbol = (*it).second;
    rautoSymbol->DumpDetail();
    std::cout << std::endl ;
    // class CSymbol采用的是hash_map对象实例member，所以hmap永远不为0.
    CSymbolTable::CSymbolHashMap * phmap = rautoSymbol->GetNextNestHashMap();
    _DumpDetail(phmap);
  }
}


void CSymbolTable::_DumpDetail(CSymbolTable::CSymbolHashMap * phmap)
{
  CSymbolTable::CSymbolHashMap::iterator it;
  for (it = phmap->begin(); it != phmap->end(); ++it)
  {
    CSymbol_auto & rautoSymbol = (*it).second;
    rautoSymbol->DumpDetail();
    std::cout << std::endl ;
    // class CSymbol采用的是hash_map对象实例member，所以hmap永远不为0.
    phmap = rautoSymbol->GetNextNestHashMap();
    _DumpDetail(phmap);
  }
}


std::string CSymbolTable::ToUnifyName(const std::vector<std::string> & rvectorFindNames)
{
  std::string stringUnifyName;
  std::vector<std::string>::const_iterator it;
  for (it = rvectorFindNames.begin(); it != rvectorFindNames.end(); ++it)
  {
    stringUnifyName += "::";
    stringUnifyName += *it;
  }
  return(stringUnifyName);
}


/*******************************************************************************
 * class CSymbolAttributes
 ******************************************************************************/
CSymbolAttributes::~CSymbolAttributes()
{ }


/*******************************************************************************
 * class CFunctionSymbolAttributes
 ******************************************************************************/
CFunctionSymbolAttributes::~CFunctionSymbolAttributes()
{ }

void CFunctionSymbolAttributes::DumpDetail()
{
  std::cout << "  Return Signature: " << _stringReturnSignature << std::endl;
  std::cout << "  Function Signature: " << _stringFunctionSignature << std::endl;

/*
  std::vector<CParameter>::iterator it;
  for (it = _vectorParameters.begin(); it < _vectorParameters.end(); ++it)
  {
    std::cout << "  Parameter: Signature: " << (*it).first << " , Name: " << (*it).second << std::endl;
  }
 */
}


/*******************************************************************************
 * class CGlobalFunctionSymbolAttributes
 ******************************************************************************/
CGlobalFunctionSymbolAttributes::~CGlobalFunctionSymbolAttributes()
{ }

void CGlobalFunctionSymbolAttributes::DumpDetail()
{
  CFunctionSymbolAttributes::DumpDetail();
  std::cout << "  Access modifier: " << _eAccessModifierTag << std::endl;
}


/*******************************************************************************
 * class CVariableSymbolAttributes
 ******************************************************************************/
CVariableSymbolAttributes::~CVariableSymbolAttributes()
{ }

void CVariableSymbolAttributes::DumpDetail()
{
  std::cout << "  Variable Signature: " << _stringVariableSignature << std::endl;
}


/*******************************************************************************
 * class CGlobalVariableSymbolAttributes
 ******************************************************************************/
CGlobalVariableSymbolAttributes::~CGlobalVariableSymbolAttributes()
{ }

void CGlobalVariableSymbolAttributes::DumpDetail()
{
  CVariableSymbolAttributes::DumpDetail();
  std::cout << "  Access modifier: " << _eAccessModifierTag << std::endl;
}


/*******************************************************************************
 * class CStackVariableSymbolAttributes
 ******************************************************************************/
CStackVariableSymbolAttributes::~CStackVariableSymbolAttributes()
{ }

void CStackVariableSymbolAttributes::DumpDetail()
{
  CVariableSymbolAttributes::DumpDetail();
  if (_nBPOffset > 0)
  {
    std::cout << "  Local Variable: ";
  }
  else
  {
    std::cout << "  Parameter: ";
  }
  std::cout << "Index: " << _nIndex << " , Offset from BP: " << _nBPOffset << std::endl;
}


/*******************************************************************************
 * class CLocalVariableSymbolAttributes
 ******************************************************************************/
CLocalVariableSymbolAttributes::~CLocalVariableSymbolAttributes()
{ }

void CLocalVariableSymbolAttributes::DumpDetail()
{
  CStackVariableSymbolAttributes::DumpDetail();
}


/*******************************************************************************
 * class CParameterSymbolAttributes
 ******************************************************************************/
CParameterSymbolAttributes::~CParameterSymbolAttributes()
{ }

void CParameterSymbolAttributes::DumpDetail()
{
  CStackVariableSymbolAttributes::DumpDetail();
}


ZLS_END_NAMESPACE

