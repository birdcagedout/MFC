// CNewDlg.cpp : implementation file
//

#include "pch.h"
#include "M07ModelessDialog.h"
#include "afxdialogex.h"
#include "CNewDlg.h"


// CNewDlg dialog

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
	ON_BN_CLICKED(IDCANCEL, &CNewDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_RETURN, &CNewDlg::OnBnClickedButtonReturn)
END_MESSAGE_MAP()


// CNewDlg message handlers


void CNewDlg::OnBnClickedOk()
{
	GetParent()->PostMessage(27000);			// �θ� ��ȭ���ڿ� 27000�� ���� ==> �θ� ������ ���ο� ��ȭ���� �����ϵ���
	//CDialogEx::OnOK();
}


// ���ο� ��ȭ���ڿ��� "���"��ư �Ǵ� "X"��ư ������ ��
void CNewDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}


void CNewDlg::OnBnClickedButtonReturn()
{
	int num = GetDlgItemInt(IDC_EDIT_CHILD);
	GetParent()->SetDlgItemInt(IDC_EDIT_PARENT, num);
}
