#if !defined(DATA_H)
#define DATA_H
#include "stdafx.h"
#include "DPMDisplayParameter.h"

#define DEFAULT_BUF_LEN 50000

class CData {
public:
	CData();
	CData(void *buf, int len);
	virtual ~CData();
public:
	virtual void SetData(void *buf, int len);
public:
	unsigned char *buf;
	int buflen;
};



//主控机下发给前端机的数据
class CMasterData:public CData {
public:
	CMasterData();
	CMasterData(void *buf, int len);
	virtual ~CMasterData();
};

//前端机上准备的要发给主控机的数据
class CFrontData:public CData {
public:
	CFrontData();
	CFrontData(void *buf, int len);
	virtual void SetData(CDPMDisplayParameter &dp);
	virtual ~CFrontData();
};


#endif
