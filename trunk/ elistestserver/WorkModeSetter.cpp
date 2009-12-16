// WorkModeSetter.cpp: implementation of the CWorkModeSetter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ELISTestServer.h"
#include "WorkModeSetter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWorkModeSetter::CWorkModeSetter()
{
	changeDepth = FALSE;
	changeTime = FALSE;
	returnSubsetData = FALSE;
	depthSign = 0;

	old2Mode = 0;
	oldMode = 0;
	mode = 0;
	old2Direction = -2;
	oldDirection = -2;
	direction = -2;
}

CWorkModeSetter::~CWorkModeSetter()
{

}
void CWorkModeSetter::fillWorkMode(BUF_TYPE *buf, ULONG len) {
	UINT32 *t;
	t = (UINT32*)buf;
	
	oldMode = mode;
	mode = ntohl(t[0]);

	oldDirection = direction;
	direction = ntohl(t[1]);
}

void CWorkModeSetter::fillStandByTimeInterval(BUF_TYPE *buf, ULONG len) {
	UINT32 *t;
	t = (UINT32*)buf;
	//StandbyTime interval
	standByTimeInterval = ntohl(t[0]);
}
void CWorkModeSetter::fillDeactivated(BUF_TYPE *buf, ULONG len) {
	UINT32 *t;
	t = (UINT32*)buf;
	//RtcSYS_DEACTIVE_CMD
	deactivated = ntohl(t[0]);
}
void CWorkModeSetter::fillRecStop(BUF_TYPE *buf, ULONG len) {
	UINT32 *t;
	t = (UINT32*)buf;
	//RtcSYS_RECSTOP_CMD
	recstop = ntohl(t[0]);
}