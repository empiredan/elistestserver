; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CELISTestServerDlg
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ELISTestServer.h"

ClassCount=7
Class1=CELISTestServerApp
Class2=CELISTestServerDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_TAB_ACT
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=TabAct
Resource4=IDD_ELISTESTSERVER_DIALOG
Class5=TabCalVer
Class6=MyTabCtrl
Class7=MySocket
Resource5=IDD_TAB_CALVER

[CLS:CELISTestServerApp]
Type=0
HeaderFile=ELISTestServer.h
ImplementationFile=ELISTestServer.cpp
Filter=N
LastObject=CELISTestServerApp

[CLS:CELISTestServerDlg]
Type=0
HeaderFile=ELISTestServerDlg.h
ImplementationFile=ELISTestServerDlg.cpp
Filter=D
LastObject=CELISTestServerDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ELISTestServerDlg.h
ImplementationFile=ELISTestServerDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ELISTESTSERVER_DIALOG]
Type=1
Class=CELISTestServerDlg
ControlCount=4
Control1=IDC_STATIC,button,1342177287
Control2=IDC_ELISTESTSERVER_TAB,SysTabControl32,1342177280
Control3=IDC_Ok,button,1342242816
Control4=IDC_Cancel,button,1342242816

[DLG:IDD_TAB_ACT]
Type=1
Class=TabAct
ControlCount=1
Control1=IDC_LIST_ACT,SysListView32,1350631425

[CLS:TabAct]
Type=0
HeaderFile=TabAct.h
ImplementationFile=TabAct.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST_ACT

[CLS:TabCalVer]
Type=0
HeaderFile=TabCalVer.h
ImplementationFile=TabCalVer.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST_CALVER

[DLG:IDD_TAB_CALVER]
Type=1
Class=TabCalVer
ControlCount=1
Control1=IDC_LIST_CALVER,SysListView32,1350631425

[CLS:MyTabCtrl]
Type=0
HeaderFile=MyTabCtrl.h
ImplementationFile=MyTabCtrl.cpp
BaseClass=CTabCtrl
Filter=W
LastObject=MyTabCtrl
VirtualFilter=UWC

[CLS:MySocket]
Type=0
HeaderFile=MySocket.h
ImplementationFile=MySocket.cpp
BaseClass=CAsyncSocket
Filter=N
LastObject=MySocket
VirtualFilter=q

