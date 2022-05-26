
// M12GradientFillDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M12GradientFill.h"
#include "M12GradientFillDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM12GradientFillDlg 대화 상자



CM12GradientFillDlg::CM12GradientFillDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M12GRADIENTFILL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM12GradientFillDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM12GradientFillDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CM12GradientFillDlg 메시지 처리기

BOOL CM12GradientFillDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}



void CM12GradientFillDlg::MyGradientFill(CDC* a_dc, int a_x1, int a_y1, int a_x2, int a_y2, COLORREF a_color1, COLORREF a_color2, int a_isVertical=1)
{
	// 그레디언트를 위한 구조체(시작점, 끝점)
	// 그레디언트는 색상마다 16bit :  The color information of each channel is specified as a value from 0x0000 to 0xff00(65280).
	TRIVERTEX vertex[2];

	vertex[0].x = a_x1;			// left
	vertex[0].y = a_y1;			// top

	vertex[0].Red = GetRValue(a_color1) << 8;	//
	vertex[0].Green = GetGValue(a_color1) << 8;	// 0x80 ==> 0x8000
	vertex[0].Blue = GetBValue(a_color1) << 8;	// 0xFF ==> 0xFF00
	vertex[0].Alpha = 0;						// 지금 당장은 안씀(그림 그리고 AlphaBlend로 다시 출력해야 먹힘)


	vertex[1].x = a_x2;			// right
	vertex[1].y = a_y2;			// bottom

	vertex[1].Red = GetRValue(a_color2) << 8;	// 
	vertex[1].Green = GetGValue(a_color2) << 8;	// 0xFF ==> 0xFF00
	vertex[1].Blue = GetBValue(a_color2) << 8;	// 0xFF ==> 0xFF00
	vertex[1].Alpha = 0;						// 지금 당장은 안씀(그림 그리고 AlphaBlend로 다시 출력해야 먹힘)


	// 그레디언트 영역 구조체 : 0, 1값은 고정(바꾼다고 그라데이션 방향이 바뀌지 않는다.)
	GRADIENT_RECT r;
	r.UpperLeft = 0;
	r.LowerRight = 1;

	a_dc->GradientFill(vertex, 2, &r, 1, a_isVertical==1? GRADIENT_FILL_RECT_V : GRADIENT_FILL_RECT_H);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM12GradientFillDlg::OnPaint()
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
		MyGradientFill(&dc, 10, 10, 210, 110, RGB(0, 128, 255), RGB(0, 255, 255), 1);		// 수직 그레디언트 (진한파랑 --> 하늘색)
		MyGradientFill(&dc, 10, 110, 210, 210, RGB(0, 255, 255), RGB(0, 128, 255), 1);		// 수직 그레디언트 (하늘색 --> 진한파랑)


		MyGradientFill(&dc, 220, 10, 320, 210, RGB(0, 128, 255), RGB(0, 255, 255), 0);		// 수평 그레디언트 (진한파랑 --> 하늘색)
		MyGradientFill(&dc, 320, 10, 420, 210, RGB(0, 255, 255), RGB(0, 128, 255), 0);		// 수평 그레디언트 (하늘색 --> 진한파랑)

		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM12GradientFillDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

