
// M32KeyHookMonitorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M32KeyHookMonitor.h"
#include "M32KeyHookMonitorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM32KeyHookMonitorDlg 대화 상자



CM32KeyHookMonitorDlg::CM32KeyHookMonitorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M32KEYHOOKMONITOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM32KeyHookMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EVENT, m_listboxEvent);
	DDX_Control(pDX, IDC_EDIT_SHOW, m_editShow);
}

BEGIN_MESSAGE_MAP(CM32KeyHookMonitorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_MESSAGE(27001, &CM32KeyHookMonitorDlg::OnKeyHook)
	ON_BN_CLICKED(IDOK, &CM32KeyHookMonitorDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CM32KeyHookMonitorDlg 메시지 처리기

BOOL CM32KeyHookMonitorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.



	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_hKeyHookDLL = ::LoadLibrary(L"M32KeyHookDLL32.dll");													// DLL 로드
	void (*fpInstall)(HWND) = (void(*)(HWND))GetProcAddress(m_hKeyHookDLL, "InstallKeyHook");		// DLL에서 Install함수 주소 찾아옴
	if (fpInstall != NULL) {
		(*fpInstall)(m_hWnd);					// 실제 DLL에 있는 함수를 call
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM32KeyHookMonitorDlg::OnPaint()
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
HCURSOR CM32KeyHookMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


afx_msg LRESULT CM32KeyHookMonitorDlg::OnKeyHook(WPARAM wParam, LPARAM lParam)			// 27001 메시지
{
	CString str;
	if (lParam & 0x80000000) {
		str.Format(L"[Key UP] %08X(key=%c) %08X", wParam, wParam, lParam);
		m_editShow.PostMessageW(WM_KEYUP, wParam, lParam);
	}
	else {
		str.Format(L"[Key DN] %08X(key=%c) %08X", wParam, wParam, lParam);
		m_editShow.PostMessageW(WM_KEYDOWN, wParam, lParam);
	}
	/*
	#define WM_KEYDOWN                      0x0100
	#define WM_KEYUP                        0x0101
	*/
	
	int index = m_listboxEvent.InsertString(-1, str);
	m_listboxEvent.SetCurSel(index);

	return 0;
}


void CM32KeyHookMonitorDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	void (*fpUninstall)() = (void(*)())GetProcAddress(m_hKeyHookDLL, "UninstallKeyHook");
	if (fpUninstall != NULL) {
		(*fpUninstall)();
	 }
	::FreeLibrary(m_hKeyHookDLL);
}


void CM32KeyHookMonitorDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}
