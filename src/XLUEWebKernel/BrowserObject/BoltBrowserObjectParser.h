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
*   FileName    :   BoltBrowserObjectParser
*   Author      :   李亚星
*   Create      :   2013-6-6 
*   LastChange  :   2013-6-6
*   History     :	
*
*   Description :   BoltBrowserObject的解析器实现
*
********************************************************************/ 
#ifndef __BOLTBROWSEROBJECTPARSER_H__
#define __BOLTBROWSEROBJECTPARSER_H__

#include "./BoltBrowserObject.h"
#include "./WindowlessBoltBrowserObject.h"

class BaseBoltBrowserObjectParser
{
public:
	BaseBoltBrowserObjectParser();
	virtual ~BaseBoltBrowserObjectParser();

	bool ParserAttribute(BaseBoltBrowserObject* lpBaseObj, const char* key, const char* value );
};

class BoltBrowserObjectParser
	: public ExtObjParserImpl<BoltBrowserObject>,
	public BaseBoltBrowserObjectParser
{
public:
	BoltBrowserObjectParser(void);
	virtual ~BoltBrowserObjectParser(void);

private:

	// ExtObjParserImpl methods
	virtual bool ParserAttribute(BoltBrowserObject* lpObj, const char* /*key*/, const char* /*value*/);
};

class WindowlessBoltBrowserObjectParser
	: public ExtObjParserImpl<WindowlessBoltBrowserObject>,
	public BaseBoltBrowserObjectParser
{
public:
	WindowlessBoltBrowserObjectParser(void);
	virtual ~WindowlessBoltBrowserObjectParser(void);

private:

	// ExtObjParserImpl methods
	virtual bool ParserAttribute(obj_class* /*lpObj*/, const char* /*key*/, const char* /*value*/);
};


#endif // __BOLTBROWSEROBJECTPARSER_H__