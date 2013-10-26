/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2013              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   BaseBoltBrowserObjectEvents
*   Author      :   李亚星
*   Create      :   2013-6-26 
*   LastChange  :   2013-6-26
*   History     :	
*
*   Description :   BoltBrowserObject和WindowlessBoltBrowserObject的事件基类，通用事件需要
*					在这里实现，并使用DECLEAR_EXT_EVENT声明
*
********************************************************************/ 
#ifndef __BASEBOLTBROWSEROBJECTEVENTS_H__
#define __BASEBOLTBROWSEROBJECTEVENTS_H__

class BaseBoltBrowserObjectEvents
{
protected:
	virtual ~BaseBoltBrowserObjectEvents(void);

public:
	BaseBoltBrowserObjectEvents(XLUE_LAYOUTOBJ_HANDLE hObj);
	
	long AddRef();
	long Release();

public:

	// lifespan 
	void OnAfterCreated(bool& handled);
	void OnBeforeClose(bool& handled);
	void OnBeforePopup(CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name, bool& handled);

	// displayhandler
	void OnLoadingStateChange(bool isLoading, bool canGoBack, bool canGoForward, bool& handled);
	void OnAddressChange(CefRefPtr<CefFrame> frame, const CefString& url, bool& handled);
	void OnTitleChange(const CefString& title, bool& handled);
	void OnTooltip(CefString& text, bool& handled);

	void OnBeforeNavigation(CefRefPtr<CefFrame> frame, const CefString& url
		, cef_navigation_type_t navigation_type, bool is_redirect,
		bool& canceled, bool& handled);

	void OnFocusedNodeChanged(CefRefPtr<CefFrame> frame, bool& handled);

	void OnJavaScriptMessageReceived(const CefString messageName, CefRefPtr<CefDictionaryValue> dictionaryValue, bool& handled);

protected:

	DECLEAR_EXT_EVENT_VECTOR();

	// 通用事件需要在基类里面声明！！
	DECLEAR_EXT_EVENT(OnAfterCreated);
	DECLEAR_EXT_EVENT(OnBeforeClose);
	DECLEAR_EXT_EVENT(OnBeforePopup);

	DECLEAR_EXT_EVENT(OnLoadingStateChange);
	DECLEAR_EXT_EVENT(OnAddressChange);
	DECLEAR_EXT_EVENT(OnTitleChange);
	DECLEAR_EXT_EVENT(OnTooltip);

	DECLEAR_EXT_EVENT(OnBeforeNavigation);
	DECLEAR_EXT_EVENT(OnFocusedNodeChanged);

	DECLEAR_EXT_EVENT(OnJavaScriptMessageReceived);

protected:

	long m_ref;

	lua_State* m_luaState;
	LayoutObjectWrapper m_obj;
};

#endif // __BASEBOLTBROWSEROBJECTEVENTS_H__