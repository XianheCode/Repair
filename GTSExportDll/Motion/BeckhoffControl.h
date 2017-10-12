#ifndef _BeckhoffCONTROL_H_
#define _BeckhoffCONTROL_H_

#include "Control.h"
#include "BeckhoffBase.h"

class CBeckhoffControl :  public CControl, public CBeckhoffBase
{
public:
	CString m_lastError;
	CBeckhoffControl(void);
	~CBeckhoffControl(void);
	virtual int Init(int* enableAxiss,int iEnableAxisNum, int* iCardNum, CDWordArray& iSignals);
	virtual int WritePortBit(int iCard, int bitno, int status, int* iOutState);
	virtual int WritePort(int iCard,int iOutState);
	virtual int GetPos(int iAxis, double* dPos);
	virtual int MoveTo(int* iAxis,int iAxisNum, double* posDestination, int iLen, int iType);
	virtual int SetSpeedMove(int* iAxis, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, int iType);
	virtual int GoHome(int* iAxis, int* iDirect, int* orgmove, int iStyle);
	virtual int Stop(int* iAxis, int iCount, int iType);
	virtual int ReadPort(int iCard, int iBit);
	virtual int SetAbsPos(int iCoorAxis, double dPos);//iCoorAxis - 是逻辑坐标轴X,Y,Z 并不是物理轴号
	virtual int PMove(int* iAxis, int iLen,int iDirect);
	virtual int PowerOn(int iPowerPort, int* iOutState);
	virtual int PowerOff(int iPowerPort, int* iOutState);
	virtual int GasOpen(int iGasPort, int* iOutState);
	virtual int GasClose(int iGasPort, int* iOutState);
	virtual int AbsorptionOpen(int iAbsorptionPort, int* iOutState);
	virtual int AbsorptionClose(int iAbsorptionPort, int* iOutState);
	virtual int TestPPM(int iAxis,int iPulse);
	virtual int CheckHomeStatusAxis(int iAxis);//??有问题，不确定能否私用的
	virtual int CheckLimitStatusAxis(int iAxis);
	virtual int IsMoving(int* iAxis, int iLen);
	virtual int Pause();
	virtual int Continue();


private:
	double m_dVectorLayAccCorner;		//拐角加速度
	double* m_pSpeedArray;

public:

	int IsRunningProgram();
	bool Reset();
	bool TwincatState();
	int BeginMove();

	////
	bool OnlineCommand(CString strOnlineCommand, bool bWait);

};

#endif