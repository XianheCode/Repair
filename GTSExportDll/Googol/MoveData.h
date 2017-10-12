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

	//运动参数间的赋值
	int operator=(const MoveData& theMoveParam);
	//////////////////////////////////////////////////////////////////////////
	//								信号管理
	int m_speedDown;
	int m_goOrig;
	int m_elimit;
	int m_alarm;
	//////////////////////////////////////////////////////////////////////////
	//								轴管理
	//	X轴, Y轴, Z轴, C轴 W轴 U轴 A轴 B轴 分别对应的参数
	int m_CardNum;						//卡总个数
	int** m_CardToAxisNO;				//卡对应的轴号(二维数组)
	int m_AxisNum;						//轴总个数
	int m_lPPM[MAX_AXISNUM];			//各个轴的脉冲当量
	double m_pCurPos[MAX_AXISNUM];		//各个轴存储在本地的当前位置
	int m_iAxisReverse[MAX_AXISNUM];	//各个轴是否反向的状态.	1-轴正向, -1-轴反向
	bool m_bEnableAxis[MAX_AXISNUM];	//各个轴是否是能 false-DisableAxis true-EnableAxis
	//用于形成坐标轴与物理电机形成的映射
	//NO1.X坐标轴->的物理轴号, NO2.Y坐标轴->的物理轴号, 
	//NO3.Z坐标轴->的物理轴号, NO4.C坐标轴->的物理轴号.如果非使能则物理轴号为-1
	int m_EnableAxiss[MAX_AXISNUM];		//各个轴对应的轴号
	//////////////////////////////////////////////////////////////////////////
	//                  速度加速度管理(单位,mm/s,mm/s/s)
	//PtoP运动速度
	double m_dAxisMoveAcc[MAX_AXISNUM];				//单轴运动加速度
	double m_dAxisMoveDec[MAX_AXISNUM];				//单轴运动减速度
	double m_dAxisMoveBegSpeed[MAX_AXISNUM];		//单轴运动起始速度
	double m_dAxisMoveSpeed[MAX_AXISNUM];			//单轴加工速度
	double m_dAxisEmptyMoveBegSpeed[MAX_AXISNUM];	//单轴空程起始速度
	double m_dAxisEmptyMoveSpeed[MAX_AXISNUM];		//单轴空程速度
	
	//手动移动高速(存储常用)
	double m_dBegSpeedMoveBig[MAX_AXISNUM];			//起始移动速度
	double m_dSpeedMoveBig[MAX_AXISNUM];			//移动速度
	double m_dAccSpeedMoveBig[MAX_AXISNUM];			//移动加速度
	double m_dDecSpeedMoveBig[MAX_AXISNUM];			//移动减速度
	double m_dConSpeedMoveBig[MAX_AXISNUM];			//移动常速度
	
	//手动移动中速(存储常用)
	double m_dBegSpeedMoveMiddle[MAX_AXISNUM];
	double m_dSpeedMoveMiddle[MAX_AXISNUM];
	double m_dAccSpeedMoveMiddle[MAX_AXISNUM];
	double m_dDecSpeedMoveMiddle[MAX_AXISNUM];
	double m_dConSpeedMoveMiddle[MAX_AXISNUM];
	
	//手动移动低速(存储常用)
	double m_dBegSpeedMoveMin[MAX_AXISNUM];
	double m_dSpeedMoveMin[MAX_AXISNUM];
	double m_dAccSpeedMoveMin[MAX_AXISNUM];
	double m_dDecSpeedMoveMin[MAX_AXISNUM];
	double m_dConSpeedMoveMin[MAX_AXISNUM];
	
	//回原点移动速度(存储常用)
	double m_dBegSpeedGoOrig[MAX_AXISNUM];
	double m_dSpeedGoOrig[MAX_AXISNUM];
	double m_dAccSpeedGoOrig[MAX_AXISNUM];
	double m_dDecSpeedGoOrig[MAX_AXISNUM];
	double m_dConSpeedGoOrig[MAX_AXISNUM];

	//XY轴插补加工速度
	double m_dXYMoveAcc;			//加工加速度
	double m_dXYMoveDec;			//加工减速度
	double m_dXYMoveBegSpeed;		//加工起始速度  
	double m_dXYMoveCornerAcc;		//加工拐角加速度(也可以是个比例系数)
	double m_dXYMoveSpeed;			//加工速度

	double m_dXYEmptyBeginSpeed;	//XY 空程起始速度
	double m_dXYEmptyAccSpeed;		//XY 空程加速度
	double m_dXYEmptyDecSpeed;		//XY 空程减速度
	double m_dXYEmptySpeed;			//XY 空程速度
	//////////////////////////////////////////////////////////////////////////
	//控制其它参数
	//X,Y,Z 回参后的默认的偏移值
	double m_backOffset[MAX_AXISNUM];		//回零后的偏移值
	double m_iOriginDirection[MAX_AXISNUM];	//回零的方向
	double m_iLimitDirection[MAX_AXISNUM];	//限位触发电平
	bool m_bGoOrgStyle;						//true-Z与XY分开回参，false-Z与XY共同回参
	int m_iOutputStatus;					//输出端口状态
//	TCHAR* m_strGTSConfigPath;				//GTS配置文件的路径
	TCHAR m_strGTSConfigPath[255];		
// 	int m_iGoOrgFirst;						//是否开机回参
// 	int m_iGoOrgCount;						//是否启用累计加工次数回参
// 	int m_iGoCountTimes;					//累计回参的次数
// 	BOOL   m_iLocal;						//0-回加工起点 1-回加固定位置
};
#endif // !defined(AFX_MOVEPARAM_H__75D05967_0C99_4F32_A9FC_418996B87646__INCLUDED_)
