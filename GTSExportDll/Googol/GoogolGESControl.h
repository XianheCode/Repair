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
	//��ʼ��
	virtual int Init(int* enableAxis, int iEnableAxisNum, int* iCardNum, void* pToSelf);
	int Init(int* enableAxis, int iEnableAxisNum, int* iCardNum, double* pdLimitDir);

	//�ر�
	virtual int Close();

	//��λ����ź�
	virtual int OutputBit(int iCardNO, int bitNO, int iStatus, int* iOutStatus);

	//����ź�
	virtual int Output(int iCard, int iOutState);

	//��ȡʵʱλ��
	virtual int GetRealTimePos(int iAxisNO, double* dRealTimePos);

	//�ƶ���ָ��λ�ü��˶�ģʽ���ȴ����
	virtual int MoveTo(int* iEnableCoor, int iAxisPosNum, double* posTarget, int iType);

	//�ƶ���ָ��λ�ü��˶�ģʽ�����Ƿ�ȴ����
	//bSleep:�Ƿ�ȴ��˶����
	int MoveTo(int* iEnableAxis, int iAxisPosNum, double* posTarget, int iType, bool bSleep);

	//�����ٶȼ��ٶ�ģʽ
	virtual int SetSpeed(int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec, int iType);

	int SetSpeed(double dHighSpeed, double dLowSpeed, double dAcc, double dDec);

	//��ԭ��
	virtual int GoOrigin(int* iAxisNO, int* iDirect, int iLen, int* orgmove, bool bStyle);

	//����Home�����������ٶ�
	int GoOriginOne(int iAxisNO, int iDirect, int* orgmove, bool bStyle);

	//ֹͣ
	virtual int Stop(int* iAxisNO, int iCount, StopMode Type);

	//�����ź�
	virtual int Input(int iCardNO, int iBitNO);

	//��ȡ��ԭ��״̬
	virtual int GetOriginStatus(int iAxisNO);

	//��ȡ����λ״̬
	virtual int GetLimitStatus(int iAxisNO);

	//��ȡ�����˶�״̬
	virtual int IsMoving(int* iAxisNO, int iLen);

	//�����˶�
	virtual int JogMove(int* iEnableCoor, int iLen, int* iDirection);

	int JogMove(int* iEnableCoor, int iLen, int* iDirection,bool bSleep);

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
	//////////////////////////////////////////////////////////////////////////
private:
	double m_dVectorLayAccCorner;		//�սǼ��ٶ�
	double* m_pdHighSpeed;
	double* m_pdLowSpeed;
	double* m_pdAcc;
	double* m_pdDec;
	MoveData m_moveData;
	bool m_bInit;
};

#endif