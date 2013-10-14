/********************************************************************
/* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
/* Use of this source code is governed by a BOLT license that can be
/* found in the LICENSE file.
********************************************************************/ 

#ifndef __LUASVGRES_H__
#define __LUASVGRES_H__

#include "./SvgRes.h"

class LuaSVGRes
    : public ExtResourceLuaHostImplEx<LuaSVGRes, SVGRes>
{
public:
    LuaSVGRes(void);
    virtual ~LuaSVGRes(void);

public:

    static XLLRTGlobalAPI s_szLuaMemberFuncs[];
};

#endif // __LUAICONRES_H__