/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./BoltBrowserObjectCreator.h"

BoltBrowserObjectCreator::BoltBrowserObjectCreator(void)
{
}

BoltBrowserObjectCreator::~BoltBrowserObjectCreator(void)
{
}

BoltBrowserObject* BoltBrowserObjectCreator::CreateObj( const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj )
{
	return new BoltBrowserObject(hObj);
}

void BoltBrowserObjectCreator::DestroyObj( BoltBrowserObject* lpObj )
{
	assert(lpObj);

	delete lpObj;
}

WindowlessBoltBrowserObjectCreator::WindowlessBoltBrowserObjectCreator( void )
{

}

WindowlessBoltBrowserObjectCreator::~WindowlessBoltBrowserObjectCreator( void )
{

}

WindowlessBoltBrowserObject* WindowlessBoltBrowserObjectCreator::CreateObj( const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj )
{
	assert(hObj);

	return new WindowlessBoltBrowserObject(hObj);
}

void WindowlessBoltBrowserObjectCreator::DestroyObj( WindowlessBoltBrowserObject* lpObj )
{
	assert(lpObj);

	delete lpObj;
}