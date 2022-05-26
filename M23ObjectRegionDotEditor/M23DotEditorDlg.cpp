
// M23DotEditorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M23DotEditor.h"
#include "M23DotEditorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM23DotEditorDlg 대화 상자



CM23DotEditorDlg::CM23DotEditorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M23DOTEDITOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	// 전경색, 배경색
	m_fgColor = RGB(0, 0, 255);
	m_bgColor = RGB(250, 250, 250);

	// dot color = 흰색 
	for (int y = 0; y < GRID_Y_COUNT; y++) {
		for (int x = 0; x < GRID_X_COUNT; x++) {
			m_dotColor[y][x] = RGB(255, 255, 255);
		}
	}

	// 그리드 펜
	m_gridPen.CreatePen(PS_SOLID, 1, RGB(220, 220, 220));
}

void CM23DotEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM23DotEditorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_FGCOLOR, &CM23DotEditorDlg::OnBnClickedButtonFgcolor)
	ON_BN_CLICKED(IDC_BUTTON_BGCOLOR, &CM23DotEditorDlg::OnBnClickedButtonBgcolor)
END_MESSAGE_MAP()


// CM23DotEditorDlg 메시지 처리기

BOOL CM23DotEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	
	// 버튼 위치
	GetDlgItem(IDC_BUTTON_FGCOLOR)->GetWindowRect(m_fgRect);
	GetDlgItem(IDC_BUTTON_BGCOLOR)->GetWindowRect(m_bgRect);
	ScreenToClient(m_fgRect);
	ScreenToClient(m_bgRect);

	m_fgRect.left -= 10;
	m_fgRect.right = m_fgRect.left + 7;

	m_bgRect.left -= 10;
	m_bgRect.right = m_bgRect.left + 7;



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM23DotEditorDlg::OnPaint()
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
		CBrush* pOldBrush, newBrush;
		pOldBrush = dc.GetCurrentBrush();
		//dc.SelectStockObject(DC_BRUSH);
		
		for (int y = 0; y < GRID_Y_COUNT; y++) {
			for (int x = 0; x < GRID_X_COUNT; x++) {
				//dc.SetDCBrushColor(m_dotColor[y][x]);
				newBrush.CreateSolidBrush(m_dotColor[y][x]);
				dc.SelectObject(&newBrush);
				dc.Rectangle(x * DOT_SIZE, y * DOT_SIZE, (x + 1) * DOT_SIZE + 1, (y + 1) * DOT_SIZE + 1);
				newBrush.DeleteObject();		// 브러시를 새로 만들기 전에 반드시 삭제 (안하면 프로그램 죽음)
			}
		}

		// 버튼 옆 색깔표시
		dc.SelectStockObject(DC_BRUSH);
		dc.SetDCBrushColor(m_fgColor);
		dc.Rectangle(m_fgRect);

		dc.SelectStockObject(DC_BRUSH);
		dc.SetDCBrushColor(m_bgColor);
		dc.Rectangle(m_bgRect);


		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM23DotEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 마우스가 움직이면 항상 생성되는 메시지 (L버튼up/down, R버튼up/down 등)
// nFlags에 키보드키, 마우스버튼 모두 들어있다.
// OnMouseMove : https://docs.microsoft.com/en-us/cpp/mfc/reference/cwnd-class?view=msvc-170#onmousemove
void CM23DotEditorDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// L버튼
	//if ((nFlags & MK_LBUTTON) || (nFlags & MK_RBUTTON)) {
	if (nFlags & (MK_LBUTTON | MK_RBUTTON)) {

		// 유효영역인지 체크 ==> 맞으면 그 위치 사각형 1개 그리기
		if ((point.x < GRID_X_COUNT * DOT_SIZE) && (point.y < GRID_Y_COUNT * DOT_SIZE)) {
			int x = point.x / DOT_SIZE;
			int y = point.y / DOT_SIZE;

			CClientDC dc(this);
			CPen* pOldPen = dc.SelectObject(&m_gridPen);
			CBrush* pOldBrush = (CBrush*)dc.SelectStockObject(DC_BRUSH);

			if (nFlags & MK_LBUTTON) {
				m_dotColor[y][x] = m_fgColor;
			}
			else if (nFlags & MK_RBUTTON) {
				m_dotColor[y][x] = m_bgColor;
			}
			dc.SetDCBrushColor(m_dotColor[y][x]);
			dc.Rectangle(x * DOT_SIZE, y * DOT_SIZE, (x + 1) * DOT_SIZE + 1, (y + 1) * DOT_SIZE + 1);

			dc.SelectObject(pOldBrush);
			dc.SelectObject(pOldPen);
		}
		
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CM23DotEditorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	OnMouseMove(MK_LBUTTON, point);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CM23DotEditorDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	OnMouseMove(MK_RBUTTON, point);

	CDialogEx::OnRButtonDown(nFlags, point);
}


void CM23DotEditorDlg::OnBnClickedButtonFgcolor()
{
	CColorDialog colorDlg;
	colorDlg.m_cc.Flags |= CC_FULLOPEN;		// 컬러피커 모두 펼친 상태
	colorDlg.m_cc.Flags |= CC_RGBINIT;		// 최초 선택값을 지정하겠다
	colorDlg.m_cc.rgbResult = m_fgColor;	// ==> 그 값은 전경색

	if (colorDlg.DoModal() == IDOK) {
		m_fgColor = colorDlg.GetColor();
	}

	// 버튼 옆 색깔표시
	/*
	CClientDC dc(this);
	CPen* pOldPen = dc.SelectObject(&m_gridPen);
	dc.SelectStockObject(DC_BRUSH);
	dc.SetDCBrushColor(m_fgColor);
	dc.Rectangle(m_fgRect);
	dc.SelectObject(pOldPen);
	*/

	InvalidateRect(m_fgRect, FALSE);		// 배경을 다시 지우고 새로 칠할 필요 없이, 그 위에 덮어쓰기
}


void CM23DotEditorDlg::OnBnClickedButtonBgcolor()
{
	CColorDialog colorDlg;
	colorDlg.m_cc.Flags |= CC_FULLOPEN;		// 컬러피커 모두 펼친 상태
	colorDlg.m_cc.Flags |= CC_RGBINIT;		// 최초 선택값을 지정하겠다
	colorDlg.m_cc.rgbResult = m_bgColor;	// ==> 그 값은 배경색

	if (colorDlg.DoModal() == IDOK) {
		m_bgColor = colorDlg.GetColor();
	}

	// 버튼 옆 색깔표시
	/*
	CClientDC dc(this);
	CPen* pOldPen = dc.SelectObject(&m_gridPen);
	dc.SelectStockObject(DC_BRUSH);
	dc.SetDCBrushColor(m_bgColor);
	dc.Rectangle(m_bgRect);
	dc.SelectObject(pOldPen);
	*/
	InvalidateRect(m_bgRect, FALSE);		// 배경을 다시 지우고 새로 칠할 필요 없이, 그 위에 덮어쓰기
}
