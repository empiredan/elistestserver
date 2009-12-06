#ifndef DEALTHREAD_H
#define DEALTHREAD_H


#include "Data.h"
#include "Queue.h"
#include "MessageSender.h"
#include "CommandHandler.h"

#include "TimerDef.h"

class CELISTestServerDlg;
class DealThread
{
public:
	DealThread(CELISTestServerDlg* pDlg);
	~DealThread();
public:
	void create();
	void SetParent(CELISTestServerDlg* pDlg);
	static UINT queuethreadProc(LPVOID lmparameter);
public:
	CWinThread *pthread;
	CDialog *pserverDlg;
public:
	MasterData Mdata;
	FrontData Fdata;
	MasterDataQueue *Mqueue;
	FrontDataQueue *Fqueue;
	static long length;
	static char buf[200];
};
#endif