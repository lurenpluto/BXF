/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 
#include "stdafx.h"
#include "./SvgResParser.h"

SVGResParser::SVGResParser(void)
{
}

SVGResParser::~SVGResParser(void)
{
}

bool SVGResParser::ParseAttributeFromXML( SVGRes* lpResObj, const char* lpName, const char* lpValue )
{
    assert(lpResObj);
    assert(lpName);
    assert(lpValue);

    bool ret = true;

    if (::strcmp(lpName, "file") == 0)
    {
        lpResObj->SetFile(lpValue);
    }
    else
    {
        ret = false;
    }

    return ret;
}

bool SVGResParser::ParseAttributeFromLua( SVGRes* lpResObj, const char* lpName, lua_State* luaState, int index )
{
    assert(lpResObj);
    assert(lpName);
    assert(luaState);

    bool ret = true;

    if (::strcmp(lpName, "file") == 0)
    {
        const char* lpValue = luaL_checkstring(luaState, index);
        assert(lpValue);

        lpResObj->SetFile(lpValue);
    }
    else
    {
        assert(false);
        ret = false;
    }

    return ret;
}