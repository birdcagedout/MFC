
// M03MovePolygonDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "M03MovePolygon.h"
#include "M03MovePolygonDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// CM03MovePolygonDlg dialog

CM03MovePolygonDlg::CM03MovePolygonDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M03MOVEPOLYGON_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// 클릭 상태변수
	m_isClicked = OBJ_NONE;

	// 개체 개수
	m_objCount = OBJ_COUNT;

	// Z-order 관리객체: 개체는 총3개
	// 최상위 순서대로 : 원 - 별 - 사각형
	m_pZ = new CMyZOrder;


	// 정사각형 초기화
	m_square.SetRect(10, 10, 100, 100);

	// 직사각형 초기화
	m_rect.SetRect(100, 100, 300, 200);


	// 별모양 좌표 : 시작점 - 다음점 - 다음점 - ... - 끝점(=시작점)
	POINT starPoints[11] = { {101,0}, {77,77}, {0,77}, {62,125}, {39,201}, {101,153}, {163,201}, {138,125}, {201,77}, {124,77}, {101,0} };

	// 별모양 테두리 브러시
	m_starBrush.CreateSolidBrush(RGB(0, 0, 0));

	// 별모양 내부영역
	m_starRegion.CreatePolygonRgn(starPoints, 11, ALTERNATE);		// 별모양의 안쪽영역


	// 원모양 테두리 브러시
	m_circleBrush.CreateSolidBrush(RGB(0, 0, 0));

	// 원모양 내부영역
	m_circleRegion.CreateEllipticRgn(100, 100, 250, 250);
}

void CM03MovePolygonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM03MovePolygonDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CM03MovePolygonDlg message handlers

BOOL CM03MovePolygonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	return TRUE;  // return TRUE  unless you set the focus to a control
}







//void CM03MovePolygonDlg::PaintObject(CPaintDC *a_hDC, int a_objID)
//{
//	if (a_objID == OBJ_SQUARE) {
//		a_hDC->Rectangle(m_rect);
//	}
//	else if (a_objID == OBJ_STAR) {
//		a_hDC->PaintRgn(&m_starRegion);
//		a_hDC->FrameRgn(&m_starRegion, &m_starBrush, 1, 1);
//	}
//	else if (a_objID == OBJ_CIRCLE) {
//		a_hDC->PaintRgn(&m_circleRegion);
//		a_hDC->FrameRgn(&m_circleRegion, &m_circleBrush, 1, 1);
//	}
//}






// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CM03MovePolygonDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		// 최하위 개체부터 하나씩 그리기
		for (int i = m_objCount-1; i >= 0; i--) {
			//PaintObject(&dc, m_pZ->GetItem(i));

			int currentObject = m_pZ->GetItem(i);

			if (currentObject == OBJ_SQUARE) {
				dc.Rectangle(m_square);
			}
			else if (currentObject == OBJ_RECTANGLE) {
				dc.Rectangle(m_rect);
			}
			else if (currentObject == OBJ_STAR) {
				dc.PaintRgn(&m_starRegion);
				dc.FrameRgn(&m_starRegion, &m_starBrush, 1, 1);
			}
			else if (currentObject == OBJ_CIRCLE) {
				dc.PaintRgn(&m_circleRegion);
				dc.FrameRgn(&m_circleRegion, &m_circleBrush, 1, 1);
			}
		}

		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CM03MovePolygonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




int CM03MovePolygonDlg::GetClickedObjectIndex(CPoint point)
{
	// 최상위 개체부터 순서대로 확인
	for (int i = 0; i < m_objCount; i++)
	{
		int nObject = m_pZ->GetItem(i);
		
		// 정사각형이면
		if (nObject == OBJ_SQUARE) {
			if (m_square.PtInRect(point) == TRUE) {
				return i;
			}
		}
		// 직사각형이면
		else if (nObject == OBJ_RECTANGLE) {
			if (m_rect.PtInRect(point) == TRUE) {
				return i;
			}
		}
		// 별모양이면
		else if (nObject == OBJ_STAR) {
			if (m_starRegion.PtInRegion(point) == TRUE) {
				return i;
			}
		}
		// 원모양이면
		else if (nObject == OBJ_CIRCLE) {
			if (m_circleRegion.PtInRegion(point) == TRUE) {
				return i;
			}
		}
	}

	return OBJ_NONE_INDEX;
}





void CM03MovePolygonDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	int clickedObjIndex = GetClickedObjectIndex(point);

	// 아무 개체에도 클릭되지 않은 경우 ==> 아무것도 하지 않음
	if (clickedObjIndex == OBJ_NONE_INDEX) {
		return;
	}
	// 최상위 개체에 클릭된 경우 ==> 이동 준비
	else if(clickedObjIndex == 0) {

		// 사각형인 경우
		//if (m_pZ->GetItem(0) == OBJ_SQUARE) {
		//	m_isClicked = OBJ_SQUARE;
		//	
		//}
		//// 별모양인 경우
		//else if (m_pZ->GetItem(0) == OBJ_STAR) {
		//	m_isClicked = OBJ_STAR;
		//}
		//// 원모양인 경우
		//else if (m_pZ->GetItem(0) == OBJ_CIRCLE) {
		//	m_isClicked = OBJ_CIRCLE;
		//}
		m_isClicked = m_pZ->GetItem(0);
		m_prevPoint = point;
		SetCapture();
	}
	// 최상위 개체 외의 개체에 클릭된 경우 ==> 최상위로 옮기고, 이동 준비
	else {
		int nObject = m_pZ->GetItem(clickedObjIndex);
		m_isClicked = nObject;
		//m_prevPoint = point;
		m_pZ->SetOnTop(nObject);
		Invalidate();
		OnLButtonDown(nFlags, point);
	}




	//// 두개가 겹친 영역에 클릭한 경우
	//if (m_rect.PtInRect(point) == TRUE && m_starRegion.PtInRegion(point) == TRUE) {
	//	
	//	// 사각형이 위에
	//	if (m_isOnTop == OBJ_SQUARE) {
	//		// 이동시킬 준비 시작
	//		m_isClicked = OBJ_SQUARE;
	//		m_prevPoint = point;

	//		// 클라이언트 영역 벗어나도 메시지 받음
	//		SetCapture();
	//	}

	//	// 별모양이 위에
	//	else if (m_isOnTop == OBJ_STAR) {
	//		// 이동시킬 준비 시작
	//		m_isClicked = OBJ_STAR;
	//		m_prevPoint = point;

	//		// 클라이언트 영역 벗어나도 메시지 받음
	//		SetCapture();
	//	}
	//}
	//// 사각형 영역에만 클릭
	//else if (m_rect.PtInRect(point) == TRUE && m_starRegion.PtInRegion(point) == FALSE) {

	//	if (m_isOnTop == OBJ_SQUARE) {
	//		// 이동시킬 준비 시작
	//		m_isClicked = OBJ_SQUARE;
	//		m_prevPoint = point;

	//		// 클라이언트 영역 벗어나도 메시지 받음
	//		SetCapture();

	//	}
	//	else if (m_isOnTop == OBJ_STAR) {
	//		m_isOnTop = OBJ_SQUARE;
	//		Invalidate();
	//		OnLButtonDown(nFlags, point);
	//	}
	//}
	//// 별모양 영역에만 클릭
	//else if (m_starRegion.PtInRegion(point) == TRUE && m_rect.PtInRect(point) == FALSE) {

	//	if (m_isOnTop == OBJ_STAR) {
	//		// 이동시킬 준비 시작
	//		m_isClicked = OBJ_STAR;
	//		m_prevPoint = point;

	//		// 클라이언트 영역 벗어나도 메시지 받음
	//		SetCapture();
	//	}
	//	else if (m_isOnTop == OBJ_SQUARE) {
	//		m_isOnTop = OBJ_STAR;
	//		Invalidate();
	//		OnLButtonDown(nFlags, point);
	//	}
	//}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CM03MovePolygonDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_isClicked != OBJ_NONE) {
		m_isClicked = OBJ_NONE;

		// 클라이언트 영역 외에서 메시지 더이상 안 받음
		ReleaseCapture();
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CM03MovePolygonDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// 정사각형 이동
	if (m_isClicked == OBJ_SQUARE && m_pZ->GetItem(0) == OBJ_SQUARE) {

		// 이전지점과 현재지점의 좌표 차이
		CPoint diffPoint = point - m_prevPoint;

		// rect에 차이 반영
		m_square += diffPoint;

		// 이전 위치 업데이트
		m_prevPoint = point;

		// 다시 그리기
		Invalidate();
	}
	// 직사각형 이동
	else if (m_isClicked == OBJ_RECTANGLE && m_pZ->GetItem(0) == OBJ_RECTANGLE) {

		// 이전지점과 현재지점의 좌표 차이
		CPoint diffPoint = point - m_prevPoint;

		// rect에 차이 반영
		m_rect += diffPoint;

		// 이전 위치 업데이트
		m_prevPoint = point;

		// 다시 그리기
		Invalidate();
	}
	// 별모양 이동
	else if (m_isClicked == OBJ_STAR && m_pZ->GetItem(0) == OBJ_STAR) {
		// 이전지점과 현재지점의 좌표 차이
		CPoint diffPoint = point - m_prevPoint;

		// starRegion에 차이 반영
		m_starRegion.OffsetRgn(diffPoint);

		// 이전 위치 업데이트
		m_prevPoint = point;

		Invalidate();
	}
	// 원모양 이동
	else if (m_isClicked == OBJ_CIRCLE && m_pZ->GetItem(0) == OBJ_CIRCLE) {
		// 이전지점과 현재지점의 좌표 차이
		CPoint diffPoint = point - m_prevPoint;

		// starRegion에 차이 반영
		m_circleRegion.OffsetRgn(diffPoint);

		// 이전 위치 업데이트
		m_prevPoint = point;

		Invalidate();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
