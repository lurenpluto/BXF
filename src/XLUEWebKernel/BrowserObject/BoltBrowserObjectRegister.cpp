/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./BoltBrowserObjectRegister.h"
#include "./BoltBrowserObject.h"
#include "./WindowlessBoltBrowserObject.h"
#include "./BoltBrowserObjectCreator.h"
#include "./BoltBrowserObjectParser.h"
#include "./BoltBrowserObjectEvents.h"
#include "../BrowserObjectLuaHost/LuaWindowlessBoltBrowserObject.h"
#include "../BrowserObjectLuaHost/LuaBoltBrowserObject.h"

BOOL BoltBrowserObjectRegister::RegisterBoltBrowserObject()
{
	unsigned long attribute = 0;

	return ExtObjRegisterHelper<ExtObjType_realObj, BoltBrowserObject, BoltBrowserObjectCreator, 
		BoltBrowserObjectParser, LuaBoltBrowserObject, BoltBrowserObjectEvents>::Register(EXTCLASSNAME_BOLTBROWSEROBJECT, attribute);
}

BOOL WindowlessBoltBrowserObjectRegister::RegisterWindowlessBoltBrowserObject()
{
	unsigned long attribute = 0;

	return ExtObjRegisterHelper<ExtObjType_renderableObj, WindowlessBoltBrowserObject, WindowlessBoltBrowserObjectCreator, 
		WindowlessBoltBrowserObjectParser, LuaWindowlessBoltBrowserObject, WindowlessBoltBrowserObjectEvents>::Register(EXTCLASSNAME_WINDOWLESSBOLTBROWSEROBJECT, attribute);
}