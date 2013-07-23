/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./WindowlessBoltBrowser.h"

WindowlessBoltBrowser::WindowlessBoltBrowser( XLUE_LAYOUTOBJ_HANDLE hObj, BoltBrowserEvents* lpEvents )
:BaseBoltBrowser(hObj, lpEvents),
m_lpInputHandler(NULL),
m_transparent(false)
{

}

WindowlessBoltBrowser::~WindowlessBoltBrowser()
{
	if (m_lpInputHandler != NULL)
	{
		delete m_lpInputHandler;
		m_lpInputHandler = NULL;
	}
}

bool WindowlessBoltBrowser::Create( HWND hHostWnd )
{
	assert(hHostWnd);
	assert(::IsWindow(hHostWnd));

	CefWindowInfo info;
	info.SetAsOffScreen(hHostWnd);
	info.SetTransparentPainting(m_transparent? TRUE : FALSE);
	
	return BaseBoltBrowser::Create(info);
}

bool WindowlessBoltBrowser::Close( bool force )
{
	return BaseBoltBrowser::Close(force);
}

long WindowlessBoltBrowser::InputFilter( unsigned long actionType, unsigned long wParam, unsigned long lParam, bool& handled )
{
	if (m_lpInputHandler == NULL)
	{
		return 0;
	}

	if (actionType >= XLUE_ACTION_MOUSEFIRST && actionType <= XLUE_ACTION_MOUSELAST)
	{
		const RECT* lpAbsPos = m_obj.GetAbsPos();
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
	
		x -= lpAbsPos->left;
		y -= lpAbsPos->top;

		lParam = MAKELPARAM(x, y);
	}

	if (actionType == XLUE_ACTION_LMOUSE_DOWN
		|| actionType == XLUE_ACTION_MMOUSE_DOWN
		|| actionType == XLUE_ACTION_RMOUSE_DOWN)
	{
		m_obj.SetCaptureMouse(true);
	}
	else if (actionType == XLUE_ACTION_LMOUSE_UP
		|| actionType == XLUE_ACTION_MMOUSE_UP
		|| actionType == XLUE_ACTION_RMOUSE_UP)
	{
		m_obj.SetCaptureMouse(false);
	}

	return m_lpInputHandler->InputFilter(actionType, wParam, lParam, handled);
}

void WindowlessBoltBrowser::OnAfterCreated()
{
	assert(m_lpInputHandler == NULL);
	assert(m_browser);

	m_lpInputHandler = new InputHandler(m_browser);

	if (m_obj.GetFocus())
	{
		SetFocus();
	}

	if (m_obj.GetVisible())
	{
		Show();
	}
	else
	{
		Hide();
	}

	BaseBoltBrowser::OnAfterCreated();
}

void WindowlessBoltBrowser::OnBeforeClose()
{
	assert(m_lpInputHandler);
	delete m_lpInputHandler;
	m_lpInputHandler = NULL;
}

void WindowlessBoltBrowser::Resize()
{
	if (m_browser != NULL)
	{
		CefRefPtr<CefBrowserHost> spHost = m_browser->GetHost();
		assert(spHost);
		if (spHost != NULL)
		{
			spHost->WasResized();
		}
	}
}

void WindowlessBoltBrowser::SetFocus()
{
	if (m_browser != NULL)
	{
		CefRefPtr<CefBrowserHost> spHost = m_browser->GetHost();
		assert(spHost);
		if (spHost != NULL)
		{
			spHost->SendFocusEvent(true);
		}
	}
}

void WindowlessBoltBrowser::KillFocus()
{
	if (m_browser != NULL)
	{
		CefRefPtr<CefBrowserHost> spHost = m_browser->GetHost();
		assert(spHost);
		if (spHost != NULL)
		{
			spHost->SendFocusEvent(false);
		}
	}
}

void WindowlessBoltBrowser::ReleaseCapture()
{
	if (m_browser != NULL)
	{
		CefRefPtr<CefBrowserHost> spHost = m_browser->GetHost();
		assert(spHost);
		if (spHost != NULL)
		{
			spHost->SendCaptureLostEvent();
		}
	}
}

void WindowlessBoltBrowser::Show()
{
	if (m_browser != NULL)
	{
		CefRefPtr<CefBrowserHost> spHost = m_browser->GetHost();
		assert(spHost);
		if (spHost != NULL)
		{
			spHost->WasHidden(false);
		}
	}
}

void WindowlessBoltBrowser::Hide()
{
	if (m_browser != NULL)
	{
		CefRefPtr<CefBrowserHost> spHost = m_browser->GetHost();
		assert(spHost);
		if (spHost != NULL)
		{
			spHost->WasHidden(true);
		}
	}
}

void WindowlessBoltBrowser::SetTransparnet( bool transparent )
{
	m_transparent = transparent;
}

bool WindowlessBoltBrowser::GetTransparent()
{
	return m_transparent;
}

void WindowlessBoltBrowser::OnInitClient()
{
	BaseBoltBrowser::OnInitClient();

	assert(m_client);
	assert(m_render == NULL);
	assert(m_obj);

	m_render = new WebKernelWindowlessRender(m_obj);
	m_client->SetRenderHandler(m_render);
}

void WindowlessBoltBrowser::OnUninitClient()
{
	assert(m_client);
	assert(m_render);

	m_client->SetRenderHandler(NULL);
	m_render = NULL;

	BaseBoltBrowser::OnUninitClient();
}

XL_BITMAP_HANDLE WindowlessBoltBrowser::GetCacheBitmap( int& width, int& height )
{
	assert(m_render);

	return m_render->GetCacheBitmap(width, height);
}