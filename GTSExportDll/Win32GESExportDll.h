#ifndef _Win32ExportDll_H_20170402_
#define _Win32ExportDll_H_20170402_

#include "./Googol/MotionGESInterface.h"

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

//移动到指定位置，不用
extern "C" int __declspec(dllexport)EC_PToPMove(int* iAxisNO, int iAxisPosNum, double* posTarget);

//移动到指定位置，使用
//iMoveType: 0-自动 1-手动(只能单轴)  ;  
//iHandMoveSpeedType ：在手动模式下 0-高速  1-中速  2-低速 3-回零
extern "C" int __declspec(dllexport)EC_PToPMoveNew(int* iAxisNO, int iAxisPosNum, double* posTarget, int iMoveType, int iHandMoveSpeedType);

//设置速度及速度模式
extern "C" int  __declspec(dllexport)EC_SetPtoPSpeed(int iType, int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec);

//移动固定距离,不用
extern "C" int __declspec(dllexport)EC_StepMove(int* iAxisNO, int iAxisPosNum, double* posStep);

//移动固定距离,使用
extern "C" int __declspec(dllexport)EC_StepMoveNew(int* iAxisNO, int iAxisPosNum, double* posStep, int iMoveType, int iHandMoveSpeedType);

//设置移动固定距离的速度，不用
extern "C" int  __declspec(dllexport)EC_SetStepSpeed(int iType, int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec);

//回原点
extern "C" int  __declspec(dllexport)EC_Home();

//停止
extern "C" int  __declspec(dllexport)EC_Stop();

//输入信号
extern "C" int  __declspec(dllexport)EC_Input(int iBitNO);

//获取原点状态
extern "C" bool  __declspec(dllexport)EC_GetOriginStatus();

//获取轴原点状态
extern "C" bool  __declspec(dllexport)EC_GetOriginStatusAxis(int iAxisNO);

//获取轴限位状态
extern "C" bool  __declspec(dllexport)EC_GetLimitStatus();

//获取限位状态
extern "C" bool  __declspec(dllexport)EC_GetLimitStatusAxis(int iAxisNO);

//获取轴是运动状态
extern "C" int  __declspec(dllexport)EC_IsMoving(int* iAxisNO, int iLen);

//持续运动,不用
extern "C" int  __declspec(dllexport)EC_JogMove(int* iAxisNO, int iLen, int* iDirection);

//持续运动，使用
//iHandMoveSpeedType ：在手动模式下 0-高速  1-中速  2-低速 3-回零
extern "C" int  __declspec(dllexport)EC_JogMoveNew(int* iAxisNO, int iLen, int* iDirection, int iHandMoveSpeedType);

//设置持续运动速度
extern "C" int  __declspec(dllexport)EC_SetJogSpeed(int iType, int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec);

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

//更新加工参数
extern "C"  bool  __declspec(dllexport)EC_UpdateMoveParam();

#endif