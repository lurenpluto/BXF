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
*   FileName    :   LuaNotifyIconObject
*   Author      :   李亚星
*   Create      :   2013-10-14 
*   LastChange  :   2013-10-14
*   History     :	
*
*   Description :   NotifyIconObject的lua封装
*
********************************************************************/ 
#ifndef __LUANOTIFYICONOBJECT_H__
#define __LUANOTIFYICONOBJECT_H__

#include "./NotifyIconObject.h"

class LuaNotifyIconObject
	: public ExtObjLuaHostImplEx<LuaNotifyIconObject, NotifyIconObject>
{
public:
	LuaNotifyIconObject(void);
	virtual ~LuaNotifyIconObject(void);

private:

	static int SetIconResID(lua_State* luaState);
	static int GetIconResID(lua_State* luaState);

	static int SetIcon(lua_State* luaState);
	static int GetIcon(lua_State* luaState);

	static int SetTip(lua_State* luaState);
	static int GetTip(lua_State* luaState);

	static int SetIconVisible(lua_State* luaState);
	static int GetIconVisible(lua_State* luaState);

	static int ShowBalloonTip(lua_State* luaState);

private:

	static unsigned int GetIconType(const char* lpIconType);

public:

	static const XLLRTGlobalAPI s_szLuaMemberFuncs[];
};

#endif // __LUANOTIFYICONOBJECT_H__