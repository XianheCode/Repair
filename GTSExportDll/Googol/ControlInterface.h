// ControlInterface.h: interface for the CControlInterface class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _CONTROLINTERFACE_H_V1_20170227_
#define _CONTROLINTERFACE_H_V1_20170227_

//////////////////////////////////////////////////////////////////////////
//用于所有运动控制的底层实现接口
//////////////////////////////////////////////////////////////////////////
class CControlInterface
{
public:
public:
	enum StopMode
	{
		SuddenStop,
		SlowStop,
		StopCoordinate
	};

	//初始化
	virtual int Init(int* enableAxis, int iEnableAxisNum, int* iCardNum, void* pToSelf) = 0;

	//关闭
	virtual int Close() = 0;

	//按位输出信号
	virtual int OutputBit(int iCardNO, int bitNO, int iStatus, int* iOutStatus) = 0;

	//输出信号
	virtual int Output(int iCard, int iOutState) = 0;

	//获取实时位置
	virtual int GetRealTimePos(int iAxisNO, double* dRealTimePos) = 0;

	//移动到指定位置及运动模式
	virtual int MoveTo(int* iEnableCoor, int iAxisPosNum, double* posTarget, int iType) = 0;

	//设置速度及速度模式
	virtual int SetSpeed(int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec, int iType) = 0;

	//回原点
	virtual int GoOrigin(int* iAxisNO, int* iDirect, int iLen, int* orgmove, bool bStyle) = 0;

	//停止
	virtual int Stop(int* iAxisNO, int iCount, StopMode Type) = 0;

	//输入信号
	virtual int Input(int iCardNO, int iBitNO) = 0;

	//获取轴原点状态
	virtual int GetOriginStatus(int iAxisNO) = 0;

	//获取轴限位状态
	virtual int GetLimitStatus(int iAxisNO) = 0;

	//获取轴是运动状态
	virtual int IsMoving(int* iAxisNO, int iLen) = 0;

	//持续运动
	virtual int JogMove(int* iEnableAxis, int iLen, int* iDirection) = 0;

	//测试脉冲
	virtual int TestPPM(int iAxisNO, int iPulseCount) = 0;

	//设轴绝对坐标
	virtual int SetAbsPos(int iAxisNO, double dPos) = 0;

	//开激光
	virtual int LaserOn(int iLaserBit, int* iOutStatus) = 0;

	//关激光
	virtual int LaserOff(int iLaserBit, int* iOutStatus) = 0;

	//吹气
	virtual int GasOpen(int iGasBit, int* iOutStatus) = 0;

	//关气
	virtual int GasClose(int iGasBit, int* iOutStatus) = 0;

	//开吸附
	virtual int AbsorptionOpen(int iAbsorptionBit, int* iOutStatus) = 0;

	//关吸附
	virtual int AbsorptionClose(int iAbsorptionBit, int* iOutStatus) = 0;

	//暂停运动
	virtual int PauseMove() = 0;

	//继续运动
	virtual int RestorationMove() = 0;

	//设置当前卡号
	virtual int SetCardNO(short cardNO) = 0;

	//获取当前卡号
	virtual int GetCardNO(short* cardNO) = 0;
};
#endif
