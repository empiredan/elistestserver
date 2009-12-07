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
	: CDialog(CELISTestServerDlg::IDD, pParent), mq(), fq(), cmdh(), msgs()
{
	//{{AFX_DATA_INIT(CELISTestServerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	this->m_sPort=6050;
	this->m_psConnectSocket=NULL;
	m_rStasus=SOCK_RECEIVE_HEADER;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

//add----------------------------------------------------------------------------------start----
	cmdh.setParentWindow(this);
	msgs.setParentWindow(this);
	acttab = NULL; //091206
//add----------------------------------------------------------------------------------end----
}

CELISTestServerDlg::~CELISTestServerDlg()
{
	//m_sListenSocket.Close();
	//m_psConnectSocket->Close();
	if(m_psConnectSocket) {
		delete m_psConnectSocket;
		m_psConnectSocket=NULL;
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
	//}}AFX_MSG_MAP

//add----------------------------------------------------------------------------------start----
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CELISTestServerDlg::OnBnClickedButton1)
//add----------------------------------------------------------------------------------end----
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

//add----------------------------------------------------------------------------------start----	
	cmdh.start();
	msgs.start();
	ta = 5;
//add----------------------------------------------------------------------------------end----

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
	StopDepthTimer();
	m_psConnectSocket =new MySocket;
	m_psConnectSocket->SetParent(this);
	if(!m_sListenSocket.Accept(*m_psConnectSocket)) {
		char t[50];
		int e = GetLastError();
		sprintf_s(t, "ServerSocket Accepted Error Code:%d", e);
		AfxMessageBox(_T(t), MB_YESNO, 0);
		m_sListenSocket.Close();
	}
	//CreateDepthTimer(DEPTH_TIMER_INTERVAL);
}
void CELISTestServerDlg::OnReceive()
{
	//MasterData_Header* p_msDataHeader;
	//char* buf=NULL;
	m_rbuf=NULL;
	//long l_buf[2];
	//char c_buf[4];
	//char t[200];
	//AfxMessageBox(_T("CAcceptedSocket OnReceive"), MB_YESNO, 0);
	//sprintf(t, "%ld", sizeof(this->m_msDataHeader));
	//AfxMessageBox(_T(t), MB_YESNO, 0);
	
	if (m_rStasus == SOCK_RECEIVE_HEADER) {
		m_rStasus = SOCK_RECEIVE_BODY;
	} else if(m_rStasus == SOCK_RECEIVE_BODY) {
		//buf=new char[m_bodyLen];
		//sprintf(t, "%ld", m_bodyLen);
		//AfxMessageBox(_T(t), MB_YESNO, 0);
		m_rbuf=new char[m_bodyLen+1];//要多出1个byte的余量,否则m_rbuf长度会自动增长
		memset(m_rbuf,0,m_bodyLen+1);
		this->m_len = this->m_psConnectSocket->Receive(m_rbuf, m_bodyLen, 0);
		m_rStasus = SOCK_RECEIVE_HEADER;
	}
	if(m_rbuf){
		delete m_rbuf;
	}

}

void CELISTestServerDlg::OnButtonOk() 
{
	// TODO: Add your control notification handler code here
	this->OnClose();
	
}

void CELISTestServerDlg::OnButtonCancel() 
{
	// TODO: Add your control notification handler code here
	this->OnClose();
	
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

//add----------------------------------------------------------------------------------start----
void CELISTestServerDlg::CreateTimer(UINT_PTR nIDEvent, UINT uElapse) {
	SetTimer(nIDEvent, uElapse, NULL);
}
void CELISTestServerDlg::CreateLogTimer(UINT uElapse) {
	CreateTimer(LOGDATA_TIMER, uElapse);
}
void CELISTestServerDlg::CreateDepthTimer(UINT uElapse) {
	//每当Socket处Accept成功时，都要调用这个函数
	//创建一个Timer定期反馈深度信息给主控机。
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
	char b[100];
	switch(nIDEvent) {
		case LOGDATA_TIMER:
			//从文件中读取相应的log数据，构造ACT表
			//生成FrontData类型对象，将其入SendQueue队列
			//构造ACT表的依据是CommandHandler线程中执行NetCmd_InitServiceTable
			//时解析的参数和相关数据结构，这个数据结构应该专门定义一个类
			//并在本Dialog里保持这个类的一个对象。
			LogDataTimerHandler();
		break;
		case DEPTH_TIMER:
			DepthTimerHandler();
		break;
		default:
			sprintf_s(b, "OnTimer can not find appropriate timer:%d", nIDEvent);
			AfxMessageBox(_T(b));
		break;
	}
}
void CELISTestServerDlg::LogDataTimerHandler() {
	AfxMessageBox(_T("LogDataTimer triggered, implement me!!!"));
}
void CELISTestServerDlg::DepthTimerHandler() {
	//AfxMessageBox(_T("DepthTimer triggered, implement me!!!"));
	CDPMDisplayParameter dpmp;
	CFrontData *fd = new CFrontData();

	//下面这些参数应该从根据实际模拟的进程计算出来
	//填写
	dpmp.ddp.corr_Depth = 10;
	dpmp.ddp.true_Depth = 11;
	dpmp.ddp.speed = 1;
	dpmp.ddp.totalTension = 5;
	dpmp.ddp.differTension = 2;
	dpmp.ddp.time = 1;
	dpmp.ddp.nreserved2 = 0;

	//构造这个数据后将其放入SendQueue即可
	//MessageSender线程会自动从队列中取出
	//FrontData数据并发送之
	fd->SetData(dpmp);
	fq.en(fd);
}

void CELISTestServerDlg::SetACTTable(CActTable *tb) {//091206
	if(acttab != NULL) {
		delete acttab;
		acttab = NULL;
	}
	acttab = tb;
	AfxMessageBox(_T("SetACTTable, implement me!!!, update the CList control on ACT tab page"));
}
//add----------------------------------------------------------------------------------end----
void CELISTestServerDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	/*
	unsigned char buf[100];
	buf[0] = (unsigned char)ta;
	buf[1] = (unsigned char)ta+1;
	ta++;
	CMasterData *d = new CMasterData(buf, 2);
	mq.en(d);
	size_t s = sizeof(long) + sizeof(long) + 3*(sizeof(RTCSubset));
	unsigned char *buf = new unsigned char[s];
	long *t;
	int *ta;
	t = (long*)buf;
	t[0] = 3;
	t[1] = 9999;
	ta = (int*)(buf+sizeof(long)+sizeof(long));
	ta[0] = 1;
	ta[1] = -1;
	ta = (int*)(buf+sizeof(long)+sizeof(long)+sizeof(RTCSubset));
	ta[0] = 2;
	ta[1] = -11;
	CActTable *tb = CActTable::AllocateActTable(buf, s);
	//CActTable *tb = (CActTable*)buf;
	char test[1024];

	sprintf_s(test, "actNum:%ld,DepthInterruptMode:%ld",tb->actNum,tb->nDepthInterruptMode);
	sprintf_s(test, "%s,pSaList[0].actNo:%d,pSaList[0].switchOn:%d",test,tb->pSaList[0].actNo,tb->pSaList[0].switchOn);
	sprintf_s(test, "%s,pSaList[1].actNo:%d,pSaList[1].switchOn:%d",test,tb->pSaList[1].actNo,tb->pSaList[1].switchOn);
	AfxMessageBox(_T(test));

	CreateDepthTimer(DEPTH_TIMER_INTERVAL);
	*/
	int abc[5];
	abc[0] = 2;
	abc[1] = 2;
	abc[2] = 2;
	abc[3] = 2;
	abc[4] = 4;
	char fabc[500];
	int lcm;
	lcm = CUtils::lcm(abc, 5);
	sprintf_s(fabc, "lcm:%d", lcm);
	AfxMessageBox(_T(fabc));
}

