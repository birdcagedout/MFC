
// M23ObjectRegionDlg.h: 헤더 파일
//

#pragma once


// CM23ObjectRegionDlg 대화 상자
class CM23ObjectRegionDlg : public CDialogEx
{
// 생성입니다.
public:
	CM23ObjectRegionDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M23OBJECTREGION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	CPen m_normalPen, m_selectedPen;			// 보통객체 펜, 선택된 개체 펜
	CBrush m_normalBrush, m_selectedBrush;		// 보통객체 브러시, 선택된 개체 브러시
	int m_selectedIndex = -1;					// 0 ~ 5



	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
