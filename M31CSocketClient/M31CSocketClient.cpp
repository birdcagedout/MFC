
// M31CSocketClient.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "M31CSocketClient.h"
#include "M31CSocketClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM31CSocketClientApp

BEGIN_MESSAGE_MAP(CM31CSocketClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CM31CSocketClientApp 생성

CM31CSocketClientApp::CM31CSocketClientApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CM31CSocketClientApp 개체입니다.

CM31CSocketClientApp theApp;


// CM31CSocketClientApp 초기화

BOOL CM31CSocketClientApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	CM31CSocketClientDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

