/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./WebKernelLifeSpanHandler.h"
#include "./BaseBoltBrowser.h"

WebKernelLifeSpanHandler::WebKernelLifeSpanHandler(BaseBoltBrowser* lpOwner)
:m_lpOwner(lpOwner),
m_browserID(0)
{
	assert(m_lpOwner);
}

WebKernelLifeSpanHandler::~WebKernelLifeSpanHandler(void)
{
	assert(m_browser == NULL);
	assert(m_browserID == 0);

	assert(m_lpOwner);
	m_lpOwner = NULL;
}

bool WebKernelLifeSpanHandler::OnBeforePopup( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
											 const CefString& target_url, const CefString& target_frame_name, 
											 const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, 
											 CefRefPtr<CefClient>& client, CefBrowserSettings& settings, 
											 bool* no_javascript_access )
{
	g_webKernelGlobal.m_syncProxy.OnBeforePopup(browser, frame, target_url, target_frame_name, popupFeatures);

	// 无条件拦截popup窗口
	return true;
}

void WebKernelLifeSpanHandler::OnAfterCreated( CefRefPtr<CefBrowser> browser )
{
	if (m_browser == NULL)
	{
		m_browser = browser;
		m_browserID = m_browser->GetIdentifier();
		assert(!browser->IsPopup());

		assert(m_lpOwner);
		m_lpOwner->NotifyOnAfterCreated(m_browser.get());
	}
	else
	{
		assert(false);
		assert(browser->IsPopup());
	}
}

bool WebKernelLifeSpanHandler::DoClose( CefRefPtr<CefBrowser> browser )
{
	assert(m_lpOwner);
	return m_lpOwner->NotifyDoClose();
}

void WebKernelLifeSpanHandler::OnBeforeClose( CefRefPtr<CefBrowser> browser )
{
	if (browser->GetIdentifier() == m_browserID)
	{
		assert(m_lpOwner);
		m_lpOwner->NotifyOnBeforeClose();

		assert(m_browser);
		m_browser = NULL;
		m_browserID = 0;
	}
	else
	{
		assert(false);
	}
}

bool WebKernelLifeSpanHandler::RunModal( CefRefPtr<CefBrowser> browser )
{
	return false;
}
