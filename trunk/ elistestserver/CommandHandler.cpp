#include "stdafx.h"
#include "CommandHandler.h"
#include "Data.h"
#include "Queue.h"
#include "ELISTestServer.h"
#include "ELISTestServerDlg.h"

#include "commands.h"
#include "TimerDef.h"

//class CELISTestServerDlg;
CCommandHandler::CCommandHandler() {
	this->dlg = dlg;
	finish = FALSE;
}
CCommandHandler::~CCommandHandler(void)
{
}

void CCommandHandler::start() {
	worker = CreateThread(NULL, 
											0,
											&CCommandHandler::handle,
											this,
											0,			//start immediately after create
											&wid);
}

DWORD CCommandHandler::handle(LPVOID param) {
	CCommandHandler *handler = (CCommandHandler *)param;
	CMasterData *d;
	MasterDataQueue<CMasterData> *q;
	long cmdtype;
	
	//
	char t[512];
	q = handler->dlg->getMasterDataQueue();
	
	while(!handler->finish) {
		d = q->deQueue();
		//sprintf_s(t, "Command Handler handle:::buf[0]=%d,buf[1]=%d", d->buf[0], d->buf[1]);
		//AfxMessageBox(_T(t));
		if( d == NULL) {
			continue;
		}
		//在这里处理各种命令，调用相应的
		//命令解析函数来做。
		cmdtype = d->buf[0];
		handler->dlg->CreateTimer(LOGDATA_TIMER, 5000);
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


	//别忘了在这里要delete CMasterData类型的指针d。
	//因为原则上，这里把这个收到的前端机发送过来的数据
	//处理完毕，就不会再使用了，要把它删除掉。
	//这个CMasterData对象是在Dialog中通过socket收到之际，
	//new 出来放到队列中的！！！
	//每个这样的处理函数都需要这样做。
	//如果这里的数据需要作为长期使用的参数保存，那么
	//应该把它们通过对应的数据结构拷贝出去。
	//delete d;
}
