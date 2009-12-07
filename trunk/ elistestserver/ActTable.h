#ifndef ACTTABLE_H
#define ACTTABLE_H


//#pragma once

class RTCSubset
{
public:
	int	actNo;
	int	switchOn;
	int	actDone;
	int DepthSampleRate;
	int TimeInterval;

	//下面的是RtcSUBSET_CMD
	int	toolAddress;
	int	subsetNo;			//0－f，仪器身份标识
	int	delay;
	int	m2Length;
	int	m5Length;
	int	m7Length;
};

class CActTable
{
public:
	long actNum;
	long nDepthInterruptMode;
	RTCSubset *pSaList;
public:
	CActTable::CActTable(void);
	CActTable::~CActTable(void);
public:
	static CActTable* AllocateActTable(long actNum, unsigned char *buf, int len);
	static CActTable* AllocateActTable(unsigned char  *buf, int len);
};


#endif