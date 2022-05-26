
// M08ManageCtrlsDlg.h : header file
//

#pragma once


// CM08ManageCtrlsDlg dialog
class CM08ManageCtrlsDlg : public CDialogEx
{
// Construction
public:
	CM08ManageCtrlsDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M08MANAGECTRLS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonShow();
};
