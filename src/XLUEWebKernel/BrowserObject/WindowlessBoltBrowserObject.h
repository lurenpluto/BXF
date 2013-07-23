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
*   FileName    :   WindowlessBoltBrowserObject
*   Author      :   李亚星
*   Create      :   2013-6-26 
*   LastChange  :   2013-6-26
*   History     :	
*
*   Description :   基于libcef的无窗口模式浏览器对象
*
********************************************************************/ 
#ifndef __WINDOWLESSBOLTBROWSEROBJECT_H__
#define __WINDOWLESSBOLTBROWSEROBJECT_H__

#include "../WebKernel/WindowlessBoltBrowser.h"
#include "./BoltBrowserObjectEvents.h"
#include "./BaseBoltBrowserObject.h"

class WindowlessBoltBrowserObject
	: public ExtLayoutObjMethodsImpl
	, public BaseBoltBrowserObject
{
public:
	WindowlessBoltBrowserObject(XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual ~WindowlessBoltBrowserObject(void);

	// 返回值不增持引用计数！
	WindowlessBoltBrowserObjectEvents* GetEvents();

	void SetTransparnet(bool transparent);
	bool GetTransparnet();

private:

	// LayoutObject virtual methods
	virtual void OnInitControl();
	virtual void OnDestroy();

	virtual void OnSetFocus(BOOL bFocus, XLUE_LAYOUTOBJ_HANDLE /*hOppositeObj*/, FocusReason /*reason*/);
	virtual void OnVisibleChange(BOOL bVisible);
	virtual void OnAbsPosChanged(const RECT* /*lpOldAbsPos*/, const RECT* /*lpNewAbsPos*/);
	virtual void OnCaptureChange(BOOL bCapture);
	
	virtual long PostInputFilter(unsigned long /*actionType*/, unsigned long /*wParam*/
		, unsigned long /*lParam*/, BOOL* lpHandled);

	virtual void OnCreateHostWnd(XLUE_OBJTREE_HANDLE /*hTree*/, XLUE_HOSTWND_HANDLE /*hHostWnd*/, BOOL /*bCreate*/);

	virtual void OnPaintEx(XL_BITMAP_HANDLE /*hBitmapDest*/, const RECT* /*lpDestClipRect*/
		, const RECT* /*lpSrcClipRect*/, unsigned char /*alpha*/, XLGraphicHint* /*lpHint*/);

private:

	WindowlessBoltBrowserObjectEvents* m_lpEvents;

	WindowlessBoltBrowser* m_lpBrowser;
};

#endif // __WINDOWLESSBOLTBROWSEROBJECT_H__