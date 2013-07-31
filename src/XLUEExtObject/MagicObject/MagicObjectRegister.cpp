/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./MagicObjectRegister.h"
#include "./MagicObject.h"
#include "./MagicObjectCreator.h"
#include "./MagicObjectParser.h"
#include "./LuaMagicObject.h"

BOOL MagicObjectRegister::RegisterMagicObject()
{
	unsigned long attribute = ExtObjAttribute_clipsens;

	return ExtObjRegisterHelper<ExtObjType_renderableObj, MagicObject, 
		MagicObjectCreator, MagicObjectParser, LuaMagicObject>::Register(EXTCLASSNAME_MAGICOBJECT, attribute);
}