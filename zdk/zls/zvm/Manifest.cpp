/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/Manifest.cpp,v $
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


#include <zls/zvm/Manifest.hpp>
#include <zls/zfc/Exception.hpp>


ZLS_BEGIN_NAMESPACE(zvm)



/*
static const std::string CstringVOID_LITERAL           = "void";
static const std::string CstringBOOL_LITERAL           = "bool";
static const std::string CstringBYTE_LITERAL           = "byte";
static const std::string CstringSDWORD_LITERAL         = "sdword";
static const std::string CstringUDWORD_LITERAL         = "udword";
static const std::string CstringSQWORD_LITERAL         = "sqword";
static const std::string CstringUQWORD_LITERAL         = "uqword";
static const std::string CstringDOUBLE_LITERAL         = "double";
static const std::string CstringSTRING_LITERAL         = "string";
static const std::string CstringIPv4ADDR_LITERAL       = "ipaddress";
static const std::string CstringPPORT_LITERAL          = "pport";
static const std::string CstringBOOL_TABLE_LITERAL     = "table<bool>";
static const std::string CstringBYTE_TABLE_LITERAL     = "table<byte>";
static const std::string CstringSDWORD_TABLE_LITERAL   = "table<sdword>";
static const std::string CstringUDWORD_TABLE_LITERAL   = "table<udword>";
static const std::string CstringSQWORD_TABLE_LITERAL   = "table<sqword>";
static const std::string CstringUQWORD_TABLE_LITERAL   = "table<uqword>";
static const std::string CstringDOUBLE_TABLE_LITERAL   = "table<double>";
static const std::string CstringSTRING_TABLE_LITERAL   = "table<string>";
static const std::string CstringIPv4ADDR_TABLE_LITERAL = "table<ipaddress>";
static const std::string CstringPPORT_TABLE_LITERAL    = "table<pport>";
*/


const std::string & TypeSignatureToPrettyString(const std::string & rstringTypeSignature)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("TypeSignatureToPrettyString()");
  static std::map<std::string, std::string> _SGPrettyTypeTexts;
  static bool bYetNotInitialized = true;

  if (bYetNotInitialized)
  {
    #define __INSERT_PRETTY_TYPE_TEXT__(stringSignature, stringText) \
      _SGPrettyTypeTexts.insert(std::map<std::string, std::string>::value_type(stringSignature, stringText));

    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_VOID_SIGNATURE, "void");

    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_BOOL_SIGNATURE, "bool");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_BYTE_SIGNATURE, "byte");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_SDWORD_SIGNATURE, "sdword");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_UDWORD_SIGNATURE, "udword");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_SQWORD_SIGNATURE, "sqword");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_UQWORD_SIGNATURE, "uqword");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_DOUBLE_SIGNATURE, "double");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_STRING_SIGNATURE, "string");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_ROPE_SIGNATURE, "rope");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_IPv4ADDR_SIGNATURE, "ipaddress");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_PPORT_SIGNATURE, "pport");

    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_BOOL_REFERENCE_SIGNATURE, "bool &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_BYTE_REFERENCE_SIGNATURE, "byte &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_SDWORD_REFERENCE_SIGNATURE, "sdword &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_UDWORD_REFERENCE_SIGNATURE, "udword &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_SQWORD_REFERENCE_SIGNATURE, "sqword &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_UQWORD_REFERENCE_SIGNATURE, "uqword &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_DOUBLE_REFERENCE_SIGNATURE, "double &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_ROPE_REFERENCE_SIGNATURE, "rope &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_STRING_REFERENCE_SIGNATURE, "string &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_IPv4ADDR_REFERENCE_SIGNATURE, "ipaddress &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_PPORT_REFERENCE_SIGNATURE, "pport &");

    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_BOOL_TABLE_SIGNATURE, "table<bool>");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_BYTE_TABLE_SIGNATURE, "table<byte>");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_SDWORD_TABLE_SIGNATURE, "table<sdword>");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_UDWORD_TABLE_SIGNATURE, "table<udword>");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_SQWORD_TABLE_SIGNATURE, "table<sqword>");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_UQWORD_TABLE_SIGNATURE, "table<uqword>");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_DOUBLE_TABLE_SIGNATURE, "table<double>");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_ROPE_TABLE_SIGNATURE, "table<rope>");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_STRING_TABLE_SIGNATURE, "table<string>");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_IPv4ADDR_TABLE_SIGNATURE, "table<ipaddress>");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_PPORT_TABLE_SIGNATURE, "table<pport>");

    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_BOOL_TABLE_REFERENCE_SIGNATURE, "table<bool> &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_BYTE_TABLE_REFERENCE_SIGNATURE, "table<byte> &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_SDWORD_TABLE_REFERENCE_SIGNATURE, "table<sdword> &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_UDWORD_TABLE_REFERENCE_SIGNATURE, "table<udword> &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_SQWORD_TABLE_REFERENCE_SIGNATURE, "table<sqword> &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_UQWORD_TABLE_REFERENCE_SIGNATURE, "table<uqword> &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_DOUBLE_TABLE_REFERENCE_SIGNATURE, "table<double> &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_ROPE_TABLE_REFERENCE_SIGNATURE, "table<rope> &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_STRING_TABLE_REFERENCE_SIGNATURE, "table<string> &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_IPv4ADDR_TABLE_REFERENCE_SIGNATURE, "table<ipaddress> &");
    __INSERT_PRETTY_TYPE_TEXT__(CstringZVM_PPORT_TABLE_REFERENCE_SIGNATURE, "table<pport> &");

    bYetNotInitialized = false;
  }

  std::map<std::string, std::string>::const_iterator it;
  if ((it = _SGPrettyTypeTexts.find(rstringTypeSignature)) != _SGPrettyTypeTexts.end())
  {
    return (*it).second;
  }

  std::string stringError = "Invalid type signature '" + rstringTypeSignature + "'";
  throw zfc::EInvalidArgument(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
}


std::string ArgumentsSignatureToPrettyString(const std::string & rstringArgumentsSignature)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("ArgumentsSignatureToPrettyString()");
  std::vector<std::string> vectorTokens;
  // 分解
  ArgumentsSignatureToken(vectorTokens, rstringArgumentsSignature);
  std::string stringPretty;
  std::vector<std::string>::const_iterator it;
  // 让nSize为有符号数
  int nSize = vectorTokens.size() - 1;
  for (int i = 0; i <= nSize; ++i)
  {
    stringPretty += TypeSignatureToPrettyString(vectorTokens[i]);
    if (i != nSize)
    {
      stringPretty += ",";
    }
  }
  return stringPretty;
}


std::string FunctionNameAndSignatureToPrettyString(
  const std::string & rstringFunctionName,
  const std::string & rstringTypeSignature)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("FunctionNameAndSignatureToPrettyString()");
  std::vector<std::string> vectorTokens;
  FunctionSignatureToken(vectorTokens, rstringTypeSignature);

  std::string stringPretty = TypeSignatureToPrettyString(vectorTokens[1]) +
                             " " + rstringFunctionName + "(" +
                             ArgumentsSignatureToPrettyString(vectorTokens[0]) +
                             ")";
  return stringPretty;
}


/******************************************************************************
 * For constant pool element tag
 ******************************************************************************/
static const std::string _SastringTagTexts[] = {
  "nil-end string",                // 0
  "binary string",                 // 1
  "rope string",                   // 2
  "sdword",                        // 3
  "udword",                        // 4
  "sqword",                        // 5
  "uqword",                        // 6
  "double",                        // 7
  "protocol port",                 // 8
  "IPv4 address",                  // 9
  "name and signature reference",  // 10
  "global variable reference",     // 11
  "global function reference"      // 12
};


const std::string & ConstantPoolElementTagToString(TConstantPoolElementTag eTag)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("ConstantPoolElementTagToString()");

  LogAssert1(eTag < USHRT_MAX, "Bug: Constant element tag '%d' is great than '65535'", static_cast<SDWORD>(eTag));

  std::string stringError;

  if (eTag <= 0)
  {
    throw zfc::EOutOfRange(__FILE__, __PRETTY_FUNC__ , __LINE__,
                           "Tag", eTag, 0, CONSTANT_POOL_ELEMENT_TAG_END_OF_TAG - 1);
  }

  ///> 计算eTag的2的乘方数
  int nIndex = 0;
  while (eTag != 1)
  {
    eTag = static_cast<TConstantPoolElementTag>(eTag >> 1);
    ++nIndex;
  }

  if (nIndex >= CONSTANT_POOL_ELEMENT_TAG_END_OF_TAG)
  {
    throw zfc::EOutOfRange(__FILE__, __PRETTY_FUNC__ , __LINE__,
                           "Tag", eTag, 0, CONSTANT_POOL_ELEMENT_TAG_END_OF_TAG - 1);
  }

  return _SastringTagTexts[nIndex];
}


ZLS_END_NAMESPACE

