/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/Toolkit.cpp,v $
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


#include <zls/zfc/Toolkit.hpp>


/*******************************************************************************
 * C toolkit routines.
 ******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

NUDWORD IPv4AddressPSZToNUDWORD(const char * pszIPv4Address)
{
  struct in_addr addr;

  if(! inet_aton(pszIPv4Address, &addr))
  {
    return INADDR_NONE;
  }
  else
  {
    return addr.s_addr;
  }
}


int PrintTime(char *pchBuffer, size_t nBufferSize, time_t timeValue)
{
#ifdef ENABLE_THREADS
   struct tm tm_temp;
   localtime_r(&timeValue, &tm_temp);
   return(strftime(pchBuffer, nBufferSize, "%Y-%m-%d %H:%M:%S", &tm_temp));
#else
   struct tm *tm_temp;
   tm_temp=localtime(&timeValue);
   return(strftime(pchBuffer, nBufferSize, "%Y-%m-%d %H:%M:%S", tm_temp));
#endif
}


void UpperPSZ(char * psz)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("UpperPSZ()");

  LogAssert0(psz != 0, "Unexpected zero pointer");
  if (psz)
  {
    while (*psz != '\0')
    {
      *psz = toupper(*psz);
      *psz++;
    }
  }
}


void LowerPSZ(char * psz)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("LowerPSZ()");

  LogAssert0(psz != 0, "Unexpected zero pointer");
  if (psz)
  {
    while (*psz != '\0')
    {
      *psz = tolower(*psz);
      *psz++;
    }
  }
}


char * SkipLeading(const char * pszSrc, char chWhat)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("SkipLeading()");
  const char * ptr = pszSrc;

  LogAssert0(pszSrc != 0, "Unexpected zero pointer");
  if (pszSrc)
  {
    while (*ptr == chWhat)
      ptr++;
  }

  return((char *)ptr);
}


void LeftTrimPSZ(char * pszSrc, char chWhat)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("LeftTrimPSZ()");
  char *ptr = pszSrc;

  LogAssert0(pszSrc != 0, "Unexpected zero pointer");
  if (pszSrc)
  {
    while (*ptr == chWhat)
      ptr++;

    if (ptr != pszSrc)
    {
      strcpy(pszSrc, ptr);
    }
  }
}


void RightTrimPSZ(char * pszSrc, char chWhat)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("RightTrimPSZ()");
  char *ptr;
  char *pStop;

  LogAssert0(pszSrc != 0, "Unexpected zero pointer");
  if (pszSrc)
  {
    ptr = pszSrc + strlen(pszSrc) - 1;
    pStop = pszSrc-1;

    while (*ptr == chWhat)
    {
      *ptr = '\0';
      --ptr;
      if (ptr == pStop)
        break;
    }
  }
}


const char * BoolToPSZ(bool b)
{
  if (b)
    return "true";
  else
    return "false";
}


/**
 * Check a "char *" for valid IP address in standard dot notation.
 */
bool IsGoodIPv4AddressPSZ(const char * pszIPv4Address)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("IsGoodIPv4AddressPSZ()");
  int     dot_count;
  int     digit_count;

  LogAssert0(pszIPv4Address != 0, "Unexpected zero pointer");
  dot_count = 0;
  digit_count = 0;
  while (*pszIPv4Address != '\0' && *pszIPv4Address != ' ')
  {
    if (*pszIPv4Address == '.')
    {
      dot_count++;
      digit_count = 0;
    }
    else
    {
      if (!isdigit(*pszIPv4Address))
        dot_count = 5;
      else
      {
        digit_count++;
        if (digit_count > 3)
          dot_count = 5;
       }
    }
    pszIPv4Address++;
  }

  if (dot_count != 3)
    return(true);
  else
    return(false);
}


void fprintf_hex_stream(FILE *fh, register const UCHAR *cp, register UDWORD length)
{
  register int ad, i, j, k;
  u_char c;
  u_char line[60];
  static u_char binhex[16] = {
          '0', '1', '2', '3', '4', '5', '6', '7',
          '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

  memset (line, ' ', sizeof line);
  line[sizeof (line)-1] = 0;
  for (ad=i=j=k=0; i<length; i++) {
          c = *cp++;
          line[j++] = binhex[c>>4];
          line[j++] = binhex[c&0xf];
          if (i&1) j++;
          line[42+k++] = c >= ' ' && c < 0x7f ? c : '.';
          if ((i & 15) == 15) {
                  fprintf (fh, "\n%4x  %s", ad, line);
                  memset (line, ' ', sizeof line);
                  line[sizeof (line)-1] = j = k = 0;
                  ad += 16;
          }
  }

  if (line[0] != ' ') fprintf (fh, "\n%4x  %s", ad, line);
  fprintf(fh, "\n");
  return;
}

#ifdef __cplusplus
}
#endif


/*******************************************************************************
 * C++ toolkit routines.
 ******************************************************************************/
#ifdef __cplusplus
extern "C++"
{
#endif

ZLS_BEGIN_NAMESPACE(zfc)


////////////////////////////////////////////////////////////////////////////////
// std::string toolkit routines.
////////////////////////////////////////////////////////////////////////////////
std::string IPv4AddressToString(NUDWORD nudw)
{
   char    aszBuffer[18];
   UDWORD  addr_byte[4];
   int     i;
   UDWORD  xbyte;
   /*
    * 如果是i386机器，则nudw在内存中的格式还是网络序，如下：
    *
    *          低字            高字         <- 主机序
    *     低字节  高字节  低字节  高字节
    *     192     168     8       80        <- 网络序(在内存或寄存器中）
    *
    * 因此必须将其转换为主机序，否则在下面的'&'操作将变成：
    *
    *          低字            高字         <- 主机序
    *     低字节  高字节  低字节  高字节
    *     192     168     8       80        <- 网络序(在内存或寄存器中）
    *  &)
    *          低字            高字
    *     低字节  高字节  低字节  高字节
    *     FF      00      00      00        <- 主机序(在内存或寄存器中）
    *
    * 最后的结果变成了"80.8.168.192"，与我们希望的相反；
    *
    * 而如果是sparc机器，则nudw在内存中的格式既是网络序也是主机序，如下：
    *
    *          高字            低字         <- 主机序
    *     高字节  低字节  高字节  低字节
    *     192     168     8       80        <- 网络序(在内存或寄存器中）
    *
    * 我认为在sparc上ntohl()等函数一定是个空函数，因此即使调用了ntohl()想将其转
    * 换为主机序，也还是不会真正改变字节序，结果在下面的'&'操作将变成：
    *
    *          高字            低字         <- 主机序
    *     高字节  低字节  高字节  低字节
    *     192     168     8       80        <- 网络序(在内存或寄存器中）
    *  &)
    *          高字            低字
    *     高字节  低字节  高字节  低字节
    *     00      00      00      FF        <- 主机序(在内存或寄存器中）
    *
    * 最后的结果变成了"192.168.8.80"，是我们希望的。
    */
   UDWORD udwAddress = ntohl(nudw);

   for (i = 0; i < 4; i++)
   {
     xbyte = udwAddress >> (i*8);
     xbyte = xbyte & (UDWORD)0x000000FF;
     addr_byte[i] = xbyte;
   }
   snprintf(aszBuffer, 18, "%u.%u.%u.%u",
            addr_byte[3], addr_byte[2], addr_byte[1], addr_byte[0]);

   return(std::string(aszBuffer));
}


//std::string IPv4AddressToString(struct in_addr siAddress)
//{
   /*
    * 如果是i386机器，则s_addr在内存中的格式还是网络序，如下：
    *
    *          低字            高字         <- 主机序
    *     低字节  高字节  低字节  高字节
    *     192     168     8       80        <- 网络序(在内存或寄存器中）
    *
    * 因此必须将其转换为主机序，否则在下面的'&'操作将变成：
    *
    *          低字            高字         <- 主机序
    *     低字节  高字节  低字节  高字节
    *     192     168     8       80        <- 网络序(在内存或寄存器中）
    *  &)
    *          低字            高字
    *     低字节  高字节  低字节  高字节
    *     FF      00      00      00        <- 主机序(在内存或寄存器中）
    *
    * 最后的结果变成了"80.8.168.192"，与我们希望的相反；
    *
    * 而如果是sparc机器，则s_addr在内存中的格式既是网络序也是主机序，如下：
    *
    *          高字            低字         <- 主机序
    *     高字节  低字节  高字节  低字节
    *     192     168     8       80        <- 网络序(在内存或寄存器中）
    *
    * 我认为在sparc上ntohl()等函数一定是个空函数，因此即使调用了ntohl()想将其转
    * 换为主机序，也还是不会真正改变字节序，结果在下面的'&'操作将变成：
    *
    *          高字            低字         <- 主机序
    *     高字节  低字节  高字节  低字节
    *     192     168     8       80        <- 网络序(在内存或寄存器中）
    *  &)
    *          高字            低字
    *     高字节  低字节  高字节  低字节
    *     00      00      00      FF        <- 主机序(在内存或寄存器中）
    *
    * 最后的结果变成了"192.168.8.80"，是我们希望的。
    */

//   return IPv4AddressToString(siAddress.s_addr);
//}


std::string UQWORDToString(UQWORD uqw, int nBase)
{
  char aszBuffer[21];
  if (nBase == 16)
  {
    // Borland C++ Help中说int64应该使用"L"，而FreeBSD的manual却说应使用"q"
    snprintf(aszBuffer, 21, "%qx", uqw);
  }
  else
  {
    if (nBase == 8)
    {
      snprintf(aszBuffer, 21, "%qo", uqw);
    }
    else
    {
      snprintf(aszBuffer, 21, "%qu", uqw);
    }
  }

  return(std::string(aszBuffer));
}


std::string SQWORDToString(SQWORD sqw, int nBase)
{
  char aszBuffer[21];
  if (nBase == 16)
  {
    snprintf(aszBuffer, 21, "%qx", sqw);
  }
  else
  {
    if (nBase == 8)
    {
      snprintf(aszBuffer, 21, "%qo", sqw);
    }
    else
    {
      snprintf(aszBuffer, 21, "%qd", sqw);
    }
  }
  return(std::string(aszBuffer));
}


std::string UDWORDToString(UDWORD udw, int nBase)
{
  char aszBuffer[21];
  if (nBase == 16)
  {
    snprintf(aszBuffer, 21, "%lx", udw);
  }
  else
  {
    if (nBase == 8)
    {
      snprintf(aszBuffer, 21, "%lo", udw);
    }
    else
    {
      snprintf(aszBuffer, 21, "%lu", udw);
    }
  }

  return(std::string(aszBuffer));
}


std::string SDWORDToString(SDWORD sdw, int nBase)
{
  char aszBuffer[21];
  if (nBase == 16)
  {
    snprintf(aszBuffer, 21, "%lx", sdw);
  }
  else
  {
    if (nBase == 8)
    {
      snprintf(aszBuffer, 21, "%lo", sdw);
    }
    else
    {
      snprintf(aszBuffer, 21, "%ld", sdw);
    }
  }
  return(std::string(aszBuffer));
}


#if SIZEOF_INT == SIZEOF_LONG
std::string UnsignedLongToString(unsigned long ul, int nBase)
{
  return UDWORDToString((UDWORD)ul, nBase);
}


std::string LongToString(long l, int nBase)
{
  return SDWORDToString((SDWORD)l, nBase);
}
#endif


std::string UWORDToString(UWORD uw, int nBase)
{
  char aszBuffer[21];
  if (nBase == 16)
  {
    snprintf(aszBuffer, 21, "%x", uw);
  }
  else
  {
    if (nBase == 8)
    {
      snprintf(aszBuffer, 21, "%o", uw);
    }
    else
    {
      snprintf(aszBuffer, 21, "%u", uw);
    }
  }

  return(std::string(aszBuffer));
}


std::string SWORDToString(SWORD sw, int nBase)
{
  char aszBuffer[21];
  if (nBase == 16)
  {
    snprintf(aszBuffer, 21, "%x", sw);
  }
  else
  {
    if (nBase == 8)
    {
      snprintf(aszBuffer, 21, "%o", sw);
    }
    else
    {
      snprintf(aszBuffer, 21, "%d", sw);
    }
  }
  return(std::string(aszBuffer));
}


std::string FloatToString(float f)
{
  char aszBuffer[21];
  snprintf(aszBuffer, 21, "%f", f);
  return(std::string(aszBuffer));
}


std::string DoubleToString(double df)
{
  char aszBuffer[21];
 // 采用精度为小数点后8位，经过测试如果采用"%le"的话则打印的是科学计数法
  snprintf(aszBuffer, 21, "%.8lf", df);
  return(std::string(aszBuffer));
}


/*
void RightTrimString(std::string & rstring, char chWhichTrimed)
{
  if (! rstring.empty())
  {
    int count=0;
    int length=rstring.length();
    int i;
    int position;
    for (i=length-1;i >= 0;--i)
    {
      if (rstring[i] == chWhichTrimed)
      {
        ++count;
        position=i;
      }
      else
      {
        break;
      }
    }
    if (count > 0)
    {
      rstring.erase(position,count);
    }
  }
}
*/

/* 这个版本的right_trim_string()会引起STL thrown exception,不知道为什么?
void RightTrimString(std::string & rstring, char chWhichTrimed)
{
  if (! rstring.empty())
  {
    std::string::iterator iteratorTmp=rstring.end();
    do {
      iteratorTmp--;
      if (*iteratorTmp == chWhichTrimed)
      {
        rstring.erase(iteratorTmp);
      }
      else
      {
        break;
      }
    } while(iteratorTmp != rstring.begin());
  }
}
*/


int CInOutTracer::SnInDepth = 0;

ZLS_END_NAMESPACE

#ifdef __cplusplus
}
#endif

