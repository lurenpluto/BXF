/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./WebKernelDisplayHandler.h"
#include "./BaseBoltBrowser.h"

WebKernelDisplayHandler::WebKernelDisplayHandler(BaseBoltBrowser* lpOwner)
:m_lpOwner(lpOwner)
{
	assert(m_lpOwner);
}

WebKernelDisplayHandler::~WebKernelDisplayHandler(void)
{
	assert(m_lpOwner);
	m_lpOwner = NULL;
}

void WebKernelDisplayHandler::OnLoadingStateChange( CefRefPtr<CefBrowser> browser, bool isLoading, 
												   bool canGoBack, bool canGoForward )
{
	assert(m_lpOwner);

	bool handled = false;
	m_lpOwner->OnLoadingStateChange(isLoading, canGoBack, canGoForward, handled);
}

void WebKernelDisplayHandler::OnAddressChange( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url )
{
	assert(m_lpOwner);

	bool handled = false;
	m_lpOwner->OnAddressChange(frame, url, handled);
}

void WebKernelDisplayHandler::OnTitleChange( CefRefPtr<CefBrowser> browser, const CefString& title )
{
	assert(m_lpOwner);

	bool handled = false;
	m_lpOwner->OnTitleChange(title, handled);
}

bool WebKernelDisplayHandler::OnTooltip( CefRefPtr<CefBrowser> browser, CefString& text )
{
	assert(m_lpOwner);

	bool handled = false;
	m_lpOwner->OnTooltip(text, handled);

	return false;
}

void WebKernelDisplayHandler::OnStatusMessage( CefRefPtr<CefBrowser> browser, const CefString& value )
{
	assert(m_lpOwner);

	bool handled = false;
	m_lpOwner->OnStatusMessage(value, handled);
}

bool WebKernelDisplayHandler::OnConsoleMessage( CefRefPtr<CefBrowser> browser, const CefString& message, const CefString& source, int line )
{
	assert(m_lpOwner);

	bool handled = false;
	m_lpOwner->OnConsoleMessage(message, source, line, handled);

	return false;
}