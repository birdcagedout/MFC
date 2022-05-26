
// M23ObjectRegionDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M23ObjectRegion.h"
#include "M23ObjectRegionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM23ObjectRegionDlg 대화 상자



CM23ObjectRegionDlg::CM23ObjectRegionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M23OBJECTREGION_DIALOG, pParent),
		m_normalPen(PS_SOLID, 1, RGB(0, 200, 255)),
		m_selectedPen(PS_SOLID, 1, RGB(255, 255, 0)),
		m_normalBrush(RGB(0, 120, 200)),
		m_selectedBrush(RGB(0, 200, 255))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	// 초기화
	/*m_normalPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_selectedPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 255));

	m_normalBrush.CreateSolidBrush(RGB(0, 80, 200));
	m_selectedBrush.CreateSolidBrush(RGB(0, 200, 255));*/
}

void CM23ObjectRegionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM23ObjectRegionDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CM23ObjectRegionDlg 메시지 처리기

BOOL CM23ObjectRegionDlg::OnInitDialog()
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

void CM23ObjectRegionDlg::OnPaint()
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
		// 첫번째 Rectangle(0,0, 100, 100)으로 쓴 경우 ==> 사실은 X픽셀 : 0~99까지만 선을 그림 
		// 두번째 Rectangle(100, 0, 200, 100)이면 ==> 사실은 X픽셀 : 100~199까지만 선을 그리므로, X축 경계선 연속 2픽셀(X=99,100)로 진해진다.
		// ==> 따라서 경계선부분은 겹쳐줘야 이상하게 안 보인다.
		/*dc.Rectangle(0, 0, 100, 100);
		dc.Rectangle(100, 0, 200, 100);*/


		// 경계선을 공유하도록 설정
		/*dc.Rectangle(0, 0, 101, 100);
		dc.Rectangle(100, 0, 201, 100);
		dc.Rectangle(200, 0, 301, 100);
		dc.Rectangle(300, 0, 401, 100);
		dc.Rectangle(400, 0, 501, 100);
		dc.Rectangle(500, 0, 601, 100);*/


		// normal 사각형 그리기
		CPen* pOldPen = dc.SelectObject(&m_normalPen);				// &를 넣는지 유무에 따라 오버로딩 된 함수가 달라서 리턴값 다름
		CBrush* pOldBrush = dc.SelectObject(&m_normalBrush);		// &가 있으면 각 객체 Pointer, &가 없으면 HGDIOBJ값(리턴값 캐스팅 필요)

		for (int i = 0; i < 6; i++) {

			dc.Rectangle(i*100, 0, (i+1)*100 + 1, 100);
		}

		// 선택된 사각형 그리기
		if (m_selectedIndex != -1) {
			dc.SelectObject(&m_selectedPen);
			dc.SelectObject(&m_selectedBrush);
			dc.Rectangle(m_selectedIndex * 100, 0, (m_selectedIndex + 1) * 100 + 1, 100);
		}

		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);


		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM23ObjectRegionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM23ObjectRegionDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 정해진 6개 외의 영역 클릭 ==> 현재 상황에서 아무것도 바뀌지 않음 (선택한 항목 취소 아님)

	if (point.y < 100) {
		int xClickedIndex = point.x / 100;
		if (xClickedIndex < 6) {
			m_selectedIndex = xClickedIndex;
		}
	}
	Invalidate();

	CDialogEx::OnLButtonDown(nFlags, point);
}
