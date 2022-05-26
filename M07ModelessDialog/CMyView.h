#pragma once
#include "afxdialogex.h"


// CMyView dialog

class CMyView : public CDialogEx
{
	DECLARE_DYNAMIC(CMyView)

public:
	CMyView(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CMyView();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MYVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
