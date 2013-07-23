/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./WebKernelITC.h"

WebKernelITC::WebKernelITC()
{

}

WebKernelITC::~WebKernelITC()
{

}

bool WebKernelITC::Init()
{
	assert(!m_wnd.IsWindow());
	m_wnd.Create(HWND_MESSAGE);
	assert(m_wnd.IsWindow());

	return true;
}

bool WebKernelITC::Uninit()
{
	assert(m_wnd.IsWindow());
	m_wnd.DestroyWindow();

	return true;
}

long WebKernelITC::SendMessage( int browserIdentifier, CefRefPtr<CefProcessMessage> msg, bool& handled )
{
	assert(m_wnd.IsWindow());

	ITCMessage ITCMsg;
	ITCMsg.m_browserID = browserIdentifier;
	ITCMsg.m_threadID = ::GetCurrentThreadId();
	ITCMsg.m_message = msg;
	ITCMsg.m_handled = false;

	long ret = m_wnd.SendMessage(WEBKERNELITC_WND_MSG, (WPARAM)&ITCMsg);

	handled = ITCMsg.m_handled;

	return ret;
}

long WebKernelITC::OnThreadMessage( int browserIdentifier, unsigned long threadID, CefRefPtr<CefProcessMessage> msg, bool& handled )
{
	CefRefPtr<CefBrowser> browser = g_webKernelGlobal.m_browserManager.GetBrowserFromID(browserIdentifier);
	assert(browser);
	if (browser == NULL)
	{
		return -1;
	}
	
	g_webKernelGlobal.m_syncProxy.OnThreadMessagerRecevied(browser, msg);

	return 0;
}

LRESULT WebKernelITC::WebKernelITCWindow::OnThreadMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	ITCMessage* lpMsg = (ITCMessage*)wParam;
	assert(lpMsg);

	int browserIdentifier = (int)wParam;
	CefRefPtr<CefProcessMessage> msg = (CefProcessMessage*)lParam;

	WebKernelITC* lpOwner = (WebKernelITC*)((BYTE*)this - offsetof(WebKernelITC, m_wnd));

	return lpOwner->OnThreadMessage(lpMsg->m_browserID, lpMsg->m_threadID, lpMsg->m_message, lpMsg->m_handled);
}