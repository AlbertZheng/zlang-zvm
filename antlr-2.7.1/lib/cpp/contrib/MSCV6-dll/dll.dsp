# Microsoft Developer Studio Project File - Name="DLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DLL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DLL.mak" CFG="DLL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath "Desktop"
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DLL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "Intermediate\DLL\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DLL_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DLL_EXPORTS" /D "ANTLRDLL" /FAs /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"./ANTLR.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /map /machine:I386 /out:"./ANTLR.dll"

!ELSEIF  "$(CFG)" == "DLL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "Intermediate\DLL\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DLL_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /Gm /Gi /GR /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DLL_EXPORTS" /D "ANTLRDLL" /FAs /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"./ANTLRd.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /map /debug /machine:I386 /out:"./ANTLRd.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DLL - Win32 Release"
# Name "DLL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ANTLRException.cpp
# End Source File
# Begin Source File

SOURCE=.\AST.cpp
# End Source File
# Begin Source File

SOURCE=.\ASTFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\BitSet.cpp
# End Source File
# Begin Source File

SOURCE=.\CharBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\CharScanner.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonASTNode.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonASTNodeWithHiddenTokens.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonHiddenStreamToken.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonToken.cpp
# End Source File
# Begin Source File

SOURCE=.\DLL.cpp
# End Source File
# Begin Source File

SOURCE=.\InputBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\LexerSharedInputState.cpp
# End Source File
# Begin Source File

SOURCE=.\LLkParser.cpp
# End Source File
# Begin Source File

SOURCE=.\MismatchedTokenException.cpp
# End Source File
# Begin Source File

SOURCE=.\NoViableAltException.cpp
# End Source File
# Begin Source File

SOURCE=.\Parser.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserException.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserSharedInputState.cpp
# End Source File
# Begin Source File

SOURCE=.\ScannerException.cpp
# End Source File
# Begin Source File

SOURCE=.\String.cpp
# End Source File
# Begin Source File

SOURCE=.\Token.cpp
# End Source File
# Begin Source File

SOURCE=.\TokenBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\TokenStreamBasicFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\TokenStreamHiddenTokenFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\TokenStreamSelector.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeParser.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeParserSharedInputState.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\antlr\ANTLRException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\AST.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\ASTArray.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\ASTFactory.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\ASTNode.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\ASTNULLType.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\ASTPair.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\BitSet.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\CharBuffer.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\CharScanner.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\CircularQueue.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\CommonASTNode.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\CommonASTNodeWithHiddenTokens.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\CommonHiddenStreamToken.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\CommonToken.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\config.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\InputBuffer.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\LexerSharedInputState.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\LLkParser.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\MismatchedTokenException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\NoViableAltException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\Parser.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\ParserException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\ParserSharedInputState.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\RefCount.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\ScannerException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\String.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\Token.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\TokenBuffer.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\TokenStream.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\TokenStreamBasicFilter.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\TokenStreamHiddenTokenFilter.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\TokenStreamSelector.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\TreeParser.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\TreeParserSharedInputState.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
