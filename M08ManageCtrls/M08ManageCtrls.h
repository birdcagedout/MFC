
// M08ManageCtrls.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CM08ManageCtrlsApp:
// See M08ManageCtrls.cpp for the implementation of this class
//

class CM08ManageCtrlsApp : public CWinApp
{
public:
	CM08ManageCtrlsApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CM08ManageCtrlsApp theApp;
