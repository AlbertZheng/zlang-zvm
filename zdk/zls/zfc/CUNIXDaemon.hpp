/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zfc/CUNIXDaemon.hpp,v $
 *
 * $Date: 2002/02/28 13:59:25 $
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


#ifndef _ZLS_zfc_CUNIXDaemon_hpp_
#define _ZLS_zfc_CUNIXDaemon_hpp_

#include <zls/zfc/Manifest.h>
#include <zls/zfc/SmartPointer.hpp>
#include <zls/zfc/CSingletonFactoryT.hpp>
#include <zls/zfc/IPv4Address.hpp>


// begin namespace "zfc::"
ZLS_BEGIN_NAMESPACE(zfc)


/**
 * @brief CUNIXDaemon是一个UNIX Daemon的抽象基类.
 *
 * CUNIXDaemon是一个UNIX Daemon的抽象基类，它封装了一个UNIX Daemon所需要的全部功能.
 *
 */
class CUNIXDaemon : public CReferenceCounter {
  private:
    static CUNIXDaemon * _SpciSingleton;

    /**
     * Get singleton instance of class CUNIXDaemon or derived.
     *
     * @note This method is only internal for CUNIXDaemon::SignalHandler().
     */
    static CUNIXDaemon * Instance()
    {
      return _SpciSingleton;
    }

    /**
     * UNIX signal dispatcher.
     *
     * It will dispatch installed signals by calling back 'virtual On...()'.
     */
    static void SignalHandler(int nSignal);

    void GenerateVersionInfo();
    void GenerateCopyrightInfo();

    bool _bDaemonCanShutdown;

  protected:
    std::string      _stringMyHostName;
    CIPv4HostAddress _ciMyIPv4Address;

    std::string _stringProductName;
    std::string _stringDaemonName;
    int         _nMajorVersion;
    int         _nMinorVersion;
    //int         _nDebugLevel;
    std::string _stringVersion;
    std::string _stringCopyright;
    sigset_t    _siInstalledSignalsMask;

    virtual void Run() = 0;
    /**
     * 当Daemon从CUNIXDaemon::Run()中正常退出后，virtual CUNIXDaemon::Finalize()
     * 将被调用以进行用户的一些"垃圾"处理工作，用户可选择override它.
     */
    virtual void Finalize();

    virtual void OnUSR1Signal();
    virtual void OnUSR2Signal();
    virtual void OnHUPSignal();
    /**
     * 当收到TERM信号时，CUNIXDaemon::_bDaemonCanShutdown将被置true，因此用户
     * 如果override了CUNIXDaemon::OnTERMSignal()，则切记在实现中先调用一次
     * CUNIXDaemon::OnTERMSignal()以保证CUNIXDaemon::_bDaemonCanShutdown将被置
     * true.
     */
    virtual void OnTERMSignal();
    virtual void OnCHLDSignal();
    /**
     * Other(not be those above) installed singals's handler.
     */
    virtual void OnSignal(int nSignal);

    /**
     * Constructor.
     *
     * 将Constructor放置在protected的目的是禁止new和定义instance variable，
     * 由于CUNIXDaemon是抽象class，想创建其派生类的实例的唯一办法是定义一个
     * CSingletonFactoryT的instance variable，CSingletonFactoryT有办法来保证
     * CUNIXDaemon的派生类的instance永远只能有唯一的一个，同时CUNIXDaemon的派
     * 生类的Constructor应该是default constructor才能利用CSingletonFactoryT.
     *
     * @throw zfc::ESystemCallFailure 当调用sysinfo()或gethostname()失败时.
     */
    CUNIXDaemon(const char *pszProductName,
                const char *pszDaemonName,
                int nMajorVersion,
                int nMinorVersion,
                int nDebugLevel);

  public:
    virtual const std::string & GetVersionInfo() const;
    virtual const std::string & GetCopyrightInfo() const;

    void InstallSignal(int nSignal);
    void BlockingInstalledSignals();
    void UnblockingInstalledSignals();

    /**
     * 是否Daemon现在允许正常退出了.
     *
     * @note 当收到TERM信号时，CUNIXDaemon::_bDaemonCanShutdown将被置true.
     */
    bool DaemonCanShutdown() const
    {
      return _bDaemonCanShutdown;
    }

    void SetDaemonDebugLevel(int nDebugLevel)
    {
      SetLoggerDebugLevel(nDebugLevel);
    }

    /**
     * 开始Daemon，这将开始调用被override的Run().
     *
     * @throw zfc::ESystemCallFailure 当调用fork()失败时.
     */
    void Start();
};


inline void CUNIXDaemon::Run()
{ }

inline void CUNIXDaemon::Finalize()
{ }


ZLS_END_NAMESPACE


#endif

