/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./WebKernelBrowserManager.h"

WebKernelBrowserManager::WebKernelBrowserManager(void)
{
}

WebKernelBrowserManager::~WebKernelBrowserManager(void)
{
}

bool WebKernelBrowserManager::Register( CefBrowser* lpBrowser, BaseBoltBrowser* lpBoltBrowser, XLUE_LAYOUTOBJ_HANDLE hOwnerObj )
{
	assert(lpBrowser);
	assert(hOwnerObj == NULL || XLUE_IsObjValid(hOwnerObj));

	BrowserItem item;
	item.m_browserID = lpBrowser->GetIdentifier();
	item.m_browser = lpBrowser;
	item.m_owner = hOwnerObj;
	item.m_lpBoltBrowser = lpBoltBrowser;

	std::pair<mapBrowsers::iterator, bool> ret = m_browsers.insert(mapBrowsers::value_type(item.m_browserID, item));
	assert(ret.second);
	if (!ret.second)
	{
		return false;
	}

	OnBrowserCountChange(m_browsers.size());

	return true;
}

bool WebKernelBrowserManager::UnRegister( CefBrowser* lpBrowser )
{
	assert(lpBrowser);

	int browserID = lpBrowser->GetIdentifier();
	mapBrowsers::iterator cp = m_browsers.find(browserID);
	assert(cp != m_browsers.end());
	if (cp == m_browsers.end())
	{
		return false;
	}

	m_browsers.erase(cp);

	OnBrowserCountChange(m_browsers.size());

	return true;
}

CefBrowser* WebKernelBrowserManager::GetBrowserFromID( int browserID )
{
	mapBrowsers::iterator cp = m_browsers.find(browserID);
	if (cp == m_browsers.end())
	{
		return NULL;
	}

	return cp->second.m_browser.get();
}

XLUE_LAYOUTOBJ_HANDLE WebKernelBrowserManager::GetOwnerObjFromID( int browserID )
{
	mapBrowsers::iterator cp = m_browsers.find(browserID);
	if (cp == m_browsers.end())
	{
		return NULL;
	}

	return cp->second.m_owner;
}

BaseBoltBrowser* WebKernelBrowserManager::GetBoltBrowserFromID( int browserID )
{
	mapBrowsers::iterator cp = m_browsers.find(browserID);
	if (cp == m_browsers.end())
	{
		return NULL;
	}

	return cp->second.m_lpBoltBrowser;
}

void WebKernelBrowserManager::OnBrowserCountChange( size_t count )
{
	// TODO
}