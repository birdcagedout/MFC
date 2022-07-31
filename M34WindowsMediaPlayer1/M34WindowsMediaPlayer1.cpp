
// M34WindowsMediaPlayer1.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "M34WindowsMediaPlayer1.h"
#include "M34WindowsMediaPlayer1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM34WindowsMediaPlayer1App

BEGIN_MESSAGE_MAP(CM34WindowsMediaPlayer1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CM34WindowsMediaPlayer1App 생성

CM34WindowsMediaPlayer1App::CM34WindowsMediaPlayer1App()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CM34WindowsMediaPlayer1App 개체입니다.

CM34WindowsMediaPlayer1App theApp;


// CM34WindowsMediaPlayer1App 초기화

BOOL CM34WindowsMediaPlayer1App::InitInstance()
{
	CWinApp::InitInstance();


	AfxEnableControlContainer();

	CM34WindowsMediaPlayer1Dlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

