/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/Manifest.hpp,v $
 *
 * $Date: 2001/11/14 18:29:37 $
 *
 * $Revision: 1.7 $
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


#ifndef _ZLS_zvm_Manifest_hpp_
#define _ZLS_zvm_Manifest_hpp_

#include <zls/zfc/Manifest.h>
#include <zls/zfc/CBinaryString.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


/**
 * ZVM中所有涉及的INDEX的默认类型.
 *
 * @note 例如：constant pool的index；stack上的index；指令的index等.
 * @attention 必须让TZVMIndex为有符号数值，这样我们可以区分在stack上的index的方向.
 * 这个类型影响到产生的字节码.
 */
typedef SDWORD   TZVMIndex;


/**
 * ZVM的指令码的类型（2 Byte）.
 */
typedef UWORD   TZVMICode;


/**
 * @name ZVM的数据类型的签名字符
 */
//@{
const char CchZVM_VOID_TYPE_TAG     = 'V';  // void
const char CchZVM_BYTE_TYPE_TAG     = 'B';  // byte
const char CchZVM_BOOL_TYPE_TAG     = 'Z';  // zero
const char CchZVM_SDWORD_TYPE_TAG   = 'I';  // int
const char CchZVM_UDWORD_TYPE_TAG   = 'J';
const char CchZVM_SQWORD_TYPE_TAG   = 'L';  // long
const char CchZVM_UQWORD_TYPE_TAG   = 'M';
const char CchZVM_DOUBLE_TYPE_TAG   = 'D';  // double
const char CchZVM_ROPE_TYPE_TAG     = 'R';  // rope
const char CchZVM_STRING_TYPE_TAG   = 'S';  // string
const char CchZVM_IPv4ADDR_TYPE_TAG = 'N';  // network
const char CchZVM_PPORT_TYPE_TAG    = 'P';  // port
const char CchZVM_TABLE_TYPE_TAG    = '[';  // table，注意：这个char必须为非字母的，否则在程序中的low()调用后将使ZLang compiler出现类型不匹配错误.
//@}


/**
 * @name 一些经常使用的字符串Literal的string常量，避免compiler构造临时对象.
 */
//@{
const std::string CstringZVM_VOID_SIGNATURE("V");

const std::string CstringZVM_BYTE_SIGNATURE("B");
const std::string CstringZVM_BOOL_SIGNATURE("Z");
const std::string CstringZVM_SDWORD_SIGNATURE("I");
const std::string CstringZVM_UDWORD_SIGNATURE("J");
const std::string CstringZVM_SQWORD_SIGNATURE("L");
const std::string CstringZVM_UQWORD_SIGNATURE("M");
const std::string CstringZVM_DOUBLE_SIGNATURE("D");
const std::string CstringZVM_STRING_SIGNATURE("S");
const std::string CstringZVM_ROPE_SIGNATURE("R");
const std::string CstringZVM_IPv4ADDR_SIGNATURE("N");
const std::string CstringZVM_PPORT_SIGNATURE("P");

const std::string CstringZVM_BYTE_REFERENCE_SIGNATURE("b");
const std::string CstringZVM_BOOL_REFERENCE_SIGNATURE("z");
const std::string CstringZVM_SDWORD_REFERENCE_SIGNATURE("i");
const std::string CstringZVM_UDWORD_REFERENCE_SIGNATURE("j");
const std::string CstringZVM_SQWORD_REFERENCE_SIGNATURE("l");
const std::string CstringZVM_UQWORD_REFERENCE_SIGNATURE("m");
const std::string CstringZVM_DOUBLE_REFERENCE_SIGNATURE("d");
const std::string CstringZVM_ROPE_REFERENCE_SIGNATURE("r");
const std::string CstringZVM_STRING_REFERENCE_SIGNATURE("s");
const std::string CstringZVM_IPv4ADDR_REFERENCE_SIGNATURE("n");
const std::string CstringZVM_PPORT_REFERENCE_SIGNATURE("p");

const std::string CstringZVM_TABLE_PREFIX_SIGNATURE("[");
const std::string CstringZVM_BYTE_TABLE_SIGNATURE("[B");
const std::string CstringZVM_BOOL_TABLE_SIGNATURE("[Z");
const std::string CstringZVM_SDWORD_TABLE_SIGNATURE("[I");
const std::string CstringZVM_UDWORD_TABLE_SIGNATURE("[J");
const std::string CstringZVM_SQWORD_TABLE_SIGNATURE("[L");
const std::string CstringZVM_UQWORD_TABLE_SIGNATURE("[M");
const std::string CstringZVM_DOUBLE_TABLE_SIGNATURE("[D");
const std::string CstringZVM_ROPE_TABLE_SIGNATURE("[R");
const std::string CstringZVM_STRING_TABLE_SIGNATURE("[S");
const std::string CstringZVM_IPv4ADDR_TABLE_SIGNATURE("[N");
const std::string CstringZVM_PPORT_TABLE_SIGNATURE("[P");

const std::string CstringZVM_BYTE_TABLE_REFERENCE_SIGNATURE("[b");
const std::string CstringZVM_BOOL_TABLE_REFERENCE_SIGNATURE("[z");
const std::string CstringZVM_SDWORD_TABLE_REFERENCE_SIGNATURE("[i");
const std::string CstringZVM_UDWORD_TABLE_REFERENCE_SIGNATURE("[j");
const std::string CstringZVM_SQWORD_TABLE_REFERENCE_SIGNATURE("[l");
const std::string CstringZVM_UQWORD_TABLE_REFERENCE_SIGNATURE("[m");
const std::string CstringZVM_DOUBLE_TABLE_REFERENCE_SIGNATURE("[d");
const std::string CstringZVM_ROPE_TABLE_REFERENCE_SIGNATURE("[r");
const std::string CstringZVM_STRING_TABLE_REFERENCE_SIGNATURE("[s");
const std::string CstringZVM_IPv4ADDR_TABLE_REFERENCE_SIGNATURE("[n");
const std::string CstringZVM_PPORT_TABLE_REFERENCE_SIGNATURE("[p");


/**
 * 每个ZLang script file中都有一个隐含的static function，这个function其实是这个
 * ZLang script file中所有的global variables的初值化statements的集合，每当ZVM调
 * 入ZLang object file且link成功后，就会执行这个function来对global variables进行
 * 初值化.
 */
const std::string CstringInitializerFunctionName = "__initializer__";
//@}


/**
 * 将CstringZVM_BOOL_SIGNATURE等转换为CstringBOOL_LITERAL等.
 *
 * @throw zfc::EInvalidArgument 当type signature不合法时.
 */
const std::string & TypeSignatureToPrettyString(const std::string & rstringTypeSignature);


/**
 * 将类似"SL[D"的ZVM function的所有参数的type signature混合的串转换为类似
 * "sdword, sqword, double[]"的可读格式.
 *
 * @throw zfc::EInvalidArgument 当type signature不合法时.
 */
std::string ArgumentsSignatureToPrettyString(const std::string & rstringArgumentsSignature);


/**
 * 将类似"SL[D"的ZVM function的所有参数的type signature混合的串拆分到一个Container中.
 * 如上面的将被拆分变成：
 * <pre>
 *    "S"
 *    "L"
 *    "[D"
 * </pre>
 */
template <class StringType, class ContainerType>
void ArgumentsSignatureToken(
  ContainerType & rciContainer,
  const StringType & rciArgumentsSignature)
{
  int nSize = rciArgumentsSignature.size();
  for (int i = 0; i < nSize; ++i)
  {
    if (rciArgumentsSignature[i] != CchZVM_TABLE_TYPE_TAG)
    {
      StringType ciString(1, rciArgumentsSignature[i]);
      rciContainer.push_back(ciString);
    }
    else
    {
      StringType ciString = rciArgumentsSignature.substr(i, 2);
      rciContainer.push_back(ciString);
      ++i;  // Jump '['
    }
  }
}


/**
 * 将将类似"(SL[D)S"的ZVM function type signature串分解为Arguments signature部分
 * "SL[D"和Return signature部分"S"，然后存放到一个用户指定的container中.
 */
template <class StringType, class ContainerType>
void FunctionSignatureToken(ContainerType & rciContainer,
                            const StringType & rstringFunctionSignature)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("FunctionSignatureToken()");

  // 防止"(...)"这种bad-signature被传入
  LogAssert1(rstringFunctionSignature.rfind(')') != rstringFunctionSignature.size()-1,
             "Invalid function signature '%s'",
             rstringFunctionSignature.c_str());

  zfc::StringToken(rciContainer, rstringFunctionSignature, "()");
  // 防止"()"或""这种bad-signature被传入
  LogAssert1(rciContainer.size() != 0,
             "Invalid function signature '%s'",
             rstringFunctionSignature.c_str());

  if (rciContainer.size() == 1)
  // 如果signature是"()?"这种
  {
    // Patch一个Arguments signature
    rciContainer.insert(rciContainer.begin());
  }

  /*
   * 2001/5/9: 好象assert比throw对跟踪程序的运行流程更有用，因此是否能这样：
   * (1)如果某个条件必须绝对是真的才能继续执行程序代码，否则就是很严重的Bug，则
   * 可以考虑采用assert技术。
   * (2)如果某个条件为假时，但影响不大或是可恢复的，或你不想让你的产品core dump，
   * 而想在主程序捕捉exception，再告诉用户怎么回事，则通常可以采用throw std::logic_error
   * 型exception.
   */
  LogAssert1(rciContainer.size() == 2,
             "Invalid function signature '%s'",
             rstringFunctionSignature.c_str());
  /*
  #ifndef NDEBUG
  // size()一定是2，否则throw EInvalidArgument.
  if (rciContainer.size() != 2)
  {
    std::string stringError = "Invalid type signature: '" + rstringFunctionSignature + "'";
    throw zfc::EInvalidArgument(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
  }
  #endif
  */
}


/**
 * 将一个ZVM function名串和一个类似"(SL[D)V"的function type signature串转换为类似
 * "void functionName(sdword, sqword, double[])"的可读格式.
 *
 * @throw zfc::EInvalidArgument 当type signature - "(SU[D)V"的不合法时.
 */
std::string FunctionNameAndSignatureToPrettyString(
  const std::string & rstringFunctionName,
  const std::string & rstringTypeSignature
);


/** ZVM的Magic number. */
const UDWORD CudwZVM_MAGIC_NUMBER = 0x19730122;
/** ZVM Major version number */
const UWORD  CuwZVM_MAJOR_VERSION = 0x0200;
/** ZVM Minor version number */
const UWORD  CuwZVM_MINOR_VERSION = 0x0002;


/** 指示编写ZVM function的语言Tag. */
enum TLanguageTag {
  LANGUAGE_TAG_IS_ZLANG,  ///< Z-Language
  LANGUAGE_TAG_IS_CPP     ///< C++
};


/** Global variable或function的存取修饰符Tag. */
enum TAccessModifierTag {
  PUBLIC_BY_EXTERN_MODULE,  ///< extern型
  PUBLIC_BY_SELF_MODULE,  ///< 正常型
  PRIVATE_FOR_SELF_MODULE  ///< static型
};


/**
 * @name Group about constant pool element tag.
 */
//@{
/** Constant pool element tag. */
enum TConstantPoolElementTag {
  CONSTANT_POOL_ELEMENT_TAG_NONE = 0,
  CONSTANT_POOL_ELEMENT_TAG_NIL_END_STRING = 1,  ///< 需NIL结尾的字符串字面值
  CONSTANT_POOL_ELEMENT_TAG_BINARY_STRING = 2,   ///< 可非NIL结尾的8bit清楚的字符串字面值
  CONSTANT_POOL_ELEMENT_TAG_ROPE_STRING = 4,  ///< Rope字符串字面值
  CONSTANT_POOL_ELEMENT_TAG_SDWORD = 8,   ///< sdword literal
  CONSTANT_POOL_ELEMENT_TAG_UDWORD = 16,  ///< udword literal
  CONSTANT_POOL_ELEMENT_TAG_SQWORD = 32,  ///< sqword literal
  CONSTANT_POOL_ELEMENT_TAG_UQWORD = 64,  ///< uqword literal
  CONSTANT_POOL_ELEMENT_TAG_DOUBLE = 128,  ///< double literal
  CONSTANT_POOL_ELEMENT_TAG_PROTOCOL_PORT = 256,  ///< pport literal
  CONSTANT_POOL_ELEMENT_TAG_IPv4ADDRESS = 512,  ///< ipaddr literal
  CONSTANT_POOL_ELEMENT_TAG_NAME_AND_SIGNATURE_REFERENCE = 1024,
  CONSTANT_POOL_ELEMENT_TAG_GLOBAL_VARIABLE_REFERENCE = 2048,
  CONSTANT_POOL_ELEMENT_TAG_GLOBAL_FUNCTION_REFERENCE = 4096,

  CONSTANT_POOL_ELEMENT_TAG_END_OF_TAG = 13
};

/**
* 将Tag值转换为可读的Text.
*
* @throw zfc::EOutOfRange.
*/
const std::string & ConstantPoolElementTagToString(TConstantPoolElementTag eTag);
//@}


ZLS_END_NAMESPACE


ZLS_BEGIN_NAMESPACE(zvm)

/** 指示是否采用std::string作为ZVM string的实现. */
#define USE_std_string_AS_ZVM_STRING 1

/** 指示是否采用zfc::CBinaryString作为ZVM rope的实现. */
#define USE_zfc_CBinaryString_AS_ZVM_ROPE 1


#ifdef USE_std_string_AS_ZVM_STRING
  /** 定义在ZVM中ZVM string类型的实现class. */
  typedef std::string   CZVMString;

  #define MAKE_ZVM_STRING_HASH    std::hash<std::string>

  /**
   * @name 将各种ZVM的type转换为ZVM string型，以便能作为table的key.
   */
  //@{
  #define ZVM_BOOL_TO_ZVM_STRING(b)               zfc::UWORDToString(b, 10)
  #define ZVM_BYTE_TO_ZVM_STRING(uch)             zfc::UWORDToString(uch, 10)
  #define ZVM_SDWORD_TO_ZVM_STRING(sdw)           zfc::SDWORDToString(sdw, 10)
  #define ZVM_UDWORD_TO_ZVM_STRING(udw)           zfc::UDWORDToString(udw, 10)
  #define ZVM_SQWORD_TO_ZVM_STRING(sqw)           zfc::SQWORDToString(sqw, 10)
  #define ZVM_UQWORD_TO_ZVM_STRING(uqw)           zfc::UQWORDToString(uqw, 10)
  #define ZVM_DOUBLE_TO_ZVM_STRING(df)            zfc::DoubleToString(df)
  #define ZVM_PPORT_TO_ZVM_STRING(pci)            pci->ToString()
  #define ZVM_IPv4ADDRESS_TO_ZVM_STRING(pci)      pci->ToString()
  #define ZVM_ROPE_TO_ZVM_STRING(pci)             pci->ToString()
  //@}

  #define IPv4ADDRESS_TO_ZVM_STRING(in_addr_v)    zfc::IPv4AddressToString(in_addr_v)
#else
  /** 定义在ZVM中ZVM string类型的实现class. */
  typedef zfc::CBinaryString      CZVMString;

  #define MAKE_ZVM_STRING_HASH    zfc::MakeBinaryStringHash

  /**
   * @name 将各种ZVM的type转换为ZVM string型，以便能作为table的key.
   */
  //@{
  #define ZVM_BOOL_TO_ZVM_STRING(b)               zfc::UWORDToBinaryString(b, 10)
  #define ZVM_BYTE_TO_ZVM_STRING(uch)             zfc::UWORDToBinaryString(uch, 10)
  #define ZVM_SDWORD_TO_ZVM_STRING(sdw)           zfc::SDWORDToBinaryString(sdw, 10)
  #define ZVM_UDWORD_TO_ZVM_STRING(udw)           zfc::UDWORDToBinaryString(udw, 10)
  #define ZVM_SQWORD_TO_ZVM_STRING(sqw)           zfc::SQWORDToBinaryString(sqw, 10)
  #define ZVM_UQWORD_TO_ZVM_STRING(uqw)           zfc::UQWORDToBinaryString(uqw, 10)
  #define ZVM_DOUBLE_TO_ZVM_STRING(df)            zfc::DoubleToBinaryString(df)
  #define ZVM_PPORT_TO_ZVM_STRING(pci)            pci->ToBinaryString()
  #define ZVM_IPv4ADDRESS_TO_ZVM_STRING(pci)      pci->ToBinaryString()

  #ifdef USE_zfc_CBinaryString_AS_ZVM_ROPE
    #define ZVM_ROPE_TO_ZVM_STRING(pci)         *pci
  #else
    #error "Undeterminated implemention of macro 'ZVM_ROPE_TO_ZVM_STRING(pci)'."
  #endif
  //@}

  #define IPv4ADDRESS_TO_ZVM_STRING(in_addr_v)    zfc::IPv4AddressToBinaryString(in_addr_v)
#endif

// forward declaration
class CIPv4CIDRAddress;
class CProtocolPort;
class CTableWrapper;

#ifdef USE_zfc_CBinaryString_AS_ZVM_ROPE
  /** 定义在ZVM中ZVM rope类型的实现class. */
  typedef zfc::CBinaryString      CZVMRope;
#else
  #error "Undeterminated implemention class of 'ZVM rope'."
#endif

/** 定义在ZVM中ZVM ipaddress类型的实现class. */
typedef CIPv4CIDRAddress        CZVMIPv4Address;

/** 定义在ZVM中ZVM pport类型的实现class. */
typedef CProtocolPort           CZVMPPort;

/** 定义在ZVM中ZVM table类型的实现class. */
typedef CTableWrapper           CZVMTable;

ZLS_END_NAMESPACE


#ifndef _ZLS_zvm_CIPv4CIDRAddress_hpp_
#include <zls/zvm/CIPv4CIDRAddress.hpp>
#endif

#ifndef _ZLS_zvm_CProtocolPort_hpp_
#include <zls/zvm/CProtocolPort.hpp>
#endif

#ifndef _ZLS_zvm_CTableWrapper_hpp_
#include <zls/zvm/CTableWrapper.hpp>
#endif


#endif
