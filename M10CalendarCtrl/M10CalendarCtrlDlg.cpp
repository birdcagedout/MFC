
// M10CalendarCtrlDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "M10CalendarCtrl.h"
#include "M10CalendarCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM10CalendarCtrlDlg dialog



CM10CalendarCtrlDlg::CM10CalendarCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M10CALENDARCTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM10CalendarCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_calendar);
}

BEGIN_MESSAGE_MAP(CM10CalendarCtrlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, &CM10CalendarCtrlDlg::OnMcnSelchangeMonthcalendar1)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CM10CalendarCtrlDlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CM10CalendarCtrlDlg message handlers

BOOL CM10CalendarCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	
									
	// �޷� �ʱ�ȭ : CreateFont���� CreatePointFont�� ���� ����
	// DPI ���õǾ� ù ���ڰ� 96�� �� 12point ���� ũ��
	m_font.CreatePointFont(160, L"���� ���");
	m_calendar.SetFont(&m_font);


	// ��ħ ���� ��¥�� ������ �ִ� ��� ==> ǥ���ϱ� ���� �Լ�ȣ��
	OnMcnSelchangeMonthcalendar1(NULL, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CM10CalendarCtrlDlg::OnPaint()
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
HCURSOR CM10CalendarCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM10CalendarCtrlDlg::OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult)
{
	//LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	
	// ����ü�� ���� ���� ��¥�ð� ����
	SYSTEMTIME currentDateTime;
	m_calendar.GetCurSel(&currentDateTime);		// ���� ������ ��¥�� ������ ���� ��¥

	CString strDate;
	//const wchar_t dayOfWeek[8] = L"�Ͽ�ȭ�������";									// ������!! NULL-terminated �ȵǾ��� ����
	wchar_t* dayOfWeek[7] = { L"��", L"��", L"ȭ", L"��", L"��", L"��", L"��" };		// dayOfWeek[0] = L"��"

	strDate.Format(L"%04d�� %02d�� %02d�� (%s)", currentDateTime.wYear, currentDateTime.wMonth, currentDateTime.wDay, dayOfWeek[currentDateTime.wDayOfWeek]);		// �ú��ʴ� 0:0:0
	SetDlgItemText(IDC_STATIC_DATE, strDate);


	// ������ ��¥�� ������ ������ ���������� �ҷ��´�
	// _wfopen_s() : https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fopen-s-wfopen-s?view=msvc-170


	// �����̸� �����
	CString strFileName, strContent;
	strFileName.Format(L"%04d%02d%02d.dat", currentDateTime.wYear, currentDateTime.wMonth, currentDateTime.wDay);

	// ���� ����
	FILE* pFile;
	// ���Ͽ��� ���� = ����� ������ ����
	if (_wfopen_s(&pFile, strFileName, L"rt, ccs=UTF-8") == 0) {
		
		// ���Ͽ��� ���پ� �б� + ���� + ���� �ݱ�
		wchar_t strLine[1024];
		while (fgetws(strLine, 1024, pFile) != NULL) {
			strContent += strLine;
		}
		fclose(pFile);

		// ���๮�� ����
		strContent.Replace(L"\n", L"\r\n");
		SetDlgItemText(IDC_EDIT_NOTE, strContent);
	}
	// ���Ͽ��� ���� = �׷� ���� ���� = ����� ������ ����
	else {
		SetDlgItemText(IDC_EDIT_NOTE, L"");
	}


	// ���������� OS���� ȣ��� ��쿡�� pResult ������ 0���� �����.
	// ���� ���������� pResult=NULL�� ȣ��Ǹ� �� �κ��� skip�Ѵ�.
	if (pResult != NULL) {
		*pResult = 0;
	}
	
}


void CM10CalendarCtrlDlg::OnBnClickedButtonSave()
{
	// ����ü�� ���� ���� ��¥�ð� ����
	SYSTEMTIME currentDateTime;
	m_calendar.GetCurSel(&currentDateTime);

	// �����̸� �����
	CString strFileName, strContent;
	strFileName.Format(L"%04d%02d%02d.dat", currentDateTime.wYear, currentDateTime.wMonth, currentDateTime.wDay);

	// ���Ϸ� ����
	// // _wfopen_s() : https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fopen-s-wfopen-s?view=msvc-170
	// ����: �����ڵ� ������ ���Ͽ� �����ϱ� ���� �ɼ�(,ccs=UNICODE �Ǵ� ,ccs=UTF-8) �ʿ� (������ ANSI�� ����)
	//       ������ ���������� UNICODE, �ܺ������δ� ANSI�� �⺻��. ccs���� ������ ANSI�� ����ǰ� ccs=UNICODE�� �����ϸ� UTF-16LE�� �����
	//       Allowed values of encoding are UNICODE, UTF-8, and UTF-16LE
	FILE* pFile;
	if (_wfopen_s(&pFile, strFileName, L"wt, ccs=UTF-8") == 0) {
		GetDlgItemText(IDC_EDIT_NOTE, strContent);
		strContent.Replace(L"\r\n", L"\n");
		
		fwrite((const wchar_t*)strContent, (strContent.GetLength() + 1)*2, 1, pFile);		// {GetLength()=���� ���� + 1(NULL)} * 2 = byte����
		fclose(pFile);
	}
}
