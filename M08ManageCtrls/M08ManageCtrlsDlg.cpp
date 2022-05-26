
// M08ManageCtrlsDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "M08ManageCtrls.h"
#include "M08ManageCtrlsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM08ManageCtrlsDlg dialog



CM08ManageCtrlsDlg::CM08ManageCtrlsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M08MANAGECTRLS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM08ManageCtrlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM08ManageCtrlsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SHOW, &CM08ManageCtrlsDlg::OnBnClickedButtonShow)
END_MESSAGE_MAP()


// CM08ManageCtrlsDlg message handlers

BOOL CM08ManageCtrlsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CM08ManageCtrlsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CM08ManageCtrlsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM08ManageCtrlsDlg::OnBnClickedButtonShow()
{
	// ��Ʈ���� ��� �� �������� ���1
	/*
	int num[11];

	// Edit ��Ʈ��
	for (int i = 0; i < 5; i++) {
		num[i] = GetDlgItemInt(IDC_EDIT1 + i);
	}

	// �޺��ڽ�
	CComboBox* p;
	for (int j = 0; j < 6; j++) {
		p = (CComboBox*)GetDlgItem(IDC_COMBO1 + j);
		int index = p->GetCurSel();

		// ������ ���� ������ CB_ERR(-1) ��ȯ
		if (index != CB_ERR) {
			CString str;					// �޺��ڽ� ���� �޾ƿ� ���̺���
			p->GetLBText(index, str);
			num[j + 5] = _wtoi(str);
		}
		// ������ ���� ���� ���
		else {
			num[j + 5] = 0;
		}
	}
	*/


	// ��Ʈ���� ��� �� �������� ���2
	int num[11];

	for (int i = 0; i < 11; i++) {
		num[i] = GetDlgItemInt(IDC_EDIT1 + i);		// ComboBox���� GetDlgItemInt / SetDlgItemInt ��� ����
	}



	// ��Ʈ���� ��� ���� �迭�� �Է� ==> Editbox�� ���
	CString str, strResult;
	for (int k = 0; k < 11; k++) {
		str.Format(L"%d ", num[k]);
		strResult = strResult + str;
	}

	SetDlgItemText(IDC_EDIT_RESULT, strResult);

}
