#if !defined(QUEUE_H)
#define QUEUE_H
#include <afxmt.h>
#include "Data.h"

class Queue {
public:
	Queue();
	~Queue();
public:
	//synchronization objects declaration
	//enqueue, dequeue methods
};


class MasterDataQueue:public Queue {
public:
	MasterDataQueue();
	~MasterDataQueue();
public:
	virtual void en(CMasterData *data);
	virtual CMasterData* de();
public:
	CList<CMasterData*, CMasterData*> queue;
	CMutex masterMtx;
	CEvent masterEvt;
};

class FrontDataQueue:public Queue {
public:
	FrontDataQueue();
	~FrontDataQueue();
public:
	virtual void en(CFrontData *data);
	virtual CFrontData* de();
public:
	CList<CFrontData*, CFrontData*> queue;
	CMutex frontMtx;
	CEvent frontEvt;
};

#endif