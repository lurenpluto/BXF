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
*   FileName    :   NotifyIconObjectCreator
*   Author      :   李亚星
*   Create      :   2013-10-14 
*   LastChange  :   2013-10-14
*   History     :	
*
*   Description :   NotifyIconObject的创建器
*
********************************************************************/ 
#ifndef __NOTIFYICONOBJECTCREATOR_H__
#define __NOTIFYICONOBJECTCREATOR_H__

#include "./NotifyIconObject.h"

class NotifyIconObjectCreator
	: public ExtObjCreatorImpl<NotifyIconObject>
{
public:
	NotifyIconObjectCreator(void);
	virtual ~NotifyIconObjectCreator(void);

private:

	// ExtObjCreatorImpl
	virtual NotifyIconObject* CreateObj(const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual void DestroyObj(NotifyIconObject* lpObj);
};

#endif // __NOTIFYICONOBJECTCREATOR_H__