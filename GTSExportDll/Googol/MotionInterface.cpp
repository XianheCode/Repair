// MotionInterface.cpp: implementation of the CMotionInterface class.
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
#include "MotionInterface.h"
#include "ReadWriteOperate.h"
#include <tchar.h>
#include <string>
#include <ShellApi.h>

CMotionInterface::CMotionInterface()
{
	m_bInit = false;
	m_bHoming = false;
	m_bHomeReady = false;
	m_bInitHomeReady = false;
	m_pCMotionInterface = nullptr;
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
	//////////////////////////////////////////////////////////////////////////
	if (!m_bInit)
	{
		m_ControlGTSInterface = new CGoogolGTSControl();
		m_pCMotionInterface = m_ControlGTSInterface;
		m_bInit = true;
	}
}

CMotionInterface::~CMotionInterface()
{
	if (m_pCMotionInterface != nullptr)
	{
		delete m_pCMotionInterface;
		m_pCMotionInterface = nullptr;
	}
}

int CMotionInterface::Init(int iCardNum, CMotionInterface* pToSelf)
{
	ReadConfigFile();

	int piEnableAxis[8];
	//建立坐标系和物理轴的映射关系
	m_moveData.m_AxisNum = 0;
	for (int i = 0; i<MAX_AXISNUM; i++)
	{
		if (m_moveData.m_bEnableAxis[i])
		{
			piEnableAxis[m_moveData.m_AxisNum] = m_moveData.m_EnableAxiss[i];
			m_moveData.m_AxisNum++;
		}
	}

	char* strCfgPath = UnicodeToAnsi(m_moveData.m_strGTSConfigPath);
	return m_ControlGTSInterface->Init(piEnableAxis, m_moveData.m_AxisNum, &iCardNum, this,strCfgPath);
}

int CMotionInterface::Close()
{
	m_ControlGTSInterface->Close();
	return 0;
}

int CMotionInterface::GoOrigin()
{
	return 0;
}

//iHomeType: 0-限位回零   1-Home回零  2-Index回零
int CMotionInterface::GoOrigin(HOMEPrm movePrm[], int iArrayNum,int iHomeType)
{
	int iRtn = 0;

	int* iAxisNo = new int[iArrayNum];
	int* iDirect = new int[iArrayNum];
	double* dOrgMove = new double[iArrayNum];
	double* dHomeOff = new double[iArrayNum];
	for (int i = 0; i < iArrayNum; i++)
	{
		iAxisNo[i] = m_moveData.m_EnableAxiss[movePrm[i].iCoorAxis];
		iDirect[i] = movePrm[i].iDirect;
		dOrgMove[i] = movePrm[i].dOrgMove * (m_moveData.m_lPPM[movePrm[i].iCoorAxis]);
		dHomeOff[i] = movePrm[i].dHomeOff * (m_moveData.m_lPPM[movePrm[i].iCoorAxis]);
	}
	if (iHomeType == 0)
	{
		iRtn = m_ControlGTSInterface->GoOriginLimit(iAxisNo, iArrayNum, iDirect, dHomeOff);
	}
	else if (iHomeType == 1)
	{
		iRtn = m_ControlGTSInterface->GoOriginHome(iAxisNo, iArrayNum, iDirect, dOrgMove,dHomeOff);
	}
	else if (iHomeType == 2)
	{
		iRtn = m_ControlGTSInterface->GoOriginIndex(iAxisNo, iArrayNum, iDirect, dOrgMove,dHomeOff);
	}

	delete[] iAxisNo;
	delete[] iDirect;
	delete[] dOrgMove;
	delete[] dHomeOff;
	iAxisNo = nullptr;
	iDirect = nullptr;
	dOrgMove = nullptr;
	dHomeOff = nullptr;

	return iRtn;
}

int CMotionInterface::CheckAlreadyOrg()
{
	return 0;
}

/*
//iMoveType: 0-手动  1-自动  2-自定义
//iHandVelType: 
	手动:0-低速  1-中速  2-高速 3-回零
    自动:0 - 加工  1 - 空走
//ptopMoveSet:自定义速度参数
*/
int CMotionInterface::SetSpeed(TSPEEDPrm movePrm[],int iArrayNum)
{
	m_bStop = false;
	int iRet = 0;
	int iAxisNO = iArrayNum;
	if (iAxisNO > m_moveData.m_AxisNum)
	{
		//AfxMessageBox(("运动中轴数大于软件设置使能轴数"));
		return  -111;//USEAXISNOTMATCHENABLEAXIS;
	}

	for (int i = 0; i < iAxisNO; i++)
	{
		SPEEDPrm speedPrm = movePrm[i];
		int iCoorAxisNum = speedPrm.iCoorAxis;
		int iAxisNum = m_moveData.m_EnableAxiss[iCoorAxisNum];
		if (speedPrm.iMoveType == 0)
		{
			if (speedPrm.iHandVelType == 0)
			{
				dLowVelArray[iAxisNum-1] = m_moveData.m_dBegSpeedMoveMin[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000;
				dHighVelArray[iAxisNum-1] = m_moveData.m_dSpeedMoveMin[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000;
				dAccArray[iAxisNum-1] = m_moveData.m_dAccSpeedMoveMin[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000000;
				dDecArray[iAxisNum-1] = m_moveData.m_dDecSpeedMoveMin[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000000;
			}
			else if (speedPrm.iHandVelType == 1)
			{
				dLowVelArray[iAxisNum-1] = m_moveData.m_dBegSpeedMoveMiddle[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000;
				dHighVelArray[iAxisNum-1] = m_moveData.m_dSpeedMoveMiddle[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000;
				dAccArray[iAxisNum-1] = m_moveData.m_dAccSpeedMoveMiddle[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000000;
				dDecArray[iAxisNum-1] = m_moveData.m_dDecSpeedMoveMiddle[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000000;
			}
			else if (speedPrm.iHandVelType == 2)
			{
				dLowVelArray[iAxisNum-1] = m_moveData.m_dBegSpeedMoveBig[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000;
				dHighVelArray[iAxisNum-1] = m_moveData.m_dSpeedMoveBig[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000;
				dAccArray[iAxisNum-1] = m_moveData.m_dAccSpeedMoveBig[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000000;
				dDecArray[iAxisNum-1] = m_moveData.m_dDecSpeedMoveBig[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000000;
			}
			else if (speedPrm.iHandVelType == 3)
			{
				dLowVelArray[iAxisNum-1] = m_moveData.m_dBegSpeedGoOrig[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000;
				dHighVelArray[iAxisNum-1] = m_moveData.m_dSpeedGoOrig[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000;
				dAccArray[iAxisNum-1] = m_moveData.m_dAccSpeedGoOrig[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000000;
				dDecArray[iAxisNum-1] = m_moveData.m_dDecSpeedGoOrig[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000000;
			}
		}
		else if (speedPrm.iMoveType == 1)
		{
			if (speedPrm.iHandVelType == 0)
			{
				dLowVelArray[iAxisNum-1] = m_moveData.m_dAxisMoveBegSpeed[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000;
				dHighVelArray[iAxisNum-1] = m_moveData.m_dAxisMoveSpeed[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000;
			}
			else if (speedPrm.iHandVelType == 1)
			{
				dLowVelArray[iAxisNum-1] = m_moveData.m_dAxisEmptyMoveBegSpeed[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000;
				dHighVelArray[iAxisNum-1] = m_moveData.m_dAxisEmptyMoveSpeed[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000;
			}
			dAccArray[iAxisNum-1] = m_moveData.m_dAxisMoveAcc[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000000;
			dDecArray[iAxisNum-1] = m_moveData.m_dAxisMoveDec[iCoorAxisNum] * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000000;
		}
		else if (speedPrm.iMoveType == 2)
		{
			dLowVelArray[iAxisNum-1] = speedPrm.dLowVel * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000;
			dHighVelArray[iAxisNum-1] = speedPrm.dHighVel * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000;
			dAccArray[iAxisNum-1] = speedPrm.dAcc * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000000;
			dDecArray[iAxisNum-1] = speedPrm.dDec * (m_moveData.m_lPPM[iCoorAxisNum]) / 1000000;
		}
	}
	return iRet;
}

int CMotionInterface::PToPMove(TPTPPrm movePrm[], int iArrayNum)
{
	m_bStop = false;
	int iRet = 0;
	int iAxisNO = iArrayNum;
	if (iAxisNO > m_moveData.m_AxisNum)
	{
		//AfxMessageBox(("运动中轴数大于软件设置使能轴数"));
		return  -111;//USEAXISNOTMATCHENABLEAXIS;
	}
	
	int* iEnableAxis = new int[iAxisNO];
	double* posDes = new double[iAxisNO];
	for (int n = 0; n<iAxisNO; n++)
	{
		int iIndexTemp = movePrm[n].iCoorAxis;
		iEnableAxis[n] = m_moveData.m_EnableAxiss[iIndexTemp];
		posDes[n] = movePrm[n].dPos * m_moveData.m_iAxisReverse[iIndexTemp] * (m_moveData.m_lPPM[iIndexTemp]);
	}

	iRet = m_ControlGTSInterface->PTPMoveTo(iEnableAxis, iAxisNO, posDes, TRUE);
	if (m_bStop)
	{
		iRet= -222; //STOPMOVE
	}
	if (iRet !=0)
	{
		for (int k = 0; k < iAxisNO ; k++)
		{
			int iIndexTemp = movePrm[k].iCoorAxis;
			m_moveData.m_pCurPos[iIndexTemp] = posDes[k] / m_moveData.m_iAxisReverse[iIndexTemp]
				/ (m_moveData.m_lPPM[iIndexTemp]);
		}
	}

	delete[] iEnableAxis;
	delete[] posDes;
	iEnableAxis = nullptr;
	posDes = nullptr;
    return iRet;
}

int CMotionInterface::MoveArcTo(int iAxis1, double posCenter1, int iAxis2, double posCenter2, double angle,
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

double CMotionInterface::GetPos(int iCoorAxis)
{
    return m_moveData.m_pCurPos[iCoorAxis];
}

double CMotionInterface::SetPos(int iCoorAxis, double dPos)
{
    m_moveData.m_pCurPos[iCoorAxis] = dPos;
	return 0;
}

double CMotionInterface::SetAbsPos(int iCoorAxis, double dPos)
{
	return 0.0;
}

int CMotionInterface::GetPosCur(int iCoorAxis, double* dPos)
{
	int iRet = 0;
	iRet = m_ControlGTSInterface->GetRealTimePos(m_moveData.m_EnableAxiss[iCoorAxis],dPos);
	*dPos = *dPos/m_moveData.m_lPPM[iCoorAxis] * m_moveData.m_iAxisReverse[iCoorAxis];
	return iRet;
}

int CMotionInterface::StepPtoPMove(TSTEPPrm movePrm[], int iArrayNum)
{
	TPTPPrm* ptpTrm = new TPTPPrm[iArrayNum];
	for (int i = 0; i < iArrayNum; i++)
	{
		int iCoorAxis = movePrm[i].iCoorAxis;
		ptpTrm[i].iCoorAxis = iCoorAxis;

		double dPos = 0;
		GetPosCur(iCoorAxis, &dPos);
		ptpTrm[i].dPos = dPos + movePrm[i].dStepPos;
	}
	int iRtn = PToPMove(ptpTrm, iArrayNum);
	Sleep(100);

	delete[] ptpTrm;
	ptpTrm = nullptr;

	return iRtn;
}

//指定轴持续运动
int CMotionInterface::JogMove(TJOGPrm movePrm[], int iArrayNum)
{
	int* iEnableAxis = new int[iArrayNum];
	int* iDirect = new int[iArrayNum];

	for (int i = 0; i < iArrayNum; i++)
	{
		int iIndexTemp = movePrm[i].iCoorAxis;
		iEnableAxis[i] = m_moveData.m_EnableAxiss[iIndexTemp];
		iDirect[i] = movePrm[i].iDirect;
	}

	int iRtn = m_ControlGTSInterface->JogMove(iEnableAxis, iArrayNum, iDirect);

	delete[] iEnableAxis;
	delete[] iDirect;
	iEnableAxis = nullptr;
	iDirect = nullptr;

	return iRtn;
}


//设置输出信号
int CMotionInterface::OutputBit(int iBit,int iStatus)
{
	return m_pCMotionInterface->OutputBit(1, iBit, iStatus, &m_moveData.m_iOutputStatus);
}

int CMotionInterface::Output(int iOutState)
{
	if (m_pCMotionInterface->Output(1,iOutState) ==0)
	{
		m_moveData.m_iOutputStatus = iOutState;
	}
	return 0;
}

int CMotionInterface::GetOutputPortState()
{
	return m_moveData.m_iOutputStatus;
}
int CMotionInterface::Input(int iBit)
{
    return m_pCMotionInterface->Input(1, iBit);
}

int CMotionInterface::Stop(int iType)
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
		iRet = m_ControlGTSInterface->Stop(iAxis,iCount, type);
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
			iRet = m_ControlGTSInterface->GetRealTimePos(iAxis[n],&dPos);
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

	delete[] iAxis;
	delete[] iAxisCoor;
	iAxis = nullptr;
	iAxisCoor = nullptr;

	return iRet;
}

int CMotionInterface::HomeStatus(int iCoorAxis)
{
    return m_ControlGTSInterface->GetOriginStatus(m_moveData.m_EnableAxiss[iCoorAxis]);
}

int CMotionInterface::LimitStatus(int iCoorAxis,int* iLimitP,int* iLimitN)
{
	return m_ControlGTSInterface->GetLimitStatus(m_moveData.m_EnableAxiss[iCoorAxis], iLimitP, iLimitN);
}

int CMotionInterface::IsMoving(int* iAxis, int iLen)
{
	int* iEnableAxis = new int[iLen];
	for(int i=0; i<iLen; i++)
	{
		iEnableAxis[i] = m_moveData.m_EnableAxiss[iAxis[i]];
	}
	int iRet = m_ControlGTSInterface->IsMoving(iEnableAxis, iLen);
	
	delete[] iEnableAxis;
	iEnableAxis  = nullptr;

	return iRet;
}

int CMotionInterface::Pause()
{
	/*
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		iRet = m_pCMotionInterface->Pause();
	}
	return iRet;
	*/
	return 0;
}
int CMotionInterface::BeginMove()
{
	/*
	int iRet = 0;
	iRet = m_pCMotionInterface->BeginMove();
	return iRet;
	*/
	return 0;
}

int CMotionInterface::LaserOn(int iPowerPort)
{
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		int iOutState = 0;//GetOutputPortState();
		iRet = m_ControlGTSInterface->LaserOn(iPowerPort, &iOutState);
		if (iRet >= 0)
		{
			m_bPowerStatus = true;
			//m_moveData.m_iOutState = iOutState;
			break;
		}
	}
	return iRet;
}

int CMotionInterface::LaserOff(int iPowerPort)
{
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		int iOutState = 0;//GetOutputPortState();
		iRet = m_ControlGTSInterface->LaserOff(iPowerPort, &iOutState);
		if (iRet >= 0)
		{
			m_bPowerStatus = true;
			//m_moveData.m_iOutState = iOutState;
			break;
		}
	}
	return iRet;
}
int CMotionInterface::GasOpen(int iGasPort)
{
	/*
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		int iOutState = GetOutputPortState();
		iRet = m_ControlGTSInterface->GasOpen(iGasPort,&iOutState);
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
int CMotionInterface::GasClose(int iGasPort)
{
	/*
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		int iOutState = GetOutputPortState();

		iRet = m_ControlGTSInterface->GasClose(iGasPort,&iOutState);
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

int CMotionInterface::IsRunningProgram()
{
	/*
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		iRet = m_pCMotionInterface->IsRunningProgram();
		if (iRet >= 0)
		{
			break;
		}
	}
	return iRet;
	*/
	return 0;
}

int CMotionInterface::AbsorptionOpen(int iAbsorptionPort)
{
	/*
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		int iOutState = GetOutputPortState();
		iRet = m_ControlGTSInterface->AbsorptionOpen(iAbsorptionPort,&iOutState);
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
int CMotionInterface::AbsorptionClose(int iAbsorptionPort)
{
	/*
	int iRet = 0;
	for (int i=0; i<5; i++)
	{
		int iOutState = GetOutputPortState();

		iRet = m_ControlGTSInterface->AbsorptionClose(iAbsorptionPort,&iOutState);
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

bool CMotionInterface::GetOriginStatus()
{
	return m_bHoming;
}

bool CMotionInterface::GetAbsorptionStatus()
{
	return m_bAbsorptionStatus;
}

bool CMotionInterface::GetLaserStatus()
{
	return m_bPowerStatus;
}

bool CMotionInterface::GetGasStatus()
{
	return m_bGasStatus;
}

int CMotionInterface::GetPPM(int iCoorAxis)
{
	return m_moveData.m_lPPM[iCoorAxis];
}

bool CMotionInterface::ReadConfigFile()
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

	//rwFile.ReadKey(_T("MoveConfig"), _T("AxisNum"), m_moveData.m_AxisNum);

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
		if (iResult == 0)
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
		if (iResult == 0)
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
		//回零
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
	
	TCHAR* tch = new TCHAR[255];
	rwFile.ReadKey(_T("MoveConfig"), _T("GTSConfigPath"), tch);
	ZeroMemory(m_moveData.m_strGTSConfigPath, sizeof(TCHAR)* 255);
	wcscpy_s(m_moveData.m_strGTSConfigPath, 255, tch);

	return true;
}

bool CMotionInterface::WriteConfigFile()
{
	CReadWriteOperate rwFile;
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
		if (m_moveData.m_iAxisReverse[i] == 1)
		{
			iResult = 0;
		}
		else
		{
			iResult = 1;
		}
		rwFile.WriteKey(_T("MoveConfig"), strName, iResult);

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
		if (m_moveData.m_iOriginDirection[i] == 1)
		{
			iResult = 0;
		}
		else
		{
			iResult = 1;
		}
		rwFile.WriteKey(_T("MoveConfig"), strName, m_moveData.m_iOriginDirection[i]);

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

bool CMotionInterface::SetConfigApplication()
{
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

char* CMotionInterface::UnicodeToAnsi(const wchar_t *szStr)
 {
	 int nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
	 if (nLen == 0)
		 return NULL;
	 char* pResult = new char[nLen];
	 WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
	 return pResult;
 }