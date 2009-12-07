#include "stdafx.h"
#include "CommandHandler.h"
#include "Data.h"
#include "Queue.h"
#include "ELISTestServerDlg.h"

#include "commands.h"
#include "TimerDef.h"

//class CELISTestServerDlg;
CCommandHandler::CCommandHandler() {
	this->dlg = dlg;
	finish = FALSE;
	headSize = 2*sizeof(long);
}
CCommandHandler::~CCommandHandler(void)
{
}

void CCommandHandler::start() {
	worker = CreateThread(NULL, 
											0,
											&CCommandHandler::handle,
											this,		//传递对象指针作为线程函数LPVOID param参数
											0,			//start immediately after create
											&wid);
}

DWORD CCommandHandler::handle(LPVOID param) {
	CCommandHandler *handler = (CCommandHandler *)param;
	CMasterData *d;
	MasterDataQueue *q;
	long cmdtype;
	
	//
	char t[512];
	q = handler->dlg->getMasterDataQueue();
	
	while(!handler->finish) {
		d = q->de();
		//sprintf_s(t, "Command Handler handle:::buf[0]=%d,buf[1]=%d", d->buf[0], d->buf[1]);
		//AfxMessageBox(_T(t));
		if( d == NULL) {
			continue;
		}
		//在这里处理各种命令，调用相应的
		//命令解析函数来做。
		cmdtype = d->buf[0];
		
		switch(cmdtype) {
			case NET_CMDTYPE_INIT_SERVICE_TABLE:
				//call NetCmd_InitServiceTable(*cmdBuffer)
				handler->NetCmd_InitServiceTable(d);
			break;

			default:
				AfxMessageBox(_T("CCommandHandler::handle command type not defined"));
			break;
		}
	}

	return 0;
}

void CCommandHandler::NetCmd_InitServiceTable(CMasterData *d) {
	AfxMessageBox(_T("Implement me, NetCmd_InitServiceTable"));

	CActTable *tb;
	int rate[2];
	UINT logTimerInterval;

	logTimerInterval = 5000;

	tb = CActTable::AllocateActTable((d->buf)+headSize, d->buflen-headSize);
	dlg->SetACTTable(tb);
	tb->MaximumCommonSampleRate(rate);

	//最后所有的解析和设置都好了之后
	//用新计算得到的logTimerInterval值重新启动log timer
	dlg->StopLogTimer();
	dlg->CreateLogTimer(logTimerInterval);
	
	
	//别忘了在这里要delete CMasterData类型的指针d。
	//因为原则上，这里把这个收到的前端机发送过来的数据
	//处理完毕，就不会再使用了，要把它删除掉。
	//这个CMasterData对象是在Dialog中通过socket收到之际，
	//new 出来放到队列中的！！！
	//每个这样的处理函数都需要这样做。
	//如果这里的数据需要作为长期使用的参数保存，那么
	//应该把它们通过对应的数据结构拷贝出去。
	delete d;
}


void CCommandHandler::NetCmd_CalibPara(CMasterData *d) {
	unsigned char *bodyBuf;
	long bodyLen;

	long *head;
	long cmdType, totalLen;

	head = (long*)d->buf;
	cmdType = d->buf[0];
	totalLen = d->buf[1];

	bodyLen = totalLen - headSize;
	bodyBuf = d->buf + headSize;

	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CalibPara"));
}
void CCommandHandler::NetCmd_CalibStart(CMasterData *d) {
	unsigned char *bodyBuf;
	long bodyLen;

	long *head;
	long cmdType, totalLen;

	head = (long*)d->buf;
	cmdType = d->buf[0];
	totalLen = d->buf[1];

	bodyLen = totalLen - headSize;
	bodyBuf = d->buf + headSize;

	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CalibStart"));
}
void CCommandHandler::NetCmd_CalibStop(CMasterData *d) {
	unsigned char *bodyBuf;
	long bodyLen;

	long *head;
	long cmdType, totalLen;

	head = (long*)d->buf;
	cmdType = d->buf[0];
	totalLen = d->buf[1];

	bodyLen = totalLen - headSize;
	bodyBuf = d->buf + headSize;

	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CalibStop"));
}
void CCommandHandler::NetCmd_CtrlWorkState(CMasterData *d) {
	unsigned char *bodyBuf;
	long bodyLen;

	long *head;
	long cmdType, totalLen;

	head = (long*)d->buf;
	cmdType = d->buf[0];
	totalLen = d->buf[1];

	bodyLen = totalLen - headSize;
	bodyBuf = d->buf + headSize;

	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CtrlWorkState"));
}
void CCommandHandler::NetCmd_SetStandbyTimeInterval(CMasterData *d) {
	unsigned char *bodyBuf;
	long bodyLen;

	long *head;
	long cmdType, totalLen;

	head = (long*)d->buf;
	cmdType = d->buf[0];
	totalLen = d->buf[1];

	bodyLen = totalLen - headSize;
	bodyBuf = d->buf + headSize;

	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_SetStandbyTimeInterval"));
}
void CCommandHandler::NetCmd_CtrlRecStop(CMasterData *d) {
	unsigned char *bodyBuf;
	long bodyLen;

	long *head;
	long cmdType, totalLen;

	head = (long*)d->buf;
	cmdType = d->buf[0];
	totalLen = d->buf[1];

	bodyLen = totalLen - headSize;
	bodyBuf = d->buf + headSize;

	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CtrlRecStop"));
}
void CCommandHandler::NetCmd_CtrlActSwitch(CMasterData *d) {
	unsigned char *bodyBuf;
	long bodyLen;

	long *head;
	long cmdType, totalLen;

	head = (long*)d->buf;
	cmdType = d->buf[0];
	totalLen = d->buf[1];

	bodyLen = totalLen - headSize;
	bodyBuf = d->buf + headSize;

	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CtrlActSwitch"));
}
void CCommandHandler::NetCmd_CtrlActDeactivate(CMasterData *d) {
	unsigned char *bodyBuf;
	long bodyLen;

	long *head;
	long cmdType, totalLen;

	head = (long*)d->buf;
	cmdType = d->buf[0];
	totalLen = d->buf[1];

	bodyLen = totalLen - headSize;
	bodyBuf = d->buf + headSize;

	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CtrlActDeactivate"));
}
