﻿
// M33Thread2Dlg.h: 헤더 파일
//

#pragma once


// 쓰레드-메인쓰레드 사이의 통신을 위한 이벤트 객체(구조체) ==> 이러면 쓰레드 핸들 필요없음
struct ThreadData {
	HWND hWnd;						// 쓰레드가 윈도쪽으로 메시지 보낼 수 있도록 윈도의 핸들 저장
	unsigned int upperLimit;		// 쓰레드마다 달라지는 상한범위
	CListBox* pListbox;
	HANDLE hThread;
	HANDLE hKillEvent;
	DWORD threadID;					// 쓰레드 ID
};



// CM33Thread2Dlg 대화 상자
class CM33Thread2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CM33Thread2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M33THREAD2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	CListBox m_listboxData;
	CListBox m_listboxThread;

	ThreadData m_threadData;

	unsigned int m_baseline = 200000;				// 쓰레드마다 upperLimit = 20만, 40만, 60만, ...


	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTest();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonStopone();
	afx_msg void OnBnClickedButtonStopall();
};