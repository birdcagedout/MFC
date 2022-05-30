// CNewFolderDlg.cpp: 구현 파일
//

#include "pch.h"
#include "M26FileFolder1.h"
#include "afxdialogex.h"
#include "CNewFolderDlg.h"


// CNewFolderDlg 대화 상자

IMPLEMENT_DYNAMIC(CNewFolderDlg, CDialogEx)

CNewFolderDlg::CNewFolderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_R_NEW_FOLDER, pParent)
{
	m_folderName = "";
}

CNewFolderDlg::~CNewFolderDlg()
{
}

void CNewFolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewFolderDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNewFolderDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNewFolderDlg 메시지 처리기


void CNewFolderDlg::OnBnClickedOk()
{
	// 새폴더 이름 저장
	GetDlgItemText(IDC_EDIT_NEW_FOLDER_NAME, m_folderName);
	m_folderName.Trim();

	if (m_folderName.GetLength() == 0) {
		MessageBox(L"폴더명이 적절하지 않습니다.", L"오류", MB_OK | MB_ICONERROR);
	}

	CDialogEx::OnOK();
}




CString CNewFolderDlg::GetFolderName()
{
	return m_folderName;
}