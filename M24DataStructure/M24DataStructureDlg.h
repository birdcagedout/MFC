
// M24DataStructureDlg.h: 헤더 파일
//

#pragma once


// CM24DataStructureDlg 대화 상자
class CM24DataStructureDlg : public CDialogEx
{
// 생성입니다.
public:
	CM24DataStructureDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M24DATASTRUCTURE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	CPtrList m_dataList;					// 1. CPtrList 사용

	int m_dataArray[10];					// 2. int형 배열 사용
	int m_dataArrayLen;

	int m_dataIndexedArray[10];				// 3. int형 배열의 개선버전 (index 추가)
	int m_dataIndexedArrayLen;
	int m_dataIndexedArrayIndex;


	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
