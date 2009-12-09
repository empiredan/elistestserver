#include "stdafx.h"
#include "ActTable.h"

#include "Utils.h"
#include "commands.h"


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

void CActTable::MaximumCommonSampleRate(int dpthandtime[]) {
	ULONG i;
	int *dpthrate;
	int *timerate;

	ASSERT(actNum > 0);
	dpthrate =  new int[actNum];
	timerate = new int[actNum];
	for(i = 0; i < actNum; i++) {
		dpthrate[i] = pSaList[i].depthSampleRate;
		timerate[i] = pSaList[i].timeInterval;
	}
	dpthandtime[0] = CUtils::lcm(dpthrate, actNum);
	dpthandtime[1] = CUtils::lcm(timerate, actNum);
}


//CActTable* CActTable::AllocateActTable(ULONG actNum, unsigned char *buf, int len) {
CActTable* CActTable::AllocateActTable(ULONG actNum, unsigned char *buf, int len) {
	//�����buf��ȥ������ͷ��buf����ʵ��������������ʼδ֪
	//����Ҳ�Ǽ�ȥ����ͷ�ĳ���
	//actNum�ڵ���ǰ�ɵ����ߴ�socket���յ���buf�н�������
	CActTable *rtn;
	ULONG *f;
	ASSERT(actNum >= 0);
	
	rtn = new CActTable();
	f = (ULONG*)buf;
	rtn->actNum = actNum;
	rtn->nDepthInterruptMode = ntohl(f[1]);
	rtn->pSaList = new RTCSubset[actNum];

	memcpy(rtn->pSaList, buf+2*sizeof(ULONG), len-2*sizeof(ULONG));
	return rtn;
}
//CActTable* CActTable::AllocateActTable(unsigned char *buf, int len) {
CActTable* CActTable::AllocateActTable(unsigned char *buf, int len) {
	//�����buf��ȥ������ͷ��buf����ʵ��������������ʼδ֪
	//����Ҳ�Ǽ�ȥ����ͷ�ĳ���
	//actNum���������
	ULONG actNum;
	ULONG *t;
	t = (ULONG*)buf;
	actNum = ntohl(t[0]);
	return AllocateActTable(actNum, buf, len);
}