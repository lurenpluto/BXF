/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./SvgObjectCreator.h"

SvgObjectCreator::SvgObjectCreator(void)
{
}

SvgObjectCreator::~SvgObjectCreator(void)
{
}

SvgObject* SvgObjectCreator::CreateObj( const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj )
{
	assert(hObj);
	assert(lpObjClass);

	return new SvgObject(hObj);
}

void SvgObjectCreator::DestroyObj( SvgObject* lpObj )
{
	assert(lpObj);

	delete lpObj;
}