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
*   FileName    :   NotifyIconObjectParser
*   Author      :   李亚星
*   Create      :   2013-10-14 
*   LastChange  :   2013-10-14
*   History     :	
*
*   Description :   NotifyIconObject的xml解析器
*
********************************************************************/ 
#ifndef __NOTIFYICONOBJECTPARSER_H__
#define __NOTIFYICONOBJECTPARSER_H__

#include "./NotifyIconObject.h"

class NotifyIconObjectParser
	: public ExtObjParserImpl<NotifyIconObject>
{
public:
	NotifyIconObjectParser(void);
	virtual ~NotifyIconObjectParser(void);

private:

	// ExtObjParserImpl
	virtual bool ParserAttribute(NotifyIconObject* lpObj, const char* key, const char* value);
};

#endif // __NOTIFYICONOBJECTPARSER_H__