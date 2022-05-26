
// M06PtrArrayListDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "M06PtrArrayList.h"
#include "M06PtrArrayListDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM06PtrArrayListDlg 대화 상자



CM06PtrArrayListDlg::CM06PtrArrayListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_M06PTRARRAYLIST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CM06PtrArrayListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CM06PtrArrayListDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CM06PtrArrayListDlg 메시지 처리기

BOOL CM06PtrArrayListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CM06PtrArrayListDlg::OnPaint()
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
		// 위치 저장 방법1
		/*POINT* p = m_posList;
		for (int i = 0; i < m_posCount; i++) {
			dc.Rectangle(p->x - 10, p->y - 10, p->x + 10, p->y + 10);
			p++;
		}*/


		// 위치 저장 방법2
		//POINT* p;
		//int count = m_posArray.GetCount();
		//for (int i = 0; i < count; i++) {
		//	p = (POINT*)m_posArray.GetAt(i);			// void* 형식으로 return하므로 캐스팅 필요
		//	dc.Rectangle(p->x - 10, p->y - 10, p->x + 10, p->y + 10);
		//}


		// 위치 저장 방법3
		POINT* p;
		POSITION pos = m_posList.GetHeadPosition();

		while (pos != NULL) {
			p = (POINT*)m_posList.GetNext(pos);
			dc.Rectangle(p->x - 10, p->y - 10, p->x + 10, p->y + 10);
		}



		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CM06PtrArrayListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CM06PtrArrayListDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 위치 저장 방법1
	/*if (m_posCount < MAX_COUNT) {
		
		// 위치 저장
		m_posList[m_posCount].x = point.x;
		m_posList[m_posCount].y = point.y;
		m_posCount++;

		// 사각형 그리기
		CClientDC dc(this);
		dc.Rectangle(point.x - 10, point.y - 10, point.x + 10, point.y + 10);
	}*/


	// 위치 저장 방법2
	//POINT* p = new POINT;
	//p->x = point.x;
	//p->y = point.y;
	//m_posArray.Add(p);

	//// 사각형 그리기
	//CClientDC dc(this);
	//dc.Rectangle(point.x - 10, point.y - 10, point.x + 10, point.y + 10);


	// 위치 저장 방법3
	POINT* p = new POINT;
	p->x = point.x;
	p->y = point.y;
	m_posList.AddTail(p);

	CClientDC dc(this);
	dc.Rectangle(point.x - 10, point.y - 10, point.x + 10, point.y + 10);



	CDialogEx::OnLButtonDown(nFlags, point);
}


// WM_DESTROY에서 동적할당 삭제
void CM06PtrArrayListDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// 위치 저장 방법2
	// CPtrArray에 add했던 POINT*들을 하나씩 꺼내서 삭제
	/*int count = m_posArray.GetCount();
	for (int i = 0; i < count; i++) {
		delete (POINT*)m_posArray.GetAt(i);
	}*/


	// 위치 저장 방법3 
	POINT* p;
	POSITION pos = m_posList.GetHeadPosition();

	while (pos!= NULL) {
		p = (POINT*)m_posList.GetNext(pos);
		delete p;
	}
}


// 우클릭으로 사각형 삭제
// 
// <방법2 CPtrArray>
// CPtrArray::RemoveAt(인덱스): element를 array에서 제거하긴 하지만, element를 delete하지는 못한다.
// 그래서 RemoveAt() 호출 후에 delete 해주어야 한다.
// https://docs.microsoft.com/en-us/cpp/mfc/reference/cobarray-class?view=msvc-170#removeat
//
// <방법3 CPtrList>
// CPtrList::RemoveAt(POSITION): element를 list에서 제거하긴 하지만, element를 delete하지는 못한다.
// 그래서 RemoveAt() 호출 후에 delete 해주어야 한다.
// https://docs.microsoft.com/en-us/cpp/mfc/reference/coblist-class?view=msvc-170#removeat


void CM06PtrArrayListDlg::OnRButtonDown(UINT nFlags, CPoint point)
{

	// 위치 저장 방법2
	// 사각형 삭제
	//CRect r;
	//POINT* p;
	//int count = m_posArray.GetCount();

	//for (int i = 0; i < count; i++) {
	//	p = (POINT*)m_posArray.GetAt(i);
	//	r.SetRect(p->x - 10, p->y - 10, p->x + 10, p->y + 10);

	//	if (r.PtInRect(point) == TRUE) {
	//		m_posDeleted = p;
	//		m_posArray.RemoveAt(i);
	//		delete p;
	//		/*CString str;
	//		str.Format(L"현재 항목 : %d개", m_posArray.GetCount());
	//		SetWindowText(str);*/
	//		Invalidate();
	//		break;
	//	}
	//}


	// 위치 저장 방법3
	// 사각형 삭제
	CRect r;
	POSITION pos, posPrev;
	pos = m_posList.GetHeadPosition();
	POINT* p;

	while (pos != NULL) {
		posPrev = pos;
		p = (POINT*)m_posList.GetNext(pos);
		
		if (p != NULL) {
			r.SetRect(p->x - 10, p->y - 10, p->x + 10, p->y + 10);
			if (r.PtInRect(point) == TRUE) {
				m_posList.RemoveAt(posPrev);
				delete p;
				Invalidate();
				break;
			}
		}
	}

	CDialogEx::OnRButtonDown(nFlags, point);
}
