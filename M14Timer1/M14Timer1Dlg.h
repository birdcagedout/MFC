﻿
// M14Timer1Dlg.h: 헤더 파일
//

#pragma once


#define MAX_COUNT	200

typedef struct _MyCircle {
	int x, y;		// 중점 좌표
	int r;			// 반지름
	COLORREF c;		// 색상
} MyCircle;




// CM14Timer1Dlg 대화 상자
class CM14Timer1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CM14Timer1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_M14TIMER1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	MyCircle m_circleList[MAX_COUNT];
	CDC m_memDC;
	CBitmap m_memBMP;
	int m_width, m_height;	


	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};
