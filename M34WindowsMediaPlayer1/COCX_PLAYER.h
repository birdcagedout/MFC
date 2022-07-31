#pragma once

// 머신에서 Microsoft Visual C++를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// 참고: 이 파일의 콘텐츠를 수정하지 마세요. Microsoft Visual C++를 통해 이 클래스가 다시 생성될 경우 
// 수정 내용을 덮어씁니다.

/////////////////////////////////////////////////////////////////////////////

#include "afxwin.h"

class COCX_PLAYER : public CWnd
{
protected:
	DECLARE_DYNCREATE(COCX_PLAYER)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= {0x6bf52a52,0x394a,0x11d3,{0xb1,0x53,0x00,0xc0,0x4f,0x79,0xfa,0xa6}};
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = nullptr)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID);
	}

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
				UINT nID, CFile* pPersist = nullptr, BOOL bStorage = FALSE,
				BSTR bstrLicKey = nullptr)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

	void SetUrl(LPCTSTR lpszURL)
	{
		static BYTE params[] = VTS_BSTR;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, params, lpszURL);
	}

	// 이하 복잡한 부분 모두 삭제
};
