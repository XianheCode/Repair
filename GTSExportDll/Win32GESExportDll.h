#ifndef _Win32ExportDll_H_20170402_
#define _Win32ExportDll_H_20170402_

#include "./Googol/MotionGESInterface.h"

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

//�ƶ���ָ��λ�ã�����
extern "C" int __declspec(dllexport)EC_PToPMove(int* iAxisNO, int iAxisPosNum, double* posTarget);

//�ƶ���ָ��λ�ã�ʹ��
//iMoveType: 0-�Զ� 1-�ֶ�(ֻ�ܵ���)  ;  
//iHandMoveSpeedType �����ֶ�ģʽ�� 0-����  1-����  2-���� 3-����
extern "C" int __declspec(dllexport)EC_PToPMoveNew(int* iAxisNO, int iAxisPosNum, double* posTarget, int iMoveType, int iHandMoveSpeedType);

//�����ٶȼ��ٶ�ģʽ
extern "C" int  __declspec(dllexport)EC_SetPtoPSpeed(int iType, int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec);

//�ƶ��̶�����,����
extern "C" int __declspec(dllexport)EC_StepMove(int* iAxisNO, int iAxisPosNum, double* posStep);

//�ƶ��̶�����,ʹ��
extern "C" int __declspec(dllexport)EC_StepMoveNew(int* iAxisNO, int iAxisPosNum, double* posStep, int iMoveType, int iHandMoveSpeedType);

//�����ƶ��̶�������ٶȣ�����
extern "C" int  __declspec(dllexport)EC_SetStepSpeed(int iType, int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec);

//��ԭ��
extern "C" int  __declspec(dllexport)EC_Home();

//ֹͣ
extern "C" int  __declspec(dllexport)EC_Stop();

//�����ź�
extern "C" int  __declspec(dllexport)EC_Input(int iBitNO);

//��ȡԭ��״̬
extern "C" bool  __declspec(dllexport)EC_GetOriginStatus();

//��ȡ��ԭ��״̬
extern "C" bool  __declspec(dllexport)EC_GetOriginStatusAxis(int iAxisNO);

//��ȡ����λ״̬
extern "C" bool  __declspec(dllexport)EC_GetLimitStatus();

//��ȡ��λ״̬
extern "C" bool  __declspec(dllexport)EC_GetLimitStatusAxis(int iAxisNO);

//��ȡ�����˶�״̬
extern "C" int  __declspec(dllexport)EC_IsMoving(int* iAxisNO, int iLen);

//�����˶�,����
extern "C" int  __declspec(dllexport)EC_JogMove(int* iAxisNO, int iLen, int* iDirection);

//�����˶���ʹ��
//iHandMoveSpeedType �����ֶ�ģʽ�� 0-����  1-����  2-���� 3-����
extern "C" int  __declspec(dllexport)EC_JogMoveNew(int* iAxisNO, int iLen, int* iDirection, int iHandMoveSpeedType);

//���ó����˶��ٶ�
extern "C" int  __declspec(dllexport)EC_SetJogSpeed(int iType, int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec);

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

//���¼ӹ�����
extern "C"  bool  __declspec(dllexport)EC_UpdateMoveParam();

#endif