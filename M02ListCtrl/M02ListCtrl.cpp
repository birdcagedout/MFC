
// M02ListCtrl.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "M02ListCtrl.h"
#include "M02ListCtrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM02ListCtrlApp

BEGIN_MESSAGE_MAP(CM02ListCtrlApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CM02ListCtrlApp 생성

CM02ListCtrlApp::CM02ListCtrlApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CM02ListCtrlApp 개체입니다.

CM02ListCtrlApp theApp;


// CM02ListCtrlApp 초기화

BOOL CM02ListCtrlApp::InitInstance()
{
	CWinApp::InitInstance();

	CM02ListCtrlDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

