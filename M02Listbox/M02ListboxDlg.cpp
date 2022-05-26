
// M02ListboxDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M02Listbox.h"
#include "M02ListboxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM02ListboxDlg 대화 상자



CM02ListboxDlg::CM02ListboxDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M02LISTBOX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM02ListboxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CHAT, m_listChat);
}

BEGIN_MESSAGE_MAP(CM02ListboxDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SUBMIT, &CM02ListboxDlg::OnBnClickedButtonSubmit)
END_MESSAGE_MAP()


// CM02ListboxDlg 메시지 처리기

BOOL CM02ListboxDlg::OnInitDialog()
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

void CM02ListboxDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM02ListboxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM02ListboxDlg::OnBnClickedButtonSubmit()
{
	CString input;
	GetDlgItemText(IDC_EDIT_INPUT, input);
	
	//m_listChat.AddString(input);								// AddString: 리소스뷰에서 정렬=TRUE/FALSE에 따라 삽입위치 달라짐
	int currentIndex = m_listChat.InsertString(-1, input);		// InsertString: 특정 위치로 지정해서 넣을 수 있다.
	
	m_listChat.SetCurSel(currentIndex);							// 채팅창이 스크롤되면 가장 최근입력에 Selection을 주어야 최근 내용이 보인다.

	SetDlgItemText(IDC_EDIT_INPUT, L"");						// 한줄 입력하고나면 입력줄을 지운다.

}
