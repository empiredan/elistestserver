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
	//dpthandtime[0] = CUtils::lcm(dpthrate, actNum);
	//dpthandtime[1] = CUtils::lcm(timerate, actNum);
}


//CActTable* CActTable::AllocateActTable(ULONG actNum, unsigned char *buf, int len) {
CActTable* CActTable::AllocateActTable(ULONG actNum, unsigned char *buf, int len) {
	//这里的buf是去掉命令头的buf，是实际数据真正的起始未知
	//长度也是减去命令头的长度
	//actNum在调用前由调用者从socket接收到的buf中解析出来
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
	//这里的buf是去掉命令头的buf，是实际数据真正的起始未知
	//长度也是减去命令头的长度
	//actNum在这里解析
	ULONG actNum;
	ULONG *t;
	t = (ULONG*)buf;
	actNum = ntohl(t[0]);
	return AllocateActTable(actNum, buf, len);
}

void CActTable::buildSubsetDataAssister(CSubsetDataAssister *assist, float speed, UINT workState) {
	assist->create(actNum);

	ULONG i;
	ULONG lcm, gcd;

	UINT *depth, *time;
	UINT totalSubsets;

	depth = new UINT[actNum];
	time = new UINT[actNum];

	for(i = 0; i < actNum; i++) {
		depth[i] = pSaList[i].depthSampleRate;
		time[i] = pSaList[i].timeInterval;
	}
	lcm = CUtils::GetCommonMultipler(time, actNum);
	gcd = CUtils::GetCommonDivider(depth, actNum);

	ASSERT(lcm > 0);
	ASSERT(gcd > 0);

	if(workState == RtcSYS_STANDBY_CMD) {//time模式
		assist->assist.logTimerElapse = lcm;
		totalSubsets = 0;
		for(i = 0; i < actNum; i++) {
			assist->assist.subsetNumPerReturn[i] = lcm/pSaList[i].timeInterval;
			assist->assist.totalSizeOfSubsetsPerReturn[i] = assist->assist.subsetNumPerReturn[i]*subsetSize(i);
			totalSubsets += assist->assist.totalSizeOfSubsetsPerReturn[i];
		}
		for(i = 0; i < actNum; i++) {
			assist->assist.shareOfCommonBuffer[i] = ((float)assist->assist.totalSizeOfSubsetsPerReturn[i])/((float)totalSubsets);
		}
	} else if(workState == RtcSYS_RECSTART_CMD) {//depth模式
		assist->assist.logTimerElapse = (UINT)(1000/(speed*gcd));
		totalSubsets = 0;
		for(i = 0; i < actNum; i++) {
			assist->assist.subsetNumPerReturn[i] = pSaList[i].depthSampleRate/gcd;
			assist->assist.totalSizeOfSubsetsPerReturn[i] = assist->assist.subsetNumPerReturn[i]*subsetSize(i);
			totalSubsets += assist->assist.totalSizeOfSubsetsPerReturn[i];
		}
		for(i = 0; i < actNum; i++) {
			assist->assist.shareOfCommonBuffer[i] = ((float)assist->assist.totalSizeOfSubsetsPerReturn[i])/((float)totalSubsets);
		}
	} else {
		//AfxMessageBox(_T("buildSubsetDataAssister, wrong "));
	}
	//initialize header
	for(i = 0; i < actNum; i++) {
		assist->heads[i].toolAddr = pSaList[i].toolAddress;
		assist->heads[i].subset = pSaList[i].subsetNo;
		assist->heads[i].subsetCnt = assist->assist.subsetNumPerReturn[i];
		assist->heads[i].currentDepth = 0;
		assist->heads[i].dataSize = subsetSize(i);
		assist->heads[i].actSwitch = 111;
		assist->heads[i].currentTime = 0;
	}
}