
// M14Timer1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M14Timer1.h"
#include "M14Timer1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM14Timer1Dlg 대화 상자



CM14Timer1Dlg::CM14Timer1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M14TIMER1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM14Timer1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM14Timer1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CM14Timer1Dlg 메시지 처리기

BOOL CM14Timer1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.



	// 초기화
	CRect r;
	GetClientRect(r);

	m_width = r.Width();
	m_height = r.Height();

	
	// 메모리DC 만들기 (3단계 반드시 기억!!)
	CClientDC dc(this);
	m_memDC.CreateCompatibleDC(&dc);				// 기존 물리DC와 호환되는 메모리DC 생성(width=1, height=1)
	m_memBMP.CreateCompatibleBitmap(&dc, m_width, m_height);		// 첫번째 인자에 절대 메모리DC 사용하지 말것. 클라이언트 영역 크기의 메모리Bitmap 생성 (현재상태 검은색)
	m_memDC.SelectObject(&m_memBMP);				// 메모리DC에 클라이언트영역 크기의 메모리Bitmap 연결 (앞으로 메모리DC에 작업하면 이 메모리Bitmap에 그려진다.)


	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX_COUNT; i++) {
		m_circleList[i].x = rand() % m_width;
		m_circleList[i].y = rand() % m_height;
		m_circleList[i].r = rand() % 40 + 10;

		m_circleList[i].c = RGB(rand() % 256, rand() % 256, rand() % 256);
	}

	SetTimer(1, 50, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}



// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM14Timer1Dlg::OnPaint()
{
	// 무효화 영역이 생겼거나, Invalidate() 호출할 때 ==> OS가 flag를 확인 ==> 다른 메시지 처리 후 최종적으로 해당 윈도를 유효화시킬 때 ==> WM_PAINT 발생
	// CWindowDC, CClientDC, CPaintDC같은 물리DC를 사용할 때 ==> dc에 작업하자마자 바로 물리장치에 반영되므로 작업이 많으면 깜빡인다.
	// ==> 물리DC를 최대한 적게 사용해야(=메모리DC같은 가상DC를 최대한 많이 활용하면) 깜빡임을 줄일 수 있다.

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
		// 메모리DC에서 클라언트DC에 비트맵 복사
		/*BITMAP bmp;
		m_memBMP.GetBitmap(&bmp);
		dc.BitBlt(0, 0, bmp.bmWidth, bmp.bmHeight, &m_memDC, 0, 0, SRCCOPY);*/

		dc.BitBlt(0, 0, m_width, m_height, &m_memDC, 0, 0, SRCCOPY);		// 메모리DC에 연결된 Bitmap에 전체 원(MAX_COUNT개)을 모두 그린 최종 그림을 물리DC에 복사

		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM14Timer1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM14Timer1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {

		// 원 그리기 준비
		CBrush newBrush, * pOldBrush;
		pOldBrush = m_memDC.GetCurrentBrush();

		// 메모리Bitmap 싹다 지우기
		m_memDC.FillSolidRect(0, 0, m_width, m_height, RGB(255, 255, 255));

		// 원 리스트 update
		MyCircle* p = m_circleList;
		for (int i = 0; i < MAX_COUNT; i++) {

			// 반지름 줄이기
			(p->r)--;
			
			// 반지름이 0이면 새로운 원 생성
			if (p->r == 0) {
				p->x = rand() % m_width;
				p->y = rand() % m_height;
				p->r = rand() % 40 + 10;
				p->c = RGB(rand() % 256, rand() % 256, rand() % 256);
			}
			p++;

			newBrush.CreateSolidBrush(p->c);		// for문 안에서 brush 만들었다면
			m_memDC.SelectObject(&newBrush);
			m_memDC.Ellipse(p->x - p->r, p->y - p->r, p->x + p->r, p->y + p->r);
			newBrush.DeleteObject();				// for문 끝나기 전에 brush 삭제!!(안그러면 에러 뜸)
		}
		m_memDC.SelectObject(pOldBrush);

		Invalidate(FALSE);				// 메모리DC에서 물리DC로 바로 복사하므로 배경 지우는 작업(=깜빡임) 불필요
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}

}


void CM14Timer1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(1);
	m_memBMP.DeleteObject();
	m_memDC.DeleteDC();
}
