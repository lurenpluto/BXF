/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/
#include "stdafx.h"
#include "./WebKernelV8Handler.h"
#include "./WebKernelConvertor.h"
#include "./DBG.h"


WebKernelV8Handler::WebKernelV8Handler(CefRefPtr<WebKernelRenderProcessHandler> renderProcessHandler)
:m_renderProcessHandler(renderProcessHandler)
{

}

bool WebKernelV8Handler::Execute(const CefString& name
								 ,CefRefPtr<CefV8Value> object
								 ,const CefV8ValueList& arguments
								 ,CefRefPtr<CefV8Value>& retval
								 ,CefString& exception)
{
	bool handled = false;

	if (name == "sendMessage") 
	{
		// Send a message to the browser process.
		if ((arguments.size() == 1 || arguments.size() == 2) && arguments[0]->IsString()) 
		{
				CefRefPtr<CefBrowser> browser = CefV8Context::GetCurrentContext()->GetBrowser();
				assert(browser.get());

				std::string name = "xlue.js.message."+arguments[0]->GetStringValue().ToString();
				if (!name.empty())
				{
					CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(name);

					// Translate the arguments, if any.
					if (arguments.size() == 2 && arguments[1]->IsObject())
					{
						CefRefPtr<CefDictionaryValue> dictionaryValue=CefDictionaryValue::Create();
						WebKernelConvertor::CefV8JsonObject2DictionaryValue(arguments[1], dictionaryValue);
						CefRefPtr<CefListValue> argList = message->GetArgumentList();
						argList->SetDictionary(0,dictionaryValue);
					}

					browser->SendProcessMessage(PID_BROWSER, message);
					handled = true;
				}
		}
	}
	else if (name == "setMessageCallback") 
	{
		// Set a message callback.
		if (arguments.size() == 2 && arguments[0]->IsString() &&arguments[1]->IsFunction()) 
		{
				std::string name = "xlue.js.message."+arguments[0]->GetStringValue().ToString();
				CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
				int browser_id = context->GetBrowser()->GetIdentifier();
				m_renderProcessHandler->SetMessageCallback(name, browser_id, context,arguments[1]);
				handled = true;
		}
	}  
	else if (name == "removeMessageCallback") 
	{
		// Remove a message callback.
		if (arguments.size() == 1 && arguments[0]->IsString()) 
		{
			std::string name = "xlue.js.message."+arguments[0]->GetStringValue().ToString();
			CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
			int browser_id = context->GetBrowser()->GetIdentifier();
			bool removed = m_renderProcessHandler->RemoveMessageCallback(name, browser_id);
			retval = CefV8Value::CreateBool(removed);
			handled = true;
		}
	}

	if (!handled)
	{
		exception = "Invalid method arguments";
	}

	return true;
}