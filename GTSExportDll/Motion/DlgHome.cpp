// DlgHome.cpp : implementation file
//

#include "stdafx.h"
#include "DlgHome.h"
#include "MotionControl.h"
#include "DlgMotionControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHome dialog

CDlgHome::CDlgHome(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHome::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHome)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
void CDlgHome::SetMotionCtrl(CMotionControl* pMotionCtrl)
{
	m_pMotionCtrl = pMotionCtrl;
}
void CDlgHome::SetStopType(int iStopType)
{
	m_stopType = iStopType;
}

int CDlgHome::GetStopType()
{
	return m_stopType;
}
void CDlgHome::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHome)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgHome, CDialog)
	//{{AFX_MSG_MAP(CDlgHome)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHome message handlers

BOOL CDlgHome::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CenterWindow(GetParent());
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgHome::OnCancel() 
{
	// TODO: Add extra cleanup here
	m_pMotionCtrl->Stop(1);
	m_pMotionCtrl->Stop(2);
	((CDlgMotionControl*)GetParent())->GetDlgItem(IDC_BUTTON_UP)->EnableWindow();
	((CDlgMotionControl*)GetParent())->GetDlgItem(IDC_BUTTON_LEFT)->EnableWindow();
	((CDlgMotionControl*)GetParent())->GetDlgItem(IDC_BUTTON_DOWN)->EnableWindow();
	((CDlgMotionControl*)GetParent())->GetDlgItem(IDC_BUTTON_RIGHT)->EnableWindow();
	((CDlgMotionControl*)GetParent())->GetDlgItem(IDC_BUTTON_ZUP)->EnableWindow();
	((CDlgMotionControl*)GetParent())->GetDlgItem(IDC_BUTTON_ZDOWN)->EnableWindow();
	((CDlgMotionControl*)GetParent())->GetDlgItem(IDC_CHECK_ONSTEP)->EnableWindow();
	((CDlgMotionControl*)GetParent())->GetDlgItem(IDC_EDIT_MOVEONESTEP)->EnableWindow();
	((CDlgMotionControl*)GetParent())->GetDlgItem(IDC_RADIO_BIG)->EnableWindow();
	((CDlgMotionControl*)GetParent())->GetDlgItem(IDC_RADIO_MIDDLE)->EnableWindow();
	((CDlgMotionControl*)GetParent())->GetDlgItem(IDC_RADIO_MIN)->EnableWindow();
	((CDlgMotionControl*)GetParent())->GetDlgItem(IDC_BUTTON_ORIGN)->EnableWindow();
	((CDlgMotionControl*)GetParent())->GetDlgItem(IDC_BUTTON_SETCONFIG)->EnableWindow();
	try
	{
		CDialog::OnCancel();
	}
	catch (...)
	{
	}
	
}
