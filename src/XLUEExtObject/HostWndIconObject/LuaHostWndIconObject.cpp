/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./LuaHostWndIconObject.h"

XLLRTGlobalAPI LuaHostWndIconObject::s_szLuaMemberFuncs[] = 
{
	{"SetIconResID", SetIconResID},
	{"GetIconResID", GetIconResID},

	{"SetIcon", SetIcon},
	{"GetIcon", GetIcon},

	{NULL, NULL}
};

LuaHostWndIconObject::LuaHostWndIconObject(void)
{
}

LuaHostWndIconObject::~LuaHostWndIconObject(void)
{
}

int LuaHostWndIconObject::SetIconResID( lua_State* luaState )
{
	HostWndIconObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		const char* lpResID = lua_tostring(luaState, 2);
		bool big = !!lua_toboolean(luaState, 3);

		lpObj->SetIconResID(lpResID, big);
	}

	return 0;
}

int LuaHostWndIconObject::GetIconResID( lua_State* luaState )
{
	HostWndIconObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		bool big = !!lua_toboolean(luaState, 2);

		lua_pushstring(luaState, lpObj->GetIconResID(big));

		return 1;
	}

	lua_pushnil(luaState);
	return 1;
}

int LuaHostWndIconObject::SetIcon( lua_State* luaState )
{
	HostWndIconObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		XLUE_RESOURCE_HANDLE hResHandle = NULL;
		XLUE_CheckResEx(luaState, 2, XLUE_EXTRES_ICON, &hResHandle);

		bool big = !!lua_toboolean(luaState, 3);

		lpObj->SetIcon(hResHandle, big);

		if (hResHandle != NULL)
		{
			XLUE_ReleaseResource(hResHandle);
		}
	}

	return 0;
}

int LuaHostWndIconObject::GetIcon( lua_State* luaState )
{
	HostWndIconObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		bool big = !!lua_toboolean(luaState, 2);
		XLUE_RESOURCE_HANDLE hResHandle = lpObj->GetIcon(big);

		XLUE_PushRes(luaState, hResHandle);

		return 1;
	}

	lua_pushnil(luaState);
	return 1;
}