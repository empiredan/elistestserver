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
		UINT *subsetNumPerReturn;//是一个数组，元素个数为actNum，subsetNumPerReturn[i] = lcm/Ti=lcm/CActTable::pSaList[i].timeInterval;
		UINT *totalSizeOfSubsetsPerReturn;//是一个数组，元素个数为actNum，表示一次反馈时每一项subset的总size
		float *shareOfCommonBuffer; //是一个数组，元素个数为actNum，计算得出的每一项应分配的公共文件缓冲区大小比例。根据这个数组里的值计算每个项应分得的缓冲区空间大小。
	} ASSISTER;
	ASSISTER assist;
	BOOL created;
public:
	void clear();
	void create(UINT actNum);
};

#endif // !defined(AFX_SUBSETDATAASSISTER_H__628DED63_614B_44BF_8069_0C2A62485016__INCLUDED_)
