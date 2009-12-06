// TabAct.cpp : implementation file
//

#include "stdafx.h"
#include "ELISTestServer.h"
#include "TabAct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TabAct dialog


TabAct::TabAct(CWnd* pParent /*=NULL*/)
	: CDialog(TabAct::IDD, pParent)
{
	//{{AFX_DATA_INIT(TabAct)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
}
/*
BOOL TabAct::OnInitDialog()
{
	LVCOLUMN lvcol;
	lvcol.mask=LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;
	lvcol.fmt=LVCFMT_CENTER;
	lvcol.iSubItem=1;
	lvcol.cx=50;
	lvcol.pszText="ACT #";
	this->m_listctrlAct.InsertColumn(0,&lvcol);
	
	lvcol.cx=90;
	lvcol.pszText="Tool Series";
	this->m_listctrlAct.InsertColumn(1,&lvcol);
	
	lvcol.cx=80;
	lvcol.pszText="Subset #";
	this->m_listctrlAct.InsertColumn(2,&lvcol);
	
	lvcol.cx=120;
	lvcol.pszText="Depth Samplerate";
	this->m_listctrlAct.InsertColumn(3,&lvcol);
	
	lvcol.cx=100;
	lvcol.pszText="Time Interval";
	this->m_listctrlAct.InsertColumn(4,&lvcol);
	
	lvcol.cx=130;
	lvcol.pszText="Change Mapping Mode";
	this->m_listctrlAct.InsertColumn(5,&lvcol);

	return true;
}
*/
void TabAct::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TabAct)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_LIST_ACT, m_listctrlAct);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TabAct, CDialog)
	//{{AFX_MSG_MAP(TabAct)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TabAct message handlers
