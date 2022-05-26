
// M23ObjectRegionOmokDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M23ObjectRegionOmok.h"
#include "M23ObjectRegionOmokDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM23ObjectRegionOmokDlg 대화 상자



CM23ObjectRegionOmokDlg::CM23ObjectRegionOmokDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M23OBJECTREGIONOMOK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM23ObjectRegionOmokDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM23ObjectRegionOmokDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CM23ObjectRegionOmokDlg 메시지 처리기

BOOL CM23ObjectRegionOmokDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	// 바둑판 배경색
	SetBackgroundColor(RGB(244, 176, 77));

	// 격자 테두리선
	m_gridPen.CreatePen(PS_SOLID, 1, RGB(144, 80, 40));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM23ObjectRegionOmokDlg::OnPaint()
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
		CPen* pOldPen = dc.SelectObject(&m_gridPen);

		for (int i = 0; i < GRID_LEN; i++) {
			// 수직선
			dc.MoveTo(MARGIN_X + CELL_SIZE * i, MARGIN_Y + 0);
			dc.LineTo(MARGIN_X + CELL_SIZE * i, MARGIN_Y + CELL_SIZE * (GRID_LEN-1));

			//수평선
			dc.MoveTo(MARGIN_X + 0, MARGIN_Y + CELL_SIZE * i);
			dc.LineTo(MARGIN_X + CELL_SIZE * (GRID_LEN-1), MARGIN_Y + CELL_SIZE * i);
		}

		dc.SelectObject(pOldPen);
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM23ObjectRegionOmokDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM23ObjectRegionOmokDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	int x = point.x / CELL_SIZE;
	int y = point.y / CELL_SIZE;

	CClientDC dc(this);

	dc.Ellipse(point.x - 15, point.y - 15, point.x + 15, point.y + 15);

	CDialogEx::OnLButtonDown(nFlags, point);
}
