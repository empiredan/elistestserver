// CalibSubset.cpp: implementation of the CCalibSubset class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ELISTestServer.h"
#include "CalibSubset.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCalibSubset::CCalibSubset()
{
	//�˴��������calib subsetdata body���ȵĴ���Ҫ����
	//�յ��������������ĽṹCActTable������
	//bodyLen = sizeof();
	AfxMessageBox(_T("�˴��������calib subset subsetdata body���ȵĴ���Ҫ�����յ��������������ĽṹCActTable������"));
	cmdLen = bodyLen + SOCK_RECEIVE_HEADER_LEN;
	cmdType = NET_RETURN_SNGLACQ_DATAREADY;
}

CCalibSubset::CCalibSubset(BUF_TYPE* bf, ULONG len):CFrontData(bf, len)
{
	//�˴��������calib subsetdata body���ȵĴ���Ҫ����
	//�յ��������������ĽṹCActTable������
	//bodyLen = sizeof();
	AfxMessageBox(_T("�˴��������calib subset subsetdata body���ȵĴ���Ҫ�����յ��������������ĽṹCActTable������"));
	cmdLen = bodyLen + SOCK_RECEIVE_HEADER_LEN;
	cmdType = NET_RETURN_SNGLACQ_DATAREADY;
}

CCalibSubset::~CCalibSubset()
{

}
