#ifndef DPMDISPLAYPARAMETER_H
#define DPMDISPLAYPARAMETER_H

#pragma once

#include "commands.h"

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
	ULONG cmdType;
	ULONG cmdLen;
	ULONG bodyLen;
public:
	CDPMDisplayParameter(void);
	virtual ~CDPMDisplayParameter(void);
public:
	ULONG getCmdLength() {
		return cmdLen;
	}
	ULONG getCmdType() {
		return cmdType;
	}
	ULONG getBodyLength() {
		return bodyLen;
	}
};

#endif