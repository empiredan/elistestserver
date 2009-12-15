// DataFileBuf.h: interface for the CDataFileBuf class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAFILEBUF_H__32B6A05D_26E5_4A82_B9D1_825BD44433A5__INCLUDED_)
#define AFX_DATAFILEBUF_H__32B6A05D_26E5_4A82_B9D1_825BD44433A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "commands.h"

class CELISTestServerDlg;
class CDataFileBuf  
{
public:
	CDataFileBuf(CELISTestServerDlg* dlg);
	virtual ~CDataFileBuf();
public:
	CELISTestServerDlg* m_pdlg; 
	BUF_TYPE* m_dataFileBuf;
	BUF_TYPE** m_dataFilePointer;//һ��BYTE�����飬Ԫ�ظ���ΪactNum
	BUF_TYPE* m_nextDataFilePointer;
	UINT m_nextBlockNo;
	ULONG m_dataFileBufSize;//buf��С
	ULONG* m_blockSize;
	UINT m_actNum;
	//float *shareOfCommonBuffer; //��һ�����飬Ԫ�ظ���ΪactNum������ó���ÿһ��Ӧ����Ĺ����ļ���������С��������������������ֵ����ÿ����Ӧ�ֵõĻ������ռ��С��
public:
	BUF_TYPE* getNextDataPointer(int i);
	void create(ULONG bufsize, UINT actnum);
	void clear();
	void allocateDataFilePointer(float *socb);
	void fillWithDataFile();
	BUF_TYPE* getNextDataPointer();
};

#endif // !defined(AFX_DATAFILEBUF_H__32B6A05D_26E5_4A82_B9D1_825BD44433A5__INCLUDED_)
