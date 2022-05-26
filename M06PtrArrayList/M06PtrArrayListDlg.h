
// M06PtrArrayListDlg.h: 헤더 파일
//

#pragma once


#define	MAX_COUNT		50



// CM06PtrArrayListDlg 대화 상자
class CM06PtrArrayListDlg : public CDialogEx
{
// 생성입니다.
public:
	CM06PtrArrayListDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M06PTRARRAYLIST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 위치 저장 방법1
	//int m_posCount = 0;					// 사각형의 개수
	//POINT m_posList[MAX_COUNT];			// 사각형의 위치 저장변수

	// 위치 저장 방법2
	//CPtrArray m_posArray;					// 사각형의 위치 저장변수
	//POINT* m_posDeleted;

	// 위치 저장 방법3
	CPtrList m_posList;						// 사각형의 위치 저장변수



	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
