/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./RotateObjectRegister.h"
#include "./LuaRotateObject.h"
#include "./RotateObjectParser.h"
#include "./RotateObjectCreator.h"

bool RotateObjectRegister::RegisterRotateObject()
{
	unsigned long attribute = ExtObjAttribute_clipsens;

	return ExtObjRegisterHelper<ExtObjType_renderableObj, RotateObject, RotateObjectCreator, 
		RotateObjectParser, LuaRotateObject>::Register(EXTCLASSNAME_ROTATEOBJECT, attribute);
}