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
		WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[1]")),dValue);//X轴手动慢
		dValue = 12;	
		WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[2]")),dValue);//X轴手动快
		dValue = 2;
		WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[4]")),dValue);//Y轴手动慢
		dValue = 5;
		WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[5]")),dValue);//Y轴手动快
		dValue = 1;
		WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[7]")),dValue);//Z轴手动慢
		dValue = 4;
		WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[8]")),dValue);//Z轴手动快
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
// 	AfxMessageBox(_T("倍福不提供所有IO同时输出功能"));
	return 0;//DigitalOutput(iOutState);
}
int CBeckhoffControl::WritePortBit(int iCard, int bitno, int status, int* iOutState)
{
// 	if ((bitno <= 0) || (bitno >= 16))
// 	{
// 		m_lastError = _T("写入Beckhoff设置出错,需要在0-16之间");
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
		m_lastError = _T("轴号不能为0或负数");
		return -1;
	}
	else
	{
		//倍福没有具体的轴号，默认配置X,Y,Z轴轴号为0,1,2
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
函 数 名:			MoveTo
功    能:	运动到定位置
输入参数:   iAxis 物理轴 1,2,3...
			iAxisNum 轴个数
			posDestination 目标数组
			iType  (1-不实际运动 2-实际移动)
输出参数:   
返 回 值:   0 初始化成功 <0 初始化失败
******************************************************************************/
int CBeckhoffControl::MoveTo(int* iAxis,int iAxisNum, double* posDestination, int iLen, int iType)
{
 	int iRet = 0;
	if (iType == 2)
	{
		//只有单步运动才会进来
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
				beckhoffLog.WriteLog(_T("移动XY"));
				m_GCodeStdioFile.WriteString(_T("G90\n"));
				CString strSpeed, strCommand;
				//移动X,Y
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
				//移动Z
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

				//移动U
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
函 数 名:			SetSpeedMove
功    能:	运动到定位置
输入参数:   iEnableCoor 与物理轴对应的数学坐标轴(X,Y,Z)
			posDes 到达指定坐标位置 iLen 目标位置和物理数学坐标系数组大小
			iSpeedType 运动的速度数据 0.加工速度 1.运动回参速度, 2-高速速度, 3-低速速度 4-微速速度
			iType  (1-不实际运动 2-实际移动)
输出参数:   
返 回 值:   0 初始化成功 <0 初始化失败
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
	AfxMessageBox(_T("暂未开发"));//	DigitalInputBit(bitno, &iRet);
	return iRet;
}

int CBeckhoffControl::CheckHomeStatusAxis(int iAxis)
{
	AfxMessageBox(_T("检查原点状态出错"));
	return -1;//IsOrg(iAxis);
}

int CBeckhoffControl::CheckLimitStatusAxis(int iAxis)
{
	AfxMessageBox(_T("Aerotech的限位暂未处理"));
	return 0;//IsLimitatiAxis);
}
/******************************************************************************
函 数 名:			IsMoving
功    能:	获取轴的运动状态
输入参数:   iAxis 指定的轴 iLen 轴的长度
输出参数:   
返 回 值:   1 运动状态 0 停止状态 -1 调用失败
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
	double dValue = m_pSpeedArray[0]/16.666;//16.66用于单位换算
	WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[1]")),dValue);//X轴手动慢
	WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[4]")),dValue);//Y轴手动慢
	dValue = 0.3;
	WriteDataFromBeckhoff((CString)(_T(".PLCMParList1[7]")),dValue);//Z轴手动慢
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
	AfxMessageBox(_T("Aerotech 数控系统不需要在PC软件端设置脉冲当量"));
	return 0;
}

int CBeckhoffControl::SetAbsPos(int iCoorAxis, double dPos)
{	
	//return m_mp2810.set_abs_pos(iCoorAxis, dPos);
	AfxMessageBox(_T("设置绝对坐标模式出错"));
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
