
// M23DotEditorDlg.h: 헤더 파일
//

#pragma once


#define GRID_X_COUNT	30
#define GRID_Y_COUNT	30
#define DOT_SIZE		20


// CM23DotEditorDlg 대화 상자
class CM23DotEditorDlg : public CDialogEx
{
// 생성입니다.
public:
	CM23DotEditorDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M23DOTEDITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	COLORREF m_fgColor, m_bgColor;							// 전경색(L버튼),  배경색(R버튼)
	COLORREF m_dotColor[GRID_Y_COUNT][GRID_X_COUNT];		// 모든 dot의 color
	CPen m_gridPen;											// 그리드 테두리선(회색)

	CRect m_fgRect, m_bgRect;								// 버튼 2개의 영역




	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonFgcolor();
	afx_msg void OnBnClickedButtonBgcolor();
};
