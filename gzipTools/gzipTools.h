
// gzipTools.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CgzipToolsApp:
// �йش����ʵ�֣������ gzipTools.cpp
//

class CgzipToolsApp : public CWinAppEx
{
public:
	CgzipToolsApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CgzipToolsApp theApp;