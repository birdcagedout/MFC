
// M07ModelessDialogDlg.h: 헤더 파일
//

#pragma once


#include "CNewDlg.h"			// 새로운 Modeless 대화상자1
#include "CMyView.h"			// 새로운 Modeless 대화상자2: 부모 대화상자 속에 포함된 Modeless 대화상자 (style=chlid, border=thin, visual=True)


// CM07ModelessDialogDlg 대화 상자
class CM07ModelessDialogDlg : public CDialogEx
{
// 생성입니다.
public:
	CM07ModelessDialogDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M07MODELESSDIALOG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// 새로운 대화상자 클래스로 만든 멤버변수
	CNewDlg* m_pNewDlg = NULL;							// 대화상자1
	CMyView* m_pMyView;									// 대화상자2

public:
	afx_msg void OnBnClickedButtonShowDlg();
	afx_msg void OnDestroy();
protected:
	afx_msg LRESULT On27000(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButtonSetnum();
};
