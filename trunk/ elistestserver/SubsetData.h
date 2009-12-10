#pragma once
#include "data.h"

class CSubsetData :	public CFrontData
{
public:
	CSubsetData(void);
	CSubsetData(BUF_TYPE* bf, ULONG len);
	virtual ~CSubsetData(void);
public:
	void setData(BUF_TYPE *bf, ULONG len);
};
