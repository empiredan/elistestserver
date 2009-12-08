#include "stdafx.h"
#include "DPMDisplayParameter.h"

CDPMDisplayParameter::CDPMDisplayParameter(void)
{
	bodyLen = sizeof(DPM_DISPLAY_PARA);
	cmdLen = bodyLen + SOCK_RECEIVE_HEADER_LEN;
	cmdType = NET_RETURN_DPMPARA;
}

CDPMDisplayParameter::~CDPMDisplayParameter(void)
{
}

