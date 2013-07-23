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

	static void PushString(lua_State* luaState, const CefString& value)
	{
		std::string utf8Value;
		XLUETranscode::Unicode_to_UTF8(value.c_str(), value.size(), utf8Value);

		lua_pushstring(luaState, utf8Value.c_str());
	}
};

#endif // __WEBKERNELLUAHELPER_H__