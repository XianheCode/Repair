// Win32ExportDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "GTSExportDll.h"

#include "./Googol/MotionInterface.h"

CMotionInterface motionCrl;


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

//点位运动移动到指定位置及运动模式
int EC_PToPMove(TPTPPrm movePrm[], int iArrayNum)
{
	return motionCrl.PToPMove(movePrm, iArrayNum);
}

int EC_SetSglSpeed(TSPEEDPrm movePrm[], int iArrayNum)
{
	return motionCrl.SetSpeed(movePrm, iArrayNum);
}

//点位运动移动到指定位置及运动模式
int EC_StepMove(TSTEPPrm movePrm[], int iArrayNum)
{
	return motionCrl.StepPtoPMove(movePrm, iArrayNum);
}

//回原点
int EC_Home(HOMEPrm movePrm[], int iArrayNum, int iHomeType)
{
	return motionCrl.GoOrigin(movePrm, iArrayNum, iHomeType);
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
//	return motionCrl.GetOriginStatus(iAxisNO);
	return true;
}

//获取轴限位状态
bool EC_GetLimitStatusAxis(int iAxisNO,int* iLimitP,int* iLimitN)
{
	return motionCrl.LimitStatus(iAxisNO, iLimitP, iLimitN);
}

//获取轴是运动状态
int EC_IsMoving(int* iAxisNO, int iLen)
{
	return motionCrl.IsMoving(iAxisNO, iLen);
}

//持续运动
int EC_JogMove(TJOGPrm movePrm[], int iArrayNum)
{
	return motionCrl.JogMove(movePrm, iArrayNum);
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