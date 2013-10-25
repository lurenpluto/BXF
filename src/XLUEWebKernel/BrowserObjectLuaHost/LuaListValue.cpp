/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./LuaListValue.h"
#include "../WebKernel/DBG.h"

void LuaListValue::PushListValue(lua_State* luaState, CefListValue* lpListValue)
{
	int arg_length = static_cast<int>(lpListValue->GetSize());
	if (arg_length == 0)
	{
		return;
	}

	lua_newtable(luaState);
	for (int i = 0; i < arg_length; ++i)
	{
		int slot=i+1;
		CefValueType type = lpListValue->GetType(i);
		switch (type) {
		case VTYPE_LIST: 
			PushListValue(luaState,lpListValue->GetList(i));
			lua_rawseti(luaState,-2,slot);
			break;
		case VTYPE_BOOL:
			lua_pushboolean(luaState,lpListValue->GetBool(i));
			lua_rawseti(luaState,-2,slot);
			break;
		case VTYPE_DOUBLE:
			lua_pushnumber(luaState,lpListValue->GetDouble(i));
			lua_rawseti(luaState,-2,slot);
			break;
		case VTYPE_INT:
			lua_pushinteger(luaState,lpListValue->GetInt(i));
			lua_rawseti(luaState,-2,slot);
			break;
		case VTYPE_STRING:
			WebKernelLuaHelper::PushString(luaState,lpListValue->GetString(i));
			lua_rawseti(luaState,-2,slot);
			break;
		//case VTYPE_NULL:
		//	DBG("push nil");
		//	lua_pushnil(luaState);
		//	lua_rawseti(luaState,-2,slot);
		default:
			break;
		}
	}
}

CefListValue* LuaListValue::CheckListValue(lua_State* luaState, int index)
{
	//TODO: 将Lua的table转换成CefListValue
	return NULL;
}