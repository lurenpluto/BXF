/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./LuaBaseFunctor.h"
#include "./LuaJavascriptFunctor.h"
#include "../WebKernel/DBG.h"
#include <sstream>

LuaJavascriptFunctor::LuaJavascriptFunctor(std::wstring functionName, lua_State* luaState, long luaRef )
:BaseLuaListener(luaState, luaRef)
,m_functionName(functionName)
{

}

CefRefPtr<CefDictionaryValue> LuaJavascriptFunctor::operator()(CefRefPtr<CefDictionaryValue> dictionaryValue)
{
	// 保持栈顶
	LuaStackKeeper luaState(m_luaState);


	// 获取Lua函数，并入栈
	BaseLuaListener::PushLuaFunction();

	// 字典参数入栈
	WebKernelLuaHelper::PushCefDictionaryValue(luaState,dictionaryValue);

	// 调用Lua函数
	int nRet = BaseLuaListener::Call(1, 1,m_functionName.c_str());
	
	// 获取返回值字典
	CefRefPtr<CefDictionaryValue> result = CefDictionaryValue::Create();
	if (nRet == 0)
	{
		result = WebKernelLuaHelper::ToCefDictionaryValue(luaState,-1);
	}

	return result;
}


LuaJavascriptCallbackFunctor::LuaJavascriptCallbackFunctor(std::wstring functionName, lua_State* luaState, long luaRef )
:BaseLuaListener(luaState, luaRef)
,m_functionName(functionName)
{

}

bool LuaJavascriptCallbackFunctor::operator()(CefRefPtr<CefDictionaryValue> dictionaryValue)
{
	// 保持栈顶
	LuaStackKeeper luaState(m_luaState);


	// 获取Lua函数，并入栈
	BaseLuaListener::PushLuaFunction();

	// 字典参数入栈
	WebKernelLuaHelper::PushCefDictionaryValue(luaState,dictionaryValue);

	// 调用Lua函数
	int nRet = BaseLuaListener::Call(1, 1,m_functionName.c_str());

	// 获取返回值字典
	if (nRet == 0)
	{
		return true;
	}

	return false;
}
