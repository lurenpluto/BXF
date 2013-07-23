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
*   FileName    :   LuaBaseBoltBrowserObject
*   Author      :   李亚星
*   Create      :   2013-7-4 
*   LastChange  :   2013-7-4
*   History     :	
*
*   Description :   BoltBrowserObject和WindowlessBoltBrowserObject的lua封装基类
*
********************************************************************/ 
#ifndef __LUABASEBOLTBROWSEROBJECT_H__
#define __LUABASEBOLTBROWSEROBJECT_H__

#include "../BrowserObject/BaseBoltBrowserObject.h"

class LuaBaseBoltBrowserObject
	: public ExtObjLuaHostImpl<LuaBaseBoltBrowserObject, BaseBoltBrowserObject>
{
public:
	LuaBaseBoltBrowserObject(void);
	virtual ~LuaBaseBoltBrowserObject(void);

private:

	// ExtObjLuaHostImpl
	virtual bool GetLuaFunction(const char* className, const XLLRTGlobalAPI** lplpLuaFunctions, size_t* lpFuncCount);
	virtual bool RegisterAuxClass(const char* /*className*/, XL_LRT_ENV_HANDLE /*hEnv*/);

protected:

	// 由子类负责实现，来获取
	virtual const XLLRTGlobalAPI* GetChildLuaAPIs() = 0;

private:

	// lua functions
	static int Navigate(lua_State* luaState);

	static int CanGoBack(lua_State* luaState);
	static int GoBack(lua_State* luaState);

	static int CanGoForward(lua_State* luaState);
	static int GoForward(lua_State* luaState);

	static int IsLoading(lua_State* luaState);
	static int Reload(lua_State* luaState);
	static int ReloadIgnoreCache(lua_State* luaState);
	static int StopLoad(lua_State* luaState);

	static int HasDocument(lua_State* luaState);

	static int GetMainFrame(lua_State* luaState);
	static int GetFocusedFrame(lua_State* luaState);
	static int GetFrame(lua_State* luaState); 

protected:

	static const XLLRTGlobalAPI s_szLuaMemberFuncs[];
};

#endif // __LUABASEBOLTBROWSEROBJECT_H__