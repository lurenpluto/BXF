/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./MirrorObjectRegister.h"
#include "./MirrorObject.h"
#include "./MirrorObjectCreator.h"
#include "./MirrorObjectParser.h"
#include "./LuaMirrorObject.h"

BOOL MirrorObjectRegister::RegisterMirrorObject()
{
	unsigned long attribute = ExtObjAttribute_clipsens;

	return ExtObjRegisterHelper<ExtObjType_renderableObj, MirrorObject, MirrorObjectCreator, 
		MirrorObjectParser, LuaMirrorObject>::Register(EXTCLASSNAME_MIRROROBJECT, attribute);
}