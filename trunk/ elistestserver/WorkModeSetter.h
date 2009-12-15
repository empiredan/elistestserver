// WorkModeSetter.h: interface for the CWorkModeSetter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKMODESETTER_H__9B10621B_9E95_4A9E_A0D6_9CB2CEFA5886__INCLUDED_)
#define AFX_WORKMODESETTER_H__9B10621B_9E95_4A9E_A0D6_9CB2CEFA5886__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Data.h"
#include "commands.h"

class CWorkModeSetter  
{
public:
	CWorkModeSetter();
	virtual ~CWorkModeSetter();
public:
	UINT32 oldMode;
	UINT32 mode;
	UINT32 direction;
	UINT32 oldDirection;

	UINT32 standByTimeInterval;

	UINT32 deactivated;

	UINT32 recstop;

	BOOL changeDepth;
	BOOL changeTime;
	BOOL returnSubsetData;
public:
	void fillWorkMode(BUF_TYPE *buf, ULONG len);
	void fillStandByTimeInterval(BUF_TYPE *buf, ULONG len);
	void fillDeactivated(BUF_TYPE *buf, ULONG len);
	void fillRecStop(BUF_TYPE *buf, ULONG len);
};

#endif // !defined(AFX_WORKMODESETTER_H__9B10621B_9E95_4A9E_A0D6_9CB2CEFA5886__INCLUDED_)
