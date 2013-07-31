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
*   FileName    :   HostWndIconObjectParser
*   Author      :   李亚星
*   Create      :   2013-7-29 
*   LastChange  :   2013-7-29
*   History     :	
*
*   Description :   HostWndIconObject的解析器
*
********************************************************************/ 
#ifndef __HOSTWNDICONOBJECTPARSER_H__
#define __HOSTWNDICONOBJECTPARSER_H__

#include "./HostWndIconObject.h"

class HostWndIconObjectParser
	: public ExtObjParserImpl<HostWndIconObject>
{
public:
	HostWndIconObjectParser(void);
	virtual ~HostWndIconObjectParser(void);

private:

	// ExtObjParserImpl
	virtual bool ParserAttribute(HostWndIconObject* lpObj, const char* key, const char* value);
};

#endif // __HOSTWNDICONOBJECTPARSER_H_