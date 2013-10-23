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
*   FileName    :   LuaHostWndIconObject
*   Author      :   李亚星
*   Create      :   2013-7-29 
*   LastChange  :   2013-7-29
*   History     :	
*
*   Description :   HostWndIconObject的lua封装
*
********************************************************************/ 
#ifndef __LUAHOSTWNDICONOBJECT_H__
#define __LUAHOSTWNDICONOBJECT_H__

#include "./HostWndIconObject.h"

class LuaHostWndIconObject
	: public ExtObjLuaHostImplEx<LuaHostWndIconObject, HostWndIconObject>
{
public:
	LuaHostWndIconObject(void);
	virtual ~LuaHostWndIconObject(void);

private:

	static int SetIconResID(lua_State* luaState);
	static int GetIconResID(lua_State* luaState);

	static int SetIcon(lua_State* luaState);
	static int GetIcon(lua_State* luaState);

public:

	static const XLLRTGlobalAPI s_szLuaMemberFuncs[];
};

#endif // __LUAHOSTWNDICONOBJECT_H__