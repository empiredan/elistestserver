// SubsetDataAssister.h: interface for the CSubsetDataAssister class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBSETDATAASSISTER_H__628DED63_614B_44BF_8069_0C2A62485016__INCLUDED_)
#define AFX_SUBSETDATAASSISTER_H__628DED63_614B_44BF_8069_0C2A62485016__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSubsetDataAssister  
{
public:
	CSubsetDataAssister();
	virtual ~CSubsetDataAssister();
public:
	typedef struct {
		UINT logTimerElapse;
		UINT *subsetNumPerReturn;//��һ�����飬Ԫ�ظ���ΪactNum��subsetNumPerReturn[i] = lcm/Ti=lcm/CActTable::pSaList[i].timeInterval;
		UINT *totalSizeOfSubsetsPerReturn;//��һ�����飬Ԫ�ظ���ΪactNum����ʾһ�η���ʱÿһ��subset����size
		float *shareOfCommonBuffer; //��һ�����飬Ԫ�ظ���ΪactNum������ó���ÿһ��Ӧ����Ĺ����ļ���������С��������������������ֵ����ÿ����Ӧ�ֵõĻ������ռ��С��
	} ASSISTER;
	ASSISTER assist;
	BOOL created;
public:
	void clear();
	void create(UINT actNum);
};

#endif // !defined(AFX_SUBSETDATAASSISTER_H__628DED63_614B_44BF_8069_0C2A62485016__INCLUDED_)
