
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

	// Ŭ�� ���º���
	m_isClicked = OBJ_NONE;

	// ��ü ����
	m_objCount = OBJ_COUNT;

	// Z-order ������ü: ��ü�� ��3��
	// �ֻ��� ������� : �� - �� - �簢��
	m_pZ = new CMyZOrder;


	// ���簢�� �ʱ�ȭ
	m_square.SetRect(10, 10, 100, 100);

	// ���簢�� �ʱ�ȭ
	m_rect.SetRect(100, 100, 300, 200);


	// ����� ��ǥ : ������ - ������ - ������ - ... - ����(=������)
	POINT starPoints[11] = { {101,0}, {77,77}, {0,77}, {62,125}, {39,201}, {101,153}, {163,201}, {138,125}, {201,77}, {124,77}, {101,0} };

	// ����� �׵θ� �귯��
	m_starBrush.CreateSolidBrush(RGB(0, 0, 0));

	// ����� ���ο���
	m_starRegion.CreatePolygonRgn(starPoints, 11, ALTERNATE);		// ������� ���ʿ���


	// ����� �׵θ� �귯��
	m_circleBrush.CreateSolidBrush(RGB(0, 0, 0));

	// ����� ���ο���
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
		// ������ ��ü���� �ϳ��� �׸���
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
	// �ֻ��� ��ü���� ������� Ȯ��
	for (int i = 0; i < m_objCount; i++)
	{
		int nObject = m_pZ->GetItem(i);
		
		// ���簢���̸�
		if (nObject == OBJ_SQUARE) {
			if (m_square.PtInRect(point) == TRUE) {
				return i;
			}
		}
		// ���簢���̸�
		else if (nObject == OBJ_RECTANGLE) {
			if (m_rect.PtInRect(point) == TRUE) {
				return i;
			}
		}
		// ������̸�
		else if (nObject == OBJ_STAR) {
			if (m_starRegion.PtInRegion(point) == TRUE) {
				return i;
			}
		}
		// ������̸�
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

	// �ƹ� ��ü���� Ŭ������ ���� ��� ==> �ƹ��͵� ���� ����
	if (clickedObjIndex == OBJ_NONE_INDEX) {
		return;
	}
	// �ֻ��� ��ü�� Ŭ���� ��� ==> �̵� �غ�
	else if(clickedObjIndex == 0) {

		// �簢���� ���
		//if (m_pZ->GetItem(0) == OBJ_SQUARE) {
		//	m_isClicked = OBJ_SQUARE;
		//	
		//}
		//// ������� ���
		//else if (m_pZ->GetItem(0) == OBJ_STAR) {
		//	m_isClicked = OBJ_STAR;
		//}
		//// ������� ���
		//else if (m_pZ->GetItem(0) == OBJ_CIRCLE) {
		//	m_isClicked = OBJ_CIRCLE;
		//}
		m_isClicked = m_pZ->GetItem(0);
		m_prevPoint = point;
		SetCapture();
	}
	// �ֻ��� ��ü ���� ��ü�� Ŭ���� ��� ==> �ֻ����� �ű��, �̵� �غ�
	else {
		int nObject = m_pZ->GetItem(clickedObjIndex);
		m_isClicked = nObject;
		//m_prevPoint = point;
		m_pZ->SetOnTop(nObject);
		Invalidate();
		OnLButtonDown(nFlags, point);
	}




	//// �ΰ��� ��ģ ������ Ŭ���� ���
	//if (m_rect.PtInRect(point) == TRUE && m_starRegion.PtInRegion(point) == TRUE) {
	//	
	//	// �簢���� ����
	//	if (m_isOnTop == OBJ_SQUARE) {
	//		// �̵���ų �غ� ����
	//		m_isClicked = OBJ_SQUARE;
	//		m_prevPoint = point;

	//		// Ŭ���̾�Ʈ ���� ����� �޽��� ����
	//		SetCapture();
	//	}

	//	// ������� ����
	//	else if (m_isOnTop == OBJ_STAR) {
	//		// �̵���ų �غ� ����
	//		m_isClicked = OBJ_STAR;
	//		m_prevPoint = point;

	//		// Ŭ���̾�Ʈ ���� ����� �޽��� ����
	//		SetCapture();
	//	}
	//}
	//// �簢�� �������� Ŭ��
	//else if (m_rect.PtInRect(point) == TRUE && m_starRegion.PtInRegion(point) == FALSE) {

	//	if (m_isOnTop == OBJ_SQUARE) {
	//		// �̵���ų �غ� ����
	//		m_isClicked = OBJ_SQUARE;
	//		m_prevPoint = point;

	//		// Ŭ���̾�Ʈ ���� ����� �޽��� ����
	//		SetCapture();

	//	}
	//	else if (m_isOnTop == OBJ_STAR) {
	//		m_isOnTop = OBJ_SQUARE;
	//		Invalidate();
	//		OnLButtonDown(nFlags, point);
	//	}
	//}
	//// ����� �������� Ŭ��
	//else if (m_starRegion.PtInRegion(point) == TRUE && m_rect.PtInRect(point) == FALSE) {

	//	if (m_isOnTop == OBJ_STAR) {
	//		// �̵���ų �غ� ����
	//		m_isClicked = OBJ_STAR;
	//		m_prevPoint = point;

	//		// Ŭ���̾�Ʈ ���� ����� �޽��� ����
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

		// Ŭ���̾�Ʈ ���� �ܿ��� �޽��� ���̻� �� ����
		ReleaseCapture();
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CM03MovePolygonDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// ���簢�� �̵�
	if (m_isClicked == OBJ_SQUARE && m_pZ->GetItem(0) == OBJ_SQUARE) {

		// ���������� ���������� ��ǥ ����
		CPoint diffPoint = point - m_prevPoint;

		// rect�� ���� �ݿ�
		m_square += diffPoint;

		// ���� ��ġ ������Ʈ
		m_prevPoint = point;

		// �ٽ� �׸���
		Invalidate();
	}
	// ���簢�� �̵�
	else if (m_isClicked == OBJ_RECTANGLE && m_pZ->GetItem(0) == OBJ_RECTANGLE) {

		// ���������� ���������� ��ǥ ����
		CPoint diffPoint = point - m_prevPoint;

		// rect�� ���� �ݿ�
		m_rect += diffPoint;

		// ���� ��ġ ������Ʈ
		m_prevPoint = point;

		// �ٽ� �׸���
		Invalidate();
	}
	// ����� �̵�
	else if (m_isClicked == OBJ_STAR && m_pZ->GetItem(0) == OBJ_STAR) {
		// ���������� ���������� ��ǥ ����
		CPoint diffPoint = point - m_prevPoint;

		// starRegion�� ���� �ݿ�
		m_starRegion.OffsetRgn(diffPoint);

		// ���� ��ġ ������Ʈ
		m_prevPoint = point;

		Invalidate();
	}
	// ����� �̵�
	else if (m_isClicked == OBJ_CIRCLE && m_pZ->GetItem(0) == OBJ_CIRCLE) {
		// ���������� ���������� ��ǥ ����
		CPoint diffPoint = point - m_prevPoint;

		// starRegion�� ���� �ݿ�
		m_circleRegion.OffsetRgn(diffPoint);

		// ���� ��ġ ������Ʈ
		m_prevPoint = point;

		Invalidate();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
