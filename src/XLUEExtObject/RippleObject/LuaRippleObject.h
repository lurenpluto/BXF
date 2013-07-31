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
*   FileName    :   LuaRippleObject
*   Author      :   李亚星
*   Create      :   2013-5-31 
*   LastChange  :   2013-5-31
*   History     :	
*
*   Description :   RippleObject的lua封装
*
********************************************************************/ 
#ifndef __LUARIPPLEOBJECT_H__
#define __LUARIPPLEOBJECT_H__

#include "./RippleObject.h"

class LuaRippleObject
	:public ExtObjLuaHostImplEx<LuaRippleObject, RippleObject>
{
public:
	LuaRippleObject(void);
	virtual ~LuaRippleObject(void);

private:

	static int SetMouseDrop(lua_State* luaState);
	static int GetMouseDrop(lua_State* luaState);

	static int SetRandomDrop(lua_State* luaState);
	static int GetRandomDrop(lua_State* luaState);

	static int SetDropDensity(lua_State* luaState);
	static int GetDropDensity(lua_State* luaState);

	static int SetUpdateInterval(lua_State* luaState);
	static int GetUpdateInterval(lua_State* luaState);

	static int SetWaterDensity(lua_State* luaState);
	static int GetWaterDensity(lua_State* luaState);

	static int ClearAllDrops(lua_State* luaState);

public:

	static const XLLRTGlobalAPI s_szLuaMemberFuncs[];
};

#endif // __LUARIPPLEOBJECT_H__