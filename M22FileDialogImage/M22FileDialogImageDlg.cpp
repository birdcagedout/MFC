
// M22FileDialogImageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M22FileDialogImage.h"
#include "M22FileDialogImageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM22FileDialogImageDlg 대화 상자



CM22FileDialogImageDlg::CM22FileDialogImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M22FILEDIALOGIMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM22FileDialogImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM22FileDialogImageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CM22FileDialogImageDlg::OnBnClickedButtonOpen)
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CM22FileDialogImageDlg 메시지 처리기

BOOL CM22FileDialogImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	
	// 초기화
	m_newImg = false;			// 새 이미지 선택 여부
	GetClientRect(m_rect);		// 클라이언트 영역
	SetBackgroundColor(RGB(168, 198, 0));


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM22FileDialogImageDlg::OnPaint()
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
		// 최초 윈도생성시에 호출된 경우(m_img가 껍데기일 때) ==> 건너뜀
		if (m_img.IsNull() == false) {
			dc.SetStretchBltMode(COLORONCOLOR);		// JPG 파일이 깨진 것 같을 때 (비율이 다를 때 호출되는 StretchBitBlt의 모드 초기값 변경)

			// 새로운 이미지 선택되었다면 ==> 이미지 크기에 맞춰서 윈도 크기를 변경
			if (m_newImg == true) {
				CRect wr, cr;
				GetWindowRect(wr);
				GetClientRect(cr);
				int margin_x = wr.Width() - cr.Width();
				int margin_y = wr.Height() - cr.Height();
				//MoveWindow(wr.left, wr.top, m_img.GetWidth() + margin_x, m_img.GetHeight() + margin_y, TRUE);		// MoveWindow로 윈도 위치, 크기 바꾸는 방법
				SetWindowPos(NULL, 0, 0, m_img.GetWidth() + margin_x, m_img.GetHeight() + margin_y, SWP_NOMOVE);	// SWP_NOMOVE일 때 시작위치 0,0은 무시

				m_newImg = false;
			}

			// 이미지 그리기 : Draw(영역) = 클라이언트 영역에 꽉 차게 그린다.
			m_img.Draw(dc, m_rect);
			//m_img.Draw(dc, 0, 0, m_img.GetWidth(), m_img.GetHeight());
		}

		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM22FileDialogImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 파일 열기
void CM22FileDialogImageDlg::OnBnClickedButtonOpen()
{
	// File Dialog 설정
	wchar_t filter[] = L"모든파일 (*.*)|*.*|PNG파일 (*.PNG)|*.PNG|JPG파일 (*.JPG)|*.JPG||";
	CFileDialog fileDlg(TRUE, L"JPG", L"*.JPG", OFN_HIDEREADONLY | OFN_NOCHANGEDIR, filter);	// OFN_HIDEREADONLY = 대화상자 하단에 "읽기전용으로 열기"라는 checkbox를 숨기기 (최근 대화상자는 없어도 원래 안 보임)
	fileDlg.m_ofn.nFilterIndex = 2;
	

	// 선택한 파일명으로 CImage 가져오기
	if (fileDlg.DoModal() == IDOK) {

		// 기존 이미지가 있다면 먼저 지운다
		if (m_img.IsNull() == false) {
			m_img.Destroy();
		}
		m_img.Load(fileDlg.GetPathName());		// 경로를 포함한 이미지 파일명
		m_newImg = true;
		Invalidate(TRUE);
	}
}


void CM22FileDialogImageDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	GetClientRect(m_rect);		// m_rect.right = cx; m_rect.bottom = cy;
	Invalidate(FALSE);
}


void CM22FileDialogImageDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_img.IsNull() == false) {
		m_img.Destroy();
	}
}
