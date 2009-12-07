#if !defined(AFX_TABACT_H__65293594_27EC_4430_B0A7_42474F117A7D__INCLUDED_)
#define AFX_TABACT_H__65293594_27EC_4430_B0A7_42474F117A7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabAct.h : header file
//
#include "MyListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// TabAct dialog

class TabAct : public CDialog
{
// Construction
public:
	TabAct(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(TabAct)
	enum { IDD = IDD_TAB_ACT };
		// NOTE: the ClassWizard will add data members here
	MyListCtrl m_listctrlAct;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TabAct)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TabAct)
	//afx_msg void OnItemdblclickListAct(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListAct(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABACT_H__65293594_27EC_4430_B0A7_42474F117A7D__INCLUDED_)
