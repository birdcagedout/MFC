#pragma once
#include "afxdialogex.h"


// CNewDlg 대화 상자

class CNewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewDlg)

public:
	CNewDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CNewDlg();

	void SetNum(int a_num)
	{
		m_num = a_num;
	}
	int GetNum()
	{
		return m_num;
	}

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NEW };
#endif

protected:
	int m_num;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonExit();
};
