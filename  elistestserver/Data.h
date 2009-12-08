#if !defined(DATA_H)
#define DATA_H

#include "commands.h"
#include "DPMDisplayParameter.h"

class CData {
public:
	CData();
	CData(BUF_TYPE* bf, ULONG len);
	virtual ~CData();
	virtual void setData(BUF_TYPE* bf, ULONG len);
	//void setBuf(BUF_TYPE* b);
	//void setBufLen(long bl);
public:
	BUF_TYPE* buf;
	ULONG buflen;
	ULONG contentlen;
	//CString buf;
};



//主控机上发给前端机的数据
class CMasterData:public CData {
public:
	CMasterData();
	CMasterData(BUF_TYPE* bf, ULONG len);
	virtual ~CMasterData();
};

//前端机上准备的要发给主控机的数据
class CFrontData:public CData {
public:
	CFrontData();
	CFrontData(BUF_TYPE* bf, ULONG len);
	virtual ~CFrontData();
public:
	virtual void setData(CDPMDisplayParameter &dp);
};


#endif
