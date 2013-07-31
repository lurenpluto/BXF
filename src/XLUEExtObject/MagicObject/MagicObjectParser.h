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
*   FileName    :   MagicObjectParser
*   Author      :   李亚星
*   Create      :   2013-5-20 0:32
*   LastChange  :   2013-5-20 0:32
*   History     :	
*
*   Description :   MagicObject的xml定义解析器
*
********************************************************************/ 
#ifndef __MAGICOBJECTPARSER_H__
#define __MAGICOBJECTPARSER_H__

#include "./MagicObject.h"

class MagicObjectParser
	: public ExtObjParserImpl<MagicObject>
{
public:
	MagicObjectParser(void);
	virtual ~MagicObjectParser(void);

private:

	// ExtObjParserImpl
	virtual bool ParserAttribute(MagicObject* lpObj, const char* key, const char* value);
};

#endif // __MAGICOBJECTPARSER_H__