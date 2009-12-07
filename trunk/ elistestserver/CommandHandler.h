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
	//��������������̵߳�whileѭ��
	void setFinish(BOOL op) {
		finish = op;
	}
	void setParentWindow(CELISTestServerDlg *dlg) {
		this->dlg = dlg;
	}
	//������������߳�
	void start();
	//����������̵߳Ĺ�������
	static DWORD __stdcall handle(LPVOID param);
	//LPTHREAD_START_ROUTINE handle;
//���º��������������Ĵ���
public:
	void NetCmd_InitServiceTable(CMasterData *d);
};


#endif
