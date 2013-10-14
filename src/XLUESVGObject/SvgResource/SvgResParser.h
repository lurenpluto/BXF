/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 

#ifndef __SVGRESPARSER_H__
#define __SVGRESPARSER_H__

#include "./SvgRes.h"

class SVGResParser
    : public ExtResourceParserImplEx<SVGRes>
{
public:
    SVGResParser(void);
    virtual ~SVGResParser(void);

private:

    // ExtResourceParserImpl
    virtual bool ParseAttributeFromXML(SVGRes* lpResObj, const char* lpName, const char* lpValue);
    virtual bool ParseAttributeFromLua(SVGRes* lpResObj, const char* lpName, lua_State* luaState, int index);

};

#endif // __SVGRESPARSER_H__