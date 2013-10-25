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
*   FileName    :   BaseBoltBrowserObject
*   Author      :   李亚星
*   Create      :   2013-7-1 
*   LastChange  :   2013-7-1
*   History     :	
*
*   Description :   窗口和无窗口模式两种浏览器对象的共同基类，主要用以提供对BaseBoltBrowser的封装
*
********************************************************************/ 
#ifndef __BASEBOLTBROWSEROBJECT_H__
#define __BASEBOLTBROWSEROBJECT_H__

#include "../WebKernel/BaseBoltBrowser.h"
#include "./BaseBoltBrowserObjectEvents.h"

class BaseBoltBrowserObject
	: public BoltBrowserEvents
{
public:
	BaseBoltBrowserObject(void);
	virtual ~BaseBoltBrowserObject(void);

public:

	 // BaseBoltBrowser
	bool Navigate(const wchar_t* lpUrl);

	bool CanGoBack();
	void GoBack();

	bool CanGoForward();
	void GoForward();

	bool IsLoading();
	void Reload();
	void ReloadIgnoreCache();
	void StopLoad();

	bool HasDocument();

	CefRefPtr<CefFrame> GetMainFrame();
	CefRefPtr<CefFrame> GetFocusedFrame();
	CefRefPtr<CefFrame> GetFrame(const wchar_t* name); 

	// attribute
	void SetPopupInplace(bool popupInplace);
	bool GetPopupInplace();

protected:

	// BaseBoltBrowserEvents
	virtual void OnAfterCreated(bool& handled);
	virtual void OnBeforeClose(bool& handled);

	virtual void OnLoadingStateChange(bool isLoading, bool canGoBack, bool canGoForward, bool& handled);
	virtual void OnAddressChange(CefRefPtr<CefFrame> frame, const CefString& url, bool& handled);
	virtual void OnTitleChange(const CefString& title, bool& handled);
	virtual bool OnTooltip(CefString& text, bool& handled);
	virtual void OnStatusMessage(const CefString& value, bool& handled);
	virtual bool OnConsoleMessage(const CefString& message, const CefString& source, int line, bool& handled);

	virtual bool OnBeforeNavigation(CefRefPtr<CefFrame> frame, const CefString& url
		, cef_navigation_type_t navigation_type, bool is_redirect, bool& handled);
	virtual void OnFocusedNodeChanged(CefRefPtr<CefFrame> frame, bool& handled);

	virtual void OnBeforePopup(CefRefPtr<CefFrame> frame, const CefString& targetUrl
		, const CefString& targetFrameName, bool& handled);

	virtual void OnJavaScriptMessageReceived(const CefString messageName
		, CefRefPtr<CefListValue> argList,bool& handled);

protected:

	void Init(XLUE_LAYOUTOBJ_HANDLE hOwnerObj, BaseBoltBrowser* lpBaseBrowser, BaseBoltBrowserObjectEvents* lpEvents);
	void Uninit();

private:

	BaseBoltBrowser* m_lpBaseBrowser;
	BaseBoltBrowserObjectEvents* m_lpBaseBrowserObjectEvents;
	LayoutObjectWrapper m_obj;
};

#endif // __BASEBOLTBROWSEROBJECT_H__