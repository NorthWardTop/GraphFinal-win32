
// MFCGraph2.h : MFCGraph2 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMFCGraph2App:
// �йش����ʵ�֣������ MFCGraph2.cpp
//

class CMFCGraph2App : public CWinApp
{
public:
	CMFCGraph2App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCGraph2App theApp;
