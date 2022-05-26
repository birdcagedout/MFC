
// M07ModalDialogDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M07ModalDialog.h"
#include "M07ModalDialogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM07ModalDialogDlg 대화 상자



CM07ModalDialogDlg::CM07ModalDialogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M07MODALDIALOG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM07ModalDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM07ModalDialogDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SHOW_DLG, &CM07ModalDialogDlg::OnBnClickedButtonShowDlg)
END_MESSAGE_MAP()


// CM07ModalDialogDlg 메시지 처리기

BOOL CM07ModalDialogDlg::OnInitDialog()
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

void CM07ModalDialogDlg::OnPaint()
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
HCURSOR CM07ModalDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


#include "CNewDlg.h"

void CM07ModalDialogDlg::OnBnClickedButtonShowDlg()
{
	int num = GetDlgItemInt(IDC_EDIT_PARENT);

	CNewDlg dlg;
	//dlg.SetDlgItemInt(IDC_EDIT_CHILD, num);		// DoModal() 호출 전에는 대화상자 윈도가 만들어지지 않은 상태라 컨트롤에 입력 ==> **절대** 안 됨
	dlg.SetNum(num);								// 클래스 내부변수에 값 저장 ==> OnInitDialog() 내에서 SetDlgItemInt() 호출

	int response = dlg.DoModal();
	if (response == IDOK) {
		num = dlg.GetNum();
		SetDlgItemInt(IDC_EDIT_PARENT, num);
	}
	else if (response == 20) {						// EndDialog(반환값)으로 종료시킬 수도 있다.
		SetDlgItemInt(IDC_EDIT_PARENT, 0);
	}
}
