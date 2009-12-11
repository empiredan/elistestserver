#include "stdafx.h"
#include "SubsetData.h"

#include "ELISTestServerDlg.h"
CSubsetData::CSubsetData(void)
{
	//�˴��������subsetdata body���ȵĴ���Ҫ����
	//�յ��������������ĽṹCActTable������
	bodyLen = 0;
	//AfxMessageBox(_T("�˴��������subsetdata body���ȵĴ���Ҫ�����յ��������������ĽṹCActTable������"));
	//cmdLen = bodyLen + SOCK_RECEIVE_HEADER_LEN;
	cmdLen = 0;
	cmdType = NET_RETURN_SUBSETDATA;
}
CSubsetData::CSubsetData(BUF_TYPE* bf, ULONG len):CFrontData(bf, len)
{
	//�˴��������subsetdata body���ȵĴ���Ҫ����
	//�յ��������������ĽṹCActTable������
	bodyLen = 0;
	//AfxMessageBox(_T("�˴��������subsetdata body���ȵĴ���Ҫ�����յ��������������ĽṹCActTable������"));
	//cmdLen = bodyLen + SOCK_RECEIVE_HEADER_LEN;
	cmdLen = 0;
	cmdType = NET_RETURN_SUBSETDATA;
}

void CSubsetData::setCommandHeader(CSubsetDataAssister *assist) {
	//
	setBodyLength(assist);
	//must called after setBodyLength
	setHeader(cmdType, cmdLen);

	ULONG generalState = 0;
	setData((BUF_TYPE*)&generalState, sizeof(ULONG));
}
void CSubsetData::setSubsetData(CSubsetDataAssister *assist, CActTable *acttab) {
	//
	UINT i;
	for(i = 0; i < assist->actNum; i++) {
		assist->heads[i].currentDepth = assist->dataFileBuf->m_pdlg->GetCurrentDepth();
		assist->heads[i].currentTime = assist->dataFileBuf->m_pdlg->GetCurrentTestTime();
		
		setData((BUF_TYPE*)&assist->heads[i], assist->getRTCBlockDataHeaderSize());
		//totalSizeOfSubsetsPerReturn��Ӧ�Ѿ�������subsetͷ������long�ĳ���
		setData(assist->dataFileBuf->getNextDataPointer(), assist->assist.totalSizeOfSubsetsPerReturn[i]);
	}
}
void CSubsetData::setData(BUF_TYPE *bf, ULONG len) {
	CData::setData(bf, len);
}
CSubsetData::~CSubsetData(void)
{
}


//must called before setHeader
void CSubsetData::setBodyLength(CSubsetDataAssister *assist) {
	bodyLen = assist->getTotalActDataSize();
	cmdLen = bodyLen + SOCK_RECEIVE_HEADER_LEN;
}
