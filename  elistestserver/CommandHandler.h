#if !defined(COMMANDHANDLER_H)
#define COMMANDHANDLER_H
#include "stdafx.h"
#include <afxmt.h>

#include "Data.h"
#include "Queue.h"
#include "TimerDef.h"

#pragma once

class CELISTestServerDlg;

class CCommandHandler
{
public:
	CCommandHandler();
	virtual ~CCommandHandler(void);
public:
	HANDLE worker;
	DWORD wid;
	CELISTestServerDlg *dlg;
	BOOL finish;
public:
	//用这个函数结束线程的while循环
	void setFinish(BOOL op) {
		finish = op;
	}
	void setParentWindow(CELISTestServerDlg *dlg) {
		this->dlg = dlg;
	}
	//这个函数启动线程
	void start();
	//这个函数是线程的工作函数
	static DWORD __stdcall handle(LPVOID param);
	//LPTHREAD_START_ROUTINE handle;
//以下函数定义各种命令的处理
public:
	void NetCmd_InitServiceTable(CMasterData *d);
};


#endif
