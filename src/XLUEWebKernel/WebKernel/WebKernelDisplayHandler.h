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
*   FileName    :   WebKernelDisplayHandler
*   Author      :   李亚星
*   Create      :   2013-6-9 
*   LastChange  :   2013-6-9
*   History     :	
*
*   Description :   CefDisplayHandler的实现
*
********************************************************************/ 
#ifndef __WEBKERNELDISPLAYHANDLER_H__
#define __WEBKERNELDISPLAYHANDLER_H__

class BaseBoltBrowser;

class WebKernelDisplayHandler
	: public CefDisplayHandler
{
public:
	WebKernelDisplayHandler(BaseBoltBrowser* lpOwner);
	virtual ~WebKernelDisplayHandler(void);

private:

	// CefDisplayHandler methods
	virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading,
		bool canGoBack, bool canGoForward);
	
	virtual void OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
		const CefString& url);

	virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title);

	virtual bool OnTooltip(CefRefPtr<CefBrowser> browser, CefString& text);

	virtual void OnStatusMessage(CefRefPtr<CefBrowser> browser, const CefString& value);

	virtual bool OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString& message,
		const CefString& source, int line);

	IMPLEMENT_REFCOUNTING(WebKernelDisplayHandler);

private:

	BaseBoltBrowser* m_lpOwner;
};


#endif // __WEBKERNELDISPLAYHANDLER_H__