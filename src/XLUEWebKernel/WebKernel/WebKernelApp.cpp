/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./WebKernelApp.h"
#include "./DBG.h"
#include "./WebKernelV8Handler.h"
#include "./ListUtil.h"

WebKernelApp::WebKernelApp(void)
:m_spBrowserProcessHandler(NULL),
m_spRenderProcessHandler(NULL)
{
}

WebKernelApp::~WebKernelApp(void)
{
	assert(m_spBrowserProcessHandler == NULL);
	assert(m_spRenderProcessHandler == NULL);
}

void WebKernelApp::OnBeforeCommandLineProcessing( const CefString& process_type, CefRefPtr<CefCommandLine> command_line )
{
	
}

CefRefPtr<CefBrowserProcessHandler> WebKernelApp::GetBrowserProcessHandler()
{
	return m_spBrowserProcessHandler.get();
}

CefRefPtr<CefRenderProcessHandler> WebKernelApp::GetRenderProcessHandler()
{
	return m_spRenderProcessHandler.get();
}

bool WebKernelApp::Init()
{
	assert(m_spBrowserProcessHandler == NULL);
	assert(m_spRenderProcessHandler == NULL);

	if (g_webKernelGlobal.m_browserProcess)
	{
		m_spBrowserProcessHandler = new WebKernelBrowserProcessHandler();
	}
	else
	{
		m_spRenderProcessHandler = new WebKernelRenderProcessHandler();
	}

	return true;
}

bool WebKernelApp::Uninit()
{
	if (m_spBrowserProcessHandler != NULL)
	{
		m_spBrowserProcessHandler = NULL;
	}

	if (m_spRenderProcessHandler != NULL)
	{
		m_spRenderProcessHandler = NULL;
	}

	return true;
}

void WebKernelBrowserProcessHandler::OnContextInitialized()
{

}

void WebKernelBrowserProcessHandler::OnBeforeChildProcessLaunch( CefRefPtr<CefCommandLine> command_line )
{
	command_line->AppendArgument(L"servicetype");
	command_line->AppendArgument(L"web");

	wchar_t szID[255];
	::memset(szID, 0, 255);

	wsprintf(szID, L"Xunlei.UIEngine.WebServer.%d.%d.%d", ::GetCurrentProcessId(), ::GetCurrentThreadId(), m_renderServerNextID);
	m_renderServerNextID++;

	command_line->AppendArgument(L"id");
	command_line->AppendArgument(szID);

	wsprintf(szID, L"%d", ::GetCurrentProcessId());
	command_line->AppendArgument(L"pid");
	command_line->AppendArgument(szID);

	wchar_t szEXEPath[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, szEXEPath, MAX_PATH);

	command_line->AppendArgument(L"clientpath");
	command_line->AppendArgument(szEXEPath);
}

void WebKernelBrowserProcessHandler::OnRenderProcessThreadCreated( CefRefPtr<CefListValue> extra_info )
{

}

WebKernelBrowserProcessHandler::WebKernelBrowserProcessHandler()
:m_renderServerNextID(1)
{

}

WebKernelBrowserProcessHandler::~WebKernelBrowserProcessHandler()
{

}

void WebKernelRenderProcessHandler::OnRenderThreadCreated( CefRefPtr<CefListValue> extra_info )
{

}

void WebKernelRenderProcessHandler::OnWebKitInitialized()
{
	std::string app_code =
		"var app;"
		"if (!app)"
		"  app = {};"
		"(function() {"
		"  app.sendMessage = function(name, arguments) {"
		"    native function sendMessage();"
		"    return sendMessage(name, arguments);"
		"  };"
		"  app.setMessageCallback = function(name, callback) {"
		"    native function setMessageCallback();"
		"    return setMessageCallback(name, callback);"
		"  };"
		"  app.removeMessageCallback = function(name) {"
		"    native function removeMessageCallback();"
		"    return removeMessageCallback(name);"
		"  };"
		"})();";

	CefRegisterExtension("v8/app", app_code,
		new WebKernelV8Handler(this));

}

void WebKernelRenderProcessHandler::OnBrowserCreated( CefRefPtr<CefBrowser> browser )
{

}

void WebKernelRenderProcessHandler::OnBrowserDestroyed( CefRefPtr<CefBrowser> browser )
{

}

bool WebKernelRenderProcessHandler::OnBeforeNavigation( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
													   CefRefPtr<CefRequest> request, NavigationType navigation_type, bool is_redirect )
{
	return g_webKernelGlobal.m_syncProxy.OnBeforeNavigation(browser, frame, request, navigation_type, is_redirect);
}

void WebKernelRenderProcessHandler::OnContextCreated( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
													 CefRefPtr<CefV8Context> context )
{
	
}

void WebKernelRenderProcessHandler::OnContextReleased( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
													  CefRefPtr<CefV8Context> context )
{

}

void WebKernelRenderProcessHandler::OnUncaughtException( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
														CefRefPtr<CefV8Context> context, CefRefPtr<CefV8Exception> exception, 
														CefRefPtr<CefV8StackTrace> stackTrace )
{

}

void WebKernelRenderProcessHandler::OnFocusedNodeChanged( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
														 CefRefPtr<CefDOMNode> node )
{
	g_webKernelGlobal.m_syncProxy.OnFocusedNodeChanged(browser, frame, node);
}

bool WebKernelRenderProcessHandler::OnProcessMessageReceived( CefRefPtr<CefBrowser> browser, CefProcessId source_process, 
															 CefRefPtr<CefProcessMessage> message )
{
	if(g_webKernelGlobal.m_syncProxy.OnProcessMessageReceived(browser,message))
	{
		return true;
	}

	bool handled = false;
	// Execute the registered JavaScript callback if any.
	if (!callback_map_.empty()) {
		CefString message_name = message->GetName();
		CallbackMap::const_iterator it = callback_map_.find(
			std::make_pair(message_name.ToString(),
			browser->GetIdentifier()));
		if (it != callback_map_.end()) {
			// Keep a local reference to the objects. The callback may remove itself
			// from the callback map.
			CefRefPtr<CefV8Context> context = it->second.first;
			CefRefPtr<CefV8Value> callback = it->second.second;

			// Enter the context.
			context->Enter();

			CefV8ValueList arguments;

			// First argument is the message name.
			arguments.push_back(CefV8Value::CreateString(message_name));

			// Second argument is the list of message arguments.
			CefRefPtr<CefListValue> list = message->GetArgumentList();
			CefRefPtr<CefV8Value> args =
				CefV8Value::CreateArray(static_cast<int>(list->GetSize()));
			SetList(list, args);
			arguments.push_back(args);

			// Execute the callback.
			CefRefPtr<CefV8Value> retval = callback->ExecuteFunction(NULL, arguments);
			if (retval.get()) {
				if (retval->IsBool())
					handled = retval->GetBoolValue();
			}

			// Exit the context.
			context->Exit();
		}
	}

	return handled;
}

void WebKernelRenderProcessHandler::SetMessageCallback(
	const std::string& message_name,
	int browser_id,
	CefRefPtr<CefV8Context> context,
	CefRefPtr<CefV8Value> function) 
{
	assert(CefCurrentlyOn(TID_RENDERER));

	callback_map_.insert(
	std::make_pair(std::make_pair(message_name, browser_id),
	std::make_pair(context, function)));
}

bool WebKernelRenderProcessHandler::RemoveMessageCallback(
	const std::string& message_name,
	int browser_id) 
{
	assert(CefCurrentlyOn(TID_RENDERER));

	CallbackMap::iterator it =
	  callback_map_.find(std::make_pair(message_name, browser_id));
	if (it != callback_map_.end()) {
	  callback_map_.erase(it);
	  return true;
	}

	return false;
}