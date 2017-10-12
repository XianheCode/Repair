// CMotionInterface.h: interface for the MotionControl
/*
 * CopyRight (c) 2017
 * All Rights reserved
 *
 * File Name		: MotionInterface.h
 * File ID			: None
 * Sumary			: For All Motion
 *
 * Current Version	: 1.0.0
 * Author			: Jackie Wu
 * Finish Time		: 2017-2-27
 * Last Modify Time : 2017-2-27
*/
//////////////////////////////////////////////////////////////////////
#ifndef _MOTIONINTERFACE_H_V1_20170227_
#define _MOTIONINTERFACE_H_V1_20170227_

#include "../stdafx.h"
#include <vector>
#include "MoveData.h"
#include "ControlInterface.h"
#include "GoogolGTSControl.h"
#include "../GTSExportDll.h"

class CMotionInterface
{
public:
	CMotionInterface();
	virtual ~CMotionInterface();

	bool m_bStop;
	CGoogolGTSControl* m_ControlGTSInterface;
	CControlInterface* m_pCMotionInterface;
	//////////////////////////////////////////////////////////////////////////

	MoveData m_moveData;
	//////////////////////////////////////////////////////////////////////////
	/******************************************************************************
	* Name		:	Init
	* Function	:	Init
	* In param	: iCardNum CarNO(Default CardNO 0)
	* Out param	:
	* Return	: 0-Success <0 Error
	******************************************************************************/
	int Init(int iCardNum = 0, CMotionInterface* pToSelf=nullptr);

	/******************************************************************************
	* Name		:	Close
	* Function	:	Close Card
	* In param	: 
	* Out param	:
	* Return	: 0-Success <0 Error
	******************************************************************************/
	int Close();

	/******************************************************************************
	* Name		:	GoOrigin
	* Function	:	Home
	* In param	: 
	* Out param	:   
	* Return	: 0-Success <0 Error
	******************************************************************************/	
	int GoOrigin();	

	int GoOrigin(HOMEPrm movePrm[], int iArrayNum, int iHomeType);

	/******************************************************************************
	* Name		:	PToPMove
	* Function	:	Move to abs pos (Point to Point)
	* In param	:	iEnableCoor MathCoordinate
	posDes PosArray
	iSpeedType Type
	Beckhoff (1-No Move 2-Acturly Move)
	* Out param	:
	* Return	: 0-Success <0 Error
	******************************************************************************/
	int PToPMove(TPTPPrm movePrm[], int iArrayNum);

	int SetSpeed(TSPEEDPrm movePrm[], int iArrayNum);

	/******************************************************************************
	* Name		:	PToPMove
	* Function	:	Move to abs pos (Point to Point)
	* In param	:	iType		SpeedType 0-Min 1-Middle 2-Max 3-Home 4-Custom
					iAxisNO		MathCoordinate
					iAxisNum	Axis-Count
					dHighSpeed	High-Speed
					dLowSpeed	Low-Speed
					dAcc		Acc
					dDec		Dec					
	* Out param	:
	* Return	: 0-Success <0 Error
	******************************************************************************/
	int SetPtoPSpeed(int iType, int * iAxisNO = nullptr, int iAxisNum = 0, double* dHighSpeed = nullptr, double* dLowSpeed=nullptr, double* dAcc=nullptr, double* dDec=nullptr);

	/******************************************************************************
	* Name		:	MoveArcTo
	* Function	:	Move to Circle EndPosition
	* In param	:	iAxis1 AxisNO1
					posCenter2 CenterX
					iAxis2 AxisN2
					posCenter2 CenterY
					angle SweepAngle
					dPosDes1 EndPosX
					dPosDes1 EndPosY
	* Out param	:   
	* Return	: 0-Success <0 Error
	******************************************************************************/
	int MoveArcTo(int iAxis1, double posCenter1, int iAxis2, double posCenter2, double angle,
		double dPosDes1, double dPosDes2);

	/******************************************************************************
	* Name		:	GetPos
	* Function	:	Get Save Pos
	* In param	:	iAxis AxisNO
	* Out param	:   
	* Return	:   Abs Pos
	******************************************************************************/
	double GetPos(int iCoorAxis);

	/******************************************************************************
	* Name		:	SetPos
	* Function	:	Set Save Pos (Change Local Data)
	* In param	:	iAxis AxisNO
	* Out param	:   
	* Return	:   Set Abs Pos
	******************************************************************************/
	double SetPos(int iCoorAxis, double dPos);

	/******************************************************************************
	* Name		:	SetAbsPos
	* Function	:	Set Actual Pos
	* In param	:	iAxis AxisNO
	* Out param	:   
	* Return	:   Set Abs Pos
	******************************************************************************/
	double SetAbsPos(int iCoorAxis, double dPos);	

	/******************************************************************************
	* Name		:	GetPosCur
	* Function	:	Get Actual Pos
	* In param	:	iAxis AxisNO
	* Out param	:   dPos Actual Pos
	* Return	:   0-Success <0 Error
	******************************************************************************/
	int GetPosCur(int iCoorAxis, double* dPos);

	/******************************************************************************
	* Name		:	StepPtoPMove
	* Function	:	Move Distace
	* In param	:	iAxisCoor MathCooridnate
					iAxisPosNum AxisCount
					posStep Move Step Distance
	* Out param	:   dPos Actual Pos
	* Return	:   0-Success <0 Error
	******************************************************************************/
	int StepPtoPMove(TSTEPPrm movePrm[], int iArrayNum);

	/******************************************************************************
	* Name		:	SetStepPtoPSpeed
	* Function	:	Move to Inc pos (Point to Point)
	* In param	:	iAxisNO MathCoordinate
					iAxisNum Axis-Count
					dHighSpeed High-Speed
					dLowSpeed  Low-Speed
					dAcc	   Acc
					dDec	   Dec
	* Out param	:
	* Return	: 0-Success <0 Error
	******************************************************************************/
	int SetStepPtoPSpeed(int iType, int* iAxisNO = nullptr, int iAxisNum = 0, double* dHighSpeed = nullptr, double* dLowSpeed = nullptr, double* dAcc = nullptr, double* dDec = nullptr);

	/******************************************************************************
	* Name		:	JogMove
	* Function	:	Jog Move
	* In param	:	iAxis Axis NO
					iAxis Count
					iDirect 
	* Out param	:   
	* Return	:   0-Success <0 Error
	******************************************************************************/
	int JogMove(TJOGPrm movePrm[], int iArrayNum);

	/******************************************************************************
	* Name		:	SetJogSpeed
	* Function	:	Set Jog Move Speed
	* In param	:	iType		SpeedType 0-Min 1-Middle 2-Max 3-Home 4-Custom
					iAxisNO		MathCoordinate
					iAxisNum	Axis-Count
					dHighSpeed	High-Speed
					dLowSpeed	Low-Speed
					dAcc		Acc
					dDec		Dec
	* Out param	:
	* Return	: 0-Success <0 Error
	******************************************************************************/
	int SetJogSpeed(int iType, int* iAxisNO=nullptr, int iAxisNum=0, double* dHighSpeed=nullptr, double* dLowSpeed=nullptr, double* dAcc=nullptr, double* dDec=nullptr);

	/******************************************************************************
	* Name		:	OutputBit
	* Function	:	Set Bit Output Signal
	* In param	:	iBit Bit
					iStatus 1-High  0-Low
	* Out param	:   
	* Return	:   0-Success <0 Error
	******************************************************************************/
	int OutputBit(int iBit,int iStatus);

	/******************************************************************************
	* Name		:	Output
	* Function	:	Set Output Signal
	* In param	:	iOutState all In Port
	* Out param	:   
	* Return	:   0-Success <0 Error
	******************************************************************************/
	int Output(int iOutState);

	/******************************************************************************
	* Name		:	GetOutputPortState
	* Function	:	Get Output Signal
	* In param	:	
	* Out param	:   
	* Return	:   Output Signal
	******************************************************************************/
	int GetOutputPortState();

	/******************************************************************************
	* Name		:	Input
	* Function	:	Get Input Signal
	* In param	:	
	* Out param	:   
	* Return	:   1-High  0-Low
	******************************************************************************/
	int Input(int iBit);

	/******************************************************************************
	* Name		:	Stop
	* Function	:	Stop Move
	* In param	:	iType
	* Out param	:   
	* Return	:   0-Success <0 Error
	******************************************************************************/
	int Stop(int iType = 0);

	/******************************************************************************
	* Name		:	HomeStatus
	* Function	:	Get Home Status
	* In param	:	iCoorAxis AxisCoordinate
	* Out param	:   
	* Return	:   0-Low  1-High
	******************************************************************************/
	int HomeStatus(int iCoorAxis);

	/******************************************************************************
	* Name		:	LimitStatus
	* Function	:	Get Limit Status
	* In param	:	iCoorAxis AxisCoordinate
	* Out param	:   
	* Return	:    0-Low  1-High
	******************************************************************************/
	int LimitStatus(int iAxisNO, int* iLimitP, int* iLimitN);
	/******************************************************************************
	* Name		:	IsMoving
	* Function	:	Get Move Status					
	* In param	:	iAxis -NO
	* Out param	:   iLen  -Counts
	* Return	:   0-Success <0 Error
	******************************************************************************/
	int IsMoving(int* iAxis, int iLen);
	/******************************************************************************
	* Name		:	Pause
	* Function	:	Pause Move					
	* In param	:	
	* Out param	:   
	* Return	:   0-Success <0 Error
	******************************************************************************/
	int Pause();
	/******************************************************************************
	* Name		:	BeginMove
	* Function	:	Begin Move Mode					
	* In param	:	
	* Out param	:   
	* Return	:   0-Success <0 Error
	******************************************************************************/
	int BeginMove();
	/******************************************************************************
	* Name		:	IsRunningProgram
	* Function	:	Move State					
	* In param	:	
	* Out param	:   
	* Return	:   0-Success <0 Error
	******************************************************************************/
	int IsRunningProgram();
	/******************************************************************************
	* Name		:	GetPPM
	* Function	:	Get Axis PPM					
	* In param	:	 0-X 1-Y 2-Z
	* Out param	:   
	* Return	:   PPM
	******************************************************************************/
	int GetPPM(int iCoorAxis);

	/******************************************************************************
	* Name		:	LaserOn
	* Function	:	Set Laser On					
	* In param	:	 iLaserBit - LaserPort
	* Out param	:   
	* Return	:   0-OK <0 Error
	******************************************************************************/
	int LaserOn(int iLaserBit);
	/******************************************************************************
	* Name		:	LaserOff
	* Function	:	Set Laser Off					
	* In param	:	iLaserBit - LaserPort
	* Out param	:   
	* Return	:   0-OK <0 Error
	******************************************************************************/
	int LaserOff(int iLaserBit);
	/******************************************************************************
	* Name		:	GasOpen
	* Function	:	Set Gas Open					
	* In param	:	iGasBit - GasPort
	* Out param	:   
	* Return	:   0-OK <0 Error
	******************************************************************************/
	int GasOpen(int iGasBit);
	/******************************************************************************
	* Name		:	GasClose
	* Function	:	Set Gas Close					
	* In param	:	iGasBit - GasPort
	* Out param	:   
	* Return	:   0-OK <0 Error
	******************************************************************************/
	int GasClose(int iGasBit);
	/******************************************************************************
	* Name		:	AbsorptionOpen
	* Function	:	Set Absorption Open					
	* In param	:	iAbsorptionBit - Absorption Port
	* Out param	:   
	* Return	:   0-OK <0 Error
	******************************************************************************/
	int AbsorptionOpen(int iAbsorptionBit);
	/******************************************************************************
	* Name		:	AbsorptionClose
	* Function	:	Set Absorption Close					
	* In param	:	iAbsorptionBit - Absorption Port
	* Out param	:   
	* Return	:   0-OK <0 Error
	******************************************************************************/
	int AbsorptionClose(int iAbsorptionBit);

	/******************************************************************************
	* Name		:	GetOriginStatus
	* Function	:	Get Origin Status
	* In param	:	
	* Out param	:   
	* Return	:   true-Yes false-No
	******************************************************************************/
	bool GetOriginStatus();
	/******************************************************************************
	* Name		:	GetAbsorptionStatus
	* Function	:	Get Absorption Status
	* In param	:	
	* Out param	:   
	* Return	:   true-Yes false-No
	******************************************************************************/
	bool GetAbsorptionStatus();
	/******************************************************************************
	* Name		:	GetLaserStatus
	* Function	:	Get Laser Status
	* In param	:	
	* Out param	:   
	* Return	:   true-Yes false-No
	******************************************************************************/
	bool GetLaserStatus();
	/******************************************************************************
	* Name		:	GetGasStatus
	* Function	:	Get Gas Status
	* In param	:	
	* Out param	:   
	* Return	:   true-Yes false-No
	******************************************************************************/
	bool GetGasStatus();
	/******************************************************************************
	* Name		:	SetConfigApplication
	* Function	:	UseApplicationSetSoftware
	* In param	:
	* Out param	:
	* Return	:   true-Yes false-No
	******************************************************************************/
	bool SetConfigApplication();

	char* UnicodeToAnsi(const wchar_t *szStr);

	int iAxisNOArray[MAX_AXISNUM];
	int iDirectArray[MAX_AXISNUM];
	double dLowVelArray[MAX_AXISNUM];
	double dHighVelArray[MAX_AXISNUM];
	double dAccArray[MAX_AXISNUM];
	double dDecArray[MAX_AXISNUM];

private:
	//	未回参过，未回参过未初始化过软件暂存坐标值，从控制器里面读取所有坐标值初始化。
	int CheckAlreadyOrg();
	bool m_bHoming;				//true-回参状态		false-非回参状态
	bool m_bHomeReady;			//true-已经回参过	false-未回参过
	bool m_bInitHomeReady;		//true-未回参过已经初始化过软件暂存坐标值 false-未回参过未初始化过软件暂存坐标值
	bool m_bAbsorptionStatus;	//true-吸附状态		false-停止吸附状态
	bool m_bPowerStatus;		//true-激光状态		false-停止激光状态
	bool m_bGasStatus;			//true-吹气状态		false-停止吹气状态
	bool m_bInit;				//true-已经初始化	false-未初始化



	/******************************************************************************
	* Name		:	ReadConfigFile
	* Function	:	Read config From File
	* In param	:
	* Out param	:
	* Return	:   true-Yes false-No
	******************************************************************************/
	bool ReadConfigFile();
	/******************************************************************************
	* Name		:	WriteConfigFile
	* Function	:	Write Config To File
	* In param	:
	* Out param	:
	* Return	:   true-Yes false-No
	******************************************************************************/
	bool WriteConfigFile();
};

#endif
