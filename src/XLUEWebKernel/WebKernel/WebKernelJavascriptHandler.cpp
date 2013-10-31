/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/
#include "stdafx.h"
#include "./WebKernelJavascriptHanlder.h"
#include "./WebKernelScriptIPCMessage.h"
#include "./BaseBoltBrowser.h"
#include "./DBG.h"

WebKernelJavascriptHandler::WebKernelJavascriptHandler()
{
	
}

bool WebKernelJavascriptHandler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message)
{
	if (OnJavascriptMessageRecevied(browser,message))
	{
		return true;
	}

	if (OnJavascriptCallMessageRecevied(browser,message))
	{
		return true;
	}

	if (OnLuaCallbackMessageRecevied(browser,message))
	{
		return true;
	}

	return false;
}

bool WebKernelJavascriptHandler::OnJavascriptMessageRecevied(CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message)
{
	// get message name
	CefString javascriptMessageName=message->GetName();
	std::wstring javascriptMessage;
	bool success = WebKernelScriptIPCMessage::DecodeJavascriptMessage(javascriptMessageName.ToWString(),javascriptMessage);
	if(!success)
	{
		return false;
	}

	// get arguments
	CefRefPtr<CefListValue> argList = message->GetArgumentList();
	CefRefPtr<CefDictionaryValue> dictionaryValue = argList->GetDictionary(0);

	// Fire the BaseBoltBrowser OnJavascriptMessageReceived Event
	bool handled = false;
	BaseBoltBrowser* lpBoltBrowser = g_webKernelGlobal.m_browserManager.GetBoltBrowserFromID(browser->GetIdentifier());
	lpBoltBrowser->OnJavaScriptMessageReceived(javascriptMessage,dictionaryValue,handled);

	return true;
}

bool WebKernelJavascriptHandler::OnJavascriptCallMessageRecevied(CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message)
{
	// get message name
	CefString javascriptCallMessageName=message->GetName();
	std::wstring wrappedLuaFunctionName;
	bool success = WebKernelScriptIPCMessage::DecodeJavascriptCallMessage(javascriptCallMessageName.ToWString(),wrappedLuaFunctionName);
	if(!success)
	{
		return false;
	}
	std::wstring luaFunctionName = WebKernelScriptIPCMessage::UnWrapLuaFunctionName(wrappedLuaFunctionName);

	// get arguments
	CefRefPtr<CefListValue> argList = message->GetArgumentList();
	CefRefPtr<CefDictionaryValue> dictionaryValue = argList->GetDictionary(0);

	// call the registered Lua function in BaseBoltBrowser 
	bool handled = false;
	BaseBoltBrowser* lpBoltBrowser = g_webKernelGlobal.m_browserManager.GetBoltBrowserFromID(browser->GetIdentifier());
	CefRefPtr<CefDictionaryValue> ret = lpBoltBrowser->OnJavascriptCallMessageRecivied(luaFunctionName,dictionaryValue,handled);
	
	// create the result message
	std::wstring javascriptCallbackMessageName = WebKernelScriptIPCMessage::EncodeJavascriptCallbackMessage(wrappedLuaFunctionName);
	CefRefPtr<CefProcessMessage> resultMessage = CefProcessMessage::Create(javascriptCallbackMessageName);
	CefRefPtr<CefListValue> resultArgList = resultMessage->GetArgumentList();
	resultArgList->SetDictionary(0,ret);

	// send result message to Render process
	browser->SendProcessMessage(PID_RENDERER,resultMessage);

	return true;
}

bool WebKernelJavascriptHandler::OnLuaCallbackMessageRecevied(CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message)
{
	// get message name
	CefString luaCallbackMessageName=message->GetName();
	std::wstring luaCallbackName;

	bool success = WebKernelScriptIPCMessage::DecodeLuaCallbackMessage(luaCallbackMessageName.ToWString(),luaCallbackName);
	if (!success)
	{
		return false;
	}

	// get arguments
	CefRefPtr<CefListValue> argList = message->GetArgumentList();
	CefRefPtr<CefDictionaryValue> dictionaryValue = argList->GetDictionary(0);

	// call the registered Lua callback in BaseBoltBrowser
	bool handled = false;
	BaseBoltBrowser* lpBoltBrowser = g_webKernelGlobal.m_browserManager.GetBoltBrowserFromID(browser->GetIdentifier());
	lpBoltBrowser->OnLuaCallbackMessageRecevied(luaCallbackName,dictionaryValue,handled);

	return handled;
}

bool WebKernelJavascriptHandler::CallJavascriptFunction(CefRefPtr<CefBrowser> browser, const CefString& wrappedJavascriptFunctionName, CefRefPtr<CefDictionaryValue> dictionaryValue)
{
	// encoding message name
	std::wstring luaCallMessageName = WebKernelScriptIPCMessage::EncodeLuaCallMessage(wrappedJavascriptFunctionName.c_str());
	
	// create message
	CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(luaCallMessageName);
	CefRefPtr<CefListValue> argList = message->GetArgumentList();
	argList->SetDictionary(0,dictionaryValue);

	// send message to Render process.
	return browser->SendProcessMessage(PID_RENDERER,message);
}

bool WebKernelJavascriptHandler::SendMessageToJavascript( CefRefPtr<CefBrowser> browser , const CefString& messageName , CefRefPtr<CefDictionaryValue> dictionaryValue )
{
	// encoding message name
	std::wstring luaMessageName = WebKernelScriptIPCMessage::EncodeLuaMessage(messageName.c_str());
	
	// create message
	CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(luaMessageName);
	CefRefPtr<CefListValue> argList = message->GetArgumentList();
	argList->SetDictionary(0,dictionaryValue);

	// send message to Render process
	return browser->SendProcessMessage(PID_RENDERER,message);
}