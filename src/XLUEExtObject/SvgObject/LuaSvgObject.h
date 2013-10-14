/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#ifndef __LUASVGOBJECT_H__
#define __LUASVGOBJECT_H__

#include "./SvgObject.h"

class LuaSvgObject
	: public ExtObjLuaHostImplEx<LuaSvgObject, SvgObject>
{
public:
	LuaSvgObject(void);
	virtual ~LuaSvgObject(void);

private:

	static int SetSvgResID(lua_State* luaState);
	static int GetSvgResID(lua_State* luaState);

    static int SetSvgRes(lua_State* luaState);
    static int GetSvgRes(lua_State* luaState);

public:

	static const XLLRTGlobalAPI s_szLuaMemberFuncs[];
};

#endif // __LUASVGOBJECT_H__