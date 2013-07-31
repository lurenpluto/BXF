/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./MagicObjectCreator.h"

MagicObjectCreator::MagicObjectCreator(void)
{
}

MagicObjectCreator::~MagicObjectCreator(void)
{
}

MagicObject* MagicObjectCreator::CreateObj( const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj )
{
	assert(lpObjClass);
	assert(hObj);

	MagicObject* lpExtObj = new MagicObject(hObj);

	return lpExtObj;
}

void MagicObjectCreator::DestroyObj( MagicObject* lpObj )
{
	assert(lpObj);

	delete lpObj;
}