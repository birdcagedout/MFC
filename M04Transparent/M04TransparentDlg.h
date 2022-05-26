
// M04TransparentDlg.h: 헤더 파일
//

#pragma once


// CM04TransparentDlg 대화 상자
class CM04TransparentDlg : public CDialogEx
{
// 생성입니다.
public:
	CM04TransparentDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M04TRANSPARENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	CString m_strTitle;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonLayeredOn();
	afx_msg void OnBnClickedButtonLayeredOff();
	afx_msg void OnBnClickedButtonAlpha1();
	afx_msg void OnBnClickedButtonAlpha2();
	afx_msg void OnBnClickedButtonColorkey();
};
