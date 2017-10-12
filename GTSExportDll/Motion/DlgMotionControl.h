#if !defined(AFX_DLG2810CONTROL_H__1014BEE1_EBD9_4FF1_BE6E_3215FBC42D0F__INCLUDED_)
#define AFX_DLG2810CONTROL_H__1014BEE1_EBD9_4FF1_BE6E_3215FBC42D0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg2810Control.h : header file

#include "MotionInterface.h"
#include "../resource.h"
#include "afxwin.h"


struct Point
{
	double X;
	double Y;
	double Z;
	double C;
	double U;
	double W;
	double A;
	double B;
};
/////////////////////////////////////////////////////////////////////////////
// CDlgMotionControl dialog
class CDlgMotionControl : public CDialog
{
// Construction
public:
	int CheckGoHoming();
	int ShowAxisStatus();
	//iType 0-下 1-上 2-左 3-右 4-Z上 5-Z下 6-X轴有无限位 7-Y轴有无限位 8-Z轴有无限位 -1-是否存在限位
	//返回: true-超出限位 //false-未超出限位
	bool CheckSoftwareLimit(int iType);		
	int EnableControls(BOOL bEnable);
	int GetAbsCoor(CString& strXPos, CString& strYPos);
	CDlgMotionControl(CWnd* pParent = NULL);   // standard constructor
	CMotionInterface m_MC;
	int m_AxisNum;
	int m_EnableX;
	int m_EnableY;
	int m_EnableZ;
	//CEvent m_eventExit();
	HANDLE m_ExiteThread;
	void ShowAxisInfo(int iEnableX,int iEnableY,int iEnableZ);
	int Init();
	int DlgPos();
	HBITMAP m_hBitmapNal;
	HBITMAP m_hBitmapAl;
	HCURSOR hCursor;
	double m_dAxisLeftX;
	double m_dAxisRightX;
	double m_dAxisTopY;
	double m_dAxisBottomY;

	CFont m_font;
	Point ptTargetOne;
	Point ptTargetTwo;
	Point ptTargetThree;
	Point ptTargetFour;
	
	static UINT CheckMCStatus( LPVOID pParam );
	static UINT MoveTo( LPVOID pParam );
	void ThreadMoveTo();
	BOOL m_bShowStatus;

	//-1 未设定 0移动到指定坐标 1移动到目标位置1 2移动到目标位置2 3移动到取料位置
	int m_iMoveType;	

	virtual ~CDlgMotionControl();

private:
	//当前轴的绝对坐标
	BOOL ShowXYZPosition();
	//开启线程回参
	static UINT BeginBackHome(LPVOID lPparam);
//	CDlgHome* m_homeShow;


// Dialog Data
	//{{AFX_DATA(CDlgMotionControl)
	enum { IDD = IDD_DLG_MotionControl };
	CStatic	m_staticPosZ;
	CStatic	m_staticPosY;
	CStatic	m_staticPosX;
	CStatic	m_staticAxisZ;
	CStatic	m_staticAxisY;
	CStatic	m_staticAxisX;
	CStatic	m_ctl_OrigionZ;
	CStatic	m_ctl_OrigionY;
	CStatic	m_ctl_OrigionX;
	CStatic	m_ctl_LimitZ;
	CStatic	m_ctl_LimitY;
	CStatic	m_ctl_LimitX;
	//}}AFX_DATA
		

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMotionControl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMotionControl)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckOnstep();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonOrign();
	afx_msg void OnDestroy();
//	afx_msg void OnClose();
	afx_msg void OnBtnTargetOne();
	afx_msg void OnBtnTargetGesSth();
	afx_msg void OnBtnTargetTwo();
	afx_msg void OnBtnCCDLocation1();
	afx_msg void OnBtnCCDLocation2();
	afx_msg void OnBtnCCDLocation3();
public:
	afx_msg void OnBtnRadioOne();
	afx_msg void OnBtnRadioTwo();
	afx_msg void OnBtnRadioGetSth();
	afx_msg void OnBtnMoveToCCDLocation1();
	afx_msg void OnBtnMoveToCCDLocation2();
	afx_msg void OnBtnMoveToCCDLocation3();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CButton m_BtnUp;
	CButton m_BtnDown;
	CButton m_BtnLeft;
	CButton m_BtnRight;
	CButton m_BtnZUp;
	CButton m_BtnZDown;
	CButton m_BtnHome;

	CButton m_TargetOne;
	CButton m_TargetTwo;
	CButton m_TargetGetSth;
	int m_SelTestValue;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG2810CONTROL_H__1014BEE1_EBD9_4FF1_BE6E_3215FBC42D0F__INCLUDED_)
