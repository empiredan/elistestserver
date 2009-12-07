// ELISTestServerDlg.h : header file
//

#if !defined(AFX_ELISTESTSERVERDLG_H__6AFE4040_494B_4411_87B4_38BD588A2CAA__INCLUDED_)
#define AFX_ELISTESTSERVERDLG_H__6AFE4040_494B_4411_87B4_38BD588A2CAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <windows.h>
//#include "MasterHeader.h"
#include "MyTabCtrl.h"
#include "MySocket.h"
#include "Data.h"
#include "Queue.h"
#include "MessageSender.h"
#include "CommandHandler.h"

#include "TimerDef.h"

#include "ActTable.h"
//#include "DealThread.h"
//#include <deque>
//using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CELISTestServerDlg dialog

class CELISTestServerDlg : public CDialog
{
// Construction
public:
	CELISTestServerDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CELISTestServerDlg();

	UINT m_sPort;
	MySocket m_sListenSocket;
	MySocket* m_psConnectSocket;
	int m_rStasus;

	long m_len;
	long m_bodyLen;
	long m_msDataType;
	long m_msDataLen;
	BUF_TYPE* m_rbuf;

	MasterDataQueue<CMasterData>* m_pmasterDataQueue;
	//MasterDataQueue<CMasterData> mq;
	FrontDataQueue<CFrontData> fq;
	CCommandHandler cmdh;
	CMessageSender msgs;
	CActTable *acttab;
	unsigned char ta;

	void OnReceive();
	void OnAccept();
	void OnClose();

	MasterDataQueue<CMasterData>* getMasterDataQueue() {
		return m_pmasterDataQueue;
	}
	void CreateTimer(UINT_PTR nIDEvent, UINT uElapse);
	void CreateLogTimer(UINT uElapse);
	void CreateDepthTimer(UINT uElapse);
	void StopTimer(UINT_PTR nIDEvent);
	void StopLogTimer();
	void StopDepthTimer();
	FrontDataQueue<CFrontData>* getFrontDataQueue() {
		return &fq;
	}
	
	void DepthTimerHandler();
	void LogDataTimerHandler();
	void SetACTTable(CActTable *tb);

	//DWORD WINAPI WriteCmdRecvQueFunc(LPVOID lpParameter);

// Dialog Data
	//{{AFX_DATA(CELISTestServerDlg)
	enum { IDD = IDD_ELISTESTSERVER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	MyTabCtrl m_tabMyTabCtrl;
	CButton* m_fileButton;
	
	
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CELISTestServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CELISTestServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOk();
	afx_msg void OnButtonCancel();
	afx_msg void OnSelchangeElistestserverTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonActFolder();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELISTESTSERVERDLG_H__6AFE4040_494B_4411_87B4_38BD588A2CAA__INCLUDED_)