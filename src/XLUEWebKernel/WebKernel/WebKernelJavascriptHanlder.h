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
*   FileName    :   WebKernelJavascriptHanlder
*   Author      :   范飞龙
*   Create      :   2013-10-29 
*   LastChange  :   2013-10-29
*   History     :	
*
*   Description :   Browser进程负责Lua与Javascript交互的类
*
********************************************************************/ 
#ifndef __WEBKERNELJAVASCRIPTHANDLER_H__
#define __WEBKERNELJAVASCRIPTHANDLER_H__

class WebKernelJavascriptHandler: public CefBase
{
public: 
	/**
	 *	Constructor
	 */
	WebKernelJavascriptHandler();

public:
	/**
	 *	Receive message from Render process.
	 */
	bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message);

	/**
	 *	Send Message To Render Process, which will Call Javascript Function.
	 */
	bool CallJavascriptFunction(
		CefRefPtr<CefBrowser> browser
		, const CefString& functionName
		, CefRefPtr<CefDictionaryValue> dictionaryValue);

	/**
	 *	Send Lua Message To Render Process.
	 */
	bool SendMessageToJavascript(
		CefRefPtr<CefBrowser> browser
		, const CefString& messageName
		, CefRefPtr<CefDictionaryValue> dictionaryValue);

private:
	/**
	 *	Receive Message From Render Process, which will fire the corresponding BoltBrowser events.
	 */
	bool OnJavascriptMessageRecevied(CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message);

	/**
	 *	Receive Message From Render Process, which will call the registered Lua function.
	 */
	bool OnJavascriptCallMessageRecevied(CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message);

	/**
	 *	Receive Message From Render Process, which will call the registered Lua callback function.
	 */
	bool OnLuaCallbackMessageRecevied(CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message);

private:
	IMPLEMENT_REFCOUNTING(WebKernelJavascriptHandler) 
};

#endif //__WEBKERNELJAVASCRIPTHANDLER_H__
