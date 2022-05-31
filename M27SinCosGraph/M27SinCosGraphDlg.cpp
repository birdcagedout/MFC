
// M27SinCosGraphDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M27SinCosGraph.h"
#include "M27SinCosGraphDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM27SinCosGraphDlg 대화 상자



CM27SinCosGraphDlg::CM27SinCosGraphDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M27SINCOSGRAPH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM27SinCosGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM27SinCosGraphDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CM27SinCosGraphDlg 메시지 처리기

BOOL CM27SinCosGraphDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// 초기화
	GetClientRect(m_rect);						// LT=(0, 0), RB=(700, 375)
	m_centerPoint = m_rect.CenterPoint();		// x=350, y=187

	SetBackgroundColor(RGB(0, 0, 0));

	m_coordPen.CreatePen(PS_DOT, 1, RGB(168, 168, 168));
	m_textPen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	m_graphSinPen.CreatePen(PS_SOLID, 2, RGB(0, 200, 255));
	m_graphCosPen.CreatePen(PS_SOLID, 2, RGB(255, 100, 0));


	m_upperBound = 1;
	SetTimer(1, 10, NULL);

	m_img.Create(m_rect.Width(), m_rect.Height(), 32, 0);
	m_dc.Attach(m_img.GetDC());

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM27SinCosGraphDlg::OnPaint()
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

		// 먼저 싹다 지우기
		m_dc.FillSolidRect(m_rect, RGB(0, 0, 0));

		// 좌표축용 펜
		CPen* pOldPen = m_dc.SelectObject(&m_coordPen);
		m_dc.SetBkMode(TRANSPARENT);						// 점선 사이사이의 배경색 없애기(기본=흰색)

		// y축
		m_dc.MoveTo(m_centerPoint.x, 0);
		m_dc.LineTo(m_centerPoint.x, m_rect.bottom);

		// x축
		m_dc.MoveTo(0, m_centerPoint.y);
		m_dc.LineTo(m_rect.right, m_centerPoint.y);


		// sin 펜
		m_dc.SelectObject(&m_graphSinPen);

		// sine : 클라이언트 영역의 x좌표를 degree로 간주
		int x = 0, y = 0;												// x좌표(0~700), y좌표(0~375)
		double radian;												// x좌표(0~700) ==> 중심축 기준 좌표(-350~+350) ==> 라디안 변환(-6.1~+6.1)=(-1.9pi~+1.9pi)

		for (x = 0; x < m_upperBound /*m_rect.right*/; x++) {
			radian = (x - m_centerPoint.x) * PI / 180;
			y = (int)(-100 * sin(radian)) + m_centerPoint.y;		// y값을 100배 크게 + y축 하방 이동

			if (x == 0) {
				m_dc.MoveTo(x, y);
			}
			else {
				m_dc.LineTo(x, y);
			}
		}
		m_dc.Ellipse(x - 15, y - 15, x + 15, y + 15);		// 맨끝점에 원
		m_dc.SelectObject(&m_textPen);
		m_dc.TextOutW(x - 10, y - 9, L"sin");


		// cos 펜
		m_dc.SelectObject(&m_graphCosPen);

		for (x = 0; x < m_upperBound /*m_rect.right*/; x++) {
			radian = (x - m_centerPoint.x) * PI / 180;
			y = (int)(-100 * cos(radian)) + m_centerPoint.y;		// y값을 100배 크게 + y축 하방 이동

			if (x == 0) {
				m_dc.MoveTo(x, y);
			}
			else {
				m_dc.LineTo(x, y);
			}
		}
		m_dc.Ellipse(x - 15, y - 15, x + 15, y + 15);		// 맨끝점에 원
		m_dc.SelectObject(&m_textPen);
		m_dc.TextOutW(x - 10, y - 9, L"cos");

		m_dc.SelectObject(pOldPen);

		m_img.Draw(dc, 0, 0);

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM27SinCosGraphDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM27SinCosGraphDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {
		if (m_upperBound < m_rect.right) {
			m_upperBound++;
		}
		else {
			m_upperBound = 1;
		}
		Invalidate(FALSE);
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}


void CM27SinCosGraphDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(1);
	m_coordPen.DeleteObject();
	m_graphSinPen.DeleteObject();
	m_graphCosPen.DeleteObject();

	m_dc.Detach();
	m_img.ReleaseDC();
}
