
// M05SliderCtrl.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CM05SliderCtrlApp:
// See M05SliderCtrl.cpp for the implementation of this class
//

class CM05SliderCtrlApp : public CWinApp
{
public:
	CM05SliderCtrlApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CM05SliderCtrlApp theApp;
