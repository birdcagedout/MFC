
// M13SystemDateTimeDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M13SystemDateTime.h"
#include "M13SystemDateTimeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM13SystemDateTimeDlg 대화 상자



CM13SystemDateTimeDlg::CM13SystemDateTimeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M13SYSTEMDATETIME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM13SystemDateTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM13SystemDateTimeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GETTIME, &CM13SystemDateTimeDlg::OnBnClickedButtonGettime)
	ON_BN_CLICKED(IDC_BUTTON_GETTIME_AUTO, &CM13SystemDateTimeDlg::OnBnClickedButtonGettimeAuto)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CM13SystemDateTimeDlg 메시지 처리기

BOOL CM13SystemDateTimeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM13SystemDateTimeDlg::OnPaint()
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
HCURSOR CM13SystemDateTimeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM13SystemDateTimeDlg::OnBnClickedButtonGettime()
{
	// C 방식
	/*
	time_t t = time(NULL);			// 64bit, 현재시간(1970년 기준 경과시간)을 초단위로 반환 (2049년에 32bit int값 overflow 예정)
	tm dt;							// year + 1900 = 현재년, mon[0] = 1월, wday[0] = SUN
	localtime_s(&dt, &t);			// localtime()=depricated, 반드시 이 호출형태 준수할 것. UTC+9

	CString str;
	str.Format(L"%04d년 %02d월 %02d일 %02d:%02d:%02d", dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday, dt.tm_hour, dt.tm_min, dt.tm_sec);
	*/

	
	// MFC 방식
	// Time String Formatting : https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strftime-wcsftime-strftime-l-wcsftime-l?f1url=%3FappId%3DDev16IDEF1%26l%3DKO-KR%26k%3Dk(TIME%252Fstrftime);k(strftime);k(DevLang-C%252B%252B);k(TargetOS-Windows)%26rd%3Dtrue&view=msvc-170
	/*
	CTime t = CTime::GetCurrentTime();					// CTime의 static 함수!! 호출방식 주의!!
	CString str, strTime;
	str.Format(L"%04d년 %02d월 %02d일 %02d:%02d:%02d", t.GetYear(), t.GetMonth(), t.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond());
	strTime = t.Format(L"%Y년 %m월 %d일 %H:%M:%S");		// Time Formatting
	
	//SetDlgItemText(IDC_EDIT_SHOW, str);
	SetDlgItemText(IDC_EDIT_SHOW, strTime);
	*/


	// SYSTEMTIME 구조체 : millisecond 단위도 가능
	SYSTEMTIME t;
	::GetLocalTime(&t);

	CString str;
	str.Format(L"%04d년 %02d월 %02d일 %02d:%02d:%02d:%03d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
	SetDlgItemText(IDC_EDIT_SHOW, str);
}


void CALLBACK MyTimerProc(HWND a_hWnd, UINT a_msgID, UINT_PTR a_timerID, DWORD a_systemTime)
{
	if (a_timerID == 1) {
		::SendMessage(a_hWnd, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_GETTIME, BN_CLICKED), 0);
		//				윈도핸들,						LOWORD=버튼ID,	HIWORD=클릭됨
	}
}


void CM13SystemDateTimeDlg::OnBnClickedButtonGettimeAuto()
{
	if (m_timerSet == FALSE) {
		//SetTimer(1, 1, NULL);		// 2번째 인자 = millisecond 단위, 3번째 인자=NULL이면 WM_TIMER 메시지로 처리
		SetTimer(1, 1, MyTimerProc);
		m_timerSet = TRUE;
		SetDlgItemText(IDC_BUTTON_GETTIME_AUTO, L"자동 끄기(ON->OFF)");
	}
	else {
		KillTimer(1);
		m_timerSet = FALSE;
		SetDlgItemText(IDC_BUTTON_GETTIME_AUTO, L"자동 켜기(OFF->ON)");
	}
}


void CM13SystemDateTimeDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {
		OnBnClickedButtonGettime();
	}
	

	CDialogEx::OnTimer(nIDEvent);
}


void CM13SystemDateTimeDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_timerSet == TRUE) {
		KillTimer(1);				// Timer는 flag성 메시지이므로 SetTimer 없이도 KillTimer 문제없음
	}
	
}
