
// M23ObjectRegionCrossDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M23ObjectRegionCross.h"
#include "M23ObjectRegionCrossDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM23ObjectRegionCrossDlg 대화 상자



CM23ObjectRegionCrossDlg::CM23ObjectRegionCrossDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M23OBJECTREGIONCROSS_DIALOG, pParent),
			m_normalPen(PS_SOLID, 1, RGB(0, 200, 255)),
			m_selectedPen(PS_SOLID, 1, RGB(255, 255, 0)),
			m_normalBrush(RGB(0, 120, 200)),
			m_selectedBrush(RGB(0, 200, 255))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM23ObjectRegionCrossDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM23ObjectRegionCrossDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CM23ObjectRegionCrossDlg 메시지 처리기

BOOL CM23ObjectRegionCrossDlg::OnInitDialog()
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

void CM23ObjectRegionCrossDlg::OnPaint()
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
		// normal 사각형 그리기
		CPen* pOldPen = dc.SelectObject(&m_normalPen);				// &를 넣는지 유무에 따라 오버로딩 된 함수가 달라서 리턴값 다름
		CBrush* pOldBrush = dc.SelectObject(&m_normalBrush);		// &가 있으면 각 객체 Pointer, &가 없으면 HGDIOBJ값(리턴값 캐스팅 필요)

		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 6; x++) {
				dc.Rectangle(50 + x * 100, 50 + y * 100, 50 + (x + 1) * 100 + 1, 50 + (y + 1) * 100 + 1);
			}
		}


		// 선택된 사각형 그리기(인덱스 2개 버전)
		/*if (m_xSelected != -1 && m_ySelected != -1) {
			dc.SelectObject(&m_selectedPen);
			dc.SelectObject(&m_selectedBrush);
			dc.Rectangle(m_xSelected * 100, m_ySelected * 100, (m_xSelected + 1) * 100 + 1, (m_ySelected + 1) * 100 + 1);
		}*/



		// 선택된 사각형 그리기(인덱스 1개 버전)
		if (m_selected != -1) {
			dc.SelectObject(&m_selectedPen);
			dc.SelectObject(&m_selectedBrush);

			int x = m_selected % 7;
			int y = m_selected / 7;

			dc.Ellipse(x * 100, y * 100, (x + 1) * 100 + 1, (y + 1) * 100 + 1);
		}

		// 펜, 브러시 원상복구
		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);

		//CDialogEx::OnPaint();
	}
}



// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM23ObjectRegionCrossDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM23ObjectRegionCrossDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 정해진 6개 외의 영역 클릭 ==> 현재 상황에서 아무것도 바뀌지 않음 (선택한 항목 취소 아님)
	if (point.x < 700 && point.y < 400) {

		// 선택된 사각형 인덱스 1개 통합
		int x = point.x / 100;
		int y = point.y / 100;

		m_selected = y * 7 + x;

		// 선택된 사각형 인덱스 2개 버전 : 이 두 값은 바뀌려면 한번에 바뀌고, 안 바뀌면 함께 안 바뀐다.
		/*m_xSelected = point.x / 100;
		m_ySelected = point.y / 100;*/
	}
	else {
		m_selected = -1;
	}
	Invalidate();		// 이번 선택된 사각형에 대하여 다시 그리기


	CDialogEx::OnLButtonDown(nFlags, point);
}
