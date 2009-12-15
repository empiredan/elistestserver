#include "stdafx.h"
#include "SubsetData.h"

#include "ELISTestServerDlg.h"
CSubsetData::CSubsetData(void)
{
	//此处加入计算subsetdata body长度的代码要根据
	//收到的命令所解析的结构CActTable来计算
	bodyLen = 0;
	//AfxMessageBox(_T("此处加入计算subsetdata body长度的代码要根据收到的命令所解析的结构CActTable来计算"));
	//cmdLen = bodyLen + SOCK_RECEIVE_HEADER_LEN;
	cmdLen = 0;
	cmdType = NET_RETURN_SUBSETDATA;
}
CSubsetData::CSubsetData(BUF_TYPE* bf, ULONG len):CFrontData(bf, len)
{
	//此处加入计算subsetdata body长度的代码要根据
	//收到的命令所解析的结构CActTable来计算
	bodyLen = 0;
	//AfxMessageBox(_T("此处加入计算subsetdata body长度的代码要根据收到的命令所解析的结构CActTable来计算"));
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
		assist->heads[i].currentDepth = assist->dataFileBuf->m_pdlg->GetCurrentDepth();//调试注释掉
		assist->heads[i].currentTime = assist->dataFileBuf->m_pdlg->GetCurrentTestTime();//调试注释掉
		//assist->heads[i].currentDepth = 9999;//assist->dataFileBuf->m_pdlg->GetCurrentDepth();//调试注释掉
		//assist->heads[i].currentTime = 8888;//assist->dataFileBuf->m_pdlg->GetCurrentTestTime();//调试注释掉
		
		setData((BUF_TYPE*)&assist->heads[i], assist->getRTCBlockDataHeaderSize());
		//totalSizeOfSubsetsPerReturn里应已经包含了subset头的两个long的长度
		setData(assist->dataFileBuf->getNextDataPointer(), assist->assist.totalSizeOfSubsetsPerReturn[i]);//调试注释掉
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

void CSubsetData::Save(CSubsetDataAssister*assist, CFile &log) {
	char b[4096];
	ULONG *tul;
	UINT32 *tui;
	UINT i,headsize;
	
	tul = (ULONG*)buf;
	sprintf(b, "===cmd start==\nCMDTYPE:%lx,CMDLEN:%d, GENStaus:%lx\n", tul[0], tul[1], tul[2]);
	log.Write(b, strlen(b));
	log.Flush();
	tul = (ULONG*)(buf + 3*sizeof(ULONG));
	headsize = 3*sizeof(ULONG)+4*sizeof(UINT32);
	for(i = 0; i < assist->actNum; i++) {
		tul = (ULONG*)(buf + 3*sizeof(ULONG) +  i*headsize);
		sprintf(b, "ToolAddr:%ld,SubsetNo:%ld,SubsetCnt:%ld",tul[0],tul[1],tul[2]);
		tui = (UINT32*)(tul+3);
		sprintf(b, "CurDepth:%d,DataSize:%d,ActSwitch:%d,CurTime:%d\n", 
			tui[0],tui[1],tui[2],tui[3]);
		log.Write(b, strlen(b));
	}
	sprintf(b, "===cmd end==\n");
	log.Write(b, strlen(b));
	log.Flush();
}
