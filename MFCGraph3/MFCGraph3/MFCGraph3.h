
// MFCGraph3.h : MFCGraph3 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMFCGraph3App:
// �йش����ʵ�֣������ MFCGraph3.cpp
//

class CMFCGraph3App : public CWinApp
{
public:
	CMFCGraph3App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCGraph3App theApp;
