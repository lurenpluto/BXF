#ifndef __SVGRESPARSER_H__
#define __SVGRESPARSER_H__

#include "./SvgRes.h"

class SvgResParser
    : public ExtResourceParserImplEx<SvgRes>
{
public:
    SvgResParser(void);
    virtual ~SvgResParser(void);

private:

    // ExtResourceParserImpl
    virtual bool ParseAttributeFromXML(SvgRes* lpResObj, const char* lpName, const char* lpValue);
    virtual bool ParseAttributeFromLua(SvgRes* lpResObj, const char* lpName, lua_State* luaState, int index);

};

#endif // __SVGRESPARSER_H__