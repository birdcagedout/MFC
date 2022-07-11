
// M33Thread1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M33Thread1.h"
#include "M33Thread1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM33Thread1Dlg 대화 상자



CM33Thread1Dlg::CM33Thread1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M33THREAD1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM33Thread1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATA, m_listboxData);
}

BEGIN_MESSAGE_MAP(CM33Thread1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CM33Thread1Dlg::OnBnClickedButtonTest)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CM33Thread1Dlg 메시지 처리기

BOOL CM33Thread1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_threadData.hThread = NULL;
	m_threadData.pListbox = &m_listboxData;
	m_threadData.hKillEvent = CreateEvent(NULL, 1, 0, L"ThreadData");			// 1=수동설정, 0=초기값, 이벤트의 이름(으로 공유)


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM33Thread1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM33Thread1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


DWORD WINAPI ThreadProc(void* lpParameter)
{
	CString str;

	for (int i = 0; i < 10000; i++) {

		// 쓰레드 내부에서 이벤트 객체값을 감시 ==> 프로그램 메인 쓰레드가 종료하는 경우(이벤트 객체=1) ==> 쓰레드 종료
		// 이벤트 객체값이 set(signaled)되었는지를 기다리는 함수 = WaitForSingleObject
		// https://docs.microsoft.com/ko-kr/windows/win32/api/synchapi/nf-synchapi-waitforsingleobject?f1url=%3FappId%3DDev16IDEF1%26l%3DKO-KR%26k%3Dk(SYNCHAPI%252FWaitForSingleObject)%3Bk(WaitForSingleObject)%3Bk(DevLang-C%252B%252B)%3Bk(TargetOS-Windows)%26rd%3Dtrue
		// 반환값: WAIT_OBJECT_0 (이벤트 signaled) / WAIT_TIMEOUT (이벤트 unsignaled + 대기시간 초과)
		if (WaitForSingleObject(((ThreadData*)lpParameter)->hKillEvent, 0) == WAIT_OBJECT_0) {
			break;
		}

		str.Format(L"item %05d", i);
		int index = ((ThreadData*)lpParameter)->pListbox->InsertString(-1, str);
		((ThreadData*)lpParameter)->pListbox->SetCurSel(index);
	}
	CloseHandle(((ThreadData*)lpParameter)->hThread);
	((ThreadData*)lpParameter)->hThread = NULL;						// 핸들값이 NULL이면 쓰레드 죽었음 guaranteed
	return 0;
}


void CM33Thread1Dlg::OnBnClickedButtonTest()
{
	// 리스트박스에 대량(1만개)의 데이터 추가한다고 가정 ==> 리스트박스에 추가되는 동안 윈도 이동시 응답없음 발생
	// 싱글 쓰레드 프로그램의 문제점

	/*CString str;

	for (int i = 0; i < 10000; i++) {
		str.Format(L"item %05d", i);
		int index = m_listboxData.InsertString(-1, str);
		m_listboxData.SetCurSel(index);
	}*/

	// 쓰레드 생성 ==> CreateThread(보안속성, 스택사이즈=최대1MB(기본값0), 함수인자, 생성시바로실행/멈춤상태, 쓰레드ID)
	m_threadData.hThread = CreateThread(NULL, 0, ThreadProc, &m_threadData, 0, NULL);
}


#include <thread>

void CM33Thread1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// 프로그램(main쓰레드) 종료시 쓰레드(worker쓰레드)를 먼저 안전하게 종료해야 함
	if (m_threadData.hThread != NULL) {
		//TerminateThread(m_hThread, 0);			// 긴급하게 쓰레드를 죽여야할 경우(쓰레드 내부 객체소멸자 없이 종료되므로 권장하지 않음)

		SetEvent(m_threadData.hKillEvent);			// 이벤트 객체 = 1 (쓰레드 종료해라)

		// SetEvent 후에 쓰레드가 종료할 때까지 **반드시 대기**해야 한다. ==> 깡통 while문 돌리지 말것
		// 메인쓰레드에서 깡통 while문 돌리는 경우 ==> 메시지 처리가 안 되므로 ==> 쓰레드 내부에서 WaitForSingleObject가 먹히지 않는다.
		/*while (m_threadData.hThread != NULL) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}*/


		// 쓰레드 종료까지 기다리는 방법 ==> 메시지 처리할 것 (메시지 처리하면서 쓰레드도 정상적으로 작동 후 종료되도록 유도)
		MSG msg;
		while (m_threadData.hThread != NULL) {

			// WM_QUIT이면 0, 그 외이면 nonzero 리턴
			if (GetMessage(&msg, NULL, 0, 0) != 0) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				break;
			}
		}
	}
}
