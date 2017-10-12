#include "stdafx.h"
#include "BeckhoffControl.h"

CBeckhoffControl::CBeckhoffControl(void)
{
	m_pSpeedArray = NULL;
}

CBeckhoffControl::~CBeckhoffControl(void)
{
}

int CBeckhoffControl::Init(int* enableAxiss,int iEnableAxisNum, int* iCardNum, CDWordArray& iSignals)
{
	bool bValue = true;
	if (WriteDataFromBeckhoff((CString)(_T(".PLCAxisEnable")),bValue))
	{
		Reset();
		double dValue = 5;
		int iValue = 1;
		bool bValue = true;
		unsigned short usValue = 1;
		dValue = 5;
		WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[1]")),dValue);//X���ֶ���
		dValue = 12;	
		WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[2]")),dValue);//X���ֶ���
		dValue = 2;
		WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[4]")),dValue);//Y���ֶ���
		dValue = 5;
		WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[5]")),dValue);//Y���ֶ���
		dValue = 1;
		WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[7]")),dValue);//Z���ֶ���
		dValue = 4;
		WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[8]")),dValue);//Z���ֶ���
		usValue = 80;
		WriteDataFromBeckhoff((CString)(_T(".PLCFeedOverride")),usValue);

		WriteDataFromBeckhoff((CString)(_T(".BackwardStepMode")),bValue);
		//WriteDataFromBeckhoff((CString)(_T(".PLCManual_JogIncreament")),usValue);

		bValue = true;
		WriteDataFromBeckhoff((CString)(_T(".PLCMachineMode[1].Manual")),bValue);
		bValue = false;
		WriteDataFromBeckhoff((CString)(_T(".PLCManualTyp_Jog")),bValue);
		bValue = true;
		WriteDataFromBeckhoff((CString)(_T(".PLCManualTyp_Tip")),bValue);
		bValue = false;
		WriteDataFromBeckhoff((CString)(_T(".PLCManualRapidMode")),bValue);
		bValue = false;
		WriteDataFromBeckhoff((CString) _T(".PLCManualAxisPlus"),bValue);
		WriteDataFromBeckhoff((CString) _T(".PLCManualAxisMinus"),bValue);
	}
	return 0;
}
int CBeckhoffControl::WritePort(int iCard,int iOutState)
{
// 	WriteDataFromBeckhoff((CString) _T(".Valve_IO"),iOutState);
// 	AfxMessageBox(_T("�������ṩ����IOͬʱ�������"));
	return 0;//DigitalOutput(iOutState);
}
int CBeckhoffControl::WritePortBit(int iCard, int bitno, int status, int* iOutState)
{
// 	if ((bitno <= 0) || (bitno >= 16))
// 	{
// 		m_lastError = _T("д��Beckhoff���ó���,��Ҫ��0-16֮��");
// 		return -1;
// 	}
// 	else
// 	{
// 		if (status == 0)
// 		{
// 			int iValue = 1;
// 			int iData = iValue << (bitno - 1);
// 			int iLastData = ~iData;
// 			*iOutState = *iOutState & iLastData;
// 			WritePort(iCard, *iOutState);
// 		}
// 		else
// 		{
// 			int iValue = 1;
// 			int iData = iValue << (bitno - 1);
// 			*iOutState = *iOutState | iData;
// 			WritePort(iCard, *iOutState);
// 		}
// 	}
	return 0;
}

int CBeckhoffControl::GetPos(int iAxis, double* dPos)
{
	if (iAxis <= 0)
	{
		m_lastError = _T("��Ų���Ϊ0����");
		return -1;
	}
	else
	{
		//����û�о������ţ�Ĭ������X,Y,Z�����Ϊ0,1,2
		if (iAxis == 1)
		{
			return ReadDataFromBeckhoff((CString) _T(".AxisX_CurrPosition"),*dPos);
		}
		else if (iAxis == 2)
		{
			ReadDataFromBeckhoff((CString) _T(".AxisY_CurrPosition"),*dPos);
		}
		else if (iAxis == 3)
		{											 //.AxisZ_CurrPosition
			return ReadDataFromBeckhoff((CString) _T(".AxisZ_CurrPosition"),*dPos);
		}
		else if (iAxis == 4)
		{
			return WriteDataFromBeckhoff((CString) _T(".AxisU_CurrPosition"),*dPos);
		}
		else 
		{
			return -1;
		}
	}
	return 0;
}

/******************************************************************************
�� �� ��:			MoveTo
��    ��:	�˶�����λ��
�������:   iAxis ������ 1,2,3...
			iAxisNum �����
			posDestination Ŀ������
			iType  (1-��ʵ���˶� 2-ʵ���ƶ�)
�������:   
�� �� ֵ:   0 ��ʼ���ɹ� <0 ��ʼ��ʧ��
******************************************************************************/
int CBeckhoffControl::MoveTo(int* iAxis,int iAxisNum, double* posDestination, int iLen, int iType)
{
 	int iRet = 0;
	if (iType == 2)
	{
		//ֻ�е����˶��Ż����
		if (iAxisNum < 0)
		{
			return -1;
		}
		else
		{
			bool bValue = true;
			CStdioFile m_GCodeStdioFile;
			CString strGCodeStrFilePath = _T("C:\\AutoNC.nc");
			::DeleteFile(strGCodeStrFilePath);
			if (m_GCodeStdioFile.Open(strGCodeStrFilePath,CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate, NULL))
			{
				beckhoffLog.WriteLog(_T("�ƶ�XY"));
				m_GCodeStdioFile.WriteString(_T("G90\n"));
				CString strSpeed, strCommand;
				//�ƶ�X,Y
				bool bEnableXY = false;
				for (int i = 0; i<iAxisNum; i++)
				{
					CString strPos;
					strPos.Format(_T("%f"),posDestination[i]);
					if (iAxis[i] == 1)
					{
						strCommand = strCommand +  _T("X") + strPos;
						bEnableXY = true;
					}
					else if (iAxis[i] == 2)
					{
						strCommand = strCommand +  _T(" Y") + strPos;
						bEnableXY = true;
					}
				}
				if (bEnableXY)
				{
					strSpeed.Format(_T("F%f\n"),m_pSpeedArray[0]*60);
					m_GCodeStdioFile.WriteString(strSpeed);					
					beckhoffLog.WriteLog(_T("BegMoveTo"));
					m_GCodeStdioFile.WriteString(_T("G01 ") + strCommand +_T("\n"));
					beckhoffLog.WriteLog(_T("EndMoveTo"));
				}

				strCommand.Empty();
				bool bEnableZ = false;
				//�ƶ�Z
				for (int i = 0; i<iAxisNum; i++)
				{
					CString strPos;
					strPos.Format(_T("%f"),posDestination[i]);
					if (iAxis[i] == 3)
					{
						strCommand = strCommand +  _T(" Z") + strPos;
						bEnableZ = true;
					}
				}
				if (bEnableZ)
				{
					strSpeed.Format(_T("F600\n"));
					m_GCodeStdioFile.WriteString(strSpeed);					
					beckhoffLog.WriteLog(_T("BegMoveTo"));
					m_GCodeStdioFile.WriteString(_T("G01 ") + strCommand +_T("\n"));
					beckhoffLog.WriteLog(_T("EndMoveTo"));
				}

				//�ƶ�U
				strCommand.Empty();
				bool bEnableU = false;
				for (int i = 0; i<iAxisNum; i++)
				{
					CString strPos;
					strPos.Format(_T("%f"),posDestination[i]);
					if (iAxis[i] == 4)
					{
						strCommand = strCommand +  _T(" U") + strPos;
						bEnableU = true;
					}
				}
				if (bEnableU)
				{
					strSpeed.Format(_T("F100\n"));
					m_GCodeStdioFile.WriteString(strSpeed);					
					beckhoffLog.WriteLog(_T("BegMoveTo"));
					m_GCodeStdioFile.WriteString(_T("G01 ") + strCommand +_T("\n"));
					beckhoffLog.WriteLog(_T("EndMoveTo"));
				}
				m_GCodeStdioFile.WriteString(_T("M30\n"));
			}
			m_GCodeStdioFile.Close();
			BeginMove();
		}
	}
	return iRet;
}

/******************************************************************************
�� �� ��:			SetSpeedMove
��    ��:	�˶�����λ��
�������:   iEnableCoor ���������Ӧ����ѧ������(X,Y,Z)
			posDes ����ָ������λ�� iLen Ŀ��λ�ú�������ѧ����ϵ�����С
			iSpeedType �˶����ٶ����� 0.�ӹ��ٶ� 1.�˶��ز��ٶ�, 2-�����ٶ�, 3-�����ٶ� 4-΢���ٶ�
			iType  (1-��ʵ���˶� 2-ʵ���ƶ�)
�������:   
�� �� ֵ:   0 ��ʼ���ɹ� <0 ��ʼ��ʧ��
******************************************************************************/
int CBeckhoffControl::SetSpeedMove(int* iAxis, int iAxisNum, double* dHighSpeed, double* dLowSpeed, double* dAcc, int iType)
{
	if (m_pSpeedArray != NULL)
	{
		delete[] m_pSpeedArray;
		m_pSpeedArray = NULL;
	}

	if (iType == 2)
	{
		m_pSpeedArray = new double[iAxisNum];
		for (int j=0; j<iAxisNum; j++)
		{
			m_pSpeedArray[j] = dHighSpeed[j];
		}
	}
    return 0;
}

int CBeckhoffControl::GoHome(int* iAxis, int* iDirect, int* orgmove, int iStyle)
{
	Continue();
	CheckDone();
	return 0;
}

int CBeckhoffControl::Stop(int* iAxis, int iCount, int iType)
{
	int iRet = 0;
	if (iType == 1)
	{
		bool bValue = false;
		iRet = WriteDataFromBeckhoff((CString) _T(".PLCManualAxisMinus"),bValue);
		if (iRet < 0)
		{
			return iRet;
		}
		iRet = WriteDataFromBeckhoff((CString) _T(".PLCManualAxisPlus"),bValue);
		if (iRet < 0)
		{
			return iRet;
		}
// 		iRet = Pause();
// 		if (iRet < 0)
// 		{
// 			return iRet;
// 		}
	}
	else if (iType == 0)
	{
		bool bValue = false;
		int iRet = WriteDataFromBeckhoff((CString) _T(".PLCManualAxisMinus"),bValue);
		if (iRet < 0)
		{
			return iRet;
		}
		iRet = WriteDataFromBeckhoff((CString) _T(".PLCManualAxisPlus"),bValue);
		if (iRet < 0)
		{
			return iRet;
		}
// 		iRet = Pause();
// 		if (iRet < 0)
// 		{
// 			return iRet;
// 		}
		iRet = Reset();
		if (iRet < 0)
		{
			return iRet;
		}
	}
    return 0;
}

int CBeckhoffControl::ReadPort(int iCard, int bitno)
{
 	DWORD iRet = 0;
	AfxMessageBox(_T("��δ����"));//	DigitalInputBit(bitno, &iRet);
	return iRet;
}

int CBeckhoffControl::CheckHomeStatusAxis(int iAxis)
{
	AfxMessageBox(_T("���ԭ��״̬����"));
	return -1;//IsOrg(iAxis);
}

int CBeckhoffControl::CheckLimitStatusAxis(int iAxis)
{
	AfxMessageBox(_T("Aerotech����λ��δ����"));
	return 0;//IsLimitatiAxis);
}
/******************************************************************************
�� �� ��:			IsMoving
��    ��:	��ȡ����˶�״̬
�������:   iAxis ָ������ iLen ��ĳ���
�������:   
�� �� ֵ:   1 �˶�״̬ 0 ֹͣ״̬ -1 ����ʧ��
******************************************************************************/
int CBeckhoffControl::IsMoving(int* iAxis, int iLen)
{
//	return CheckDone(*iAxis);
	return 0;
}

int CBeckhoffControl::Pause()
{
	bool bValue = true;
	WriteDataFromBeckhoff((CString) _T(".PLCMachineMode[1].Stop"),bValue);
	return 0;
}
int CBeckhoffControl::Continue()
{
	bool bValue = true;
	Sleep(200);
	WriteDataFromBeckhoff((CString) _T(".PLCMachineMode[1].Start"), bValue);
	Sleep(200);
	return 0;
}
int CBeckhoffControl::PMove(int* iAxis, int iLen,int iDirect)
{
	bool bValue = true;
	unsigned short usValue = *iAxis;	
	double dValue = m_pSpeedArray[0]/16.666;//16.66���ڵ�λ����
	WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[1]")),dValue);//X���ֶ���
	WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[4]")),dValue);//Y���ֶ���
	dValue = 0.3;
	WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[7]")),dValue);//Z���ֶ���
	WriteDataFromBeckhoff((CString) _T(".GD_VisuAxisNumber"),usValue);
	bValue = false;
	WriteDataFromBeckhoff((CString)(_T(".PLCManualTyp_Jog")),bValue);
	bValue = true;
	WriteDataFromBeckhoff((CString)(_T(".PLCManualTyp_Tip")),bValue);
	if(iDirect > 0)
	{
		bValue = false;
		WriteDataFromBeckhoff((CString) _T(".PLCManualAxisMinus"),bValue);
		bValue = true;
		WriteDataFromBeckhoff((CString) _T(".PLCManualAxisPlus"),bValue);

	}
	else
	{
		bValue = false;
		WriteDataFromBeckhoff((CString) _T(".PLCManualAxisPlus"),bValue);
		bValue = true;
		WriteDataFromBeckhoff((CString) _T(".PLCManualAxisMinus"),bValue);
	}
    return 0;
}


int CBeckhoffControl::TestPPM(int iAxis,int iPulse)
{
	AfxMessageBox(_T("Aerotech ����ϵͳ����Ҫ��PC������������嵱��"));
	return 0;
}

int CBeckhoffControl::SetAbsPos(int iCoorAxis, double dPos)
{	
	//return m_mp2810.set_abs_pos(iCoorAxis, dPos);
	AfxMessageBox(_T("���þ�������ģʽ����"));
	return 0;
}

int CBeckhoffControl::PowerOn(int iPowerPort, int* iOutState)
{
	CString strCommand = _T("M60");
	return  OnlineCommand(strCommand, true);
}

int CBeckhoffControl::PowerOff(int iPowerPort, int* iOutState)
{
	CString strCommand = _T("M61");
	return  OnlineCommand(strCommand, true);
}

int CBeckhoffControl::GasOpen(int iGasPort,int* iOutState)
{
	return WritePortBit(1, iGasPort, 0, iOutState);
}

int CBeckhoffControl::GasClose(int iGasPort,int* iOutState)
{
	return WritePortBit(1, iGasPort, 1, iOutState);
}

int CBeckhoffControl::AbsorptionOpen(int iAbsorptionPort, int* iOutState)
{
	return WritePortBit(1, iAbsorptionPort, 1, iOutState);
}

int CBeckhoffControl::AbsorptionClose(int iAbsorptionPort, int* iOutState)
{
	return WritePortBit(1, iAbsorptionPort, 0, iOutState);
}

int CBeckhoffControl::IsRunningProgram()
{	
	if (!CheckDone())
	{
		return -2;
	}
	return 0;
}

bool CBeckhoffControl::Reset()
{
	double dValue = 5;
	int iValue = 1;
	bool bValue = true;
	unsigned short usValue = 1;
	bValue = true;
	WriteDataFromBeckhoff((CString)_T(".PLCMachineMode[1].Reset"),bValue);
	return true;
}

bool CBeckhoffControl::TwincatState()
{
	bool bValue = false;
	ReadDataFromBeckhoff((CString) _T(".bTwincatState"),bValue);
	return bValue;	
}

bool CBeckhoffControl::OnlineCommand(CString strOnlineCommand, bool bWait)
{
	bool bValue = true;
	CStdioFile m_GCodeStdioFile;
	CString strGCodeStrFilePath = _T("C:\\AutoNC.nc");
	::DeleteFile(strGCodeStrFilePath);
	if (m_GCodeStdioFile.Open(strGCodeStrFilePath,CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate, NULL))
	{
		m_GCodeStdioFile.WriteString(strOnlineCommand);
		beckhoffLog.WriteLog(strOnlineCommand);
	}
	m_GCodeStdioFile.Close();
	BeginMove();
	return true;
}

int CBeckhoffControl::BeginMove()
{
	Continue();
	if (!CheckDone())
	{
		return -2;
	}
	return true;
}
