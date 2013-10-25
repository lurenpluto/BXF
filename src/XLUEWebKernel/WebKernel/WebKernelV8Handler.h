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
*   FileName    :   WebKernelV8Handler
*   Author      :   ·¶·ÉÁú
*   Create      :   2013-10-25
*   LastChange  :   2013-10-25
*   History     :	
*
*   Description :   V8HandlerµÄÊµÏÖ
*
********************************************************************/ 
#ifndef __WEBKERNELV8HANDLER_H__
#define __WEBKERNELV8HANDLER_H__

class WebKernalApp;

class WebKernelV8Handler : public CefV8Handler
{
public:
	WebKernelV8Handler(CefRefPtr<WebKernelRenderProcessHandler> renderProcessHandler);

	virtual bool Execute(const CefString& name
		,CefRefPtr<CefV8Value> object
		,const CefV8ValueList& arguments
		,CefRefPtr<CefV8Value>& retval
		,CefString& exception);

private:
	CefRefPtr<WebKernelRenderProcessHandler> m_renderProcessHandler;

	// Provide the reference counting implementation for this class.
	IMPLEMENT_REFCOUNTING(WebKernelV8Handler);
};

#endif // __WEBKERNELV8HANDLER_H__