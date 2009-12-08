#include "stdafx.h"
#include "Data.h"


CData::CData() {
	buf = new BUF_TYPE[DEFAULT_BUF_LEN];
	buflen = DEFAULT_BUF_LEN;
	pBuf = buf;
	contentlen = 0;
}

CData::CData(BUF_TYPE* bf, ULONG len) {
	this->buf = new BUF_TYPE[len];
	buflen = len;
	if(buf == NULL) {
		AfxMessageBox("Creating Data buffer not allocated");
	} else {
		memcpy(this->buf, bf, len);
	}
}

CData::~CData() {
	if(buf != NULL) {
		delete []buf;
	}
}

void CData::assureCapacity(ULONG sizeNeeded) {
	ULONG rem = buflen - contentlen;
	BUF_TYPE *buft;
	if(this->buf == NULL || rem < sizeNeeded) {
		buft = new BUF_TYPE[contentlen + sizeNeeded];
		ASSERT(buft != NULL);
		this->buflen = contentlen + sizeNeeded;

		if(this->buf != NULL) {
			if(contentlen > 0) {
				memcpy(buft, buf, contentlen);
			}
			delete []this->buf;
		} else {//这不应该出现,contentlen必须已经是0
			contentlen = 0;
		}
		this->buf = buft;
		this->pBuf = (this->buf + contentlen);
	}
}

void CData::setData(BUF_TYPE* bf, ULONG len) {
	assureCapacity(len);
	memcpy(this->pBuf, bf, len);
	pBuf += len;
	contentlen += len;
}

void CData::setHeader(ULONG cmdType, ULONG cmdLen) {
	ULONG *t;
	
	assureCapacity(SOCK_RECEIVE_HEADER_LEN);
	
	t = (ULONG*)pBuf;
	t[0] = cmdType;
	t[1] = cmdLen;

	pBuf += SOCK_RECEIVE_HEADER_LEN;
	contentlen += SOCK_RECEIVE_HEADER_LEN;
}


//CMasterData----------------
CMasterData::CMasterData():CData() {
}
CMasterData::CMasterData(BUF_TYPE* bf, ULONG len):CData(bf, len) {
}
CMasterData::~CMasterData() {
	//CData::~CData();
}



//CFrontData----------------
CFrontData::CFrontData():CData() {
}
CFrontData::CFrontData(BUF_TYPE* bf, ULONG len):CData(bf, len) {
}
void CFrontData::setData(CDPMDisplayParameter &dp) {
	setHeader(dp.getCmdType(), dp.getCmdLength());
	//memcpy(buf+SOCK_RECEIVE_HEADER_LEN, &(dp.ddp), sizeof(CDPMDisplayParameter::DPM_DISPLAY_PARA));
	CData::setData((BUF_TYPE*)&(dp.ddp), sizeof(CDPMDisplayParameter::DPM_DISPLAY_PARA));
}
CFrontData::~CFrontData() {
	//CData::~CData();
}