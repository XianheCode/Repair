// MoveParam.h: interface for the MoveData class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _MOVEPARAM_H_V1_20170227_
#define _MOVEPARAM_H_V1_20170227_

#include <iostream>
#include "Define.h"
#include <tchar.h>
#include <stdlib.h>
#include<string.h>
using namespace std;

enum StopMode
{
	SuddenStop,
	SlowStop,
	StopCoordinate
};

struct MoveData
{
public:
	MoveData();
	virtual ~MoveData();

	//�˶�������ĸ�ֵ
	int operator=(const MoveData& theMoveParam);
	//////////////////////////////////////////////////////////////////////////
	//								�źŹ���
	int m_speedDown;
	int m_goOrig;
	int m_elimit;
	int m_alarm;
	//////////////////////////////////////////////////////////////////////////
	//								�����
	//	X��, Y��, Z��, C�� W�� U�� A�� B�� �ֱ��Ӧ�Ĳ���
	int m_CardNum;						//���ܸ���
	int** m_CardToAxisNO;				//����Ӧ�����(��ά����)
	int m_AxisNum;						//���ܸ���
	int m_lPPM[MAX_AXISNUM];			//����������嵱��
	double m_pCurPos[MAX_AXISNUM];		//������洢�ڱ��صĵ�ǰλ��
	int m_iAxisReverse[MAX_AXISNUM];	//�������Ƿ����״̬.	1-������, -1-�ᷴ��
	bool m_bEnableAxis[MAX_AXISNUM];	//�������Ƿ����� false-DisableAxis true-EnableAxis
	//�����γ����������������γɵ�ӳ��
	//NO1.X������->���������, NO2.Y������->���������, 
	//NO3.Z������->���������, NO4.C������->���������.�����ʹ�����������Ϊ-1
	int m_EnableAxiss[MAX_AXISNUM];		//�������Ӧ�����
	//////////////////////////////////////////////////////////////////////////
	//                  �ٶȼ��ٶȹ���(��λ,mm/s,mm/s/s)
	//PtoP�˶��ٶ�
	double m_dAxisMoveAcc[MAX_AXISNUM];				//�����˶����ٶ�
	double m_dAxisMoveDec[MAX_AXISNUM];				//�����˶����ٶ�
	double m_dAxisMoveBegSpeed[MAX_AXISNUM];		//�����˶���ʼ�ٶ�
	double m_dAxisMoveSpeed[MAX_AXISNUM];			//����ӹ��ٶ�
	double m_dAxisEmptyMoveBegSpeed[MAX_AXISNUM];	//����ճ���ʼ�ٶ�
	double m_dAxisEmptyMoveSpeed[MAX_AXISNUM];		//����ճ��ٶ�
	
	//�ֶ��ƶ�����(�洢����)
	double m_dBegSpeedMoveBig[MAX_AXISNUM];			//��ʼ�ƶ��ٶ�
	double m_dSpeedMoveBig[MAX_AXISNUM];			//�ƶ��ٶ�
	double m_dAccSpeedMoveBig[MAX_AXISNUM];			//�ƶ����ٶ�
	double m_dDecSpeedMoveBig[MAX_AXISNUM];			//�ƶ����ٶ�
	double m_dConSpeedMoveBig[MAX_AXISNUM];			//�ƶ����ٶ�
	
	//�ֶ��ƶ�����(�洢����)
	double m_dBegSpeedMoveMiddle[MAX_AXISNUM];
	double m_dSpeedMoveMiddle[MAX_AXISNUM];
	double m_dAccSpeedMoveMiddle[MAX_AXISNUM];
	double m_dDecSpeedMoveMiddle[MAX_AXISNUM];
	double m_dConSpeedMoveMiddle[MAX_AXISNUM];
	
	//�ֶ��ƶ�����(�洢����)
	double m_dBegSpeedMoveMin[MAX_AXISNUM];
	double m_dSpeedMoveMin[MAX_AXISNUM];
	double m_dAccSpeedMoveMin[MAX_AXISNUM];
	double m_dDecSpeedMoveMin[MAX_AXISNUM];
	double m_dConSpeedMoveMin[MAX_AXISNUM];
	
	//��ԭ���ƶ��ٶ�(�洢����)
	double m_dBegSpeedGoOrig[MAX_AXISNUM];
	double m_dSpeedGoOrig[MAX_AXISNUM];
	double m_dAccSpeedGoOrig[MAX_AXISNUM];
	double m_dDecSpeedGoOrig[MAX_AXISNUM];
	double m_dConSpeedGoOrig[MAX_AXISNUM];

	//XY��岹�ӹ��ٶ�
	double m_dXYMoveAcc;			//�ӹ����ٶ�
	double m_dXYMoveDec;			//�ӹ����ٶ�
	double m_dXYMoveBegSpeed;		//�ӹ���ʼ�ٶ�  
	double m_dXYMoveCornerAcc;		//�ӹ��սǼ��ٶ�(Ҳ�����Ǹ�����ϵ��)
	double m_dXYMoveSpeed;			//�ӹ��ٶ�

	double m_dXYEmptyBeginSpeed;	//XY �ճ���ʼ�ٶ�
	double m_dXYEmptyAccSpeed;		//XY �ճ̼��ٶ�
	double m_dXYEmptyDecSpeed;		//XY �ճ̼��ٶ�
	double m_dXYEmptySpeed;			//XY �ճ��ٶ�
	//////////////////////////////////////////////////////////////////////////
	//������������
	//X,Y,Z �زκ��Ĭ�ϵ�ƫ��ֵ
	double m_backOffset[MAX_AXISNUM];		//������ƫ��ֵ
	double m_iOriginDirection[MAX_AXISNUM];	//����ķ���
	double m_iLimitDirection[MAX_AXISNUM];	//��λ������ƽ
	bool m_bGoOrgStyle;						//true-Z��XY�ֿ��زΣ�false-Z��XY��ͬ�ز�
	int m_iOutputStatus;					//����˿�״̬
//	TCHAR* m_strGTSConfigPath;				//GTS�����ļ���·��
	TCHAR m_strGTSConfigPath[255];		
// 	int m_iGoOrgFirst;						//�Ƿ񿪻��ز�
// 	int m_iGoOrgCount;						//�Ƿ������ۼƼӹ������ز�
// 	int m_iGoCountTimes;					//�ۼƻزεĴ���
// 	BOOL   m_iLocal;						//0-�ؼӹ���� 1-�ؼӹ̶�λ��
};
#endif // !defined(AFX_MOVEPARAM_H__75D05967_0C99_4F32_A9FC_418996B87646__INCLUDED_)
