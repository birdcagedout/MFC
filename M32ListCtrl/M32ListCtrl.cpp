
// M32ListCtrl.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "M32ListCtrl.h"
#include "M32ListCtrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM32ListCtrlApp

BEGIN_MESSAGE_MAP(CM32ListCtrlApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CM32ListCtrlApp 생성

CM32ListCtrlApp::CM32ListCtrlApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CM32ListCtrlApp 개체입니다.

CM32ListCtrlApp theApp;


// CM32ListCtrlApp 초기화

BOOL CM32ListCtrlApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	CM32ListCtrlDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}

