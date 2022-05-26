
// M11CImageDlg.h: 헤더 파일
//

#pragma once


// CM11CImageDlg 대화 상자
class CM11CImageDlg : public CDialogEx
{
// 생성입니다.
public:
	CM11CImageDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M11CIMAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	CImage m_img;					// 이미지
	CRect m_imageRect;				// 이미지 영역
	CRect m_mouseRect;				// 마우스로 진하게 보여줄 영역
	CRect m_magRect;				// 확대해서 보여줄 영역
	CRect m_clientRect;				// 클라이언트 영역

	CDC m_memDC;
	CBitmap m_memBMP;

	bool m_mouseOver = false;


	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};
