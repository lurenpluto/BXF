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
*   FileName    :   RotateObjectParser
*   Author      :   李亚星
*   Create      :   2013-8-1 
*   LastChange  :   2013-8-1
*   History     :	
*
*   Description :   RotateObject的xml解析器
*
********************************************************************/ 
#ifndef __ROTATEOBJECTPARSER_H__
#define __ROTATEOBJECTPARSER_H__

#include "./RotateObject.h"

class RotateObjectParser
	: public ExtObjParserImpl<RotateObject>
{
public:
	RotateObjectParser(void);
	virtual ~RotateObjectParser(void);

private:

	// ExtObjParserImpl
	virtual bool ParserAttribute(RotateObject* lpObj, const char* key, const char* value);
};

#endif // __ROTATEOBJECTPARSER_H__