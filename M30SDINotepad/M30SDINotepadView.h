
// M30SDINotepadView.h: CM30SDINotepadView 클래스의 인터페이스
//

#pragma once


class CM30SDINotepadView : public CEditView
{
protected: // serialization에서만 만들어집니다.
	CM30SDINotepadView() noexcept;
	DECLARE_DYNCREATE(CM30SDINotepadView)

// 특성입니다.
public:
	CM30SDINotepadDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CM30SDINotepadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // M30SDINotepadView.cpp의 디버그 버전
inline CM30SDINotepadDoc* CM30SDINotepadView::GetDocument() const
   { return reinterpret_cast<CM30SDINotepadDoc*>(m_pDocument); }
#endif

