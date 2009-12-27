// ELISTestServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ELISTestServer.h"
#include "ELISTestServerDlg.h"
#include "errno.h"
#include "commands.h"
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
	: CDialog(CELISTestServerDlg::IDD, pParent),
	log(".\\commandlist.txt", CFile::modeCreate|CFile::modeWrite|CFile::shareDenyNone)
{
	//{{AFX_DATA_INIT(CELISTestServerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	this->m_sPort=0;
	this->m_psConnectSocket=NULL;
	m_rStatus=SOCK_RECEIVE_HEADER;
	m_pmasterDataQueue=new MasterDataQueue<CMasterData>;
	m_rbuf = new BUF_TYPE[DEFAULT_BUF_LEN];
	pBuf = m_rbuf;
	m_rbuflen = DEFAULT_BUF_LEN;
	rremain = SOCK_RECEIVE_HEADER_LEN;
	received = 0;

	acttab = NULL;
	calibpara = NULL;

	wms = new CWorkModeSetter();
	wms->changeDepth = FALSE;
	wms->changeTime = FALSE;
	wms->returnSubsetData = FALSE;
	wms->depthSign = 0;
	
	calibsubset=NULL;

	m_dataFileBufSize=5*1024*1024;

	//m_actDataFilePathChanged=FALSE;
	//m_actTableChanged=FALSE;

	//m_calverDataFilePathChanged=TRUE;

	m_subsetAssister=new CSubsetDataAssister;
	m_dataFileBuf=new CDataFileBuf(this);
	m_subsetAssister->setDataFileBuf(m_dataFileBuf);

	m_measure=0;
	m_speed=0.5f;
	//m_trueDepth=500;
	
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	cmdh.setParentWindow(this);
	msgs.setParentWindow(this);
}

CELISTestServerDlg::~CELISTestServerDlg()
{
	//delete this->m_pmasterDataQueue;
	//m_pmasterDataQueue=NULL;

	CString dataConfigFileName = "dataconfig.ini";//D:\\vc6\\MyProjects\\elis\\ELISTestServer6.3.2
	char currentDirectoryChar[1024];
	GetCurrentDirectory(1024, currentDirectoryChar);
	CString dataConfigFilePath = currentDirectoryChar;
	dataConfigFilePath+= "\\";
	dataConfigFilePath+= dataConfigFileName;
	
	//_TCHAR confBuf[1024];
	CString confStr;
	
	WritePrivateProfileString("Parameter Setting", "TrueDepth", m_trueDepthStr, dataConfigFilePath);
	
	
	WritePrivateProfileString("Parameter Setting", "Speed", m_speedStr, dataConfigFilePath);
	
	confStr.Format("%d", m_measure);
	WritePrivateProfileString("Parameter Setting", "Measure", confStr, dataConfigFilePath);
	
	confStr.Format("%d", m_sPort);
	WritePrivateProfileString("Net Connection", "Port", confStr, dataConfigFilePath);
	
	WritePrivateProfileString("Data File", "ACTRoot", m_actListRootFolder, dataConfigFilePath);
	
	WritePrivateProfileString("Data File", "CALVERRoot", m_calverListRootFolder, dataConfigFilePath);
	
	confStr.Format("%ld", m_dataFileBufSize/(1024*1024));
	WritePrivateProfileString("Data File", "BufSize", confStr, dataConfigFilePath);


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
	if (m_subsetAssister)
	{
		delete m_subsetAssister;
	}
	
	if (m_dataFileBuf)
	{
		delete m_dataFileBuf;
	} 
	if(m_rbuf != NULL) {
		delete [] m_rbuf;
	}
	log.Close();
}

void CELISTestServerDlg::SetCurrentWorkState()
{
	
	switch (wms->mode)
	{
	case RtcSYS_DEACTIVE_CMD:
		m_currentWorkStateStr="RtcSYS_DEACTIVE_CMD";
		break;
	case RtcSYS_IDLE_CMD:
		m_currentWorkStateStr="RtcSYS_IDLE_CMD";
		break;
	case RtcSYS_STANDBY_CMD:
		m_currentWorkStateStr="RtcSYS_STANDBY_CMD";
		break;
	case RtcSYS_RECSTART_CMD:
		m_currentWorkStateStr="RtcSYS_RECSTART_CMD";
		break;
	case RtcSYS_RECSTOP_CMD:
		m_currentWorkStateStr="RtcSYS_RECSTOP_CMD";
		break;
	case RtcSYS_CALIBSTART_CMD:
		m_currentWorkStateStr="RtcSYS_CALIBSTART_CMD";
		break;
	default:
		CString ex; 
		ex.Format("Current Work State %lx not identified!\n",wms->mode);

		log.Write(ex.GetBuffer(ex.GetLength()),ex.GetLength());
		break;
	}
	
	GetDlgItem(IDC_STATIC_MODE_VALUE)->SetWindowText(m_currentWorkStateStr);
	//UpdateData(FALSE);
	
}
void CELISTestServerDlg::SetDirection()
{
	switch(wms->direction) {
	case 0:
		m_directionStr="UP";
		break;
	case 1:
		m_directionStr="DOWN";
		break;
	default:
		/*
		AfxMessageBox("方向数据错误!");
		*/
		break;
	}
	GetDlgItem(IDC_STATIC_DIRECTION_VALUE)->SetWindowText(m_directionStr);
	//UpdateData(FALSE);
}
UINT CELISTestServerDlg::GetCurrentTestTime()
{
	//UpdateData(TRUE);
	GetDlgItem(IDC_STATIC_CURRENT_TIME_VALUE)->GetWindowText(m_currentTimeStr);
	float currentTime;
	currentTime=atof(m_currentTimeStr);
	if (errno==ERANGE||errno==EINVAL)
	{
		currentTime=5.0;
		
	} 
	
	return (UINT)currentTime*1000;
}
void CELISTestServerDlg::SetCurrentTestTime(UINT ct)
{
	m_currentTimeStr.Format("%10.2f",ct/1000.0);
	GetDlgItem(IDC_STATIC_CURRENT_TIME_VALUE)->SetWindowText(m_currentTimeStr);
	//UpdateData(FALSE);

}
float CELISTestServerDlg::GetCurrentDepth()
{
	//UpdateData(TRUE);
	GetDlgItem(IDC_STATIC_CURRENT_DEPTH_SHOW_VALUE)->GetWindowText(m_currentDepthStr);
	float currentDepth;
	currentDepth=atof(m_currentDepthStr);
	if (errno==ERANGE||errno==EINVAL)
	{
		currentDepth=5000;
		
	} 
	
	return currentDepth;
}
void CELISTestServerDlg::SetCurrentDepth(float cp)
{
	m_currentDepthStr.Format("%f",cp);
	//UpdateData(FALSE);
	GetDlgItem(IDC_STATIC_CURRENT_DEPTH_SHOW_VALUE)->SetWindowText(m_currentDepthStr);
	if (m_measure)
	{
		GetDlgItem(IDC_STATIC_CURRENT_DEPTH_SHOW_UNIT)->SetWindowText("m");
	} 
	else
	{
		GetDlgItem(IDC_STATIC_CURRENT_DEPTH_SHOW_UNIT)->SetWindowText("feet");
	}
	
}
void CELISTestServerDlg::EnableStartLog(BOOL enableButton)
{
	GetDlgItem(IDC_BUTTON_START_LOG)->EnableWindow(enableButton);

}

void CELISTestServerDlg::EnableCreateLog(BOOL enableButton)
{
	GetDlgItem(IDC_BUTTON_CREATE_LOG)->EnableWindow(enableButton);
	
}

void CELISTestServerDlg::EnableStopLog(BOOL enableButton)
{
	GetDlgItem(IDC_BUTTON_STOP_LOG)->EnableWindow(enableButton);
	
}

void CELISTestServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CELISTestServerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_MY_TAB, m_tabMyTabCtrl);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_sPort);
	DDX_Text(pDX, IDC_EDIT_ACT_FOLDER, m_actListRootFolder);
	DDX_Text(pDX, IDC_EDIT_CALVER_FOLDER, m_calverListRootFolder);
	DDX_Text(pDX, IDC_STATIC_MODE_VALUE, m_currentWorkStateStr);
	DDX_Text(pDX, IDC_STATIC_DIRECTION_VALUE, m_directionStr);
	DDX_Text(pDX, IDC_STATIC_CURRENT_DEPTH_SHOW_VALUE, m_currentDepthStr);
	DDX_Text(pDX, IDC_STATIC_CURRENT_TIME_VALUE, m_currentTimeStr);
	DDX_Text(pDX, IDC_EDIT_SPEED, m_speedStr);
	DDX_Text(pDX, IDC_EDIT_TRUE_DEPTH, m_trueDepthStr);
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
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SERVER_PORT, OnButtonServerPort)
	ON_BN_CLICKED(IDC_BUTTON_CALVER_FOLDER, OnButtonCalverFolder)
	ON_BN_CLICKED(IDC_BUTTON_DATA_BUFFER_SIZE, OnButtonDataBufferSize)
	ON_BN_CLICKED(IDC_BUTTON_SPEED, OnButtonSpeed)
	ON_BN_CLICKED(IDC_BUTTON_START_LOG, OnButtonStartLog)
	ON_BN_CLICKED(IDC_BUTTON_TRUE_DEPTH, OnButtonTrueDepth)
	ON_BN_CLICKED(IDC_RADIO_IMPERIAL, OnRadioImperial)
	ON_BN_CLICKED(IDC_RADIO_METRIC, OnRadioMetric)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_LOG, OnButtonCreateLog)
	ON_BN_CLICKED(IDC_BUTTON_STOP_LOG, OnButtonStopLog)
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
	
	//m_tabMyTabCtrl.m_dlgAct->SetParent(this);
	//m_tabMyTabCtrl.m_dlgCalVer->SetParent(this);

	m_tabMyTabCtrl.m_dlgAct->setCElisTestServerDlg(this);
	m_tabMyTabCtrl.m_dlgCalVer->setCElisTestServerDlg(this);

	//OnButtonDataBufferSize();

	//GetDlgItem(IDC_EDIT_TRUE_DEPTH)->SetWindowText("50000");
	//GetDlgItem(IDC_EDIT_SPEED)->SetWindowText("0.05");
	//GetDlgItem(IDC_EDIT_SERVER_PORT)->SetWindowText("6050");

	CString dataConfigFileName = "dataconfig.ini";//D:\\vc6\\MyProjects\\elis\\ELISTestServer6.3.2
	char currentDirectoryChar[1024];
	GetCurrentDirectory(1024, currentDirectoryChar);
	CString dataConfigFilePath = currentDirectoryChar;
	dataConfigFilePath+= "\\";
	dataConfigFilePath+= dataConfigFileName;

	LPCTSTR lpDefault;
	INT nDefault;
	_TCHAR confBuf[1024];

	GetPrivateProfileString("Parameter Setting", "TrueDepth", lpDefault, confBuf, 1024, dataConfigFilePath);
	m_trueDepthStr = confBuf;

	GetPrivateProfileString("Parameter Setting", "Speed", lpDefault, confBuf, 1024, dataConfigFilePath);
	m_speedStr = confBuf;

	m_measure = GetPrivateProfileInt("Parameter Setting", "Measure", nDefault, dataConfigFilePath);

	m_sPort = GetPrivateProfileInt("Net Connection", "Port", nDefault, dataConfigFilePath);

	GetPrivateProfileString("Data File", "ACTRoot", lpDefault, confBuf, 1024, dataConfigFilePath);
	m_actListRootFolder = confBuf;

	GetPrivateProfileString("Data File", "CALVERRoot", lpDefault, confBuf, 1024, dataConfigFilePath);
	m_calverListRootFolder = confBuf;

	m_dataFileBufSize = GetPrivateProfileInt("Data File", "BufSize", nDefault, dataConfigFilePath);
/*
	typedef struct{
		CString trueDepth;
		CString speed;
		int m_measure;
	}ParamConf;

	typedef struct{
		UINT port;
	}NetConf;

	typedef struct{
		CString actRoot;
		CString calverRoot;
		ULONG bufSize;
	}DataFileConf;

	_TCHAR* paramConfBuf = new _TCHAR[sizeof(ParamConf)];
	_TCHAR* netConfBuf = new _TCHAR[sizeof(NetConf)];
	_TCHAR* dataFileConfBuf = new _TCHAR[sizeof(DataFileConf)];

	DWORD readSize = GetPrivateProfileSection("Parameter Setting", paramConfBuf, sizeof(ParamConf), dataConfigFilePath);
	readSize = GetPrivateProfileSection("Net Connection", netConfBuf, sizeof(NetConf), dataConfigFilePath);
	GetPrivateProfileSection("Data File", dataFileConfBuf, sizeof(DataFileConf), dataConfigFilePath);

	ParamConf* paramConf = (ParamConf*)paramConfBuf;
	NetConf* netConf = (NetConf*)netConfBuf;
	DataFileConf* dataFileConf = (DataFileConf*)dataFileConfBuf;

	m_trueDepthStr = paramConf->trueDepth;
	m_speedStr = paramConf->speed;
	m_measure = paramConf->m_measure;
	m_sPort = netConf->port;
	m_actListRootFolder = dataFileConf->actRoot;
	m_calverListRootFolder = dataFileConf->calverRoot;
	m_dataFileBufSize = dataFileConf->bufSize;
*/
	/*
	m_sPort=6050;
	m_speedStr="100";
	m_trueDepthStr="5000";
	*/
	if (m_measure)
	{
		m_currentDepthDU = atof(m_trueDepthStr)*METRIC_DU;
		((CButton*)GetDlgItem(IDC_RADIO_METRIC))->SetCheck(TRUE);
	} 
	else
	{
		m_currentDepthDU = atof(m_trueDepthStr)*IMPERIAL_DU;
		((CButton*)GetDlgItem(IDC_RADIO_IMPERIAL))->SetCheck(TRUE);
	}

	CString dataFileBufSizeStr;
	dataFileBufSizeStr.Format("%ld", m_dataFileBufSize);
	m_dataFileBufSize*= 1024*1024;
	GetDlgItem(IDC_EDIT_DATA_BUFFER_SIZE)->SetWindowText(dataFileBufSizeStr);
	//GetDlgItem(IDC_EDIT_DATA_BUFFER_SIZE)->SetWindowText("5");
	//((CButton*)GetDlgItem(IDC_RADIO_IMPERIAL))->SetCheck(TRUE);
	
	//m_actListRootFolder="D:\\LogData\\E130~MSF71_file1";
	//m_calverListRootFolder="D:\\LogData\\刻度数据";

	cmdh.start();
	msgs.start();
	ta = 5;

	//acttab->setParentDlg(this);

	UpdateData(FALSE);

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
	} else {
		CString clientIP;
		UINT clientPort;

		m_psConnectSocket->GetPeerName(clientIP,clientPort);
		
		CString strClientPort;
		strClientPort.Format("%d",clientPort);

		GetDlgItem(IDC_STATIC_CLIENT_IP_PORT_VALUE)->SetWindowText(_T(clientIP+":"+strClientPort));

		//Accept成功，启动DepthTimer进行定期传输
		//深度数据
		StopDepthTimer();
		CreateDepthTimer(DEPTH_TIMER_INTERVAL);
	}
}
void CELISTestServerDlg::OnReceive()
{
	//char t[200];
	//AfxMessageBox(_T("CAcceptedSocket OnReceive"), MB_YESNO, 0);
	//sprintf(t, "%ld", sizeof(this->m_msDataHeader));
	ULONG *t;
	ULONG len;
	ULONG cmdType;
	//int *t;
	//int len;
	

	if (m_rStatus == SOCK_RECEIVE_HEADER) {
		len = m_psConnectSocket->Receive(pBuf, rremain, 0);
		//解析header，确定body长度
		if(len != SOCKET_ERROR && len > 0) {
			received += len;
			if(received == SOCK_RECEIVE_HEADER_LEN) {
				t = (ULONG*)m_rbuf;
				cmdType = ntohl(t[0]);
				//t = (int*)m_rbuf;	
				m_msDataLen = ntohl(t[1]);
				m_bodyLen = m_msDataLen - SOCK_RECEIVE_HEADER_LEN;
			
				if(m_bodyLen <= 0) {
					AfxMessageBox(_T("OnReceive Strange Err: message body have 0 length"));
				} else {
					if((m_bodyLen + SOCK_RECEIVE_HEADER_LEN) > m_rbuflen) {
						BUF_TYPE *bft;
						bft = new BUF_TYPE[m_bodyLen + SOCK_RECEIVE_HEADER_LEN];

						ASSERT(bft != NULL);
						
						memcpy(bft, m_rbuf, SOCK_RECEIVE_HEADER_LEN);
						delete []m_rbuf;
						m_rbuf = bft;
						m_rbuflen = m_bodyLen + SOCK_RECEIVE_HEADER_LEN;
						received = 0;
						pBuf = m_rbuf;
						rremain = m_bodyLen;
					}
					m_rStatus = SOCK_RECEIVE_BODY;
					rremain = m_bodyLen;
					received = 0;
					pBuf = m_rbuf + SOCK_RECEIVE_HEADER_LEN;
				}
			} else {
				rremain = SOCK_RECEIVE_HEADER_LEN - len;
				pBuf = pBuf + len;
			}
		} 
	} else if(m_rStatus == SOCK_RECEIVE_BODY) {
		len = m_psConnectSocket->Receive(pBuf, rremain, 0);
		
		if(len != SOCKET_ERROR && len > 0) {
			received += len;
			if(received == m_bodyLen) {
				//把接收到的rbuf填入ReceiverQueue中
				CMasterData* p_msData=new CMasterData();
				p_msData->setData(m_rbuf, m_bodyLen + SOCK_RECEIVE_HEADER_LEN);
				m_pmasterDataQueue->enQueue(p_msData);
				
				m_rStatus = SOCK_RECEIVE_HEADER;
				pBuf = m_rbuf;
				rremain = SOCK_RECEIVE_HEADER_LEN;
				received = 0;
			} else if(received < m_bodyLen) {
				rremain = m_bodyLen - received;
				pBuf += len;
			} else {
				AfxMessageBox(_T("Recceive Body should no occur"));
			}
		} else {
			if(len <= 0) {
				AfxMessageBox(_T("OnReceive body length received <=0"));
			} else {
				AfxMessageBox(_T("OnReceive Socket error"));
			}
		}
	} else {
		AfxMessageBox(_T("OnReceive wrong status"));
		//m_rStatus = SOCK_RECEIVE_HEADER;
	}
	
	//m_psConnectSocket->OnReceive(nErrorCode);
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
	msgs.finish = TRUE;
	cmdh.finish = TRUE;

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
	msgs.finish = TRUE;
	cmdh.finish = TRUE;

	DestroyWindow();
}


void CELISTestServerDlg::HandleWorkStateChange() {
	//
	char loginfo[1024];
	switch(wms->mode) {
	case RtcSYS_IDLE_CMD:
		wms->changeDepth = FALSE;
		wms->changeTime = FALSE;
		wms->returnSubsetData = FALSE;
		//EnableStartLog(FALSE);
		//EnableCreateLog(FALSE);
		break;
	case RtcSYS_STANDBY_CMD:
		ASSERT(acttab != NULL);

		if(wms->direction == 0) {
			wms->depthSign = -1;
		} else if(wms->direction = 1) {
			wms->depthSign = 1;
		} else {//-1, 
			//wms->depthSign = 0;
		}
		wms->changeDepth = FALSE;
		wms->changeTime = TRUE;
		wms->returnSubsetData = TRUE;
		break;
	case RtcSYS_RECSTART_CMD:
		ASSERT(acttab != NULL);
		
		if(wms->direction == 0) {
			wms->depthSign = -1;
		} else if(wms->direction = 1) {
			wms->depthSign = 1;
		} else {//-1, 
			//wms->depthSign = 0;
			//should not here
		}
		wms->changeDepth = TRUE;
		wms->changeTime = TRUE;
		wms->returnSubsetData = TRUE;
		break;
	case RtcSYS_CALIBSTART_CMD:
		//重新设置DataFileBuf的缓冲区，将对应的文件
		//读入到相应的位置上，后来的刻度命令会从这个
		//位置读取刻度的SubsetData
		//离开这个状态进入
		StopLogTimer();
		break;
	case RtcSYS_TRAINSTART_CMD:
		StopLogTimer();
		break;
	default:
		StopLogTimer();//????
		sprintf(loginfo, "handleWorkStateChange, Un handled Workstate, StopLogTimer???\n");
		log.Write(loginfo, strlen(loginfo));
		break;
	}

/**
 * CreateLogTimer的条件：
 * （1）设置服务表后
 * （2）从CalVer状态结束后返回Standby time状态
 * （3）点击CreateLog（开始log）按钮
 * （4）
 * （5）
 */
/**
 * StopLogTimer的条件：
 * （1）系统Deactivate时，即处于NA状态
 * （2）系统从Idle，Standby time进入CalVer状态
 * （3）系统进入除time，depth，idle之外的其他状态
 * （4）
 * （5）
 */

	if(wms->old2Mode == NET_CMD_NA && wms->oldMode == NET_CMD_NA && wms->mode == RtcSYS_STANDBY_CMD) {
		//刚刚激活服务表。
		//重新生成缓冲区后重新构造DataFileBuf缓冲区并加载文件
		acttab->buildSubsetDataAssister(m_subsetAssister, m_speed, wms->mode, m_measure);
		
		m_dataFileBuf->create(m_dataFileBufSize, acttab->actNum);
		m_dataFileBuf->layout();
		m_dataFileBuf->fillWithDataFile();
		EnableCreateLog(TRUE);
		//
	} else if((wms->old2Mode == RtcSYS_RECSTART_CMD && wms->oldMode == RtcSYS_IDLE_CMD && wms->mode == RtcSYS_STANDBY_CMD) ||
		(wms->old2Mode == RtcSYS_STANDBY_CMD && wms->oldMode == RtcSYS_IDLE_CMD && wms->mode == RtcSYS_RECSTART_CMD) ||
		(wms->old3Mode == RtcSYS_STANDBY_CMD && wms->oldMode == RtcSYS_IDLE_CMD && wms->oldMode == RtcSYS_IDLE_CMD && wms->mode == RtcSYS_RECSTART_CMD) ||
		(wms->old3Mode == RtcSYS_RECSTART_CMD && wms->oldMode == RtcSYS_IDLE_CMD && wms->oldMode == RtcSYS_IDLE_CMD && wms->mode == RtcSYS_STANDBY_CMD)) {
		//经过了深度到时间或时间到深度模式的切换
		//重新构造DataFileBuf缓冲区并重新加载文件
		acttab->reBuildSubsetDataAssister(m_subsetAssister, m_speed, wms->mode, m_measure);
		m_subsetAssister->Save(log);

		//(1)stop log timer
		StopLogTimer();
		//(2)layout, fill
		m_subsetAssister->dataFileBuf->layout();
		m_subsetAssister->dataFileBuf->fillWithDataFile();
		//(3)CreateLogTimer
		CreateLogTimer(m_subsetAssister->assist.logTimerElapse);
		//
	} else if(wms->oldMode == RtcSYS_IDLE_CMD && wms->mode == RtcSYS_CALIBSTART_CMD) {
		//从Idle或Standby time模式进入CalVer模式
		//要在DataFileBuf中构造CalVer文件的缓冲区

		//Stop log timer
		StopLogTimer();
		//fill(i)===>用calver的数据文件
		
		//
	} else if( (wms->old2Mode == RtcSYS_CALIBSTART_CMD && wms->oldMode == RtcSYS_IDLE_CMD && wms->mode == RtcSYS_STANDBY_CMD) ||
		(wms->old2Mode == RtcSYS_CALIBSTART_CMD && wms->oldMode == RtcSYS_IDLE_CMD && wms->oldMode == RtcSYS_IDLE_CMD && wms->mode == RtcSYS_STANDBY_CMD) ) {
		//从CalVer状态退出时，自动转换到Idle再到Standby time
		//重新构造DataFileBuf缓冲区并重新加载文件
		//
		//Stop log timer原则上不需要再stop，因为在进入Calver时已经stop过了，见上
		//fill(i)==>用ACT的数据文件
		UINT i = m_subsetAssister->dataFileBuf->getCalVerBufBlockIndex();
		m_subsetAssister->dataFileBuf->resetCurrentPointer(i);
		fillDataFileBufWithAct();
		//
	}

	sprintf(loginfo, "Old3Mode:0x%lx,Old2Mode:0x%lx,OldMode:0x%lx,Mode:0x%lx;", wms->old3Mode, wms->old2Mode, wms->oldMode, wms->mode);
	sprintf(loginfo, "%sOld3Dir:%d,Old2Dir:%d,OldDir:%d,Dir:%d;", loginfo, wms->old3Direction, wms->old2Direction, wms->oldDirection, wms->direction);
	sprintf(loginfo, "%schangeDepth:%d,changeTime:%d, ReturnSubsetData:%d,depthSign:%d\n", loginfo, wms->changeDepth, wms->changeTime, wms->returnSubsetData, wms->depthSign);
	log.Write(loginfo, strlen(loginfo));
	log.Flush();
}

void CELISTestServerDlg::fillDataFileBufWithCalVer()
{
	

	MyListCtrl& calverListCtrl=m_tabMyTabCtrl.m_dlgCalVer->m_listctrlCalVer;
	CString filePath = calverListCtrl.GetItemText(0, 3);
	UINT i = m_subsetAssister->dataFileBuf->getCalVerBufBlockIndex();
	m_subsetAssister->dataFileBuf->fillWithDataFile(i, filePath);
	
	
}

void CELISTestServerDlg::fillDataFileBufWithAct()
{
	
	UINT i = m_subsetAssister->dataFileBuf->getCalVerBufBlockIndex();
	m_subsetAssister->dataFileBuf->fillWithDataFile(i);
	
}

CCalibSubset* CELISTestServerDlg::getCalibSubset()
{
	CCalibSubset *rtn = NULL;
	rtn = new CCalibSubset();
	//
	rtn->setCommandHeader(calibpara, m_subsetAssister);
	rtn->setSubsetData(calibpara, m_subsetAssister);
	getFrontDataQueue()->enQueue(rtn);
	return calibsubset;
}

void CELISTestServerDlg::CreateTimer(UINT_PTR nIDEvent, UINT uElapse) {
	SetTimer(nIDEvent, uElapse, NULL);
}
/**
 * CreateLogTimer的条件：
 * （1）设置服务表后
 * （2）从CalVer状态结束后返回Standby time状态
 * （3）点击CreateLog（开始log）按钮
 * （4）
 * （5）
 */
void CELISTestServerDlg::CreateLogTimer(UINT uElapse) {
	CreateTimer(LOGDATA_TIMER, uElapse);
	SetCurrentTestTime(0);
}
void CELISTestServerDlg::CreateDepthTimer(UINT uElapse) {
	CreateTimer(DEPTH_TIMER, uElapse);
}
void CELISTestServerDlg::StopTimer(UINT_PTR nIDEvent) {
	KillTimer(nIDEvent);
}
/**
 * StopLogTimer的条件：
 * （1）系统Deactivate时，即处于NA状态
 * （2）系统从Idle，Standby time进入CalVer状态
 * （3）系统进入除time，depth，idle之外的其他状态
 * （4）
 * （5）
 */
void CELISTestServerDlg::StopLogTimer() {
	StopTimer(LOGDATA_TIMER);
}
void CELISTestServerDlg::StopDepthTimer() {
	StopTimer(DEPTH_TIMER);
}



void CELISTestServerDlg::OnTimer(UINT nIDEvent) {
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
		AfxMessageBox(_T("OnTimer can not find appropriate timer type"));
		break;
	}
}
void CELISTestServerDlg::LogDataTimerHandler() {
	//AfxMessageBox(_T("LogDataTimer triggered, implement me!!!"));
	/*
	if (m_actTableChanged)
	{
		
	}
	*/
	//UpdateData(TRUE);
	int direction=wms->direction;
	if (wms->changeTime)
	{
		SetCurrentTestTime(GetCurrentTestTime()+(UINT)m_subsetAssister->assist.logTimerElapse);
	}
	if (wms->changeDepth)
	{
		
		if (acttab->nDepthInterruptMode)
		{
			m_currentDepthDU+= wms->depthSign*METRIC_DU/acttab->gcd;
			if (m_measure)
			{
				SetCurrentDepth(GetCurrentDepth()+(float)wms->depthSign/acttab->gcd);
			} 
			else
			{
				SetCurrentDepth(GetCurrentDepth()+(float)wms->depthSign*METRIC_DU/(acttab->gcd*IMPERIAL_DU));
			}
			
		} 
		else
		{
			m_currentDepthDU+= wms->depthSign*IMPERIAL_DU/acttab->gcd;
			if (m_measure)
			{
				SetCurrentDepth(GetCurrentDepth()+(float)wms->depthSign*IMPERIAL_DU/(acttab->gcd*METRIC_DU));
			} 
			else
			{
				SetCurrentDepth(GetCurrentDepth()+(float)wms->depthSign/acttab->gcd);
			}

		}
		
		
	}

	/*
	if (wms->direction)
	{
		//SetCurrentDepth(GetCurrentDepth()+m_speed*(m_subsetAssister->assist.logTimerElapse/1000));
	} 
	else
	{
		//SetCurrentDepth(GetCurrentDepth()-m_speed*(m_subsetAssister->assist.logTimerElapse/1000));
	}
	*/
	if (wms->returnSubsetData)
	{
		CSubsetData* subsetData=new CSubsetData;
		subsetData->setCommandHeader(m_subsetAssister);
		subsetData->setSubsetData(m_subsetAssister, acttab);
		//subsetData->Save(m_subsetAssister, log);
		getFrontDataQueue()->enQueue(subsetData);

	}
	
}
void CELISTestServerDlg::DepthTimerHandler() {
	//AfxMessageBox(_T("DepthTimer triggered, implement me!!!"));
	CDPMDisplayParameter *dpmp = new CDPMDisplayParameter();
	//CFrontData *fd = new CFrontData();

	//下面这些参数应该从根据实际模拟的进程计算出来
	//填写
	dpmp->ddp.corr_Depth = 10;
	dpmp->ddp.true_Depth = m_currentDepthDU;//this->getCurrentDepthDU();
	dpmp->ddp.speed = m_speedDU*60;
	dpmp->ddp.totalTension = 5;
	dpmp->ddp.differTension = 2;
	dpmp->ddp.time = GetCurrentTestTime();
	dpmp->ddp.nreserved2 = 0;

	//构造这个数据后将其放入SendQueue即可
	//MessageSender线程会自动从队列中取出
	//FrontData数据并发送之
	dpmp->setData(dpmp->ddp);
	fq.enQueue(dpmp);
}

//<<<<<<< .mine
void CELISTestServerDlg::SetCalibParameter(CCalibParameter *clibpara) {
	if(calibpara != NULL) {
		delete calibpara;
		calibpara = NULL;
	}
	calibpara = clibpara;
	//在这理添加代码更新Cal/Ver的ClistTable。
	this->m_tabMyTabCtrl.m_dlgCalVer->SetCalibParameter(clibpara,acttab);
	fillDataFileBufWithCalVer();
	
}

void CELISTestServerDlg::SetACTTable(CActTable *tb) {//091206

	if(acttab != NULL) {
		delete acttab;
		acttab = NULL;
	}
	acttab = tb;
	this->m_tabMyTabCtrl.m_dlgAct->setACTTable(acttab);

/*
	char bff[8192];

	sprintf(bff, "actNum:%ld,nDepthInterruptMode:%ld,",acttab->actNum, acttab->nDepthInterruptMode);
	sprintf(bff, "%spSaList[0].actNo:%d,", bff, acttab->pSaList[0].actNo);

	sprintf(bff, "%spSaList[0].switchOn:%d,", bff, acttab->pSaList[0].switchOn);
	sprintf(bff, "%spSaList[0].actDone:%d,", bff, acttab->pSaList[0].actDone);
	sprintf(bff, "%spSaList[0].depthSampleRate:%d,", bff, acttab->pSaList[0].depthSampleRate);
	sprintf(bff, "%spSaList[0].timeInterval:%d,", bff, acttab->pSaList[0].timeInterval);

	sprintf(bff, "%spSaList[0].toolAddress:%d,", bff, acttab->pSaList[0].toolAddress);
	sprintf(bff, "%spSaList[0].subsetNo:%d,", bff, acttab->pSaList[0].subsetNo);
	sprintf(bff, "%spSaList[0].delay:%d,", bff, acttab->pSaList[0].delay);
	sprintf(bff, "%spSaList[0].m2Length:%d,", bff, acttab->pSaList[0].m2Length);
	sprintf(bff, "%spSaList[0].m5Length:%d,", bff, acttab->pSaList[0].m5Length);
	sprintf(bff, "%spSaList[0].m7Length:%d", bff, acttab->pSaList[0].m7Length);

	AfxMessageBox(_T(bff));
	*/
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
	char szPath[MAX_PATH]; //存放选择的目录路径
    CString str;
    ZeroMemory(szPath, sizeof(szPath)); 
    BROWSEINFO bi;
    bi.hwndOwner = m_hWnd;
    bi.pidlRoot = NULL;
    bi.pszDisplayName = szPath;
    bi.lpszTitle = "请选择ACT数据文件的目录:";
    bi.ulFlags = BIF_USENEWUI;//0
    bi.lpfn = NULL;
    bi.lParam = 0;
    bi.iImage = 0;
	
    //弹出选择目录对话框
    LPITEMIDLIST lp = SHBrowseForFolder(&bi);
    if( lp && SHGetPathFromIDList(lp, szPath) ) {
        str.Format("%s",  szPath);
        //AfxMessageBox(_T(str));
		GetDlgItem(IDC_EDIT_ACT_FOLDER)->SetWindowText(str);
		UpdateData(TRUE);
		TabAct* actListCtrlDlg = m_tabMyTabCtrl.m_dlgAct;
		int itemCount = actListCtrlDlg->m_listctrlAct.GetItemCount();
		if (itemCount > 0)
		{
			for (int i = 0; i < itemCount; i++)
			{
				actListCtrlDlg->setDataFilePath(str, i);
			}
		}
		//m_actListRootFolder=str;
    } else {
        //AfxMessageBox(_T("无效的目录，请重新选择!"));
    }

	
}

void CELISTestServerDlg::OnButtonServerPort() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	GetDlgItem(IDC_BUTTON_SERVER_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVER_PORT)->EnableWindow(FALSE);


	AfxSocketInit(NULL);
	
	
	if(!m_sListenSocket.Create(this->m_sPort)) {
		AfxMessageBox(_T("Socket Error!"));
		m_sListenSocket.Close();
	}else{

		CString serverIP;
		CString serverPort;
		serverPort.Format("%d",m_sPort);
		
		
		//CString serverADDR=serverIP+":"+CString(serverPort);
		char   name[256];  
		hostent*   pHost;  
		gethostname(name,   128);//获得主机名  
		pHost   =   gethostbyname(name);//获得主机结构  
		serverIP   =   inet_ntoa(*((in_addr   *)pHost->h_addr));
		
		GetDlgItem(IDC_STATIC_SERVER_IP_PORT_VALUE)->SetWindowText(_T(serverIP+":"+serverPort));
	}
	
	if(!m_sListenSocket.Listen()){
		int nErrorCode = m_sListenSocket.GetLastError();
		if (nErrorCode != WSAEWOULDBLOCK) {
			m_sListenSocket.Close(); 
		}
	}

	
	

	
}

void CELISTestServerDlg::OnButtonCalverFolder() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH]; //存放选择的目录路径
    CString str;
    ZeroMemory(szPath, sizeof(szPath)); 
    BROWSEINFO bi;
    bi.hwndOwner = m_hWnd;
    bi.pidlRoot = NULL;
    bi.pszDisplayName = szPath;
    bi.lpszTitle = "请选择CAL/VER数据文件的目录:";
    bi.ulFlags = BIF_USENEWUI;//0
    bi.lpfn = NULL;
    bi.lParam = 0;
    bi.iImage = 0;
	
    //弹出选择目录对话框
    LPITEMIDLIST lp = SHBrowseForFolder(&bi);
    if( lp && SHGetPathFromIDList(lp, szPath) ) {
        str.Format("%s",  szPath);
        //AfxMessageBox(_T(str));
		GetDlgItem(IDC_EDIT_CALVER_FOLDER)->SetWindowText(str);
		UpdateData(TRUE);
		//m_actListRootFolder=str;
    } else {
        //AfxMessageBox(_T("无效的目录，请重新选择!"));
    }
	
}

void CELISTestServerDlg::OnButtonDataBufferSize() 
{
	// TODO: Add your control notification handler code here
	CString strBufSize;
	GetDlgItem(IDC_EDIT_DATA_BUFFER_SIZE)->GetWindowText(strBufSize);
	ULONG ul=atol(strBufSize);
	if (errno==ERANGE||errno==EINVAL)
	{
		ul=5;
		
	} 
	
	m_dataFileBufSize=ul*1024*1024;//兆字节转变为字节
	
	
	
	
}

void CELISTestServerDlg::OnButtonSpeed() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_STATIC_SPEED_SHOW_VALUE)->SetWindowText(m_speedStr);
	m_speed = atof(m_speedStr);
	m_speed/= 60;
	if (errno==ERANGE||errno==EINVAL){
		m_speed=0.5f;
	}
	if (m_measure)
	{
		GetDlgItem(IDC_STATIC_SPEED_SHOW_UNIT)->SetWindowText("m/min");
		m_speedDU = m_speed*METRIC_DU;
	} 
	else
	{
		GetDlgItem(IDC_STATIC_SPEED_SHOW_UNIT)->SetWindowText("feet/min");
		m_speedDU = m_speed*IMPERIAL_DU;
	}
	
	
}

/*
这个按钮的响应改成：
修改速度后，启用新的速度进行log数据的传输。
首先在速度框里输入新速度值，点击其后面的Set
按钮后，新速度值显示在当前速度指示的label上。
此时再点击“以新速度进行log”按钮，则logtimer
会在新修改的速度上执行数据返回。
用户点击速度文本框后的Set按钮时，应保证把新的速度
存到成员变量m_speed中。
这个button只有当工作状态处在log数据返回状态：
RtcSYS_STANDBY_CMD、RtcSYS_RECSTART_CMD，且
已经初始化了服务表后才起作用
*/
void CELISTestServerDlg::OnButtonStartLog() 
{
	// TODO: Add your control notification handler code here
	if((wms->mode == RtcSYS_STANDBY_CMD || wms->mode == RtcSYS_RECSTART_CMD) && acttab != NULL) {
		acttab->getLogTimerElapse(m_subsetAssister, m_speed, wms->mode, m_measure);
		StopLogTimer();
		CreateLogTimer(m_subsetAssister->assist.logTimerElapse);
		//SetCurrentTestTime(0);
	} else {
		if(acttab != NULL) {
			acttab->getLogTimerElapse(m_subsetAssister, m_speed, wms->mode, m_measure);
		}
		AfxMessageBox(_T("新速度已生效，系统当前状态不是StandBy Time或Record Time"));
	}
}

void CELISTestServerDlg::OnButtonTrueDepth() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_STATIC_CURRENT_DEPTH_SHOW_VALUE)->SetWindowText(m_trueDepthStr);
	
	if (m_measure)
	{
		GetDlgItem(IDC_STATIC_CURRENT_DEPTH_SHOW_UNIT)->SetWindowText("m");
		m_currentDepthDU = atof(m_trueDepthStr)*METRIC_DU;
	} 
	else
	{
		GetDlgItem(IDC_STATIC_CURRENT_DEPTH_SHOW_UNIT)->SetWindowText("feet");
		m_currentDepthDU = atof(m_trueDepthStr)*IMPERIAL_DU;
	}
	/*
	m_trueDepth=atof(m_trueDepthStr);
	if (errno==ERANGE||errno==EINVAL){
		m_trueDepth=500f;
	}
	*/
	

}

void CELISTestServerDlg::OnRadioImperial() 
{
	// TODO: Add your control notification handler code here
	m_measure=0;
	
}

void CELISTestServerDlg::OnRadioMetric() 
{
	// TODO: Add your control notification handler code here
	m_measure=1;
	
}

int CELISTestServerDlg::getMeasure()
{
	return m_measure;
}
/*
UINT CELISTestServerDlg::getCurrentDepthDU()
{
	float currentDepth;
	if (m_measure)
	{
		currentDepth=GetCurrentDepth()*METRIC_DU;
	} 
	else
	{
		currentDepth=GetCurrentDepth()*IMPERIAL_DU;
	}
	return (UINT)currentDepth;
}
*/
void CELISTestServerDlg::OnButtonCreateLog() 
{
	// TODO: Add your control notification handler code here
	
	if((wms->mode == RtcSYS_STANDBY_CMD || wms->mode == RtcSYS_RECSTART_CMD) && acttab != NULL) {//|| wms->mode == RtcSYS_CALIBSTART_CMD
		StopLogTimer();
		//这个调用要在handleWorkstatechange中执行。
		//acttab->buildSubsetDataAssister(m_subsetAssister, m_speed, wms->mode);
		m_subsetAssister->Save(log);
		CreateLogTimer(m_subsetAssister->assist.logTimerElapse);
		EnableStopLog(TRUE);
		EnableCreateLog(FALSE);
		//SetCurrentTestTime(0);
	} else {
		AfxMessageBox(_T("系统当前状态不是StandBy Time或Record Time"));
	}
	
}






void CELISTestServerDlg::OnButtonStopLog() 
{
	// TODO: Add your control notification handler code here
	StopLogTimer();
	EnableStopLog(FALSE);
	EnableCreateLog(TRUE);

}
