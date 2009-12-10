#ifndef ACTTABLE_H
#define ACTTABLE_H


//#pragma once

class RTCSubset
{
public:
	int	actNo;
	int	switchOn;
	int	actDone;
	int	depthSampleRate;
	int	timeInterval;

	//下面的是RtcSUBSET_CMD
	int	toolAddress;
	int	subsetNo;			//0－f，仪器身份标识
	int	delay;
	int	m2Length;
	int	m5Length;
	int	m7Length;
public:
	void ConvertData() {
		actNo = ntohl(actNo);
		switchOn = ntohl(switchOn);
		actDone = ntohl(actDone);
		depthSampleRate = ntohl(depthSampleRate);
		timeInterval = ntohl(timeInterval);

		toolAddress = ntohl(toolAddress);
		subsetNo = ntohl(subsetNo);
		delay = ntohl(delay);
		m2Length = ntohl(m2Length);
		m5Length = ntohl(m5Length);
		m7Length = ntohl(m7Length);
	}
};

class CActTable
{
public:
	ULONG actNum;
	ULONG nDepthInterruptMode;
	RTCSubset *pSaList;
public:
	CActTable::CActTable(void);
	CActTable::~CActTable(void);
public:
	void MaximumCommonSampleRate(int dpthandtime[]);
public:
	static CActTable* AllocateActTable(ULONG actNum, unsigned char *buf, int len);
	static CActTable* AllocateActTable(unsigned char  *buf, int len);
public:
	void ConvertData() {
		ULONG i;
		for( i = 0; i < actNum; i++) {
			pSaList[i].ConvertData();
		}
	}
public:
	int getCommonMultiple();
	int getCommonDivisor();
	int FindSubsetNum();
	ULONG FindSubset();
};


#endif