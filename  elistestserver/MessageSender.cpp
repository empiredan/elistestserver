#include "stdafx.h"
#include "Data.h"
#include "Queue.h"
#include "MessageSender.h"
#include "ELISTestServer.h"
#include "ELISTestServerDlg.h"

//class CELISTestServerDlg;
CMessageSender::CMessageSender()
{
	this->dlg = dlg;
	finish = FALSE;
}
void CMessageSender::start() {
	worker = CreateThread(NULL, 
											0,
											&CMessageSender::handle,
											this,
											0,			//start immediately after create
											&wid);
}

CMessageSender::~CMessageSender(void)
{
}

DWORD CMessageSender::handle(LPVOID param) {
	CMessageSender *handler = (CMessageSender *)param;
	CFrontData *d;
	FrontDataQueue<CFrontData> *q;
	int err;
	//int *t;
	//char oo[1024];
	
	q = handler->dlg->getFrontDataQueue();
	//AfxMessageBox(_T("MessageSenderStarted:::"));
	while(!handler->finish) {
		d = q->deQueue();
		if( d == NULL || d->buflen <= 0) {
			continue;
		}
		//
		//t = (int*)(d->buf+SOCK_RECEIVE_HEADER_LEN);
		//sprintf(oo, "corr_Depth:%d,true_Depth:%d", t[0], t[1]);
		//AfxMessageBox(_T(oo));
		
		err = handler->dlg->m_psConnectSocket->Send(d->buf, d->contentlen);
		if(err == SOCKET_ERROR) {
			AfxMessageBox(_T("Sending Messages Socket error"));
			delete d;
			continue;
		}
		
		//����Ҳ��������ɾ��CFrontData���͵Ķ���
		//���CFrontData���Ͷ���������ɶ�ʱ��������
		//CommandHendler���߳��ӵ������еģ�����Щ
		//��ʱ�������߳������ͨ��new�İ취����
		//��Щ����ģ���
		delete d;
	}

	return 0;
}
