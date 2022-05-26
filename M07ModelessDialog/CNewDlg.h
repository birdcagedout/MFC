#pragma once
#include "afxdialogex.h"



// CNewDlg dialog

class CNewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewDlg)

public:
	CNewDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CNewDlg();

	void SetNum(int a_num)
	{
		m_num = a_num;
	}

	int GetNum()
	{
		return m_num;
	}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	int m_num;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonReturn();
};
