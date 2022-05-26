
// M04TransparentDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M04Transparent.h"
#include "M04TransparentDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM04TransparentDlg 대화 상자



CM04TransparentDlg::CM04TransparentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M04TRANSPARENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM04TransparentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM04TransparentDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_LAYERED_ON, &CM04TransparentDlg::OnBnClickedButtonLayeredOn)
	ON_BN_CLICKED(IDC_BUTTON_LAYERED_OFF, &CM04TransparentDlg::OnBnClickedButtonLayeredOff)
	ON_BN_CLICKED(IDC_BUTTON_ALPHA1, &CM04TransparentDlg::OnBnClickedButtonAlpha1)
	ON_BN_CLICKED(IDC_BUTTON_ALPHA2, &CM04TransparentDlg::OnBnClickedButtonAlpha2)
	ON_BN_CLICKED(IDC_BUTTON_COLORKEY, &CM04TransparentDlg::OnBnClickedButtonColorkey)
END_MESSAGE_MAP()


// CM04TransparentDlg 메시지 처리기

BOOL CM04TransparentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// 캡션넣기
	m_strTitle = L"투명한 윈도";
	SetWindowText(m_strTitle);

	// 창에 Layered 속성을 준 경우
	// Alpha값으로 전체 불투명도를 설정할 것인지, 일부 영역을 크로마키로 투명하게 할 것인지를 먼저 선택하여
	// 반드시 시작 전에 SetLayeredWindowAttributes() 호출하여야 한다.
	// ==> 안그러면 기본값이 SetLayeredWindowAttributes(0, 0, LWA_ALPHA)이 되어 창이 보이지 않는다.


	// 1. 일부 투명화 작업 : 특정 색상을 지정하고, 그 색상 영역을 투명화시킴 : 첫번째 인자, 세번째 인자만 유효함
	//                       리소스 창에 Layered(계층화) 속성 True ==> SetLayeredWindowAttributes(색깔, 0, LWA_COLORKEY)
	//SetLayeredWindowAttributes(RGB(255, 1, 7), 0, LWA_COLORKEY);		// LWA_COLORKEY일때는 투명도 무시 (주의: 0~255값으로 투명도 조절 안 됨)


	// 2. 전체 윈도 투명화 : 윈도 전체의 Alpha값을 조절하여 투명도 조절 : 두번째 인자, 세번째 인자만 유효함
	//                       리소스 창에 Layered(계층화) 속성 True ==> SetLayeredWindowAttributes(0, 알파값0~255, LWA_ALPHA)
	SetLayeredWindowAttributes(0, 150, LWA_ALPHA);



	// 현재 Layered 속성 여부를 캡션에 표시
	CString str;
	int winStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if (!(winStyle & WS_EX_LAYERED)) {
		str = m_strTitle + L"  (Layered 속성 OFF)";
	}
	else {
		str = m_strTitle + L"  (Layered 속성 ON)";
	}
	SetWindowText(str);
	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM04TransparentDlg::OnPaint()
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
		// 투명을 적용할 색상으로 네모 칠하기
		dc.FillSolidRect(10, 10, 200, 200, RGB(255, 1, 7));

		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM04TransparentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CM04TransparentDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	/*CClientDC dc(this);
//	int x = point.x;
//	int y = point.y;
//	dc.FillSolidRect(x-20, y-20, 40, 40, RGB(255, 1, 7));*/
//
//	int winStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
//	// Layered 속성이 없다면 ==> Layered 속성 ON
//	if ( !(winStyle & WS_EX_LAYERED)) {
//		::SetWindowLong(m_hWnd, GWL_EXSTYLE, winStyle | WS_EX_LAYERED);
//	}
//	//SetLayeredWindowAttributes(RGB(255, 1, 7), 0, LWA_COLORKEY);
//	SetLayeredWindowAttributes(0, 150, LWA_ALPHA);
//
//	CDialogEx::OnLButtonDown(nFlags, point);
//}


//void CM04TransparentDlg::OnRButtonDown(UINT nFlags, CPoint point)
//{
//	int winStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
//	// Layered 속성이 있다면 ==> Layered 속성 OFF
//	if (winStyle & WS_EX_LAYERED) {
//		::SetWindowLong(m_hWnd, GWL_EXSTYLE, winStyle & ~WS_EX_LAYERED);			// 특정 비트만 제외하고 싶을 때 이렇게 연산함을 기억할 것.
//	}
//
//	/*CClientDC dc(this);
//	dc.FillSolidRect(10, 10, 200, 200, RGB(255, 1, 7));*/
//
//	CDialogEx::OnRButtonDown(nFlags, point);
//}


// Layered 속성 ON
void CM04TransparentDlg::OnBnClickedButtonLayeredOn()
{
	// 현재 Layered 속성 여부를 캡션에 표시
	CString str;
	int winStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if (!(winStyle & WS_EX_LAYERED)) {
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, winStyle | WS_EX_LAYERED);			// Layered ON
		str = m_strTitle + L"  (Layered 속성 ON)";
		SetWindowText(str);
	}
}


// Layered 속성 OFF
void CM04TransparentDlg::OnBnClickedButtonLayeredOff()
{
	// 현재 Layered 속성 여부를 캡션에 표시
	CString str;
	int winStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if (winStyle & WS_EX_LAYERED) {
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, winStyle & ~WS_EX_LAYERED);		// Layered OFF
		str = m_strTitle + L"  (Layered 속성 OFF)";
		SetWindowText(str);
	}
}


// (Layered 속성이 ON인 경우에만) Alpha=50으로 전체 투명
void CM04TransparentDlg::OnBnClickedButtonAlpha1()
{
	SetLayeredWindowAttributes(0, 50, LWA_ALPHA);
}


// (Layered 속성이 ON인 경우에만) Alpha=150으로 전체 투명
void CM04TransparentDlg::OnBnClickedButtonAlpha2()
{
	SetLayeredWindowAttributes(0, 150, LWA_ALPHA);
}

// (Layered 속성이 ON인 경우에만) ColorKey로 부분 투명
void CM04TransparentDlg::OnBnClickedButtonColorkey()
{
	SetLayeredWindowAttributes(RGB(255, 1, 7), 0, LWA_COLORKEY);
}
