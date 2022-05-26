
// M01TestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M01Test.h"
#include "M01TestDlg.h"
#include "afxdialogex.h"
#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM01TestDlg 대화 상자



CM01TestDlg::CM01TestDlg(CWnd* pParent /*=nullptr*/) : CDialogEx(IDD_M01TEST_DIALOG, pParent)/*, m_editMsg(_T(""))*/
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM01TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EDIT_MSG, m_editMsg);
}

BEGIN_MESSAGE_MAP(CM01TestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_SUBMIT, &CM01TestDlg::OnClickedButtonSubmit)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CM01TestDlg::OnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, &CM01TestDlg::OnClickedButtonWrite)
END_MESSAGE_MAP()


// CM01TestDlg 메시지 처리기

BOOL CM01TestDlg::OnInitDialog()
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

void CM01TestDlg::OnPaint()
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
HCURSOR CM01TestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//LRESULT CM01TestDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
//{
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//
//	return CDialogEx::WindowProc(message, wParam, lParam);
//}


//void CM01TestDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	CClientDC dc(this);
//
//	int x = point.x;
//	int y = point.y;
//
//	if (nFlags & MK_CONTROL) {
//		dc.Ellipse(x - 15, y - 15, x + 15, y + 15);
//	}
//	else {
//		dc.Rectangle(x - 15, y - 15, x + 15, y + 15);
//	}
//
//	CDialogEx::OnLButtonDown(nFlags, point);
//}


void CM01TestDlg::OnClickedButtonSubmit()
{
	// Edit 컨트롤에서 문자열 가져오기
	/*wchar_t str[64];
	GetDlgItemText(IDC_EDIT_MSG, str, 64);*/

	// CString으로 문자열 가져오기 : 문자열 길이 필요없다.
	CString str;
	GetDlgItemText(IDC_EDIT_MSG, str);

	// 메시지박스 띄우기: (내용, 제목, 형식) 중 내용만 적어도 된다.
	MessageBox(L"사용자 입력: " + str, L"알림");
}


void CM01TestDlg::OnClickedButtonRead()
{
	// 1. 컨트롤을 변수에 연결한 경우
	// TRUE: 컨트롤 ==> 변수
	/*UpdateData(TRUE);
	AfxMessageBox(m_editMsg);*/


	// 2. 컨트롤을 변수에 연결하지 않고 값 얻기
	/*CString str;
	GetDlgItemText(IDC_EDIT_MSG, str);
	AfxMessageBox(str);*/


	// 3. 컨트롤을 변수에 연결하지 않고 int형으로 값 얻기
	//    - 음수도 가능
	//    - 첫문자부터 숫자가 아니면 ==> 0
	//    - 처음의 숫자부분과 숫자 아닌 부분이 섞이면 숫자부분까지만(0032a11 ==> 32)
	/*int val = GetDlgItemInt(IDC_EDIT_MSG);
	CString str;
	str.Format(L"%d", val);
	AfxMessageBox(str);*/


	// 4. Edit 컨트롤에 입력된 문자 길이 받기
	CEdit* p = (CEdit*)GetDlgItem(IDC_EDIT_MSG);
	int len = p->SendMessage(WM_GETTEXTLENGTH);
	len = p->GetWindowTextLength();

	wchar_t str[10];
	if (len >= 10) {
		AfxMessageBox(L"문자길이 9자까지만 허용됩니다.");
	}
	else {
		GetDlgItemText(IDC_EDIT_MSG, str, 10);		// 널문자 빼고 9자까지만 들어감
		AfxMessageBox(str);
	}


}


void CM01TestDlg::OnClickedButtonWrite()
{
	// 1. 컨트롤을 변수에 연결한 경우
	//m_editMsg = L"초기값입니다.";
	//// TRUE: 변수 ==> 컨트롤
	//UpdateData(FALSE);


	// 2. 컨트롤을 변수에 연결하지 않고 값 쓰기
	CString str = L"기본값입니다";
	SetDlgItemText(IDC_EDIT_MSG, str);
}
