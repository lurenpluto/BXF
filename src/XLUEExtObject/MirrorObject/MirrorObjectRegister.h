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
*   FileName    :   MirrorObjectRegister
*   Author      :   李亚星
*   Create      :   2013-5-26 13:32
*   LastChange  :   2013-5-26 13:32
*   History     :	
*
*   Description :   MirrorObject的注册辅助类
*
********************************************************************/ 
#ifndef __MIRROROBJECTREGISTER_H__
#define __MIRROROBJECTREGISTER_H__

#define EXTCLASSNAME_MIRROROBJECT "MirrorObject"

class MirrorObjectRegister
{
public:

	static BOOL RegisterMirrorObject();
};

#endif // __MIRROROBJECTREGISTER_H__