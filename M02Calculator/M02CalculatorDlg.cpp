
// M02CalculatorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M02Calculator.h"
#include "M02CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM02CalculatorDlg 대화 상자



CM02CalculatorDlg::CM02CalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M02CALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM02CalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM02CalculatorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CM02CalculatorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CM02CalculatorDlg::OnBnClickedCancel)
	ON_COMMAND_RANGE(IDC_BUTTON0, IDC_BUTTON9, OnSetNum)						// 숫자 0 ~ 9버튼: OnSetNum함수가 처리한다.
	ON_COMMAND_RANGE(IDC_BUTTON_OP_ADD, IDC_BUTTON_OP_DIV, OnProcessOp)			// 연산자 버튼: OnProcessOp함수가 처리한다.
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CM02CalculatorDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_ENTER, &CM02CalculatorDlg::OnBnClickedButtonEnter)
	ON_BN_CLICKED(IDC_BUTTON_BACKSPACE, &CM02CalculatorDlg::OnBnClickedButtonBackspace)
END_MESSAGE_MAP()


// CM02CalculatorDlg 메시지 처리기

BOOL CM02CalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// 표시기의 폰트 키우기
	m_font.CreatePointFont(300, L"맑은 고딕");		// 12포인트 ==> 120
	GetDlgItem(IDC_EDIT_SHOW)->SetFont(&m_font);

	// 표시기의 초기값=0
	SetDlgItemInt(IDC_EDIT_SHOW, 0);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM02CalculatorDlg::OnPaint()
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
HCURSOR CM02CalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM02CalculatorDlg::OnBnClickedOk()
{
	// 엔터를 눌렀을 때 프로그램 종료되는 것을 방지 ==> 주석처리
	//CDialogEx::OnOK();
}


void CM02CalculatorDlg::OnBnClickedCancel()
{
	// ESC를 눌렀을 때 프로그램이 종료되는 것을 방지하기 위해 아래를 주석처리하면 
	// 시스템 메뉴의 Close버튼을 눌러도 종료되지 않으므로 놔둔다.

	// 폰트 지우기
	m_font.DeleteObject();

	CDialogEx::OnCancel();
}


//============================================================ 계산기 함수 ============================================================

// 숫자버튼 처리함수
void CM02CalculatorDlg::OnSetNum(UINT a_ctrlID)
{
	//원래 표시기에 있던 숫자 (cf. 현재 들어온 숫자 = a_ctrlID - IDC_BUTTON0)
	int prevNum = GetDlgItemInt(IDC_EDIT_SHOW);

	
	if (m_bNewOperand == FALSE) {
		SetDlgItemInt(IDC_EDIT_SHOW, prevNum * 10 + (a_ctrlID - IDC_BUTTON0));		// 표시기에 숫자 표시
	}
	else {
		m_bNewOperand = FALSE;
		SetDlgItemInt(IDC_EDIT_SHOW, (a_ctrlID - IDC_BUTTON0));
	}
	
}

// 연산자버튼 처리함수
void CM02CalculatorDlg::OnProcessOp(UINT a_ctrlID)
{
	// 입력된 연산자 종류 저장
	m_op = a_ctrlID - IDC_BUTTON_OP_ADD + 1;

	// 새로운 피연산자 아직 받지 않는 상태인 경우(=연산자가 이번에 최초로 눌린 경우)에만 ==> 새로운 피연산자=TRUE, 처음 피연산자=저장
	if (m_bNewOperand == FALSE) {
		m_bNewOperand = TRUE;
		m_operand1 = GetDlgItemInt(IDC_EDIT_SHOW);
	}
	
}


// Clear버튼 처리함수
void CM02CalculatorDlg::OnBnClickedButtonClear()
{
	SetDlgItemInt(IDC_EDIT_SHOW, 0);
	m_bNewOperand = TRUE;
}


// Backspace버튼 처리함수
void CM02CalculatorDlg::OnBnClickedButtonBackspace()
{
	int prevNum = GetDlgItemInt(IDC_EDIT_SHOW);
	int nowNum = (int)(prevNum / 10);

	if (nowNum == 0) {
		m_bNewOperand = TRUE;
	}
	else {
		m_bNewOperand = FALSE;
	}
	SetDlgItemInt(IDC_EDIT_SHOW, nowNum);
	
}


// Enter버튼 처리함수
void CM02CalculatorDlg::OnBnClickedButtonEnter()
{
	int operand2 = GetDlgItemInt(IDC_EDIT_SHOW);
	int result = 0;

	if (m_op == OP_NONE) {
		return;
	}
	else  if (m_op == OP_ADD) {
		result = (int)(m_operand1 + operand2);
	}
	else if (m_op == OP_SUB) {
		result = (int)(m_operand1 - operand2);
	}
	else if (m_op == OP_MUL) {
		result = (int)(m_operand1 * operand2);
	}
	else if (m_op == OP_DIV) {
		if (operand2 != 0) {
			result = (int)(m_operand1 / operand2);
		}
	}

	SetDlgItemInt(IDC_EDIT_SHOW, result);

	// 현재의 결과 = operand1
	m_operand1 = result;

	// 연산자 = 없음
	m_op = OP_NONE;

	// 새로운 operand를 받을 상태는 아니다
	m_bNewOperand = FALSE;
}

