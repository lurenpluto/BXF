/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./MirrorObjectCreator.h"

MirrorObjectCreator::MirrorObjectCreator(void)
{
}

MirrorObjectCreator::~MirrorObjectCreator(void)
{
}

MirrorObject* MirrorObjectCreator::CreateObj( const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj )
{
	assert(hObj);
	assert(lpObjClass);

	return new MirrorObject(hObj);
}

void MirrorObjectCreator::DestroyObj( MirrorObject* lpObj )
{
	assert(lpObj);

	delete lpObj;
}