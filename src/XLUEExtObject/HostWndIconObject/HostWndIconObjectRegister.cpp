/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./HostWndIconObjectRegister.h"
#include "./HostWndIconObjectCreator.h"
#include "./HostWndIconObjectParser.h"
#include "./LuaHostWndIconObject.h"

bool HostWndIconObjectRegister::RegisterHostWndIconObject()
{
	return ExtObjRegisterHelper<ExtObjType_layoutObj, HostWndIconObject, HostWndIconObjectCreator,
		HostWndIconObjectParser, LuaHostWndIconObject>::Register(EXTCLASSNAME_HOSTWNDICONOBJECT, 0);
}