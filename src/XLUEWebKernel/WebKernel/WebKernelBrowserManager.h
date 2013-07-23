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
*   FileName    :   WebKernelBrowserManager
*   Author      :   李亚星
*   Create      :   2013-6-27 
*   LastChange  :   2013-6-27
*   History     :	
*
*   Description :   全局的browser管理器，用以维持当前打开来的浏览器对象
*
********************************************************************/ 
#ifndef __WEBKERNELBROWSERMANAGER_H__
#define __WEBKERNELBROWSERMANAGER_H__

#include <hash_map>

class BaseBoltBrowser;

class WebKernelBrowserManager
{
public:
	WebKernelBrowserManager(void);
	~WebKernelBrowserManager(void);

	bool Register(CefBrowser* lpBrowser, BaseBoltBrowser* lpBoltBrowser, XLUE_LAYOUTOBJ_HANDLE hOwnerObj);
	bool UnRegister(CefBrowser* lpBrowser);

	CefBrowser* GetBrowserFromID(int browserID);
	XLUE_LAYOUTOBJ_HANDLE GetOwnerObjFromID(int browserID);
	BaseBoltBrowser* GetBoltBrowserFromID(int browserID);

private:

	void OnBrowserCountChange(size_t count);

private:

	struct BrowserItem
	{
		int m_browserID;
		CefRefPtr<CefBrowser> m_browser;
		XLUE_LAYOUTOBJ_HANDLE m_owner;
		BaseBoltBrowser* m_lpBoltBrowser;
	};

	typedef stdext::hash_map<int, BrowserItem> mapBrowsers;
	mapBrowsers m_browsers;
};

#endif // __WEBKERNELBROWSERMANAGER_H__