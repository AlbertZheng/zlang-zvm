# Z-Language语言、编译器和字节码虚拟机

该项目是本人在2000年时的一个作品：**一种健壮的、高速的强类型嵌入式语言，以及提供了该语言的`编译器`和`字节码虚拟机`实现**。

## Z-Language语言简介

Z-Language语言是我在2000年创业时为当时的创业产品NetDefender-1 IDS系统（黑客入侵检测系统）特别设计的一种强类型嵌入式编程语言，用于灵活编写和扩展IDS系统的入侵检测规则。

2000年彼时的Lua语言还很简单、且是运行时动态解析的弱类型脚本语言，满足不了IDS系统对网络数据流内容进行高速检测的要求，因此我决定自己设计一种健壮的、高速的强类型嵌入式语言，其具有如下特征：

1. Z-Language在2000年时已经采用了字节码和虚拟机技术（类似`JVM`），我自己设计了一套字节码和实现了字节码虚拟机，因此能够实现真正的“一次编译，跨平台高速运行”。

2. Z-Language采用了“沙盒”安全保护技术，因此可以保护IDS系统，避免错误编写的Z-Language程序摧毁IDS系统，或者消耗掉系统资源，例如：死循环检测、内存申请限制、函数递归层数限制等技术。

3. Z-Language提供了一套高效率的C++嵌入式调用接口，因此能够很容易地将Z-Language集成到作者的NetDefender-1 IDS系统中的任何网络协议处理层里；

4. Z-Language借鉴了C语言的语法结构，保留了C语言的灵活性和强大功能，但是去除了C语言中的不安全因素，例如：指针、数组、显式内存申请、释放，等等。

5. Z-Language提供了多种丰富的基本数据类型和高级数据类型，即bool、byte、sdword、udword、sqword、uqword、double、string、rope、ipaddress、pport、table等数据类型，特别其中ipaddress、pport是专门设计的网络数据类型，rope是一种高效率的串数据类型，而table是一种比数组更灵活、更安全的关联表数据类型。

6. Z-Language支持多种高级编程语言才具有的特征，例如：变量类型cast、函数递归、for和while循环控制、引用参数、引用变量、AND和OR逻辑操作短路、C/C++风格的宏预处理，等等。

7. Z-Language支持将变量与NetDefender-1 IDS系统中正监测的任何TCP Session进行打结，因此可以让用户在Z-Language程序中轻松地跟踪某个TCP Session的状态变化。

8. Z-Language提供了一套简洁的用于编写、扩展系统库函数的C++接口，在Z-Language代码里能够像原生代码那样调用新扩展的系统库函数。

<br>

## Z-Language语言的语法规范

Z-Language借鉴了C语言的语法结构，保留了C语言的灵活性和强大功能，但是去除了C语言中的不安全因素，例如：指针、数组、显式内存申请、释放，等等。**只要你会编写C代码，你就会编写Z-Language代码**。

Z-Language语言的语法规范，请参见[Z-Language语言语法规范白皮书](/doc/Z-Language语言语法规范白皮书.pdf)。

<br>

## Z-Language`字节码虚拟机`设计

直接阅读源代码[InstructionCode.hpp里的注释](https://github.com/AlbertZheng/zlang-zvm/blob/master/zdk/zls/zvm/InstructionCode.hpp)，以及[`~/zlang-zvm/zdk/zls/zvm/`](https://github.com/AlbertZheng/zlang-zvm/tree/master/zdk/zls/zvm)下的源代码。

<br>

## 快速体验Z-Language语言

Z-Language语言的`编译器`（`词法分析器`、`语法分析器`、`语义分析器`、`字节码生成器`）和`字节码虚拟机`采用跨平台的**C++**和**STL库**编写实现，Z-Language语言的`编译器`采用自上而下（top-down）的递归下降[**LL(*)算法**](https://en.wikipedia.org/wiki/LL_parser)，感谢[**ANTLR**](http://www.antlr.org/)这套开源工具，使得我们可以写出优雅的lexer/parser代码。

编译构建Z-Language语言的`编译器`和`虚拟机`需要采用`gcc/g++-3.0.1`（注：这是2000年时可用的gcc/g++最新版本），需要使用到[**ANTLR-2.7.1**](http://www.antlr2.org)；运行操作系统环境为`FreeBSD 4.4`或`Debian 3`。

Z-Language语言的`编译器`和`字节码虚拟机`的源代码应该是能够被移植到现在最新版本的`gcc/g++`和`CentOS`操作系统的，由于我现在的精力实在有限，未能有时间去实现，欢迎对编译器技术感兴趣的同学`fork`本开源项目进行`PR`和移植。

为了方便体验Z-Language语言，我特地构建了[**一个开箱即用的`FreeBSD 4.4 i386`的vagrant box**](https://github.com/AlbertZheng/vagrant-freebsd-4.4-i386-minimal)，该vagrant box已经内置了Z-Language语言的源代码和编译、运行所需的一切工具链依赖。因此最简单的体验方法就是直接使用这个vagrant box在你的Mac或PC上启动一个FreeBSD虚拟机环境。

<br>

### 部署一个`FreeBSD 4.4 i386`虚拟机环境

前提条件：假设你的macOS已经安装了，
1. VirtualBox；
2. vagrant 2.0.1或之前的版本（注意：不要安装vagrant 2.0.2或以上新版本，这些版本有1个OpenSSL底层依赖的issue如下）。
    > /opt/vagrant/embedded/gems/2.0.3/gems/net-ssh-4.2.0/lib/net/ssh/transport/openssl.rb:112:in `ssh_do_verify':
    > uninitialized constant OpenSSL::Digest::DSS1 (NameError)

```bash
$ git clone git@github.com:AlbertZheng/vagrant-freebsd-4.4-i386-minimal.git
$ cd vagrant-freebsd-4.4-i386-minimal
$ vagrant up

Bringing machine 'default' up with 'virtualbox' provider...
==> default: Clearing any previously set forwarded ports...
==> default: Clearing any previously set network interfaces...
==> default: Preparing network interfaces based on configuration...
    default: Adapter 1: nat
==> default: Forwarding ports...
    default: 23 (guest) => 2223 (host) (adapter 1)
    default: 22 (guest) => 2222 (host) (adapter 1)
==> default: Running 'pre-boot' VM customizations...
==> default: Booting VM...
==> default: Waiting for machine to boot. This may take a few minutes...
    default: SSH address: 127.0.0.1:2222
    default: SSH username: root
    default: SSH auth method: private key
    default: Warning: Connection reset. Retrying...
    default: Warning: Remote connection disconnect. Retrying...
    default: Warning: Connection reset. Retrying...

>>> 如下ssh报错忽略它：

The configured shell (config.ssh.shell) is invalid and unable
to properly execute commands. The most common cause for this is
using a shell that is unavailable on the system. Please verify
you're using the full path to the shell and that the shell is
executable by the SSH user.
```

现在你可以以`root`身份ssh登录到本开源项目的专用freebsd box里了：
```bash
$ vagrant ssh
```

<br>

### 体验Z-Language语言的`编译器`（简称`zlangc`）和`字节码虚拟机`（简称`zvm`）

现在你可愉快地play了：

1. 用`zlangc`（make install安装为`/usr/local/bin/zlangc`）去编译用Z-Language语言编写的几个测试/演示代码文件（`~/zlang-zvm/zdk/zls/zlang/data`目录下`*.z`），将会在`~/zlang-zvm/zdk/zls/zlang/data`下产生相应的目标文件`*.zo`：

```bash
# cd /root/zlang-zvm/zdk/zls/zlang/data
# zlangc demo1.z
# zlangc demo2.z
# zlangc t5.z
```

2. 然后用`~/zlang-zvm/zdk/zls/zvm`目录下的一个演示程序`demo1`来体验Z-Language语言`字节码虚拟机`是如何执行上面编译产生的3个目标文件`demo1.zo`、`demo2.zo`、`t5.zo`：
```bash
# cd ../../zvm
# ./demo1
```

### 在你的C++应用程序代码里使用`zvm`

具体如何在你的C++程序代码里嵌入和使用`zvm`、以及如何用C++编写自己扩展的Z-Language语言系统函数等用法，可参考[`~/zlang-zvm/zdk/zls/zvm/demo1.cpp`](https://github.com/AlbertZheng/zlang-zvm/blob/master/zdk/zls/zvm/demo1.cpp)代码的实现。

<br>

## Z-Language`编译器`命令行参数

`zlangc`提供的命令行参数如下：
```bash
# /usr/local/bin/zlangc --help
zlangc 1.0

Usage: zlangc [OPTIONS]... [FILES]...
   -h         --help                 Print help and exit
   -V         --version              Print version and exit
   -DSTRING   --define-macro=STRING  A macro
   -ISTRING   --include-path=STRING  A include path
   -oSTRING   --object-file=STRING   Specific obejct file
              --trace-lexer          Trace lexer
              --trace-ast            Trace AST generated
              --trace-symbol-table   Trace symbol table generated
              --trace-code           Trace byte code generated
```

<br>

## 如何从头开始编译本项目的源代码

如果你想编译本项目的源代码，先`vagrant ssh`登录freebsd box后，步骤如下：

### 编译和安装`antlr-2.7.1`
```bash
# cd ~/zlang-zvm/antlr-2.7.1/lib/cpp
# ./configure --prefix=/usr/local/antlr-2.7.1
# make
# make install
```

### 编译和安装`zlang编译器`和`zlang虚拟机`
```bash
# cd ~/zlang-zvm/zdk
# ./configure
# ./make
# ./make install
```

<br>

## License

Copyright (C) 2000-2018 Albert Zheng, 郑立松

The binaries and source code of this Project can be used according to the [Apache License, Version 2.0](http://www.apache.org/licenses/LICENSE-2.0.html).
