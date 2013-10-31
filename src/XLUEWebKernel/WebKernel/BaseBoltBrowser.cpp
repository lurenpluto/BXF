/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./BaseBoltBrowser.h"

BaseBoltBrowser::BaseBoltBrowser( XLUE_LAYOUTOBJ_HANDLE hObj, BoltBrowserEvents* lpEvents )
:m_obj(hObj),
m_lpEvents(lpEvents),
m_ref(1),
m_status(BrowserStatus_initial),
m_closeOnCreate(false),
m_popupInplace(true),
m_url(L"about:blank")
{
	assert(m_lpEvents);
}

BaseBoltBrowser::~BaseBoltBrowser(void)
{
	assert(m_obj.IsValid());

	assert(m_lpEvents);
	m_lpEvents = NULL;

	assert(m_ref == 0);
}

long BaseBoltBrowser::AddRef()
{
	assert(m_ref >= 0);
	return ++m_ref;
}

long BaseBoltBrowser::Release()
{
	assert(m_ref > 0);
	long ret = --m_ref;
	if (m_ref <= 0)
	{
		delete this;
	}

	return ret;
}

bool BaseBoltBrowser::InitClient()
{
	assert(m_client == NULL);

	m_client = new WebKernelClient();
	
	OnInitClient();

	return true;
}

bool BaseBoltBrowser::UninitClient()
{
	OnUninitClient();

	assert(m_client);
	m_client = NULL;

	return true;
}

void BaseBoltBrowser::NotifyOnAfterCreated( CefBrowser* lpBrowser )
{
	assert(m_browser == NULL);
	assert(lpBrowser);

	m_browser = lpBrowser;

	g_webKernelGlobal.m_browserManager.Register(lpBrowser, this, m_obj);

	assert(GetStatus() == BrowserStatus_creating);

	OnAfterCreated();

	assert(GetStatus() == BrowserStatus_creating);
	SetStatus(BrowserStatus_created);

	// 在创建过程中被close了
	if (m_closeOnCreate)
	{
		m_closeOnCreate = false;
		Close(true);
	}
}

bool BaseBoltBrowser::NotifyDoClose()
{
	assert(m_browser);
	m_browser->GetHost()->ParentWindowWillClose();

	assert(GetStatus() == BrowserStatus_created);
	SetStatus(BrowserStatus_closing);

	return false;
}

void BaseBoltBrowser::NotifyOnBeforeClose()
{
	assert(GetStatus() == BrowserStatus_closing);

	OnBeforeClose();

	g_webKernelGlobal.m_browserManager.UnRegister(m_browser);

	assert(m_browser);
	m_browser = NULL;

	g_webKernelGlobal.m_msgLoop.DecreaseBrowserUser();

	assert(GetStatus() == BrowserStatus_closing);
	SetStatus(BrowserStatus_closed);

	Release();
}

void BaseBoltBrowser::SetStatus( BrowserStatus newStatus )
{
	if (m_status != newStatus)
	{
		m_status = newStatus;
	}
}

BrowserStatus BaseBoltBrowser::GetStatus() const
{
	return m_status;
}

bool BaseBoltBrowser::Create( const CefWindowInfo& windowInfo )
{
	assert(m_browser == NULL);
	assert(GetStatus() == BrowserStatus_initial 
		|| GetStatus() == BrowserStatus_closed);

	if (GetStatus() != BrowserStatus_initial
		&& GetStatus() != BrowserStatus_closed)
	{
		return false;
	}

	assert(m_client == NULL);
	InitClient();
	assert(m_client);

	CefBrowserSettings settings;

	bool ret = CefBrowserHost::CreateBrowser(windowInfo, m_client.get(), m_url, settings);
	assert(ret);
	if (!ret)
	{
		UninitClient();

		return false;
	}

	g_webKernelGlobal.m_msgLoop.IncreaseBrowserUser();

	SetStatus(BrowserStatus_creating);

	// 创建后到销毁完毕，整个周期需要加锁保护
	AddRef();

	return true;
}

bool BaseBoltBrowser::Close(bool force)
{
	// 开始创建但是尚未创建完毕
	if (GetStatus() == BrowserStatus_creating)
	{
		m_closeOnCreate = true;
	}
	else if (GetStatus() == BrowserStatus_created)
	{
		assert(m_browser);
		if (m_browser != NULL)
		{
			SetStatus(BrowserStatus_closing);
			m_browser->GetHost()->CloseBrowser(force);
		}
	}

	return true;
}

void BaseBoltBrowser::OnAfterCreated()
{
	assert(m_lpEvents);
	if (m_obj.IsValid())
	{
		bool handled = false;
		m_lpEvents->OnAfterCreated(handled);
	}
}

void BaseBoltBrowser::OnBeforeClose()
{
	assert(m_lpEvents);
	if (m_obj.IsValid())
	{
		bool handled = false;
		m_lpEvents->OnBeforeClose(handled);
	}
}

void BaseBoltBrowser::OnInitClient()
{
	assert(m_client);

	m_lifeSpanHandler = new WebKernelLifeSpanHandler(this);
	m_client->SetLifeSpanHandler(m_lifeSpanHandler.get());

	m_displayHandler = new WebKernelDisplayHandler(this);
	m_client->SetDisplayHandler(m_displayHandler.get());
}

void BaseBoltBrowser::OnUninitClient()
{
	assert(m_client);
	m_client->SetDisplayHandler(NULL);
	m_client->SetLifeSpanHandler(NULL);

	assert(m_lifeSpanHandler);
	m_lifeSpanHandler = NULL;

	assert(m_displayHandler);
	m_displayHandler = NULL;
}

void BaseBoltBrowser::OnBeforePopup( CefRefPtr<CefFrame> frame, const CefString& targetUrl
									, const CefString& targetFrameName, bool& handled )
{
	handled = false;
	m_lpEvents->OnBeforePopup(frame, targetUrl, targetFrameName, handled);

	if (!handled && m_popupInplace)
	{
		Navigate(targetUrl.c_str());
	}
}

void BaseBoltBrowser::SetPopupInplace( bool popupInplace )
{
	m_popupInplace = popupInplace;
}

bool BaseBoltBrowser::GetPopupInplace()
{
	return m_popupInplace;
}

bool BaseBoltBrowser::CanGoBack()
{
	assert(m_browser);
	if (m_browser == NULL)
	{
		return false;
	}

	return m_browser->CanGoBack();
}

void BaseBoltBrowser::GoBack()
{
	assert(m_browser);
	if (m_browser == NULL)
	{
		return;
	}

	return m_browser->GoBack();
}

bool BaseBoltBrowser::CanGoForward()
{
	assert(m_browser);
	if (m_browser == NULL)
	{
		return false;
	}

	return m_browser->CanGoForward();
}

void BaseBoltBrowser::GoForward()
{
	assert(m_browser);
	if (m_browser == NULL)
	{
		return;
	}

	return m_browser->GoForward();
}

bool BaseBoltBrowser::IsLoading()
{
	assert(m_browser);
	if (m_browser == NULL)
	{
		return false;
	}

	return m_browser->IsLoading();
}

void BaseBoltBrowser::Reload()
{
	assert(m_browser);
	if (m_browser == NULL)
	{
		return;
	}

	return m_browser->Reload();
}

void BaseBoltBrowser::ReloadIgnoreCache()
{
	assert(m_browser);
	if (m_browser == NULL)
	{
		return;
	}

	return m_browser->ReloadIgnoreCache();
}

void BaseBoltBrowser::StopLoad()
{
	assert(m_browser);
	if (m_browser == NULL)
	{
		return;
	}

	return m_browser->StopLoad();
}

bool BaseBoltBrowser::Navigate( const wchar_t* lpUrl )
{
	if (lpUrl != NULL)
	{
		m_url = lpUrl;
	}
	else
	{
		m_url.clear();
	}

	if (m_browser != NULL)
	{
		m_browser->GetMainFrame()->LoadURL(m_url);
	}

	return true;
}

bool BaseBoltBrowser::HasDocument()
{
	assert(m_browser);
	if (m_browser == NULL)
	{
		return false;
	}

	return m_browser->HasDocument();
}

CefRefPtr<CefFrame> BaseBoltBrowser::GetMainFrame()
{
	assert(m_browser);
	if (m_browser == NULL)
	{
		return NULL;
	}

	return m_browser->GetMainFrame();
}

CefRefPtr<CefFrame> BaseBoltBrowser::GetFocusedFrame()
{
	assert(m_browser);
	if (m_browser == NULL)
	{
		return NULL;
	}

	return m_browser->GetFocusedFrame();
}

CefRefPtr<CefFrame> BaseBoltBrowser::GetFrame( const wchar_t* name )
{
	assert(m_browser);
	if (m_browser == NULL)
	{
		return NULL;
	}

	CefString strName = name;

	return m_browser->GetFrame(strName);
}

void BaseBoltBrowser::OnLoadingStateChange( bool isLoading, bool canGoBack, bool canGoForward, bool& handled )
{
	assert(m_lpEvents);

	m_lpEvents->OnLoadingStateChange(isLoading, canGoBack, canGoForward, handled);
}

void BaseBoltBrowser::OnAddressChange( CefRefPtr<CefFrame> frame, const CefString& url, bool& handled )
{
	assert(m_lpEvents);

	m_lpEvents->OnAddressChange(frame, url, handled);
}

void BaseBoltBrowser::OnTitleChange( const CefString& title, bool& handled )
{
	assert(m_lpEvents);

	m_lpEvents->OnTitleChange(title, handled);
}

bool BaseBoltBrowser::OnTooltip( CefString& text, bool& handled )
{
	assert(m_lpEvents);

	return m_lpEvents->OnTooltip(text, handled);
}

void BaseBoltBrowser::OnStatusMessage( const CefString& value, bool& handled )
{
	assert(m_lpEvents);

	m_lpEvents->OnStatusMessage(value, handled);
}

bool BaseBoltBrowser::OnConsoleMessage( const CefString& message, const CefString& source, int line, bool& handled )
{
	assert(m_lpEvents);

	return m_lpEvents->OnConsoleMessage(message, source, line, handled);
}

bool BaseBoltBrowser::OnBeforeNavigation( CefRefPtr<CefFrame> frame, const CefString& url 
										 , cef_navigation_type_t navigation_type, bool is_redirect, bool& handled )
{
	assert(m_lpEvents);

	return m_lpEvents->OnBeforeNavigation(frame, url, navigation_type, is_redirect, handled);
}

void BaseBoltBrowser::OnFocusedNodeChanged( CefRefPtr<CefFrame> frame, bool& handled )
{
	assert(m_lpEvents);

	m_lpEvents->OnFocusedNodeChanged(frame, handled);
}

void BaseBoltBrowser::OnJavaScriptMessageReceived(const CefString messageName, CefRefPtr<CefDictionaryValue> dictionaryValue,bool& handled)
{
	assert(m_lpEvents);
	m_lpEvents->OnJavaScriptMessageReceived(messageName,dictionaryValue,handled);
}

CefRefPtr<CefDictionaryValue> BaseBoltBrowser::OnJavascriptCallMessageRecivied( CefString luaFunctionName, CefRefPtr<CefDictionaryValue> dictionaryValue,bool& handled)
{
	assert(m_lpEvents);
	return m_lpEvents->OnJavascriptCallMessageReceived(luaFunctionName.ToWString(),dictionaryValue,handled);
}

void BaseBoltBrowser::OnLuaCallbackMessageRecevied( CefString luaFunctionName, CefRefPtr<CefDictionaryValue> dictionaryValue, bool& handled )
{
	assert(m_lpEvents);

	m_lpEvents->OnLuaCallbackMessageRecevied(luaFunctionName,dictionaryValue,handled);
}

bool BaseBoltBrowser::CallJavascriptFunction( const CefString& functionName, CefRefPtr<CefDictionaryValue> dictionaryValue )
{
	assert(m_browser);
	if (m_browser == NULL)
	{
		return NULL;
	}

	assert(m_client);
	if (m_client == NULL)
	{
		return NULL;
	}

	return m_client->GetJavascriptHandler()->CallJavascriptFunction(m_browser,functionName,dictionaryValue);
}

bool BaseBoltBrowser::SendMessageToJavascript( const CefString& messageName, CefRefPtr<CefDictionaryValue> dictionaryValue )
{
	assert(m_browser);
	if (m_browser == NULL)
	{
		return NULL;
	}

	assert(m_client);
	if (m_client == NULL)
	{
		return NULL;
	}

	return m_client->GetJavascriptHandler()->SendMessageToJavascript(m_browser,messageName,dictionaryValue);
}