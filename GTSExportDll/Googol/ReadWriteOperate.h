// ReadWriteOperate.h: interface for the CReadWriteOperate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READWRITEOPERATE_H__CB345D20_5F97_48F4_98CC_E5F764E87BC4__INCLUDED_)
#define AFX_READWRITEOPERATE_H__CB345D20_5F97_48F4_98CC_E5F764E87BC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../stdafx.h"

#include <stdlib.h>

class CReadWriteOperate  
{
public:
	TCHAR m_pathAddress[255];
	CReadWriteOperate();
	CReadWriteOperate(const TCHAR* pArray);
	virtual ~CReadWriteOperate();
	int GetAppPath(LPTSTR pathAddress);
	int ReadKey(LPTSTR strSection, LPTSTR strSectionKey, LPTSTR &strValue);
	int ReadKey(LPTSTR strSection, LPTSTR strSectionKey , int &iValue);
	int ReadKey(LPTSTR strSection, LPTSTR strSectionKey , short &sValue);
	int ReadKey(LPTSTR strSection, LPTSTR strSectionKey , long &lValue);
	int ReadKey(LPTSTR strSection, LPTSTR strSectionKey , float &fValue);
	int ReadKey(LPTSTR strSection, LPTSTR strSectionKey , double &dValue);
	int ReadKey(LPTSTR strSection, LPTSTR strSectionKey , bool& bValue);

	int WriteKey(LPTSTR strSection, LPTSTR strSectionKey , LPTSTR value );
	int WriteKey(LPTSTR strSection, LPTSTR strSectionKey , float fvalue );
	int WriteKey(LPTSTR strSection, LPTSTR strSectionKey , int  ivalue );
	int WriteKey(LPTSTR strSection, LPTSTR strSectionKey , short sValue);
	int WriteKey(LPTSTR strSection, LPTSTR strSectionKey , long lValue);
	int WriteKey(LPTSTR strSection, LPTSTR strSectionKey , double dvalue );
	int WriteKey(LPTSTR strSection, LPTSTR strSectionKey , bool& bValue );


	//单独设置配置文件
	int ReadKey(LPTSTR strSection, LPTSTR strSectionKey, LPTSTR strValue, LPTSTR strUserFile);
	int WriteKey(LPTSTR strSection, LPTSTR strSectionKey, LPTSTR strValue, LPTSTR strUserFile);

// 	void UnicodeToAnsi(WCHAR* lpString,char *szAnsi);
// 	void AnsiTounicode(LPCSTR lpString,WCHAR * lpUni);
};

#endif // !defined(AFX_READWRITEOPERATE_H__CB345D20_5F97_48F4_98CC_E5F764E87BC4__INCLUDED_)
