
// MFCGraph1.h : MFCGraph1 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMFCGraph1App:
// �йش����ʵ�֣������ MFCGraph1.cpp
//

class CMFCGraph1App : public CWinApp
{
public:
	CMFCGraph1App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCGraph1App theApp;
