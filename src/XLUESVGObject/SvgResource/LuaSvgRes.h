#ifndef __LUASVGRES_H__
#define __LUASVGRES_H__

#include "./SvgRes.h"

class LuaSvgRes
    : public ExtResourceLuaHostImplEx<LuaSvgRes, SvgRes>
{
public:
    LuaSvgRes(void);
    virtual ~LuaSvgRes(void);

public:

    static XLLRTGlobalAPI s_szLuaMemberFuncs[];
};

#endif // __LUAICONRES_H__