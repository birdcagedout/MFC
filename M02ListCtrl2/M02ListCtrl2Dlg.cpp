
// M02ListCtrl2Dlg.cpp: 구현 파일
// 
// List 컨트롤 구현 응용 : https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=hhhighhh&logNo=220752397721

#include "pch.h"
#include "framework.h"
#include "M02ListCtrl2.h"
#include "M02ListCtrl2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM02ListCtrl2Dlg 대화 상자



CM02ListCtrl2Dlg::CM02ListCtrl2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M02LISTCTRL2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM02ListCtrl2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATA, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CM02ListCtrl2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CM02ListCtrl2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CM02ListCtrl2Dlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUB, &CM02ListCtrl2Dlg::OnBnClickedButtonSub)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_DATA, &CM02ListCtrl2Dlg::OnLvnItemchangedListData)
	ON_BN_CLICKED(IDC_BUTTON_MOD, &CM02ListCtrl2Dlg::OnBnClickedButtonMod)
END_MESSAGE_MAP()


// CM02ListCtrl2Dlg 메시지 처리기

BOOL CM02ListCtrl2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	// List 컨트롤에 style 추가/변경하기
	// 1) Report 스타일로 바꾸기(맨하위 2bit)
	// 2) singleline select 스타일 변경하기(3번째 bit)
	CListCtrl* p = (CListCtrl*)GetDlgItem(IDC_LIST_DATA);
	LONG wndStyle = GetWindowLong(p->m_hWnd, GWL_STYLE);
	wndStyle = (wndStyle & ~0x0003) | LVS_REPORT;						// 맨 뒤에 필요한 style 넣으면 됨 : LVS_ICON=0, LVS_REPORT=1, LVS_SMALLICON=2, LVS_LIST=3
	//wndStyle = wndStyle & ~LVS_SINGLESEL;								// 항상 한줄 선택 style (TRUE/FALSE)
	SetWindowLong(p->m_hWnd, GWL_STYLE, wndStyle); 

	
	// List 컨트롤 초기화 작업
	// List 컨트롤 크기에 따라 Column을 배분한다.
	CRect r;
	m_listCtrl.GetWindowRect(&r);
	m_listCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);		// 엑셀스타일 그리드라인 + 한줄 전체 셀렉션 ==> 항상 필수 style

	m_listCtrl.InsertColumn(0, L"연번", LVCFMT_LEFT, r.Width() * 0.15);
	m_listCtrl.InsertColumn(1, L"이름", LVCFMT_CENTER, r.Width() * 0.3);
	m_listCtrl.InsertColumn(2, L"연락처", LVCFMT_CENTER, r.Width() * 0.55);


	// List 컨트롤 작업을 위한 예시 입력
	SetDlgItemText(IDC_EDIT_NAME, L"0길동");
	SetDlgItemText(IDC_EDIT_PHONE, L"010-1111-2222");
	OnBnClickedButtonAdd();

	SetDlgItemText(IDC_EDIT_NAME, L"1성엽");
	SetDlgItemText(IDC_EDIT_PHONE, L"010-2222-3333");
	OnBnClickedButtonAdd();

	SetDlgItemText(IDC_EDIT_NAME, L"2삿갓");
	SetDlgItemText(IDC_EDIT_PHONE, L"010-3333-4444");
	OnBnClickedButtonAdd();

	SetDlgItemText(IDC_EDIT_NAME, L"3대갈");
	SetDlgItemText(IDC_EDIT_PHONE, L"010-4444-5555");
	OnBnClickedButtonAdd();

	SetDlgItemText(IDC_EDIT_NAME, L"");
	SetDlgItemText(IDC_EDIT_PHONE, L"");


	// 작업표시줄 높이 구하기
	HWND hWndTrayWnd = ::FindWindow(L"Shell_TrayWnd", NULL);
	RECT rect;
	if (hWndTrayWnd) {
		::GetWindowRect(hWndTrayWnd, &rect);
		CString title;
		title.Format(L"작업표시줄 길이: %d, 높이: %d", rect.right - rect.left, rect.bottom - rect.top);		// 1920, 40
		SetWindowText(title);
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM02ListCtrl2Dlg::OnPaint()
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
HCURSOR CM02ListCtrl2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM02ListCtrl2Dlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CM02ListCtrl2Dlg::OnBnClickedButtonAdd()
{
	// 개수, 이름, 연락처 가져오기
	int index = m_listCtrl.GetItemCount();
	CString strNum, strName, strPhone;
	strNum.Format(L"%d", index + 1);
	GetDlgItemText(IDC_EDIT_NAME, strName);
	GetDlgItemText(IDC_EDIT_PHONE, strPhone);

	// List 컨트롤에 추가
	m_listCtrl.InsertItem(index, strNum);											// 첫번째는 InsertItem()
	//m_listCtrl.SetItem(index, 1, LVIF_TEXT, strName, NULL, NULL, NULL, NULL);		// 두번째부터는
	//m_listCtrl.SetItem(index, 2, LVIF_TEXT, strPhone, NULL, NULL, NULL, NULL);	// SetItem()
	m_listCtrl.SetItemText(index, 1, strName);										// Text만 넣을 때는
	m_listCtrl.SetItemText(index, 2, strPhone);										// SetItemText()
}


// 선택된 아이템(행) 모두 삭제하기
// 첫번째(index=0) 아이템을 삭제하면 두번째 아이템의 index=0이 되므로
// 여러개를 삭제할 때는 매번 ==> 첫번째 아이템 찾고 하나 지우고, 첫번째 아이템 찾고 하나 지워야 한다.
void CM02ListCtrl2Dlg::OnBnClickedButtonSub()
{
	// 선택된 행의 위치 찾기 : 없으면 NULL
	// GetFirstSelectedItemPosition()의 핵심:	**선택한 순서는 중요하지 않고**, 선택된 것들 중 index가 작은 것부터 시작
	//											0,1,2번째 item을 선택하면 => 0,1,2 순서로 저장됨
	//											2,1,0번째 item을 선택해도 => 0,1,2 순서로 저장됨
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	
	// 삭제
	while (pos != NULL) {
		int index = m_listCtrl.GetNextSelectedItem(pos);		// 그 위치 item 꺼내고 pos++ until pos == NULL
		m_listCtrl.DeleteItem(index);							// 하나 지울 때마다 item들의 index 바뀜
		pos = m_listCtrl.GetFirstSelectedItemPosition();
	}
}



// List 컨트롤의 선택 항목이 바뀌었을 때 이벤트 핸들러
// 주의: 이전 선택항목을 떠났을 때도 호출되고, 새로운 항목이 선택되어도 호출됨
// ==> 새로운 항목이 선택되었을 때만(LVIS_SELECTED) 처리 필요
void CM02ListCtrl2Dlg::OnLvnItemchangedListData(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW p = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);	// 맨나중(가장 최근)에 선택된 item을 가리키는 포인터

	if (p->uNewState & LVIS_SELECTED) {
		CString strName, strPhone;
		strName = m_listCtrl.GetItemText(p->iItem, 1);			// 현재 선택된 item의 1번 column 문자열
		strPhone = m_listCtrl.GetItemText(p->iItem, 2);			// 현재 선택된 item의 2번 column 문자열

		SetDlgItemText(IDC_EDIT_NAME, strName);
		SetDlgItemText(IDC_EDIT_PHONE, strPhone);

		// 맨나중 선택된 item의 index를 멤버변수에 저장
		m_lastSelectedItemIndex = p->iItem;
	}

	*pResult = 0;
}


void CM02ListCtrl2Dlg::OnBnClickedButtonMod()
{
	// 현재 index = 맨나중에 선택한 item의 index = m_lastSelectedItemIndex
	CString strName, strPhone;
	GetDlgItemText(IDC_EDIT_NAME, strName);
	GetDlgItemText(IDC_EDIT_PHONE, strPhone);
	
	m_listCtrl.SetItemText(m_lastSelectedItemIndex, 1, strName);											// 값을 바꾸는 것이므로 InsertItem() 아님
	m_listCtrl.SetItemText(m_lastSelectedItemIndex, 2, strPhone);
}
