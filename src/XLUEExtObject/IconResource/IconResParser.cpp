/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./IconResParser.h"

IconResParser::IconResParser(void)
{
}

IconResParser::~IconResParser(void)
{
}

bool IconResParser::ParseAttributeFromXML( IconRes* lpResObj, const char* lpName, const char* lpValue )
{
	assert(lpResObj);
	assert(lpName);
	assert(lpValue);

	bool ret = true;

	if (::strcmp(lpName, "module") == 0)
	{
		lpResObj->SetModule(lpValue);
	}
	else if (::strcmp(lpName, "file") == 0)
	{
		lpResObj->SetFile(lpValue);
	}
	else if (::strcmp(lpName, "ext") == 0)
	{
		lpResObj->SetExt(lpValue);
	}
	else if (::strcmp(lpName, "width") == 0)
	{
		int value = ::atoi(lpValue);
		lpResObj->SetWidth(value);
	}
	else if (::strcmp(lpName, "height") == 0)
	{
		int value = ::atoi(lpValue);
		lpResObj->SetHeight(value);
	}
	else if (::strcmp(lpName, "index") == 0)
	{
		int value = ::atoi(lpValue);
		lpResObj->SetIconIndex(value);
	}
	else
	{
		ret = false;
	}

	return ret;
}

bool IconResParser::ParseAttributeFromLua( IconRes* lpResObj, const char* lpName, lua_State* luaState, int index )
{
	assert(lpResObj);
	assert(lpName);
	assert(luaState);

	bool ret = true;

	if (::strcmp(lpName, "module") == 0)
	{
		const char* lpValue = luaL_checkstring(luaState, index);
		assert(lpValue);
		lpResObj->SetModule(lpValue);
	}
	else if (::strcmp(lpName, "file") == 0)
	{
		const char* lpValue = luaL_checkstring(luaState, index);
		assert(lpValue);

		lpResObj->SetFile(lpValue);
	}
	else if (::strcmp(lpName, "ext") == 0)
	{
		const char* lpValue = luaL_checkstring(luaState, index);
		assert(lpValue);

		lpResObj->SetExt(lpValue);
	}
	else if (::strcmp(lpName, "width") == 0)
	{
		int value = lua_tointeger(luaState, index);

		lpResObj->SetWidth(value);
	}
	else if (::strcmp(lpName, "height") == 0)
	{
		int value = lua_tointeger(luaState, index);

		lpResObj->SetHeight(value);
	}
	else if (::strcmp(lpName, "index") == 0)
	{
		int value = lua_tointeger(luaState, index);

		lpResObj->SetIconIndex(value);
	}
	else
	{
		assert(false);
		ret = false;
	}

	return ret;
}