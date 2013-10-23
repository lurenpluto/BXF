/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "StdAfx.h"
#include "NotifyIconObjectCreator.h"

NotifyIconObjectCreator::NotifyIconObjectCreator(void)
{
}

NotifyIconObjectCreator::~NotifyIconObjectCreator(void)
{
}

NotifyIconObject* NotifyIconObjectCreator::CreateObj( const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj )
{
	assert(lpObjClass);
	assert(hObj);

	return new NotifyIconObject(hObj);
}

void NotifyIconObjectCreator::DestroyObj( NotifyIconObject* lpObj )
{
	assert(lpObj);
	
	lpObj->SafeDelete();
}