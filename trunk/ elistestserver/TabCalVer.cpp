// TabCalVer.cpp : implementation file
//

#include "stdafx.h"
#include "ELISTestServer.h"
#include "TabCalVer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TabCalVer dialog


TabCalVer::TabCalVer(CWnd* pParent /*=NULL*/)
	: CDialog(TabCalVer::IDD, pParent)
{
	//{{AFX_DATA_INIT(TabCalVer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
}


void TabCalVer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TabCalVer)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_LIST_CALVER, m_listctrlCalVer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TabCalVer, CDialog)
	//{{AFX_MSG_MAP(TabCalVer)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TabCalVer message handlers
