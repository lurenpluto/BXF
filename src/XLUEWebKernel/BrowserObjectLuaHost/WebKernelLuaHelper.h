/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2013              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   WebKernelLuaHelper
*   Author      :   李亚星
*   Create      :   2013-6-28 
*   LastChange  :   2013-6-28
*   History     :	
*
*   Description :   浏览器对象lua封装的辅助函数
*
********************************************************************/ 
#ifndef __WEBKERNELLUAHELPER_H__
#define __WEBKERNELLUAHELPER_H__

class WebKernelLuaHelper
{
public:
	static void PushCefString(lua_State* luaState, const CefString& value);
	static CefString ToCefString(lua_State* luaState,int index);

	static void PushCefListValue(lua_State* luaState, CefRefPtr<CefListValue> lpListValue);
	static CefRefPtr<CefListValue> ToCefListValue(lua_State* luaState, int index);

	static void PushCefDictionaryValue(lua_State* luaState,CefRefPtr<CefDictionaryValue> lpDictionaryValue);
	static CefRefPtr<CefDictionaryValue> ToCefDictionaryValue(lua_State* luaState,int index);
};

#endif // __WEBKERNELLUAHELPER_H__