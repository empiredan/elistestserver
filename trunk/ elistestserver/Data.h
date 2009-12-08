#if !defined(DATA_H)
#define DATA_H

#include "commands.h"
#include "DPMDisplayParameter.h"

class CData {
public:
	CData();
	CData(BUF_TYPE* bf, ULONG len);
	virtual ~CData();
public:
	virtual void setData(BUF_TYPE* bf, ULONG len);
	//ȷ��buf���ܳ��ȹ���
	//�����������buflen�Ĵ�СӦ>=sizeNeeded
	virtual void assureCapacity(ULONG sizeNeeded);
	//����buf��ǰ����long��
	//�������������ͷ��pBuf��ǰ��2��sizeof(ULONG)
	//contentlenҲ����Ӧ����Ϊ2��sizeof(ULONG)
	virtual void setHeader(ULONG cmdType, ULONG cmdLen);
	//void setBuf(BUF_TYPE* b);
	//void setBufLen(long bl);
public:
	//pBuf��Ϊ��ʱָ�룬ָ��buf�еĵ�һ����λ��
	BUF_TYPE *buf, *pBuf;
	//buflen��buf����Ч���ȣ�contentlenӦ��С�ڵ���buflen
	ULONG buflen;
	//contentlen��¼��ǰbuf���Ѿ��ж�����Ч������
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