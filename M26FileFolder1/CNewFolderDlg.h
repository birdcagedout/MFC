#pragma once
#include "afxdialogex.h"


// CNewFolderDlg 대화 상자

class CNewFolderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewFolderDlg)

public:
	CNewFolderDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CNewFolderDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_R_NEW_FOLDER };
#endif

protected:
	CString m_folderName;


	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
