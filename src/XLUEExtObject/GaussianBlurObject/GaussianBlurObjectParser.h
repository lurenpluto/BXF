/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#ifndef __GAUSSIANBLUROBJECTPARSER_H__
#define __GAUSSIANBLUROBJECTPARSER_H__

#include "./GaussianBlurObject.h"

class GaussianBlurObjectParser
	: public ExtObjParserImpl<GaussianBlurObject>
{
public:
	GaussianBlurObjectParser(void);
	virtual ~GaussianBlurObjectParser(void);

private:

	// ExtObjParserImpl
	virtual bool ParserAttribute(GaussianBlurObject* lpObj, const char* key, const char* value);
};

#endif // __GAUSSIANBLUROBJECTPARSER_H__