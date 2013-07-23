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
*   FileName    :   WebKernelHostWnd
*   Author      :   李亚星
*   Create      :   2013-6-6 
*   LastChange  :   2013-6-6
*   History     :	
*
*   Description :   窗口模式浏览器的宿主窗口
*
********************************************************************/ 
#ifndef __WEBKERNELHOSTWND_H__
#define __WEBKERNELHOSTWND_H__

#include <atlwin.h>

class WebKernelHostWnd
	: public CWindowImpl<WebKernelHostWnd>
{
public:
	WebKernelHostWnd(void);
	virtual ~WebKernelHostWnd(void);

	DECLARE_WND_CLASS_EX(L"XLUEBoltBrowserObjectHostWnd", CS_DBLCLKS, COLOR_WINDOW)

private:

	BEGIN_MSG_MAP(WebKernelHostWnd)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	END_MSG_MAP()

	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};

#endif // __WEBKERNELHOSTWND_H__