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
void CDataFileBuf::increase(UINT i) {
	//
	UINT sz = m_pdlg->m_subsetAssister->assist.totalSizeOfSubsetsPerReturn[i];
	bf[i].dbcur += sz;
	if(bf[i].dbcur == bf[i].dbhead + bf[i].dbufsz) {
		//
		bf[i].dbcur = bf[i].dbhead;
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
		
		bf[i].fileExists = TRUE;
	} else {
		bf[i].fileExists = FALSE;
		fillInWithRandomData(i);
	}
}

BUF_TYPE* CDataFileBuf::getNextDataPointer(int i)
{
	BUF_TYPE *rtn;
	
	rtn = bf[i].dbcur;
	increase(i);

	return rtn;
}
