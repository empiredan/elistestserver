# Microsoft Developer Studio Project File - Name="ELISTestServer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ELISTestServer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ELISTestServer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ELISTestServer.mak" CFG="ELISTestServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ELISTestServer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ELISTestServer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ELISTestServer - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ELISTestServer - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ELISTestServer - Win32 Release"
# Name "ELISTestServer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ActTable.cpp
# End Source File
# Begin Source File

SOURCE=.\CalibParameter.cpp
# End Source File
# Begin Source File

SOURCE=.\CalibSubset.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\Data.cpp
# End Source File
# Begin Source File

SOURCE=.\DataFileBuf.cpp
# End Source File
# Begin Source File

SOURCE=.\DepthPanelReadTensionAngle.cpp
# End Source File
# Begin Source File

SOURCE=.\DepthPanelTensionFactor.cpp
# End Source File
# Begin Source File

SOURCE=.\DPMDisplayParameter.cpp
# End Source File
# Begin Source File

SOURCE=.\ELISTestServer.cpp
# End Source File
# Begin Source File

SOURCE=.\ELISTestServer.rc
# End Source File
# Begin Source File

SOURCE=.\ELISTestServerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageSender.cpp
# End Source File
# Begin Source File

SOURCE=.\MyListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\MySocket.cpp
# End Source File
# Begin Source File

SOURCE=.\MyTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SingleACQDataReady.cpp
# End Source File
# Begin Source File

SOURCE=.\SpeedFast.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SubsetData.cpp
# End Source File
# Begin Source File

SOURCE=.\SubsetDataAssister.cpp
# End Source File
# Begin Source File

SOURCE=.\TabAct.cpp
# End Source File
# Begin Source File

SOURCE=.\TabCalVer.cpp
# End Source File
# Begin Source File

SOURCE=.\UpholeSendDataReady.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkMode.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkModeSetter.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ActTable.h
# End Source File
# Begin Source File

SOURCE=.\CalibParameter.h
# End Source File
# Begin Source File

SOURCE=.\CalibSubset.h
# End Source File
# Begin Source File

SOURCE=.\CommandHandler.h
# End Source File
# Begin Source File

SOURCE=.\commands.h
# End Source File
# Begin Source File

SOURCE=.\Data.h
# End Source File
# Begin Source File

SOURCE=.\DataFileBuf.h
# End Source File
# Begin Source File

SOURCE=.\DepthPanelReadTensionAngle.h
# End Source File
# Begin Source File

SOURCE=.\DepthPanelTensionFactor.h
# End Source File
# Begin Source File

SOURCE=.\DPMDisplayParameter.h
# End Source File
# Begin Source File

SOURCE=.\ELISTestServer.h
# End Source File
# Begin Source File

SOURCE=.\ELISTestServerDlg.h
# End Source File
# Begin Source File

SOURCE=.\MessageSender.h
# End Source File
# Begin Source File

SOURCE=.\MyListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\MySocket.h
# End Source File
# Begin Source File

SOURCE=.\MyTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Queue.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SingleACQDataReady.h
# End Source File
# Begin Source File

SOURCE=.\SpeedFast.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SubsetData.h
# End Source File
# Begin Source File

SOURCE=.\SubsetDataAssister.h
# End Source File
# Begin Source File

SOURCE=.\TabAct.h
# End Source File
# Begin Source File

SOURCE=.\TabCalVer.h
# End Source File
# Begin Source File

SOURCE=.\TimerDef.h
# End Source File
# Begin Source File

SOURCE=.\UpholeSendDataReady.h
# End Source File
# Begin Source File

SOURCE=.\Utils.h
# End Source File
# Begin Source File

SOURCE=.\WorkMode.h
# End Source File
# Begin Source File

SOURCE=.\WorkModeSetter.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ELISTestServer.ico
# End Source File
# Begin Source File

SOURCE=.\res\ELISTestServer.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
