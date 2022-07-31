
// M33Thread3Dlg.h: 헤더 파일
//
// 이번에는 2~160만 범위 내의 모든 소수의 합을 구하되,
// 각 쓰레드가 범위 내에서 협업으로 소수들을 계산하게 된다.
// 이때 쓰레드는 32/64개를 사용하며, 각 쓰레드는 동시에 작업을 시작한다.
// ==> 32개 사용시: 쓰레드1 = 2, 34, 66, ..., 쓰레드2 = 3, 35, 67, ..., 쓰레드3 = 4, 36, 68, ...
// ==> 64개 사용시: 쓰레드1 = 2, 66, 130, ..., 쓰레드2 = 3, 67, 131, ..., 쓰레드3 = 4, 68, 132, ...
// 특징1. 쓰레드의 협업
// 특징2. 소수 합계를 저장할 변수를 쓰레드가 공유


#pragma once

#define THREAD_COUNT		64
#define MSG_THREAD_ENDED	27001

// 쓰레드-윈도(메인쓰레드) 사이의 통신을 위한 이벤트 구조체 ==> 이러면 쓰레드 핸들을 멤버변수로 저장할 필요없음
struct ThreadData {
	HWND hWnd;						// 쓰레드가 윈도쪽으로 메시지 보낼 수 있도록 윈도의 핸들 저장
	unsigned int lowerLimit;		// 쓰레드의 시작값
	unsigned int upperLimit;		// 쓰레드의 끝값
	unsigned int threadCount;
	unsigned long long* pSum;
	CListBox* pListbox;
	HANDLE hThread;
	HANDLE hKillEvent;
	DWORD threadID;					// 쓰레드 ID
};


// CM33Thread3Dlg 대화 상자
class CM33Thread3Dlg : public CDialogEx
{
// 생성입니다.
public:
	CM33Thread3Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M33THREAD3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	unsigned int m_upperLimit = 1600000;			// 쓰레드1 = 2, 34, 66, ..., 쓰레드2 = 3, 35, 67, ..., 쓰레드3 = 4, 36, 68, ...
	unsigned int m_threadCount = THREAD_COUNT;		// 쓰레드 개수
	unsigned long long m_sum = 0;					// 최종 소수의 합계
	unsigned long long m_startTick;						

	CListBox m_listboxData;							// 쓰레드 동작 출력창
	CListBox m_listboxThread;						// 쓰레드 목록 출력창


	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStopSelected();
	afx_msg void OnBnClickedButtonStopAll();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnMsgThreadEnded(WPARAM isKilled, LPARAM pThreadData);
};
