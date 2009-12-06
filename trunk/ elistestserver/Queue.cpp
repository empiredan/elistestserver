#include "stdafx.h"
#include "Queue.h"


Queue::Queue() {

}
Queue::~Queue() {

}

MasterDataQueue::MasterDataQueue():Queue(),queue(),masterMtx(),
masterEvt(FALSE, FALSE) {
	
}
MasterDataQueue::~MasterDataQueue() {
	
}

void MasterDataQueue::en(CMasterData *data) {
	//AfxMessageBox(_T("MasterData enqueued!"));
	CSingleLock l(&masterMtx);
	if(l.Lock()) {
		queue.AddTail(data);
		masterEvt.SetEvent();
	}
	l.Unlock();
}
CMasterData* MasterDataQueue::de() {
	CMasterData *d;
	CSingleLock l(&masterMtx);
	while(queue.IsEmpty()) {
		//AfxMessageBox(_T("MasterDataQueue  empty, waitting!"));
		::WaitForSingleObject(masterEvt.m_hObject, 3000);
	}
	if(l.Lock()) {
		d = queue.RemoveHead();
	}
	l.Unlock();
	return d;
}


FrontDataQueue::FrontDataQueue():Queue(),queue(),frontMtx(),
frontEvt(FALSE, FALSE) {
	
}
FrontDataQueue::~FrontDataQueue() {
	
}
void FrontDataQueue::en(CFrontData *data) {
	CSingleLock l(&frontMtx);
	if(l.Lock()) {
		queue.AddTail(data);
		frontEvt.SetEvent();
	}
	l.Unlock();
}
CFrontData* FrontDataQueue::de() {
	CFrontData *d;
	CSingleLock l(&frontMtx);
	while(queue.IsEmpty()) {
		//AfxMessageBox(_T("FrontDataQueue  empty, waitting!"));
		::WaitForSingleObject(frontEvt.m_hObject, 3000);
	}
	if(l.Lock()) {
		d = queue.RemoveHead();
	}
	l.Unlock();
	return d;
}
