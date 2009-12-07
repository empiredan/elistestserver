#include "stdafx.h"
#include "Data.h"


CData::CData() {
	buf = new BUF_TYPE[DEFAULT_BUF_LEN];
	buflen = DEFAULT_BUF_LEN;
}

CData::CData(BUF_TYPE* bf, long len) {
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

void CData::setData(BUF_TYPE* bf, long len) {
	if(len > DEFAULT_BUF_LEN) {
		delete []this->buf;
		this->buf = new BUF_TYPE[len];
		this->buflen = len;
	}
	memcpy(this->buf, bf, len);
}

/*
void CData::setBuf(BUF_TYPE* b){
	buf=b;
}
void CData::setBufLen(long bl){
	buflen=bl;
}
*/

CMasterData::CMasterData():CData() {
}
CMasterData::CMasterData(BUF_TYPE* bf, long len):CData(bf, len) {
}
CMasterData::~CMasterData() {
	//CData::~CData();
}


CFrontData::CFrontData():CData() {
}
CFrontData::CFrontData(BUF_TYPE* bf, long len):CData(bf, len) {
}
CFrontData::~CFrontData() {
	//CData::~CData();
}