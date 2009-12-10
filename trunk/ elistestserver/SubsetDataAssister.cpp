// SubsetDataAssister.cpp: implementation of the CSubsetDataAssister class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ELISTestServer.h"
#include "SubsetDataAssister.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSubsetDataAssister::CSubsetDataAssister()
{
	assist.shareOfCommonBuffer = NULL;
	assist.subsetNumPerReturn = NULL;
	assist.totalSizeOfSubsetsPerReturn = NULL;

	heads = NULL;

	created = FALSE;
}

CSubsetDataAssister::~CSubsetDataAssister()
{
	clear();
}

void CSubsetDataAssister::clear()
{
	if(assist.shareOfCommonBuffer != NULL) delete []assist.shareOfCommonBuffer;
	if(assist.subsetNumPerReturn !=  NULL) delete []assist.subsetNumPerReturn;
	if(assist.totalSizeOfSubsetsPerReturn != NULL) delete []assist.totalSizeOfSubsetsPerReturn;
	
	if(heads != NULL) delete []heads;

	created = FALSE;
}

void CSubsetDataAssister::create(UINT actNum)
{
	clear();
	ASSERT(actNum > 0);

	assist.shareOfCommonBuffer = new float[actNum];
	assist.subsetNumPerReturn = new UINT[actNum];
	assist.totalSizeOfSubsetsPerReturn = new UINT[actNum];
	heads = new RtcBLOCK_DATA_HEADER[actNum];

	this->actNum = actNum;
	created = TRUE;
}
