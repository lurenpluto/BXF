/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./LuaNotifyIconObject.h"

#include <ShellAPI.h>

const XLLRTGlobalAPI LuaNotifyIconObject::s_szLuaMemberFuncs[] = 
{
	{"SetIconResID", SetIconResID},
	{"GetIconResID", GetIconResID},

	{"SetIcon", SetIcon},
	{"GetIcon", GetIcon},

	{"SetTip", SetTip},
	{"GetTip", GetTip},

	{"SetIconVisible", SetIconVisible},
	{"GetIconVisible", GetIconVisible},

	{"ShowBalloonTip", ShowBalloonTip},

	{NULL, NULL}
};


LuaNotifyIconObject::LuaNotifyIconObject(void)
{
}

LuaNotifyIconObject::~LuaNotifyIconObject(void)
{
}

int LuaNotifyIconObject::SetIconResID( lua_State* luaState )
{
	NotifyIconObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		const char* lpResID = lua_tostring(luaState, 2);

		lpObj->SetIconResID(lpResID);
	}

	return 0;
}

int LuaNotifyIconObject::GetIconResID( lua_State* luaState )
{
	NotifyIconObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		lua_pushstring(luaState, lpObj->GetIconResID());

		return 1;
	}

	lua_pushnil(luaState);
	return 1;
}

int LuaNotifyIconObject::SetIcon( lua_State* luaState )
{
	NotifyIconObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		XLUE_RESOURCE_HANDLE hResHandle = NULL;
		XLUE_CheckResEx(luaState, 2, XLUE_EXTRES_ICON, &hResHandle);

		lpObj->SetIcon(hResHandle);

		if (hResHandle != NULL)
		{
			XLUE_ReleaseResource(hResHandle);
		}
	}

	return 0;
}

int LuaNotifyIconObject::GetIcon( lua_State* luaState )
{
	NotifyIconObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		XLUE_RESOURCE_HANDLE hResHandle = lpObj->GetIcon();

		XLUE_PushRes(luaState, hResHandle);

		return 1;
	}

	lua_pushnil(luaState);
	return 1;
}

int LuaNotifyIconObject::SetTip( lua_State* luaState )
{
	NotifyIconObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		const char* lpTip = lua_tostring(luaState, 2);
		std::wstring tip;
		if (lpTip != NULL)
		{
			XLUETranscode::UTF8_to_Unicode(lpTip, ::strlen(lpTip), tip);
		}

		lpObj->SetTip(tip.c_str());
	}

	return 0;
}

int LuaNotifyIconObject::GetTip( lua_State* luaState )
{
	NotifyIconObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		const wchar_t* lpTip = lpObj->GetTip();
		std::string tip;
		XLUETranscode::Unicode_to_UTF8(lpTip, ::wcslen(lpTip), tip);

		lua_pushstring(luaState, tip.c_str());

		return 1;
	}

	lua_pushnil(luaState);

	return 1;
}

int LuaNotifyIconObject::SetIconVisible( lua_State* luaState )
{
	NotifyIconObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		bool visible = !!lua_toboolean(luaState, 2);
		bool ret = lpObj->SetIconVisible(visible);

		lua_pushboolean(luaState, ret);
		return 1;
	}

	lua_pushboolean(luaState, 0);
	return 1;
}

int LuaNotifyIconObject::GetIconVisible( lua_State* luaState )
{
	NotifyIconObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		lua_pushboolean(luaState, lpObj->GetIconVisible());

		return 1;
	}

	lua_pushboolean(luaState, 0);

	return 1;
}

int LuaNotifyIconObject::ShowBalloonTip( lua_State* luaState )
{
	NotifyIconObject* lpObj = CheckExtObject(luaState, 1);
	if (lpObj != NULL)
	{
		std::wstring message, title;

		const char* lpMessage = lua_tostring(luaState, 2);
		if (lpMessage != NULL)
		{
			XLUETranscode::UTF8_to_Unicode(lpMessage, ::strlen(lpMessage), message);
		}

		const char* lpTitle = lua_tostring(luaState, 3);
		if (lpTitle != NULL)
		{
			XLUETranscode::UTF8_to_Unicode(lpTitle, ::strlen(lpTitle), title);
		}

		unsigned int timeout = (unsigned int)lua_tointeger(luaState, 4);

		const char* lpIconType = lua_tostring(luaState, 5);
		unsigned int flags = NIIF_NONE;
		if (lpIconType != NULL)
		{
			flags = GetIconType(lpIconType);
		}
		
		bool ret = lpObj->ShowBalloonTip(message.c_str(), title.c_str(), timeout, flags);

		lua_pushboolean(luaState, ret);
		return 1;
	}

	lua_pushboolean(luaState, 0);
	return 1;
}

unsigned int LuaNotifyIconObject::GetIconType( const char* lpIconType )
{
	assert(lpIconType);

	unsigned int flags = NIIF_NONE;
	if (::strcmp(lpIconType, "error") == 0)
	{
		flags = NIIF_ERROR;
	}
	else if (::strcmp(lpIconType, "info") == 0)
	{
		flags = NIIF_INFO;
	}
	else if (::strcmp(lpIconType, "user") == 0)
	{
		flags = NIIF_USER;
	}
	else if (::strcmp(lpIconType, "warning") == 0)
	{
		flags = NIIF_WARNING;
	}
	else
	{
		assert(::strcmp(lpIconType, "none") == 0);
		flags = NIIF_NONE;
	}

	return flags;
}