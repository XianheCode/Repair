#pragma once

#include "../resource.h"

// CDlgSetTargetCoord dialog
class CMotionInterface;
class CDlgSetTargetCoord : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetTargetCoord)

public:
	CDlgSetTargetCoord(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSetTargetCoord();

// Dialog Data
	enum { IDD = IDD_DLG_SetTargetCoor };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	double m_dSetPosX;
	double m_dSetPosY;
	double m_dSetPosZ;
	double m_dSetPosC;
	double m_dSetPosU;
	double m_dSetPosW;
	double m_dSetPosA;
	double m_dSetPosB;
	CMotionInterface* pMC;
	afx_msg void OnBnClickedBtnUpdatecurpos();
};
