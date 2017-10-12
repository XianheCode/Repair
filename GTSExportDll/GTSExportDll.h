#ifndef _Win32ExportDll_H_20170402_
#define _Win32ExportDll_H_20170402_

//struct

typedef struct JOGPrm
{
	int iCoorAxis;
	int iDirect;

	JOGPrm()
	{
		iCoorAxis = 0;
		iDirect = 0;
	}

} TJOGPrm;

typedef struct PTPPrm
{
	int iCoorAxis;
	double dPos;

	PTPPrm()
	{
		iCoorAxis = 0;
		dPos = 0;
	}

} TPTPPrm;

typedef struct STEPPrm
{
	int iCoorAxis;
	double dStepPos;

	STEPPrm()
	{
		iCoorAxis = 0;
		dStepPos = 0;
	}

} TSTEPPrm;

typedef struct SPEEDPrm
{
	int iCoorAxis;
	int iMoveType;
	int iHandVelType;
	double dLowVel;
	double dHighVel;
	double dAcc;
	double dDec;

	SPEEDPrm()
	{
		iCoorAxis = 0;
		iMoveType = 0;
		iHandVelType = 0;
		dLowVel = 0;
		dHighVel = 0;
		dAcc = 0;
		dDec = 0;
	}

} TSPEEDPrm;

typedef struct HOMEPrm
{
	int iCoorAxis;
	int iDirect;
	double dOrgMove;
	double dHomeOff;

	HOMEPrm()
	{
		iCoorAxis = 0;
		iDirect = 0;
		dOrgMove = 0;
		dHomeOff = 0;
	}

} THOMEPrm;

// Method
//初始化
extern "C" int __declspec(dllexport)EC_Init();

//关闭
extern "C" int __declspec(dllexport)EC_Close();

//按位输出信号
extern "C" int __declspec(dllexport)EC_OutputBit(int bitNO, int iStatus);

//输出信号
extern "C" int __declspec(dllexport)EC_Output(int iOutState);

//获取实时位置
extern "C" int __declspec(dllexport)EC_GetRealTimePos(int iAxisNO, double* dRealTimePos);

//设置独立运动速度参数
extern "C" int __declspec(dllexport)EC_SetSglSpeed(TSPEEDPrm movePrm[], int iArrayNum);

//移动到指定位置
extern "C" int __declspec(dllexport)EC_PToPMove(TPTPPrm movePrm[], int iArrayNum);

//移动固定距离
extern "C" int __declspec(dllexport)EC_StepMove(TSTEPPrm movePrm[], int iArrayNum);

//回原点
//iHomeType: 0-限位回零   1-Home回零  2-Index回零
extern "C" int  __declspec(dllexport)EC_Home(HOMEPrm movePrm[], int iArrayNum, int iHomeType);

//停止
extern "C" int  __declspec(dllexport)EC_Stop();

//输入信号
extern "C" int  __declspec(dllexport)EC_Input(int iBitNO);

//获取轴原点状态
extern "C" bool  __declspec(dllexport)EC_GetOriginStatusAxis(int iAxisNO);

//获取限位状态
extern "C" bool  __declspec(dllexport)EC_GetLimitStatusAxis(int iAxisNO, int* iLimitP, int* iLimitN);

//获取轴是运动状态
extern "C" int  __declspec(dllexport)EC_IsMoving(int* iAxisNO, int iLen);

//持续运动
extern "C" int  __declspec(dllexport)EC_JogMove(TJOGPrm movePrm[], int iArrayNum);

//设轴绝对坐标
extern "C"  double  __declspec(dllexport)EC_SetAbsPos(int iAxisNO, double dPos);

//开激光
extern "C" int  __declspec(dllexport)EC_LaserOn(int iLaserBit);

//关激光
extern "C" int  __declspec(dllexport)EC_LaserOff(int iLaserBit);

//吹气
extern "C" int  __declspec(dllexport)EC_GasOpen(int iGasBit);

//关气
extern "C" int  __declspec(dllexport)EC_GasClose(int iGasBit);

//开吸附
extern "C" int  __declspec(dllexport)EC_AbsorptionOpen(int iAbsorptionBit);

//关吸附
extern "C" int  __declspec(dllexport)EC_AbsorptionClose(int iAbsorptionBit);

//暂停运动
extern "C" int  __declspec(dllexport)EC_PauseMove();

// 继续运动
// extern "C" int  __declspec(dllexport)EC_RestorationMove();

//设置当前卡号
extern "C"  int  __declspec(dllexport)EC_SetCardNO(short cardNO);

//获取当前卡号
extern "C"  int  __declspec(dllexport)EC_GetCardNO(short* cardNO);

//执行设置参数软件
extern "C"  bool  __declspec(dllexport)EC_ExeSetParamApplication();

#endif