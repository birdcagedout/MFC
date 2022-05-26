
// M04Transparent.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "M04Transparent.h"
#include "M04TransparentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM04TransparentApp

BEGIN_MESSAGE_MAP(CM04TransparentApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CM04TransparentApp 생성

CM04TransparentApp::CM04TransparentApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CM04TransparentApp 개체입니다.

CM04TransparentApp theApp;


// CM04TransparentApp 초기화

BOOL CM04TransparentApp::InitInstance()
{
	CWinApp::InitInstance();

	CM04TransparentDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}


