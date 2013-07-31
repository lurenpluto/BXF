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
*   FileName    :   LuaMirrorObject
*   Author      :   李亚星
*   Create      :   2013-5-26 3:27
*   LastChange  :   2013-5-26 3:27
*   History     :	
*
*   Description :   MirrorObject的lua封装
*
********************************************************************/ 
#ifndef __LUAMIRROROBJECT_H__
#define __LUAMIRROROBJECT_H__

#include "./MirrorObject.h"

class LuaMirrorObject
	: public ExtObjLuaHostImplEx<LuaMirrorObject, MirrorObject>
{
public:
	LuaMirrorObject(void);
	virtual ~LuaMirrorObject(void);

public:

	static MirrorObject::MirrorType GetMirrorTypeFromString(const char* lpType);
	static const char* GetMirrorTypeString(MirrorObject::MirrorType type);

private:

	static int SetMirrorType(lua_State* luaState);
	static int GetMirrorType(lua_State* luaState);

public:

	static const XLLRTGlobalAPI s_szLuaMemberFuncs[];
};

#endif // __LUAMIRROROBJECT_H__