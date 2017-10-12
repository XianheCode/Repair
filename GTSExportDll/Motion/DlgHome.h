#if !defined(AFX_DLGHOME_H__6E4C45FA_3BCB_46B8_8403_1E7F9EFDD8BC__INCLUDED_)
#define AFX_DLGHOME_H__6E4C45FA_3BCB_46B8_8403_1E7F9EFDD8BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHome.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CDlgHome dialog
#include "../Resource.h"

class CMotionControl;
class CDlgHome : public CDialog
{
// Construction
public:
	CDlgHome(CWnd* pParent = NULL);   // standard constructor
	CMotionControl* m_pMotionCtrl;
	int m_stopType; //0-JogStop, 1-ProgramStop
	void SetMotionCtrl(CMotionControl* pMotionCtrl);
	void SetStopType(int iStopType);
	int GetStopType();
// Dialog Data
	//{{AFX_DATA(CDlgHome)
	enum { IDD = IDD_DLG_HOME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHome)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHome)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHOME_H__6E4C45FA_3BCB_46B8_8403_1E7F9EFDD8BC__INCLUDED_)
