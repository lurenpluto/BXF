/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./WebKernelSyncProxy.h"
#include "./BaseBoltBrowser.h"

const wchar_t WebKernelSyncProxy::s_szOnBeforeNavigation[] = L"OnBeforeNavigation";
const wchar_t WebKernelSyncProxy::s_szOnBeforeNavigationRet[] = L"OnBeforeNavigationRet";
const wchar_t WebKernelSyncProxy::s_szOnFocusedNodeChanged[] = L"OnFocusedNodeChanged";

const wchar_t WebKernelSyncProxy::s_szOnBeforePopup[] = L"OnBeforePopup";

WebKernelSyncReplyManager::WebKernelSyncReplyManager()
:m_no(0)
{

}

WebKernelSyncReplyManager::~WebKernelSyncReplyManager()
{
	assert(m_replys.empty());
}

int WebKernelSyncReplyManager::GetReplyNo()
{
	return m_no++;
}

bool WebKernelSyncReplyManager::Add( int no, CefRefPtr<CefListValue> spResult )
{
	std::pair<mapReply::iterator, bool> ret = m_replys.insert(mapReply::value_type(no, spResult));
	assert(ret.second);

	return ret.second;
}

CefRefPtr<CefListValue> WebKernelSyncReplyManager::Fetch( int no )
{
	CefRefPtr<CefListValue> value;
	mapReply::iterator cp = m_replys.find(no);
	if (cp != m_replys.end())
	{
		value = cp->second;
		m_replys.erase(cp);
	}

	return value;
}

void WebKernelSyncReplyManager::Clear()
{
	m_replys.clear();
}

WebKernelSyncProxy::WebKernelSyncProxy(void)
{
}

WebKernelSyncProxy::~WebKernelSyncProxy(void)
{
}

bool WebKernelSyncProxy::Init()
{
	if (g_webKernelGlobal.m_browserProcess)
	{
		m_messageMap.insert(messageMap::value_type(s_szOnBeforeNavigation, &WebKernelSyncProxy::OnBeforeNavigationMessage));
		m_messageMap.insert(messageMap::value_type(s_szOnFocusedNodeChanged, &WebKernelSyncProxy::OnFocusedNodeChangedMessage));

		m_messageMap.insert(messageMap::value_type(s_szOnBeforePopup, &WebKernelSyncProxy::OnBeforePopupMessage));
	}
	else
	{
		m_messageMap.insert(messageMap::value_type(s_szOnBeforeNavigationRet, &WebKernelSyncProxy::OnBeforeNavigationRetMessage));
	}

	return true;
}

bool WebKernelSyncProxy::Uninit()
{
	m_replyManager.Clear();

	m_messageMap.clear();

	return true;
}

bool WebKernelSyncProxy::OnProcessMessageReceived( CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message )
{
	CefString msgName = message->GetName();

	messageMap::iterator cp = m_messageMap.find(msgName.c_str());
	if (cp == m_messageMap.end())
	{
		assert(false);
		return false;
	}

	LPFNONPROCESSMESSAGE lpProc = cp->second;
	assert(lpProc);

	return (this->*lpProc)(browser, message);
}

bool WebKernelSyncProxy::OnThreadMessagerRecevied( CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message )
{
	CefString msgName = message->GetName();

	messageMap::iterator cp = m_messageMap.find(msgName.c_str());
	if (cp == m_messageMap.end())
	{
		assert(false);
		return false;
	}

	LPFNONPROCESSMESSAGE lpProc = cp->second;
	assert(lpProc);

	return (this->*lpProc)(browser, message);
}

bool WebKernelSyncProxy::OnBeforeNavigation( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, cef_navigation_type_t navigation_type, bool is_redirect )
{
	CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(s_szOnBeforeNavigation);
	CefRefPtr<CefListValue> argList = msg->GetArgumentList();

	int callNo = m_replyManager.GetReplyNo();
	argList->SetInt(0, callNo);

	SerializeFrame(argList, frame, 1);

	argList->SetString(2, request->GetURL());
	argList->SetInt(3, navigation_type);
	argList->SetBool(4, is_redirect);

	bool canceled = false;
	bool ret = browser->SendProcessMessage(PID_BROWSER, msg);
	if (ret)
	{
		argList = m_replyManager.Fetch(callNo);
		if (argList != NULL)
		{
			canceled = argList->GetBool(1);
		}
	}

	return canceled;
}

bool WebKernelSyncProxy::OnBeforeNavigationMessage( CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message )
{
	assert(browser);
	assert(message);

	BaseBoltBrowser* lpBoltBrowser = g_webKernelGlobal.m_browserManager.GetBoltBrowserFromID(browser->GetIdentifier());
	assert(lpBoltBrowser);
	if (lpBoltBrowser == NULL)
	{
		return false;
	}

	CefRefPtr<CefListValue> argList = message->GetArgumentList();

	int replyNo = argList->GetInt(0);

	CefRefPtr<CefFrame> spFrame = UnSerializeFrame(argList, browser, 1);
	assert(spFrame);

	CefString request = argList->GetString(2);
	cef_navigation_type_t type = (cef_navigation_type_t)argList->GetInt(3);
	bool isRedirect = argList->GetBool(4);

	bool handled = false;
	bool canceled = lpBoltBrowser->OnBeforeNavigation(spFrame, request, type, isRedirect, handled);

	// 只有在cancel情况下才需要应答
	if (canceled)
	{
		CefRefPtr<CefProcessMessage> retMsg = CefProcessMessage::Create(s_szOnBeforeNavigationRet);
		argList = retMsg->GetArgumentList();
		argList->SetInt(0, replyNo);
		argList->SetBool(1, canceled);

		browser->SendProcessMessage(PID_RENDERER, retMsg);
	}

	return true;
}

bool WebKernelSyncProxy::OnBeforeNavigationRetMessage( CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message )
{
	assert(browser);
	assert(message);

	CefRefPtr<CefListValue> argList = message->GetArgumentList();

	int callNo = argList->GetInt(0);
	
	m_replyManager.Add(callNo, argList->Copy());

	return true;
}

void WebKernelSyncProxy::OnFocusedNodeChanged( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame
										, CefRefPtr<CefDOMNode> node )
{
	CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(s_szOnFocusedNodeChanged);
	CefRefPtr<CefListValue> argList = msg->GetArgumentList();

	SerializeFrame(argList, frame, 0);

	browser->SendProcessMessage(PID_BROWSER, msg);
}

bool WebKernelSyncProxy::OnFocusedNodeChangedMessage( CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message )
{
	assert(browser);
	assert(message);

	BaseBoltBrowser* lpBoltBrowser = g_webKernelGlobal.m_browserManager.GetBoltBrowserFromID(browser->GetIdentifier());
	assert(lpBoltBrowser);
	if (lpBoltBrowser == NULL)
	{
		return false;
	}

	CefRefPtr<CefListValue> argList = message->GetArgumentList();

	CefRefPtr<CefFrame> spFrame = UnSerializeFrame(argList, browser, 0);
	assert(spFrame);

	bool handled = false;
	lpBoltBrowser->OnFocusedNodeChanged(spFrame, handled);

	return true;
}

void WebKernelSyncProxy::SerializeFrame( CefListValue* lpListValue, CefFrame* lpFrame, int index )
{
	assert(lpListValue);
	assert(lpFrame);

	int64 frameID = lpFrame->GetIdentifier();
	CefRefPtr<CefBinaryValue> spFrameID = CefBinaryValue::Create(&frameID, sizeof(frameID));
	lpListValue->SetBinary(index, spFrameID);
}

CefRefPtr<CefFrame> WebKernelSyncProxy::UnSerializeFrame( CefListValue* lpListValue, CefBrowser* lpBrowser, int index )
{
	assert(lpListValue);

	int64 frameID = 0;
	lpListValue->GetBinary(index)->GetData(&frameID, sizeof(frameID), 0);
	CefRefPtr<CefFrame> spFrame = lpBrowser->GetFrame(frameID);
	assert(spFrame);

	return spFrame;
}

void WebKernelSyncProxy::OnBeforePopup( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame
								 , const CefString& target_url, const CefString& target_frame_name, const CefPopupFeatures& popupFeatures )
{
	CefRefPtr<CefProcessMessage> spMsg = CefProcessMessage::Create(s_szOnBeforePopup);
	CefRefPtr<CefListValue> spListValue = spMsg->GetArgumentList();

	SerializeFrame(spListValue, frame, 0);

	spListValue->SetString(1, target_url);
	spListValue->SetString(2, target_frame_name);

	bool handled = false;
	g_webKernelGlobal.m_itc.SendMessage(browser->GetIdentifier(), spMsg, handled);
}

bool WebKernelSyncProxy::OnBeforePopupMessage( CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message )
{
	assert(browser);
	assert(message);

	BaseBoltBrowser* lpBoltBrowser = g_webKernelGlobal.m_browserManager.GetBoltBrowserFromID(browser->GetIdentifier());
	assert(lpBoltBrowser);
	if (lpBoltBrowser == NULL)
	{
		return false;
	}

	CefRefPtr<CefListValue> listValue = message->GetArgumentList();

	CefRefPtr<CefFrame> spFrame = UnSerializeFrame(listValue, browser, 0);
	assert(spFrame);

	CefString targetUrl = listValue->GetString(1);
	CefString targetFrameName = listValue->GetString(2);

	bool handled = false;
	lpBoltBrowser->OnBeforePopup(spFrame, targetUrl, targetFrameName, handled);

	return true;
}