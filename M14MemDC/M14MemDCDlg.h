
// M14MemDCDlg.h: 헤더 파일
//

#pragma once


#define MAX_COUNT		100


typedef struct _Circle {
	int x, y;
	int r;
	COLORREF c;
} Circle;



// CM14MemDCDlg 대화 상자
class CM14MemDCDlg : public CDialogEx
{
// 생성입니다.
public:
	CM14MemDCDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M14MEMDC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	int m_width = -1;		// 최초 실행시점 판별용
	int m_height = -1;		// 최초 실행시점 판별용

	Circle m_circleList[MAX_COUNT];

	CDC m_memDC;
	CBitmap m_memBMP;



	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
};
