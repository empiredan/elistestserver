// DataFileBuf.cpp: implementation of the CDataFileBuf class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ELISTestServer.h"
#include "ELISTestServerDlg.h"
#include "MyListCtrl.h"
#include "DataFileBuf.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataFileBuf::CDataFileBuf(CELISTestServerDlg* dlg)
{
	m_pdlg=dlg;
	store = NULL;
	bf = NULL;
}

CDataFileBuf::~CDataFileBuf()
{
	clear();
}
void CDataFileBuf::clear()
{
	if (bf != NULL)
	{
		delete[] bf;
	}
	if(store != NULL) {
		delete []store;
	}
}
void CDataFileBuf::clearStore() {
	if(store != NULL) delete []store;
}
void CDataFileBuf::clearLayout() {
	if(bf != NULL) delete []bf;
}
void CDataFileBuf::layout() {
	float *share = m_pdlg->m_subsetAssister->assist.shareOfCommonBuffer;
	UINT *numPerRtn = m_pdlg->m_subsetAssister->assist.subsetNumPerReturn;
	UINT *tSizePerRtn = m_pdlg->m_subsetAssister->assist.totalSizeOfSubsetsPerReturn;
	ULONG bufszi;

	BUF_TYPE *c;
	c = store;
	for (UINT i = 0; i < m_actNum; i++)
	{
		bufszi = ((ULONG)((m_dataFileBufSize*share[i])/tSizePerRtn[i]))*tSizePerRtn[i];
		bf[i].dbhead = c;
		bf[i].dbcur = c;
		c += bufszi;
		bf[i].dbufsz = bufszi;
		bf[i].fileExists = FALSE;
	}
}
void CDataFileBuf::createStore(ULONG bufsize) {
	//
	clearStore();
	
	m_dataFileBufSize = bufsize;
	ASSERT(m_dataFileBufSize > 0);
	store = new BUF_TYPE[m_dataFileBufSize];
	ASSERT(store != NULL);
}
void CDataFileBuf::createLayout(UINT actnum) {
	//
	clearLayout();
	
	m_actNum = actnum;
	ASSERT(m_actNum > 0);
	bf = new Buffer[actnum];
	ASSERT(bf != NULL);
}

void CDataFileBuf::create(ULONG bufsize, UINT actnum)
{
	createStore(bufsize);
	createLayout(actnum);
}
//״̬����Ⱥ�ʱ��ģʽ֮���л�ʱ��
//��CalVer״̬����ʱ
//����buildSubsetDataAssister֮��(��CalVer״̬����ʱ����Ҫ�ⲽ)
//Ҫ��������������¼��������ļ���仺����
void CDataFileBuf::fillWithDataFile()
{
	MyListCtrl* p_actList=&(m_pdlg->m_tabMyTabCtrl.m_dlgAct->m_listctrlAct);

	for (UINT i=0; i<m_actNum; i++)
	{
		CString filePath=p_actList->GetItemText(i, 5);
		fillIn(filePath, i);
	}
}
//�л���CalVerʱҪ��������������ؿ̶������ļ�
void CDataFileBuf::fillWithDataFile(UINT i, CString &file) {
	//ΪCalVer����
	fillIn(file, i);
}
void CDataFileBuf::fillWithDataFile(UINT i) {
	//Ϊ����Դ�ļ����ı����ã�
	MyListCtrl* p_actList=&(m_pdlg->m_tabMyTabCtrl.m_dlgAct->m_listctrlAct);
	CString filePath=p_actList->GetItemText(i, 5);
	fillIn(filePath, i);
}
void CDataFileBuf::increase(UINT i, UINT disp) {
	//
	//UINT sz = m_pdlg->m_subsetAssister->assist.totalSizeOfSubsetsPerReturn[i];
	bf[i].dbcur += disp;
	if(bf[i].dbcur >= bf[i].dbhead + bf[i].dbufsz) {
		//
		resetCurrentPointer(i);
	}
}
void CDataFileBuf::fillInWithRandomData(UINT i) {
	//
}
void CDataFileBuf::fillIn(CString &filePath, UINT i) {
	//
	CFileException ex;
	char szerror[1024];
	if (filePath != "") {
		if(!bf[i].df.Open(_T(filePath), CFile::modeRead, &ex)) {
			ex.GetErrorMessage(szerror, 1024);
			AfxMessageBox(_T(szerror));
		}
		bf[i].df.Seek(sizeof(UINT32)*3, CFile::begin);
		bf[i].df.Read(bf[i].dbhead, bf[i].dbufsz);
		bf[i].df.Close();
		bf[i].fileExists = TRUE;
	} else {
		bf[i].fileExists = FALSE;
		fillInWithRandomData(i);
	}
	resetCurrentPointer(i);
}

BUF_TYPE* CDataFileBuf::getNextDataPointer(UINT i)
{
	BUF_TYPE *rtn;
	rtn = bf[i].dbcur;
	UINT disp = m_pdlg->m_subsetAssister->assist.totalSizeOfSubsetsPerReturn[i];
	increase(i, disp);

	return rtn;
}

BUF_TYPE* CDataFileBuf::getNextCalibSubsetDataPointer()
{
	BUF_TYPE *rtn;
	UINT i = getCalVerBufBlockIndex();
	rtn = bf[i].dbcur;
	UINT disp = m_pdlg->calibpara->calulcateSubsetMasterSize();
	increase(i, disp);
	
	return rtn;
}

UINT CDataFileBuf::getCalVerBufBlockIndex()
{
	int toolADDR = m_pdlg->calibpara->getToolADDR();
	int subsetNo = m_pdlg->calibpara->getSubsetNo();
	
	MyListCtrl& actListCtrl=m_pdlg->m_tabMyTabCtrl.m_dlgAct->m_listctrlAct;
	
	UINT i;
	for (i = 0;i < actListCtrl.GetItemCount();i++)
	{
		if ( (toolADDR==atoi(actListCtrl.GetItemText(i,1)))
			&& (subsetNo==atoi(actListCtrl.GetItemText(i,2))) )
		{
			break;
		}
	}

	return i;
}

void CDataFileBuf::resetCurrentPointer(UINT i)
{
	bf[i].dbcur = bf[i].dbhead;
}

void CDataFileBuf::resetCurrentPointer()
{
	for (UINT i=0;i<m_actNum;i++)
	{
		resetCurrentPointer(i);
	}
}
void CDataFileBuf::Save(CFile &log ) {
	//
	UINT i;
	char b[1024];
	sprintf(b, "BUFLAYOUT:");
	for(i = 0; i < m_actNum; i++) {
		sprintf(b, "%s, i=%d, bufsize:%d,head:0x%lx\n", b, i, bf[i].dbufsz, bf[i].dbhead);
	}
	log.Write(b, strlen(b));
	log.Flush();
}
