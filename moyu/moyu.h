
// moyu.h : moyu Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CmoyuApp:
// �йش����ʵ�֣������ moyu.cpp
//

class CmoyuApp : public CWinApp
{
public:
	CmoyuApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CmoyuApp theApp;

