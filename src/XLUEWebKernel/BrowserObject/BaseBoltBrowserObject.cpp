/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./BaseBoltBrowserObject.h"
#include "../BrowserObjectLuaHost/LuaJavascriptFunctor.h"
#include "../WebKernel/DBG.h"
#include "../WebKernel/WebKernelScriptIPCMessage.h"

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

void BaseBoltBrowserObject::RegisterLuaFunction(std::wstring functionName,LuaJavascriptFunctor functor)
{
	m_luaFunctorMap.insert(std::pair<std::wstring,LuaJavascriptFunctor>(functionName,functor));
}

bool BaseBoltBrowserObject::RemoveLuaFunction(std::wstring functionName)
{
	JavascriptFunctorMap::iterator it = m_luaFunctorMap.find(functionName);
	if (it != m_luaFunctorMap.end()) 
	{
		m_luaFunctorMap.erase(it);
		return true;
	}

	return false;
}

void BaseBoltBrowserObject::RegisterLuaCallbackFunctor(std::wstring functionName,LuaJavascriptCallbackFunctor functor)
{
	m_luaCallbackFunctorMap.insert(std::pair<std::wstring,LuaJavascriptCallbackFunctor>(functionName,functor));
}

bool BaseBoltBrowserObject::RemoveLuaCallbackFunction(std::wstring functionName)
{
	JavascriptCallbackFunctorMap::iterator it = m_luaCallbackFunctorMap.find(functionName);
	if (it != m_luaCallbackFunctorMap.end()) 
	{
		m_luaCallbackFunctorMap.erase(it);
		return true;
	}

	return false;
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

bool BaseBoltBrowserObject::CallJavascriptFunction( const CefString& functionName, CefRefPtr<CefDictionaryValue> dictionaryValue, LuaJavascriptCallbackFunctor functor)
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return NULL;
	}

	std::wstring wrapJavascriptFunctionName = WebKernelScriptIPCMessage::WrapLuaCallName(functionName);
	RegisterLuaCallbackFunctor(wrapJavascriptFunctionName,functor);

	return m_lpBaseBrowser->CallJavascriptFunction(wrapJavascriptFunctionName,dictionaryValue);
}

bool BaseBoltBrowserObject::SendMessageToJavascript( const CefString& messageName, CefRefPtr<CefDictionaryValue> dictionaryValue )
{
	assert(m_lpBaseBrowser);
	if (m_lpBaseBrowser == NULL)
	{
		return NULL;
	}

	return m_lpBaseBrowser->SendMessageToJavascript(messageName,dictionaryValue);
}

void BaseBoltBrowserObject::OnJavaScriptMessageReceived(const CefString messageName, CefRefPtr<CefDictionaryValue> dictionaryValue,bool& handled)
{
	assert(m_lpBaseBrowserObjectEvents);

	m_lpBaseBrowserObjectEvents->OnJavaScriptMessageReceived(messageName,dictionaryValue, handled);
}

CefRefPtr<CefDictionaryValue> BaseBoltBrowserObject::OnJavascriptCallMessageReceived(std::wstring functionName,CefRefPtr<CefDictionaryValue> dictionaryValue,bool& handled)
{
	handled = false;
	JavascriptFunctorMap::iterator it = m_luaFunctorMap.find(functionName);
	if (it != m_luaFunctorMap.end()) 
	{
		LuaJavascriptFunctor functor = it->second;
		CefRefPtr<CefDictionaryValue> result = functor(dictionaryValue);
		handled = true;
		return result;
	}
	return CefDictionaryValue::Create();
}

void BaseBoltBrowserObject::OnLuaCallbackMessageRecevied(CefString luaFunctionName,  CefRefPtr<CefDictionaryValue> dictionaryValue, bool& handled )
{
	handled = false;
	JavascriptCallbackFunctorMap::iterator it = m_luaCallbackFunctorMap.find(luaFunctionName);
	if (it != m_luaCallbackFunctorMap.end()) 
	{
		LuaJavascriptCallbackFunctor functor = it->second;
		handled = functor(dictionaryValue);

		RemoveLuaCallbackFunction(luaFunctionName.ToWString());
	}
}

