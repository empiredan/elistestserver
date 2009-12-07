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
		//�����ﴦ��������������Ӧ��
		//�����������������
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


	//������������Ҫdelete CMasterData���͵�ָ��d��
	//��Ϊԭ���ϣ����������յ���ǰ�˻����͹���������
	//������ϣ��Ͳ�����ʹ���ˣ�Ҫ����ɾ������
	//���CMasterData��������Dialog��ͨ��socket�յ�֮�ʣ�
	//new �����ŵ������еģ�����
	//ÿ�������Ĵ���������Ҫ��������
	//��������������Ҫ��Ϊ����ʹ�õĲ������棬��ô
	//Ӧ�ð�����ͨ����Ӧ�����ݽṹ������ȥ��
	//delete d;
}
