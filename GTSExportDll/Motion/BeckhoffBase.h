#ifndef _BECKHOFFBASE_H_
#define _BECKHOFFBASE_H_
// #include "C:\twincat\adsapi\tcadsdll\include\tcadsdef.h"
// #include "C:\twincat\adsapi\tcadsdll\include\tcadsapi.h"

class CBeckhoffBase
{
public:
	CLog beckhoffLog;
	CBeckhoffBase();
	~CBeckhoffBase();
	bool CheckDone();
	bool StopMove();
	//»ñÈ¡PLC×´Ì¬
	int AdsState();
	int AutoMode();
	int MDIMode();
	int ManualMode();
	int ReferenceMode();

	bool ReadDataFromBeckhoff(CString strPLCName,int& iData);
	bool WriteDataFromBeckhoff(CString strPLCName,int& iData);

	bool ReadDataFromBeckhoff(CString strPLCName,bool& bData);
	bool WriteDataFromBeckhoff(CString strPLCName,bool& bData);

	bool ReadDataFromBeckhoff(CString strPLCName,double& dData);
	bool WriteDataFromBeckhoff(CString strPLCName,double& dData);

	bool ReadDataFromBeckhoff(CString strPLCName,float& fData);
	bool WriteDataFromBeckhoff(CString strPLCName,float& fData);

	bool ReadDataFromBeckhoff(CString strPLCName,unsigned short& iData);
	bool WriteDataFromBeckhoff(CString strPLCName,unsigned short& dData);

	bool ReadDataFromBeckhoff(CString strPLCName,unsigned int& iData);
	bool WriteDataFromBeckhoff(CString strPLCName,unsigned int& dData);

	bool ReadDataFromBeckhoff(CString strPLCName,CString& strData);
	bool WriteDataFromBeckhoff(CString strPLCName,CString& strData);

};
#endif
