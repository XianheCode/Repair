#ifndef _GOOGOLBASE_H_V1_20170227_
#define _GOOGOLBASE_H_V1_20170227_

#include "gts.h"
#pragma comment(lib, ".\\Googol\\gts.lib")
class CGoogolGTSBase
{
public:
	unsigned short m_uiBaseAddress;	//����ַ
	short rtn;						//����ֵ

//	CLog ErrorLog;
	CGoogolGTSBase();
	~CGoogolGTSBase();
};
#endif
