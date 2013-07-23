/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2012              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   Win32Transcode
*   Author      :   李亚星
*   Create      :   2012-12-27 18:02
*   LastChange  :   2012-12-27 18:02
*   History     :	
*
*   Description :   win32平台下的转码函数
*
********************************************************************/ 
#ifndef __WIN32TRANSCODE_H__
#define __WIN32TRANSCODE_H__

#include <string>

class Win32Transcode
{
public:

	static void Unicode_to_UTF8(const wchar_t* in, size_t len, std::string& out);
	static void UTF8_to_Unicode(const char* in, size_t len, std::wstring& out);

	static void ANSI_to_Unicode(const char* in, size_t len, std::wstring& out);
	static void Unicode_to_ANSI(const wchar_t* in, size_t len, std::string& out);

	static void Unicode_to_GBK(const wchar_t* in, size_t len, std::string& out);
	static void GBK_to_Unicode(const char* in, size_t len, std::wstring& out);

	static void GBK_to_UTF8(const char* in, size_t len, std::string& out);
	static void UTF8_to_GBK(const char* in, size_t len, std::string& out);
};

#endif // __WIN32TRANSCODE_H__