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
*   FileName    :   WindowBoltBrowser
*   Author      :   李亚星
*   Create      :   2013-6-26 
*   LastChange  :   2013-6-26
*   History     :	
*
*   Description :   窗口模式的浏览器核心
*
********************************************************************/ 
#ifndef __WINDOWBOLTBROWSER_H__
#define __WINDOWBOLTBROWSER_H__

#include "./BaseBoltBrowser.h"

class WindowBoltBrowser
	: public BaseBoltBrowser
{
private:

	virtual ~WindowBoltBrowser();

public:
	WindowBoltBrowser(XLUE_LAYOUTOBJ_HANDLE hObj, BoltBrowserEvents* lpEvents);
	
	bool Create(HWND hParent);
	bool Close(bool force);

	void SetRealFocus();

private:

	// BaseBoltBrowser
	virtual void OnAfterCreated();
	virtual void OnBeforeClose();
};

#endif // __WINDOWBOLTBROWSER_H__