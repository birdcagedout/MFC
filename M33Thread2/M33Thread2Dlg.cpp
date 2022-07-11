
// M33Thread2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M33Thread2.h"
#include "M33Thread2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM33Thread2Dlg 대화 상자



CM33Thread2Dlg::CM33Thread2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M33THREAD2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM33Thread2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATA, m_listboxData);
	DDX_Control(pDX, IDC_LIST_THREAD, m_listboxThread);
}

BEGIN_MESSAGE_MAP(CM33Thread2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CM33Thread2Dlg::OnBnClickedButtonTest)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_STOPONE, &CM33Thread2Dlg::OnBnClickedButtonStopone)
	ON_BN_CLICKED(IDC_BUTTON_STOPALL, &CM33Thread2Dlg::OnBnClickedButtonStopall)
END_MESSAGE_MAP()


// CM33Thread2Dlg 메시지 처리기

BOOL CM33Thread2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	// 초기화
	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM33Thread2Dlg::OnPaint()
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
HCURSOR CM33Thread2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 쓰레드에 부하주는 연산
bool IsPrimeNumber(int num)
{
	if (num < 2) {
		return false;
	}

	for (int i = 2; i < num; i++) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

// 쓰레드 프로시저
DWORD WINAPI ThreadProc(void* lpParameter)
{
	int index = 0;
	unsigned long long start = GetTickCount64();

	ThreadData* pData = (ThreadData*)lpParameter;
	long long int sum = 0;				// 최소 64bit int(표준) cf. MS에서 __int64와 같음

	CString str;
	str.Format(L"[ThreadID=%08x] 작업을 시작합니다.", pData->threadID);
	index = pData->pListbox->InsertString(-1, str);
	pData->pListbox->SetCurSel(index);


	for (int i = 2; i < 500000; i++) {

		// 이벤트 객체값이 set(signaled)되었는지를 기다리는 함수 = WaitForSingleObject
		// 반환값: WAIT_OBJECT_0 (이벤트 signaled) / WAIT_TIMEOUT (이벤트 unsignaled + 대기시간 초과)
		if (WaitForSingleObject(pData->hKillEvent, 0) == WAIT_OBJECT_0) {
			break;
		}

		if (IsPrimeNumber(i) == true) {
			sum += i;
		}

		if (i % 100000 == 0) {
			str.Format(L"====> 작업진행중: 현재 %d까지 완료", i);
			index = pData->pListbox->InsertString(-1, str);
			pData->pListbox->SetCurSel(index);
		}
	}

	str.Format(L"[%05lldms] The sum of all the prime numbers b/w 2 ~ 50,000 = %lld ", (GetTickCount64() - start), sum);
	
	index = pData->pListbox->InsertString(-1, str);
	pData->pListbox->SetCurSel(index);

	CloseHandle(pData->hThread);
	pData->hThread = NULL;						// 핸들값이 NULL이면 쓰레드 죽었음 guaranteed
	return 0;
}



void CM33Thread2Dlg::OnBnClickedButtonTest()
{
	// 쓰레드 추가할 때마다 새로운 ThreadData 생성
	ThreadData* pData = new ThreadData;
	pData->hWnd = m_hWnd;
	pData->upperLimit = m_baseline;
	pData->pListbox = &m_listboxData;
	pData->hKillEvent = CreateEvent(NULL, 1, 0, NULL);

	// 쓰레드 생성 ==> CreateThread(보안속성, 스택사이즈=최대1MB(기본값0), 함수인자, 생성시바로실행/멈춤상태, 쓰레드ID)
	pData->hThread = CreateThread(NULL, 0, ThreadProc, pData, 0, &(pData->threadID));

	// 쓰레드 정보 리스트박스에 기록
	CString str;
	str.Format(L"[ThreadID=%08x] %6u까지 소수 합산", pData->threadID, pData->upperLimit);
	int index = m_listboxThread.InsertString(-1, str);
	m_listboxThread.SetItemDataPtr(index, pData);			// 리스트박스 item마다 들어있는 4byte DataPtr 활용(CPtrList 필요없음)

	m_baseline *= 2;
}


void CM33Thread2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// 프로그램(main쓰레드) 종료시 쓰레드(worker쓰레드)를 먼저 안전하게 종료해야 함
	if (m_threadData.hThread != NULL) {

		SetEvent(m_threadData.hKillEvent);			// 이벤트 객체 = 1 (쓰레드 종료해라)

		// 쓰레드 종료까지 기다리는 방법 ==> 메시지 처리할 것 (메시지 처리하면서 쓰레드도 정상적으로 작동 후 종료되도록 유도)
		MSG msg;
		while (m_threadData.hThread != NULL) {

			// WM_QUIT이면 0, 그 외이면 nonzero 리턴
			// ==> 실제로는 WM_DESTROY가 들어온 상태에서 또다시 WM_QUIT이 들어오는 경우는 없기 때문에 else부분은 실행 안 됨
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





void CM33Thread2Dlg::OnBnClickedButtonStopone()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CM33Thread2Dlg::OnBnClickedButtonStopall()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
