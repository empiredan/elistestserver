#include "stdafx.h"
#include "CommandHandler.h"
#include "Data.h"
#include "Queue.h"
#include "ELISTestServerDlg.h"

#include "commands.h"
#include "TimerDef.h"

//class CELISTestServerDlg;
CCommandHandler::CCommandHandler() {
	this->dlg = dlg;
	finish = FALSE;
	headSize = SOCK_RECEIVE_HEADER_LEN;
}
CCommandHandler::~CCommandHandler(void)
{
}

void CCommandHandler::start() {
	worker = CreateThread(NULL, 
											0,
											&CCommandHandler::handle,
											this,		//���ݶ���ָ����Ϊ�̺߳���LPVOID param����
											0,			//start immediately after create
											&wid);
}

DWORD CCommandHandler::handle(LPVOID param) {
	CCommandHandler *handler = (CCommandHandler *)param;
	CMasterData *d;
	CDataQueue<CMasterData> *q;
	ULONG cmdtype;
	ULONG *buft;
	
	//
	char t[512];
	q = handler->dlg->getMasterDataQueue();
	
	while(!handler->finish) {
		d = q->deQueue();
		//sprintf_s(t, "Command Handler handle:::buf[0]=%d,buf[1]=%d", ntohl(d->buf[0]), ntohl(d->buf[1]));
		//AfxMessageBox(_T(t));
		if( d == NULL) {
			continue;
		}
		//�����ﴦ��������������Ӧ��
		//�����������������
		buft = (ULONG*)d->buf;
		cmdtype = ntohl(buft[0]);
		
		switch(cmdtype) {
			case NET_CMDTYPE_INIT_SERVICE_TABLE:
				//call NetCmd_InitServiceTable(*cmdBuffer)
				handler->NetCmd_InitServiceTable(d);
			break;
			case NET_CMDTYPE_INIT_CONFIG_PARAMETER:
				handler->NetCmd_InitConfigParameter(d);
			break;
			case NET_CMDTYPE_CTRL_DEACTIVATE:
				handler->NetCmd_CtrlActDeactivate(d);
			break;
			case NET_CMDTYPE_CTRL_WORK_STATE:
				handler->NetCmd_CtrlWorkState(d);
			break;
			case NET_CMDTYPE_CTRL_STANDBYTIME_INTERVAL:
				handler->NetCmd_CtrlStandbytimeInterval(d);
			break;
			case NET_CMDTYPE_CTRL_RECSTOP:
				handler->NetCmd_CtrlRecstop(d);
			break;
			case NET_CMDTYPE_CTRL_ACTSWITCH:
				handler->NetCmd_CtrlACTSwitch(d);
			break;
			//����Ϊ�̶���������
			case NET_CMDTYPE_CALIB_PARA:
				handler->NetCmd_CalibPara(d);
			break;
			case NET_CMDTYPE_CALIB_START:
				handler->NetCmd_CalibStart(d);
			break;
			case NET_CMDTYPE_CALIB_STOP:
				handler->NetCmd_CalibStop(d);
			break;
			//���ο�������
			case NET_CMDTYPE_SNGL_CTLCMD:
				handler->NetCmd_SnglCtl(d);
			break;
			//��������ж�Ϊ�ڲ����ⲿ,
			//����ȣ�4���ֽڣ����0Ϊ�ڲ���1Ϊ�ⲿ�ж�
			case NET_CMDTYPE_DEPTH_INTERNAL:
				handler->NetCmd_DepthInternal(d);
			break;
			//�ڲ���ʽ�£����÷���,
			//����ȣ�4���ֽڣ���� 0Ϊ�ϣ�1Ϊ��
			case NET_CMDTYPE_DEPTH_DIRECTION:
				handler->NetCmd_DepthDirection(d);
			break;
			//���ڲ���ʽ�£������ٶ�
			//����ȣ�4���ֽڣ�����ٶ�ֵ
			case NET_CMDTYPE_DEPTH_SPEED:
				handler->NetCmd_DepthSpeed(d);
			break;
			//������ʵ���
			//����ȣ�4���ֽڣ�������ֵ��DU��
			case NET_CMDTYPE_DEPTH_TRUEDEPTH:
				handler->NetCmd_TrueDepth(d);
			break;
			//�������
			//����ȣ�4���ֽڣ�������ֵ��DU��
			case NET_CMDTYPE_DEPTH_CORRECTEDDEPTH:
				handler->NetCmd_CorrectedDepth(d);
			break;
			//�ֶ�У�����Ӽ������
			//����ȣ�8���ֽڣ�ǰ4 byteΪ�Ӽ����0Ϊ����1Ϊ�ӣ�
			//��4 byteΪ��Ӣ�����0ΪӢ�ƣ� 1Ϊ����
			case NET_CMDTYPE_DEPTH_MANUALDEPTHCORR:
				handler->NetCmd_ManualDepthCorrection(d);
			break;
			//�Զ�У�����Ӽ������
			//����ȣ�8���ֽڣ�ǰ4 byteΪ�������0ΪֹͣУ����1Ϊ��ʼУ����
			//��4 byteΪУ�����
			case NET_CMDTYPE_DEPTH_AUTODEPTHCORR:
				handler->NetCmd_AutoDepthCorrection(d);
			break;
			//��Ȱ�����
			//����ȣ�4���ֽڣ����1
			case NET_CMDTYPE_DEPTH_LOCK:
				handler->NetCmd_DepthLock(d);
			break;
			//��Ȱ����
			//����ȣ�4���ֽڣ����0
			case NET_CMDTYPE_DEPTH_UNLOCK:
				handler->NetCmd_DepthUnlock(d);
			break;
			//֪ͨ������������
			//����ȣ�4���ֽڣ����1
			//���أ�4���ֽڣ���16λmaxTension����16λoffsetTension��
			//�������ͣ�NET_RETURN_DEPTHPANEL_READTENSIONFACTOR
			case NET_CMDTYPE_DEPTH_TENSIONFACTOR:
				handler->NetCmd_DepthTensionFactor(d);
			break;
			//֪ͨ���������Ƕ�
			//����ȣ�4���ֽڣ����1
			//���أ�4���ֽڣ������Ƕȣ�
			//�������ͣ�NET_RETURN_DEPTHPANEL_READTENSIONANGLE
			case NET_CMDTYPE_DEPTH_TENSIONANGLE:
				handler->NetCmd_DepthTensionAngle(d);
			break;
			//֪ͨ����CHT
			//����ȣ�4���ֽڣ����CHTֵ
			case NET_CMDTYPE_DEPTH_CHT:
				handler->NetCmd_DepthCHT(d);
			break;
			/*
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			case :
			break;
			*/
			default:
				char cmdtp[500];
				ULONG *cmdtpt;
				cmdtpt = (ULONG*)d->buf;
				sprintf(cmdtp, "CCommandHandler::handle, type%lx not defined", cmdtpt[1]);
				//AfxMessageBox(_T(cmdtp));
			break;
		}
	}

	return 0;
}

void CCommandHandler::NetCmd_InitServiceTable(CMasterData *d) {
	AfxMessageBox(_T("Implement me, NetCmd_InitServiceTable"));

	CActTable *tb;
	//int rate[2];
	UINT logTimerInterval;

	logTimerInterval = 5000;

	tb = CActTable::AllocateActTable((d->buf)+headSize, d->contentlen-headSize);
	tb->ConvertData();
	dlg->SetACTTable(tb);
	//tb->MaximumCommonSampleRate(rate);

	//������еĽ��������ö�����֮��
	//���¼���õ���logTimerIntervalֵ��������log timer
	dlg->StopLogTimer();
	dlg->CreateLogTimer(logTimerInterval);
	
	//������������Ҫdelete CMasterData���͵�ָ��d��
	//��Ϊԭ���ϣ����������յ���ǰ�˻����͹���������
	//������ϣ��Ͳ�����ʹ���ˣ�Ҫ����ɾ������
	//���CMasterData��������Dialog��ͨ��socket�յ�֮�ʣ�
	//new �����ŵ������еģ�����
	//ÿ�������Ĵ���������Ҫ��������
	//��������������Ҫ��Ϊ����ʹ�õĲ������棬��ô
	//Ӧ�ð�����ͨ����Ӧ�����ݽṹ������ȥ��
	delete d;
}

void CCommandHandler::NetCmd_CalibPara(CMasterData *d) {
	BUF_TYPE *bodyBuf;
	ULONG bodyLen;

	ULONG *head;
	ULONG cmdType, totalLen;

	head = (ULONG*)d->buf;
	cmdType = ntohl(d->buf[0]);
	totalLen = ntohl(d->buf[1]);

	bodyLen = totalLen - headSize;
	bodyBuf = d->buf + headSize;

	//AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CalibPara"));
	CCalibParameter *ccp = new CCalibParameter(bodyBuf, bodyLen);
	dlg->SetCalibParameter(ccp);
}
void CCommandHandler::NetCmd_CalibStart(CMasterData *d) {
	BUF_TYPE *bodyBuf;
	ULONG bodyLen;

	ULONG *head;
	ULONG cmdType, totalLen;

	head = (ULONG*)d->buf;
	cmdType = ntohl(d->buf[0]);
	totalLen = ntohl(d->buf[1]);

	bodyLen = totalLen - headSize;
	bodyBuf = d->buf + headSize;

	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CalibStart"));
}
void CCommandHandler::NetCmd_CalibStop(CMasterData *d) {
	BUF_TYPE *bodyBuf;
	ULONG bodyLen;

	ULONG *head;
	ULONG cmdType, totalLen;

	head = (ULONG*)d->buf;
	cmdType = ntohl(d->buf[0]);
	totalLen = ntohl(d->buf[1]);

	bodyLen = totalLen - headSize;
	bodyBuf = d->buf + headSize;

	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CalibStop"));
}
void CCommandHandler::NetCmd_CtrlWorkState(CMasterData *d) {
	BUF_TYPE *bodyBuf;
	ULONG bodyLen;

	ULONG *head;
	ULONG cmdType, totalLen;

	head = (ULONG*)d->buf;
	cmdType = ntohl(d->buf[0]);
	totalLen = ntohl(d->buf[1]);

	bodyLen = totalLen - headSize;
	bodyBuf = d->buf + headSize;

	//CWorkModeSetter *wms = dlg->getWorkModeSetter();
	CWorkModeSetter *wms = NULL;
	wms->fillWorkMode(bodyBuf, bodyLen);
	//AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CtrlWorkState"));
}
void CCommandHandler::NetCmd_SetStandbyTimeInterval(CMasterData *d) {
	BUF_TYPE *bodyBuf;
	ULONG bodyLen;

	ULONG *head;
	ULONG cmdType, totalLen;

	head = (ULONG*)d->buf;
	cmdType = ntohl(d->buf[0]);
	totalLen = ntohl(d->buf[1]);

	bodyLen = totalLen - headSize;
	bodyBuf = d->buf + headSize;

	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_SetStandbyTimeInterval"));
}
void CCommandHandler::NetCmd_CtrlRecStop(CMasterData *d) {
	BUF_TYPE *bodyBuf;
	ULONG bodyLen;

	ULONG *head;
	ULONG cmdType, totalLen;

	head = (ULONG*)d->buf;
	cmdType = ntohl(d->buf[0]);
	totalLen = ntohl(d->buf[1]);

	bodyLen = totalLen - headSize;
	bodyBuf = d->buf + headSize;

	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CtrlRecStop"));
}
void CCommandHandler::NetCmd_CtrlActSwitch(CMasterData *d) {
	BUF_TYPE *bodyBuf;
	ULONG bodyLen;

	ULONG *head;
	ULONG cmdType, totalLen;

	head = (ULONG*)d->buf;
	cmdType = ntohl(d->buf[0]);
	totalLen = ntohl(d->buf[1]);

	bodyLen = totalLen - headSize;
	bodyBuf = d->buf + headSize;

	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CtrlActSwitch"));
}
void CCommandHandler::NetCmd_CtrlActDeactivate(CMasterData *d) {
	BUF_TYPE *bodyBuf;
	ULONG bodyLen;

	ULONG *head;
	ULONG cmdType, totalLen;

	head = (ULONG*)d->buf;
	cmdType = ntohl(d->buf[0]);
	totalLen = ntohl(d->buf[1]);

	bodyLen = totalLen - headSize;
	bodyBuf = d->buf + headSize;

	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CtrlActDeactivate"));
}


void CCommandHandler::NetCmd_InitConfigParameter(CMasterData *d) {
	//AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_InitConfigParameter"));
}
void CCommandHandler::NetCmd_CtrlStandbytimeInterval(CMasterData *d) {
	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CtrlStandbytimeInterval"));
}
void CCommandHandler::NetCmd_CtrlRecstop(CMasterData *d) {
	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CtrlRecstop"));
}
void CCommandHandler::NetCmd_CtrlACTSwitch(CMasterData *d) {
	//AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CtrlACTSwitch"));
}
void CCommandHandler::NetCmd_SnglCtl(CMasterData *d) {
	//AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_SnglCtl"));
}
void CCommandHandler::NetCmd_DepthInternal(CMasterData *d) {
	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_DepthInternal"));
}
void CCommandHandler::NetCmd_DepthDirection(CMasterData *d) {
	AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_DepthDirection"));
}
void CCommandHandler::NetCmd_DepthSpeed(CMasterData *d) {
	//AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_DepthSpeed"));
}
void CCommandHandler::NetCmd_TrueDepth(CMasterData *d) {
	//AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_TrueDepth"));
}
void CCommandHandler::NetCmd_CorrectedDepth(CMasterData *d) {
	//AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_CorrectedDepth"));
}
void CCommandHandler::NetCmd_ManualDepthCorrection(CMasterData *d) {
	//AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_ManualDepthCorrection"));
}
void CCommandHandler::NetCmd_AutoDepthCorrection(CMasterData *d) {
	//AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_AutoDepthCorrection"));
}
void CCommandHandler::NetCmd_DepthLock(CMasterData *d) {
	//AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_DepthLock"));
}
void CCommandHandler::NetCmd_DepthUnlock(CMasterData *d) {
	//AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_DepthUnlock"));
}
void CCommandHandler::NetCmd_DepthTensionFactor(CMasterData *d) {
	//AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_DepthTensionFactor"));
}
void CCommandHandler::NetCmd_DepthTensionAngle(CMasterData *d) {
	//AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_DepthTensionAngle"));
}
void CCommandHandler::NetCmd_DepthCHT(CMasterData *d) {
	//AfxMessageBox(_T("Implement me!! CCommandHandler::NetCmd_DepthCHT"));
}
