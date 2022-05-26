
// M12GradientFillDlg.h: 헤더 파일
//

#pragma once




// CM12GradientFillDlg 대화 상자
class CM12GradientFillDlg : public CDialogEx
{
// 생성입니다.
public:
	CM12GradientFillDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M12GRADIENTFILL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	void MyGradientFill(CDC* a_dc, int a_x1, int a_y1, int a_x2, int a_y2, COLORREF a_color1, COLORREF a_color2, int a_isVertical);

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
