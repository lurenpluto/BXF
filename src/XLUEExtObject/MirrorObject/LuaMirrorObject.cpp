#include "stdafx.h"
#include "./LuaMirrorObject.h"

LuaMirrorObject::LuaMirrorObject(void)
{
}

LuaMirrorObject::~LuaMirrorObject(void)
{
}

const XLLRTGlobalAPI LuaMirrorObject::s_szLuaMemberFuncs[] = 
{
	{"GetMirrorType", GetMirrorType},
	{"SetMirrorType", SetMirrorType},
	{NULL, NULL},
};

MirrorObject::MirrorType LuaMirrorObject::GetMirrorTypeFromString( const char* lpType )
{
	assert(lpType);

	MirrorObject::MirrorType type;
	if (strcmp(lpType, "hor") == 0)
	{
		type = MirrorObject::MirrorType_hor;
	}
	else if (strcmp(lpType, "ver") == 0)
	{
		type = MirrorObject::MirrorType_ver;
	}
	else if (strcmp(lpType, "both") == 0)
	{
		type = MirrorObject::MirrorType_both;
	}
	else
	{
		assert(strcmp(lpType, "none") == 0);
		type = MirrorObject::MirrorType_none;
	}

	return type;
}

const char* LuaMirrorObject::GetMirrorTypeString( MirrorObject::MirrorType type )
{
	const char* lpType = NULL;

	switch (type)
	{
	case MirrorObject::MirrorType_hor:
		lpType = "hor";
		break;
	case MirrorObject::MirrorType_ver:
		lpType = "ver";
		break;
	case MirrorObject::MirrorType_both:
		lpType = "both";
		break;
	default:
		assert(type == MirrorObject::MirrorType_none);
		lpType = "none";
		break;
	}

	return lpType;
}

int LuaMirrorObject::SetMirrorType( lua_State* luaState )
{
	MirrorObject* lpExtObj = CheckExtObject(luaState, 1);
	if (lpExtObj != NULL)
	{
		const char* lpType = luaL_checkstring(luaState, 2);
		
		lpExtObj->SetMirrorType(GetMirrorTypeFromString(lpType));
	}

	return 0;
}

int LuaMirrorObject::GetMirrorType( lua_State* luaState )
{
	MirrorObject* lpExtObj = CheckExtObject(luaState, 1);
	if (lpExtObj != NULL)
	{
		const char* lpType = GetMirrorTypeString(lpExtObj->GetMirrorType());

		lua_pushstring(luaState, lpType);

		return 1;
	}

	lua_pushnil(luaState);
	return 1;
}
