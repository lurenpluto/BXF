/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./LuaBoltBrowserObject.h"

LuaBoltBrowserObject::LuaBoltBrowserObject(void)
{
}

LuaBoltBrowserObject::~LuaBoltBrowserObject(void)
{
}

const XLLRTGlobalAPI LuaBoltBrowserObject::s_szLuaMemberFuncs[] = 
{
	{NULL, NULL}
};

const XLLRTGlobalAPI* LuaBoltBrowserObject::GetChildLuaAPIs()
{
	return s_szLuaMemberFuncs;
}