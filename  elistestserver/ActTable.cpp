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
	//�����buf��ȥ������ͷ��buf����ʵ��������������ʼδ֪
	//����Ҳ�Ǽ�ȥ����ͷ�ĳ���
	//actNum�ڵ���ǰ�ɵ����ߴ�socket���յ���buf�н�������
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
	//�����buf��ȥ������ͷ��buf����ʵ��������������ʼδ֪
	//����Ҳ�Ǽ�ȥ����ͷ�ĳ���
	//actNum���������
	long actNum;
	long *t;
	t = (long*)buf;
	actNum = buf[0];
	return AllocateActTable(actNum, buf, len);
}