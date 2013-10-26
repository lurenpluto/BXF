/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./WebKernelLuaHelper.h"

void WebKernelLuaHelper::PushCefString(lua_State* luaState, const CefString& value)
{
	std::string utf8Value;
	XLUETranscode::Unicode_to_UTF8(value.c_str(), value.size(), utf8Value);

	lua_pushstring(luaState, utf8Value.c_str());
}

CefString WebKernelLuaHelper::ToCefString(lua_State* luaState,int index)
{
	std::wstring unicodeValue;
	const char* value = lua_tostring(luaState,index);
	XLUETranscode::UTF8_to_Unicode(value,strlen(value),unicodeValue);
	return CefString(unicodeValue);
}

void WebKernelLuaHelper::PushCefListValue(lua_State* luaState, CefRefPtr<CefListValue> lpListValue)
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
		switch (type) 
		{
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
			PushCefString(luaState,lpListValue->GetString(i));
			lua_rawseti(luaState,-2,slot);
			break;
		case VTYPE_NULL:
			lua_pushnil(luaState);
			lua_rawseti(luaState,-2,slot);
		case VTYPE_LIST:
			PushCefListValue(luaState,lpListValue->GetList(i));
			lua_rawseti(luaState,-2,slot);
			break;
		case VTYPE_DICTIONARY:
			PushCefDictionaryValue(luaState,lpListValue->GetDictionary(i));
			lua_rawseti(luaState,-2,slot);
		default:
			break;
		}
	}
}

CefRefPtr<CefListValue> WebKernelLuaHelper::ToCefListValue(lua_State* luaState, int index)
{
	CefRefPtr<CefListValue> listValue = CefListValue::Create();
	int length = lua_objlen(luaState,index);
	for (int i=0;i<length;i++)
	{
		int tableIndex = i+1;
		int lastTopIndex = lua_gettop(luaState);

		lua_rawgeti(luaState,index,tableIndex);
		
		if(lua_isboolean(luaState,-1))
		{
			listValue->SetBool(i,!!lua_toboolean(luaState,-1));
		}
		else if(lua_isnumber(luaState,-1))
		{
			listValue->SetDouble(i,lua_tonumber(luaState,-1));
		}
		else if(lua_isstring(luaState,-1))
		{
			listValue->SetString(i,ToCefString(luaState,-1));
		}
		else if(lua_isnoneornil(luaState,-1))
		{
			listValue->SetNull(i);
		}
		else
		{
			listValue->SetNull(i);
		}
		lua_settop(luaState,lastTopIndex);
	}
	return listValue;
}

void WebKernelLuaHelper::PushCefDictionaryValue(lua_State* luaState,CefRefPtr<CefDictionaryValue> lpDictionaryValue)
{
	CefDictionaryValue::KeyList keys;
	lpDictionaryValue->GetKeys(keys);
	CefDictionaryValue::KeyList::const_iterator beg = keys.begin();
	CefDictionaryValue::KeyList::const_iterator end = keys.end();

	lua_newtable(luaState);
	for (CefDictionaryValue::KeyList::const_iterator it = beg;it!=end;++it)
	{
		CefString key = *it;
		CefValueType type = lpDictionaryValue->GetType(key);
		switch(type)
		{
		case VTYPE_BOOL:
			{
				PushCefString(luaState,key);
				lua_pushboolean(luaState,lpDictionaryValue->GetBool(key));
				lua_rawset(luaState,-3);
			}
			break;
		case VTYPE_DOUBLE:
			{
				PushCefString(luaState,key);
				lua_pushnumber(luaState,lpDictionaryValue->GetDouble(key));
				lua_rawset(luaState,-3);
			}
			break;
		case VTYPE_INT:
			{
				PushCefString(luaState,key);
				lua_pushinteger(luaState,lpDictionaryValue->GetInt(key));
				lua_rawset(luaState,-3);
			}
			break;
		case VTYPE_STRING:
			{
				PushCefString(luaState,key);
				PushCefString(luaState,lpDictionaryValue->GetString(key));
				lua_rawset(luaState,-3);
			}
			break;
		case VTYPE_NULL:
			{
				PushCefString(luaState,key);
				lua_pushnil(luaState);
				lua_rawset(luaState,-3);
			}
			break;
		case VTYPE_LIST: 
			{
				PushCefString(luaState,key);
				PushCefListValue(luaState,lpDictionaryValue->GetList(key));
				lua_rawset(luaState,-3);
			}
			break;
		case VTYPE_DICTIONARY:
			{
				PushCefString(luaState,key);
				PushCefDictionaryValue(luaState,lpDictionaryValue->GetDictionary(key));
				lua_rawset(luaState,-3);
			}
			break;
		default:
			break;
		}
	}
}

CefRefPtr<CefDictionaryValue> WebKernelLuaHelper::ToCefDictionaryValue(lua_State* luaState,int index)
{
	CefRefPtr<CefDictionaryValue> dictionaryValue = CefDictionaryValue::Create();

	// table is in the stack at index
	lua_pushnil(luaState);  /* first key */
	while (lua_next(luaState, index) != 0) 
	{
		// uses 'key' (at index -2) and 'value' (at index -1) 
		CefString key = ToCefString(luaState,-2);
		if(lua_isboolean(luaState,-1))
		{
			dictionaryValue->SetBool(key,!!lua_toboolean(luaState,-1));
		}
		else if(lua_isnumber(luaState,-1))
		{
			dictionaryValue->SetDouble(key,lua_tonumber(luaState,-1));
		}
		else if(lua_isstring(luaState,-1))
		{
			dictionaryValue->SetString(key,ToCefString(luaState,-1));
		}
		else if(lua_isnoneornil(luaState,-1))
		{
			dictionaryValue->SetNull(key);
		}
		else if(lua_istable(luaState,-1))
		{
			dictionaryValue->SetDictionary(key,ToCefDictionaryValue(luaState,-1));
		}
		else
		{
			dictionaryValue->SetNull(key);
		}

		// removes 'value'; keeps 'key' for next iteration
		lua_pop(luaState, 1);
	}
	return dictionaryValue;
}