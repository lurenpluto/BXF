/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./LuaSvgObject.h"

LuaSVGObject::LuaSVGObject(void)
{
}

LuaSVGObject::~LuaSVGObject(void)
{
}

const XLLRTGlobalAPI LuaSVGObject::s_szLuaMemberFuncs[] = 
{
	{"GetSVGResID", GetSVGResID},
	{"SetSVGResID", SetSVGResID},
    {"GetSVGRes", GetSVGRes},
    {"SetSVGRes", SetSVGRes},
    {"SetPreserveAspectRatio", SetPreserveAspectRatio},
    {"GetPreserveAspectRatio", GetPreserveAspectRatio},
    {"SetEnableSVGAlpha", SetEnableSVGAlpha},
    {"GetEnableSVGAlpha", GetEnableSVGAlpha},
	{NULL, NULL},
};

int LuaSVGObject::SetSVGResID( lua_State* luaState )
{
	SVGObject* lpExtObj = CheckExtObject(luaState, 1);
	if (lpExtObj != NULL)
	{
		const char* lpSVGResID = luaL_checkstring(luaState, 2);
		
		lpExtObj->SetSVGResID(lpSVGResID);
	}

	return 0;
}

int LuaSVGObject::GetSVGResID( lua_State* luaState )
{
	SVGObject* lpExtObj = CheckExtObject(luaState, 1);
	if (lpExtObj != NULL)
	{
		const char* lpSVGResID = lpExtObj->GetSVGResID();

		lua_pushstring(luaState, lpSVGResID);

		return 1;
	}
    lua_pushnil(luaState);
	return 1;
}

int LuaSVGObject::SetSVGRes( lua_State* luaState )
{
    SVGObject* lpObj = CheckExtObject(luaState, 1);
    if (lpObj != NULL)
    {
        XLUE_RESOURCE_HANDLE hResHandle = NULL;
        XLUE_CheckResEx(luaState, 2, XLUE_EXTRES_SVG, &hResHandle);

        lpObj->SetSVGRes(hResHandle);

        if (hResHandle != NULL)
        {
            XLUE_ReleaseResource(hResHandle);
        }
    }

    return 0;
}

int LuaSVGObject::GetSVGRes( lua_State* luaState )
{
    SVGObject* lpObj = CheckExtObject(luaState, 1);
    if (lpObj != NULL)
    {
        XLUE_RESOURCE_HANDLE hResHandle = lpObj->GetSVGRes();

        XLUE_PushRes(luaState, hResHandle);

        return 1;
    }

    lua_pushnil(luaState);
    return 1;
}

int LuaSVGObject::SetPreserveAspectRatio(lua_State* luaState)
{
    SVGObject* lpObj = CheckExtObject(luaState, 1);
    if (lpObj != NULL)
    {
        bool preserveAspectRatio = !!lua_toboolean(luaState, 2);

        lpObj->SetPreserveAspectRatio(preserveAspectRatio);
    }

    return 0;
}

int LuaSVGObject::GetPreserveAspectRatio( lua_State* luaState )
{
    SVGObject* lpExtObj = CheckExtObject(luaState, 1);
    if (lpExtObj != NULL)
    {
        bool preserveAspectRatio = lpExtObj->GetPreserveAspectRatio();

        lua_pushboolean(luaState, preserveAspectRatio);

        return 1;
    }

    lua_pushboolean(luaState, false);
    return 1;
}

int LuaSVGObject::SetEnableSVGAlpha(lua_State* luaState)
{
    SVGObject* lpObj = CheckExtObject(luaState, 1);
    if (lpObj != NULL)
    {
        bool enableSVGAlpha = !!lua_toboolean(luaState, 2);

        lpObj->SetEnableSVGAlpha(enableSVGAlpha);
    }

    return 0;
}

int LuaSVGObject::GetEnableSVGAlpha( lua_State* luaState )
{
    SVGObject* lpExtObj = CheckExtObject(luaState, 1);
    if (lpExtObj != NULL)
    {
        bool enableSVGAlpha = lpExtObj->GetEnableSVGAlpha();

        lua_pushboolean(luaState, enableSVGAlpha);

        return 1;
    }
    lua_pushboolean(luaState, false);
    return 1;
}
