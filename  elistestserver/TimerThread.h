#ifndef TIME_THREAD
#define TIME_THREAD
#include "Queue.h"


class TimerThread
{
public:
	TimerThread();
	~TimerThread();
public:
	void create();
	static UINT timerqueueProc(LPVOID lparam);
public:
	CWinThread *pthread;
public:
	FrontData Fdata;
	FrontDataQueue *Fqueue;
};


#endif

