#if !defined(AFX_TABCALVER_H__3CE98C57_C78D_4398_B901_B9B588CF5937__INCLUDED_)
#define AFX_TABCALVER_H__3CE98C57_C78D_4398_B901_B9B588CF5937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabCalVer.h : header file
//
#include "Resource.h"
#include "MyListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// TabCalVer dialog
class CELISTestServerDlg;
class TabCalVer : public CDialog
{
// Construction
public:
	TabCalVer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(TabCalVer)
	enum { IDD = IDD_TAB_CALVER };
		// NOTE: the ClassWizard will add data members here
	MyListCtrl m_listctrlCalVer;
	CELISTestServerDlg* m_pELISTestServerDlg;
	//}}AFX_DATA

	void setCElisTestServerDlg(CELISTestServerDlg* dlg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TabCalVer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TabCalVer)
	afx_msg void OnDblclkListCalver(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABCALVER_H__3CE98C57_C78D_4398_B901_B9B588CF5937__INCLUDED_)
