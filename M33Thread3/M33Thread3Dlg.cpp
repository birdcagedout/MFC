
// M33Thread3Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M33Thread3.h"
#include "M33Thread3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CRITICAL_SECTION g_sumLock;



// CM33Thread3Dlg 대화 상자

CM33Thread3Dlg::CM33Thread3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M33THREAD3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM33Thread3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATA, m_listboxData);
	DDX_Control(pDX, IDC_LIST_THREAD, m_listboxThread);
}

BEGIN_MESSAGE_MAP(CM33Thread3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CM33Thread3Dlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP_SELECTED, &CM33Thread3Dlg::OnBnClickedButtonStopSelected)
	ON_BN_CLICKED(IDC_BUTTON_STOP_ALL, &CM33Thread3Dlg::OnBnClickedButtonStopAll)
	ON_WM_DESTROY()
	ON_MESSAGE(MSG_THREAD_ENDED, &CM33Thread3Dlg::OnMsgThreadEnded)
END_MESSAGE_MAP()


// CM33Thread3Dlg 메시지 처리기

BOOL CM33Thread3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	
	// 크리티컬 섹션 초기화(다쓴 후 ==> Ondestroy에서 DeleteCriticalSection(&g_sumLock) 호출로 제거)
	InitializeCriticalSection(&g_sumLock);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM33Thread3Dlg::OnPaint()
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
HCURSOR CM33Thread3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




// 쓰레드에 부하주는 연산
bool IsPrimeNumber(unsigned int num)
{
	if (num < 2) {
		return false;
	}

	for (unsigned int i = 2; i < num; i++) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}




// 쓰레드 프로시저
DWORD WINAPI ThreadProc(void* lpParameter)
{
	int index = 0, isKilled = 0;
	unsigned long long start = GetTickCount64();

	ThreadData* pData = (ThreadData*)lpParameter;
	CString str;

	// 쓰레드 작업 시작
	str.Format(L"[ThreadID=%08X] 작업을 시작합니다.", pData->threadID);
	index = pData->pListbox->InsertString(-1, str);
	pData->pListbox->SetCurSel(index);

	unsigned int i;
	for (i = pData->lowerLimit; i <= pData->upperLimit; i += pData->threadCount) {

		// 쓰레드 종료 이벤트 기다림
		if (WaitForSingleObject(pData->hKillEvent, 0) == WAIT_OBJECT_0) {
			/*str.Format(L"====> 작업중단: 쓰레드 종료 이벤트 set");
			index = pData->pListbox->InsertString(-1, str);
			pData->pListbox->SetCurSel(index);*/
			isKilled = 1;
			break;
		}

		// 크리티컬 섹션 설정(Enter~Leave)
		// 어느 쓰레드가 Enter 후에 TerminateThread로 죽으면 DeadLock에 걸린다 ==> 쓰지마라
		if (IsPrimeNumber(i) == true) {
			EnterCriticalSection(&g_sumLock);	//==================== CRITICAL SECTION ====================
			*(pData->pSum) += i;
			LeaveCriticalSection(&g_sumLock);	//==================== CRITICAL SECTION ====================
		}
	}

	str.Format(L"[ThreadID=%08X] 작업종료: %d까지 소수 합계 = %lld (%lldms)", pData->threadID, pData->upperLimit, *(pData->pSum), (GetTickCount64() - start));
	index = pData->pListbox->InsertString(-1, str);
	pData->pListbox->SetCurSel(index);

	CloseHandle(pData->hThread);

	// 혹시나 몰라서 이벤트 한번 더 체크
	if (WaitForSingleObject(pData->hKillEvent, 0) == WAIT_OBJECT_0) {
		isKilled = 1;
	}

	// 부모 윈도에 메시지(쓰레드 종료) 보냄
	::PostMessage(pData->hWnd, MSG_THREAD_ENDED, isKilled, (LPARAM)pData);

	return 0;
}





void CM33Thread3Dlg::OnBnClickedButtonStart()
{
	// 한번 누르면 끝
	CButton* btn = (CButton*)GetDlgItem(IDC_BUTTON_START);
	btn->EnableWindow(FALSE);
	
	// 두번째부터 누르면
	if (m_listboxThread.GetCount() >= 1) {
		//AfxMessageBox(L"눌렀자나~");
		return;
	}

	// 소수 합계 변수 초기화 + 시간 측정
	m_sum = 0;
	m_startTick = GetTickCount64();

	// 쓰레드32개 각각에 ThreadData 생성
	ThreadData* pData;
	for (unsigned int i = 0; i < m_threadCount; i++) {
		pData = new ThreadData;
		pData->hWnd = m_hWnd;
		pData->lowerLimit = 2 + i;
		pData->upperLimit = m_upperLimit;
		pData->threadCount = m_threadCount;
		pData->pSum = &m_sum;
		pData->pListbox = &m_listboxData;
		pData->hKillEvent = CreateEvent(NULL, 1, 0, NULL);

		// 쓰레드 생성 ==> CreateThread(보안속성, 스택사이즈=최대1MB(기본값0), 함수인자, 생성시바로실행/멈춤상태, 쓰레드ID)
		pData->hThread = CreateThread(NULL, 0, ThreadProc, pData, 0, &(pData->threadID));

		// 쓰레드 생성 실패한 경우 ==> 재시도
		if (pData->hThread == NULL) {
			AfxMessageBox(L"쓰레드 생성에 실패했습니다.\r\n재시도합니다.", MB_OK | MB_ICONERROR);
			CloseHandle(pData->hKillEvent);
			delete pData;
			i--;
			continue;
		}

		// 쓰레드 생성 알림 + 쓰레드 목록 리스트박스에 기록
		CString str;
		str.Format(L"[ThreadID=%08X] %u ~ %u까지 소수 합산", pData->threadID, pData->lowerLimit, pData->upperLimit);
		int index = m_listboxThread.InsertString(-1, str);
		m_listboxThread.SetItemDataPtr(index, pData);			// 리스트박스 item마다 들어있는 4byte DataPtr 활용(CPtrList 필요없음)
	}
}


void CM33Thread3Dlg::OnBnClickedButtonStopSelected()
{
	int index = m_listboxThread.GetCurSel();
	if (index != LB_ERR) {
		ThreadData* pData = (ThreadData*)m_listboxThread.GetItemDataPtr(index);

		if (pData->hThread != NULL) {
			SetEvent(pData->hKillEvent);

			MSG msg;
			while (pData->hThread != NULL) {
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != NULL) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			delete pData;
		}
	}
}


void CM33Thread3Dlg::OnBnClickedButtonStopAll()
{
	ThreadData* pData;
	int count = m_listboxThread.GetCount();

	for (int i = 0; i < count; i++) {
		pData = (ThreadData*)m_listboxThread.GetItemDataPtr(i);
		SetEvent(pData->hKillEvent);
	}

	CString str;
	str.Format(L"Thread %d개를 모두 종료합니다.", count);
	int index = m_listboxData.InsertString(-1, str);
	m_listboxData.SetCurSel(index);

	MSG msg;
	while (count >= 1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != NULL) {
			if (msg.message == MSG_THREAD_ENDED) {
				count--;
				msg.wParam = 0;			// 강제로 죽였지만(1) 쓰레드데이터 바로 삭제하도록 자연사(0)로 위장
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	index = m_listboxData.InsertString(-1, L"모든 쓰레드 종료되었습니다.");
	m_listboxData.SetCurSel(index);
}


void CM33Thread3Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	OnBnClickedButtonStopAll();

	DeleteCriticalSection(&g_sumLock);
}


afx_msg LRESULT CM33Thread3Dlg::OnMsgThreadEnded(WPARAM isKilled, LPARAM pThreadData)
{
	ThreadData* pData = (ThreadData*)pThreadData;
	int count = m_listboxThread.GetCount();

	for (int i = 0; i < count; i++) {
		if (m_listboxThread.GetItemDataPtr(i) == pData) {
			m_listboxThread.DeleteString(i);
			CloseHandle(pData->hKillEvent);

			// 자연사한 경우 ==> 데이터 바로 삭제
			if (isKilled == 0) {
				delete pData;
			}
			// 강제로 죽인 경우 ==> OnBnClickedButtonStopSelected() 에서 데이터 삭제하도록 유도
			else {
				pData->hThread = NULL;
			}

			break;
		}
	}

	// 마지막 쓰레드인 경우
	if (count == 1) {
		CString str;
		str.Format(L"2 ~ %u까지 소수 합계: %lld (%lldms)", m_upperLimit, m_sum, GetTickCount64() - m_startTick);
		int index = m_listboxData.InsertString(-1, str);
		m_listboxData.SetCurSel(index);

		// 버튼 살려놓기
		CWnd* btn = GetDlgItem(IDC_BUTTON_START);
		btn->EnableWindow(TRUE);
	}

	return 0;
}
