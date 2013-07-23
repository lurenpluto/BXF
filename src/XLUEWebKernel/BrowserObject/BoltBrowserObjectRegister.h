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
*   FileName    :   BoltBrowserObjectRegister
*   Author      :   李亚星
*   Create      :   2013-6-6 
*   LastChange  :   2013-6-26
*   History     :	
*
*   Description :   BoltBrowserObject和WindowlessBoltBrowserObject的注册辅助类
*
********************************************************************/ 
#ifndef __BOLTBROWSEROBJECTREGISTER_H__
#define __BOLTBROWSEROBJECTREGISTER_H__

#define EXTCLASSNAME_BOLTBROWSEROBJECT "BoltBrowserObject"
#define EXTCLASSNAME_WINDOWLESSBOLTBROWSEROBJECT "WindowlessBoltBrowserObject"

class BoltBrowserObjectRegister
{
public:
	static BOOL RegisterBoltBrowserObject();
};

class WindowlessBoltBrowserObjectRegister
{
public:
	static BOOL RegisterWindowlessBoltBrowserObject();
};


#endif // __BOLTBROWSEROBJECTREGISTER_H__