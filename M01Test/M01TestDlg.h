
// M01TestDlg.h: 헤더 파일
//

#pragma once


// CM01TestDlg 대화 상자
class CM01TestDlg : public CDialogEx
{
// 생성입니다.
public:
	CM01TestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M01TEST_DIALOG };
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
//	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClickedButtonSubmit();
	afx_msg void OnClickedButtonRead();
	afx_msg void OnClickedButtonWrite();
protected:
	// 에디트 컨트롤과 연결된 변수
	//CString m_editMsg;
};
