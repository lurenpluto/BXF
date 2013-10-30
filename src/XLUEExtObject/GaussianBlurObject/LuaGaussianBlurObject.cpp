/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./LuaGaussianBlurObject.h"

LuaGaussianBlurObject::LuaGaussianBlurObject(void)
{
}

LuaGaussianBlurObject::~LuaGaussianBlurObject(void)
{
}

float LuaGaussianBlurObject::GetSigmaFromString(const char* lpSigma)
{
	float ret = atof(lpSigma);
	return ret;
}

const XLLRTGlobalAPI LuaGaussianBlurObject::s_szLuaMemberFuncs[] = 
{
	{"SetSigma", SetSigma},
	{"GetSigma", GetSigma},
	{"SetRadius", SetRadius},
	{"GetRadius", GetRadius}, 
	{"SetGaussianType", SetGaussianType},
	{"GetGaussianType", GetGaussianType},
	{NULL, NULL}
};


int LuaGaussianBlurObject::SetSigma( lua_State* luaState )
{
	GaussianBlurObject* lpExtObj = CheckExtObject(luaState, 1);
	if (lpExtObj != NULL)
	{
		float lpSigma = luaL_checknumber(luaState, 2);
		lpExtObj->SetSigma(lpSigma);
	}

	return 0;
}

int LuaGaussianBlurObject::GetSigma( lua_State* luaState )
{
	GaussianBlurObject* lpExtObj = CheckExtObject(luaState, 1);
	if (lpExtObj != NULL)
	{
		float sigma = lpExtObj->GetSigma();
		lua_pushnumber(luaState, sigma);
		return 1;
	}

	lua_pushnil(luaState);
	return 1;
}

int LuaGaussianBlurObject::SetRadius( lua_State* luaState )
{
	GaussianBlurObject* lpExtObj = CheckExtObject(luaState, 1);
	if (lpExtObj != NULL)
	{
		int lpRadius = luaL_checkint(luaState, 2);
		lpExtObj->SetRadius(lpRadius);
	}

	return 0;
}

int LuaGaussianBlurObject::GetRadius( lua_State* luaState )
{
	GaussianBlurObject* lpExtObj = CheckExtObject(luaState, 1);
	if (lpExtObj != NULL)
	{
		int radius = lpExtObj->GetRadius();
		lua_pushinteger(luaState, radius);
		return 1;
	}

	lua_pushnil(luaState);
	return 1;
}

int LuaGaussianBlurObject::SetGaussianType( lua_State* luaState )
{
	GaussianBlurObject* lpExtObj = CheckExtObject(luaState, 1);
	if (lpExtObj != NULL)
	{
		const char* type = luaL_checkstring(luaState, 2);
		lpExtObj->SetGaussianType(type);
	}

	return 0;
}

int LuaGaussianBlurObject::GetGaussianType( lua_State* luaState )
{
	GaussianBlurObject* lpExtObj = CheckExtObject(luaState, 1);
	if (lpExtObj != NULL)
	{
		const char* type = lpExtObj->GetGaussianType();
		lua_pushstring(luaState, type);
		return 1;
	}

	lua_pushnil(luaState);
	return 1;
}
