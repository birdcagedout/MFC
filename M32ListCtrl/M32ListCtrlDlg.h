
// M32ListCtrlDlg.h: 헤더 파일
//

#pragma once


// CM32ListCtrlDlg 대화 상자
class CM32ListCtrlDlg : public CDialogEx
{
// 생성입니다.
public:
	CM32ListCtrlDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M32LISTCTRL_DIALOG };
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
	// // 리스트 컨트롤에 연결된 변수
	CListCtrl m_dataList;
public:
	afx_msg void OnBnClickedButtonAdd();
};
