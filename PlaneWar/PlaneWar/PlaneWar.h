
// PlaneWar.h : PlaneWar Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CPlaneWarApp:
// �йش����ʵ�֣������ PlaneWar.cpp
//

class CPlaneWarApp : public CWinAppEx
{
public:
	CPlaneWarApp();


	// ��д
public:
	virtual BOOL InitInstance();


	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPlaneWarApp theApp;
