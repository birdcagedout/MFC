
// M10CalendarCtrl.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CM10CalendarCtrlApp:
// See M10CalendarCtrl.cpp for the implementation of this class
//

class CM10CalendarCtrlApp : public CWinApp
{
public:
	CM10CalendarCtrlApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CM10CalendarCtrlApp theApp;
