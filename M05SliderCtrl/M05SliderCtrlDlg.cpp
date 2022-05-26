
// M05SliderCtrlDlg.cpp : implementation file
// 슬라이더를 사용할 때의 유의점
// 1. NM_THUMBPOSCHANGING을 제대로 동작제어하기 어렵다 ==> 쓰지마라
// 2. 슬라이더 이동값을 실시간 처리 어렵다.
// 3. 키보드로 슬라이더 이동시키는 경우 이벤트 발생 안 함.
// ==> 위의 2,3번을 처리하고 싶다면 스크롤바 메시지를 처리할 것



#include "pch.h"
#include "framework.h"
#include "M05SliderCtrl.h"
#include "M05SliderCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM05SliderCtrlDlg dialog



CM05SliderCtrlDlg::CM05SliderCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M05SLIDERCTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM05SliderCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_1, m_mySlider);
	DDX_Control(pDX, IDC_LIST_SHOW, m_listShow);
}

BEGIN_MESSAGE_MAP(CM05SliderCtrlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_1, &CM05SliderCtrlDlg::OnNMReleasedcaptureSlider1)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CM05SliderCtrlDlg message handlers

BOOL CM05SliderCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	// 슬라이더 범위 초기화(원래 0~100)
	m_mySlider.SetRange(0, 200);

	m_mySlider.SetTicFreq(10);




	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CM05SliderCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CM05SliderCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM05SliderCtrlDlg::OnNMReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	/*int pos = m_mySlider.GetPos();

	CString str;
	str.Format(L"%d", pos);
	int index = m_listShow.InsertString(-1, str);
	m_listShow.SetCurSel(index);*/
	

	*pResult = 0;
}


void CM05SliderCtrlDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// nSBCode : 현재 메시지가 들어온 여려가지 원인 정보
	// nPos : nSBCode의 종류에 따라 값의 의미가 달라지거나, 의미가 없을 수도 있다.(무조건 믿지 말것)
	// pScrollBar : 현재 스크롤바의 주소(포인터). 주의 ==> 윈도 기본 스크롤인 경우 NULL이 들어옴

	if (pScrollBar != NULL && pScrollBar->GetDlgCtrlID() == IDC_SLIDER_1) {

		// 마우스로 슬라이더 썸을 ***드래그***하면서 계속 값 검사
		// ==> 유의 : 1. 마우스로 슬라이더 중간을 클릭, 클릭하면 이 메시지 발생하지 않음. 2. 키보드로 움직여도 메시지 발생 안 함
		if (nSBCode == SB_THUMBTRACK) {
			// 이 경우에는 nPos값 유효
			CString str;
			str.Format(L"%d", nPos);
			int index = m_listShow.InsertString(-1, str);
			m_listShow.SetCurSel(index);
		}
		// 썸 위치의 스크롤이 끝났을 때 발생하는 메시지
		// 1) 마우스로 슬라이더 중간을 1회씩 클릭했을 때도 발생 
		// 2) 키보드로 움직여도 메시지 발생 (단, 키를 누르는 동안 연속적으로 계속 발생하는 것이 아니라 끝난 후 1번만 발생)
		// ==> 유의 : 이때는 nPos값이 유효하지 않음 (따라서 슬라이더 멤버변수의  GetPos() 필요)
		else if (nSBCode == SB_ENDSCROLL) {
			// nPos 대신 슬라이더 변수의 GetPos() 사용
			int pos = m_mySlider.GetPos();
			CString str;
			str.Format(L"%d", pos);
			int index = m_listShow.InsertString(-1, str);
			m_listShow.SetCurSel(index);
		}
	}


	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
