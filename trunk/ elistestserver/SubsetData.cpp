#include "stdafx.h"
#include "SubsetData.h"

CSubsetData::CSubsetData(void)
{
	//�˴��������subsetdata body���ȵĴ���Ҫ����
	//�յ��������������ĽṹCActTable������
	//bodyLen = sizeof();
	AfxMessageBox(_T("�˴��������subsetdata body���ȵĴ���Ҫ�����յ��������������ĽṹCActTable������"));
	cmdLen = bodyLen + SOCK_RECEIVE_HEADER_LEN;
	cmdType = NET_RETURN_SUBSETDATA;
}
CSubsetData::CSubsetData(BUF_TYPE* bf, ULONG len):CFrontData(bf, len)
{
	//�˴��������subsetdata body���ȵĴ���Ҫ����
	//�յ��������������ĽṹCActTable������
	AfxMessageBox(_T("�˴��������subsetdata body���ȵĴ���Ҫ�����յ��������������ĽṹCActTable������"));
	//bodyLen = sizeof();
	cmdLen = bodyLen + SOCK_RECEIVE_HEADER_LEN;
	cmdType = NET_RETURN_SUBSETDATA;
}

CSubsetData::~CSubsetData(void)
{
}
