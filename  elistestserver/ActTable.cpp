#include "stdafx.h"
#include "ActTable.h"


CActTable::CActTable(void)
{
	pSaList = NULL;
}

CActTable::~CActTable(void)
{
	if(pSaList != NULL) {
		delete [] pSaList;
	}
}


//CActTable* CActTable::AllocateActTable(long actNum, unsigned char *buf, int len) {
CActTable* CActTable::AllocateActTable(long actNum, unsigned char *buf, int len) {
	//这里的buf是去掉命令头的buf，是实际数据真正的起始未知
	//长度也是减去命令头的长度
	//actNum在调用前由调用者从socket接收到的buf中解析出来
	CActTable *rtn;
	long *f;
	size_t size;
	ASSERT(actNum >= 0);
	
	rtn = new CActTable();
	f = (long*)buf;
	rtn->actNum = actNum;
	rtn->nDepthInterruptMode = f[1];
	rtn->pSaList = new RTCSubset[actNum];
	memcpy(rtn->pSaList, buf+2*sizeof(long), len-2*sizeof(long));
	return rtn;
}
//CActTable* CActTable::AllocateActTable(unsigned char *buf, int len) {
CActTable* CActTable::AllocateActTable(unsigned char *buf, int len) {
	//这里的buf是去掉命令头的buf，是实际数据真正的起始未知
	//长度也是减去命令头的长度
	//actNum在这里解析
	long actNum;
	long *t;
	t = (long*)buf;
	actNum = buf[0];
	return AllocateActTable(actNum, buf, len);
}