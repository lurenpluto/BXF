/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./WindowlessBoltBrowserObject.h"

WindowlessBoltBrowserObject::WindowlessBoltBrowserObject(XLUE_LAYOUTOBJ_HANDLE hObj)
:ExtLayoutObjMethodsImpl(hObj)
{
	m_lpEvents = new WindowlessBoltBrowserObjectEvents(hObj);

	m_lpBrowser = new WindowlessBoltBrowser(hObj, this);

	BaseBoltBrowserObject::Init(hObj, m_lpBrowser, m_lpEvents);
}

WindowlessBoltBrowserObject::~WindowlessBoltBrowserObject(void)
{
	BaseBoltBrowserObject::Uninit();

	assert(m_lpEvents);
	m_lpEvents->Release();
	m_lpEvents = NULL;

	assert(m_lpBrowser);
	m_lpBrowser->Release();
	m_lpBrowser = NULL;
}

WindowlessBoltBrowserObjectEvents* WindowlessBoltBrowserObject::GetEvents()
{
	assert(m_lpEvents);

	return m_lpEvents;
}

void WindowlessBoltBrowserObject::OnInitControl()
{

}

void WindowlessBoltBrowserObject::OnDestroy()
{

}

void WindowlessBoltBrowserObject::OnSetFocus( BOOL bFocus, XLUE_LAYOUTOBJ_HANDLE /*hOppositeObj*/, FocusReason /*reason*/ )
{
	assert(m_lpBrowser);

	if (bFocus)
	{
		m_lpBrowser->SetFocus();
	}
	else
	{
		m_lpBrowser->KillFocus();
	}
}

void WindowlessBoltBrowserObject::OnVisibleChange( BOOL bVisible )
{
	assert(m_lpBrowser);

	if (bVisible)
	{
		m_lpBrowser->Show();
	}
	else
	{
		m_lpBrowser->Hide();
	}
}

void WindowlessBoltBrowserObject::OnAbsPosChanged( const RECT* /*lpOldAbsPos*/, const RECT* /*lpNewAbsPos*/ )
{
	assert(m_lpBrowser);

	m_lpBrowser->Resize();
}

void WindowlessBoltBrowserObject::OnCaptureChange( BOOL bCapture )
{
	assert(m_lpBrowser);

	if (!bCapture)
	{
		m_lpBrowser->ReleaseCapture();
	}
}

long WindowlessBoltBrowserObject::PostInputFilter( unsigned long actionType, unsigned long wParam
												  , unsigned long lParam, BOOL* lpHandled )
{
	assert(m_lpBrowser);

	bool handled = false;
	long ret = m_lpBrowser->InputFilter(actionType, wParam, lParam, handled);

	if (lpHandled != NULL)
	{
		*lpHandled = handled? TRUE : FALSE;
	}

	return ret;
}

void WindowlessBoltBrowserObject::OnCreateHostWnd( XLUE_OBJTREE_HANDLE /*hTree*/, XLUE_HOSTWND_HANDLE hHostWnd, BOOL bCreate )
{
	assert(m_lpBrowser);

	if (bCreate)
	{
		assert(hHostWnd);
		HWND hWnd = (HWND)XLUE_GetHostWndWindowHandle(hHostWnd);
		assert(::IsWindow(hWnd));

		m_lpBrowser->Create(hWnd);
	}
	else
	{
		m_lpBrowser->Close(true);
	}
}

void WindowlessBoltBrowserObject::OnPaintEx( XL_BITMAP_HANDLE hBitmapDest, const RECT* lpDestClipRect
											, const RECT* lpSrcClipRect, unsigned char alpha, XLGraphicHint* lpHint )
{
	assert(m_lpBrowser);

	XL_BITMAP_HANDLE hCacheBitmap;
	int cacheWidth, cacheHeight;
	
	hCacheBitmap = m_lpBrowser->GetCacheBitmap(cacheWidth, cacheHeight);
	if (hCacheBitmap == NULL)
	{
		return;
	}

	RECT rcClip = *lpSrcClipRect;
	if (rcClip.right > cacheWidth)
	{
		rcClip.right = cacheWidth;
	}
	if (rcClip.bottom > cacheHeight)
	{
		rcClip.bottom = cacheHeight;
	}

	if (RectHelper::IsRectEmpty(&rcClip))
	{
		return;
	}

	XL_BITMAP_HANDLE hClipBitmap = XL_ClipSubBindBitmap(hCacheBitmap, &rcClip);
	assert(hClipBitmap);

	XLBlendHint hint;
	hint.BaseHint = *lpHint;
	hint.ConstAlpha = alpha;
	hint.BlendType = XLGRAPHIC_BLEND_SRC_ALPHA;

	XL_Blend(hBitmapDest, lpDestClipRect->left, lpDestClipRect->top, hClipBitmap, &hint);

	XL_ReleaseBitmap(hClipBitmap);
}

void WindowlessBoltBrowserObject::SetTransparnet( bool transparent )
{
	assert(m_lpBrowser);

	return m_lpBrowser->SetTransparnet(transparent);
}

bool WindowlessBoltBrowserObject::GetTransparnet()
{
	assert(m_lpBrowser);

	return m_lpBrowser->GetTransparent();
}