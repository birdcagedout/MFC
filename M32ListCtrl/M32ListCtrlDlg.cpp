
// M32ListCtrlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M32ListCtrl.h"
#include "M32ListCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM32ListCtrlDlg 대화 상자



CM32ListCtrlDlg::CM32ListCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M32LISTCTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM32ListCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATA, m_dataList);
}

BEGIN_MESSAGE_MAP(CM32ListCtrlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CM32ListCtrlDlg::OnBnClickedButtonAdd)
END_MESSAGE_MAP()


// CM32ListCtrlDlg 메시지 처리기

BOOL CM32ListCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.




	// 리스트 컨트롤 헤더(컬럼) 만들기 : 리소스 속성 = "Report"
	LV_COLUMN column;
	column.mask = LVCF_TEXT | LVCF_WIDTH;		// 구조체에서 2개 정보만 쓰겠다.
	column.pszText = L"이름";
	column.cx = 100;
	m_dataList.InsertColumn(0, &column);

	column.pszText = L"전화번호";
	column.cx = 150;
	m_dataList.InsertColumn(1, &column);

	column.pszText = L"주소";
	column.cx = 250;
	m_dataList.InsertColumn(2, &column);


	// 선택되면 한줄 모두 선택
	m_dataList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM32ListCtrlDlg::OnPaint()
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
HCURSOR CM32ListCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM32ListCtrlDlg::OnBnClickedButtonAdd()
{
	CString strName, strPhone, strAddress;
	GetDlgItemText(IDC_EDIT_NAME, strName);
	GetDlgItemText(IDC_EDIT_PHONE, strPhone);
	GetDlgItemText(IDC_EDIT_ADDRESS, strAddress);


	int itemIndex = m_dataList.GetItemCount();			// 리스트박스의 마지막에 추가하기 위해 현재 개수 얻어와서 아이템의 인덱스로 사용


	LV_ITEM item;
	item.mask = LVIF_TEXT;
	item.iItem = itemIndex;

	item.pszText = (wchar_t*)strName.GetString();
	item.iSubItem = 0;
	m_dataList.InsertItem(&item);						// 이름		: 첫번째는 InsertItem

	item.pszText = (wchar_t*)strPhone.GetString();
	item.iSubItem = 1;
	m_dataList.SetItem(&item);							// 전화번호	: 두번째부터는 SetItem

	item.pszText = (wchar_t*)strAddress.GetString();
	item.iSubItem = 2;
	m_dataList.SetItem(&item);							// 주소		: 두번째부터는 SetItem

}
