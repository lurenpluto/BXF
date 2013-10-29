/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./GaussianBlurObjectCreator.h"

GaussianBlurObjectCreator::GaussianBlurObjectCreator(void)
{
}

GaussianBlurObjectCreator::~GaussianBlurObjectCreator(void)
{
}

GaussianBlurObject* GaussianBlurObjectCreator::CreateObj( const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj )
{
	assert(hObj);
	assert(lpObjClass);

	return new GaussianBlurObject(hObj);
}

void GaussianBlurObjectCreator::DestroyObj( GaussianBlurObject* lpObj )
{
	assert(lpObj);

	delete lpObj;
}