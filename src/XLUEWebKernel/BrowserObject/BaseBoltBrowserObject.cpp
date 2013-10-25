/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./BaseBoltBrowserObject.h"

BaseBoltBrowserObject::BaseBoltBrowserObject(void)
:m_lpBaseBrowser(NULL),
m_lpBaseBrowserObjectEvents(NULL)
{
}

BaseBoltBrowserObject::~BaseBoltBrowserObject(void)
{
	assert(m_lpBaseBrowser == NULL);
	assert(m_lpBaseBrowserObjectEvents == NULL);
}

void BaseBoltBrowserObject::Init( XLUE_LAYOUTOBJ_HANDLE hOwnerObj, BaseBoltBrowser* lpBaseBrowser, BaseBoltBrowserObjectEvents* lpEvents )
{
	assert(m_lpBaseBrowser == NULL);
	assert(lpBaseBrowser);
	assert(m_obj == NULL);
	assert(XLUE_IsObjValid(hOwnerObj));
	assert(lpEvents);
	assert(m_lpBaseBrowserObjectEvents == NULL);

	m_obj = hOwnerObj;

	m_lpBaseBrowser = lpBaseBrowser;
	m_lpBaseBrowser->AddRef();

	m_lpBaseBrowserObjectEvents = lpEvents;
	m_lpBaseBrowserObjectEvents->AddRef();
}

void BaseBoltBrowserObject::Uninit()
{
	assert(m_lpBaseBrowser);
	m_lpBaseBrowser->Release();
	m_lpBaseBrowser = NULL;

	assert(m_lpBaseBrowserObjectEvents);
	m_lpBaseBrowserObjectEvents->Release();
	m_lpBaseBrowserObjectEvents = NULL;

	assert(m_obj);
	m_obj.Detach();
}

bool BaseBoltBrowserObject::Navigate( const wchar_t* lpUrl )
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return false;
	}

	return m_lpBaseBrowser->Navigate(lpUrl);
}

bool BaseBoltBrowserObject::CanGoBack()
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return false;
	}

	return m_lpBaseBrowser->CanGoBack();
}

void BaseBoltBrowserObject::GoBack()
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return;
	}

	return m_lpBaseBrowser->GoBack();
}

bool BaseBoltBrowserObject::CanGoForward()
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return false;
	}

	return m_lpBaseBrowser->CanGoForward();
}

void BaseBoltBrowserObject::GoForward()
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return;
	}

	return m_lpBaseBrowser->GoForward();
}

bool BaseBoltBrowserObject::IsLoading()
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return false;
	}

	return m_lpBaseBrowser->IsLoading();
}

void BaseBoltBrowserObject::Reload()
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return;
	}

	return m_lpBaseBrowser->Reload();
}

void BaseBoltBrowserObject::ReloadIgnoreCache()
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return;
	}

	return m_lpBaseBrowser->ReloadIgnoreCache();
}

void BaseBoltBrowserObject::StopLoad()
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return;
	}

	return m_lpBaseBrowser->StopLoad();
}

bool BaseBoltBrowserObject::HasDocument()
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return false;
	}

	return m_lpBaseBrowser->HasDocument();
}

CefRefPtr<CefFrame> BaseBoltBrowserObject::GetMainFrame()
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return NULL;
	}

	return m_lpBaseBrowser->GetMainFrame();
}

CefRefPtr<CefFrame> BaseBoltBrowserObject::GetFocusedFrame()
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return NULL;
	}

	return m_lpBaseBrowser->GetFocusedFrame();
}

CefRefPtr<CefFrame> BaseBoltBrowserObject::GetFrame( const wchar_t* name )
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return NULL;
	}

	return m_lpBaseBrowser->GetFrame(name);
}

void BaseBoltBrowserObject::SetPopupInplace( bool popupInplace )
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return;
	}

	return m_lpBaseBrowser->SetPopupInplace(popupInplace);
}

bool BaseBoltBrowserObject::GetPopupInplace()
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return false;
	}

	return m_lpBaseBrowser->GetPopupInplace();
}

void BaseBoltBrowserObject::OnAfterCreated(bool& handled)
{
	assert(m_lpBaseBrowserObjectEvents);
	if (m_obj.IsValid())
	{
		m_lpBaseBrowserObjectEvents->OnAfterCreated(handled);
	}
}

void BaseBoltBrowserObject::OnBeforeClose(bool& handled)
{
	assert(m_lpBaseBrowserObjectEvents);
	if (m_obj.IsValid())
	{
		m_lpBaseBrowserObjectEvents->OnBeforeClose(handled);
	}
}

void BaseBoltBrowserObject::OnLoadingStateChange( bool isLoading, bool canGoBack, bool canGoForward, bool& handled )
{
	assert(m_lpBaseBrowserObjectEvents);

	m_lpBaseBrowserObjectEvents->OnLoadingStateChange(isLoading, canGoBack, canGoForward, handled);
}

void BaseBoltBrowserObject::OnAddressChange( CefRefPtr<CefFrame> frame, const CefString& url, bool& handled )
{
	assert(m_lpBaseBrowserObjectEvents);

	m_lpBaseBrowserObjectEvents->OnAddressChange(frame, url, handled);
}

void BaseBoltBrowserObject::OnTitleChange( const CefString& title, bool& handled )
{
	assert(m_lpBaseBrowserObjectEvents);

	m_lpBaseBrowserObjectEvents->OnTitleChange(title, handled);
}

bool BaseBoltBrowserObject::OnTooltip( CefString& text, bool& handled )
{
	assert(m_lpBaseBrowserObjectEvents);

	m_lpBaseBrowserObjectEvents->OnTooltip(text, handled);

	return false;
}

void BaseBoltBrowserObject::OnStatusMessage( const CefString& value, bool& handled )
{
	assert(m_lpBaseBrowserObjectEvents);

	//TODO
}

bool BaseBoltBrowserObject::OnConsoleMessage( const CefString& message, const CefString& source, int line, bool& handled )
{
	assert(m_lpBaseBrowserObjectEvents);

	return false;
}

bool BaseBoltBrowserObject::OnBeforeNavigation( CefRefPtr<CefFrame> frame, const CefString& url 
										 , cef_navigation_type_t navigation_type, bool is_redirect, bool& handled )
{
	assert(m_lpBaseBrowserObjectEvents);

	bool canceled = false;
	m_lpBaseBrowserObjectEvents->OnBeforeNavigation(frame, url, navigation_type, is_redirect, canceled, handled);

	return canceled;
}

void BaseBoltBrowserObject::OnFocusedNodeChanged( CefRefPtr<CefFrame> frame, bool& handled )
{
	assert(m_lpBaseBrowserObjectEvents);

	m_lpBaseBrowserObjectEvents->OnFocusedNodeChanged(frame, handled);
}

void BaseBoltBrowserObject::OnBeforePopup( CefRefPtr<CefFrame> frame, const CefString& targetUrl
									, const CefString& targetFrameName, bool& handled )
{
	assert(m_lpBaseBrowserObjectEvents);

	m_lpBaseBrowserObjectEvents->OnBeforePopup(frame, targetUrl, targetFrameName, handled);
}

void BaseBoltBrowserObject::OnJavaScriptMessageReceived(const CefString messageName, CefRefPtr<CefListValue> argList,bool& handled)
{
	assert(m_lpBaseBrowserObjectEvents);

	m_lpBaseBrowserObjectEvents->OnJavaScriptMessageReceived(messageName,argList, handled);
}
