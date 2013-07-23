/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./BoltBrowserObjectEvents.h"
#include "./BoltBrowserObject.h"
#include "./WindowlessBoltBrowserObject.h"

BEGIN_EXT_EVENT_VECTOR_EX(BoltBrowserObjectEvents, BaseBoltBrowserObjectEvents)
END_EXT_EVENT_VECTOR()

BEGIN_EXT_EVENT_VECTOR_EX(WindowlessBoltBrowserObjectEvents, BaseBoltBrowserObjectEvents)
END_EXT_EVENT_VECTOR()

BoltBrowserObjectEvents::BoltBrowserObjectEvents(XLUE_LAYOUTOBJ_HANDLE hOwner)
:BaseBoltBrowserObjectEvents(hOwner)
{}

BoltBrowserObjectEvents::~BoltBrowserObjectEvents(void)
{}

BoltBrowserObjectEvents* BoltBrowserObjectEvents::ExtEventObjFromObject( BoltBrowserObject* lpObj )
{
	assert(lpObj);

	return lpObj->GetEvents();
}

WindowlessBoltBrowserObjectEvents::WindowlessBoltBrowserObjectEvents( XLUE_LAYOUTOBJ_HANDLE hOwner)
:BaseBoltBrowserObjectEvents(hOwner)
{}

WindowlessBoltBrowserObjectEvents::~WindowlessBoltBrowserObjectEvents( void )
{}

WindowlessBoltBrowserObjectEvents* WindowlessBoltBrowserObjectEvents::ExtEventObjFromObject( WindowlessBoltBrowserObject* lpObj )
{
	assert(lpObj);

	return lpObj->GetEvents();
}