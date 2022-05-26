
// M02CalculatorDlg.h: 헤더 파일
//

#pragma once


#define OP_NONE		0x00
#define OP_ADD		0x01
#define OP_SUB		0x02
#define OP_MUL		0x03
#define OP_DIV		0x04



// CM02CalculatorDlg 대화 상자
class CM02CalculatorDlg : public CDialogEx
{
// 생성입니다.
public:
	CM02CalculatorDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M02CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	CFont m_font;

	BYTE m_op = OP_NONE;						// 연산자 저장: 없음=0, ADD=1, SUB=2, MUL=3, DIV=4
	BOOL m_bNewOperand = TRUE;					// 새로운 피연산자 받을지 여부(TRUE: 처음, 연산자버튼 눌린 경우)
	int m_operand1 = 0;							// 첫번째 피연산자




	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	void OnSetNum(UINT a_ctrlID);
	void OnProcessOp(UINT a_ctrlID);
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonEnter();
	afx_msg void OnBnClickedButtonBackspace();
};
