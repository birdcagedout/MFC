
// M26FileFolder1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M26FileFolder1.h"
#include "M26FileFolder1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM26FileFolder1Dlg 대화 상자



CM26FileFolder1Dlg::CM26FileFolder1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M26FILEFOLDER1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM26FileFolder1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LSHOW, m_listboxLeft);
	DDX_Control(pDX, IDC_LIST_RSHOW, m_listboxRight);
}

BEGIN_MESSAGE_MAP(CM26FileFolder1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_DBLCLK(IDC_LIST_LSHOW, &CM26FileFolder1Dlg::OnLbnDblclkListLshow)
	ON_LBN_DBLCLK(IDC_LIST_RSHOW, &CM26FileFolder1Dlg::OnLbnDblclkListRshow)
	ON_BN_CLICKED(IDC_BUTTON_R_NEW_FOLDER, &CM26FileFolder1Dlg::OnBnClickedButtonRNewFolder)
END_MESSAGE_MAP()


// CM26FileFolder1Dlg 메시지 처리기

BOOL CM26FileFolder1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	
	// 현재 작업경로 얻어옴
	wchar_t fullPath[MAX_PATH];
	int pathLen = GetCurrentDirectory(MAX_PATH, fullPath);

	fullPath[pathLen] = '\\';
	fullPath[pathLen + 1] = NULL;

	SetDlgItemText(IDC_EDIT_LPATH, fullPath);
	SetDlgItemText(IDC_EDIT_RPATH, fullPath);

	FileDirectoryToListbox(&m_listboxLeft, fullPath);
	FileDirectoryToListbox(&m_listboxRight, fullPath);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}




void CM26FileFolder1Dlg::FileDirectoryToListbox(CListBox* a_pListBox, CString a_strPath)
{
	// 기존 목록 제거
	a_pListBox->ResetContent();
	
	// 변수 초기화: MFC 방식
	//m_listboxLeft.Dir(DDL_ARCHIVE | DDL_HIDDEN | DDL_READONLY | DDL_DIRECTORY /*| DDL_DRIVES*/, L".\\*.*");

	// 변수 초기화: API 방식
	WIN32_FIND_DATA fileData;
	HANDLE hItemList = FindFirstFile(a_strPath + L"*.*", &fileData);		// 파일이름 string 끝에 trailing \ 없어야 됨

	if (hItemList != INVALID_HANDLE_VALUE) {

		do {
			// 파일 리스트에서 .(현재폴더) 제거
			if (fileData.cFileName[0] == '.' && fileData.cFileName[1] == NULL) {
				continue;
			}
			else {
				CString filename = fileData.cFileName;

				// 폴더이면 앞뒤로 대괄호 + 맨앞에 추가
				if ((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != NULL) {
					filename = L"[" + filename + L"]";

					// 이미 저장된 폴더들 중에서는 마지막에 넣는다
					int i = a_pListBox->GetCount();
					for (; i > 0; i--) {
						CString strItem;
						a_pListBox->GetText(i - 1, strItem);
						if (strItem.GetString()[0] == L'[') {
							break;
						}
						else {
							continue;
						}
					}	
					a_pListBox->InsertString(i, filename);
				}
				// 파일이면 그대로 + 맨 뒤에 추가
				else {
					a_pListBox->InsertString(-1, filename);
				}
			}
		} while (FindNextFile(hItemList, &fileData) == TRUE);	// 해당 경로의 모든 파일/디렉토리 찾음

		FindClose(hItemList);
	}
	else {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
			MessageBox(L"파일을 찾을 수 없습니다.", L"에러 발생", MB_OK | MB_ICONERROR);
		}
	}

}







// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM26FileFolder1Dlg::OnPaint()
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
HCURSOR CM26FileFolder1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CM26FileFolder1Dlg::ChangeDirectory(bool isLeft) {
	
	// 왼쪽 or 오른쪽 선택
	CListBox* pListBox;
	CEdit* pEditPath;
	if (isLeft == true) {
		pListBox = &m_listboxLeft;
		pEditPath = (CEdit*)GetDlgItem(IDC_EDIT_LPATH);
	}
	else {
		pListBox = &m_listboxRight;
		pEditPath = (CEdit*)GetDlgItem(IDC_EDIT_RPATH);
	}

	int index = pListBox->GetCurSel();
	CString strItem, strCurrentPath;
	pListBox->GetText(index, strItem);

	// 폴더만 골라서
	if (strItem.GetString()[0] == L'[') {

		// item에서 좌우 대괄호 삭제
		strItem.TrimLeft(L'[');
		strItem.TrimRight(L']');
		pEditPath->GetWindowTextW(strCurrentPath);

		// 상위 디렉토리인 경우
		if (strItem == L"..") {
			strCurrentPath.TrimRight(L'\\');				// 맨끝에 붙은 \ 제거

			int pos = strCurrentPath.ReverseFind(L'\\');	// 그 다음번 \의 index
			strCurrentPath.Truncate(pos + 1);

			/*
			for (int i = strCurrentPath.GetLength(); i > 0; i--) {
				if (strCurrentPath.GetString()[i - 1] != L'\\') {
					strCurrentPath.Truncate(i - 1);
				}
				else {
					break;
				}
			}
			*/
		}
		// 하위 디렉토리인 경우
		else {
			strCurrentPath = strCurrentPath + strItem + L'\\';
		}

		pEditPath->SetWindowTextW(strCurrentPath);
		FileDirectoryToListbox(pListBox, strCurrentPath);
	}
}


// 왼쪽 ListBox에서 아이템에 더블클릭
void CM26FileFolder1Dlg::OnLbnDblclkListLshow()
{
	ChangeDirectory(true);
}


// 오른쪽 ListBox에서 아이템에 더블클릭
void CM26FileFolder1Dlg::OnLbnDblclkListRshow()
{
	ChangeDirectory(false);
}


// 오른쪽 "새폴더" 생성
void CM26FileFolder1Dlg::OnBnClickedButtonRNewFolder()
{
	// 새폴더 이름받는 대화상자 추가


}
