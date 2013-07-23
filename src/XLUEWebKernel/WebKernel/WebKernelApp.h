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
*   FileName    :   WebKernelApp
*   Author      :   李亚星
*   Create      :   2013-6-4 
*   LastChange  :   2013-6-4
*   History     :	
*
*   Description :   cefapp的实现
*
********************************************************************/ 
#ifndef __WEBKERNELAPP_H__
#define __WEBKERNELAPP_H__

class WebKernelBrowserProcessHandler;
class WebKernelRenderProcessHandler;

class WebKernelApp
	: public CefApp
{
public:
	WebKernelApp(void);
	virtual ~WebKernelApp(void);

	bool Init();
	bool Uninit();

private:

	// CefApp
	virtual void OnBeforeCommandLineProcessing(
		const CefString& process_type,
		CefRefPtr<CefCommandLine> command_line);

	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler();

	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler();

	IMPLEMENT_REFCOUNTING(WebKernelApp);

private:

	CefRefPtr<WebKernelBrowserProcessHandler> m_spBrowserProcessHandler;
	CefRefPtr<WebKernelRenderProcessHandler> m_spRenderProcessHandler;
};

class WebKernelBrowserProcessHandler
	: public CefBrowserProcessHandler
{
public:
	WebKernelBrowserProcessHandler();
	virtual ~WebKernelBrowserProcessHandler();

	// CefBrowserProcessHandler
	virtual void OnContextInitialized();
	virtual void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line);
	virtual void OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extra_info);

	IMPLEMENT_REFCOUNTING(WebKernelBrowserProcessHandler);

private:

	unsigned long m_renderServerNextID;
};

class WebKernelRenderProcessHandler
	: public CefRenderProcessHandler
{
public:

	// CefRenderProcessHandler
	virtual void OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info);
	virtual void OnWebKitInitialized();

	virtual void OnBrowserCreated(CefRefPtr<CefBrowser> browser);
	virtual void OnBrowserDestroyed(CefRefPtr<CefBrowser> browser);

	virtual bool OnBeforeNavigation(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request, NavigationType navigation_type, bool is_redirect);

	virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);
	virtual void OnContextReleased(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);

	virtual void OnUncaughtException(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context,
		CefRefPtr<CefV8Exception> exception,
		CefRefPtr<CefV8StackTrace> stackTrace);


	virtual void OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame, CefRefPtr<CefDOMNode> node);

	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
		CefProcessId source_process, CefRefPtr<CefProcessMessage> message);

	IMPLEMENT_REFCOUNTING(WebKernelRenderProcessHandler);
};

#endif // __WEBKERNELAPP_H__