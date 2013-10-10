/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#ifndef __LUASVGOBJECT_H__
#define __LUASVGOBJECT_H__

#include "./SvgObject.h"

class LuaSVGObject
	: public ExtObjLuaHostImplEx<LuaSVGObject, SVGObject>
{
public:
	LuaSVGObject(void);
	virtual ~LuaSVGObject(void);

private:

	static int SetSVGResID(lua_State* luaState);
	static int GetSVGResID(lua_State* luaState);

    static int SetSVGRes(lua_State* luaState);
    static int GetSVGRes(lua_State* luaState);

    static int SetPreserveAspectRatio(lua_State* luaState);
    static int GetPreserveAspectRatio(lua_State* luaState);

    static int SetEnableSVGAlpha(lua_State* luaState);
    static int GetEnableSVGAlpha(lua_State* luaState);

public:

	static const XLLRTGlobalAPI s_szLuaMemberFuncs[];
};

#endif // __LUASVGOBJECT_H__