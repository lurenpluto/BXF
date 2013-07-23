/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2011              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   LuaEvent
*   Author      :   李亚星
*   Create      :   2011-10-10 16:26
*   LastChange  :   2011-10-10 16:26
*   History     :	
*
*   Description :   基础的lua回调封装
*
********************************************************************/ 
#ifndef __LUAEVENT_H__
#define __LUAEVENT_H__

namespace Xunlei
{
namespace XAF
{

class BaseLuaListener
{
public:
    BaseLuaListener(lua_State* luaState,long luaFunRef)
		:m_luaState(luaState),
		m_luaFunRef(luaFunRef)
	{
		assert(m_luaState);
		assert(m_luaFunRef != LUA_NOREF);
	}

    BaseLuaListener(const BaseLuaListener& other)
	{
		Copy(other);
	}

    BaseLuaListener& operator=(const BaseLuaListener& other)
	{
		Copy(other);

		return *this;
	}

    virtual ~BaseLuaListener()
	{
		Clear();
	}

public:

	lua_State* GetLuaState() const
	{
		assert(m_luaState);
		return m_luaState;
	}

	// 把当前保存的lua函数放到lua栈顶
	void PushLuaFunction() const
	{
		assert(m_luaState);
		assert(m_luaFunRef != LUA_NOREF);

		lua_rawgeti(m_luaState, LUA_REGISTRYINDEX, m_luaFunRef);
		assert(lua_isfunction(m_luaState, -1));
	}

	void Clear()
	{
		assert(m_luaState);
		if (m_luaState != NULL)
		{
			assert(m_luaFunRef != LUA_NOREF);
			luaL_unref(m_luaState, LUA_REGISTRYINDEX, m_luaFunRef);
			m_luaFunRef = LUA_NOREF;

			m_luaState = NULL;
		}
	}

    virtual long Call(int nArgs, int nReturns, const wchar_t* lpContextInfo)
	{
		assert(m_luaState);
		assert(m_luaFunRef != LUA_NOREF);

		long ret = XLLRT_LuaCall(m_luaState, nArgs, nReturns, lpContextInfo);
		//assert(ret == XLLRT_RESULT_SUCCESS);

		return ret;
	}

protected:

	void Copy(const BaseLuaListener& other)
	{
		assert(other.m_luaState);
		assert(other.m_luaFunRef != LUA_NOREF);

		Clear();

		m_luaState = other.m_luaState;
		if (m_luaState != NULL)
		{
			lua_rawgeti(m_luaState, LUA_REGISTRYINDEX, other.m_luaFunRef);
			m_luaFunRef = luaL_ref(m_luaState, LUA_REGISTRYINDEX);
			assert(m_luaFunRef != LUA_NOREF);
		}
	}

protected:

    lua_State*	m_luaState;
    long		m_luaFunRef;
};

// 该类用来保存luastate和lua回调的栈顶
class LuaStackKeeper
{
public:

	LuaStackKeeper(const BaseLuaListener& luaListener)
		:m_savedLuaState(luaListener.GetLuaState())
	{
		assert(m_savedLuaState);
		m_savedStackTop = lua_gettop(m_savedLuaState);
	}

	LuaStackKeeper(lua_State* luaState)
		:m_savedLuaState(luaState)
	{
		assert(m_savedLuaState);
		m_savedStackTop = lua_gettop(m_savedLuaState);
	}

	~LuaStackKeeper()
	{
		assert(m_savedLuaState);
		lua_settop(m_savedLuaState, m_savedStackTop);
		m_savedStackTop = 0;
		m_savedLuaState = NULL;
	}
	
	operator lua_State*() const
	{
		assert(m_savedLuaState);
		return m_savedLuaState;
	}

private:

	int			m_savedStackTop;
	lua_State*	m_savedLuaState;
};

} // XAF
} // Xunlei

#endif //__LUAEVENT_H__