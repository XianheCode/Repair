// MotionInterface.cpp: implementation of the CMotionGESInterface class.
/*
 * CopyRight (c) 2017
 * All Rights reserved
 *
 * File Name		: MotionInterface.h
 * File ID			: None
 * Sumary			: For All Motion
 *
 * Current Version	: 1.0.0
 * Author			: Jackie Wu
 * Finish Time		: 2017-2-27
 * Last Modify Time : 2017-2-27
*/
//#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include "MotionGESInterface.h"
#include "ReadWriteOperate.h"
#include <tchar.h>
#include <string>
#include <ShellApi.h>



using namespace std;

CMotionGESInterface::CMotionGESInterface()
{
	m_bInit = false;
	m_bHoming = false;
	m_bHomeReady = false;
	m_bInitHomeReady = false;
	m_pCMotionGESInterface = nullptr;
	//////////////////////////////////////////////////////////////////////////
	// 代码初始化运动
	for(int i=COORDI_AXISX; i < 5; i++)
	{
		m_moveData.m_pCurPos[i] = 0;
		m_moveData.m_bEnableAxis[i] = true;
		m_moveData.m_iAxisReverse[i] = 1;
		m_moveData.m_backOffset[i]= 0;
		m_moveData.m_iOriginDirection[i]= -1;

		if (m_moveData.m_bEnableAxis[i])
		{
			if(i == 4)
			{
				m_moveData.m_EnableAxiss[i] = 6;//划刀改为轴6
			}
			else
			{
				m_moveData.m_EnableAxiss[i] = i+1;
			}
			
		}
// 		m_dAxisMoveAcc[i]= 0;
// 		m_dAxisMoveDec[i]= 0;
// 		m_dAxisMoveBegSpeed[i]= 0;
// 		m_dAxisMoveSpeed[i]= 0;
// 		m_dAxisEmptyMoveBegSpeed[i]= 0;
// 		m_dAxisEmptyMoveSpeed[i]= 0;

		if (i == COORDI_AXISX  || i==COORDI_AXISY)
		{
			m_moveData.m_lPPM[i] = 2000;

			m_moveData.m_dBegSpeedMoveBig[i]= 20;
			m_moveData.m_dSpeedMoveBig[i]= 50;
			m_moveData.m_dAccSpeedMoveBig[i]= 200;
			m_moveData.m_dDecSpeedMoveBig[i]= 200;
			m_moveData.m_dConSpeedMoveBig[i]= 50;

			m_moveData.m_dBegSpeedMoveMiddle[i]= 10;
			m_moveData.m_dSpeedMoveMiddle[i]= 30;
			m_moveData.m_dAccSpeedMoveMiddle[i]= 100;
			m_moveData.m_dDecSpeedMoveMiddle[i]= 100;
			m_moveData.m_dConSpeedMoveMiddle[i]= 30;

			m_moveData.m_dBegSpeedMoveMin[i]= 5;
			m_moveData.m_dSpeedMoveMin[i]= 10;
			m_moveData.m_dAccSpeedMoveMin[i]= 100;
			m_moveData.m_dDecSpeedMoveMin[i]= 100;
			m_moveData.m_dConSpeedMoveMin[i]= 10;

			m_moveData.m_dBegSpeedGoOrig[i]= 10;
			m_moveData.m_dSpeedGoOrig[i]= 30;
			m_moveData.m_dAccSpeedGoOrig[i]= 100;
			m_moveData.m_dDecSpeedGoOrig[i]= 100;
			m_moveData.m_dConSpeedGoOrig[i]= 30;
		}
		else if (i == COORDI_AXISZ)
		{
			//test
			m_moveData.m_lPPM[i] = 10000;

			m_moveData.m_dBegSpeedMoveBig[i]= 20;
			m_moveData.m_dSpeedMoveBig[i]= 50;
			m_moveData.m_dAccSpeedMoveBig[i]= 200;
			m_moveData.m_dDecSpeedMoveBig[i]= 200;
			m_moveData.m_dConSpeedMoveBig[i]= 50;

			m_moveData.m_dBegSpeedMoveMiddle[i]= 5;
			m_moveData.m_dSpeedMoveMiddle[i]= 10;
			m_moveData.m_dAccSpeedMoveMiddle[i]= 100;
			m_moveData.m_dDecSpeedMoveMiddle[i]= 100;
			m_moveData.m_dConSpeedMoveMiddle[i]= 30;

			m_moveData.m_dBegSpeedMoveMin[i]= 1;
			m_moveData.m_dSpeedMoveMin[i]= 10;
			m_moveData.m_dAccSpeedMoveMin[i]= 100;
			m_moveData.m_dDecSpeedMoveMin[i]= 100;
			m_moveData.m_dConSpeedMoveMin[i]= 10;

			m_moveData.m_dBegSpeedGoOrig[i]= 5;
			m_moveData.m_dSpeedGoOrig[i]= 10;
			m_moveData.m_dAccSpeedGoOrig[i]= 100;
			m_moveData.m_dDecSpeedGoOrig[i]= 100;
			m_moveData.m_dConSpeedGoOrig[i]= 30;
		}
		else if (i == COORDI_AXISC)
		{
			//test
			m_moveData.m_lPPM[i] = 900;

			m_moveData.m_dBegSpeedMoveBig[i]= 20;
			m_moveData.m_dSpeedMoveBig[i]= 50;
			m_moveData.m_dAccSpeedMoveBig[i]= 200;
			m_moveData.m_dDecSpeedMoveBig[i]= 200;
			m_moveData.m_dConSpeedMoveBig[i]= 50;

			m_moveData.m_dBegSpeedMoveMiddle[i]= 10;
			m_moveData.m_dSpeedMoveMiddle[i]= 30;
			m_moveData.m_dAccSpeedMoveMiddle[i]= 100;
			m_moveData.m_dDecSpeedMoveMiddle[i]= 100;
			m_moveData.m_dConSpeedMoveMiddle[i]= 30;

			m_moveData.m_dBegSpeedMoveMin[i]= 5;
			m_moveData.m_dSpeedMoveMin[i]= 10;
			m_moveData.m_dAccSpeedMoveMin[i]= 100;
			m_moveData.m_dDecSpeedMoveMin[i]= 100;
			m_moveData.m_dConSpeedMoveMin[i]= 10;

			m_moveData.m_dBegSpeedGoOrig[i]= 10;
			m_moveData.m_dSpeedGoOrig[i]= 30;
			m_moveData.m_dAccSpeedGoOrig[i]= 100;
			m_moveData.m_dDecSpeedGoOrig[i]= 100;
			m_moveData.m_dConSpeedGoOrig[i]= 30;
		}
		else if (i == COORDI_AXISU)
		{
			//test
			m_moveData.m_lPPM[i] = 3200;
			m_moveData.m_dBegSpeedMoveBig[i]= 1;
			m_moveData.m_dSpeedMoveBig[i]= 3;
			m_moveData.m_dAccSpeedMoveBig[i]= 50;
			m_moveData.m_dDecSpeedMoveBig[i]= 50;
			m_moveData.m_dConSpeedMoveBig[i]= 3;

			m_moveData.m_dBegSpeedMoveMiddle[i]= 1;
			m_moveData.m_dSpeedMoveMiddle[i]= 3;
			m_moveData.m_dAccSpeedMoveMiddle[i]= 30;
			m_moveData.m_dDecSpeedMoveMiddle[i]= 30;
			m_moveData.m_dConSpeedMoveMiddle[i]= 3;

			m_moveData.m_dBegSpeedMoveMin[i]= 1;
			m_moveData.m_dSpeedMoveMin[i]= 3;
			m_moveData.m_dAccSpeedMoveMin[i]= 20;
			m_moveData.m_dDecSpeedMoveMin[i]= 20;
			m_moveData.m_dConSpeedMoveMin[i]= 3;

			m_moveData.m_dBegSpeedGoOrig[i]= 1;
			m_moveData.m_dSpeedGoOrig[i]= 3;
			m_moveData.m_dAccSpeedGoOrig[i]= 30;
			m_moveData.m_dDecSpeedGoOrig[i]= 30;
			m_moveData.m_dConSpeedGoOrig[i]= 3;
		}
	}

	m_moveData.m_dXYMoveAcc = 200;
	m_moveData.m_dXYMoveDec = 200;
	m_moveData.m_dXYMoveCornerAcc = 200;
	m_moveData.m_dXYMoveBegSpeed = 5;
	m_moveData.m_dXYMoveSpeed = 50;

	if (!m_bInit)
	{
		m_ControlGESInterface = new CGoogolGESControl();
		m_pCMotionGESInterface = m_ControlGESInterface;
		m_bInit = true;
	}
	
}

CMotionGESInterface::~CMotionGESInterface()
{
	if (m_pCMotionGESInterface != nullptr)
	{
		delete m_pCMotionGESInterface;
		m_pCMotionGESInterface = nullptr;
	}
}

int CMotionGESInterface::Init(int iCardNum)
{
	ReadConfigFile();

	double pdLimitDirction[8];
	//建立坐标系和物理轴的映射关系
	m_moveData.m_AxisNum = 0;
	for (int i=0; i<MAX_AXISNUM; i++)
	{
		if (m_moveData.m_bEnableAxis[i])
		{
			piEnableAxis[m_moveData.m_AxisNum] = m_moveData.m_EnableAxiss[i];
			pdLimitDirction[m_moveData.m_AxisNum] = m_moveData.m_iLimitDirection[i];
			m_moveData.m_AxisNum ++;
		}
	}

	return m_ControlGESInterface->Init(piEnableAxis, m_moveData.m_AxisNum, &iCardNum, pdLimitDirction);
}

int CMotionGESInterface::Close()
{
	m_ControlGESInterface->Close();
	//return WriteConfigFile();
	return 0;
}

int CMotionGESInterface::GoOrigin()
{
	m_bHoming = true;
	int iRet = 0;
	int* iDirect = new int[m_moveData.m_AxisNum];
	int* orgmove = new int[m_moveData.m_AxisNum];
	int* goOrgAxis = new int[m_moveData.m_AxisNum];
	double* dHighSpeed = new double[m_moveData.m_AxisNum];
	double* dLowSpeed = new double[m_moveData.m_AxisNum];
	double* dAcc = new double[m_moveData.m_AxisNum];
	double* dDec = new double[m_moveData.m_AxisNum];
	int iCount = 0;
	for (int i = COORDI_AXISX; i<MAX_AXISNUM; i++)
	{
		if (m_moveData.m_bEnableAxis[i])
		{
			iDirect[iCount] = m_moveData.m_iOriginDirection[i];
 			goOrgAxis[iCount] = m_moveData.m_EnableAxiss[i];
			orgmove[iCount] = 5 * m_moveData.m_lPPM[i];

			dHighSpeed[iCount] = m_moveData.m_dSpeedGoOrig[i] * m_moveData.m_lPPM[i]/1000;
			dLowSpeed[iCount] = m_moveData.m_dBegSpeedGoOrig[i] * m_moveData.m_lPPM[i]/1000;
			dAcc[iCount] = m_moveData.m_dAccSpeedGoOrig[i] * m_moveData.m_lPPM[i]/1000000;
			dDec[iCount] = m_moveData.m_dDecSpeedGoOrig[i] * m_moveData.m_lPPM[i]/1000000;
			iCount ++;
		}
	}

	//依次回零
	for (int i = 0; i < iCount; i++)
	{
		int iAxisNum = goOrgAxis[i];
		int iDirectO = iDirect[i];
		double dLowV = dLowSpeed[i];
		double dHighV = dHighSpeed[i];
		double dHomeAcc = dAcc[i];
		double dHomeDec = dDec[i];
		int iorgmove = orgmove[i];
		iRet = m_ControlGESInterface->SetSpeed(dHighV, dLowV, dHomeAcc, dHomeDec);
		iRet = m_ControlGESInterface->GoOriginOne(iAxisNum, iDirectO, orgmove, m_moveData.m_bGoOrgStyle);
		if (iRet != 0)
		{
			break;
		}
	}

	m_bHoming = false;
	if (iRet ==0)
	{
		m_bHomeReady = true;
	}

	delete[] goOrgAxis;
	delete[] dHighSpeed;
	delete[] dLowSpeed;
	delete[] dAcc;
	delete[] iDirect;
	delete[] orgmove;
	goOrgAxis = nullptr;
	dHighSpeed = nullptr;
	dLowSpeed = nullptr;
	dAcc = nullptr;
	orgmove = nullptr;
	iDirect = nullptr;
	return iRet;
}

int CMotionGESInterface::CheckAlreadyOrg()
{
	/*
	if (!m_bHomeReady && !m_bInitHomeReady && !m_bHoming)
	{
		//未回参过，未回参过未初始化过软件暂存坐标值，从卡里面读取所有坐标值初始化。
		double dPos = 0;
		for(int m=COORDI_AXISX; m<m_moveData.m_AxisNum; m++)
		{
			if (GetPosCur(m,&dPos) == 0)
			{
				SetPos(m,dPos);
				m_bInitHomeReady = true;
			}
			else
			{
				m_bInitHomeReady = false;
				break;
			}
		}
		if (!m_bInitHomeReady)
		{
			return InitHomeReadyError;
		}
	}
	*/
	return 0;
}

int CMotionGESInterface::SetPtoPSpeed(int iType, int* iEnableCoor, int iLen, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec)
{
	m_bStop = false;
	int iRet = 0;
	// 	iRet = CheckAlreadyOrg();
	// 	if (iRet !=0)
	// 	{
	// 		return iRet;
	// 	}
	int iAxisNO = iLen;
	if (iAxisNO > m_moveData.m_AxisNum)
	{
		//AfxMessageBox(("运动中轴数大于软件设置使能轴数"));
		return  -111;//USEAXISNOTMATCHENABLEAXIS;
	}

	int* iEnableAxis = new int[iAxisNO];
	for (int i = 0; i < iAxisNO; i++)
	{
		if (iType == 0)
		{
			m_moveData.m_dAxisMoveSpeed[iEnableCoor[i]]    = m_moveData.m_dSpeedMoveMin[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveBegSpeed[iEnableCoor[i]] = m_moveData.m_dBegSpeedMoveMin[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveAcc[iEnableCoor[i]] = m_moveData.m_dAccSpeedMoveMin[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveDec[iEnableCoor[i]] = m_moveData.m_dDecSpeedMoveMin[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
		}
		else if (iType == 1)
		{
			m_moveData.m_dAxisMoveSpeed[iEnableCoor[i]] = m_moveData.m_dSpeedMoveMiddle[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveBegSpeed[iEnableCoor[i]] = m_moveData.m_dBegSpeedMoveMiddle[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveAcc[iEnableCoor[i]] = m_moveData.m_dAccSpeedMoveMiddle[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveDec[iEnableCoor[i]] = m_moveData.m_dDecSpeedMoveMiddle[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
		}
		else if (iType == 2)
		{
			m_moveData.m_dAxisMoveSpeed[iEnableCoor[i]] = m_moveData.m_dSpeedMoveBig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveBegSpeed[iEnableCoor[i]] = m_moveData.m_dBegSpeedMoveBig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveAcc[iEnableCoor[i]] = m_moveData.m_dAccSpeedMoveBig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveDec[iEnableCoor[i]] = m_moveData.m_dDecSpeedMoveBig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
		}
		else if (iType == 3)
		{
			m_moveData.m_dAxisMoveSpeed[iEnableCoor[i]] = m_moveData.m_dSpeedGoOrig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveBegSpeed[iEnableCoor[i]] = m_moveData.m_dBegSpeedGoOrig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveAcc[iEnableCoor[i]] = m_moveData.m_dAccSpeedGoOrig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveDec[iEnableCoor[i]] = m_moveData.m_dDecSpeedGoOrig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
		}
		else if (iType == 4)
		{
			m_moveData.m_dAxisMoveSpeed[iEnableCoor[i]] = dHighSpeed[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveBegSpeed[iEnableCoor[i]] = dLowSpeed[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveAcc[iEnableCoor[i]] = dAcc[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveDec[iEnableCoor[i]] = dDec[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
		}
	}
	return iRet;
}

/*
	iType: 0-低速 1-中速  2-高速  3-回零 4-自定义速度
*/
int CMotionGESInterface::SetStepPtoPSpeed(int iType, int* iEnableCoor, int iLen, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec)
{
	m_bStop = false;
	int iRet = 0;
	// 	iRet = CheckAlreadyOrg();
	// 	if (iRet !=0)
	// 	{
	// 		return iRet;
	// 	}
	int iAxisNO = iLen;
	if (iAxisNO > m_moveData.m_AxisNum)
	{
		//AfxMessageBox(("运动中轴数大于软件设置使能轴数"));
		return  -111;//USEAXISNOTMATCHENABLEAXIS;
	}
	int* iEnableAxis = new int[iAxisNO];
	for (int i = 0; i < iAxisNO; i++)
	{
		if (iType == 0)
		{
			m_moveData.m_dAxisMoveSpeed[iEnableCoor[i]] = m_moveData.m_dSpeedMoveMin[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveBegSpeed[iEnableCoor[i]] = m_moveData.m_dBegSpeedMoveMin[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveAcc[iEnableCoor[i]] = m_moveData.m_dAccSpeedMoveMin[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveDec[iEnableCoor[i]] = m_moveData.m_dDecSpeedMoveMin[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
		}
		else if (iType == 1)
		{
			m_moveData.m_dAxisMoveSpeed[iEnableCoor[i]] = m_moveData.m_dSpeedMoveMiddle[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveBegSpeed[iEnableCoor[i]] = m_moveData.m_dBegSpeedMoveMiddle[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveAcc[iEnableCoor[i]] = m_moveData.m_dAccSpeedMoveMiddle[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveDec[iEnableCoor[i]] = m_moveData.m_dDecSpeedMoveMiddle[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
		}
		else if (iType == 2)
		{
			m_moveData.m_dAxisMoveSpeed[iEnableCoor[i]] = m_moveData.m_dSpeedMoveBig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveBegSpeed[iEnableCoor[i]] = m_moveData.m_dBegSpeedMoveBig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveAcc[iEnableCoor[i]] = m_moveData.m_dAccSpeedMoveBig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveDec[iEnableCoor[i]] = m_moveData.m_dDecSpeedMoveBig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
		}
		else if (iType == 3)
		{
			m_moveData.m_dAxisMoveSpeed[iEnableCoor[i]] = m_moveData.m_dSpeedGoOrig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveBegSpeed[iEnableCoor[i]] = m_moveData.m_dBegSpeedGoOrig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveAcc[iEnableCoor[i]] = m_moveData.m_dAccSpeedGoOrig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveDec[iEnableCoor[i]] = m_moveData.m_dDecSpeedGoOrig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
		}
		else if (iType == 4)
		{
			m_moveData.m_dAxisMoveSpeed[iEnableCoor[i]] = dHighSpeed[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveBegSpeed[iEnableCoor[i]] = dLowSpeed[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveAcc[iEnableCoor[i]] = dAcc[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveDec[iEnableCoor[i]] = dDec[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
		}
	}
	return iRet;
}


int CMotionGESInterface::SetJogSpeed(int iType, int* iEnableCoor, int iLen, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec)
{
	m_bStop = false;
	int iRet = 0;
// 	iRet = CheckAlreadyOrg();
// 	if (iRet !=0)
// 	{
// 		return iRet;
// 	}
	int iAxisNO = iLen;
	if (iAxisNO > m_moveData.m_AxisNum)
	{
		//AfxMessageBox(("运动中轴数大于软件设置使能轴数"));
		return  -111;//USEAXISNOTMATCHENABLEAXIS;
	}

	int* iEnableAxis = new int[iAxisNO];
	for (int i = 0; i < iAxisNO; i++)
	{
		if (iType == 0)
		{
			m_moveData.m_dAxisMoveSpeed[iEnableCoor[i]] = m_moveData.m_dSpeedMoveMin[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveBegSpeed[iEnableCoor[i]] = m_moveData.m_dBegSpeedMoveMin[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveAcc[iEnableCoor[i]] = m_moveData.m_dAccSpeedMoveMin[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveDec[iEnableCoor[i]] = m_moveData.m_dDecSpeedMoveMin[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
		}
		else if (iType == 1)
		{
			m_moveData.m_dAxisMoveSpeed[iEnableCoor[i]] = m_moveData.m_dSpeedMoveMiddle[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveBegSpeed[iEnableCoor[i]] = m_moveData.m_dBegSpeedMoveMiddle[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveAcc[iEnableCoor[i]] = m_moveData.m_dAccSpeedMoveMiddle[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveDec[iEnableCoor[i]] = m_moveData.m_dDecSpeedMoveMiddle[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
		}
		else if (iType == 2)
		{
			m_moveData.m_dAxisMoveSpeed[iEnableCoor[i]] = m_moveData.m_dSpeedMoveBig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveBegSpeed[iEnableCoor[i]] = m_moveData.m_dBegSpeedMoveBig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveAcc[iEnableCoor[i]] = m_moveData.m_dAccSpeedMoveBig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveDec[iEnableCoor[i]] = m_moveData.m_dDecSpeedMoveBig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
		}
		else if (iType == 3)
		{
			m_moveData.m_dAxisMoveSpeed[iEnableCoor[i]] = m_moveData.m_dSpeedGoOrig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveBegSpeed[iEnableCoor[i]] = m_moveData.m_dBegSpeedGoOrig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveAcc[iEnableCoor[i]] = m_moveData.m_dAccSpeedGoOrig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveDec[iEnableCoor[i]] = m_moveData.m_dDecSpeedGoOrig[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
		}
		else if (iType == 4)
		{
			m_moveData.m_dAxisMoveSpeed[iEnableCoor[i]] = dHighSpeed[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveBegSpeed[iEnableCoor[i]] = dLowSpeed[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveAcc[iEnableCoor[i]] = dAcc[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
			m_moveData.m_dAxisMoveDec[iEnableCoor[i]] = dDec[iEnableCoor[i]] * (m_moveData.m_lPPM[iEnableCoor[i]]);
		}
	}
	return iRet;
}

//设置所有运动的速度
//iEnableCoor: 使能的XYZ序列号
//iMoveType: 0-自动 1-手动(只能单轴)
//iHandMoveSpeedType ：在手动模式下 0-高速  1-中速  2-低速 3-回零
int CMotionGESInterface::SetSpeed(int* iEnableCoor, int iLen, int iMoveType, int iHandMoveSpeedType)
{
	double dSLowV;
	double dSHighV;
	double dSAcc;
	double dSDec;

	double dPPM = m_moveData.m_lPPM[iEnableCoor[0]];
	if (iMoveType==0)	//自动
	{
		if (iLen == 1)    //单轴运动参数
		{
			dSLowV = m_moveData.m_dAxisMoveBegSpeed[iEnableCoor[0]] * dPPM/1000;
			dSHighV = m_moveData.m_dAxisMoveSpeed[iEnableCoor[0]] * dPPM/1000;
			dSAcc = m_moveData.m_dAxisMoveAcc[iEnableCoor[0]] * dPPM/1000000;
			dSDec = m_moveData.m_dAxisMoveDec[iEnableCoor[0]] * dPPM/1000000;
		}
		else if (iLen > 1)   //XY插补参数
		{		
			dSLowV = m_moveData.m_dXYMoveBegSpeed*dPPM/1000;
			dSHighV = m_moveData.m_dXYMoveSpeed*dPPM/1000;
			dSAcc = m_moveData.m_dXYMoveAcc*dPPM/1000000;
			dSDec = m_moveData.m_dXYMoveDec*dPPM/1000000;
		}
		else
		{
			return -1;
		}
	}
	else    //手动
	{
		if (iHandMoveSpeedType == 0)	//高速
		{
			dSLowV = m_moveData.m_dBegSpeedMoveBig[iEnableCoor[0]] * dPPM/1000;
			dSHighV = m_moveData.m_dSpeedMoveBig[iEnableCoor[0]] * dPPM/1000;
			dSAcc = m_moveData.m_dAccSpeedMoveBig[iEnableCoor[0]] * dPPM/1000000;
			dSDec = m_moveData.m_dDecSpeedMoveBig[iEnableCoor[0]] * dPPM/1000000;
		}
		else if (iHandMoveSpeedType == 1)	//中速
		{
			dSLowV = m_moveData.m_dBegSpeedMoveMiddle[iEnableCoor[0]] * dPPM/1000;
			dSHighV = m_moveData.m_dSpeedMoveMiddle[iEnableCoor[0]] * dPPM/1000;
			dSAcc = m_moveData.m_dAccSpeedMoveMiddle[iEnableCoor[0]] * dPPM/1000000;
			dSDec = m_moveData.m_dDecSpeedMoveMiddle[iEnableCoor[0]] * dPPM/1000000;
		}
		else if (iHandMoveSpeedType == 2)	//低速
		{
			dSLowV = m_moveData.m_dBegSpeedMoveMin[iEnableCoor[0]] * dPPM/1000;
			dSHighV = m_moveData.m_dSpeedMoveMin[iEnableCoor[0]] * dPPM/1000;
			dSAcc = m_moveData.m_dAccSpeedMoveMin[iEnableCoor[0]] * dPPM/1000000;
			dSDec = m_moveData.m_dDecSpeedMoveMin[iEnableCoor[0]] * dPPM/1000000;
		}
		else if (iHandMoveSpeedType == 3)	//回零
		{
			dSLowV = m_moveData.m_dBegSpeedGoOrig[iEnableCoor[0]] * dPPM/1000;
			dSHighV = m_moveData.m_dSpeedGoOrig[iEnableCoor[0]] * dPPM/1000;
			dSAcc = m_moveData.m_dAccSpeedGoOrig[iEnableCoor[0]] * dPPM/1000000;
			dSDec = m_moveData.m_dDecSpeedGoOrig[iEnableCoor[0]] * dPPM/1000000;
		}
		else
		{
			return -1;
		}
	}
	return m_ControlGESInterface->SetSpeed(dSHighV, dSLowV, dSAcc, dSDec);
}

int PToPMove(int* iEnableCoor, double* posDes, int iLen)
{
	return 0;
}

//iMoveType: 0-自动 1-手动(只能单轴)
//iHandMoveSpeedType ：在手动模式下 0-高速  1-中速  2-低速 3-回零
int CMotionGESInterface::PToPMove(int* iEnableCoor, double* posDes, int iLen,int iMoveType,int iHandMoveSpeedType)
{
	m_bStop = false;
	int iRet = 0;

	int iAxisNO = iLen;
	if (iAxisNO > m_moveData.m_AxisNum)
	{
		//AfxMessageBox(("运动中轴数大于软件设置使能轴数"));
		return  -111;//USEAXISNOTMATCHENABLEAXIS;
	}
	
	int* iEnableAxis = new int[iLen];
	int iCount = 0;
	for (int i = 0; i<iLen; i++)
	{
		iEnableAxis[i] = m_moveData.m_EnableAxiss[iEnableCoor[i]];
	}
	//速度设置
	iRet = SetSpeed(iEnableCoor, iLen, iMoveType, iHandMoveSpeedType);
	//运动控制
	if (iRet >= 0)
	{
		for (int n=0; n<iLen; n++)
		{
			posDes[n] *= m_moveData.m_iAxisReverse[iEnableCoor[n]]
						*(m_moveData.m_lPPM[iEnableCoor[n]]);
		}

		iRet = m_ControlGESInterface->MoveTo(iEnableAxis, iLen, posDes, 2, true);
		if (m_bStop)
		{
			iRet= -222; //STOPMOVE
		}
		if (iRet >=0)
		{
			for (int k = 0; k < iAxisNO ; k++)
			{
				m_moveData.m_pCurPos[iEnableCoor[k]] = posDes[k]/m_moveData.m_iAxisReverse[iEnableCoor[k]]
														/(m_moveData.m_lPPM[iEnableCoor[k]]);
			}
		}
	}
    return iRet;
}

int CMotionGESInterface::MoveArcTo(int iAxis1, double posCenter1, int iAxis2, double posCenter2, double angle,
	double dPosDes1, double dPosDes2)
{
	/*
	int iAxisNO = 2;
	int iEnableCoor[2];
	iEnableCoor[0] = COORDI_AXISX;
	iEnableCoor[1] = COORDI_AXISY;
	if (iAxisNO > m_moveData.m_AxisNum)
	{
		AfxMessageBox(("运动中轴数大于软件设置使能轴数"));
		return USEAXISNOTMATCHENABLEAXIS;
	}
	for (int k = 0; k < iAxisNO ; k++)
	{
		if (iEnableCoor[k] == COORDI_AXISX)
		{
			m_moveData.m_pCurPos[iEnableCoor[k]] = dPosDes1;
		}
		else if (iEnableCoor[k] == COORDI_AXISY)
		{
			m_moveData.m_pCurPos[iEnableCoor[k]] = dPosDes2;
		}
		else
		{
			return -2;//error,只能用于X,Y轴 不能用于Z轴
		}
	}
	*/
	return 0;
}

double CMotionGESInterface::GetPos(int iCoorAxis)
{
    return m_moveData.m_pCurPos[iCoorAxis];
}

double CMotionGESInterface::SetPos(int iCoorAxis, double dPos)
{
    m_moveData.m_pCurPos[iCoorAxis] = dPos;
	return 0;
}

double CMotionGESInterface::SetAbsPos(int iCoorAxis, double dPos)
{
	return 0.0;
}

int CMotionGESInterface::GetPosCur(int iCoorAxis, double* dPos)
{
	int iRet = 0;
	iRet = m_ControlGESInterface->GetRealTimePos(m_moveData.m_EnableAxiss[iCoorAxis],dPos);
	*dPos = *dPos/m_moveData.m_lPPM[iCoorAxis] * m_moveData.m_iAxisReverse[iCoorAxis];
	return iRet;
}

int CMotionGESInterface::StepPtoPMove(int* iAxisCoor, int iAxisPosNum, double* posStep)
{
	return 0;
}

//iMoveType: 0-自动 1-手动(只能单轴)
//iHandMoveSpeedType ：在手动模式下 0-高速  1-中速  2-低速 3-回零
int CMotionGESInterface::StepPtoPMove(int* iCoorAxis, int iAxisPosNum, double* posStep, int iMoveType, int iHandMoveSpeedType)
{
	double* posDes = new double[iAxisPosNum];
	for (int i = 0; i < iAxisPosNum; i++)
	{
		double dPos = 0;
		GetPosCur(iCoorAxis[i], &dPos);
		posDes[i] = dPos + posStep[i];
	}
	int iRtn = PToPMove(iCoorAxis, posDes, iAxisPosNum, iMoveType, iHandMoveSpeedType);
	delete[] posDes;
	posDes = nullptr;
	return iRtn;
}

int CMotionGESInterface::JogMove(int* iCoorAxis, int iAxisLen, int* iDirect)
{
	return 0;
}

//Jog模式只能采用手动(只能单轴)模式
//iHandMoveSpeedType ：在手动模式下 0-高速  1-中速  2-低速  3-回零
int CMotionGESInterface::JogMove(int* iCoorAxis, int iAxisLen, int* iDirect, int iHandMoveSpeedType)
{
	if (iAxisLen != 1)
	{
		//AfxMessageBox(("持续运动只能使用一个轴!"));
		return -1;
	}
    double dHighSpeed[1];
    double dLowSpeed[1];
    double dAcc[1];
	int iRet = 0;

	int iAxis[1];
	iAxis[0] = m_moveData.m_EnableAxiss[iCoorAxis[0]];
	iRet = SetSpeed(iCoorAxis, iAxisLen, 1, iHandMoveSpeedType);
	if (iRet ==0)
	{
//		iDirect[0] *= m_moveData.m_iAxisReverse[iCoorAxis[0]];
		iRet = m_ControlGESInterface->JogMove(iAxis,1, iDirect,true);
	}
    return iRet;
}


//设置输出信号
int CMotionGESInterface::OutputBit(int iBit,int iStatus)
{
	return m_pCMotionGESInterface->OutputBit(1, iBit, iStatus, &m_moveData.m_iOutputStatus);
}

int CMotionGESInterface::Output(int iOutState)
{
	if (m_pCMotionGESInterface->Output(1,iOutState) ==0)
	{
		m_moveData.m_iOutputStatus = iOutState;
	}
	return 0;
}

int CMotionGESInterface::GetOutputPortState()
{
	return m_moveData.m_iOutputStatus;
}

int CMotionGESInterface::Input(int iBit)
{
    return m_pCMotionGESInterface->Input(1, iBit);
}

int CMotionGESInterface::Stop(int iType)
{
	//过滤使能的物理轴和其所代表的坐标系
	int* iAxis = new int[m_moveData.m_AxisNum];
	int* iAxisCoor = new int[m_moveData.m_AxisNum];
	int iCount =0;
	for(int m=COORDI_AXISX; m<MAX_AXISNUM; m++)
	{
		if (m_moveData.m_bEnableAxis[m])
		{
			iAxis[iCount] = m_moveData.m_EnableAxiss[m];
			iAxisCoor[iCount] = m;
			iCount ++;
		}
	}
	CControlInterface::StopMode type = CControlInterface::SlowStop;
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		iRet = m_ControlGESInterface->Stop(iAxis,iCount, type);
		if (iRet >= 0)
		{
			break;
		}
	}
	if (iRet < 0)
	{
		//STOPMOVEERROR 
		iRet = -1111;
	}
	else
    {
        for (int n = 0; n < iCount; n++)
		{
			double dPos=0;
			iRet = m_ControlGESInterface->GetRealTimePos(iAxis[n],&dPos);
			if (iRet < 0)
			{
				iRet = -222;
			}
			else
			{
				m_moveData.m_pCurPos[iAxisCoor[n]] = dPos/m_moveData.m_lPPM[iAxisCoor[n]];
			}
		}
		m_bStop=true;
    }
	return iRet;
}

int CMotionGESInterface::HomeStatus(int iCoorAxis)
{
    return m_ControlGESInterface->GetOriginStatus(m_moveData.m_EnableAxiss[iCoorAxis]);
}

int CMotionGESInterface::LimitStatus(int iCoorAxis)
{
    return m_ControlGESInterface->GetLimitStatus(m_moveData.m_EnableAxiss[iCoorAxis]);
}

int CMotionGESInterface::IsMoving(int* iAxis, int iLen)
{
/*	int* iEnableAxis = new int[iLen];
	for(int i=0; i<iLen; i++)
	{
		iEnableAxis[i] = m_EnableAxiss[iAxis[i]];
	}
*/
	int iRet = 0;
	iRet = m_ControlGESInterface->IsMoving(iAxis, iLen);
	
//	delete[] iEnableAxis;
//	iEnableAxis  = nullptr;
	return iRet;
}

int CMotionGESInterface::Pause()
{
	/*
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		iRet = m_pCMotionGESInterface->Pause();
	}
	return iRet;
	*/
	return 0;
}
int CMotionGESInterface::BeginMove()
{
	/*
	int iRet = 0;
	iRet = m_pCMotionGESInterface->BeginMove();
	return iRet;
	*/
	return 0;
}

int CMotionGESInterface::LaserOn(int iPowerPort)
{
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		int iOutState = 0;//GetOutputPortState();
		iRet = m_ControlGESInterface->LaserOn(iPowerPort, &iOutState);
		if (iRet >= 0)
		{
			m_bPowerStatus = true;
			//m_moveData.m_iOutState = iOutState;
			break;
		}
	}
	return iRet;
}

int CMotionGESInterface::LaserOff(int iPowerPort)
{
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		int iOutState = 0;//GetOutputPortState();
		iRet = m_ControlGESInterface->LaserOff(iPowerPort, &iOutState);
		if (iRet >= 0)
		{
			m_bPowerStatus = true;
			//m_moveData.m_iOutState = iOutState;
			break;
		}
	}
	return iRet;
}
int CMotionGESInterface::GasOpen(int iGasPort)
{
	/*
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		int iOutState = GetOutputPortState();
		iRet = m_ControlGESInterface->GasOpen(iGasPort,&iOutState);
		if (iRet >= 0)
		{
			m_bGasStatus = true;
			m_moveData.m_iOutState = iOutState;

			break;
		}
	}
	return iRet;
	*/
	return 0;
}
int CMotionGESInterface::GasClose(int iGasPort)
{
	/*
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		int iOutState = GetOutputPortState();

		iRet = m_ControlGESInterface->GasClose(iGasPort,&iOutState);
		if (iRet >= 0)
		{
			m_bGasStatus = false;
			m_moveData.m_iOutState = iOutState;

			break;
		}
	}
	return iRet;
	*/
	return 0;
}

int CMotionGESInterface::IsRunningProgram()
{
	/*
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		iRet = m_pCMotionGESInterface->IsRunningProgram();
		if (iRet >= 0)
		{
			break;
		}
	}
	return iRet;
	*/
	return 0;
}

int CMotionGESInterface::AbsorptionOpen(int iAbsorptionPort)
{
	/*
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		int iOutState = GetOutputPortState();
		iRet = m_ControlGESInterface->AbsorptionOpen(iAbsorptionPort,&iOutState);
		if (iRet >= 0)
		{
			m_bGasStatus = true;
			m_moveData.m_iOutState = iOutState;

			break;
		}
	}
	return iRet;
	*/
	return 0;
}
int CMotionGESInterface::AbsorptionClose(int iAbsorptionPort)
{
	/*
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		int iOutState = GetOutputPortState();

		iRet = m_ControlGESInterface->AbsorptionClose(iAbsorptionPort,&iOutState);
		if (iRet >= 0)
		{
			m_bGasStatus = false;
			m_moveData.m_iOutState = iOutState;

			break;
		}
	}
	return iRet;
	*/
	return 0;
}

bool CMotionGESInterface::GetOriginStatus()
{
	return m_bHoming;
}

bool CMotionGESInterface::GetAbsorptionStatus()
{
	return m_bAbsorptionStatus;
}

bool CMotionGESInterface::GetLaserStatus()
{
	return m_bPowerStatus;
}

bool CMotionGESInterface::GetGasStatus()
{
	return m_bGasStatus;
}

int CMotionGESInterface::GetPPM(int iCoorAxis)
{
	return m_moveData.m_lPPM[iCoorAxis];
}

bool CMotionGESInterface::ReadConfigFile()
{
	CReadWriteOperate rwFile(_T("config.ini"));
	rwFile.ReadKey(_T("MoveConfig"), _T("speedDown"), m_moveData.m_speedDown);
	rwFile.ReadKey(_T("MoveConfig"), _T("goOrig"), m_moveData.m_goOrig);
	rwFile.ReadKey(_T("MoveConfig"), _T("elimit"), m_moveData.m_elimit);
	rwFile.ReadKey(_T("MoveConfig"), _T("alarm"), m_moveData.m_alarm);

	rwFile.ReadKey(_T("MoveConfig"), _T("CardNum"), m_moveData.m_CardNum);
	//////////////////////////////////////////////////////////////////////////
	//rwFile.ReadKey(_T("MoveConfig"), _T("CardToAxisNO"), m_moveData.m_CardToAxisNO);
	//二维数组存储的确认
	//////////////////////////////////////////////////////////////////////////
	rwFile.ReadKey(_T("MoveConfig"), _T("AxisNum"), m_moveData.m_AxisNum);

	int iResult = 0;
	for (int  i = 0; i < MAX_AXISNUM; i++)
	{
		//轴参数设置
		TCHAR strName[255];
		TCHAR countChar[2];
		swprintf(countChar, 2, _T("%d"), (i + 1));
		int iLen = 0;
		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AxisNum"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_lPPM[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("CurPos"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_pCurPos[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AxisReverse"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, iResult);
		if(iResult == 0)
		{
			m_moveData.m_iAxisReverse[i] = 1;
		}
		else
		{
			m_moveData.m_iAxisReverse[i] = -1;
		}

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("EnableAxis"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_bEnableAxis[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("EnableAxiss"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_EnableAxiss[i]);

			ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("backOffset"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_backOffset[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("OriginDirection"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, iResult);
		if(iResult == 0)
		{
			m_moveData.m_iOriginDirection[i] = 1;
		}
		else
		{
			m_moveData.m_iOriginDirection[i] = -1;
		}

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("LimitDirection"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, iResult);
		if (iResult == 0)
		{
			m_moveData.m_iLimitDirection[i] = 1;
		}
		else
		{
			m_moveData.m_iLimitDirection[i] = -1;
		}
		//单轴运动参数
		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AxisMoveAcc"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dAxisMoveAcc[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AxisMoveDec"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dAxisMoveDec[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AxisMoveBegSpeed"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dAxisMoveBegSpeed[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AxisMoveSpeed"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dAxisMoveSpeed[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AxisEmptyMoveBegSpeed"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dAxisEmptyMoveBegSpeed[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AxisEmptyMoveSpeed"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dAxisEmptyMoveSpeed[i]);
		//高速
		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("BegSpeedMoveBig"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dBegSpeedMoveBig[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("SpeedMoveBig"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dSpeedMoveBig[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AccSpeedMoveBig"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dAccSpeedMoveBig[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("DecSpeedMoveBig"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dDecSpeedMoveBig[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("ConSpeedMoveBig"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dConSpeedMoveBig[i]);
		//中速
		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("BegSpeedMoveMiddle"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dBegSpeedMoveMiddle[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("SpeedMoveMiddle"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dSpeedMoveMiddle[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AccSpeedMoveMiddle"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dAccSpeedMoveMiddle[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("DecSpeedMoveMiddle"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dDecSpeedMoveMiddle[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("ConSpeedMoveMiddle"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dConSpeedMoveMiddle[i]);
		//低速
		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("BegSpeedMoveMin"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dBegSpeedMoveMin[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("SpeedMoveMin"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dSpeedMoveMin[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AccSpeedMoveMin"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dAccSpeedMoveMin[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("DecSpeedMoveMin"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dDecSpeedMoveMin[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("ConSpeedMoveMin"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dConSpeedMoveMin[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("BegSpeedGoOrig"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dBegSpeedGoOrig[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("SpeedGoOrig"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dSpeedGoOrig[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AccSpeedGoOrig"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dAccSpeedGoOrig[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("DecSpeedGoOrig"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dDecSpeedGoOrig[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("ConSpeedGoOrig"));
		wcscat_s(strName, 255, countChar);
		rwFile.ReadKey(_T("MoveConfig"), strName, m_moveData.m_dConSpeedGoOrig[i]);

	
	}

	rwFile.ReadKey(_T("MoveConfig"), _T("XYMoveAcc"), m_moveData.m_dXYMoveAcc);
	rwFile.ReadKey(_T("MoveConfig"), _T("XYMoveDec"), m_moveData.m_dXYMoveDec);
	rwFile.ReadKey(_T("MoveConfig"), _T("XYMoveBegSpeed"), m_moveData.m_dXYMoveBegSpeed);
	rwFile.ReadKey(_T("MoveConfig"), _T("XYMoveCornerAcc"), m_moveData.m_dXYMoveCornerAcc);
	rwFile.ReadKey(_T("MoveConfig"), _T("XYMoveSpeed"), m_moveData.m_dXYMoveSpeed);

	rwFile.ReadKey(_T("MoveConfig"), _T("XYEmptyBeginSpeed"), m_moveData.m_dXYEmptyBeginSpeed);
	rwFile.ReadKey(_T("MoveConfig"), _T("XYEmptyAccSpeed"), m_moveData.m_dXYEmptyAccSpeed);
	rwFile.ReadKey(_T("MoveConfig"), _T("XYEmptyDecSpeed"), m_moveData.m_dXYEmptyDecSpeed);
	rwFile.ReadKey(_T("MoveConfig"), _T("XYEmptySpeed"), m_moveData.m_dXYEmptySpeed);

	rwFile.ReadKey(_T("MoveConfig"), _T("GoOrgStyle"), m_moveData.m_bGoOrgStyle);
	rwFile.ReadKey(_T("MoveConfig"), _T("OutputStatus"), m_moveData.m_iOutputStatus);
	return true;
}

bool CMotionGESInterface::WriteConfigFile()
{
	CReadWriteOperate rwFile(_T("config.ini"));
	rwFile.WriteKey(_T("MoveConfig"), _T("speedDown"), m_moveData.m_speedDown);
	rwFile.WriteKey(_T("MoveConfig"), _T("goOrig"), m_moveData.m_goOrig);
	rwFile.WriteKey(_T("MoveConfig"), _T("elimit"), m_moveData.m_elimit);
	rwFile.WriteKey(_T("MoveConfig"), _T("alarm"), m_moveData.m_alarm);

	rwFile.WriteKey(_T("MoveConfig"), _T("CardNum"), m_moveData.m_CardNum);
	//////////////////////////////////////////////////////////////////////////
	//rwFile.WriteKey(_T("MoveConfig"), _T("CardToAxisNO"), m_moveData.m_CardToAxisNO);
	//二维数组存储的确认
	//////////////////////////////////////////////////////////////////////////
	rwFile.WriteKey(_T("MoveConfig"), _T("AxisNum"), m_moveData.m_AxisNum);

	int iResult = 0;
	for (int i = 0; i < MAX_AXISNUM; i++)
	{
		TCHAR strName[255];
		TCHAR countChar[2];
		int iLen = 0;
		swprintf(countChar, 2, _T("%d"), (i + 1));

		//轴参数
		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AxisNum"));
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_lPPM[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("CurPos"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_pCurPos[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AxisReverse"));
		wcscat_s(strName, 255, countChar);
		if(m_moveData.m_iAxisReverse[i] == 1)
		{
			iResult = 0;
		}
		else
		{
			iResult = 1;
		}
		rwFile.WriteKey(_T("MoveConfig"), strName,iResult );

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("EnableAxis"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_bEnableAxis[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("EnableAxiss"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_EnableAxiss[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("backOffset"));
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_backOffset[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("OriginDirection"));
		wcscat_s(strName, 255, countChar);
		if(m_moveData.m_iOriginDirection[i] == 1)
		{
			iResult = 0;
		}
		else
		{
			iResult = 1;
		}
		rwFile.WriteKey(_T("MoveConfig"), strName, iResult);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("LimitDirection"));
		wcscat_s(strName, 255, countChar);
		if (m_moveData.m_iLimitDirection[i] == 1)
		{
			iResult = 0;
		}
		else
		{
			iResult = 1;
		}
		rwFile.WriteKey(_T("MoveConfig"), strName, iResult);

		//单轴运动参数
		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AxisMoveAcc"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dAxisMoveAcc[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AxisMoveDec"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dAxisMoveDec[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AxisMoveBegSpeed"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dAxisMoveBegSpeed[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AxisMoveSpeed"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dAxisMoveSpeed[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AxisEmptyMoveBegSpeed"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dAxisEmptyMoveBegSpeed[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AxisEmptyMoveSpeed"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dAxisEmptyMoveSpeed[i]);

		//高速
		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("BegSpeedMoveBig"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dBegSpeedMoveBig[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("SpeedMoveBig"));
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dSpeedMoveBig[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AccSpeedMoveBig"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dAccSpeedMoveBig[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("DecSpeedMoveBig"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dDecSpeedMoveBig[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("ConSpeedMoveBig"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dConSpeedMoveBig[i]);
		//中速
		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("BegSpeedMoveMiddle"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dBegSpeedMoveMiddle[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("SpeedMoveMiddle"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dSpeedMoveMiddle[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AccSpeedMoveMiddle"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dAccSpeedMoveMiddle[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("DecSpeedMoveMiddle"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dDecSpeedMoveMiddle[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("ConSpeedMoveMiddle"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dConSpeedMoveMiddle[i]);
		//低速
		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("BegSpeedMoveMin"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dBegSpeedMoveMin[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("SpeedMoveMin"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dSpeedMoveMin[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AccSpeedMoveMin"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dAccSpeedMoveMin[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("DecSpeedMoveMin"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dDecSpeedMoveMin[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("ConSpeedMoveMin"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dConSpeedMoveMin[i]);
		//回零
		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("BegSpeedGoOrig"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dBegSpeedGoOrig[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("SpeedGoOrig"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dSpeedGoOrig[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("AccSpeedGoOrig"));	
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dAccSpeedGoOrig[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("DecSpeedGoOrig"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dDecSpeedGoOrig[i]);

		ZeroMemory(strName, sizeof(TCHAR)* 255);
		wcscpy_s(strName, 255, _T("ConSpeedGoOrig"));		
		wcscat_s(strName, 255, countChar);
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_dConSpeedGoOrig[i]);
	}

	rwFile.WriteKey(_T("MoveConfig"), _T("XYMoveAcc"), m_moveData.m_dXYMoveAcc);
	rwFile.WriteKey(_T("MoveConfig"), _T("XYMoveDec"), m_moveData.m_dXYMoveDec);
	rwFile.WriteKey(_T("MoveConfig"), _T("XYMoveBegSpeed"), m_moveData.m_dXYMoveBegSpeed);
	rwFile.WriteKey(_T("MoveConfig"), _T("XYMoveCornerAcc"), m_moveData.m_dXYMoveCornerAcc);
	rwFile.WriteKey(_T("MoveConfig"), _T("XYMoveSpeed"), m_moveData.m_dXYMoveSpeed);

	rwFile.WriteKey(_T("MoveConfig"), _T("XYEmptyBeginSpeed"), m_moveData.m_dXYEmptyBeginSpeed);
	rwFile.WriteKey(_T("MoveConfig"), _T("XYEmptyAccSpeed"), m_moveData.m_dXYEmptyAccSpeed);
	rwFile.WriteKey(_T("MoveConfig"), _T("XYEmptyDecSpeed"), m_moveData.m_dXYEmptyDecSpeed);
	rwFile.WriteKey(_T("MoveConfig"), _T("XYEmptySpeed"), m_moveData.m_dXYEmptySpeed);

	rwFile.WriteKey(_T("MoveConfig"), _T("GoOrgStyle"), m_moveData.m_bGoOrgStyle);
	rwFile.WriteKey(_T("MoveConfig"), _T("OutputStatus"), m_moveData.m_iOutputStatus);

	return true;
}

bool CMotionGESInterface::SetConfigApplication()
{
/*	STARTUPINFO si; //一些必备参数设置  
	PROCESS_INFORMATION pi; //必备参数设置结束 
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	//std::string file(filename.GetBuffer(0));  
//	if (!CreateProcess(NULL, _T("K://G//编程//GTS//Win32ExportDll(2010)//Debug//MoveData.exe"), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) //8888为命令行参数  
//	{
//		return false;
//	}
//	WinExec("MoveData.exe", SW_SHOW);
*/

	TCHAR buf[1000];
	int i = 1000;
	GetCurrentDirectory(1000, buf);  //得到当前工作路径
	TCHAR strModule[256];
	GetModuleFileName(NULL, strModule, 256); //得到当前模块路径
	(wcsrchr(strModule, '\\') + 1)[0] = 0; // 删除文件名，只获得路径字串

	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = L"open";//多种类别有 "explorer" "print" 等  
	ShExecInfo.lpFile = L"MoveData.exe";//exe 路径      
	ShExecInfo.lpParameters = L"";//参数  
	ShExecInfo.lpDirectory = strModule;
	ShExecInfo.nShow = SW_SHOW;//  
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);

	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);//等待完成   第二个参数是超时时间（毫秒）超时后返回超时代码 


	//更新运行参数配置
	ReadConfigFile();

	return true;
}