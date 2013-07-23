/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2012              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   PosixTranscode
*   Author      :   李亚星
*   Create      :   2012-12-27 18:05
*   LastChange  :   2012-12-27 18:05
*   History     :	
*
*   Description :   posix标准平台的转码函数
*
********************************************************************/ 
#ifndef __POSIXTRANSCODE_H__
#define __POSIXTRANSCODE_H__

#include <string>

class PosixTranscode
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

#endif // __POSIXTRANSCODE_H__