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
*   FileName    :   BoltBrowserObject
*   Author      :   李亚星
*   Create      :   2013-6-6 
*   LastChange  :   2013-6-6
*   History     :	
*
*   Description :   基于libcef的窗口模式浏览器对象
*
********************************************************************/ 
#ifndef __BOLTBROWSEROBJECT_H__
#define __BOLTBROWSEROBJECT_H__

#include "../WebKernel/WindowBoltBrowser.h"
#include "./BoltBrowserObjectEvents.h"
#include "./BaseBoltBrowserObject.h"

class BoltBrowserObject
	: public ExtRealObjMethodsImpl
	, public BaseBoltBrowserObject
{
public:
	BoltBrowserObject(XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual ~BoltBrowserObject(void);

	BoltBrowserObjectEvents* GetEvents();

private:

	// LayoutObject virtual methods
	virtual void OnInitControl();
	virtual void OnDestroy();

	// RealObject virtual methods
	virtual void OnCreateRealWindow(BOOL /*bCreate*/, OS_HOSTWND_HANDLE /*hWnd*/);
	virtual void OnSetRealFocus(BOOL /*focus*/);
	virtual OS_HOSTWND_HANDLE OnGetRenderWindow();

private:

	BoltBrowserObjectEvents* m_lpEvents;

	WindowBoltBrowser* m_lpBrowser;
};

#endif // __BOLTBROWSEROBJECT_H__