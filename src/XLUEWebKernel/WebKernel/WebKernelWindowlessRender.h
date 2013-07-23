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
*   FileName    :   WebKernelWindowlessRender
*   Author      :   李亚星
*   Create      :   2013-6-12 
*   LastChange  :   2013-6-12
*   History     :	
*
*   Description :   CefRenderHandler的实现
*
********************************************************************/ 
#ifndef __WEBKERNELWINDOWLESSRENDER_H__
#define __WEBKERNELWINDOWLESSRENDER_H__

class WebKernelWindowlessRender
	: public CefRenderHandler
{
public:
	WebKernelWindowlessRender(XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual ~WebKernelWindowlessRender(void);

	XL_BITMAP_HANDLE GetCacheBitmap(int& width, int& height);

private:

	virtual bool GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect);

	virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect);

	virtual bool GetScreenPoint(CefRefPtr<CefBrowser> browser,
		int viewX,
		int viewY,
		int& screenX,
		int& screenY);

	virtual bool GetScreenInfo(CefRefPtr<CefBrowser> browser,
		CefScreenInfo& screen_info);

	virtual void OnPopupShow(CefRefPtr<CefBrowser> browser,
		bool show);

	virtual void OnPopupSize(CefRefPtr<CefBrowser> browser,
		const CefRect& rect);

	virtual void OnPaint(CefRefPtr<CefBrowser> browser,
		PaintElementType type,
		const RectList& dirtyRects,
		const void* buffer,
		int width, int height);

	virtual void OnCursorChange(CefRefPtr<CefBrowser> browser,
		CefCursorHandle cursor);

	IMPLEMENT_REFCOUNTING(WebKernelWindowlessRender)

private:

	LayoutObjectWrapper m_obj;

	XL_BITMAP_HANDLE m_hCacheBitmap;

	int m_cacheWidth, m_cacheHeight;
};

#endif // __WEBKERNELWINDOWLESSRENDER_H__