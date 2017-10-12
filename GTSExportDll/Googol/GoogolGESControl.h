// GoogolControl.h: implementation of the CGoogolGESControl class.
/*
 * CopyRight (c) 2017
 * All Rights reserved
 *
 * File Name		: GoogolControl.h
 * File ID			: None
 * Sumary			: For Googol Ges
 *
 * Current Version	: 1.0.0
 * Author			: Jackie Wu
 * Finish Time		: 2017-2-27
 * Last Modify Time : 2017-2-27
*/

#ifndef _GOOGOLCONTROL_H_V1_20170227
#define _GOOGOLCONTROL_H_V1_20170227

#include "MoveData.h"
#include "GoogolGESBase.h"
#include "ControlInterface.h"

class CGoogolGESControl :  public CControlInterface, public CGoogolGESBase
{
public:
	CGoogolGESControl(void);
	~CGoogolGESControl(void);
//////////////////////////////////////////////////////////////////////////
	//Virtual Method
	//初始化
	virtual int Init(int* enableAxis, int iEnableAxisNum, int* iCardNum, void* pToSelf);
	int Init(int* enableAxis, int iEnableAxisNum, int* iCardNum, double* pdLimitDir);

	//关闭
	virtual int Close();

	//按位输出信号
	virtual int OutputBit(int iCardNO, int bitNO, int iStatus, int* iOutStatus);

	//输出信号
	virtual int Output(int iCard, int iOutState);

	//获取实时位置
	virtual int GetRealTimePos(int iAxisNO, double* dRealTimePos);

	//移动到指定位置及运动模式，等待完成
	virtual int MoveTo(int* iEnableCoor, int iAxisPosNum, double* posTarget, int iType);

	//移动到指定位置及运动模式，并是否等待完成
	//bSleep:是否等待运动完成
	int MoveTo(int* iEnableAxis, int iAxisPosNum, double* posTarget, int iType, bool bSleep);

	//设置速度及速度模式
	virtual int SetSpeed(int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec, int iType);

	int SetSpeed(double dHighSpeed, double dLowSpeed, double dAcc, double dDec);

	//回原点
	virtual int GoOrigin(int* iAxisNO, int* iDirect, int iLen, int* orgmove, bool bStyle);

	//单次Home，方便设置速度
	int GoOriginOne(int iAxisNO, int iDirect, int* orgmove, bool bStyle);

	//停止
	virtual int Stop(int* iAxisNO, int iCount, StopMode Type);

	//输入信号
	virtual int Input(int iCardNO, int iBitNO);

	//获取轴原点状态
	virtual int GetOriginStatus(int iAxisNO);

	//获取轴限位状态
	virtual int GetLimitStatus(int iAxisNO);

	//获取轴是运动状态
	virtual int IsMoving(int* iAxisNO, int iLen);

	//持续运动
	virtual int JogMove(int* iEnableCoor, int iLen, int* iDirection);

	int JogMove(int* iEnableCoor, int iLen, int* iDirection,bool bSleep);

	//测试脉冲
	virtual int TestPPM(int iAxisNO, int iPulseCount);

	//设轴绝对坐标
	virtual int SetAbsPos(int iAxisNO, double dPos);

	//开激光
	virtual int LaserOn(int iLaserBit, int* iOutStatus);

	//关激光
	virtual int LaserOff(int iLaserBit, int* iOutStatus);

	//吹气
	virtual int GasOpen(int iGasBit, int* iOutStatus);

	//关气
	virtual int GasClose(int iGasBit, int* iOutStatus);

	//开吸附
	virtual int AbsorptionOpen(int iAbsorptionBit, int* iOutStatus);

	//关吸附
	virtual int AbsorptionClose(int iAbsorptionBit, int* iOutStatus);

	//暂停运动
	virtual int PauseMove();

	//继续运动
	virtual int RestorationMove();

	//设置当前卡号
	virtual int SetCardNO(short cardNO);

	//获取当前卡号
	virtual int GetCardNO(short* cardNO);
	//////////////////////////////////////////////////////////////////////////
private:
	double m_dVectorLayAccCorner;		//拐角加速度
	double* m_pdHighSpeed;
	double* m_pdLowSpeed;
	double* m_pdAcc;
	double* m_pdDec;
	MoveData m_moveData;
	bool m_bInit;
};

#endif