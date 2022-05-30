
// M27SineGraphDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M27SineGraph.h"
#include "M27SineGraphDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM27SineGraphDlg 대화 상자



CM27SineGraphDlg::CM27SineGraphDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M27SINEGRAPH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM27SineGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM27SineGraphDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CM27SineGraphDlg 메시지 처리기

BOOL CM27SineGraphDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	
	// 초기화
	GetClientRect(m_rect);						// LT=(0, 0), RB=(560, 375)
	m_centerPoint = m_rect.CenterPoint();		// x=280, y=187


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM27SineGraphDlg::OnPaint()
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
		// y축
		dc.MoveTo(m_centerPoint.x, 0);
		dc.LineTo(m_centerPoint.x, m_rect.bottom);

		// x축
		dc.MoveTo(0, m_centerPoint.y);
		dc.LineTo(m_rect.right, m_centerPoint.y);

		// sine : 그래프를 크게 그리기 위해 x(0~560)값을 degree로 간주
		int x, y;		// 실제 클라이언트 영역의 x좌표(0~560), y좌표(0~375)
		double radian;
		for (int x = 0; x < m_rect.right; x++) {
			radian = (x - m_centerPoint.x) * PI / 180;
			y = (int)(-100 * sin(radian)) + m_centerPoint.y;		// y값을 100배 크게 + y축 하방 이동

			if (x == 0) {
				dc.MoveTo(x, y);
			}
			else {
				dc.LineTo(x, y);
			}
		}

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM27SineGraphDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

