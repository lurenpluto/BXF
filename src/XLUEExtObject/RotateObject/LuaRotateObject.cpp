/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./LuaRotateObject.h"

LuaRotateObject::LuaRotateObject(void)
{
}

LuaRotateObject::~LuaRotateObject(void)
{
}

RotateMode LuaRotateObject::GetRotateModeFromString( const char* value )
{
	assert(value);

	RotateMode mode = RotateMode_normal;
	if (::strcmp(value, "antialias") == 0)
	{
		mode = RotateMode_antialias;
	}
	else if (::strcmp(value, "normal") == 0)
	{
		mode = RotateMode_normal;
	}
	else
	{
		assert(false);
		mode = RotateMode_normal;
	}

	return mode;
}

const char* LuaRotateObject::GetStringFromRotateMode( RotateMode mode )
{
	if (mode == RotateMode_antialias)
	{
		return "antialias";
	}
	else if (mode == RotateMode_normal)
	{
		return "normal";
	}
	else
	{
		assert(false);
		return NULL;
	}
}

int LuaRotateObject::SetAngel( lua_State* luaState )
{
	RotateObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		lpObj->SetAngel(lua_tonumber(luaState, 2));
	}

	return 0;
}

int LuaRotateObject::GetAngel( lua_State* luaState )
{
	RotateObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		lua_pushnumber(luaState, lpObj->GetAngel());
	}

	return 0;
}

int LuaRotateObject::SetCenter( lua_State* luaState )
{
	RotateObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		bool retx, rety;
		if (lua_isnumber(luaState, 2))
		{
			retx = lpObj->SetNumberX(lua_tointeger(luaState, 2));
		}
		else
		{
			retx = lpObj->SetStringX(luaL_checkstring(luaState, 2));
		}

		if (lua_isnumber(luaState, 3))
		{
			rety = lpObj->SetNumberY(lua_tointeger(luaState, 3));
		}
		else
		{
			rety = lpObj->SetStringY(luaL_checkstring(luaState, 3));
		}

		lua_pushboolean(luaState, retx);
		lua_pushboolean(luaState, rety);

		return 2;
	}

	lua_pushboolean(luaState, 0);
	lua_pushboolean(luaState, 0);

	return 2;
}

int LuaRotateObject::GetCenter( lua_State* luaState )
{
	RotateObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		POINT pt = lpObj->GetCenter();

		lua_pushinteger(luaState, pt.x);
		lua_pushinteger(luaState, pt.y);

		return 2;
	}

	lua_pushinteger(luaState, 0);
	lua_pushinteger(luaState, 0);

	return 2;
}

int LuaRotateObject::SetRotateMode( lua_State* luaState )
{
	RotateObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		RotateMode mode = GetRotateModeFromString(luaL_checkstring(luaState, 2));

		lpObj->SetRotateMode(mode);
	}

	return 0;
}

int LuaRotateObject::GetRotateMode( lua_State* luaState )
{
	RotateObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		lua_pushstring(luaState, GetStringFromRotateMode(lpObj->GetRotateMode()));

		return 1;
	}

	lua_pushnil(luaState);
	return 1;
}

const XLLRTGlobalAPI LuaRotateObject::s_szLuaMemberFuncs[] = 
{
	{"SetAngel", SetAngel},
	{"GetAngel", GetAngel},

	{"SetCenter", SetCenter},
	{"GetCenter", GetCenter},

	{"SetRotateMode", SetRotateMode},
	{"GetRotateMod", GetRotateMode},

	{NULL, NULL},
};