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
	//��ʼ��
	virtual int Init(int* enableAxis, int iEnableAxisNum, int* iCardNum, void* pToSelf);	//����
	int Init(int* enableAxiss, int iEnableAxisNum, int* iCardNum, void* pToSelf,char* cCfgPath);

	//�ر�
	virtual int Close();

	//��λ����ź�
	virtual int OutputBit(int iCardNO, int bitNO, int iStatus, int* iOutStatus);

	//����ź�
	virtual int Output(int iCard,int iOutState);

	//��ȡʵʱλ��
	virtual int GetRealTimePos(int iAxisNO, double* dRealTimePos);

	//�ƶ���ָ��λ�ü��˶�ģʽ
	//iAxisNO-�������Ų�����������ţ�����ѧ����ϵ����
	virtual int MoveTo(int* iEnableCoor, int iAxisPosNum, double* posTarget, int iType);
	int PTPMoveTo(int* iEnableAxis, int iAxisPosNum, double* posTarget, bool bSleep);

	//�����ٶȼ��ٶ�ģʽ
	virtual int SetSpeed(int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec, int iType);

	//��ԭ��
	virtual int GoOrigin(int* iAxisNO, int* iDirect, int iLen, int* orgmove, bool bStyle);
	int GoOrigin(int* iAxisNO, int iLen, int* iDirect, double* orgmove, double* dHomeOffPos, bool bStyle);
	int GoOriginLimit(int* iAxisNO, int iLen, int* iDirect, double* dHomeOff);
	int GoOriginHome(int* iAxisNO, int iLen, int* iDirect, double* orgmove, double* dHomeOff);
	int GoOriginIndex(int* iAxisNO, int iLen, int* iDirect, double* orgmove, double* dHomeOff);

	int ZeroPos(int* iAxisNO, int iLen);

	//ֹͣ
	virtual int Stop(int* iAxisNO, int iCount, StopMode Type);

	//�����ź�
	virtual int Input(int iCardNO, int iBitNO);

	//��ȡ��ԭ��״̬
	virtual int GetOriginStatus(int iAxisNO);

	//��ȡ����λ״̬
	virtual int GetLimitStatus(int iAxisNO);
	int GetLimitStatus(int iAxisNO, int* piLimitP,int* piLimitN);

	//��ȡ�����˶�״̬
	virtual int IsMoving(int* iAxisNO, int iLen);

	//�����˶�
	virtual int JogMove(int* iEnableAxis, int iLen, int* iDirection);

	//��������
	virtual int TestPPM(int iAxisNO, int iPulseCount);

	//�����������
	virtual int SetAbsPos(int iAxisNO, double dPos);

	//������
	virtual int LaserOn(int iLaserBit, int* iOutStatus);

	//�ؼ���
	virtual int LaserOff(int iLaserBit, int* iOutStatus);

	//����
	virtual int GasOpen(int iGasBit, int* iOutStatus);

	//����
	virtual int GasClose(int iGasBit, int* iOutStatus);

	//������
	virtual int AbsorptionOpen(int iAbsorptionBit, int* iOutStatus);

	//������
	virtual int AbsorptionClose(int iAbsorptionBit, int* iOutStatus);

	//��ͣ�˶�
	virtual int PauseMove();

	//�����˶�
	virtual int RestorationMove();

	//���õ�ǰ����
	virtual int SetCardNO(short cardNO);

	//��ȡ��ǰ����
	virtual int GetCardNO(short* cardNO);

	/*
	����:�岹��������ϵ+ǰհ��ʼ��
	iAxisNo:      ����ϵ�ж�Ӧ�����
	iCoorAxisNum: ����ϵ�����
	dMaxVel:      ����ٶ�
	dMaxAcc:	  �����ٶ�
	dEvenTime:    ƽ��ʱ��(ms)
	lZeroOff:     ����ϵ�������ڻ�е����ƫ��
	dCornerTime:  ����ʱ��(ms)
	*/
	int CGoogolGTSControl::CoorInit(int* iAxisNo, int iCoorAxisNum, double dMaxVel, double dMaxAcc, short dEvenTime, long* lZeroOff, double dCornerTime);

	/*
	���ܣ���ǰհ�������е�����ѹ�뵽�˶�������
	����ֵ����Ϊ���㣬˵��ǰհ�л�������û�б�ѹ���˶������������˶��������Ѿ�û�пռ��ˣ�
	����Ҫ����˶��������еĿռ��ˡ�
	*/
	int CoorCrdData();

	//XY��άֱ�߲岹
	int CoorLnXY(long lX, long lY, double dVel, double dAcc);

	//XYZ��άֱ�߲岹
	int CoorLnXYZ(long lX, long lY, long lZ, double dVel, double dAcc);

	//XYZA��άֱ�߲岹
	int CoorLnXYZA(long lX, long lY, long lZ, long lA, double dVel, double dAcc);

	//XY��άֱ�߲岹(�յ��ٶ�Ϊ��)
	int CoorLnXYG0(long lX, long lY, double dVel, double dAcc);

	//XYZ��άֱ�߲岹(�յ��ٶ�Ϊ��)
	int CoorLnXYZG0(long lX, long lY, long lZ, double dVel, double dAcc);

	//XYZA��άֱ�߲岹(�յ��ٶ�Ϊ��)
	int CoorLnXYZAG0(long lX, long lY, long lZ, long lA, double dVel, double dAcc);

	//XYԲ���岹-�뾶
	int CoorArcXYR(long lX, long lY, double dRadius, short sCircleDir, double dVel, double dAcc);

	//XYԲ���岹-Բ��
	int CoorArcXYC(long lX, long lY, double dXCenter, double dYCenter, short sCircleDir, double dVel, double dAcc);

	//YZԲ���岹-�뾶
	int CoorArcYZR(long lY, long lZ, double dRadius, short sCircleDir, double dVel, double dAcc);

	//YZԲ���岹-Բ��
	int CoorArcYZC(long lY, long lZ, double dYCenter, double dZCenter, short sCircleDir, double dVel, double dAcc);

	//ZXԲ���岹-�뾶
	int CoorArcZXR(long lZ, long lX, double dRadius, short sCircleDir, double dVel, double dAcc);

	//ZXԲ���岹-Բ��
	int CoorArcZXC(long lZ, long lX, double dZCenter, double dXCenter, short sCircleDir, double dVel, double dAcc);

	//ͨ�����������
	int CoorBufIO(unsigned short doMask, unsigned short doValue);

	//��������ʱ
	int CoorBufDelay(unsigned short usDelayTime);

	//�������������˶�
	int CoorBufMove(short sAxisNO, long lPos, double dVel, double dAcc, short sModal);

	//��ȡ�˶�������ʣ��ռ�
	int CoorGetSpace(long* plSpace);

	//����˶�������
	int CoorClear();

	//��ʼ����ϵ�˶�
	int CoorStart(int iCoorNo);
	
	//��ȡ����ϵ������״̬���Ѿ���ɵĲ岹����
	int CoorGetSts(short* psRun, long* plSegment);

	//��������ϵֹͣ���ٶ�
	int CoorSetStopDec(double dSmoothStopDec, double dAbruptStopDec);

	//��������ϵ�ٶȱ���
	int CoorSetOverride(double dVelRatio);

	//��ȡ����ϵ��ǰλ��
	int CoorGetPos(double* pdCrdPos);

	//��ȡ����ϵ��ǰ�ٶ�
	int CoorGetVel(double* pdCrdVel);
//////////////////////////////////////////////////////////////////////////

	int SetLaserOut(double dFrequence, double dLaserPrf,int iChannel);
private:
	double m_dVectorLayAccCorner;		//�սǼ��ٶ�
	bool m_bInit;

	//������ñ����ָ�룬ʹ���������ٶ��ƶ�������(Ŀǰѡ�񴫵ݵ��ǵ������ָ�룬������ѡ�񴫵�MoveData��ָ��)
	CMotionInterface* m_pGetMI;
};

#endif