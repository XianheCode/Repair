
// Dlg2810Control.cpp : implementation file
//
#include "stdafx.h"
#include "DlgMotionControl.h"
#include "../Tool/Tool.h"
#include "DlgSetTargetCoord.h"
#include "../Tool/ReadWriteOperate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define  BUTTONSIZE 38;
/////////////////////////////////////////////////////////////////////////////
// CDlgMotionControl dialog

CDlgMotionControl::CDlgMotionControl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMotionControl::IDD, pParent)
	, m_SelTestValue(0)
{
	//{{AFX_DATA_INIT(CDlgMotionControl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hBitmapNal = NULL;
	m_hBitmapAl = NULL;
	hCursor = NULL;
	m_bShowStatus = TRUE;
	m_iMoveType = -1;
	m_AxisNum = 2;
}

CDlgMotionControl::~CDlgMotionControl()
{
	int mc= 0;
	hCursor = NULL;
}

void CDlgMotionControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMotionControl)
	DDX_Control(pDX, IDC_STATIC_SHOWCURPOSITIONZ, m_staticPosZ);
	DDX_Control(pDX, IDC_STATIC_SHOWCURPOSITIONY, m_staticPosY);
	DDX_Control(pDX, IDC_STATIC_SHOWCURPOSITIONX, m_staticPosX);
	DDX_Control(pDX, IDC_Static_AxisZ, m_staticAxisZ);
	DDX_Control(pDX, IDC_Static_AxisY, m_staticAxisY);
	DDX_Control(pDX, IDC_Static_AxisX, m_staticAxisX);
	DDX_Control(pDX, IDC_Static_OrgZ, m_ctl_OrigionZ);
	DDX_Control(pDX, IDC_Static_OrgY, m_ctl_OrigionY);
	DDX_Control(pDX, IDC_Static_OrgX, m_ctl_OrigionX);
	DDX_Control(pDX, IDC_Static_LimitZ, m_ctl_LimitZ);
	DDX_Control(pDX, IDC_Static_LimitY, m_ctl_LimitY);
	DDX_Control(pDX, IDC_Static_LimitX, m_ctl_LimitX);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTON_UP, m_BtnUp);
	DDX_Control(pDX, IDC_BUTTON_DOWN, m_BtnDown);
	DDX_Control(pDX, IDC_BUTTON_ZUP, m_BtnZUp);
	DDX_Control(pDX, IDC_BUTTON_ZDOWN, m_BtnZDown);
	DDX_Control(pDX, IDC_BUTTON_LEFT, m_BtnLeft);
	DDX_Control(pDX, IDC_BUTTON_RIGHT, m_BtnRight);
	DDX_Control(pDX, IDC_BUTTON_ORIGN, m_BtnHome);
	
	DDX_Control(pDX, IDC_BTN_TargetOne, m_TargetOne);
	DDX_Control(pDX, IDC_BTN_TargetTwo, m_TargetTwo);
	DDX_Control(pDX, IDC_BTN_TargetGetSth, m_TargetGetSth);

	DDX_Radio(pDX, IDC_RADIOOne, m_SelTestValue);
}


BEGIN_MESSAGE_MAP(CDlgMotionControl, CDialog)
	//{{AFX_MSG_MAP(CDlgMotionControl)
	ON_BN_CLICKED(IDC_CHECK_ONSTEP, OnCheckOnstep)
	ON_BN_CLICKED(IDC_RADIOOne,OnBtnRadioOne)
	ON_BN_CLICKED(IDC_RADIOTwo,OnBtnRadioTwo)
	ON_BN_CLICKED(IDC_RADIOGetSth,OnBtnRadioGetSth)
// 	ON_BN_CLICKED(IDC_BTN_MoveToCCDLocation1, OnBtnMoveToCCDLocation1)
// 	ON_BN_CLICKED(IDC_BTN_MoveToCCDLocation2, OnBtnMoveToCCDLocation2)
// 	ON_BN_CLICKED(IDC_BTN_MoveToCCDLocation3, OnBtnMoveToCCDLocation3)
	ON_BN_CLICKED(IDC_BTN_TargetOne, OnBtnTargetOne)
	ON_BN_CLICKED(IDC_BTN_TargetTwo, OnBtnTargetTwo)
// 	ON_BN_CLICKED(IDC_BTN_CCDLocation1, OnBtnCCDLocation1)
// 	ON_BN_CLICKED(IDC_BTN_CCDLocation2, OnBtnCCDLocation2)
// 	ON_BN_CLICKED(IDC_BTN_CCDLocation3, OnBtnCCDLocation3)
	ON_BN_CLICKED(IDC_BTN_TargetGetSth, OnBtnTargetGesSth)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_ORIGN, OnButtonOrign)
	ON_WM_DESTROY()
//	ON_WM_CLOSE()
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMotionControl message handlers

BOOL CDlgMotionControl::OnInitDialog()
{
	CDialog::OnInitDialog();
	CReadWriteOperate RWINI;
	RWINI.ReadKey(_T("MotionNode"), _T("TargetOneX"),ptTargetOne.X);
	RWINI.ReadKey(_T("MotionNode"), _T("TargetOneY"),ptTargetOne.Y);
	RWINI.ReadKey(_T("MotionNode"), _T("TargetOneZ"),ptTargetOne.Z);
	RWINI.ReadKey(_T("MotionNode"), _T("TargetOneC"),ptTargetOne.C);
	RWINI.ReadKey(_T("MotionNode"), _T("TargetOneU"),ptTargetOne.U);

	RWINI.ReadKey(_T("MotionNode"), _T("TargetTwoX"),ptTargetTwo.X);
	RWINI.ReadKey(_T("MotionNode"), _T("TargetTwoY"),ptTargetTwo.Y);
	RWINI.ReadKey(_T("MotionNode"), _T("TargetTwoZ"),ptTargetTwo.Z);
	RWINI.ReadKey(_T("MotionNode"), _T("TargetTwoC"),ptTargetTwo.C);
	RWINI.ReadKey(_T("MotionNode"), _T("TargetTwoU"),ptTargetTwo.U);

	RWINI.ReadKey(_T("MotionNode"), _T("TargetThreeX"),ptTargetThree.X);
	RWINI.ReadKey(_T("MotionNode"), _T("TargetThreeY"),ptTargetThree.Y);
	RWINI.ReadKey(_T("MotionNode"), _T("TargetThreeZ"),ptTargetThree.Z);
	RWINI.ReadKey(_T("MotionNode"), _T("TargetThreeC"),ptTargetThree.C);
	RWINI.ReadKey(_T("MotionNode"), _T("TargetThreeU"),ptTargetThree.U);

// 	m_homeShow = new CDlgHome();
// 	m_homeShow->Create(IDD_DLG_HOME,this);
// 	m_homeShow->MoveWindow(12,220,213,30);
// 	m_homeShow->ShowWindow(SW_HIDE);

	//////////////////////////////////////////////////////////////////////////
	//ButtonPos
	//1.Up
	CRect rect;
	m_BtnUp.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_UP)));
	//2.Down
	m_BtnDown.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_DOWN)));
	//3.Left
	m_BtnLeft.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_LEFT)));
	//4.Right
	m_BtnRight.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_RIGHT)));
	//////////////////////////////////////////////////////////////////////////
	//由于Z轴的上下是反着的，而且因此首先将图片加载反过来。再把控件的位置反过来
	//5.ZUp
	m_BtnZUp.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ZDOWN)));
	//6.ZDown
	m_BtnZDown.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_ZUP)));
	//////////////////////////////////////////////////////////////////////////
	//6.Home
	m_BtnHome.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_HOME)));
	//7.TargetOne
	m_TargetOne.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_CAMERA)));
	//8.TargetTwo
	m_TargetTwo.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_CAMERA)));
	//9.TargetGetSth
	m_TargetGetSth.SetBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP_WHERE)));
	Init();
	CenterWindow(GetParent());
	UpdateData(FALSE);
	return TRUE;
}

void CDlgMotionControl::ShowAxisInfo(int iEnableX,int iEnableY,int iEnableZ)
{
	if (m_bShowStatus)
	{
		if (iEnableX == 1)
		{
			GetDlgItem(IDC_Static_AxisX)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_SHOWCURPOSITIONX)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_Static_LimitX)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_Static_OrgX)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BUTTON_LEFT)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BUTTON_RIGHT)->ShowWindow(SW_SHOW);
		}
		else
		{
			GetDlgItem(IDC_Static_AxisX)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_SHOWCURPOSITIONX)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_Static_LimitX)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_Static_OrgX)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BUTTON_LEFT)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BUTTON_RIGHT)->ShowWindow(SW_HIDE);
		}
		if (iEnableY == 1)
		{
			GetDlgItem(IDC_Static_AxisY)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_SHOWCURPOSITIONY)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_Static_LimitY)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_Static_OrgY)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BUTTON_UP)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BUTTON_DOWN)->ShowWindow(SW_SHOW);
		}
		else
		{
			GetDlgItem(IDC_Static_AxisY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_SHOWCURPOSITIONY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_Static_LimitY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_Static_OrgY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BUTTON_UP)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BUTTON_DOWN)->ShowWindow(SW_HIDE);
		}
		if (iEnableZ == 1)
		{
			GetDlgItem(IDC_Static_AxisZ)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_SHOWCURPOSITIONZ)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_Static_LimitZ)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_Static_OrgZ)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BUTTON_ZUP)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BUTTON_ZDOWN)->ShowWindow(SW_SHOW);
		}
		else
		{
			GetDlgItem(IDC_Static_AxisZ)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_SHOWCURPOSITIONZ)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_Static_LimitZ)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_Static_OrgZ)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BUTTON_ZUP)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BUTTON_ZDOWN)->ShowWindow(SW_HIDE);
		}
	}
}
int CDlgMotionControl::Init()
{
	DlgPos();
//	m_MC.m_moveData = gpWorkData->m_param.m_moveData;
	if (m_MC.Init(0) < 0)
	{
		AfxMessageBox(_T("控制初始化失败!"));
	}
	else
	{		
// 		gpWorkData->m_param.m_moveData = m_MC.m_moveData;
// 		if (m_MC.m_moveData.m_iGoOrgFirst == 1)
// 		{
// 			OnButtonOrign();
// 		}		
	}
// 	m_AxisNum = m_MC.m_moveData.m_AxisNum;
// 	m_EnableX = m_MC.m_moveData.m_EnableX;
// 	m_EnableY = m_MC.m_moveData.m_EnableY;
// 	m_EnableZ = m_MC.m_moveData.m_EnableZ;

	//默认为中速
	((CButton *)GetDlgItem(IDC_RADIO_MIDDLE))->SetCheck(TRUE);
// 	if (m_MC.m_moveData.m_iCardType == 0)
// 	{
// 		AfxBeginThread(CheckMCStatus,this);
// 	}
// 	else
	{
#ifdef ENABLESHOWPOS
		SetTimer(12345,200,NULL);
#endif
	}
	return 0;
}

void CDlgMotionControl::OnButtonOrign() 
{
	// TODO: Add your control notification handler code here
	if (CheckGoHoming()==1)
	{
		return ;
	}
//	m_MC.m_moveData = gpWorkData->m_param.m_moveData;
// 	m_homeShow->SetMotionCtrl(&m_MC);
// 	m_homeShow->ShowWindow(SW_SHOW);
//	gpWorkData->m_bExistRefereceError = false;
	AfxBeginThread(BeginBackHome,this);
}


BOOL CDlgMotionControl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	int dwAxisX[1];
	int dwAxisY[1];
	int dwAxisZ[1];
	int dwAxisC[1];
	int dwAxisU[1];
	int dwAxisW[1];
	int dwAxisA[1];
	int dwAxisB[1];
	dwAxisX[0] = COORDI_AXISX;
	dwAxisY[0] = COORDI_AXISY;
	dwAxisZ[0] = COORDI_AXISZ;
	dwAxisC[0] = COORDI_AXISC;
	dwAxisU[0] = COORDI_AXISU;
	dwAxisW[0] = COORDI_AXISW;
	dwAxisA[0] = COORDI_AXISA;
	dwAxisB[0] = COORDI_AXISB;
	BOOL bOneStep = FALSE;
	double dMoveStep = 0;
	CString sMoveStep = _T("");
	bOneStep = ((CButton*)(GetDlgItem(IDC_CHECK_ONSTEP)))->GetCheck();
	if (bOneStep)//单步移动模式则读取单步数据
	{
		GetDlgItem(IDC_EDIT_MOVEONESTEP)->GetWindowText(sMoveStep);
		dMoveStep = CTool::CStringToDouble(sMoveStep);
	}

	//速度设置
	int iSpeedMode = -1;
	if ( ((CButton *)GetDlgItem(IDC_RADIO_BIG))->GetCheck())
	{
		iSpeedMode = 0;
	}
	else if ( ((CButton *)GetDlgItem(IDC_RADIO_MIDDLE))->GetCheck())
	{
		iSpeedMode = 1;
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO_MIN))->GetCheck())
	{
		iSpeedMode = 2;
	}
	else
	{
		AfxMessageBox(_T("速度模式设置1错误!"));
		return FALSE;
	}

	if (bOneStep) //单步移动
	{
		switch (pMsg->message)
		{
		case WM_LBUTTONDOWN:
			//放在每个端口移动前设置速度的原因是防止有除了
			//上，下，左，右端口给信号后，在回参发生前引起的速度被设置问题。

			if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_UP)->m_hWnd)
			{
				if (CheckGoHoming()==1)
				{
					return FALSE;
				}
				EnableControls(FALSE);
				m_MC.MoveStep(COORDI_AXISY,dMoveStep,iSpeedMode);
				EnableControls(TRUE);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_DOWN)->m_hWnd)
			{
				if (CheckGoHoming()==1)
				{
					return FALSE;
				}
				EnableControls(FALSE);
				m_MC.MoveStep(COORDI_AXISY,-dMoveStep,iSpeedMode);
				EnableControls(TRUE);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_LEFT)->m_hWnd)
			{
				if (CheckGoHoming()==1)
				{
					return FALSE;
				}
				EnableControls(FALSE);
				m_MC.MoveStep(COORDI_AXISX,-dMoveStep,iSpeedMode);
				EnableControls(TRUE);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_RIGHT)->m_hWnd)
			{
				if (CheckGoHoming()==1)
				{
					return FALSE;
				}
				EnableControls(FALSE);
				m_MC.MoveStep(COORDI_AXISX,dMoveStep,iSpeedMode);
				EnableControls(TRUE);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ZUP)->m_hWnd)
			{
				if (CheckGoHoming()==1)
				{
					return FALSE;
				}
				EnableControls(FALSE);

				m_MC.MoveStep(COORDI_AXISZ,dMoveStep,iSpeedMode);
				EnableControls(TRUE);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ZDOWN)->m_hWnd)
			{
				if (CheckGoHoming()==1)
				{
					return FALSE;
				}
				EnableControls(FALSE);
				
				m_MC.MoveStep(COORDI_AXISZ,-dMoveStep,iSpeedMode);
				EnableControls(TRUE);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCW)->m_hWnd)
			{
				if (CheckGoHoming()==1)
				{
					return FALSE;
				}
				EnableControls(FALSE);

				m_MC.MoveStep(COORDI_AXISC,dMoveStep,iSpeedMode);
				EnableControls(TRUE);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCCW)->m_hWnd)
			{
				if (CheckGoHoming()==1)
				{
					return FALSE;
				}
				EnableControls(FALSE);

				m_MC.MoveStep(COORDI_AXISC,-dMoveStep,iSpeedMode);
				EnableControls(TRUE);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_UFORWARD)->m_hWnd)
			{
				if (CheckGoHoming()==1)
				{
					return FALSE;
				}
				EnableControls(FALSE);

				m_MC.MoveStep(COORDI_AXISU,dMoveStep,iSpeedMode);
				EnableControls(TRUE);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_UBACK)->m_hWnd)
			{
				if (CheckGoHoming()==1)
				{
					return FALSE;
				}
				EnableControls(FALSE);

				m_MC.MoveStep(COORDI_AXISU,-dMoveStep,iSpeedMode);
				EnableControls(TRUE);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_WFORWARD)->m_hWnd)
			{
				if (CheckGoHoming()==1)
				{
					return FALSE;
				}
				EnableControls(FALSE);

				m_MC.MoveStep(COORDI_AXISU,dMoveStep,iSpeedMode);
				EnableControls(TRUE);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_WBACK)->m_hWnd)
			{
				if (CheckGoHoming()==1)
				{
					return FALSE;
				}
				EnableControls(FALSE);

				m_MC.MoveStep(COORDI_AXISU,-dMoveStep,iSpeedMode);
				EnableControls(TRUE);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_AFORWARD)->m_hWnd)
			{
				if (CheckGoHoming()==1)
				{
					return FALSE;
				}
				EnableControls(FALSE);

				m_MC.MoveStep(COORDI_AXISU,dMoveStep,iSpeedMode);
				EnableControls(TRUE);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ABACK)->m_hWnd)
			{
				if (CheckGoHoming()==1)
				{
					return FALSE;
				}
				EnableControls(FALSE);

				m_MC.MoveStep(COORDI_AXISU,-dMoveStep,iSpeedMode);
				EnableControls(TRUE);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_BFORWARD)->m_hWnd)
			{
				if (CheckGoHoming()==1)
				{
					return FALSE;
				}
				EnableControls(FALSE);

				m_MC.MoveStep(COORDI_AXISU,dMoveStep,iSpeedMode);
				EnableControls(TRUE);
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_BBACK)->m_hWnd)
			{
				if (CheckGoHoming()==1)
				{
					return FALSE;
				}
				EnableControls(FALSE);

				m_MC.MoveStep(COORDI_AXISU,-dMoveStep,iSpeedMode);
				EnableControls(TRUE);
			}
			break;
		}
	}
	else		//连续移动
	{
		switch (pMsg->message)
		{
		case WM_LBUTTONDOWN:
			{
				if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_DOWN)->m_hWnd)
				{
					if (CheckGoHoming()==1)
					{
						return FALSE;
					}
					m_MC.JogMove(dwAxisY,1,iSpeedMode,-1);
				}
				else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_UP)->m_hWnd)
				{
					if (CheckGoHoming()==1)
					{
						return FALSE;
					}
					m_MC.JogMove(dwAxisY,1,iSpeedMode,1);
				}
				else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_LEFT)->m_hWnd)
				{
					if (CheckGoHoming()==1)
					{
						return FALSE;
					}
					m_MC.JogMove(dwAxisX,1,iSpeedMode,-1);
				}
				else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_RIGHT)->m_hWnd)
				{
					if (CheckGoHoming()==1)
					{
						return FALSE;
					}
					m_MC.JogMove(dwAxisX,1,iSpeedMode,1);
					TRACE(_T("向右开始\n"));
				}
				else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ZUP)->m_hWnd)
				{
					if (CheckGoHoming()==1)
					{
						return FALSE;
					}
					m_MC.JogMove(dwAxisZ,1,iSpeedMode,1);
				}
				else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ZDOWN)->m_hWnd)
				{
					if (CheckGoHoming()==1)
					{
						return FALSE;
					}
					m_MC.JogMove(dwAxisZ,1,iSpeedMode,-1);
				}
				else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCW)->m_hWnd)
				{
					if (CheckGoHoming()==1)
					{
						return FALSE;
					}
					m_MC.JogMove(dwAxisC,1,iSpeedMode,1);
				}
				else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCCW)->m_hWnd)
				{
					if (CheckGoHoming()==1)
					{
						return FALSE;
					}
					m_MC.JogMove(dwAxisC,1,iSpeedMode,-1);
				}
				else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_UFORWARD)->m_hWnd)
				{
					if (CheckGoHoming()==1)
					{
						return FALSE;
					}
					m_MC.JogMove(dwAxisU,1,iSpeedMode,1);
				}
				else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_UBACK)->m_hWnd)
				{
					if (CheckGoHoming()==1)
					{
						return FALSE;
					}
					m_MC.JogMove(dwAxisU,1,iSpeedMode,-1);
				}
				else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_WFORWARD)->m_hWnd)
				{
					if (CheckGoHoming()==1)
					{
						return FALSE;
					}
					m_MC.JogMove(dwAxisW,1,iSpeedMode,1);
				}
				else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_WBACK)->m_hWnd)
				{
					if (CheckGoHoming()==1)
					{
						return FALSE;
					}
					m_MC.JogMove(dwAxisW,1,iSpeedMode,-1);
				}
				else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_AFORWARD)->m_hWnd)
				{
					if (CheckGoHoming()==1)
					{
						return FALSE;
					}
					m_MC.JogMove(dwAxisA,1,iSpeedMode,1);
				}
				else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_ABACK)->m_hWnd)
				{
					if (CheckGoHoming()==1)
					{
						return FALSE;
					}
					m_MC.JogMove(dwAxisA,1,iSpeedMode,-1);
				}
				else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_BFORWARD)->m_hWnd)
				{
					if (CheckGoHoming()==1)
					{
						return FALSE;
					}
					m_MC.JogMove(dwAxisB,1,iSpeedMode,1);
				}
				else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_BBACK)->m_hWnd)
				{
					if (CheckGoHoming()==1)
					{
						return FALSE;
					}
					m_MC.JogMove(dwAxisB,1,iSpeedMode,1);
				}
				break;
			}

		case  WM_LBUTTONUP:
			{
				if ((pMsg->hwnd == GetDlgItem(IDC_BUTTON_UP)->m_hWnd)
				||(pMsg->hwnd == GetDlgItem(IDC_BUTTON_DOWN)->m_hWnd)
				||(pMsg->hwnd == GetDlgItem(IDC_BUTTON_LEFT)->m_hWnd)
				||(pMsg->hwnd == GetDlgItem(IDC_BUTTON_RIGHT)->m_hWnd)
				||(pMsg->hwnd == GetDlgItem(IDC_BUTTON_ZUP)->m_hWnd)
				||(pMsg->hwnd == GetDlgItem(IDC_BUTTON_ZDOWN)->m_hWnd)
				||(pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCW)->m_hWnd)
				||(pMsg->hwnd == GetDlgItem(IDC_BUTTON_CCCW)->m_hWnd)
				||(pMsg->hwnd == GetDlgItem(IDC_BUTTON_UFORWARD)->m_hWnd)
				||(pMsg->hwnd == GetDlgItem(IDC_BUTTON_UBACK)->m_hWnd)
				||(pMsg->hwnd == GetDlgItem(IDC_BUTTON_WFORWARD)->m_hWnd)
				||(pMsg->hwnd == GetDlgItem(IDC_BUTTON_WBACK)->m_hWnd)
				||(pMsg->hwnd == GetDlgItem(IDC_BUTTON_AFORWARD)->m_hWnd)
				||(pMsg->hwnd == GetDlgItem(IDC_BUTTON_ABACK)->m_hWnd)
				||(pMsg->hwnd == GetDlgItem(IDC_BUTTON_BFORWARD)->m_hWnd)
				||(pMsg->hwnd == GetDlgItem(IDC_BUTTON_BBACK)->m_hWnd))
				{
					m_MC.Stop(1);
				}
			break;
			}
		}
	}
	if (pMsg->message == WM_KEYDOWN)
	{ 
		TCHAR nChar = (TCHAR) (pMsg->wParam);
		if (nChar == VK_ESCAPE)
		{
			return TRUE;
		}
		else if(nChar == VK_RETURN)
		{
			return TRUE;
		}
		else if (nChar == VK_SPACE)
		{
			return TRUE;
		}
	}	
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgMotionControl::OnBtnRadioTwo()
{
	if (CheckGoHoming()==1)
	{
		return ;
	}

	CDlgSetTargetCoord setTarget;
	setTarget.m_dSetPosX = ptTargetTwo.X;
	setTarget.m_dSetPosY = ptTargetTwo.Y;
	setTarget.m_dSetPosZ = ptTargetTwo.Z;
	setTarget.m_dSetPosC = ptTargetTwo.C;
	setTarget.m_dSetPosU = ptTargetTwo.U;
	setTarget.pMC = &m_MC;
	if (setTarget.DoModal() == IDOK)
	{
		ptTargetTwo.X = setTarget.m_dSetPosX;
		ptTargetTwo.Y = setTarget.m_dSetPosY;
		ptTargetTwo.Z = setTarget.m_dSetPosZ;
		ptTargetTwo.C = setTarget.m_dSetPosC;
		ptTargetTwo.U = setTarget.m_dSetPosU;
	}
}
void CDlgMotionControl::OnBtnRadioGetSth()
{
	if (CheckGoHoming()==1)
	{
		return ;
	}

	CDlgSetTargetCoord setTarget;
	setTarget.m_dSetPosX = ptTargetThree.X;
	setTarget.m_dSetPosY = ptTargetThree.Y;
	setTarget.m_dSetPosZ = ptTargetThree.Z;
	setTarget.m_dSetPosC = ptTargetThree.C;
	setTarget.m_dSetPosU = ptTargetThree.U;
	setTarget.pMC = &m_MC;
	if (setTarget.DoModal() == IDOK)
	{
		ptTargetThree.X = setTarget.m_dSetPosX;
		ptTargetThree.Y = setTarget.m_dSetPosY;
		ptTargetThree.Z = setTarget.m_dSetPosZ;
		ptTargetThree.C = setTarget.m_dSetPosC;
		ptTargetThree.U = setTarget.m_dSetPosU;
	}
}
void CDlgMotionControl::OnBtnRadioOne()
{
	if (CheckGoHoming()==1)
	{
		return ;
	}

	CDlgSetTargetCoord setTarget;
	setTarget.m_dSetPosX = ptTargetOne.X;
	setTarget.m_dSetPosY = ptTargetOne.Y;
	setTarget.m_dSetPosZ = ptTargetOne.Z;
	setTarget.m_dSetPosC = ptTargetOne.C;
	setTarget.m_dSetPosU = ptTargetOne.U;
	setTarget.pMC = &m_MC;
	if (setTarget.DoModal() == IDOK)
	{
		ptTargetOne.X = setTarget.m_dSetPosX;
		ptTargetOne.Y = setTarget.m_dSetPosY;
		ptTargetOne.Z = setTarget.m_dSetPosZ;
		ptTargetOne.C = setTarget.m_dSetPosC;
		ptTargetOne.U = setTarget.m_dSetPosU;
	}
}

void CDlgMotionControl::OnBtnMoveToCCDLocation1()
{
	m_iMoveType = 4;
	AfxBeginThread(MoveTo,this);
}

void CDlgMotionControl::OnBtnMoveToCCDLocation2()
{
	m_iMoveType = 5;
	AfxBeginThread(MoveTo,this);
}

void CDlgMotionControl::OnBtnMoveToCCDLocation3()
{
	m_iMoveType = 6;
	AfxBeginThread(MoveTo,this);
}
void CDlgMotionControl::OnBtnTargetOne()
{
	if (UpdateData(TRUE))
	{
		m_SelTestValue = 0;
		m_iMoveType = m_SelTestValue+1;
		AfxBeginThread(MoveTo,this);
	}

}
void CDlgMotionControl::OnBtnTargetGesSth()
{
	if (UpdateData(TRUE))
	{
		m_SelTestValue = 2;
		m_iMoveType = m_SelTestValue+1;
		AfxBeginThread(MoveTo,this);
	}
}
void CDlgMotionControl::OnBtnTargetTwo()
{
	if (UpdateData(TRUE))
	{
		m_SelTestValue = 1;
		m_iMoveType = m_SelTestValue+1;
		AfxBeginThread(MoveTo,this);
	}
}
void CDlgMotionControl::OnBtnCCDLocation1()
{
// 	if (CheckGoHoming()==1)
// 	{
// 		return ;
// 	}
// 	CDlgSetTargetCoord setTarget;
// 	setTarget.m_dSetPosX = m_MC.m_moveData.m_CCDLocation1X;
// 	setTarget.m_dSetPosY = m_MC.m_moveData.m_CCDLocation1Y;
// 	setTarget.m_dSetPosZ = m_MC.m_moveData.m_CCDLocation1Z;
// 	setTarget.pMC = &m_MC;
// 	if (setTarget.DoModal() == IDOK)
// 	{
// 		m_MC.m_moveData.m_CCDLocation1X = setTarget.m_dSetPosX;
// 		m_MC.m_moveData.m_CCDLocation1Y = setTarget.m_dSetPosY;
// 		m_MC.m_moveData.m_CCDLocation1Z = setTarget.m_dSetPosZ;
// 		m_MC.m_moveData.WriteConfig();
// 	}
}
void CDlgMotionControl::OnBtnCCDLocation2()
{
// 	if (CheckGoHoming()==1)
// 	{
// 		return ;
// 	}
// 	CDlgSetTargetCoord setTarget;
// 	setTarget.m_dSetPosX = m_MC.m_moveData.m_CCDLocation2X;
// 	setTarget.m_dSetPosY = m_MC.m_moveData.m_CCDLocation2Y;
// 	setTarget.m_dSetPosZ = m_MC.m_moveData.m_CCDLocation2Z;
// 	setTarget.pMC = &m_MC;
// 	if (setTarget.DoModal() == IDOK)
// 	{
// 		m_MC.m_moveData.m_CCDLocation2X = setTarget.m_dSetPosX;
// 		m_MC.m_moveData.m_CCDLocation2Y = setTarget.m_dSetPosY;
// 		m_MC.m_moveData.m_CCDLocation2Z = setTarget.m_dSetPosZ;
// 		m_MC.m_moveData.WriteConfig();
// 	}
}
void CDlgMotionControl::OnBtnCCDLocation3()
{
// 	if (CheckGoHoming()==1)
// 	{
// 		return ;
// 	}
// 	CDlgSetTargetCoord setTarget;
// 	setTarget.m_dSetPosX = m_MC.m_moveData.m_CCDLocation3X;
// 	setTarget.m_dSetPosY = m_MC.m_moveData.m_CCDLocation3Y;
// 	setTarget.m_dSetPosZ = m_MC.m_moveData.m_CCDLocation3Z;
// 	setTarget.pMC = &m_MC;
// 	if (setTarget.DoModal() == IDOK)
// 	{
// 		m_MC.m_moveData.m_CCDLocation3X = setTarget.m_dSetPosX;
// 		m_MC.m_moveData.m_CCDLocation3Y = setTarget.m_dSetPosY;
// 		m_MC.m_moveData.m_CCDLocation3Z = setTarget.m_dSetPosZ;
// 		m_MC.m_moveData.WriteConfig();
// 	}
}

UINT CDlgMotionControl::BeginBackHome(LPVOID lPparam)
{
	CoInitialize(NULL);
	CDlgMotionControl* pCtrl = (CDlgMotionControl*) lPparam;
	pCtrl->m_MC.GoOrigin();
//	pCtrl->m_homeShow->ShowWindow(SW_HIDE);
	::CoUninitialize();
	return 0;
}

int CDlgMotionControl::DlgPos()
{
	CBitmap bmp;	
	bmp.LoadBitmap(IDB_BITMAP_NORMAL);
	m_ctl_LimitX.ModifyStyle(0,SS_BITMAP);
	
	m_ctl_LimitX.SetBitmap(bmp);
	
	m_hBitmapNal = ::LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP_NORMAL));
	m_hBitmapAl = ::LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP_ALARM));
	
	m_ctl_LimitX.ModifyStyle(0,SS_BITMAP);	
	m_ctl_LimitX.SetBitmap(m_hBitmapNal);
	
	m_ctl_LimitY.ModifyStyle(0,SS_BITMAP);
	m_ctl_LimitY.SetBitmap(m_hBitmapNal);
	
	m_ctl_LimitZ.ModifyStyle(0,SS_BITMAP);
	m_ctl_LimitZ.SetBitmap(m_hBitmapNal);
	
	m_ctl_OrigionX.ModifyStyle(0,SS_BITMAP);
	m_ctl_OrigionX.SetBitmap(m_hBitmapNal);
	
	m_ctl_OrigionY.ModifyStyle(0,SS_BITMAP);
	m_ctl_OrigionY.SetBitmap(m_hBitmapNal);
	
	m_ctl_OrigionZ.ModifyStyle(0,SS_BITMAP);
	m_ctl_OrigionZ.SetBitmap(m_hBitmapNal);
	return 0;
}

void CDlgMotionControl::OnCheckOnstep() 
{
	if(((CButton*)(GetDlgItem(IDC_CHECK_ONSTEP)))->GetCheck())
	{
		GetDlgItem(IDC_EDIT_MOVEONESTEP)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_MOVEONESTEP)->EnableWindow(FALSE);
	}	
}

void CDlgMotionControl::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (nIDEvent == 12345)
	{
 		ShowAxisStatus();
// 		ShowAxisInfo(m_EnableX,m_EnableY,m_EnableZ);

// 		if (CheckSoftwareLimit(-1))
// 		{
// 			((CMainFrame*)AfxGetApp()->m_pMainWnd)->WriteLog(_T("检测到软限位停止"));
// 			m_MC.Stop(0);
// 		}
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CDlgMotionControl::ShowXYZPosition()
{
	return TRUE;
}

int CDlgMotionControl::GetAbsCoor(CString& strXPos, CString& strYPos)
{
	int iRet = 0;
	double dPos = -10000;
	iRet = m_MC.GetPosCur(COORDI_AXISX,&dPos);
	strXPos.Format(_T("\n%.4f"), dPos);
	if (iRet != 0)
	{
		return iRet;
	}

	iRet = m_MC.GetPosCur(COORDI_AXISY,&dPos);
	strYPos.Format(_T("\n%.4f"), dPos);
	return iRet;
}
int CDlgMotionControl::EnableControls(BOOL bEnable)
{
	GetDlgItem(IDC_BUTTON_UP)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_DOWN)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_LEFT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_RIGHT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_ZDOWN)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_ZUP)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_ORIGN)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_TargetOne)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_TargetTwo)->EnableWindow(bEnable);
 	GetDlgItem(IDC_CHECK_ONSTEP)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MOVEONESTEP)->EnableWindow(bEnable);
	return 0;
}

//iType 0-下 1-上 2-左 3-右 4-Z上 5-Z下 6-X轴有无限位 7-Y轴有无限位 8-Z轴有无限位 -1-是否存在限位
bool CDlgMotionControl::CheckSoftwareLimit(int iType)
{
//	if (!((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_bDisableSoftwareLimit)
	{
		if (!m_MC.GetOriginStatus())
		{
			double dPosX = 0;
			double dPosY = 0;
			int iRet = m_MC.GetPosCur(COORDI_AXISX,&dPosX);
			iRet = m_MC.GetPosCur(COORDI_AXISY,&dPosY);	
			if (iType == -1)
			{
				if (((dPosX-m_dAxisLeftX)<0)
					||((dPosX-m_dAxisRightX)>0)
					||((dPosY-m_dAxisBottomY)<0)
					||((dPosY-m_dAxisTopY)>0))
				{
					return true;
				}
				else
				{
					return false;
				}	
			}
			else if (iType == 6)
			{
				if (((dPosX-m_dAxisLeftX)<0)
					||((dPosX-m_dAxisRightX)>0))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (iType == 7)
			{
				if (((dPosY-m_dAxisBottomY)<0)
					||((dPosY-m_dAxisTopY)>0))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (iType == 8)
			{
				return false;
			}
			else
			{
				if ((dPosX-m_dAxisLeftX)<0)			
				{
					if (iType == 3)
					{
						return false;
					}
					else
					{
						return true;
					}
				}
				if ((dPosX-m_dAxisRightX)>0)
				{
					if (iType == 2)
					{
						return false;
					}
					else
					{
						return true;
					}
				}
				if ((dPosY-m_dAxisBottomY)<0)
				{
					if (iType == 1)
					{
						return false;
					}
					else
					{
						return true;
					}
				}
				if ((dPosY-m_dAxisTopY)>0)
				{
					if (iType == 0)
					{
						return false;
					}
					else
					{
						return true;
					}
				}
				return false;
			}
		}
		else
		{
			return false;
		}
 	}
// 	else
// 	{
// 		return false;
// 	}
}
int CDlgMotionControl::ShowAxisStatus()
{
	try
	{
		int* iAxis = new int[m_AxisNum];
		int* iStatusLimit = new int[m_AxisNum];
		int* iStatusHome = new int[m_AxisNum];
		CString s;		
		int iCount = 0;
		for (int k=COORDI_AXISX; k<MAX_AXISNUM; k++)
		{
// 			if (m_MC.m_moveData.m_EnableAxiss[k] >0)
// 			{
// 				iStatusLimit[iCount] = m_MC.LimitStatus(k);
//				iStatusHome[iCount] = m_MC.HomeStatus(k);
// 				iAxis[iCount] = k;
// 				iCount ++;
// 			}
		}
	
// 		if (m_EnableX == 1)
// 		{
			double dPos = -10000;
			m_MC.GetPosCur(COORDI_AXISX,&dPos);
			s.Format(_T("%.3f"), (dPos));
 			GetDlgItem(IDC_STATIC_SHOWCURPOSITIONX)->SetWindowText(s);
// 		}
// 		if (m_EnableY == 1)
// 		{
			m_MC.GetPosCur(COORDI_AXISY,&dPos);
			s.Format(_T("%.3f"), (dPos));
			GetDlgItem(IDC_STATIC_SHOWCURPOSITIONY)->SetWindowText(s);
//		}
//		if (m_EnableZ == 1)
//		{
			m_MC.GetPosCur(COORDI_AXISZ,&dPos);
			s.Format(_T("%.3f"), (dPos));
			GetDlgItem(IDC_STATIC_SHOWCURPOSITIONZ)->SetWindowText(s);

			m_MC.GetPosCur(COORDI_AXISC,&dPos);
			s.Format(_T("%.3f"), (dPos));
			GetDlgItem(IDC_STATIC_SHOWCURPOSITIONC)->SetWindowText(s);

			m_MC.GetPosCur(COORDI_AXISU,&dPos);
			s.Format(_T("%.3f"), (dPos));
			GetDlgItem(IDC_STATIC_SHOWCURPOSITIONU)->SetWindowText(s);


			//非回参状态下，减少Z轴负向行程，进行软件坐标的保护
//		}	
		
// 		for(int i=0; i<m_AxisNum; i++)
// 		{
// 			if(iStatusHome[i]==1)
// 			{
// 				if (iAxis[i] == 0)
// 				{
// 					GetDlgItem(IDC_STATIC_SHOWCURPOSITIONX)->SetWindowText(_T("0.000"));
// 					m_ctl_OrigionX.SetBitmap(m_hBitmapNal);
// 				}
// 				else if (iAxis[i] == 1)
// 				{
// 					GetDlgItem(IDC_STATIC_SHOWCURPOSITIONY)->SetWindowText(_T("0.000"));
// 					m_ctl_OrigionY.SetBitmap(m_hBitmapNal);
// 				}
// 				else if (iAxis[i] == 2)
// 				{
// 					GetDlgItem(IDC_STATIC_SHOWCURPOSITIONZ)->SetWindowText(_T("0.000"));
// 					m_ctl_OrigionZ.SetBitmap(m_hBitmapNal);
// 				}
// 			}
// 			else
// 			{
// 				if (iAxis[i] == 0)
// 					m_ctl_OrigionX.SetBitmap(m_hBitmapAl);
// 				else if (iAxis[i] == 1)
// 					m_ctl_OrigionY.SetBitmap(m_hBitmapAl);
// 				else if (iAxis[i] == 2)
// 					m_ctl_OrigionZ.SetBitmap(m_hBitmapAl);
// 			}
// 			if(iStatusLimit[i]==1)
// 			{
// 				if (iAxis[i] == 0)
// 					m_ctl_LimitX.SetBitmap(m_hBitmapAl);
// 				else if (iAxis[i] == 1)
// 					m_ctl_LimitY.SetBitmap(m_hBitmapAl);
// 				else if (iAxis[i] == 2)
// 					m_ctl_LimitZ.SetBitmap(m_hBitmapAl);
// 			}
// 			else
// 			{
// 				if (iAxis[i] == 0)
// 					m_ctl_LimitX.SetBitmap(m_hBitmapNal);
// 				else if (iAxis[i] == 1)
// 					m_ctl_LimitY.SetBitmap(m_hBitmapNal);
// 				else if (iAxis[i] == 2)
// 					m_ctl_LimitZ.SetBitmap(m_hBitmapNal);
// 			}
// 		}	
		delete[] iAxis;
		iAxis = NULL;
		delete[] iStatusLimit;
		iStatusLimit = NULL;
		delete[] iStatusHome;
		iStatusHome = NULL;
	}
	catch(...)
	{
		AfxMessageBox(_T("Error0"));
	}
	
	return 0;
}
UINT CDlgMotionControl::MoveTo( LPVOID pParam )
{
	CoInitialize(NULL);
	CDlgMotionControl* pDlg = (CDlgMotionControl*)pParam;
	pDlg->ThreadMoveTo();
	::CoUninitialize();
	return 0;
}
void CDlgMotionControl::ThreadMoveTo()
{
	if (CheckGoHoming()==1)
	{
		return ;
	}
	double dDesPos[5];
	int iAxis[5];
	iAxis[0] = COORDI_AXISX;
	iAxis[1] = COORDI_AXISY;
	iAxis[2] = COORDI_AXISZ;
	iAxis[3] = COORDI_AXISC;
	iAxis[4] = COORDI_AXISU;

	if (m_iMoveType == 1)
	{
		dDesPos[COORDI_AXISX] = ptTargetOne.X;
		dDesPos[COORDI_AXISY] = ptTargetOne.Y;
		dDesPos[COORDI_AXISZ] = ptTargetOne.Z;
		dDesPos[COORDI_AXISC] = ptTargetOne.C;
		dDesPos[COORDI_AXISU] = ptTargetOne.U;
	}
	else if (m_iMoveType == 2)
	{
		dDesPos[COORDI_AXISX] = ptTargetTwo.X;
		dDesPos[COORDI_AXISY] = ptTargetTwo.Y;
		dDesPos[COORDI_AXISZ] = ptTargetTwo.Z;
		dDesPos[COORDI_AXISC] = ptTargetTwo.C;
		dDesPos[COORDI_AXISU] = ptTargetTwo.U;
	}
	else if (m_iMoveType == 3)
	{
		dDesPos[COORDI_AXISX] = ptTargetThree.X;
		dDesPos[COORDI_AXISY] = ptTargetThree.Y;
		dDesPos[COORDI_AXISZ] = ptTargetThree.Z;
		dDesPos[COORDI_AXISC] = ptTargetThree.C;
		dDesPos[COORDI_AXISU] = ptTargetThree.U;
	}
	else
	{
		AfxMessageBox(_T("出现位置移动类型"));
		return ;
	}
	if (dDesPos[COORDI_AXISX] < -0.000001 || dDesPos[COORDI_AXISX] > 11111111)
	{
		dDesPos[COORDI_AXISX] = 0;
	}
	if (dDesPos[COORDI_AXISY] < -0.000001 || dDesPos[COORDI_AXISY] > 11111111)
	{
		dDesPos[COORDI_AXISY] = 0;
	}
	if (dDesPos[COORDI_AXISZ] < -0.000001 || dDesPos[COORDI_AXISZ] > 11111111)
	{
		dDesPos[COORDI_AXISZ] = 0;
	}
	if (dDesPos[COORDI_AXISC] < -0.000001 || dDesPos[COORDI_AXISC] > 11111111)
	{
		dDesPos[COORDI_AXISC] = 0;
	}
	if (dDesPos[COORDI_AXISU] < -0.000001 || dDesPos[COORDI_AXISU] > 11111111)
	{
		dDesPos[COORDI_AXISU] = 0;
	}
	int iSpeedMode = 1;//默认中速
	EnableWindow(FALSE);
	int iRet = 0;
	iRet =  m_MC.MoveTo(iAxis,dDesPos,5,iSpeedMode+2,2);
	Sleep(400);//稳定工作台
	EnableWindow(TRUE);
	if (iRet != 0)
	{
		AfxMessageBox(_T("到目标位置失败"));
	}
}

UINT CDlgMotionControl::CheckMCStatus( LPVOID pParam )
{
	CDlgMotionControl* pDlg = (CDlgMotionControl*)pParam;
	//ResetEvent(pDlg->m_ExiteThread);
	CoInitialize(NULL);
	try
	{
		BOOL bShowStatus = pDlg->m_bShowStatus;
		while(pDlg->m_bShowStatus)
		{			
			pDlg->ShowAxisStatus();
			Sleep(100);
		}
	}
	catch (...)
	{
		AfxMessageBox(_T("出现异常CheckMCStatus"));
	}
	CoUninitialize();
//	SetEvent(pDlg->m_ExiteThread);
	return 0;
}

void CDlgMotionControl::OnDestroy() 
{
	m_bShowStatus = FALSE;
	CReadWriteOperate RWINI;
	RWINI.WriteKey(_T("MotionNode"), _T("TargetOneX"),ptTargetOne.X);
	RWINI.WriteKey(_T("MotionNode"), _T("TargetOneY"),ptTargetOne.Y);
	RWINI.WriteKey(_T("MotionNode"), _T("TargetOneZ"),ptTargetOne.Z);
	RWINI.WriteKey(_T("MotionNode"), _T("TargetOneC"),ptTargetOne.C);
	RWINI.WriteKey(_T("MotionNode"), _T("TargetOneU"),ptTargetOne.U);

	RWINI.WriteKey(_T("MotionNode"), _T("TargetTwoX"),ptTargetTwo.X);
	RWINI.WriteKey(_T("MotionNode"), _T("TargetTwoY"),ptTargetTwo.Y);
	RWINI.WriteKey(_T("MotionNode"), _T("TargetTwoZ"),ptTargetTwo.Z);
	RWINI.WriteKey(_T("MotionNode"), _T("TargetTwoC"),ptTargetTwo.C);
	RWINI.WriteKey(_T("MotionNode"), _T("TargetTwoU"),ptTargetTwo.U);

	RWINI.WriteKey(_T("MotionNode"), _T("TargetThreeX"),ptTargetThree.X);
	RWINI.WriteKey(_T("MotionNode"), _T("TargetThreeY"),ptTargetThree.Y);
	RWINI.WriteKey(_T("MotionNode"), _T("TargetThreeZ"),ptTargetThree.Z);
	RWINI.WriteKey(_T("MotionNode"), _T("TargetThreeC"),ptTargetThree.C);
	RWINI.WriteKey(_T("MotionNode"), _T("TargetThreeU"),ptTargetThree.U);
	CDialog::OnDestroy();
}

int CDlgMotionControl::CheckGoHoming()
{
	if (m_MC.GetOriginStatus())
	{
		AfxMessageBox(_T("机器回参过程中不可操作"));
		return 1;
	}
	return 0;
}