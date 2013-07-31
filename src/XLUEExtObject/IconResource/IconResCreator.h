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
*   FileName    :   IconResCreator
*   Author      :   李亚星
*   Create      :   2013-7-29 
*   LastChange  :   2013-7-29
*   History     :	
*
*   Description :   ICON扩展资源类型的创建器
*
********************************************************************/ 
#ifndef __ICONRESCREATOR_H__
#define __ICONRESCREATOR_H__

#include "./IconRes.h"

class IconResCreator
	: public ExtResourceCreatorImpl<IconRes>
{
public:
	IconResCreator(void);
	virtual ~IconResCreator(void);

private:

	// ExtResourceCreatorImpl
	virtual IconRes* CreateResource(const char* lpResType, XLUE_RESOURCE_HANDLE hResHandle);
	virtual void DestroyResource(IconRes* lpResObj);
};

#endif // __ICONRESCREATOR_H__