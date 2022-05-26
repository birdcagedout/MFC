
// M16GlobalHotkeyDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M16GlobalHotkey.h"
#include "M16GlobalHotkeyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM16GlobalHotkeyDlg 대화 상자



CM16GlobalHotkeyDlg::CM16GlobalHotkeyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M16GLOBALHOTKEY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM16GlobalHotkeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM16GlobalHotkeyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HOTKEY()
END_MESSAGE_MAP()


// CM16GlobalHotkeyDlg 메시지 처리기

BOOL CM16GlobalHotkeyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	
	// 현재 윈도에 WM_HOTKEY 메시지 + 26000이라는 ID 발생시키는 핫키 등록
	// Ctrl + Shift + 0
	RegisterHotKey(m_hWnd, 26000, MOD_CONTROL | MOD_SHIFT, (int)'0');		// Ctrl + Shift + 0



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM16GlobalHotkeyDlg::OnPaint()
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
HCURSOR CM16GlobalHotkeyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// nKey1(=6) = MOD_CONTROL(=2) | MOD_SHIFT(=4)
// nKey2(=48) = (int)'0'
void CM16GlobalHotkeyDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	if (nHotKeyId == 26000) {
		if (m_show == true) {
			m_show = false;
			ShowWindow(SW_HIDE);
		}
		else {
			m_show = true;
			ShowWindow(SW_SHOW);
		}
	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}
