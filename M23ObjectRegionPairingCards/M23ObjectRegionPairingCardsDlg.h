
// M23ObjectRegionPairingCardsDlg.h: 헤더 파일
//

#pragma once


// CM23ObjectRegionPairingCardsDlg 대화 상자
class CM23ObjectRegionPairingCardsDlg : public CDialogEx
{
// 생성입니다.
public:
	CM23ObjectRegionPairingCardsDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M23OBJECTREGIONPAIRINGCARDS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;



	CImage m_img[19];			// 카드 이미지 0=뒷면, 1~18=앞면
	int m_imgW, m_imgH;			// 카드 1장 Width, Height
	
	bool m_bShow;				// 카드 앞면 보여줄지 여부 (최초=true, 3초 후부터=false)

	bool m_bPicked1;			// 첫번째 카드를 골랐는지 여부 ==> 두번째 클릭 기다림
	bool m_bPicked2;			// 두번째 카드를 골랐는지 여부 ==> 더이상의 클릭 무시

	int m_cardIndex1;			// 첫번째 카드의 cardMap index (초기값 = -1)
	
	int m_cardMap[36];			// 동일카드 2장씩 총36장 (6 x 6), 값: 0=제거됨, 1~18=카드종류

	int m_pairLeft;				// 남은 카드쌍 (초기값 = 18)
	int m_hintLeft;

	// 프로그레스바 컨트롤과 연결된 변수
	CProgressCtrl m_progressTime;




	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonHint();


	void InitGame();
};
