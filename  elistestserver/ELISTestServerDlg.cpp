// ELISTestServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ELISTestServer.h"
#include "ELISTestServerDlg.h"


//#include "stdio.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define   BIF_NEWDIALOGSTYLE    0x0040   
#define   BIF_USENEWUI (BIF_NEWDIALOGSTYLE | BIF_EDITBOX)      
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CELISTestServerDlg dialog

CELISTestServerDlg::CELISTestServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CELISTestServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CELISTestServerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	this->m_sPort=6050;
	this->m_psConnectSocket=NULL;
	m_rStasus=SOCK_RECEIVE_HEADER;
	m_pmasterDataQueue=new MasterDataQueue<CMasterData>;
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	cmdh.setParentWindow(this);
	msgs.setParentWindow(this);
}

CELISTestServerDlg::~CELISTestServerDlg()
{
	//delete this->m_pmasterDataQueue;
	//m_pmasterDataQueue=NULL;
	m_sListenSocket.Close();
	
	if(m_psConnectSocket){
		m_psConnectSocket->Close();
		//m_psConnectSocket->Close();
		delete m_psConnectSocket;
		m_psConnectSocket=NULL;
	}
	if(m_pmasterDataQueue){
		delete m_pmasterDataQueue;
		m_pmasterDataQueue=NULL;
		//char* t="m_pmasterDataQueue deconstructed!";
		//AfxMessageBox(_T(t), MB_YESNO, 0);
	}
	

}

void CELISTestServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CELISTestServerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_MY_TAB, m_tabMyTabCtrl);
	
	
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CELISTestServerDlg, CDialog)
	//{{AFX_MSG_MAP(CELISTestServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Ok, OnButtonOk)
	ON_BN_CLICKED(IDC_Cancel, OnButtonCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_ELISTESTSERVER_TAB, OnSelchangeElistestserverTab)
	ON_BN_CLICKED(IDC_BUTTON_ACT_FOLDER, OnButtonActFolder)

	//ON_WM_TIMER()
	//ON_BN_CLICKED(IDC_BUTTON1, &CELISTestServerDlg::OnBnClickedButton1)
	//}}AFX_MSG_MAP

	

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CELISTestServerDlg message handlers

BOOL CELISTestServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	m_sListenSocket.SetParent(this);

	m_tabMyTabCtrl.InsertItem(0, _T("ACT"));
	m_tabMyTabCtrl.InsertItem(1, _T("Cal/Ver"));
	m_tabMyTabCtrl.Init();
	
	AfxSocketInit(NULL);

	
	if(!m_sListenSocket.Create(this->m_sPort)) {
		AfxMessageBox(_T("Socket Error!"));
		m_sListenSocket.Close();
	}

	if(!m_sListenSocket.Listen()){
		int nErrorCode = m_sListenSocket.GetLastError();
		if (nErrorCode != WSAEWOULDBLOCK) {
			m_sListenSocket.Close(); 
		}
	}
	
	cmdh.start();
	msgs.start();
	ta = 5;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CELISTestServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CELISTestServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CELISTestServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CELISTestServerDlg::OnClose()
{
	
	//m_psConnectSocket->Close();		

}

void CELISTestServerDlg::OnAccept()
{
	
	//this->m_sConnectSocket;
	//AfxMessageBox(_T(this->m_sConnectSocket));
	//AfxMessageBox(_T("Hello!"));
	m_psConnectSocket =new MySocket;
	m_psConnectSocket->SetParent(this);
	if(!m_sListenSocket.Accept(*m_psConnectSocket)){
		char t[50];
		int e = GetLastError();
		sprintf(t, "ServerSocket Accepted Error Code:%d", e);
		AfxMessageBox(_T(t), MB_YESNO, 0);
		m_sListenSocket.Close();
	}
	/*
	else{
		int d=1000;
		char c[4];
		itoa(d,c,10);
		m_psConnectSocket->Send(c,sizeof(d));
	}
	*/

		
}
void CELISTestServerDlg::OnReceive()
{
	//MasterData_Header* p_msDataHeader;
	//char* buf=NULL;
	m_rbuf=NULL;
	//long l_buf[2];
	char c_buf[4];
	char t[200];
	//AfxMessageBox(_T("CAcceptedSocket OnReceive"), MB_YESNO, 0);
	//sprintf(t, "%ld", sizeof(this->m_msDataHeader));
	//AfxMessageBox(_T(t), MB_YESNO, 0);
	
	if (m_rStasus == SOCK_RECEIVE_HEADER) {
		m_rbuf=new BUF_TYPE[SOCK_RECEIVE_HEADER_LEN];
		memset(m_rbuf,0,SOCK_RECEIVE_HEADER_LEN);
		this->m_len = this->m_psConnectSocket->Receive(m_rbuf, SOCK_RECEIVE_HEADER_LEN, 0);
		//����header��ȷ��body����
		if(this->m_len != SOCKET_ERROR && this->m_len >0) {
			memcpy(c_buf,m_rbuf,sizeof(long));
			m_msDataType=atol(c_buf);
			memcpy(c_buf,m_rbuf+sizeof(long),sizeof(long));
			m_msDataLen=atol(c_buf);
			//p_msDataHeader = (MasterData_Header*)this->m_rbuf;
			//this->m_msDataHeader = *p_msDataHeader;
			//buf = (long*)this->m_rbuf;
			//this->m_bodyLen = this->m_msDataHeader.len - SOCK_RECEIVE_HEADER_LEN;
			//this->m_bodyLen = buf[1] - SOCK_RECEIVE_HEADER_LEN;
			m_bodyLen = m_msDataLen - SOCK_RECEIVE_HEADER_LEN;
			sprintf(t, "CAcceptedSocket:CMD:%ld,len:%ld,bodyLen:%ld", m_msDataType, m_msDataLen, m_bodyLen);
			//sprintf(t, "%s", this->m_rbuf);
			AfxMessageBox(_T(t), MB_YESNO, 0);
		}
		m_rStasus = SOCK_RECEIVE_BODY;

	} else if(m_rStasus == SOCK_RECEIVE_BODY) {
		//buf=new char[m_bodyLen];
		//sprintf(t, "%ld", m_bodyLen);
		//AfxMessageBox(_T(t), MB_YESNO, 0);
		m_rbuf=new BUF_TYPE[m_bodyLen+1];//Ҫ���1��byte������,����m_rbuf���Ȼ��Զ�����
		memset(m_rbuf,0,m_bodyLen+1);
		m_len = m_psConnectSocket->Receive(m_rbuf, m_bodyLen, 0);
		
		
		if(m_len != SOCKET_ERROR && m_len > SOCK_RECEIVE_HEADER_LEN && m_len <= m_bodyLen){
			//�ѽ��յ���rbuf����ReceiverQueue��
			CMasterData* p_msData=new CMasterData(m_rbuf, m_len);
			p_msData->msDataHeader.type=m_msDataType;
			p_msData->msDataHeader.len=m_msDataLen;
			//md.buf=new char[m_bodyLen];
			//memcpy(md.buf,m_rbuf,m_bodyLen);
			//md.buflen=m_bodyLen;
			//p_msData->setBuf(m_rbuf);
			//p_msData->setBufLen(m_len);
			
			sprintf(t, "%s", m_rbuf);
			AfxMessageBox(_T(t), MB_YESNO, 0);
			//sprintf(t, "%s", md.buf.GetBuffer(md.buf.GetLength()));
			//AfxMessageBox(_T(t), MB_YESNO, 0);
			sprintf(t, "%s", p_msData->buf);
			AfxMessageBox(_T(t), MB_YESNO, 0);
			sprintf(t, "%ld", p_msData->buflen);
			AfxMessageBox(_T(t), MB_YESNO, 0);

			m_pmasterDataQueue->enQueue(p_msData);
			//POSITION p=m_pmasterDataQueue->Dataqueue.GetHeadPosition();
			
			sprintf(t, "%s", m_pmasterDataQueue->dataQueue.GetHead()->buf);
			AfxMessageBox(_T(t), MB_YESNO, 0);

			
			delete p_msData;
			
		}
		m_rStasus = SOCK_RECEIVE_HEADER;
	}
	/*if(buf){
		delete buf;
	}*/
	/*
	if(m_rbuf){
		delete m_rbuf;
	}
	*/

}

void CELISTestServerDlg::OnButtonOk() 
{
	// TODO: Add your control notification handler code here
	/*m_sListenSocket.Close();
	if(m_psConnectSocket){
		m_psConnectSocket->Close();
		delete m_psConnectSocket;
	}
	this->DestroyWindow();
	*/
	DestroyWindow();
	
}

void CELISTestServerDlg::OnButtonCancel() 
{
	// TODO: Add your control notification handler code here
	/*m_sListenSocket.Close();
	if(m_psConnectSocket){
		m_psConnectSocket->Close();
		delete m_psConnectSocket;
	}
	this->DestroyWindow();
	*/
	DestroyWindow();
	
}



void CELISTestServerDlg::CreateTimer(UINT_PTR nIDEvent, UINT uElapse) {
	SetTimer(nIDEvent, uElapse, NULL);
}
void CELISTestServerDlg::CreateLogTimer(UINT uElapse) {
	CreateTimer(LOGDATA_TIMER, uElapse);
}
void CELISTestServerDlg::CreateDepthTimer(UINT uElapse) {
	CreateTimer(DEPTH_TIMER, uElapse);
}
void CELISTestServerDlg::StopTimer(UINT_PTR nIDEvent) {
	KillTimer(nIDEvent);
}
void CELISTestServerDlg::StopLogTimer() {
	StopTimer(LOGDATA_TIMER);
}
void CELISTestServerDlg::StopDepthTimer() {
	StopTimer(DEPTH_TIMER);
}

void CELISTestServerDlg::OnTimer(UINT nIDEvent) {
	switch(nIDEvent) {
	case LOGDATA_TIMER:
		//���ļ��ж�ȡ��Ӧ��log���ݣ�����ACT��
		//����FrontData���Ͷ��󣬽�����SendQueue����
		//����ACT����������CommandHandler�߳���ִ��NetCmd_InitServiceTable
		//ʱ�����Ĳ�����������ݽṹ��������ݽṹӦ��ר�Ŷ���һ����
		//���ڱ�Dialog�ﱣ��������һ������
		LogDataTimerHandler();
		break;
	case DEPTH_TIMER:
		DepthTimerHandler();
	default:
		AfxMessageBox(_T("OnTimer can not find appropriate timer type"));
		break;
	}
}
void CELISTestServerDlg::LogDataTimerHandler() {
	AfxMessageBox(_T("LogDataTimer triggered, implement me!!!"));
}
void CELISTestServerDlg::DepthTimerHandler() {
	AfxMessageBox(_T("DepthTimer triggered, implement me!!!"));
}

void CELISTestServerDlg::SetACTTable(CActTable *tb) {//091206
	if(acttab != NULL) {
		delete acttab;
		acttab = NULL;
	}
	acttab = tb;
	AfxMessageBox(_T("SetACTTable, implement me!!!, update the CList control on ACT tab page"));
}



void CELISTestServerDlg::OnSelchangeElistestserverTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
	switch(m_tabMyTabCtrl.GetCurSel()){

	case 0:
		m_tabMyTabCtrl.m_dlgAct->ShowWindow(SW_SHOW);
		m_tabMyTabCtrl.m_dlgCalVer->ShowWindow(SW_HIDE);
		break;
	case 1:
		m_tabMyTabCtrl.m_dlgAct->ShowWindow(SW_HIDE);
		m_tabMyTabCtrl.m_dlgCalVer->ShowWindow(SW_SHOW);
		break;
	default:
		break;

	}
}


void CELISTestServerDlg::OnButtonActFolder() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH]; //���ѡ���Ŀ¼·��
    CString str;
    ZeroMemory(szPath, sizeof(szPath)); 
    BROWSEINFO bi;
    bi.hwndOwner = m_hWnd;
    bi.pidlRoot = NULL;
    bi.pszDisplayName = szPath;
    bi.lpszTitle = "��ѡ��ACT�����ļ���Ŀ¼:";
    bi.ulFlags = BIF_USENEWUI;//0
    bi.lpfn = NULL;
    bi.lParam = 0;
    bi.iImage = 0;
	
    //����ѡ��Ŀ¼�Ի���
    LPITEMIDLIST lp = SHBrowseForFolder(&bi);
    if( lp && SHGetPathFromIDList(lp, szPath) ) {
        str.Format("ѡ���Ŀ¼Ϊ %s",  szPath);
        AfxMessageBox(_T(str));
    } else {
        AfxMessageBox(_T("��Ч��Ŀ¼��������ѡ��"));
    }

	
}