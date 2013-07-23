/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2011              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   LuaHelper
*   Author      :   李亚星
*   Create      :   2011-10-13 2:09
*   LastChange  :   2011-10-13 2:09
*   History     :	
*
*   Description :   lua的辅助函数
*
********************************************************************/ 
#ifndef __LUAHELPER_H__
#define __LUAHELPER_H__

#include "../Transcode/XLUETranscode.h"

namespace Xunlei
{
namespace XAF
{

class LuaHelper
{
public:

	// 如果index指定的栈值为function，那么就把它放到registry，
	// 并返回相应的refvalue，否则返回LUA_NOREF
	static int RefIfFunction(lua_State* luaState, int index, bool check = false)
	{
		int ref = LUA_NOREF;

		if (check)
		{
			luaL_argcheck(luaState, lua_isfunction(luaState, index), index, "function expect");
		}

		if (lua_isfunction(luaState, index))
		{
			lua_pushvalue(luaState, index);
			ref = luaL_ref(luaState, LUA_REGISTRYINDEX);
			assert(ref != LUA_NOREF);
		}

		return ref;
	}

	static void UnrefFunction(lua_State* luaState, int ref)
	{
		assert(ref != LUA_NOREF);
		luaL_unref(luaState, LUA_REGISTRYINDEX, ref);
	}


	static int RefUserData(lua_State* luaState, int index)
	{
		lua_pushvalue(luaState, index);
		int ref = luaL_ref(luaState, LUA_REGISTRYINDEX);
		assert(ref != LUA_NOREF);

		return ref;
	}

	static void UnrefUserData(lua_State* luaState, int ref)
	{
		assert(ref != LUA_NOREF);
		luaL_unref(luaState, LUA_REGISTRYINDEX, ref);
	}

	// 下面是一组从栈上获取返回值的函数，一般情况下都会有多个返回值，而很多时候用户
	// 不会所有值都返回，这种情况下就需要使用默认值了，所在在发现指定的栈位置的值为nil
	// 情况下，采用指定的默认值
	static bool GetBoolValue(lua_State* luaState, int index, bool defaultValue = false, bool check = false)
	{
		assert(luaState);
		if (check)
		{
			luaL_argcheck(luaState, lua_isboolean(luaState, index), index, "boolean expect");
		}

		if (lua_isnoneornil(luaState, index))
		{
			return defaultValue;
		}
		else
		{
			return lua_toboolean(luaState, index)? true : false;
		}
	}

	static int GetIntValue(lua_State* luaState, int index, int defaultValue = 0, bool check = false)
	{
		assert(luaState);
		if (!check && lua_isnoneornil(luaState, index))
		{
			return defaultValue;
		}
		else
		{
			return check ? static_cast<int>(luaL_checkint(luaState, index)) : static_cast<int>(lua_tointeger(luaState, index));
		}
	}

	static unsigned long GetUnsignedLong(lua_State* luaState, int index, unsigned long defaultValue = 0, bool check = false)
	{
		assert(luaState);
		if (!check && lua_isnoneornil(luaState, index))
		{
			return defaultValue;
		}
		else
		{
			return check ? static_cast<unsigned long>(luaL_checknumber(luaState, index)) : static_cast<unsigned long>(lua_tonumber(luaState, index));
		}
	}

	static const char* GetStringValue(lua_State* luaState, int index, const char* defaultValue = NULL, bool check = false)
	{
		assert(luaState);
		if (!check && lua_isnoneornil(luaState, index))
		{
			return defaultValue;
		}
		else
		{
			return check ? luaL_checkstring(luaState, index) : lua_tostring(luaState, index);
		}
	}

	static double GetNumberValue(lua_State* luaState, int index, double defaultValue = 0.0, bool check = false)
	{
		assert(luaState);
		if (!check && lua_isnoneornil(luaState, index))
		{
			return defaultValue;
		}
		else
		{
			return check ? luaL_checknumber(luaState, index) : lua_tonumber(luaState, index);
		}
	}

	static bool GetUnicodeValue(lua_State* luaState, int index, std::wstring& strOut, bool check = false)
	{
		assert(luaState);

		const char* lpValue = GetStringValue(luaState, index, NULL, check);
		if (lpValue)
		{
			XLUETranscode::UTF8_to_Unicode(lpValue, ::strlen(lpValue), strOut);
			return true;
		}
		
		return false;
	}

	static bool PushUnicodeValue(lua_State* luaState, const wchar_t* lpValue)
	{
		assert(luaState);
		assert(lpValue);

		if (lpValue)
		{
			std::string strValue;
			XLUETranscode::Unicode_to_UTF8(lpValue, ::wcslen(lpValue), strValue);
			lua_pushstring(luaState, strValue.c_str());
			return true;
		}

		return false;
	}
};

} //XAF
} //Xunlei


#endif // __LUAHELPER_H__