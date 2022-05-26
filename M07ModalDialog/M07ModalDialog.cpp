
// M07ModalDialog.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "M07ModalDialog.h"
#include "M07ModalDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM07ModalDialogApp

BEGIN_MESSAGE_MAP(CM07ModalDialogApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CM07ModalDialogApp 생성

CM07ModalDialogApp::CM07ModalDialogApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CM07ModalDialogApp 개체입니다.

CM07ModalDialogApp theApp;


// CM07ModalDialogApp 초기화

BOOL CM07ModalDialogApp::InitInstance()
{
	CWinApp::InitInstance();

	CM07ModalDialogDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

