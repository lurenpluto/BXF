/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./WebKernelApp.h"

WebKernelApp::WebKernelApp(void)
:m_spBrowserProcessHandler(NULL),
m_spRenderProcessHandler(NULL)
{
}

WebKernelApp::~WebKernelApp(void)
{
	assert(m_spBrowserProcessHandler == NULL);
	assert(m_spRenderProcessHandler == NULL);
}

void WebKernelApp::OnBeforeCommandLineProcessing( const CefString& process_type, CefRefPtr<CefCommandLine> command_line )
{
	
}

CefRefPtr<CefBrowserProcessHandler> WebKernelApp::GetBrowserProcessHandler()
{
	return m_spBrowserProcessHandler.get();
}

CefRefPtr<CefRenderProcessHandler> WebKernelApp::GetRenderProcessHandler()
{
	return m_spRenderProcessHandler.get();
}

bool WebKernelApp::Init()
{
	assert(m_spBrowserProcessHandler == NULL);
	assert(m_spRenderProcessHandler == NULL);

	if (g_webKernelGlobal.m_browserProcess)
	{
		m_spBrowserProcessHandler = new WebKernelBrowserProcessHandler();
	}
	else
	{
		m_spRenderProcessHandler = new WebKernelRenderProcessHandler();
	}

	return true;
}

bool WebKernelApp::Uninit()
{
	if (m_spBrowserProcessHandler != NULL)
	{
		m_spBrowserProcessHandler = NULL;
	}

	if (m_spRenderProcessHandler != NULL)
	{
		m_spRenderProcessHandler = NULL;
	}

	return true;
}

void WebKernelBrowserProcessHandler::OnContextInitialized()
{

}

void WebKernelBrowserProcessHandler::OnBeforeChildProcessLaunch( CefRefPtr<CefCommandLine> command_line )
{
	command_line->AppendArgument(L"servicetype");
	command_line->AppendArgument(L"web");

	wchar_t szID[255];
	::memset(szID, 0, 255);

	wsprintf(szID, L"Xunlei.UIEngine.WebServer.%d.%d.%d", ::GetCurrentProcessId(), ::GetCurrentThreadId(), m_renderServerNextID);
	m_renderServerNextID++;

	command_line->AppendArgument(L"id");
	command_line->AppendArgument(szID);

	wsprintf(szID, L"%d", ::GetCurrentProcessId());
	command_line->AppendArgument(L"pid");
	command_line->AppendArgument(szID);

	wchar_t szEXEPath[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, szEXEPath, MAX_PATH);

	command_line->AppendArgument(L"clientpath");
	command_line->AppendArgument(szEXEPath);
}

void WebKernelBrowserProcessHandler::OnRenderProcessThreadCreated( CefRefPtr<CefListValue> extra_info )
{

}

WebKernelBrowserProcessHandler::WebKernelBrowserProcessHandler()
:m_renderServerNextID(1)
{

}

WebKernelBrowserProcessHandler::~WebKernelBrowserProcessHandler()
{

}

void WebKernelRenderProcessHandler::OnRenderThreadCreated( CefRefPtr<CefListValue> extra_info )
{

}

void WebKernelRenderProcessHandler::OnWebKitInitialized()
{

}

void WebKernelRenderProcessHandler::OnBrowserCreated( CefRefPtr<CefBrowser> browser )
{
	assert(browser);
	bool ret = g_webKernelGlobal.m_browserManager.Register(browser.get(), NULL, NULL);
	assert(ret);
}

void WebKernelRenderProcessHandler::OnBrowserDestroyed( CefRefPtr<CefBrowser> browser )
{
	assert(browser);
	g_webKernelGlobal.m_browserManager.UnRegister(browser.get());
}

bool WebKernelRenderProcessHandler::OnBeforeNavigation( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
													   CefRefPtr<CefRequest> request, NavigationType navigation_type, bool is_redirect )
{
	return g_webKernelGlobal.m_syncProxy.OnBeforeNavigation(browser, frame, request, navigation_type, is_redirect);
}

void WebKernelRenderProcessHandler::OnContextCreated( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
													 CefRefPtr<CefV8Context> context )
{
	
}

void WebKernelRenderProcessHandler::OnContextReleased( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
													  CefRefPtr<CefV8Context> context )
{

}

void WebKernelRenderProcessHandler::OnUncaughtException( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
														CefRefPtr<CefV8Context> context, CefRefPtr<CefV8Exception> exception, 
														CefRefPtr<CefV8StackTrace> stackTrace )
{

}

void WebKernelRenderProcessHandler::OnFocusedNodeChanged( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
														 CefRefPtr<CefDOMNode> node )
{
	g_webKernelGlobal.m_syncProxy.OnFocusedNodeChanged(browser, frame, node);
}

bool WebKernelRenderProcessHandler::OnProcessMessageReceived( CefRefPtr<CefBrowser> browser, CefProcessId source_process, 
															 CefRefPtr<CefProcessMessage> message )
{
	return false;
}
