#include "stdafx.h"
#include "Data.h"


CData::CData() {
	buf = new unsigned char[DEFAULT_BUF_LEN];
	buflen = DEFAULT_BUF_LEN;
}
CData::CData(void *buf, int len) {
	this->buf = new unsigned char[len];
	buflen = len;
	if(buf == NULL) {
		AfxMessageBox("Creating Data buffer not allocated");
	} else {
		memcpy(this->buf, buf, len);
	}
}

CData::~CData() {
	if(buf != NULL) {
		//AfxMessageBox("FrontData buf is not null", MB_YESNO, 0);
		delete []buf;
	}
}

void CData::SetData(void *buf, int len) {
	if(len > DEFAULT_BUF_LEN) {
		delete []this->buf;
		this->buf = new unsigned char[len];
		this->buflen = len;
	}
	memcpy(this->buf, buf, len);
}

CMasterData::CMasterData():CData() {
}
CMasterData::CMasterData(void *buf, int len):CData(buf, len) {
	//CData::SetData(buf, len);
}
CMasterData::~CMasterData() {
	//CData::~CData();
}


CFrontData::CFrontData():CData() {
}
CFrontData::CFrontData(void *buf, int len):CData(buf, len) {
}
void CFrontData::SetData(CDPMDisplayParameter &dp) {
	//char b[100];
	//int *t;
	memcpy(buf, &(dp.ddp), sizeof(CDPMDisplayParameter::DPM_DISPLAY_PARA));

	//t = (int*)buf;
	//sprintf_s(b, "%ld,%ld", t[0], t[1]);
	//AfxMessageBox(_T(b));
}
CFrontData::~CFrontData() {
	//CData::~CData();
}