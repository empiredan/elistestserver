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



//���ػ��Ϸ���ǰ�˻�������
class CMasterData:public CData {
public:
	CMasterData();
	CMasterData(BUF_TYPE* bf, ULONG len);
	virtual ~CMasterData();
};

//ǰ�˻���׼����Ҫ�������ػ�������
class CFrontData:public CData {
public:
	CFrontData();
	CFrontData(BUF_TYPE* bf, ULONG len);
	virtual ~CFrontData();
public:
	virtual void setData(CDPMDisplayParameter &dp);
};


#endif
