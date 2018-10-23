# What is the project?

English | [简体中文](/README-zh_CN.md)

This project is one of my private work started in 2001: A robust, flexible, high-speed strongly-typed embedded language for C++ application, and also implements the Lexical, Syntax, Semantic Compiler, and the Bytecode Virtual Machine.

## Introduction of Z-Language, its compilers and Bytecode Virtual Machine

Z-language is a strongly-typed embedded programming language that I specially designed for the NetDefender-1 IDS (Intrusion Detection System) when I started my business in 2000. It was used to flexibly write and extend the intrusion detection rules for IDS.

In 2001, the ```Lua``` language was still simple, and it was a weakly-typed script language that was dynamically parsed at runtime, which could not meet the requirements of IDS system for high-speed detection of network data flow content, so I decided to design a robust, high-speed strong-typed embedded languages with the following features:

1. Z-Language had already adopted the Bytecode and Bytecode Virtual Machine technology (similar to ```JVM```) in 2001. I designed a set of Bytecode instructment set and implemented the Bytecode Virtual Machine, so Z-Language achieved the characteristic ```once compiled, run across platforms``` similar to ```Java```.

2. The Bytecode Virtual Machine can avoid the error-writing or malicious Z-Language programs to damage IDS systems, or consume the system resources, such as dead-loop detection, memory request limits, function recursive layer limit and other techniques.

3. Z-Language provides a set of efficient invoking interfaces for embedding in  C++ programs, so it is easy to integrate Z-Language into any network protocol processing layer in any C++ applicaiton, such as my NetDefender-1 IDS system.

4. Z-Language borrows the syntax structure of C language, and retains the flexibility and powerful features of C language, but removes the insecurity factors in C language, such as pointer, array, explicit memory allocating, releasing, and so on.

5. Z-Language provides a variety of basic and advanced data types, such as ```bool```, ```byte```, ```sdword```, ```udword```, ```sqword```, ```uqword```, ```double```, ```string```, ```rope```, ```ipaddress```, ```pport```, ```table```, in which ```ipaddress```, ```pport``` is a specially designed network data type, ```rope``` is a highly efficient string data type, and ```table``` is a secure association table data type, more flexible than an array.

6. Z-Language supports the characteristics of many advanced programming languages, such as ```variable type cast```, ```function recursion```, ```for and while loop control```, ```reference parameter```, ```reference variable```, ```AND and OR logic operation short circuit```, ```C/C++ style macro preprocessing```, and so on.

7. Z-Language supports to tie its variables to any TCP session that is being monitored in the NetDefender-1 IDS system, so users can easily track the state of a TCP session in a Z-Language program.

8. Z-Language provides a set of simple C++ interface for writing and extending its system library. In Z-Language code, the newly extended system library functions can be called in the same way as if its native code.

<br>

## Syntax specification of Z-Language

Z-Language borrows the syntax structure of ```C``` language, so **if you can write C codes, you can write Z-Language codes too.**

Please refer to [the technical white paper of Z-Language syntax specification](/doc/Z-Language语言语法规范白皮书.pdf). Sorry, currently there is just a Chinese version :(.

<br>

## Design of Bytecode Virtual Machine of Z-Language

Please directly read the source codes for knowing the design of Bytecode Virtual Machine of Z-Language.

1. The source codes and comments in [InstructionCode.hpp](https://github.com/AlbertZheng/zlang-zvm/blob/master/zdk/zls/zvm/InstructionCode.hpp);
2. The source codes in the directory [```~/zlang-zvm/zdk/zls/zvm/```](https://github.com/AlbertZheng/zlang-zvm/tree/master/zdk/zls/zvm).

<br>

## Quickly play the Z-Language

Z-Language's ```compiler``` (```lexical parser```, ```semantic parser```, ```bytecode generator```) and ```Bytecode Virtual Machine``` were implemented by using cross-platform  ```C++```codes and ```STL``` library.

Z-Language's ```compiler``` adopts the top-down recursive descent [**LL(*) algorithm**](https://en.wikipedia.org/wiki/LL_parser), and thanks to the [**ANTLR**](http://www.antlr.org/), so that I can write elegant codes for lexer and parser implementation. 

To build the compiler and virtual machine by yourself, you will need to use the ```gcc/g++-3.0.1``` (note: this was the latest version of gcc/g++ available in 2001.), and [ANTLR-2.7.1](http://www.antlr2.org). The OS for runtime is ```FreeBSD 4.4``` or ```Debian 3```.

For your convenience, I had built a special out-of-the-box [FreeBSD 4.4 i386 vagrant box]((https://github.com/AlbertZheng/vagrant-freebsd-4.4-i386-minimal)) for playing the Z-Language. This vagrant box had installed the GNU toolchain, cloned the source codes of Z-Language, and built the compiler, the Bytecode Virtual Machine of Z-Language. So the easiest way to experience Z-Language is to directly use this vagrant box to start a FreeBSD virtual environment on your Mac or PC.

<br>

### How to deploy the ```FreeBSD 4.4 i386 vagrant box```

Prerequisite：You have installed below softwares on your macOS.

1. ```VirtualBox```;
2. ```vagrant 2.0.1``` or lower versions (note：DON'T use ```vagrant 2.0.2``` or above versions because they have an issue relating to OpenSSL as below).
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

>>> Please ignore below error of ssh:

The configured shell (config.ssh.shell) is invalid and unable
to properly execute commands. The most common cause for this is
using a shell that is unavailable on the system. Please verify
you're using the full path to the shell and that the shell is
executable by the SSH user.
```

Now you can ssh into this freebsd box with ```root```:
```bash
$ vagrant ssh
```

<br>

### Play the compiler (```zlangc```) and Bytecode Virtual Machine (```zvm```) of Z-Language

Now you can play:

1. Using ```zlangc``` (installed as ```/usr/local/bin/zlangc```) to compile several demo and testing Z-Language codes (i.e. ```*.z``` files in the directory ```~/zlang-zvm/zdk/zls/zlang/data```), and the compiler will generate the output files ```*.zo``` in the directory ```~/zlang-zvm/zdk/zls/zlang/data```:

```bash
# cd /root/zlang-zvm/zdk/zls/zlang/data
# zlangc demo1.z
# zlangc demo2.z
# zlangc t5.z
```

2. Then using the executable file ```demo1``` of  ```demo1.cpp``` in the directory ```~/zlang-zvm/zdk/zls/zvm``` to experience how the ```zvm``` will execute the above three oebject files ```demo1.zo```, ```demo2.zo```, ```t5.zo```：

```bash
# cd ../../zvm
# ./demo1
```

### How to embed and use ```zvm``` in your C++ application ?

Please refer to the source codes of [/zlang-zvm/zdk/zls/zvm/demo1.cpp](https://github.com/AlbertZheng/zlang-zvm/blob/master/zdk/zls/zvm/demo1.cpp) for how to embed and use the Bytecode Virtual Machine ```zvm``` in your C++ application? and how to write new functions to extend the system library of Z-Language? 

<br>

## Command usage of the compiler ```zlangc```

Command usage:
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

## How to compile the source codes of this project?

If you want to compile the source codes of this project to build the ```zlangc``` and ```zvm```, firstly ```vagrant ssh``` to login the freebsd box, then issue commands as the following steps:

### Build and install ```antlr-2.7.1```
```bash
# cd ~/zlang-zvm/antlr-2.7.1/lib/cpp
# ./configure --prefix=/usr/local/antlr-2.7.1
# make
# make install
```

### Build and install ```zlangc``` and ```zvm```
```bash
# cd ~/zlang-zvm/zdk
# ./configure
# ./make
# ./make install
```

<br>

## License

Copyright (C) 2001-2018 Lisong Zheng, 郑立松

The binaries and source code of this Project can be used according to the [Apache License, Version 2.0](http://www.apache.org/licenses/LICENSE-2.0.html).
