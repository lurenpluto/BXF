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
*   FileName    :   WebKernelScriptIPCMessage
*   Author      :   范飞龙
*   Create      :   2013-10-29 
*   LastChange  :   2013-10-29
*   History     :	
*
*   Description :  定义javascript和lua进程间通信消息
*
********************************************************************/
#ifndef __WEBKERNELSCRIPTIPCMESSAGE_H__
#define __WEBKERNELSCRIPTIPCMESSAGE_H__

#include <sstream>
#include "./DBG.h"

class WebKernelScriptIPCMessage
{
private:
	static const wchar_t s_szJavascriptMessageHeader[];
	static const wchar_t s_szJavascriptCallHeader[];
	static const wchar_t s_szJavascriptCallbackHeader[];

	static const wchar_t s_szLuaMessageHeader[];
	static const wchar_t s_szLuaCallHeader[];
	static const wchar_t s_szLuaCallbackHeader[];

	static int m_luaFunctionNumber;
	static int m_javascriptFunctionNumber;

public:
	static const std::wstring EncodeJavascriptMessage(std::wstring message)
	{
		return Concat(s_szJavascriptMessageHeader,message);
	}
	static const std::wstring EncodeJavascriptCallMessage(std::wstring message)
	{
		return Concat(s_szJavascriptCallHeader,message);
	}
	static const std::wstring EncodeJavascriptCallbackMessage(std::wstring message)
	{
		return Concat(s_szJavascriptCallbackHeader,message);
	}
	static const std::wstring EncodeLuaMessage(std::wstring message)
	{
		return Concat(s_szLuaMessageHeader,message);
	}
	static const std::wstring EncodeLuaCallMessage(std::wstring message)
	{
		return Concat(s_szLuaCallHeader,message);
	}
	static const std::wstring EncodeLuaCallbackMessage(std::wstring message)
	{
		return Concat(s_szLuaCallbackHeader,message);
	}
	
public:
	static bool DecodeJavascriptMessage(const std::wstring& prefixMessage,std::wstring& output)
	{
		return Decode(s_szJavascriptMessageHeader,prefixMessage,output);
	}

	static bool DecodeJavascriptCallMessage(const std::wstring& prefixMessage,std::wstring& output)
	{
		return Decode(s_szJavascriptCallHeader,prefixMessage,output);
	}

	static bool DecodeJavascriptCallbackMessage(const std::wstring& prefixMessage,std::wstring& output)
	{
		return Decode(s_szJavascriptCallbackHeader,prefixMessage,output);
	}

	static bool DecodeLuaMessage(const std::wstring& prefixMessage,std::wstring& output)
	{
		return Decode(s_szLuaMessageHeader,prefixMessage,output);
	}

	static bool DecodeLuaCallMessage(const std::wstring& prefixMessage,std::wstring& output)
	{
		return Decode(s_szLuaCallHeader,prefixMessage,output);
	}

	static bool DecodeLuaCallbackMessage(const std::wstring& prefixMessage,std::wstring& output)
	{
		return Decode(s_szLuaCallbackHeader,prefixMessage,output);
	}

public:
	static const std::wstring WrapLuaFunctionName(const std::wstring& name)
	{
		return Wrap(name,m_luaFunctionNumber++);
	}
	static const std::wstring WrapLuaCallName(const std::wstring& name)
	{
		return Wrap(name,m_javascriptFunctionNumber++);
	}

public:
	static const std::wstring UnWrapLuaFunctionName(const std::wstring& name)
	{
		return UnWrap(name);
	}
	static const std::wstring UnWrapJavascriptFunctionName(const std::wstring& name)
	{
		return UnWrap(name);
	}
	
private:
	static const std::wstring Concat(const wchar_t* wstr1,std::wstring wstr2)
	{
		std::wstring s(wstr1);
		s += wstr2;
		return s;
	}

	static bool Decode(const wchar_t* header,const std::wstring& prefixMessage,std::wstring& output)
	{
		int length = std::wcslen(header);
		int equal = std::wcsncmp(prefixMessage.c_str(),header,length);
		if(equal==0)
		{
			output = prefixMessage.substr(length);
			return true;
		}
		return false;
	}

	static const std::wstring Wrap(std::wstring name,int number)
	{
		std::wstringstream wss;
		wss<<number<<"_"<<name;
		return wss.str();
	}

	static const std::wstring UnWrap(const std::wstring& name)
	{
		std::wstring output;
		int number;
		wchar_t split;
		std::wstringstream wss;
		wss<<name;
		wss>>number>>split>>output;
		return output;
	}
};



#endif //__WEBKERNELSCRIPTIPCMESSAGE_H__
