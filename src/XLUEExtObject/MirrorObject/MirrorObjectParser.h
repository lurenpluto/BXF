/********************************************************************
*
* =-----------------------------------------------------------------=
* =                                                                 =
* =             Copyright (c) Xunlei, Ltd. 2004-2013              =
* =                                                                 =
* =-----------------------------------------------------------------=
* 
*   FileName    :   MirrorObjectParser
*   Author      :   李亚星
*   Create      :   2013-5-26 13:30
*   LastChange  :   2013-5-26 13:30
*   History     :	
*
*   Description :   MirrorObject的xml定义解析器
*
********************************************************************/ 
#ifndef __MIRROROBJECTPARSER_H__
#define __MIRROROBJECTPARSER_H__

#include "./MirrorObject.h"

class MirrorObjectParser
	: public ExtObjParserImpl<MirrorObject>
{
public:
	MirrorObjectParser(void);
	virtual ~MirrorObjectParser(void);

private:

	// ExtObjParserImpl
	virtual bool ParserAttribute(MirrorObject* lpObj, const char* key, const char* value);
};

#endif // __MIRROROBJECTPARSER_H__