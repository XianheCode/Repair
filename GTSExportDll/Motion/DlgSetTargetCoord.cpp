// DlgSetTargetCoord.cpp : implementation file
//

#include "stdafx.h"
#include "DlgSetTargetCoord.h"
#include "afxdialogex.h"
#include "DlgMotionControl.h"


// CDlgSetTargetCoord dialog

IMPLEMENT_DYNAMIC(CDlgSetTargetCoord, CDialogEx)

CDlgSetTargetCoord::CDlgSetTargetCoord(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSetTargetCoord::IDD, pParent)
	, m_dSetPosX(0)
	, m_dSetPosY(0)
	, m_dSetPosZ(0)
	, m_dSetPosC(0)
	, m_dSetPosU(0)
	, m_dSetPosW(0)
	, m_dSetPosA(0)
	, m_dSetPosB(0)
{
	pMC = NULL;
}

CDlgSetTargetCoord::~CDlgSetTargetCoord()
{
}

void CDlgSetTargetCoord::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_POSX, m_dSetPosX);
	DDV_MinMaxDouble(pDX, m_dSetPosX, -100000000, 100000000);
	DDX_Text(pDX, IDC_EDIT_POSY, m_dSetPosY);
	DDV_MinMaxDouble(pDX, m_dSetPosY, -100000000, 100000000);
	DDX_Text(pDX, IDC_EDIT_POSZ, m_dSetPosZ);
	DDV_MinMaxDouble(pDX, m_dSetPosZ, -100000000, 100000000);
	DDX_Text(pDX, IDC_EDIT_POSC, m_dSetPosC);
	DDV_MinMaxDouble(pDX, m_dSetPosC, -100000000, 100000000);
	DDX_Text(pDX, IDC_EDIT_POSU, m_dSetPosU);
	DDV_MinMaxDouble(pDX, m_dSetPosU, -100000000, 100000000);
	DDX_Text(pDX, IDC_EDIT_POSW, m_dSetPosW);
	DDV_MinMaxDouble(pDX, m_dSetPosW, -100000000, 100000000);
	DDX_Text(pDX, IDC_EDIT_POSA, m_dSetPosA);
	DDV_MinMaxDouble(pDX, m_dSetPosA, -100000000, 100000000);
	DDX_Text(pDX, IDC_EDIT_POSB, m_dSetPosB);
	DDV_MinMaxDouble(pDX, m_dSetPosB, -100000000, 100000000);
}


BEGIN_MESSAGE_MAP(CDlgSetTargetCoord, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgSetTargetCoord::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_UpdateCurPos, &CDlgSetTargetCoord::OnBnClickedBtnUpdatecurpos)
END_MESSAGE_MAP()


// CDlgSetTargetCoord message handlers


void CDlgSetTargetCoord::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (UpdateData())
	{
	}
	CDialogEx::OnOK();
}


BOOL CDlgSetTargetCoord::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	if (m_dSetPosX < -0.000001 || m_dSetPosX > 11111111)
	{
		m_dSetPosX = 0;
	}
	else if (m_dSetPosY < -0.000001 || m_dSetPosY > 11111111)
	{
		m_dSetPosY = 0;
	}
	else if (m_dSetPosZ < -0.000001 || m_dSetPosZ > 11111111)
	{
		m_dSetPosZ = 0;
	}
	else if (m_dSetPosC < -0.000001 || m_dSetPosC > 11111111)
	{
		m_dSetPosC = 0;
	}
	else if (m_dSetPosU < -0.000001 || m_dSetPosU > 11111111)
	{
		m_dSetPosU = 0;
	}
	else if (m_dSetPosW < -0.000001 || m_dSetPosW > 11111111)
	{
		m_dSetPosW = 0;
	}
	else if (m_dSetPosA < -0.000001 || m_dSetPosA > 11111111)
	{
		m_dSetPosA = 0;
	}
	else if (m_dSetPosB < -0.000001 || m_dSetPosB > 11111111)
	{
		m_dSetPosB = 0;
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgSetTargetCoord::OnBnClickedBtnUpdatecurpos()
{
	// TODO: Add your control notification handler code here
	if (pMC != NULL)
	{
		CString s;
		pMC->GetPosCur(COORDI_AXISX,&m_dSetPosX);
		s.Format(_T("\n%.4f"), m_dSetPosX);
		SetDlgItemText(IDC_EDIT_POSX,s);

		pMC->GetPosCur(COORDI_AXISY,&m_dSetPosY);
		s.Format(_T("\n%.4f"), m_dSetPosY);
		SetDlgItemText(IDC_EDIT_POSY,s);

		pMC->GetPosCur(COORDI_AXISZ,&m_dSetPosZ);
		if (m_dSetPosZ < -0.000001 || m_dSetPosZ > 11111111)
		{
			m_dSetPosZ = 0;
		}
		s.Format(_T("\n%.4f"), m_dSetPosZ);
		SetDlgItemText(IDC_EDIT_POSZ,s);

		pMC->GetPosCur(COORDI_AXISC,&m_dSetPosC);
		s.Format(_T("\n%.4f"), m_dSetPosC);
		SetDlgItemText(IDC_EDIT_POSC,s);

		pMC->GetPosCur(COORDI_AXISU,&m_dSetPosU);
		s.Format(_T("\n%.4f"), m_dSetPosU);
		SetDlgItemText(IDC_EDIT_POSU,s);

		pMC->GetPosCur(COORDI_AXISW,&m_dSetPosW);
		s.Format(_T("\n%.4f"), m_dSetPosW);
		SetDlgItemText(IDC_EDIT_POSW,s);

		pMC->GetPosCur(COORDI_AXISA,&m_dSetPosA);
		s.Format(_T("\n%.4f"), m_dSetPosA);
		SetDlgItemText(IDC_EDIT_POSA,s);

		pMC->GetPosCur(COORDI_AXISB,&m_dSetPosB);
		s.Format(_T("\n%.4f"), m_dSetPosB);
		SetDlgItemText(IDC_EDIT_POSB,s);
	}
	else
	{
		AfxMessageBox(_T("更新目标位置数据传输出错"));
	}
}
