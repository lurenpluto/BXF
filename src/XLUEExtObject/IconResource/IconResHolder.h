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
*   FileName    :   IconResHolder
*   Author      :   李亚星
*   Create      :   2013-7-29 
*   LastChange  :   2013-7-29
*   History     :	
*
*   Description :   ICON资源的holder封装类
*
********************************************************************/ 
#ifndef __ICONRESHOLDER_H__
#define __ICONRESHOLDER_H__

#include "./IconRes.h"

class IconResTraits
	: public ExtResTraits<IconResTraits>
{
public:

	static const char* GetResType()
	{
		return XLUE_EXTRES_ICON;
	}
};

typedef BaseResHolder<IconResTraits> IconResHolder;

#endif // __ICONRESHOLDER_H__