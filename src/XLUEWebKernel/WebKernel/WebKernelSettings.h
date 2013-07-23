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
*   FileName    :   WebKernelSettings
*   Author      :   李亚星
*   Create      :   2013-6-4 
*   LastChange  :   2013-6-4
*   History     :	
*
*   Description :   cef的基础配置选项，进程相关
*
********************************************************************/ 
#ifndef __WEBKERNELSETTINGS_H__
#define __WEBKERNELSETTINGS_H__

class WebKernelSettings
{
public:
	WebKernelSettings();
	~WebKernelSettings();

	bool Init();
	bool Uninit();

	const CefSettings& GetCefSettings() const;

	bool GetMsgLoopUseTimer() const;
	unsigned long GetMsgLoopTimerInterval() const;

private:

	static const wchar_t s_szUserAgent[];
	static const wchar_t s_szDefaultLocale[];
	static const wchar_t s_szOriginUserAgent[];
	static const wchar_t s_szBoltBrowserUserAgent[];

	CefSettings m_setting;

	// 消息循环相关配置
	bool m_msgLoopUseTimer;
	unsigned long m_msgLoopTimerInterval;
};

#endif // __WEBKERNELSETTINGS_H__