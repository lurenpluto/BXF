/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 

#ifndef __SVGOBJECTPARSER_H__
#define __SVGOBJECTPARSER_H__

#include "./SvgObject.h"

class SvgObjectParser
	: public ExtObjParserImpl<SvgObject>
{
public:
	SvgObjectParser(void);
	virtual ~SvgObjectParser(void);

private:

	// ExtObjParserImpl
	virtual bool ParserAttribute(SvgObject* lpObj, const char* key, const char* value);
};

#endif // __SVGOBJECTPARSER_H__