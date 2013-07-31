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
*   FileName    :   RippleObjectCreator
*   Author      :   ÀîÑÇÐÇ
*   Create      :   2013-5-28
*   LastChange  :   2013-5-28
*   History     :	
*
*   Description :   RippleObjectµÄcreator
*
********************************************************************/ 
#ifndef __RIPPLEOBJECTCREATOR_H__
#define __RIPPLEOBJECTCREATOR_H__

#include "./RippleObject.h"

class RippleObjectCreator
	: public ExtObjCreatorImpl<RippleObject>
{
public:
	RippleObjectCreator(void);
	virtual ~RippleObjectCreator(void);

private:

	virtual RippleObject* CreateObj(const char* lpObjClass, XLUE_LAYOUTOBJ_HANDLE hObj);
	virtual void DestroyObj(RippleObject* lpObj);
};

#endif // __RIPPLEOBJECTCREATOR_H__