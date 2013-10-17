/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./NotifyIconObjectRegister.h"
#include "./LuaNotifyIconObject.h"
#include "./NotifyIconObjectCreator.h"
#include "./NotifyIconObjectParser.h"
#include "./NotifyIconObjectEvents.h"

bool NotifyIconObjectRegister::RegisterNotifyIconObject()
{
	return ExtObjRegisterHelper<ExtObjType_layoutObj, NotifyIconObject, NotifyIconObjectCreator
		,NotifyIconObjectParser, LuaNotifyIconObject, NotifyIconObjectEvents>::Register(EXTCLASSNAME_NOTIFYICONOBJECT, 0);
}