// CMyView.cpp : implementation file
//

#include "pch.h"
#include "M07ModelessDialog.h"
#include "afxdialogex.h"
#include "CMyView.h"


// CMyView dialog

IMPLEMENT_DYNAMIC(CMyView, CDialogEx)

CMyView::CMyView(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MYVIEW, pParent)
{

}

CMyView::~CMyView()
{
}

void CMyView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyView, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMyView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMyView::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMyView message handlers


void CMyView::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMyView::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}


BOOL CMyView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetBackgroundColor(RGB(100, 100, 200));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
