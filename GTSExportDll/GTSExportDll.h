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
//��ʼ��
extern "C" int __declspec(dllexport)EC_Init();

//�ر�
extern "C" int __declspec(dllexport)EC_Close();

//��λ����ź�
extern "C" int __declspec(dllexport)EC_OutputBit(int bitNO, int iStatus);

//����ź�
extern "C" int __declspec(dllexport)EC_Output(int iOutState);

//��ȡʵʱλ��
extern "C" int __declspec(dllexport)EC_GetRealTimePos(int iAxisNO, double* dRealTimePos);

//���ö����˶��ٶȲ���
extern "C" int __declspec(dllexport)EC_SetSglSpeed(TSPEEDPrm movePrm[], int iArrayNum);

//�ƶ���ָ��λ��
extern "C" int __declspec(dllexport)EC_PToPMove(TPTPPrm movePrm[], int iArrayNum);

//�ƶ��̶�����
extern "C" int __declspec(dllexport)EC_StepMove(TSTEPPrm movePrm[], int iArrayNum);

//��ԭ��
//iHomeType: 0-��λ����   1-Home����  2-Index����
extern "C" int  __declspec(dllexport)EC_Home(HOMEPrm movePrm[], int iArrayNum, int iHomeType);

//ֹͣ
extern "C" int  __declspec(dllexport)EC_Stop();

//�����ź�
extern "C" int  __declspec(dllexport)EC_Input(int iBitNO);

//��ȡ��ԭ��״̬
extern "C" bool  __declspec(dllexport)EC_GetOriginStatusAxis(int iAxisNO);

//��ȡ��λ״̬
extern "C" bool  __declspec(dllexport)EC_GetLimitStatusAxis(int iAxisNO, int* iLimitP, int* iLimitN);

//��ȡ�����˶�״̬
extern "C" int  __declspec(dllexport)EC_IsMoving(int* iAxisNO, int iLen);

//�����˶�
extern "C" int  __declspec(dllexport)EC_JogMove(TJOGPrm movePrm[], int iArrayNum);

//�����������
extern "C"  double  __declspec(dllexport)EC_SetAbsPos(int iAxisNO, double dPos);

//������
extern "C" int  __declspec(dllexport)EC_LaserOn(int iLaserBit);

//�ؼ���
extern "C" int  __declspec(dllexport)EC_LaserOff(int iLaserBit);

//����
extern "C" int  __declspec(dllexport)EC_GasOpen(int iGasBit);

//����
extern "C" int  __declspec(dllexport)EC_GasClose(int iGasBit);

//������
extern "C" int  __declspec(dllexport)EC_AbsorptionOpen(int iAbsorptionBit);

//������
extern "C" int  __declspec(dllexport)EC_AbsorptionClose(int iAbsorptionBit);

//��ͣ�˶�
extern "C" int  __declspec(dllexport)EC_PauseMove();

// �����˶�
// extern "C" int  __declspec(dllexport)EC_RestorationMove();

//���õ�ǰ����
extern "C"  int  __declspec(dllexport)EC_SetCardNO(short cardNO);

//��ȡ��ǰ����
extern "C"  int  __declspec(dllexport)EC_GetCardNO(short* cardNO);

//ִ�����ò������
extern "C"  bool  __declspec(dllexport)EC_ExeSetParamApplication();

#endif