/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2013              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   LuaFrame
*   Author      :   李亚星
*   Create      :   2013-6-27 
*   LastChange  :   2013-6-27
*   History     :	
*
*   Description :   CefFrame的lua封装
*
********************************************************************/ 
#ifndef __LUAFRAME_H__
#define __LUAFRAME_H__

struct LuaFrameData
{
	int m_browserID;
	int64 m_frameID;
};

class LuaFrame
{
public:
	
	static void Register(XL_LRT_ENV_HANDLE hEnv);

	static void PushFrame(lua_State* luaState, CefFrame* lpFrame);
	static CefFrame* CheckFrame(lua_State* luaState, int index);

private:

	static int GC(lua_State* luaState);

	static int Undo(lua_State* luaState);
	static int Redo(lua_State* luaState);
	static int Cut(lua_State* luaState);
	static int Copy(lua_State* luaState);
	static int Paste(lua_State* luaState);
	static int Delete(lua_State* luaState);
	static int SelectAll(lua_State* luaState);

	static int IsMain(lua_State* luaState);
	static int IsFocused(lua_State* luaState);
	static int GetName(lua_State* luaState);

	static int GetParent(lua_State* luaState);
	static int GetURL(lua_State* luaState);
	static int GetBrowser(lua_State* luaState);

private:

	static XLLRTGlobalAPI s_LuaFrameMemberFunctions[];
};

#endif // __LUAFRAME_H__