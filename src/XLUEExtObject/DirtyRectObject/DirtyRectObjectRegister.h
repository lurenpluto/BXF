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
*   FileName    :   DirtyRectObjectRegister
*   Author      :   ÀîÑÇÐÇ
*   Create      :   2013-9-27 
*   LastChange  :   2013-9-27
*   History     :	
*
*   Description :   DirtyRectObjectµÄ×¢²áÆ÷
*
********************************************************************/ 
#ifndef __DIRTYRECTOBJECTREGISTER_H__
#define __DIRTYRECTOBJECTREGISTER_H__

#include "./DirtyRectObject.h"

class DirtyRectObjectRegister
{
public:
	static bool RegisterDirtyRectObject();
};

#endif // __DIRTYRECTOBJECTREGISTER_H__