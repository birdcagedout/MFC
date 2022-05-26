
// M03MovePolygon.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "M03MovePolygon.h"
#include "M03MovePolygonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM03MovePolygonApp

BEGIN_MESSAGE_MAP(CM03MovePolygonApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CM03MovePolygonApp construction

CM03MovePolygonApp::CM03MovePolygonApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CM03MovePolygonApp object

CM03MovePolygonApp theApp;


// CM03MovePolygonApp initialization

BOOL CM03MovePolygonApp::InitInstance()
{
	CWinApp::InitInstance();
	CM03MovePolygonDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}

