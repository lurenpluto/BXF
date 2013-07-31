/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./HostWndIconObjectCreator.h"

HostWndIconObjectCreator::HostWndIconObjectCreator(void)
{
}

HostWndIconObjectCreator::~HostWndIconObjectCreator(void)
{
}

HostWndIconObject* HostWndIconObjectCreator::CreateObj( const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj )
{
	assert(lpObjClass);
	assert(hObj);

	return new HostWndIconObject(hObj);
}

void HostWndIconObjectCreator::DestroyObj( HostWndIconObject* lpObj )
{
	assert(lpObj);
	delete lpObj;
}