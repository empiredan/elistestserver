#include "stdafx.h"
#include "Queue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/*
MasterDataQueue::MasterDataQueue(MasterData &data)
{
	Mdata =  data;
	Mutex = CreateMutex(NULL, TRUE, NULL);
}
*/

MasterDataQueue::MasterDataQueue()
{
	
	Mutex = CreateMutex(NULL, TRUE, NULL);
}
/*
UINT MasterDataQueue::en(LPVOID lpParam)
{
      WaitForSingleObject(Mutex, INFINITE);
      this->Dataqueue.AddTail(Mdata);
	  ReleaseMutex(Mutex);
	  return 0;
}
*/
UINT MasterDataQueue::en(MasterData md)
{
	WaitForSingleObject(Mutex, INFINITE);
	this->Dataqueue.AddTail(md);
	ReleaseMutex(Mutex);
	return 0;
}

UINT MasterDataQueue::dn(LPVOID lpParam)
{
	   WaitForSingleObject(Mutex, INFINITE);
	   if (!Dataqueue.IsEmpty())
	   {
	      this->Dataqueue.RemoveHead();
	   }
	   ReleaseMutex(Mutex);
	   return 0;
}


FrontDataQueue::FrontDataQueue(FrontData &data)
{
	Fdata = data;
	Mutex = CreateMutex(NULL, FALSE, NULL);
}

UINT FrontDataQueue::en(LPVOID lpParam)
{
	WaitForSingleObject(Mutex, INFINITE);
	this->Dataqueue.AddTail(Fdata);
	ReleaseMutex(Mutex);
	return 0;
}

UINT FrontDataQueue::dn(LPVOID lpParam)
{

	WaitForSingleObject(Mutex, INFINITE);
	if (!Dataqueue.IsEmpty())
		{
			this->Dataqueue.RemoveHead();
		}
	ReleaseMutex(Mutex); 
	return 0;
}

