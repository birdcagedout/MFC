
// M14MemDCbyCImageDlg.h: 헤더 파일
//

#pragma once



#define MAX_COUNT		100


typedef struct _Circle {
	int x, y;
	int r;
	COLORREF c;
} Circle;


// CM14MemDCbyCImageDlg 대화 상자
class CM14MemDCbyCImageDlg : public CDialogEx
{
// 생성입니다.
public:
	CM14MemDCbyCImageDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M14MEMDCBYCIMAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;


	Circle m_circleList[MAX_COUNT];
	CImage m_img;


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
