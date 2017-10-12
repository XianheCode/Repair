// Win32ExportDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Win32GESExportDll.h"

CMotionGESInterface motionCrl;


//��ʼ��
int EC_Init()
{
	return motionCrl.Init(0);
}

//�ر�
int EC_Close()
{
	return motionCrl.Close();
}


//��λ����ź�
int EC_OutputBit(int bitNO, int iState)
{
	return motionCrl.OutputBit(bitNO, iState);
}

//����ź�
int EC_Output(int iOutState)
{
	return motionCrl.Output(iOutState);
}

//��ȡʵʱλ��
int EC_GetRealTimePos(int iAxisNO, double* dRealTimePos)
{
	return motionCrl.GetPosCur(iAxisNO, dRealTimePos);
}

//��λ�˶��ƶ���ָ��λ�ü��˶�ģʽ,����
int EC_PToPMove(int* iAxisNO, int iAxisPosNum, double* posTarget)
{
//	return motionCrl.PToPMove(iAxisNO, posTarget, iAxisPosNum);
	return 0;
}
//��λ�˶��ƶ���ָ��λ�ü��˶�ģʽ,ʹ��
int EC_PToPMoveNew(int* iAxisNO, int iAxisPosNum, double* posTarget, int iMoveType, int iHandMoveSpeedType)
{
	return motionCrl.PToPMove(iAxisNO, posTarget, iAxisPosNum, iMoveType, iHandMoveSpeedType);
}

//�����ٶȼ��ٶ�ģʽ
int EC_SetPtoPSpeed(int iType, int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec)
{
	return motionCrl.SetPtoPSpeed(iType, iAxisNO, iAxisNum, dHighSpeed, dLowSpeed, dAcc, dDec);
}

//��λ�˶��ƶ���ָ��λ�ü��˶�ģʽ������
int EC_StepMove(int* iAxisNO, int iAxisPosNum, double* posStep)
{
	return motionCrl.StepPtoPMove(iAxisNO, iAxisPosNum, posStep);
}

//��λ�˶��ƶ���ָ��λ�ü��˶�ģʽ��ʹ��
int EC_StepMoveNew(int* iAxisNO, int iAxisPosNum, double* posStep, int iMoveType, int iHandMoveSpeedType)
{
	return motionCrl.StepPtoPMove(iAxisNO, iAxisPosNum, posStep, iMoveType, iHandMoveSpeedType);
}

//�����ٶȼ��ٶ�ģʽ
int EC_SetStepSpeed(int iType, int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec)
{
	return motionCrl.SetStepPtoPSpeed(iType, iAxisNO, iAxisNum, dHighSpeed, dLowSpeed, dAcc, dDec);
}

//��ԭ��
int EC_Home()
{
	return motionCrl.GoOrigin();
}

//ֹͣ
int EC_Stop()
{
	return motionCrl.Stop();
}

//�����ź�
int EC_Input(int iBitNO)
{
	return  motionCrl.Input(iBitNO);
}

//��ȡ��ԭ��״̬
bool EC_GetOriginStatusAxis(int iAxisNO)
{
	//return motionCrl.GetOriginStatus(iAxisNO);
	return 0;
}

//��ȡ��ԭ��״̬
bool EC_GetOriginStatus()
{
	return motionCrl.GetOriginStatus();
}

//��ȡ����λ״̬
bool EC_GetLimitStatusAxis(int iAxisNO)
{
	//return motionCrl.GetLaserStatus(iAxisNO);
	return true;
}

//��ȡ����λ״̬
bool EC_GetLimitStatus()
{
	return motionCrl.GetLaserStatus();
}

//��ȡ�����˶�״̬
int EC_IsMoving(int* iAxisNO, int iLen)
{
	return motionCrl.IsMoving(iAxisNO, iLen);
}

//�����˶�������
int EC_JogMove(int* iAxisNO, int iLen, int* iDirection)
{
	return motionCrl.JogMove(iAxisNO, iLen, iDirection);
}

//�����˶���ʹ��
int EC_JogMoveNew(int* iAxisNO, int iLen, int* iDirection, int iHandMoveSpeedType)
{
	return motionCrl.JogMove(iAxisNO, iLen, iDirection, iHandMoveSpeedType);
}

int EC_SetJogSpeed(int iType, int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec)
{
	return motionCrl.SetJogSpeed(iType, iAxisNO, iAxisNum, dHighSpeed, dLowSpeed, dAcc, dDec);
}

//�����������
double EC_SetAbsPos(int iAxisNO, double dPos)
{
	return motionCrl.SetAbsPos(iAxisNO, dPos);
}

//������
int EC_LaserOn(int iLaserBit)
{
	return motionCrl.LaserOn(iLaserBit);
}

//�ؼ���
int EC_LaserOff(int iLaserBit)
{
	return motionCrl.LaserOff(iLaserBit);
}

//����
int EC_GasOpen(int iGasBit)
{
	return motionCrl.GasOpen(iGasBit);
}

//����
int EC_GasClose(int iGasBit)
{
	return motionCrl.GasClose(iGasBit);
}

//������
int EC_AbsorptionOpen(int iAbsorptionBit)
{
	return motionCrl.AbsorptionOpen(iAbsorptionBit);
}

//������
int EC_AbsorptionClose(int iAbsorptionBit)
{
	return motionCrl.AbsorptionClose(iAbsorptionBit);
}

//��ͣ�˶�
int EC_PauseMove()
{
	return motionCrl.Pause();
}

//�����˶�
//int RestorationMove()
//{
//	return motionCrl.m_ControlGESInterface
//}

//���õ�ǰ����
int EC_SetCardNO(short cardNO)
{
	//return SetCardNO(cardNO);
	return 0;
}

//��ȡ��ǰ����
int EC_GetCardNO(short* cardNO)
{
	//return motionCrl.get
	return 0;
}

bool EC_ExeSetParamApplication()
{
	return motionCrl.SetConfigApplication();
}

//���¼ӹ�����
bool EC_UpdateMoveParam()
{
	return motionCrl.Init(0);
}