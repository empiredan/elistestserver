#include "stdafx.h"
#include "TimerThread.h"

#ifdef _DEBUG
#define new DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

UINT TimerThread::timerqueueProc(LPVOID lparam)
{
	//���ڲ��� FrontData�����뷢�Ͷ�����
	FrontDataQueue *frontdataque = (FrontDataQueue *)lparam;
	//........
	FrontData frontdata;
	Sleep(10000);
	frontdataque->en(frontdata);
	return 0;
	SetTimer()
}

void TimerThread::create()
{
	pthread = AfxBeginThread(timerqueueProc, this);
}