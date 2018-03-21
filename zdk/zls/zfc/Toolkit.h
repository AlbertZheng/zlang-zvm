/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/Toolkit.h,v $
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


#ifndef _ZLS_zfc_Toolkit_h_
#define _ZLS_zfc_Toolkit_h_

#include <zls/zfc/Manifest.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * 将用"a1.a2.a3.a4"的串格式表示的IPv4 address转换为一个NUDWORD.
 * @note 这个函数只是对inet_aton()进行了封装.
 */
NUDWORD IPv4AddressPSZToNUDWORD __P((const char * pszIPv4Address));


/**
 * 按"YYYY-MM-DD HH:MM:SS"格式打印time_t到一个指定的buffer中.
 * @param pchBuffer 缓存区.
 * @param nBufferSize 缓存区长度.
 * @param timeValue A "time_t" value（秒），这是一个自从0 hours, 0 minutes,
 * 0 seconds, January 1, 1970开始到现在的时间值，可以表示最大为136.1925...年，
 * 通常这个值是通过调用系统调用time(0)来得到.
 * @attention "time_t"通常是象如下这样被typedef的：
 * <pre>
 *   #define _BSD_TIME_T_    long
 *   typedef _BSD_TIME_T_    time_t;
 * </pre>
 */
int PrintTime __P((char *pchBuffer, size_t nBufferSize, time_t timeValue));


/**
 * 将'\0'结尾的串转换位全部大写.
 * @param psz '\0'结尾的串.
 */
void UpperPSZ __P((char * psz));


/**
 * 将'\0'结尾的串转换位全部小写.
 * @param psz '\0'结尾的串.
 */
void LowerPSZ __P((char * psz));


/**
 * 将'\0'结尾的串的最左边的特定字符去除.
 * @param pszSrc '\0'结尾的串.
 * @param chWhat 特定的字符.
 * @attention pszSrc的内容可能因为"去除"而变小.
 */
void LeftTrimPSZ __P((char * pszSrc, char chWhat));


/**
 * 将'\0'结尾的串的最右边的特定字符去除.
 * @param pszSrc '\0'结尾的串.
 * @param chWhat 特定的字符.
 * @attention pszSrc的内容可能因为"去除"而变小.
 */
void RightTrimPSZ __P((char * pszSrc, char chWhat));


/**
 * 扫描一个'\0'结尾的串，跳过其最左边的特定字符，然后返回第一次碰到非特定字符时
 * 的开始指针.
 * @param pszSrc '\0'结尾的串.
 * @param chWhat 特定的字符.
 * @return 第一次碰到非特定字符时的开始指针.
 */
char * SkipLeading __P((const char * pszSrc, char chWhat));


/**
 * 将一个bool型的值转化为"true"或"false"串.
 * @param b bool值.
 * @return 一个const char *，调用者绝对不应该free这个指针的.
 */
const char * BoolToPSZ __P((bool b));


/**
 * Check a "char *" for valid IP address in standard dot notation.
 * @param pszIPv4Address '\0'结尾的类似"192.168.8.90"格式的串.
 */
bool IsGoodIPv4AddressPSZ __P((const char * pszIPv4Address));


/**
 * 安全地取得data中第iPosition个字节的第iBitPos位（0~7）.
 *
 * @attention 这里的“安全”并没有它的真正含义，只是为了系列函数的统一命名.
 */
inline UCHAR SafelyGetSpecialBit(const UCHAR * puchData, const int iPosition, const int iBitPos)
{
  return (puchData[iPosition] >> iBitPos) & 0x01;
}


enum THigh4OrLow4Flag {
  tholfHIGH4_BITS = 0,
  tholfLOW4_BITS = 1
};

/**
 * 安全地取得data中第iPosition个字节的低/高4位.
 *
 * @attention 这里的“安全”并没有它的真正含义，只是为了系列函数的统一命名.
 */
inline UCHAR SafelyGet4Bits(const UCHAR * puchData, const int iPosition, const enum THigh4OrLow4Flag eHigh4OrLow4)
{
  if (eHigh4OrLow4 == tholfLOW4_BITS)
  {
    return puchData[iPosition] >> 4 & 0x0F;
  }
  else
  {
    return puchData[iPosition] & 0x0F;
  }
}


/**
 * 安全地取得data中第iPosition个字节.
 *
 * @attention 这里的“安全”并没有它的真正含义，只是为了系列函数的统一命名.
 */
inline UCHAR SafelyGet8Bits(const UCHAR * puchData, const int iPosition)
{
  return (UCHAR)puchData[iPosition];
}


/**
 * 安全地取得data中第iPosition个字节开始的2个字节（按网络字节序组装成UWORD）.
 *
 * @attention 这里的“安全”并没有它的真正含义，只是为了系列函数的统一命名.
 */
inline NUWORD SafelyGet16BitsByBigEndian(const UCHAR * puchData, const int iPosition)
{
  NUWORD nuw;
  memcpy(&nuw, puchData+iPosition, sizeof(NUWORD));
  return nuw;
}


/**
 * 安全地取得data中第iPosition个字节开始的4个字节（按网络字节序组装成UDWORD）.
 *
 * @attention 这里的安全有它真正的意义，通常在sparc等RISC CPU上dload、dstore指令
 * 都需要地址是4byte对齐的，否则会core dump。在这个函数里采用的是memcpy()的安全
 * 方法，所以不会core dump.
 */
inline NUDWORD SafelyGet32BitsByBigEndian(const UCHAR * puchData, const int iPosition)
{
  NUDWORD nudw;
  memcpy(&nudw, puchData+iPosition, sizeof(NUDWORD));
  return nudw;
}


void fprintf_hex_stream __P((FILE *fh, register const UCHAR *cp, register UDWORD length));

#ifdef __cplusplus
}
#endif


#endif

