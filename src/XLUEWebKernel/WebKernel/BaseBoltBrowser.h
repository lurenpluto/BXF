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
*   FileName    :   BaseBoltBrowser
*   Author      :   李亚星
*   Create      :   2013-6-10 
*   LastChange  :   2013-6-10
*   History     :	
*
*   Description :   浏览器的基础实现，不区分是不是无窗口模式
*
********************************************************************/ 
#ifndef __BASEBOLTBROWSER_H__
#define __BASEBOLTBROWSER_H__

#include "./WebKernelClient.h"
#include "./WebKernelDisplayHandler.h"
#include "./WebKernelLifeSpanHandler.h"

enum BrowserStatus
{
	BrowserStatus_initial = 0,
	BrowserStatus_creating = 1,
	BrowserStatus_created = 2,
	BrowserStatus_closing = 3,
	BrowserStatus_closed = 4
};

class BoltBrowserEvents
{
public:
	virtual ~BoltBrowserEvents() {}

	virtual void OnAfterCreated(bool& handled) = 0;
	virtual void OnBeforeClose(bool& handled) = 0;

	virtual void OnLoadingStateChange(bool isLoading, bool canGoBack, bool canGoForward, bool& handled) = 0;
	virtual void OnAddressChange(CefRefPtr<CefFrame> frame, const CefString& url, bool& handled) = 0;
	virtual void OnTitleChange(const CefString& title, bool& handled) = 0;
	virtual bool OnTooltip(CefString& text, bool& handled) = 0;
	virtual void OnStatusMessage(const CefString& value, bool& handled) = 0;
	virtual bool OnConsoleMessage(const CefString& message, const CefString& source, int line, bool& handled) = 0;

	virtual bool OnBeforeNavigation(CefRefPtr<CefFrame> frame, const CefString& url
		, cef_navigation_type_t navigation_type, bool is_redirect, bool& handled) = 0;
	virtual void OnFocusedNodeChanged(CefRefPtr<CefFrame> frame, bool& handled) = 0;

	virtual void OnBeforePopup(CefRefPtr<CefFrame> frame, const CefString& targetUrl
		, const CefString& targetFrameName, bool& handled) = 0;

	virtual void OnJavaScriptMessageReceived(const CefString messageName
		, CefRefPtr<CefDictionaryValue> dictionaryValue, bool& handled) = 0;
};

class BaseBoltBrowser
{
private:
	
	friend class WebKernelLifeSpanHandler;

protected:
	
	virtual ~BaseBoltBrowser(void);

public:
	BaseBoltBrowser(XLUE_LAYOUTOBJ_HANDLE hObj, BoltBrowserEvents* lpEvents);
	
	long AddRef();
	long Release();

	BrowserStatus GetStatus() const;
	
	bool Create(const CefWindowInfo& windowInfo);
	bool Close(bool force);

	void SetPopupInplace(bool popupInplace);
	bool GetPopupInplace();

public:

	// browser触发的事件
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

	virtual void OnJavaScriptMessageReceived(const CefString messageName,CefRefPtr<CefDictionaryValue> dictionaryValue, bool& handled);

public:

	// browser的控制方法
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

protected:

	// 子类可以重写的虚方法
	virtual void OnAfterCreated();
	virtual void OnBeforeClose();

	virtual void OnInitClient();
	virtual void OnUninitClient();

private:

	bool InitClient();
	bool UninitClient();

private:

	void SetStatus(BrowserStatus newStatus);

	// 生命周期相关方法，由lifespan负责通知
	void NotifyOnAfterCreated(CefBrowser* lpBrowser);
	bool NotifyDoClose();
	void NotifyOnBeforeClose();

protected:

	LayoutObjectWrapper m_obj;

	BoltBrowserEvents* m_lpEvents;

	CefRefPtr<CefBrowser> m_browser;

	CefRefPtr<WebKernelClient> m_client;

private:

	// 引用计数
	long m_ref;

	// 浏览器所处生命周期状态
	BrowserStatus m_status;

	CefRefPtr<WebKernelLifeSpanHandler> m_lifeSpanHandler;

	CefRefPtr<WebKernelDisplayHandler> m_displayHandler;

	bool m_closeOnCreate;

private:

	// 可配置属性

	// 初始url
	CefString m_url;

	// 是否在原浏览器控件上打开popup页面
	bool m_popupInplace;
};

#endif // __BASEBOLTBROWSER_H__