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
*   FileName    :   LuaRotateObject
*   Author      :   李亚星
*   Create      :   2013-8-1 
*   LastChange  :   2013-8-1
*   History     :	
*
*   Description :   RotateObject的lua封装
*
********************************************************************/ 
#ifndef __LUAROTATEOBJECT_H__
#define __LUAROTATEOBJECT_H__

#include "./RotateObject.h"

class LuaRotateObject
	: public ExtObjLuaHostImplEx<LuaRotateObject, RotateObject>
{
public:
	LuaRotateObject(void);
	virtual ~LuaRotateObject(void);

	static RotateMode GetRotateModeFromString(const char* value);
	static const char* GetStringFromRotateMode(RotateMode mode);

private:

	static int SetAngel(lua_State* luaState);
	static int GetAngel(lua_State* luaState);

	static int SetCenter(lua_State* luaState);
	static int GetCenter(lua_State* luaState);

	static int SetRotateMode(lua_State* luaState);
	static int GetRotateMode(lua_State* luaState);

public:

	static const XLLRTGlobalAPI s_szLuaMemberFuncs[];
};

#endif // __LUAROTATEOBJECT_H__