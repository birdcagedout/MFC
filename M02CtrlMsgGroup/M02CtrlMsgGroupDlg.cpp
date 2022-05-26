
// M02CtrlMsgGroupDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M02CtrlMsgGroup.h"
#include "M02CtrlMsgGroupDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM02CtrlMsgGroupDlg 대화 상자



CM02CtrlMsgGroupDlg::CM02CtrlMsgGroupDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M02CTRLMSGGROUP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM02CtrlMsgGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM02CtrlMsgGroupDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND_RANGE(IDC_BUTTON1, IDC_BUTTON3, OnSetNum)
END_MESSAGE_MAP()


// CM02CtrlMsgGroupDlg 메시지 처리기

BOOL CM02CtrlMsgGroupDlg::OnInitDialog()
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

void CM02CtrlMsgGroupDlg::OnPaint()
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
HCURSOR CM02CtrlMsgGroupDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// 1. WindowProc 사용
//LRESULT CM02CtrlMsgGroupDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
//{
//	// WM_COMMAND : https://docs.microsoft.com/en-us/windows/win32/menurc/wm-command?redirectedfrom=MSDN
//	// 3가지 경우에 보내짐 : 메뉴, 단축키, 컨트롤
//	// 컨트롤인 경우 : wParam의 LOWORD에 컨트롤 ID, lParam에 컨트롤 핸들
//	if (message == WM_COMMAND) {
//
//		UINT ctrlID = LOWORD(wParam);
//		if (ctrlID >= IDC_BUTTON1 && ctrlID <= IDC_BUTTON3) {			// 한번에 처리할 버튼들의 ID값은 header파일에서 먼저 정렬한다.
//			SetDlgItemInt(IDC_EDIT_SHOW, ctrlID - IDC_BUTTON1 + 1);		// ID를 값으로 변환하는 방법 기억할 것.
//		}
//	}
//
//	return CDialogEx::WindowProc(message, wParam, lParam);
//}



// 2. WM_COMMAND 메시지만 처리하는 WindowProc
//BOOL CM02CtrlMsgGroupDlg::OnCommand(WPARAM wParam, LPARAM lParam)
//{
//	UINT ctrlID = LOWORD(wParam);
//	if (ctrlID >= IDC_BUTTON1 && ctrlID <= IDC_BUTTON3) {			// 한번에 처리할 버튼들의 ID값은 header파일에서 먼저 정렬한다.
//		SetDlgItemInt(IDC_EDIT_SHOW, ctrlID - IDC_BUTTON1 + 1);		// ID를 값으로 변환하는 방법 기억할 것.
//	}
//
//	return CDialogEx::OnCommand(wParam, lParam);
//}


// 3. 특정 메시지에 대한 프로시저 수동으로 지정 : MFC 권장 방법
//    1) 메시지맵에서 On_COMMAND_RANGE(메시지 범위, 처리함수) 추가
//    2) 헤더파일에 처리함수 추가
//    3) 함수 정의
void CM02CtrlMsgGroupDlg::OnSetNum(UINT a_ctrlID)
{
	SetDlgItemInt(IDC_EDIT_SHOW, a_ctrlID - IDC_BUTTON1 + 1);
}