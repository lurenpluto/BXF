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