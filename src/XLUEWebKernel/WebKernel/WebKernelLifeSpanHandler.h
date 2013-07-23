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
*   FileName    :   WebKernelLifeSpanHandler
*   Author      :   李亚星
*   Create      :   2013-6-10 
*   LastChange  :   2013-6-10
*   History     :	
*
*   Description :   CefLifeSpan的实现类
*
********************************************************************/ 
#ifndef __WEBKERNELLIFESPANHANDLER_H__
#define __WEBKERNELLIFESPANHANDLER_H__

class BaseBoltBrowser;

class WebKernelLifeSpanHandler
	: public CefLifeSpanHandler
{
public:
	WebKernelLifeSpanHandler(BaseBoltBrowser* lpOwner);
	virtual ~WebKernelLifeSpanHandler(void);

private:

	// CefLifeSpanHandler methods
	virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& target_url,
		const CefString& target_frame_name,
		const CefPopupFeatures& popupFeatures,
		CefWindowInfo& windowInfo,
		CefRefPtr<CefClient>& client,
		CefBrowserSettings& settings,
		bool* no_javascript_access);
	virtual bool RunModal(CefRefPtr<CefBrowser> browser);
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser);
	virtual bool DoClose(CefRefPtr<CefBrowser> browser);
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser);

	IMPLEMENT_REFCOUNTING(WebKernelLifeSpanHandler);

private:

	CefRefPtr<CefBrowser> m_browser;
	int m_browserID;

	BaseBoltBrowser* m_lpOwner;
};

#endif // __WEBKERNELLIFESPANHANDLER_H__