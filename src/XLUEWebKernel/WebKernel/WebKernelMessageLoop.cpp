/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./WebKernelMessageLoop.h"

WebKernelMessageLoop::WebKernelMessageLoop(void)
:m_msgLoopTimerID(0),
m_browserUserCount(0),
m_messageLoopWorkCookie(0)
{
	m_timerManager.SetTimerProc(this, &WebKernelMessageLoop::OnTimer);
}

WebKernelMessageLoop::~WebKernelMessageLoop(void)
{
	assert(m_msgLoopTimerID == 0);
	assert(m_browserUserCount == 0);
	assert(m_messageLoopWorkCookie == 0);

	End();
}

void WebKernelMessageLoop::IncreaseBrowserUser()
{
	assert(m_browserUserCount >= 0);
	++m_browserUserCount;

	if (m_browserUserCount == 1)
	{
		Start();
	}
}

void WebKernelMessageLoop::DecreaseBrowserUser()
{
	assert(m_browserUserCount >= 1);
	--m_browserUserCount;

	if (m_browserUserCount <= 0)
	{
		End();
	}
}

bool WebKernelMessageLoop::Start()
{
	if (g_webKernelGlobal.m_setting.GetMsgLoopUseTimer())
	{
		assert(m_msgLoopTimerID == 0);
		m_msgLoopTimerID = m_timerManager.SetTimer(g_webKernelGlobal.m_setting.GetMsgLoopTimerInterval());
		assert(m_msgLoopTimerID);
	}
	else
	{
		assert(m_messageLoopWorkCookie == 0);
		m_messageLoopWorkCookie = XLUE_RegisterMessageLoopListener(&WebKernelMessageLoop::MessageLoopWorkCallBack, this);
		assert(m_messageLoopWorkCookie);
	}

	return true;
}

bool WebKernelMessageLoop::End()
{
	if (m_messageLoopWorkCookie != 0)
	{
		BOOL ret = XLUE_UnregisterMessageLoopListener(m_messageLoopWorkCookie, NULL);
		assert(ret);
		m_messageLoopWorkCookie = 0;
	}

	if (m_msgLoopTimerID != 0)
	{
		m_timerManager.KillTimer(m_msgLoopTimerID);
		m_msgLoopTimerID = 0;
	}

	return true;
}

void WebKernelMessageLoop::OnTimer( unsigned int /*timerID*/ )
{
	::CefDoMessageLoopWork();
}

long WebKernelMessageLoop::OnMessageLoopWork()
{
	::CefDoMessageLoopWork();

	return 0;
}

long XLUE_STDCALL WebKernelMessageLoop::MessageLoopWorkCallBack( void* userData )
{
	WebKernelMessageLoop* lpThis = (WebKernelMessageLoop*)userData;
	assert(lpThis);

	return lpThis->OnMessageLoopWork();
}