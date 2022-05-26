
// M09NotepadDlg.h : header file
//

#pragma once


// CM09NotepadDlg dialog
class CM09NotepadDlg : public CDialogEx
{
// Construction
public:
	CM09NotepadDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M09NOTEPAD_DIALOG };
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
	afx_msg void OnBnClickedButtonOpenfile();
	afx_msg void OnBnClickedButtonSavefile();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
