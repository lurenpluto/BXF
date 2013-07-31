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
*   FileName    :   HostWndIconObjectCreator
*   Author      :   李亚星
*   Create      :   2013-7-29 
*   LastChange  :   2013-7-29
*   History     :	
*
*   Description :   HostWndIconObject的创建器
*
********************************************************************/ 
#ifndef __HOSTWNDICONOBJECTCREATOR_H__
#define __HOSTWNDICONOBJECTCREATOR_H__

#include "./HostWndIconObject.h"

class HostWndIconObjectCreator
	: public ExtObjCreatorImpl<HostWndIconObject>
{
public:
	HostWndIconObjectCreator(void);
	virtual ~HostWndIconObjectCreator(void);

public:

	// ExtObjCreatorImpl
	virtual HostWndIconObject* CreateObj(const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual void DestroyObj(HostWndIconObject* lpObj);
};

#endif // __HOSTWNDICONOBJECTCREATOR_H__