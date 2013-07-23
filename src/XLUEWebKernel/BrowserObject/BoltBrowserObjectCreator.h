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
*   FileName    :   BoltBrowserObjectCreator
*   Author      :   李亚星
*   Create      :   2013-6-6 
*   LastChange  :   2013-6-26
*   History     :	
*
*   Description :   BoltBrowserObject和WindowlessBoltBrowserObject的创建器
*
********************************************************************/ 
#ifndef __BOLTBROWSEROBJECTCREATOR_H__
#define __BOLTBROWSEROBJECTCREATOR_H__

#include "./BoltBrowserObject.h"
#include "./WindowlessBoltBrowserObject.h"

class BoltBrowserObjectCreator
	: public ExtObjCreatorImpl<BoltBrowserObject>
{
public:
	BoltBrowserObjectCreator(void);
	virtual ~BoltBrowserObjectCreator(void);

private:

	// ExtObjCreatorImpl methods
	virtual BoltBrowserObject* CreateObj(const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual void DestroyObj(BoltBrowserObject* lpObj);
};

class WindowlessBoltBrowserObjectCreator
	: public ExtObjCreatorImpl<WindowlessBoltBrowserObject>
{
public:
	WindowlessBoltBrowserObjectCreator(void);
	virtual ~WindowlessBoltBrowserObjectCreator(void);

private:

	// ExtObjCreatorImpl methods
	virtual WindowlessBoltBrowserObject* CreateObj(const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual void DestroyObj(WindowlessBoltBrowserObject* lpObj);
};

#endif // __BOLTBROWSEROBJECTCREATOR_H__