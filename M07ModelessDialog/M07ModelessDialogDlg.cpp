
// M07ModelessDialogDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M07ModelessDialog.h"
#include "M07ModelessDialogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM07ModelessDialogDlg 대화 상자



CM07ModelessDialogDlg::CM07ModelessDialogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M07MODELESSDIALOG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM07ModelessDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM07ModelessDialogDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SHOW_DLG, &CM07ModelessDialogDlg::OnBnClickedButtonShowDlg)
	ON_WM_DESTROY()
	ON_MESSAGE(27000, &CM07ModelessDialogDlg::On27000)
	ON_BN_CLICKED(IDC_BUTTON_SETNUM, &CM07ModelessDialogDlg::OnBnClickedButtonSetnum)
END_MESSAGE_MAP()


// CM07ModelessDialogDlg 메시지 처리기

BOOL CM07ModelessDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	// 새로운 대화상자2 바로 만들어버림
	m_pMyView = new CMyView;
	m_pMyView->Create(IDD_DIALOG_MYVIEW, this);
	m_pMyView->SetWindowPos(NULL, 15, 300, 0, 0, SWP_NOSIZE);				// SetWindowPos(Z-order, 시작x, 시작y, 폭, 높이, SWP_NOSIZE=폭과높이원래크기대로);



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM07ModelessDialogDlg::OnPaint()
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
HCURSOR CM07ModelessDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 새로운 대화상자 만들기
void CM07ModelessDialogDlg::OnBnClickedButtonShowDlg()
{
	// 새로운 대화상자가 이미 만들어지지 않은 경우에만
	if (m_pNewDlg == NULL) {
		m_pNewDlg = new CNewDlg;
		m_pNewDlg->Create(IDD_DIALOG_NEW, this);			// Modeless 대화상자 생성: Create(다이얼로그ID, 부모Wnd의 포인터) ==> 부모Wnd 포인터에 NULL을 주면 애비에미 없는 대화상자
	}
}


void CM07ModelessDialogDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_pNewDlg != NULL) {
		On27000(0, 0);
		//delete m_pNewDlg;
	}

	// 새로운 대화상자2 지움
	m_pMyView->DestroyWindow();
	delete m_pMyView;

}


// 새로운 대화상자에서 PostMessage(27000) 전송했을 때 처리함수
afx_msg LRESULT CM07ModelessDialogDlg::On27000(WPARAM wParam, LPARAM lParam)
{
	m_pNewDlg->DestroyWindow();
	delete m_pNewDlg;
	m_pNewDlg = NULL;				// 다시 새로운 대화상자 생성할 수 있도록 초기화
	return 0;
}


void CM07ModelessDialogDlg::OnBnClickedButtonSetnum()
{
	// 새로운 대화상자가 이미 실행된 경우에만
	if (m_pNewDlg != NULL) {
		int num = GetDlgItemInt(IDC_EDIT_PARENT);
		m_pNewDlg->SetDlgItemInt(IDC_EDIT_CHILD, num);		// 새로운 대화상자가 이미 만들어져 있으므로 멤버변수에 값을 넣는 방식 쓸 필요 없다
	}
}
