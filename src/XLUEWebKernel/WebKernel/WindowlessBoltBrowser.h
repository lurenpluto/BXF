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
*   FileName    :   WindowlessBoltBrowser
*   Author      :   李亚星
*   Create      :   2013-6-26 
*   LastChange  :   2013-6-26
*   History     :	
*
*   Description :   无窗口模式的浏览器核心
*
********************************************************************/ 
#ifndef __WINDOWLESSBOLTBROWSER_H__
#define __WINDOWLESSBOLTBROWSER_H__

#include "./BaseBoltBrowser.h"
#include "./WebKernelWindowlessRender.h"
#include "./InputHandler.h"

class WindowlessBoltBrowser
	: public BaseBoltBrowser
{
private:

	virtual ~WindowlessBoltBrowser();

public:
	WindowlessBoltBrowser(XLUE_LAYOUTOBJ_HANDLE hObj, BoltBrowserEvents* lpEvents);
	

	void SetTransparnet(bool transparent);
	bool GetTransparent();

	bool Create(HWND hHostWnd);
	bool Close(bool force);

	long InputFilter(unsigned long actionType, unsigned long wParam, unsigned long lParam, bool& handled);

	void Resize();
	void Show();
	void Hide();
	void SetFocus();
	void KillFocus();
	void ReleaseCapture();

	XL_BITMAP_HANDLE GetCacheBitmap(int& width, int& height);

private:

	// BaseBoltBrowser
	virtual void OnAfterCreated();
	virtual void OnBeforeClose();

	virtual void OnInitClient();
	virtual void OnUninitClient();

private:

	CefRefPtr<WebKernelWindowlessRender> m_render;

	InputHandler* m_lpInputHandler;

	bool m_transparent;
};

#endif // __WINDOWLESSBOLTBROWSER_H__