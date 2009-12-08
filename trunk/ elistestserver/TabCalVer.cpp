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
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
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
			sprintf(t, "%s", "Cal/Ver�����ļ�Ŀ¼����Ϊ��!");
			AfxMessageBox(_T(t));
		}else{

			WIN32_FIND_DATA fd;
			HANDLE hFind = FindFirstFile(calverListRootFolder, &fd);
			if ((hFind != INVALID_HANDLE_VALUE) && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
				//Ŀ¼����
				CFileDialog openActDataFileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_FILEMUSTEXIST, "All Files(*.*)|*.*||", this);
				openActDataFileDlg.m_ofn.lpstrInitialDir=calverListRootFolder;
				CString strFilePath;
				if (openActDataFileDlg.DoModal()==IDOK)
				{
					strFilePath=openActDataFileDlg.GetPathName();
					m_listctrlCalVer.SetItemText(rowNo, 8, strFilePath);
				}
			}else{
				char t[50];
				sprintf(t, "%s", "��Ŀ¼�Ѳ�����!");
				AfxMessageBox(_T(t));
			}
		}
		

	}
	*pResult = 0;
}

void TabCalVer::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
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
		ScrollWindow(-(nPos-oPos),0);//�����������ƶ�ʱ,dlg������ʵ���������ƶ�.pos��ʾԭʼλ��,nPos��ʾ��λ��
		//RedrawWindow();
		SetScrollPos(SB_HORZ,nPos);
		break;
	case SB_LINELEFT://�����������ƶ�
		if (oPos!=0)
		{
			ScrollWindow(1,0);//dlg���������ƶ�
			SetScrollPos(SB_HORZ,oPos-1);//�����������ƶ�
		}
		break;
	case SB_LINERIGHT://�����������ƶ�
		if (oPos+thumbwidth<=max)
		{
			ScrollWindow(-1,0);//dlg���������ƶ�
			SetScrollPos(SB_HORZ,oPos+1);//�����������ƶ�
		}
		break;
	case SB_PAGELEFT:
		if (oPos>=thumbwidth)
		{
			ScrollWindow(thumbwidth,0);//dlg���������ƶ�
			SetScrollPos(SB_HORZ,oPos-thumbwidth);//�����������ƶ�
		}else{
			ScrollWindow(oPos,0);//dlg���������ƶ�
			SetScrollPos(SB_HORZ,0);//�������Ƶ������
		}
		break;
	case SB_PAGERIGHT:
		if (oPos+thumbwidth<=max-thumbwidth)
		{
			ScrollWindow(-thumbwidth,0);//dlg���������ƶ�
			SetScrollPos(SB_HORZ,oPos+thumbwidth);//�����������ƶ�
		}else{
			ScrollWindow(-(max-(oPos+thumbwidth)),0);//dlg���������ƶ�
			SetScrollPos(SB_HORZ,max-thumbwidth);//�������Ƶ����Ҷ�
		}
		break;
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void TabCalVer::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
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
		ScrollWindow(0,-(nPos-oPos));//�����������ƶ�ʱ,dlg������ʵ���������ƶ�.pos��ʾԭʼλ��,nPos��ʾ��λ��
		//RedrawWindow();
		SetScrollPos(SB_VERT,nPos);
		break;
	case SB_LINEUP://�����������ƶ�
		if (oPos!=0)
		{
			ScrollWindow(0,1);//dlg���������ƶ�
			//RedrawWindow();
			SetScrollPos(SB_VERT,oPos-1);//�����������ƶ�
		}
		break;
	case SB_LINEDOWN://�����������ƶ�
		if (oPos+thumbwidth<=max)
		{
			ScrollWindow(0,-1);//dlg���������ƶ�
			SetScrollPos(SB_VERT,oPos+1);//�����������ƶ�
		}
		break;
	case SB_PAGEUP:
		if (oPos>=thumbwidth)
		{
			ScrollWindow(0,thumbwidth);//dlg���������ƶ�
			SetScrollPos(SB_VERT,oPos-thumbwidth);//�����������ƶ�
		}else{
			ScrollWindow(0,oPos);//dlg���������ƶ�
			SetScrollPos(SB_VERT,0);//�������Ƶ������
		}
		break;
	case SB_PAGEDOWN:
		if (oPos+thumbwidth<=max-thumbwidth)
		{
			ScrollWindow(0,-thumbwidth);//dlg���������ƶ�
			SetScrollPos(SB_VERT,oPos+thumbwidth);//�����������ƶ�
		}else{
			ScrollWindow(0,-(max-(oPos+thumbwidth)));//dlg���������ƶ�
			SetScrollPos(SB_VERT,max-thumbwidth);//�������Ƶ����Ҷ�
		}
		break;
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}