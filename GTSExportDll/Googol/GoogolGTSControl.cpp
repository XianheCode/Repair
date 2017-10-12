// GoogolGTSControl.cpp: implementation of the CGoogolGTSControl class.
/*
 * CopyRight (c) 2017
 * All Rights reserved
 *
 * File Name		: GoogolGTSControl.cpp
 * File ID			: None
 * Sumary			: For Googol
 *
 * Current Version	: 1.0.0
 * Author			: Jackie Wu
 * Finish Time		: 2017-2-27
 * Last Modify Time : 2017-2-27
*/
//#include "stdafx.h"
#include "GoogolGTSControl.h"
#include "MotionInterface.h"
#include <string.h>

#define SEARCH_HOME		-12000000
#define HOME_OFFSET		-2000

CGoogolGTSControl::CGoogolGTSControl(void)
{
	m_pGetMI = nullptr;
}

CGoogolGTSControl::~CGoogolGTSControl(void)
{
}

int CGoogolGTSControl::Init(int* enableAxiss, int iEnableAxisNum, int* iCardNum, void* pToSelf)
{
	return rtn;
}

int CGoogolGTSControl::Init(int* enableAxiss, int iEnableAxisNum, int* iCardNum, void* pToSelf,char* cCfgPath)
{
	Mutex::Lock lock(m_mutex);

	m_pGetMI = (CMotionInterface*)pToSelf;
	long val = 0;
	rtn = GT_Open();
	if (rtn != 0)
	{
		return rtn;
	}
	// 复位运动控制器
	rtn = GT_Reset();
	if (rtn != 0)
	{
		return rtn;
	}
	//加载配置文件
	rtn = GT_LoadConfig(cCfgPath);
	if (rtn != 0)
	{
		return rtn;
	}
	// 清除各轴的报警和限位
	rtn = GT_ClrSts(1, MAX_AXISNUM);
	if (rtn != 0)
	{
		return rtn;
	}
	//设置激光参数
	rtn = GT_SetLaserMode(0);
	rtn = GT_LaserPowerMode(0, 100, 10, 1, 0);
	//使能轴
	for (int i = 0; i<iEnableAxisNum; i++)
	{
		rtn = GT_AxisOn(enableAxiss[i]);
	}
	if (rtn == 0)
	{
		m_bInit = true;
	}

	return rtn;
}

int CGoogolGTSControl::Close()
{
	Mutex::Lock lock(m_mutex);

	GT_Close();
	return 0;
}

int CGoogolGTSControl::OutputBit(int iCardNO, int bitNO, int iStatus, int* iOutStatus)
{
	Mutex::Lock lock(m_mutex);

	return GT_SetDoBit(MC_GPO,bitNO,iStatus);
}

int CGoogolGTSControl::Output(int iCard,int iOutState)
{
	Mutex::Lock lock(m_mutex);

	return GT_SetDo(MC_GPO, iOutState);
}

int CGoogolGTSControl::Input(int iCardNO, int iBitNO)
{
	Mutex::Lock lock(m_mutex);

	long lDiSts;
	GT_GetDi(MC_GPI, &lDiSts);
	if (lDiSts&(0x01 << iBitNO))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int CGoogolGTSControl::GetOriginStatus(int iAxisNO)
{
	//暂时无用
	return 0;
}

int CGoogolGTSControl::GetLimitStatus(int iAxisNO)
{
	return 0;
}

int CGoogolGTSControl::GetLimitStatus(int iAxisNO, int* piLimitP, int* piLimitN)
{
	Mutex::Lock lock(m_mutex);

	*piLimitP = 0;
	*piLimitN = 0;

	long sRtn;
	long lAxisStatus;					// 轴状态
	int rtn = GT_ClrSts(iAxisNO, 1);
	// 读取轴状态
	sRtn = GT_GetSts(iAxisNO, &lAxisStatus);
	// 正负限位
	bool bLimitP = false;
	bool bLimitN = false;
	if (lAxisStatus & 0x20)
	{
		*piLimitP = 1;
	}
	if (lAxisStatus & 0x40)
	{
		*piLimitN = 1;
	}

	return sRtn;
}

int CGoogolGTSControl::GetRealTimePos(int iAxisNO, double* dRealTimePos)
{
	Mutex::Lock lock(m_mutex);

	int iRtn = GT_GetPrfPos(iAxisNO, dRealTimePos);
	return iRtn;
}

//点位运动
int CGoogolGTSControl::MoveTo(int* iEnableCoor, int iAxisPosNum, double* posTarget, int iType)
{
	return 0;
}

//点位运动-整合
int CGoogolGTSControl::PTPMoveTo(int* iEnableAxis, int iAxisPosNum, double* posTarget, bool bSleep)
{
	int iRtn = 0;
	TTrapPrm trap;
	// 清除各轴的报警和限位
	{
		Mutex::Lock lock(m_mutex);

		iRtn = GT_ClrSts(1, MAX_AXISNUM);
		if (iRtn != 0)
		{
			return iRtn;
		}
	}

	//SetSpeed
	for (int i = 0; i<iAxisPosNum; i++)
	{
		Mutex::Lock lock(m_mutex);

		// 将AXIS轴设为点位模式
		iRtn = GT_PrfTrap(iEnableAxis[i]);
		if (iRtn != 0)
		{
			break;
		}
		// 设置点位运动参数
		iRtn = GT_GetTrapPrm(iEnableAxis[i], &trap);
		if (iRtn != 0)
		{
			break;
		}
		trap.velStart = m_pGetMI->dLowVelArray[iEnableAxis[i]-1];
		trap.acc = m_pGetMI->dAccArray[iEnableAxis[i]-1];
		trap.dec = m_pGetMI->dDecArray[iEnableAxis[i]-1];
		trap.smoothTime = 25;//ms	
		iRtn = GT_SetTrapPrm(iEnableAxis[i], &trap);
		if (iRtn != 0)
		{
			break;
		}
		// 设置AXIS轴的目标速度
		iRtn = GT_SetVel(iEnableAxis[i], m_pGetMI->dHighVelArray[iEnableAxis[i]-1]); //将单位转换为pulse/ms
		if (iRtn != 0)
		{
			break;
		}
	}
	if (iRtn != 0)
	{
		return iRtn;
	}

	//MoveTo
	long sts;
	double prfPos;
	for (int i = 0; i<iAxisPosNum; i++)
	{
		Mutex::Lock lock(m_mutex);

		// 设置AXIS轴的目标位置
		int iRtn = GT_SetPos(iEnableAxis[i], posTarget[i]);
		if (iRtn != 0)
		{
			break;
		}
		// 启动AXIS轴的运动
		iRtn = GT_Update(1 << (iEnableAxis[i] - 1));
		if (iRtn != 0)
		{
			break;
		}
	}
	if (iRtn != 0)
	{
		return iRtn;
	}
	//等待完成
	if (bSleep)
	{
		for (int i = 0; i < iAxisPosNum; i++)
		{
			do
			{
				{
					Mutex::Lock lock(m_mutex);
					// 读取AXIS轴的状态
					iRtn = GT_GetSts(iEnableAxis[i], &sts);
				}
				Sleep(100);

			} while (sts & 0x400);	// 等待AXIS轴规划停止
		}
	}

	return 0;
}

int CGoogolGTSControl::IsMoving(int* iAxisNO, int iLen)
{
	bool bMoveDone = true;  //速度为0, 运动完成
	long status = 0;
	long sRtn = 0;
	double encPos = 0;
	double prfPos = 0;
	long sts;
	for (int i = 0; i<iLen; i++)
	{
		{
			Mutex::Lock lock(m_mutex);
			// 读取AXIS轴的状态
			sRtn = GT_GetSts(iAxisNO[i], &sts); 
		}
		if ((sts & 0x400) != 0)// AXIS轴在运动
		{
			bMoveDone = false;
		}
	}
	if (bMoveDone)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int CGoogolGTSControl::SetSpeed(int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec, int iType)
{
    return 0;
}

int CGoogolGTSControl::GoOrigin(int* iAxisNO, int* iDirect, int iLen, int* orgmove, bool bStyle)
{
	short sRtn =0 , capture = 0;
	TTrapPrm trapPrm;
	long status, pos;
	double prfPos, encPos, axisPrfPos, axisEncPos;	

/*	// 清除各轴的报警和限位
	sRtn = GT_ClrSts(1, MAX_AXISNUM);
	if (sRtn != 0)
	{
		return sRtn;
	}

	for (int i=0; i<iLen; i++)
	{
		if (i != COORDI_AXISC)
		{
			//使用限位回零
			int iAxisNO[1];
			double dHighSpeed[1];
			double dLowSpeed[1];
			double dAcc[1];
			int iDirect[1];
			iAxisNO[0] = i+1;
			dHighSpeed[0] = m_pGetMI->m_moveData.m_dSpeedGoOrig[i] * m_pGetMI->m_moveData.m_lPPM[i];
			dLowSpeed[0] = m_pGetMI->m_moveData.m_dBegSpeedGoOrig[i] * m_pGetMI->m_moveData.m_lPPM[i];
			dAcc[0] = m_pGetMI->m_moveData.m_dAccSpeedGoOrig[i] * m_pGetMI->m_moveData.m_lPPM[i];
			SetSpeed(iAxisNO,1,dHighSpeed,dLowSpeed,dAcc,dAcc,2);
			sRtn = JogMove(&iAxisNO[0],1,iDirect);
		}
		else
		{
			continue;
		}
	}
	//等待运动完成开始
	while(IsMoving(iAxisNO,iLen)==1)
	{
		//////////////////////////////////////////////////////////////////////////
		//Sleep Error
		//Sleep(100);
		//////////////////////////////////////////////////////////////////////////
	}
	//C轴回零
	// 启动Index捕获
	sRtn = GT_SetCaptureMode(iAxisNO[COORDI_AXISC], CAPTURE_INDEX);
	// 启动Home捕获
	//sRtn = GT_SetCaptureMode(iAxisNO[i], CAPTURE_HOME);
	if (sRtn != 0)
	{
		return sRtn;
	}
	// 切换到点位运动模式
	sRtn = GT_PrfTrap(iAxisNO[COORDI_AXISC]);
	if (sRtn != 0)
	{
		return sRtn;
	}

	// 读取点位模式运动参数
	sRtn = GT_GetTrapPrm(iAxisNO[COORDI_AXISC], &trapPrm);
	if (sRtn != 0)
	{
		return sRtn;
	}
	trapPrm.acc = m_pGetMI->m_moveData.m_dAccSpeedGoOrig[COORDI_AXISC] * m_pGetMI->m_moveData.m_lPPM[COORDI_AXISC] / 1000000;
	trapPrm.dec = m_pGetMI->m_moveData.m_dDecSpeedGoOrig[COORDI_AXISC] * m_pGetMI->m_moveData.m_lPPM[COORDI_AXISC] / 1000000;

	// 设置点位模式运动参数
	sRtn = GT_SetTrapPrm(iAxisNO[COORDI_AXISC], &trapPrm);
	if (sRtn != 0)
	{
		return sRtn;
	}

	// 设置点位模式目标速度，即回原点速度
	sRtn = GT_SetVel(iAxisNO[COORDI_AXISC], m_pGetMI->m_moveData.m_dSpeedGoOrig[COORDI_AXISC] * m_pGetMI->m_moveData.m_lPPM[COORDI_AXISC] / 1000);
	if (sRtn != 0)
	{
		return sRtn;
	}

	// 设置点位模式目标位置，即原点搜索距离
	sRtn = GT_SetPos(iAxisNO[COORDI_AXISC], SEARCH_HOME);
	if (sRtn != 0)
	{
		return sRtn;
	}

	// 启动运动
	sRtn = GT_Update(1<<(iAxisNO[COORDI_AXISC]-1));
	if (sRtn != 0)
	{
		return sRtn;
	}

	do
	{
		// 读取轴状态
		sRtn = GT_GetSts(iAxisNO[COORDI_AXISC], &status);
		if (sRtn != 0)
		{
			break;
		}

		// 读取捕获状态
		sRtn = GT_GetCaptureStatus(iAxisNO[COORDI_AXISC], &capture, &pos);
		if (sRtn != 0)
		{
			break;
		}

		// 读取规划位置
		sRtn = GT_GetPrfPos(iAxisNO[COORDI_AXISC], &prfPos);
		if (sRtn != 0)
		{
			break;
		}

		// 读取编码器位置
		sRtn = GT_GetEncPos(iAxisNO[COORDI_AXISC], &encPos);
		if (sRtn != 0)
		{
			break;
		}

		// 如果运动停止，返回出错信息
		if( 0 == ( status & 0x400 ) )
		{
			break;
		}
		if (capture == 1)
		{
			break;
		}
		// 等待捕获触发
	}while( 0 == capture );

	if (sRtn !=0 )
	{
		return sRtn;
	}
	// 运动到"捕获位置+偏移量"
	sRtn = GT_SetPos(iAxisNO[COORDI_AXISC], pos + HOME_OFFSET);
	if (sRtn != 0)
	{
		return sRtn;
	}

	// 在运动状态下更新目标位置
	sRtn = GT_Update(1<<(iAxisNO[COORDI_AXISC]-1));
	if (sRtn != 0)
	{
		return sRtn;
	}

	do
	{
		// 读取轴状态
		sRtn = GT_GetSts(iAxisNO[COORDI_AXISC], &status);
		if (sRtn != 0)
		{
			break;
		}

		// 读取规划位置
		sRtn = GT_GetPrfPos(iAxisNO[COORDI_AXISC], &prfPos);
		if (sRtn != 0)
		{
			break;
		}

		// 读取编码器位置
		sRtn = GT_GetEncPos(iAxisNO[COORDI_AXISC], &encPos);
		if (sRtn != 0)
		{
			break;
		}
		// 等待运动停止
	}while( status & 0x400 );

	if (sRtn != 0)
	{
		return sRtn;
	}

	// 检查是否到达"Home捕获位置+偏移量"
	if( prfPos != pos+HOME_OFFSET )
	{
		//AfxMessageBox(("C轴回零未成功"));
	}

	//等待运动完成开始
	while(IsMoving(iAxisNO,iLen)==1)
	{
		//Sleep(100);
		//////////////////////////////////////////////////////////////////////////
		//??
		//////////////////////////////////////////////////////////////////////////
	}
	//等待运动完成结束
	for (int i=0; i<iLen; i++)
	{
		sRtn = GT_ZeroPos(iAxisNO[i]);
		double dPos =0;
		GT_GetPrfPos(iAxisNO[i],&dPos);
		if (sRtn != 0)
		{
			break;
		}
		if ((fabs(dPos))>0.001)
		{
			sRtn = GT_ZeroPos(iAxisNO[i]);
			double dPos =0;
			GT_GetPrfPos(iAxisNO[i],&dPos);
			if (sRtn != 0)
			{
				break;
			}
			if ((fabs(dPos))>0.001)
			{
				//AfxMessageBox(("清零未成功"));
			}
		}
	}
*/
	return sRtn;
}

int CGoogolGTSControl::ZeroPos(int* iAxisNO, int iLen)
{
	short sRtn = 0;
	//等待运动完成结束
	for (int i = 0; i<iLen; i++)
	{
		Mutex::Lock lock(m_mutex);

		sRtn = GT_ZeroPos(iAxisNO[i]);
		double dPos = 0;
		sRtn = GT_GetPrfPos(iAxisNO[i], &dPos);
		if (sRtn != 0)
		{
			break;
		}
		if ((fabs(dPos))>0.001)
		{
			sRtn = GT_ZeroPos(iAxisNO[i]);
			double dPos = 0;
			GT_GetPrfPos(iAxisNO[i], &dPos);
			if (sRtn != 0)
			{
				break;
			}
			if ((fabs(dPos))>0.001)
			{
				return -1;
			}
		}
	}

	return sRtn;
}

int CGoogolGTSControl::GoOriginLimit(int* iAxisNO, int iLen, int* iDirect,double* dHomeOff)
{
	short sRtn = 0, capture = 0;
	TTrapPrm trapPrm;
	long status, pos;
	double prfPos, encPos, axisPrfPos, axisEncPos;
	long dCapPos[8];

	// 清除各轴的报警和限位
	{
		Mutex::Lock lock(m_mutex);

		sRtn = GT_ClrSts(1, MAX_AXISNUM);
		if (sRtn != 0)
		{
			return sRtn;
		}
	}

	//去限位
	sRtn = JogMove(iAxisNO, iLen, iDirect);
	Sleep(100);
	if (sRtn != 0)
	{
		return sRtn;
	}
	//等待运动完成
	while (1 ==IsMoving(iAxisNO, iLen))
	{
		Sleep(100);
	}

	//检测限位是否触发
	bool bAllLimitOver = true;
	for (int i = 0; i < iLen; i++)
	{
		int iLimitP = 0;
		int iLimitN = 0;
		sRtn = GetLimitStatus(iAxisNO[i], &iLimitP, &iLimitN);
		if (iDirect[i] == 1)
		{
			if (iLimitP != 1)
			{
				bAllLimitOver = false;
			}
		}
		else if (iDirect[i] == -1)
		{
			if (iLimitN != 1)
			{
				bAllLimitOver = false;
			}
		}
	}

	if (!bAllLimitOver)
		return -1;
	if (sRtn != 0)
	{
		return sRtn;
	}

	while (IsMoving(iAxisNO, iLen) == 1)
	{
		Sleep(100);
	}

	//偏移运动
	double* posDec2 = new double[iLen];
	for (int i = 0; i < iLen; i++)
	{
		double dPos = 0;
		sRtn = GetRealTimePos(iAxisNO[i], &dPos);
		if (sRtn != 0)
		{
			break;
		}
		posDec2[i] = dPos + dHomeOff[i];
	}
	if (sRtn != 0)
	{
		return sRtn;
	}
	sRtn = PTPMoveTo(iAxisNO, iLen, posDec2, true);
	Sleep(100);
	if (sRtn != 0)
	{
		return sRtn;
	}

	//清零
	sRtn = ZeroPos(iAxisNO, iLen);

	delete[] posDec2;
	posDec2 = nullptr;

	return sRtn;
}

int CGoogolGTSControl::GoOriginHome(int* iAxisNO, int iLen, int* iDirect, double* orgmove,double* dHomeOff)
{
	int sRtn = 0;
	// 清除各轴状态
	{
		Mutex::Lock lock(m_mutex);

		sRtn = GT_ClrSts(1, MAX_AXISNUM);
		if (sRtn != 0)
		{
			return sRtn;
		}
	}

	//开启Home捕获
	for (int i = 0; i<iLen; i++)
	{
		{
			Mutex::Lock lock(m_mutex);
			sRtn = GT_SetCaptureMode(iAxisNO[i], CAPTURE_HOME);
			if (sRtn != 0)
			{
				break;
			}
		}
	}
	if (sRtn != 0)
	{
		return sRtn;
	}
	//开启运动
	double* posDec = new double[iLen];
	for (int i = 0; i < iLen; i++)
	{
		double dPos = 0;
		sRtn = GetRealTimePos(iAxisNO[i], &dPos);
		if (sRtn != 0)
		{
			break;
		}
		posDec[i] = dPos + orgmove[i];
	}
	if (sRtn != 0)
	{
		return sRtn;
	}
	sRtn = PTPMoveTo(iAxisNO, iLen, posDec,false);
	Sleep(100);
	if (sRtn != 0)
	{
		return sRtn;
	}

	//等待Home捕获
	bool bAllCaption = true;
	bool bSubbenStop = true;
	long* lCapPos = new long[iLen];
	do
	{
		bAllCaption = true;
		for (int i = 0; i < iLen; i++)
		{
			short capture = 0;
			{
				Mutex::Lock lock(m_mutex);
				sRtn = GT_GetCaptureStatus(iAxisNO[i], &capture, &(lCapPos[i]));
				if (sRtn != 0)
				{
					break;
				}
			}
			if (capture == 1)
			{
				int iAxisOne[1] = { iAxisNO[i] };
				Stop(iAxisOne, 1, SuddenStop);
				break;
			}
			else
			{
				bAllCaption = false;
			}
			
		}
		//运动停止后，还没有捕获信号
		if (!bAllCaption)
		{
			if (0 == IsMoving(iAxisNO, iLen))
			{
				sRtn = -2;
				return sRtn;
			}
		}

		Sleep(100);
	} while (!bAllCaption);
	if (sRtn != 0)
	{
		return sRtn;
	}
	//等待运动完成
	while (IsMoving(iAxisNO, iLen) == 1)
	{
		Sleep(100);
	}

	//运动到Caption位 
	double* posDec1 = new double[iLen];
	for (int i = 0; i < iLen; i++)
	{
		posDec1[i] = lCapPos[i];
	}
	sRtn = PTPMoveTo(iAxisNO, iLen, posDec1, true);
	Sleep(100);
	if (sRtn != 0)
	{
		return sRtn;
	}
	while (IsMoving(iAxisNO, iLen) == 1)
	{
		Sleep(100);
	}

	//偏移运动
	double* posDec2 = new double[iLen];
	for (int i = 0; i < iLen; i++)
	{
		double dPos = 0;
		sRtn = GetRealTimePos(iAxisNO[i], &dPos);
		if (sRtn != 0)
		{
			break;
		}
		posDec2[i] = dPos + dHomeOff[i];
	}
	if (sRtn != 0)
	{
		return sRtn;
	}
	sRtn = PTPMoveTo(iAxisNO, iLen, posDec2, true);
	Sleep(100);
	if (sRtn != 0)
	{
		return sRtn;
	}

	//清零
	sRtn = ZeroPos(iAxisNO, iLen);

	delete[] posDec;
	delete[] posDec1;
	delete[] posDec2;
	delete[] lCapPos;
	posDec = nullptr;
	posDec1 = nullptr;
	posDec2 = nullptr;
	lCapPos = nullptr;

	return sRtn;
}

int CGoogolGTSControl::GoOriginIndex(int* iAxisNO, int iLen, int* iDirect, double* orgmove, double* dHomeOff)
{
	int sRtn = 0;
	// 清除各轴状态
	{
		Mutex::Lock lock(m_mutex);

		sRtn = GT_ClrSts(1, MAX_AXISNUM);
		if (sRtn != 0)
		{
			return sRtn;
		}
	}

	//开启Index捕获
	for (int i = 0; i<iLen; i++)
	{
		{
			Mutex::Lock lock(m_mutex);
			sRtn = GT_SetCaptureMode(iAxisNO[i], CAPTURE_INDEX);
			if (sRtn != 0)
			{
				break;
			}
		}
	}
	if (sRtn != 0)
	{
		return sRtn;
	}
	//开启运动
	double* posDec = new double[iLen];
	for (int i = 0; i < iLen; i++)
	{
		double dPos = 0;
		sRtn = GetRealTimePos(iAxisNO[i], &dPos);
		if (sRtn != 0)
		{
			break;
		}
		posDec[i] = dPos + orgmove[i];
	}
	if (sRtn != 0)
	{
		return sRtn;
	}
	sRtn = PTPMoveTo(iAxisNO, iLen, posDec, false);
	Sleep(100);
	if (sRtn != 0)
	{
		return sRtn;
	}

	//等待Index捕获
	bool bAllCaption = true;
	bool bSubbenStop = true;
	long* lCapPos = new long[iLen];
	do
	{
		bAllCaption = true;
		for (int i = 0; i < iLen; i++)
		{
			short capture = 0;
			{
				Mutex::Lock lock(m_mutex);
				sRtn = GT_GetCaptureStatus(iAxisNO[i], &capture, &(lCapPos[i]));
				if (sRtn != 0)
				{
					break;
				}
			}
			if (capture == 1)
			{
				int iAxisOne[1] = { iAxisNO[i] };
				Stop(iAxisOne, 1, SuddenStop);
				break;
			}
			else
			{
				bAllCaption = false;
			}
		}
		//运动停止后，还没有捕获信号
		if (!bAllCaption)
		{
			if (0 == IsMoving(iAxisNO, iLen))
			{
				sRtn = -2;
				return sRtn;
			}
		}

		Sleep(100);
	} while (!bAllCaption);
	if (sRtn != 0)
	{
		return sRtn;
	}
	//等待运动完成
	while (IsMoving(iAxisNO, iLen) == 1)
	{
		Sleep(100);
	}

	//运动到Caption位 
	double* posDec1 = new double[iLen];
	for (int i = 0; i < iLen; i++)
	{
		posDec1[i] = lCapPos[i];
	}
	sRtn = PTPMoveTo(iAxisNO, iLen, posDec1, true);
	Sleep(100);
	if (sRtn != 0)
	{
		return sRtn;
	}
	while (IsMoving(iAxisNO, iLen) == 1)
	{
		Sleep(100);
	}
	//偏移运动
	double* posDec2 = new double[iLen];
	for (int i = 0; i < iLen; i++)
	{
		double dPos = 0;
		sRtn = GetRealTimePos(iAxisNO[i], &dPos);
		if (sRtn != 0)
		{
			break;
		}
		posDec2[i] = dPos + dHomeOff[i];
	}
	if (sRtn != 0)
	{
		return sRtn;
	}
	sRtn = PTPMoveTo(iAxisNO, iLen, posDec2, true);
	Sleep(100);
	if (sRtn != 0)
	{
		return sRtn;
	}

	//清零
	sRtn = ZeroPos(iAxisNO, iLen);

	delete[] posDec;
	delete[] posDec1;
	delete[] posDec2;
	delete[] lCapPos;
	posDec = nullptr;
	posDec1 = nullptr;
	posDec2 = nullptr;
	lCapPos = nullptr;

	return sRtn;
}

int CGoogolGTSControl::Stop(int* iAxisNO, int iCount, StopMode Type)
{
	int iRet = 0;
	long mask = 0;
	long option = 0xFFFFFFFF;
	for (int i=0; i<iCount; i++)
	{
		mask = mask | (1<<(iAxisNO[i]-1));
		if (Type == SuddenStop)
		{
			option = option | (1<<(iAxisNO[i]-1));
		}
		else // == SlowStop
		{
			option = option & (~(1<<(iAxisNO[i]-1)));
		}		
	}
	Mutex::Lock lock(m_mutex);

	iRet = GT_Stop(mask,option);
    return iRet;
}

int CGoogolGTSControl::JogMove(int* iEnableAxis, int iLen, int* iDirection)
{
	short sRtn = 0;
	TJogPrm jog;
	long sts;
	double prfPos, prfVel;
	// 清除各轴的报警和限位
	{
		Mutex::Lock lock(m_mutex);

		sRtn = GT_ClrSts(1, MAX_AXISNUM);
		if (sRtn != 0)
		{
			return sRtn;
		}
	}

	for (int i = 0; i<iLen; i++)
	{
		Mutex::Lock lock(m_mutex);

		// 将AXIS轴设为Jog模式
		sRtn = GT_PrfJog(iEnableAxis[i]);
		if (sRtn != 0)
		{
			break;
		}
		// 读取Jog运动参数
		sRtn = GT_GetJogPrm(iEnableAxis[i], &jog);
		if (sRtn != 0)
		{
			break;
		}
		jog.acc = m_pGetMI->dAccArray[iEnableAxis[i]-1];
		jog.dec = m_pGetMI->dDecArray[iEnableAxis[i]-1];
		// 设置Jog运动参数
		sRtn = GT_SetJogPrm(iEnableAxis[i], &jog);
		if (sRtn != 0)
		{
			break;
		}
		// 设置AXIS轴的目标速度
		sRtn = GT_SetVel(iEnableAxis[i], m_pGetMI->dHighVelArray[iEnableAxis[i]-1] *iDirection[i]);
		if (sRtn != 0)
		{
			break;
		}
		// 启动AXIS轴的运动
		sRtn = GT_Update(1 << (iEnableAxis[i] - 1));
		if (sRtn != 0)
		{
			break;
		}
	}

	return sRtn;
}

int CGoogolGTSControl::CoorInit(int* iAxisNo,int iCoorAxisNum,double dMaxVel,double dMaxAcc,short dEvenTime,long* lZeroOff,double dCornerTime)
{
	short sRtn = 0;
	TCrdPrm crdPrm;
	memset(&crdPrm, 0, sizeof(crdPrm));
	crdPrm.dimension = iCoorAxisNum;                        // 建立三维的坐标系
	crdPrm.synVelMax = dMaxVel;                      // 坐标系的最大合成速度
	crdPrm.synAccMax = dMaxAcc;                        // 坐标系的最大合成加速度
	crdPrm.evenTime = dEvenTime;                         // 坐标系的最小匀速时间
	for (int i = 0; i < iCoorAxisNum;i++)
	{
		crdPrm.profile[i] = iAxisNo[i];                       // 规划器对应到坐标系轴
	}
	//设定零点偏移
	crdPrm.setOriginFlag = 1;                    // 需要设置加工坐标系原点位置
	for (int i = 0; i < iCoorAxisNum; i++)
	{
		crdPrm.originPos[i] = lZeroOff[i];
	}

	Mutex::Lock lock(m_mutex);

	sRtn = GT_SetCrdPrm(1, &crdPrm);
	if (sRtn != 0)
	{
		return sRtn;
	}
	rtn = GT_CrdClear(1, 0);
	if (sRtn != 0)
	{
		return sRtn;
	}
	//初始化200段的前瞻缓冲区
	// 定义前瞻缓存区内存区
	TCrdData crdData[200];
	rtn = GT_InitLookAhead(1, 0, dCornerTime, dMaxAcc, 200, crdData);

	return sRtn;
}

int CGoogolGTSControl::CoorCrdData()
{
	Mutex::Lock lock(m_mutex);

	return GT_CrdData(1, NULL, 0);
}

int CGoogolGTSControl::CoorLnXY(long lX,long lY,double dVel,double dAcc)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_LnXY(1, lX,lY,dVel,dAcc);
	return sRtn;
}

int CGoogolGTSControl::CoorLnXYZ(long lX, long lY, long lZ ,double dVel, double dAcc)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_LnXYZ(1, lX, lY, lZ, dVel, dAcc);
	return sRtn;
}

int CGoogolGTSControl::CoorLnXYZA(long lX, long lY, long lZ, long lA, double dVel, double dAcc)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_LnXYZA(1, lX, lY, lZ, lA, dVel, dAcc);
	return sRtn;
}
int CGoogolGTSControl::CoorLnXYG0(long lX, long lY, double dVel, double dAcc)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_LnXYG0(1, lX, lY, dVel, dAcc);
	return sRtn;
	return 0;
}

int CGoogolGTSControl::CoorLnXYZG0(long lX, long lY, long lZ, double dVel, double dAcc)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_LnXYZG0(1, lX, lY, lZ, dVel, dAcc);
	return sRtn;
}

int CGoogolGTSControl::CoorLnXYZAG0(long lX, long lY, long lZ, long lA, double dVel, double dAcc)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_LnXYZAG0(1, lX, lY, lZ, lA, dVel, dAcc);
	return sRtn;
}

int CGoogolGTSControl::CoorArcXYR(long lX, long lY, double dRadius, short sCircleDir, double dVel, double dAcc)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_ArcXYR(1, lX, lY, dRadius,sCircleDir, dVel, dAcc);
	return sRtn;
}

int CGoogolGTSControl::CoorArcXYC(long lX, long lY, double dXCenter, double dYCenter, short sCircleDir, double dVel, double dAcc)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_ArcXYC(1, lX, lY, dXCenter,dYCenter, sCircleDir, dVel, dAcc);
	return sRtn;
}

int CGoogolGTSControl::CoorArcYZR(long lY, long lZ, double dRadius, short sCircleDir, double dVel, double dAcc)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_ArcYZR(1, lY, lZ, dRadius,sCircleDir, dVel, dAcc);
	return sRtn;
}

int CGoogolGTSControl::CoorArcYZC(long lY, long lZ, double dYCenter, double dZCenter, short sCircleDir, double dVel, double dAcc)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_ArcYZC(1, lY, lZ, dYCenter,dZCenter, sCircleDir, dVel, dAcc);
	return sRtn;
}

int CGoogolGTSControl::CoorArcZXR(long lZ, long lX, double dRadius, short sCircleDir, double dVel, double dAcc)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_ArcZXR(1, lZ, lX, dRadius, sCircleDir, dVel, dAcc);
	return sRtn;
}

int CGoogolGTSControl::CoorArcZXC(long lZ, long lX, double dZCenter, double dXCenter, short sCircleDir, double dVel, double dAcc)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_ArcZXC(1, lZ, lX, dZCenter, dXCenter, sCircleDir, dVel, dAcc);
	return sRtn;
}

//通用数字量输出
int CGoogolGTSControl::CoorBufIO(unsigned short doMask, unsigned short doValue)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_BufIO(1,MC_GPO, doMask, doValue);
	return sRtn;
}

int CGoogolGTSControl::CoorBufDelay(unsigned short usDelayTime)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_BufDelay(1, usDelayTime);
	return sRtn;
}

int CGoogolGTSControl::CoorBufMove(short sAxisNO, long lPos,double dVel,double dAcc,short sModal)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_BufMove(1, sAxisNO,lPos,dVel,dAcc,sModal);
	return sRtn;
}

int CGoogolGTSControl::CoorGetSpace(long* plSpace)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_CrdSpace(1, plSpace);
	return sRtn;
}

int CGoogolGTSControl::CoorClear()
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_CrdClear(1, 0);
	return sRtn;
}

int CGoogolGTSControl::CoorStart(int iCoorNo)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	if (iCoorNo == 1)	//启动坐标系1的fifo0
	{
		sRtn = GT_CrdStart(0x1, 0);
	}
	else if (iCoorNo == 2)	//启动坐标系2的fifo0
	{
		sRtn = GT_CrdStart(0x2, 0);
	}
	else
	{
		sRtn = -1;
	}
	return sRtn;
}

int CGoogolGTSControl::CoorGetSts(short* psRun, long* plSegment)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_CrdStatus(1, psRun,plSegment,0);
	return sRtn;
}

int CGoogolGTSControl::CoorSetStopDec(double dSmoothStopDec,double dAbruptStopDec)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_SetCrdStopDec(1, dSmoothStopDec, dAbruptStopDec);
	return sRtn;
}

int CGoogolGTSControl::CoorSetOverride(double dVelRatio)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_SetOverride(1, dVelRatio);
	return sRtn;
}

int CGoogolGTSControl::CoorGetPos(double* pdCrdPos)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_GetCrdPos(1, pdCrdPos);
	return sRtn;
}

int CGoogolGTSControl::CoorGetVel(double* pdCrdVel)
{
	Mutex::Lock lock(m_mutex);

	short sRtn = 0;
	sRtn = GT_GetCrdVel(1, pdCrdVel);
	return sRtn;
}

int CGoogolGTSControl::TestPPM(int iAxisNO, int iPulseCount)
{
	//AfxMessageBox(("Aerotech 数控系统不需要在PC软件端设置脉冲当量"));
	return 0;
}

int CGoogolGTSControl::SetAbsPos(int iAxisNO, double dPos)
{	
	//AfxMessageBox(("设置绝对坐标模式出错"));
	return 0;
}

int CGoogolGTSControl::LaserOn(int iLaserBit, int* iOutStatus)
{
	Mutex::Lock lock(m_mutex);

	return GT_SetHSIOOpt(1,iLaserBit);
}

int CGoogolGTSControl::LaserOff(int iLaserBit, int* iOutStatus)
{
	Mutex::Lock lock(m_mutex);

	return GT_SetHSIOOpt(0,iLaserBit);
}

int CGoogolGTSControl::GasOpen(int iGasBit, int* iOutStatus)
{
	return OutputBit(1, iGasBit, 0, iOutStatus);
}

int CGoogolGTSControl::GasClose(int iGasBit, int* iOutStatus)
{
	return OutputBit(1, iGasBit, 1, iOutStatus);
}

int CGoogolGTSControl::AbsorptionOpen(int iAbsorptionBit, int* iOutStatus)
{
	return OutputBit(1, iAbsorptionBit, 1, iOutStatus);
}

int CGoogolGTSControl::AbsorptionClose(int iAbsorptionBit, int* iOutStatus)
{
	return OutputBit(1, iAbsorptionBit, 0, iOutStatus);
}

int CGoogolGTSControl::PauseMove()
{
	return 0;
}

int CGoogolGTSControl::RestorationMove()
{
	bool bValue = true;
	return 0;
}

int CGoogolGTSControl::SetCardNO(short cardNO)
{
	Mutex::Lock lock(m_mutex);

	return GT_SetCardNo(cardNO);
}

int CGoogolGTSControl::GetCardNO(short* cardNO)
{
	Mutex::Lock lock(m_mutex);

	return GT_GetCardNo(cardNO);
}

int CGoogolGTSControl::SetLaserOut(double dFrequence, double dLaserPrf,int iChannel)
{
	Mutex::Lock lock(m_mutex);

	int iRet =0;

	iRet = GT_LaserOutFrq(dFrequence,iChannel);
	iRet = GT_LaserPrfCmd(dLaserPrf,iChannel);
	return iRet;
}