#ifndef Queue_h
#define Queue_h
#endif
#include <deque>
#include "Data.h"
#include <afxtempl.h>

using namespace std;
class MasterDataQueue
{
public:
	//MasterDataQueue(MasterData &data);
	MasterDataQueue();
	~MasterDataQueue();
public:
    //UINT en(LPVOID lpParam);
	UINT en(MasterData md);
	UINT dn(LPVOID lpParam);
public:
	CList<MasterData, MasterData> Dataqueue;
private:
	//MasterData Mdata;
	HANDLE Mutex;
};

class FrontDataQueue
{
public:
	FrontDataQueue(FrontData &data);
	FrontDataQueue();
	~FrontDataQueue();
public:
    UINT en(LPVOID lpParam);
	UINT dn(LPVOID lpParam);
public:
	CList<FrontData, FrontData> Dataqueue;
private:
	FrontData Fdata;
	HANDLE Mutex;
};

