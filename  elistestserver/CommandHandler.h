#if !defined(COMMANDHANDLER_H)
#define COMMANDHANDLER_H
#include "stdafx.h"
#include <afxmt.h>

#include "Data.h"
#include "Queue.h"
#include "TimerDef.h"
#include "ActTable.h"

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
	long headSize;
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
	void NetCmd_CalibPara(CMasterData *d);
	void NetCmd_CalibStart(CMasterData *d);
	void NetCmd_CalibStop(CMasterData *d);
	void NetCmd_CtrlWorkState(CMasterData *d);
	void NetCmd_SetStandbyTimeInterval(CMasterData *d);
	void NetCmd_CtrlRecStop(CMasterData *d);
	void NetCmd_CtrlActSwitch(CMasterData *d);
	void NetCmd_CtrlActDeactivate(CMasterData *d);
	//void (CMasterData *d);
	//void (CMasterData *d);
};


#endif
