// GassSimulation1.1.h : main header file for the GassSimulation1.1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGassSimulation11App:
// See GassSimulation1.1.cpp for the implementation of this class
//

class CGassSimulation11App : public CWinApp
{
public:
	CGassSimulation11App();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGassSimulation11App theApp;