/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./WebKernelGlobal.h"

BOOL WebKernelGlobalMethods::Init()
{
	g_webKernelGlobal.m_browserProcess = TRUE;

	g_webKernelGlobal.m_itc.Init();

	g_webKernelGlobal.m_syncProxy.Init();

	CefRefPtr<WebKernelApp> spApp(new WebKernelApp);
	if (!spApp->Init())
	{
		return FALSE;
	}

	CefMainArgs args(g_webKernelGlobal.m_hModule);

	g_webKernelGlobal.m_setting.Init();

	bool ret = ::CefInitialize(args, g_webKernelGlobal.m_setting.GetCefSettings(), spApp.get());
	assert(ret);
	if (!ret)
	{
		return FALSE;
	}

	g_webKernelGlobal.m_app = spApp;

	return TRUE;
}

BOOL WebKernelGlobalMethods::Uninit()
{
	assert(g_webKernelGlobal.m_browserProcess);

	::CefShutdown();

	g_webKernelGlobal.m_syncProxy.Uninit();

	g_webKernelGlobal.m_itc.Uninit();

	g_webKernelGlobal.m_app->Uninit();
	g_webKernelGlobal.m_app = NULL;

	//TODO
	return TRUE;
}

long WebKernelGlobalMethods::RunWebServer()
{
	g_webKernelGlobal.m_browserProcess = FALSE;

	CefRefPtr<WebKernelApp> spApp(new WebKernelApp);
	if (!spApp->Init())
	{
		return -1;
	}

	g_webKernelGlobal.m_itc.Init();

	g_webKernelGlobal.m_syncProxy.Init();

	g_webKernelGlobal.m_app = spApp;

	CefMainArgs args(g_webKernelGlobal.m_hModule);

	long exit_code = ::CefExecuteProcess(args, spApp.get());
	assert(exit_code != -1);

	g_webKernelGlobal.m_syncProxy.Uninit();

	g_webKernelGlobal.m_itc.Uninit();

	g_webKernelGlobal.m_app->Uninit();
	g_webKernelGlobal.m_app = NULL;

	return exit_code;
}