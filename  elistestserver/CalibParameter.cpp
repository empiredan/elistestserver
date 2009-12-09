// CalibParameter.cpp: implementation of the CCalibParameter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ELISTestServer.h"
#include "CalibParameter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCalibParameter::CCalibParameter(BUF_TYPE *buf, ULONG len)
{
	ASSERT(len == sizeof(CALIB_PARA));
	memcpy(&cpara, buf, len);
	ConvertData();
}

CCalibParameter::~CCalibParameter()
{
	
}
int CCalibParameter::getToolADDR()
{
	int cmd=cpara.m_nCalibAcqCmd;
	cmd=cmd>>8;
	int toolADDR=cmd&255;
	return toolADDR;
}
int CCalibParameter::getSubsetNo()
{
	int cmd=cpara.m_nCalibAcqCmd;
	int subsetNo=cmd&15;
	return subsetNo;
}
