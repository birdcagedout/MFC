
// M32KeyHookMonitorDlg.h: 헤더 파일
//

#pragma once


// CM32KeyHookMonitorDlg 대화 상자
class CM32KeyHookMonitorDlg : public CDialogEx
{
// 생성입니다.
public:
	CM32KeyHookMonitorDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M32KEYHOOKMONITOR_DIALOG };
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

protected:
	CListBox m_listboxEvent;						// 이벤트 출력하는 리스트박스
	CEdit m_editShow;								// 키 메시지 그대로 출력
	HINSTANCE m_hKeyHookDLL;						// dll 인스턴스

public:
	afx_msg void OnDestroy();
protected:
	afx_msg LRESULT OnKeyHook(WPARAM wParam, LPARAM lParam);

	
public:
	afx_msg void OnBnClickedOk();
};
