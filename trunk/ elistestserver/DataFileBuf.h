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
	BUF_TYPE** m_dataFilePointer;//一个BYTE型数组，元素个数为actNum
	BUF_TYPE** m_currentDataFilePointer;
	BUF_TYPE** m_nextDataFilePointer;
	UINT m_currentDataFilePointerIndex;
	//UINT m_nextBlockNo;
	ULONG m_dataFileBufSize;//buf大小
	ULONG* m_blockSize;
	ULONG* m_realUsedBlockSize;
	UINT m_actNum;
	//float *shareOfCommonBuffer; //是一个数组，元素个数为actNum，计算得出的每一项应分配的公共文件缓冲区大小比例。根据这个数组里的值计算每个项应分得的缓冲区空间大小。
public:
	//BUF_TYPE* getNextDataPointer(UINT i);
	BUF_TYPE* getNextDataPointer(UINT i, UINT32 subsetSize);
	void create(ULONG bufsize, UINT actnum);
	void clear();
	void allocateDataFilePointer(float *socb);
	void fillWithDataFile();
	//BUF_TYPE* getNextDataPointer();
};

#endif // !defined(AFX_DATAFILEBUF_H__32B6A05D_26E5_4A82_B9D1_825BD44433A5__INCLUDED_)
