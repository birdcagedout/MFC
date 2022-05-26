
// M02ListCtrlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M02ListCtrl.h"
#include "M02ListCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM02ListCtrlDlg 대화 상자



CM02ListCtrlDlg::CM02ListCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M02LISTCTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM02ListCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATA, m_listData);
}

BEGIN_MESSAGE_MAP(CM02ListCtrlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CM02ListCtrlDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDOK, &CM02ListCtrlDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CM02ListCtrlDlg 메시지 처리기

BOOL CM02ListCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	
	// 리스트에 헤더 컨트롤 추가하기 위해 LV_COLUMN 구조체에 값을 채운다. (List + View + ConFig)
	// LV_COLUMN 구조체는 report view의 1개의 column이 담고있는 정보를 가지고 있다.
	// LV_COLUMN : https://docs.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-lvcolumnw
	
	LV_COLUMN columnInfo;

	// 0. 첫번째 column은 중간 정렬 안 되므로 더미 column 하나 둔다
	columnInfo.mask = LVCF_TEXT | LVCF_WIDTH /*| LVCF_FMT*/;
	//columnInfo.fmt = LVCFMT_CENTER;							//  The alignment of the leftmost column is always LVCFMT_LEFT; it cannot be changed. 
	columnInfo.pszText = L"";
	columnInfo.cx = 0;
	m_listData.InsertColumn(0, &columnInfo);

	// 1. 이름 column 
	columnInfo.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
	columnInfo.fmt = LVCFMT_CENTER;								//  The alignment of the leftmost column is always LVCFMT_LEFT; it cannot be changed. 
	columnInfo.pszText = L"이름";
	columnInfo.cx = 70;
	m_listData.InsertColumn(1, &columnInfo);

	// 2. 전화번호 column 
	columnInfo.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
	columnInfo.fmt = LVCFMT_CENTER;
	columnInfo.pszText = L"전화번호";
	columnInfo.cx = 115;
	m_listData.InsertColumn(2, &columnInfo);

	// 3. 주소 column 
	columnInfo.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
	columnInfo.fmt = LVCFMT_CENTER;
	columnInfo.pszText = L"주소";
	columnInfo.cx = 250;
	m_listData.InsertColumn(3, &columnInfo);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM02ListCtrlDlg::OnPaint()
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
HCURSOR CM02ListCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 추가 버튼 
void CM02ListCtrlDlg::OnBnClickedButtonAdd()
{
	CString strName, strPhone, strAddr;
	GetDlgItemText(IDC_EDIT_NAME, strName);
	GetDlgItemText(IDC_EDIT_PHONE, strPhone);
	GetDlgItemText(IDC_EDIT_ADDRESS, strAddr);

	// 현재 리스트 컨트롤의 아이템 개수
	int listIndex = m_listData.GetItemCount();

	// 리스트에 항목을 넣을 때 사용하는 구조체: LV_ITEM
	// LV_ITEM: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/ns-commctrl-lvitemw
	LV_ITEM columnInfo;
	columnInfo.mask = LVIF_TEXT;
	columnInfo.iItem = listIndex;								// 행=현재추가될 위치

	// 0. 더미 column
	columnInfo.iSubItem = 0;									// 열=0
	columnInfo.pszText = L"";									// str의 연산자 오버로딩이 const wchar_t* 이므로 wchar_t*로 자동 변환 안 됨(까다로워졌음)
	m_listData.InsertItem(&columnInfo);							// **** 매우 중요 **** : 첫번째는 InsertItem, 나머지는 SetItem
	
	
	// 1. 이름
	columnInfo.iSubItem = 1;									// 열=1
	columnInfo.pszText = (wchar_t*)(const wchar_t*)strName;		// str의 연산자 오버로딩이 const wchar_t* 이므로 wchar_t*로 자동 변환 안 됨(까다로워졌음)
	m_listData.SetItem(&columnInfo);
	//m_listData.InsertItem(&columnInfo);


	// 2. 전화번호
	columnInfo.iSubItem = 2;									// 열=2
	columnInfo.pszText = (wchar_t*)(const wchar_t*)strPhone;	// str의 연산자 오버로딩이 const wchar_t* 이므로 wchar_t*로 자동 변환 안 됨(까다로워졌음)
	m_listData.SetItem(&columnInfo);


	// 3. 주소
	columnInfo.iSubItem = 3;									// 열=3
	columnInfo.pszText = (wchar_t*)(const wchar_t*)strAddr;		// str의 연산자 오버로딩이 const wchar_t* 이므로 wchar_t*로 자동 변환 안 됨(까다로워졌음)
	m_listData.SetItem(&columnInfo);
}


void CM02ListCtrlDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}
