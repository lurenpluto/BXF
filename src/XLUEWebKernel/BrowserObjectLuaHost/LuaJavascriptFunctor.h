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
*   FileName    :   LuaBaseFunctor
*   Author      :   ·¶·ÉÁú
*   Create      :   2013-10-28 
*   LastChange  :   2013-10-28
*   History     :	
*
*   Description :   Lua×¢²á¸øJavascriptµÄº¯Êý
*
********************************************************************/ 
#ifndef __LUAJAVASCRIPTFUNCTOR_H__
#define __LUAJAVASCRIPTFUNCTOR_H__

#include "./LuaBaseFunctor.h"

class LuaJavascriptFunctor:public BaseLuaListener
{
public:
	LuaJavascriptFunctor(std::wstring functionName,lua_State* luaState,long luaRef);
	CefRefPtr<CefDictionaryValue> operator()(CefRefPtr<CefDictionaryValue> dictionaryValue);
	
private:
	std::wstring m_functionName;
};

class LuaJavascriptCallbackFunctor:public BaseLuaListener
{
public:
	LuaJavascriptCallbackFunctor(std::wstring functionName,lua_State* luaState,long luaRef);
	bool operator()(CefRefPtr<CefDictionaryValue> dictionaryValue);

private:
	std::wstring m_functionName;
};

#endif //__LUAJAVASCRIPTFUNCTOR_H__