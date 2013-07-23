/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./LuaBaseBoltBrowserObject.h"
#include "./LuaFrame.h"

LuaBaseBoltBrowserObject::LuaBaseBoltBrowserObject(void)
{
}

LuaBaseBoltBrowserObject::~LuaBaseBoltBrowserObject(void)
{
}

const XLLRTGlobalAPI LuaBaseBoltBrowserObject::s_szLuaMemberFuncs[] = 
{
	{"Navigate", Navigate},

	{"CanGoBack", CanGoBack},
	{"GoBack", GoBack},
	{"CanGoForward", CanGoForward},
	{"GoForward", GoForward},

	{"IsLoading", IsLoading},
	{"Reload", Reload},
	{"ReloadIgnoreCache", ReloadIgnoreCache},
	{"StopLoad", StopLoad},

	{"HasDocument", HasDocument},

	{"GetMainFrame", GetMainFrame},
	{"GetFocusedFrame", GetFocusedFrame},
	{"GetFrame", GetFrame},

	{NULL, NULL},
};

bool LuaBaseBoltBrowserObject::RegisterAuxClass( const char* /*className*/, XL_LRT_ENV_HANDLE hEnv )
{
	assert(hEnv);

	static bool s_registered = false;
	if (!s_registered)
	{
		s_registered = true;
		LuaFrame::Register(hEnv);
	}

	return true;
}

bool LuaBaseBoltBrowserObject::GetLuaFunction( const char* className, const XLLRTGlobalAPI** lplpLuaFunctions, size_t* lpFuncCount )
{
	const XLLRTGlobalAPI* lpChildAPIs = GetChildLuaAPIs();
	assert(lpChildAPIs);

	size_t count = 0;
	const XLLRTGlobalAPI* lpIterator = lpChildAPIs;
	while (lpIterator->func != NULL)
	{
		++count;
		++lpIterator;
	}

	lpIterator = s_szLuaMemberFuncs;
	while(lpIterator->func != NULL)
	{
		++count;
		++lpIterator;
	}

	XLLRTGlobalAPI* lpAllAPIs = new XLLRTGlobalAPI[count];
	lpIterator = lpChildAPIs;
	XLLRTGlobalAPI *lpDestIterator = lpAllAPIs;
	while (lpIterator->func != NULL)
	{
		*lpDestIterator = *lpIterator;
		++lpDestIterator;
		++lpIterator;
	}

	lpIterator = s_szLuaMemberFuncs;
	while (lpIterator->func != NULL)
	{
		*lpDestIterator = *lpIterator;
		++lpDestIterator;
		++lpIterator;
	}

	*lplpLuaFunctions = lpAllAPIs;
	*lpFuncCount = count;

	return true;
}

int LuaBaseBoltBrowserObject::Navigate( lua_State* luaState )
{
	BaseBoltBrowserObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		std::wstring url;
		LuaHelper::GetUnicodeValue(luaState, 2, url);

		bool ret = lpObj->Navigate(url.c_str());

		lua_pushboolean(luaState, ret);

		return 1;
	}

	lua_pushboolean(luaState, 0);
	return 1;
}

int LuaBaseBoltBrowserObject::CanGoBack( lua_State* luaState )
{
	BaseBoltBrowserObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		bool ret = lpObj->CanGoBack();

		lua_pushboolean(luaState, ret);

		return 1;
	}

	lua_pushboolean(luaState, 0);
	return 1;
}

int LuaBaseBoltBrowserObject::GoBack( lua_State* luaState )
{
	BaseBoltBrowserObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		lpObj->GoBack();
	}

	return 0;
}

int LuaBaseBoltBrowserObject::CanGoForward( lua_State* luaState )
{
	BaseBoltBrowserObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		bool ret = lpObj->CanGoForward();

		lua_pushboolean(luaState, ret);

		return 1;
	}

	lua_pushboolean(luaState, 0);
	return 1;
}

int LuaBaseBoltBrowserObject::GoForward( lua_State* luaState )
{
	BaseBoltBrowserObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		lpObj->GoForward();
	}

	return 0;
}

int LuaBaseBoltBrowserObject::IsLoading( lua_State* luaState )
{
	BaseBoltBrowserObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		bool ret = lpObj->IsLoading();

		lua_pushboolean(luaState, ret);

		return 1;
	}

	lua_pushboolean(luaState, 0);
	return 1;
}

int LuaBaseBoltBrowserObject::Reload( lua_State* luaState )
{
	BaseBoltBrowserObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		lpObj->Reload();
	}

	return 0;
}

int LuaBaseBoltBrowserObject::ReloadIgnoreCache( lua_State* luaState )
{
	BaseBoltBrowserObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		lpObj->ReloadIgnoreCache();
	}

	return 0;
}

int LuaBaseBoltBrowserObject::StopLoad( lua_State* luaState )
{
	BaseBoltBrowserObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		lpObj->StopLoad();
	}

	return 0;
}

int LuaBaseBoltBrowserObject::HasDocument( lua_State* luaState )
{
	BaseBoltBrowserObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		bool ret = lpObj->HasDocument();

		lua_pushboolean(luaState, ret);

		return 1;
	}

	lua_pushboolean(luaState, 0);
	return 1;
}

int LuaBaseBoltBrowserObject::GetMainFrame( lua_State* luaState )
{
	BaseBoltBrowserObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		LuaFrame::PushFrame(luaState, lpObj->GetMainFrame());

		return 1;
	}

	lua_pushnil(luaState);
	return 1;
}

int LuaBaseBoltBrowserObject::GetFocusedFrame( lua_State* luaState )
{
	BaseBoltBrowserObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		LuaFrame::PushFrame(luaState, lpObj->GetFocusedFrame());

		return 1;
	}

	lua_pushnil(luaState);
	return 1;
}

int LuaBaseBoltBrowserObject::GetFrame( lua_State* luaState )
{
	BaseBoltBrowserObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		std::wstring name;
		LuaHelper::GetUnicodeValue(luaState, 2, name);

		LuaFrame::PushFrame(luaState, lpObj->GetFrame(name.c_str()));

		return 1;
	}

	lua_pushnil(luaState);
	return 1;
}

