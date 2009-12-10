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
	m_dataFileBuf=NULL;
	m_dataFilePointer=NULL;
	m_blockSize=NULL;
}

CDataFileBuf::~CDataFileBuf()
{
	
	clear();
}
void CDataFileBuf::clear()
{
	if (m_dataFileBuf)
	{
		delete[] m_dataFileBuf;
	}
	if (m_dataFilePointer)
	{
		delete[] m_dataFilePointer;
	}
	if (m_blockSize)
	{
		delete[] m_blockSize;
	}
}
void CDataFileBuf::create(ULONG bufsize, UINT actnum)
{
	m_dataFileBufSize=bufsize;
	m_actNum=actnum;
	m_dataFileBuf=new BUF_TYPE[m_dataFileBufSize];
	m_dataFilePointer=new BUF_TYPE*[m_actNum];
	m_blockSize=new ULONG[m_actNum];
}
void CDataFileBuf::allocateDataFilePointer(float *socb)
{
	BUF_TYPE* p=m_dataFileBuf;


	for (UINT i=0; i<m_actNum; i++)
	{
		m_dataFilePointer[i]=p;
		m_blockSize[i]=(ULONG)(m_dataFileBufSize*socb[i]);
		p+=m_blockSize[i];
	}

}
void CDataFileBuf::fillWithDataFile()
{
	MyListCtrl* p_actList=&(m_pdlg->m_tabMyTabCtrl.m_dlgAct->m_listctrlAct);

	for (UINT i=0; i<m_actNum; i++)
	{
		CString filePath=p_actList->GetItemText(i, 5);
		if (filePath!="")
		{
			CFile dataFile(filePath, CFile::modeRead);
			dataFile.Seek(sizeof(UINT32)*3, CFile::begin);
			dataFile.Read(m_dataFilePointer[i],m_blockSize[i]);
			dataFile.Close();
		} 
		else//随机指定填入缓冲区的数据
		{
			
			for (ULONG j=0; j<m_blockSize[i]; j++)
			{
				m_dataFilePointer[i][j]=(BUF_TYPE)(rand()%256);

			}
		}
		
		
	}

}