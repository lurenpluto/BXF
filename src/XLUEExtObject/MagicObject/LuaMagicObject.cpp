/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./LuaMagicObject.h"

LuaMagicObject::LuaMagicObject(void)
{
}

LuaMagicObject::~LuaMagicObject(void)
{
}

XLLRTGlobalAPI LuaMagicObject::s_szLuaMemberFuncs[] = 
{
	{"GetType", GetType},
	{"SetType", SetType},
	{NULL, NULL},
};

int LuaMagicObject::GetType( lua_State* luaState )
{
	MagicObject* lpExtObj = CheckExtObject(luaState, 1);
	if (lpExtObj != NULL)
	{
		
	}

	lua_pushnil(luaState);
	return 1;
}

int LuaMagicObject::SetType( lua_State* luaState )
{
	MagicObject* lpExtObj = CheckExtObject(luaState, 1);
	if (lpExtObj != NULL)
	{

	}

	return 0;
}