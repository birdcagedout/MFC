
// M27SineGraphDlg.h: 헤더 파일
//

#pragma once


#include <math.h>
#define PI	3.14159265358979323846	

// CM27SineGraphDlg 대화 상자
class CM27SineGraphDlg : public CDialogEx
{
// 생성입니다.
public:
	CM27SineGraphDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M27SINEGRAPH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	CRect m_rect;
	CPoint m_centerPoint;


	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
