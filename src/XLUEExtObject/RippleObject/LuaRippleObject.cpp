/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./LuaRippleObject.h"

const XLLRTGlobalAPI LuaRippleObject::s_szLuaMemberFuncs[] = 
{
	{"SetMouseDrop", SetMouseDrop},
	{"GetMouseDrop", GetMouseDrop},

	{"SetRandomDrop", SetRandomDrop},
	{"GetRandomDrop", GetRandomDrop},

	{"SetUpdateInterval", SetUpdateInterval},
	{"GetUpdateInterval", GetUpdateInterval},

	{"SetDropDensity", SetDropDensity},
	{"GetDropDensity", GetDropDensity},

	{"SetWaterDensity", SetWaterDensity},
	{"GetWaterDensity", GetWaterDensity},

	{"ClearAllDrops", ClearAllDrops},

	{NULL, NULL},
};

LuaRippleObject::LuaRippleObject(void)
{
}

LuaRippleObject::~LuaRippleObject(void)
{
}

int LuaRippleObject::SetMouseDrop( lua_State* luaState )
{
	RippleObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		bool enable = !!lua_toboolean(luaState, 2);
		lpObj->SetMouseDrop(enable);
	}

	return 0;
}

int LuaRippleObject::GetMouseDrop( lua_State* luaState )
{
	RippleObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		lua_pushboolean(luaState, lpObj->GetMouseDrop());
		return 1;
	}

	lua_pushboolean(luaState, 0);
	return 1;
}

int LuaRippleObject::SetRandomDrop( lua_State* luaState )
{
	RippleObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		bool enable = !!lua_toboolean(luaState, 2);
		lpObj->SetRandomDrop(enable);
	}

	return 0;
}

int LuaRippleObject::GetRandomDrop( lua_State* luaState )
{
	RippleObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		lua_pushboolean(luaState, lpObj->GetRandomDrop());
		return 1;
	}

	lua_pushboolean(luaState, 0);
	return 1;
}

int LuaRippleObject::SetDropDensity( lua_State* luaState )
{
	RippleObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		unsigned long value = (unsigned long)lua_tointeger(luaState, 2);
		lpObj->SetDropDensity(value);
	}

	return 0;
}

int LuaRippleObject::GetDropDensity( lua_State* luaState )
{
	RippleObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		lua_pushinteger(luaState, lpObj->GetDropDensity());
		return 1;
	}

	lua_pushinteger(luaState, 0);
	return 1;
}

int LuaRippleObject::SetUpdateInterval( lua_State* luaState )
{
	RippleObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		unsigned long value = (unsigned long)lua_tointeger(luaState, 2);
		lpObj->SetUpdateInterval(value);
	}

	return 0;
}

int LuaRippleObject::GetUpdateInterval( lua_State* luaState )
{
	RippleObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		lua_pushinteger(luaState, lpObj->GetUpdateInterval());
		return 1;
	}

	lua_pushinteger(luaState, 0);
	return 1;
}

int LuaRippleObject::SetWaterDensity( lua_State* luaState )
{
	RippleObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		unsigned long value = (unsigned long)lua_tointeger(luaState, 2);
		lpObj->SetWaterDensity(value);
	}

	return 0;
}

int LuaRippleObject::GetWaterDensity( lua_State* luaState )
{
	RippleObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		lua_pushinteger(luaState, lpObj->GetWaterDensity());
		return 1;
	}

	lua_pushinteger(luaState, 0);
	return 1;
}

int LuaRippleObject::ClearAllDrops( lua_State* luaState )
{
	RippleObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		lpObj->ClearAllDrops();
	}

	return 0;
}