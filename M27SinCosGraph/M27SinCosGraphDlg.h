
// M27SinCosGraphDlg.h: 헤더 파일
//

#pragma once


#include <math.h>
#define PI	3.14159265358979323846	


// CM27SinCosGraphDlg 대화 상자
class CM27SinCosGraphDlg : public CDialogEx
{
// 생성입니다.
public:
	CM27SinCosGraphDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M27SINCOSGRAPH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	CRect m_rect;						// 클라이언트 영역
	CPoint m_centerPoint;				// 클라이언트 영역의 중심점

	CPen m_coordPen, m_textPen, m_graphSinPen, m_graphCosPen;		// 좌표축 펜, sin 펜, cos 펜

	int m_upperBound;					// 타이머 호출될 때마다 설정할 upperBound

	CImage m_img;						// 메모리DC로 사용할 이미지
	CDC m_dc;							// 메모리DC

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};
