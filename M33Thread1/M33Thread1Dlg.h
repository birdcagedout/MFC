
// M33Thread1Dlg.h: 헤더 파일
//

#pragma once


// 쓰레드-메인쓰레드 사이의 통신을 위한 이벤트 객체(구조체) ==> 이러면 쓰레드 핸들 필요없음
struct ThreadData {
	CListBox* pListbox;
	HANDLE hThread;
	HANDLE hKillEvent;
};

// CM33Thread1Dlg 대화 상자
class CM33Thread1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CM33Thread1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M33THREAD1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	CListBox m_listboxData;


	//HANDLE m_hThread = NULL;
	ThreadData m_threadData;			// 이벤트 객체 안에 이미 핸들 들어있음



	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTest();
	afx_msg void OnDestroy();
};
