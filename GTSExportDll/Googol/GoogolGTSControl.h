// GoogolGTSControl.h: implementation of the CGoogolGTSControl class.
/*
 * CopyRight (c) 2017
 * All Rights reserved
 *
 * File Name		: GoogolGTSControl.h
 * File ID			: None
 * Sumary			: For Googol
 *
 * Current Version	: 1.0.0
 * Author			: Jackie Wu
 * Finish Time		: 2017-2-27
 * Last Modify Time : 2017-2-27
*/

#ifndef _GoogolGTSControl_H_V1_20170227
#define _GoogolGTSControl_H_V1_20170227

#include "MoveData.h"
#include "GoogolGTSBase.h"
#include "ControlInterface.h"
#include "Mutex.h"

class CMotionInterface;

class CGoogolGTSControl :  public CControlInterface, public CGoogolGTSBase
{
public:
	CGoogolGTSControl(void);
	~CGoogolGTSControl(void);

	Mutex m_mutex;
//////////////////////////////////////////////////////////////////////////
	//Virtual Method
	//初始化
	virtual int Init(int* enableAxis, int iEnableAxisNum, int* iCardNum, void* pToSelf);	//不用
	int Init(int* enableAxiss, int iEnableAxisNum, int* iCardNum, void* pToSelf,char* cCfgPath);

	//关闭
	virtual int Close();

	//按位输出信号
	virtual int OutputBit(int iCardNO, int bitNO, int iStatus, int* iOutStatus);

	//输出信号
	virtual int Output(int iCard,int iOutState);

	//获取实时位置
	virtual int GetRealTimePos(int iAxisNO, double* dRealTimePos);

	//移动到指定位置及运动模式
	//iAxisNO-这里的轴号并不是物理轴号，是数学坐标系轴编号
	virtual int MoveTo(int* iEnableCoor, int iAxisPosNum, double* posTarget, int iType);
	int PTPMoveTo(int* iEnableAxis, int iAxisPosNum, double* posTarget, bool bSleep);

	//设置速度及速度模式
	virtual int SetSpeed(int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec, int iType);

	//回原点
	virtual int GoOrigin(int* iAxisNO, int* iDirect, int iLen, int* orgmove, bool bStyle);
	int GoOrigin(int* iAxisNO, int iLen, int* iDirect, double* orgmove, double* dHomeOffPos, bool bStyle);
	int GoOriginLimit(int* iAxisNO, int iLen, int* iDirect, double* dHomeOff);
	int GoOriginHome(int* iAxisNO, int iLen, int* iDirect, double* orgmove, double* dHomeOff);
	int GoOriginIndex(int* iAxisNO, int iLen, int* iDirect, double* orgmove, double* dHomeOff);

	int ZeroPos(int* iAxisNO, int iLen);

	//停止
	virtual int Stop(int* iAxisNO, int iCount, StopMode Type);

	//输入信号
	virtual int Input(int iCardNO, int iBitNO);

	//获取轴原点状态
	virtual int GetOriginStatus(int iAxisNO);

	//获取轴限位状态
	virtual int GetLimitStatus(int iAxisNO);
	int GetLimitStatus(int iAxisNO, int* piLimitP,int* piLimitN);

	//获取轴是运动状态
	virtual int IsMoving(int* iAxisNO, int iLen);

	//持续运动
	virtual int JogMove(int* iEnableAxis, int iLen, int* iDirection);

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

	/*
	功能:插补运行坐标系+前瞻初始化
	iAxisNo:      坐标系中对应的轴号
	iCoorAxisNum: 坐标系轴个数
	dMaxVel:      最大速度
	dMaxAcc:	  最大加速度
	dEvenTime:    平滑时间(ms)
	lZeroOff:     坐标系零点相对于机械零点的偏移
	dCornerTime:  拐弯时间(ms)
	*/
	int CGoogolGTSControl::CoorInit(int* iAxisNo, int iCoorAxisNum, double dMaxVel, double dMaxAcc, short dEvenTime, long* lZeroOff, double dCornerTime);

	/*
	功能：将前瞻缓冲区中的数据压入到运动缓存区
	返回值：如为非零，说明前瞻中还有数据没有被压入运动缓存区，而运动缓存区已经没有空间了，
	则需要检查运动缓存区中的空间了。
	*/
	int CoorCrdData();

	//XY二维直线插补
	int CoorLnXY(long lX, long lY, double dVel, double dAcc);

	//XYZ三维直线插补
	int CoorLnXYZ(long lX, long lY, long lZ, double dVel, double dAcc);

	//XYZA四维直线插补
	int CoorLnXYZA(long lX, long lY, long lZ, long lA, double dVel, double dAcc);

	//XY二维直线插补(终点速度为零)
	int CoorLnXYG0(long lX, long lY, double dVel, double dAcc);

	//XYZ三维直线插补(终点速度为零)
	int CoorLnXYZG0(long lX, long lY, long lZ, double dVel, double dAcc);

	//XYZA四维直线插补(终点速度为零)
	int CoorLnXYZAG0(long lX, long lY, long lZ, long lA, double dVel, double dAcc);

	//XY圆弧插补-半径
	int CoorArcXYR(long lX, long lY, double dRadius, short sCircleDir, double dVel, double dAcc);

	//XY圆弧插补-圆心
	int CoorArcXYC(long lX, long lY, double dXCenter, double dYCenter, short sCircleDir, double dVel, double dAcc);

	//YZ圆弧插补-半径
	int CoorArcYZR(long lY, long lZ, double dRadius, short sCircleDir, double dVel, double dAcc);

	//YZ圆弧插补-圆心
	int CoorArcYZC(long lY, long lZ, double dYCenter, double dZCenter, short sCircleDir, double dVel, double dAcc);

	//ZX圆弧插补-半径
	int CoorArcZXR(long lZ, long lX, double dRadius, short sCircleDir, double dVel, double dAcc);

	//ZX圆弧插补-圆心
	int CoorArcZXC(long lZ, long lX, double dZCenter, double dXCenter, short sCircleDir, double dVel, double dAcc);

	//通用数字量输出
	int CoorBufIO(unsigned short doMask, unsigned short doValue);

	//缓存区延时
	int CoorBufDelay(unsigned short usDelayTime);

	//缓存区独立轴运动
	int CoorBufMove(short sAxisNO, long lPos, double dVel, double dAcc, short sModal);

	//获取运动缓存区剩余空间
	int CoorGetSpace(long* plSpace);

	//清空运动缓存区
	int CoorClear();

	//开始坐标系运动
	int CoorStart(int iCoorNo);
	
	//获取坐标系的运行状态和已经完成的插补段数
	int CoorGetSts(short* psRun, long* plSegment);

	//设置坐标系停止减速度
	int CoorSetStopDec(double dSmoothStopDec, double dAbruptStopDec);

	//设置坐标系速度倍率
	int CoorSetOverride(double dVelRatio);

	//获取坐标系当前位置
	int CoorGetPos(double* pdCrdPos);

	//获取坐标系当前速度
	int CoorGetVel(double* pdCrdVel);
//////////////////////////////////////////////////////////////////////////

	int SetLaserOut(double dFrequence, double dLaserPrf,int iChannel);
private:
	double m_dVectorLayAccCorner;		//拐角加速度
	bool m_bInit;

	//这个调用本类的指针，使用来关联速度移动参数的(目前选择传递的是调用类的指针，而不是选择传递MoveData的指针)
	CMotionInterface* m_pGetMI;
};

#endif