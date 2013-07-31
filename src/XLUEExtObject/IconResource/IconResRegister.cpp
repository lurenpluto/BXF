/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./IconResRegister.h"
#include "./IconResCreator.h"
#include "./IconResParser.h"
#include "./LuaIconRes.h"

bool IconResRegister::RegisterIconRes()
{
	return ExtResourceRegisterHelper<IconRes, IconResCreator, IconResParser, LuaIconRes>::Register(XLUE_EXTRES_ICON, 0);
}
