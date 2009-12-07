// TabAct.cpp : implementation file
//

#include "stdafx.h"
#include "TabAct.h"
#include "ELISTestServer.h"
#include "ELISTestServerDlg.h"

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

void TabAct::setCElisTestServerDlg(CELISTestServerDlg* dlg)
{
	m_pELISTestServerDlg=dlg;
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
	//ON_NOTIFY(HDN_ITEMDBLCLICK, IDC_LIST_ACT, OnItemdblclickListAct)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACT, OnDblclkListAct)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TabAct message handlers
/*
void TabAct::OnItemdblclickListAct(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	NMLISTVIEW* pNMLISTVIEW=(NMLISTVIEW*)pNMHDR;
	int rowNo=pNMLISTVIEW->iItem;
	int columeNo=pNMLISTVIEW->iSubItem;
	AfxMessageBox(_T("Yes!"));
	if (columeNo==6)
	{
		AfxMessageBox(_T("Yes!"));
	}
	*pResult = 0;


}
*/

void TabAct::OnDblclkListAct(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NMLISTVIEW* pNMLISTVIEW=(NMLISTVIEW*)pNMHDR;
	int rowNo=pNMLISTVIEW->iItem;
	int columeNo=pNMLISTVIEW->iSubItem;

	/*char t[20];
	sprintf(t, "%d", rowNo);
	AfxMessageBox(_T(t));*/
	//AfxMessageBox(_T("Hello!"));

	if (columeNo==6)
	{
		//AfxMessageBox(_T("Yes!"));
		//CELISTestServerDlg* parentDlg=(CELISTestServerDlg*)(this->GetParent());
		m_pELISTestServerDlg->UpdateData(TRUE);
		CString actListRootFolder=m_pELISTestServerDlg->m_actListRootFolder;
		if (actListRootFolder=="")
		{
			char t[50];
			sprintf(t, "%s", "ACT数据文件目录不能为空!");
			AfxMessageBox(_T(t));
		}else{

			WIN32_FIND_DATA fd;
			HANDLE hFind = FindFirstFile(actListRootFolder, &fd);
			if ((hFind != INVALID_HANDLE_VALUE) && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
				//目录存在
				CFileDialog openActDataFileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_FILEMUSTEXIST, "All Files(*.*)|*.*||", this);
				openActDataFileDlg.m_ofn.lpstrInitialDir=actListRootFolder;
				CString strFilePath;
				if (openActDataFileDlg.DoModal()==IDOK)
				{
					strFilePath=openActDataFileDlg.GetPathName();
					m_listctrlAct.SetItemText(rowNo, 6, strFilePath);
				}
			}else{
				char t[50];
				sprintf(t, "%s", "此目录已不存在!");
				AfxMessageBox(_T(t));
			}
		}
		

	}
	*pResult = 0;
}
