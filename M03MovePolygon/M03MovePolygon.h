
// M03MovePolygon.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CM03MovePolygonApp:
// See M03MovePolygon.cpp for the implementation of this class
//

class CM03MovePolygonApp : public CWinApp
{
public:
	CM03MovePolygonApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CM03MovePolygonApp theApp;
