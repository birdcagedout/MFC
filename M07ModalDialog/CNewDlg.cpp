// CNewDlg.cpp: 구현 파일
//

#include "pch.h"
#include "M07ModalDialog.h"
#include "afxdialogex.h"
#include "CNewDlg.h"


// CNewDlg 대화 상자

IMPLEMENT_DYNAMIC(CNewDlg, CDialogEx)

CNewDlg::CNewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NEW, pParent)
{

}

CNewDlg::~CNewDlg()
{
}

void CNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNewDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CNewDlg::OnBnClickedButtonExit)
END_MESSAGE_MAP()


// CNewDlg 메시지 처리기


BOOL CNewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemInt(IDC_EDIT_CHILD, m_num);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CNewDlg::OnBnClickedOk()
{
	m_num = GetDlgItemInt(IDC_EDIT_CHILD);

	CDialogEx::OnOK();		// EndDialog(IDOK) 숨어있음
}


void CNewDlg::OnBnClickedButtonExit()
{
	// CWnd 함수
	EndDialog(20);			// 20은 마음대로 정한 값
}
