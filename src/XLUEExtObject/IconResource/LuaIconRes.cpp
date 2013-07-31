/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./LuaIconRes.h"

XLLRTGlobalAPI LuaIconRes::s_szLuaMemberFuncs[] = 
{
	{"GetIconHandle", GetIconHandle},
	{NULL, NULL}
};

LuaIconRes::LuaIconRes(void)
{
}

LuaIconRes::~LuaIconRes(void)
{
}

int LuaIconRes::GetIconHandle( lua_State* luaState )
{
	IconRes* lpResObj = CheckExtResObj(luaState, 1, XLUE_EXTRES_ICON);
	if (lpResObj != NULL)
	{
		XLGP_ICON_HANDLE hIcon = lpResObj->GetIconHandle();
		if (hIcon != NULL)
		{
			XLGP_PushIcon(luaState, hIcon);
		}
	}

	lua_pushnil(luaState);
	return 1;
}