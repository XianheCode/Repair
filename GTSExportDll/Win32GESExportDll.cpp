// Win32ExportDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Win32GESExportDll.h"

CMotionGESInterface motionCrl;


//初始化
int EC_Init()
{
	return motionCrl.Init(0);
}

//关闭
int EC_Close()
{
	return motionCrl.Close();
}


//按位输出信号
int EC_OutputBit(int bitNO, int iState)
{
	return motionCrl.OutputBit(bitNO, iState);
}

//输出信号
int EC_Output(int iOutState)
{
	return motionCrl.Output(iOutState);
}

//获取实时位置
int EC_GetRealTimePos(int iAxisNO, double* dRealTimePos)
{
	return motionCrl.GetPosCur(iAxisNO, dRealTimePos);
}

//点位运动移动到指定位置及运动模式,不用
int EC_PToPMove(int* iAxisNO, int iAxisPosNum, double* posTarget)
{
//	return motionCrl.PToPMove(iAxisNO, posTarget, iAxisPosNum);
	return 0;
}
//点位运动移动到指定位置及运动模式,使用
int EC_PToPMoveNew(int* iAxisNO, int iAxisPosNum, double* posTarget, int iMoveType, int iHandMoveSpeedType)
{
	return motionCrl.PToPMove(iAxisNO, posTarget, iAxisPosNum, iMoveType, iHandMoveSpeedType);
}

//设置速度及速度模式
int EC_SetPtoPSpeed(int iType, int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec)
{
	return motionCrl.SetPtoPSpeed(iType, iAxisNO, iAxisNum, dHighSpeed, dLowSpeed, dAcc, dDec);
}

//点位运动移动到指定位置及运动模式，不用
int EC_StepMove(int* iAxisNO, int iAxisPosNum, double* posStep)
{
	return motionCrl.StepPtoPMove(iAxisNO, iAxisPosNum, posStep);
}

//点位运动移动到指定位置及运动模式，使用
int EC_StepMoveNew(int* iAxisNO, int iAxisPosNum, double* posStep, int iMoveType, int iHandMoveSpeedType)
{
	return motionCrl.StepPtoPMove(iAxisNO, iAxisPosNum, posStep, iMoveType, iHandMoveSpeedType);
}

//设置速度及速度模式
int EC_SetStepSpeed(int iType, int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec)
{
	return motionCrl.SetStepPtoPSpeed(iType, iAxisNO, iAxisNum, dHighSpeed, dLowSpeed, dAcc, dDec);
}

//回原点
int EC_Home()
{
	return motionCrl.GoOrigin();
}

//停止
int EC_Stop()
{
	return motionCrl.Stop();
}

//输入信号
int EC_Input(int iBitNO)
{
	return  motionCrl.Input(iBitNO);
}

//获取轴原点状态
bool EC_GetOriginStatusAxis(int iAxisNO)
{
	//return motionCrl.GetOriginStatus(iAxisNO);
	return 0;
}

//获取轴原点状态
bool EC_GetOriginStatus()
{
	return motionCrl.GetOriginStatus();
}

//获取轴限位状态
bool EC_GetLimitStatusAxis(int iAxisNO)
{
	//return motionCrl.GetLaserStatus(iAxisNO);
	return true;
}

//获取轴限位状态
bool EC_GetLimitStatus()
{
	return motionCrl.GetLaserStatus();
}

//获取轴是运动状态
int EC_IsMoving(int* iAxisNO, int iLen)
{
	return motionCrl.IsMoving(iAxisNO, iLen);
}

//持续运动，不用
int EC_JogMove(int* iAxisNO, int iLen, int* iDirection)
{
	return motionCrl.JogMove(iAxisNO, iLen, iDirection);
}

//持续运动，使用
int EC_JogMoveNew(int* iAxisNO, int iLen, int* iDirection, int iHandMoveSpeedType)
{
	return motionCrl.JogMove(iAxisNO, iLen, iDirection, iHandMoveSpeedType);
}

int EC_SetJogSpeed(int iType, int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec)
{
	return motionCrl.SetJogSpeed(iType, iAxisNO, iAxisNum, dHighSpeed, dLowSpeed, dAcc, dDec);
}

//设轴绝对坐标
double EC_SetAbsPos(int iAxisNO, double dPos)
{
	return motionCrl.SetAbsPos(iAxisNO, dPos);
}

//开激光
int EC_LaserOn(int iLaserBit)
{
	return motionCrl.LaserOn(iLaserBit);
}

//关激光
int EC_LaserOff(int iLaserBit)
{
	return motionCrl.LaserOff(iLaserBit);
}

//吹气
int EC_GasOpen(int iGasBit)
{
	return motionCrl.GasOpen(iGasBit);
}

//关气
int EC_GasClose(int iGasBit)
{
	return motionCrl.GasClose(iGasBit);
}

//开吸附
int EC_AbsorptionOpen(int iAbsorptionBit)
{
	return motionCrl.AbsorptionOpen(iAbsorptionBit);
}

//关吸附
int EC_AbsorptionClose(int iAbsorptionBit)
{
	return motionCrl.AbsorptionClose(iAbsorptionBit);
}

//暂停运动
int EC_PauseMove()
{
	return motionCrl.Pause();
}

//继续运动
//int RestorationMove()
//{
//	return motionCrl.m_ControlGESInterface
//}

//设置当前卡号
int EC_SetCardNO(short cardNO)
{
	//return SetCardNO(cardNO);
	return 0;
}

//获取当前卡号
int EC_GetCardNO(short* cardNO)
{
	//return motionCrl.get
	return 0;
}

bool EC_ExeSetParamApplication()
{
	return motionCrl.SetConfigApplication();
}

//更新加工参数
bool EC_UpdateMoveParam()
{
	return motionCrl.Init(0);
}