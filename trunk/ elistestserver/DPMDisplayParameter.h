#ifndef DPMDISPLAYPARAMETER_H
#define DPMDISPLAYPARAMETER_H

#pragma once

class CDPMDisplayParameter
{
public:
	typedef struct {
		int corr_Depth;
		int true_Depth;
		int speed;
		int totalTension;		//������
		int mmd;
		int differTension;		//�������
		UINT  time;					//ʱ��
		int   nreserved2;			//����
	} DPM_DISPLAY_PARA;
	DPM_DISPLAY_PARA ddp;
public:
	CDPMDisplayParameter(void);
	virtual ~CDPMDisplayParameter(void);
};

#endif