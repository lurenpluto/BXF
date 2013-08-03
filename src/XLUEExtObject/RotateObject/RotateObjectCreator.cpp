/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./RotateObjectCreator.h"

RotateObjectCreator::RotateObjectCreator(void)
{
}

RotateObjectCreator::~RotateObjectCreator(void)
{
}

RotateObject* RotateObjectCreator::CreateObj( const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj )
{
	assert(lpObjClass);
	assert(hObj);

	return new RotateObject(hObj);
}

void RotateObjectCreator::DestroyObj( RotateObject* lpObj )
{
	assert(lpObj);
	delete lpObj;
}