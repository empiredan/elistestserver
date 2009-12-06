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
		int totalTension;		//总张力
		int mmd;
		int differTension;		//差分张力
		UINT  time;					//时间
		int   nreserved2;			//保留
	} DPM_DISPLAY_PARA;
	DPM_DISPLAY_PARA ddp;
public:
	CDPMDisplayParameter(void);
	virtual ~CDPMDisplayParameter(void);
};

#endif