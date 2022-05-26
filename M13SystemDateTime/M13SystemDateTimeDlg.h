
// M13SystemDateTimeDlg.h: 헤더 파일
//

#pragma once
#include <afx.h>


// CM13SystemDateTimeDlg 대화 상자
class CM13SystemDateTimeDlg : public CDialogEx
{
// 생성입니다.
public:
	CM13SystemDateTimeDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M13SYSTEMDATETIME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	BOOL m_timerSet = FALSE;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGettime();
	afx_msg void OnBnClickedButtonGettimeAuto();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};
