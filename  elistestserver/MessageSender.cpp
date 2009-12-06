#include "stdafx.h"
#include "Data.h"
#include "Queue.h"
#include "MessageSender.h"
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
	FrontDataQueue *q;
	int err;
	char b[1000];
	int *t;
	
	q = handler->dlg->getFrontDataQueue();
	while(!handler->finish) {
		d = q->de();
		if( d == NULL || d->buflen <= 0) {
			continue;
		}
		t = (int*)d->buf;
		sprintf_s(b, "MessageSender::handler...%ld,%ld, send me to socket!!", t[0], t[1]);
		AfxMessageBox(_T(b));
		//err = handler->dlg->m_psConnectSocket->Send(d->buf, d->buflen);
		//����Ҳ��������ɾ��CFrontData���͵Ķ���
		//���CFrontData���Ͷ���������ɶ�ʱ��������
		//CommandHendler���߳��ӵ������еģ�����Щ
		//��ʱ�������߳������ͨ��new�İ취����
		//��Щ����ģ���
		delete d;
	}

	return 0;
}

