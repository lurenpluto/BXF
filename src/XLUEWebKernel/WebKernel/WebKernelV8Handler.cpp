/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/
#include "stdafx.h"
#include "./WebKernelV8Handler.h"
#include "./WebKernelConvertor.h"
#include "./WebKernelScriptIPCMessage.h"
#include "./DBG.h"
#include <sstream>

const wchar_t WebKernelV8Handler::s_szOnSendMessage[] = L"sendMessage";
const wchar_t WebKernelV8Handler::s_szOnCallLuaFunction[] = L"callLuaFunction";
const wchar_t WebKernelV8Handler::s_szOnRegisterJavascriptFunction[] = L"registerJavascriptFunction";
const wchar_t WebKernelV8Handler::s_szOnRemoveJavascriptFunction[] = L"removeJavascriptFunction";
const wchar_t WebKernelV8Handler::s_szOnLuaMessageReceived[] = L"onLuaMessageReceived";

WebKernelV8Handler::WebKernelV8Handler(CefRefPtr<WebKernelRenderProcessHandler> renderProcessHandler)
:m_renderProcessHandler(renderProcessHandler)
{
	m_javascriptMessageMap.insert(MessageMap::value_type(s_szOnSendMessage,&WebKernelV8Handler::OnSendMessageFromJavascript));
	m_javascriptMessageMap.insert(MessageMap::value_type(s_szOnCallLuaFunction,&WebKernelV8Handler::OnCallLuaFunctionFromJavascript));
	m_javascriptMessageMap.insert(MessageMap::value_type(s_szOnRegisterJavascriptFunction,&WebKernelV8Handler::OnRegisterJavascriptFunction));
	m_javascriptMessageMap.insert(MessageMap::value_type(s_szOnRemoveJavascriptFunction,&WebKernelV8Handler::OnRemoveJavascriptFunction));
	m_javascriptMessageMap.insert(MessageMap::value_type(s_szOnLuaMessageReceived,&WebKernelV8Handler::OnLuaMessageReceived));
}

bool WebKernelV8Handler::Execute(
	const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments
	, CefRefPtr<CefV8Value>& retval , CefString& exception)
{
	bool handled = false;

	//find the javascript message processor
	MessageMap::iterator cp = m_javascriptMessageMap.find(name.c_str());
	if (cp != m_javascriptMessageMap.end())
	{
		LPFNONJAVASCRIPTSMESSAGE lpProc = cp->second;
		assert(lpProc);
		handled = (this->*lpProc)(object,arguments,retval, exception);
		if (!handled)
		{
			exception = "Invalid method arguments";
		}
	}

	return true;
}

void WebKernelV8Handler::OnWebKitInitialized()
{
	// v8/bolt extension code
	std::string app_code =
		//-----------------------------------
		"var xlue;"
		"if (!xlue)"
		"  xlue = {};"
		"(function() {"

		//  Send message to Lua
		"  xlue.sendMessage = function(name, arguments) {"
		"    native function sendMessage();"
		"    return sendMessage(name, arguments);"
		"  };"

		// Call Lua function
		"  xlue.callLuaFunction = function(name,arguments,callback){"
		"    native function callLuaFunction();"
		"    return callLuaFunction(name,arguments,callback);"
		"  };"

		// Registered Javascript Function, which will be called by Lua
		"  xlue.registerJavascriptFunction = function(name,callback) {"
		"    native function registerJavascriptFunction();"
		"    return registerJavascriptFunction(name,callback);"
		"  };"

		// Remove the Registered Javascript Function by name
		"  xlue.removeJavascriptFunction = function(name) {"
		"    native function removeJavascriptFunction();"
		"    return removeJavascriptFunction(name);"
		"  };"
		
		// Receive message which is Sent from Lua
		"  xlue.onLuaMessageReceived = function(callback) {"
		"    native function onLuaMessageReceived();"
		"    return onLuaMessageReceived(callback);"
		"  };"

		"})();";
		//------------------------------------

	// Register v8/xlue extension module
	CefRegisterExtension("v8/xlue", app_code,this);
}

bool WebKernelV8Handler::OnSendMessageFromJavascript(
	CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments 
	, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
	// check arguments
	// arguments[0]: message name
	// arguments[1]: Json Object
	bool isArgumentsValid = 
		arguments.size() == 2 
		&& arguments[0]->IsString()
		&& arguments[1]->IsObject();

	if (!isArgumentsValid)
	{
		return false;
	}
	
	// check the message 
	std::wstring rawName = arguments[0]->GetStringValue().ToWString();
	if (rawName.empty()) 
	{
		return false;
	}

	// get browser
	CefRefPtr<CefBrowser> browser = CefV8Context::GetCurrentContext()->GetBrowser();
	assert(browser.get());

	// encoding the messageName
	std::wstring name = WebKernelScriptIPCMessage::EncodeJavascriptMessage(rawName);

	// create message
	CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(name);
	CefRefPtr<CefDictionaryValue> dictionaryValue = CefDictionaryValue::Create();
	WebKernelConvertor::CefV8JsonObject2DictionaryValue(arguments[1],dictionaryValue);
	CefRefPtr<CefListValue> argList = message->GetArgumentList();
	argList->SetDictionary(0,dictionaryValue);

	// send message to browser process
	browser->SendProcessMessage(PID_BROWSER, message);

	return true;
}

bool WebKernelV8Handler::OnCallLuaFunctionFromJavascript(
	CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments 
	, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
	// check arguments
	// arguments[0]: message name
	// arguments[1]: Json Object
	// arguments[2]: callback function
	bool isArgumentsValid = 
		arguments.size() == 3 
		&& arguments[0]->IsString()
		&& arguments[1]->IsObject() 
		&& arguments[2]->IsFunction();

	if (!isArgumentsValid) 
	{
		return false;
	}

	// check message name
	std::wstring luaFunctionName = arguments[0]->GetStringValue().ToWString();
	if(luaFunctionName.empty())
	{
		return false;
	}

	// get browser
	CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
	CefRefPtr<CefBrowser> browser =context->GetBrowser();
	int browserId = browser->GetIdentifier();
	assert(browser.get());

	// encoding message names for call and callback.
	std::wstring wrappedLuaFunctionName = WebKernelScriptIPCMessage::WrapLuaFunctionName(luaFunctionName);
	std::wstring callMessageName = WebKernelScriptIPCMessage::EncodeJavascriptCallMessage(wrappedLuaFunctionName);
	std::wstring callbackMessageName = WebKernelScriptIPCMessage::EncodeJavascriptCallbackMessage(wrappedLuaFunctionName);

	// save the callback
	InsertJavascriptCallback(callbackMessageName, browserId, context,arguments[2]);

	// create call message
	CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(callMessageName);
	CefRefPtr<CefDictionaryValue> dictionaryValue=CefDictionaryValue::Create();
	WebKernelConvertor::CefV8JsonObject2DictionaryValue(arguments[1], dictionaryValue);
	CefRefPtr<CefListValue> argList = message->GetArgumentList();
	argList->SetDictionary(0,dictionaryValue);

	// send call message to browser process.
	browser->SendProcessMessage(PID_BROWSER, message);

	return true;
}

bool WebKernelV8Handler::OnRegisterJavascriptFunction(CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
	// check arguments
	// arguments[0]: target Javascript Function name.
	// arguments[1]: register Javascript Function
	bool isArgumentsValid = 
		arguments.size() == 2 
		&& arguments[0]->IsString() 
		&& arguments[1]->IsFunction();

	if (!isArgumentsValid) 
	{
		return false;
	}

	// check message name
	std::wstring rawFunctionName = arguments[0]->GetStringValue().ToWString();
	if(rawFunctionName.empty())
	{
		return false;
	}

	// get browser
	CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
	CefRefPtr<CefBrowser> browser =context->GetBrowser();
	int browserId = browser->GetIdentifier();
	assert(browser.get());

	// save the function
	InsertJavascriptFunction(rawFunctionName, browserId, context,arguments[1]);
	
	return true;
}

bool WebKernelV8Handler::OnRemoveJavascriptFunction(CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
	// check arguments
	// arguments[0]: target Javascript Function name.
	bool isArgumentsValid = 
		arguments.size() == 1
		&& arguments[0]->IsString();

	if (!isArgumentsValid) 
	{
		return false;
	}

	// check Javascript Function name.
	std::wstring rawFunctionName = arguments[0]->GetStringValue().ToWString();
	if(rawFunctionName.empty())
	{
		return false;
	}

	// get browser
	CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
	CefRefPtr<CefBrowser> browser =context->GetBrowser();
	int browser_id = browser->GetIdentifier();
	assert(browser.get());

	// remove the target Javascript Function.
	RemoveJavascriptFunction(rawFunctionName,browser_id);

	return true;
}

bool WebKernelV8Handler::OnLuaMessageReceived(CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
	// check arguments
	// arguments[0]: Javascript function which will be called 
	//               on Lua message received from browser process.
	bool isArgumentsValid = 
		arguments.size() == 1
		&& arguments[0]->IsFunction();

	if (!isArgumentsValid)
	{
		return false;
	}

	// get browser
	CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
	CefRefPtr<CefBrowser> browser =context->GetBrowser();
	int browserId = browser->GetIdentifier();
	assert(browser.get());
	
	// add the Javascript function
	AddLuaMessageHandler(browserId,context,arguments[0]);

	return true;
}

bool WebKernelV8Handler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message )
{
	// Find the Lua message handler if any.
	if (OnLuaMessageRecieved(browser,source_process,message))
	{
		return true;
	}
	
	// Find the Lua Call message handler if any.
	if (OnLuaCallMessageRecieved(browser,source_process,message))
	{
		return true;
	}

	// Find the JavascriptCallback message handler if any.
	if (OnJavascriptCallbackMessageRecieved(browser,source_process,message) )
	{
		return true;
	}

	return false;
}

bool WebKernelV8Handler::OnLuaMessageRecieved(
	CefRefPtr<CefBrowser> browser, CefProcessId source_process
	, CefRefPtr<CefProcessMessage> message )
{
	// decode the message name
	CefString name = message->GetName();
	std::wstring messageName;
	bool success = WebKernelScriptIPCMessage::DecodeLuaMessage(name,messageName);
	if(!success)
	{
		return false;
	}

	// fire the Lua message to Javascript registered handlers
	for (JavascriptFuncMap::const_iterator it = m_luaMessageEvent.begin();
		it!=m_luaMessageEvent.end();
		++it)
	{
		// Keep a local reference to the objects. The callback may remove itself
		// from the callback map.
		CefRefPtr<CefV8Context> context = it->second.first;
		CefRefPtr<CefV8Value> callback = it->second.second;

		// Enter the context.
		context->Enter();

		CefV8ValueList arguments;

		// First argument is the message name.
		arguments.push_back(CefV8Value::CreateString(s_szOnLuaMessageReceived));

		// Second argument is the list of message arguments.
		CefRefPtr<CefListValue> list = message->GetArgumentList();
		CefRefPtr<CefDictionaryValue> ret = list->GetDictionary(0);
		CefRefPtr<CefV8Value> args = CefV8Value::CreateObject(NULL);
		WebKernelConvertor::CefDictionaryValue2V8JsonObject(ret, args);
		arguments.push_back(args);

		// Execute the callback.
		CefRefPtr<CefV8Value> retval = callback->ExecuteFunction(NULL, arguments);

		// Exit the context.
		context->Exit();
	}

	return true;
}

bool WebKernelV8Handler::OnLuaCallMessageRecieved(
	CefRefPtr<CefBrowser> browser, CefProcessId source_process
	, CefRefPtr<CefProcessMessage> message)
{
	// Decode the message 
	CefString luaCallMessage = message->GetName();
	std::wstring wrappedJavascriptFunctionName;
	bool success = WebKernelScriptIPCMessage::DecodeLuaCallMessage(luaCallMessage,wrappedJavascriptFunctionName);
	if(!success)
	{
		return false;
	}

	std::wstring javascriptFunctionName = WebKernelScriptIPCMessage::UnWrapJavascriptFunctionName(wrappedJavascriptFunctionName);

	// find the callback
	JavascriptFuncMap::const_iterator it = m_javascriptFuncMap.find(
		std::make_pair(javascriptFunctionName,browser->GetIdentifier()));
	if (it == m_javascriptFuncMap.end()) 
	{
		return true;
	}

	// Keep a local reference to the objects. The callback may remove itself
	// from the callback map.
	CefRefPtr<CefV8Context> context = it->second.first;
	CefRefPtr<CefV8Value> callback = it->second.second;

	// Enter the context.
	context->Enter();

	CefV8ValueList arguments;

	// First argument is the message name.
	arguments.push_back(CefV8Value::CreateString(javascriptFunctionName));

	// Second argument is the list of message arguments.
	CefRefPtr<CefListValue> list = message->GetArgumentList();
	CefRefPtr<CefDictionaryValue> ret = list->GetDictionary(0);
	CefRefPtr<CefV8Value> args = CefV8Value::CreateObject(NULL);
	WebKernelConvertor::CefDictionaryValue2V8JsonObject(ret, args);
	CefString v = args->GetValue("name")->GetStringValue();
	arguments.push_back(args);

	// Execute the callback.
	CefRefPtr<CefV8Value> retval = callback->ExecuteFunction(NULL, arguments);

	if (retval.get()) 
	{
		if(retval->IsObject())
		{
			// Create Message
			CefString luaCallbackMessageName = WebKernelScriptIPCMessage::EncodeLuaCallbackMessage(wrappedJavascriptFunctionName);
			CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(luaCallbackMessageName);
			
			// Init ArgList
			CefRefPtr<CefListValue> argList = message->GetArgumentList();
			CefRefPtr<CefDictionaryValue> retDict = CefDictionaryValue::Create();
			WebKernelConvertor::CefV8JsonObject2DictionaryValue(retval,retDict);
			argList->SetDictionary(0,retDict);

			// Send Process Message
			browser->SendProcessMessage(PID_BROWSER,message);
		}
	}

	// Exit the context.
	context->Exit();
	return true;
}


bool WebKernelV8Handler::OnJavascriptCallbackMessageRecieved(
	CefRefPtr<CefBrowser> browser, CefProcessId source_process, 
	CefRefPtr<CefProcessMessage> message)
{
	// Decode the message 
	
	CefString javascriptCallbackMessageName = message->GetName();
	std::wstring javascriptCallbackName;
	bool success = WebKernelScriptIPCMessage::DecodeJavascriptCallbackMessage(javascriptCallbackMessageName,javascriptCallbackName);
	if(!success)
	{
		return false;
	}

	// find the callback
	JavascriptFuncMap::const_iterator it = m_javascriptCallbackMap.find(
		std::make_pair(javascriptCallbackMessageName,browser->GetIdentifier()));

	if (it == m_javascriptCallbackMap.end())
	{
		return false;
	}

	// Keep a local reference to the objects. The callback may remove itself
	// from the callback map.
	CefRefPtr<CefV8Context> context = it->second.first;
	CefRefPtr<CefV8Value> callback = it->second.second;

	// Enter the context.
	context->Enter();

	CefV8ValueList arguments;

	// First argument is the message name.
	arguments.push_back(CefV8Value::CreateString(javascriptCallbackName));

	// Second argument is the message arguments.
	CefRefPtr<CefListValue> list = message->GetArgumentList();
	CefRefPtr<CefDictionaryValue> ret = list->GetDictionary(0);
	CefRefPtr<CefV8Value> args = CefV8Value::CreateObject(NULL);
	WebKernelConvertor::CefDictionaryValue2V8JsonObject(ret, args);
	arguments.push_back(args);

	// Execute the callback.
	bool handled = false;
	CefRefPtr<CefV8Value> retval = callback->ExecuteFunction(NULL, arguments);
	if (retval.get()) 
	{
		if (retval->IsBool())
		{
			handled = retval->GetBoolValue();
		}
	}

	// Exit the context.
	context->Exit();

	// Remove the callback
	RemoveJavascriptCallback(javascriptCallbackMessageName,browser->GetIdentifier());

	return true;
}


void WebKernelV8Handler::InsertJavascriptCallback(
	const std::wstring& message_name
	, int browser_id
	, CefRefPtr<CefV8Context> context
	, CefRefPtr<CefV8Value> function) 
{
	assert(CefCurrentlyOn(TID_RENDERER));

	m_javascriptCallbackMap.insert(
		std::make_pair(std::make_pair(message_name, browser_id),
		std::make_pair(context, function)));
}

bool WebKernelV8Handler::RemoveJavascriptCallback(const std::wstring& message_name, int browser_id) 
{
	assert(CefCurrentlyOn(TID_RENDERER));

	JavascriptFuncMap::iterator it = m_javascriptCallbackMap.find(std::make_pair(message_name, browser_id));
	if (it != m_javascriptCallbackMap.end()) 
	{
		m_javascriptCallbackMap.erase(it);
		return true;
	}
	return false;
}

void WebKernelV8Handler::InsertJavascriptFunction(
	const std::wstring& message_name
	, int browser_id
	, CefRefPtr<CefV8Context> context
	, CefRefPtr<CefV8Value> function) 
{
	assert(CefCurrentlyOn(TID_RENDERER));
	m_javascriptFuncMap.insert(
		std::make_pair(std::make_pair(message_name, browser_id),
		std::make_pair(context, function)));
}

bool WebKernelV8Handler::RemoveJavascriptFunction(const std::wstring& message_name, int browser_id) 
{
	assert(CefCurrentlyOn(TID_RENDERER));

	JavascriptFuncMap::iterator it = m_javascriptFuncMap.find(std::make_pair(message_name, browser_id));
	if (it != m_javascriptFuncMap.end()) 
	{
		m_javascriptFuncMap.erase(it);
		return true;
	}

	return false;
}

void WebKernelV8Handler::AddLuaMessageHandler(int browser_id, CefRefPtr<CefV8Context> context, CefRefPtr<CefV8Value> function)
{
	assert(CefCurrentlyOn(TID_RENDERER));

	std::ostringstream oss;
	oss << L"LuaMessageHandler_" << m_luaMessageEvent.size();
	std::string name = oss.str();
	std::wstring wname(name.begin(),name.end());

	m_luaMessageEvent.insert(
		std::make_pair(std::make_pair(wname, browser_id),
		std::make_pair(context, function)));
}
