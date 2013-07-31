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
*   FileName    :   IconResParser
*   Author      :   李亚星
*   Create      :   2013-7-29 
*   LastChange  :   2013-7-29
*   History     :	
*
*   Description :   ICON扩展资源类型的解析类
*
********************************************************************/ 
#ifndef __ICONRESPARSER_H__
#define __ICONRESPARSER_H__

#include "./IconRes.h"

class IconResParser
	: public ExtResourceParserImplEx<IconRes>
{
public:
	IconResParser(void);
	virtual ~IconResParser(void);

private:

	// ExtResourceParserImpl
	virtual bool ParseAttributeFromXML(IconRes* lpResObj, const char* lpName, const char* lpValue);
	virtual bool ParseAttributeFromLua(IconRes* lpResObj, const char* lpName, lua_State* luaState, int index);

};

#endif // __ICONRESPARSER_H__