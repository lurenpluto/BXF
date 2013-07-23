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
*   FileName    :   WebKernelClient
*   Author      :   李亚星
*   Create      :   2013-6-6 
*   LastChange  :   2013-6-6
*   History     :	
*
*   Description :   CefClient的实现
*
********************************************************************/ 
#ifndef __WEBKERNELCLIENT_H__
#define __WEBKERNELCLIENT_H__

class WebKernelClient
	: public CefClient
{
public:
	WebKernelClient(void);
	virtual ~WebKernelClient(void);

	bool SetLifeSpanHandler(CefLifeSpanHandler* lpHandler);
	bool SetDisplayHandler(CefDisplayHandler* lpHandler);
	bool SetRenderHandler(CefRenderHandler* lpHandler);

private:

	// CefClient methods
	virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler();

	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler();

	virtual CefRefPtr<CefDownloadHandler> GetDownloadHandler();

	virtual CefRefPtr<CefFocusHandler> GetFocusHandler();

	virtual CefRefPtr<CefGeolocationHandler> GetGeolocationHandler();

	virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler();

	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler();

	virtual CefRefPtr<CefLoadHandler> GetLoadHandler();

	virtual CefRefPtr<CefRenderHandler> GetRenderHandler();

	virtual CefRefPtr<CefRequestHandler> GetRequestHandler();

	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message);

	IMPLEMENT_REFCOUNTING(WebKernelClient)

private:

	CefRefPtr<CefLifeSpanHandler> m_lifeSpanHandler;

	CefRefPtr<CefDisplayHandler> m_displayHandler;

	CefRefPtr<CefRenderHandler> m_renderHandler;
};

#endif // __WEBKERNELCLIENT_H__