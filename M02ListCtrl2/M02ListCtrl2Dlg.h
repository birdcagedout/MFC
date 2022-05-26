
// M02ListCtrl2Dlg.h: 헤더 파일
//

#pragma once


// CM02ListCtrl2Dlg 대화 상자
class CM02ListCtrl2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CM02ListCtrl2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M02LISTCTRL2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSub();
	afx_msg void OnLvnItemchangedListData(NMHDR* pNMHDR, LRESULT* pResult);
protected:
	
	CListCtrl m_listCtrl;					// List 컨트롤의 멤버변수
	int m_lastSelectedItemIndex;			// List 컨트롤에서 맨나중에 선택된 item의 index
public:
	afx_msg void OnBnClickedButtonMod();
};
