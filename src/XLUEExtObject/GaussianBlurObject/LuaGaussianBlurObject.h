/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#ifndef __LUAGAUSSIANBLUROBJECT_H__
#define __LUAGAUSSIANBLUROBJECT_H__

#include "./GaussianBlurObject.h"

class LuaGaussianBlurObject
	: public ExtObjLuaHostImplEx<LuaGaussianBlurObject, GaussianBlurObject>
{
public:
	LuaGaussianBlurObject(void);
	virtual ~LuaGaussianBlurObject(void);

public:
	static float GetSigmaFromString(const char* lpSigma);

private:
	static int SetSigma(lua_State* luaState);
	static int GetSigma(lua_State* luaState);

	static int SetRadius(lua_State *luaState);
	static int GetRadius(lua_State *luaState);

	static int SetGaussianType(lua_State *luaState);
	static int GetGaussianType(lua_State *luaState);

public:
	static const XLLRTGlobalAPI s_szLuaMemberFuncs[];
};

#endif // __LUAGAUSSIANBLUROBJECT_H__