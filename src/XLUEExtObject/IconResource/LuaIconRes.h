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
*   FileName    :   LuaIconRes
*   Author      :   李亚星
*   Create      :   2013-7-29 
*   LastChange  :   2013-7-29
*   History     :	
*
*   Description :   ICON扩展资源类型的lua封装
*
********************************************************************/ 
#ifndef __LUAICONRES_H__
#define __LUAICONRES_H__

#include "./IconRes.h"

class LuaIconRes
	: public ExtResourceLuaHostImplEx<LuaIconRes, IconRes>
{
public:
	LuaIconRes(void);
	virtual ~LuaIconRes(void);

	static int GetIconHandle(lua_State* luaState);

public:

	static XLLRTGlobalAPI s_szLuaMemberFuncs[];
};

#endif // __LUAICONRES_H__