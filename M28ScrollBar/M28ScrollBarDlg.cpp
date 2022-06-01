
// M28ScrollBarDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M28ScrollBar.h"
#include "M28ScrollBarDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM28ScrollBarDlg 대화 상자



CM28ScrollBarDlg::CM28ScrollBarDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M28SCROLLBAR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM28ScrollBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM28ScrollBarDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CM28ScrollBarDlg 메시지 처리기

BOOL CM28ScrollBarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CRect r;
	GetClientRect(r);


	m_scrollPos = 0;
	SetScrollRange(SB_VERT, 0, 8*200 - r.bottom + 50);
	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM28ScrollBarDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0, 55, 250));

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
		for (int dan = 2; dan <= 9; dan++) {
			for (int i = 1; i <= 9; i++) {
				CString strOut;
				strOut.Format(L"%d * %d = %2d", dan, i, dan * i);

				dc.TextOut(20, (dan - 2) * 200 + 20 * i - m_scrollPos, strOut);
			}
		}

		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM28ScrollBarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 리소스 속성에서 세로스크롤=True
// WM_VSCROLL 처리기
void CM28ScrollBarDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == NULL) {
		int min = 0, max = 0;
		GetScrollRange(SB_VERT, &min, &max);
		m_scrollPos = GetScrollPos(SB_VERT);

		if (nSBCode == SB_LINEDOWN) {
			if (m_scrollPos < max) {
				SetScrollPos(SB_VERT, ++m_scrollPos);
			}
		}
		else if (nSBCode == SB_LINEUP) {
			if (m_scrollPos > min) {
				SetScrollPos(SB_VERT, --m_scrollPos);
			}
		}
		else if (nSBCode == SB_PAGEDOWN) {
			if (m_scrollPos < max - 20) {
				SetScrollPos(SB_VERT, m_scrollPos + 20);
				m_scrollPos += 20;
			}
		}
		else if (nSBCode == SB_PAGEUP) {
			if (m_scrollPos > min + 20) {
				SetScrollPos(SB_VERT, m_scrollPos - 20);
				m_scrollPos -= 20;
			}
		}
		else if (nSBCode == TB_THUMBPOSITION || nSBCode == TB_THUMBTRACK) {
			SetScrollPos(SB_VERT, nPos);
		}
		Invalidate();
	}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
