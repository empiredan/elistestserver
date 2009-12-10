; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=MySocket
LastTemplate=CListCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ELISTestServer.h"

ClassCount=8
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
Class8=MyListCtrl
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
ControlCount=42
Control1=IDC_STATIC_SET_PARAM,button,1342177287
Control2=IDC_ELISTESTSERVER_TAB,SysTabControl32,1342177280
Control3=IDC_Ok,button,1342242816
Control4=IDC_Cancel,button,1342242816
Control5=IDC_STATIC_TRUE_DEPTH,static,1342308352
Control6=IDC_STATIC_CORRECTED_DEPTH,static,1342308352
Control7=IDC_EDIT_TRUE_DEPTH,edit,1350631552
Control8=IDC_EDIT_SPEED,edit,1350631552
Control9=IDC_STATIC_MODE,static,1342308352
Control10=IDC_STATIC_MODE_VALUE,static,1342308352
Control11=IDC_STATIC_DIRECTION,static,1342308352
Control12=IDC_STATIC_DIRECTION_VALUE,static,1342308352
Control13=IDC_STATIC_SERVER_PORT,static,1342308352
Control14=IDC_EDIT_SERVER_PORT,edit,1350631552
Control15=IDC_BUTTON_SERVER_PORT,button,1342242816
Control16=IDC_STATIC_SERVER_IP_PORT,static,1342308352
Control17=IDC_STATIC_CLIENT_IP_PORT,static,1342308352
Control18=IDC_STATIC_SERVER_IP_PORT_VALUE,static,1342308352
Control19=IDC_STATIC_CLIENT_IP_PORT_VALUE,static,1342308352
Control20=IDC_STATIC_DATA_BUFFER_SIZE,static,1342308352
Control21=IDC_EDIT_DATA_BUFFER_SIZE,edit,1350631552
Control22=IDC_BUTTON_DATA_BUFFER_SIZE,button,1342242816
Control23=IDC_STATIC_ACT_FOLDER,static,1342308352
Control24=IDC_EDIT_ACT_FOLDER,edit,1484849280
Control25=IDC_EDIT_CALVER_FOLDER,edit,1484849280
Control26=IDC_STATIC_CALVER_FOLDER,static,1342308352
Control27=IDC_BUTTON_ACT_FOLDER,button,1342242816
Control28=IDC_BUTTON_CALVER_FOLDER,button,1342242816
Control29=IDC_STATIC_CONNECT,button,1342177287
Control30=IDC_STATIC_DATA,button,1342177287
Control31=IDC_STATIC_SHOW_PARAM,button,1342177287
Control32=IDC_STATIC_SPEED,static,1342308352
Control33=IDC_EDIT_CORRECTED_DEPTH,edit,1350631552
Control34=IDC_BUTTON_TRUE_DEPTH,button,1342242816
Control35=IDC_BUTTON_CORRECTED_DEPTH,button,1342242816
Control36=IDC_BUTTON_SPEED,button,1342242816
Control37=IDC_STATIC_TRUE_DEPTH_SHOW,static,1342308352
Control38=IDC_STATIC_CORRECTED_SHOW,static,1342308352
Control39=IDC_STATIC_SPEED_SHOW,static,1342308352
Control40=IDC_STATIC_TRUE_DEPTH_SHOW_VALUE,static,1342308352
Control41=IDC_STATIC_CORRECTED_SHOW_VALUE,static,1342308352
Control42=IDC_STATIC_SPEED_SHOW_VALUE,static,1342308352

[DLG:IDD_TAB_ACT]
Type=1
Class=TabAct
ControlCount=1
Control1=IDC_LIST_ACT,SysListView32,1350631433

[CLS:TabAct]
Type=0
HeaderFile=TabAct.h
ImplementationFile=TabAct.cpp
BaseClass=CDialog
Filter=D
LastObject=TabAct
VirtualFilter=dWC

[CLS:TabCalVer]
Type=0
HeaderFile=TabCalVer.h
ImplementationFile=TabCalVer.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST_CALVER
VirtualFilter=dWC

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

[CLS:MyListCtrl]
Type=0
HeaderFile=MyListCtrl.h
ImplementationFile=MyListCtrl.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=FWC
LastObject=MyListCtrl

