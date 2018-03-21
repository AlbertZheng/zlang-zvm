/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CPipe.cpp,v $
 *
 * $Date: 2001/11/14 17:25:11 $
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


#include <zls/zfc/CPipe.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


CPipe::CPipe()
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CPipe::CPipe()");
  if (pipe(_fd) == -1)
  {
    throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "pipe", errno);
  }
}


void CPipe::Copy(const CPipe & rci)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CPipe::Copy()");
  if (rci._fd[0] >= 0)
  {
    _fd[0] = dup(rci._fd[0]);
    if (_fd[0] < 0)
    {
      throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "dup", errno);
    }
  }
  else
  {
    _fd[0] = -1;
  }

  if (rci._fd[1] >= 0)
  {
    _fd[1] = dup(rci._fd[1]);
    if (_fd[1] < 0)
    {
      throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "dup", errno);
    }
  }
  else
  {
    _fd[1] = -1;
  }
}


CPipe & CPipe::operator=(const CPipe & rci)
{
  Close();
  Copy(rci);
  return *this;
}


void CPipe::Close()
{
  CloseRead();
  CloseWrite();
}


void CPipe::CloseWrite()
{
  if (_fd[1] >= 0)
  {
    close(_fd[1]);
    _fd[1] = -1;
  }
}


void CPipe::CloseRead()
{
  if (_fd[0] >= 0)
  {
    close(_fd[0]);
    _fd[0] = -1;
  }
}


void CPipe::Dup2FileDescriptor(int fdFromWhich, int fdToWhich)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CPipe::Dup2FileDescriptor()");
  if (dup2(fdFromWhich, fdToWhich) != fdToWhich)
  // dup2()将描述符fdFromWhich复制到指定的新描述符fdToWhich，然后返回新描述符fdToWhich。
  // 如果在复制之前如果新描述符fdToWhich已经被打开了，则会先自动关闭它；如果在复制之前
  // 描述符fdFromWhich已经等于新描述符fdToWhich，则即使新描述符fdToWhich已经被打开了，
  // dup2()却并不先自动关闭新描述符fdToWhich，而是直接返回新描述符fdToWhich.
  {
    throw zfc::ESystemCallFailure(__FILE__, __PRETTY_FUNC__, __LINE__, "dup2", errno);
  }
}


void CPipe::Dup2AndThenCloseReadFileDescriptor(int fdToWhich)
{
  if (_fd[0] != fdToWhich)
  // 保护措施，以防止如果_fd[0]已经等于fdToWhich了，但我们并不知道，然后进行的变
  // 成将自己dup2()给自己，因此当下面的代码close(_fd[0])时将使fdToWhich也变成closed.
  {
    Dup2FileDescriptor(_fd[0], fdToWhich);
    close(_fd[0]);
    _fd[0] = -1;
  }
}


void CPipe::Dup2AndThenCloseWriteFileDescriptor(int fdToWhich)
{
  if (_fd[1] != fdToWhich)
  // 保护措施，以防止如果_fd[1]已经等于fdToWhich了，但我们并不知道，然后进行的变
  // 成将自己dup2()给自己，因此当下面的代码close(_fd[1])时将使fdToWhich也变成closed.
  {
    Dup2FileDescriptor(_fd[1], fdToWhich);
    close(_fd[1]);
    _fd[1] = -1;
  }
}


ssize_t CPipe::Read(void * pvBuffer, size_t nCount)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CPipe::Read()");
  if (_fd[0] >= 0)
  {
    return read(_fd[0], pvBuffer, nCount);
  }
  else
  {
    std::string stringError = "You had already closed read file-descriptor";
    throw zfc::EInvalidState(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
  }
}


ssize_t CPipe::Write(const void * pvBuffer, size_t nCount)
{
  static const char * __PRETTY_FUNC__ = ZLS_PRETTY_FUNCTION("CPipe::Write()");
  if (_fd[1] >= 0)
  {
    return write(_fd[1], pvBuffer, nCount);
  }
  else
  {
    std::string stringError = "You had already closed write file-descriptor";
    throw zfc::EInvalidState(__FILE__, __PRETTY_FUNC__, __LINE__, stringError);
  }
}


ZLS_END_NAMESPACE

