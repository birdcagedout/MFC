
// M03MoveRectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M03MoveRect.h"
#include "M03MoveRectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM03MoveRectDlg 대화 상자



CM03MoveRectDlg::CM03MoveRectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M03MOVERECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// rect 멤버변수 초기화
	m_rect.SetRect(10, 10, 100, 100);

	// 클릭된 상태인지를 저장
	m_isClicked = FALSE;
}

void CM03MoveRectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM03MoveRectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CM03MoveRectDlg 메시지 처리기

BOOL CM03MoveRectDlg::OnInitDialog()
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

void CM03MoveRectDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	// 최소화된 상태
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
		dc.Rectangle(m_rect);
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM03MoveRectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM03MoveRectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	int x = point.x;
	int y = point.y;

	//if (x >= m_rect.left && x <= m_rect.right && y >= m_rect.top && y <= m_rect.bottom) {
	if(m_rect.PtInRect(point)) {
		m_isClicked = TRUE;
		m_prevPoint = point;

		// 마우스가 클라이언트 영역을 벗어나도 메시지를 받는다.
		SetCapture();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CM03MoveRectDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_isClicked == TRUE) {
		m_isClicked = FALSE;
		
		// 마우스 메시지 계속 받는 것을 중지
		ReleaseCapture();
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CM03MoveRectDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_isClicked == TRUE) {
		CPoint dispPoint = point - m_prevPoint;
		m_rect += dispPoint;				// 아래와 같이 4줄 쓸 필요없이 연산자 오버로딩 사용
		/*m_rect.left += dispPoint.x;
		m_rect.right += dispPoint.x;
		m_rect.top += dispPoint.y;
		m_rect.bottom += dispPoint.y;*/
		m_prevPoint = point;

		Invalidate();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
