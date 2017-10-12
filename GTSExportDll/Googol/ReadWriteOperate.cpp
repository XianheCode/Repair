// ReadWriteOperate.cpp: implementation of the CReadWriteOperate class.
//
//////////////////////////////////////////////////////////////////////
//#include "stdafx.h"
#include "ReadWriteOperate.h"
#include <tchar.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadWriteOperate::CReadWriteOperate()
{
	if (GetAppPath(m_pathAddress) == 0)
	{
		TCHAR cfgIni[] = { 'c', 'f', 'g', '.', 'I', 'N', 'I', '\0' };
		wcscat_s(m_pathAddress, 255, cfgIni);
	}
}

CReadWriteOperate::CReadWriteOperate(const TCHAR* pArray)
{
	if (GetAppPath(m_pathAddress) == 0)
	{
		wcscat_s(m_pathAddress, 255, pArray);
	}
}

CReadWriteOperate::~CReadWriteOperate()
{

}
int CReadWriteOperate::GetAppPath(LPTSTR pathAddress)
{
	TCHAR path[_MAX_PATH];
	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];

	::GetModuleFileName(NULL,path,_MAX_PATH);
	_wsplitpath_s(path,drive,dir,fname,ext);

	TCHAR* szEzdPath = new TCHAR[255];
	//_tcscpy(szEzdPath,drive);
	wcscpy_s(szEzdPath,255,drive);
	wcscat_s(szEzdPath,255,dir);
	int iLen = wcslen(szEzdPath);
	if (iLen >=0 )
	{
		iLen = wcscpy_s(m_pathAddress, 255, szEzdPath);
	}	
	return iLen;
}

int CReadWriteOperate::ReadKey(LPTSTR strSection, LPTSTR strSectionKey, LPTSTR &strValue)
{
	int ret;
	TCHAR* szbuf = new TCHAR[255];
	ret = GetPrivateProfileString(strSection, strSectionKey, NULL, szbuf, 255, m_pathAddress);
	strValue = szbuf;
	return ret;
}

int CReadWriteOperate::ReadKey(LPTSTR strSection, LPTSTR strSectionKey, float &fValue)
{
	int ret;
	TCHAR szbuf[255];
	ret = GetPrivateProfileString(strSection, strSectionKey, NULL, szbuf, 255, m_pathAddress);
	TCHAR ch[255];
	ZeroMemory(ch,255);
#ifndef _UNICODE
	//_stprintf_s(ch, "%s", szbuf);
#else
	//_stprintf_s(ch, _T("%S"), szbuf);
#endif
	fValue = _wtof(ch);
	return ret;
}

int CReadWriteOperate::ReadKey(LPTSTR strSection, LPTSTR strSectionKey , double &dValue)
{
	int ret;
	TCHAR szbuf[255];
	ret = GetPrivateProfileString(strSection, strSectionKey, NULL, szbuf, 255, m_pathAddress);	
#ifndef _UNICODE

	dValue = atof(szbuf);

#else
//	TCHAR ch[255];
//	ZeroMemory(ch,255);
//	_stprintf_s(ch, _T("%S"), szbuf);
	dValue = _wtof(szbuf);
#endif	
	return ret;
}

int CReadWriteOperate::ReadKey(LPTSTR strSection, LPTSTR strSectionKey , int &iValue)
{
	int ret;
	TCHAR szbuf[255];
	ret = GetPrivateProfileString(strSection, strSectionKey, NULL, szbuf, 255, m_pathAddress);
	iValue = _ttoi(szbuf);
	return ret;
}

int CReadWriteOperate::ReadKey(LPTSTR strSection, LPTSTR strSectionKey , short &sValue)
{
	int ret;
	TCHAR szbuf[255];
	ret = GetPrivateProfileString(strSection, strSectionKey, NULL, szbuf, 255, m_pathAddress);
	sValue = _ttoi(szbuf);
	return ret;
}

int CReadWriteOperate::ReadKey(LPTSTR strSection, LPTSTR strSectionKey , long &lValue)
{
	int ret;
	TCHAR szbuf[255];
	ret = GetPrivateProfileString(strSection, strSectionKey, NULL, szbuf, 255, m_pathAddress);
	lValue = _wtol(szbuf);
	return ret;
}

int CReadWriteOperate::ReadKey(LPTSTR strSection, LPTSTR strSectionKey , bool& bValue)
{
	int ret;
	TCHAR szbuf[255];
	int lValue = 0;
	ret = GetPrivateProfileString(strSection, strSectionKey, NULL, szbuf, 255, m_pathAddress);
	lValue = _wtol(szbuf);
	if (lValue == 1)
	{
		bValue = true;
	}
	else
	{
		bValue = false;
	}
	return ret;
}

int CReadWriteOperate::WriteKey(LPTSTR strSection, LPTSTR strSectionKey , LPTSTR strvalue )
{
	int ret = 0;
	ret = WritePrivateProfileString(strSection, strSectionKey, strvalue, m_pathAddress);
	return ret;
}

int CReadWriteOperate::WriteKey(LPTSTR strSection, LPTSTR strSectionKey , float fvalue )
{
	int ret = 0;
	TCHAR strtemp[255];
	_stprintf_s(strtemp, _T("%f"), fvalue);
	ret = WritePrivateProfileString(strSection, strSectionKey, strtemp, m_pathAddress);
	return ret;
}

int CReadWriteOperate::WriteKey(LPTSTR strSection, LPTSTR strSectionKey, double dvalue)
{
	int ret = 0;
	TCHAR strtemp[255];
	_stprintf_s(strtemp, _T("%f"), dvalue);
	ret = WritePrivateProfileString(strSection, strSectionKey, strtemp, m_pathAddress);
	return ret;
}

int CReadWriteOperate::WriteKey(LPTSTR strSection, LPTSTR strSectionKey , int ivalue )
{
	int ret = 0;
	TCHAR strtemp[255];
	_stprintf_s(strtemp, _T("%d"), ivalue);
	ret = WritePrivateProfileString(strSection, strSectionKey, strtemp, m_pathAddress);
	return ret;
}


//////////////////////////////////////////////////////////////////////////
int CReadWriteOperate::WriteKey(LPTSTR strSection, LPTSTR strSectionKey , short svalue )
{
	int ret = 0;
	TCHAR strtemp[255];
	_stprintf_s(strtemp, _T("%d"), svalue);
	ret = WritePrivateProfileString(strSection, strSectionKey, strtemp, m_pathAddress);
	return ret;
}


int CReadWriteOperate::WriteKey(LPTSTR strSection, LPTSTR strSectionKey, long lvalue)
{
	int ret = 0;
	TCHAR strtemp[255];
	_stprintf_s(strtemp, _T("%d"), lvalue);
	ret = WritePrivateProfileString(strSection, strSectionKey, strtemp, m_pathAddress);
	return ret;
}

int CReadWriteOperate::WriteKey(LPTSTR strSection, LPTSTR strSectionKey, bool& bValue)
{
	int ret = 0;
	TCHAR strtemp[255];
	if (bValue)
	{
		_stprintf_s(strtemp, _T("%s"), "1");
	}
	else
	{
		_stprintf_s(strtemp, _T("%s"), "0");
	}
	ret = WritePrivateProfileString(strSection,strSectionKey,strtemp,m_pathAddress);
	return ret;
}

// void CReadWriteOperate::UnicodeToAnsi(WCHAR* lpString,char *szAnsi)
// { 
// 	size_t len = wcslen(lpString)*2; 	
// 	char *buf = (char *)malloc(len);	
// 	size_t i = wcstombs_s(buf,lpString,len); 
// 		strcpy(szAnsi,buf); 	
// 	free(buf);	
//}

// void CReadWriteOperate::AnsiTounicode(LPCSTR lpString,WCHAR * lpUni)
// {
// 	PWSTR pWideCharStr;  // 指向UNICODE字符串的指针 	
// 	int nLenOfWideCharStr;  // UNICODE字符串的长度 	
// 	// 获取ANSI字符串的长度 	
// 	nLenOfWideCharStr = MultiByteToWideChar(CP_ACP, 0, lpString, -1, NULL, 0); 	
// 	pWideCharStr = (PWSTR)HeapAlloc(GetProcessHeap(), 0, nLenOfWideCharStr * sizeof(WCHAR)); 	
// 	// 转换ANSI字符串为UNICODE字符串 	
// 	MultiByteToWideChar(CP_ACP, 0, lpString, -1, pWideCharStr, nLenOfWideCharStr); 	
// 	wcscpy(lpUni,pWideCharStr);	
// 	// 释放分配的字符串	
// 	HeapFree(GetProcessHeap(), 0, pWideCharStr);	
//}

int CReadWriteOperate::ReadKey(LPTSTR strSection, LPTSTR strSectionKey, LPTSTR strValue, LPTSTR strUserFile)
{
	int ret;
	TCHAR* szbuf = new TCHAR[255];
	ret = GetPrivateProfileString(strSection,strSectionKey,NULL,szbuf,255,strUserFile);
	strValue = szbuf;
	return ret;
}

int CReadWriteOperate::WriteKey(LPTSTR strSection, LPTSTR strSectionKey, LPTSTR strValue, LPTSTR strUserFile)
{
	int ret = 0;
	ret = WritePrivateProfileString(strSection,strSectionKey,strValue,strUserFile);
	return ret;
}