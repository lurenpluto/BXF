/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./LuaWindowlessBoltBrowserObject.h"

LuaWindowlessBoltBrowserObject::LuaWindowlessBoltBrowserObject(void)
{
}

LuaWindowlessBoltBrowserObject::~LuaWindowlessBoltBrowserObject(void)
{
}

const XLLRTGlobalAPI LuaWindowlessBoltBrowserObject::s_szLuaMemberFuncs[] = 
{
	{"SetTransparnet", SetTransparnet},
	{"GetTransparnet", GetTransparnet},

	{NULL, NULL}
};

WindowlessBoltBrowserObject* LuaWindowlessBoltBrowserObject::CheckBoltBrowserObject( lua_State* luaState, int index )
{
	return CheckExtObjectEx<WindowlessBoltBrowserObject>(luaState, index);
}

bool LuaWindowlessBoltBrowserObject::PushBoltBrowserObject( lua_State* luaState, WindowlessBoltBrowserObject* lpObj )
{
	return PushExtObjectEx<WindowlessBoltBrowserObject>(luaState, lpObj);
}

int LuaWindowlessBoltBrowserObject::SetTransparnet( lua_State* luaState )
{
	WindowlessBoltBrowserObject* lpObj = CheckBoltBrowserObject(luaState, 1);
	if (lpObj != NULL)
	{
		bool value = !!lua_toboolean(luaState, 2);

		lpObj->SetTransparnet(value);
	}

	return 0;
}

int LuaWindowlessBoltBrowserObject::GetTransparnet( lua_State* luaState )
{
	WindowlessBoltBrowserObject* lpObj = CheckBoltBrowserObject(luaState, 1);
	if (lpObj != NULL)
	{
		lua_pushboolean(luaState, lpObj->GetTransparnet());

		return 1;
	}

	lua_pushboolean(luaState, 0);
	return 1;
}

const XLLRTGlobalAPI* LuaWindowlessBoltBrowserObject::GetChildLuaAPIs()
{
	return s_szLuaMemberFuncs;
}
