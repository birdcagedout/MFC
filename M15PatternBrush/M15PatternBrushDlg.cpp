﻿
// M15PatternBrushDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M15PatternBrush.h"
#include "M15PatternBrushDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM15PatternBrushDlg 대화 상자



CM15PatternBrushDlg::CM15PatternBrushDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M15PATTERNBRUSH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM15PatternBrushDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM15PatternBrushDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CM15PatternBrushDlg 메시지 처리기

BOOL CM15PatternBrushDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.



	// 초기화
	CBitmap myBMP, numBMP;
	myBMP.LoadBitmap(IDB_BITMAP_IMG);
	numBMP.LoadBitmap(IDB_BITMAP_NUM);

	m_myBrush.CreatePatternBrush(&myBMP);
	m_numBrush.CreatePatternBrush(&numBMP);

	/*
	CClientDC dc(this);
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	memDC.SelectObject(&myBMP);


	dc.BitBlt(0, 0, 48, 48, &memDC, 0, 0, SRCCOPY);
	*/


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM15PatternBrushDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{
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
		/*
		CBrush *pOldBrush = dc.SelectObject(&m_numBrush);

		dc.Rectangle(0, 0, 200, 200);
		dc.SelectObject(pOldBrush);
		*/
		dc.FillSolidRect(0, 0, 200, 48, RGB(218, 218, 218));


		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM15PatternBrushDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM15PatternBrushDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);

	CBrush* pOldBrush = dc.SelectObject(&m_myBrush);
	dc.SetBrushOrg(point.x - 25, point.y - 25);
	dc.Rectangle(point.x - 25, point.y - 25, point.x + 25, point.y + 25);
	dc.SelectObject(pOldBrush);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CM15PatternBrushDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON) {

		if (point.x<=200 && point.y<=48) {
			CClientDC dc(this);

			CBrush* pOldBrush = dc.SelectObject(&m_numBrush);
			CPen* pOldPen = (CPen*)dc.SelectStockObject(NULL_PEN);
			dc.Rectangle(point.x - 5, point.y - 5, point.x + 5, point.y + 5);


			dc.SelectObject(pOldBrush);
			dc.SelectObject(pOldPen);
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}