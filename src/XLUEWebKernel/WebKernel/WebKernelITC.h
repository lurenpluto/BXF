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
*   FileName    :   WebKernelITC
*   Author      :   李亚星
*   Create      :   2013-6-27 
*   LastChange  :   2013-6-27
*   History     :	
*
*   Description :   浏览器的io线程调用同步到ui线程的辅助类, 用以发起同步调用
*
********************************************************************/ 
#ifndef __WEBKERNELITC_H__
#define __WEBKERNELITC_H__

#include <atlbase.h>
#include <atlwin.h>

class WebKernelITC
{
public:

	WebKernelITC();
	~WebKernelITC();

private:

#define WEBKERNELITC_WND_MSG (WM_USER + 100)

	struct ITCMessage
	{
		int m_browserID;
		unsigned long m_threadID;
		CefRefPtr<CefProcessMessage> m_message;
		bool m_handled;
	};

	class WebKernelITCWindow
		:public CWindowImpl<WebKernelITCWindow>
	{
	public:
		
		BEGIN_MSG_MAP(WebKernelITCWindow)
			MESSAGE_HANDLER(WEBKERNELITC_WND_MSG, OnThreadMessage)
		END_MSG_MAP()

		LRESULT OnThreadMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	}m_wnd;

public:

	// 初始化和反初始化须在UI线程调用
	bool Init();
	bool Uninit();

	// 此方法可以在浏览器进程的任何线程发起调用
	long SendMessage(int browserIdentifier, CefRefPtr<CefProcessMessage> msg, bool& handled);

private:

	long OnThreadMessage(int browserIdentifier, unsigned long threadID, CefRefPtr<CefProcessMessage> msg, bool& handled);
};

#endif // __WEBKERNELITC_H__