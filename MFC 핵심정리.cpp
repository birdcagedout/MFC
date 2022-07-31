// 1. MFC App에서 InitInstance() 간소화

BOOL CM02ListboxApp::InitInstance()
{
	CWinApp::InitInstance();


	CM02ListboxDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}


// 2. 작업표시줄 높이 구하기: 핸들 구해서 높이 구하기
HWND hWndTrayWnd = ::FindWindow(L"Shell_TrayWnd", NULL);
RECT rect;
if (hWndTrayWnd) {
	::GetWindowRect(hWndTrayWnd, &rect);
	CString title;
	title.Format(L"작업표시줄 길이: %d, 높이: %d", rect.right - rect.left, rect.bottom - rect.top);		// 1920, 40
	SetWindowText(title);
}


// 3. 파일 읽기
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



// 4. 파일 쓰기
// _wfopen_s() : https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fopen-s-wfopen-s?view=msvc-170

// 파일이름 만들기
CString strFileName, strContent;
strFileName.Format(L"%04d%02d%02d.dat", currentDateTime.wYear, currentDateTime.wMonth, currentDateTime.wDay);

// 파일로 저장
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



// 5. 시간 함수

time_t t = time(NULL);			// 64bit, 현재시간(1970년 기준 경과시간)을 초단위로 반환 (2049년에 32bit int값 overflow 예정)
tm dt;							// year + 1900 = 현재년, mon[0] = 1월, wday[0] = SUN
localtime_s(&dt, &t);			// localtime()=depricated, 반드시 이 호출형태 준수할 것. UTC+9

CString str;
str.Format(L"%04d년 %02d월 %02d일 %02d:%02d:%02d", dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday, dt.tm_hour, dt.tm_min, dt.tm_sec);



// 6. 현재 윈도 크기를 변경
CRect wr, cr;
GetWindowRect(wr);
GetClientRect(cr);
int margin_x = wr.Width() - cr.Width();
int margin_y = wr.Height() - cr.Height();
//MoveWindow(wr.left, wr.top, m_img.GetWidth() + margin_x, m_img.GetHeight() + margin_y, TRUE);			// MoveWindow로 윈도 위치, 크기 바꾸는 방법
SetWindowPos(NULL, 0, 0, m_img.GetWidth() + margin_x, m_img.GetHeight() + margin_y, SWP_NOMOVE);		// SWP_NOMOVE일 때 시작위치 0,0은 무시



// 7. BitBlt계열에서 이미지 출력이 이상할 때
dc.SetStretchBltMode(COLORONCOLOR);		// JPG 파일이 깨진 것 같을 때 (비율이 다를 때 호출되는 StretchBitBlt의 모드 초기값 변경)




// 8. File Dialog 설정
wchar_t filter[] = L"모든파일 (*.*)|*.*|PNG파일 (*.PNG)|*.PNG|JPG파일 (*.JPG)|*.JPG||";
CFileDialog fileDlg(TRUE, L"JPG", L"*.JPG", OFN_HIDEREADONLY | OFN_NOCHANGEDIR, filter);	// OFN_HIDEREADONLY = 대화상자 하단에 "읽기전용으로 열기"라는 checkbox를 숨기기 (최근 대화상자는 없어도 원래 안 보임)
fileDlg.m_ofn.nFilterIndex = 2;


// 9. 선택한 파일명으로 CImage 가져오기
if (fileDlg.DoModal() == IDOK) {
	m_img.Load(fileDlg.GetPathName());		// 경로를 포함한 이미지 파일명
}



// 10. CPtrList / CObList 사용하기 : CObject에서 상속받은 클래스들은 CObList에 넣고, 나머지는 CPtrList에 넣는다.
// 1) 사용할 때
CUserSocket* pUserSock = new CUserSocket;
m_userSocketList.AddTail(pUserSock);

// 2) 제거할 때
CUserSocket* p;
POSITION pos = m_userSocketList.GetHeadPosition();

while (pos != NULL) {
	p = (CUserSocket*)m_userSocketList.GetNext(pos);
	delete p;
	m_userSocketList.RemoveHead();
}




// 11. GetDlgItemText에 CString을 사용하지 않을 때(=문자열 길이를 명시해야 할 때)
// ==> 길이는 character의 개수이지 byte가 아니다.
// ==> 길이는 NULL을 포함한 길이이다.
wchar_t str[3] = { 0, };
GetDlgItemText(IDC_EDIT_VALUE, str, 2);		==> ABC라고 적었을 때 str에는 L'A' + NULL 만 들어간다. (NULL을 포함하여 2개)




// 12. (클래스 마법사 쓰지 않고) 이벤트 핸들러 수동으로 추가하기
1) .h 파일에 메시지 정의
#define MSG_THREAD_ENDED	27001

2) .h 파일 클래스에 멤버 함수 정의
public:
	afx_msg LRESULT OnMsgThreadEnded(WPARAM isKilled, LPARAM pThreadData);
	
3) .cpp 파일 메시지맵에 ON_MESSAGE()로 함수 추가
BEGIN_MESSAGE_MAP(CM33Thread2Dlg, CDialogEx)
	ON_WM_PAINT()
	...
	ON_MESSAGE(MSG_THREAD_ENDED, &CM33Thread2Dlg::OnMsgThreadEnded)
END_MESSAGE_MAP()

4) .cpp 파일에 함수 정의 구현
afx_msg LRESULT CM33Thread2Dlg::OnMsgThreadEnded(WPARAM isKilled, LPARAM pThreadData)
{
	ThreadData* pData = (ThreadData*)pThreadData;
	return 0;
}