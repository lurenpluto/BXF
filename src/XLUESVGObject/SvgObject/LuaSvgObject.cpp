/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./LuaSvgObject.h"

LuaSvgObject::LuaSvgObject(void)
{
}

LuaSvgObject::~LuaSvgObject(void)
{
}

const XLLRTGlobalAPI LuaSvgObject::s_szLuaMemberFuncs[] = 
{
	{"GetSvgResID", GetSvgResID},
	{"SetSvgResID", SetSvgResID},
    {"GetSvgRes", GetSvgRes},
    {"SetSvgRes", SetSvgRes},
	{NULL, NULL},
};

int LuaSvgObject::SetSvgResID( lua_State* luaState )
{
	SvgObject* lpExtObj = CheckExtObject(luaState, 1);
	if (lpExtObj != NULL)
	{
		const char* lpSvgResID = luaL_checkstring(luaState, 2);
		
		lpExtObj->SetSvgResID(lpSvgResID);
	}

	return 0;
}

int LuaSvgObject::GetSvgResID( lua_State* luaState )
{
	SvgObject* lpExtObj = CheckExtObject(luaState, 1);
	if (lpExtObj != NULL)
	{
		const char* lpSvgResID = lpExtObj->GetSvgResID();

		lua_pushstring(luaState, lpSvgResID);

		return 1;
	}

	return 0;
}

int LuaSvgObject::SetSvgRes( lua_State* luaState )
{
    SvgObject* lpObj = CheckExtObject(luaState, 1);
    if (lpObj != NULL)
    {
        XLUE_RESOURCE_HANDLE hResHandle = NULL;
        XLUE_CheckResEx(luaState, 2, XLUE_EXTRES_SVG, &hResHandle);

        lpObj->SetSvgRes(hResHandle);

        if (hResHandle != NULL)
        {
            XLUE_ReleaseResource(hResHandle);
        }
    }

    return 0;
}

int LuaSvgObject::GetSvgRes( lua_State* luaState )
{
    SvgObject* lpObj = CheckExtObject(luaState, 1);
    if (lpObj != NULL)
    {
        XLUE_RESOURCE_HANDLE hResHandle = lpObj->GetSvgRes();

        XLUE_PushRes(luaState, hResHandle);

        return 1;
    }

    lua_pushnil(luaState);
    return 1;
}
