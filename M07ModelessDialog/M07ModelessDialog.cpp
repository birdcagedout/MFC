
// M07ModelessDialog.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "M07ModelessDialog.h"
#include "M07ModelessDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM07ModelessDialogApp

BEGIN_MESSAGE_MAP(CM07ModelessDialogApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CM07ModelessDialogApp 생성

CM07ModelessDialogApp::CM07ModelessDialogApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CM07ModelessDialogApp 개체입니다.

CM07ModelessDialogApp theApp;


// CM07ModelessDialogApp 초기화

BOOL CM07ModelessDialogApp::InitInstance()
{
	CWinApp::InitInstance();

	CM07ModelessDialogDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}

