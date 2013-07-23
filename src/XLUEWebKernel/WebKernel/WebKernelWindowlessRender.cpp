/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./WebKernelWindowlessRender.h"

WebKernelWindowlessRender::WebKernelWindowlessRender(XLUE_LAYOUTOBJ_HANDLE hObj)
:m_obj(hObj),
m_hCacheBitmap(NULL),
m_cacheWidth(0),
m_cacheHeight(0)
{
}

WebKernelWindowlessRender::~WebKernelWindowlessRender(void)
{
}

bool WebKernelWindowlessRender::GetRootScreenRect( CefRefPtr<CefBrowser> browser, CefRect& rect )
{
	HostWndWrapper hostWnd = m_obj.GetBindHostWnd();
	assert(hostWnd);

	if (hostWnd == NULL)
	{
		return false;
	}

	RECT rcWnd;
	hostWnd.GetWindowRect(&rcWnd);

	rect.x = rcWnd.left;
	rect.y = rcWnd.top;
	rect.width = rcWnd.right - rcWnd.left;
	rect.height = rcWnd.bottom - rcWnd.top;

	return true;
}

bool WebKernelWindowlessRender::GetViewRect( CefRefPtr<CefBrowser> browser, CefRect& rect )
{
	const RECT* lpAbsPos = m_obj.GetAbsPos();
	assert(lpAbsPos);

	if (lpAbsPos == NULL)
	{
		return false;
	}

	RECT rcAbsPos = *lpAbsPos;

	rect.x = rect.y = 0;
	rect.width = rcAbsPos.right - rcAbsPos.left;
	rect.height = rcAbsPos.bottom - rcAbsPos.top;

	return true;
}

bool WebKernelWindowlessRender::GetScreenPoint( CefRefPtr<CefBrowser> browser, int viewX, int viewY, int& screenX, int& screenY )
{
	HostWndWrapper hostWnd = m_obj.GetBindHostWnd();
	assert(hostWnd);

	const RECT* lpAbsPos = m_obj.GetAbsPos();
	assert(lpAbsPos);

	if (hostWnd == NULL || lpAbsPos == NULL)
	{
		return false;
	}

	POINT pt;
	pt.x = viewX + lpAbsPos->left;
	pt.y = viewY + lpAbsPos->top;
	hostWnd.TreePtToHostWndPt(pt);
	hostWnd.HostWndPtToScreenPt(pt);

	screenX = pt.x;
	screenY = pt.y;

	return true;
}

bool WebKernelWindowlessRender::GetScreenInfo( CefRefPtr<CefBrowser> browser, CefScreenInfo& screen_info )
{
	screen_info.device_scale_factor = 1.0;
	screen_info.depth = 32;
	screen_info.depth_per_component = 8;
	screen_info.is_monochrome = false;

	HostWndWrapper hostwnd = m_obj.GetBindHostWnd();
	HWND hWnd = (HWND)hostwnd.GetWindowHandle();

	HMONITOR hMonitor = ::MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
	MONITORINFO info = { sizeof(MONITORINFO) };
	::GetMonitorInfo(hMonitor, &info);

	screen_info.rect.x = info.rcMonitor.left;
	screen_info.rect.y = info.rcMonitor.top;
	screen_info.rect.width = info.rcMonitor.right - info.rcMonitor.left;
	screen_info.rect.height = info.rcMonitor.bottom - info.rcMonitor.top;

	screen_info.available_rect.x = info.rcWork.left;
	screen_info.available_rect.y = info.rcWork.top;
	screen_info.available_rect.width = info.rcWork.right - info.rcWork.left;
	screen_info.available_rect.height = info.rcWork.bottom - info.rcWork.top;

	return true;
}

void WebKernelWindowlessRender::OnPopupShow( CefRefPtr<CefBrowser> browser, bool show )
{
	assert(false);
}

void WebKernelWindowlessRender::OnPopupSize( CefRefPtr<CefBrowser> browser, const CefRect& rect )
{
	assert(false);
}

void WebKernelWindowlessRender::OnPaint( CefRefPtr<CefBrowser> browser, PaintElementType type, 
										const RectList& dirtyRects, const void* buffer, int width, int height )
{
	if (m_hCacheBitmap != NULL && (m_cacheWidth != width || m_cacheHeight != height))
	{
		XL_ReleaseBitmap(m_hCacheBitmap);
	}

	if (m_hCacheBitmap == NULL)
	{
		m_hCacheBitmap = XL_CreateBitmap(XLGRAPHIC_CT_ARGB32, width, height);
		m_cacheWidth = width;
		m_cacheHeight = height;
	}

	unsigned char* lpDestBuffer = XL_GetBitmapBuffer(m_hCacheBitmap, 0, 0);
	const unsigned char* lpSrcBuffer = (unsigned char*)buffer;

	RectList::const_iterator cp, end = dirtyRects.end();
	for (cp = dirtyRects.begin(); cp != end; ++cp)
	{
		const CefRect& rcDirty = *cp;

		unsigned char* lpDestLine = lpDestBuffer + width * rcDirty.y * 4 + rcDirty.x * 4;
		const unsigned char* lpSrcLine = lpSrcBuffer + width * rcDirty.y * 4 + rcDirty.x * 4;

		for (long top = 0; top < rcDirty.height; ++top)
		{
			::memcpy(lpDestLine, lpSrcLine, rcDirty.width * 4);
			lpDestLine += width * 4;
			lpSrcLine += width * 4;
		}

		RECT rect;
		rect.left = rcDirty.x;
		rect.top = rcDirty.y;
		rect.right = rect.left + rcDirty.width;
		rect.bottom = rect.top + rcDirty.height;

		m_obj.PushDirtyRect(&rect);
	}
}

void WebKernelWindowlessRender::OnCursorChange( CefRefPtr<CefBrowser> browser, CefCursorHandle cursor )
{
	char hexCursor[20] = { 0 };
	::sprintf_s(hexCursor, "#%x", cursor);

	m_obj.SetCursorID(hexCursor);
}

XL_BITMAP_HANDLE WebKernelWindowlessRender::GetCacheBitmap( int& width, int& height )
{
	width = m_cacheWidth;
	height = m_cacheHeight;

	return m_hCacheBitmap;
}