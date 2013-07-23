/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./WebKernelClient.h"

WebKernelClient::WebKernelClient(void)
{
}

WebKernelClient::~WebKernelClient(void)
{
}

CefRefPtr<CefContextMenuHandler> WebKernelClient::GetContextMenuHandler()
{
	return NULL;
}

CefRefPtr<CefDisplayHandler> WebKernelClient::GetDisplayHandler()
{
	return m_displayHandler.get();
}

CefRefPtr<CefDownloadHandler> WebKernelClient::GetDownloadHandler()
{
	return NULL;
}

CefRefPtr<CefFocusHandler> WebKernelClient::GetFocusHandler()
{
	return NULL;
}

CefRefPtr<CefGeolocationHandler> WebKernelClient::GetGeolocationHandler()
{
	return NULL;
}

CefRefPtr<CefKeyboardHandler> WebKernelClient::GetKeyboardHandler()
{
	return NULL;
}

CefRefPtr<CefLifeSpanHandler> WebKernelClient::GetLifeSpanHandler()
{
	return m_lifeSpanHandler.get();
}

CefRefPtr<CefLoadHandler> WebKernelClient::GetLoadHandler()
{
	return NULL;
}

CefRefPtr<CefRenderHandler> WebKernelClient::GetRenderHandler()
{
	return m_renderHandler.get();
}

CefRefPtr<CefRequestHandler> WebKernelClient::GetRequestHandler()
{
	return NULL;
}

bool WebKernelClient::OnProcessMessageReceived( CefRefPtr<CefBrowser> browser, CefProcessId source_process, 
											   CefRefPtr<CefProcessMessage> message )
{
	return g_webKernelGlobal.m_syncProxy.OnProcessMessageReceived(browser, message);
}

bool WebKernelClient::SetLifeSpanHandler( CefLifeSpanHandler* lpHandler )
{
	m_lifeSpanHandler = lpHandler;

	return true;
}

bool WebKernelClient::SetDisplayHandler( CefDisplayHandler* lpHandler )
{
	m_displayHandler = lpHandler;

	return true;
}

bool WebKernelClient::SetRenderHandler( CefRenderHandler* lpHandler )
{
	m_renderHandler = lpHandler;

	return true;
}