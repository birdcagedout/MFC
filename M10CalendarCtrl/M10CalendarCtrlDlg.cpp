
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

	
									
	// 달력 초기화 : CreateFont보다 CreatePointFont가 쓰기 편함
	// DPI 관련되어 첫 인자가 96일 때 12point 정도 크기
	m_font.CreatePointFont(160, L"맑은 고딕");
	m_calendar.SetFont(&m_font);


	// 마침 오늘 날짜에 일정이 있는 경우 ==> 표시하기 위해 함수호출
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
	
	// 구조체로 현재 선택 날짜시간 얻어옴
	SYSTEMTIME currentDateTime;
	m_calendar.GetCurSel(&currentDateTime);		// 만약 선택한 날짜가 없으면 오늘 날짜

	CString strDate;
	//const wchar_t dayOfWeek[8] = L"일월화수목금토";									// 오류남!! NULL-terminated 안되었기 때문
	wchar_t* dayOfWeek[7] = { L"일", L"월", L"화", L"수", L"목", L"금", L"토" };		// dayOfWeek[0] = L"일"

	strDate.Format(L"%04d년 %02d월 %02d일 (%s)", currentDateTime.wYear, currentDateTime.wMonth, currentDateTime.wDay, dayOfWeek[currentDateTime.wDayOfWeek]);		// 시분초는 0:0:0
	SetDlgItemText(IDC_STATIC_DATE, strDate);


	// 선택한 날짜에 일정이 있으면 일정파일을 불러온다
	// _wfopen_s() : https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fopen-s-wfopen-s?view=msvc-170


	// 파일이름 만들기
	CString strFileName, strContent;
	strFileName.Format(L"%04d%02d%02d.dat", currentDateTime.wYear, currentDateTime.wMonth, currentDateTime.wDay);

	// 파일 열기
	FILE* pFile;
	// 파일열기 성공 = 저장된 일정이 있음
	if (_wfopen_s(&pFile, strFileName, L"rt, ccs=UTF-8") == 0) {
		
		// 파일에서 한줄씩 읽기 + 저장 + 파일 닫기
		wchar_t strLine[1024];
		while (fgetws(strLine, 1024, pFile) != NULL) {
			strContent += strLine;
		}
		fclose(pFile);

		// 개행문자 변경
		strContent.Replace(L"\n", L"\r\n");
		SetDlgItemText(IDC_EDIT_NOTE, strContent);
	}
	// 파일열기 실패 = 그런 파일 없음 = 저장된 일정이 없음
	else {
		SetDlgItemText(IDC_EDIT_NOTE, L"");
	}


	// 정상적으로 OS에서 호출된 경우에만 pResult 내용을 0으로 만든다.
	// 최초 윈도생성시 pResult=NULL로 호출되면 이 부분을 skip한다.
	if (pResult != NULL) {
		*pResult = 0;
	}
	
}


void CM10CalendarCtrlDlg::OnBnClickedButtonSave()
{
	// 구조체로 현재 선택 날짜시간 얻어옴
	SYSTEMTIME currentDateTime;
	m_calendar.GetCurSel(&currentDateTime);

	// 파일이름 만들기
	CString strFileName, strContent;
	strFileName.Format(L"%04d%02d%02d.dat", currentDateTime.wYear, currentDateTime.wMonth, currentDateTime.wDay);

	// 파일로 저장
	// // _wfopen_s() : https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fopen-s-wfopen-s?view=msvc-170
	// 주의: 유니코드 내용을 파일에 저장하기 위한 옵션(,ccs=UNICODE 또는 ,ccs=UTF-8) 필요 (없으면 ANSI로 저장)
	//       윈도는 내부적으로 UNICODE, 외부적으로는 ANSI가 기본값. ccs설정 없으면 ANSI로 저장되고 ccs=UNICODE로 설정하면 UTF-16LE로 저장됨
	//       Allowed values of encoding are UNICODE, UTF-8, and UTF-16LE
	FILE* pFile;
	if (_wfopen_s(&pFile, strFileName, L"wt, ccs=UTF-8") == 0) {
		GetDlgItemText(IDC_EDIT_NOTE, strContent);
		strContent.Replace(L"\r\n", L"\n");
		
		fwrite((const wchar_t*)strContent, (strContent.GetLength() + 1)*2, 1, pFile);		// {GetLength()=문자 개수 + 1(NULL)} * 2 = byte단위
		fclose(pFile);
	}
}
