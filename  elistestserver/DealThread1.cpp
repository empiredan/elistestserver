#include "stdafx.h"
#include "DealThread.h"
#include "ELISTestServer.h"
#include "ELISTestServerDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

long DealThread::length=0;
char DealThread::buf[]={'0'};

DealThread::DealThread(CELISTestServerDlg* pDlg)
{
	pserverDlg = pDlg;
}

DealThread::~DealThread()
{

}


void DealThread::SetParent(CELISTestServerDlg* pDlg)
{
	pserverDlg = pDlg;
}

UINT DealThread::queuethreadProc(LPVOID lparam)
{
	MasterDataQueue *masterqueue = (MasterDataQueue *)lparam;
	MasterData masterdata;

	//从接收队列中取数据
	masterdata = masterqueue->dn();
	//解析MasterData
	length = masterdata.buf.GetLength();
	memcpy(buf, masterdata.buf, sizeof(masterdata.buf));
	char t[50];
	sprintf(t, "%s", buf);
	AfxMessageBox(_T(t), MB_YESNO, 0);
	//应答
	//.......
    //判断情况，应答后，如果需要反馈，则将对象放入命令发送队列
	switch(length)
	{
	case 1:
		//不需反馈
		break;
	case 2:
        //需要反馈
		//......
		FrontData frontdata;
		//frontdata.buflen = length;
		//memcpy(frontdata.buf, buf, sizeof(buf));
		frontdata.buf=buf;
		FrontDataQueue *frontque;
	    frontque->en(frontdata);
	}
	
	return 0;
}

void DealThread::create()
{
	/*
	char str[] = "123456789";
	memcpy(this->Mdata.buf, str, sizeof(str));
	this->Mdata.buflen = sizeof(str);
	int i;
	for (i=0; i<10; i++)
	{
		Mqueue->en(Mdata);

	}
	*/
	//建立命令处理线程
	pthread = AfxBeginThread(queuethreadProc, this);
}
