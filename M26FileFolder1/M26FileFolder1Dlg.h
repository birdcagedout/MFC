
// M26FileFolder1Dlg.h: 헤더 파일
//

#pragma once


// CM26FileFolder1Dlg 대화 상자
class CM26FileFolder1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CM26FileFolder1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M26FILEFOLDER1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	CListBox m_listboxLeft;				// 파일, 폴더 리스트(왼쪽)
	CListBox m_listboxRight;			// 파일, 폴더 리스트(오른쪽)

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	void FileDirectoryToListbox(CListBox* a_pListBox, CString a_strPath);
	void ChangeDirectory(bool isLeft);
	afx_msg void OnLbnDblclkListLshow();
	afx_msg void OnLbnDblclkListRshow();
};
