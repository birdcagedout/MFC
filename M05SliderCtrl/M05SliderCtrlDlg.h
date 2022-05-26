
// M05SliderCtrlDlg.h : header file
//

#pragma once


// CM05SliderCtrlDlg dialog
class CM05SliderCtrlDlg : public CDialogEx
{
// Construction
public:
	CM05SliderCtrlDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M05SLIDERCTRL_DIALOG };
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
	// IDC_SLIDER_1
	CSliderCtrl m_mySlider;
public:
	// Listbox ¸â¹öº¯¼ö
	CListBox m_listShow;
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
