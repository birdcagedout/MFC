
// M15PatternBrushDlg.h: 헤더 파일
//

#pragma once


// CM15PatternBrushDlg 대화 상자
class CM15PatternBrushDlg : public CDialogEx
{
// 생성입니다.
public:
	CM15PatternBrushDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M15PATTERNBRUSH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	CBrush m_myBrush;			// 패턴브러시(하트)
	CBrush m_numBrush;			// 패턴브러시(숫자)

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
