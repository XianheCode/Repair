// ControlInterface.h: interface for the CControlInterface class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _CONTROLINTERFACE_H_V1_20170227_
#define _CONTROLINTERFACE_H_V1_20170227_

//////////////////////////////////////////////////////////////////////////
//���������˶����Ƶĵײ�ʵ�ֽӿ�
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

	//��ʼ��
	virtual int Init(int* enableAxis, int iEnableAxisNum, int* iCardNum, void* pToSelf) = 0;

	//�ر�
	virtual int Close() = 0;

	//��λ����ź�
	virtual int OutputBit(int iCardNO, int bitNO, int iStatus, int* iOutStatus) = 0;

	//����ź�
	virtual int Output(int iCard, int iOutState) = 0;

	//��ȡʵʱλ��
	virtual int GetRealTimePos(int iAxisNO, double* dRealTimePos) = 0;

	//�ƶ���ָ��λ�ü��˶�ģʽ
	virtual int MoveTo(int* iEnableCoor, int iAxisPosNum, double* posTarget, int iType) = 0;

	//�����ٶȼ��ٶ�ģʽ
	virtual int SetSpeed(int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec, int iType) = 0;

	//��ԭ��
	virtual int GoOrigin(int* iAxisNO, int* iDirect, int iLen, int* orgmove, bool bStyle) = 0;

	//ֹͣ
	virtual int Stop(int* iAxisNO, int iCount, StopMode Type) = 0;

	//�����ź�
	virtual int Input(int iCardNO, int iBitNO) = 0;

	//��ȡ��ԭ��״̬
	virtual int GetOriginStatus(int iAxisNO) = 0;

	//��ȡ����λ״̬
	virtual int GetLimitStatus(int iAxisNO) = 0;

	//��ȡ�����˶�״̬
	virtual int IsMoving(int* iAxisNO, int iLen) = 0;

	//�����˶�
	virtual int JogMove(int* iEnableAxis, int iLen, int* iDirection) = 0;

	//��������
	virtual int TestPPM(int iAxisNO, int iPulseCount) = 0;

	//�����������
	virtual int SetAbsPos(int iAxisNO, double dPos) = 0;

	//������
	virtual int LaserOn(int iLaserBit, int* iOutStatus) = 0;

	//�ؼ���
	virtual int LaserOff(int iLaserBit, int* iOutStatus) = 0;

	//����
	virtual int GasOpen(int iGasBit, int* iOutStatus) = 0;

	//����
	virtual int GasClose(int iGasBit, int* iOutStatus) = 0;

	//������
	virtual int AbsorptionOpen(int iAbsorptionBit, int* iOutStatus) = 0;

	//������
	virtual int AbsorptionClose(int iAbsorptionBit, int* iOutStatus) = 0;

	//��ͣ�˶�
	virtual int PauseMove() = 0;

	//�����˶�
	virtual int RestorationMove() = 0;

	//���õ�ǰ����
	virtual int SetCardNO(short cardNO) = 0;

	//��ȡ��ǰ����
	virtual int GetCardNO(short* cardNO) = 0;
};
#endif
