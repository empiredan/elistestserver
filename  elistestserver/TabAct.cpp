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
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACT, OnDblclkListAct)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_PAINT()
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

void TabAct::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	SCROLLINFO hScrollInfo;
	GetScrollInfo(SB_HORZ, &hScrollInfo);
	int oPos = hScrollInfo.nPos;
	int min = hScrollInfo.nMin;
	int max = hScrollInfo.nMax;
	int thumbwidth = hScrollInfo.nPage;

	switch(nSBCode){
	case SB_THUMBTRACK:
		ScrollWindow(-(nPos-oPos),0);//滚动条向右移动时,dlg窗口其实是在向左移动.pos表示原始位置,nPos表示新位置
		//RedrawWindow();
		SetScrollPos(SB_HORZ,nPos);
		break;
	case SB_LINELEFT://滚动条向左移动
		if (oPos!=0)
		{
			ScrollWindow(1,0);//dlg窗口向右移动
			SetScrollPos(SB_HORZ,oPos-1);//滚动条向左移动
		}
		break;
	case SB_LINERIGHT://滚动条向右移动
		if (oPos+thumbwidth<=max)
		{
			ScrollWindow(-1,0);//dlg窗口向左移动
			SetScrollPos(SB_HORZ,oPos+1);//滚动条向右移动
		}
		break;
	case SB_PAGELEFT:
		if (oPos>=thumbwidth)
		{
			ScrollWindow(thumbwidth,0);//dlg窗口向右移动
			SetScrollPos(SB_HORZ,oPos-thumbwidth);//滚动条向左移动
		}else{
			ScrollWindow(oPos,0);//dlg窗口向右移动
			SetScrollPos(SB_HORZ,0);//滚动条移到最左端
		}
		break;
	case SB_PAGERIGHT:
		if (oPos+thumbwidth<=max-thumbwidth)
		{
			ScrollWindow(-thumbwidth,0);//dlg窗口向左移动
			SetScrollPos(SB_HORZ,oPos+thumbwidth);//滚动条向右移动
		}else{
			ScrollWindow(-(max-(oPos+thumbwidth)),0);//dlg窗口向左移动
			SetScrollPos(SB_HORZ,max-thumbwidth);//滚动条移到最右端
		}
		break;
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void TabAct::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	SCROLLINFO vScrollInfo;
	GetScrollInfo(SB_VERT, &vScrollInfo);
	int oPos = vScrollInfo.nPos;
	int min = vScrollInfo.nMin;
	int max = vScrollInfo.nMax;
	int thumbwidth = vScrollInfo.nPage;
	
	switch(nSBCode){
	case SB_THUMBTRACK:
		ScrollWindow(0,-(nPos-oPos));//滚动条向右移动时,dlg窗口其实是在向左移动.pos表示原始位置,nPos表示新位置
		//RedrawWindow();
		SetScrollPos(SB_VERT,nPos);
		break;
	case SB_LINEUP://滚动条向左移动
		if (oPos!=0)
		{
			ScrollWindow(0,1);//dlg窗口向右移动
			//RedrawWindow();
			SetScrollPos(SB_VERT,oPos-1);//滚动条向左移动
		}
		break;
	case SB_LINEDOWN://滚动条向右移动
		if (oPos+thumbwidth<=max)
		{
			ScrollWindow(0,-1);//dlg窗口向左移动
			SetScrollPos(SB_VERT,oPos+1);//滚动条向右移动
		}
		break;
	case SB_PAGEUP:
		if (oPos>=thumbwidth)
		{
			ScrollWindow(0,thumbwidth);//dlg窗口向右移动
			SetScrollPos(SB_VERT,oPos-thumbwidth);//滚动条向左移动
		}else{
			ScrollWindow(0,oPos);//dlg窗口向右移动
			SetScrollPos(SB_VERT,0);//滚动条移到最左端
		}
		break;
	case SB_PAGEDOWN:
		if (oPos+thumbwidth<=max-thumbwidth)
		{
			ScrollWindow(0,-thumbwidth);//dlg窗口向左移动
			SetScrollPos(SB_VERT,oPos+thumbwidth);//滚动条向右移动
		}else{
			ScrollWindow(0,-(max-(oPos+thumbwidth)));//dlg窗口向左移动
			SetScrollPos(SB_VERT,max-thumbwidth);//滚动条移到最右端
		}
		break;
	}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void TabAct::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages

	
}
