/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./SvgObjectCreator.h"

SVGObjectCreator::SVGObjectCreator(void)
{
}

SVGObjectCreator::~SVGObjectCreator(void)
{
}

SVGObject* SVGObjectCreator::CreateObj( const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj )
{
	assert(hObj);
	assert(lpObjClass);

	return new SVGObject(hObj);
}

void SVGObjectCreator::DestroyObj( SVGObject* lpObj )
{
	assert(lpObj);

	delete lpObj;
}