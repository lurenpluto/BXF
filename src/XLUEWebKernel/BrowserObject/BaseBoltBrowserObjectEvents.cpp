/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./BaseBoltBrowserObjectEvents.h"
#include "../BrowserObjectLuaHost/LuaFrame.h"
#include "../BrowserObjectLuaHost/WebKernelLuaHelper.h"

IMPL_EXT_EVENT(BaseBoltBrowserObjectEvents, OnAfterCreated);
IMPL_EXT_EVENT(BaseBoltBrowserObjectEvents, OnBeforeClose);
IMPL_EXT_EVENT(BaseBoltBrowserObjectEvents, OnBeforePopup);

IMPL_EXT_EVENT(BaseBoltBrowserObjectEvents, OnLoadingStateChange);
IMPL_EXT_EVENT(BaseBoltBrowserObjectEvents, OnAddressChange);
IMPL_EXT_EVENT(BaseBoltBrowserObjectEvents, OnTitleChange);
IMPL_EXT_EVENT(BaseBoltBrowserObjectEvents, OnTooltip);

IMPL_EXT_EVENT(BaseBoltBrowserObjectEvents, OnBeforeNavigation);
IMPL_EXT_EVENT(BaseBoltBrowserObjectEvents, OnFocusedNodeChanged);

IMPL_EXT_EVENT(BaseBoltBrowserObjectEvents, OnJavaScriptMessageReceived);

BEGIN_EXT_EVENT_VECTOR(BaseBoltBrowserObjectEvents)
	EXT_EVENT_ITEM(OnAfterCreated)
	EXT_EVENT_ITEM(OnBeforeClose)
	EXT_EVENT_ITEM(OnBeforePopup)

	EXT_EVENT_ITEM(OnLoadingStateChange)
	EXT_EVENT_ITEM(OnAddressChange)
	EXT_EVENT_ITEM(OnTitleChange)
	EXT_EVENT_ITEM(OnTooltip)

	EXT_EVENT_ITEM(OnBeforeNavigation)
	EXT_EVENT_ITEM(OnFocusedNodeChanged)

	EXT_EVENT_ITEM(OnJavaScriptMessageReceived)
END_EXT_EVENT_VECTOR()

BaseBoltBrowserObjectEvents::BaseBoltBrowserObjectEvents(XLUE_LAYOUTOBJ_HANDLE hObj)
:m_obj(hObj),
m_ref(1)
{
	assert(m_obj.IsValid());
	XL_LRT_ENV_HANDLE hEnv = XLLRT_GetEnv(NULL);
	XL_LRT_RUNTIME_HANDLE hRunTime = XLLRT_GetRuntime(hEnv, NULL);
	m_luaState = XLLRT_GetLuaState(hRunTime);
	assert(m_luaState);

	XLLRT_ReleaseRunTime(hRunTime);
	XLLRT_ReleaseEnv(hEnv);
}

BaseBoltBrowserObjectEvents::~BaseBoltBrowserObjectEvents(void)
{
	assert(m_luaState);
	m_luaState = NULL;

	assert(m_obj.IsValid());
	m_obj = NULL;
}

long BaseBoltBrowserObjectEvents::AddRef()
{
	assert(m_ref >= 0);

	return ++m_ref;
}

long BaseBoltBrowserObjectEvents::Release()
{
	assert(m_ref >= 1);
	long ret = --m_ref;
	if (m_ref <= 0)
	{
		delete this;
	}

	return ret;
}

void BaseBoltBrowserObjectEvents::OnLoadingStateChange( bool isLoading, bool canGoBack, bool canGoForward, bool& handled )
{
	LuaStackKeeper luaState(m_luaState);

	XLUE_PushObject(luaState, m_obj);
	lua_pushboolean(luaState, isLoading);
	lua_pushboolean(luaState, canGoBack);
	lua_pushboolean(luaState, canGoForward);

	BOOL isHandled = FALSE;
	XLUE_FireExtObjEvent(m_obj, s_OnLoadingStateChange, luaState, 4, 0, &isHandled);

	handled = !!isHandled;
}

void BaseBoltBrowserObjectEvents::OnAfterCreated(bool& handled)
{
	LuaStackKeeper luaState(m_luaState);

	XLUE_PushObject(luaState, m_obj);

	BOOL isHandled = FALSE;
	XLUE_FireExtObjEvent(m_obj, s_OnAfterCreated, luaState, 1, 0, &isHandled);

	handled = !!isHandled;
}

void BaseBoltBrowserObjectEvents::OnBeforeClose(bool& handled)
{
	LuaStackKeeper luaState(m_luaState);

	XLUE_PushObject(luaState, m_obj);

	BOOL isHandled = FALSE;
	XLUE_FireExtObjEvent(m_obj, s_OnBeforeClose, luaState, 1, 0, &isHandled);

	handled = !!isHandled;
}

void BaseBoltBrowserObjectEvents::OnBeforePopup( CefRefPtr<CefFrame> frame, const CefString& target_url
												, const CefString& target_frame_name, bool& handled )
{
	LuaStackKeeper luaState(m_luaState);

	XLUE_PushObject(luaState, m_obj);

	LuaFrame::PushFrame(luaState, frame);

	WebKernelLuaHelper::PushCefString(luaState, target_url);
	WebKernelLuaHelper::PushCefString(luaState, target_frame_name);

	BOOL isHandled = FALSE;
	XLUE_FireExtObjEvent(m_obj, s_OnBeforePopup, luaState, 4, 0, &isHandled);

	handled = !!isHandled;
}

void BaseBoltBrowserObjectEvents::OnAddressChange( CefRefPtr<CefFrame> frame, const CefString& url, bool& handled )
{
	LuaStackKeeper luaState(m_luaState);

	XLUE_PushObject(luaState, m_obj);

	LuaFrame::PushFrame(luaState, frame);
	WebKernelLuaHelper::PushCefString(luaState, url);

	BOOL isHandled = FALSE;
	XLUE_FireExtObjEvent(m_obj, s_OnAddressChange, luaState, 3, 0, &isHandled);

	handled = !!isHandled;
}

void BaseBoltBrowserObjectEvents::OnTitleChange( const CefString& title, bool& handled )
{
	LuaStackKeeper luaState(m_luaState);

	XLUE_PushObject(luaState, m_obj);

	WebKernelLuaHelper::PushCefString(luaState, title);

	BOOL isHandled = FALSE;
	XLUE_FireExtObjEvent(m_obj, s_OnTitleChange, luaState, 2, 0, &isHandled);

	handled = !!isHandled;
}

void BaseBoltBrowserObjectEvents::OnTooltip( CefString& text, bool& handled )
{
	LuaStackKeeper luaState(m_luaState);

	XLUE_PushObject(luaState, m_obj);

	WebKernelLuaHelper::PushCefString(luaState, text);

	BOOL isHandled = FALSE;
	XLUE_FireExtObjEvent(m_obj, s_OnTooltip, luaState, 2, 0, &isHandled);

	handled = !!isHandled;
}

void BaseBoltBrowserObjectEvents::OnBeforeNavigation( CefRefPtr<CefFrame> frame, const CefString& url 
													 , cef_navigation_type_t navigation_type, bool is_redirect
													 , bool& canceled, bool& handled )
{
	LuaStackKeeper luaState(m_luaState);

	XLUE_PushObject(luaState, m_obj);

	LuaFrame::PushFrame(luaState, frame);
	WebKernelLuaHelper::PushCefString(luaState, url);
	lua_pushinteger(luaState, navigation_type);
	lua_pushboolean(luaState, is_redirect);

	BOOL isHandled = FALSE;
	long ret = XLUE_FireExtObjEvent(m_obj, s_OnBeforeNavigation, luaState, 5, 2, &isHandled);

	canceled = LuaHelper::GetBoolValue(luaState, -1, canceled);

	handled = !!isHandled;
}

void BaseBoltBrowserObjectEvents::OnFocusedNodeChanged( CefRefPtr<CefFrame> frame, bool& handled )
{
	LuaStackKeeper luaState(m_luaState);

	XLUE_PushObject(luaState, m_obj);
	LuaFrame::PushFrame(luaState, frame);

	BOOL isHandled = FALSE;
	long ret = XLUE_FireExtObjEvent(m_obj, s_OnFocusedNodeChanged, luaState, 2, 0, &isHandled);

	handled = !!isHandled;
}

void BaseBoltBrowserObjectEvents::OnJavaScriptMessageReceived(const CefString messageName, CefRefPtr<CefDictionaryValue> dictionaryValue,bool& handled)
{
	LuaStackKeeper luaState(m_luaState);
	
	XLUE_PushObject(luaState,m_obj);                                       // 传入浏览器对象
	WebKernelLuaHelper::PushCefString(luaState,messageName);               // 传入Javascript消息名字
	WebKernelLuaHelper::PushCefDictionaryValue(luaState,dictionaryValue);  // 传入Javascript消息字典

	BOOL isHandled = FALSE;
	long ret = XLUE_FireExtObjEvent(m_obj,s_OnJavaScriptMessageReceived,luaState,3,0,&isHandled);

	handled = !!isHandled;
}