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
*   Author      :   范飞龙
*   Create      :   2013-10-25
*   LastChange  :   2013-10-25
*   History     :	
*
*   Description :   V8Handler的实现，负责管理和维护Js与Lua交互的Js端资源
*
********************************************************************/ 
#ifndef __WEBKERNELV8HANDLER_H__
#define __WEBKERNELV8HANDLER_H__

#include "./WebKernelApp.h"

class WebKernelBrowserProcessHandler;
class WebKernelRenderProcessHandler;

class WebKernelV8Handler : public CefV8Handler
{
public:
	WebKernelV8Handler(CefRefPtr<WebKernelRenderProcessHandler> renderProcessHandler);

public:
	
	/**
	 *	CefV8Handler Methods, Which will be called when the V8 extension 
	 *  is called in the Javascript environment
	 */
	virtual bool Execute(const CefString& name
		,CefRefPtr<CefV8Value> object
		,const CefV8ValueList& arguments
		,CefRefPtr<CefV8Value>& retval
		,CefString& exception);

public:

	/**
	 *	This Method will be called at WebKernelApp::OnWebKitInitialize function
	 */
	virtual void OnWebKitInitialized();

	/**
	 *	This Method will be Called by WebKernelRenderProcessHandler 
	 *  when browser Process Message Received
	 */
	virtual bool OnProcessMessageReceived( 
		CefRefPtr<CefBrowser> browser, CefProcessId source_process, 
		CefRefPtr<CefProcessMessage> message );

	/**
	 * Send Javascript Message From Render Process to Browser Process
	 */
	virtual bool OnSendMessageFromJavascript(
		CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments 
		, CefRefPtr<CefV8Value>& retval, CefString& exception);

	/**
	 * Send Javascript CallLuaFunctin Message From Render Process to Browser Process
	 */
	virtual bool OnCallLuaFunctionFromJavascript(
		CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments 
		, CefRefPtr<CefV8Value>& retval, CefString& exception);

	/**
	 *	Register Javascript Function, which will be called by lua.
	 */
	virtual bool OnRegisterJavascriptFunction(
		CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments 
		, CefRefPtr<CefV8Value>& retval, CefString& exception);

	/**
	 *	Remove Registered Javascript Function by Name
	 */
	virtual bool OnRemoveJavascriptFunction(
		CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments 
		, CefRefPtr<CefV8Value>& retval, CefString& exception);

	/**
	 *	Register the LuaMessageReceived callback
	 */
	virtual bool OnLuaMessageReceived(
		CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments 
		, CefRefPtr<CefV8Value>& retval, CefString& exception);

private:
	/**
	 *	Receive Lua Message From Browser Process,
	 *  which will be send to registered javascript handler.
	 */
	bool OnLuaMessageRecieved(
		CefRefPtr<CefBrowser> browser, CefProcessId source_process
		, CefRefPtr<CefProcessMessage> message );

	/**
	 *	Receive Lua Call Message From Browser Process,
	 *  which will call the registered Javascript Function.
	 */
	bool OnLuaCallMessageRecieved(
		CefRefPtr<CefBrowser> browser, CefProcessId source_process
		, CefRefPtr<CefProcessMessage> message );

	/**
	 *	Receive Javascript callback Message From Browser Process,
	 *  which will call the registered Javascript callback.
	 */
	bool OnJavascriptCallbackMessageRecieved(
		CefRefPtr<CefBrowser> browser, CefProcessId source_process
		, CefRefPtr<CefProcessMessage> message );

private:
	void InsertJavascriptCallback(
		const std::wstring& message_name, int browser_id
		, CefRefPtr<CefV8Context> context, CefRefPtr<CefV8Value> function);

	bool RemoveJavascriptCallback(
		const std::wstring& message_name, int browser_id);

	void InsertJavascriptFunction(
		const std::wstring& message_name, int browser_id
		, CefRefPtr<CefV8Context> context, CefRefPtr<CefV8Value> function);

	bool RemoveJavascriptFunction(
		const std::wstring& message_name, int browser_id);

	void AddLuaMessageHandler(
		int browser_id, CefRefPtr<CefV8Context> context, CefRefPtr<CefV8Value> function);

	std::wstring WrapJavascriptCallbackName(const std::wstring& name);
	std::wstring UnWrapJavascriptCallbackName(const std::wstring& name);

private:
	// Javascript MessageMap typedef
	typedef bool (WebKernelV8Handler::*LPFNONJAVASCRIPTSMESSAGE)(
		CefRefPtr<CefV8Value>, const CefV8ValueList& 
		, CefRefPtr<CefV8Value>& ,CefString& );
	typedef stdext::hash_map<std::wstring, LPFNONJAVASCRIPTSMESSAGE> MessageMap;

	// Javascript FuncMap typedef
	typedef std::pair<std::wstring, int> JavascriptFuncKey;
	typedef std::pair<CefRefPtr<CefV8Context>, CefRefPtr<CefV8Value> > JavascriptFuncValue;
	typedef std::map<JavascriptFuncKey,JavascriptFuncValue> JavascriptFuncMap;

private:
	CefRefPtr<WebKernelRenderProcessHandler> m_renderProcessHandler;  // RenderProcessHandler
	MessageMap m_javascriptMessageMap;                                // Javascript Message 

	JavascriptFuncMap m_javascriptCallbackMap;                        // Javascript callback 4 luaCall
	JavascriptFuncMap m_javascriptFuncMap;                            // Javascript function
	JavascriptFuncMap m_luaMessageEvent;                              // Javascript callback 4 lua Message

	// Javascript Event Names
	static const wchar_t s_szOnSendMessage[];                         // "sendMessage" Message
	static const wchar_t s_szOnCallLuaFunction[];                     // "luaCall" Message
	static const wchar_t s_szOnRegisterJavascriptFunction[];          // "registerLuaFunction" Message
	static const wchar_t s_szOnRemoveJavascriptFunction[];            // "removeLuaFunction" Message
	static const wchar_t s_szOnLuaMessageReceived[];                  // "onLuaMessageReceived" Message

	// Provide the reference counting implementation for this class.
	IMPLEMENT_REFCOUNTING(WebKernelV8Handler);
};

#endif // __WEBKERNELV8HANDLER_H__