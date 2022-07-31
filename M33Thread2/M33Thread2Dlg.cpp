
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
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CM33Thread2Dlg::OnBnClickedButtonStart)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_STOPONE, &CM33Thread2Dlg::OnBnClickedButtonStopSelected)
	ON_BN_CLICKED(IDC_BUTTON_STOPALL, &CM33Thread2Dlg::OnBnClickedButtonStopAll)
	ON_MESSAGE(MSG_THREAD_ENDED, &CM33Thread2Dlg::OnMsgThreadEnded)
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
	int index = 0, isKilled = 0;
	unsigned long long start = GetTickCount64();

	ThreadData* pData = (ThreadData*)lpParameter;
	long long int sum = 0;								// 최소 64bit int(표준) cf. MS에서 __int64와 같음

	// 쓰레드 작업 시작
	CString str;
	str.Format(L"[ThreadID=%08X] 작업을 시작합니다.", pData->threadID);
	index = pData->pListbox->InsertString(-1, str);
	pData->pListbox->SetCurSel(index);

	unsigned int i;
	for (i = 2; i < pData->upperLimit; i++) {

		// 쓰레드 종료 이벤트 기다림
		if (WaitForSingleObject(pData->hKillEvent, 0) == WAIT_OBJECT_0) {
			str.Format(L"====> 작업중단: 쓰레드 종료 이벤트 set");
			index = pData->pListbox->InsertString(-1, str);
			pData->pListbox->SetCurSel(index);
			isKilled = 1;
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

	str.Format(L"[ThreadID=%08X] 작업종료: %lld까지 소수 합계 = %lld (%lldms)", pData->threadID, pData->upperLimit, i, sum, (GetTickCount64() - start));
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



void CM33Thread2Dlg::OnBnClickedButtonStart()
{
	// 쓰레드 추가할 때마다 새로운 ThreadData 생성
	ThreadData* pData = new ThreadData;
	pData->hWnd = m_hWnd;
	pData->upperLimit = m_baseline;
	pData->pListbox = &m_listboxData;
	pData->hKillEvent = CreateEvent(NULL, 1, 0, NULL);

	// 쓰레드 생성 ==> CreateThread(보안속성, 스택사이즈=최대1MB(기본값0), 함수인자, 생성시바로실행/멈춤상태, 쓰레드ID)
	pData->hThread = CreateThread(NULL, 0, ThreadProc, pData, 0, &(pData->threadID));

	// 쓰레드 생성 실패한 경우
	if (pData->hThread == NULL) {
		AfxMessageBox(L"쓰레드 생성에 실패했습니다.\r\n초기화합니다.", MB_OK | MB_ICONERROR);
		CloseHandle(pData->hKillEvent);
		delete pData;
		return;
	}

	// 쓰레드 목록 리스트박스에 기록
	CString str;
	str.Format(L"[ThreadID=%08X] %6u까지 소수 합산", pData->threadID, pData->upperLimit);
	int index = m_listboxThread.InsertString(-1, str);
	m_listboxThread.SetItemDataPtr(index, pData);			// 리스트박스 item마다 들어있는 4byte DataPtr 활용(CPtrList 필요없음)

	m_baseline *= 2;
}


void CM33Thread2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	OnBnClickedButtonStopAll();
}





void CM33Thread2Dlg::OnBnClickedButtonStopSelected()
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


void CM33Thread2Dlg::OnBnClickedButtonStopAll()
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



afx_msg LRESULT CM33Thread2Dlg::OnMsgThreadEnded(WPARAM isKilled, LPARAM pThreadData)
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

	return 0;
}
