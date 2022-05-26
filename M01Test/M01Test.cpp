
// M01Test.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "M01Test.h"
#include "M01TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM01TestApp

BEGIN_MESSAGE_MAP(CM01TestApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CM01TestApp 생성

CM01TestApp::CM01TestApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CM01TestApp 개체입니다.

CM01TestApp theApp;


// CM01TestApp 초기화

BOOL CM01TestApp::InitInstance()
{
	CWinApp::InitInstance();

	CM01TestDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

