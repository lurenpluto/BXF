/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2013              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   WebKernelGlobal
*   Author      :   李亚星
*   Create      :   2013-7-10 
*   LastChange  :   2013-7-10
*   History     :	
*
*   Description :   浏览器的全局数据结构和相关函数
*
********************************************************************/ 
#ifndef __WEBKERNELGLOBAL_H__
#define __WEBKERNELGLOBAL_H__

#include "./WebKernelBrowserManager.h"
#include "./WebKernelITC.h"
#include "./WebKernelSettings.h"
#include "./WebKernelMessageLoop.h"
#include "./WebKernelSyncProxy.h"
#include "./WebKernelApp.h"

class WebKernelGlobal
{
public:

	BOOL m_browserProcess;

	HMODULE	m_hModule;

	CefRefPtr<WebKernelApp> m_app;

	WebKernelSettings m_setting;

	WebKernelBrowserManager m_browserManager;

	WebKernelITC m_itc;

	WebKernelSyncProxy m_syncProxy;

	WebKernelMessageLoop m_msgLoop;
};

extern WebKernelGlobal g_webKernelGlobal;


class WebKernelGlobalMethods
{
public:

	static BOOL Init();
	static BOOL Uninit();

	static long RunWebServer();
};
#endif // __WEBKERNELGLOBAL_H__