
// M10CalendarCtrlDlg.h : header file
//

#pragma once


// CM10CalendarCtrlDlg dialog
class CM10CalendarCtrlDlg : public CDialogEx
{
// Construction
public:
	CM10CalendarCtrlDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M10CALENDARCTRL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	
	CMonthCalCtrl m_calendar;			// IDC_MONTHCALENDAR1의 멤버변수
	CFont m_font;						// 달력 내부 폰트

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonSave();
};
