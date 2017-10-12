#include "StdAfx.h"
#include "BeckhoffBase.h"
#include "../Tool/Tool.h"
//#include "TestBeckhoff.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

#ifdef _DEBUG
#include "c:\twincat\adsapi\tcadsdll\include\tcadsdef.h"
#include "c:\twincat\adsapi\tcadsdll\include\tcadsapi.h"
#else
#include "c:\twincat\adsapi\tcadsdll\include\tcadsdef.h"
#include "c:\twincat\adsapi\tcadsdll\include\tcadsapi.h"
#endif

long      nErr, nPort; 
AmsAddr   Addr; 
PAmsAddr  pAddr = &Addr; 
ULONG     lHdlVar, nData; 
char      szVar []={".CNCSystem.Channel[1].ActState"}; 
CBeckhoffBase::CBeckhoffBase()
{
	// Open communication port on the ADS router
// 	long      nErr, nPort; 
// 	AmsAddr   Addr; 
// 	PAmsAddr  pAddr = &Addr; 
// 	ULONG     lHdlVar, nData; 
// 	char      szVar []={".CNCSystem.Channel[1].ActState"}; 

	// Open communication port on the ADS router
	nPort = AdsPortOpen();
	nErr = AdsGetLocalAddress(pAddr);
	if (nErr != 0) cerr << "Error: AdsGetLocalAddress: " << nErr << '\n';
	pAddr->port = AMSPORT_R0_PLC_RTS1;

/*
	// Get the handle of the PLC-variable <szVar> 
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar), &lHdlVar, sizeof(szVar), szVar);
	if (nErr != 0) 
		cerr << "Error: AdsSyncReadWriteReq: " << nErr << '\n';
	do 
	{ 
		// Read the value of a PLC-variable, via handle 
		nErr = AdsSyncReadReq( pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(nData), &nData ); 
		if (nErr != 0) 
			cerr << "Error: AdsSyncReadReq: " << nErr << '\n'; 
		else 
			cout << "Value: " << nData << '\n'; 
		cout.flush(); 
		if (nData > 10)
		{ 
			//set the value of the PLC variable to 0 
			nData = 0; 
			nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(nData), &nData); 
			if (nErr != 0) 
				cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
		}
	}
	while ( getch() == '\r');  // n鋍hsten Wert auslesen mit RETURN, sonst Ende

	//Release the handle of the PLC-variable
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &lHdlVar); 
	if (nErr != 0) 
		cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';

	// Close the communication port
	nErr = AdsPortClose(); 
	if (nErr != 0) 
		cerr << "Error: AdsPortClose: " << nErr << '\n';
		*/
	beckhoffLog.CreateLogFile(_T("C:\\"));
	beckhoffLog.SetModel(ALLTIME);
	CString strErrorMes;
	strErrorMes.Format(_T("Open beckhoff"));
	beckhoffLog.WriteLog(strErrorMes);
}

CBeckhoffBase::~CBeckhoffBase()
{
	// Close the communication port
	CString strEnableAxis = _T(".PLCAxisEnable");

	bool bValue = false;
	WriteDataFromBeckhoff((CString) strEnableAxis,bValue);

	int nErr  =AdsPortClose();
	if (nErr != 0)
	{
		CString strErrorMes;
		strErrorMes.Format(_T("release beckhoff error:%d"),nErr);
		beckhoffLog.WriteLog(strEnableAxis + _T(",") + strErrorMes);
		//beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
	}
}
bool CBeckhoffBase::CheckDone()
{
	beckhoffLog.WriteLog(_T("->[BegCheckDone"));
	unsigned short iMoveDone = 0;
	bool bMove = true;
	double dAxisXVel = 0;
	double dAxisYVel = 0;
	double dAxisZVel = 0;

	ReadDataFromBeckhoff((CString)".CncSystemState",iMoveDone);
	int iStateOld = iMoveDone;
	int iStateNew = iStateOld;

	int iTimeOut = 600000;
	//一直持续为状态3
	if (iStateOld == 3)
	{
		ReadDataFromBeckhoff((CString)".CncSystemState",iMoveDone);
		if (iMoveDone == 3)
		{
			bMove = false;
		}
		else
		{
			int iBegTimes = 0;
			int iBeg2 = 0;
			int iBeg3 = 0;
			int iBeg6 = 0;
			while (bMove && (iTimeOut>=0))
			{
				Sleep(20);
				iTimeOut -= 20;
				ReadDataFromBeckhoff((CString)".CncSystemState",iMoveDone);
				iStateNew = iMoveDone;
				if (iStateOld == 4 && iStateNew == 3)
				{
					Sleep(500);
					ReadDataFromBeckhoff((CString) ".AxisX_ActVelo",dAxisXVel);
					ReadDataFromBeckhoff((CString) ".AxisY_ActVelo",dAxisYVel);
					if (abs(dAxisXVel) < 0.001 && abs(dAxisYVel) < 0.001)
					{
						bMove = false;
					}
					else
					{
						beckhoffLog.WriteLog(_T("state4-3,Speed0Error"));
					}
				}
				else
				{
					if (iStateNew == 2)
					{
						iBeg2 += 20;
					}
					else if (iStateNew == 3)
					{
						iBeg3 += 20;
					}
					else if (iStateNew == 6)
					{
						iBeg6 += 20;
					}
					else if (iStateNew > 100)
					{
						CString strMes;
						strMes.Format(_T("状态值过大iStateNew:%d"),iStateNew);
						beckhoffLog.WriteLog(strMes);
					}
					else
					{
						iBeg2 = 0;
						iBeg3 = 0;
						iBeg6 = 0;
					}
				}
				if (iBeg2 >=1000 ||iBeg3 >=1000 || iBeg6 >= 3000)
				{
					CString str;
					str.Format(_T("Timeout2,3,6, %d,%d,%d"),iBeg2,iBeg3,iBeg6);
					beckhoffLog.WriteLog(str);
					bMove = false;
				}
				iStateOld = iStateNew;
			}
			if (bMove && iTimeOut<=0)
			{
				beckhoffLog.WriteLog(_T("WaitFinishTimeout"));
			}
		}
	}
	else
	{
		int iBegTimes = 0;
		int iBeg2 = 0;
		int iBeg3 = 0;
		int iBeg6 = 0;
		while (bMove && (iTimeOut>=0))
		{
			Sleep(20);
			iTimeOut -= 20;
			ReadDataFromBeckhoff((CString)".CncSystemState",iMoveDone);
			iStateNew = iMoveDone;
			if (iStateOld == 4 && iStateNew == 3)
			{
				Sleep(500);
				ReadDataFromBeckhoff((CString) ".AxisX_ActVelo",dAxisXVel);
				ReadDataFromBeckhoff((CString) ".AxisY_ActVelo",dAxisYVel);
				if (abs(dAxisXVel) < 0.001 && abs(dAxisYVel) < 0.001)
				{
					bMove = false;
				}
				else
				{
					beckhoffLog.WriteLog(_T("state4-3,Speed0Error"));
				}
			}
			else
			{
				if (iStateNew == 2)
				{
					iBeg2 += 20;
				}
				else if (iStateNew == 3)
				{
					iBeg3 += 20;
				}
				else if (iStateNew == 6)
				{
					iBeg6 += 20;
				}
				else if (iStateNew > 100)
				{
					CString strMes;
					strMes.Format(_T("状态值过大iStateNew:%d"),iStateNew);
					beckhoffLog.WriteLog(strMes);
				}
				else
				{
					iBeg2 = 0;
					iBeg3 = 0;
					iBeg6 = 0;
				}
			}
			if (iBeg2 >=1000 ||iBeg3 >=1000 || iBeg6 >= 3000)
			{
				CString str;
				str.Format(_T("Timeout2,3,6, %d,%d,%d"),iBeg2,iBeg3,iBeg6);
				beckhoffLog.WriteLog(str);
				bMove = false;
			}
			iStateOld = iStateNew;
		}
		if (bMove && iTimeOut<=0)
		{
			beckhoffLog.WriteLog(_T("WaitFinishTimeout"));
		}
	}
	ReadDataFromBeckhoff((CString)".CncSystemState",iMoveDone);
	CString strMes;
	strMes.Format(_T("%d"),iMoveDone);
	beckhoffLog.WriteLog(strMes);
	beckhoffLog.WriteLog(_T("->]EndCheckDone"));
	return !bMove;
}

bool CBeckhoffBase::ReadDataFromBeckhoff(CString strPLCName,int& iData)
{
	char*      szVar = CTool::UnicodeToAnsi(((LPCTSTR)strPLCName));
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar),
		&lHdlVar, strPLCName.GetLength(), szVar);

	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//AfxMessageBox(strErrorMes);
		//return false;
	}
	nErr = AdsSyncReadReq( pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(int), &iData); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &lHdlVar); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReqRelease:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	return true;
}
bool CBeckhoffBase::WriteDataFromBeckhoff(CString strPLCName,int& iData)
{
	char*      szVar = CTool::UnicodeToAnsi(((LPCTSTR)strPLCName));
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar),
		&lHdlVar, strPLCName.GetLength(), szVar);

	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	ULONG len = sizeof(int);
	ULONG lenData = iData;
// 	CString strData;
// 	strData.Format(_T("%d"),iData);
// 	char* pData = CTool::UnicodeToAnsi((LPCTSTR)strData);
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(int), &iData); 
	if (nErr != 0)
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &lHdlVar); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReqRelease:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	return true;
}


bool CBeckhoffBase::ReadDataFromBeckhoff(CString  strPLCName,double& dData)
{
	char*      szVar = CTool::UnicodeToAnsi(((LPCTSTR)strPLCName));
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar),
		&lHdlVar, strPLCName.GetLength(), szVar);

	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncReadReq( pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(double), &dData); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &lHdlVar); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReqRelease:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	return true;
}
bool CBeckhoffBase::WriteDataFromBeckhoff(CString strPLCName,double& dData)
{
	char*      szVar = CTool::UnicodeToAnsi(((LPCTSTR)strPLCName));
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar),
		&lHdlVar, strPLCName.GetLength(), szVar);

	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	int sizeofdouble = sizeof(double);
	if (dData == 100)
	{
		sizeofdouble = 16;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeofdouble, &dData); 
	if (nErr != 0)
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &lHdlVar); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReqRelease:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	return true;
}

bool CBeckhoffBase::ReadDataFromBeckhoff(CString strPLCName,float& fData)
{
	char*      szVar = CTool::UnicodeToAnsi(((LPCTSTR)strPLCName));
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar),
		&lHdlVar, strPLCName.GetLength(), szVar);

	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncReadReq( pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(float), &fData); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &lHdlVar); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReqRelease:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	return true;
}

bool CBeckhoffBase::WriteDataFromBeckhoff(CString strPLCName,float& fData)
{
	char*      szVar = CTool::UnicodeToAnsi(((LPCTSTR)strPLCName));
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar),
		&lHdlVar, strPLCName.GetLength(), szVar);

	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(float), &fData); 
	if (nErr != 0)
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &lHdlVar); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReqRelease:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	return true;
}


bool CBeckhoffBase::ReadDataFromBeckhoff(CString strPLCName,CString& strData)
{
	char*      szVar = CTool::UnicodeToAnsi(((LPCTSTR)strPLCName));
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar),
		&lHdlVar, strPLCName.GetLength(), szVar);
	char rData[255];
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncReadReq( pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, 255, rData); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &lHdlVar); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error:AdsSyncWriteReqRelease:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	strData = rData;
	return true;
}
bool CBeckhoffBase::WriteDataFromBeckhoff(CString strPLCName,CString& strData)
{
	char*      szVar = CTool::UnicodeToAnsi(((LPCTSTR)strPLCName));
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar),
		&lHdlVar, strPLCName.GetLength(), szVar);
	char* pWData = CTool::UnicodeToAnsi((LPCTSTR)strData);
	char* pChar1024 = new char[1024];
	int iLen = strData.GetLength();	
	for (int i=0; i<1024; i++)
	{
		if (i<iLen)
		{
			pChar1024[i] = pWData[i];
		}
		else
		{
			pChar1024[i] = 0;
		}
		
	}
	iLen = 1024;
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));

		CString strLen;
		strLen.Format(_T("%sLen%d"),strData,strData.GetLength());
		beckhoffLog.WriteLog(strLen);
		strLen.Format(_T("CharLen%d"),iLen);
		beckhoffLog.WriteLog(strLen);
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, iLen, pChar1024); 
	if (nErr != 0)
	{
		CString strErrorMes;
		nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, iLen+1, pWData); 
		strErrorMes.Format(_T("Error: AdsSyncWriteReq1:%d"),nErr);
		nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, iLen+2, pWData); 
		strErrorMes.Format(_T("Error: AdsSyncWriteReq2:%d"),nErr);
		nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, iLen+3, pWData); 
		strErrorMes.Format(_T("Error: AdsSyncWriteReq3:%d"),nErr);
		nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, iLen+4, pWData); 
		strErrorMes.Format(_T("Error: AdsSyncWriteReq4:%d"),nErr);
		nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, iLen+5, pWData); 
		strErrorMes.Format(_T("Error: AdsSyncWriteReq5:%d"),nErr);
		nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, iLen+6, pWData); 
		strErrorMes.Format(_T("Error: AdsSyncWriteReq6:%d"),nErr);
		nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, iLen+7, pWData); 
		strErrorMes.Format(_T("Error: AdsSyncWriteReq7:%d"),nErr);
		nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, iLen+8, pWData); 
		strErrorMes.Format(_T("Error: AdsSyncWriteReq8:%d"),nErr);
		nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, iLen+9, pWData); 
		strErrorMes.Format(_T("Error: AdsSyncWriteReq9:%d"),nErr);
		nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, iLen+10, pWData); 
		strErrorMes.Format(_T("Error: AdsSyncWriteReq10:%d"),nErr);
		nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, iLen+11, pWData); 
		
		strErrorMes.Format(_T("Error: AdsSyncWriteReq11:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		////return false;

		CString strLen;
		strLen.Format(_T("%sLen%d"),strData,strData.GetLength());
		beckhoffLog.WriteLog(strLen);
		strLen.Format(_T("CharLen%d"),iLen);
		beckhoffLog.WriteLog(strLen);
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &lHdlVar); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReqRelease:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));

		CString strLen;
		strLen.Format(_T("%sLen%d"),strData,strData.GetLength());
		beckhoffLog.WriteLog(strLen);
		strLen.Format(_T("CharLen%d"),iLen);
		beckhoffLog.WriteLog(strLen);
		////return false;
	}
	return true;
}



bool CBeckhoffBase::ReadDataFromBeckhoff(CString strPLCName,bool& bData)
{
	char*      szVar = CTool::UnicodeToAnsi(((LPCTSTR)strPLCName));
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar),
		&lHdlVar, strPLCName.GetLength(), szVar);
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncReadReq( pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(bData), &bData); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &lHdlVar); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReqRelease:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		///return false;
	}
	return true;
}
bool CBeckhoffBase::WriteDataFromBeckhoff(CString strPLCName,bool& bData)
{
	char*      szVar = CTool::UnicodeToAnsi(((LPCTSTR)strPLCName));
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar),
		&lHdlVar, strPLCName.GetLength(), szVar);
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		////return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(bData), &bData); 
	if (nErr != 0)
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &lHdlVar); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReqRelease:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	return true;
}

bool CBeckhoffBase::StopMove()
{
	bool bValue = true;
	return WriteDataFromBeckhoff((CString)_T(".PLCMachineMode[1].Stop"),bValue);
//	return WriteDataFromBeckhoff((CString)_T(".PLCMachineMode[1].Reset"),bValue);
}

bool CBeckhoffBase::ReadDataFromBeckhoff(CString strPLCName,unsigned short& usData)
{
	char*      szVar = CTool::UnicodeToAnsi(((LPCTSTR)strPLCName));
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar),
		&lHdlVar, strPLCName.GetLength(), szVar);
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncReadReq( pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(usData), &usData); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &lHdlVar); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReqRelease:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	return true;
}
bool CBeckhoffBase::WriteDataFromBeckhoff(CString strPLCName,unsigned short& usData)
{
	char*      szVar = CTool::UnicodeToAnsi(((LPCTSTR)strPLCName));
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar),
		&lHdlVar, strPLCName.GetLength(), szVar);
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(usData), &usData); 
	if (nErr != 0)
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &lHdlVar); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReqRelease:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	return true;
}

bool CBeckhoffBase::ReadDataFromBeckhoff(CString strPLCName,unsigned int& usData)
{
	char*      szVar = CTool::UnicodeToAnsi(((LPCTSTR)strPLCName));
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar),
		&lHdlVar, strPLCName.GetLength(), szVar);
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncReadReq( pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(usData), &usData); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &lHdlVar); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReqRelease:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	return true;
}
bool CBeckhoffBase::WriteDataFromBeckhoff(CString strPLCName,unsigned int& usData)
{
	char*      szVar = CTool::UnicodeToAnsi(((LPCTSTR)strPLCName));
	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar),
		&lHdlVar, strPLCName.GetLength(), szVar);
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncReadWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(usData), &usData); 
	if (nErr != 0)
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReq:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &lHdlVar); 
	if (nErr != 0) 
	{
		CString strErrorMes;
		strErrorMes.Format(_T("Error: AdsSyncWriteReqRelease:%d"),nErr);
		beckhoffLog.WriteLog(strPLCName + _T(",") + strErrorMes+ _T(","));
		//return false;
	}
	return true;
}
int CBeckhoffBase::AutoMode()
{
	bool bValue = false;
	unsigned short iActMode = 0;
	ReadDataFromBeckhoff((CString)(_T(".CncSystemSelectedMode")),iActMode);
	if (iActMode != 2)
	{
		bValue = true;
		WriteDataFromBeckhoff((CString)(_T(".PLCMachineMode[1].Automatic")),bValue);
		ReadDataFromBeckhoff((CString)(_T(".PLCMachineMode[1].Automatic")),iActMode);
		beckhoffLog.WriteLog(_T(".PLCMachineMode[1].Automatic,True"));
		
	}
	WriteDataFromBeckhoff((CString)(_T(".PLCMachineMode[1].ProgramName")),(CString)(_T("C:\\AutoNC.nc")));
	Sleep(500);
	return 0;
}
int CBeckhoffBase::ManualMode()
{
	bool bValue = false;
	unsigned short iActMode = 0;
	ReadDataFromBeckhoff((CString)(_T(".CncSystemSelectedMode")),iActMode);
	if (iActMode != 4)
	{
		bValue = true;
		WriteDataFromBeckhoff((CString)(_T(".PLCMachineMode[1].Manual")),bValue);
		beckhoffLog.WriteLog(_T(".PLCMachineMode[1].Manual,True"));
	}
	return 0;
}

int CBeckhoffBase::MDIMode()
{
	bool bValue = false;
	unsigned short iActMode = 0;
	ReadDataFromBeckhoff((CString)(_T(".CncSystemSelectedMode")),iActMode);
	if (iActMode != 3)
	{
		bValue = true;
		WriteDataFromBeckhoff((CString)(_T(".PLCMachineMode[1].MDI")),bValue);
		beckhoffLog.WriteLog(_T(".PLCMachineMode[1].MDI,True"));
	}
	Sleep(500);
	return 0;
}

int CBeckhoffBase::ReferenceMode()
{
	bool bValue = false;
	unsigned short iActMode = 0;
	ReadDataFromBeckhoff((CString)(_T(".CncSystemSelectedMode")),iActMode);
	if (iActMode != 5)
	{
		bValue = true;
		WriteDataFromBeckhoff((CString)(_T(".PLCMachineMode[1].Reference")),bValue);
		beckhoffLog.WriteLog(_T(".PLCMachineMode[1].Reference,True"));
		ReadDataFromBeckhoff((CString)(_T(".CncSystemSelectedMode")),iActMode);
	}
	Sleep(500);
	return 0;
}

int CBeckhoffBase::AdsState()
{
	USHORT   nAdsState;
	USHORT	 nDeviceState;
	int iRet = AdsSyncReadStateReq(pAddr, &nAdsState, &nDeviceState);
	return 0;
}