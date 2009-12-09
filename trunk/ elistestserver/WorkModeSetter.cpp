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

}

CWorkModeSetter::~CWorkModeSetter()
{

}
void CWorkModeSetter::fillWorkMode(BUF_TYPE *buf, ULONG len) {
	UINT32 *t;
	t = (UINT32*)buf;
	mode = ntohl(t[0]);
	direction = ntohl(t[1]);
}

void CWorkModeSetter::fillStandByTimeInterval(BUF_TYPE *buf, ULONG len) {
	UINT32 *t;
	t = (UINT32*)buf;
	standByTimeInterval = ntohl(t[0]);
}
void CWorkModeSetter::fillDeactivated(BUF_TYPE *buf, ULONG len) {
}
void CWorkModeSetter::fillRecStop(BUF_TYPE *buf, ULONG len) {
}