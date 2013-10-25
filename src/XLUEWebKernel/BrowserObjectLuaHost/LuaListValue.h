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
*   FileName    :   LuaListValue
*   Author      :   ·¶·ÉÁú
*   Create      :   2013-10-25
*   LastChange  :   2013-10-25
*   History     :	
*
*   Description :   CefListValueµÄlua·â×°
*
********************************************************************/ 
#ifndef __LUALISTVALUE_H__
#define __LUALISTVALUE_H__

class LuaListValue
{
public:
	static void PushListValue(lua_State* luaState, CefListValue* lpListValue);
	static CefListValue* CheckListValue(lua_State* luaState, int index);
};

#endif //__LUALISTVALUE_H__