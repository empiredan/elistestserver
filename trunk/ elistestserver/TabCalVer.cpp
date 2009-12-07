// TabCalVer.cpp : implementation file
//

#include "stdafx.h"
#include "TabCalVer.h"
#include "ELISTestServer.h"
#include "ELISTestServerDlg.h"

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

void TabCalVer::setCElisTestServerDlg(CELISTestServerDlg* dlg)
{
	m_pELISTestServerDlg=dlg;
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
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CALVER, OnDblclkListCalver)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TabCalVer message handlers

void TabCalVer::OnDblclkListCalver(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NMLISTVIEW* pNMLISTVIEW=(NMLISTVIEW*)pNMHDR;
	int rowNo=pNMLISTVIEW->iItem;
	int columeNo=pNMLISTVIEW->iSubItem;

	if (columeNo==8)
	{
		//AfxMessageBox(_T("Yes!"));
		//CELISTestServerDlg* parentDlg=(CELISTestServerDlg*)(this->GetParent());
		m_pELISTestServerDlg->UpdateData(TRUE);
		CString calverListRootFolder=m_pELISTestServerDlg->m_calverListRootFolder;
		if (calverListRootFolder=="")
		{
			char t[50];
			sprintf(t, "%s", "Cal/Ver数据文件目录不能为空!");
			AfxMessageBox(_T(t));
		}else{

			WIN32_FIND_DATA fd;
			HANDLE hFind = FindFirstFile(calverListRootFolder, &fd);
			if ((hFind != INVALID_HANDLE_VALUE) && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
				//目录存在
				CFileDialog openActDataFileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_FILEMUSTEXIST, "All Files(*.*)|*.*||", this);
				openActDataFileDlg.m_ofn.lpstrInitialDir=calverListRootFolder;
				CString strFilePath;
				if (openActDataFileDlg.DoModal()==IDOK)
				{
					strFilePath=openActDataFileDlg.GetPathName();
					m_listctrlCalVer.SetItemText(rowNo, 6, strFilePath);
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
