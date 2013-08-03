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
*   FileName    :   RotateObjectCreator
*   Author      :   李亚星
*   Create      :   2013-8-1 
*   LastChange  :   2013-8-1
*   History     :	
*
*   Description :   RotateObject的创建类
*
********************************************************************/ 
#ifndef __ROTATEOBJECTCREATOR_H__
#define __ROTATEOBJECTCREATOR_H__

#include "./RotateObject.h"

class RotateObjectCreator
	: public ExtObjCreatorImpl<RotateObject>
{
public:
	RotateObjectCreator(void);
	virtual ~RotateObjectCreator(void);

private:

	virtual RotateObject* CreateObj(const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual void DestroyObj(RotateObject* lpObj);
};

#endif // __ROTATEOBJECTCREATOR_H__