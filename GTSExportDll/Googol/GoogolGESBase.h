#ifndef _GOOGOLBASE_H_V1_20170227_
#define _GOOGOLBASE_H_V1_20170227_

#include "ges.h"
#pragma comment(lib, "..\\Win32ExportDll\\Googol\\ges.lib")
class CGoogolGESBase
{
public:
	unsigned short m_uiBaseAddress;	//����ַ
	short rtn;						//����ֵ

//	CLog ErrorLog;
	CGoogolGESBase();
	~CGoogolGESBase();
};
#endif
