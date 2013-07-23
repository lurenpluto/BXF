/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2013              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   BoltBrowserObjectEvents
*   Author      :   李亚星
*   Create      :   2013-6-9 
*   LastChange  :   2013-6-26
*   History     :	
*
*   Description :   BoltBrowserObject和WindowlessBoltBrowserObject的事件托管实现
*
********************************************************************/ 
#ifndef __BOLTBROWSEROBJECTEVENTS_H__
#define __BOLTBROWSEROBJECTEVENTS_H__

#include "./BaseBoltBrowserObjectEvents.h"

class BoltBrowserObject;

class BoltBrowserObjectEvents
	: public ExtObjEventImplEx<BoltBrowserObjectEvents, BoltBrowserObject>,
	public BaseBoltBrowserObjectEvents
{
private:
	virtual ~BoltBrowserObjectEvents(void);

public:
	BoltBrowserObjectEvents(XLUE_LAYOUTOBJ_HANDLE);
	
public:

	DECLEAR_EXT_EVENT_VECTOR();
	
	// ExtObjEventImplEx methods
	static BoltBrowserObjectEvents* ExtEventObjFromObject(BoltBrowserObject* lpObj);
};

class WindowlessBoltBrowserObject;

class WindowlessBoltBrowserObjectEvents
	: public ExtObjEventImplEx<WindowlessBoltBrowserObjectEvents, WindowlessBoltBrowserObject>,
	public BaseBoltBrowserObjectEvents
{
private:
	virtual ~WindowlessBoltBrowserObjectEvents(void);

public:
	WindowlessBoltBrowserObjectEvents(XLUE_LAYOUTOBJ_HANDLE);
	
public:

	DECLEAR_EXT_EVENT_VECTOR();

	// ExtObjEventImplEx methods
	static WindowlessBoltBrowserObjectEvents* ExtEventObjFromObject(WindowlessBoltBrowserObject* lpObj);
};

#endif // __BOLTBROWSEROBJECTEVENTS_H__