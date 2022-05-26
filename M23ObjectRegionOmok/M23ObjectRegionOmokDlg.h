
// M23ObjectRegionOmokDlg.h: 헤더 파일
//

#pragma once


#define GRID_LEN	19
#define CELL_SIZE	30
#define MARGIN_X	(CELL_SIZE / 2)
#define MARGIN_Y	(CELL_SIZE / 2)


// CM23ObjectRegionOmokDlg 대화 상자
class CM23ObjectRegionOmokDlg : public CDialogEx
{
// 생성입니다.
public:
	CM23ObjectRegionOmokDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M23OBJECTREGIONOMOK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	CPen m_gridPen;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
