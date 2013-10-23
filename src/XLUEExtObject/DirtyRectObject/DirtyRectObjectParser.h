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
*   FileName    :   DirtyRectObjectParser
*   Author      :   李亚星
*   Create      :   2013-9-27 
*   LastChange  :   2013-9-27
*   History     :	
*
*   Description :   DirtyRectObject的xml配置解析器
*
********************************************************************/ 
#ifndef __DIRTYRECTOBJECTPARSER_H__
#define __DIRTYRECTOBJECTPARSER_H__

#include "./DirtyRectObject.h"

class DirtyRectObjectParser
	: public ExtObjParserImpl<DirtyRectObject>
{
public:
	DirtyRectObjectParser(void);
	virtual ~DirtyRectObjectParser(void);

private:

	// ExtObjParserImpl
	virtual bool ParserAttribute(DirtyRectObject* lpObj, const char* key, const char* value);
};

#endif // __DIRTYRECTOBJECTPARSER_H__