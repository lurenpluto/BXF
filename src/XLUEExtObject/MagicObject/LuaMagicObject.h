/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2013              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   LuaMagicObject
*   Author      :   李亚星
*   Create      :   2013-5-22 11:58
*   LastChange  :   2013-5-22 11:58
*   History     :	
*
*   Description :   MagicObject对应的lua封装
*
********************************************************************/ 
#ifndef __LUAMAGICOBJECT_H__
#define __LUAMAGICOBJECT_H__

#include "./MagicObject.h"

class LuaMagicObject
	: public ExtObjLuaHostImpl<LuaMagicObject, MagicObject>
{
public:
	LuaMagicObject(void);
	virtual ~LuaMagicObject(void);

protected:

	static int GetType(lua_State* luaState);
	static int SetType(lua_State* luaState);

public:

	static XLLRTGlobalAPI s_szLuaMemberFuncs[];
};

#endif // __LUAMAGICOBJECT_H__