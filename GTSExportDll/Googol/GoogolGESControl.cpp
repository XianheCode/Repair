// GoogolControl.cpp: implementation of the CGoogolGESControl class.
/*
 * CopyRight (c) 2017
 * All Rights reserved
 *
 * File Name		: GoogolControl.cpp
 * File ID			: None
 * Sumary			: For Googol
 *
 * Current Version	: 1.0.0
 * Author			: Jackie Wu
 * Finish Time		: 2017-2-27
 * Last Modify Time : 2017-2-27
*/
//#include "stdafx.h"
#include "GoogolGESControl.h"

#define SEARCH_HOME		-12000000
#define HOME_OFFSET		-2000

CGoogolGESControl::CGoogolGESControl(void)
{
	m_pdHighSpeed = nullptr;
	m_pdLowSpeed = nullptr;
	m_pdAcc = nullptr;
	m_pdDec = nullptr;
}

CGoogolGESControl::~CGoogolGESControl(void)
{
	if (m_pdHighSpeed != nullptr)
	{
		delete[] m_pdHighSpeed;
		m_pdHighSpeed = nullptr;
	}
	if (m_pdLowSpeed != nullptr)
	{
		delete[] m_pdLowSpeed;
		m_pdLowSpeed = nullptr;
	}
	if (m_pdAcc != nullptr)
	{
		delete[] m_pdAcc;
		m_pdAcc = nullptr;
	}
	if (m_pdDec != nullptr)
	{
		delete[] m_pdDec;
		m_pdDec = nullptr;
	}
}

int CGoogolGESControl::Init(int* enableAxis, int iEnableAxisNum, int* iCardNum, void* pToSelf)
{
	unsigned short val = 0;
	long rtn = 0;

	rtn =GT_SwitchtoCardNo(0);
	rtn = GT_Open();
	if (rtn != 0)
	{
		return rtn;
	}

	// ��λ�˶�������
	rtn = GT_Reset();
	if (rtn != 0)
	{
		return rtn;
	}	

	unsigned short usLimitSts, usTempLimitSts, usTempLimitSts1;
	usTempLimitSts = 0x0000;
	//ֱ������Ϊ��������
	for (int i=0; i<iEnableAxisNum; i++)
	{
		//2017/4/12 ĿǰĬ��ʹ������+������ơ� ��ʹ��ģ�����ջ�����
		rtn = GT_CtrlMode(enableAxis[i], 1);
		if (rtn !=0 )
		{
			break;
		}
		rtn = GT_AlarmOff(enableAxis[i]);
		if (rtn !=0 )
		{
			break;
		}
 		// ���ø���������λ��Ч�͵�ƽ����״̬
		rtn = GT_LmtsOff(enableAxis[i]);
 		if (rtn !=0 )
 		{
 			break;
 		}

		rtn = GT_ClrSts(enableAxis[i]);
		if (rtn != 0)
		{
			break;
		}
		rtn = GT_AxisOn(enableAxis[i]);
		if (rtn != 0)
		{
			break;
		}
	}
	if (rtn != 0)
	{
		return rtn;
	}
	
	return rtn;
}

int CGoogolGESControl::Init(int* enableAxis, int iEnableAxisNum, int* iCardNum, double* pdLimitDir)
{
	unsigned short val = 0;
	long rtn = 0;

	rtn = GT_SwitchtoCardNo(0);
	rtn = GT_Open();
	if (rtn != 0)
	{
		return rtn;
	}

	// ��λ�˶�������
	rtn = GT_Reset();
	if (rtn != 0)
	{
		return rtn;
	}

	unsigned short usLimitSts, usTempLimitSts, usTempLimitSts1;
	usTempLimitSts = 0x0000;
	//ֱ������Ϊ��������
	for (int i = 0; i<iEnableAxisNum; i++)
	{
		//2017/4/12 ĿǰĬ��ʹ������+������ơ� ��ʹ��ģ�����ջ�����
		rtn = GT_CtrlMode(enableAxis[i], 1);
		if (rtn != 0)
		{
			break;
		}
		rtn = GT_AlarmOff(enableAxis[i]);
		if (rtn != 0)
		{
			break;
		}
		// ���ø���������λ��Ч�͵�ƽ����״̬
		rtn = GT_LmtsOn(enableAxis[i]);
		if (rtn != 0)
		{
			break;
		}
		if (pdLimitDir[i] == -1)
		{
			usTempLimitSts1 = 0x0001 << (enableAxis[i] - 1);
			usTempLimitSts = usTempLimitSts | usTempLimitSts1;
		}

		rtn = GT_ClrSts(enableAxis[i]);
		if (rtn != 0)
		{
			break;
		}
		rtn = GT_AxisOn(enableAxis[i]);
		if (rtn != 0)
		{
			break;
		}
	}
	if (rtn != 0)
	{
		return rtn;
	}

	//������λ������ƽ
	usLimitSts = 0xffff & usTempLimitSts;
	rtn = GT_LmtSns(usLimitSts);
	if (rtn == 0)
	{
		m_bInit = true;
	}

	return rtn;
}

int CGoogolGESControl::Close()
{
	GT_Close();
	return 0;
}

int CGoogolGESControl::OutputBit(int iCardNO, int bitNO, int iStatus, int* iOutStatus)
{
	int rtn = 0;
	/*	unsigned short outSts;
	rtn = GT_GetExOpt(&outSts);
	if (iStatus == 0)
	{
		outSts = outSts & (0xFFFE << bitNO);
	}
	else
	{
		outSts = outSts | (0x0001 << bitNO);
	}
	rtn = GT_ExOpt(outSts);
	if (rtn != 0)
		return rtn;

	rtn = GT_GetExOpt(&outSts);
	iOutStatus = (int*)outSts;
*/
	return GT_ExOptBit(bitNO, iStatus);
}

int CGoogolGESControl::Output(int iCard,int iOutState)
{
	rtn = GT_ExOpt(iOutState);
	if (rtn != 0)
		return rtn;

	return 0;
}

int CGoogolGESControl::GetRealTimePos(int iAxisNO, double* dRealTimePos)
{
	int iRtn = 0;
	double dRealPos[8];
	iRtn = GT_GetPrfPnt(dRealPos);
	*dRealTimePos = dRealPos[iAxisNO-1];

	return iRtn;
}

//���������岹
int CGoogolGESControl::MoveTo(int* iEnableCoor, int iAxisPosNum, double* posTarget,int iType)
{
	int iRtn = 0;

	//����ᱨ��״̬
	for (int i = 0; i < iAxisPosNum; i++)
	{
		iRtn = GT_ClrSts(iEnableCoor[i]);
	}
	/*
	//SetSpeed
	iRtn = GT_SetStrtVel(m_pdLowSpeed[0]);
	if (iType == 5)
	{
		iRtn += GT_SetSynAcc(m_pdHighSpeed[0]/10);
	}
	else
	{
		iRtn += GT_SetSynAcc(m_pdHighSpeed[0]);
	}
	iRtn += GT_SetSynVel(m_pdAcc[0]);
	iRtn += GT_SetStpAcc(m_pdDec[0]);
	iRtn += GT_SetEStpAcc(m_pdDec[0]);
	
	if (iRtn)
	{
		return iRtn;
	}
	*/

	//��ȡ��ǰλ��
	double posCurrent[4] = {0,0,0,0};
	iRtn = GT_GetPrfPnt(posCurrent);	//��ȡ����ĵ�ǰλ��

	//MoveTo
	double dXPos = posCurrent[0];
	double dYPos = posCurrent[1];
	double dZPos = posCurrent[2];
	double dAPos = posCurrent[3];
	for (int i = 0; i<iAxisPosNum; i++)
	{
		if (iEnableCoor[i] == 0)
		{
			dXPos = posTarget[i];
		}
		else if (iEnableCoor[i] == 1)
		{
			dYPos = posTarget[i];
		}
		else if (iEnableCoor[i] == 2)
		{
			dZPos = posTarget[i];
		}
		else if (iEnableCoor[i] == 3)
		{
			dAPos = posTarget[i];
		}
	}
	iRtn = GT_LnXYZA(dXPos, dYPos, dZPos, dAPos);
	if (iRtn)
	{
		return iRtn;
	}

	//�ȴ��˶����

		//Sleep(200);
		unsigned short crd_status;
		do
		{
			GT_GetCrdSts(&crd_status); //��ȡ����ϵ״̬
		} while (!(crd_status & 1)); //�ȴ��˶����

	return 0;
}

//bSleep:�Ƿ�ȴ��˶����
int CGoogolGESControl::MoveTo(int* iEnableAxis, int iAxisPosNum, double* posTarget,int iType, bool bSleep)
{
	int iRtn = 0;

	//����ᱨ��״̬
	for (int i = 0; i < iAxisPosNum; i++)
	{
		iRtn = GT_ClrSts(iEnableAxis[i]);
	}
	/*
	//SetSpeed
	iRtn = GT_SetStrtVel(m_pdLowSpeed[0]);
	if (iType == 5)
	{
	iRtn += GT_SetSynAcc(m_pdHighSpeed[0]/10);
	}
	else
	{
	iRtn += GT_SetSynAcc(m_pdHighSpeed[0]);
	}
	iRtn += GT_SetSynVel(m_pdAcc[0]);
	iRtn += GT_SetStpAcc(m_pdDec[0]);
	iRtn += GT_SetEStpAcc(m_pdDec[0]);

	if (iRtn)
	{
	return iRtn;
	}
	*/

	//��ȡ��ǰλ��
	double posCurrent[4] = { 0, 0, 0, 0 };
	iRtn = GT_GetPrfPnt(posCurrent);	//��ȡ����ĵ�ǰλ��

	//MoveTo
	bool bAxis1Do = false;
	bool bAxis2Do = false;
	bool bAxis3Do = false;
	bool bAxis4Do = false;
	double dXPos = posCurrent[0];
	double dYPos = posCurrent[1];
	double dZPos = posCurrent[2];
	double dAPos = posCurrent[3];
	for (int i = 0; i<iAxisPosNum; i++)
	{
		if (iEnableAxis[i] == 1)
		{
			dXPos = posTarget[i];
			bAxis1Do = true;
		}
		else if (iEnableAxis[i] == 2)
		{
			dYPos = posTarget[i];
			bAxis2Do = true;
		}
		else if (iEnableAxis[i] == 3)
		{
			dZPos = posTarget[i];
			bAxis3Do = true;
		}
		else if (iEnableAxis[i] == 4)
		{
			dAPos = posTarget[i];
			bAxis4Do = true;
		}
	}

	if (bAxis4Do)
	{
		iRtn = GT_LnXYZA(dXPos, dYPos, dZPos, dAPos);
	}
	else if (bAxis3Do)
	{
		iRtn = GT_LnXYZ(dXPos, dYPos, dZPos);
	}
	else
	{
		iRtn = GT_LnXY(dXPos, dYPos);
	}
	if (iRtn)
	{
		return iRtn;
	}

	//�ȴ��˶����
	if (bSleep)
	{
		//Sleep(200);
		unsigned short crd_status;
		do
		{
			GT_GetCrdSts(&crd_status); //��ȡ����ϵ״̬
		} while (!(crd_status & 1)); //�ȴ��˶����
	}

	return 0;
}

int CGoogolGESControl::SetSpeed(int* iAxisNO, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, double* dDec, int iType)
{
	return 0;
}

int CGoogolGESControl::SetSpeed(double dHighSpeed, double dLowSpeed, double dAcc, double dDec)
{
	int iRtn = 0;
	iRtn = GT_SetStrtVel(dLowSpeed);
	iRtn += GT_SetSynAcc(dAcc);
	iRtn += GT_SetSynVel(dHighSpeed);
	iRtn += GT_SetStpAcc(dDec);
	iRtn += GT_SetEStpAcc(dDec * 5);	//��ͣ���ٶ�Ϊƽ��ֹͣ��5��

	return iRtn;
}

//����Home���㷽ʽ
int CGoogolGESControl::GoOrigin(int* iAxisNO, int* iDirect, int iLen, int* orgmove, bool bStyle)
{
	short sRtn =0;
	unsigned short crd_status,axis_status;

	// �������ı�������λ
	for (int i = 0; i < iLen; i++)
	{
		sRtn = GT_ClrSts(iAxisNO[i]);
	}

	//�������λ���
	for (int i = 0; i < iLen; i++)
	{
		unsigned short iAxis = iAxisNO[i];
		int iHomeDirect = iDirect[i];
		
		int iAxisOne[1] = { iAxis };
		int iHomeDirectOne[1] = { -iHomeDirect };
		double dHomeCaptionOne[1] = { 0.0 };

		//�˶�����λ
		sRtn = JogMove(iAxisOne, 1, iHomeDirectOne,true);
		//����Home
		GT_ClrSts(iAxis);		//���ԭ����״̬
		GT_CaptHome(iAxis);		
		iHomeDirectOne[0] = iHomeDirect;
		sRtn = JogMove(iAxisOne, 1, iHomeDirectOne,false);
		do
		{
			GT_GetCrdSts(&crd_status); //��ȡ����ϵ״̬
			if (crd_status & 1)		   //����˶��Ѿ����
			{ //��Ȼû�д���Home �ź�
				return -1; //���ش������1
			}
			GT_GetSts(iAxis, &axis_status); //��ȡ������״̬
		} while (!(axis_status & 0x8)); //�ȴ�Home �źŴ���
		GT_StpMtn(); //ƽ��ֹͣ
		do
		{
			GT_GetCrdSts(&crd_status); //��ȡ����ϵ״̬
		} while (!(crd_status & 1)); //�ȴ��˶����

		long lpos;
		GT_GetCapt(iAxis, &lpos); //��ȡ����λ��
		dHomeCaptionOne[0] = lpos;
		MoveTo(iAxisOne, 1, dHomeCaptionOne, 0, true);
	}

	//�ȴ��˶���ɿ�ʼ
	while (IsMoving(iAxisNO, iLen) == 1)
	{
		//Sleep(100);
	}
	//�ȴ��˶���ɽ���
	for (int i=0; i<iLen; i++)
	{
		sRtn = GT_ZeroPos(iAxisNO[i]);
		if (sRtn != 0)
		{
			break;
		}
		double dPos[4] = {0,0,0,0};
		GT_GetPrfPnt(dPos);
		
		if ((fabs(dPos[iAxisNO[i]]))>0.001)
		{
			sRtn = GT_ZeroPos(iAxisNO[i]);
			GT_GetPrfPnt(dPos);
			if (sRtn != 0)
			{
				break;
			}
			if ((fabs(dPos[iAxisNO[i]]))>0.001)
			{
				//AfxMessageBox(("����δ�ɹ�"));
				return -1;
			}
		}
	}
	
	return sRtn;
}

//����Home�����������ٶ�
int CGoogolGESControl::GoOriginOne(int iAxisNO, int iDirect, int* orgmove, bool bStyle)
{
	short sRtn = 0;
	unsigned short crd_status, axis_status;

	// �����ı�������λ
	sRtn = GT_ClrSts(iAxisNO);

	//�������λ���
	unsigned short iAxis = iAxisNO;
	int iHomeDirect = iDirect;

	int iAxisOne[1] = { iAxis };
	int iHomeDirectOne[1] = { -iHomeDirect };
	double dHomeCaptionOne[1] = { 0.0 };

	//�˶�����λ
	sRtn = JogMove(iAxisOne, 1, iHomeDirectOne, true);
	//����Home
	GT_ClrSts(iAxis);		//���ԭ����״̬
	GT_CaptHome(iAxis);
	iHomeDirectOne[0] = iHomeDirect;
	sRtn = JogMove(iAxisOne, 1, iHomeDirectOne, false);
	do
	{
		GT_GetCrdSts(&crd_status); //��ȡ����ϵ״̬
		if (crd_status & 1)		   //����˶��Ѿ����
		{ //��Ȼû�д���Home �ź�
			return -1; //���ش������1
		}
		GT_GetSts(iAxis, &axis_status); //��ȡ������״̬
	} while (!(axis_status & 0x8)); //�ȴ�Home �źŴ���
	GT_StpMtn(); //ƽ��ֹͣ
	do
	{
		GT_GetCrdSts(&crd_status); //��ȡ����ϵ״̬
	} while (!(crd_status & 1)); //�ȴ��˶����

	long lpos;
	GT_GetCapt(iAxis, &lpos); //��ȡ����λ��
	dHomeCaptionOne[0] = lpos;
	MoveTo(iAxisOne, 1, dHomeCaptionOne, 0, true);

	//�ȴ��˶���ɿ�ʼ
	int iAxisL[4] = { 0, 1, 2, 3 };
	while (IsMoving(iAxisL, 4) == 1)
	{
		//Sleep(100);
	}
	//�ȴ��˶���ɽ���
	sRtn = GT_ZeroPos(iAxisNO);
	if (sRtn != 0)
	{
		return sRtn;
	}
	double dPos[4] = { 0, 0, 0, 0 };
	GT_GetPrfPnt(dPos);

	if ((fabs(dPos[iAxisNO]))>0.001)
	{
		sRtn = GT_ZeroPos(iAxisNO);
		GT_GetPrfPnt(dPos);
		if (sRtn != 0)
		{
			return sRtn;
		}
		if ((fabs(dPos[iAxisNO]))>0.001)
		{
			//AfxMessageBox(("����δ�ɹ�"));
			return -1;
		}
	}
	return sRtn;
}

int CGoogolGESControl::Stop(int* iAxisNO, int iCount, StopMode Type)
{
	return GT_StpMtn();
}

int CGoogolGESControl::Input(int iCardNO, int iBitNO)
{
	unsigned short sInputStatus;
	GT_ExInpt(&sInputStatus);
	if (sInputStatus&(0x1 << iBitNO))
	{
		return 1;
	}
	else
		return 0;
}

int CGoogolGESControl::GetOriginStatus(int iAxisNO)
{
	long sRtn;
	unsigned short sAxisStatus;					// ��״̬
	// ��ȡ��״̬
	sRtn = GT_GetSts(iAxisNO, &sAxisStatus);
	// ���Ѿ�������Home�����ͨ�����״̬λ
	if (sAxisStatus & 0x8)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int CGoogolGESControl::GetLimitStatus(int iAxisNO)
{
	long sRtn;
	unsigned short sAxisStatus;					// ��״̬
	int rtn = GT_ClrSts(iAxisNO);
	// ��ȡ��״̬
	sRtn = GT_GetSts(iAxisNO, &sAxisStatus);
	// ������λ
	if ((sAxisStatus & 0x20) || (sAxisStatus & 0x40))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int CGoogolGESControl::IsMoving(int* iAxisNO, int iLen)
{
	unsigned short crd_status;
	short sRtn = GT_GetCrdSts(&crd_status); //��ȡ����ϵ״̬
	if (!(crd_status & 1))
		return 1;
	else
		return 0;
}

//ͨ���˶�һ����ֵ��λ����ģ��Jogģʽ
int CGoogolGESControl::JogMove(int* iEnableCoor, int iLen, int* iDirection)
{
	double dJogPos[4];
	for (int i = 0; i < iLen; i++)
	{
		dJogPos[i] = iDirection[i] * 100000000;
	}

	return MoveTo(iEnableCoor, iLen, dJogPos, 5);
}

int CGoogolGESControl::JogMove(int* iEnableCoor, int iLen, int* iDirection, bool bSleep)
{
	double dJogPos[4];
	for (int i = 0; i < iLen; i++)
	{
		dJogPos[i] = iDirection[i] * 100000000;
	}

	return MoveTo(iEnableCoor, iLen, dJogPos, 5, bSleep);
}

int CGoogolGESControl::TestPPM(int iAxisNO, int iPulseCount)
{
	//AfxMessageBox(("Aerotech ����ϵͳ����Ҫ��PC������������嵱��"));
	return 0;
}

int CGoogolGESControl::SetAbsPos(int iAxisNO, double dPos)
{	
	//AfxMessageBox(("���þ�������ģʽ����"));
	return 0;
}

int CGoogolGESControl::LaserOn(int iLaserBit, int* iOutStatus)
{
	return OutputBit(1, iLaserBit, 0, iOutStatus);
}

int CGoogolGESControl::LaserOff(int iLaserBit, int* iOutStatus)
{
	return OutputBit(1, iLaserBit, 1, iOutStatus);
}

int CGoogolGESControl::GasOpen(int iGasBit, int* iOutStatus)
{
	return OutputBit(1, iGasBit, 0, iOutStatus);
}

int CGoogolGESControl::GasClose(int iGasBit, int* iOutStatus)
{
	return OutputBit(1, iGasBit, 1, iOutStatus);
}

int CGoogolGESControl::AbsorptionOpen(int iAbsorptionBit, int* iOutStatus)
{
	return OutputBit(1, iAbsorptionBit, 1, iOutStatus);
}

int CGoogolGESControl::AbsorptionClose(int iAbsorptionBit, int* iOutStatus)
{
	return OutputBit(1, iAbsorptionBit, 0, iOutStatus);
}

int CGoogolGESControl::PauseMove()
{
	return 0;
}

int CGoogolGESControl::RestorationMove()
{
	return 0;
}

int CGoogolGESControl::SetCardNO(short cardNO)
{
	 return GT_SwitchtoCardNo(cardNO);
}

int CGoogolGESControl::GetCardNO(short* cardNO)
{
	*cardNO  = GT_GetCurrentCardNo();
	return 0;
}