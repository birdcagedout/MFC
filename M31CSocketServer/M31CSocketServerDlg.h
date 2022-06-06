
// M31CSocketServerDlg.h: 헤더 파일
//

#pragma once

#include "CServerSocket.h"

// CM31CSocketServerDlg 대화 상자
class CM31CSocketServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CM31CSocketServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M31CSOCKETSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	CServerSocket m_serverSock;

	CListBox m_eventList;					// Listbox 컨트롤 연결 변수

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	void AddEventString(const wchar_t* str);
};
