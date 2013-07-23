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
*   FileName    :   WebKernelMessageLoop
*   Author      :   李亚星
*   Create      :   2013-6-28 
*   LastChange  :   2013-6-28
*   History     :	
*
*   Description :   浏览器的消息循环驱动，目前采用timer
*
********************************************************************/ 
#ifndef __WEBKERNELMESSAGELOOP_H__
#define __WEBKERNELMESSAGELOOP_H__

class WebKernelMessageLoop
{
public:
	WebKernelMessageLoop(void);
	~WebKernelMessageLoop(void);

	void IncreaseBrowserUser();
	void DecreaseBrowserUser();

private:

	bool Start();
	bool End();

	long OnMessageLoopWork();
	static long XLUE_STDCALL MessageLoopWorkCallBack(void* userData);

private:

	// Timer
	void OnTimer(unsigned int timerID);

private:

	// 当前依赖消息循环的浏览器数量
	int m_browserUserCount;

	// XLUE消息循环机制的cookie
	long m_messageLoopWorkCookie;

	// 消息循环timerid
	unsigned long m_msgLoopTimerID;

	typedef Xunlei::Bolt::MemberTimerManagerWrapperT<WebKernelMessageLoop> TimerManager;
	TimerManager m_timerManager;
};

#endif // __WEBKERNELMESSAGELOOP_H__