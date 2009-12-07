#if !defined(DATA_H)
#define DATA_H

#define DEFAULT_BUF_LEN 50000
typedef BYTE BUF_TYPE; 

typedef struct{
	long type;
	long len;
}MasterData_Header;

class CData {
public:
	CData();
	CData(BUF_TYPE* bf, long len);
	virtual ~CData();
	virtual void setData(BUF_TYPE* bf, long len);
	//void setBuf(BUF_TYPE* b);
	//void setBufLen(long bl);
public:
	BUF_TYPE* buf;
	long buflen;
	//CString buf;
};



//���ػ��Ϸ���ǰ�˻�������
class CMasterData:public CData {
public:
	CMasterData();
	CMasterData(BUF_TYPE* bf, long len);
	virtual ~CMasterData();
//public:
	//MasterData_Header msDataHeader;
};

//ǰ�˻���׼����Ҫ�������ػ�������
class CFrontData:public CData {
public:
	CFrontData();
	CFrontData(BUF_TYPE* bf, long len);
	virtual ~CFrontData();
};


#endif
