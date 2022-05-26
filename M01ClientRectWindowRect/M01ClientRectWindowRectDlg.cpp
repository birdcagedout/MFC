
// M01ClientRectWindowRectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M01ClientRectWindowRect.h"
#include "M01ClientRectWindowRectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM01ClientRectWindowRectDlg 대화 상자



CM01ClientRectWindowRectDlg::CM01ClientRectWindowRectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M01CLIENTRECTWINDOWRECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM01ClientRectWindowRectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM01ClientRectWindowRectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHILD, &CM01ClientRectWindowRectDlg::OnBnClickedButtonChild)
	ON_WM_MOVE()
END_MESSAGE_MAP()


// CM01ClientRectWindowRectDlg 메시지 처리기

BOOL CM01ClientRectWindowRectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	




	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM01ClientRectWindowRectDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{
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
HCURSOR CM01ClientRectWindowRectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM01ClientRectWindowRectDlg::OnBnClickedButtonChild()
{
	//===============================================================================
		// 3. ScreenToSclient(많이 사용) vs. ClientToScreen(별로 안 사용)

		// 자식 윈도의 좌표를 얻고 이동시키고 싶을 때
		// 자식 윈도의 좌표 얻기 = 윈도좌표(GetWindowRect)
		// 이동시킬 좌표 넣기 = 클라이언트좌표(GetClientRect)

	CRect r;
	GetDlgItem(IDC_BUTTON_CHILD)->GetWindowRect(r);

	ScreenToClient(r);
	
	r.left += 20;
	r.right += 20;

	GetDlgItem(IDC_BUTTON_CHILD)->MoveWindow(r);
}


// 주의 : OnInitDialog() 보다 먼저 실행된다.
// ==> 대화상자 부모 윈도가 최초 만들어지는 시점에 처음으로  WM_MOVE 들어온다.
// ==> 아직 생성되지 않은 자식 윈도가 있을 수 있으므로 오류처리 필요
void CM01ClientRectWindowRectDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);


	//===============================================================================
	// 1. 부모 윈도우

	CRect clientRect_p, windowRect_p;
	GetClientRect(clientRect_p);
	GetWindowRect(windowRect_p);

	// 출력 문자열
	CString strClient_p, strWindow_p;
	strClient_p.Format(L"left=%d, top=%d, right=%d, bottom=%d", clientRect_p.left, clientRect_p.top, clientRect_p.right, clientRect_p.bottom);
	strWindow_p.Format(L"left=%d, top=%d, right=%d, bottom=%d", windowRect_p.left, windowRect_p.top, windowRect_p.right, windowRect_p.bottom);

	// 화면 출력
	/*TextOut(dc, 50, 50, strClient_p, strClient_p.GetLength());
	TextOut(dc, 50, 100, strWindow_p, strWindow_p.GetLength());*/
	SetDlgItemText(IDC_EDIT_PARENT_WINDOWRECT, strWindow_p);
	SetDlgItemText(IDC_EDIT_PARENT_CLIENTRECT, strClient_p);


	//===============================================================================
	// 2. 자식 윈도우 ==> 최초 부모 윈도 생성시에 호출된 경우, 자식윈도 생성 전에 호출시 오류

	CWnd* pButtonOK = GetDlgItem(IDC_BUTTON_CHILD);
	if (pButtonOK == NULL) {
		return;
	}

	// GetClientRect vs. GetWindowRect
	CRect clientRect_c, windowRect_c;
	GetDlgItem(IDC_BUTTON_CHILD)->GetClientRect(clientRect_c);
	GetDlgItem(IDC_BUTTON_CHILD)->GetWindowRect(windowRect_c);

	// 출력 문자열
	CString strClient_c, strWindow_c;
	strClient_c.Format(L"left=%d, top=%d, right=%d, bottom=%d", clientRect_c.left, clientRect_c.top, clientRect_c.right, clientRect_c.bottom);
	strWindow_c.Format(L"left=%d, top=%d, right=%d, bottom=%d", windowRect_c.left, windowRect_c.top, windowRect_c.right, windowRect_c.bottom);

	// 화면 출력
	/*TextOut(dc, 50, 150, strClient_c, strClient_c.GetLength());
	TextOut(dc, 50, 200, strWindow_c, strWindow_c.GetLength());*/
	SetDlgItemText(IDC_EDIT_CHILD_WINDOWRECT, strWindow_c);
	SetDlgItemText(IDC_EDIT_CHILD_CLIENTRECT, strClient_c);


	//===============================================================================
	// 3. 자식 윈도우 ScreenToClient
	CRect s2cRect_c;
	GetDlgItem(IDC_BUTTON_CHILD)->GetWindowRect(s2cRect_c);
	ScreenToClient(s2cRect_c);
	
	CString strScreenToClient;
	strScreenToClient.Format(L"left=%d, top=%d, right=%d, bottom=%d", s2cRect_c.left, s2cRect_c.top, s2cRect_c.right, s2cRect_c.bottom);
	SetDlgItemText(IDC_EDIT_CHILD_SCREENTOCLIENT, strScreenToClient);
}
