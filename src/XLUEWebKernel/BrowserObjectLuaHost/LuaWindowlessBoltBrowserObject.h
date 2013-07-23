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
*   FileName    :   LuaWindowlessBoltBrowserObject
*   Author      :   李亚星
*   Create      :   2013-7-1 
*   LastChange  :   2013-7-1
*   History     :	
*
*   Description :   WindowlessBoltBrowserObject的lua封装
*
********************************************************************/ 
#ifndef __LUAWINDOWLESSBOLTBROWSEROBJECT_H__
#define __LUAWINDOWLESSBOLTBROWSEROBJECT_H__

#include "../BrowserObject/WindowlessBoltBrowserObject.h"
#include "./LuaBaseBoltBrowserObject.h"

class LuaWindowlessBoltBrowserObject
	: public LuaBaseBoltBrowserObject
{
public:
	LuaWindowlessBoltBrowserObject(void);
	virtual ~LuaWindowlessBoltBrowserObject(void);

	static WindowlessBoltBrowserObject* CheckBoltBrowserObject(lua_State* luaState, int index);
	static bool PushBoltBrowserObject(lua_State* luaState, WindowlessBoltBrowserObject* lpObj);

private:

	// LuaBaseBoltBrowserObject
	virtual const XLLRTGlobalAPI* GetChildLuaAPIs();

private:

	static int SetTransparnet(lua_State* luaState);
	static int GetTransparnet(lua_State* luaState);

private:

	static const XLLRTGlobalAPI s_szLuaMemberFuncs[];
};

#endif // __LUAWINDOWLESSBOLTBROWSEROBJECT_H__