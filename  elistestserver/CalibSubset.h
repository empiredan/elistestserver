// CalibSubset.h: interface for the CCalibSubset class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALIBSUBSET_H__50408564_660B_4E6E_A5A6_83B4D606D855__INCLUDED_)
#define AFX_CALIBSUBSET_H__50408564_660B_4E6E_A5A6_83B4D606D855__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Data.h"
#include "commands.h"

class CCalibSubset:public CFrontData
{
public:
	CCalibSubset();
	CCalibSubset(BUF_TYPE* bf, ULONG len);
	virtual ~CCalibSubset();
};

#endif // !defined(AFX_CALIBSUBSET_H__50408564_660B_4E6E_A5A6_83B4D606D855__INCLUDED_)
