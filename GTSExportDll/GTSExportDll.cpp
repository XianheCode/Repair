// Win32ExportDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "GTSExportDll.h"

#include "./Googol/MotionInterface.h"

CMotionInterface motionCrl;


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

//��λ�˶��ƶ���ָ��λ�ü��˶�ģʽ
int EC_PToPMove(TPTPPrm movePrm[], int iArrayNum)
{
	return motionCrl.PToPMove(movePrm, iArrayNum);
}

int EC_SetSglSpeed(TSPEEDPrm movePrm[], int iArrayNum)
{
	return motionCrl.SetSpeed(movePrm, iArrayNum);
}

//��λ�˶��ƶ���ָ��λ�ü��˶�ģʽ
int EC_StepMove(TSTEPPrm movePrm[], int iArrayNum)
{
	return motionCrl.StepPtoPMove(movePrm, iArrayNum);
}

//��ԭ��
int EC_Home(HOMEPrm movePrm[], int iArrayNum, int iHomeType)
{
	return motionCrl.GoOrigin(movePrm, iArrayNum, iHomeType);
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
//	return motionCrl.GetOriginStatus(iAxisNO);
	return true;
}

//��ȡ����λ״̬
bool EC_GetLimitStatusAxis(int iAxisNO,int* iLimitP,int* iLimitN)
{
	return motionCrl.LimitStatus(iAxisNO, iLimitP, iLimitN);
}

//��ȡ�����˶�״̬
int EC_IsMoving(int* iAxisNO, int iLen)
{
	return motionCrl.IsMoving(iAxisNO, iLen);
}

//�����˶�
int EC_JogMove(TJOGPrm movePrm[], int iArrayNum)
{
	return motionCrl.JogMove(movePrm, iArrayNum);
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