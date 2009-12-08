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

	//�������RtcSUBSET_CMD
	int	toolAddress;
	int	subsetNo;			//0��f��������ݱ�ʶ
	int	delay;
	int	m2Length;
	int	m5Length;
	int	m7Length;
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
};


#endif