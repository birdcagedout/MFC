
// M29TransparentWindow2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M29TransparentWindow2.h"
#include "M29TransparentWindow2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM29TransparentWindow2Dlg 대화 상자



CM29TransparentWindow2Dlg::CM29TransparentWindow2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M29TRANSPARENTWINDOW2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM29TransparentWindow2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM29TransparentWindow2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CM29TransparentWindow2Dlg 메시지 처리기

BOOL CM29TransparentWindow2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	

	// 리소스 속성 먼저 할 것
	// 테두리=None, 제목표시줄=False
	// 계층화(Layered)=True, 맨위(Topmost)=True

	// 원모양 윈도
	CRgn rgn;
	rgn.CreateEllipticRgn(0, 0, 200, 200);
	SetWindowRgn(rgn, TRUE);

	// 내부영역=파란색
	SetBackgroundColor(RGB(0, 150, 255));

	// 마우스 클릭된 상태
	m_isClicked = false;

	//SetLayeredWindowAttributes(0, 80, LWA_ALPHA);		// 현재 윈도를 80불투명도로 알파 적용 (LWA_ALPHA ==> 두번째 인자만 적용, 0일수록 투명)
	SetLayeredWindowAttributes(RGB(255, 0, 0), 80, LWA_ALPHA | LWA_COLORKEY);		// 80불투명도로 알파 적용 + 빨간색에 컬러키(완전 투명) 적용



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM29TransparentWindow2Dlg::OnPaint()
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
		// 내부에 빨간 원 그리기 ==> 컬러키 적용하면 투명해짐
		dc.SelectStockObject(DC_BRUSH);
		dc.SetDCBrushColor(RGB(255, 0, 0));
		dc.SelectStockObject(NULL_PEN);
		dc.Ellipse(30, 30, 170, 170);


		// 중심에 십자 조준선
		CPen gridPen(PS_DOT, 1, RGB(0, 0, 128));
		CPen* pOldPen = dc.SelectObject(&gridPen);
		dc.SetBkMode(TRANSPARENT);

		// 상하
		dc.MoveTo(100, 30);
		dc.LineTo(100, 170);

		// 좌우
		dc.MoveTo(30, 100);
		dc.LineTo(170, 100);


		dc.SelectObject(pOldPen);
		gridPen.DeleteObject();
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM29TransparentWindow2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM29TransparentWindow2Dlg::OnLButtonDown(UINT nFlags, CPoint point)			// point값은 클라이언트 영역 기준 좌표이므로 쓸 수 없다.
{
	if (m_isClicked == false) {
		m_isClicked = true;

		// 화면 전체에서의 마우스 커서 위치 얻어오기
		GetCursorPos(&m_prevPoint);

		// 마우스 메시지 계속 받기
		SetCapture();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CM29TransparentWindow2Dlg::OnMouseMove(UINT nFlags, CPoint point)				// point값은 클라이언트 영역 기준 좌표이므로 쓸 수 없다.
{
	if (m_isClicked == true) {

		// 화면에서 윈도 영역 얻어오기
		CRect r;
		GetWindowRect(r);

		// 현재 마우스커서 위치 얻어오기
		CPoint currentPoint, offsetPoint;
		GetCursorPos(&currentPoint);

		// 이전 위치와의 변위 차이
		offsetPoint = currentPoint - m_prevPoint;

		// 영역에 반영
		r.OffsetRect(offsetPoint);

		// 윈도 위치 변경 : 화면 전체에서의 좌표임에 주의
		SetWindowPos(NULL, r.left, r.top, r.Width(), r.Height(), SWP_NOSIZE);

		// 현재 위치 update
		m_prevPoint = currentPoint;
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CM29TransparentWindow2Dlg::OnLButtonUp(UINT nFlags, CPoint point)				// point값은 클라이언트 영역 기준 좌표이므로 쓸 수 없다.
{
	if (m_isClicked == true) {
		ReleaseCapture();
		m_isClicked = false;
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}
