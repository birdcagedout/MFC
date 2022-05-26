
// M22FileDialogImageDlg.h: 헤더 파일
//

#pragma once


// CM22FileDialogImageDlg 대화 상자
class CM22FileDialogImageDlg : public CDialogEx
{
// 생성입니다.
public:
	CM22FileDialogImageDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M22FILEDIALOGIMAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	bool m_newImg;			// 새로운 이미지 선택되었는지
	CImage m_img;			// 이미지
	CRect m_rect;			// 클라이언트 영역

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
};
