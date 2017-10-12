// GoogolControl.cpp: implementation of the CGoogolGESControl class.
/*
 * CopyRight (c) 2017
 * All Rights reserved
 *
 * File Name		: GoogolControl.cpp
 * File ID			: None
 * Sumary			: For Googol
 *
 * Current Version	: 1.0.0
 * Author			: Jackie Wu
 * Finish Time		: 2017-2-27
 * Last Modify Time : 2017-2-27
*/
//#include "stdafx.h"
#include "GoogolGESControl.h"

#define SEARCH_HOME		-12000000
#define HOME_OFFSET		-2000

CGoogolGESControl::CGoogolGESControl(void)
{
	m_pdHighSpeed = nullptr;
	m_pdLowSpeed = nullptr;
	m_pdAcc = nullptr;
	m_pdDec = nullptr;
}

CGoogolGESControl::~CGoogolGESControl(void)
{
	if (m_pdHighSpeed != nullptr)
	{
		delete[] m_pdHighSpeed;
		m_pdHighSpeed = nullptr;
	}
	if (m_pdLowSpeed != nullptr)
	{
		delete[] m_pdLowSpeed;
		m_pdLowSpeed = nullptr;
	}
	if (m_pdAcc != nullptr)
	{
		delete[] m_pdAcc;
		m_pdAcc = nullptr;
	}
	if (m_pdDec != nullptr)
	{
		delete[] m_pdDec;
		m_pdDec = nullptr;
	}
}

int CGoogolGESControl::Init(int* enableAxis, int iEnableAxisNum, int* iCardNum, void* pToSelf)
{
	unsigned short val = 0;
	long rtn = 0;

	rtn =GT_SwitchtoCardNo(0);
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

	unsigned short usLimitSts, usTempLimitSts, usTempLimitSts1;
	usTempLimitSts = 0x0000;
	//直接设置为开环控制
	for (int i=0; i<iEnableAxisNum; i++)
	{
		//2017/4/12 目前默认使用脉冲+方向控制。 不使用模拟量闭环控制
		rtn = GT_CtrlMode(enableAxis[i], 1);
		if (rtn !=0 )
		{
			break;
		}
		rtn = GT_AlarmOff(enableAxis[i]);
		if (rtn !=0 )
		{
			break;
		}
 		// 配置各轴正负限位有效和电平触发状态
		rtn = GT_LmtsOff(enableAxis[i]);
 		if (rtn !=0 )
 		{
 			break;
 		}

		rtn = GT_ClrSts(enableAxis[i]);
		if (rtn != 0)
		{
			break;
		}
		rtn = GT_AxisOn(enableAxis[i]);
		if (rtn != 0)
		{
			break;
		}
	}
	if (rtn != 0)
	{
		return rtn;
	}
	
	return rtn;
}

int CGoogolGESControl::Init(int* enableAxis, int iEnableAxisNum, int* iCardNum, double* pdLimitDir)
{
	unsigned short val = 0;
	long rtn = 0;

	rtn = GT_SwitchtoCardNo(0);
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

	unsigned short usLimitSts, usTempLimitSts, usTempLimitSts1;
	usTempLimitSts = 0x0000;
	//直接设置为开环控制
	for (int i = 0; i<iEnableAxisNum; i++)
	{
		//2017/4/12 目前默认使用脉冲+方向控制。 不使用模拟量闭环控制
		rtn = GT_CtrlMode(enableAxis[i], 1);
		if (rtn != 0)
		{
			break;
		}
		rtn = GT_AlarmOff(enableAxis[i]);
		if (rtn != 0)
		{
			break;
		}
		// 配置各轴正负限位有效和电平触发状态
		rtn = GT_LmtsOn(enableAxis[i]);
		if (rtn != 0)
		{
			break;
		}
		if (pdLimitDir[i] == -1)
		{
			usTempLimitSts1 = 0x0001 << (enableAxis[i] - 1);
			usTempLimitSts = usTempLimitSts | usTempLimitSts1;
		}

		rtn = GT_ClrSts(enableAxis[i]);
		if (rtn != 0)
		{
			break;
		}
		rtn = GT_AxisOn(enableAxis[i]);
		if (rtn != 0)
		{
			break;
		}
	}
	if (rtn != 0)
	{
		return rtn;
	}

	//设置限位触发电平
	usLimitSts = 0xffff & usTempLimitSts;
	rtn = GT_LmtSns(usLimitSts);
	if (rtn == 0)
	{
		m_bInit = true;
	}

	return rtn;
}

int CGoogolGESControl::Close()
{
	GT_Close();
	return 0;
}

int CGoogolGESControl::OutputBit(int iCardNO, int bitNO, int iStatus, int* iOutStatus)
{
	int rtn = 0;
	/*	unsigned short outSts;
	rtn = GT_GetExOpt(&outSts);
	if (iStatus == 0)
	{
		outSts = outSts & (0xFFFE << bitNO);
	}
	else
	{
		outSts = outSts | (0x0001 << bitNO);
	}
	rtn = GT_ExOpt(outSts);
	if (rtn != 0)
		return rtn;

	rtn = GT_GetExOpt(&outSts);
	iOutStatus = (int*)outSts;
*/
	return GT_ExOptBit(bitNO, iStatus);
}

int CGoogolGESControl::Output(int iCard,int iOutState)
{
	rtn = GT_ExOpt(iOutState);
	if (rtn != 0)
		return rtn;

	return 0;
}

int CGoogolGESControl::GetRealTimePos(int iAxisNO, double* dRealTimePos)
{
	int iRtn = 0;
	double dRealPos[8];
	iRtn = GT_GetPrfPnt(dRealPos);
	*dRealTimePos = dRealPos[iAxisNO-1];

	return iRtn;
}

//多轴联动插补
int CGoogolGESControl::MoveTo(int* iEnableCoor, int iAxisPosNum, double* posTarget,int iType)
{
	int iRtn = 0;

	//清除轴报警状态
	for (int i = 0; i < iAxisPosNum; i++)
	{
		iRtn = GT_ClrSts(iEnableCoor[i]);
	}
	/*
	//SetSpeed
	iRtn = GT_SetStrtVel(m_pdLowSpeed[0]);
	if (iType == 5)
	{
		iRtn += GT_SetSynAcc(m_pdHighSpeed[0]/10);
	}
	else
	{
		iRtn += GT_SetSynAcc(m_pdHighSpeed[0]);
	}
	iRtn += GT_SetSynVel(m_pdAcc[0]);
	iRtn += GT_SetStpAcc(m_pdDec[0]);
	iRtn += GT_SetEStpAcc(m_pdDec[0]);
	
	if (iRtn)
	{
		return iRtn;
	}
	*/

	//获取当前位置
	double posCurrent[4] = {0,0,0,0};
	iRtn = GT_GetPrfPnt(posCurrent);	//读取各轴的当前位置

	//MoveTo
	double dXPos = posCurrent[0];
	double dYPos = posCurrent[1];
	double dZPos = posCurrent[2];
	double dAPos = posCurrent[3];
	for (int i = 0; i<iAxisPosNum; i++)
	{
		if (iEnableCoor[i] == 0)
		{
			dXPos = posTarget[i];
		}
		else if (iEnableCoor[i] == 1)
		{
			dYPos = posTarget[i];
		}
		else if (iEnableCoor[i] == 2)
		{
			dZPos = posTarget[i];
		}
		else if (iEnableCoor[i] == 3)
		{
			dAPos = posTarget[i];
		}
	}
	iRtn = GT_LnXYZA(dXPos, dYPos, dZPos, dAPos);
	if (iRtn)
	{
		return iRtn;
	}

	//等待运动完成

		//Sleep(200);
		unsigned short crd_status;
		do
		{
			GT_GetCrdSts(&crd_status); //读取坐标系状态
		} while (!(crd_status & 1)); //等待运动完成

	return 0;
}

//bSleep:是否等待运动完成
int CGoogolGESControl::MoveTo(int* iEnableAxis, int iAxisPosNum, double* posTarget,int iType, bool bSleep)
{
	int iRtn = 0;

	//清除轴报警状态
	for (int i = 0; i < iAxisPosNum; i++)
	{
		iRtn = GT_ClrSts(iEnableAxis[i]);
	}
	/*
	//SetSpeed
	iRtn = GT_SetStrtVel(m_pdLowSpeed[0]);
	if (iType == 5)
	{
	iRtn += GT_SetSynAcc(m_pdHighSpeed[0]/10);
	}
	else
	{
	iRtn += GT_SetSynAcc(m_pdHighSpeed[0]);
	}
	iRtn += GT_SetSynVel(m_pdAcc[0]);
	iRtn += GT_SetStpAcc(m_pdDec[0]);
	iRtn += GT_SetEStpAcc(m_pdDec[0]);

	if (iRtn)
	{
	return iRtn;
	}
	*/

	//获取当前位置
	double posCurrent[4] = { 0, 0, 0, 0 };
	iRtn = GT_GetPrfPnt(posCurrent);	//读取各轴的当前位置

	//MoveTo
	bool bAxis1Do = false;
	bool bAxis2Do = false;
	bool bAxis3Do = false;
	bool bAxis4Do = false;
	double dXPos = posCurrent[0];
	double dYPos = posCurrent[1];
	double dZPos = posCurrent[2];
	double dAPos = posCurrent[3];
	for (int i = 0; i<iAxisPosNum; i++)
	{
		if (iEnableAxis[i] == 1)
		{
			dXPos = posTarget[i];
			bAxis1Do = true;
		}
		else if (iEnableAxis[i] == 2)
		{
			dYPos = posTarget[i];
			bAxis2Do = true;
		}
		else if (iEnableAxis[i] == 3)
		{
			dZPos = posTarget[i];
			bAxis3Do = true;
		}
		else if (iEnableAxis[i] == 4)
		{
			dAPos = posTarget[i];
			bAxis4Do = true;
		}
	}

	if (bAxis4Do)
	{
		iRtn = GT_LnXYZA(dXPos, dYPos, dZPos, dAPos);
	}
	else if (bAxis3Do)
	{
		iRtn = GT_LnXYZ(dXPos, dYPos, dZPos);
	}
	else
	{
		iRtn = GT_LnXY(dXPos, dYPos);
	}
	if (iRtn)
	{
		return iRtn;
	}

	//等待运动完成
	if (bSleep)
	{
		//Sleep(200);
		unsigned short crd_status;
		do
		{
			GT_GetCrdSts(&crd_status); //读取坐标系状态
		} while (!(crd_status & 1)); //等待运动完成
	}

	return 0;
}

int CGoogolGESControl::SetSpeed(int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec, int iType)
{
	return 0;
}

int CGoogolGESControl::SetSpeed(double dHighSpeed, double dLowSpeed, double dAcc, double dDec)
{
	int iRtn = 0;
	iRtn = GT_SetStrtVel(dLowSpeed);
	iRtn += GT_SetSynAcc(dAcc);
	iRtn += GT_SetSynVel(dHighSpeed);
	iRtn += GT_SetStpAcc(dDec);
	iRtn += GT_SetEStpAcc(dDec * 5);	//急停减速度为平滑停止的5倍

	return iRtn;
}

//整体Home回零方式
int CGoogolGESControl::GoOrigin(int* iAxisNO, int* iDirect, int iLen, int* orgmove, bool bStyle)
{
	short sRtn =0;
	unsigned short crd_status,axis_status;

	// 清除各轴的报警和限位
	for (int i = 0; i < iLen; i++)
	{
		sRtn = GT_ClrSts(iAxisNO[i]);
	}

	//采用依次回零
	for (int i = 0; i < iLen; i++)
	{
		unsigned short iAxis = iAxisNO[i];
		int iHomeDirect = iDirect[i];
		
		int iAxisOne[1] = { iAxis };
		int iHomeDirectOne[1] = { -iHomeDirect };
		double dHomeCaptionOne[1] = { 0.0 };

		//运动到限位
		sRtn = JogMove(iAxisOne, 1, iHomeDirectOne,true);
		//开启Home
		GT_ClrSts(iAxis);		//清回原点轴状态
		GT_CaptHome(iAxis);		
		iHomeDirectOne[0] = iHomeDirect;
		sRtn = JogMove(iAxisOne, 1, iHomeDirectOne,false);
		do
		{
			GT_GetCrdSts(&crd_status); //读取坐标系状态
			if (crd_status & 1)		   //如果运动已经完成
			{ //仍然没有触发Home 信号
				return -1; //返回错误代码1
			}
			GT_GetSts(iAxis, &axis_status); //读取控制轴状态
		} while (!(axis_status & 0x8)); //等待Home 信号触发
		GT_StpMtn(); //平滑停止
		do
		{
			GT_GetCrdSts(&crd_status); //读取坐标系状态
		} while (!(crd_status & 1)); //等待运动完成

		long lpos;
		GT_GetCapt(iAxis, &lpos); //读取捕获位置
		dHomeCaptionOne[0] = lpos;
		MoveTo(iAxisOne, 1, dHomeCaptionOne, 0, true);
	}

	//等待运动完成开始
	while (IsMoving(iAxisNO, iLen) == 1)
	{
		//Sleep(100);
	}
	//等待运动完成结束
	for (int i=0; i<iLen; i++)
	{
		sRtn = GT_ZeroPos(iAxisNO[i]);
		if (sRtn != 0)
		{
			break;
		}
		double dPos[4] = {0,0,0,0};
		GT_GetPrfPnt(dPos);
		
		if ((fabs(dPos[iAxisNO[i]]))>0.001)
		{
			sRtn = GT_ZeroPos(iAxisNO[i]);
			GT_GetPrfPnt(dPos);
			if (sRtn != 0)
			{
				break;
			}
			if ((fabs(dPos[iAxisNO[i]]))>0.001)
			{
				//AfxMessageBox(("清零未成功"));
				return -1;
			}
		}
	}
	
	return sRtn;
}

//单次Home，方便设置速度
int CGoogolGESControl::GoOriginOne(int iAxisNO, int iDirect, int* orgmove, bool bStyle)
{
	short sRtn = 0;
	unsigned short crd_status, axis_status;

	// 清除轴的报警和限位
	sRtn = GT_ClrSts(iAxisNO);

	//采用依次回零
	unsigned short iAxis = iAxisNO;
	int iHomeDirect = iDirect;

	int iAxisOne[1] = { iAxis };
	int iHomeDirectOne[1] = { -iHomeDirect };
	double dHomeCaptionOne[1] = { 0.0 };

	//运动到限位
	sRtn = JogMove(iAxisOne, 1, iHomeDirectOne, true);
	//开启Home
	GT_ClrSts(iAxis);		//清回原点轴状态
	GT_CaptHome(iAxis);
	iHomeDirectOne[0] = iHomeDirect;
	sRtn = JogMove(iAxisOne, 1, iHomeDirectOne, false);
	do
	{
		GT_GetCrdSts(&crd_status); //读取坐标系状态
		if (crd_status & 1)		   //如果运动已经完成
		{ //仍然没有触发Home 信号
			return -1; //返回错误代码1
		}
		GT_GetSts(iAxis, &axis_status); //读取控制轴状态
	} while (!(axis_status & 0x8)); //等待Home 信号触发
	GT_StpMtn(); //平滑停止
	do
	{
		GT_GetCrdSts(&crd_status); //读取坐标系状态
	} while (!(crd_status & 1)); //等待运动完成

	long lpos;
	GT_GetCapt(iAxis, &lpos); //读取捕获位置
	dHomeCaptionOne[0] = lpos;
	MoveTo(iAxisOne, 1, dHomeCaptionOne, 0, true);

	//等待运动完成开始
	int iAxisL[4] = { 0, 1, 2, 3 };
	while (IsMoving(iAxisL, 4) == 1)
	{
		//Sleep(100);
	}
	//等待运动完成结束
	sRtn = GT_ZeroPos(iAxisNO);
	if (sRtn != 0)
	{
		return sRtn;
	}
	double dPos[4] = { 0, 0, 0, 0 };
	GT_GetPrfPnt(dPos);

	if ((fabs(dPos[iAxisNO]))>0.001)
	{
		sRtn = GT_ZeroPos(iAxisNO);
		GT_GetPrfPnt(dPos);
		if (sRtn != 0)
		{
			return sRtn;
		}
		if ((fabs(dPos[iAxisNO]))>0.001)
		{
			//AfxMessageBox(("清零未成功"));
			return -1;
		}
	}
	return sRtn;
}

int CGoogolGESControl::Stop(int* iAxisNO, int iCount, StopMode Type)
{
	return GT_StpMtn();
}

int CGoogolGESControl::Input(int iCardNO, int iBitNO)
{
	unsigned short sInputStatus;
	GT_ExInpt(&sInputStatus);
	if (sInputStatus&(0x1 << iBitNO))
	{
		return 1;
	}
	else
		return 0;
}

int CGoogolGESControl::GetOriginStatus(int iAxisNO)
{
	long sRtn;
	unsigned short sAxisStatus;					// 轴状态
	// 读取轴状态
	sRtn = GT_GetSts(iAxisNO, &sAxisStatus);
	// 在已经设置了Home捕获后，通过检测状态位
	if (sAxisStatus & 0x8)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int CGoogolGESControl::GetLimitStatus(int iAxisNO)
{
	long sRtn;
	unsigned short sAxisStatus;					// 轴状态
	int rtn = GT_ClrSts(iAxisNO);
	// 读取轴状态
	sRtn = GT_GetSts(iAxisNO, &sAxisStatus);
	// 正负限位
	if ((sAxisStatus & 0x20) || (sAxisStatus & 0x40))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int CGoogolGESControl::IsMoving(int* iAxisNO, int iLen)
{
	unsigned short crd_status;
	short sRtn = GT_GetCrdSts(&crd_status); //读取坐标系状态
	if (!(crd_status & 1))
		return 1;
	else
		return 0;
}

//通过运动一个极值的位置来模拟Jog模式
int CGoogolGESControl::JogMove(int* iEnableCoor, int iLen, int* iDirection)
{
	double dJogPos[4];
	for (int i = 0; i < iLen; i++)
	{
		dJogPos[i] = iDirection[i] * 100000000;
	}

	return MoveTo(iEnableCoor, iLen, dJogPos, 5);
}

int CGoogolGESControl::JogMove(int* iEnableCoor, int iLen, int* iDirection, bool bSleep)
{
	double dJogPos[4];
	for (int i = 0; i < iLen; i++)
	{
		dJogPos[i] = iDirection[i] * 100000000;
	}

	return MoveTo(iEnableCoor, iLen, dJogPos, 5, bSleep);
}

int CGoogolGESControl::TestPPM(int iAxisNO, int iPulseCount)
{
	//AfxMessageBox(("Aerotech 数控系统不需要在PC软件端设置脉冲当量"));
	return 0;
}

int CGoogolGESControl::SetAbsPos(int iAxisNO, double dPos)
{	
	//AfxMessageBox(("设置绝对坐标模式出错"));
	return 0;
}

int CGoogolGESControl::LaserOn(int iLaserBit, int* iOutStatus)
{
	return OutputBit(1, iLaserBit, 0, iOutStatus);
}

int CGoogolGESControl::LaserOff(int iLaserBit, int* iOutStatus)
{
	return OutputBit(1, iLaserBit, 1, iOutStatus);
}

int CGoogolGESControl::GasOpen(int iGasBit, int* iOutStatus)
{
	return OutputBit(1, iGasBit, 0, iOutStatus);
}

int CGoogolGESControl::GasClose(int iGasBit, int* iOutStatus)
{
	return OutputBit(1, iGasBit, 1, iOutStatus);
}

int CGoogolGESControl::AbsorptionOpen(int iAbsorptionBit, int* iOutStatus)
{
	return OutputBit(1, iAbsorptionBit, 1, iOutStatus);
}

int CGoogolGESControl::AbsorptionClose(int iAbsorptionBit, int* iOutStatus)
{
	return OutputBit(1, iAbsorptionBit, 0, iOutStatus);
}

int CGoogolGESControl::PauseMove()
{
	return 0;
}

int CGoogolGESControl::RestorationMove()
{
	return 0;
}

int CGoogolGESControl::SetCardNO(short cardNO)
{
	 return GT_SwitchtoCardNo(cardNO);
}

int CGoogolGESControl::GetCardNO(short* cardNO)
{
	*cardNO  = GT_GetCurrentCardNo();
	return 0;
}