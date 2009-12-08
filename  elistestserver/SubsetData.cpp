#include "stdafx.h"
#include "SubsetData.h"

CSubsetData::CSubsetData(void)
{
	//此处加入计算subsetdata body长度的代码要根据
	//收到的命令所解析的结构CActTable来计算
	//bodyLen = sizeof();
	AfxMessageBox(_T("此处加入计算subsetdata body长度的代码要根据收到的命令所解析的结构CActTable来计算"));
	cmdLen = bodyLen + SOCK_RECEIVE_HEADER_LEN;
	cmdType = NET_RETURN_SUBSETDATA;
}
CSubsetData::CSubsetData(BUF_TYPE* bf, ULONG len):CFrontData(bf, len)
{
	//此处加入计算subsetdata body长度的代码要根据
	//收到的命令所解析的结构CActTable来计算
	AfxMessageBox(_T("此处加入计算subsetdata body长度的代码要根据收到的命令所解析的结构CActTable来计算"));
	//bodyLen = sizeof();
	cmdLen = bodyLen + SOCK_RECEIVE_HEADER_LEN;
	cmdType = NET_RETURN_SUBSETDATA;
}

CSubsetData::~CSubsetData(void)
{
}
