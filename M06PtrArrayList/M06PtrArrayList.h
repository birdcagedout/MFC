
// M06PtrArrayList.h: PROJECT_NAME 애플리케이션에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.


// CM06PtrArrayListApp:
// 이 클래스의 구현에 대해서는 M06PtrArrayList.cpp을(를) 참조하세요.
//

class CM06PtrArrayListApp : public CWinApp
{
public:
	CM06PtrArrayListApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern CM06PtrArrayListApp theApp;
