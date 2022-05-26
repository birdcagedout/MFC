
// M20FindWindowExDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M20FindWindowEx.h"
#include "M20FindWindowExDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM20FindWindowExDlg 대화 상자



CM20FindWindowExDlg::CM20FindWindowExDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M20FINDWINDOWEX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM20FindWindowExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM20FindWindowExDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CM20FindWindowExDlg::OnBnClickedButtonFind)
END_MESSAGE_MAP()


// CM20FindWindowExDlg 메시지 처리기

BOOL CM20FindWindowExDlg::OnInitDialog()
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

void CM20FindWindowExDlg::OnPaint()
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
HCURSOR CM20FindWindowExDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// FindWindowEx(최상위윈도핸들, 찾는기준윈도핸들(다음부터찾기), 찾는대상클래스이름(컨트롤은 이름고정, 대소문자 무관), 윈도의문자열)
// 1. API: HWND(핸들) = ::FindWindowEx();
// 2. MFC: CWnd*(윈도) = FindWindowEx();


void CM20FindWindowExDlg::OnBnClickedButtonFind()
{
	// 1. API 방식 : 가장 간단
	/*
	HWND hWndFound = NULL;
	while (hWndFound = ::FindWindowEx(m_hWnd, hWndFound, L"EDIT", NULL)) {
		::SetWindowText(hWndFound, L"Hello~");
	}
	*/


	// 2. MFC 방식 : FindWindowEx() 2번 써야해서 번잡
	/*
	CWnd* pWndFound = FindWindowEx(m_hWnd, NULL, L"EDIT", NULL);
	while (pWndFound != NULL) {
		pWndFound->SetWindowText(L"Hello~");
		pWndFound = FindWindowEx(m_hWnd, pWndFound->m_hWnd, L"EDIT", NULL);
	}
	*/


	// 2-1. MFC기준 + API : FindWindowEX() 1번만 쓰도록 개선
	/*
	HWND hWndFound = NULL;
	CWnd* pWndFound;
	while (pWndFound = FindWindowEx(m_hWnd, hWndFound, L"BUTTON", NULL)) {
		pWndFound->SetWindowTextW(L"Hello~");
		hWndFound = pWndFound->m_hWnd;
	}
	*/


	// 3. API기준 + MFC : FromHandle()로 CWnd 임시객체(포인터) 만들어 사용 : 멀티쓰레드 환경에서 위험, 비추천
	/*
	HWND hWndFound = NULL;
	while (hWndFound = ::FindWindowEx(m_hWnd, hWndFound, L"EDIT", NULL)) {
		CWnd* pWndFound = CWnd::FromHandle(hWndFound);
		pWndFound->SetWindowTextW(L"Hello~");
	}
	*/

	// 4. API기준 + MFC : CWnd 더미객체에 Attach/Detach 사용
	HWND hWndFound = NULL;
	CWnd WndFound;
	while (hWndFound = ::FindWindowEx(m_hWnd, hWndFound, L"BUTTON", NULL)) {
		WndFound.Attach(hWndFound);
		WndFound.SetWindowText(L"Hello~");
		WndFound.Detach();
	}

}
