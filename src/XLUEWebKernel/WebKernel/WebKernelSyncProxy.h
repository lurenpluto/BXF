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
*   FileName    :   WebKernelSyncProxy
*   Author      :   李亚星
*   Create      :   2013-7-6 
*   LastChange  :   2013-7-6
*   History     :	
*
*   Description :   浏览器跨进程/线程同步通信的代理
*
********************************************************************/ 
#ifndef __WEBKERNELSYNCPROXY_H__
#define __WEBKERNELSYNCPROXY_H__

// 跨进程/线程同步通信的应答管理
// 目前仅可在render和browser两个进程的主线程调用
class WebKernelSyncReplyManager
{
public:
	WebKernelSyncReplyManager();
	~WebKernelSyncReplyManager();

	int GetReplyNo();
	bool Add(int no, CefRefPtr<CefListValue> spResult);
	CefRefPtr<CefListValue> Fetch(int no);

	void Clear();

private:

	int m_no;

	typedef stdext::hash_map<int, CefRefPtr<CefListValue> > mapReply;
	mapReply m_replys;
};


class WebKernelSyncProxy
{
public:
	WebKernelSyncProxy(void);
	~WebKernelSyncProxy(void);

	bool Init();
	bool Uninit();

	// 进程间消息
	bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message);

	// 线程间消息
	bool OnThreadMessagerRecevied(CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message);

public:

	// RenderProcess functions
	bool OnBeforeNavigation( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
		CefRefPtr<CefRequest> request, cef_navigation_type_t navigation_type, bool is_redirect );

	void OnFocusedNodeChanged( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
		CefRefPtr<CefDOMNode> node );

	// BrowserProcess UI Thread
	void OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
		const CefString& target_url, const CefString& target_frame_name,
		const CefPopupFeatures& popupFeatures);

private:

	bool OnBeforeNavigationMessage(CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message);
	bool OnBeforeNavigationRetMessage(CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message);

	bool OnFocusedNodeChangedMessage(CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message);

	bool OnBeforePopupMessage(CefRefPtr<CefBrowser> browser, CefRefPtr<CefProcessMessage> message);

private:

	static void SerializeFrame(CefListValue* lpListValue, CefFrame* lpFrame, int index);
	static CefRefPtr<CefFrame> UnSerializeFrame(CefListValue* lpListValue, CefBrowser* lpBrowser, int index);

private:

	// 事件名称列表
	static const wchar_t s_szOnBeforeNavigation[];
	static const wchar_t s_szOnBeforeNavigationRet[];
	static const wchar_t s_szOnFocusedNodeChanged[];

	static const wchar_t s_szOnBeforePopup[];
	
	// 事件回调函数列表
	typedef bool (WebKernelSyncProxy::*LPFNONPROCESSMESSAGE)(CefRefPtr<CefBrowser>, CefRefPtr<CefProcessMessage>);
	typedef stdext::hash_map<std::wstring, LPFNONPROCESSMESSAGE> messageMap;
	messageMap m_messageMap;

	// 回调应答管理器
	WebKernelSyncReplyManager m_replyManager;
};

#endif // __WEBKERNELSYNCPROXY_H__