// MoveParam.cpp: implementation of the MoveData class.
//
//////////////////////////////////////////////////////////////////////
//#include "stdafx.h"
#include "MoveData.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
MoveData::MoveData()
{
	m_speedDown = 0;
	m_goOrig = 0;
	m_elimit = 0;
	m_alarm = 0;

	m_AxisNum = 0;
	m_CardNum = 0;
	for(int i=0; i<MAX_AXISNUM; i++)
	{
		m_pCurPos[i] = 0;
		m_lPPM[i] = 0;
		m_bEnableAxis[i] = false;
		m_iAxisReverse[i] = 1;
		m_EnableAxiss[i] = -1;
		m_dAxisMoveAcc[i]= 0;
		m_dAxisMoveDec[i]= 0;
		m_dAxisMoveBegSpeed[i]= 0;
		m_dAxisMoveSpeed[i]= 0;
		m_dAxisEmptyMoveBegSpeed[i]= 0;
		m_dAxisEmptyMoveSpeed[i]= 0;
		m_dBegSpeedMoveBig[i]= 0;
		m_dSpeedMoveBig[i]= 0;
		m_dAccSpeedMoveBig[i]= 0;
		m_dDecSpeedMoveBig[i]= 0;
		m_dConSpeedMoveBig[i]= 0;
		m_dBegSpeedMoveMiddle[i]= 0;
		m_dSpeedMoveMiddle[i]= 0;
		m_dAccSpeedMoveMiddle[i]= 0;
		m_dDecSpeedMoveMiddle[i]= 0;
		m_dConSpeedMoveMiddle[i]= 0;
		m_dBegSpeedMoveMin[i]= 0;
		m_dSpeedMoveMin[i]= 0;
		m_dAccSpeedMoveMin[i]= 0;
		m_dDecSpeedMoveMin[i]= 0;
		m_dConSpeedMoveMin[i]= 0;
		m_dBegSpeedGoOrig[i]= 0;
		m_dSpeedGoOrig[i]= 0;
		m_dAccSpeedGoOrig[i]= 0;
		m_dDecSpeedGoOrig[i]= 0;
		m_dConSpeedGoOrig[i]= 0;
		m_backOffset[i]= 0;
		m_iOriginDirection[i]= 1;
	}
	m_dXYMoveAcc = 0;
	m_dXYMoveDec = 0;
	m_dXYMoveBegSpeed = 0;
	m_dXYMoveCornerAcc = 0;
	m_dXYMoveSpeed = 0;
	m_dXYEmptyBeginSpeed = 0;
	m_dXYEmptyAccSpeed = 0;
	m_dXYEmptyDecSpeed = 0;
	m_dXYEmptySpeed = 0;
	m_bGoOrgStyle = false;
	m_iOutputStatus = 0xFFFFFF;

//	m_strGTSConfigPath = new TCHAR[255];
}

MoveData::~MoveData()
{
}

int MoveData::operator=(const MoveData& theMoveParam)
{
	m_speedDown = theMoveParam.m_speedDown;
	m_goOrig = theMoveParam.m_goOrig;
	m_elimit = theMoveParam.m_elimit;
	m_alarm = theMoveParam.m_alarm;

	m_AxisNum = theMoveParam.m_AxisNum;
	m_CardNum = theMoveParam.m_CardNum;
	for(int i=0; i<MAX_AXISNUM; i++)
	{
		m_pCurPos[i] = theMoveParam.m_pCurPos[i];
		m_lPPM[i] = theMoveParam.m_lPPM[i];
		m_bEnableAxis[i] = theMoveParam.m_bEnableAxis[i];
		m_iAxisReverse[i] = theMoveParam.m_iAxisReverse[i];
		m_dAxisMoveAcc[i] = theMoveParam.m_dAxisMoveAcc[i];
		m_dAxisMoveDec[i] = theMoveParam.m_dAxisMoveDec[i];
		m_dAxisMoveBegSpeed[i] = theMoveParam.m_dAxisMoveBegSpeed[i];
		m_dAxisMoveSpeed[i] = theMoveParam.m_dAxisMoveSpeed[i];
		m_dAxisEmptyMoveBegSpeed[i] = theMoveParam.m_dAxisEmptyMoveBegSpeed[i];
		m_dAxisEmptyMoveSpeed[i] = theMoveParam.m_dAxisEmptyMoveSpeed[i];
		m_dBegSpeedMoveBig[i] = theMoveParam.m_dBegSpeedMoveBig[i];
		m_dSpeedMoveBig[i] = theMoveParam.m_dSpeedMoveBig[i];
		m_dAccSpeedMoveBig[i] = theMoveParam.m_dAccSpeedMoveBig[i];
		m_dDecSpeedMoveBig[i] = theMoveParam.m_dDecSpeedMoveBig[i];
		m_dConSpeedMoveBig[i] = theMoveParam.m_dConSpeedMoveBig[i];
		m_dBegSpeedMoveMiddle[i] = theMoveParam.m_dBegSpeedMoveMiddle[i];
		m_dSpeedMoveMiddle[i] = theMoveParam.m_dSpeedMoveMiddle[i];
		m_dAccSpeedMoveMiddle[i] = theMoveParam.m_dAccSpeedMoveMiddle[i];
		m_dDecSpeedMoveMiddle[i] = theMoveParam.m_dDecSpeedMoveMiddle[i];
		m_dConSpeedMoveMiddle[i] = theMoveParam.m_dConSpeedMoveMiddle[i];
		m_dBegSpeedMoveMin[i] = theMoveParam.m_dBegSpeedMoveMin[i];
		m_dSpeedMoveMin[i] = theMoveParam.m_dSpeedMoveMin[i];
		m_dAccSpeedMoveMin[i] = theMoveParam.m_dAccSpeedMoveMin[i];
		m_dDecSpeedMoveMin[i] = theMoveParam.m_dDecSpeedMoveMin[i];
		m_dConSpeedMoveMin[i] = theMoveParam.m_dConSpeedMoveMin[i];
		m_dBegSpeedGoOrig[i] = theMoveParam.m_dBegSpeedGoOrig[i];
		m_dSpeedGoOrig[i] = theMoveParam.m_dSpeedGoOrig[i];
		m_dAccSpeedGoOrig[i] = theMoveParam.m_dAccSpeedGoOrig[i];
		m_dDecSpeedGoOrig[i] = theMoveParam.m_dDecSpeedGoOrig[i];
		m_dConSpeedGoOrig[i] = theMoveParam.m_dConSpeedGoOrig[i];
		m_backOffset[i] = theMoveParam.m_backOffset[i];
		m_iOriginDirection[i] = theMoveParam.m_iOriginDirection[i];
	}
	m_dXYMoveAcc = theMoveParam.m_dXYMoveAcc;
	m_dXYMoveDec = theMoveParam.m_dXYMoveDec;
	m_dXYMoveDec = theMoveParam.m_dXYMoveDec;
	m_dXYMoveCornerAcc = theMoveParam.m_dXYMoveCornerAcc;
	m_dXYMoveSpeed = theMoveParam.m_dXYMoveSpeed;
	m_dXYEmptyBeginSpeed = theMoveParam.m_dXYEmptyBeginSpeed;
	m_dXYEmptyAccSpeed = theMoveParam.m_dXYEmptyAccSpeed;
	m_dXYEmptyDecSpeed = theMoveParam.m_dXYEmptyDecSpeed;
	m_dXYEmptySpeed = theMoveParam.m_dXYEmptySpeed;
	m_bGoOrgStyle = theMoveParam.m_bGoOrgStyle;
	m_iOutputStatus = theMoveParam.m_iOutputStatus;

//	m_strGTSConfigPath = theMoveParam.m_strGTSConfigPath;
	wcscpy_s(m_strGTSConfigPath, theMoveParam.m_strGTSConfigPath);

	return 0;
}