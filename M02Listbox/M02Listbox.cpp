
// M02Listbox.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "M02Listbox.h"
#include "M02ListboxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM02ListboxApp

BEGIN_MESSAGE_MAP(CM02ListboxApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CM02ListboxApp 생성

CM02ListboxApp::CM02ListboxApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CM02ListboxApp 개체입니다.

CM02ListboxApp theApp;


// CM02ListboxApp 초기화

BOOL CM02ListboxApp::InitInstance()
{
	CWinApp::InitInstance();


	CM02ListboxDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

