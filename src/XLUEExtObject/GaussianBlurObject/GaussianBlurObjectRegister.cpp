/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./GaussianBlurObjectRegister.h"
#include "BXF/ExtObjRegisterHelper.h"
#include "./GaussianBlurObject.h"
#include "./GaussianBlurObjectCreator.h"
#include "./GaussianBlurObjectParser.h"
#include "./LuaGaussianBlurObject.h"

BOOL GaussianBlurObjectRegister::RegisterGaussianBlurObject()
{
	unsigned long attribute = ExtObjAttribute_clipsens;

	return ExtObjRegisterHelper<ExtObjType_renderableObj, GaussianBlurObject, GaussianBlurObjectCreator, 
		GaussianBlurObjectParser, LuaGaussianBlurObject>::Register(EXTCLASSNAME_GAUSSIANBLUROBJECT, attribute);
}