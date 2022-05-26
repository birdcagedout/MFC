
// M09NotepadDlg.cpp : implementation file
// 파일열기/파일저장하는 메모장 연습(똠방각하)

#include "pch.h"
#include "framework.h"
#include "M09Notepad.h"
#include "M09NotepadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM09NotepadDlg dialog



CM09NotepadDlg::CM09NotepadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M09NOTEPAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM09NotepadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM09NotepadDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPENFILE, &CM09NotepadDlg::OnBnClickedButtonOpenfile)
	ON_BN_CLICKED(IDC_BUTTON_SAVEFILE, &CM09NotepadDlg::OnBnClickedButtonSavefile)
	ON_BN_CLICKED(IDOK, &CM09NotepadDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CM09NotepadDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CM09NotepadDlg message handlers

BOOL CM09NotepadDlg::OnInitDialog()
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

void CM09NotepadDlg::OnPaint()
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
HCURSOR CM09NotepadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 파일 대화상자 열기
// CFileDialog : https://docs.microsoft.com/en-us/cpp/mfc/reference/cfiledialog-class?f1url=%3FappId%3DDev16IDEF1%26l%3DEN-US%26k%3Dk(AFXDLGS%252FCFileDialog)%3Bk(CFileDialog)%3Bk(DevLang-C%252B%252B)%3Bk(TargetOS-Windows)%26rd%3Dtrue&view=msvc-170#cfiledialog

void CM09NotepadDlg::OnBnClickedButtonOpenfile()
{
	wchar_t fileExtFilter[] = L"모든 파일(*.*)|*.*|C++소스파일(*.cpp)|*.cpp|C++헤더파일(*.h)|*.h|텍스트파일(*.txt)|*.txt||";	// 확장자 필터 = L"보여질부분|실제확장자조건|......||"
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR, fileExtFilter);
	//			fileDlg(TRUE=파일열기 FALSE=파일저장, 기본확장자(저장할때 확장자 지정하지 않으면 뒤에 자동 붙음), 기본파일이름, 속성Flags, 확장자filter문자열);
	fileDlg.m_ofn.nFilterIndex = 4;		// 파일 대화상자가 열렸을 때 기본 filter 선택(0=선택안함, 1=fileExtFilter배열의 1번째, 2=fileExtFilter배열의 2번째, ...)


	// 파일 대화상자에서 OK버튼 누른 경우만 처리
	if (fileDlg.DoModal() == IDOK) {
		SetDlgItemText(IDC_EDIT_PATH, fileDlg.GetPathName());		// 전체 경로 + 파일이름


		// File 처리
		FILE* pFile = NULL;
		CString strContent;

		// File Encoding : 3가지 (2번 3번이 Unicode)
		// 1) ANSI(EUC-KR, CP949 등) : 영문 1byte, 한글/한자 2byte									==> 윈도에서 작성된 문서(The system default Windows ANSI code page)
		// 2) 유니코드 : 모두 2byte, 전세계 모든 문자 표현 가능, Web문서 작성 불가
		// 3) UTF-8 : 영문 1byte, 한글/한자 등 3byte, 전세계 모든 문자 표현 가능, Web문서 표준		==> 리눅스/오픈소스/웹 기본값
		// ==> 유니코드와 UTF-8의 관계 : https://jeongdowon.medium.com/unicode%EC%99%80-utf-8-%EA%B0%84%EB%8B%A8%ED%9E%88-%EC%9D%B4%ED%95%B4%ED%95%98%EA%B8%B0-b6aa3f7edf96
		// Big-Endian vs Little-Endian : https://jhnyang.tistory.com/172


		// 파일 이름=UNICODE일 때 파일열기(에러 없으면 0)
		if (_wfopen_s(&pFile, fileDlg.GetPathName(), L"rt") == 0) {

			// 파일 내용 1줄 받아올 buffer
			char buff[1024];
			int len;
			wchar_t strConverted[1024];

			while (fgets(buff, 1024, pFile) != NULL) {							// fgets(): 한줄씩 읽어오기, 더이상 읽을 줄이 없으면 NULL 반환


				// 1. ANSI 디코딩: MultiByteToWideChar함수에 CP_ACP 사용 ==> 현재 CPP파일 열었을 때 한글 안깨짐(=원래 파일이 ANSI로 인코딩됨)
				//len = MultiByteToWideChar(CP_ACP, 0, buff, -1, NULL, 0);		// ANSI로 변환할 때 생기는 총 문자열 길이(한줄) 계산	(인자 6개 중 맨끝 2개)
				//MultiByteToWideChar(CP_ACP, 0, buff, -1, strConverted, len);	// 변환 후 생긴 문자열(한줄)을 strConverted에 넣기		(인자 6개 중 맨끝 2개)
				//strContent += strConverted;


				// 2. UTF-8 디코딩: MultiByteToWideChar함수에 CP_UTF8 사용 ==> 현재 CPP파일 열었을 때 한글 깨짐(=원래 파일이 UTF-8로 인코딩되지 않았음)
				len = MultiByteToWideChar(CP_UTF8, 0, buff, -1, NULL, 0);		// UTF-8로 변환할 때 생기는 총 문자열 길이(한줄) 계산	(인자 6개 중 맨끝 2개)
				MultiByteToWideChar(CP_UTF8, 0, buff, -1, strConverted, len);	// 변환 후 생긴 문자열(한줄)을 strConverted에 넣기		(인자 6개 중 맨끝 2개)
				strContent += strConverted;



				//strContent += buff;												// buff=ASCII, CString의 +연산자는 buff의 ASCII를 유니코드로 변환
			}
			strContent.Replace(L"\n", L"\r\n");									// 줄바꿈 수정
			SetDlgItemText(IDC_EDIT_MAIN, strContent);

			fclose(pFile);
		}
	}
}


// 파일 저장하기 버튼
void CM09NotepadDlg::OnBnClickedButtonSavefile()
{
	wchar_t fileExtFilter[] = L"모든 파일(*.*)|*.*|C++소스파일(*.cpp)|*.cpp|C++헤더파일(*.h)|*.h|텍스트파일(*.txt)|*.txt||";	// 확장자 필터 = L"보여질부분|실제확장자조건|......||"
	CFileDialog fileDlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR | OFN_OVERWRITEPROMPT, fileExtFilter);				// OFN_OVERWRITEPROMPT = 덮어쓰기 경고
	//			fileDlg(TRUE=파일열기 FALSE=파일저장, 기본확장자(저장할때 확장자 지정하지 않으면 뒤에 자동 붙음), 기본파일이름, 속성Flags, 확장자filter문자열);
	//fileDlg.m_ofn.nFilterIndex = 4;		// 파일 대화상자가 열렸을 때 기본 filter 선택(0=선택안함, 1=fileExtFilter배열의 1번째, 2=fileExtFilter배열의 2번째, ...)


	// 파일 대화상자에서 OK버튼 누른 경우만 처리
	if (fileDlg.DoModal() == IDOK) {
		SetDlgItemText(IDC_EDIT_PATH, fileDlg.GetPathName());


		// 파일 처리
		FILE* pFile = NULL;
		CString strContent;

		// 파일 이름=UNICODE일 때 파일열기(에러 없으면 0)
		if (_wfopen_s(&pFile, fileDlg.GetPathName(), L"wt") == 0) {
			GetDlgItemText(IDC_EDIT_MAIN, strContent);
			strContent.Replace(L"\r\n", L"\n");

			// ANSI로 저장 (현재는 UTF-8로 열려있다고 가정)
			int len = WideCharToMultiByte(CP_ACP, 0, strContent, -1, NULL, 0, NULL, NULL);		// ANSI로 변환할 때 생기는 총 문자열 길이(전체) 계산
			char* p = new char[len];															// 내용 전체를 담을 char 배열 (커야 하므로 동적 생성)
			WideCharToMultiByte(CP_ACP, 0, strContent, -1, p, len, NULL, NULL);

			// 파일에 쓰기
			fwrite(p, len, 1, pFile);
			delete[] p;

			fclose(pFile);
		}
	}
}


void CM09NotepadDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//CDialogEx::OnOK();
}


void CM09NotepadDlg::OnBnClickedCancel()
{
	// 종료하시겠습니까 물어봄
	if (MessageBox(L"프로그램을 종료하시겠습니까?", L"확인", MB_OKCANCEL | MB_ICONINFORMATION) == IDOK) {
		CDialogEx::OnCancel();
	}
	
}
