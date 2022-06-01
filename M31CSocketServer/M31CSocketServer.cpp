
// M31CSocketServer.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "M31CSocketServer.h"
#include "M31CSocketServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM31CSocketServerApp

BEGIN_MESSAGE_MAP(CM31CSocketServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CM31CSocketServerApp 생성

CM31CSocketServerApp::CM31CSocketServerApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CM31CSocketServerApp 개체입니다.

CM31CSocketServerApp theApp;


// CM31CSocketServerApp 초기화

BOOL CM31CSocketServerApp::InitInstance()
{
	CWinApp::InitInstance();

	// 소켓 초기화
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	CM31CSocketServerDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

