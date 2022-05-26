
// M14MemDCbyCImageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M14MemDCbyCImage.h"
#include "M14MemDCbyCImageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM14MemDCbyCImageDlg 대화 상자



CM14MemDCbyCImageDlg::CM14MemDCbyCImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M14MEMDCBYCIMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM14MemDCbyCImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM14MemDCbyCImageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()


// CM14MemDCbyCImageDlg 메시지 처리기

BOOL CM14MemDCbyCImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	

	// 클라이언트 영역
	CRect r;
	GetClientRect(r);

	// CImage 객체로 메모리DC 만들기
	m_img.Create(r.Width(), r.Height(), 32);

	// 원 만들기
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX_COUNT; i++) {
		m_circleList[i].x = rand() % m_img.GetWidth();
		m_circleList[i].y = rand() % m_img.GetHeight();
		m_circleList[i].r = rand() % 50 + 10;
		m_circleList[i].c = RGB(rand() % 256, rand() % 256, rand() % 256);
	}

	// 타이머 만들기
	SetTimer(1, 50, NULL);



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM14MemDCbyCImageDlg::OnPaint()
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
		m_img.Draw(dc, 0, 0);		// 첫번째 인자에 hDC를 넣어야 하는데 연산자 재정의 때문에 그냥 CDC 객체 넣으면 됨
		//dc.BitBlt(0, 0, m_width, m_height, &m_memDC, 0, 0, SRCCOPY);		// 메모리DC에 연결된 Bitmap에 전체 원(MAX_COUNT개)을 모두 그린 최종 그림을 물리DC에 복사

		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM14MemDCbyCImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM14MemDCbyCImageDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {

		// 원 그리기 준비
		// CImage객체에서는 HDC를 CDC 객체로 변환할 필요 있음
		HDC hImgDC = m_img.GetDC();					// GetDC 후에는 반드시 ReleaseDC
		CDC* pImgDC = CDC::FromHandle(hImgDC);

		CBrush newBrush, * pOldBrush;
		pOldBrush = pImgDC->GetCurrentBrush();

		// 메모리Bitmap 싹다 지우기
		pImgDC->FillSolidRect(0, 0, m_img.GetWidth(), m_img.GetHeight(), RGB(255, 255, 255));

		// 원 리스트 update
		Circle* p = m_circleList;
		for (int i = 0; i < MAX_COUNT; i++) {

			// 반지름 줄이기
			(p->r)--;

			// 반지름이 0이면 새로운 원 생성
			if (p->r == 0) {
				p->x = rand() % m_img.GetWidth();
				p->y = rand() % m_img.GetHeight();
				p->r = rand() % 50 + 10;
				p->c = RGB(rand() % 256, rand() % 256, rand() % 256);
			}
			p++;

			newBrush.CreateSolidBrush(p->c);		// for문 안에서 brush 만들었다면
			pImgDC->SelectObject(&newBrush);
			pImgDC->Ellipse(p->x - p->r, p->y - p->r, p->x + p->r, p->y + p->r);
			newBrush.DeleteObject();				// for문 끝나기 전에 brush 삭제!! (안그러면 에러 뜸)
		}
		pImgDC->SelectObject(pOldBrush);
		m_img.ReleaseDC();							// GetDC 후에는 반드시 ReleaseDC
		Invalidate(FALSE);							// 메모리DC에서 물리DC로 바로 복사하므로 배경 지우는 작업(=깜빡임) 불필요
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}


void CM14MemDCbyCImageDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(1);
}



// 위치, 사이즈, Z-order 바뀌었을 때 호출
// ==> 여기서는 윈도 사이즈가 바뀌었을 때(WM_SIZE) 바뀐 크기에 따라 클라이언트 영역에 비트맵 새로 그림
void CM14MemDCbyCImageDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// BOOL(TRUE/FALSE)는 C기반 매크로(int)
	// bool(true/false)는 C++ 표준
	if (m_img.IsNull() == false) {
		m_img.Destroy();
		m_img.Create(lpwndpos->cx, lpwndpos->cy, 32);
	}
}
