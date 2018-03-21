/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CBinaryString.cpp,v $
 *
 * $Date: 2001/08/10 19:08:04 $
 *
 * $Revision: 1.2 $
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


#include <zls/zfc/CBinaryString.hpp>


ZLS_BEGIN_NAMESPACE(zfc)


std::string CBinaryString::ToString() const
{
  std::string stringTemp(reinterpret_cast<const char *>(c_str()), size());
  return stringTemp;
}


////////////////////////////////////////////////////////////////////////////////
// zfc::CBinaryString toolkit routines.
////////////////////////////////////////////////////////////////////////////////
CBinaryString IPv4AddressToBinaryString(NUDWORD nudw)
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

   return(CBinaryString(aszBuffer));
}


//CBinaryString IPv4AddressToBinaryString(struct in_addr siAddress)
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

//   return IPv4AddressToBinaryString(siAddress.s_addr);
//}


CBinaryString UQWORDToBinaryString(UQWORD uqw, int nBase)
{
  char aszBuffer[21];
  if (nBase == 16)
  {
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

  return(CBinaryString(aszBuffer));
}


CBinaryString SQWORDToBinaryString(SQWORD sqw, int nBase)
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
  return(CBinaryString(aszBuffer));
}


CBinaryString UDWORDToBinaryString(UDWORD udw, int nBase)
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

  return(CBinaryString(aszBuffer));
}


CBinaryString SDWORDToBinaryString(SDWORD sdw, int nBase)
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
  return(CBinaryString(aszBuffer));
}


#if SIZEOF_INT == SIZEOF_LONG
CBinaryString UnsignedLongToBinaryString(unsigned long ul, int nBase)
{
  return UDWORDToBinaryString((UDWORD)ul, nBase);
}


CBinaryString LongToBinaryString(long l, int nBase)
{
  return SDWORDToBinaryString((SDWORD)l, nBase);
}
#endif


CBinaryString UWORDToBinaryString(UWORD uw, int nBase)
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

  return(CBinaryString(aszBuffer));
}


CBinaryString SWORDToBinaryString(SWORD sw, int nBase)
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
  return(CBinaryString(aszBuffer));
}


CBinaryString FloatToBinaryString(float f)
{
  char aszBuffer[21];
  snprintf(aszBuffer, 21, "%f", f);
  return(CBinaryString(aszBuffer));
}


CBinaryString DoubleToBinaryString(double df)
{
  char aszBuffer[21];
  snprintf(aszBuffer, 21, "%.8lf", df);
  return(CBinaryString(aszBuffer));
}


void RightTrimBinaryString(CBinaryString & rbstring, char chWhichTrimed)
{
  if (! rbstring.empty())
  {
    int count=0;
    int length=rbstring.length();
    int i;
    int position;
    for (i=length-1;i >= 0;--i)
    {
      if (rbstring[i] == chWhichTrimed)
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
      rbstring.erase(position,count);
    }
  }
}



ZLS_END_NAMESPACE

