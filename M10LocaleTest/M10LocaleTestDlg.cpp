
// M10LocaleTestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M10LocaleTest.h"
#include "M10LocaleTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM10LocaleTestDlg 대화 상자



CM10LocaleTestDlg::CM10LocaleTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M10LOCALETEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM10LocaleTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MYCALENDAR, m_calendar);
}

BEGIN_MESSAGE_MAP(CM10LocaleTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(MCN_SELCHANGE, IDC_MYCALENDAR, &CM10LocaleTestDlg::OnMcnSelchangeMycalendar)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CM10LocaleTestDlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CM10LocaleTestDlg 메시지 처리기

BOOL CM10LocaleTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// 마침 오늘 날짜에 일정이 있는 경우 ==> 표시하기 위해 함수호출
	OnMcnSelchangeMycalendar(NULL, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM10LocaleTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM10LocaleTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM10LocaleTestDlg::OnMcnSelchangeMycalendar(NMHDR* pNMHDR, LRESULT* pResult)
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


void CM10LocaleTestDlg::OnBnClickedButtonSave()
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

		fwrite((const wchar_t*)strContent, (strContent.GetLength() + 1) * 2, 1, pFile);		// {GetLength()=문자 개수 + 1(NULL)} * 2 = byte단위
		fclose(pFile);
	}
}
