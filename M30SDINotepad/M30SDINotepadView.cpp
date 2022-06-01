
// M30SDINotepadView.cpp: CM30SDINotepadView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "M30SDINotepad.h"
#endif

#include "M30SDINotepadDoc.h"
#include "M30SDINotepadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM30SDINotepadView

IMPLEMENT_DYNCREATE(CM30SDINotepadView, CEditView)

BEGIN_MESSAGE_MAP(CM30SDINotepadView, CEditView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CM30SDINotepadView 생성/소멸

CM30SDINotepadView::CM30SDINotepadView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CM30SDINotepadView::~CM30SDINotepadView()
{
}

BOOL CM30SDINotepadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);				// 자동수평스크롤, 수평스크롤 제외

	return bPreCreated;
}

void CM30SDINotepadView::OnRButtonUp(UINT /* nFlags */, CPoint point)		// 우클릭시 컨텍스트 메뉴
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CM30SDINotepadView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CM30SDINotepadView 진단

#ifdef _DEBUG
void CM30SDINotepadView::AssertValid() const
{
	CEditView::AssertValid();
}

void CM30SDINotepadView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CM30SDINotepadDoc* CM30SDINotepadView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CM30SDINotepadDoc)));
	return (CM30SDINotepadDoc*)m_pDocument;
}
#endif //_DEBUG


// CM30SDINotepadView 메시지 처리기
