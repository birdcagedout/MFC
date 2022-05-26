
// M11CImageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M11CImage.h"
#include "M11CImageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM11CImageDlg 대화 상자



CM11CImageDlg::CM11CImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M11CIMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM11CImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM11CImageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CM11CImageDlg 메시지 처리기

BOOL CM11CImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.




	// 이미지 불러오기 : 현 시점에서는 대화상자 윈도가 만들어져 있으니 보이지는 않는 상태
	m_img.Load(L"경리500x500.png");		// 특정 경로인 경우: L"C:\\temp\\경리500x500.jpg"

	if (m_img == NULL) {
		MessageBox(L"파일을 읽을 수 없습니다.", L"에러 발생", MB_OK);
		PostQuitMessage(WM_CLOSE);
		return TRUE;
	}

	// 이미지 영역
	m_imageRect.SetRect(10, 10, m_img.GetWidth() + 10, m_img.GetHeight() + 10);


	// 클라이언트 영역
	GetClientRect(m_clientRect);


	// 메모리DC 만들기 (3단계 반드시 기억!!)
	CClientDC dc(this);
	m_memDC.CreateCompatibleDC(&dc);													// 기존 물리DC와 호환되는 메모리DC 생성(width=1, height=1)
	m_memBMP.CreateCompatibleBitmap(&dc, m_clientRect.Width(), m_clientRect.Height());	// 클라이언트 영역 크기의 메모리Bitmap 생성 (현재상태 검은색)
	m_memDC.SelectObject(&m_memBMP);													// 메모리DC에 클라이언트영역 크기의 메모리Bitmap 연결


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM11CImageDlg::OnPaint()
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
		int w = m_img.GetWidth();		// 원본 너비 = 500
		int h = m_img.GetHeight();		// 원본 높이 = 500

		// CImage변수.Draw(dc, Dest좌표4개, Src좌표 4개)
		// 원래는 HDC자리여서 dc.m_hDC를 넣어야 하지만, (HDC)캐스팅 연산자가 oveloading되어 자동으로 dc.m_hDC값이 전달됨

		//m_img.Draw(dc, 10, 10);					// 원본 크기 출력
		//m_img.Draw(dc, 10, 10, w * 0.5, h * 0.5);	// 원본 50% 크기 출력
		//m_img.Draw(dc, 10, 10, w * 0.8, h * 0.8);	// 원본 80% 크기 출력
		//m_img.Draw(dc, 10, 10, w * 2, h * 2);		// 원본 2배 크기 출력

		//m_img.Draw(dc, 10, 10, 150, 150, 200, 100, 150, 150);		// 원래 사진의 일부(200, 100, 150, 150) ==> 그만큼의 크기(150, 150)로 출력
		//m_img.Draw(dc, 10, 10, 150*2, 150*2, 200, 100, 150, 150);	// 원래 사진의 일부(200, 100, 150, 150) ==> 일부의 2배 크기(150*2, 150*2)로 출력
		//m_img.Draw(dc, 10, 10, w, h, 200, 100, 150, 150);			// 원래 사진의 일부(200, 100, 150, 150) ==> 원래 사진 크기만큼으로 확대 출력

		// CImage변수.AlphaBlend(dc, x시작, y시작, 0~255)
		//dc.FillSolidRect(10, 10, 500, 500, RGB(0, 0, 255));			// 뒷배경 테스트용
		//m_img.AlphaBlend(dc, 10, 10, 255);						// 완전 불투명(또렷)
		//m_img.AlphaBlend(dc, 10, 10, 100);						// 100 투명도
		//m_img.AlphaBlend(dc, 10, 10, 50);							// 50 투명도


		//m_img.AlphaBlend(dc, 10, 10, 180);						// 원본 이미지(살짝 흐리게)
		//dc.FillSolidRect(10, 10, 500, 500, RGB(0, 0, 255));
		

		// 메모리 Bitmap 싹다 흰색으로 지우기
		m_memDC.FillSolidRect(0, 0, m_clientRect.Width(), m_clientRect.Height(), RGB(255, 255, 255));


		// 알파블렌드 기본값
		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 150;	// 0=투명, 255=불투명
		bf.AlphaFormat = 0;

		//dc.AlphaBlend(10, 10, w, h, &m_memDC, 0, 0, w, h, bf);

		// 1. 메모리 Bitmap에 이미지의 알파블렌드 그리기
		// 전역 AlphaBlend 사용법 : http://www.tipssoft.com/bulletin/board.php?bo_table=update&wr_id=1250
		AlphaBlend(m_memDC.m_hDC, 10, 10, m_imageRect.Width(), m_imageRect.Height(),
					m_img.GetDC(), 0, 0, m_img.GetWidth(), m_img.GetHeight(), bf);
		

		// 2. 마우스가 그림 위에 있으면 ==> 메모리 Bitmap에 마우스 위치 사각형 + 확대 사각형 그리기
		/*if (m_mouseOver == true) {

		}*/

		// 3. 물리DC로 내보내기
		dc.BitBlt(0, 0, m_clientRect.Width(), m_clientRect.Height(), &m_memDC, 0, 0, SRCCOPY);

		
		m_img.ReleaseDC();
		

		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM11CImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM11CImageDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	//CClientDC dc(this);
	HDC hImgDC = m_img.GetDC();
	CDC* pImgDC = CDC::FromHandle(hImgDC);

	int w = m_img.GetWidth();
	int h = m_img.GetHeight();
	int delta = 50;

	// 마우스가 그림영역 안에 들어오면 작동
	if (m_imageRect.PtInRect(point)) {

		// 마우스가 현재 그림 위에 위치함
		m_mouseOver = true;



		RECT srcRect, dstRect, magRect;


		// 소스 영역 : 마우스 좌표(10,10) ==> 소스 좌표(0,0)으로 매핑
		int srcLeft = max(point.x - 10 - delta, 0);
		int srcTop = max(point.y - 10 - delta, 0);
		int srcRight = min(point.x - 10 + delta, w);
		int srcBottom = min(point.y - 10 + delta, h);
		int srcWidth = srcRight - srcLeft;
		int srcHeight = srcBottom - srcTop;

		srcRect.left = srcLeft;
		srcRect.top = srcTop;
		srcRect.right = srcRight;
		srcRect.bottom = srcBottom;
		
		
		
		// 마우스 영역 : 마우스 좌표 그대로 출력
		int dstLeft = max(point.x - delta, 10);
		int dstTop = max(point.y - delta, 10);
		int dstRight = min(point.x + delta, w + 10);
		int dstBottom = min(point.y + delta, h + 10);
		int dstWidth = dstRight - dstLeft;
		int dstHeight = dstBottom - dstTop;

		dstRect.left = dstLeft;
		dstRect.top = dstTop;
		dstRect.right = dstRight;
		dstRect.bottom = dstBottom;


		// 확대 영역 : 이미지 오른쪽에 별도 표시
		magRect.left = 550;
		magRect.top = 10;
		magRect.right = 550 + dstWidth*3;
		magRect.bottom = 10 + dstHeight*3;
		int magWidth = magRect.right - magRect.left;
		int magHeight = magRect.bottom - magRect.top;
		

		// 6번 오버로딩 함수 사용(dc, &RECT타겟, &RECT소스)
		//dc.FillSolidRect(10, 10, w, h, RGB(255, 255, 255));
		//m_img.AlphaBlend(dc, 10, 10, w, h, 0, 0, w, h, 255);

		Invalidate(FALSE);
		// 출력 : 출력영역1
		//m_img.Draw(hImgDC, srcRect, srcRect);
		//m_img.BitBlt(dc, dstRect.left, dstRect.top, SRCCOPY);
		m_memDC.StretchBlt(dstRect.left, dstRect.top, dstWidth, dstHeight, pImgDC, srcRect.left, srcRect.top, srcWidth, srcHeight, SRCCOPY);

		// 출력 : 출력영역2(확대)
		//m_img.Draw(hImgDC, magRect, srcRect);
		//m_img.BitBlt(dc, magRect.left, magRect.top, SRCCOPY);
		m_memDC.StretchBlt(magRect.left, magRect.top, magWidth, magHeight, pImgDC, srcRect.left, srcRect.top, srcWidth, srcHeight, SRCCOPY);

		CPaintDC dc(this);
		dc.BitBlt(0, 0, m_clientRect.Width(), m_clientRect.Height(), &m_memDC, 0, 0, SRCCOPY);


		m_img.ReleaseDC();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CM11CImageDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
